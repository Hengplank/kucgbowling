#pragma once

#include "Vector.h"

namespace Virgin
{

enum CollisionType
{
    CollisionType_NoCollision,
    CollisionType_Contact,
    CollisionType_Collision,
    CollisionType_Penetrating,  // �հ� �� ���
};

class RigidBody;

class Collision
{
public:
    static float CollisionTolerance;
    static float PenetrationTolerance;
    static float ContactTolerance;

public:

    //int body1;  // 1�� ��ü ��ȣ(������̸� -1 �̿�) // * Todo: RigidBody* �� ������ �� ���� ��
    //int body2;  // 2�� ��ü ��ȣ(������̸� -1 �̿�)
    RigidBody* body1;   // ������̸� nullptr
    RigidBody* body2;   // ������̸� nullptr
    Vector3 collisionNormal;    // 2�� ��ü �鿡�� ������ ������ ���� ����
    Vector3 collisionPoint;     // ������, ��ü ��ǥ
    Vector3 relativeVelocity;   // ��� �ӵ�
    Vector3 relativeAcceleration;   // ��� ���ӵ�
    Vector3 collisionTangent;   // ���� �����̰�, ���� ����� ���� ���� ��� �ӵ��� �ݴ� ����
};

}


