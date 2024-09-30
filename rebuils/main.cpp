

#include <iostream>
#include <vector>
#include <thread>
#include <ranges>
#include <fstream>
#include <mutex>         // Include for std::mutex
#include <filesystem>    // Include for std::filesystem
#include <omp.h>

#include "hasher.h"
#include "input_output.h"
#include "cat/Cat.h"
#include "result/result_list.h"




const std::string FILE_NAME = "cats.json";
const std::string RESULT_FILE = "result.txt";

constexpr std::size_t NUM_THREADS = 5;



int main() {
    std::cout << omp_get_num_threads() << std::endl;
    std::vector<Cat> cats = input_output::read_cats_json(FILE_NAME);
    result_list results;



    if (std::filesystem::exists(RESULT_FILE)) {
        std::filesystem::remove(RESULT_FILE);
    }
    std::ofstream out(RESULT_FILE,  std::ios::app);
    out << "Pradiniai duomenys:" << '\n';
    input_output::write_result_txt(cats, out);
    out << '\n';
    out << "Po filtravimo ir rikiavimo:" << '\n';
    input_output::write_result_txt(results, out);
    out.close();

    return 0;
}
