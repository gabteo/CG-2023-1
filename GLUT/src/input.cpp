#include "../includes/input.h"
#include "../includes/gutils.h"

#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

#include <iostream>
using namespace std;

void keyboard(unsigned char key, int x, int y)
{
    cout << "Pressed: " <<  key << endl;

    switch (key)
    {
        case 27:
            glutLeaveMainLoop();
            break;
        case 'q':
        case 'Q':
            glutLeaveMainLoop();
            break;
        case '2':
            listaAtual = lista::lista2;
            break;
        default:
            break;
    }
	glutPostRedisplay();

}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN){
        switch (button)
        {
            case GLUT_LEFT_BUTTON:
                 cout << "Selecionou lista 2." << endl;

                /* switch (listaAtual)
                {
                    case lista::lista2:
                        clickLista2(x, y);
                        cout << "Selecionou lista 2." << endl;
                        break;
                    
                    default:
                        break;
                } */
                break;

            default:
                break;
        }
    }
	//glutPostRedisplay();

}

void clickLista2(int x, int y)
{
#ifdef L2
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
        

        renderScene();

        poq.clear();
    }
#endif
}