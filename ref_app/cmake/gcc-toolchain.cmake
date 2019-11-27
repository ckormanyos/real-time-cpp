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
  set(TRIPLE arm-none-eabi)
endif()

message(STATUS "Triple ................. ${TRIPLE}")

STRING(REGEX REPLACE "^([a-zA-Z0-9]+).*" "\\1" target_arch "${TRIPLE}")
message(STATUS "Triple Arch ............ ${target_arch}")

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ${target_arch})


if(MINGW OR CYGWIN OR WIN32)
    set(UTIL_SEARCH_CMD where)
elseif(UNIX OR APPLE)
    set(UTIL_SEARCH_CMD which)
endif()

execute_process(
  COMMAND ${UTIL_SEARCH_CMD} ${TRIPLE}-g++
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

set(CMAKE_AR ${TRIPLE}-ar)
set(CMAKE_ASM_COMPILER ${TRIPLE}-gcc)
set(CMAKE_CC_COMPILER ${TRIPLE}-gcc)

if("${TRIPLE}" STREQUAL "x86_64-w64-mingw32" AND "${TARGET}" STREQUAL "host")
    set(CMAKE_CXX_COMPILER ${TRIPLE}-g++-posix)
else()
    set(CMAKE_CXX_COMPILER ${TRIPLE}-g++)
endif()


set(CPPFILT ${TRIPLE}-c++filt)
set(NM ${TRIPLE}-nm)
set(OBJDUMP ${TRIPLE}-objdump)
set(OBJCOPY ${TRIPLE}-objcopy)
set(READELF ${TRIPLE}-readelf)
set(SIZE ${TRIPLE}-size)


set(GCCFLAGS
    -g
    -Wall
    -Wextra
    -pedantic
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

set(_CPPFLAGS ${GCCFLAGS}
    -x c++
    -fno-rtti
    -fstrict-enums
    -fno-use-cxa-atexit
    -fno-use-cxa-get-exception-ptr
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
)

# remove list item delimeter
string(REPLACE ";" " " CFLAGS "${_CFLAGS}")
string(REPLACE ";" " " CPPFLAGS "${_CPPFLAGS}")
string(REPLACE ";" " " AFLAGS "${_AFLAGS}")
string(REPLACE ";" " " LDFLAGS "${_LDFLAGS}")