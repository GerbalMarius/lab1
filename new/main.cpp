
#include <iostream>
#include <set>
#include <vector>
#include <thread>
#include <set>

#include "hasher.h"
#include "reader.h"
#include "cats/Cat.h"
#include "monitor/monitor.h"
#include "result/result_list.h"


const std::string FILE_NAME = "cats.json";


int main() {
    std::vector<Cat> cats = reader::read_cats_json(FILE_NAME);
    monitor monitor;
    result_list results;
    const auto remove_fn = [&monitor, &results] {
         while (monitor.size() > 0 || !monitor.isFinished()) {
             Cat cat = monitor.remove();
             const auto hash_str = hasher::hash(cat.serialize());
             cat.setHash(hash_str);
             results.add_if(cat);
         }
     };


     std::thread t1(remove_fn);
     std::thread t2(remove_fn);


     for (const auto &cat: cats) {
         monitor.add(cat);
     }
     monitor.finish();
     t1.join();
     t2.join();
    for (const auto &result: results) {
        std::cout << result << std::endl;
    }
    std::cout << monitor.size();

    return 0;
}
