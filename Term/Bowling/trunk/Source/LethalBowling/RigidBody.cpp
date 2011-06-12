#include "RigidBody.h"

#include "Collision.h"
#include "World.h"
#include "Physics.h"
#include "TMath.h"
#include "Geometric.h"
#include "Edge.h"

namespace Virgin
{

RigidBody::RigidBody()
    : mass_(0.0f)
    , speed_(0.0f)
    , radius_(0.0f)
{
}

void RigidBody::Update(TimeSpan timeSpan)
{
    float dTime = static_cast<float>(timeSpan.TotalSeconds());

    // �ϴ� �׽�Ʈ������ �ӵ��� ó��, ������ ������ �ְԲ� ��
    location_ += velocity_ * speed_ * dTime;
}

// * ����: RigidBody::mass_ �� 0.0�� ��� ���ӵ� ���� �� Divide by Zero ���� �߻��� �� ����
void RigidBody::CalcObjectForces()
{
    Vector3 Fb, Mb;
    Vector3 vDragVector;
    Vector3 vAngularDragVector;
    Vector3 ContactForce;
    Vector3 pt;
    CollisionType collisionType = CollisionType_NoCollision;
    //Collision* collisionData;    // ���⼭ �������� ���(Predicated, ��� World::Collsions() ���)
    Vector3 FrictionForce;
    Vector3 fDir;

    for(uint i = 0; i < World::Instance().Sprites().size(); ++i)
    {
        RigidBody& rigidBody = World::Instance().Sprites()[i]->GetRigidBody();

        // ���� ���Ʈ�� �缳��
        rigidBody.forces_.Reset();
        rigidBody.moments_.Reset();

        if(rigidBody.mass_ == 0.0f)
        {
            continue;
        }

        // �߷� ���� ����, �����߽ɿ� �ۿ� 
        // * Predicated, ���༱��
        /*if(i == CAR)
        {
            Thrust.X = 1.0f;
            Thrust.Y = 0.0f;
            Thrust.Z = 0.0f;
            Thrust *= ThrustForce;
            Fb += Thrust;
        }*/

        //
        // ����ڰ� ���� ���� ��
        //
        Fb += rigidBody.immediateForce_;
        rigidBody.immediateForce_.Reset();

        //// �׷� ����
        //vDragVector = -rigidBody.velocityBody;
        //vDragVector.Normalize();
        //Fb += vDragVector * (rigidBody.speed_ * rigidBody.speed_ * Physics::AirDensity * Physics::LinearDragCoefficient * rigidBody.radius_ * rigidBody.radius_);

        //vAngularDragVector = -rigidBody.angularVelocity_;
        //vAngularDragVector.Normalize();
        //Mb += vAngularDragVector * (rigidBody.angularVelocity_.Size() * rigidBody.angularVelocity_.Size() * Physics::AirDensity * Physics::AngularDragCoefficient * rigidBody.radius_ * rigidBody.radius_);

        

        // ���� �� �������� ��ü �������� ��ȯ
        rigidBody.forces_ = rigidBody.orientation_.VRotate(Fb);

        // �߷� �ۿ�
        rigidBody.forces_.Y += Physics::Gravity * rigidBody.mass_;

        // ���Ʈ ����
        rigidBody.moments_ += Mb;

        // ������ �����ϴ� ��Ȳ ó��
        rigidBody.acceleration_ = rigidBody.forces_ / rigidBody.mass_;
        rigidBody.angularAcceleration_ = rigidBody.inertiaInverse_ * (rigidBody.moments_ - rigidBody.angularVelocity_.Cross(rigidBody.inertia_ * rigidBody.angularVelocity_));
        
        vector<Collision>& collisions = World::Instance().Collisions();
        collisions.clear();
        collisionType = CheckGroundPlaneContacts(rigidBody);
        if(collisionType == CollisionType_Contact)
        {
            // ���� ������
            for(uint j = 0; j < collisions.size(); ++j)
            {
                ContactForce = (rigidBody.mass_/collisions.size() * (-collisions[j].relativeAcceleration.Dot(collisions[j].collisionNormal))) * collisions[j].collisionNormal;
                FrictionForce = (ContactForce.Size() * Physics::FrictionCoefficient) * collisions[j].collisionTangent;
                rigidBody.forces_ += ContactForce;
                rigidBody.forces_ += FrictionForce;
                
                ContactForce = (~rigidBody.orientation_).VRotate(ContactForce);
                FrictionForce = (~rigidBody.orientation_).VRotate(FrictionForce);
                pt = collisions[j].collisionPoint - rigidBody.location_;
                rigidBody.moments_ += pt.Cross(ContactForce);
                rigidBody.moments_ += pt.Cross(FrictionForce);
            }
        }
    }
}

CollisionType RigidBody::CheckGroundPlaneCollisions(RigidBody& rigidBody)
{
	Vector3 v1[BoxVertexCount];
	Vector3 tmp;
	Vector3 u, v;
	float d;	
	Vector3 f[4];
	Vector3 vel1;
	Vector3 pt1;
	Vector3 Vr;
	float Vrn;
	Vector3 n;
	CollisionType collisionType = CollisionType_NoCollision;

	//rotate bounding vertices and covert to global coordinates
	for(int i = 0; i < BoxVertexCount; ++i)
	{
		tmp = rigidBody.vertexList_[i];
        v1[i] = rigidBody.orientation_.VRotate(tmp);
		v1[i] += rigidBody.location_;
	}

	//check each vertex of body i against each face of body j
	for(int i = 0; i < BoxVertexCount; ++i)
	{
		// Check the ground plane
		
        if(v1[i].Z < Collision::CollisionTolerance)
		{
			// calc relative velocity, if <0 collision
			pt1 = v1[i] - rigidBody.location_;

				
            vel1 = rigidBody.velocity_ + (rigidBody.angularVelocityGlobal_.Cross(pt1));
			
			
			n.X = 0;
			n.Y = 0;
			n.Z = 1;
				
			Vr = vel1;
			Vrn = Vr.Dot(n);
				
			if(Vrn < 0.0f)
			{
                vector<Collision>& collisions = World::Instance().Collisions();
                vector<Sprite*>& sprites = World::Instance().Sprites();

				// have a collision, fill the data structure and return
				//assert(NumCollisions < (NUMBODIES*16));
				if(collisions.size() < (sprites.size() * 16))
				{
                    Collision collision;
                    collision.body1 = const_cast<RigidBody*>(&rigidBody);
                    collision.body2 = nullptr;
                    collision.collisionNormal = n;
                    collision.collisionPoint = v1[i];
                    collision.relativeVelocity = Vr;

                    collision.collisionTangent = (n.Cross(Vr)).Cross(n);
                    collision.collisionTangent.Reverse();
                    collision.collisionTangent.Normalize();
                        
                    collisions.push_back(collision);
                    collisionType = CollisionType_Collision;
				}				
			}
		}


	}

	return collisionType;
}

CollisionType RigidBody::CheckGroundPlaneContacts(const RigidBody& rigidBody)
{
    Vector3 v1[BoxVertexCount];
    Vector3 tmp;
    Vector3 u, v;
    float d;
    Vector3 f[4];
    Vector3 vel1;
    Vector3 pt1;
    Vector3 Vr; // ���ӵ�(Velocity Relative)
    float Vrn;
    Vector3 n;
    CollisionType collisionType = CollisionType_NoCollision;
    Vector3 Ar; // ��밡�ӵ�(Acceleration Relative)
    float Arn;

    // ��� �������� ȸ�����Ѽ� ��ü ��ǥ�� ��ȯ
    for(int i = 0; i < BoxVertexCount; ++i)
    {
        tmp = rigidBody.vertexList_[i];
        v1[i] = rigidBody.orientation_.VRotate(tmp);
        v1[i] += rigidBody.location_;
    }

    // ������ �� �������� ����鿡 ����� Ȯ��
    for(int i = 0; i < BoxVertexCount; ++i)
    {
        // * Todo: �츮�� X, Y�� �ٴ��� �ƴϰ� Z, X ����� �ٴ��̹Ƿ� ������ �ؾ� �� ��
        // u: X�� ���� ����
        u.X = 0.0f;
        u.Y = 0.0f;
        u.Z = 1.0f;
        // v: Y�� ���� ����
        v.X = 1.0f;
        v.Y = 0.0f;
        v.Z = 0.0f;
        tmp.Reset();

        d = Geometric::DistanceFromPointToPlane(v1[i], u, v, tmp);
        if(d < Physics::CollisionTolerance)
        {
            // ��� �ӵ� ���
            pt1 = v1[i] - rigidBody.location_;

            /*vel1 = rigidBody.velocityBody + (rigidBody.angularVelocity_.Cross(pt1));
            vel1 = rigidBody.orientation_.VRotate(vel1);*/
            vel1 = rigidBody.velocity_ + (rigidBody.angularVelocityGlobal_.Cross(pt1));

            n = u.Cross(v);
            n.Normalize();

            Vr = vel1;
            Vrn = Vr.Dot(n);

            if(Math::Abs(Vrn) <= /*Math::Sqrt(2*(-Physics::Gravity)*Collision::ContactTolerance)*/ Physics::VelocityTolerance /*sqrt(2*32.174*CONTACTTOLERANCE)*/ )    // ���� // * Todo: �񱳰� ��ü
            {
                // ���� ��� ���ӵ� Ȯ��
                Ar = rigidBody.acceleration_ + (rigidBody.angularVelocity_.Cross(rigidBody.angularVelocity_.Cross(pt1))) + (rigidBody.angularAcceleration_.Cross(pt1));

                Arn = Ar.Dot(n);

                if(Arn <= 0.0f)
                {
                    vector<Collision>& collisions = World::Instance().Collisions();
                    vector<Sprite*>& sprites = World::Instance().Sprites();
                    
                    // ������ �����̰�, ������ ����ü�� ä���, ���ư���
                    //assert(collisions.size() < sprites.size() * BoxVertexCount);

                    if(collisions.size() < sprites.size() * BoxVertexCount)
                    {
                        Collision collision;
                        collision.body1 = const_cast<RigidBody*>(&rigidBody);
                        collision.body2 = nullptr;
                        collision.collisionNormal = n;
                        collision.collisionPoint = v1[i];
                        collision.relativeVelocity = Vr;
                        collision.relativeAcceleration = Ar;
                        collision.collisionTangent = -(Vr - ((Vr.Dot(n)) * n));
                        // ���� ������ ������ ���̶�� ���� ���� �ӵ��� �ݴ� ������ ��Ÿ��
                        // ���߿� ������ ó���ϱ� ����

                        collision.collisionTangent.Normalize();
                        
                        collisions.push_back(collision);
                        collisionType = CollisionType_Contact;
                    }
                }
            }
        }
    }

    return collisionType;
}

// ���Ϸ� ��� �̿�(����)
// * ����: ����(mass)�� 0.0�� ��� ���ӵ��� ���Ѵ밡 ��
void RigidBody::StepSimulation(TimeSpan timeDelta)
{
    int turn = 0;  // �ð� 1/2�� �� �� ���� ȸ���� �� (1ȸ��, 2ȸ��, ...)
    bool doCheckPenetration = Geometric::DoPenetrationCheck;
    Vector3 Ae; // ���ӵ�
    float dt = static_cast<float>(timeDelta.TotalSeconds());

    // ��� ��ü�� �ۿ��ϴ� ���� ���Ʈ�� ���� ���
    CalcObjectForces();

tryagain:

    // ����
    vector<Sprite*>& sprites = World::Instance().Sprites();
    for(uint i = 0; i < sprites.size(); ++i)
    {
        RigidBody& rigidBody = sprites[i]->GetRigidBody();

        if(rigidBody.mass_ == 0.0f)
        {
            continue;
        }

        // ��ü ��ǥ���� ���ӵ� ���
        Ae = rigidBody.forces_ / rigidBody.mass_;
        rigidBody.acceleration_ = Ae;

        // ��ü ��ǥ���� �ӵ� ���
        rigidBody.velocity_ += Ae * dt;

        // ��ü ��ǥ���� ��ġ ���
        rigidBody.location_ += rigidBody.velocity_ * dt;

        // ȸ��� ó��
        float mag;
        rigidBody.angularAcceleration_ = rigidBody.inertiaInverse_ * (rigidBody.moments_ - (rigidBody.angularVelocity_.Cross(rigidBody.inertia_ * rigidBody.angularVelocity_)));
        rigidBody.angularVelocity_ = rigidBody.angularAcceleration_ * dt;

        // ȸ�� ����� ���� ���
        rigidBody.orientation_ += (rigidBody.orientation_ * rigidBody.angularVelocity_) * (0.5f * dt);

        // ���� ����� �԰�ȭ
        mag = rigidBody.orientation_.Size();
        if(mag != 0.0)
        {
            rigidBody.orientation_ /= mag;
        }

        // ��ü �������� �ӵ� ��� (we'll need this to calculate lift and drag forces)
        rigidBody.velocityBody = (~rigidBody.orientation_).VRotate(rigidBody.velocity_);

		// get the angular velocity in global coords:
        rigidBody.angularVelocityGlobal_ = rigidBody.orientation_.VRotate(rigidBody.angularVelocity_);

		// get the angular acceleration in global coords:
        rigidBody.angularAccelerationGlobal_ = rigidBody.orientation_.VRotate(rigidBody.angularAcceleration_);
		
		// Get the inverse intertia tensor in global coordinates
		Matrix3 R, RT;		
		R = rigidBody.orientation_.ToMatrix();
		RT = R.Transpose();
        rigidBody.ieInverse_ = R * rigidBody.inertiaInverse_ * RT;

        // �ӷ� ���
        rigidBody.speed_ = rigidBody.velocity_.Size();

        // ���Ϸ� �� ���ϱ�
        Vector3 u;

        u = rigidBody.orientation_.ToEulerAngles();
        rigidBody.eulerAngles_.X = u.X; // roll
        rigidBody.eulerAngles_.Y = u.Y; // pitch
        rigidBody.eulerAngles_.Z = u.Z; // yaw
    }

    // �浹 ó��
    CollisionType collisionType = CheckForCollisions(doCheckPenetration);
    if(collisionType == CollisionType_Collision || collisionType == CollisionType_Penetrating)
    {
        ResolveCollisions();
    }
    else if(collisionType == CollisionType_Penetrating)
    {
// * �ǹ���: ���⼭ i�� RigidBody�� Count�� �������� �Ǽ� �ᱹ �ε����� ����µ�... �� ���ư� ��?

  //      // back up -dt and try again at dt/2
		//dt = -dt;

		//// calculate the acceleration of the airplane in earth space:
		//Ae = Bodies[i].vForces / Bodies[i].mass_;
		//Bodies[i].vAcceleration = Ae;

		//// calculate the velocity of the airplane in earth space:
		//Bodies[i].velocity_ += Ae * dt;

		//// calculate the position of the airplane in earth space:
		//Bodies[i].location_ += Bodies[i].velocity_ * dt;

		//// Now handle the rotations:
		//float		mag;

		//Bodies[i].vAngularAcceleration = Bodies[i].mInertiaInverse * 
		//								(Bodies[i].vMoments - 
		//								(Bodies[i].vAngularVelocity^
		//								(Bodies[i].mInertia * Bodies[i].vAngularVelocity)));													

		//Bodies[i].vAngularVelocity += Bodies[i].vAngularAcceleration * dt;	

		//// calculate the new rotation quaternion:
		//Bodies[i].qOrientation +=	(Bodies[i].qOrientation * Bodies[i].vAngularVelocity) *									
		//							(0.5f * dt);

		//// now normalize the orientation quaternion:
		//mag = Bodies[i].qOrientation.Magnitude();
		//if (mag != 0)
		//	Bodies[i].qOrientation /= mag;

		//// calculate the velocity in body space:
		//// (we'll need this to calculate lift and drag forces)
		//Bodies[i].vVelocityBody = QVRotate(~Bodies[i].qOrientation, Bodies[i].velocity_);


		//// get the angular velocity in global coords:
		//Bodies[i].angularVelocityGlobal_ = QVRotate(Bodies[i].qOrientation, Bodies[i].vAngularVelocity);

		//// get the angular acceleration in global coords:
		//Bodies[i].vAngularAccelerationGlobal = QVRotate(Bodies[i].qOrientation, Bodies[i].vAngularAcceleration);
		//
		//// Get the inverse intertia tensor in global coordinates
		//Matrix3x3 R, RT;		
		//R = MakeMatrixFromQuaternion(Bodies[i].qOrientation);
		//RT = R.Transpose();
		//Bodies[i].ieInverse_ = R * Bodies[i].mInertiaInverse * RT;

		//
		//// calculate the air speed:
		//Bodies[i].fSpeed = Bodies[i].velocity_.Magnitude();

		//// get the Euler angles for our information
		//Vector3 u;
		//
		//u = MakeEulerAnglesFromQ(Bodies[i].qOrientation);
		//Bodies[i].vEulerAngles.X = u.X;	// roll
		//Bodies[i].vEulerAngles.Y = u.Y;	// pitch
		//Bodies[i].vEulerAngles.Z = u.Z;	// yaw

		//dt = -dt;
		//dt = dt/2;
		//turn++;
		//if(turn < 10)
		//	goto tryagain;
		//else
		//{
		//	doCheckPenetration = false;
		//	//dt = dtime/2;
		//	goto tryagain;
		//}
    }
    
    // * Todo: ���� �� timeDelta 1/2�� �翬��
}

CollisionType RigidBody::CheckForCollisions(bool doCheckPenetration)
{
    CollisionType collisionType = CollisionType_NoCollision;
    CollisionType check = CollisionType_NoCollision;
	Vector3 d;  // ��ü 1, 2 ������ ���� ��(����;�Ÿ�)
	
    vector<Collision>& collisions = World::Instance().Collisions();
    collisions.clear();
	
	// check object collisions with each other	
    vector<Sprite*>& sprites = World::Instance().Sprites();
	for(uint i = 0; i < sprites.size(); ++i)
	{
        RigidBody& rigidBody1 = sprites[i]->GetRigidBody();

		for(uint j = 0; j < sprites.size(); ++j)
        {
            if(i == j) // don't check object against itself
            {
                continue;
            }
			
            RigidBody& rigidBody2 = sprites[j]->GetRigidBody();

            // do a bounding sphere check first	
            d = rigidBody1.location_ - rigidBody2.location_;
			if(d.Size() < (rigidBody1.radius_ + rigidBody2.radius_))				
			{
                // possible collision
				if(doCheckPenetration)
                {
					check = IsPenetrating(rigidBody1, rigidBody2);
                }

				if(check == CollisionType_Penetrating)
				{
					collisionType = CollisionType_Penetrating;
					break;
				} 
                else 
                {
					check = CheckBoxCollision(rigidBody1, rigidBody2);
                    if(check == CollisionType_Collision)
					{
						collisionType = CollisionType_Collision;
					}
				}
			}
			
        }

        if(collisionType == CollisionType_Penetrating) 
			break;
	}

	if(collisionType != CollisionType_Penetrating)
	{
		// check object collisions with the ground	
		for(uint i = 0; i < sprites.size(); ++i)
		{
            RigidBody& rigidBody = sprites[i]->GetRigidBody();

			if(doCheckPenetration)
            {
				check = IsPenetratingGround(rigidBody);
            }

            if(check == CollisionType_Penetrating)
			{
				collisionType = CollisionType_Penetrating;
				break;
			} 
            else 
            {
				check = CheckGroundPlaneCollisions(rigidBody);
				if(check == CollisionType_Collision)
				{
					collisionType = CollisionType_Collision;
				}
			}
		}
	}
	
	return collisionType;
}

CollisionType RigidBody::IsPenetrating(const RigidBody& rigidBody1, const RigidBody& rigidBody2)
{
	Vector3 v1[BoxVertexCount];
	Vector3 v2[BoxVertexCount];
	Vector3 tmp;
	Vector3 u, v;
	float d;	
	Vector3 f[4];
	Vector3 vel1, vel2;
	Vector3 pt1, pt2;
	Vector3 Vr;	
	Vector3 n;
	CollisionType collisionType = CollisionType_NoCollision;
	bool outside = false;

	//rotate bounding vertices and covert to global coordinates
    vector<Sprite*>& sprites = World::Instance().Sprites();
	for(int i = 0; i < BoxVertexCount; ++i)
	{
		tmp = rigidBody1.vertexList_[i];
        v1[i] = rigidBody1.orientation_.VRotate(tmp);
        v1[i] += rigidBody1.location_;

		tmp = rigidBody2.vertexList_[i];
        v2[i] = rigidBody2.orientation_.VRotate(tmp);
        v2[i] = rigidBody2.location_;
	}
	
	//check each vertex of body 1 against each face of body 2
	for(int i = 0; i < BoxVertexCount; ++i)
	{
		outside = false;

		// Front face of body 2:
		u = v2[1] - v2[0];
		v = v2[3] - v2[0];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
		if(d > -Collision::PenetrationTolerance) 
        {
			outside = true;
        }
	
		// Aft face of body 2:   
		v = v2[6] - v2[7];
		u = v2[4] - v2[7];
        d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
        if(d > -Collision::PenetrationTolerance) 
        {
			outside = true;
        }

		// Top face of body 2:  
		v = v2[2] - v2[6];
		u = v2[5] - v2[6];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
		if(d > -Collision::PenetrationTolerance) 
        {
            outside = true;
        }

		// Bottom face of body 2:
		u = v2[0] - v2[4];
		v = v2[7] - v2[4];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
		if(d > -Collision::PenetrationTolerance) 
        {
			outside = true;
        }

		// Left face of body 2:   
		v = v2[5] - v2[4];
		u = v2[0] - v2[4];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
		if(d > -Collision::PenetrationTolerance) 
        {
			outside = true;
        }

		// Right face of body 2:
		u = v2[6] - v2[2];
		v = v2[3] - v2[2];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, u);
		if(d > -Collision::PenetrationTolerance) 
        {
			outside = true;
        }

		if(!outside)
        {
			return CollisionType_Penetrating;
        }
			
	}

