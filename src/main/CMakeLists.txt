project(foo)

include(GNUInstallDirs)

cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_AUTOMOC ON)

set(FOO_MAJOR_VERSION 0)
set(FOO_MINOR_VERSION 1)
set(FOO_PATCH_VERSION 0)

if(BLA)
    message(STATUS "use BLA")
    add_definitions(
        -DBLA
    )
    set(BLALIB
        libbla
    )
    set(BLAINC
         ../libbla
    )
endif(BLA)

add_definitions(
    -DVMAJOR=${FOO_MAJOR_VERSION}
    -DVMINOR=${FOO_CFG_MINOR_VERSION}
    -DVPATCH=${FOO_CFG_PATCH_VERSION}
)

set(EXECUTABLE_NAME ${PROJECT_NAME})

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST})

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${BLAINC}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    ${BLALIB}
)

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION /usr/local/bin)
