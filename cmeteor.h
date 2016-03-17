#ifndef CMETEOR_H
#define CMETEOR_H

#include <cmath>
#include <cstdlib> //rand

#include "cobject2d.h"

class meteor: public Object2D
{
public:
    float f_speed;
    float f_rotateSpeed;
    float f_imageAngle;
    meteor(float fx, float fy, float fsize,  float fangle, const char* str_path);
    float lookAt(float fx, float fy);
    void update(float f_deltaTime);
    void draw();
};

#endif // CMETEOR_H
