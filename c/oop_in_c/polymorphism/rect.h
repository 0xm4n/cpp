#ifndef RECT_H
#define RECT_H
#include "shape.h"

typedef struct {
    Shape super;
    int width;
    int height;
} Rectangle;

void Rect_ctor(Rectangle * const self, 
                int x, int y, 
                int width, int height);

#endif