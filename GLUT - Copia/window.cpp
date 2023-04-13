#include "gutils.h"
#include "window.h"
#include "shadersUtils.h"


void renderScene()
{
    glClearColor(0.87, 0.72, 0.53, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    glBindVertexArray(VAO);
    // Draws the triangle.
    glDrawArrays(GL_TRIANGLES, 0, 6);

    /* 	glBegin(GL_TRIANGLES);
        glVertex3f(-0.5,-0.5,0.0);
        glVertex3f(0.5,0.0,0.0);
        glVertex3f(0.0,0.5,0.0);
    glEnd(); */

    glutSwapBuffers();
} 


void reshape(int width, int height)
{
    win_width = width;
    win_height = height;
    glViewport(0, 0, width, height);
    glutPostRedisplay();
	renderScene();
}