#include "../include/point.h"
#include <math.h>

Point::Point(): _x(0), _y(0) {}

Point::Point(double x, double y): _x{x}, _y{y} {}

double Point::distance(const Point& other) {
    double df_x = this->_x - other._x;
    double df_y = this->_y - other._y;
    return std::sqrt(df_x * df_x + df_y * df_y);
}

bool Point::operator==(const Point& other) const {
    return (this->_x == other._x && this->_y == other._y);
}

bool Point::operator!=(const Point& other) const {
    return !(*this == other);
}

std::istream& operator>>(std::istream& is, Point& p) {
    is >> p._x >> p._y;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << " " << p._x << " " <<p._y << std::endl;
    return os;
}
