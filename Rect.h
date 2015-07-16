//
// Created by user on 3/6/2015.
//

#ifndef SHAPES_RECT_H
#define SHAPES_RECT_H


#include "Point.h"

class Rect {
public:
    Point pos;
    Num width;
    Num height;


    Rect(const Point &pos, Num width, Num Height) : pos(pos), width(width), height(Height) { }

    Rect(Num left, Num right, Num width, Num Height) : pos({left, right}), width(width), height(Height) { }

    Rect() { }

    bool collide(const Rect &other) const;
};


#endif //SHAPES_RECT_H
