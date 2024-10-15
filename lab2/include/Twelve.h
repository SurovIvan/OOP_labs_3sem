#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

class Twelve
{
    private:
        void reallocate(const size_t new_size);
        int8_t conversion_to_number(char symbol);

    public:
        Twelve();
        Twelve(const std::string& number);
        Twelve(const size_t& size);
        Twelve(const Twelve& other);
        Twelve(Twelve&& other) noexcept;
        Twelve(std::initializer_list<unsigned char> &t);


        Twelve& operator=(const Twelve& other);
        Twelve operator+(const Twelve& other);
        Twelve operator-(const Twelve& other);
        Twelve& operator+=(const Twelve& other);
        Twelve& operator-=(const Twelve& other);
        Twelve& operator++();
        Twelve& operator--();
        Twelve operator++(int);
        Twelve operator--(int);
        bool operator==(const Twelve& other) const;
        bool operator!=(const Twelve& other) const;
        bool operator<(const Twelve& other) const;
        bool operator>(const Twelve& other) const;
        size_t size();
        unsigned char operator[](const int16_t& index) const;
        friend std::ostream& operator<<(std::ostream& os, const Twelve& num);

        ~Twelve() noexcept;
    
    public:
        std::string alphabet = "0123456789AB";

    private:
        size_t _size;
        unsigned char *_array;

};