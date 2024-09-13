//
// Created by marius on 2024-09-12.
//

#ifndef RESULT_H
#define RESULT_H
#include <mutex>
#include <functional>

#include "../cats/Cat.h"


class result {
public:

    result();
    ~result();
    explicit result(std::function<bool(Cat, Cat)> func);

    [[nodiscard]]
    int size() const;

    friend Cat& operator[](int index);

private:
    std::mutex m_;
    std::array<Cat, 30> cats_;
    std::function<bool(Cat, Cat)> cmp;
    int size_{};
};


#endif //RESULT_H
