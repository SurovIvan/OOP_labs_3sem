#pragma once
#include "figure.hpp"
#include "cmath"
#define eps 1e-12

template<Scalar T>
class Rhomb: public Figure<T> {
    public:

        virtual operator double() override{
            double d_1 = side_calculation(this->_points[0]->get_x(), this->_points[2]->get_x(), this->_points[0]->get_y(), this->_points[2]->get_y());
            double d_2 = side_calculation(this->_points[1]->get_x(), this->_points[3]->get_x(), this->_points[1]->get_y(), this->_points[3]->get_y());
            return 0.5 * d_1 * d_2;
        }

        virtual Point<T> calc_geom_center() const override {
            double y_c = 0.0;
            double x_c = 0.0;
            size_t size = count_point();
            for (size_t i = 0; i < size; ++i) {
                x_c += this->_points[i]->get_x();
                y_c += this->_points[i]->get_y();
            }
            double x = x_c / size;
            double y = y_c / size;
            return Point<T>(x, y);
        }

        T side_calculation(T x1, T x2, T y1, T y2) {
            return std::sqrt(std::pow((x1 - x2), 2) + std::pow((y1 - y2), 2));
        }

        friend std::istream& operator>>(std::istream& is, Rhomb<T>& r) {
            std::cout << "Введите 4 координаты по порядку!" << std::endl;
            size_t size = r.count_point();
            T cur_x;
            T cur_y;
            for (size_t i = 0; i < size; ++i) {
                is >> cur_x >> cur_y;
                r._points.push_back(std::make_unique<Point<T>>(cur_x, cur_y));
            }
            double s_1 = r.side_calculation(r._points[0]->get_x(), r._points[1]->get_x(),
                                            r._points[0]->get_y(), r._points[1]->get_y());
            double s_2 = r.side_calculation(r._points[1]->get_x(), r._points[2]->get_x(),
                                            r._points[1]->get_y(), r._points[2]->get_y());
            double s_3 = r.side_calculation(r._points[2]->get_x(), r._points[3]->get_x(),
                                            r._points[2]->get_y(), r._points[3]->get_y());
            double s_4 = r.side_calculation(r._points[3]->get_x(), r._points[0]->get_x(),
                                            r._points[3]->get_y(), r._points[0]->get_y());

            
            double diag_x = (r._points[0]->get_x() - r._points[2]->get_x()) *
                            (r._points[1]->get_x() - r._points[3]->get_x());
            double diag_y = (r._points[0]->get_y() - r._points[2]->get_y()) *
                            (r._points[1]->get_y() - r._points[3]->get_y());


            if (!((abs(s_1 - s_2) < eps && abs(s_1 - s_3) < eps, abs(s_2 - s_4) < eps) && (diag_x + diag_y == 0))) {
                std::cerr << "It's not a rhomb, your coordinates are wrong" << std::endl;
                exit(1);
            }
            return is;
        }

        friend std::ostream& operator<<(std::ostream& os, const Rhomb<T>& r) {
            size_t size = r.count_point();
            for (size_t i = 0; i < size; ++i) {
                os << "The " << i + 1 << " coordinate " << "x: " << r._points[i]->get_x() << " y: "  << r._points[i]->get_y() << std::endl;
            }
            return os;
        }

        virtual size_t count_point() const override { return 4; }
};
