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

$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -march=native -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter04_01-001_led_hierarchy.cpp             -o ./bin/chapter04_01-001_led_hierarchy.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -march=native -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter04_04-001_dynamic_polymorphism.cpp      -o ./bin/chapter04_04-001_dynamic_polymorphism.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -march=native -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter04_04-002_dynamic_polymorphism_cast.cpp -o ./bin/chapter04_04-002_dynamic_polymorphism_cast.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -march=native -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter04_04-003_dynamic_polymorphism_ref.cpp  -o ./bin/chapter04_04-003_dynamic_polymorphism_ref.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -march=native -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter04_07-001_led_hierarchy_uses_pwm.cpp    -o ./bin/chapter04_07-001_led_hierarchy_uses_pwm.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -march=native -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter04_08-001_const_com_class.cpp           -o ./bin/chapter04_08-001_const_com_class.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -march=native -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter04_08-002_nonconst_com_class.cpp        -o ./bin/chapter04_08-002_nonconst_com_class.exe
$GCC -std=$STD -Wall -Wextra -Wpedantic -Werror -O3 -march=native -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter04_08-003_poll_communication.cpp        -o ./bin/chapter04_08-003_poll_communication.exe


ls -la \
./bin/chapter04_01-001_led_hierarchy.exe              \
./bin/chapter04_04-001_dynamic_polymorphism.exe       \
./bin/chapter04_04-002_dynamic_polymorphism_cast.exe  \
./bin/chapter04_04-003_dynamic_polymorphism_ref.exe   \
./bin/chapter04_07-001_led_hierarchy_uses_pwm.exe     \
./bin/chapter04_08-001_const_com_class.exe            \
./bin/chapter04_08-002_nonconst_com_class.exe         \
./bin/chapter04_08-003_poll_communication.exe

result_ls=$?

echo "result_ls: "  "$result_ls"

exit $result_ls
