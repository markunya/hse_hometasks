#include "planar_topology.h"

PlanarTopology::PlanarTopology(std::vector<std::vector<bool>> map) : Topology(map) {
}

std::vector<Point> PlanarTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> neighbours;
    Point neighbour;
    neighbour.y = point.y + 1;
    neighbour.x = point.x;
    if (PlanarTopology::map_.Height() > neighbour.y && !PlanarTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y - 1;
    neighbour.x = point.x;
    if (point.y > 0 && !PlanarTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y;
    neighbour.x = point.x + 1;
    if (PlanarTopology::map_.Width() > neighbour.x && !PlanarTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y;
    neighbour.x = point.x - 1;
    if (point.x > 0 && !PlanarTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    return neighbours;
}
