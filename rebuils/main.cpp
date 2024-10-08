

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
#include "monitor/monitor.h"
#include "result/result_list.h"



using std::size_t;
const std::string FILE_NAME = "cats.json";
const std::string RESULT_FILE = "result.txt";

constexpr size_t NUM_THREADS = 5;



int main() {
    const std::vector<Cat> cats = input_output::read_cats_json(FILE_NAME);
    monitor monitor;
    result_list results;
    int items_removed = 0;
    const auto remove_fn = [&monitor, &results, &items_removed, &cats] {
        while (items_removed < cats.size()) {
            Cat cat = monitor.remove();
            items_removed++;
            const auto hash_str = hasher::hash(cat.serialize());
            cat.setHash(hash_str);
            results.add_if(cat, [](const Cat& c) { return  true; });
        }
    };


    std::vector<std::thread> threads;
    threads.reserve(NUM_THREADS);
    for (size_t i = 0; i < NUM_THREADS; i++) {
        threads.emplace_back(remove_fn);
    }

    for (const auto &cat: cats) {
        monitor.add(cat);
    }
    monitor.finish();
    std::ranges::for_each(threads, mem_fn(&std::thread::join));
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
