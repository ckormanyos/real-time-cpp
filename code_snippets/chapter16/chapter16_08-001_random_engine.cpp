/////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter16_08-001_random_engine.cpp

// See also https://godbolt.org/z/7fW8jYKKx

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>

namespace mcal { namespace random {

class random_engine
{
public:
  using result_type = std::uint64_t;

  random_engine() = default;

  ~random_engine() = default;

  random_engine(const random_engine&) = delete;
  random_engine(random_engine&&) noexcept = delete;

  auto operator=(const random_engine&) -> random_engine& = delete;
  auto operator=(random_engine&&) noexcept -> random_engine& = delete;

  auto entropy() const noexcept -> std::uint_fast8_t
  {
    return 1U;
  }

  result_type operator()()
  {
    const result_type basis_for_seed = seed_value<result_type>();

    return basis_for_seed;
  }

private:
  template<typename IntegralType>
  static auto seed_value() -> IntegralType
  {
    using strftime_uint8_array_type = std::array<std::uint8_t, static_cast<std::size_t>(UINT8_C(64))>;

    strftime_uint8_array_type buf_u8 { }; buf_u8.fill(static_cast<std::uint8_t>(UINT8_C(0)));

    std::size_t str_tm_len { };

    {
      // Get the time.
      const std::time_t now = std::time(nullptr);

      using strftime_char_array_type = std::array<char, std::tuple_size<strftime_uint8_array_type>::value>;

      strftime_char_array_type buf { };

      #if defined(_MSC_VER)
      #pragma warning(push)
      #pragma warning(disable : 4996)
      #endif
      // Format the time in a calendar-style.
      strftime(buf.data(), buf.size(), "%c", std::localtime(&now)); // NOLINT(concurrency-mt-unsafe)
      #if defined(_MSC_VER)
      #pragma warning( pop )
      #endif

      std::stringstream strm;

      // Append the clock()-time in arbitrary units.
      strm << buf.data();
      strm << '+' << std::setfill('0') << std::setw(static_cast<std::streamsize>(INT8_C(9))) << std::clock();

      const auto str_tm = strm.str();

      str_tm_len = str_tm.length();

      std::copy(str_tm.cbegin(), str_tm.cend(), buf_u8.begin());
    }

    using local_integral_type = IntegralType;

    return static_cast<local_integral_type>(crc_crc64(buf_u8.data(), str_tm_len));
  }

  static constexpr auto test() noexcept -> bool;

  template<const std::size_t NumberOfBits,
            typename UnsignedIntegralType>
  static constexpr auto crc_bitwise_template(const std::uint8_t*        message,
                                              const std::size_t          count,
                                              const UnsignedIntegralType polynomial, // NOLINT(bugprone-easily-swappable-parameters)
                                              const UnsignedIntegralType initial_value,
                                              const UnsignedIntegralType final_xor_value) -> UnsignedIntegralType
  {
    using value_type = UnsignedIntegralType;

    // The data_type is fixed to exactly 8-bits in width at the moment.
    using data_type = std::uint8_t;

    value_type crc = initial_value;

    // Perform the polynomial division, one element at a time.
    for(auto data_index = static_cast<std::size_t>(UINT8_C(0)); data_index < count; ++data_index)
    {
      // Obtain the next data element (and reflect it if necessary).
      const data_type next_data_element = message[data_index]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

      {
        constexpr auto left_shift_amount =
          static_cast<std::size_t>
          (
            std::numeric_limits<value_type>::digits - std::numeric_limits<data_type >::digits
          );

        crc ^= static_cast<value_type>(static_cast<value_type>(next_data_element) << left_shift_amount);
      }

      // Process the next data byte, one bit at a time.
      for(std::uint_fast8_t   index = 0U;
                              index < static_cast<std::uint_fast8_t>(std::numeric_limits<data_type>::digits);
                            ++index)
      {
        const auto high_bit_value =
          static_cast<value_type>
          (
              crc
            & static_cast<value_type>
              (
                static_cast<std::uintmax_t>(UINT8_C(1)) << static_cast<unsigned>(std::numeric_limits<value_type>::digits - 1)
              )
          );

        const bool high_bit_of_crc_is_set = (high_bit_value != static_cast<value_type>(UINT8_C(0)));

        crc = crc << static_cast<unsigned>(UINT8_C(1));

        if(high_bit_of_crc_is_set)
        {
          // Shift through the polynomial. Also left-justify the
          // polynomial within the width of value_type, if necessary.

          crc ^= static_cast<value_type>(polynomial);
        }
      }
    }

    // Perform the final XOR on the result.
    crc ^= final_xor_value;

    return crc;
  }

  static constexpr auto crc_crc64(const std::uint8_t* message, const std::size_t count) -> std::uint64_t
  {
    // check: 0x6C40DF5F0B497347
    return crc_bitwise_template<static_cast<std::size_t>(UINT8_C(64)), std::uint64_t>
    (
      message,
      count,
      static_cast<std::uint64_t>(UINT64_C(0x42F0E1EBA9EA3693)),
      static_cast<std::uint64_t>(UINT64_C(0x0000000000000000)),
      static_cast<std::uint64_t>(UINT64_C(0x0000000000000000))
    );
  }
};

} } // namespace mcal::random

auto do_something() -> void;

auto do_something() -> void
{
        mcal::random::random_engine                       rng;
  const typename mcal::random::random_engine::result_type seed(rng());
        std::mt19937_64                                   generator(seed);

  std::uniform_int_distribution<unsigned>
    distribution
    {
      static_cast<unsigned>(UINT8_C(1)),
      static_cast<unsigned>(UINT16_C(1023))
    };

  const auto flg = std::cout.flags();

  // Print the seed.
  std::cout << "Seed is: 0x"
            << std::hex
            << std::setw(static_cast<std::streamsize>(INT8_C(16)))
            << std::setfill('0')
            << std::uppercase
            << seed
            << ". ";

  // Generate 9 pseudo-random numbers in [1, 1023].
  const std::array<unsigned, static_cast<std::size_t>(UINT8_C(3))> random_numbers =
  {
    distribution(generator),
    distribution(generator),
    distribution(generator)
  };

  std::cout << "Random numbers in [1, 1023]: ";
  std::cout << std::dec << std::setw(static_cast<std::streamsize>(INT8_C(5))) << std::setfill(' ') << random_numbers[static_cast<std::size_t>(UINT8_C(0))] << ", ";
  std::cout << std::dec << std::setw(static_cast<std::streamsize>(INT8_C(5))) << std::setfill(' ') << random_numbers[static_cast<std::size_t>(UINT8_C(1))] << ", ";
  std::cout << std::dec << std::setw(static_cast<std::streamsize>(INT8_C(5))) << std::setfill(' ') << random_numbers[static_cast<std::size_t>(UINT8_C(2))] << std::endl;

  std::cout.flags(flg);
}

auto main() -> int;

auto main() -> int
{
  // Generate 20 sequences of 3 pseudo-random numbers.
  for(auto i = static_cast<std::uint_fast8_t>(UINT8_C(0)); i < static_cast<std::uint_fast8_t>(UINT8_C(20)); ++i)
  {
    do_something();
  }
}
