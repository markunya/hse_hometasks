#include <algorithm>
#include "rgb.h"

RGB::RGB() : red(0.0), green(0.0), blue(0.0) {
}

RGB::RGB(double color) : red(color), green(color), blue(color) {
}

RGB::RGB(double red, double green, double blue) : red(red), green(green), blue(blue) {
}

void RGB::Normalize() {
    red = std::min(1.0, std::max(0.0, red));
    green = std::min(1.0, std::max(0.0, green));
    blue = std::min(1.0, std::max(0.0, blue));
}

void RGB::Inverse() {
    red = 1.0 - red;
    green = 1.0 - green;
    blue = 1.0 - blue;
}

RGB RGB::operator+(const RGB& other) const {
    return RGB(red + other.red, green + other.green, blue + other.blue);
}

RGB RGB::operator-(const RGB& other) const {
    return RGB(red - other.red, green - other.green, blue - other.blue);
}

RGB RGB::operator+=(const RGB& other) {
    red += other.red;
    green += other.green;
    blue += other.blue;
    return *this;
}

RGB operator*(const double lambda, const RGB& rgb) {
    return RGB(lambda * rgb.red, lambda * rgb.green, lambda * rgb.blue);
}

RGB operator*(const RGB& rgb, const double lambda) {
    return RGB(lambda * rgb.red, lambda * rgb.green, lambda * rgb.blue);
}
bool RGB::operator==(const RGB& other) const {
    const double normal_deviation = 0.01;
    return std::abs(red - other.red) < normal_deviation && std::abs(green - other.green)  <  normal_deviation &&
           std::abs(blue - other.blue) < normal_deviation;
}
