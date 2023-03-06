#include <unordered_set>
#include "poly.h"

size_t Pow(int64_t value, size_t power) {
    size_t result = 1;
    for (size_t i = 0; i < power; ++i) {
        result *= value;
    }
    return result;
}

Poly::Poly() {
    monomials_ = {};
}

Poly::Poly(std::vector<int64_t> monomials) {
    for (size_t i = 0; i < monomials.size(); ++i) {
        if (monomials[i] != 0) {
            monomials_[i] = monomials[i];
        }
    }
}

Poly::Poly(std::initializer_list<int64_t> monomials) : Poly(static_cast<std::vector<int64_t>>(monomials)) {
}

Poly::Poly(std::map<size_t, int64_t> monomials) {
    for (auto i : monomials) {
        if (i.second != 0) {
            monomials_[i.first] = i.second;
        }
    }
}

Poly::Poly(std::initializer_list<std::pair<size_t, int64_t>> monomials) {
    for (auto monomial : monomials) {
        if (monomial.second != 0) {
            monomials_[monomial.first] = monomial.second;
        }
    }
}

bool Poly::operator==(const Poly& other) const {
    if (monomials_.size() != other.monomials_.size()) {
        return false;
    }
    for (auto monomial : monomials_) {
        if (!other.monomials_.contains(monomial.first) || monomial.second != other.monomials_.at(monomial.first)) {
            return false;
        }
    }
    return true;
}

Poly Poly::operator+(const Poly& other) const {
    std::map<size_t, int64_t> result_monomials;
    std::vector<size_t> monomials_with_zeros;
    for (auto monomial : monomials_) {
        result_monomials[monomial.first] += monomial.second;
    }
    for (auto monomial : other.monomials_) {
        result_monomials[monomial.first] += monomial.second;
        if (result_monomials[monomial.first] == 0) {
            monomials_with_zeros.emplace_back(monomial.first);
        }
    }
    for (auto i : monomials_with_zeros) {
        result_monomials.erase(i);
    }
    return Poly(result_monomials);
}

void Poly::operator+=(const Poly& other) {
    std::vector<size_t> monomials_with_zeros;
    for (auto monomial : other.monomials_) {
        monomials_[monomial.first] += monomial.second;
        if (monomials_[monomial.first] == 0) {
            monomials_with_zeros.emplace_back(monomial.first);
        }
    }
    for (auto i : monomials_with_zeros) {
        monomials_.erase(i);
    }
}

Poly Poly::operator-() const {
    std::map<size_t, int64_t> result_monomials;
    for (auto monomial : monomials_) {
        result_monomials[monomial.first] = -monomial.second;
    }
    return Poly(result_monomials);
}


Poly Poly::operator-(const Poly& other) const {
    std::map<size_t, int64_t> result_monomials;
    std::vector<size_t> monomials_with_zeros;
    for (auto monomial : monomials_) {
        result_monomials[monomial.first] += monomial.second;
    }
    for (auto monomial : other.monomials_) {
        result_monomials[monomial.first] -= monomial.second;
        if (result_monomials[monomial.first] == 0) {
            monomials_with_zeros.emplace_back(monomial.first);
        }
    }
    for (auto i : monomials_with_zeros) {
        result_monomials.erase(i);
    }
    return Poly(result_monomials);
}

void Poly::operator-=(const Poly& other) {
    std::vector<size_t> monomials_with_zeros;
    for (auto monomial : other.monomials_) {
        monomials_[monomial.first] -= monomial.second;
        if (monomials_[monomial.first] == 0) {
            monomials_with_zeros.emplace_back(monomial.first);
        }
    }
    for (auto i : monomials_with_zeros) {
        monomials_.erase(i);
    }
}

Poly Poly::operator*(const Poly& other) {
    std::map<size_t, int64_t> result_monomials;
    std::unordered_set<size_t> monomials_with_zeros;
    for (auto monomial_1 : monomials_) {
        for (auto monomial_2 : other.monomials_) {
            result_monomials[monomial_1.first + monomial_2.first] += monomial_1.second * monomial_2.second;
            if (result_monomials[monomial_1.first + monomial_2.first] == 0) {
                monomials_with_zeros.insert(monomial_1.first + monomial_2.first);
            } else {
                monomials_with_zeros.erase(monomial_1.first + monomial_2.first);
            }
        }
    }
    for (auto i : monomials_with_zeros) {
        result_monomials.erase(i);
    }
    return Poly(result_monomials);
}

void Poly::operator*=(const Poly& other) {
    *this = *this * other;
}

size_t Poly::operator()(size_t value) const {
    size_t result = 0;
    for (auto monomial : monomials_) {
        result += monomial.second * (Pow(value, monomial.first));
    }
    return result;
}

std::ostream& operator<<(std::ostream& stream, const Poly& poly) {
    if (poly.monomials_.empty()) {
        stream << "y = ";
        stream << 0;
        return stream;
    }
    stream << "y = ";
    for (auto it = poly.monomials_.rbegin(); it != poly.monomials_.rend(); ++it) {
        if (it->first == 0) {
            if (it == poly.monomials_.rbegin()) {
                stream << it->second << "x^" << it->first;
                return stream;
            }
            stream << (it->second < 0 ? '-' : '+') << ' ' << std::abs(it->second);
            return stream;
        }
        if (it == poly.monomials_.rbegin()) {
            stream << it->second << "x^" << it->first << (poly.monomials_.size() > 1 ? " " : "");
        } else {
            stream << (it->second < 0 ? '-' : '+') << ' ' << std::abs(it->second) << "x^" << it->first << ' ';
        }
    }
    return stream;
}

