#include "shape.h"

static int Shape_area_(Shape const * const self);

void Shape_ctor(Shape * const self, int x, int y) {
    static struct ShapeVtbl const vtbl = {
        &Shape_area_
    };
    self->vptr = &vtbl;
    self->x = x;
    self->y = y;
}

static int Shape_area_(Shape const * const self) {
    assert(0);
    return 0;
}