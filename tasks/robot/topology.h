#pragma once

#include "point.h"
#include "field.h"

#include <vector>

class Topology {
public:
    using Distance = ssize_t;

    explicit Topology(std::vector<std::vector<bool>> map);

    virtual std::vector<Point> GetNeighbours(const Point& point) const = 0;
    Distance MeasureDistance(const Point& from, const Point& to) const;
    std::vector<Point> FindPath(const Point& from, const Point& to) const;

    inline static const Distance UNREACHABLE = -1;

protected:
    Field map_;

};
