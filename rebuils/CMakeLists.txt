cmake_minimum_required(VERSION 3.29)
project(rebuils)

set(CMAKE_CXX_STANDARD 20)
include(FetchContent)

# Fetch nlohmann_json
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.11.3
)
FetchContent_MakeAvailable(nlohmann_json)
find_package(OpenSSL REQUIRED)

add_executable(rebuils main.cpp
        cat/Cat.cpp
        cat/Cat.h
        hasher.h
        input_output.h
        monitor/monitor.cpp
        monitor/monitor.h
        result/result_list.cpp
        result/result_list.h)
# Platform-specific OpenMP integration
if(MSVC)
    # Enable OpenMP for Visual Studio
    target_compile_options(rebuils PRIVATE /openmp)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
else ()
    find_package(OpenMP REQUIRED)
    target_link_libraries(rebuils PRIVATE OpenMP::OpenMP_CXX)
endif ()

# Link OpenMP libraries manually
target_link_libraries(rebuils
        PRIVATE
        nlohmann_json::nlohmann_json
        OpenSSL::SSL
        OpenSSL::Crypto
)