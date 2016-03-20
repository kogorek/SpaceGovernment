#include "cmeteor.h"
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

meteor::meteor(float fx, float fy, float fsize,  float fangle, const char* str_path, std::vector<planet>* inputPlanets):Object2D (fx, fy, fsize, fangle,str_path)
{
    f_angle = lookAt(rand()%640 - 320, rand()%480 - 240);
    f_speed = float(rand()%50) + 50.0f;
    f_imageAngle = rand()%720-360; // from -360 to 360
    f_rotateSpeed = rand()%200 - 100;
    Planets = inputPlanets;
    f_vx = 0;
    f_vy = 0;
}

float meteor::lookAt(float fx, float fy)
{
    return atan2(f_y - fy, f_x - fx)/ M_PI * 180+180;
}

void meteor::update(float f_deltaTime)
{
    int N = Planets->size();
    for (unsigned i = 0; i < N; i++)
    {
        float d = xeDistance2d(f_x, f_y, Planets->at(i).f_x, Planets->at(i).f_y);
        if (d > 24)
        {
            //            f_x += 0.07 * 100 / d / d * (Planets->at(i).f_x - f_x) / d;
            //            f_y += 0.07 * 100 / d / d * (Planets->at(i).f_y - f_y) / d;
            f_vx += 7 * 100 / d / d * (Planets->at(i).f_x - f_x) / d;
            f_vy += 7 * 100 / d / d * (Planets->at(i).f_y - f_y) / d;

        }
        f_x += f_vx*f_deltaTime;
        f_y += f_vy*f_deltaTime;
    }

   // if (d > 100)
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
