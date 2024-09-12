//
// Created by marius on 2024-09-11.
//

#include "monitor.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <array>


monitor::monitor() = default;

monitor::~monitor() = default;

Cat &monitor::operator[](const int index) {
    if (index < 0 || index > size_) {
        throw std::out_of_range("index out of range");
    }
    return cats_[index];
}

int monitor::size() const {
    return size_;
}


void monitor::add(const Cat &cat) {
    std::unique_lock lock(mutex_);

    cv_.wait(lock, [&] { return size_ < cats_.max_size(); });

    cats_[size_++] = cat;
    cv_.notify_all();
}

Cat monitor::remove() {
    std::unique_lock lock(mutex_);
    cv_.wait(lock, [&] { return size_ > 0; });

    Cat last = cats_[size_ - 1];
    --size_;

    cv_.notify_all();
    return last;
}
