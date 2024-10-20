#ifndef TRAPEZOID_H
#define TRAPEZOID_H
#include "figure.h"
#include "cmath"

class Trapezoid: public Figure {
    public:
        operator double() override;
        Point calc_geom_center() const override;
        size_t count_point() const;
        bool is_trapezoid(); 
        double calculate_slope(const Point& p1, const Point& p2);
        friend std::istream& operator>>(std::istream& is, Trapezoid& t);
        friend std::ostream& operator<<(std::ostream& os, Trapezoid& t);
};

#endif //TRAPEZOID_H