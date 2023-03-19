#pragma once

#include "topology.h"

class CheckersTopology : public Topology {
public:
    explicit CheckersTopology(std::vector<std::vector<bool>> map);

    std::vector<Point> GetNeighbours(const Point& point) const override;

private:
    void GetNeighbours1(std::vector<Point>& neighbours, const Point& point) const;
    void GetNeighbours2(std::vector<Point>& neighbours, const Point& point) const;
};
