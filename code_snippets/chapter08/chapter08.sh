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

$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_01-001_my_startup.cpp                -o ./bin/chapter08_01-001_my_startup.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_02-001_static_init_ram.cpp           -o ./bin/chapter08_02-001_static_init_ram.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_02-002_static_init_bss.cpp           -o ./bin/chapter08_02-002_static_init_bss.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_02-003_static_init_data.cpp          -o ./bin/chapter08_02-003_static_init_data.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_03-001_static_constructor.cpp        -o ./bin/chapter08_03-001_static_constructor.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_05-001_static_initialization.cpp     -o ./bin/chapter08_05-001_static_initialization.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_05-002_static_initialization.cpp     -o ./bin/chapter08_05-002_static_initialization.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_05-003_static_initialization.cpp     -o ./bin/chapter08_05-003_static_initialization.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_06-001_singleton_object.cpp          -o ./bin/chapter08_06-001_singleton_object.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_06-002_singleton_object.cpp          -o ./bin/chapter08_06-002_singleton_object.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_07-001_my_startup_and_main.cpp       -o ./bin/chapter08_07-001_my_startup_and_main.exe
$GCC -std=$STD     -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -O3 -m64 -fsanitize=address -fsanitize=shift -fsanitize=shift-exponent -fsanitize=shift-base -fsanitize=integer-divide-by-zero -fsanitize=null -fsanitize=signed-integer-overflow -fsanitize=bounds -fsanitize=alignment -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fsanitize=enum ./chapter08_07-002_main_and_scheduler.cpp        -o ./bin/chapter08_07-002_main_and_scheduler.exe

ls -la \
./bin/chapter08_01-001_my_startup.exe                 \
./bin/chapter08_02-001_static_init_ram.exe            \
./bin/chapter08_02-002_static_init_bss.exe            \
./bin/chapter08_02-003_static_init_data.exe           \
./bin/chapter08_03-001_static_constructor.exe         \
./bin/chapter08_05-001_static_initialization.exe      \
./bin/chapter08_05-002_static_initialization.exe      \
./bin/chapter08_05-003_static_initialization.exe      \
./bin/chapter08_06-001_singleton_object.exe           \
./bin/chapter08_06-002_singleton_object.exe           \
./bin/chapter08_07-001_my_startup_and_main.exe        \
./bin/chapter08_07-002_main_and_scheduler.exe      

result_ls=$?

echo "result_ls: "  "$result_ls"

exit $result_ls
