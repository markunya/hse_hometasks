#pragma once

#include <cstddef>
#include <tuple>
#include <unordered_map>

const size_t P1 = 16769023;
const size_t P2 = 16127;
const size_t P3 = 3967;

struct Point {
    size_t x = 0;
    size_t y = 0;

    bool operator==(const Point& other) const {
        return std::tie(this->x, this->y) == std::tie(other.x, other.y);
    }
};

namespace std {
template <>
struct hash<Point> {
    inline size_t operator()(const Point& point) const {
        return P1 * point.x * point.y + P2 * point.x + P3 * point.y;
    }
};
}
