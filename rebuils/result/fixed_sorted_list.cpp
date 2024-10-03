
//
// Created by marius on 2024-09-12.
//

#include "fixed_sorted_list.h"

#include <utility>
#include <functional>
#include <stdexcept>

fixed_sorted_list::fixed_sorted_list() {
    cmp = [](const Cat& r1, const Cat & r2) {
        return r1 > r2;
    };
}
fixed_sorted_list::~fixed_sorted_list() = default;
fixed_sorted_list::fixed_sorted_list(std::function<bool(Cat, Cat)> func) {
    cmp = std::move(func);
}
int fixed_sorted_list::size() const {
    return size_;
}

void fixed_sorted_list::add_if(const Cat &cat, const std::function<bool(Cat)>& pred) {
    if (!pred(cat)) {
        return;
    }
#pragma omp critical
    {
        if (size_ >= cats_.max_size()) {
            throw std::overflow_error("result list is full");
        }
        int i;
        for(i = size_ - 1; i >= 0 && cmp(cats_[i], cat); i--) {
            cats_[i + 1] = cats_[i];
        }
        cats_[i + 1] = cat;
        size_++;
    }

}

void fixed_sorted_list::remove(const Cat &cat) {

        if (size_ == 0) {
            return;
        }
#pragma omp critical
    {
            auto newEnd = std::remove(begin(), end(), cat);//find new end of collection after removal of cat
            size_ = static_cast<int>(std::distance(begin(), newEnd));// recalculate the size
            std::fill(newEnd, end(), Cat());//fill the unused parts with default values
    }
}

Cat &fixed_sorted_list::operator[](int index) {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("index out of range");
    }
    return cats_[index];
}
const Cat &fixed_sorted_list::operator[](int index) const {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("index out of range");
    }
    return cats_[index];
}

fixed_sorted_list::iterator fixed_sorted_list::begin() {
    return cats_.begin();
}
fixed_sorted_list::iterator fixed_sorted_list::end() {
    return cats_.begin() + size_;
}

fixed_sorted_list::const_iterator fixed_sorted_list::begin() const {
    return cats_.begin();
}
fixed_sorted_list::const_iterator fixed_sorted_list::end() const {
    return cats_.begin() + size_;
}
