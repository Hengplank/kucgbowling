// Magic Software, Inc.
// http://www.magic-software.com
// http://www.wild-magic.com
// Copyright (c) 2003.  All Rights Reserved
//
// The Game Physics source code is supplied under the terms of the license
// agreement http://www.magic-software.com/License/GamePhysics.pdf and may not
// be copied or disclosed except in accordance with the terms of that
// agreement.

#ifndef WMLMASSSPRINGARBITRARY_H
#define WMLMASSSPRINGARBITRARY_H

#include "WmlParticlePhysics.h"
#include "WmlUnorderedSet.h"

namespace Wml
{

template <class Real, class TVector>
class WML_ITEM MassSpringArbitrary : public ParticlePhysics<Real,TVector>
{
public:
    // Construction and destruction.  This class represents a set of M
    // masses that are connected by S springs with arbitrary topology.  The
    // function SetSpring(...) should be called for each spring that you
    // want in the system.  At most one spring is allowed between a pair of
    // masses.
    MassSpringArbitrary (int iNumParticles, int iNumSprings, Real fStep);
    virtual ~MassSpringArbitrary ();

    int GetNumSprings () const;
    void SetSpring (int iSpring, int iParticle0, int iParticle1,
        Real fConstant, Real fLength);
    void GetSpring (int iSpring, int& riParticle0, int& riParticle1,
        Real& rfConstant, Real& rfLength) const;

    Real& Constant (int iSpring);
    Real& Length (int iSpring);

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
    class Spring
    {
    public:
        int Particle0, Particle1;
        Real Constant, Length;
    };

    int m_iNumSprings;
    Spring* m_akSpring;

    // Each particle has an associated array of spring indices for those
    // springs adjacent to the particle.  The set elements are spring
    // indices, not indices of adjacent particles.
    UnorderedSet<int>* m_akAdjacent;
};

typedef MassSpringArbitrary<float,Vector2f> MassSpringArbitrary2f;
typedef MassSpringArbitrary<double,Vector2d> MassSpringArbitrary2d;
typedef MassSpringArbitrary<float,Vector3f> MassSpringArbitrary3f;
typedef MassSpringArbitrary<double,Vector3d> MassSpringArbitrary3d;

}

#endif
