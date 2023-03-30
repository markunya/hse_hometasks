#pragma once

#include "../filter.h"

class Crop : public Filter {
public:
    Crop(uint32_t width, uint32_t height);
    void Apply(Image &image) override;

    uint32_t Width() const;
    uint32_t Height() const;

private:
    uint32_t width_;
    uint32_t height_;
};