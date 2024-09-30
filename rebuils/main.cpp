

#include <iostream>
#include <vector>
#include <fstream>
#include <mutex>         // Include for std::mutex
#include <filesystem>    // Include for std::filesystem
#include <omp.h>

#include "hasher.h"
#include "input_output.h"
#include "cat/Cat.h"
#include "result/result_list.h"


void process_parallel(const std::vector<Cat>& cats, result_list& results);

const std::string FILE_NAME = "cats.json";
const std::string RESULT_FILE = "result.txt";

constexpr std::size_t NUM_THREADS = 10;



int main() {
    std::vector<Cat> cats = input_output::read_cats_json(FILE_NAME);
    result_list results;


    process_parallel(cats, results);

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

void process_parallel(const std::vector<Cat>& cats, result_list& results) {
    omp_set_num_threads(NUM_THREADS);

    std::size_t base_count = cats.size() / NUM_THREADS;
    std::size_t remainder = cats.size() % NUM_THREADS;


#pragma omp parallel default(none) shared(cats, results, std::cout, base_count, remainder)
    {
        int thread_id = omp_get_thread_num();

        int start_index;
        int end_index;

        if (thread_id < remainder) {
            start_index = thread_id * (base_count + 1);
            end_index = start_index + (base_count + 1);
        }
        else {
            start_index = thread_id * (base_count) + remainder;
            end_index = start_index + (base_count);
        }

        if (remainder == 0) {
            start_index = thread_id * (cats.size() / NUM_THREADS);
            end_index = start_index + (cats.size() / NUM_THREADS);
        }

//#pragma omp critical
 //       std::cout << "Thread #" << thread_id << ":" << end_index - start_index << '\n';
        for (std::size_t i = start_index; i < end_index; i++) {
            Cat cat = cats.at(i);
            const std::string hash = hasher::hash(cat.serialize());
            cat.setHash(hash);
            results.add_if(cat, [&](const Cat& c) { return c.getWeight() > 6; });
        }
    }
}
