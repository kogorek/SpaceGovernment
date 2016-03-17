#ifndef XENFAINS_H
#define XENFAINS_H

#include <iostream>
#include <GL/gl.h>
#include <cstdlib> //rand
#include <cmath>


float xeDistance2d(float f_x0, float f_y0, float f_x1, float f_y1);
void xeDDrawCircle(float f_x, float f_y, float f_radius, int n_points);
void xeDDrawFilledCircle(float f_x, float f_y, float f_radius, int n_points, float fillColor[3]);
void xeDDrawCross(float f_x, float f_y, float f_size);
int xeRandOne();

#endif // XENFAINS_H
