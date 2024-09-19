//
// Created by marius on 2024-09-11.
//

#include "Cat.h"

#include <format>
#include <utility>
#include  <cmath>
#include <iomanip>
#include <ios>

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

void Cat::setHash(std::string hash) {
    hash_ = std::move(hash);
}

std::string Cat::serialize() const {
    return getName() + std::to_string(getAge()) + std::to_string(getWeight());
}


std::ostream &operator <<(std::ostream &os, const Cat &cat) {
    return os << "|" << std::setw(6) << cat.age_ << "|"
           << std::left << std::setw(16) << cat.name_ << "|"
           << std::right << std::setw(6) << std::fixed << std::setprecision(2) << cat.weight_ << "|"
           << cat.hash_ << "|";
}

bool operator ==(const Cat &cat1, const Cat &cat2) {
    return cat1.age_ == cat2.age_ && cat1.name_ == cat2.name_ && std::abs(cat1.weight_ - cat2.weight_) < 1e-6;
}

bool operator !=(const Cat &cat1, const Cat &cat2) {
    return !(cat1 == cat2);
}
bool operator >(const Cat &cat1, const Cat &cat2) {
    int result = cat1.name_.compare(cat2.name_);
    return result > 0;
}

