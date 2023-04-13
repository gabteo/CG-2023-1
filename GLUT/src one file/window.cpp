#include "../includes/gutils.h"
#include "../includes/window.h"
#include "../includes/shadersUtils.h"
#include "../includes/colors.h"

#include <iostream>
using namespace std;

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

void renderScene()
{
   /*  setBackgroundColor(lightBrown);
    //setBackgroundColor(rgbToFloat(3, 169, 252));
    //glClearColor(0.87, 0.72, 0.53, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(VAO);
    
    // Draws the triangle.
    glDrawArrays(GL_TRIANGLES, 0, 3);
    cout << "drawing two triangles" << endl;

    glutSwapBuffers(); */


    glClearColor(0.37, 0.72, 0.53, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(VAO);
    // Draws the triangle.
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glutSwapBuffers();
} 


void reshape(int width, int height)
{
    win_width = width;
    win_height = height;
    glViewport(0, 0, width, height);
    glutPostRedisplay();
	//renderScene();
}
