#include <SDL2/SDL.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <iostream>
#include <cstdlib> //rand
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

#include "cspaceship.h"
#include "cobject2d.h"
#include "cplanet.h"
#include "cmeteor.h"
#include "vars.h"

#define UNUSED(x) (void)(x)

SDL_Window *win = NULL;

int n_screenWidth = 640;
int n_screenHeight = 480;

bool b_FPScap = true;
int n_FPScap = 30;

struct star
{
    float f_x, f_y;
    float color[3];
};

void initGLandSDL();
void endSDL();

int main(int argc, char *argv[])
{
    UNUSED(argc);
    UNUSED(argv);
    for (int i = 0; i < 10; i++)
        xeRandOne();

    srand(time(0));
    unsigned int n_meteorQuantity = 5;
    bool b_running = true;
    double deltaTime = 0;
    float f_starAngle = 0;
    SDL_Event event;
    Uint64 currentTime = SDL_GetTicks();
    Uint64 lastTime = 0;
    Uint32 time = 0; // Используется для ограничения FPS
    star stars[512];
    std::vector<planet> planets;
    std::vector<spaceShip> Jim;
    std::vector<meteor> meteorList;
    std::vector<std::string> meteorModels;

    for (int i = 0; i < 512; i++)
    {
        stars[i].f_x = rand()%(n_screenWidth+100) - (n_screenWidth+100)/2;
        stars[i].f_y = rand()%(n_screenWidth+100) - (n_screenWidth+100)/2;
        stars[i].color[0] = float(rand()%10+5)/10;
        stars[i].color[1] = float(rand()%10)/10;
        stars[i].color[2] = float(rand()%10)/10;
    }
    for(int i = 0; i < 4; i++)
    {
        float fx, fy;
        float f_degree = rand()%360;
        static float radius;
        radius += rand()%40+30;
        fx = cos(f_degree*M_PI/180)*radius;
        fy = sin(f_degree*M_PI/180)*radius;
        planets.push_back(planet(fx, fy, 10.0f, 0.0f, "./Res/Models/Planet.kjk"));
    }
    Jim.push_back(spaceShip(0.0f, 0.0f, 10.0f, 90.0f, "./Res/Models/SpaceShip.kjk", &planets));
    //    Jim.push_back(spaceShip(-100.0f, 100.0f, 10.0f, 90.0f, "./Res/Models/SpaceShip.kjk", &planets));
    //    Jim.push_back(spaceShip(100.0f, 100.0f, 10.0f, 90.0f, "./Res/Models/SpaceShip.kjk", &planets));
    //    Jim.push_back(spaceShip(-100.0f, -100.0f, 10.0f, 90.0f, "./Res/Models/SpaceShip.kjk", &planets));
    //    Jim.push_back(spaceShip(100.0f, 100.0f, 10.0f, 90.0f, "./Res/Models/SpaceShip.kjk", &planets));
    meteorModels.push_back(std::string("./Res/Models/Meteor1.kjk"));
    meteorModels.push_back(std::string("./Res/Models/Meteor2.kjk"));
    meteorModels.push_back(std::string("./Res/Models/Meteor3.kjk"));
    meteorModels.push_back(std::string("./Res/Models/Meteor4.kjk"));

    initGLandSDL();
    while(b_running)
    {
        if (currentTime > lastTime)
        {
            lastTime = currentTime;
        }
        currentTime = SDL_GetTicks();
        deltaTime = (double)((currentTime - lastTime)/1000.0f);
        time = SDL_GetTicks();
        while ( SDL_PollEvent(&event) )
        {
            switch(event.type)
            {
            case SDL_QUIT:
                b_running = false;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    b_running = false;
                    break;
                case SDLK_j:
                    for(unsigned int i = 0; i <= planets.size()-1; i++ )
                    {
                        std::cout << "------------" << std::endl;
                        std::cout << "sell cost on " << i << ": " << planets[i].sellCost.f_meal << std::endl;
                        std::cout << "buy cost on " << i << ": " << planets[i].cost.f_meal << std::endl;
                        std::cout << "storage on " << i << ": " << planets[i].storage.f_meal << std::endl;
                    }
                    break;
                case SDLK_k:
                    planets[0].cost.f_meal = 0;
                    break;
                case SDLK_f:
                    b_FPScap = !b_FPScap;
                    break;
                }
                break;
            }
        }
        glLoadIdentity();
        glClear(GL_COLOR_BUFFER_BIT ); //| GL_DEPTH_BUFFER_BIT
        gluOrtho2D(-n_screenWidth/2, n_screenWidth/2, -n_screenHeight/2, n_screenHeight/2);
        //xeDDrawCircle(0.0f, 0.0f, 15.0f, 12);
        // Draw things
        glPushMatrix();
        glRotatef(f_starAngle, 0, 0, 1);
        glBegin(GL_POINTS);
        for(int i = 0; i < 512; i++)
        {
            glColor3fv(stars[i].color);
            glVertex2d(1, 100);
            glRotatef(f_starAngle, 0, 0, 1);
            glVertex2d(stars[i].f_x, stars[i].f_y);
            f_starAngle += 0.0005*deltaTime;

        }
        glColor3f(1,1,1);
        glEnd();
        glPopMatrix();
        float sunColor[3] = {1.0f, 0.2f, 0.0f};
        xeDDrawFilledCircle(0.0f, 0.0f, 15.0f, 12, sunColor);
        for(unsigned int i = 0; i < meteorList.size(); i++)
            for(unsigned int j = 0; j < planets.size(); j++)
                if (xeDistance2d(meteorList[i].f_x, meteorList[i].f_y, planets[j].f_x, planets[j].f_y) < 15)
                    meteorList.erase(meteorList.begin() + i);
        for(unsigned int i = 0; i < meteorList.size(); i++)
            if (xeDistance2d(meteorList[i].f_x, meteorList[i].f_y, 0, 0) < 20)
                meteorList.erase(meteorList.begin() + i);
        for(unsigned int i = 0; i < planets.size(); i++)
        {
            planets[i].update(deltaTime);
        }
        for(unsigned int i = 0; i < Jim.size(); i++)
        {
            Jim[i].update(deltaTime);
        }
        for(unsigned int i = 0; i < meteorList.size(); i++)
        {
            meteorList[i].update(deltaTime);
        }

        //Create meteors until != 10
        while (meteorList.size() != n_meteorQuantity)
        {
            int modelNum = rand()%meteorModels.size();
            meteorList.push_back(meteor(rand()%640-320, 240.0f*xeRandOne(), 5.0f, 0.0f, meteorModels[modelNum].c_str(), &planets));
        }
        for (unsigned int i = 0; i < meteorList.size(); i++)
            if((meteorList[i].f_x > 320) | (meteorList[i].f_x < -320) | (meteorList[i].f_y > 240) | (meteorList[i].f_y < -240))
                meteorList.erase(meteorList.begin() + i);
        // xeDDrawCross(0.0f, 0.0f, 10.0f);
        // Ограничение FPS.
        if(b_FPScap && 1000/n_FPScap > int(SDL_GetTicks()-time))
        {
            SDL_Delay(1000/n_FPScap-(SDL_GetTicks()-time));
        }
        SDL_GL_SwapWindow(win);
    }
    endSDL();
    return 0;
}

void initGLandSDL()
{
    // Инициализация SDL

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        std::cout << "Unable to init SDL, error: " << SDL_GetError() << std::endl;
        exit(1);
    }

    // Включаем двойной буфер, настраиваем цвета

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);

    win = SDL_CreateWindow("Space Government",
                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           n_screenWidth, n_screenHeight,
                           SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    SDL_GLContext glcontext = SDL_GL_CreateContext(win); // создаем контекст OpenGL
    UNUSED(glcontext);

    if(win == NULL){ // если не получилось создать окно, то выходим
        exit(1);
    }

    // Инициализация OpenGL

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // устанавливаем фоновый цвет на черный
    glClearDepth(1.0);
    //    glDepthFunc(GL_LESS);
    //    glEnable(GL_DEPTH_TEST); // включаем тест глубины
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void endSDL()
{
    SDL_DestroyWindow(win);
    SDL_Quit();
}

