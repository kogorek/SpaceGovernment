#ifndef CSPACESHIP_H
#define CSPACESHIP_H

#include "cobject2d.h"
#include "xenfains.h"
#include "cplanet.h"
#include "vars.h"

#include <iostream>
#include <cmath>

class spaceShip: public Object2D
{
    float lookAt(float fx, float fy);
    struct tradeInformation
    {
        float buyCoords[2];
        float sellCoords[2];
        int planetNumbers[2]; // 0 - where to buy, 1 - where to sell
    };

public:
    int n_money;
    int profit;
    bool b_isBusy;
    bool b_wasOnFPlanet;
    bool b_waitOnPlanet;
    float f_fuel;
    float f_HP;
    float f_speed;
    float f_damage;
    float f_storage;
    float FUELCOST;
    float MAXFUEL;
    float MAXSTORAGE;
    float wireColor[3];
    float fillColor[3];
    production ship_storage;
    tradeInformation tradeInfo;
    std::vector<planet>* planets;

    spaceShip(float fx, float fy, float fsize, float fangle, const char* str_path, std::vector<planet> *planets);
    void update (float f_deltaTime);
    void buyFuel();
};

#endif // CSPACESHIP_H
