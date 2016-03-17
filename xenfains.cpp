#include "xenfains.h"
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

float xeDistance2d(float f_x0, float f_y0, float f_x1, float f_y1)
{
    //distance = sqrt( (bulletList[i].x - meteorList[j].f_x)*(bulletList[i].x - meteorList[j].f_x) + (bulletList[i].y - meteorList[j].f_y)*(bulletList[i].y - meteorList[j].f_y));
    return sqrt((f_x0 - f_x1)*(f_x0 - f_x1) + (f_y0 - f_y1) * (f_y0 - f_y1));
}

void xeDDrawCircle(float f_x, float f_y, float f_radius, int n_points)
{
    float f_degrees = 0;
    glBegin(GL_LINE_LOOP);
    for (int i=0; i<n_points; i++)
    {
        glVertex2f(cos(f_degrees*M_PI/180)*f_radius+f_x, sin(f_degrees*M_PI/180)*f_radius+f_y);
        f_degrees += (360/n_points);
    }
    glEnd();
}

void xeDDrawFilledCircle(float f_x, float f_y, float f_radius, int n_points, float fillColor[3])
{
    float f_degrees = 0;
    glBegin(GL_POLYGON);
    glColor3fv(fillColor);
    for (int i=0; i<n_points; i++)
    {
        glVertex2f(cos(f_degrees*M_PI/180)*f_radius+f_x, sin(f_degrees*M_PI/180)*f_radius+f_y);
        f_degrees += (360/n_points);
    }
    glEnd();
    glColor3f(1.0f, 1.0f, 1.0f);
}

void xeDDrawCross(float f_x, float f_y, float f_size)
{
    glBegin(GL_LINES);
    glVertex2f(0.0f+f_x, -1.0f*f_size+f_y);
    glVertex2f(0.0f+f_x, 1.0f*f_size+f_y);
    glVertex2f(-1.0f*f_size+f_x, 0.0f+f_y);
    glVertex2f(1.0f*f_size+f_x, 0.0f+f_y);
    glEnd();
}

int xeRandOne()
{
    int one = 0;
    while(one == 0)
        one = rand()%3-1;
    return one;
}
