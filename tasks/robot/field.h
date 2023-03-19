#pragma once

#include <vector>
#include "point.h"

class Field {
public:
    explicit Field(std::vector<std::vector<bool>> field);

    size_t Height() const;
    size_t Width() const;

    bool operator[](const Point& point) const;

private:
    std::vector<std::vector<bool>> field_;
};