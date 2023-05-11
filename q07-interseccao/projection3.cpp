/**
 * @file projection3.cpp
 * Applies a perspective projection to draw a triangle and a line.
 * 
 * @author Ricardo Dutra da Silva
 */

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "../lib/utils.h"

using namespace std;

/* Globals */
/** Window width. */
int win_width  = 600;
/** Window height. */
int win_height = 600;

/** Program variable. */
int program;
/** Vertex array object. */
unsigned int VAO1;
/** Vertex buffer object. */
unsigned int VBO1;
/** Vertex array object. */
unsigned int VAO2;
/** Vertex buffer object. */
unsigned int VBO2;

GLuint feedbackBuffer;


/** Pyramid x angle */
float px_angle = 0.0f;
/** Pyramid x angle increment */
float px_inc = 0.01f;
/** Pyramid y angle */
float py_angle = 0.0f;
/** Pyramid y angle increment */
float py_inc = 0.02f;

/** Cube x angle */
float cx_angle = 0.0f;
/** Cube x angle increment */
float cx_inc = 0.01f;
/** Cube y angle (orbit) */
float cy_angle = 0.0f;
/** Cube y angle increment */
float cy_inc = 0.03f;
/** Cube z angle */
float cz_angle = 0.0f;
/** Cube z angle increment */
float cz_inc = 0.02f;


/** Vertex shader. */
const char *vertex_code = "\n"
"#version 330 core\n"
"layout (location = 0) in vec3 position;\n"
"layout (location = 1) in vec3 color;\n"
"\n"
"out vec3 vColor;\n"
"out vec4 positionOut;\n"
"\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"\n"
"void main()\n"
"{\n"
"    positionOut = projection * view * model * vec4(position, 1.0);\n"
"    gl_Position = projection * view * model * vec4(position, 1.0);\n"
"    vColor = color;\n"
"}\0";

/** Fragment shader. */
const char *fragment_code = "\n"
"#version 330 core\n"
"\n"
"in vec3 vColor;\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"    FragColor = vec4(vColor, 1.0f);\n"
"}\0";

struct vector4
{
    float x;
    float y;
    float z;
    float w;

    vector4 operator/(float divisor)
    {
        vector4 result;
        result.x = x/divisor;
        result.y = y/divisor;
        result.z = z/divisor;
        return result;
    }

    vector4 operator-(vector4 b)
    {
        vector4 result;
        result.x = x - b.x;
        result.y = y - b.y;
        result.z = z - b.z;
        result.w = 1.0f;
        return result;
    }
};

struct point4
{
    float x;
    float y;
    float z;
    float w;

    vector4 operator-(point4 b)
    {
        vector4 result;
        result.x = x - b.x;
        result.y = y - b.y;
        result.z = z - b.z;
        result.w = 1.0f;
        return result;
    }
};

struct planeEquation
{
    float x;
    float y;
    float z;
    float w;
};

struct lineParametricEquation
{
    point4 e;
    vector4 d;
    float t;
};

struct lineParametricCoordinate
{
    float e;
    float d;

    lineParametricCoordinate operator*(float factor) {
        lineParametricCoordinate result;
        result.e = e*factor;
        result.d = d*factor;
        return result;
    }
};

/* Functions. */
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);
void idle(void);
void initData(void);
void initShaders(void);

planeEquation getPlaneEquation(vector4 normal, point4 point);
bool intersectionLinePlane();
vector4 vectorialProduct(vector4 u, vector4 v);
vector4 getNormalFromVectors(vector4 u, vector4 v);
vector4 getVector4FromCoordinates(float x, float y, float z);
vector4 getVector4FromPoints(point4 p, point4 q);
vector4 getVector4FromPoints(point4 p, point4 q);
vector4 normalizeVector4(vector4 u);
float getVectorMagnitude(vector4 u);
lineParametricEquation getLineParametricEquation(point4 origin, vector4 direction, float magnitude);


planeEquation getPlaneEquation(vector4 normal, point4 point) {
    planeEquation parameters;
    parameters.x = normal.x;
    parameters.y = normal.y;
    parameters.z = normal.z;
    parameters.w = normal.x*point.x + normal.y*point.y + normal.z*point.z;
    return parameters;
}

