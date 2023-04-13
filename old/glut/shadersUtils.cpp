#include "gutils.h"
#include <fstream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "shadersUtils.h"




char* loadCodeFromFile(codes code) {
	FILE *f;
	if (code == codes::vertexCode) 
	{
		FILE *f = fopen("vertex_code.txt", "rb");
	}
	else if (code == codes::fragmentCode)
	{
		FILE *f = fopen("fragment_code.txt", "rb");
	}

	
	
	int error = -1;
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *string = (char *)malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);

	string[fsize] = 0;
	return string;
	throw(error);	
}


void initShaders()
{
    // Request a program and shader slots from GPU
    program  = glCreateProgram();
    int vertex   = glCreateShader(GL_VERTEX_SHADER);
    int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    
	char *vertex_code = loadCodeFromFile(codes::vertexCode);
	char *fragment_code = loadCodeFromFile(codes::fragmentCode);

    // Set shaders source
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    // Compile shaders
    glCompileShader(vertex);
    glCompileShader(fragment);

    // Attach shader objects to the program
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Link the program
    glLinkProgram(program);

    // Get rid of shaders (not needed anymore)
    glDetachShader(program, vertex);
    glDetachShader(program, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    // Set the program to be used.
    glUseProgram(program);
}

