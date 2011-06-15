#pragma once

#include "Vector.h"
#include "TString.h"
#include "PrimitiveType.h"
#include "RigidBody.h"
#include "TimeSpan.h"
#include <vector>

namespace Virgin
{

struct QuadVertice
{
public:
    int Index[4];
};

struct TriangleVertice
{
public:
    int Index[4];
};

enum MeshMode
{
    MeshMode_Point,
    MeshMode_Wireframe,
    MeshMode_QuadMesh
};

class Sprite
{
public:
    Sprite(void);
    virtual ~Sprite(void);

    bool Load(const String& fileName, const String& textureName);

    void RotateXMore(float angle);
    void RotateYMore(float angle);
    void RotateZMore(float angle);
    void RotateAxis(float angle, const Vector3& axisBegin, const Vector3& axisEnd);
    void TranslateMore(float x, float y, float z);
    void Scale(float x, float y, float z);
    void ScaleRate(float x, float y, float z);
    void ScaleFrom(const Vector3& from, float x, float y, float z);
    void Reset();

    Vector3& Position();

    void Draw();
    void SetMeshMode(MeshMode mode);
    void SetDrawNormal(bool drawNormal);
    void SetDrawTexture(bool drawTexture);

    void CopyTo(Sprite& rhs) const;

    void CalculateModelCenterAndRadius();

    void DrawCoveringSphere();

    void SetVelocity(Vector3 direction, float speed);
    void Update(TimeSpan time, TimeSpan timeDelta);
    RigidBody& GetRigidBody();

    //static void InitializeRigidBodyForBall(RigidBody& rigidBody);
    //static void InitializeRigidBodyForPin(RigidBody& rigidBody);

private:
    std::vector<Vector3> vertice_;
    std::vector<Vector3> texels_;
	std::vector<Vector3> normals_;
    std::vector<QuadVertice> faces_;
    std::vector<QuadVertice> textureFaces_;
	std::vector<QuadVertice> normalVertices_;
	std::vector<TriangleVertice> triFaces_;
    std::vector<TriangleVertice> triTextureFaces_;
	std::vector<TriangleVertice> triNormalVertices_;

    std::vector<Vector3> faceNormals_;
    std::vector<Vector3> vertexNormals_;

    Vector3 anglesForEachAxis_;

    float rotateAngle_;
    Vector3 rotateAxisBegin_;
    Vector3 rotateAxisEnd_;

    Vector3 scales_;

    Vector3 pivotPointForScaling_;
    Vector3 pivotPointScales_;

    MeshMode meshMode_;
    bool doDrawNormal_;
    bool doDrawTexture_;

    uint texture_[3];

    //
    // ���� �𵨸�
    //

    Vector3 modelCenter_;   // �� ��ǥ ��������, ���� ����(Cube�� ������ ��). �׸� �� ���� -modelCenter_ ��ŭ Translate ����� ��
    float radius_;

    RigidBody rigidBody_;
};

}
