///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_DETAIL_2014_06_12_H_
  #define MCAL_CPU_DETAIL_2014_06_12_H_

  namespace mcal
  {
    namespace cpu
    {
      namespace detail
      {
        void init     ();
        void load_nmi ();
        void user_mode();
      }
    }
  } // namespace mcal::cpu::detail

#endif // MCAL_CPU_DETAIL_2014_06_12_H_
