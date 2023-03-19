#pragma once

#include "topology.h"

class KnightTopology : public Topology {
public:
    explicit KnightTopology(std::vector<std::vector<bool>> map);

    std::vector<Point> GetNeighbours(const Point& point) const override;
};
