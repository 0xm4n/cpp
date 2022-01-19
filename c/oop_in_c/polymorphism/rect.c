#include "rect.h"

static int Rectangle_area_(Shape const * const self);

void Rect_ctor(Rectangle * const self, int x, int y, int width, int height) {
    static struct ShapeVtbl const vtbl = {
        &Rectangle_area_
    };
    Shape_ctor(&(self->super), x, y);
    self->super.vptr = &vtbl;
    self->width = width;
    self->height = height;
}

static int Rectangle_area_ (Shape const * const self) {
    Rectangle const * const self_ = (Rectangle const *)self;
    return (int)self_->width * self_->height;
}