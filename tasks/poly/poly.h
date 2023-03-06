#pragma once

#include <vector>
#include <map>
#include <ostream>

class Poly {
public:
    Poly();
    explicit Poly(std::vector<int64_t>);
    explicit Poly(std::map<size_t, int64_t>);
    Poly(std::initializer_list<int64_t>);
    Poly(std::initializer_list<std::pair<size_t, int64_t>>);
    bool operator==(const Poly& other) const;
    Poly operator+(const Poly& other) const;
    void operator+=(const Poly& other);
    Poly operator-() const;
    Poly operator-(const Poly& other) const;
    void operator-=(const Poly& other);
    Poly operator*(const Poly& other);
    void operator*=(const Poly& other);
    size_t operator()(size_t value) const;

    friend std::ostream& operator<<(std::ostream& stream, const Poly& poly);

private:
    std::map<size_t, int64_t> monomials_;
};
