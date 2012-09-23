#ifndef _MCAL_PORT_2012_06_27_H_
  #define _MCAL_PORT_2012_06_27_H_

  #include <util/utility/util_type.h>
  #include <util/utility/util_noncopyable.h>
  #include <mcal_reg_access.h>

  namespace mcal
  {
    namespace port
    {
      typedef void config_type;
      inline void init(const config_type*) { }

      class port_pin : private util::noncopyable
      {
      public:
        static void set_direction_output() { }
        static void set_direction_input() { }
        static void set_pin_high() { }
        static void set_pin_low() { }
        static bool read_pin_value() { }
        static void toggle_pin() { }
      };
    }
  }

#endif // _MCAL_PORT_2012_06_27_H_
