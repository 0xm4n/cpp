#ifndef MY_SHAPE_H
#define MY_SHAPE_H

struct ShapeVtbl;

typedef struct {
    struct ShapeVtbl const *vptr;
    int x;
    int y;
} Shape;

struct ShapeVtbl {
    int (*area)(Shape const * const self);
};

void Shape_ctor(Shape * const self, int x, int y);

static inline int Shape_area(Shape const * const self) {
    return (*self->vptr->area)(self);
}

#endif