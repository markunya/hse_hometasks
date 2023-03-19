#include "checkers_topology.h"

#include <unordered_set>
#include <queue>

CheckersTopology::CheckersTopology(std::vector<std::vector<bool>> map) : Topology(map) {
}

void CheckersTopology::GetNeighbours_1(std::vector<Point>& neighbours, const Point& point) const {
    Point neighbour;
    neighbour.y = point.y + 1;
    neighbour.x = point.x + 1;
    if (CheckersTopology::map_.Height() > neighbour.y && CheckersTopology::map_.Width() > neighbour.x &&
        !CheckersTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y - 1;
    neighbour.x = point.x + 1;
    if (point.y > 0 && CheckersTopology::map_.Width() > neighbour.x && !CheckersTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y + 1;
    neighbour.x = point.x - 1;
    if (point.x > 0 && CheckersTopology::map_.Height() > neighbour.y && !CheckersTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
    neighbour.y = point.y - 1;
    neighbour.x = point.x - 1;
    if (point.x > 0 && point.y > 0 && !CheckersTopology::map_[neighbour]) {
        neighbours.emplace_back(neighbour);
    }
}

void CheckersTopology::GetNeighbours_2(std::vector<Point>& neighbours, const Point& p) const {
    std::unordered_set<Point> already_counted_points;
    std::queue<Point> points;
    points.push(p);
    while (!points.empty()) {
        Point point = points.front();
        Point neighbour;
        Point between;
        neighbour.y = point.y + 2;
        neighbour.x = point.x + 2;
        between.y = point.y + 1;
        between.x = point.x + 1;
        if (CheckersTopology::map_.Height() > neighbour.y && CheckersTopology::map_.Width() > neighbour.x &&
            !already_counted_points.contains(neighbour) && !CheckersTopology::map_[neighbour] &&
            CheckersTopology::map_[between]) {
            neighbours.emplace_back(neighbour);
            points.push(neighbour);
            already_counted_points.insert(neighbour);
        }
        neighbour.y = point.y - 2;
        neighbour.x = point.x + 2;
        between.y = point.y - 1;
        between.x = point.x + 1;
        if (point.y > 1 && CheckersTopology::map_.Width() > neighbour.x &&
            !already_counted_points.contains(neighbour) && !CheckersTopology::map_[neighbour] &&
            CheckersTopology::map_[between]) {
            neighbours.emplace_back(neighbour);
            points.push(neighbour);
            already_counted_points.insert(neighbour);
        }
        neighbour.y = point.y + 2;
        neighbour.x = point.x - 2;
        between.y = point.y + 1;
        between.x = point.x - 1;
        if (point.x > 1 && CheckersTopology::map_.Height() > neighbour.y &&
            !already_counted_points.contains(neighbour) && !CheckersTopology::map_[neighbour] &&
            CheckersTopology::map_[between]) {
            neighbours.emplace_back(neighbour);
            points.push(neighbour);
            already_counted_points.insert(neighbour);
        }
        neighbour.y = point.y - 2;
        neighbour.x = point.x - 2;
        between.y = point.y - 1;
        between.x = point.x - 1;
        if (point.x > 1 && point.y > 1 && !already_counted_points.contains(neighbour) &&
            !CheckersTopology::map_[neighbour] && CheckersTopology::map_[between]) {
            neighbours.emplace_back(neighbour);
            points.push(neighbour);
            already_counted_points.insert(neighbour);
        }
        points.pop();
    }
}

std::vector<Point> CheckersTopology::GetNeighbours(const Point& point) const {
    std::vector<Point> neighbours;
    GetNeighbours_1(neighbours, point);
    GetNeighbours_2(neighbours, point);
    return neighbours;
}