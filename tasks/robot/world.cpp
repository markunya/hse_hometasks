#include "world.h"


World::World(const Topology& topology, Point start, Point end) : topology_(topology), start_(start), end_(end), current_position_(start) {}

const Point& World::GetStart() const {
    return start_;
}

const Point& World::GetEnd() const {
    return end_;
}

const Point& World::GetCurrentPosition() const {
    return current_position_;
}

void World::Move(const Point& to) {
    std::vector<Point> neighbours = topology_.GetNeighbours(current_position_);
    bool is_neighbour = false;
    for (auto neighbour : neighbours) {
        if (neighbour == to) {
            current_position_ = to;
            is_neighbour = true;
            break;
        }
    }
    if (!is_neighbour) {
        throw IllegalMoveException();
    }
}

std::unordered_map<Point, Topology::Distance> World::Lookup() const {
    std::unordered_map<Point, Topology::Distance> lookup;
    std::vector<Point> neighbours = topology_.GetNeighbours(current_position_);
    for (auto neighbour : neighbours) {
        lookup[neighbour] = topology_.MeasureDistance(neighbour, end_);
    }
    return lookup;
}

std::vector<Point> World::FindPath() const {
    return topology_.FindPath(start_, end_);
}