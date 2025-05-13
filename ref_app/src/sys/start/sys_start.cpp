///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>

#if defined(_MSC_VER)
#define ATTRIBUTE(a)
#else
#define ATTRIBUTE(a) __attribute__((a))
#endif

#if (defined(__XTENSA__) && !defined(CONFIG_IDF_TARGET_ESP32S3))
extern "C" ATTRIBUTE(used) auto app_main_loop() -> int;
#else
ATTRIBUTE(used) auto main() -> int;
#endif

#if (defined(__XTENSA__) && !defined(CONFIG_IDF_TARGET_ESP32S3))
auto app_main_loop() -> int
#else
auto main() -> int
#endif
{
  // Initialize the microcontroller abstraction layer.
  mcal::init();

  // Start the multitasking scheduler. This does not return.
  // Handle an unexpected return from main() in the startup code.
  os::start_os();

  #if (defined(__XTENSA__) && !defined(CONFIG_IDF_TARGET_ESP32S3))
  return 0;
  #endif
}
