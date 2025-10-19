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

$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_01-001_template_add.cpp                       -o ./bin/chapter05_01-001_template_add.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_01-002_template_add2.cpp                      -o ./bin/chapter05_01-002_template_add2.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_02-001_make_word.cpp                          -o ./bin/chapter05_02-001_make_word.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_02-002_make_large.cpp                         -o ./bin/chapter05_02-002_make_large.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_03-001_communication_nontemplate.cpp          -o ./bin/chapter05_03-001_communication_nontemplate.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_03-002_communication_template.cpp             -o ./bin/chapter05_03-002_communication_template.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_03-003_communication_session.cpp              -o ./bin/chapter05_03-003_communication_session.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_04-001_template_point.cpp                     -o ./bin/chapter05_04-001_template_point.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_05-001_template_point.cpp                     -o ./bin/chapter05_05-001_template_point.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_05-002_template_point.cpp                     -o ./bin/chapter05_05-002_template_point.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_05-003_template_point.cpp                     -o ./bin/chapter05_05-003_template_point.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_06-001_template_specialization.cpp            -o ./bin/chapter05_06-001_template_specialization.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_06-002_template_enable_if.cpp                 -o ./bin/chapter05_06-002_template_enable_if.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_06-003_template_concepts.cpp                  -o ./bin/chapter05_06-003_template_concepts.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_06-004_template_point.cpp                     -o ./bin/chapter05_06-004_template_point.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_07-001_led_static_polymorphism.cpp            -o ./bin/chapter05_07-001_led_static_polymorphism.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_08-001_using_the_stl.cpp                      -o ./bin/chapter05_08-001_using_the_stl.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_08-002_using_the_stl_algo.cpp                 -o ./bin/chapter05_08-002_using_the_stl_algo.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_08-003_std_for_each.cpp                       -o ./bin/chapter05_08-003_std_for_each.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_09-001_factory_simple.cpp                     -o ./bin/chapter05_09-001_factory_simple.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_09-002_factory_variadic_template.cpp          -o ./bin/chapter05_09-002_factory_variadic_template.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_10-001_metaprogram_factorial.cpp              -o ./bin/chapter05_10-001_metaprogram_factorial.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_10-002_const_eval_pow10.cpp                   -o ./bin/chapter05_10-002_const_eval_pow10.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_10-003_const_eval_inner_product.cpp           -o ./bin/chapter05_10-003_const_eval_inner_product.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_11-001_tuple_things_simple.cpp                -o ./bin/chapter05_11-001_tuple_things_simple.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_11-002_tuple_things_metaprogram.cpp           -o ./bin/chapter05_11-002_tuple_things_metaprogram.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_11-003_tuple_things_metaprog_alias.cpp        -o ./bin/chapter05_11-003_tuple_things_metaprog_alias.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_12-001_prime_number.cpp                       -o ./bin/chapter05_12-001_prime_number.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_12-002_constants.cpp                          -o ./bin/chapter05_12-002_constants.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_12-003_stirlings_approx.cpp                   -o ./bin/chapter05_12-003_stirlings_approx.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_12-004_stirlings_approx_numbers.cpp           -o ./bin/chapter05_12-004_stirlings_approx_numbers.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_13-001_integer_sequence.cpp                   -o ./bin/chapter05_13-001_integer_sequence.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_13-002_array_to_tuple.cpp                     -o ./bin/chapter05_13-002_array_to_tuple.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_13-003_exp_series.cpp                         -o ./bin/chapter05_13-003_exp_series.exe
$GCC -std=c++20 -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter05_14-001_stirlings_approx_complex.cpp           -o ./bin/chapter05_14-001_stirlings_approx_complex.exe

ls -la \
./bin/chapter05_01-001_template_add.exe                    \
./bin/chapter05_01-002_template_add2.exe                   \
./bin/chapter05_02-001_make_word.exe                       \
./bin/chapter05_02-002_make_large.exe                      \
./bin/chapter05_03-001_communication_nontemplate.exe       \
./bin/chapter05_03-002_communication_template.exe          \
./bin/chapter05_03-003_communication_session.exe           \
./bin/chapter05_04-001_template_point.exe                  \
./bin/chapter05_05-001_template_point.exe                  \
./bin/chapter05_05-002_template_point.exe                  \
./bin/chapter05_05-003_template_point.exe                  \
./bin/chapter05_06-001_template_specialization.exe         \
./bin/chapter05_06-002_template_enable_if.exe              \
./bin/chapter05_06-003_template_concepts.exe               \
./bin/chapter05_06-004_template_point.exe                  \
./bin/chapter05_07-001_led_static_polymorphism.exe         \
./bin/chapter05_08-001_using_the_stl.exe                   \
./bin/chapter05_08-002_using_the_stl_algo.exe              \
./bin/chapter05_08-003_std_for_each.exe                    \
./bin/chapter05_09-001_factory_simple.exe                  \
./bin/chapter05_09-002_factory_variadic_template.exe       \
./bin/chapter05_10-001_metaprogram_factorial.exe           \
./bin/chapter05_10-002_const_eval_pow10.exe                \
./bin/chapter05_10-003_const_eval_inner_product.exe        \
./bin/chapter05_11-001_tuple_things_simple.exe             \
./bin/chapter05_11-002_tuple_things_metaprogram.exe        \
./bin/chapter05_11-003_tuple_things_metaprog_alias.exe     \
./bin/chapter05_12-001_prime_number.exe                    \
./bin/chapter05_12-002_constants.exe                       \
./bin/chapter05_12-003_stirlings_approx.exe                \
./bin/chapter05_12-004_stirlings_approx_numbers.exe        \
./bin/chapter05_13-001_integer_sequence.exe                \
./bin/chapter05_13-002_array_to_tuple.exe                  \
./bin/chapter05_13-003_exp_series.exe                      \
./bin/chapter05_14-001_stirlings_approx_complex.exe

result_ls=$?

echo "result_ls: "  "$result_ls"

exit $result_ls
