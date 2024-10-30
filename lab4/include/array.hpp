#include "../include/figure.hpp"

template<typename T>
class Array {
    public:
        Array(): _figures(nullptr), _size(0), _capacity(0) {}

        Array(size_t capacity): _size(capacity), _capacity(capacity) {
            _figures = std::shared_ptr<T[]>(new T[capacity]);
        }

        Array(const Array<T>& other){
            _size = other._size;
            _capacity = other._capacity;
            _figures = std::shared_ptr<T[]>(new T[_capacity]);
            for(size_t i = 0; i < _size; ++i) {
                _figures[i] = other._figures[i];
            }
        }

        Array<T>& operator=(const Array<T>& other) {
            if (this == &other) {
                return *this;
            }
            _size = other._size;
            _capacity = other._capacity;
            _figures = std::shared_ptr<T[]>(new T[_capacity]);
            for(size_t i = 0; i < _size; ++i) {
                _figures[i] = other._figures[i];
            }
            return *this;
        }

        Array<T>& operator=(Array<T>&& other) noexcept {
            if (this != &other) {
                _size = other._size;
                _capacity = other._capacity;
                _figures = std::move(other._figures);
                other._size = 0;
                other._capacity = 0;
                other._figures = nullptr;
            }
            return *this;
        }
        void push_back(const T& value) {
            if (_size == _capacity) {
                _capacity = _capacity == 0 ? 1 : _capacity * 2;
            
                std::shared_ptr<T[]> new_figures (new T[_capacity]);
                for(size_t i = 0; i < _size; ++i) {
                    new_figures[i] = std::move(this->_figures[i]);
                }
                _figures = std::move(new_figures);
            }
            _figures[_size++] = value;
        }

        void erase(size_t ind) {
            if (ind < _size) {
                for (size_t i = ind; i < _size - 1; ++i) {
                    _figures[i] = std::move(_figures[i+1]);
                }
                --_size;
            }
        }

        T& operator[](size_t ind) {
            return _figures[ind];
        }

        double total_area() {
            double area = 0;
            for (size_t i = 0; i < _size - 1; ++i) {
                    area += double(*_figures[i]);
            }
            return area;
        }

        size_t get_size() const {return _size;}
        size_t get_capacity() const {return _capacity;}

    private:
        size_t _size;
        size_t _capacity;
        std::shared_ptr<T[]> _figures;
};