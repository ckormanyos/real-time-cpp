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
      void init(const config_type*);

      template<typename addr_type,
               typename reg_type,
               const addr_type port,
               const reg_type bpos>
      class port_pin : private util::noncopyable
      {
      public:
        static void set_direction_output()
        {
          // Set the port pin direction to output.
          mcal::reg_access<addr_type, reg_type, pdir, bpos>::bit_set();
        }

        static void set_direction_input()
        {
          // Set the port pin direction to input.
          mcal::reg_access<addr_type, reg_type, pdir, bpos>::bit_clr();
        }

        static void set_pin_high()
        {
          // Set the port high.
          mcal::reg_access<addr_type, reg_type, port, bpos>::bit_set();
        }

        static void set_pin_low()
        {
          // Set the port low.
          mcal::reg_access<addr_type, reg_type, port, bpos>::bit_clr();
        }

        static bool read_pin_value()
        {
          // Read the port value.
          return mcal::reg_access<addr_type, reg_type, port, bpos>::bit_get();
        }

        static void toggle_pin()
        {
          // Toggle the port.
          mcal::reg_access<addr_type, reg_type, port, bpos>::bit_not();
        }

      private:
        static constexpr addr_type pdir = port - 1U;
      };
    }
  }

#endif // _MCAL_PORT_2012_06_27_H_
