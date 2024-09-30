#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <mutex>         // Include for std::mutex
#include <filesystem>    // Include for std::filesystem
#include <omp.h>

#include "hasher.h"
#include "input_output.h"
#include "cat/Cat.h"
#include "result/result_list.h"


void calculate_results(const std::vector<Cat> &cats, result_list &results, int &sum_ints, double &sum_doubles);

const std::string FILE_NAME = "cats.json";
const std::string RESULT_FILE = "result.txt";

constexpr std::size_t NUM_THREADS = 6;


int main() {
    std::vector<Cat> cats = input_output::read_cats_json(FILE_NAME);
    result_list results;

    int age_sum = 0;
    double weight_sum = 0;

    calculate_results(cats, results, age_sum, weight_sum);
    std::cout << age_sum << " " << weight_sum << std::endl;

    if (std::filesystem::exists(RESULT_FILE)) {
        std::filesystem::remove(RESULT_FILE);
    }
    std::ofstream out(RESULT_FILE, std::ios::app);
    out << "Pradiniai duomenys:" << '\n';
    input_output::write_result_txt(cats, out);
    out << '\n';
    out << "Po filtravimo ir rikiavimo:" << '\n';
    input_output::write_result_txt(results, out);
    out << std::setw(90) << "Amziaus (int) suma: " << age_sum << '\n';
    out << std::setw(90) << "Svorio (double) suma: " << weight_sum << '\n';
    out.close();

    return 0;
}

void calculate_results(const std::vector<Cat> &cats, result_list &results, int &sum_ints, double &sum_doubles) {

    if (cats.empty() || NUM_THREADS < 1) {
        return;
    }

    omp_set_num_threads(NUM_THREADS);

    const std::size_t base_count = cats.size() / NUM_THREADS;
    const std::size_t remainder = cats.size() % NUM_THREADS;


#pragma omp parallel reduction(+:sum_ints,sum_doubles) default(none) shared(cats, results, std::cout, base_count, remainder)
    {
        const int thread_id = omp_get_thread_num();

        int start_index;
        int end_index;

        if (thread_id < remainder) {
            //first remainder threads calculate the extra element
            start_index = thread_id * (base_count + 1);
            end_index = start_index + (base_count + 1);
        } else {
            //other threads calculate the base
            start_index = thread_id * (base_count) + remainder;
            end_index = start_index + (base_count);
        }
        //if remainder is zero we can evenly split the tasks across threads by the divisor
        if (remainder == 0) {
            start_index = thread_id * (cats.size() / NUM_THREADS);
            end_index = start_index + (cats.size() / NUM_THREADS);
        }

       // #pragma omp critical
        //      std::cout << "Thread #" << thread_id << ":" << end_index - start_index << " number of elements" <<  '\n';
        for (std::size_t i = start_index; i < end_index; i++) {
            Cat cat = cats[i];
            const std::string hash = hasher::hash(cat.serialize());
            cat.setHash(hash);
            if (cat.getWeight() > 6) {
                results.add(cat);
                sum_ints += cat.getAge();
                sum_doubles += cat.getWeight();
            }
        }
    }
}
