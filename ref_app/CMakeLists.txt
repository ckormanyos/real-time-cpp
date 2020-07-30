#
# MIT License
#
# Copyright (c) 2019 Joel Winarske
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
cmake_minimum_required(VERSION 3.11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "MinSizeRel" CACHE STRING "Choose the type of build, options are: Debug, Release, or MinSizeRel." FORCE)
    message(STATUS "CMAKE_BUILD_TYPE not set, defaulting to MinSizeRel.")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(ref_app VERSION "${REALTIME_CPP_VERSION}" LANGUAGES CXX ASM)

message(STATUS "Generator .............. ${CMAKE_GENERATOR}")
message(STATUS "Build Type ............. ${CMAKE_BUILD_TYPE}")

# ------------------------------------------------------------------------------
# defaults for host build
# ------------------------------------------------------------------------------
if(NOT APP)
    set(APP ref_app)
endif()

if(NOT TARGET)
    set(TARGET host)
endif()

if(NOT NAME)
    set(NAME ${TARGET})
endif()

if(NOT OBJDUMP)
    set(OBJDUMP objdump)
endif()

if(NOT NM)
    set(NM nm)
endif()

if(NOT READELF)
    if(NOT APPLE)
        set(READLEF readelf)
    else()
        set(READLEF otool)
    endif()
endif()

if(NOT CPPFILT)
    set(CPPFILT c++filt)
endif()

if(NOT SIZE)
    set(SIZE size)
endif()

if(NOT APPLE)
    set(SIZE_OPTIONS -A -t)
endif()

# ------------------------------------------------------------------------------
# paths
# ------------------------------------------------------------------------------
set(PATH_APP          src)
set(PATH_TGT          target/micros/${TARGET})
set(PATH_APP_MAKE     target/app/make)
set(PATH_TGT_MAKE     ${PATH_TGT}/make)
set(PATH_BIN          bin)
set(PATH_TMP          tmp)
set(PATH_OBJ          ${PATH_TMP}/obj)
set(PATH_SRC          ${PATH_TMP}/src)
set(PATH_ERR          ${PATH_TMP}/err)

# ------------------------------------------------------------------------------
# the application
# ------------------------------------------------------------------------------
#set(APP ${PATH_BIN}/ref_app)

# ------------------------------------------------------------------------------
# linker definition file
# ------------------------------------------------------------------------------
set(LINKER_DEFINITION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/${PATH_TGT_MAKE}/${TARGET}.ld)

# ------------------------------------------------------------------------------
# target variables
# ------------------------------------------------------------------------------
include(${TARGET})

# ------------------------------------------------------------------------------
# set build flags from toolchain and target
# ------------------------------------------------------------------------------

