
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "L02.h"
#include <math.h> 
#include <iostream>
using namespace std;


enum POQ { P, O, Q };


float normalizeClickInAxis(int value, int axis) 
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

void outputText(int x, int y, string str)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, win_width, 0.0, win_height);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f( 0.0f,1.0f, 0.0f );
    glRasterPos2f(x, y);
    void * font = GLUT_BITMAP_9_BY_15;
    int len;
    len = (int)str.length();
    for (int i = 0; i < len; i++) {
        glutBitmapCharacter(font, str[i]);
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

point normalizeClick(int x, int y)
{
    point normalized;
    normalized.x = normalizeClickInAxis(x, X_AXIS);
    normalized.y = normalizeClickInAxis(y, Y_AXIS);

    return normalized;
}

double angleBetweenVectors(vector2d u, vector2d v)
{
    double angle;

    double uv = internalProduct(u, v);
    double denominator = mag(u)*mag(v);

    double cos = uv/denominator;
    angle = acos(cos);


    return angle;
}

double internalProduct(vector2d u, vector2d v)
{
    return u.x * v.x + u.y * v.y;
}

/* vector2d vectorialProduct(vector2d u, vector2d v)
{

    return vector2d(0,0);
} */

double mag(vector2d u)
{
    return sqrt(pow(u.x, 2) + pow(u.y, 2));
}


void printPoint(point point) 
{
    printf("%f/n", point.x);
    printf("%f/n/n", point.y);

    return;
}

/** 
 * Drawing function.
 *
 * Draws a triangle.
 */
void display()
{
    	glClearColor(0.87, 0.72, 0.53, 1.0);
    	glClear(GL_COLOR_BUFFER_BIT);

    	glUseProgram(program);
    	glBindVertexArray(VAO);
    	// Draws the triangle.
        glLineWidth(255);
    	glDrawArrays(GL_LINE_STRIP, 0, 3);

    	glutSwapBuffers();

}

/**
 * Reshape function.
 *
 * Called when window is resized.
 *
 * @param width New window width.
 * @param height New window height.
 */
void reshape(int width, int height)
{
    win_width = width;
    win_height = height;
    glViewport(0, 0, width, height);
    glutPostRedisplay();
}


/** 
 * Keyboard function.
 *
 * Called to treat pressed keys.
 *
 * @param key Pressed key.
 * @param x Mouse x coordinate when key pressed.
 * @param y Mouse y coordinate when key pressed.
 */
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


/** 
 * Mouse function.
 *
 * Called to treat pressed buttons on the mouse.
 *
 * @param button Pressed button.
 * @param x Mouse x coordinate when key pressed.
 * @param y Mouse y coordinate when key pressed.
 * @param state GLUT_DOWN or GLUT_UP.
 * 
 */
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN){
        switch (button)
        {
        case GLUT_LEFT_BUTTON:
            if (poq.size() < 3) 
            {
                point click;
                click = normalizeClick(x, y);
                //printPoint(click);
                poq.push_back(click);
            }
            if ( poq.size() == 3 ) 
            {
                initData();
            	initShaders();
                
                //display();
                //string hello = "hello";
                //outputText(30, 30, hello);
                cout << "Dois vetores!" << endl;
                vector2d u;
                vector2dFromPoints();
                display();

                poq.clear();
            }
            
            break;

        default:
            break;
        }
    }
}

/**
 * Init vertex data.
 *
 * Defines the coordinates for vertices, creates the arrays for OpenGL.
 */

void initData()
{
    // Set triangle vertices.
    float vertices[] = {
        poq[P].x, poq[P].y, 0,      0.96f, 0.49f, 0.50f,
        poq[O].x, poq[O].y, 0,      0.11f, 0.71f, 0.88f,
        poq[Q].x, poq[Q].y, 0,      0.50f, 0.5f, 0.45f
    };
    
    // Vertex array object.
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Vertex buffer
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Set attributes.
    // COORDENADA
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // COLOR
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind Vertex Array Object.
    glBindVertexArray(0);
}

/** Create program (shaders).
 * 
 * Compile shaders and create the program.
 */
void initShaders()
{
    // Request a program and shader slots from GPU
    program  = glCreateProgram();
    int vertex   = glCreateShader(GL_VERTEX_SHADER);
    int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    
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

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(win_width,win_height);
	glutCreateWindow(argv[0]);
	glewInit();

    	// Init vertex data for the triangle.
    	//initData();
    
    	// Create shaders.
    	//initShaders();
	
    	glutReshapeFunc(reshape);
    	glutDisplayFunc(display);
    	glutKeyboardFunc(keyboard);
        glutMouseFunc(mouse);

        glEnable(GL_LINE_SMOOTH);

        
	glutMainLoop();
}
