///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>
#include <math/checksums/hash_base/sha512.h>

namespace
{
  typedef sha512<std::uint8_t> sha512_type;

  const std::uint64_t control_value = UINT64_C(0x3F7E0479733B7E33);

  sha512_type the_sha512;

  sha512_type::result_type_as_integral_values the_sha512_result_as_integral_values;
}

extern "C" int main()
{
  // Initialize the Microcontroller Abstraction Layer.
  mcal::init();

  the_sha512.process_data("creativity", sha512_type::count_type(10U));

  the_sha512_result_as_integral_values = the_sha512.get_result_as_integral_values_and_finalize_the_state();

  const bool the_result_is_ok = (the_sha512_result_as_integral_values.front() == control_value);

  // Start the multitasking scheduler (and never return).
  if(the_result_is_ok)
  {
    os::start_os();
  }
  else
  {
    for(;;)
    {
      // Make a visible error reaction here...
      ;
    }
  }
}
