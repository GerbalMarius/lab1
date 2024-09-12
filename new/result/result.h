//
// Created by marius on 2024-09-12.
//

#ifndef RESULT_H
#define RESULT_H
#include <mutex>
#include <set>

#include "../cats/Cat.h"


class result {



private:
    std::mutex m_;
    std::multiset<Cat> s_;
    int size{};
};



#endif //RESULT_H
