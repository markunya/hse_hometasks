#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t length_of_palindrome = str.size();
    size_t left = 0;
    size_t right =  length_of_palindrome == 0 ? 0 : length_of_palindrome - 1;
    while (left < right) {
        if (str[left] == ' ') {
            ++left;
            continue;
        }
        if (str[right] == ' ') {
            --right;
            continue;
        }
        if (str[left] != str[right]) {
            return false;
        } else {
            ++left;
            --right;
        }
    }
    return true;
}
