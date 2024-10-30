#pragma once
#include <iostream>
#include <type_traits>
#include <math.h>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
    public:
        
        Point(): _x(0), _y(0) {}

        Point(T x, T y): _x{x}, _y{y} {}

        double distance(const Point<T>& other) {
            T df_x = this->_x - other._x;
            T df_y = this->_y - other._y;
            return std::sqrt(df_x * df_x + df_y * df_y);
        }

        bool operator==(const Point<T>& other) const {
            return (this->_x == other._x && this->_y == other._y);
        }

        bool operator!=(const Point<T>& other) const {
            return !(*this == other);
        }

        
        friend std::istream& operator>>(std::istream& is, Point<T>& p) {
            is >> p._x >> p._y;
            return is;
        }

        
        friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
            os << " " << p._x << " " <<p._y << std::endl;
            return os;
        }
        T get_x() const {return this->_x;};
        T get_y() const {return this->_y;};

    private:
        T _x;
        T _y;
};
