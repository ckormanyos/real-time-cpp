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

$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_01-001_sinc_function.cpp         -o ./bin/chapter12_01-001_sinc_function.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_04-001_ellint_1.cpp              -o ./bin/chapter12_04-001_ellint_1.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_04-001_tgamma.cpp                -o ./bin/chapter12_04-001_tgamma.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_04-002_euler_gamma_approx.cpp    -o ./bin/chapter12_04-002_euler_gamma_approx.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_05-001_complex.cpp               -o ./bin/chapter12_05-001_complex.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_05-002_complex_sinc_function.cpp -o ./bin/chapter12_05-002_complex_sinc_function.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_06-001_constexpr_sine.cpp        -o ./bin/chapter12_06-001_constexpr_sine.exe
$GCC -std=c++11 -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_06-002_constexpr_exp.cpp         -o ./bin/chapter12_06-002_constexpr_exp.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_07-001_area_of_a_circle.cpp      -o ./bin/chapter12_07-001_area_of_a_circle.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter12_07-002_derivative.cpp            -o ./bin/chapter12_07-002_derivative.exe

ls -la \
./bin/chapter12_01-001_sinc_function.exe            \
./bin/chapter12_04-001_ellint_1.exe                 \
./bin/chapter12_04-001_tgamma.exe                   \
./bin/chapter12_04-002_euler_gamma_approx.exe       \
./bin/chapter12_05-001_complex.exe                  \
./bin/chapter12_05-002_complex_sinc_function.exe    \
./bin/chapter12_06-001_constexpr_sine.exe           \
./bin/chapter12_06-002_constexpr_exp.exe            \
./bin/chapter12_07-001_area_of_a_circle.exe         \
./bin/chapter12_07-002_derivative.exe

result_ls=$?

echo "result_ls: "  "$result_ls"

exit $result_ls
