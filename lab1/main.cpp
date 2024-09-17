#include <iostream>
#include <string>
#include "src/lab.h"

int main(){
    std::string line;
    std::getline(std::cin, line);
    int16_t count = couting_vowels(line);
    std::cout << count << std::endl;
    return 0;
}