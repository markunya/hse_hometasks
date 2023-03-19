#include <queue>
#include "topology.h"

Topology::Topology(std::vector<std::vector<bool>> map) : map_(map) {
}

Topology::Distance Topology::MeasureDistance(const Point& from, const Point& to) const {
    if (from == to) {
        return 0;
    }
    std::queue<Point> points;
    points.push(from);
    std::unordered_map<Point, size_t> already_counted_points;
    already_counted_points[from] = 0;
    std::vector<Point> nearest_neighbours = this->GetNeighbours(from);
    while (!points.empty()) {
        nearest_neighbours = this->GetNeighbours(points.front());
        for (auto point : nearest_neighbours) {
            if (point == to) {
                return static_cast<ssize_t>(already_counted_points[points.front()] + 1);
            }
            if (!already_counted_points.contains(point)) {
                already_counted_points[point] = already_counted_points[points.front()] + 1;
                points.push(point);
            }
        }
        points.pop();
    }
    return UNREACHABLE;
}

std::vector<Point> Topology::FindPath(const Point& from, const Point& to) const {
    if (from == to) {
        return {from};
    }
    std::queue<Point> points;
    points.push(from);
    std::unordered_map<Point, Point> already_counted_points;
    already_counted_points[from] = from;
    std::vector<Point> nearest_neighbours = this->GetNeighbours(from);
    while (!points.empty()) {
        nearest_neighbours = this->GetNeighbours(points.front());
        for (auto point : nearest_neighbours) {
            if (!already_counted_points.contains(point)) {
                already_counted_points[point] = points.front();
                points.push(point);
            }
            if (point == to) {
                std::vector<Point> path;
                Point position = point;
                while (already_counted_points[position] != position) {
                    path.emplace_back(position);
                    position = already_counted_points[position];
                }
                path.emplace_back(from);
                std::reverse(path.begin(), path.end());
                return path;
            }
        }
        points.pop();
    }
    return {};
}
