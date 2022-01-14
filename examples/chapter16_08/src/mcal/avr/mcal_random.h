///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_RANDOM_2020_06_11_H_
  #define MCAL_RANDOM_2020_06_11_H_

  #include <cstdint>
  #include <limits>

  #include <mcal_cpu.h>
  #include <mcal_port.h>
  #include <mcal_port_pin_dummy.h>
  #include <mcal_spi/mcal_spi_software_port_driver.h>
  #include <util/utility/util_time.h>

  namespace mcal { namespace random {

  namespace detail {

  template<typename SpiType,
           typename UnsignedIntegralType>
  class random_engine_reverse_z_diode_raw
  {
  private:
    using spi_type = SpiType;

  public:
    using result_type = UnsignedIntegralType;

    static_assert(std::uint_fast8_t(std::numeric_limits<result_type>::digits % 8) == 0U,
                  "Error: Integral type must have a multiple of 8 digits.");

    static_assert((   (std::numeric_limits<result_type>::is_integer == true)
                   && (std::numeric_limits<result_type>::is_signed  == false)),
                  "Error: Integral type must an unsigned integral type.");

    random_engine_reverse_z_diode_raw(const result_type = result_type()) noexcept
      : my_spi() { }

    random_engine_reverse_z_diode_raw(const random_engine_reverse_z_diode_raw&)
      : my_spi() { }

    random_engine_reverse_z_diode_raw(const random_engine_reverse_z_diode_raw&&)
      : my_spi() { }

    random_engine_reverse_z_diode_raw& operator=(const random_engine_reverse_z_diode_raw&)
    {
      return *this;
    }

    random_engine_reverse_z_diode_raw& operator=(const random_engine_reverse_z_diode_raw&&)
    {
      return *this;
    }

    static constexpr result_type(min)() noexcept
    {
      return result_type(0U);
    }

    static constexpr result_type(max)() noexcept
    {
      return (std::numeric_limits<result_type>::max)();
    }

    void seed(result_type = result_type()) { }

    result_type operator()() noexcept
    {
      // Get random value having type result_type.
      return get_value(my_spi);
    }

    void discard(unsigned long long skip) noexcept
    {
      for(unsigned long long i = 0U; i < skip; ++i)
      {
        const result_type tmp = get_value(my_spi);

        static_cast<void>(tmp);
      }
    }

  private:
    spi_type my_spi;

    static result_type get_value(util::communication_base& com) noexcept
    {
      result_type value = result_type(0U);

      for(std::uint_fast8_t i = 0U; i < std::uint_fast8_t(std::numeric_limits<result_type>::digits / 8); ++i)
      {
        std::uint8_t by;

        com.send(UINT8_C(0xFFU));
        com.recv(by);

        value |= result_type(result_type(by) << (i * 8U));
      }

      return value;
    }
  };

  using spi_software_port_driver_type =
    mcal::spi::spi_software_port_driver<mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, 4U>,
                                        mcal::port::port_pin_dummy,
                                        mcal::port::port_pin_dummy,
                                        mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, 5U>,
                                        45U,
                                        false>;

  } // namespace detail

  using default_random_engine =
    detail::random_engine_reverse_z_diode_raw<detail::spi_software_port_driver_type,
                                              std::uint8_t>;

  } } // namespace mcal::random

#endif // MCAL_RANDOM_2020_06_11_H_
