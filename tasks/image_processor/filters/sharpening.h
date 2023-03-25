#pragma once

#include "../filter.h"

class Sharpening : public MatrixFilter {
private:
    std::vector<std::vector<int>> GetMatrix() const final;
    const std::vector<std::vector<int>> matrix_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};