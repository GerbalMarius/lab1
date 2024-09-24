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

# Add executable first
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

# Platform-specific OpenMP integration
if (MSVC)
    # Enable OpenMP for Visual Studio
    target_compile_options(new PRIVATE /openmp)
elseif (APPLE)
    # macOS: Find and link OpenMP
    find_package(OpenMP REQUIRED)
    if (OpenMP_FOUND)
        target_link_libraries(new PRIVATE OpenMP::OpenMP_CXX)
    endif()
else()
    # For other platforms (e.g., Linux, MinGW)
    find_package(OpenMP REQUIRED)
    if (OpenMP_FOUND)
        target_link_libraries(new PRIVATE OpenMP::OpenMP_CXX)
    endif()
endif()

# Link OpenMP libraries manually
target_link_libraries(new
        PRIVATE
        nlohmann_json::nlohmann_json
        OpenSSL::SSL
        OpenSSL::Crypto
)
