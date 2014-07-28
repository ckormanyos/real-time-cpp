///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// The Led Program (with a skinny operating system)

#include <mcal/mcal.h>
#include <os/os.h>

int main(void)
{
  // Initialize the mcal.
  mcal::init();

  os::start_os();
}
