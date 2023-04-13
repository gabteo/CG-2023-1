#include <GL/glew.h>
#include <GL/freeglut.h>
#include "gutils.h"

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