//
// Created by marius on 2024-09-12.
//

#ifndef RESULT_H
#define RESULT_H
#include <mutex>
#include <functional>

#include "../cats/Cat.h"


class result_list {
public:
    using iterator = std::array<Cat, 30>::iterator;
    using const_iterator = std::array<Cat, 30>::const_iterator;

    result_list();
    ~result_list();
    explicit result_list(std::function<bool(Cat, Cat)> func);

    [[nodiscard]]
    int size() const;

    void add_if(const Cat& cat, const std::function<bool(Cat)>& pred);
    void add(const Cat& cat) {
        add_if(cat, [](const Cat& _) {return true;});
    }

     Cat& operator[](int index);
     iterator begin();
     iterator end();

    [[nodiscard]] const_iterator begin() const;
    [[nodiscard]] const_iterator end() const;

private:
    std::mutex m_;
    std::array<Cat, 30> cats_;
    std::function<bool(Cat, Cat)> cmp;
    int size_{};

    int search_for_insert(const Cat& cat) const;
};


#endif //RESULT_H
