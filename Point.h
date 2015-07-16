//
// Created by user on 3/6/2015.
//

#ifndef SHAPES_POINT_H
#define SHAPES_POINT_H

typedef float Num;

class Point {
public:
    Num x;
    Num y;

    Point(float x = 0, float y = 0) : x(x), y(y) { }

    Point operator+(const Point &point) const;

    Point operator-(const Point &point) const;

    Point operator-() const;

    Point operator*(Num num) const;

    Point operator*(const Point &other) const; //dot product

    Point operator/(Num num) const;

    Point operator/(const Point &other) const;

    friend Point operator*(Num num, const Point &p);

    friend Point sqrt(const Point &other);
};


#endif //SHAPES_POINT_H
