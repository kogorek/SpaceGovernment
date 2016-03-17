#include "cspaceship.h"
#ifndef M_PI
#define M_PI           3.14159265358979323846
#endif

spaceShip::spaceShip(float fx, float fy, float fsize, float fangle, const char* str_path, std::vector<planet>* inputPlanets):Object2D (fx, fy, fsize, fangle, str_path)
{
    n_money = 1000;
    f_speed = 80;
    f_fuel = 100;
    f_angle = fangle;
    b_isBusy = false;
    profit = 0;
    b_wasOnFPlanet = false;
    b_waitOnPlanet = false;
    f_storage = 0;
    planets = inputPlanets;
    MAXSTORAGE = 100;
    FUELCOST = 6;
    MAXFUEL = 100;
}

float spaceShip::lookAt(float fx, float fy)
{
    return atan2(f_y - fy, f_x - fx)/ M_PI * 180+180;
}

void spaceShip::update (float f_deltaTime)
{
    if(!b_isBusy)
    {

        for(unsigned int i = 0; i < planets->size(); i++)
        {
            for(unsigned int j = 0; j < planets->size(); j++)
            {
                if (i != j && profit < planets->at(j).sellCost.f_meal - planets->at(i).cost.f_meal)
                {
                    profit = planets->at(j).sellCost.f_meal - planets->at(i).cost.f_meal;
                    tradeInfo.buyCoords[0] = planets->at(i).f_x;
                    tradeInfo.buyCoords[1] = planets->at(i).f_y;
                    tradeInfo.sellCoords[0] = planets->at(j).f_x;
                    tradeInfo.sellCoords[1] = planets->at(j).f_y;
                    tradeInfo.planetNumbers[0] = i;
                    tradeInfo.planetNumbers[1] = j;

                }
            }
        }
        //        std::cout << "Buy " << tradeInfo.planetNumbers[0] << std::endl;
        //        std::cout << "Sell " << tradeInfo.planetNumbers[1] << std::endl;
        if (profit > 0 && planets->at(tradeInfo.planetNumbers[0]).storage.f_meal > 0)
        {
            f_angle = lookAt(tradeInfo.buyCoords[0], tradeInfo.buyCoords[1]);
            //std::cout << "profit " << profit << std::endl;

            b_isBusy = true;
            b_wasOnFPlanet = false;
        }else
        {
            b_waitOnPlanet = true;
        }
        if (b_waitOnPlanet && profit > 0 && planets->at(tradeInfo.planetNumbers[0]).storage.f_meal > 0)
        {
            b_waitOnPlanet = false;
        }
    }
    if(b_isBusy && f_fuel > 0)
    {
        tradeInfo.buyCoords[0] = planets->at(tradeInfo.planetNumbers[0]).f_x;
        tradeInfo.buyCoords[1] = planets->at(tradeInfo.planetNumbers[0]).f_y;
        tradeInfo.sellCoords[0] = planets->at(tradeInfo.planetNumbers[1]).f_x;
        tradeInfo.sellCoords[1] = planets->at(tradeInfo.planetNumbers[1]).f_y;
        if(!b_wasOnFPlanet)
            f_angle = lookAt(tradeInfo.buyCoords[0], tradeInfo.buyCoords[1]);
        else
            f_angle = lookAt(tradeInfo.sellCoords[0], tradeInfo.sellCoords[1]);
    }
    if(!b_wasOnFPlanet && f_fuel > 0 && !b_waitOnPlanet
            && planets->at(tradeInfo.planetNumbers[0]).f_size > xeDistance2d(f_x, f_y, planets->at(tradeInfo.planetNumbers[0]).f_x, planets->at(tradeInfo.planetNumbers[0]).f_y))
    {
        b_wasOnFPlanet = true;
        f_angle = lookAt(tradeInfo.sellCoords[0], tradeInfo.sellCoords[1]);
        // There are more than 100 units of meal on planet
        //and enough money on ship
        if((n_money - MAXSTORAGE*planets->at(tradeInfo.planetNumbers[0]).cost.f_meal >= 0)
                && (planets->at(tradeInfo.planetNumbers[0]).storage.f_meal >= MAXSTORAGE))
        {
            //std::cout << f_storage << std::endl;
            n_money -= (MAXSTORAGE - f_storage)*planets->at(tradeInfo.planetNumbers[0]).cost.f_meal;
            planets->at(tradeInfo.planetNumbers[0]).storage.f_meal -= MAXSTORAGE;
            f_storage = MAXSTORAGE;
            //std::cout << f_storage << std::endl;
        }
        // There are less than 100 units of meal on planet
        //and enough money on ship
        else if((planets->at(tradeInfo.planetNumbers[0]).storage.f_meal <= MAXSTORAGE)
                && (n_money >= planets->at(tradeInfo.planetNumbers[0]).cost.f_meal*planets->at(tradeInfo.planetNumbers[0]).storage.f_meal))
        {
            f_storage += planets->at(tradeInfo.planetNumbers[0]).storage.f_meal;
            planets->at(tradeInfo.planetNumbers[0]).storage.f_meal = 0;
            n_money -=  planets->at(tradeInfo.planetNumbers[0]).cost.f_meal*planets->at(tradeInfo.planetNumbers[0]).storage.f_meal;
        }
        // There are more than 100 units of meal on planet
        //and not enough money on ship
        else if((planets->at(tradeInfo.planetNumbers[0]).storage.f_meal >= MAXSTORAGE)
                && (n_money <= planets->at(tradeInfo.planetNumbers[0]).cost.f_meal*MAXSTORAGE))
        {
            f_storage = n_money/(planets->at(tradeInfo.planetNumbers[0]).cost.f_meal);
            planets->at(tradeInfo.planetNumbers[0]).storage.f_meal -= n_money/(planets->at(tradeInfo.planetNumbers[0]).cost.f_meal);
            n_money = 0;
        }
        else
        {
            std::cout << "FUCK ME I'LL DIE" << std::endl;
        }
        buyFuel();
    }
    if(b_wasOnFPlanet && f_fuel > 0 && !b_waitOnPlanet && planets->at(tradeInfo.planetNumbers[1]).f_size > xeDistance2d(f_x, f_y, planets->at(tradeInfo.planetNumbers[1]).f_x, planets->at(tradeInfo.planetNumbers[1]).f_y))
    {
         buyFuel();
        b_isBusy = false;
        profit = 0;
        tradeInfo.buyCoords[0] = 0;
        tradeInfo.buyCoords[1] = 0;
        planets->at(tradeInfo.planetNumbers[1]).storage.f_meal += f_storage;
        n_money += planets->at(tradeInfo.planetNumbers[1]).sellCost.f_meal*f_storage;
        f_storage = 0;
    }
    if (!b_waitOnPlanet)
    {
        if(f_fuel > 0)
        {
            f_fuel -= 15*f_deltaTime;
        }
        f_x+=f_speed*cos(f_angle*M_PI/180)*f_deltaTime; //M_PI/180
        f_y+=f_speed*sin(f_angle*M_PI/180)*f_deltaTime; //180*M_PI
        wireColor[0] = 1;
        wireColor[1] = f_fuel/100;
        wireColor[2] = f_fuel/100;
        glColor3fv(wireColor);
        draw();
        glColor3f(1,1,1);
    }
}

void spaceShip::buyFuel()
{
    //    std::cout << "I had " << f_fuel << " of fuel" << std::endl;
    if(n_money - (MAXFUEL - f_fuel)*FUELCOST >= 0)
    {
        n_money -= (MAXFUEL - f_fuel)*FUELCOST;
        f_fuel = 100.0f;
    }
    else
    {
        f_fuel += n_money/FUELCOST;
        n_money = 0;
    }
       std::cout << "I have " << f_fuel << " of fuel and " << n_money << " mons." << std::endl;
}