set(CMAKE_CC_FLAGS "${CFLAGS} ${TARGET_CFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS "${AFLAGS} ${TARGET_CFLAGS} ${TARGET_AFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS "${CPPFLAGS} ${TARGET_CFLAGS} ${TARGET_CPPFLAGS}" CACHE STRING "" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${LDFLAGS} ${TARGET_LDFLAGS}" CACHE STRING "" FORCE)

# ------------------------------------------------------------------------------
# app files
# ------------------------------------------------------------------------------
set(app_src
    ${PATH_APP}/app/benchmark/app_benchmark
    ${PATH_APP}/app/benchmark/app_benchmark_complex
    ${PATH_APP}/app/benchmark/app_benchmark_crc
    ${PATH_APP}/app/benchmark/app_benchmark_fast_math
    ${PATH_APP}/app/benchmark/app_benchmark_filter
    ${PATH_APP}/app/benchmark/app_benchmark_fixed_point
    ${PATH_APP}/app/benchmark/app_benchmark_float
    ${PATH_APP}/app/benchmark/app_benchmark_pi_spigot
    ${PATH_APP}/app/benchmark/app_benchmark_wide_integer
    ${PATH_APP}/app/led/app_led
    ${PATH_APP}/mcal/${TARGET}/mcal_cpu
    ${PATH_APP}/mcal/${TARGET}/mcal_eep
    ${PATH_APP}/mcal/${TARGET}/mcal_gpt
    ${PATH_APP}/mcal/${TARGET}/mcal_irq
    ${PATH_APP}/mcal/${TARGET}/mcal_led
    ${PATH_APP}/mcal/${TARGET}/mcal_osc
    ${PATH_APP}/mcal/${TARGET}/mcal_pwm
    ${PATH_APP}/mcal/${TARGET}/mcal_port
    ${PATH_APP}/mcal/${TARGET}/mcal_spi
    ${PATH_APP}/mcal/${TARGET}/mcal_wdg
    ${PATH_APP}/mcal/mcal
    ${PATH_APP}/os/os
    ${PATH_APP}/os/os_task_control_block
    ${PATH_APP}/sys/idle/sys_idle
    ${PATH_APP}/sys/mon/sys_mon
    ${PATH_APP}/sys/start/sys_start
)

add_executable(ref_app
    ${app_src}
    ${FILES_TARGET}
)

target_include_directories(ref_app PUBLIC
    ${TARGET_INCLUDES} 
    ${PATH_APP}
    ${PATH_APP}/mcal/${TARGET}
)

set_target_properties(ref_app PROPERTIES OUTPUT_NAME ${APP})

# ------------------------------------------------------------------------------
# post build steps
# ------------------------------------------------------------------------------
if("${CMAKE_EXECUTABLE_SUFFIX}" STREQUAL ".exe")

    if(NOT MSVC)
        install(FILES
            ${CMAKE_BINARY_DIR}/${APP}${CMAKE_EXECUTABLE_SUFFIX}
            DESTINATION
            ${CMAKE_CURRENT_SOURCE_DIR}/bin/${APP}-${NAME}-${CMAKE_BUILD_TYPE}
        )
    else()
        install(FILES
            ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/${APP}${CMAKE_EXECUTABLE_SUFFIX}
            DESTINATION
            ${CMAKE_CURRENT_SOURCE_DIR}/bin/${APP}-${NAME}-${CMAKE_BUILD_TYPE}
        )
    endif()

elseif(("${CMAKE_EXECUTABLE_SUFFIX}" STREQUAL ".elf") OR ("${CMAKE_EXECUTABLE_SUFFIX}" STREQUAL ""))

    add_custom_command(TARGET ref_app POST_BUILD

        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}

        COMMENT "Generating Post Build Artifacts"

        # generate assembly listing
        COMMAND ${OBJDUMP} -h -S ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}.lss

        # parsing symbols with nm to generate: ${APP}_nm.txt
        COMMAND ${NM} --numeric-sort ${PARSE_SYMBOL_OPTIONS} ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}_nm.txt

        # demangling symbols with c++filt to generate: ${APP}_cppfilt.txt
        COMMAND ${NM} --numeric-sort ${PARSE_SYMBOL_OPTIONS} ${APP}${CMAKE_EXECUTABLE_SUFFIX} | ${CPPFILT} > ${APP}_cppfilt.txt

        # creating size summary table with size to generate: ${APP}_size.txt
        COMMAND ${SIZE} ${SIZE_OPTIONS} ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}_size.txt

        # parsing symbols with readelf to generate: ${APP}_readelf.txt
        COMMAND ${POSTBUILD_GEN_SYMBOL_LISTING}

        # creating hex module: ${APP}.hex
        COMMAND ${POSTBUILD_GEN_HEX}

        # creating hex module: ${APP}.bin
        COMMAND ${POSTBUILD_GEN_BIN}
    )

    install(FILES

        ${CMAKE_BINARY_DIR}/${APP}${CMAKE_EXECUTABLE_SUFFIX}
        ${CMAKE_BINARY_DIR}/${APP}.lss
        ${CMAKE_BINARY_DIR}/${APP}_cppfilt.txt
        ${CMAKE_BINARY_DIR}/${APP}_size.txt
        ${MAP_FILE}
        ${SYMBOL_LISTING_FILE}
        ${HEX_FILE}
        ${BIN_FILE}

        DESTINATION
        
        ${CMAKE_CURRENT_SOURCE_DIR}/bin/${APP}-${NAME}-${CMAKE_BUILD_TYPE}
    )

endif()
