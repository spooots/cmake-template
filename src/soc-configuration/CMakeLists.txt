# *****************************************************************
# * Project        Harman Car Multimedia System
# * Copyright (C)  2009, 2011-2013, 2016 Harman Becker Automotive
# *                Systems GmbH.
# *                Authors: Andreas Schedel
# * Secrecy Level  STRICTLY CONFIDENTIAL
# ****************************************************************

project(soc-configuration)
include(GNUInstallDirs)

cmake_minimum_required(VERSION 2.8.11)
set(CMAKE_AUTOMOC ON)

set(SOC_CFG_MAJOR_VERSION 0)
set(SOC_CFG_MINOR_VERSION 1)
set(SOC_CFG_PATCH_VERSION 0)

if(TFMGOV)
    message(STATUS "use TFM governor")
    add_definitions(
        -DTFMGOV
    )
    set(TFMGOVLIB
        libnsmconsumer
        libtfmgovernor
    )
    set(TFMGOVINC
         ../libnsmconsumer
         ../libtfmgovernor
    )
endif(TFMGOV)

add_definitions(
    -DVMAJOR=${SOC_CFG_MAJOR_VERSION}
    -DVMINOR=${SOC_CFG_MINOR_VERSION}
    -DVPATCH=${SOC_CFG_PATCH_VERSION}
    -DSOCPERF
)

set(EXECUTABLE_NAME ${PROJECT_NAME})

aux_source_directory(. SRC_LIST)

FILE(GLOB_RECURSE CfgFiles "cfg/*")
add_custom_target(Configurations SOURCES ${CfgFiles})

add_executable(${PROJECT_NAME} ${SRC_LIST})

include_directories(
     ${NaRELogging_INCLUDE_DIRS}
     ${Qt5Core_INCLUDE_DIRS}
     ${TFMGOVINC}
     ../libsocperfctrl
)

set(SOCCTRL_LIBS
    ${TFMGOVLIB}
    libsocperfctrl
)

set(NARE_LIBS
    ${NaRECore_LIBRARIES}
    ${NaRELogging_LIBRARIES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    ${NARE_LIBS}
    ${SOCCTRL_LIBS}
)

function(add_capi_package TARGET NAME)
    pkg_check_modules(PC_${NAME} "${NAME}.core")
    pkg_check_modules(PC_${NAME}_SOMEIP "${NAME}.someip")

    target_compile_options(${TARGET} PUBLIC ${PC_${NAME}_CFLAGS})
    target_link_libraries(${TARGET}
        PRIVATE CommonAPI
        ${PC_${NAME}_LDFLAGS}
        ${PC_${NAME}_SOMEIP_LDFLAGS}
        )
        include_directories(
            ${PC_${NAME}_INCLUDE_DIRS}
            ${PC_${NAME}_SOMEIP_INCLUDE_DIRS}
    )
endfunction()

install(TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION /usr/bin)
