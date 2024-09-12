//
// Created by marius on 2024-09-11.
//

#ifndef READER_H
#define READER_H
#include <fstream>
#include <vector>
#include <nlohmann/json.hpp>

#include "cats/Cat.h"

namespace reader {
    inline std::vector<Cat> read_cats_json(const std::string& jsonFile) {
        nlohmann::json cats_json;

        std::ifstream file(jsonFile);
        if (!file.is_open()) {
            throw std::invalid_argument("Could not open file " + jsonFile);
        }

        file >> cats_json;

        std::vector<Cat> cats;

        cats.reserve(cats_json.size());

        for (const auto& cat_data : cats_json) {
            int age = cat_data["age"].get<int>();

            std::string name = cat_data["name"].get<std::string>();
            double weight = cat_data["weight"].get<double>();

            cats.emplace_back(age, name, weight);
        }
        file.close();

        return cats;


    }
}

#endif //READER_H
