///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_WDT_2010_04_10_H_
  #define MCAL_WDT_2010_04_10_H_

  extern "C" void __my_startup() __attribute__((section(".startup"), used, noinline));
  extern "C" void app_led_task_toggle_led0(void* pv);

  namespace sys { namespace idle { void task_func(); } }

  namespace mcal
  {
    namespace wdg
    {
      typedef void config_type;

      void init(const config_type*);

      struct secure final
      {
      private:
        static void trigger();

        friend void ::app_led_task_toggle_led0(void* pv);
        friend void ::__my_startup();
      };
    }
  }

#endif // MCAL_WDT_2010_04_10_H_
