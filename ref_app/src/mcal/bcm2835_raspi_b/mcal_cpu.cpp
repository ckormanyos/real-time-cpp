///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal_cpu.h>
#include <mcal_osc.h>
#include <mcal_port.h>
#include <mcal_reg.h>
#include <mcal_wdg.h>

namespace mcal
{
  namespace cpu
  {
    namespace detail
    {
      void enable_branch_prediction    ();
      void enable_the_instruction_cache();

      void enable_branch_prediction()
      {
        asm volatile("mrc p15, #0, r1, c1, c0, #0");
        asm volatile("orr r1, r1, #0x0800");
        asm volatile("mcr p15, #0,r1, c1, c0, #0");
      }

      void enable_the_instruction_cache()
      {
        // Here we have:
        // * bit 12 = instruction cache
        asm volatile("mrc p15, #0, r1, c1, c0, #0");
        asm volatile("orr r1, r1, #0x1000");
        asm volatile("mcr p15, #0, r1, c1, c0, #0");
      }
    }
  }
}

void mcal::cpu::init()
{
//  detail::enable_branch_prediction();

//  detail::enable_the_instruction_cache();

  mcal::wdg::init(nullptr);
  mcal::port::init(nullptr);
  mcal::osc::init(nullptr);
}