    return collisionType;
}


CollisionType RigidBody::IsPenetratingGround(const RigidBody& rigidBody)
{
	Vector3	v1[BoxVertexCount];
	
	Vector3	tmp;
	Vector3	u, v;
	
	Vector3	f[4];
	Vector3	vel1;
	Vector3	pt1;
	Vector3	Vr;
	
	Vector3	n;
	CollisionType	status = CollisionType_NoCollision;
	bool	inside = true;
	int		c = 0;

	//rotate bounding vertices and covert to global coordinates
	for(int i = 0; i < BoxVertexCount; i++)
	{ 
		tmp = rigidBody.vertexList_[i];
		v1[i] = rigidBody.orientation_.VRotate(tmp);
		v1[i] += rigidBody.location_;//+ Bodies[body1].vVelocity*0.0005;
	}
	
	//check each vertex of body 1 against ground plane
	for(int i = 0; i < BoxVertexCount; i++)
	{
        if(v1[i].Z <=  -Collision::CollisionTolerance) // should this be the collision tolerance
			return CollisionType_Penetrating;			
	}
	return status;

}

CollisionType RigidBody::CheckBoxCollision(const RigidBody& rigidBody1, const RigidBody& rigidBody2)
{
	CollisionType status1 = CollisionType_NoCollision;
	CollisionType status2 = CollisionType_NoCollision;
	CollisionType status3 = CollisionType_NoCollision;
	
	status1 = CheckVertexFaceCollisions(rigidBody1, rigidBody2);
	status2 = CheckVertexEdgeCollisions(rigidBody1, rigidBody2);
	status3 = CheckEdgeEdgeCollisions(rigidBody1, rigidBody2);

	if((status1 == CollisionType_Penetrating) || (status2 == CollisionType_Penetrating) || (status3 == CollisionType_Penetrating))
    {
		return CollisionType_Penetrating;
    }
	else if((status1 == CollisionType_Collision) || (status2 == CollisionType_Collision) || (status3 == CollisionType_Collision))
    {
        return CollisionType_Collision;
    }
	else
    {
        return CollisionType_NoCollision;
    }

}

