#include "Pin.h"

namespace Virgin
{

Sphere& Pin::CoveringSphere()
{
    return coverSphere_;
}

Vector3* Pin::GetBox()
{
    return box_;
}

//void Pin::Update(TimeSpan time, TimeSpan timeDelta)
//{
//    Sprite::Update(time, timeDelta);
//
//    // Box ��ǥ ����
//    // * Todo: ȸ�� ���
//    for(int i = 0; i < BoxVerticeCount; ++i)
//    {
//        const Vector3& position = GetRigidBody().GetPosition();
//
//        box_[i] += position;
//    }
//}

void Pin::GetBox(Vector3 box[8])
{
    // move the box vertices
    for (int i = 0; i < BoxVerticeCount; i++)
        box[i] = GetRigidBody().GetROrientation()*box_[i] + GetRigidBody().GetPosition();
}

}


