//
// Created by marius on 2024-09-12.
//

#include "result.h"

#include <utility>
#include <functional>

result::result() {
    cmp = [](const Cat& r1, const Cat & r2) {
        return r1 < r2;
    };
}
result::~result() = default;
result::result(std::function<bool(Cat, Cat)> func) {
    cmp = std::move(func);
}
int result::size() const {
    return size_;
}
 Cat &result::operator[](int index) {
     if (index >= size_ || index < 0) {
         throw std::out_of_range("index out of range");
     }
     return cats_[index];
 }



