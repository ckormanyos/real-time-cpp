///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_gpt.h>
#include <mcal_reg_access.h>

mcal::gpt::value_type mcal::gpt::secure::get_time_elapsed()
{
  return static_cast<mcal::gpt::value_type>(0U);
}

void mcal::gpt::init(const config_type*)
{
}

extern "C" void __vector_timer2();

void __vector_timer2()
{
}
