
#include <iostream>
#include <vector>
#include <thread>
#include <ranges>

#include "hasher.h"
#include "input_output.h"
#include "cats/Cat.h"
#include "monitor/monitor.h"
#include "result/result_list.h"

using std::size_t;
const std::string FILE_NAME = "..\\cats.json";
const std::string RESULT_FILE = "..\\result.txt";

constexpr size_t NUM_THREADS = 10;

int main() {
    std::vector<Cat> cats = input_output::read_cats_json(FILE_NAME);
    monitor monitor;
    result_list results;
    const auto remove_fn = [&monitor, &results] {
         while (monitor.size() > 0 || !monitor.isFinished()) {
             Cat cat = monitor.remove();
             const auto hash_str = hasher::hash(cat.serialize());
             cat.setHash(hash_str);
             results.add_if(cat, [](const Cat &c) {return c.getWeight() > 5;});
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

    input_output::write_result_txt(results, RESULT_FILE);

    return 0;
}
