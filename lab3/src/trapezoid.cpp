#include "../include/Trapezoid.h"

Trapezoid::operator double() {
    double square = 0.0;
    size_t size = count_point();
    for (size_t i = 0; i < size - 1; ++i) {
        square += _points[i]._x * _points[i + 1]._y;
        square -= _points[i]._y * _points[i + 1]._x;
    }
    return 0.5 * square;
}

size_t Trapezoid::count_point() const{
    return 4;
}

bool Trapezoid::is_trapezoid() {
    double slope_ab = calculate_slope(_points[0], _points[1]);
    double slope_cd = calculate_slope(_points[2], _points[3]);
    
    double slope_bc = calculate_slope(_points[1], _points[2]);
    double slope_da = calculate_slope(_points[3], _points[0]);

    // Допустимая погрешность
    const double epsilon = 1e-6;
    
    // Проверка на параллельность с учетом погрешности
    if (std::abs(slope_ab - slope_cd) < epsilon || std::abs(slope_bc - slope_da) < epsilon) {
        return true; 
    }
    return false;
}

double Trapezoid::calculate_slope(const Point& p1, const Point& p2) {
    return (p2._y - p1._y) / (p2._x - p1._x); //угол наклона
}

Point Trapezoid::calc_geom_center() const{
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

std::istream& operator>>(std::istream& is, Trapezoid& t) {
    std::cout << "Введите 4 координаты по порядку!" << std::endl;
    size_t size = t.count_point();
    double cur_x;
    double cur_y;
    for (size_t i = 0; i < size; ++i) {
        is >> cur_x >> cur_y;
        Point pnt = Point(cur_x, cur_y);
        t._points.push_back(Point(cur_x, cur_y));
    }
    if (!(t.is_trapezoid())) {
        std::cerr << "It's not a trapezoid, your coordinates are wrong" << std::endl;
        exit(1);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, Trapezoid& t) {
    size_t size = t.count_point();
    for (size_t i = 0; i < size; ++i) {
        os << "The " << i + 1 << " coordinate " << "x: " << t._points[i]._x << " y: "  << t._points[i]._y << std::endl;
    }
    return os;
}