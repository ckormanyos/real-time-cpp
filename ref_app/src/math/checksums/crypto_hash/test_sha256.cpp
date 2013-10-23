///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>
#include <math/checksums/crypto_hash/sha256.h>

namespace
{
  typedef sha256<std::uint8_t> sha256_type;

  const std::uint32_t control_value = UINT32_C(0x5A59225B);

  sha256_type the_sha256;

  sha256_type::result_type_as_dwords the_sha256_result_as_dwords;
}

extern "C" int main()
{
  // Initialize the Microcontroller Abstraction Layer.
  mcal::init();

  the_sha256.process_data("creativity", sha256_type::count_type(10U));

  the_sha256_result_as_dwords = the_sha256.get_result_as_dwords_and_finalize_the_state();

  const bool the_result_is_ok = (the_sha256_result_as_dwords.front() == control_value);

  // Start the multitasking scheduler (and never return).
  if(the_result_is_ok)
  {
    os::start_os();
  }
}
