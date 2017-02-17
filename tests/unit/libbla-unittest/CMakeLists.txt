# *****************************************************************
# * Project        Harman Car Multimedia System
# * Copyright (C)  2009, 2011-2013, 2016 Harman Becker Automotive
# *                Systems GmbH.
# *                Authors: Andreas Schedel
# * Secrecy Level  STRICTLY CONFIDENTIAL
# ****************************************************************

project(libbla_unittest)
include(GNUInstallDirs)

cmake_minimum_required(VERSION 2.6.0)
set(CMAKE_AUTOMOC ON)

enable_testing()

set(SRC_LIST
    bla-unittest.cpp
   )

add_executable(${PROJECT_NAME} ${SRC_LIST})

include_directories(
    .
    ${Qt5Core_INCLUDE_DIRS}
    ../../../src/libbla
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    libgmock
    libbla
    qtgtestrunner
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} ${GTEST_PARAMS})
install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION /usr/bin)
