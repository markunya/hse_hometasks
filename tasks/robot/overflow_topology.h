#pragma once

#include "topology.h"

class OverflowTopology : public Topology {
public:
    explicit OverflowTopology(std::vector<std::vector<bool>> map);

    std::vector<Point> GetNeighbours(const Point& point) const override;
};
