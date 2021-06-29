///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef APP_LED_2020_10_07_H_
  #define APP_LED_2020_10_07_H_

  #if defined(__cplusplus)
  extern "C"
  {
  #endif

  void app_led_task_background (void* pv);
  void app_led_task_toggle_led0(void* pv);

  #if defined(__cplusplus)
  }
  #endif

#endif // APP_LED_2020_10_07_H_
