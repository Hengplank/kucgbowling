#pragma once

#include "Vector.h"
#include "Color.h"

namespace Virgin
{

class Light
{
public:
    Light(void);
    ~Light(void);

    void MoveTo(float x, float y, float z);
    void SetAmbient(float r, float g, float b);
    void SetDiffuse(float r, float g, float b);
    void SetSpecular(float r, float g, float b);
    
    void Enable();
    void Disable();
	Vector3 GetLocation() { return location_;};
private:
    Vector3 location_;
    Color ambient_;
    Color diffuse_;
    Color specular_;
};

}
