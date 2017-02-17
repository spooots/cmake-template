cmake_minimum_required(VERSION 2.8.11)

project(foobla-tools)

set(BLA 1)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)

set(CMAKE_BUILD_TYPE Debug)
add_compile_options(
    -Wall -Wextra -Werror
    -std=c++14 -fno-strict-aliasing -fPIC
    "$<$<CONFIG:Debug>:-ggdb;-O0;-g>"
)

enable_testing()


if(COVERAGE)
    include(CTest)
    message(STATUS "COVERAGE -> enabled")
    add_compile_options(-g -O0 --coverage)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
    set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} --coverage")
    set(GTEST_PARAMS "--nare-verbose --gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/Testing/unittest/")
    configure_file(CTestCustom.cmake CTestCustom.cmake)
endif(COVERAGE)

add_subdirectory(src)
add_subdirectory(tests)
