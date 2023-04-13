

#ifndef GUTILS_H
#define GUTILS_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

//#define LISTA2 0

#define HD_WIN_WIDTH 1280
#define HD_WIN_HEIGH 720

#define WIN_WIDTH HD_WIN_WIDTH
#define WIN_HEIGH HD_WIN_HEIGH

int win_width = WIN_WIDTH;
int win_height = WIN_HEIGH;


enum { X_AXIS, Y_AXIS };


namespace geometry {
    

    struct point
    {
        float x;
        float y;
        float z;
    };

    typedef point vector3;

    struct vector4
    {
        float x;
        float y;
        float z;
        float w;
    };

     

    point normalizeClick(int x, int y);
    float normalizeClickInAxis(int value, int axis, int win_width, int win_height);





}


#endif