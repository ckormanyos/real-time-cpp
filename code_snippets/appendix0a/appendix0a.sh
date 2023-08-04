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

$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_01-001_static_cast.cpp             -o ./bin/appendix0a_01-001_static_cast.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_01-002_reinterpret_cast.cpp        -o ./bin/appendix0a_01-002_reinterpret_cast.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_02-001_uniform_initialization.cpp  -o ./bin/appendix0a_02-001_uniform_initialization.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_02-002_uniform_initialization.cpp  -o ./bin/appendix0a_02-002_uniform_initialization.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_02-003_uniform_initialization.cpp  -o ./bin/appendix0a_02-003_uniform_initialization.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_02-004_uniform_initialization.cpp  -o ./bin/appendix0a_02-004_uniform_initialization.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_02-005_uniform_initialization.cpp  -o ./bin/appendix0a_02-005_uniform_initialization.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_03-001_function_overloading.cpp    -o ./bin/appendix0a_03-001_function_overloading.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_04-001_static_assert.cpp           -o ./bin/appendix0a_04-001_static_assert.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_04-002_static_assert.cpp           -o ./bin/appendix0a_04-002_static_assert.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_04-003_static_assert.cpp           -o ./bin/appendix0a_04-003_static_assert.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_05-001_numeric_limits.cpp          -o ./bin/appendix0a_05-001_numeric_limits.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_05-002_numeric_limits.cpp          -o ./bin/appendix0a_05-002_numeric_limits.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_06-001_stl_containers.cpp          -o ./bin/appendix0a_06-001_stl_containers.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_07-001_stl_iterators.cpp           -o ./bin/appendix0a_07-001_stl_iterators.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_07-002_stl_iterators.cpp           -o ./bin/appendix0a_07-002_stl_iterators.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_07-003_stl_iterators.cpp           -o ./bin/appendix0a_07-003_stl_iterators.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_08-001_stl_algorithms.cpp          -o ./bin/appendix0a_08-001_stl_algorithms.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_08-002_stl_algorithms.cpp          -o ./bin/appendix0a_08-002_stl_algorithms.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_08-003_stl_algorithms.cpp          -o ./bin/appendix0a_08-003_stl_algorithms.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_08-004_stl_algorithms.cpp          -o ./bin/appendix0a_08-004_stl_algorithms.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_08-005_stl_algorithms.cpp          -o ./bin/appendix0a_08-005_stl_algorithms.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_09-001_lambda_expressions.cpp      -o ./bin/appendix0a_09-001_lambda_expressions.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_10-001_initializer_list.cpp        -o ./bin/appendix0a_10-001_initializer_list.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_10-002_initializer_list.cpp        -o ./bin/appendix0a_10-002_initializer_list.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_11-001_type_inference.cpp          -o ./bin/appendix0a_11-001_type_inference.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_11-002_type_inference.cpp          -o ./bin/appendix0a_11-002_type_inference.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_11-003_decltype.cpp                -o ./bin/appendix0a_11-003_decltype.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_12-001_range_based_for.cpp         -o ./bin/appendix0a_12-001_range_based_for.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_13-001_tuple_basics.cpp            -o ./bin/appendix0a_13-001_tuple_basics.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_13-002_tuple_assign.cpp            -o ./bin/appendix0a_13-002_tuple_assign.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_13-003_tuple_comparison.cpp        -o ./bin/appendix0a_13-003_tuple_comparison.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_13-004_tuple_get_by_type.cpp       -o ./bin/appendix0a_13-004_tuple_get_by_type.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_14-001_regex_basics.cpp            -o ./bin/appendix0a_14-001_regex_basics.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_15-001_type_traits.cpp             -o ./bin/appendix0a_15-001_type_traits.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_15-002_type_traits.cpp             -o ./bin/appendix0a_15-002_type_traits.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_15-003_type_traits.cpp             -o ./bin/appendix0a_15-003_type_traits.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_15-004_type_traits.cpp             -o ./bin/appendix0a_15-004_type_traits.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_16-001_any_basics.cpp              -o ./bin/appendix0a_16-001_any_basics.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_16-002_any_basics.cpp              -o ./bin/appendix0a_16-002_any_basics.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_16-003_any_and_stl_container.cpp   -o ./bin/appendix0a_16-003_any_and_stl_container.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./appendix0a_17-001_structured_binding.cpp      -o ./bin/appendix0a_17-001_structured_binding.exe

ls -la \
./bin/appendix0a_01-001_static_cast.exe               \
./bin/appendix0a_01-002_reinterpret_cast.exe          \
./bin/appendix0a_02-001_uniform_initialization.exe    \
./bin/appendix0a_02-002_uniform_initialization.exe    \
./bin/appendix0a_02-003_uniform_initialization.exe    \
./bin/appendix0a_02-004_uniform_initialization.exe    \
./bin/appendix0a_02-005_uniform_initialization.exe    \
./bin/appendix0a_03-001_function_overloading.exe      \
./bin/appendix0a_04-001_static_assert.exe             \
./bin/appendix0a_04-002_static_assert.exe             \
./bin/appendix0a_04-003_static_assert.exe             \
./bin/appendix0a_05-001_numeric_limits.exe            \
./bin/appendix0a_05-002_numeric_limits.exe            \
./bin/appendix0a_06-001_stl_containers.exe            \
./bin/appendix0a_07-001_stl_iterators.exe             \
./bin/appendix0a_07-002_stl_iterators.exe             \
./bin/appendix0a_07-003_stl_iterators.exe             \
./bin/appendix0a_08-001_stl_algorithms.exe            \
./bin/appendix0a_08-002_stl_algorithms.exe            \
./bin/appendix0a_08-003_stl_algorithms.exe            \
./bin/appendix0a_08-004_stl_algorithms.exe            \
./bin/appendix0a_08-005_stl_algorithms.exe            \
./bin/appendix0a_09-001_lambda_expressions.exe        \
./bin/appendix0a_10-001_initializer_list.exe          \
./bin/appendix0a_10-002_initializer_list.exe          \
./bin/appendix0a_11-001_type_inference.exe            \
./bin/appendix0a_11-002_type_inference.exe            \
./bin/appendix0a_11-003_decltype.exe                  \
./bin/appendix0a_12-001_range_based_for.exe           \
./bin/appendix0a_13-001_tuple_basics.exe              \
./bin/appendix0a_13-002_tuple_assign.exe              \
./bin/appendix0a_13-003_tuple_comparison.exe          \
./bin/appendix0a_13-004_tuple_get_by_type.exe         \
./bin/appendix0a_14-001_regex_basics.exe              \
./bin/appendix0a_15-001_type_traits.exe               \
./bin/appendix0a_15-002_type_traits.exe               \
./bin/appendix0a_15-003_type_traits.exe               \
./bin/appendix0a_15-004_type_traits.exe               \
./bin/appendix0a_16-001_any_basics.exe                \
./bin/appendix0a_16-002_any_basics.exe                \
./bin/appendix0a_16-003_any_and_stl_container.exe     \
./bin/appendix0a_17-001_structured_binding.exe

result_ls=$?

echo "result_ls: "  "$result_ls"

exit $result_ls
