#include "rect.h"

void Rectangle_ctor(Rectangle * const me, int x, int y, int w, int h) {
    Shape_ctor(&me->super, x, y);
    me->width = w;
    me->height = h;
}