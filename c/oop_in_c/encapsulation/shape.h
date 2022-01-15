#ifndef SHAPE_H
#define SHAPE_H

/* Shape's attributes */
typedef struct {
    int x;
    int y;
} Shape;

void Shape_ctor(Shape * const me, int x, int y);
void Shape_moveBy(Shape * const me, int x, int y);
int Shape_getX(Shape const * const me);
int Shape_getY(Shape const * const me);

#endif