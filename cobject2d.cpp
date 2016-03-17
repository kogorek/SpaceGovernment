#include "cobject2d.h"

Object2D::Object2D(float fx, float fy, float fsize, float fangle, const char* str_path)
{
    f_x = fx;
    f_y = fy;
    f_size = fsize;
    f_angle = fangle;
    loadModel(str_path);
}

bool Object2D::loadModel(const char* str_path)
{
    std::ifstream modelFile;
    modelFile.open(str_path);
    if (modelFile.fail())
    {
        std::cerr << "Error: cannot open OBJ file: " << str_path << std::endl;
        return true;
    }

    for (int i = 0; !modelFile.eof(); i++)
    {
        fig.push_back(figure());
        modelFile >> fig[i].f_x >> fig[i].f_y;
    }
    modelFile.close();
    return false;
}

void Object2D::draw()
{
    glPushMatrix();
    glTranslatef(f_x, f_y, 0.0f);
    glRotatef(f_angle, 0.0f, 0.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    for (unsigned int i = 0; i < fig.size(); i++)
    {
        glVertex2f(fig[i].f_x*f_size, fig[i].f_y*f_size);
    }
    glEnd();
    glPopMatrix();
}
