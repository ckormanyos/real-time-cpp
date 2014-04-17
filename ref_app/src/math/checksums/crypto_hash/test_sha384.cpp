///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>
#include <math/checksums/crypto_hash/sha384.h>

namespace
{
  typedef sha384<std::uint8_t> sha384_type;

  const std::uint64_t control_value = UINT64_C(0x8BB184C5851558CA);

  sha384_type the_sha384;

  sha384_type::result_type_as_integral_values the_sha384_result_as_integral_values;
}

extern "C" int main()
{
  // Initialize the Microcontroller Abstraction Layer.
  mcal::init();

  the_sha384.process_data("creativity", sha384_type::count_type(10U));

  the_sha384_result_as_integral_values = the_sha384.get_result_as_integral_values_and_finalize_the_state();

  const bool the_result_is_ok = (the_sha384_result_as_integral_values.front() == control_value);

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
