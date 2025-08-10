///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_GPT_2011_10_20_H
  #define MCAL_GPT_2011_10_20_H

  #include <cstdint>

  namespace mcal
  {
    namespace gpt
    {
      typedef void          config_type;
      typedef std::uint64_t value_type;

      void init(const config_type*);

      struct secure final
      {
        static value_type get_time_elapsed();
      };
    }
  }

#endif // MCAL_GPT_2011_10_20_H
