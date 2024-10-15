#ifndef RHOMB_H
#define RHOMB_H
#include "figure.h"
#include "cmath"

class Rhomb: public Figure {
    public:
        virtual operator double() override;
        virtual Point calc_geom_center() const override;
        virtual size_t count_point() const;
        double side_calculation(double x1, double x2, double y1, double y2);
        friend std::istream& operator>>(std::istream& is, Rhomb& r);
        friend std::ostream& operator<<(std::ostream& os, const Rhomb& r);
};

#endif //RHOMB_H