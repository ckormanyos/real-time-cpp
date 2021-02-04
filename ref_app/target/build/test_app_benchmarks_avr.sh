#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2021.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# For local test:
# ./tools/Util/MinGW/msys/1.0/local/gcc-7.3.0-avr/bin/avr-g++

mkdir -p bin

rm -f ./bin/*.*

echo run benchmarks with avr-g++ and language standard c++11

avr-g++ -std=c++11 -Wall -Wextra -pedantic -Wmain -Wundef -Wsign-conversion -Wunused-parameter -Wuninitialized -Wmissing-declarations -Wshadow -Wunreachable-code -Wswitch-default -Wswitch-enum -Wcast-align -Wmissing-include-dirs -Winit-self -Wfloat-equal -Wdouble-promotion -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_COMPLEX -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_complex.cpp ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_complex.map -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_complex.elf
avr-g++ -std=c++11 -Wall -Wextra -pedantic -Wmain -Wundef -Wsign-conversion -Wunused-parameter -Wuninitialized -Wmissing-declarations -Wshadow -Wunreachable-code -Wswitch-default -Wswitch-enum -Wcast-align -Wmissing-include-dirs -Winit-self -Wfloat-equal -Wdouble-promotion -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_CRC     -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_crc.cpp     ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_crc.map     -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_crc.elf

ls -la ./bin/app_benchmark_complex.elf ./bin/app_benchmark_complex.map
result_ls_complex=$?

ls -la ./bin/app_benchmark_crc.elf ./bin/app_benchmark_crc.map
app_benchmark_crc=$?

echo "result_ls_complex           : "  "$result_ls_complex"
echo "result_ls_crc               : "  "$result_ls_crc"

result_total=$((result_ls_complex+result_ls_crc))

echo "result_total                 : "  "$result_total"

exit $result_total
