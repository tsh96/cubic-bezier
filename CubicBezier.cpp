//
// Created by user on 15/6/2015.
//

#include "CubicBezier.h"
#include <cmath>

CubicBezier::CubicBezier(const Point &p0, const Point &p1, const Point &p2, const Point &p3) : p0(p0), p1(p1),
                                                                                               p2(p2), p3(p3) {
    getTurningPoint();
}

Rect CubicBezier::getBound(const CubicBezier::Range &range) const {
    Num minX = getX(range.t0);
    Num maxX = minX;

    minMax(minX, maxX, getX(range.t1));

    if (inRange(verticalTurningPoint_t0, range))
        minMax(minX, maxX, getX(verticalTurningPoint_t0));


    if (inRange(verticalTurningPoint_t1, range))
        minMax(minX, maxX, getX(verticalTurningPoint_t1));


    Num minY = getY(range.t0);
    Num maxY = minY;

    minMax(minY, maxY, getY(range.t1));

    if (inRange(horizontalTurningPoint_t0, range))
        minMax(minY, maxY, getY(horizontalTurningPoint_t0));


    if (inRange(horizontalTurningPoint_t1, range))
        minMax(minY, maxY, getY(horizontalTurningPoint_t1));

    return Rect(minX, maxY, maxX - minX, maxY - minY);
}

CubicBezier CubicBezier::getCubicBezier(const CubicBezier::Range &range) const {
    const Num t0 = range.t0;
    Point p01 = (1 - t0) * p0 + t0 * p1;
    Point p12 = (1 - t0) * p1 + t0 * p2;
    Point p23 = (1 - t0) * p2 + t0 * p3;

    Point p012 = (1 - t0) * p01 + t0 * p12;
    Point p123 = (1 - t0) * p12 + t0 * p23;

    Point p0123 = (1 - t0) * p012 + t0 * p123;

    const Num t1 = (range.t1 - range.t0) / (1 - range.t0);
    Point p_0 = (1 - t1) * p0123 + t1 * p123;
    Point p_1 = (1 - t1) * p123 + t1 * p23;
    Point p_2 = (1 - t1) * p23 + t1 * p3;

    Point p_01 = (1 - t1) * p_0 + t1 * p_1;
    Point p_12 = (1 - t1) * p_1 + t1 * p_2;

    Point p_012 = (1 - t1) * p_01 + t1 * p_12;

    return (CubicBezier{p0123, p_0, p_01, p_012});
}

CircularList<Point> CubicBezier::intersect(const CubicBezier &other) const {

    CircularList<CubicBezier::Range> ranges1;
    CircularList<CubicBezier::Range> ranges2;
    CircularList<Point> points;

    ranges1.append(CubicBezier::Range{0, 0.5});
    ranges1.append(CubicBezier::Range{0.5, 1});

    ranges2.append(CubicBezier::Range{0, 0.5});
    ranges2.append(CubicBezier::Range{0.5, 1});


    while (ranges1.length() || ranges2.length()) {
        cycle(*this, other, ranges1, ranges2, points);
        cycle(other, *this, ranges2, ranges1, points);

    }

    return points;
}

// private
inline void CubicBezier::getTurningPoint() {
    Num ax = -p0.x + 3 * p1.x - 3 * p2.x + p3.x;
    Num bx = 2 * (p0.x - 2 * p1.x + p2.x);
    Num cx = p1.x - p0.x;

    Num ay = -p0.y + 3 * p1.y - 3 * p2.y + p3.y;
    Num by = 2 * (p0.y - 2 * p1.y + p2.y);
    Num cy = p1.y - p0.y;

    if (ax == 0) {
        verticalTurningPoint_t0 = -cx / bx;
    } else {
        Num sqrt_discriminant = std::sqrt(bx * bx - 4 * ax * cx);

        verticalTurningPoint_t0 = (-bx + sqrt_discriminant) / (2 * ax);

        verticalTurningPoint_t1 = (-bx - sqrt_discriminant) / (2 * ax);
    }


    if (ay == 0) {
        horizontalTurningPoint_t0 = -cy / by;
    } else {
        Num sqrt_discriminant = std::sqrt(by * by - 4 * ay * cy);

        horizontalTurningPoint_t0 = (-by + sqrt_discriminant) / (2 * ay);

        horizontalTurningPoint_t1 = (-by - sqrt_discriminant) / (2 * ay);
    }
}

inline Num CubicBezier::getX(const Num &t) const {
    return p0.x * (1 - t) * (1 - t) * (1 - t)
           + p1.x * 3 * (1 - t) * (1 - t) * t
           + p2.x * 3 * (1 - t) * t * t
           + p3.x * t * t * t;
}

inline Num CubicBezier::getY(const Num &t) const {
    return p0.y * (1 - t) * (1 - t) * (1 - t)
           + p1.y * 3 * (1 - t) * (1 - t) * t
           + p2.y * 3 * (1 - t) * t * t
           + p3.y * t * t * t;
}

inline bool CubicBezier::inRange(const Num &t, const CubicBezier::Range &range) const {
    if (t < range.t0) return false;
    return t <= range.t1;
}

inline void CubicBezier::minMax(Num &min, Num &max, const Num &value) const {
    if (min > value) min = value;
    if (max < value) max = value;
}

void CubicBezier::cycle(const CubicBezier &cb1, const CubicBezier &cb2, CircularList<Range> &ranges1,
                        CircularList<Range> &ranges2, CircularList<Point> &points) const {

    for (int i = 0, length = ranges1.length(); i < length; ++i) {
        Range range = ranges1.next();
        Rect bound = cb1.getBound(range);
        ranges1.remove();

        if (bound.width <= accuracyWH || bound.height <= accuracyWH) {
            bool hasSimilar = false;

            for (int j = 0, length1 = points.length(); j < length1; ++j) {
                Point point = points.next();
                if (((bound.pos.x - point.x) * (bound.pos.x - point.x) < accuracyP) &&
                    ((bound.pos.y - point.y) * (bound.pos.y - point.y) < accuracyP)) {
                    hasSimilar = true;
                    break;
                }
            }
            if (!hasSimilar) {
                points.append(bound.pos);
            }
            continue;
        }

        bool collide = false;

        CircularList<Range>::Node *curr = ranges1.current;
        for (int k = 0, length3 = ranges1.length(); k < length3; ++k) {
            Range range2 = ranges1.next();
            if (bound.collide(cb1.getBound(range2))) {
                collide = true;
                break;
            }
        }
        ranges1.current = curr;

        for (int l = 0, length4 = ranges2.length(); l < length4; ++l) {
            Range range2 = ranges2.next();
            if (bound.collide(cb2.getBound(range2))) {
                collide = true;
                break;
            }
        }
        if (!collide) continue;

        Range range0;
        Range range1;
        range.splitHalf(range0, range1);

        ranges1.append(range0);
        ranges1.append(range1);
    }
}

//Range
CubicBezier::Range::Range(Num t0, Num t1) : t0(t0), t1(t1) { }

inline void CubicBezier::Range::splitHalf(CubicBezier::Range &range0, CubicBezier::Range &range1) const {
    range0 = {t0, (t0 + t1) / 2};
    range1 = {(t0 + t1) / 2, t1};
}


