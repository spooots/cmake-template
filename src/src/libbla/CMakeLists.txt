# *****************************************************************
# * Project        Harman Car Multimedia System
# * Copyright (C)  2009, 2011-2013, 2016 Harman Becker Automotive
# *                Systems GmbH.
# *                Authors: Andreas Schedel
# * Secrecy Level  STRICTLY CONFIDENTIAL
# ****************************************************************
project(libbla)
include(GNUInstallDirs)

cmake_minimum_required(VERSION 2.6.0)
set(CMAKE_AUTOMOC ON)

add_definitions(-DVMAJOR=0 -DVMINOR=1 -DVPATCH=0)

set(LIB_NAME ${PROJECT_NAME})
aux_source_directory(. SRC_LIST)
add_library(${LIB_NAME} ${SRC_LIST})

include_directories(
     ${Qt5Core_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
)

#install(TARGETS ${LIB_NAME} LIBRARY DESTINATION /usr/lib)
