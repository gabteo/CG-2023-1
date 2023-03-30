/**
 * @file triangle.cpp
 * Draws a triangle.
 *
 * Defines the basics for drawing in OpenGL, shaders, arrays, buffers, etc.
 *
 * @author Ricardo Dutra da Silva
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>
using namespace std;

enum { X_AXIS, Y_AXIS };

/* Globals */
/** Window width. */
int win_width  = 800;
/** Window height. */
int win_height = 600;


/** Program variable. */
int program;
/** Vertex array object. */
unsigned int VAO;
/** Vertex buffer object. */
unsigned int VBO;

/** Vertex shader. */
const char *vertex_code = "\n"
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"out vec3 vColor;\n"
"\n"
"void main()\n"
"{\n"
"    gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
"    vColor = color;\n"
"}\0";

/** Fragment shader. */
const char *fragment_code = "\n"
"#version 330 core\n"

"in vec3 vColor;\n"
"layout (location = 0) out vec4 color;\n"

//"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"    color = vec4(vColor, 1.0f);\n"
"}\0";

/* Functions. */
//display
void display(void);
void reshape(int, int);

//user input
void keyboard(unsigned char, int, int);
void mouse(int button, int state, int x, int y);

// inits
void initData(void);
void initShaders(void);

struct point
{
    float x;
    float y;
} ;

typedef point vector2d;

vector<point> poq;


/** 
 * Map a click component to the [-1, 1] interval in a given axis.
 *
 *
 * @param value Original value to map.
 * @param axis Either X_AXIS or Y_AXIS of the click.
 * 
 *  @return A float in the interval [-1, 1].
 */
float normalizeClickInAxis(int value, int axis);

/** 
 * Map a click to the [-1, 1] interval in both axis.
 *
 *
 * @param x The x axis of the click.
 * @param y The y axis of the click.
 * 
 * @return A point struct whose components are in the interval [-1, 1].
 */
point normalizeClick(int x, int y);

void printPoint(point point);

float angleBetweenVectors(vector2d u, vector2d v);
float internalProduct(vector2d u, vector2d v);
point vectorialProduct(vector2d u, vector2d v);
