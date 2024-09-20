cmake_minimum_required(VERSION 3.29)
project(new)

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

# Set compilers to use LLVM's clang from Homebrew
set(CMAKE_C_COMPILER "/opt/homebrew/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/opt/homebrew/opt/llvm/bin/clang++")

# Add paths to LLVM's OpenMP
set(OpenMP_C_FLAGS "-Xpreprocessor -fopenmp")
set(OpenMP_C_LIB_NAMES "omp")
set(OpenMP_omp_LIBRARY "/opt/homebrew/opt/libomp/lib/libomp.dylib")
set(OpenMP_CXX_FLAGS "-Xpreprocessor -fopenmp")

# Add OpenMP flags to both C and C++ compilers
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -L/opt/homebrew/opt/libomp/lib -lomp")

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

# Link OpenMP libraries manually
target_link_libraries(new
        PRIVATE
        ${OpenMP_omp_LIBRARY}
        nlohmann_json::nlohmann_json
        OpenSSL::SSL
        OpenSSL::Crypto
)
