#pragma once

#include "image.h"

class Filter {
public:
    virtual void Apply(Image& image) = 0;
    virtual ~Filter() = default;
};

class MatrixFilter : public Filter {
public:
    virtual const std::vector<std::vector<std::vector<double>>>& GetMatrixVector() const = 0;
    void Apply(Image& image) override;
};