CollisionType RigidBody::CheckVertexFaceCollisions(const RigidBody& rigidBody1, const RigidBody& rigidBody2)
{
	Vector3 v1[BoxVertexCount];
	Vector3 v2[BoxVertexCount];
	Vector3 tmp;
	Vector3 u, v;
	float d;	
	Vector3 f[4];
	Vector3 vel1, vel2;
	Vector3 pt1, pt2;
	Vector3 Vr;
	float Vrn;
	Vector3 n;
    CollisionType status = CollisionType_NoCollision;
	bool inside = true;

	//rotate bounding vertices and covert to global coordinates
	for(int i = 0; i < BoxVertexCount; ++i)
	{
		tmp = rigidBody1.vertexList_[i];
        v1[i] = rigidBody1.orientation_.VRotate(tmp);
		v1[i] += rigidBody1.location_;

		tmp = rigidBody2.vertexList_[i];
        v2[i] = rigidBody2.orientation_.VRotate(tmp);
		v2[i] += rigidBody2.location_;
	}

	//check each vertex of body i against each face of body j
    for(int i = 0; i < BoxVertexCount; ++i)
	{
		inside = true;
		// Front face of body 2:
		u = v2[1] - v2[0];
		v = v2[3] - v2[0];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, v2[0]);		
        if(d < Collision::CollisionTolerance)
		{
			f[0] = v2[0]; 
			f[1] = v2[1]; 
			f[2] = v2[2]; 
			f[3] = v2[3]; 
			if(Geometric::IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - rigidBody1.location_;
				pt2 = v1[i] - rigidBody2.location_;

				
				vel1 = rigidBody1.velocity_ + (rigidBody1.angularVelocityGlobal_.Cross(pt1));
				vel2 = rigidBody2.velocity_ + (rigidBody2.angularVelocityGlobal_.Cross(pt2));

				
				n = u.Cross(v);
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr.Dot(n);

				if(Vrn < 0.0f)
				{
                    vector<Collision>& collisions = World::Instance().Collisions();
                    vector<Sprite*>& sprites = World::Instance().Sprites();

					// have a collision, fill the data structure and return
					//assert(NumCollisions < (NUMBODIES*16));
					if(collisions.size() < (sprites.size() * 16))
					{
                        Collision collision;
                        collision.body1 = const_cast<RigidBody*>(&rigidBody1);
                        collision.body2 = const_cast<RigidBody*>(&rigidBody2);
                        collision.collisionNormal = n;
                        collision.collisionPoint = v1[i];
                        collision.relativeVelocity = Vr;
                        collision.collisionTangent = (n.Cross(Vr)).Cross(n);
                        collision.collisionTangent.Normalize();
                        
                        collisions.push_back(collision);

                        status = CollisionType_Collision;
					}									
				}
			}
		}


		// Aft face of body 2:
		v = v2[6]-v2[7];
		u = v2[4]-v2[7];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, v2[7]);		
        if(d < Collision::CollisionTolerance)
		{
			f[0] = v2[7]; 
			f[1] = v2[6]; 
			f[2] = v2[5]; 
			f[3] = v2[4]; 
			if(Geometric::IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - rigidBody1.location_;
				pt2 = v1[i] - rigidBody2.location_;

				
				vel1 = rigidBody1.velocity_ + (rigidBody1.angularVelocityGlobal_.Cross(pt1));
				vel2 = rigidBody2.velocity_ + (rigidBody2.angularVelocityGlobal_.Cross(pt2));

				
				n = u.Cross(v);
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr.Dot(n);
				
				if(Vrn < 0.0f)
				{
                    vector<Collision>& collisions = World::Instance().Collisions();
                    vector<Sprite*>& sprites = World::Instance().Sprites();

					// have a collision, fill the data structure and return
					//assert(NumCollisions < (NUMBODIES*16));
					if(collisions.size() < (sprites.size() * 16))
					{
                        Collision collision;
                        collision.body1 = const_cast<RigidBody*>(&rigidBody1);
                        collision.body2 = const_cast<RigidBody*>(&rigidBody2);
                        collision.collisionNormal = n;
                        collision.collisionPoint = v1[i];
                        collision.relativeVelocity = Vr;
                        collision.collisionTangent = (n.Cross(Vr)).Cross(n);
                        collision.collisionTangent.Normalize();
                        
                        collisions.push_back(collision);

                        status = CollisionType_Collision;
					}									
				}
			}
		}

		// Top face of body 2:
		v = v2[2] - v2[6];
		u = v2[5] - v2[6];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, v2[6]);		
        if(d < Collision::CollisionTolerance)
		{
			f[0] = v2[6]; 
			f[1] = v2[2]; 
			f[2] = v2[1]; 
			f[3] = v2[5]; 
			if(Geometric::IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - rigidBody1.location_;
				pt2 = v1[i] - rigidBody2.location_;

			
                vel1 = rigidBody1.velocity_ + (rigidBody1.angularVelocityGlobal_.Cross(pt1));
                vel2 = rigidBody2.velocity_ + (rigidBody2.angularVelocityGlobal_.Cross(pt2));

				
                n = u.Cross(v);
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr.Dot(n);
				
				if(Vrn < 0.0f)
				{
                    vector<Collision>& collisions = World::Instance().Collisions();
                    vector<Sprite*>& sprites = World::Instance().Sprites();

					// have a collision, fill the data structure and return
					//assert(NumCollisions < (NUMBODIES*16));
					if(collisions.size() < (sprites.size() * 16))
					{
                        Collision collision;
                        collision.body1 = const_cast<RigidBody*>(&rigidBody1);
                        collision.body2 = const_cast<RigidBody*>(&rigidBody2);
                        collision.collisionNormal = n;
                        collision.collisionPoint = v1[i];
                        collision.relativeVelocity = Vr;
                        collision.collisionTangent = (n.Cross(Vr)).Cross(n);
                        collision.collisionTangent.Normalize();
                        
                        collisions.push_back(collision);

                        status = CollisionType_Collision;
					}									
				}
			}
		}

		// Bottom face of body 2:
		u = v2[0] - v2[4];
		v = v2[7] - v2[4];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, v2[4]);		
        if(d < Collision::CollisionTolerance)
		{
			f[0] = v2[4]; 
			f[1] = v2[0]; 
			f[2] = v2[3]; 
			f[3] = v2[7]; 
			if(Geometric::IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - rigidBody1.location_;
				pt2 = v1[i] - rigidBody2.location_;

			
                vel1 = rigidBody1.velocity_ + (rigidBody1.angularVelocityGlobal_.Cross(pt1));
				vel2 = rigidBody2.velocity_ + (rigidBody2.angularVelocityGlobal_.Cross(pt2));

				
				n = u.Cross(v);
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr.Dot(n);
				
				if(Vrn < 0.0f)
				{
                    vector<Collision>& collisions = World::Instance().Collisions();
                    vector<Sprite*>& sprites = World::Instance().Sprites();

					// have a collision, fill the data structure and return
					//assert(NumCollisions < (NUMBODIES*16));
					if(collisions.size() < (sprites.size() * 16))
					{
                        Collision collision;
                        collision.body1 = const_cast<RigidBody*>(&rigidBody1);
                        collision.body2 = const_cast<RigidBody*>(&rigidBody2);
                        collision.collisionNormal = n;
                        collision.collisionPoint = v1[i];
                        collision.relativeVelocity = Vr;
                        collision.collisionTangent = (n.Cross(Vr)).Cross(n);
                        collision.collisionTangent.Normalize();
                        
                        collisions.push_back(collision);

                        status = CollisionType_Collision;
					}									
				}
			}
		}

		// Left face of body 2:???
		v = v2[5] - v2[4];
		u = v2[0] - v2[4];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, v2[4]);		
        if(d < Collision::CollisionTolerance)
		{
			f[0] = v2[4]; 
			f[1] = v2[5]; 
			f[2] = v2[1]; 
			f[3] = v2[0]; 
			if(Geometric::IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - rigidBody1.location_;
				pt2 = v1[i] - rigidBody2.location_;

			
                vel1 = rigidBody1.velocity_ + (rigidBody1.angularVelocityGlobal_.Cross(pt1));
                vel2 = rigidBody2.velocity_ + (rigidBody2.angularVelocityGlobal_.Cross(pt2));

			
                n = u.Cross(v);
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr.Dot(n);
				
				if(Vrn < 0.0f)
				{
                    vector<Collision>& collisions = World::Instance().Collisions();
                    vector<Sprite*>& sprites = World::Instance().Sprites();

					// have a collision, fill the data structure and return
					//assert(NumCollisions < (NUMBODIES*16));
					if(collisions.size() < (sprites.size() * 16))
					{
                        Collision collision;
                        collision.body1 = const_cast<RigidBody*>(&rigidBody1);
                        collision.body2 = const_cast<RigidBody*>(&rigidBody2);
                        collision.collisionNormal = n;
                        collision.collisionPoint = v1[i];
                        collision.relativeVelocity = Vr;
                        collision.collisionTangent = (n.Cross(Vr)).Cross(n);
                        collision.collisionTangent.Normalize();
                        
                        collisions.push_back(collision);

                        status = CollisionType_Collision;
					}									
				}
			}
		}

		// Right face of body 2:
		u = v2[6] - v2[2];
		v = v2[3] - v2[2];
		d = Geometric::DistanceFromPointToPlane(v1[i], u, v, v2[2]);		
        if(d < Collision::CollisionTolerance)
		{
			f[0] = v2[2]; 
			f[1] = v2[6]; 
			f[2] = v2[7]; 
			f[3] = v2[3]; 
			if(Geometric::IsPointOnFace(v1[i], f))
			{	
				// calc relative velocity, if <0 collision
				pt1 = v1[i] - rigidBody1.location_;
				pt2 = v1[i] - rigidBody2.location_;

				
				vel1 = rigidBody1.velocity_ + (rigidBody1.angularVelocityGlobal_.Cross(pt1));
                vel2 = rigidBody2.velocity_ + (rigidBody2.angularVelocityGlobal_.Cross(pt2));

				
				n = u.Cross(v);
				n.Normalize();
				
				Vr = (vel1 - vel2);
				Vrn = Vr.Dot(n);
				
				if(Vrn < 0.0f)
				{
                    vector<Collision>& collisions = World::Instance().Collisions();
                    vector<Sprite*>& sprites = World::Instance().Sprites();

					// have a collision, fill the data structure and return
					//assert(NumCollisions < (NUMBODIES*16));
					if(collisions.size() < (sprites.size() * 16))
					{
                        Collision collision;
                        collision.body1 = const_cast<RigidBody*>(&rigidBody1);
                        collision.body2 = const_cast<RigidBody*>(&rigidBody2);
                        collision.collisionNormal = n;
                        collision.collisionPoint = v1[i];
                        collision.relativeVelocity = Vr;
                        collision.collisionTangent = (n.Cross(Vr)).Cross(n);
                        collision.collisionTangent.Normalize();
                        
                        collisions.push_back(collision);

                        status = CollisionType_Collision;
					}									
				}
			}
		}		
		
	}

	return status;

}

