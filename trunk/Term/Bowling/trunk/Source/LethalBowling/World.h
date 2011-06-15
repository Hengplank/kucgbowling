#pragma once

#include "Sprite.h"
#include "Camera.h"
#include "Light.h"
#include "TimeSpan.h"
#include "Ball.h"
#include "Pin.h"
#include "Contact.h"

#include <glut.h>

using namespace std;

namespace Virgin
{

// �� ���α׷��� ��� 3D ��� - ��������Ʈ, ����, �ɼ� ��� - �� �� �ִ� Singleton Ŭ����
class World
{
private:
    World();    // Singleton

public:
    static World& Instance();

    void DrawScene();

    Ball& GetBall();
    Ball& GetBall2();
    Pin& GetPin(int number);
    void ResizePinCount(int count);

    Camera& GetCamera();
    Light& GetLight();

    void ShowCollisionInfo();
    void HideCollisionInfo();
	void Init();
	void DrawObject();
	void DrawFloor();

	void Update(TimeSpan time, TimeSpan timeDelta);

    vector<Sprite*>& Sprites();  
    vector<Collision>& Collisions();

    void DrawString3(void *font, const char *str, float x_position, float y_position, float z_position);
    // ���� �ùķ��̼�
    void DoPhysical();

    // �浹 ����
    void DoCollisionDetection();
    bool FarFromBoundary(int i);
    bool FarApart(int iT0, int iT1);
    bool TetraBoundaryIntersection(int iTetra, int iBoundary, float* afDistance, Contact& rkContact);
    void BuildContactMoveTetra(int iTetra, int iBoundary, int iHitIndex, float fDepthMax, Contact& rkContact);
    void Reposition(int iT0, int iT1, Contact& rkContact);
    bool IsVertex(const Vector3* akVertex, const Vector3& rkRes);
    void CalculateNormal(const Vector3* akVertex, const Vector3& rkRes, Contact& rkContact);
    Vector3 ClosestEdge(const Vector3* akVertex, const Vector3& rkRes,Vector3& rkOtherVertex);

    // �浹 ����
    void DoCollisionResponse();
    void ComputePreimpulseVelocity(std::vector<float>& preRelVel);
    void ComputeImpulseMagnitude(std::vector<float>& preRelVel, std::vector<float>& impulseMag);
    void DoImpulse(std::vector<float>& impulseMag);
    void DoMotion();
    static float CalcKE(const RigidBody& rigidBody);

    // �ð�ȭ
    void DoVisual();

    static Vector3 Force (float fTime, float fMass, const Vector3& rkPos,
        const Quaternion& rkQOrient, const Vector3& rkLinMom,
        const Vector3& rkAngMom, const Matrix3& rkOrient,
        const Vector3& rkLinVel, const Vector3& rkAngVel);

    static Vector3 Torque (float fTime, float fMass, const Vector3& rkPos,
        const Quaternion& rkQOrient, const Vector3& rkLinMom,
        const Vector3& rkAngMom, const Matrix3& rkOrient,
        const Vector3& rkLinVel, const Vector3& rkAngVel);

private:
	vector<Sprite*> sprites_;   // ���⿡ ��� ��������Ʈ���� ����صξ�� �� (�浹 �˻� � ���)
    vector<Collision> collisions_;
    vector<Contact> contacts_;
    Ball ball_;
    Ball ball2_;
    vector<Pin> pins_;
	float shadow_matrix[16];
    Light light_;

    RigidBody floor_;
    float totalKE_;

    Camera camera_;
    Camera topCamera_;
    Camera sideCamera_;
    Camera frontCamera_;
	GLuint texture[4];
    bool doShowCollisionInfo_;
	void LoadGLTextures();
};

}
