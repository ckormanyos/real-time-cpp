#!/usr/bin/env bash
#
#  Copyright Christopher Kormanyos 2020 - 2025.
#  Distributed under the Boost Software License,
#  Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#

if [[ "$1" != "" ]]; then
    STD="$1"
else
    STD=c++14
fi

GCC=arm-none-eabi-g++

wflags="-Wextra -Wpedantic -Wmain -Wundef -Wconversion -Wsign-conversion -Wunused-parameter -Wuninitialized -Wmissing-declarations -Wshadow -Wunreachable-code -Wswitch-default -Wswitch-enum -Wcast-align -Wmissing-include-dirs -Winit-self -Wfloat-equal -Wdouble-promotion -Wno-psabi"

mkdir -p bin

rm -f ./bin/*.*

echo run benchmarks with $GCC and language standard $STD
echo

$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_COMPLEX                      -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_complex.cpp                   ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_complex.map                    -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_complex.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_CRC                          -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_crc.cpp                       ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_crc.map                        -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_crc.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FAST_MATH                    -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_fast_math.cpp                 ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_fast_math.map                  -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_fast_math.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FILTER                       -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_filter.cpp                    ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_filter.map                     -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_filter.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FIXED_POINT                  -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_fixed_point.cpp               ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_fixed_point.map                -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_fixed_point.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_FLOAT                        -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_float.cpp                     ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_float.map                      -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_float.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_HASH                         -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_hash.cpp                      ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_hash.map                       -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_hash.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_NONE                         -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_none.cpp                      ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_none.map                       -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_none.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_PI_AGM                       -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_pi_agm.cpp                    ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_pi_agm.map                     -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_pi_agm.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_PI_SPIGOT                    -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_pi_spigot.cpp                 ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_pi_spigot.map                  -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_pi_spigot.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_PI_SPIGOT_SINGLE             -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_pi_spigot_single.cpp          ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_pi_spigot_single.map           -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_pi_spigot_single.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_SOFT_DOUBLE_H2F1             -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_soft_double_h2f1.cpp          ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_soft_double_h2f1.map           -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_soft_double_h2f1.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_TRAPEZOID_INTEGRAL           -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_trapezoid_integral.cpp        ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_trapezoid_integral.map         -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_trapezoid_integral.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_WIDE_DECIMAL                 -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_wide_decimal.cpp              ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_wide_decimal.map               -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_wide_decimal.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_WIDE_INTEGER                 -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_wide_integer.cpp              ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_wide_integer.map               -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_wide_integer.elf
$GCC -std=$STD -Werror -Wall         -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128                                 -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                          -I../../boost-root -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_BOOST_MATH_CBRT_TGAMMA       -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_boost_math_cbrt_tgamma.cpp    ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_boost_math_cbrt_tgamma.map     -T ./target/micros/stm32f446/make/stm32f446_with_stdlib.ld --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_boost_math_cbrt_tgamma.elf
$GCC -std=$STD -Werror -Wall         -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128                                 -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                          -I../../boost-root -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_BOOST_MATH_CYL_BESSEL_J      -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_boost_math_cyl_bessel_j.cpp   ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_boost_math_cyl_bessel_j.map    -T ./target/micros/stm32f446/make/stm32f446_with_stdlib.ld --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_boost_math_cyl_bessel_j.elf
$GCC -std=$STD -Werror -Wall         -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128                                 -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                          -I../../boost-root -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_BOOST_MULTIPRECISION_CBRT    -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_boost_multiprecision_cbrt.cpp ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_boost_multiprecision_cbrt.map  -T ./target/micros/stm32f446/make/stm32f446_with_stdlib.ld --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_boost_multiprecision_cbrt.elf
$GCC -std=$STD -Werror -Wall $wflags -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_HASH_SHA256                  -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_hash_sha256.cpp               ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_hash_sha256.map                -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_hash_sha256.elf
$GCC -std=$STD -Werror -Wall $wflags -Os -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src                                                             -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_ECC_GENERIC_ECC              -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_ecc_generic_ecc.cpp           ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_ecc_generic_ecc.map            -T ./target/micros/stm32f446/make/stm32f446_with_stdlib.ld --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_ecc_generic_ecc.elf
$GCC -std=$STD -Werror -Wall         -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src -I../../cppalliance-decimal-root/include -I../../boost-root -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_NON_STD_DECIMAL              -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_non_std_decimal.cpp           ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_non_std_decimal.map            -T ./target/micros/stm32f446/make/stm32f446_with_stdlib.ld --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_non_std_decimal.elf
$GCC -std=$STD -Werror -Wall         -O2 -g -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -x c++ -fno-rtti -fno-use-cxa-atexit -fno-exceptions -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -mcpu=cortex-m4 -mtune=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffast-math -mno-unaligned-access -mno-long-calls -I./src/mcal/stm32f446 -I./src -I../../cppalliance-crypt-root/include -I../../boost-root   -DAPP_BENCHMARK_TYPE=APP_BENCHMARK_TYPE_BOOST_CRYPT_HASHER           -DAPP_BENCHMARK_STANDALONE_MAIN ./src/app/benchmark/app_benchmark_boost_crypt_hasher.cpp        ./target/micros/stm32f446/make/single/crt.cpp -nostartfiles -Wl,--gc-sections -Wl,-Map,./bin/app_benchmark_boost_crypt_hasher.map         -T ./target/micros/stm32f446/make/stm32f446.ld             --specs=nano.specs --specs=nosys.specs -o ./bin/app_benchmark_boost_crypt_hasher.elf

echo check existences of ELF-files and map-files
echo

ls -la ./bin/app_benchmark_complex.elf ./bin/app_benchmark_complex.map
result_ls_complex=$?

ls -la ./bin/app_benchmark_crc.elf ./bin/app_benchmark_crc.map
result_ls_crc=$?

ls -la ./bin/app_benchmark_fast_math.elf ./bin/app_benchmark_fast_math.map
result_ls_fast_math=$?

ls -la ./bin/app_benchmark_filter.elf ./bin/app_benchmark_filter.map
result_ls_filter=$?

ls -la ./bin/app_benchmark_fixed_point.elf ./bin/app_benchmark_fixed_point.map
result_ls_fixed_point=$?

ls -la ./bin/app_benchmark_float.elf ./bin/app_benchmark_float.map
result_ls_float=$?

ls -la ./bin/app_benchmark_hash.elf ./bin/app_benchmark_hash.map
result_ls_hash=$?

ls -la ./bin/app_benchmark_none.elf ./bin/app_benchmark_none.map
result_ls_none=$?

ls -la ./bin/app_benchmark_pi_agm.elf ./bin/app_benchmark_pi_agm.map
result_ls_pi_agm=$?

ls -la ./bin/app_benchmark_pi_spigot.elf ./bin/app_benchmark_pi_spigot.map
result_ls_pi_spigot=$?

ls -la ./bin/app_benchmark_pi_spigot_single.elf ./bin/app_benchmark_pi_spigot_single.map
result_ls_pi_spigot_single=$?

ls -la ./bin/app_benchmark_soft_double_h2f1.elf ./bin/app_benchmark_soft_double_h2f1.map
result_ls_soft_double_h2f1=$?

ls -la ./bin/app_benchmark_trapezoid_integral.elf ./bin/app_benchmark_trapezoid_integral.map
result_ls_trapezoid_integral=$?

ls -la ./bin/app_benchmark_wide_decimal.elf ./bin/app_benchmark_wide_decimal.map
result_ls_wide_decimal=$?

ls -la ./bin/app_benchmark_wide_integer.elf ./bin/app_benchmark_wide_integer.map
result_ls_wide_integer=$?

ls -la ./bin/app_benchmark_boost_math_cbrt_tgamma.elf ./bin/app_benchmark_boost_math_cbrt_tgamma.map
result_ls_boost_math_cbrt_tgamma=$?

ls -la ./bin/app_benchmark_boost_math_cyl_bessel_j.elf ./bin/app_benchmark_boost_math_cyl_bessel_j.map
result_ls_boost_math_cyl_bessel_j=$?

ls -la ./bin/app_benchmark_boost_multiprecision_cbrt.elf ./bin/app_benchmark_boost_multiprecision_cbrt.map
result_ls_boost_multiprecision_cbrt=$?

ls -la ./bin/app_benchmark_hash_sha256.elf ./bin/app_benchmark_hash_sha256.map
result_ls_hash_sha256=$?

ls -la ./bin/app_benchmark_wide_integer.elf ./bin/app_benchmark_ecc_generic_ecc.map
result_ls_ecc_generic_ecc=$?

ls -la ./bin/app_benchmark_non_std_decimal.elf ./bin/app_benchmark_non_std_decimal.map
result_ls_non_std_decimal=$?

ls -la ./bin/app_benchmark_boost_crypt_hasher.elf ./bin/app_benchmark_boost_crypt_hasher.map
result_ls_boost_crypt_hasher=$?

echo "result_ls_complex                   : "  "$result_ls_complex"
echo "result_ls_crc                       : "  "$result_ls_crc"
echo "result_ls_fast_math                 : "  "$result_ls_fast_math"
echo "result_ls_filter                    : "  "$result_ls_filter"
echo "result_ls_fixed_point               : "  "$result_ls_fixed_point"
echo "result_ls_float                     : "  "$result_ls_float"
echo "result_ls_hash                      : "  "$result_ls_hash"
echo "result_ls_none                      : "  "$result_ls_none"
echo "result_ls_pi_agm                    : "  "$result_ls_pi_agm"
echo "result_ls_pi_spigot                 : "  "$result_ls_pi_spigot"
echo "result_ls_pi_spigot_single          : "  "$result_ls_pi_spigot_single"
echo "result_ls_soft_double_h2f1          : "  "$result_ls_soft_double_h2f1"
echo "result_ls_trapezoid_integral        : "  "$result_ls_trapezoid_integral"
echo "result_ls_wide_decimal              : "  "$result_ls_wide_decimal"
echo "result_ls_wide_integer              : "  "$result_ls_wide_integer"
echo "result_ls_boost_math_cbrt_tgamma    : "  "$result_ls_boost_math_cbrt_tgamma"
echo "result_ls_boost_math_cyl_bessel_j   : "  "$result_ls_boost_math_cyl_bessel_j"
echo "result_ls_boost_multiprecision_cbrt : "  "$result_ls_boost_multiprecision_cbrt"
echo "result_ls_hash_sha256               : "  "$result_ls_hash_sha256"
echo "result_ls_ecc_generic_ecc           : "  "$result_ls_ecc_generic_ecc"
echo "result_ls_non_std_decimal           : "  "$result_ls_non_std_decimal"
echo "result_ls_boost_crypt_hasher        : "  "$result_ls_boost_crypt_hasher"

echo verify result_total
echo

result_total=$((result_ls_complex+result_ls_crc+result_ls_fast_math+result_ls_filter+result_ls_fixed_point+result_ls_float+result_ls_hash+result_ls_none+result_ls_pi_agm+result_ls_pi_spigot+result_ls_pi_spigot_single+result_ls_soft_double_h2f1+result_ls_trapezoid_integral+result_ls_wide_decimal+result_ls_wide_integer+result_ls_boost_math_cbrt_tgamma+result_ls_boost_math_cyl_bessel_j+result_ls_boost_multiprecision_cbrt+result_ls_hash_sha256+$result_ls_ecc_generic_ecc+result_ls_non_std_decimal+result_ls_boost_crypt_hasher))

echo "result_total                        : "  "$result_total"

exit $result_total
