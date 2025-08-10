///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDG_2010_04_10_H
  #define MCAL_WDG_2010_04_10_H

  namespace mcal
  {
    namespace wdg
    {
      using config_type = void;

      auto init(const config_type*) -> void;

      struct secure final
      {
        static auto trigger() -> void;
      };
    }
  }

#endif // MCAL_WDG_2010_04_10_H
