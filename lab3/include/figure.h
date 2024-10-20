#ifndef FIGURE_H
#define FIGURE_H
#include "point.h"
#include <vector>
#include <iostream>

class Figure {
    public:
        Figure();
        Figure(const Figure& other);
        virtual operator double() = 0;
        virtual Point calc_geom_center() const = 0;
        virtual size_t count_point() const = 0;
        Figure& operator=(Figure&& other) noexcept;
        Figure& operator=(const Figure& other);
        bool operator==(const Figure& other) const;
        virtual ~Figure() = default;

    
    protected:
        std::vector<Point> _points;
};

#endif //FIGURE_H