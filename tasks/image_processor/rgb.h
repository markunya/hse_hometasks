#pragma once

class RGB {
public:
    double red;
    double green;
    double blue;
    RGB();
    explicit RGB(double color);
    RGB(double red, double green, double blue);

    void Normalize();
    void Inverse();

    RGB operator+(const RGB& other) const;
    RGB operator-(const RGB& other) const;
    RGB operator+=(const RGB& other);
    friend RGB operator*(const double lambda, const RGB& rgb);
    friend RGB operator*(const RGB& rgb, const double lambda);
};

RGB operator*(const double lambda, const RGB& rgb);
RGB operator*(const RGB& rgb, const double lambda);
