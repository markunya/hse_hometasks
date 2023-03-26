#pragma once

#include "../filter.h"

class EdgeDetection : public MatrixFilter {
public:
    explicit EdgeDetection(const double& threshold);
    void Apply(Image& image) override;
    const std::vector<std::vector<std::vector<double>>>& GetMatrixVector() const final;

private:
    const double threshold_;
    const std::vector<std::vector<std::vector<double>>> matrix_vector_ = {{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}};
};