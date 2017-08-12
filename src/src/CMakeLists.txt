cmake_minimum_required(VERSION 2.8.11)

add_subdirectory(main)
if(BLA)
    add_subdirectory(libbla)
endif(BLA)
