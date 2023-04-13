#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

//#include <GL/gl.h>

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include "../includes/gutils.h"
#include "../includes/input.h"
#include "../includes/colors.h"
#include "../includes/shadersUtils.h"
#include "../includes/window.h"

void initShaders()
{
    // Request a program and shader slots from GPU
    program  = glCreateProgram();
    int vertex   = glCreateShader(GL_VERTEX_SHADER);
    int fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //loadCodeFromFile(codes::vertexCode);
    
	//char *vertex_code = loadCodeFromFile(codes::vertexCode);
	//char *fragment_code = loadCodeFromFile(codes::fragmentCode);


    // Set shaders source code
    glShaderSource(vertex, 1, &vertex_code, NULL);
    glShaderSource(fragment, 1, &fragment_code, NULL);

    // Compile shaders
    glCompileShader(vertex);
    
    int  success;
    char infoLog[512];
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else 
    {
        cout << "Success compiling vertex shader." << success << endl;
    }

    
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else 
    {
        cout << "Success compiling fragment shader." << endl;
    }



    // Attach shader objects to the program
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    // Link the program
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    } else 
    {
        cout << "Success linking vertex and fragment shaders to program." << endl;
    }

    // Get rid of shaders (not needed anymore)
    glDetachShader(program, vertex);
    glDetachShader(program, fragment);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    
    // Set the program to be used.
    // 2. use our shader program when we want to render an object
    glUseProgram(program);
}

void renderScene()
{
    setBackgroundColor(lightBrown);
    //setBackgroundColor(rgbToFloat(3, 169, 252));
    //glClearColor(0.87, 0.72, 0.53, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(VAO);
    
    // Draws the triangle.
    cout << "Rendering scene..." << endl;
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glutSwapBuffers();


/*         	glClearColor(0.87, 0.72, 0.53, 1.0);
    	glClear(GL_COLOR_BUFFER_BIT);

    	glUseProgram(program);
    	glBindVertexArray(VAO);
    	// Draws the triangle.
    	glDrawArrays(GL_TRIANGLES, 0, 6);

    	glutSwapBuffers(); */
} 






void initData()
{
    // Set triangle vertices.
    float vertices[] = {
	// First triangle
        // coordinate     color
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        // Second triangle
        // coordinate     color
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.8f, 0.0f, 1.0f, 0.0f, 0.0f
/*         -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
        // Second triangle
        // coordinate     color
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f */
    };
    
    // Generate a vertex array with an unique array id (1).???
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate a vertex buffer with an unique buffer id (1).
    // Vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// 0. copy our vertices array in a buffer for OpenGL to use
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    
	/*----------------------------------------------------------------------------------------*/
	// Set attributes. 
	// 1. then set the vertex attributes pointers
	// Location = 0 (layout location 0); size = 3 (x, y, z); distance from x to x =  6*sizeof(float); starts at [0]
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

	// Location = 1; size = 3 (r, g, b); distance from x to x =  6*sizeof(float); starts at [3]
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind Vertex Array Object.
    glBindVertexArray(0);
}

int main(int argc, char **argv) 
{
/** 
 * /mnt/c/Users/gabte/Documents/UTFPR/2023-1/CG/GLUT
**/

	// init GLUT and create window
    glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);

    //glutInitWindowPosition(int x, int y);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(win_width, win_height);

	glutCreateWindow(argv[1]);
	glewInit();

        initData();
        initShaders();
        
        // register callbacks
        glutReshapeFunc(reshape);
        glutDisplayFunc(renderScene);
        glutKeyboardFunc(keyboard);
        //glutMouseFunc(mouse);

	

	// enter GLUT event processing cycle
	glutMainLoop();


	//return 0;

}