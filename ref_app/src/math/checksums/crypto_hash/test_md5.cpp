///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>
#include <math/checksums/crypto_hash/md5.h>

namespace
{
  typedef md5<std::uint8_t> md5_type;

  const std::uint32_t control_value = UINT32_C(0x09191D4F);

  md5_type the_md5;

  md5_type::result_type_as_integral_values the_md5_result_as_integral_values;
}

extern "C" int main()
{
  // Initialize the Microcontroller Abstraction Layer.
  mcal::init();

  the_md5.process_data("creativity", md5_type::count_type(10U));

  the_md5_result_as_integral_values = the_md5.get_result_as_integral_values_and_finalize_the_state();

  const bool the_result_is_ok = (the_md5_result_as_integral_values.front() == control_value);

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
