#pragma once

#include "../filter.h"

class Sharpening : public MatrixFilter {
private:
    const std::vector<std::vector<std::vector<double>>>& GetMatrixVector() const final;
    const double cm_ = 5;
    std::vector<std::vector<std::vector<double>>> matrix_vector_ = {{{0, -1, 0}, {-1, cm_, -1}, {0, -1, 0}}};
};