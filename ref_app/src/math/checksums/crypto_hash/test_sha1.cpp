///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <os/os.h>
#include <math/checksums/crypto_hash/sha1.h>

namespace
{
  sha1_context example_hash;
}

extern "C" int main()
{
  example_hash.sha1_initialize();
  example_hash.sha1_input("The quick brown fox jumps over the lazy dog", 43U);
  example_hash.sha1_finalize();

  const std::array<std::uint32_t, 5> sha_hash = example_hash.get_hash();

  // Initialize the Microcontroller Abstraction Layer.
  mcal::init();

  // Start the multitasking scheduler (and never return).
  if(sha_hash.front() == UINT32_C(0x2FD4E1C6))
  {
    os::start_os();
  }
}
