#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "gutils.h"

using namespace geometry;


namespace geometry {


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
    normalized.x = geometry::normalizeClickInAxis(x, X_AXIS);
    normalized.y = geometry::normalizeClickInAxis(y, Y_AXIS);

    return normalized;
}


}





