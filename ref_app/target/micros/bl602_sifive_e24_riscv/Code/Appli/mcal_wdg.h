///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDG_2025_10_30_H
  #define MCAL_WDG_2025_10_30_H

  namespace mcal
  {
    namespace wdg
    {
      using config_type = void;

      inline auto init(const config_type*) -> void { }

      struct secure final
      {
        static auto trigger() -> void { }
      };
    }
  }

#endif // MCAL_WDG_2025_10_30_H