CollisionType RigidBody::CheckEdgeEdgeCollisions(const RigidBody& rigidBody1, const RigidBody& rigidBody2)
{
	Vector3 v1[BoxVertexCount];
	Vector3 v2[BoxVertexCount];
	Vector3 tmp;
	Vector3 u, v;
	      
	Vector3 f[4];
	Vector3 vel1, vel2;
	Vector3 pt1, pt2;
	Vector3 Vr;
	float Vrn;
	Vector3 n;
	CollisionType status = CollisionType_NoCollision;
	bool inside = true;
	Edge e[12];
	float t, tx, ty, tz;
	float num, denom;
	int	 a1, b1;
	int	 a2, b2;
	Vector3 vE1, vE2;
	

	//rotate bounding vertices and covert to global coordinates
	for(int i = 0; i < BoxVertexCount; i++)
	{
		tmp = rigidBody1.vertexList_[i];
        v1[i] = rigidBody1.orientation_.VRotate(tmp);
		v1[i] += rigidBody1.location_;

		tmp = rigidBody2.vertexList_[i];
		v2[i] = rigidBody2.orientation_.VRotate(tmp);
		v2[i] += rigidBody2.location_;
	}

	e[0].a = 0;		e[0].b = 1;
	e[1].a = 1;		e[1].b = 2;
	e[2].a = 2;		e[2].b = 3;
	e[6].a = 3;		e[6].b = 0;	
	e[3].a = 4;		e[3].b = 5;
	e[4].a = 5;		e[4].b = 6;
	e[5].a = 6;		e[5].b = 7;	
	e[7].a = 7;		e[7].b = 4;
	e[8].a = 1;		e[8].b = 5;
	e[9].a = 2;		e[9].b = 6;
	e[10].a = 3;	e[10].b = 7;
	e[11].a = 0;	e[11].b = 4;

	//check each edge of body 1 against each edge of body 2
	for(int i = 0; i < 12; i++)
	{
		a1 = e[i].a;
		b1 = e[i].b;
		for(int j = 0; j < 12; j++)
		{
			// calc tx
			a2 = e[j].a;
			b2 = e[j].b;
			num = v1[a1].X - v2[a2].X;
			denom = v2[b2].X - v2[a2].X - v1[b1].X + v1[a1].X;
			
            if(Math::Abs(denom) < Math::Epsilon)
				tx = -1; // parallel in x direction			
			else
				tx = num / denom;

			// calc ty
			a2 = e[j].a;
			b2 = e[j].b;
			num = v1[a1].Y - v2[a2].Y;
			denom = v2[b2].Y - v2[a2].Y - v1[b1].Y + v1[a1].Y;
			
			if(Math::Abs(denom) < Math::Epsilon)
				ty = -1; // parallel in x direction			
			else
				ty = num / denom;

			// calc tz
			a2 = e[j].a;
			b2 = e[j].b;
			num = v1[a1].Z - v2[a2].Z;
			denom = v2[b2].Z - v2[a2].Z - v1[b1].Z + v1[a1].Z;
			
			if(Math::Abs(denom) < Math::Epsilon)
				tz = -1; // parallel in x direction			
			else
				tz = num / denom;

			// test for intersection
			t = tx;
            if( ((Math::Abs(t-ty) < Collision::PenetrationTolerance/2) && (Math::Abs(t-tz) < Collision::PenetrationTolerance/2)) && (t>=0) && (t <=1))
			{ // have intersection

				tmp.X = v1[a1].X + (v1[b1].X - v1[a1].X) * t;
				tmp.Y = v1[a1].Y + (v1[b1].Y - v1[a1].Y) * t;
				tmp.Z = v1[a1].Z + (v1[b1].Z - v1[a1].Z) * t;				
				
				// calc relative velocity, if <0 collision
				pt1 = tmp - rigidBody1.location_;
				pt2 = tmp - rigidBody2.location_;

			
                vel1 = rigidBody1.velocity_ + (rigidBody1.angularVelocityGlobal_.Cross(pt1));
				vel2 = rigidBody2.velocity_ + (rigidBody2.angularVelocityGlobal_.Cross(pt2));

			
				vE1 = v1[b1] - v1[a1];
				vE2 = v2[b2] - v2[a2];
				
				n = vE1.Cross(vE2);
				
				n.Normalize();
				
				
				Vr = (vel1 - vel2);
				Vrn = Vr.Dot(n);
				
				if(Vrn < 0.0f)
				{
                    vector<Collision>& collisions = World::Instance().Collisions();
                    vector<Sprite*>& sprites = World::Instance().Sprites();

					// have a collision, fill the data structure and return
					//assert(NumCollisions < (NUMBODIES*16));
					if(collisions.size() < (sprites.size() * 16))
					{
                        Collision collision;
                        collision.body1 = const_cast<RigidBody*>(&rigidBody1);
                        collision.body2 = const_cast<RigidBody*>(&rigidBody2);
                        collision.collisionNormal = n;
                        collision.collisionPoint = tmp;
                        collision.relativeVelocity = Vr;
                        collision.collisionTangent = (n.Cross(Vr)).Cross(n);
                        collision.collisionTangent.Normalize();
                        
                        collisions.push_back(collision);

                        status = CollisionType_Collision;
					}									
				}
			}
		}
	}

	
	return status;
}

