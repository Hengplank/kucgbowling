// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Game Physics source code is supplied under the terms of the license
// agreement http://www.magic-software.com/License/GamePhysics.pdf and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.

#ifndef KEPLERPOLARFORM_H
#define KEPLERPOLARFORM_H

#include "WmlApplication2.h"
#include "PhysicsModule.h"

class KeplerPolarForm : public Application2
{
public:
    KeplerPolarForm ();
    virtual ~KeplerPolarForm ();

    virtual bool OnInitialize ();
    virtual void OnTerminate ();
    virtual void OnDisplay ();
    virtual void OnKeyDown (unsigned char ucKey, int iX, int iY);

protected:
    PhysicsModule m_kModule;
    std::vector<Vector2d> m_kPosition;
};

#endif


