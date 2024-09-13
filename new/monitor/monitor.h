//
// Created by marius on 2024-09-11.
//

#ifndef MONITOR_H
#define MONITOR_H
#include <array>
#include <condition_variable>
#include <mutex>

#include "../cats/Cat.h"


class monitor {
public:
    monitor();

    ~monitor();

    void add(const Cat &cat);

    Cat remove();

    Cat &operator[](int index);

    [[nodiscard]]
    int size() const;

    [[nodiscard]]
    bool isFinished() const;

    void finish() {
        finished_ = true;
    }

private:
    std::array<Cat, 10> cats_;
    int size_{};
    std::mutex mutex_;
    std::condition_variable cv_;
    bool finished_{false};
};


#endif //MONITOR_H
