//
// Created by user on 15/6/2015.
//

#ifndef CUBIC_CUBICBEZIER_H
#define CUBIC_CUBICBEZIER_H

#include "Rect.h"
#include "CircularList.h"


class CubicBezier {
public:

//private:
    Point p0;
    Point p1;
    Point p2;
    Point p3;

    Num horizontalTurningPoint_t0 = -1;
    Num horizontalTurningPoint_t1 = -1;

    Num verticalTurningPoint_t0 = -1;
    Num verticalTurningPoint_t1 = -1;

    Num accuracyWH = 1e-3;
    Num accuracyP = accuracyWH * 2;
//end private

    class Range {
    public:
        Num t0;
        Num t1;

        Range(Num t0 = 0, Num t1 = 0);

        void splitHalf(Range &range0, Range &range1) const;
    };

    CubicBezier(const Point &p0 = 0, const Point &p1 = 0, const Point &p2 = 0, const Point &p3 = 0);

    Rect getBound(const Range &range = {0, 1}) const;

    CubicBezier getCubicBezier(const Range &range = {0, 1}) const;

    CircularList<Point> intersect(const CubicBezier &other) const;

//     private: /* inline method */
    void getTurningPoint();

    bool inRange(const Num &t, const Range &range = {0, 1}) const;

    void minMax(Num &min, Num &max, const Num &value) const;

    Num getX(const Num &t) const;

    Num getY(const Num &t) const;

    void cycle(const CubicBezier &cb1, const CubicBezier &cb2, CircularList<Range> &ranges1,
               CircularList<Range> &ranges2,
               CircularList<Point> &points) const;


};


#endif //CUBIC_CUBICBEZIER_H
