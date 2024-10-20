#include "../include/Pentagon.h"

Pentagon::operator double() {
    double square = 0.0;
    size_t size = count_point();
    for (size_t i = 0; i < size - 1; ++i) {
        square += _points[i]._x * _points[i + 1]._y;
        square -= _points[i]._y * _points[i + 1]._x;
    }
    return 0.5 * square;
}

size_t Pentagon::count_point() const{
    return 5;
}

Point Pentagon::calc_geom_center() const{
    double y_c = 0.0;
    double x_c = 0.0;
    size_t size = count_point();
    for (size_t i = 0; i < size; ++i) {
        x_c += _points[i]._x;
        y_c += _points[i]._y;
    }
    Point point_c = Point(x_c / size, y_c / size);
    return point_c;
}

bool Pentagon::is_collinear(const Point& p1, const Point& p2, const Point& p3) {
    return (p1._x * (p2._y - p3._y) + p2._x * (p3._y - p1._y) + p3._x * (p1._y - p2._y) == 0);
}

std::istream& operator>>(std::istream& is, Pentagon& t) {
    std::cout << "Введите 5 координат по порядку!" << std::endl;
    size_t size = t.count_point();
    double cur_x;
    double cur_y;
    for (size_t i = 0; i < size; ++i) {
        is >> cur_x >> cur_y;
        Point pnt = Point(cur_x, cur_y);
        t._points.push_back(Point(cur_x, cur_y));
    }

    for (size_t i = 0; i < size; ++i) {
        if (t.is_collinear(t._points[i % size], t._points[(i + 1) % size], t._points[(i + 2) % size])) {
            std::cerr << "It's not a pentagon, your coordinates are wrong" << std::endl;
            exit(1);
        }
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, Pentagon& p) {
    size_t size = p.count_point();
    for (size_t i = 0; i < size; ++i) {
        os << "The " << i + 1 << " coordinate " << "x: " << p._points[i]._x << " y: "  << p._points[i]._y << std::endl;
    }
    return os;
}