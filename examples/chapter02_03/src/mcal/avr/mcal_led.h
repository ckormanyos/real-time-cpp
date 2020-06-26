///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_LED_2014_07_28_H_
  #define _MCAL_LED_2014_07_28_H_


  #include <cstdint>

  class led
  {
  public:
    typedef std::uint8_t port_type;
    typedef std::uint8_t bval_type;

    led(const port_type p,
        const bval_type b) : port(p),
                             bval(b)
    {
      // Set the port pin to low.
      *reinterpret_cast<volatile bval_type*>(port) &= static_cast<bval_type>(~bval);

      // Set the port pin to output.
      *reinterpret_cast<volatile bval_type*>(port - 1U) |= bval;
    }

    void toggle(void) const
    {
      // Toggle the LED.
      *reinterpret_cast<volatile bval_type*>(port) ^= bval;
    }

  private:
    const port_type port;
    const bval_type bval;
  };

  extern const led led_b5;

#endif // _MCAL_LED_2014_07_28_H_
