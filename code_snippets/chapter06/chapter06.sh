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

$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_01-001_crc32_mpeg2.cpp                -o ./bin/chapter06_01-001_crc32_mpeg2.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_03-001_mul_16x16to32.cpp              -o ./bin/chapter06_03-001_mul_16x16to32.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_06-001_name_mangling.cpp              -o ./bin/chapter06_06-001_name_mangling.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_06-002_name_mangling_get_event.cpp    -o ./bin/chapter06_06-002_name_mangling_get_event.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_07-001_assembly_sequences.cpp         -o ./bin/chapter06_07-001_assembly_sequences.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_08-001_comments.cpp                   -o ./bin/chapter06_08-001_comments.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_09-001_typedef_reg_access.cpp         -o ./bin/chapter06_09-001_typedef_reg_access.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_09-002_typedef_led_template.cpp       -o ./bin/chapter06_09-002_typedef_led_template.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_09-003_alias_reg_access.cpp           -o ./bin/chapter06_09-003_alias_reg_access.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_10-001_checksum_uint8_t.cpp           -o ./bin/chapter06_10-001_checksum_uint8_t.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_10-002_checksum_uint_fast8_t.cpp      -o ./bin/chapter06_10-002_checksum_uint_fast8_t.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_11-001_scale_with_powers_of_two.cpp   -o ./bin/chapter06_11-001_scale_with_powers_of_two.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_12-001_mul_shift_and_add.cpp          -o ./bin/chapter06_12-001_mul_shift_and_add.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_13-001_adc_dimensioning.cpp           -o ./bin/chapter06_13-001_adc_dimensioning.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_14-001_romable_string.cpp             -o ./bin/chapter06_14-001_romable_string.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_14-002_romable_array.cpp              -o ./bin/chapter06_14-002_romable_array.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_14-003_romable_initializer_list.cpp   -o ./bin/chapter06_14-003_romable_initializer_list.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_14-004_container_initializer_list.cpp -o ./bin/chapter06_14-004_container_initializer_list.exe
$GCC -std=c++20 -Wall -Wextra -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum -I../../../boost-root ./chapter06_14-005_iterator_facade.cpp            -o ./bin/chapter06_14-005_iterator_facade.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum -pthread -lpthread ./chapter06_15-001_minimize_interrupt_frame.cpp -o ./bin/chapter06_15-001_minimize_interrupt_frame.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum -pthread -lpthread ./chapter06_15-002_minimize_interrupt_frame.cpp -o ./bin/chapter06_15-002_minimize_interrupt_frame.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_16-001_operator_new.cpp               -o ./bin/chapter06_16-001_operator_new.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_17-001_use_the_stl.cpp                -o ./bin/chapter06_17-001_use_the_stl.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_17-002_use_the_stl.cpp                -o ./bin/chapter06_17-002_use_the_stl.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_18-001_use_lambdas.cpp                -o ./bin/chapter06_18-001_use_lambdas.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_18-002_use_lambdas.cpp                -o ./bin/chapter06_18-002_use_lambdas.exe
$GCC -std=$STD  -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter06_21-001_rtti_typeinfo.cpp              -o ./bin/chapter06_21-001_rtti_typeinfo.exe


ls -la \
./bin/chapter06_01-001_crc32_mpeg2.exe                \
./bin/chapter06_03-001_mul_16x16to32.exe              \
./bin/chapter06_06-001_name_mangling.exe              \
./bin/chapter06_06-002_name_mangling_get_event.exe    \
./bin/chapter06_07-001_assembly_sequences.exe         \
./bin/chapter06_08-001_comments.exe                   \
./bin/chapter06_09-001_typedef_reg_access.exe         \
./bin/chapter06_09-002_typedef_led_template.exe       \
./bin/chapter06_09-003_alias_reg_access.exe           \
./bin/chapter06_10-001_checksum_uint8_t.exe           \
./bin/chapter06_10-002_checksum_uint_fast8_t.exe      \
./bin/chapter06_11-001_scale_with_powers_of_two.exe   \
./bin/chapter06_12-001_mul_shift_and_add.exe          \
./bin/chapter06_13-001_adc_dimensioning.exe           \
./bin/chapter06_14-001_romable_string.exe             \
./bin/chapter06_14-002_romable_array.exe              \
./bin/chapter06_14-003_romable_initializer_list.exe   \
./bin/chapter06_14-004_container_initializer_list.exe \
./bin/chapter06_14-005_iterator_facade.exe            \
./bin/chapter06_15-001_minimize_interrupt_frame.exe   \
./bin/chapter06_15-002_minimize_interrupt_frame.exe   \
./bin/chapter06_16-001_operator_new.exe               \
./bin/chapter06_17-001_use_the_stl.exe                \
./bin/chapter06_17-002_use_the_stl.exe                \
./bin/chapter06_18-001_use_lambdas.exe                \
./bin/chapter06_18-002_use_lambdas.exe                \
./bin/chapter06_21-001_rtti_typeinfo.exe

result_ls=$?

echo "result_ls: "  "$result_ls"

exit $result_ls
