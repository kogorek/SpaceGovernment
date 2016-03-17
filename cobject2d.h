#ifndef COBJECT2D_H
#define COBJECT2D_H

#include "vars.h"

#include <GL/glu.h>
#include <iostream>
#include <fstream>
#include <GL/gl.h>
#include <vector>

class Object2D
{
public:
    float f_x, f_y;
    float f_size;
    float f_angle;
    std::vector<figure> fig;

    Object2D(float fx, float fy, float fsize, float fangle, const char *str_path);
    bool loadModel(const char* str_path);
    void draw();
};

#endif // COBJECT2D_H
