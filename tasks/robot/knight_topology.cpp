#include "knight_topology.h"

KnightTopology::KnightTopology(std::vector<std::vector<bool>> map) : Topology(map) {
}

std::vector<Point> KnightTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> neighbours;
    Point neighbour;
    neighbour.y = point.y + 1;
    neighbour.x = point.x - 2;
    if (KnightTopology::map_.Height() > neighbour.y && point.x > 1 && !KnightTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y + 1;
    neighbour.x = point.x + 2;
    if (KnightTopology::map_.Height() > neighbour.y && KnightTopology::map_.Width() > neighbour.x &&
        !KnightTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y - 1;
    neighbour.x = point.x - 2;
    if (point.y > 0 && point.x > 1 && !KnightTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y - 1;
    neighbour.x = point.x + 2;
    if (point.y > 0 && KnightTopology::map_.Width() > neighbour.x && !KnightTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y + 2;
    neighbour.x = point.x + 1;
    if (KnightTopology::map_.Width() > neighbour.x && KnightTopology::map_.Height() > neighbour.y &&
        !KnightTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y - 2;
    neighbour.x = point.x + 1;
    if (KnightTopology::map_.Width() > neighbour.x && point.y > 1 && !KnightTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y + 2;
    neighbour.x = point.x - 1;
    if (point.x > 0 && KnightTopology::map_.Height() > neighbour.y && !KnightTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y - 2;
    neighbour.x = point.x - 1;
    if (point.x > 0 && point.y > 1 && !KnightTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    return neighbours;
}