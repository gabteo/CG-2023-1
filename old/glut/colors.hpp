//#include "myLibsGL.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>



#ifndef COLORS_H
#define COLORS_H

struct color
    {
        float r;
        float g;
        float b;
    };

color lightBrown = 
{
    .r = 0.87,
    .g = 0.72,
    .b = 0.53
};

color rgbToFloat(int r, int g, int b); 


void setBackgroundColor(color color, float opacity = 1.0);

void renderScene();



#endif