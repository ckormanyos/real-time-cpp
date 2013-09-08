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
  typedef md5<std::uint_least8_t> md5_type;

  md5_type the_md5("creativity", md5_type::count_type(10U));
}

extern "C" int main()
{
  // Initialize the Microcontroller Abstraction Layer.
  mcal::init();

  const md5_type::result_type_as_dwords the_md5_result = the_md5.get_result_as_dwords_and_finalize_the_state();

  // Start the multitasking scheduler (and never return).
  if(the_md5_result.back() == UINT32_C(0x9F78BFB7))
  {
    os::start_os();
  }
}
