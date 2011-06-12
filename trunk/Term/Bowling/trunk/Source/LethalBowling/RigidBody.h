#pragma once

#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"
#include "TimeSpan.h"
#include "Collision.h"

namespace Virgin
{

enum
{
    BoxVertexCount = 8
};

class RigidBody
{
public:
    RigidBody();

    static void CalcObjectForces(); // ������ Ư�� ������ ��ü�� �ۿ��ϴ� ���� ���Ʈ�� ���� ����Ѵ�
    static CollisionType CheckGroundPlaneContacts(const RigidBody& rigidBody);    // ����
    static CollisionType CheckForCollisions(bool doCheckPenetration);
    static CollisionType CheckGroundPlaneCollisions(RigidBody& rigidBody);

    static CollisionType IsPenetrating(const RigidBody& rigidBody1, const RigidBody& rigidBody2);

    static void StepSimulation(TimeSpan timeDelta);   // ���Ϸ� ��� �̿�(����)

    // �浹 ���� ó��
    void ResolveCollisions();

    // 

    void Update(TimeSpan timeSpan);

public:
    float mass_;                    // ��ü ����(����)
    Matrix3 inertia_;               // ���� �������Ʈ, ��ü ��ǥ
    Matrix3 inertiaInverse_;        // ���� �������Ʈ ����� ��

    Vector3 location_;              // ��ü ��ġ, ��ü ��ǥ
    Vector3 velocity_;              // �ӵ�, ��ü ��ǥ
    Vector3 velocityBody;           // �ӵ�, ��ü ��ǥ
    Vector3 acceleration_;          // �����߽� ���ӵ�, ��ü ����
    Vector3 angularAcceleration_;   // �����ӵ�, ��ü ��ǥ
    Vector3 angularVelocity_;       // ���ӵ�, ��ü ��ǥ
    Vector3 eulerAngles_;           // ���Ϸ� ��, ��ü ��ǥ
    float speed_;                   // �ӷ�

    Quaternion orientation_;        // ����, ��ü ��ǥ

    Vector3 forces_;                // ��ü�� �ۿ��ϴ� ��ü ��
    Vector3 moments_;               // ��ü�� �ۿ��ϴ� ��ü ���Ʈ(��ũ)
    
    Matrix3 ieInverse_;             // ���� ���Ʈ�� ��, ��ü ��ǥ
    
    Vector3 angularVelocityGlobal_; // angular velocity in terms of earth fixed coords.
	Vector3 angularAccelerationGlobal_; // angular acceleration in terms of earth fixed coords.

    float radius_;
    Vector3 vertexList_[BoxVertexCount];    // �浹 �˻縦 Box�� ��
};

}
