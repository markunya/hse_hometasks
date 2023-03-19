#include "overflow_topology.h"

OverflowTopology::OverflowTopology(std::vector<std::vector<bool>> map) : Topology(map) {}

std::vector<Point> OverflowTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> neighbours;
    Point neighbour;
    neighbour.y = point.y < OverflowTopology::map_.Height() - 1 ? (point.y + 1) : (0);
    neighbour.x = point.x;
    if (OverflowTopology::map_.Height() > neighbour.y && !OverflowTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y > 0 ? (point.y - 1) : (OverflowTopology::map_.Height() - 1);
    neighbour.x = point.x;
    if (!OverflowTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y;
    neighbour.x = point.x < OverflowTopology::map_.Width() - 1 ? (point.x + 1) : (0);
    if (!OverflowTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y;
    neighbour.x = point.x > 0 ? (point.x - 1) : (OverflowTopology::map_.Width() - 1);
    if (!OverflowTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    return neighbours;
}