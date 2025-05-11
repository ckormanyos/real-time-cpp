///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_RANDOM_2020_06_11_H
  #define MCAL_RANDOM_2020_06_11_H

  #include <mcal_cpu.h>
  #include <mcal_port.h>
  #include <mcal_port_pin_dummy.h>
  #include <mcal_spi/mcal_spi_software_port_driver.h>
  #include <util/utility/util_time.h>

  #include <cstdint>
  #include <limits>

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

    static_assert(static_cast<std::uint_fast8_t>(std::numeric_limits<result_type>::digits % 8) == std::uint_fast8_t { UINT8_C(0) },
                  "Error: Integral type must have a multiple of 8 digits.");

    static_assert((     std::numeric_limits<result_type>::is_integer
                   && (!std::numeric_limits<result_type>::is_signed)),
                  "Error: Integral type must an unsigned integral type.");

    explicit random_engine_reverse_z_diode_raw(const result_type = result_type()) noexcept { }

    random_engine_reverse_z_diode_raw(const random_engine_reverse_z_diode_raw&) noexcept { }

    random_engine_reverse_z_diode_raw(const random_engine_reverse_z_diode_raw&&) noexcept { }

    ~random_engine_reverse_z_diode_raw() noexcept { }

    auto operator=(const random_engine_reverse_z_diode_raw&) noexcept -> random_engine_reverse_z_diode_raw&
    {
      return *this;
    }

    auto operator=(const random_engine_reverse_z_diode_raw&&) noexcept -> random_engine_reverse_z_diode_raw&
    {
      return *this;
    }

    static constexpr auto (min)() noexcept -> result_type
    {
      return result_type { UINT8_C(0) };
    }

    static constexpr auto (max)() noexcept -> result_type
    {
      return (std::numeric_limits<result_type>::max)();
    }

    auto seed(result_type = result_type()) noexcept -> void { }

    auto operator()() noexcept -> result_type
    {
      // Get random value having type result_type.
      return get_value(my_spi);
    }

    auto discard(unsigned long long skip) noexcept -> void
    {
      for(unsigned long long i = static_cast<unsigned long long>(UINT8_C(0)); i < skip; ++i)
      {
        const result_type tmp { get_value(my_spi) };

        static_cast<void>(tmp);
      }
    }

  private:
    spi_type my_spi { };

    static auto get_value(util::communication_base& com) noexcept -> result_type
    {
      result_type value { UINT8_C(0) };

      for(std::uint_fast8_t  i { std::uint_fast8_t { UINT8_C(0) } };
                             i < static_cast<std::uint_fast8_t>(std::numeric_limits<result_type>::digits / 8);
                           ++i)
      {
        std::uint8_t by;

        com.send(UINT8_C(0xFF));
        com.recv(by);

        value |= static_cast<result_type>(static_cast<result_type>(by) << static_cast<unsigned>(i * 8U));
      }

      return value;
    }
  };

  using spi_software_port_driver_type =
    mcal::spi::spi_software_port_driver<mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, std::uint8_t { UINT8_C(4) }>,
                                        mcal::port::port_pin_dummy,
                                        mcal::port::port_pin_dummy,
                                        mcal::port::port_pin<std::uint8_t, std::uint8_t, mcal::reg::portc, std::uint8_t { UINT8_C(5) }>,
                                        static_cast<std::uint_fast16_t>(UINT8_C(45)),
                                        false>;

  } // namespace detail

  using default_random_engine = detail::random_engine_reverse_z_diode_raw<detail::spi_software_port_driver_type, std::uint8_t>;

  } } // namespace mcal::random

#endif // MCAL_RANDOM_2020_06_11_H
