#pragma once

#include "../filter.h"

class GaussianBlur : public MatrixFilter {
public:
    explicit GaussianBlur(const double& sigma);
    void Apply(Image &image) override;
    const std::vector<std::vector<std::vector<double>>>& GetMatrixVector() const final;
private:
    std::vector<std::vector<std::vector<double>>> matrix_vector_;
};
