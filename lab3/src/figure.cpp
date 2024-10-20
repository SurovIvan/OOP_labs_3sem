#include "../include/figure.h"


Figure::Figure() {
    std::vector<Point> new_points;
    this->_points = new_points;
}

Figure::Figure(const Figure& other) {
    std::vector<Point> points(other.count_point());
    for (size_t i = 0; i < other.count_point(); ++i) {
        points[i] = other._points[i];
    }
    this->_points = points;
}

Figure& Figure::operator=(const Figure& other) {
    if (this == &other) {
        return *this;
    }
    std::vector<Point> points(other.count_point());
    for (size_t i = 0; i < other._points.size(); ++i) {
        points[i] = other._points[i];
    }
    this->_points = points;
    return *this;
}

Figure& Figure::operator=(Figure&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    this->_points = std::move(other._points);
    return *this;
}

bool Figure::operator==(const Figure& other) const {
    if (this->_points.size() != other._points.size()) {
        return false;
    }
    for (size_t i = 0; i < other._points.size(); ++i) {
        if (_points[i] != other._points[i]) {
            return false;
        } 
    }
    return true;
}



