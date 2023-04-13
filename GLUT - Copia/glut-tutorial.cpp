#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

//#include "window.h"
//#include "gutils.h"
//#include "inputHandlers.h"
//#include "shadersUtils.h"
#include "colors.h"


#define HD_WIN_WIDTH 1280
#define HD_WIN_HEIGH 720

#define WIN_WIDTH HD_WIN_WIDTH
#define WIN_HEIGH HD_WIN_HEIGH

int win_width = WIN_WIDTH;
int win_height = WIN_HEIGH;
/** Program variable. */
int program;
/** Vertex array object. */
unsigned int VAO;
/** Vertex buffer object. */
unsigned int VBO;

void setBackgroundColor(color color, float opacity)
{
    glClearColor(color.r, color.g, color.b, opacity);
    return;
}

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

//void (*renderPtr)() = renderScene;

void keyboard(unsigned char key, int x, int y)
{
        switch (key)
        {
                case 27:
                    glutLeaveMainLoop();
                case 'q':
                case 'Q':
                    glutLeaveMainLoop();
        }

}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN){
        switch (button)
        {
        case GLUT_LEFT_BUTTON:
#if LISTA2
            if (poq.size() < 3) 
            {
                point click;
                click = normalizeClick(x, y);
                //printPoint(click);
                poq.push_back(click);
            }
            if ( poq.size() == 3 ) 
            {
                //initData();
            	initShaders();
                
                //display();
                string hello = "hello";
                //outputText(30, 30, hello);
                renderScene();

                poq.clear();
            }
#endif
            break;
        default:
            break;
        }
    }
}

int main(int argc, char **argv) 
{
/** 
 * /mnt/c/Users/gabte/Documents/UTFPR/2023-1/CG/GLUT
**/
    //pudim();
	// init GLUT and create window
    glutInit(&argc, argv);
	//glutInitContextVersion(3, 3);
	//glutInitContextProfile(GLUT_CORE_PROFILE);

    //glutInitWindowPosition(int x, int y);
	glutInitWindowSize(WIN_WIDTH, WIN_HEIGH);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow(argv[1]);
	glewInit();

	// register callbacks
   	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);

	// enter GLUT event processing cycle
	glutMainLoop();


	return 0;

}