project(qtgtestrunner)
cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Test REQUIRED)

aux_source_directory(. SRC_LIST)
add_library(${PROJECT_NAME} ${SRC_LIST})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt5::Test
    PRIVATE ${NaRECore_LIBRARIES}
    PRIVATE ${GTEST_LIBRARIES}
)
