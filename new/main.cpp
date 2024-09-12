
#include <iostream>
#include <set>
#include <vector>
#include <thread>
#include <set>

#include "reader.h"
#include "cats/Cat.h"
#include "monitor/monitor.h"


const std::string FILE_NAME = "cats.json";





int main() {

    std::vector<Cat> cats = reader::read_cats_json(FILE_NAME);
    monitor monitor;


   const auto remove_fn = [&monitor] {
       while (monitor.size() > 0) {
           monitor.remove();
       }

    };


    std::thread t1(remove_fn);

    std::thread t2(remove_fn);
    std::thread t3(remove_fn);


    for (const auto& cat : cats) {
        monitor.add(cat);
    }

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
