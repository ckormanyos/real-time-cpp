///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_SYS_START_INTERFACE_2017_11_21_H_
  #define MCAL_LED_SYS_START_INTERFACE_2017_11_21_H_

  #include <atomic>

  namespace mcal { namespace led {

  struct sys_start_interface
  {
    static void my_sys_start();

    static std::atomic<bool>& my_exit_pc_api_flag();
  };

  } } // namespace mcal::led

#endif // MCAL_LED_SYS_START_INTERFACE_2017_11_21_H_
