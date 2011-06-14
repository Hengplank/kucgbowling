// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#ifndef WMLBEZIERRECTANGLE_H
#define WMLBEZIERRECTANGLE_H

#include "WmlBezierPatch.h"

namespace Wml
{

class WML_ITEM BezierRectangle : public BezierPatch
{
    WmlDeclareRTTI;
    WmlDeclareStream;

public:
    virtual PatchType GetType () const { return PT_RECTANGLE; }

    // number of vertices/triangles generated by tessellation at given level
    virtual int GetVerticesPerPatch (int iLevel) const;
    virtual int GetTrianglesPerPatch (int iLevel) const;

protected:
    // Construction.  BezierRectangle accepts responsibility for deleting
    // the input array.
    BezierRectangle (int iDegree, int iIndexQuantity, int* aiIndex);

    BezierRectangle ();

    // tessellation
    void GenerateConnectivity (int iLevel, TriMesh* pkMesh,
        int& riTriangleStart);
};

WmlSmartPointer(BezierRectangle);
WmlRegisterStream(BezierRectangle);

}

#endif
