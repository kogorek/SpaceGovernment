#ifndef CPLANET_H
#define CPLANET_H

#include "vars.h"
#include "xenfains.h"
#include "cobject2d.h"

#include <cstdlib>

class planet: public Object2D
{
public:
    float f_storage;
    float f_turnTime;
    int population;
    float f_degrees;
    float f_radius;
    production planetProduction;
    production consumption; // production consumption per mounth
    production storage;
    production cost; // production cost per kg
    production sellCost;

    planet(float fx, float fy, float fsize, float fangle, const char *str_path);
    void draw();
    void updatePrice();
    void update(float f_deltaTime);
};

#endif // CPLANET_H
