//
//  camera.h
//  graphic_playGround
//
//  Created by Charles on 2019-02-21.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef camera_h
#define camera_h
#endif /* camera_h */

#include <iostream>
#include <utility>
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#include <math.h>

#include "matrix.h"
#include "environment.h"

dmatrix_t *build_camera_matrix(dmatrix_t *E, dmatrix_t *G) {

    dmatrix_t N ; /* Viewing axis */

    N = *dmat_normalize(dmat_sub(E,G)) ;
    N.l = 3 ;

    dmatrix_t UP ;
    dmat_alloc(&UP,4,1) ;
    UP.l = 3 ;

    UP.m[1][1] = UPx ;
    UP.m[2][1] = UPy ;
    UP.m[3][1] = UPz ;
    UP.m[4][1] = 1.0 ;

    dmatrix_t U ;

    U = *dmat_normalize(dcross_product(&UP,&N)) ;

    dmatrix_t V ;
    V = *dcross_product(&N,&U) ;

    dmatrix_t Mv ; /* Build matrix M_v */
    dmat_alloc(&Mv,4,4) ;

    Mv.m[1][1] = U.m[1][1] ;
    Mv.m[1][2] = U.m[2][1] ;
    Mv.m[1][3] = U.m[3][1] ;
    Mv.m[1][4] = -1.0*((*E).m[1][1]*U.m[1][1] + (*E).m[2][1]*U.m[2][1] + (*E).m[3][1]*U.m[3][1]) ;

    Mv.m[2][1] = V.m[1][1] ;
    Mv.m[2][2] = V.m[2][1] ;
    Mv.m[2][3] = V.m[3][1] ;
    Mv.m[2][4] = -1.0*((*E).m[1][1]*V.m[1][1] + (*E).m[2][1]*V.m[2][1] + (*E).m[3][1]*V.m[3][1]) ;

    Mv.m[3][1] = N.m[1][1] ;
    Mv.m[3][2] = N.m[2][1] ;
    Mv.m[3][3] = N.m[3][1] ;
    Mv.m[3][4] = -1.0*((*E).m[1][1]*N.m[1][1] + (*E).m[2][1]*N.m[2][1] + (*E).m[3][1]*N.m[3][1]) ;

    Mv.m[4][1] = 0.0 ;
    Mv.m[4][2] = 0.0 ;
    Mv.m[4][3] = 0.0 ;
    Mv.m[4][4] = 1.0 ;

    dmatrix_t Mp ; /* Build matrix Mp */
    dmat_alloc(&Mp,4,4) ;
    Mp = *dmat_identity(&Mp) ;

    float a = -1.0*(FP + NP)/(FP - NP) ;
    float b = -2.0*(FP*NP)/(FP - NP) ;

    Mp.m[1][1] = NP ;
    Mp.m[2][2] = NP ;
    Mp.m[3][3] = a ;
    Mp.m[3][4] = b ;
    Mp.m[4][3] = -1.0 ;
    Mp.m[4][4] = 0.0 ;

    /* Build matrices T_1 and S_1 */

    /* Work out coordinates of near plane corners */

    float top = NP*tan(M_PI/180.0*THETA/2.0) ;
    float right = ASPECT*top ;
    float bottom = -top ;
    float left = -right ;

    dmatrix_t T1 ;
    dmat_alloc(&T1,4,4) ;

    T1 = *dmat_identity(&T1) ;
    T1.m[1][4] = -(right + left)/2.0 ;
    T1.m[2][4] = -(top + bottom)/2.0 ;

    dmatrix_t S1 ;
    dmat_alloc(&S1,4,4) ;

    S1 = *dmat_identity(&S1) ;
    S1.m[1][1] = 2.0/(right - left) ;
    S1.m[2][2] = 2.0/(top - bottom) ;

    /* Build matrices T2, S2, and W2 */

    dmatrix_t T2 ;
    dmatrix_t S2 ;
    dmatrix_t W2 ;

    dmat_alloc(&T2,4,4) ;
    dmat_alloc(&S2,4,4) ;
    dmat_alloc(&W2,4,4) ;

    T2 = *dmat_identity(&T2) ;
    S2 = *dmat_identity(&S2) ;
    W2 = *dmat_identity(&W2) ;

    T2.m[1][4] = 1.0 ;
    T2.m[2][4] = 1.0 ;

    S2.m[1][1] = W/2.0 ;
    S2.m[2][2] = H/2.0 ;

    W2.m[2][2] = -1.0 ;
    W2.m[2][4] = (double)H ;

    dmatrix_t temp = *dmat_mult(&W2,dmat_mult(&S2,dmat_mult(&T2,dmat_mult(&S1,dmat_mult(&T1,dmat_mult(&Mp,&Mv))))));
    //return dmat_mult(&translation,&temp);
    return &temp;
}

