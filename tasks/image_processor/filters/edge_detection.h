#pragma once

#include "../filter.h"

class EdgeDetection : public MatrixFilter {
public:
    explicit EdgeDetection(const double& threshold);
    void Apply(Image& image) override;
    std::vector<std::vector<int>> GetMatrix() const final;

private:
    const double threshold_;
    const std::vector<std::vector<int>> matrix_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
};