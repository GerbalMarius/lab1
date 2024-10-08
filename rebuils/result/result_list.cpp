
//
// Created by marius on 2024-09-12.
//

#include "result_list.h"

#include <utility>
#include <functional>
#include <stdexcept>

result_list::result_list() {
    cmp = [](const Cat& r1, const Cat & r2) {
        return r1 > r2;
    };
}
result_list::~result_list() = default;
result_list::result_list(std::function<bool(Cat, Cat)> func) {
    cmp = std::move(func);
}
int result_list::size() const {
    return size_;
}

void result_list::add_if(const Cat &cat, const std::function<bool(Cat)>& pred) {
    std::unique_lock lock(m_);
    if (!pred(cat) || cat == Cat::EMPTY) {
        return;
    }
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

void result_list::remove(const Cat &cat) {
    std::unique_lock lock(m_);
    if (size_ == 0) {
        return;
    }
    auto newEnd = std::remove(begin(), end(), cat);//find new end of collection after removal of cat
    size_ = static_cast<int>(std::distance(begin(), newEnd));// recalculate the size
    std::fill(newEnd, end(), Cat());//fill the unused parts with default values
}

Cat &result_list::operator[](int index) {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("index out of range");
    }
    return cats_[index];
}
const Cat &result_list::operator[](int index) const {
    if (index >= size_ || index < 0) {
        throw std::out_of_range("index out of range");
    }
    return cats_[index];
}

result_list::iterator result_list::begin() {
    return cats_.begin();
}
result_list::iterator result_list::end() {
    return cats_.begin() + size_;
}

result_list::const_iterator result_list::begin() const {
    return cats_.begin();
}
result_list::const_iterator result_list::end() const {
    return cats_.begin() + size_;
}
