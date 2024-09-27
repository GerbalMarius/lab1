
//
// Created by marius on 2024-09-12.
//

#ifndef HASHER_H
#define HASHER_H

#include <iomanip>
#include <mutex>
#include <sstream>
#include <string>
#include <openssl/sha.h>

namespace hasher {

    inline std::string hash(const std::string &serialized_str) {
        unsigned char hash[SHA256_DIGEST_LENGTH];


        SHA256(reinterpret_cast<const unsigned char *>(serialized_str.c_str()), serialized_str.length(), hash);

        std::stringstream ss;
        for (unsigned char ch : hash) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(ch);
        }
        return ss.str();
    }
}

#endif //HASHER_H
