#pragma once

#include <iterator>

template <typename iterator_1, typename iterator_2>
class SequenceIterator {
public:
    SequenceIterator(iterator_1 it_1, iterator_2 it_2) : it_1_(it_1), it_2_(it_2) {}

    SequenceIterator& operator++() {
        ++it_1_;
        ++it_2_;
        return *this;
    }

    bool operator!=(const SequenceIterator& other) {
        return (it_1_ != other.it_1_ && it_2_ != other.it_2_);
    }

    auto operator*() {
        return std::pair{*it_1_, *it_2_};
    }

private:
    iterator_1 it_1_;
    iterator_2 it_2_;
};

template <typename iterator_1, typename iterator_2>
class Sequence {
public:
    Sequence (iterator_1 begin_1, iterator_1 end_1, iterator_2 begin_2, iterator_2 end_2) :
          begin_1_(begin_1),
          end_1_(end_1),
          begin_2_(begin_2),
          end_2_(end_2) {}

    auto begin() {
        return SequenceIterator(begin_1_, begin_2_);
    }

    auto end() {
        return SequenceIterator(end_1_, end_2_);
    }

private:
    iterator_1 begin_1_;
    iterator_1 end_1_;
    iterator_2 begin_2_;
    iterator_2 end_2_;
};

template <typename Sequence1, typename Sequence2>
auto Zip(const Sequence1& sequence1, const Sequence2& sequence2) {
    return Sequence(std::begin(sequence1), std::end(sequence1), std::begin(sequence2), std::end(sequence2));
}
