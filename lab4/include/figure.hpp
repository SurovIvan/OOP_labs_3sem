#pragma once
#include "point.hpp"
#include <vector>
#include <iostream>
#include <memory>

template<Scalar T>
class Figure {
    public:
        Figure() {
            _points = std::vector<std::unique_ptr<Point<T>>>();
        }

        Figure(const Figure<T>& other) {
            for (size_t i = 0; i < other.count_point(); ++i) {
                _points.push_back(std::make_unique<Point<T>>(*other._points[i]));
            }
        }

        Figure(const std::initializer_list<Point<T>> &lst) {
            _points.reserve(lst.size());
            for (const auto &t : lst) {
                _points.push_back(std::make_unique<Point<T>>(t));
            }
        }

        Figure<T>& operator=(const Figure<T>& other) {
            if (this == &other) {
                return *this;
            }
            this->_points.clear();
            for (size_t i = 0; i < other._points.size(); ++i) {
                _points.push_back(std::make_unique<Point<T>>(*other._points[i]));
            }
            return *this;
        }

        Figure<T>& operator=(Figure<T>&& other) noexcept {
            if (this == &other) {
                return *this;
            }
            this->_points = std::move(other._points);
            other._points.clear();
            return *this;
        }

        bool operator==(const Figure<T>& other) const {
            if (this->_points.size() != other._points.size()) {
                return false;
            }
            for (size_t i = 0; i < other._points.size(); ++i) {
                if (*_points[i] != *other._points[i]) {
                    return false;
                } 
            }
            return true;
        }

        virtual operator double() = 0;
        virtual Point<T> calc_geom_center() const = 0;
        virtual size_t count_point() const = 0;
    
    protected:
        std::vector<std::unique_ptr<Point<T>>> _points;
};
