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
    int amount_of_lower = 0;
    int amount_of_upper = 0;
    int amount_of_digit = 0;
    int amount_of_symbol = 0;
    for (int i = 0; i < password.size(); ++i) {
        int char_code = password[i];
        if (char_code < MIN_CHAR_CODE || char_code > MAX_CHAR_CODE) {
            return false;
        }
        if (islower(password[i])) {
            ++amount_of_lower;
        }
        if (isupper(password[i])) {
            ++amount_of_upper
        }
        if (isdigit(password[i])) {
            ++amount_of_digit;
        }
        if (!isdigit(password[i]) && !isalpha(password[i])) {
            ++amount_of_symbol;
        }
    }
    if (amount_of_lower >= 3 || amount_of_upper >= 3 || amount_of_digit >= 3 || amount_of_symbol >= 3) {
        return true;
    } else {
        return false;
    }
}
