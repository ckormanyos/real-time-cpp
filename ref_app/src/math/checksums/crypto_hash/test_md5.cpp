///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <string>
#include <mcal/mcal.h>
#include <os/os.h>
#include <math/checksums/crypto_hash/md5.h>
#include <util/memory/util_static_allocator.h>

namespace
{
  typedef md5<std::uint_least8_t> md5_type;

  typedef std::basic_string<char, std::char_traits<char>, util::static_allocator<char, 2U>> string_type;

  const string_type control_string("4F1D1909B527806E7633504AB7BF789F");

  md5_type the_md5;

  md5_type::result_type_as_chars the_md5_result_as_chars;
}

extern "C" int main()
{
  // Initialize the Microcontroller Abstraction Layer.
  mcal::init();

  the_md5.process_data("creativity", md5_type::count_type(10U));

  the_md5_result_as_chars = the_md5.get_result_as_chars_and_finalize_the_state();

  const string_type result_string (the_md5_result_as_chars.begin(), the_md5_result_as_chars.end());

  const bool the_result_is_ok = (result_string == control_string);

  // Start the multitasking scheduler (and never return).
  if(the_result_is_ok)
  {
    os::start_os();
  }
}
