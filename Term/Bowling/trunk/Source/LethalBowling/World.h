#pragma once

#include "Sprite.h"
#include "Camera.h"
#include "Light.h"

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

private:
    Sprite ball_;
    Sprite ball2_;
    vector<Sprite> pins_;

    Light light_;

    Camera camera_;
    Camera topCamera_;
    Camera sideCamera_;
    Camera frontCamera_;

    bool doShowCollisionInfo_;
};

}
