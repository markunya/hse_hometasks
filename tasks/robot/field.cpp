#include "field.h"

Field::Field(std::vector<std::vector<bool>> field) : field_(field) {
}

size_t Field::Height() const {
    return field_.size();
}

size_t Field::Width() const {
    return field_[0].size();
}

bool Field::operator[](const Point& point) const {
    return field_[point.y][point.x];
}