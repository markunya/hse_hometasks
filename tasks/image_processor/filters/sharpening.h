#pragma once

#include "../filter.h"

class Sharpening : public MatrixFilter {
private:
    const std::vector<std::vector<std::vector<double>>>& GetMatrixVector() const final;
    std::vector<std::vector<std::vector<double>>> matrix_vector_ = {{{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}},};
};