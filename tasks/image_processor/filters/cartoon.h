#pragma once

#include "../filter.h"

class Cartoon : public Filter {
public:
    void Apply(Image &image) override;
};
