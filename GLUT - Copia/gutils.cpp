#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "gutils.h"
//#include "colors.h"
//using namespace geometry;


//namespace geometry {
color rgbToFloat(int r, int g, int b)
{
    color color;
    color.r = ((float)r)/255.0;
    color.g = ((float)g)/255.0;
    color.b = ((float)b)/255.0;

    return color;
}

float normalizeClickInAxis(int value, int axis, int win_width = win_width, int win_height = win_height) 
{

    if (axis == X_AXIS)
    {
        return ( 2 * (float)value / win_width ) - 1;
    }
    else 
    {
        return (( 2 * (float)value / win_height ) - 1)*(-1);
    }
}

point normalizeClick(int x, int y)
{
    point normalized;
    normalized.x = normalizeClickInAxis(x, X_AXIS);
    normalized.y = normalizeClickInAxis(y, Y_AXIS);

    return normalized;
}





//}





