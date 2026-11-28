cmake_minimum_required(VERSION 3.20)
project(lab4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic -fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)

add_library(figures STATIC
    src/figure.cpp
    src/figure_collection.cpp
    src/triangle.cpp
    src/square.cpp
    src/pentagon.cpp
)
target_include_directories(figures PUBLIC include)

add_executable(lab4_app src/main.cpp)
target_link_libraries(lab4_app PRIVATE figures)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests tests/test_figures.cpp)
target_link_libraries(run_tests PRIVATE figures gtest_main)

enable_testing()
include(GoogleTest)
gtest_discover_tests(run_tests)