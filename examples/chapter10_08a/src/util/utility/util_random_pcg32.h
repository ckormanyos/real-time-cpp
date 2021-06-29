///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_RANDOM_PCG32_2020_01_17_H_
  #define UTIL_RANDOM_PCG32_2020_01_17_H_

  #include <algorithm>
  #include <cstddef>
  #include <cstdint>
  #include <limits>

  namespace util {

  class random_pcg32_fast_base
  {
  public:
    // We use random 64-bit unsigned integer "strings" as part
    // of the variable names within the wstp kernel.
    // We use pcg32_fast for quick generation of pseudo-random numbers.
    virtual ~random_pcg32_fast_base() = default;

  protected:
    using internal_type = std::uint64_t;

    explicit random_pcg32_fast_base(const internal_type) { }

    random_pcg32_fast_base(const random_pcg32_fast_base&) = default;

    random_pcg32_fast_base& operator=(const random_pcg32_fast_base&) = default;

    template<typename ArithmeticType>
    static ArithmeticType rotr(const ArithmeticType& value_being_shifted,
                               const std::size_t     bits_to_shift)
    {
      const std::size_t left_shift_amount =
        std::numeric_limits<ArithmeticType>::digits - bits_to_shift;

      const ArithmeticType part1 = ((bits_to_shift > 0U) ? ArithmeticType(value_being_shifted >> bits_to_shift)     : value_being_shifted);
      const ArithmeticType part2 = ((bits_to_shift > 0U) ? ArithmeticType(value_being_shifted << left_shift_amount) : 0U);

      return ArithmeticType(part1 | part2);
    }

    template<typename OutputType, typename InternalType>
    static OutputType output(const InternalType internal_value)
    {
      using local_output_type   = OutputType;
      using local_internal_type = InternalType;

      using bitcount_t = std::size_t;

      constexpr bitcount_t bits         = bitcount_t(sizeof(local_internal_type) * 8U);
      constexpr bitcount_t xtypebits    = bitcount_t(sizeof(local_output_type)   * 8U);
      constexpr bitcount_t sparebits    = bits - xtypebits;
      constexpr bitcount_t wantedopbits =   ((xtypebits >= 128U) ? 7U
                                          : ((xtypebits >=  64U) ? 6U
                                          : ((xtypebits >=  32U) ? 5U
                                          : ((xtypebits >=  16U) ? 4U
                                          :                        3U))));

      constexpr bitcount_t opbits       = ((sparebits >= wantedopbits) ? wantedopbits : sparebits);
      constexpr bitcount_t amplifier    = wantedopbits - opbits;
      constexpr bitcount_t mask         = (1ULL << opbits) - 1U;
      constexpr bitcount_t topspare     = opbits;
      constexpr bitcount_t bottomspare  = sparebits - topspare;
      constexpr bitcount_t xshift       = (topspare + xtypebits) / 2U;

      const bitcount_t rot =
        ((opbits != 0U) ? (bitcount_t(internal_value >> (bits - opbits)) & mask)
                        : 0U);

      const bitcount_t amprot = (rot << amplifier) & mask;

      const local_internal_type internal_value_xor = internal_value ^ local_internal_type(internal_value >> xshift);

      const local_output_type result = random_pcg32_fast_base::rotr(local_output_type(internal_value_xor >> bottomspare), amprot);

      return result;
    }
  };

  class random_pcg32_fast : public random_pcg32_fast_base
  {
  public:
    using result_type = std::uint32_t;

    static constexpr random_pcg32_fast_base::internal_type default_seed = static_cast<random_pcg32_fast_base::internal_type>(0xCAFEF00DD15EA5E5ULL);

    explicit random_pcg32_fast(const random_pcg32_fast_base::internal_type state = default_seed)
      : random_pcg32_fast_base(state),
        my_inc  (default_increment),
        my_state(bump(state + increment())) { }

    random_pcg32_fast(const random_pcg32_fast& other)
      : random_pcg32_fast_base(other),
        my_inc  (other.my_inc),
        my_state(other.my_state) { }

    virtual ~random_pcg32_fast() = default;

    random_pcg32_fast& operator=(const random_pcg32_fast& other)
    {
      static_cast<void>(random_pcg32_fast_base::operator=(other));

      if(this != &other)
      {
        my_inc   = other.my_inc;
        my_state = other.my_state;
      }

      return *this;
    }

    void seed(const random_pcg32_fast_base::internal_type state = default_seed)
    {
      my_inc = default_increment;

      my_state = bump(state + increment());
    }

    result_type operator()()
    {
      const result_type value = output<result_type, random_pcg32_fast_base::internal_type>(base_generate0());

      return value;
    }

    static random_pcg32_fast::result_type (min)() { return (std::numeric_limits<result_type>::min)(); }
    static random_pcg32_fast::result_type (max)() { return (std::numeric_limits<result_type>::max)(); }

  private:
    static constexpr random_pcg32_fast_base::internal_type default_multiplier = static_cast<random_pcg32_fast_base::internal_type>(6364136223846793005ULL);
    static constexpr random_pcg32_fast_base::internal_type default_increment  = static_cast<random_pcg32_fast_base::internal_type>(1442695040888963407ULL);

    random_pcg32_fast_base::internal_type my_inc;
    random_pcg32_fast_base::internal_type my_state;

    static internal_type multiplier() { return default_multiplier; }

    static internal_type increment () { return default_increment; }

    internal_type bump(const random_pcg32_fast_base::internal_type state)
    {
      return random_pcg32_fast_base::internal_type(state * multiplier()) + increment();
    }

    internal_type base_generate0()
    {
      const random_pcg32_fast_base::internal_type old_state = my_state;

      my_state = bump(my_state);

      return old_state;
    }
  };

  } // namespace util

#endif // UTIL_RANDOM_PCG32_2020_01_17_H_
