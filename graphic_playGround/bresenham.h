//
//  bresenham.h
//  graphic_playGround
//
//  Created by Charles on 2019-02-22.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef bresenham_h
#define bresenham_h

#include "point.h"

#endif /* bresenham_h */

/*
 * Draw a line by Bresenham's algorithm.
 *
 * @author Mu He
 *
 */
void Bresenham( int x1,  int y1,  int x2,  int y2, unsigned char r, unsigned char g, unsigned char b) {

    int dx  = x2 - x1,
    dy  = y2 - y1,
    y   = y1,
    epsilon = 0; // epsilon as error.

    /*
     * As we know, a Bresenham's Algo must work together for 8 octants. Starts from 12 o' clock, I named the first
     * octants as #1, then #2; the 3'o clock's as #3, #4, lastly end with #8.
     *
     * Obviously, Case 2 and Case 1 is the basis of all cases. Case 2 could generate #3, #7, #6 and Case 1 do the rest.
     *
     * Case 2, I learn from class note, and I do the rest all by myself.
     */

    /* First four groups: based on Case 2 */

    if(0 <= dy && dy <= dx){ // 0 < m < 1, case 2
        //std::cout << "case 2" << std::endl;
        for(int x = x1; x <= x2; x+=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dy;
            if ( (epsilon << 1) >= dx )  { //Some little optimization, avoiding division with left-shift.
                y++;  epsilon -= dx;
            }
        }
    }

    if(dy >=0 && dy <= -dx){ // 0 > m > -1, case 7

        // Case 7 is mirror of 2, around y-axis.  So change For Loop's order, and dx, dy into abs.

        //std::cout << "case 7" << std::endl;
        dx = -dx;
        for(int x = x1; x >= x2; x-=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dy;
            if ( (epsilon << 1) >= dx )  {
                y++;  epsilon -= dx;
            }
        }
    }

    else if(dy <= 0 && -dy <= dx){ // -1 < m < 0, case 3

        // 3 is mirror of 2, around x-axis. So y++ => y--, and dx, dy into abs.

        //std::cout << "case 3" << std::endl;
        dy = -dy;
        for(int x = x1; x <= x2; x+=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dy;
            if ( (epsilon << 1) >= dx )  {
                y--;  epsilon -= dx;
            }
        }
    }

    //Another version of case 3 is regard it as case 7's reverse. So exchange the end points.
    //Bresenham(x2,y2, x1, y1);

    else if(dy <= 0 && dx <= dy){ // -1 < m < 0, case 6
        //case 6 is just a reverse of case 2. So exchange the end points.
        Bresenham(x2,y2, x1, y1,r,g,b);
    }


    /* Another four groups: based on Case 1
     *
     * The design idea of Case 1 is, it's a mirror around line y = x.
     *
     * So simply exchange x,y, and all is done.
     * However, just call Bre(y1,x1,y2,x2) won't work for it.
     */

    else if(0 <= dx && dx <= dy){ // m > 1, case 1

        //Case 1 is case 2's sibling: Change every x and y, but don't change Draw(x,y).

        //std::cout << "case 1" << std::endl;

        int x = x1;
        for(int y = y1; y <= y2; y+=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dx;
            if ( (epsilon << 1) >= dy )  {
                x++;  epsilon -= dy;
            }
        }
    }

    else if(dx <= 0 && -dx <= dy){ // m < -1, case 8

        //Case 8 is case 1's mirror around y-axis. Simply change the order of for loop; Abs dx, dy; and x = x1 => x = x2;

        //std::cout << "case 8" << std::endl;

        dx = -dx;
        int x = x2;
        for(int y = y2; y >= y1; y-=1){
            DrawPixel(x,y,r,g,b);
            epsilon += dx;
            if ( (epsilon << 1) >= dy )  {
                x++;  epsilon -= dy;
            }
        }
    }

    else if(dx <= 0 && dy <= dx){ // m < -1, case 5
        //case 5 is just a reverse of case 1. So exchange the end points.
        Bresenham(x2,y2, x1, y1,r,g,b);
    }

    else if(0 <= dx && dy <= -dx){ // m < -1, case 4
        //case 4 is just a reverse of case 8. So exchange the end points.
        Bresenham(x2,y2, x1, y1,r,g,b);
    }
}

/*
 This function is writen because an error in our assignment.
 In assignment#1 the bresenham algo ask us input int, but know is double/float

 @author Mu He
 */
void Line(float x1,  float y1,  float x2,  float y2){
    Bresenham((int)x1,(int)y1,(int)x2,(int)y2,0,0,0);
}

//part of bresenham, in oct 2;
void o2( int x1,  int y1,  int x2,  int y2) {
    int dx  = x2 - x1,
    dy  = y2 - y1,
    y   = y1,
    epsilon = 0; // epsilon as error.

    if(0 <= dy && dy <= dx){ // 0 < m < 1, case 2
        //std::cout << "case 2" << std::endl;
        for(int x = x1; x <= x2; x+=1){
            DrawPixel(x,y,0,0,0);
            epsilon += dy;
            if ( (epsilon << 1) >= dx )  {
                y++;  epsilon -= dx;
            }
        }
    }
}

//part of bresenham, in oct 1;
void o3( int x1,  int y1,  int x2,  int y2) {

    int dx  = x2 - x1,
    dy  = y2 - y1,
    y   = y1,
    epsilon = 0; // epsilon as error.

    dy = -dy;

    if( 0 <= dy <= dx){ // -1 < m < 0, case 3
        std::cout << "case 3" << std::endl;
        for(int x = x1; x <= x2; x+=1){
            DrawPixel(x,y,0,0,0);
            epsilon += dy;
            if ( (epsilon << 1) >= dx )  {
                y--;  epsilon -= dx;
            }
        }
    }
}

void o6( int x1,  int y1,  int x2,  int y2) {
    std::cout<<"o6 is called;"<<std::endl;
    o2(x2,y2,x1,y1);

}

void o7( int x1,  int y1,  int x2,  int y2) {
    std::cout<<"o7 is called;"<<std::endl;
    o3(x2,y2,x1,y1);
}

void o1( int y1,  int x1,  int y2,  int x2) {
    int dx  = x2 - x1,
    dy  = y2 - y1,
    y   = y1,
    epsilon = 0; // epsilon as error.

    if(0 <= dy && dy <= dx){ // 0 < m < 1, case 2
        //std::cout << "case 2" << std::endl;
        for(int x = x1; x <= x2; x+=1){
            DrawPixel(y,x,0,0,0);
            epsilon += dy;
            if ( (epsilon << 1) >= dx )  {
                y++;  epsilon -= dx;
            }
        }
    }
}
