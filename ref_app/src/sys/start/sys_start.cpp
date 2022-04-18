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

// To manually build with CMake for target host:
// cd real-time-cpp
// mkdir -p build
// cd build
// cmake ../ref_app -DTARGET=host -DCMAKE_TOOLCHAIN_FILE=../ref_app/cmake/gcc-toolchain.cmake
// make -j ref_app

// To build the local clang-tidy project on *nix:
// cd /mnt/c/Users/User/Documents/Ks/uC_Software/Boards/real-time-cpp
// cd .tidy/make
// make prepare -f make_tidy_01_generic.gmk
// make tidy -f make_tidy_01_generic.gmk --jobs=8

#if defined(__GNUC__)
#if defined(__XTENSA__)
extern "C" int app_main_loop(void) __attribute__((used)); // NOLINT(clang-diagnostic-ignored-attributes)
#else
auto main() -> int __attribute__((used)); // NOLINT(clang-diagnostic-ignored-attributes)
#endif
#endif

#if defined(__GNUC__) && defined(__XTENSA__)
int app_main_loop(void)
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
