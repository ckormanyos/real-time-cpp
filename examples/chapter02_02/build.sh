#!/usr/bin/env bash
#
# Copyright Christopher Kormanyos 2014 - 2025.
# Distributed under the Boost Software License,
# Version 1.0. (See accompanying file LICENSE_1_0.txt
# or copy at http://www.boost.org/LICENSE_1_0.txt)
#


#
# Usage:
#
# If command
#     /usr/bin/avr-g++
# installed, e.g. via command   apt-get install gcc-avr avr-libc
# then:
# ./build.sh
#
# Otherwise for custom installations
# ./build.sh directory_of_gcc_bin avr
# For example,
# ./build.sh /usr/bin avr
#
# Usage example A (from *nix shell)
# cd /usr/local/real-time-cpp/examples/chapter02_02
# ./build.sh /usr/local/real-time-cpp/examples/chapter02_02/tools/Util/MinGW/msys/1.0/local/gcc-9.2.0-avr/bin avr

# Usage example B (from Win* shell such as in Git for Win*)
# cd C:/Users/User/Documents/Ks/uC_Software/Boards/real-time-cpp/examples/chapter02_02
# ./build.sh C:/Users/User/Documents/Ks/uC_Software/Boards/real-time-cpp/examples/chapter02_02/tools/Util/MinGW/msys/1.0/local/gcc-9.2.0-avr/bin avr

if [[ $# == 0 ]]; then                   ##  $# is the number of arguments
    if [[ -n "$(which avr-g++)" ]]; then ## -n tests if string is not empty
        TOOL_PATH="$(dirname $(which avr-g++))"
        TOOL_PREFIX=avr
    else
        echo
        echo "Try:  apt-get install gcc-avr avr-libc"
        echo "Then: ./build.sh"
        echo "Otherwise, if you're using a custom avr, use: ./build.sh /directory/to/gcc_avr_bin Prefix"
        echo "                                              (such that /directory/to/gcc_avr_bin/Prefix-g++ is the name"
        echo "                                                   of the c++ compiler)"
        exit 1
    fi
else
    TOOL_PATH="$1"
    TOOL_PREFIX="$2"
fi

echo
echo "Building with        : build.sh"
echo "Using tool path      : $TOOL_PATH"
echo "Using tool prefix    : $TOOL_PREFIX"
echo "Remove bin directory : bin/"
rm -rf bin/
echo "Create bin directory : bin/"
mkdir -p bin

echo
echo "Assemble : crt0.s  to bin/crt0.o"
$TOOL_PATH/$TOOL_PREFIX-g++ -mmcu=atmega328p -fsigned-char -x assembler crt0.s -c -o bin/crt0.o

echo "Compile  : led.cpp to bin/led.o"
$TOOL_PATH/$TOOL_PREFIX-g++ -mmcu=atmega328p -fsigned-char -O2 -std=c++0x -I. -c led.cpp -o bin/led.o

echo "Link     : objects to bin/led.elf"
$TOOL_PATH/$TOOL_PREFIX-g++ -mmcu=atmega328p -nostartfiles -nostdlib -Wl,-Tavr.ld,-Map,bin/led.map bin/led.o bin/crt0.o -o bin/led.elf

echo
echo "Extract  : executalbe hex file : from bin/led.elf"
$TOOL_PATH/$TOOL_PREFIX-objcopy -O ihex bin/led.elf bin/led.hex

echo "Extract  : assembly list file  : from bin/led.elf"
$TOOL_PATH/$TOOL_PREFIX-objdump --disassemble bin/led.elf > bin/led.lss

echo "Extract  : size information    : from bin/led.elf"
$TOOL_PATH/$TOOL_PREFIX-size -A -t bin/led.elf > bin/led_size.txt

echo "Extract  : name information    : from bin/led.elf"
$TOOL_PATH/$TOOL_PREFIX-nm --numeric-sort --print-size bin/led.elf > bin/led_nm.txt

echo "Extract  : demangled names     : from bin/led.elf"
$TOOL_PATH/$TOOL_PREFIX-nm --numeric-sort --print-size bin/led.elf | $TOOL_PATH/$TOOL_PREFIX-c++filt > bin/led_cppfilt.txt
