///////////////////////////////////////////////////////////////////
//                                                               //
//  Copyright Iliass Mahjoub 2022.                               //
//  Copyright Christopher Kormanyos 2019 - 2025.                 //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
//                                                               //
///////////////////////////////////////////////////////////////////

#ifndef PI_SPIGOT_2022_06_08_H
  #define PI_SPIGOT_2022_06_08_H

  #include <math/checksums/hash/hash_base.h>

  #include <algorithm>
  #include <array>
  #include <iterator>
  #include <type_traits>

  #if (__cplusplus >= 201703L)
  namespace math::constants {
  #else
  namespace math { namespace constants {
  #endif

  namespace detail {

  template<typename InputIterator,
           typename IntegralType>
  constexpr auto advance_and_point(InputIterator it, IntegralType n) -> InputIterator
  {
    using local_difference_type = typename std::iterator_traits<InputIterator>::difference_type;

    return it + static_cast<local_difference_type>(n);
  }

  } // namespace detail

  template<const std::uint32_t ResultDigit,
           const std::uint32_t LoopDigit,
           typename UnsignedSmallType = std::uint32_t,
           typename UnsignedLargeType = std::uint64_t>
  class pi_spigot
  {
  public:
    using unsigned_small_type = UnsignedSmallType;
    using unsigned_large_type = UnsignedLargeType;

  private:
    using callback_type = void(*)(const std::uint32_t);

    static constexpr auto result_digit() -> std::uint32_t { return ResultDigit; }

    static constexpr auto loop_digit() -> std::uint32_t { return LoopDigit; }

    static constexpr auto input_scale(std::uint32_t x) -> std::uint32_t
    {
      return
          x
        * (
              static_cast<std::uint32_t>
              (
                  static_cast<std::uint32_t>(static_cast<std::uint32_t>(UINT8_C(10)) * loop_digit())
                / static_cast<std::uint32_t>(UINT8_C(3))
              )
            + static_cast<std::uint32_t>(UINT8_C(1))
          ) / loop_digit();
    }

  public:
    static constexpr auto get_input_static_size() -> std::uint32_t { return input_scale(result_digit()); }

    constexpr pi_spigot() = default; // LCOV_EXCL_LINE

    constexpr pi_spigot(const pi_spigot&) = delete;

    constexpr pi_spigot(pi_spigot&&) = delete;

    ~pi_spigot() = default; // LCOV_EXCL_LINE

    constexpr auto operator=(const pi_spigot&) -> pi_spigot& = delete;

    constexpr auto operator=(pi_spigot&&) -> pi_spigot& = delete;

    constexpr auto get_operation_count() const -> std::uintmax_t
    {
      return my_operation_count;
    }

    template<typename InputIteratorType>
    auto calculate(InputIteratorType my_pi_in,
                   callback_type pfn_callback_to_report_digits10 = nullptr,
                   ::math::checksums::hash::hash_stream_base* p_hash = nullptr) -> void
    {
      // Use pi_spigot::calculate() to calculate result_digit
      // decimal digits of pi.

      // The caller is responsible for providing the output memory
      // for the result of pi. The input memory used for internal
      // calculation details while performing the calculation is
      // provided by the pi_spigot class itself.

      if(p_hash != nullptr)
      {
        p_hash->initialize();
      }

      using local_input_iterator_type = InputIteratorType;
      using local_input_value_type = typename std::iterator_traits<local_input_iterator_type>::value_type;

      // Invalidate the input container values at the first 32 indices.
      const std::uint32_t
        invalidate_size
        {
          (std::min)(std::uint32_t { UINT8_C(32) }, get_input_static_size())
        };

      std::fill(my_pi_in,
                detail::advance_and_point(my_pi_in, invalidate_size),
                (std::numeric_limits<local_input_value_type>::max)());

      unsigned_small_type val_c { static_cast<unsigned_small_type>(static_cast<unsigned>(UINT8_C(0))) };

      my_output_count = static_cast<std::uint32_t>(UINT8_C(0));
      my_operation_count = static_cast<std::uintmax_t>(UINT8_C(0));

      if(pfn_callback_to_report_digits10 != nullptr)
      {
        pfn_callback_to_report_digits10(my_output_count);
      }

      constexpr unsigned_large_type p10_loop { static_cast<unsigned_large_type>(pow10(loop_digit())) };

      // Operation count Mathematica(R), example for loop_digit=9.
      // Sum[Floor[((d - j) (Floor[((10 9)/3)] + 1))/9], {j, 0, Floor[d/9] 9, 9}]

      for(std::uint32_t j = { static_cast<std::uint32_t>(UINT8_C(0)) };
                        j < result_digit();
                        j = static_cast<std::uint32_t>(static_cast<std::uint32_t>(j + loop_digit())))
      {
        unsigned_large_type val_d { static_cast<unsigned_large_type>(UINT8_C(0)) };

        const auto ilim { input_scale(result_digit() - j) };

        for(auto   i = static_cast<std::uint32_t>(UINT8_C(0));
                   i < ilim;
                 ++i)
        {
          const auto my_index =
            static_cast<std::uint32_t>
            (
                static_cast<std::uint32_t>(ilim - static_cast<std::uint32_t>(UINT8_C(1)))
              - i
            );

          const auto di =
            ((j == static_cast<std::uint32_t>(UINT8_C(0)))
              ? static_cast<unsigned_large_type>(d_init())
              : static_cast<unsigned_large_type>(*detail::advance_and_point(my_pi_in, my_index)));

          val_d =
            static_cast<unsigned_large_type>
            (
                val_d
              + static_cast<unsigned_large_type>(di * p10_loop)
            );

          const auto val_b =
            static_cast<std::uint32_t>
            (
                static_cast<std::uint32_t>
                (
                  my_index * static_cast<std::uint32_t>(UINT8_C(2))
                )
              + static_cast<std::uint32_t>(UINT8_C(1))
            );

          *detail::advance_and_point(my_pi_in, my_index) = static_cast<std::uint32_t>(val_d % val_b);

          val_d /= val_b;

          if(my_index > static_cast<std::uint32_t>(UINT8_C(1)))
          {
            val_d *= my_index;
          }

          ++my_operation_count;
        }

        // Parse the next digits of pi, where the group has loop_digit digits.
        // If loop_digit is 4, for instance, then successive groups
        // of digits have a form such as: 3141, 5926, ..., etc.

        // Sequences of consecutive zeros having length as large as or larger
        // than the loop_digit count will stop successful spigot iteration.
        // A group of four sequential zeros, for instance, at a point slightly
        // above 50,000 digits stops iteration for a loop_digit count of 4.
        // For this reason, we usually use a loop_digit count of 9, which
        // has been tested on the PC up to 1,000,001 (a million) decimal digits.

        const auto next_digits =
          static_cast<unsigned_small_type>
          (
            val_c + static_cast<unsigned_small_type>(val_d / p10_loop)
          );

        val_c = static_cast<unsigned_small_type>(val_d % p10_loop);

        const std::uint_fast8_t
          n_loop
          {
            static_cast<std::uint_fast8_t>
            (
              (std::min)
              (
                loop_digit(),
                static_cast<std::uint32_t>(result_digit() - j)
              )
            )
          };

        unsigned_small_type scale10 { pow10(loop_digit() - static_cast<std::uint32_t>(UINT8_C(1))) };

        using output_chars_array_type = std::array<std::uint8_t, static_cast<std::size_t>(loop_digit())>;

        output_chars_array_type output_chars_as_bytes_hash_array { };

        for(std::uint_fast8_t loop_index { UINT8_C(0) }; loop_index < n_loop; ++loop_index)
        {
          const auto output_value =
            static_cast<std::uint_fast8_t>
            (
              static_cast<unsigned_small_type>
              (
                  static_cast<unsigned_small_type>(next_digits / scale10)
                % static_cast<unsigned>(UINT8_C(10))
              )
            );

          if(p_hash != nullptr)
          {
            output_chars_as_bytes_hash_array[static_cast<std::size_t>(loop_index)] =
              static_cast<std::uint8_t>
              (
                output_value + static_cast<std::uint8_t>(UINT8_C(0x30))
              );
          }

          scale10 = static_cast<unsigned_small_type>(scale10 / static_cast<unsigned>(UINT8_C(10)));
        }

        if(p_hash != nullptr)
        {
          using local_count_type = typename ::math::checksums::hash::hash_stream_base::count_type;

          const local_count_type
            length_to_hash
            {
              (std::min)
              (
                static_cast<local_count_type>(n_loop),
                static_cast<local_count_type>(std::tuple_size_v<output_chars_array_type>)
              )
            };

          p_hash->process(output_chars_as_bytes_hash_array.data(), length_to_hash);
        }

        my_output_count += n_loop;

        if(pfn_callback_to_report_digits10 != nullptr)
        {
          pfn_callback_to_report_digits10(my_output_count);
        }
      }

      ++my_count_of_calculations;

      if(pfn_callback_to_report_digits10 != nullptr)
      {
        pfn_callback_to_report_digits10(my_output_count);
      }

      if(p_hash != nullptr)
      {
        p_hash->finalize();
      }
    }

    auto get_output_count() const -> std::uint32_t { return my_output_count; }

    static auto get_count_of_calculations() -> std::uint32_t { return my_count_of_calculations; }

  private:
    static std::uint32_t my_count_of_calculations;

    std::uintmax_t my_operation_count { };
    std::uint32_t  my_output_count { };

    static constexpr auto pow10(std::uint32_t n) -> unsigned_small_type
    {
      return
      (
        (n == static_cast<std::uint32_t>(UINT8_C(0)))
          ? static_cast<unsigned_small_type>(UINT8_C(1))
          : static_cast<unsigned_small_type>
            (
                pow10(n - static_cast<std::uint32_t>(UINT8_C(1)))
              * static_cast<unsigned>(UINT8_C(10))
            )
      );
    }

    static constexpr auto d_init() -> unsigned_small_type
    {
      return
        static_cast<unsigned_small_type>
        (
          pow10(loop_digit()) / static_cast<unsigned>(UINT8_C(5))
        );
    }

    static_assert(loop_digit() <= static_cast<std::uint32_t>(std::numeric_limits<unsigned_small_type>::digits10),
                  "Error: loop_digit exceeds the number of base-10 digits in its constituent unsigned_small_type");

    static_assert(result_digit() <= static_cast<std::uint32_t>(UINT32_C(100001)),
                  "Error: result_digit exceeds its limit of 100,001");

    static_assert(std::numeric_limits<unsigned_small_type>::digits * 2 == std::numeric_limits<unsigned_large_type>::digits,
                  "Error: unsigned_large_type must be exactly twice as wide as unsigned_small_type");

    static_assert((!std::numeric_limits<unsigned_small_type>::is_signed),
                  "Error: unsigned_small_type must be unsigned");

    static_assert((!std::numeric_limits<unsigned_large_type>::is_signed),
                  "Error: unsigned_large_type must be unsigned");
  };

  template<const std::uint32_t ResultDigit,
           const std::uint32_t LoopDigit,
           typename UnsignedSmallType,
           typename UnsignedLargeType>
  std::uint32_t pi_spigot<ResultDigit, LoopDigit, UnsignedSmallType, UnsignedLargeType>::my_count_of_calculations { };

  #if (__cplusplus >= 201703L)
  } // namespace math::constants
  #else
  } // namespace constants
  } // namespace math
  #endif

#endif // PI_SPIGOT_2022_06_08_H
