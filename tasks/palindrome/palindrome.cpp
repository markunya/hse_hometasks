#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    int left = 0;
    int right = str.length() - 1;
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
