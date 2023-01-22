#include "cctype"
#include "password.h"

const int MIN_SIZE_OF_PASSWORD = 8;
const int MAX_SIZE_OF_PASSWORD = 14;
const int MIN_CHAR_CODE = 33;
const int MAX_CHAR_CODE = 126;

bool ValidatePassword(const std::string& password) {
    if (password.size() < MIN_SIZE_OF_PASSWORD || password.size() > MAX_SIZE_OF_PASSWORD) {
        return false;
    }
    bool has_lower = false;
    bool has_upper = false;
    bool has_digit = false;
    bool has_symbol = false;
    for (int i = 0; i < password.size(); ++i) {
        int char_code = password[i];
        if (char_code < MIN_CHAR_CODE || char_code > MAX_CHAR_CODE) {
            return false;
        }
        if (islower(password[i])) {
            has_lower = true;
        }
        if (isupper(password[i])) {
            has_upper = true;
        }
        if (isdigit(password[i])) {
            has_digit = true;
        }
        if (!isdigit(password[i]) && !isalpha(password[i])) {
            has_symbol = true;
        }
    }
    if (has_lower && has_upper && has_digit && has_symbol) {
        return true;
    } else {
        return false;
    }
}
