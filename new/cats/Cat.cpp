//
// Created by marius on 2024-09-11.
//

#include "Cat.h"

#include <format>
#include <utility>
#include  <cmath>

Cat::Cat() = default;
Cat::Cat(const int age, std::string name, const double weight): age_(age), name_(std::move(name)), weight_(weight) {

}

int Cat::getAge() const {
    return age_;
}
std::string Cat::getName() const {
    return name_;
}
double Cat::getWeight() const {
    return weight_;
}

void Cat::setAge(const int age) {
    age_ = age;
}
void Cat::setName(const std::string &name) {
    name_ = name;
}
void Cat::setWeight(const double weight) {
    weight_ = weight;
}


std::ostream& operator <<(std::ostream& os, const Cat& cat) {
    return os << std::format("|{:>6d}|{:<16}|{:>6.2f}|", cat.age_, cat.name_, cat.weight_);
}

bool operator ==(const Cat& cat1, const Cat& cat2) {
    return cat1.age_ == cat2.age_ && cat1.name_ == cat2.name_ && std::abs(cat1.weight_ - cat2.weight_) < 1e-6;
}

bool operator !=(const Cat& cat1, const Cat& cat2) {
    return !(cat1 == cat2);
}

