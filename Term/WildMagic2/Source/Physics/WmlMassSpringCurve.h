// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Game Physics source code is supplied under the terms of the license
// agreement http://www.magic-software.com/License/GamePhysics.pdf and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.

#ifndef WMLMASSSPRINGCURVE_H
#define WMLMASSSPRINGCURVE_H

#include "WmlParticlePhysics.h"

namespace Wml
{

template <class Real, class TVector>
class WML_ITEM MassSpringCurve : public ParticlePhysics<Real,TVector>
{
public:
    // Construction and destruction.  This class represents a set of N-1
    // springs connecting N masses that lie on a curve.  Spring i connects
    // masses i-1 and i for 1 <= i <= N-1.
    MassSpringCurve (int iNumParticles, Real fStep);
    virtual ~MassSpringCurve ();

    int GetNumSprings () const;
    Real& Constant (int i);  // spring constant
    Real& Length (int i);  // spring resting length

    // Callback for physical impulses (ODE solver uses x" = F/m) applied to
    // particle i due to the spring forces of neighboring particles.  The
    // positions and velocities are not necessarily m_akPosition and
    // m_akVelocity since the ODE solver evaluates the impulse function at
    // intermediate positions.
    virtual TVector Impulse (int i, Real fTime, const TVector* akPosition,
        const TVector* akVelocity);

    // The default external force is zero.  Derive a class from MassSpring1
    // to provide nonzero external forces such as gravity, wind, friction,
    // and so on.  This function is called by Impulse(...) to append the
    // impulse F/m generated by the external force F.
    virtual TVector ExternalImpulse (int i, Real fTime,
        const TVector* akPosition, const TVector* akVelocity);

protected:
    int m_iNumSprings;
    Real* m_afConstant;
    Real* m_afLength;
};

typedef MassSpringCurve<float,Vector2f> MassSpringCurve2f;
typedef MassSpringCurve<double,Vector2d> MassSpringCurve2d;
typedef MassSpringCurve<float,Vector3f> MassSpringCurve3f;
typedef MassSpringCurve<double,Vector3d> MassSpringCurve3d;

}

#endif
