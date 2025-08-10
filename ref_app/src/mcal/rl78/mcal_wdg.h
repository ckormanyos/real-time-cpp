///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDT_2010_04_10_H_
  #define MCAL_WDT_2010_04_10_H_

  namespace mcal
  {
    namespace wdg
    {
      typedef void config_type;

      void init(const config_type*);

      struct secure final
      {
        static void trigger();
      };
    }
  }

#endif // MCAL_WDT_2010_04_10_H
