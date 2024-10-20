#ifndef PENTAGON_H
#define PENTAGON_H
#include "figure.h"
#include "cmath"

class Pentagon: public Figure {
    public:
        operator double() override;
        Point calc_geom_center()  const override;
        size_t count_point() const;
        bool is_collinear(const Point& p1, const Point& p2, const Point& p3);
        friend std::istream& operator>>(std::istream& is, Pentagon& p);
        friend std::ostream& operator<<(std::ostream& os, Pentagon& p);
};

#endif //PENTAGON_H