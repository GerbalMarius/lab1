//
// Created by mariu on 2024-10-03.
//

#ifndef THREAD_UTILS_H
#define THREAD_UTILS_H

namespace thread_utils {
    inline void calculate_indexes(const size_t size, const size_t num_threads, const int thread_id, int &start_index, int &end_index, const size_t base, const size_t remainder) {

        //if remainder is zero we can evenly split the tasks across threads by the divisor
        if (remainder == 0) {
            start_index = thread_id * (size / num_threads);
            end_index = start_index + (size / num_threads);
        }
        else if (thread_id < remainder) {
            //first remainder threads calculate the extra element
            start_index = thread_id * (base + 1);
            end_index = start_index + (base + 1);
        } else {
            //other threads calculate the base
            start_index = thread_id * (base) + remainder;
            end_index = start_index + (base);
        }
    }
}

#endif //THREAD_UTILS_H
