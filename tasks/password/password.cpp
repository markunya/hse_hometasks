#include "cctype"
#include "password.h"

bool ValidatePassword(const std::string& password) {
    if (password.size() < 8 || password.size() > 14) {
        return false;
    }
    bool has_lower = false;
    bool has_upper = false;
    bool has_digit = false;
    bool has_symbol = false;
    for (int i = 0; i < password.size(); ++i) {
        int char_code = password[i];
        if (char_code < 33 || char_code > 126) {
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
        if (!isdigit(password[i] && !isalpha(password[i]))) {
            has_symbol = true;
        }
    }
    if (has_lower && has_upper && has_digit && has_symbol) {
        return true;
    } else {
        return false;
    }
}
