#ifndef CMETEOR_H
#define CMETEOR_H

#include <cmath>
#include <cstdlib> //rand

#include "cplanet.h"
#include "xenfains.h"
#include "cobject2d.h"

class meteor: public Object2D
{
public:
    float f_speed;
    float f_rotateSpeed;
    float f_imageAngle;
    float f_vx;
    float f_vy;
     std::vector<planet>* Planets;

    meteor(float fx, float fy, float fsize,  float fangle, const char* str_path, std::vector<planet> *inputPlanets);
    float lookAt(float fx, float fy);
    void update(float f_deltaTime);
    void draw();
};

#endif // CMETEOR_H
