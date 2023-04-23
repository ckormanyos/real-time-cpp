///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>

// To manually build with GNUmake on *nix:
// cd /mnt/c/Users/User/Documents/Ks/uC_Software/Boards/real-time-cpp/ref_app
// make -f target/app/make/app_make.gmk rebuild TGT=x86_64-w64-mingw32

// To manually build on *nix command line for target host:
// cd /mnt/c/Users/User/Documents/Ks/uC_Software/Boards/real-time-cpp
// g++ -O3 -march=native -mtune=native -std=c++14 -Wall -Wextra -Wpedantic -Wmain -Wundef -Wconversion -Wsign-conversion -Wunused-parameter -Wuninitialized -Wmissing-declarations -Wshadow -Wunreachable-code -Wswitch-default -Wswitch-enum -Wcast-align -Wmissing-include-dirs -Winit-self -Wfloat-equal -Wdouble-promotion -Wno-comment -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -fno-rtti -fno-use-cxa-atexit -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -Iref_app/src -Iref_app/src/mcal/host -pthread -lpthread ref_app/src/app/benchmark/app_benchmark.cpp ref_app/src/app/benchmark/app_benchmark_none.cpp ref_app/src/app/led/app_led.cpp ref_app/src/mcal/host/mcal_cpu.cpp ref_app/src/mcal/host/mcal_eep.cpp ref_app/src/mcal/host/mcal_gpt.cpp ref_app/src/mcal/host/mcal_irq.cpp ref_app/src/mcal/host/mcal_led.cpp ref_app/src/mcal/host/mcal_osc.cpp ref_app/src/mcal/host/mcal_pwm.cpp ref_app/src/mcal/host/mcal_port.cpp ref_app/src/mcal/host/mcal_spi.cpp ref_app/src/mcal/host/mcal_wdg.cpp ref_app/src/mcal/host/mcal_wdg_watchdog.cpp ref_app/src/mcal/mcal.cpp ref_app/src/os/os.cpp ref_app/src/os/os_task_control_block.cpp ref_app/src/sys/idle/sys_idle.cpp ref_app/src/sys/mon/sys_mon.cpp ref_app/src/sys/start/sys_start.cpp -o real_time_cpp.exe

// To build the local clang-tidy project on *nix:
// cd /mnt/c/Users/User/Documents/Ks/uC_Software/Boards/real-time-cpp
// cd .tidy/make
// make prepare -f make_tidy_01_generic.gmk
// make tidy -f make_tidy_01_generic.gmk --jobs=8

// cd /mnt/c/Users/User/Documents/Ks/uC_Software/Boards/real-time-cpp
// PATH=/home/chris/local/coverity/cov-analysis-linux64-2021.12.1/bin:$PATH
// cov-build --dir cov-int g++ -O3 -march=native -mtune=native -std=c++14 -Wall -Wextra -Wpedantic -Wmain -Wundef -Wconversion -Wsign-conversion -Wunused-parameter -Wuninitialized -Wmissing-declarations -Wshadow -Wunreachable-code -Wswitch-default -Wswitch-enum -Wcast-align -Wmissing-include-dirs -Winit-self -Wfloat-equal -Wdouble-promotion -Wno-comment -gdwarf-2 -fno-exceptions -ffunction-sections -fdata-sections -fno-rtti -fno-use-cxa-atexit -fno-nonansi-builtins -fno-threadsafe-statics -fno-enforce-eh-specs -ftemplate-depth=128 -Wzero-as-null-pointer-constant -Iref_app/src -Iref_app/src/mcal/host -pthread -lpthread ref_app/src/app/benchmark/app_benchmark.cpp ref_app/src/app/benchmark/app_benchmark_none.cpp ref_app/src/app/led/app_led.cpp ref_app/src/mcal/host/mcal_cpu.cpp ref_app/src/mcal/host/mcal_eep.cpp ref_app/src/mcal/host/mcal_gpt.cpp ref_app/src/mcal/host/mcal_irq.cpp ref_app/src/mcal/host/mcal_led.cpp ref_app/src/mcal/host/mcal_osc.cpp ref_app/src/mcal/host/mcal_pwm.cpp ref_app/src/mcal/host/mcal_port.cpp ref_app/src/mcal/host/mcal_spi.cpp ref_app/src/mcal/host/mcal_wdg.cpp ref_app/src/mcal/host/mcal_wdg_watchdog.cpp ref_app/src/mcal/mcal.cpp ref_app/src/os/os.cpp ref_app/src/os/os_task_control_block.cpp ref_app/src/sys/idle/sys_idle.cpp ref_app/src/sys/mon/sys_mon.cpp ref_app/src/sys/start/sys_start.cpp ref_app/src/sys/start/coverity.c -o real_time_cpp.exe
// tar caf real_time_cpp.bz2 cov-int

#if defined(__GNUC__)
#if defined(__XTENSA__)
extern "C"
__attribute__((used)) auto app_main_loop(void) -> int; // NOLINT(clang-diagnostic-ignored-attributes)
#else
__attribute__((used)) auto main() -> int; // NOLINT(clang-diagnostic-ignored-attributes)
#endif
#endif

#if defined(__GNUC__) && defined(__XTENSA__)
auto app_main_loop(void) -> int
#else
auto main() -> int
#endif
{
  // Initialize the microcontroller abstraction layer.
  mcal::init();

  // Start the multitasking scheduler. (This does not return.)
  // Handle an unexpected return from main() in the startup code.
  os::start_os();

  #if defined(__GNUC__) && defined(__XTENSA__)
  return 0;
  #endif
}
