#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2023 -2025.
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

$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter01_01-001_led_program.cpp   -o ./bin/chapter01_01-001_led_program.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter01_07-001_namespace.cpp     -o ./bin/chapter01_07-001_namespace.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter01_07-002_namespace.cpp     -o ./bin/chapter01_07-002_namespace.exe

ls -la \
./bin/chapter01_01-001_led_program.exe \
./bin/chapter01_07-001_namespace.exe \
./bin/chapter01_07-002_namespace.exe

result_ls=$?

echo "result_ls: "  "$result_ls"

exit $result_ls
