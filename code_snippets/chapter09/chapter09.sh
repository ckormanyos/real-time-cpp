#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2023.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

if [[ "$1" != "" ]]; then
    GCC="$1"
else
    GCC=g++
fi

if [[ "$2" != "" ]]; then
    STD="$2"
else
    STD=c++14
fi

mkdir -p bin

rm -f ./bin/*.*

echo build snippets with GCC=$GCC STD=$STD

$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter09_01-001_port_pin_template.cpp         -o ./bin/chapter09_01-001_port_pin_template.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter09_02-001_programming_interrupts.cpp    -o ./bin/chapter09_02-001_programming_interrupts.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter09_02-002_enable_timer_interrupt.cpp    -o ./bin/chapter09_02-002_enable_timer_interrupt.exe
if [[ "$GCC" == "g++" ]]; then
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter09_03-001_system_tick.cpp               -o ./bin/chapter09_03-001_system_tick.exe
fi

if [[ "$GCC" == "g++" ]]; then
ls -la \
./bin/chapter09_01-001_port_pin_template.exe              \
./bin/chapter09_02-001_programming_interrupts.exe         \
./bin/chapter09_02-002_enable_timer_interrupt.exe         \
./bin/chapter09_03-001_system_tick.exe
else
ls -la \
./bin/chapter09_01-001_port_pin_template.exe              \
./bin/chapter09_02-001_programming_interrupts.exe         \
./bin/chapter09_02-002_enable_timer_interrupt.exe
fi

result_ls=$?

echo "result_ls: "  "$result_ls"

exit $result_ls
