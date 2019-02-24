//
//  point.h
//  graphic_playGround
//
//  Created by Charles on 2019-02-22.
//  Copyright © 2019 Mu He. All rights reserved.
//

#ifndef point_h
#define point_h


#endif /* point_h */

//draw a pixel on screen
void DrawPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
    if (x >= windowW || y >= windowH)
        return;
    unsigned int index = 3 * (y * windowW + x);
    frame[index] = r;
    frame[index + 1] = g;
    frame[index + 2] = b;
}
