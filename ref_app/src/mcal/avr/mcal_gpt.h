///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_GPT_2011_10_20_H_
  #define _MCAL_GPT_2011_10_20_H_

  #include <cstdint>

  namespace mcal
  {
    namespace gpt
    {
      typedef void          config_type;
      typedef std::uint32_t value_type;

      void init(const config_type*);

      value_type get_time_elapsed();
    }
  }

  mcal::gpt::value_type consistent_microsecond_tick();

#endif // _MCAL_GPT_2011_10_20_H_