dmatrix_t *perspective_projection(dmatrix_t *P) {

    (*P).m[1][1] /= (*P).m[4][1] ;
    (*P).m[2][1] /= (*P).m[4][1] ;
    (*P).m[3][1] /= (*P).m[4][1] ;
    (*P).m[4][1] /= (*P).m[4][1] ;

    return P ;
}

dmatrix_t *camera_init(){
    // Camera matrix
    dmatrix_t C;

    dmatrix_t e ; /* The centre of projection for the camera */

    dmat_alloc(&e,4,1) ;
    //    e.m[1][1] = Ex ;
    //    e.m[2][1] = Ey ;
    //    e.m[3][1] = Ez ;
    //    e.m[4][1] = 1.0 ;
    //loc
    //0.000001
    //    e.m[1][1] = 0.01 ;
    e.m[1][1] = 150 ;
    //    e.m[2][1] = 0.01 ;
    e.m[2][1] = 140 ;
    //    e.m[3][1] = 0.000001 ;
    e.m[3][1] = 140 ;
    e.m[4][1] = 1.0 ;

    dmatrix_t g ; /* Point gazed at by camera */
    dmat_alloc(&g,4,1) ;
    g.m[1][1] = 0;
    g.m[2][1] = 0;
    g.m[3][1] = 0 ;
    g.m[4][1] = 1.0 ;

    //dmatrix_t C ; /* The camera matrix */

    dmat_alloc(&C,4,4) ;
    C = *build_camera_matrix(&e,&g) ;

    printf("Camera Matrix:\n"); write_dmatrix(&C) ;

    dmatrix_t p ;

    dmat_alloc(&p,4,1) ;
    p.m[1][1] = 0.0 ;
    p.m[2][1] = 0.0 ;
    p.m[3][1] = 0.0 ;
    p.m[4][1] = 1.0 ;

    printf("Point (0,0,0) multiplied with camera matrix:\n") ;
    write_dmatrix(dmat_mult(&C,&p)) ;
    printf("Point (0,0,0) after prespective projection:\n") ;
    write_dmatrix(perspective_projection(dmat_mult(&C,&p))) ;

    //Rotation matrix around z-axis
    //loc
    dmatrix_t rotation ;
    float degree = -M_PI/2;
    dmat_alloc(&rotation,4,4);
    dmat_identity(&rotation);
    rotation.m[1][1] = cos(degree);
    rotation.m[1][2] = -sin(degree);
    rotation.m[2][1] = sin(degree);
    rotation.m[2][2] = cos(degree);

    C = *dmat_mult(&rotation, &C);

    std::cout<<"Camera Matrix after Rotation, with "<< degree <<" degree:"<<std::endl;
    write_dmatrix(&C);

    //Translation matrix
    dmatrix_t translation ; //translation matrix
    double scalar_translation = W;//the distance of translation
    dmat_alloc(&translation,4,4);
    dmat_identity(&translation);
    translation.m[1][4] = scalar_translation/2;
    translation.m[2][4] = scalar_translation*1.5;
    translation.m[3][4] = scalar_translation;

    C = *dmat_mult(&translation, &C);

    std::cout<<"Camera Matrix after translation, with "<< scalar_translation<<" pixels:"<<std::endl;
    write_dmatrix(&C);

    //free them all
    delete_dmatrix(&e);
    delete_dmatrix(&g);

    return &C;
}
