#ifndef SHADERS_UTILS_H
#define SHADERS_UTILS_H

#include <fstream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "gutils.h"

enum class codes {
    vertexCode,
    fragmentCode
};

/** Program variable. */
int program;
/** Vertex array object. */
unsigned int VAO;
/** Vertex buffer object. */
unsigned int VBO;

/**
 * Loads a file containg the vertex shader or the fragment shader
*/
char* loadCodeFromFile(codes code);


/** Create program (shaders).
 * Compile shaders and create the program.
*/
void initShaders();


#endif