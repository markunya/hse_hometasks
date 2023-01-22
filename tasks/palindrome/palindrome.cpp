#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    uint64_t left = 0;
    uint64_t right = str.size() - 1;
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
