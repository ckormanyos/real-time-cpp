#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2023 - 2025.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#
#  cd /mnt/c/Users/ckorm/Documents/Ks/uC_Software/Boards/real-time-cpp/code_snippets/chapter03
#  ./chapter03.sh g++ c++20

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

echo build snippets with GCC=${GCC} STD=${STD}

${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_01-001_declare_locals.cpp           -o ./bin/chapter03_01-001_declare_locals.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_02-001_fixed_size_integer.cpp       -o ./bin/chapter03_02-001_fixed_size_integer.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_02-002_prime_number.cpp             -o ./bin/chapter03_02-002_prime_number.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_02-002a_explore_prime_numbers.cpp   -o ./bin/chapter03_02-002a_explore_prime_numbers.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_03-001_bool_type.cpp                -o ./bin/chapter03_03-001_bool_type.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_04-001_namespaces.cpp               -o ./bin/chapter03_04-001_namespaces.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_04-002_anonymous_namespace.cpp      -o ./bin/chapter03_04-002_anonymous_namespace.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_04-003_nested_namespace.cpp         -o ./bin/chapter03_04-003_nested_namespace.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_05-001_basic_classes.cpp            -o ./bin/chapter03_05-001_basic_classes.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_06-001_basic_templates_add.cpp      -o ./bin/chapter03_06-001_basic_templates_add.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_06-002_basic_templates_xy_point.cpp -o ./bin/chapter03_06-002_basic_templates_xy_point.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_07-001_nullptr.cpp                  -o ./bin/chapter03_07-001_nullptr.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_08-001_constexpr.cpp                -o ./bin/chapter03_08-001_constexpr.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_08-002_constexpr_more.cpp           -o ./bin/chapter03_08-002_constexpr_more.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_08-003_constexpr_pown.cpp           -o ./bin/chapter03_08-003_constexpr_pown.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_09-001_static_assert.cpp            -o ./bin/chapter03_09-001_static_assert.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_10-001_limits.cpp                   -o ./bin/chapter03_10-001_limits.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_11-001_array.cpp                    -o ./bin/chapter03_11-001_array.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_12-001_basic_stl.cpp                -o ./bin/chapter03_12-001_basic_stl.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_13-001_basic_stl_numeric.cpp        -o ./bin/chapter03_13-001_basic_stl_numeric.exe
if [[ "${GCC}" == "g++" ]]; then
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_14-001_atomic_operations.cpp        -o ./bin/chapter03_14-001_atomic_operations.exe
fi
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_15-001_digit_separators.cpp         -o ./bin/chapter03_15-001_digit_separators.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_15-002_digit_separators.cpp         -o ./bin/chapter03_15-002_digit_separators.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_16-001_binary_literals.cpp          -o ./bin/chapter03_16-001_binary_literals.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_16-002_binary_literals.cpp          -o ./bin/chapter03_16-002_binary_literals.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_17-001_user_defined_literals.cpp    -o ./bin/chapter03_17-001_user_defined_literals.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_17-002_user_defined_literals.cpp    -o ./bin/chapter03_17-002_user_defined_literals.exe
if [[ "$GCC" == "g++" ]]; then
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_17-003_user_defined_literals.cpp    -o ./bin/chapter03_17-003_user_defined_literals.exe
fi
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_17-004_user_defined_literals.cpp    -o ./bin/chapter03_17-004_user_defined_literals.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_17-005_user_defined_literals.cpp    -o ./bin/chapter03_17-005_user_defined_literals.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_17-006_user_defined_literals.cpp    -o ./bin/chapter03_17-006_user_defined_literals.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_18-001_alignment.cpp                -o ./bin/chapter03_18-001_alignment.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_18-002_alignment.cpp                -o ./bin/chapter03_18-002_alignment.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_19-001_final.cpp                    -o ./bin/chapter03_19-001_final.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_19-002_final.cpp                    -o ./bin/chapter03_19-002_final.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_20-001_alias.cpp                    -o ./bin/chapter03_20-001_alias.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_20-002_alias.cpp                    -o ./bin/chapter03_20-002_alias.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_21-001_span.cpp                     -o ./bin/chapter03_21-001_span.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_22-001_mersenne_twister_19937.cpp   -o ./bin/chapter03_22-001_mersenne_twister_19937.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_22-002_test_random_engines.cpp      -o ./bin/chapter03_22-002_test_random_engines.exe
if [[ "${GCC}" == "g++" ]]; then
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_23-001_expected_div_int.cpp         -o ./bin/chapter03_23-001_expected_div_int.exe
${GCC} -std=${STD} -Wall -Wextra -Wpedantic -Werror -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter03_23-002_expected_div_integral.cpp    -o ./bin/chapter03_23-002_expected_div_integral.exe
fi

if [[ "${GCC}" == "g++" ]]; then
ls -la \
./bin/chapter03_01-001_declare_locals.exe             \
./bin/chapter03_02-001_fixed_size_integer.exe         \
./bin/chapter03_02-002_prime_number.exe               \
./bin/chapter03_02-002a_explore_prime_numbers.exe     \
./bin/chapter03_03-001_bool_type.exe                  \
./bin/chapter03_04-001_namespaces.exe                 \
./bin/chapter03_04-002_anonymous_namespace.exe        \
./bin/chapter03_04-003_nested_namespace.exe           \
./bin/chapter03_05-001_basic_classes.exe              \
./bin/chapter03_06-001_basic_templates_add.exe        \
./bin/chapter03_06-002_basic_templates_xy_point.exe   \
./bin/chapter03_07-001_nullptr.exe                    \
./bin/chapter03_08-001_constexpr.exe                  \
./bin/chapter03_08-002_constexpr_more.exe             \
./bin/chapter03_08-003_constexpr_pown.exe             \
./bin/chapter03_09-001_static_assert.exe              \
./bin/chapter03_10-001_limits.exe                     \
./bin/chapter03_11-001_array.exe                      \
./bin/chapter03_12-001_basic_stl.exe                  \
./bin/chapter03_13-001_basic_stl_numeric.exe          \
./bin/chapter03_14-001_atomic_operations.exe          \
./bin/chapter03_15-001_digit_separators.exe           \
./bin/chapter03_15-002_digit_separators.exe           \
./bin/chapter03_16-001_binary_literals.exe            \
./bin/chapter03_16-002_binary_literals.exe            \
./bin/chapter03_17-001_user_defined_literals.exe      \
./bin/chapter03_17-002_user_defined_literals.exe      \
./bin/chapter03_17-003_user_defined_literals.exe      \
./bin/chapter03_17-004_user_defined_literals.exe      \
./bin/chapter03_17-005_user_defined_literals.exe      \
./bin/chapter03_17-006_user_defined_literals.exe      \
./bin/chapter03_18-001_alignment.exe                  \
./bin/chapter03_18-002_alignment.exe                  \
./bin/chapter03_19-001_final.exe                      \
./bin/chapter03_19-002_final.exe                      \
./bin/chapter03_20-001_alias.exe                      \
./bin/chapter03_20-002_alias.exe                      \
./bin/chapter03_21-001_span.exe                       \
./bin/chapter03_22-001_mersenne_twister_19937.exe     \
./bin/chapter03_22-002_test_random_engines.exe        \
./bin/chapter03_23-001_expected_div_int.exe           \
./bin/chapter03_23-002_expected_div_integral.exe
else
ls -la \
./bin/chapter03_01-001_declare_locals.exe             \
./bin/chapter03_02-001_fixed_size_integer.exe         \
./bin/chapter03_02-002_prime_number.exe               \
./bin/chapter03_02-002a_explore_prime_numbers.exe     \
./bin/chapter03_03-001_bool_type.exe                  \
./bin/chapter03_04-001_namespaces.exe                 \
./bin/chapter03_04-002_anonymous_namespace.exe        \
./bin/chapter03_04-003_nested_namespace.exe           \
./bin/chapter03_05-001_basic_classes.exe              \
./bin/chapter03_06-001_basic_templates_add.exe        \
./bin/chapter03_06-002_basic_templates_xy_point.exe   \
./bin/chapter03_07-001_nullptr.exe                    \
./bin/chapter03_08-001_constexpr.exe                  \
./bin/chapter03_08-002_constexpr_more.exe             \
./bin/chapter03_08-003_constexpr_pown.exe             \
./bin/chapter03_09-001_static_assert.exe              \
./bin/chapter03_10-001_limits.exe                     \
./bin/chapter03_11-001_array.exe                      \
./bin/chapter03_12-001_basic_stl.exe                  \
./bin/chapter03_13-001_basic_stl_numeric.exe          \
./bin/chapter03_15-001_digit_separators.exe           \
./bin/chapter03_15-002_digit_separators.exe           \
./bin/chapter03_16-001_binary_literals.exe            \
./bin/chapter03_16-002_binary_literals.exe            \
./bin/chapter03_17-001_user_defined_literals.exe      \
./bin/chapter03_17-002_user_defined_literals.exe      \
./bin/chapter03_17-004_user_defined_literals.exe      \
./bin/chapter03_17-005_user_defined_literals.exe      \
./bin/chapter03_17-006_user_defined_literals.exe      \
./bin/chapter03_18-001_alignment.exe                  \
./bin/chapter03_18-002_alignment.exe                  \
./bin/chapter03_19-001_final.exe                      \
./bin/chapter03_19-002_final.exe                      \
./bin/chapter03_20-001_alias.exe                      \
./bin/chapter03_20-002_alias.exe                      \
./bin/chapter03_21-001_span.exe                       \
./bin/chapter03_22-001_mersenne_twister_19937.exe     \
./bin/chapter03_22-002_test_random_engines.exe
fi

result_ls=$?

echo "result_ls: "  "${result_ls}"

exit ${result_ls}
