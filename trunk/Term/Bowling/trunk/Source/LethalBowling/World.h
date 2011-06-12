#pragma once

#include "Sprite.h"
#include "Camera.h"
#include "Light.h"
#include "TimeSpan.h"
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

    Sprite& GetBall();
    Sprite& GetBall2();
    Sprite& GetPin(int number);
    void ResizePinCount(int count);

    Camera& GetCamera();
    Light& GetLight();

    void ShowCollisionInfo();
    void HideCollisionInfo();
	void Init();
	void DrawObject();
	void DrawFloor();

	void Update(TimeSpan timeDelta);

    vector<Sprite*>& Sprites();  
    vector<Collision>& Collisions();
private:
	vector<Sprite*> sprites_;   // ���⿡ ��� ��������Ʈ���� ����صξ�� �� (�浹 �˻� � ���)
    vector<Collision> collisions_;
    Sprite ball_;
    Sprite ball2_;
    vector<Sprite> pins_;
	float shadow_matrix[16];
    Light light_;

    Camera camera_;
    Camera topCamera_;
    Camera sideCamera_;
    Camera frontCamera_;
	GLuint texture[4];
    bool doShowCollisionInfo_;
	void LoadGLTextures();
};

}