lineParametricEquation getLineParametricEquation(point4 origin, vector4 direction, float magnitude = 1.0f) {
    lineParametricEquation line { 
        origin,
        direction,
        magnitude
    };
    return line;
}

bool intersectionLinePlane(lineParametricEquation line, planeEquation plane) {
    lineParametricCoordinate lineX {
        line.e.x,
        line.d.x
    };
    lineParametricCoordinate lineY {
        line.e.y,
        line.d.y
    };
    lineParametricCoordinate lineZ {
        line.e.z,
        line.d.z
    };
    lineX = lineX*plane.x;
    lineY = lineY*plane.x;
    lineZ = lineZ*plane.x;

    float totalD = lineX.d + lineY.d + lineZ.d;
    float totalE = plane.w - (lineX.e + lineY.e + lineZ.e);
    float t = totalE/totalD;    // t for which an intersection occurs

    if (t <= line.t) {
        return true;
    }
    return false;
}

vector4 vectorialProduct(vector4 u, vector4 v) 
{
    vector4 result;
    result.x = u.x*v.z - u.z*v.y;
    result.y = u.z*v.x - u.x*v.z;
    result.z = u.x*v.y - u.y*v.x;
    result.w = 1.0f;
    
    return result;
}

vector4 getNormalFromVectors(vector4 u, vector4 v) {
    return vectorialProduct(u, v);
}

vector4 getVector4FromCoordinates(float x, float y, float z) {
    vector4 u {x, y, z, 1.0f};
    return u;
}

vector4 getVector4FromPoints(point4 p, point4 q) {
    vector4 point =  p - q;
    /* vector4 result {
        result.x = point.x,
        result.y = point.y,
        result.z = point.z,
        result.w = 1.0f,
    }; */
    return point;
}

vector4 normalizeVector4(vector4 u) {
    return u/getVectorMagnitude(u);
}

float getVectorMagnitude(vector4 u) {
    return sqrt(pow(u.x, 2) + pow(u.y, 2) + pow(u.z, 2));
}
/** 
 * Drawing function.
 *
 * Draws primitive.
 */
void display()
{
    	glClearColor(0.6, 0.8, 0.3, 1.0);
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    	glUseProgram(program);
	
	// Define view matrix.
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-3.0f));

    	// Retrieve location of tranform variable in shader.
	unsigned int loc = glGetUniformLocation(program, "view");
   	// Send matrix to shader.
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(view));

    	// Define projection matrix.
	glm::mat4 projection = glm::perspective(glm::radians(60.0f), (win_width/(float)win_height), 0.1f, 100.0f);
    	// Retrieve location of tranform variable in shader.	
 	loc = glGetUniformLocation(program, "projection");
   	// Send matrix to shader.
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(projection));
	
	// Pyramid --> linha
	glBindVertexArray(VAO2);

    	// Define model matrix.
	glm::mat4 S  = glm::scale(glm::mat4(1.0f), glm::vec3(1.3f, 1.3f, 1.3f));
	glm::mat4 Rx = glm::rotate(glm::mat4(1.0f), glm::radians(px_angle), glm::vec3(1.0f,0.0f,0.0f));
	glm::mat4 Ry = glm::rotate(glm::mat4(1.0f), glm::radians(py_angle), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 T  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-1.0f));
	//glm::mat4 model = glm::mat4(1.0f); //T*Ry*Rx*S;
	glm::mat4 model = T*Ry*Rx;

    	// Retrieve location of tranform variable in shader.
	loc = glGetUniformLocation(program, "model");
   	// Send matrix to shader.
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));



    
    glBeginTransformFeedback(GL_LINES);
    	glDrawArrays(GL_LINES, 0, 2);
    glEndTransformFeedback();
    
    int numVertices = 2;
    glm::vec4* feedbackData = new glm::vec4[numVertices];
    glGetBufferSubData(GL_ARRAY_BUFFER, 0, numVertices * sizeof(glm::vec4), feedbackData);

    for(int i = 0; i < numVertices; i++) {
        cout << "x: " << feedbackData[i].x << " y: " << feedbackData[i].y << " z: " << feedbackData[i].z<< endl;
    }




    // ------------------------------------------
	// Cube --> triangula
	glBindVertexArray(VAO1);

    	// Define model matrix.
	S  = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f,0.3f,0.3f));
	Rx = glm::rotate(glm::mat4(1.0f), glm::radians(cx_angle), glm::vec3(1.0f,0.0f,0.0f));
	Ry = glm::rotate(glm::mat4(1.0f), glm::radians(cy_angle), glm::vec3(0.0f,1.0f,0.0f));
	glm::mat4 Rz = glm::rotate(glm::mat4(1.0f), glm::radians(cz_angle), glm::vec3(0.0f,0.0f,1.0f));
	T  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-2.0f));
	model = T*Ry*T*Rx*Rz;

    	// Retrieve location of tranform variable in shader.
	loc = glGetUniformLocation(program, "model");
   	// Send matrix to shader.
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(model));
	
    	glDrawArrays(GL_TRIANGLES, 0, 3);

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
    
	glutPostRedisplay();
}

