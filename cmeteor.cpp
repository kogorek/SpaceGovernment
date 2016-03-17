#include "cmeteor.h"
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

meteor::meteor(float fx, float fy, float fsize,  float fangle, const char* str_path):Object2D (fx, fy, fsize, fangle,str_path)
{
    f_angle = lookAt(rand()%640 - 320, rand()%480 - 240);
    f_speed = float(rand()%50) + 50.0f;
    f_imageAngle = rand()%720-360; // from -360 to 360
    f_rotateSpeed = rand()%200 - 100;
}

float meteor::lookAt(float fx, float fy)
{
    return atan2(f_y - fy, f_x - fx)/ M_PI * 180+180;
}

void meteor::update(float f_deltaTime)
{
    f_x+=f_speed*cos(f_angle*M_PI/180)*f_deltaTime; //M_PI/180
    f_y+=f_speed*sin(f_angle*M_PI/180)*f_deltaTime; //180*M_PI
    f_imageAngle+=f_rotateSpeed*f_deltaTime;
    draw();
}

void meteor::draw()
{
    //f_imageAngle;
    glPushMatrix();
    glTranslatef(f_x, f_y, 0.0f);
    glRotatef(f_imageAngle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (unsigned int i = 0; i < fig.size(); i++)
    {
        glVertex2f(fig[i].f_x*f_size, fig[i].f_y*f_size);
    }
    glEnd();
    glPopMatrix();
}
