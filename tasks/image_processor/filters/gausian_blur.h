#pragma once

#include "../filter.h"

class GaussianBlur : public Filter {
    void Apply(Image &image) override;
};
