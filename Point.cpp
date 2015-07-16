//
// Created by user on 3/6/2015.
//

#include "Point.h"

#include <cmath>

Point Point::operator*(Num num) const {
    return Point(x * num, y * num);
}

Point operator*(Num num, const Point &p) {
    return p * num;
}

Point Point::operator+(const Point &point) const {
    return Point(x + point.x, y + point.y);
}

Point Point::operator-(const Point &point) const {
    return Point(x - point.x, y - point.y);
}

Point Point::operator/(Num num) const {
    return Point(x / num, y / num);
}

Point Point::operator-() const {
    return Point(-x, -y);
}

Point Point::operator*(const Point &other) const {
    return Point(x * other.x, y * other.y);
}

Point sqrt(const Point &other) {
    return Point(std::sqrt(other.x), std::sqrt(other.y));
}

Point Point::operator/(const Point &other) const {
    return Point(x / other.x, y / other.y);
}
