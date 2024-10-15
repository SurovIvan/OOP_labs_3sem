#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point {
    public:
        double _x;
        double _y;

        Point();
        Point(double x, double y);
        double distance(const Point& other);
        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
        friend std::istream& operator>>(std::istream& is, Point& p);
        friend std::ostream& operator<<(std::ostream& os, const Point& p);

};

#endif //POINT_H