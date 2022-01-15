#include "shape.h"

void Shape_ctor(Shape * const me, int x, int y) {
    me->x = x;
    me->y = y;
}

void Shape_moveBy(Shape * const me, int x, int y) {
    me->x += x;
    me->y += y;
}

int Shape_getX(Shape const * const me) {
    return me->x;
}

int Shape_getY(Shape const * const me) {
    return me->y;
}