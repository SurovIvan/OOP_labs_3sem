#include "lab.h"


bool IsVowel(char letter) {
    if (letter == 'e' || letter == 'y' || letter == 'u' || letter == 'i' || letter == 'o' || letter == 'a') {
        return true;
    }
    return false;
}

int16_t couting_vowels(std::string line) {
    int16_t count = 0;
    for (char letter : line) {
        if (IsVowel(std::tolower(letter))) {
            count++;
        }
    }
    return count;
}