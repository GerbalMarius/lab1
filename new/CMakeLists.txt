cmake_minimum_required(VERSION 3.29)
project(new)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# Fetch nlohmann_json
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3  # You can set a specific version here
)
FetchContent_MakeAvailable(nlohmann_json)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# Add executable
add_executable(new
        main.cpp
        cats/Cat.cpp
        cats/Cat.h
        input_output.h
        monitor/monitor.cpp
        monitor/monitor.h
        result/result_list.cpp
        result/result_list.h
        hasher.h
)

# Link libraries
target_link_libraries(new
        PRIVATE
        nlohmann_json::nlohmann_json
        OpenSSL::SSL
        OpenSSL::Crypto
)
