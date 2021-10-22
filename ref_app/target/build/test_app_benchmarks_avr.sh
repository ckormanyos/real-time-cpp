#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2021.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

# For local test:
# ./tools/Util/MinGW/msys/1.0/local/gcc-7.3.0-avr/bin/avr-g++

if [[ "$1" != "" ]]; then
    STD="$1"
else
    STD=c++11
fi

wflags="-Wextra -pedantic -Wmain -Wundef -Wsign-conversion -Wunused-parameter -Wuninitialized -Wmissing-declarations -Wshadow -Wunreachable-code -Wswitch-default -Wswitch-enum -Wcast-align -Wmissing-include-dirs -Winit-self -Wfloat-equal -Wdouble-promotion"

mkdir -p bin

rm -f ./bin/*.*

echo run benchmarks with avr-g++ and language standard $STD

avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_COMPLEX            -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_complex.cpp            ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_complex.map            -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_complex.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_CRC                -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_crc.cpp                ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_crc.map                -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_crc.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FAST_MATH          -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_fast_math.cpp          ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_fast_math.map          -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_fast_math.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FILTER             -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_filter.cpp             ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_filter.map             -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_filter.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FIXED_POINT        -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_fixed_point.cpp        ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_fixed_point.map        -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_fixed_point.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FLOAT              -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_float.cpp              ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_float.map              -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_float.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_HASH               -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_hash.cpp               ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_hash.map               -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_hash.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_NONE               -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_none.cpp               ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_none.map               -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_none.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_PI_AGM             -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_pi_agm.cpp             ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_pi_agm.map             -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_pi_agm.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_PI_SPIGOT          -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_pi_spigot.cpp          ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_pi_spigot.map          -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_pi_spigot.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE   -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_pi_spigot_single.cpp   ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_pi_spigot_single.map   -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_pi_spigot_single.elf
avr-g++ -std=$STD -Wall $wflags -Os -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1   -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_soft_double_h2f1.cpp   ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_soft_double_h2f1.map   -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_soft_double_h2f1.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_WIDE_DECIMAL       -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_wide_decimal.cpp       ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_wide_decimal.map       -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_wide_decimal.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_WIDE_INTEGER       -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_wide_integer.cpp       ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_wide_integer.map       -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_wide_integer.elf
avr-g++ -std=$STD -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=32 -Wzero-as-null-pointer-constant -mmcu=atmega328p -mrelax -I./src/util/STL -I./src/mcal/avr -I./src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_trapezoid_integral.cpp ./src/mcal/mcal_gcc_cxx_completion.cpp -nostdlib  -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_trapezoid_integral.map -T ./target/micros/avr/make/avr.ld -o ./bin/app_benchmark_trapezoid_integral.elf

ls -la ./bin/app_benchmark_complex.elf ./bin/app_benchmark_complex.map
result_ls_complex=$?

ls -la ./bin/app_benchmark_crc.elf ./bin/app_benchmark_crc.map
result_ls_crc=$?

ls -la ./bin/app_benchmark_fast_math.elf ./bin/app_benchmark_fast_math.map
result_ls_fast_math=$?

ls -la ./bin/app_benchmark_filter.elf ./bin/app_benchmark_filter.map
result_ls_filter=$?

ls -la ./bin/app_benchmark_fixed_point.elf ./bin/app_benchmark_fixed_point.map
result_ls_fixed_point=$?

ls -la ./bin/app_benchmark_float.elf ./bin/app_benchmark_float.map
result_ls_float=$?

ls -la ./bin/app_benchmark_hash.elf ./bin/app_benchmark_hash.map
result_ls_hash=$?

ls -la ./bin/app_benchmark_none.elf ./bin/app_benchmark_none.map
result_ls_none=$?

ls -la ./bin/app_benchmark_pi_agm.elf ./bin/app_benchmark_pi_agm.map
result_ls_pi_agm=$?

ls -la ./bin/app_benchmark_pi_spigot.elf ./bin/app_benchmark_pi_spigot.map
result_ls_pi_spigot=$?

ls -la ./bin/app_benchmark_pi_spigot_single.elf ./bin/app_benchmark_pi_spigot_single.map
result_ls_pi_spigot_single=$?

ls -la ./bin/app_benchmark_soft_double_h2f1.elf ./bin/app_benchmark_soft_double_h2f1.map
result_ls_soft_double_h2f1=$?

ls -la ./bin/app_benchmark_trapezoid_integral.elf ./bin/app_benchmark_trapezoid_integral.map
result_ls_trapezoid_integral=$?

ls -la ./bin/app_benchmark_wide_decimal.elf ./bin/app_benchmark_wide_decimal.map
result_ls_wide_decimal=$?

ls -la ./bin/app_benchmark_wide_integer.elf ./bin/app_benchmark_wide_integer.map
result_ls_wide_integer=$?

echo "result_ls_complex           : "  "$result_ls_complex"
echo "result_ls_crc               : "  "$result_ls_crc"
echo "result_ls_fast_math         : "  "$result_ls_fast_math"
echo "result_ls_filter            : "  "$result_ls_filter"
echo "result_ls_fixed_point       : "  "$result_ls_fixed_point"
echo "result_ls_float             : "  "$result_ls_float"
echo "result_ls_hash              : "  "$result_ls_hash"
echo "result_ls_none              : "  "$result_ls_none"
echo "result_ls_pi_agm            : "  "$result_ls_pi_agm"
echo "result_ls_soft_double_h2f1  : "  "$result_ls_soft_double_h2f1"
echo "result_ls_pi_spigot         : "  "$result_ls_pi_spigot"
echo "result_ls_pi_spigot_single  : "  "$result_ls_pi_spigot_single"
echo "result_ls_trapezoid_integral: "  "$result_ls_trapezoid_integral"
echo "result_ls_wide_decimal      : "  "$result_ls_wide_decimal"
echo "result_ls_wide_integer      : "  "$result_ls_wide_integer"

result_total=$((result_ls_complex+result_ls_crc+result_ls_fast_math+result_ls_filter+result_ls_fixed_point+result_ls_float+result_ls_hash+result_ls_none+result_ls_pi_agm+result_ls_pi_spigot+result_ls_pi_spigot_single+result_ls_soft_double_h2f1+result_ls_trapezoid_integral+result_ls_wide_decimal+result_ls_wide_integer))

echo "result_total                : "  "$result_total"

exit $result_total
