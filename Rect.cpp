#include "Rect.h"

bool Rect::collide(const Rect &other) const {
    Num _width = pos.x - other.pos.x;
    if (_width >= 0) {
        if (other.width <= _width) {
            return false;
        }
    }
    else if (width <= -_width) {
        return false;
    }

    Num _height = pos.y - other.pos.y;
    if (_height >= 0) {
        if (height < _height) {
            return false;
        }
    }
    else if (other.height <= -_height) {
        return false;
    }

    return true;
}
