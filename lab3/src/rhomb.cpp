#include "../include/Rhomb.h"
#define eps 1e-12

Rhomb::operator double() {
    double d_1 = side_calculation(_points[0]._x, _points[2]._x, _points[0]._y, _points[2]._y);
    double d_2 = side_calculation(_points[1]._x, _points[3]._x, _points[1]._y, _points[3]._y);
    return 0.5 * d_1 * d_2;
}

Point Rhomb::calc_geom_center() const {
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

size_t Rhomb::count_point() const{
    return 4;
}

double Rhomb::side_calculation(double x1, double x2, double y1, double y2) {
    return std::sqrt(std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2));
}

std::istream& operator>>(std::istream& is, Rhomb& r) {
    std::cout << "Введите 4 координаты по порядку!" << std::endl;
    size_t size = r.count_point();
    double cur_x;
    double cur_y;
    for (size_t i = 0; i < size; ++i) {
        is >> cur_x >> cur_y;
        Point pnt = Point(cur_x, cur_y);
        r._points.push_back(Point(cur_x, cur_y));
    }
    double s_1 = r.side_calculation(r._points[0]._x, r._points[1]._x, r._points[0]._y, r._points[1]._y);
    double s_2 = r.side_calculation(r._points[1]._x, r._points[2]._x, r._points[1]._y, r._points[2]._y);
    double s_3 = r.side_calculation(r._points[2]._x, r._points[3]._x, r._points[2]._y, r._points[3]._y);
    double s_4 = r.side_calculation(r._points[3]._x, r._points[0]._x, r._points[3]._y, r._points[0]._y);

    double diag_x = (r._points[0]._x - r._points[2]._x) * (r._points[1]._x - r._points[3]._x);
    double diag_y = (r._points[0]._y - r._points[2]._y) * (r._points[1]._y - r._points[3]._y);

    if (!((abs(s_1 - s_2) < eps && abs(s_1 - s_3) < eps, abs(s_2 - s_4) < eps) && (diag_x + diag_y == 0))) {
        std::cerr << "It's not a rhomb, your coordinates are wrong" << std::endl;
        exit(1);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Rhomb& r) {
    size_t size = r.count_point();
    for (size_t i = 0; i < size; ++i) {
        os << "The " << i + 1 << " coordinate " << "x: " << r._points[i]._x << " y: "  << r._points[i] << std::endl;
    }
    return os;
}
