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

message(STATUS "Generator .............. ${CMAKE_GENERATOR}")
message(STATUS "Build Type ............. ${CMAKE_BUILD_TYPE}")

include (ExternalProject)

set(TARGET_CFG_LIST
    # NAME | TARGET | TRIPLE
    sitara|am335x|arm-none-eabi
    stm32f100|stm32f100|arm-none-eabi
    stm32f407|stm32f407|arm-none-eabi
    stm32f429|stm32f429|arm-none-eabi
    stm32f446|stm32f446|arm-none-eabi
    stm32h7a3|stm32h7a3|arm-none-eabi
    stm32l152|stm32l152|arm-none-eabi
    rpi3|bcm2835_raspi_b|arm-none-eabi
    nxp|lpc11c24|arm-none-eabi
    nxp|nxp_imxrt1062|arm-none-eabi

    atmega2560|atmega2560|avr
    atmega328p|avr|avr

    riscvfe310|riscvfe310|riscv64-unknown-elf

    rl78|rl78|rl78-elf

    rx63n|rx63n|rx-elf

    xtensa32|xtensa32|xtensa-esp32-elf

    mingw32|host|x86_64-w64-mingw32
)

if(UNIX)
    list(APPEND TARGET_CFG_LIST linux|host|x86_64-linux-gnu)
endif()

macro(add_ext_proj name target triple)

    ExternalProject_Add(${name}
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ref_app
        BUILD_IN_SOURCE 0
        CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DNAME=${name}
            -DTRIPLE=${triple}
            -DTARGET=${target}
            -DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/ref_app/cmake/gcc-toolchain.cmake
    )

endmacro(add_ext_proj)

foreach(cfg ${TARGET_CFG_LIST})

    string(REPLACE "|" ";" TGT_CFG "${cfg}")

    list(GET TGT_CFG 0 PROJ_NAME)
    list(GET TGT_CFG 1 TARGET)
    list(GET TGT_CFG 2 TRIPLE)

    add_ext_proj(${PROJ_NAME} ${TARGET} ${TRIPLE})

endforeach(cfg)
