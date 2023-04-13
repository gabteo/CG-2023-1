#include "../includes/shadersUtils.h"

#include <fstream>
#include <iostream>
using namespace std;


#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "../includes/gutils.h"

char* loadCodeFromFile(codes code) {
	FILE *f;
    //ifstream file;
	if (code == codes::vertexCode) 
	{
		f = fopen("src/vertex_code.vs", "r");
	}
	else if (code == codes::fragmentCode)
	{
        f = fopen("src/fragment_code.fs", "r");
	}
    if(f == NULL)
    {
        cout << "Não abriu o arquivo." << endl;
        perror("Erro abrindo arquivo!");
    } else
    {
        cout << "Abriu o arquivo. Ponteiro aponta para " << f << endl;
    }

    rewind(f);
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);
    
    cout << "tamanho: " << fsize << endl;

	char *string = (char *)malloc(fsize + 1);
	fread(string, fsize, 1, f);
	fclose(f);


	string[fsize] = 0;
    cout << "Início do código do " << ((code == codes::vertexCode)? "Vertex" : "Fragment") << "Shader" << string << endl;
	return string;
}
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
//"layout (location = 0) out vec4 color;\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"    FragColor = vec4(vColor, 1.0f);\n"
"}\0";

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

