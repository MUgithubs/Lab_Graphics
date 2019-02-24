//
//  render.h
//  graphic_playGround
//
//  Created by Charles on 2019-02-21.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef render_h
#define render_h
#endif /* render_h */


#include "camera.h"
#include "bresenham.h"

void Draw();
void Draw_1();
void Draw_2();
void Draw_3();
void OnDisplay() {
    memset(frame, 255, windowW * windowH * 3);
    switch (num) {
        case 0:
            Draw();
            break;
        case 1:
            Draw_1();
            break;
        case 2:
            Draw_2();
            break;
        case 3:
            Draw_3();
            break;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glDrawPixels(windowW, windowH, GL_RGB, GL_UNSIGNED_BYTE, (GLubyte*)frame);
    glutSwapBuffers();
    glFlush();
}

void DrawPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);

void Draw() {

    dmatrix_t C ; // the main camera matrix.

    C = *camera_init();

    dmatrix_t x, y, z;//x, y, z for torus
    dmatrix_t x_s, y_s, z_s;//x_s, y_s, z_s for shpere

    dmat_alloc(&x,4,1) ;
    dmat_alloc(&y,4,1) ;
    dmat_alloc(&z,4,1) ;
    dmat_alloc(&x_s,4,1) ;
    dmat_alloc(&y_s,4,1) ;
    dmat_alloc(&z_s,4,1) ;

    //parametric equation
    //loc
    double center, radium_torus, radium_shpere, radium_torus_pipe;
    radium_torus = 200;radium_torus_pipe = 20;
    radium_shpere = 80;
    center = W/2;

    double du = 2.0*M_PI/8; //or 32, it depends;
    double dv = 2.0*M_PI/100;

    for(double v = 0.0 ; v <= 2.0*M_PI;v+=dv){
        for (double u = 0.0 ; u <= 2.0*M_PI;u+=du) {
            //x, y, z for torus
            x.m[1][1] = (radium_torus+radium_torus_pipe*cos(u))*cos(v);
            x.m[2][1] = (radium_torus+radium_torus_pipe*cos(u))*sin(v);
            x.m[3][1] = radium_torus_pipe*sin(u);
            x.m[4][1] = 1 ;
            x = *perspective_projection(dmat_mult(&C,&x));
            y.m[1][1] = (radium_torus+radium_torus_pipe*cos(u+du))*cos(v);
            y.m[2][1] = (radium_torus+radium_torus_pipe*cos(u+du))*sin(v);
            y.m[3][1] = radium_torus_pipe*sin(u+du);
            y.m[4][1] = 1;
            y = *perspective_projection(dmat_mult(&C,&y));
            z.m[1][1] = (radium_torus+radium_torus_pipe*cos(u))*cos(v+dv);
            z.m[2][1] = (radium_torus+radium_torus_pipe*cos(u))*sin(v+dv);
            z.m[3][1] = radium_torus_pipe*sin(u);
            z.m[4][1] = 1;
            z = *perspective_projection(dmat_mult(&C,&z));

            Line(x.m[1][1],x.m[2][1],y.m[1][1],y.m[2][1]) ;
            Line(x.m[1][1],x.m[2][1],z.m[1][1],z.m[2][1]) ;
        }
    }

    //u_s, v_s, du_s, dv_s are values for shpere
    double dv_s = 2.0*M_PI/40.0;
    double du_s = M_PI/16.0;

    /* Notice: the shpere's u, that is every slices' euqation, only need run a half */
    for(double v_s = 0.0; v_s <= 2*M_PI; v_s+=dv_s){
        for (double u_s = 0.0; u_s <= M_PI; u_s+=du_s) {
            //loc
            x_s.m[1][1] = radium_shpere*cos(v_s)*sin(u_s);
            x_s.m[2][1] = radium_shpere*sin(v_s)*sin(u_s);
            x_s.m[3][1] = radium_shpere*cos(u_s);
            x_s.m[4][1] = 1 ;
            x_s = *perspective_projection(dmat_mult(&C,&x_s));
            y_s.m[1][1] = radium_shpere*cos(v_s)*sin(u_s+du_s);
            y_s.m[2][1] = radium_shpere*sin(v_s)*sin(u_s+du_s);
            y_s.m[3][1] = radium_shpere*cos(u_s+du_s);
            y_s.m[4][1] = 1;
            y_s = *perspective_projection(dmat_mult(&C,&y_s));
            z_s.m[1][1] = radium_shpere*cos(v_s+dv_s)*sin(u_s);
            z_s.m[2][1] = radium_shpere*sin(v_s+dv_s)*sin(u_s);
            z_s.m[3][1] = radium_shpere*cos(u_s);
            z_s.m[4][1] = 1;
            z_s = *perspective_projection(dmat_mult(&C,&z_s));

            Line( x_s.m[1][1],
                 x_s.m[2][1],
                 y_s.m[1][1],
                 y_s.m[2][1]) ;
            Line( x_s.m[1][1],
                 x_s.m[2][1],
                 z_s.m[1][1],
                 z_s.m[2][1]) ;
        }
    }
}

void Draw_1(){
    o1(100,100,200,650);
}
void Draw_2(){
    Line(1,1,100,100);
}
void Draw_3(){
    Line(1,1,100,100);
}