/**
 * Idle function.
 *
 * Called continuously.
 */
void idle()
{
    px_angle = ((px_angle+px_inc) < 360.0f) ? px_angle+px_inc : 360.0-px_angle+px_inc;
    py_angle = ((py_angle+py_inc) < 360.0f) ? py_angle+py_inc : 360.0-py_angle+py_inc;

    cx_angle = ((cx_angle+cx_inc) < 360.0f) ? cx_angle+cx_inc : 360.0-cx_angle+cx_inc;
    cy_angle = ((cy_angle+cy_inc) < 360.0f) ? cy_angle+cy_inc : 360.0-cy_angle+cy_inc;
    cz_angle = ((cz_angle+cz_inc) < 360.0f) ? cz_angle+cz_inc : 360.0-cz_angle+cz_inc;

    glutPostRedisplay();
}


/**
 * Init vertex data.
 *
 * Defines the coordinates for vertices, creates the arrays for OpenGL.
 */
void initData()
{
    // Set triangle vertices.
    float triangle[] = {
	//Front face first triangle.
        // coordinate       // color
        -0.5f, -0.5f,  0.5f,  0.5f, 0.0f, 0.2f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.6f, 0.8f,
         0.5f,  0.5f,  0.5f,  0.9f, 0.7f, 0.0f,

    };
    
    // Vertex array.
    glGenVertexArrays(1, &VAO1);
    glBindVertexArray(VAO1);

    // Vertex buffer
    glGenBuffers(1, &VBO1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    
    // Set attributes.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);


    glGenBuffers(2, &feedbackBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, feedbackBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(glm::vec4), nullptr, GL_DYNAMIC_COPY);

    glBindBuffer(GL_ARRAY_BUFFER, feedbackBuffer);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 8*sizeof(float), nullptr);

    const char* outputNames[] = { "positionOut" }; // the name of the output variable in your shader
    glTransformFeedbackVaryings(program, 1, outputNames, GL_INTERLEAVED_ATTRIBS);

    
    float line[] = {
	    //Front face first triangle.
        // coordinate        // color
	    -0.9f,  0.0f,  0.0f, 0.53f, 0.1f, 0.2f,
         0.9f,  0.0f,  0.0f, 0.53f, 0.1f, 0.2f,

    };
    
    // Vertex array.
    glGenVertexArrays(1, &VAO2);
    glBindVertexArray(VAO2);

    // Vertex buffer
    glGenBuffers(1, &VBO2);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(line), line, GL_STATIC_DRAW);
    
    // Set attributes.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind Vertex Array Object.
    glBindVertexArray(0);
    
    glEnable(GL_DEPTH_TEST);
}

/** Create program (shaders).
 * 
 * Compile shaders and create the program.
 */
void initShaders()
{
    // Request a program and shader slots from GPU
    program = createShaderProgram(vertex_code, fragment_code);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(win_width,win_height);
	glutCreateWindow(argv[0]);
	glewInit();

    	// Init vertex data for the triangle.
    	initData();
    
    	// Create shaders.
    	initShaders();
	
    	glutReshapeFunc(reshape);
    	glutDisplayFunc(display);
    	glutKeyboardFunc(keyboard);
    	glutIdleFunc(idle);

	glutMainLoop();
}
