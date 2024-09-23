#include "../include/Twelve.h"

Twelve::Twelve(): _size{0}, _array{nullptr} {}

Twelve::Twelve(const std::string& number) {
    _size = 0;
    _array = new unsigned char[number.size()];
    for (auto &el: number)
        this->_array[this->_size++] = el;
}

Twelve::Twelve(const size_t& size) {
    _size = size;
    _array = new unsigned char[this->_size];
}

Twelve::Twelve(const Twelve& other) {
    _size = other._size;
    _array = new unsigned char[this->_size];
    std::copy(other._array, other._array + other._size, this->_array);
}

Twelve::Twelve(Twelve&& other) noexcept {
    _size = other._size;
    _array = other._array;
    
    other._size = 0;
    other._array = nullptr;
}

Twelve::Twelve(std::initializer_list<unsigned char> &t) {
    _size = 0;
    _array = new unsigned char[t.size()];
    for (auto &el: t) {
        _array[_size++] = el;
    }
}

Twelve& Twelve::operator=(const Twelve& other) {
    if (this == &other){
        return *this;
    }
    delete [] this->_array;
    this->_size = other._size;
    _array = new unsigned char[this->_size];
    std::copy(other._array, other._array + other._size, this->_array);
    return *this;
}

size_t Twelve::size() {
    return this->_size;
}

unsigned char Twelve::operator[](const int16_t& index) {
    return this->_array[index];
}

Twelve Twelve::operator+(const Twelve& other) {
    size_t max_size = std::max(this->_size, other._size);
    Twelve new_numb = Twelve(max_size);
    int8_t cur_symbol;
    int8_t s1 = 0;
    int8_t s2 = 0;
    int8_t ost = 0;
    for (size_t i = 0; i < max_size; ++i) {
        s1, s2 = 0, 0;
        if (this->_size > i) {
            s1 = conversion_to_number(this->_array[i]);
        }
        if (other._size > i) {
            s2 = conversion_to_number(other._array[i]);
        }
        cur_symbol = s1 + s2 + ost;
        ost = cur_symbol / 12;
        new_numb._array[i] = this->alphabet[cur_symbol % 12];
    }
    if (ost != 0) {
        new_numb.reallocate(max_size + 1);
        new_numb._array[max_size] = this->alphabet[ost % 12];
    }
    return new_numb;
}

Twelve Twelve::operator-(const Twelve& other) {
    if (*(this) < other) {
        throw std::range_error("Operator minus: the number to be subtracted is greater");
    } 
    Twelve new_numb = Twelve(this->_size);
    int8_t cur_symbol;
    int8_t s1 = 0;
    int8_t s2 = 0;
    int8_t debt = 0;
    for (size_t i = 0; i < this->_size; i++) {
        s1, s2 = 0, 0;
        s1 = conversion_to_number(this->_array[i]);
        if (i < other._size) {
            s2 = conversion_to_number(other._array[i]);
        }
        cur_symbol = s1 - s2 - debt;
        debt = 0;
        if (cur_symbol < 0) {
            cur_symbol += 12;
            debt = 1;
        }
        new_numb._array[i] = this->alphabet[cur_symbol]; 
    }
    size_t new_size = this->_size - 1;
    while (this->_size > 1 && new_size > 0 && new_numb._array[new_size] == '0') {
        new_size -= 1;
    }

    if ((new_size + 1) < this->_size) {
        new_numb.reallocate(new_size + 1);
    }
    return new_numb;
}

Twelve& Twelve::operator+=(const Twelve& other) {
    Twelve tmp = *(this) + other;
    *this = tmp;
    return *this;
}

Twelve& Twelve::operator-=(const Twelve& other) {
    Twelve tmp = *(this) - other;
    *this = tmp;
    return *this;
}

Twelve& Twelve::operator++() {
    *this += Twelve("1");
    return *this;
}

Twelve& Twelve::operator--() {
    *this -= Twelve("1");
    return *this;
}

Twelve Twelve::operator++(int) {
    Twelve tmp = (*this);
    ++(*this);
    return tmp;
}


Twelve Twelve::operator--(int) {
    Twelve tmp = (*this);
    --(*this);
    return tmp;
}

bool Twelve::operator==(const Twelve& other) const{
    if (this->_size != other._size) {
        return false;
    }
    for (size_t i = 0; i < this->_size; ++i) {
        if (this->_array[i] != other._array[i]) {
            return false;
        }
    }
    return true;
}

bool Twelve::operator!=(const Twelve& other) const{
    return !(*(this) == other);
}

bool Twelve::operator<(const Twelve& other) const{
    if (this->_size < other._size) {
        return true;
    }

    if (this->_size > other._size) {
        return false;
    }

    if (*this == other) {
        return false;
    }

    for (size_t i = this->_size - 1; i >= 0; --i) {
        if (this->_array[i] < other._array[i]) {
            return true;
        }

        if (this->_array[i] > other._array[i]) {
            return false;
        }
    }
}

bool Twelve::operator>(const Twelve& other) const{
    return other < *this;
}

void Twelve::reallocate(size_t new_size) {
    unsigned char* new_array = new unsigned char[new_size];
    size_t min_size = std::min(this->_size, new_size);
    for(size_t i = 0; i < min_size; ++i) {
        new_array[i] = this->_array[i];
    }
    this->_size = new_size;
    delete [] this->_array;
    this->_array = new_array;
}

int8_t Twelve::conversion_to_number(char symbol) {
    switch (symbol)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    case 'A':
        return 10;
    case 'B':
        return 11;
    default:
        return -1;
    }
}

Twelve::~Twelve() noexcept{
    this->_size = 0;
    delete [] this->_array;
    this->_array = nullptr;
}



