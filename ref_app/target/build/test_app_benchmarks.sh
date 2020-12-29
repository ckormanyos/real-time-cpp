#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2020.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

rm -f ./ref_app/bin/*.*

g++ -std=c++11 -Wall -Werror -O3 -march=native                                         -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_COMPLEX           -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_complex.cpp           -o ./ref_app/bin/app_benchmark_complex.exe
g++ -std=c++11 -Wall -Werror -O3 -march=native                                         -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_CRC               -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_crc.cpp               -o ./ref_app/bin/app_benchmark_crc.exe
g++ -std=c++11 -Wall -Werror -O3 -march=native                                         -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FAST_MATH         -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_fast_math.cpp         -o ./ref_app/bin/app_benchmark_fast_math.exe
g++ -std=c++11 -Wall -Werror -O3 -march=native                                         -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FILTER            -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_filter.cpp            -o ./ref_app/bin/app_benchmark_filter.exe
g++ -std=c++11 -Wall -Werror -O3 -march=native                                         -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FIXED_POINT       -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_fixed_point.cpp       -o ./ref_app/bin/app_benchmark_fixed_point.exe
g++ -std=c++11 -Wall -Werror -O3 -march=native -I./ref_app/src/util/STL_C++XX_stdfloat -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FLOAT             -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_float.cpp             -o ./ref_app/bin/app_benchmark_float.exe
g++ -std=c++11 -Wall -Werror -O3 -march=native                                         -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_HASH              -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_hash.cpp              -o ./ref_app/bin/app_benchmark_hash.exe
g++ -std=c++11 -Wall -Werror -O3 -march=native                                         -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_PI_SPIGOT         -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_pi_spigot.cpp         -o ./ref_app/bin/app_benchmark_pi_spigot.exe
g++ -std=c++11 -Wall -Werror -O3 -march=native                                         -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE  -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_pi_spigot_single.cpp  -o ./ref_app/bin/app_benchmark_pi_spigot_single.exe
g++ -std=c++11 -Wall -Werror -O3 -march=native                                         -I./ref_app/src/mcal/host -I./ref_app/src -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_WIDE_INTEGER      -DAPP_BENCHMARK_STANDALONE_MAIN ./ref_app/src/app/benchmark/app_benchmark_wide_integer.cpp      -o ./ref_app/bin/app_benchmark_wide_integer.exe

./ref_app/bin/app_benchmark_complex.exe
result_var_complex=$?

./ref_app/bin/app_benchmark_crc.exe
result_var_crc=$?

./ref_app/bin/app_benchmark_fast_math.exe
result_var_fast_math=$?

./ref_app/bin/app_benchmark_filter.exe
result_var_filter=$?

./ref_app/bin/app_benchmark_fixed_point.exe
result_var_fixed_point=$?

./ref_app/bin/app_benchmark_float.exe
result_var_float=$?

./ref_app/bin/app_benchmark_hash.exe
result_var_hash=$?

./ref_app/bin/app_benchmark_pi_spigot.exe
result_var_pi_spigot=$?

./ref_app/bin/app_benchmark_pi_spigot_single.exe
result_var_pi_spigot_single=$?

./ref_app/bin/app_benchmark_wide_integer.exe
result_var_wide_integer=$?

echo "result_var_complex:"           "$result_var_complex"
echo "result_var_crc:"               "$result_var_crc"
echo "result_var_fast_math:"         "$result_var_fast_math"
echo "result_var_filter:"            "$result_var_filter"
echo "result_var_fixed_point:"       "$result_var_fixed_point"
echo "result_var_float:"             "$result_var_float"
echo "result_var_hash:"              "$result_var_hash"
echo "result_var_pi_spigot:"         "$result_var_pi_spigot"
echo "result_var_pi_spigot_single:"  "$result_var_pi_spigot_single"
echo "result_var_wide_integer:"      "$result_var_wide_integer"

result_total=$((result_var_complex+result_var_crc+result_var_fast_math+result_var_filter+result_var_fixed_point+result_var_float+result_var_hash+result_var_pi_spigot+result_var_pi_spigot_single+result_var_wide_integer))

echo "result_total:"                 "$result_total"

exit $result_total
