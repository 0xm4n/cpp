#ifndef RECT_H
#define RECT_H

#include "shape.h"

typedef struct {
    Shape super;
    int width;
    int height;
} Rectangle;

void Rectangle_ctor(Rectangle * const me, int x, int y, int w, int h);

#endif