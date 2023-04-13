#include "colors.hpp"


void setBackgroundColor(color color, float opacity)
{
    glClearColor(color.r, color.g, color.b, opacity);
    return;
}

color rgbToFloat(int r, int g, int b)
{
    color color;
    color.r = ((float)r)/255.0;
    color.g = ((float)g)/255.0;
    color.b = ((float)b)/255.0;

    return color;
}

