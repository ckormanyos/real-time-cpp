///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>

#if (defined(__GNUC__) || defined(__clang__))
#if defined(__XTENSA__)
extern "C"
__attribute__((used)) auto app_main_loop(void) -> int; // NOLINT(clang-diagnostic-ignored-attributes)
#else
extern "C"
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
