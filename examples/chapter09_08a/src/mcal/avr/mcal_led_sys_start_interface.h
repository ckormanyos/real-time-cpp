///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_SYS_START_INTERFACE_2017_11_21_H
  #define MCAL_LED_SYS_START_INTERFACE_2017_11_21_H

  namespace mcal { namespace led {

  struct sys_start_interface
  {
    static auto my_sys_start() -> void;

    static auto my_exit_pc_api_flag() -> bool&;
  };

  } } // namespace mcal::led

#endif // MCAL_LED_SYS_START_INTERFACE_2017_11_21_H
