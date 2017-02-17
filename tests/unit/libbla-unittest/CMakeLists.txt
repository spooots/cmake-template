# *****************************************************************
# * Project        Harman Car Multimedia System
# * Copyright (C)  2009, 2011-2013, 2016 Harman Becker Automotive
# *                Systems GmbH.
# *                Authors: Andreas Schedel
# * Secrecy Level  STRICTLY CONFIDENTIAL
# ****************************************************************

project(libsocperfctrl_unittest)
include(GNUInstallDirs)

cmake_minimum_required(VERSION 2.6.0)
set(CMAKE_AUTOMOC ON)

enable_testing()

add_definitions(-DVMAJOR=${BLA_MAJOR_VERSION} -DVMINOR=${BLA_MINOR_VERSION} -DVPATCH=${BLA_PATCH_VERSION})

set(SRC_LIST
    socperfctrlserver-unittest.cpp
    socperfctrltestproxy.cpp
   )

add_executable(${PROJECT_NAME} ${SRC_LIST})

find_package(GMock REQUIRED)

include_directories(
    .
    ${GMOCK_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ../../../src/libbla
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    ${GMOCK_LIBRARIES}
    libbla
    qtgtestrunner
)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME} ${GTEST_PARAMS})
install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION /usr/bin)
