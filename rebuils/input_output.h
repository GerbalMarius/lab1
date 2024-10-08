//
// Created by Marius Ambrazevičius on 27/09/2024.
//

#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H


#include <fstream>
#include <vector>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <sstream>

#include "cat/Cat.h"

namespace input_output {
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

    inline std::string repeat_chars(const char c, const size_t count) {
        std::stringstream ss;
        for (size_t i = 0; i < count; i++) {
            ss << c;
        }
        return ss.str();
    }

    template <typename list>
    void write_result_txt(const list &results,  std::ofstream &file) {

        if (!file.is_open()) {
            throw std::invalid_argument("Could not open file ");
        }

        if (results.size() <= 0) {
            file << "No cats present" << std::endl;
            file.close();
            return;
        }
        const Cat& proxy = results[0];

        const auto dashes = repeat_chars('-', 107);

        file << dashes << std::endl;
        file << "|" << std::setw(6) << "Age" << "|" <<
            std::left << std::setw(16) << "Name" << "|" <<
                std::left << std::setw(16) << "Weight" << "|" << std::left <<
                    std::setw(static_cast<int>(proxy.getHash().length()))  << "Hash" << "|" << std::endl;

        file << dashes << std::endl;

        for (const Cat& cat : results) {
            file << cat << '\n';
        }
        file << dashes << std::endl;
    }
}

#endif //INPUT_OUTPUT_H
