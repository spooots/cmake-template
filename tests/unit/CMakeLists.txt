cmake_minimum_required(VERSION 2.8.11)

if(BLA)
    add_subdirectory(libbla-unittest)
endif(BLA)

add_subdirectory(testrunner)
