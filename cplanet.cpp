#include "cplanet.h"
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

planet::planet(float fx, float fy, float fsize,  float fangle, const char* str_path):Object2D (fx, fy, fsize, fangle,str_path)
{
    f_degrees = 0;
    f_radius = xeDistance2d(0.0f, 0.0f, f_x, f_y);
    f_turnTime = 15;
    population = rand()%100 + 10;
    cost.f_gems = 0;
    cost.f_meal = storage.f_meal*1/(10*10);
    cost.f_medicine = 0;
    sellCost.f_gems = 0;
    sellCost.f_meal = 11 - storage.f_meal*1/(10*10);
    sellCost.f_medicine = 0;
    storage.f_gems = rand()%90+10; // from 10 to 100
    storage.f_meal = rand()%150 + 50; // from 50 to 200
    storage.f_medicine = rand()%150 + 50; // from 50 to 200
    consumption.f_gems = float(population)/100;
    consumption.f_meal = float(population);
    consumption.f_medicine = float(population)/40;
    planetProduction.f_gems = rand()%10; // from 0 to 10
    planetProduction.f_meal = population; // from 10 to 40
    planetProduction.f_medicine = rand()%10+10; // from 10 to 20
}

void planet::updatePrice()
{
    sellCost.f_meal = 11 - storage.f_meal*1/(10*10);
    cost.f_meal = storage.f_meal*1/(10*10);
}

void planet::update(float f_deltaTime)
{
    f_turnTime = f_turnTime - 10*f_deltaTime;
    f_degrees += 500/f_radius*f_deltaTime;
    if ( f_degrees > 360)
        f_degrees = 0;
    f_x = cos(f_degrees*M_PI/180)*f_radius;
    f_y = sin(f_degrees*M_PI/180)*f_radius;
    //std::cout << f_y << std::endl;
    if (f_turnTime < 1)
    {
        updatePrice();
        if(storage.f_meal > 0)
            storage.f_meal -= consumption.f_meal;
        if(storage.f_meal < 1000 - planetProduction.f_meal)
            storage.f_meal += planetProduction.f_meal;
        f_turnTime = 15;
    }
    draw();
}

void planet::draw()
{
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x0F0F);
    glColor3f(0.7f, 0.5f, 0.0f);
    xeDDrawCircle(0.0f, 0.0f, f_radius, 24);
    glDisable(GL_LINE_STIPPLE);
    glPushMatrix();
    glTranslatef(f_x, f_y, 0.0f);
    glRotatef(f_angle, 0.0f, 0.0f, 1.0f);
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    for (unsigned int i = 0; i < fig.size(); i++)
    {
        glVertex2f(fig[i].f_x*f_size, fig[i].f_y*f_size);
    }
    glEnd();
    glColor3f(1, 1, 1);
    glBegin(GL_LINE_LOOP);
    for (unsigned int i = 0; i < fig.size(); i++)
    {
        glVertex2f(fig[i].f_x*f_size, fig[i].f_y*f_size);
    }
    glEnd();
    glPopMatrix();
}