CollisionType RigidBody::CheckVertexEdgeCollisions(const RigidBody& rigidBody1, const RigidBody& rigidBody2)
{
	CollisionType status = CollisionType_NoCollision;
	
	return status;
}


void RigidBody::ResolveCollisions()
{
	double	j;
	Vector3	pt1, pt2, vB1V, vB2V, vB1AV, vB2AV;
    float	fCr = Physics::CoefficientOfRestitution;
	int		b1, b2;
	float	Vrt;
	float	mu = Physics::FrictionCoefficient;
    bool	dofriction = Physics::DoFriction;

    vector<Collision>& collisions = World::Instance().Collisions();

	for(uint i = 0; i < collisions.size(); ++i)
	{
        RigidBody* rigidBody1 = collisions[i].body1;
        RigidBody* rigidBody2 = collisions[i].body2;

		if( (rigidBody1 != nullptr) && (rigidBody1 != rigidBody2) )
		{
			if(rigidBody2 != nullptr) // not ground plane
			{
				pt1 = collisions[i].collisionPoint - rigidBody1->location_;
				pt2 = collisions[i].collisionPoint - rigidBody2->location_;
				
				// calculate impulse
				j = (-(1 + fCr) * (collisions[i].relativeVelocity.Dot(collisions[i].collisionNormal))) /						
					( (1/rigidBody1->mass_ + 1/rigidBody2->mass_) +
					(collisions[i].collisionNormal.Dot(( ( (pt1.Cross(collisions[i].collisionNormal))*rigidBody1->ieInverse_ ).Cross(pt1)))) +
					(collisions[i].collisionNormal.Dot(( ( (pt2.Cross(collisions[i].collisionNormal))*rigidBody2->ieInverse_ ).Cross(pt2))))
					);
			
				Vrt = collisions[i].relativeVelocity.Dot(collisions[i].collisionTangent);
	
				if(Math::Abs(Vrt) > 0.0 && dofriction) {
					rigidBody1->velocity_ += ( (j * collisions[i].collisionNormal) + ((mu * j) * collisions[i].collisionTangent) ) / rigidBody1->mass_;										
					rigidBody1->angularVelocityGlobal_ += (pt1.Cross(((j * collisions[i].collisionNormal) + ((mu * j) * collisions[i].collisionTangent))))*rigidBody1->ieInverse_;
                    rigidBody1->angularVelocity_ = (~rigidBody1->orientation_).VRotate(rigidBody1->angularVelocityGlobal_);

					rigidBody2->velocity_ += ((-j * collisions[i].collisionNormal) + ((mu * j) * collisions[i].collisionTangent)) / rigidBody2->mass_;										
					rigidBody2->angularVelocityGlobal_ += (pt2.Cross(((-j * collisions[i].collisionNormal) + ((mu * j) * collisions[i].collisionTangent))))*rigidBody2->ieInverse_;
					rigidBody2->angularVelocity_ = (~rigidBody2->orientation_).VRotate(rigidBody2->angularVelocityGlobal_);

				} else {					
					// apply impulse
					rigidBody1->velocity_ += (j * collisions[i].collisionNormal) / rigidBody1->mass_;										
					rigidBody1->angularVelocityGlobal_ += (pt1.Cross((j * collisions[i].collisionNormal)))*rigidBody1->ieInverse_;
					rigidBody1->angularVelocity_ = (~rigidBody1->orientation_).VRotate(rigidBody1->angularVelocityGlobal_);
					
					rigidBody2->velocity_ -= (j * collisions[i].collisionNormal) / rigidBody2->mass_;										
					rigidBody2->angularVelocityGlobal_ -= (pt2.Cross((j * collisions[i].collisionNormal)))*rigidBody2->ieInverse_;
					rigidBody2->angularVelocity_ = (~rigidBody2->orientation_).VRotate(rigidBody2->angularVelocityGlobal_);
				}

			} else { // ground plane
                fCr = Physics::CoefficientOfRestitutionGround;
				pt1 = collisions[i].collisionPoint - rigidBody1->location_;
				
				// calculate impulse
				j = (-(1+fCr) * (collisions[i].relativeVelocity.Dot(collisions[i].collisionNormal))) /						
					( (1/rigidBody1->mass_) +
                    (collisions[i].collisionNormal.Dot(( ( (pt1.Cross(collisions[i].collisionNormal))*rigidBody1->ieInverse_ ).Cross(pt1)))));
			
				Vrt = collisions[i].relativeVelocity.Dot(collisions[i].collisionTangent);
	
				if(Math::Abs(Vrt) > 0.0 && dofriction) {
					rigidBody1->velocity_ += ( (j * collisions[i].collisionNormal) + ((mu * j) * collisions[i].collisionTangent) ) / rigidBody1->mass_;										
					rigidBody1->angularVelocityGlobal_ += (pt1.Cross(((j * collisions[i].collisionNormal)) + ((mu * j) * collisions[i].collisionTangent)))*rigidBody1->ieInverse_;
					rigidBody1->angularVelocity_ = (~rigidBody1->orientation_).VRotate(rigidBody1->angularVelocityGlobal_);
				} else {					
					// apply impulse
					rigidBody1->velocity_ += (j * collisions[i].collisionNormal) / rigidBody1->mass_;			
					rigidBody1->angularVelocityGlobal_ += (pt1.Cross((j * collisions[i].collisionNormal)))*rigidBody1->ieInverse_;
					rigidBody1->angularVelocity_ = (~rigidBody1->orientation_).VRotate(rigidBody1->angularVelocityGlobal_);
				}
		
			}
		}
	}
}

void RigidBody::ApplyForce(Vector3 force)
{
    immediateForce_ = force;
}

}
