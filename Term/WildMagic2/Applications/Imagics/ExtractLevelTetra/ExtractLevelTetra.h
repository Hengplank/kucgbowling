// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Wild Magic Library (WML) source code is supplied under the terms of
// the license agreement http://www.magic-software.com/License/WildMagic.pdf
// and may not be copied or disclosed except in accordance with the terms of
// that agreement.

#ifndef EXTRACTLEVELTETRA_H
#define EXTRACTLEVELTETRA_H

#include "WmlApplication.h"
using namespace Wml;

class ExtractLevelTetra : public Application
{
public:
    ExtractLevelTetra ();
    virtual ~ExtractLevelTetra ();

    virtual bool OnInitialize ();
    virtual void OnTerminate ();
    virtual void OnIdle ();
    virtual void OnKeyDown (unsigned char ucKey, int iX, int iY);

protected:
    void CreateModel ();

    NodePtr m_spkScene, m_spkTrnNode;
    TriMeshPtr m_spkModel;
    WireframeStatePtr m_spkWireframe;
};

#endif
