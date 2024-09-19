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
    if (!pred(cat)) {
        return;
    }
        int index = search_for_insert(cat);

        if (size_ >= cats_.max_size()) {
            throw std::overflow_error("result list is full");
        }

        for(int i = size_; i > index; i--) {
            cats_[i] = cats_[i - 1];
        }
        cats_[index] = cat;
        size_++;

}

Cat &result_list::operator[](int index) {
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

int result_list::search_for_insert(const Cat &cat) const {
    for(int i = 0; i < size_; i++) {
        if (!cmp(cat, cats_[i])) {
            return i;
        }
    }
        return size_;
}



