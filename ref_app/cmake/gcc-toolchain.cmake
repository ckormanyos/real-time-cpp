##############################################################################
#  Copyright Christopher Kormanyos 2021 - 2025.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)

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

IF(NOT TRIPLE)
    set(GCC_TOOLCHAIN_PREFIX "")
else()
    set(GCC_TOOLCHAIN_PREFIX ${TRIPLE}-)
endif()

message(STATUS "Triple ................. ${TRIPLE}")

STRING(REGEX REPLACE "^([a-zA-Z0-9]+).*" "\\1" target_arch "${TRIPLE}")
message(STATUS "Triple Arch ............ ${target_arch}")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ${target_arch})

if(NOT APP)
    set(APP ref_app)
endif()
if(NOT NAME)
    set(NAME ${TARGET})
endif()

if(MINGW OR CYGWIN OR WIN32)
    set(UTIL_SEARCH_CMD where)
elseif(UNIX OR APPLE)
    set(UTIL_SEARCH_CMD which)
endif()

execute_process(
  COMMAND ${UTIL_SEARCH_CMD} ${GCC_TOOLCHAIN_PREFIX}g++
  OUTPUT_VARIABLE BINUTILS_PATH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
get_filename_component(TOOLCHAIN_PATH ${BINUTILS_PATH} DIRECTORY)

message(STATUS "Toolchain Path ......... ${TOOLCHAIN_PATH}")

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_AR ${GCC_TOOLCHAIN_PREFIX}ar)
set(CMAKE_ASM_COMPILER ${GCC_TOOLCHAIN_PREFIX}gcc)
set(CMAKE_CC_COMPILER ${GCC_TOOLCHAIN_PREFIX}gcc)

if("${GCC_TOOLCHAIN_PREFIX}" STREQUAL "x86_64-w64-mingw32" AND "${TARGET}" STREQUAL "host")
    set(CMAKE_CXX_COMPILER ${GCC_TOOLCHAIN_PREFIX}g++-posix)
else()
    set(CMAKE_CXX_COMPILER ${GCC_TOOLCHAIN_PREFIX}g++)
endif()


set(CPPFILT ${GCC_TOOLCHAIN_PREFIX}c++filt)
set(NM ${GCC_TOOLCHAIN_PREFIX}nm)
set(OBJDUMP ${GCC_TOOLCHAIN_PREFIX}objdump)
set(OBJCOPY ${GCC_TOOLCHAIN_PREFIX}objcopy)
set(READELF ${GCC_TOOLCHAIN_PREFIX}readelf)
set(SIZE ${GCC_TOOLCHAIN_PREFIX}size)
set(CMAKE_EXECUTABLE_SUFFIX .elf)

set(GCCFLAGS
    -g
    -Wall
    -Wextra
    -Wpedantic
    -Wmain
    -Wundef
    -Wsign-conversion
    -Wunused-parameter
    -Wuninitialized
    -Wmissing-declarations
    -Wshadow
    -Wunreachable-code
    -Wswitch-default
    -Wswitch-enum
    -Wcast-align
    -Wmissing-include-dirs
    -Winit-self
    -Wfloat-equal
    -Wdouble-promotion
    -Wno-comment
    -gdwarf-2
    -fno-exceptions
    -ffunction-sections
    -fdata-sections
)

set(_CFLAGS ${GCCFLAGS}
    -Wunsuffixed-float-constants
    -x c
    -std=c99
)

set(_CXXFLAGS ${GCCFLAGS}
    -x c++
    -fno-rtti
    -fno-use-cxa-atexit
    -fno-nonansi-builtins
    -fno-threadsafe-statics
    -fno-enforce-eh-specs
    -ftemplate-depth=32
    -Wzero-as-null-pointer-constant
)

set(_AFLAGS ${GCCFLAGS}
    -x assembler
)

set(_LDFLAGS ${GCCFLAGS}
    -x none
    -Wl,--gc-sections
    -Wl,--print-memory-usage
    -Wl,-Map,${APP}.map
)

set(PARSE_SYMBOL_OPTIONS --print-size)

# Postbuild binutil commands
set(POSTBUILD_GEN_SYMBOL_LISTING ${READELF} --syms ${APP}${CMAKE_EXECUTABLE_SUFFIX} > ${APP}_readelf.txt)
set(POSTBUILD_GEN_HEX ${OBJCOPY} -O ihex ${APP}${CMAKE_EXECUTABLE_SUFFIX} ${APP}.hex)
set(POSTBUILD_GEN_S19 ${OBJCOPY} -O srec --srec-forceS3 --srec-len=16 ${APP}${CMAKE_EXECUTABLE_SUFFIX} ${APP}.s19)
set(POSTBUILD_GEN_BIN ${OBJCOPY} -S -O binary ${APP}${CMAKE_EXECUTABLE_SUFFIX} ${APP}.bin)

# Install Files
set(MAP_FILE ${CMAKE_BINARY_DIR}/${APP}.map)
set(SYMBOL_LISTING_FILE ${CMAKE_BINARY_DIR}/${APP}_readelf.txt)
set(HEX_FILE ${CMAKE_BINARY_DIR}/${APP}.hex)
set(BIN_FILE ${CMAKE_BINARY_DIR}/${APP}.bin)

# remove list item delimeter
string(REPLACE ";" " " CFLAGS "${_CFLAGS}")
string(REPLACE ";" " " CXXFLAGS "${_CXXFLAGS}")
string(REPLACE ";" " " AFLAGS "${_AFLAGS}")
string(REPLACE ";" " " LDFLAGS "${_LDFLAGS}")
