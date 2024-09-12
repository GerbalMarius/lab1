cmake_minimum_required(VERSION 3.29)
project(new)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3  # You can set a specific version here
)

# Make the content available
FetchContent_MakeAvailable(nlohmann_json)


add_executable(new main.cpp
        cats/Cat.cpp
        cats/Cat.h
        reader.h
        monitor/monitor.cpp
        monitor/monitor.h
        result/result.cpp
        result/result.h
        hasher.h)
target_link_libraries(new PRIVATE nlohmann_json::nlohmann_json)
