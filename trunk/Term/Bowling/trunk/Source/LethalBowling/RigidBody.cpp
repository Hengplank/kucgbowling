#include "RigidBody.h"

#include "Collision.h"
#include "World.h"
#include "Physics.h"
#include "TMath.h"

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

        // �߷� ���� ����, �����߽ɿ� �ۿ� 
        // * Predicated, ���༱��
        /*if(i == CAR)
        {
            Thrust.x = 1.0f;
            Thrust.y = 0.0f;
            Thrust.z = 0.0f;
            Thrust *= ThrustForce;
            Fb += Thrust;
        }*/

        // �׷� ����
        vDragVector = -rigidBody.velocityBody;
        vDragVector.Normalize();
        Fb += vDragVector * (rigidBody.speed_ * rigidBody.speed_ * Physics::AirDensity * Physics::LinearDragCoefficient * rigidBody.radius_ * rigidBody.radius_);

        vAngularDragVector = -rigidBody.angularVelocity_;
        vAngularDragVector.Normalize();
        Mb += vAngularDragVector * (rigidBody.angularVelocity_.Size() * rigidBody.angularVelocity_.Size() * Physics::AirDensity * Physics::AngularDragCoefficient * rigidBody.radius_ * rigidBody.radius_);

        // ���� �� �������� ��ü �������� ��ȯ
        rigidBody.forces_ = rigidBody.orientation_.VRotate(Fb);

        // �߷� �ۿ�
        rigidBody.forces_.Z += Physics::Gravity * rigidBody.mass_;

        // ���Ʈ ����
        rigidBody.moments_ += Mb;

        // ������ �����ϴ� ��Ȳ ó��
        rigidBody.acceleration_ = rigidBody.forces_ / rigidBody.mass_;
        rigidBody.angularAcceleration_ = rigidBody.inertiaInverse_ * (rigidBody.moments_ - rigidBody.angularVelocity_.Cross(rigidBody.inertia_ * rigidBody.angularVelocity_));
        
        vector<Collision>& collisions = World::Instance().Collisions();
        collisions.clear();
 //       collisionType = CheckGroundPlaneContacts(rigidBody);
        if(collisionType == CollisionType_Contact)
        {
            // ���� ������
            for(uint j = 0; j < collisions.size(); ++j)
            {
                //ContactForce = rigidBody.mass_/collisions.size() 
            }
        }
    }

}

}
