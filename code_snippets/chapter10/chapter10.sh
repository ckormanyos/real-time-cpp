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
    STD=c++20
fi

mkdir -p bin

rm -f ./bin/*.*

echo build snippets with GCC=$GCC STD=$STD

$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter10_08-000_pi_spigot_single.cpp -o ./bin/chapter10_08-000_pi_spigot_single.exe
if [[ "$GCC" == "g++" ]]; then
$GCC -std=$STD -Wall -Wextra -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum -I../../../boost-root ./chapter10_08-001_pi_millions_with_boost.cpp -lgmp -o ./bin/chapter10_08-001_pi_millions_with_boost.exe
fi

if [[ "$GCC" == "g++" ]]; then
ls -la \
./bin/chapter10_08-000_pi_spigot_single.exe              \
./bin/chapter10_08-001_pi_millions_with_boost.exe
else
ls -la \
./bin/chapter10_08-000_pi_spigot_single.exe
fi

result_ls=$?

echo "result_ls: "  "$result_ls"

exit $result_ls
