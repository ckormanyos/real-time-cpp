///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2024.
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
      using config_type = void;
      using value_type = std::uint64_t;

      auto init(const config_type*) -> void;

      struct secure final
      {
        static auto get_time_elapsed() -> value_type;
      };
    }
  }

#endif // MCAL_GPT_2011_10_20_H
