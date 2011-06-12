#pragma once

#include "Vector.h"

namespace Virgin 
{

class Geometric
{
public:
    // ����� u, v, �׸��� ptOnPlane���� �����Ǿ� ����
    static float DistanceFromPointToPlane(Vector3 pt, Vector3 u, Vector3 v, Vector3 ptOnPlane)
    {
        Vector3 n = u.Cross(v);
        Vector3 PQ = pt - ptOnPlane;
    
        n.Normalize();

        return PQ.Dot(n);
    }

public:
    static bool DoPenetrationCheck;
};

}
