//
//  main.cpp
//  graphic_playGround, from CS 3388 asn#1
//
//  Created by Charles on 2019-02-19.
//  Copyright © 2019 Mu He. All rights reserved.
//

#include "render.h"
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>

void OnDisplay();
//read from keyboard
void OnKeyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'q':
            exit(0);
            break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowW, windowH);
    glutFullScreen();
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Graphics PlayGround");
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glShadeModel(GL_FLAT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //num = 0: trous; = 1: bresenhem;
    num = 0;

    //-- run the program
    glutDisplayFunc(OnDisplay);
    glutKeyboardFunc(OnKeyboard);
    glutMainLoop();

    return 0;
}
