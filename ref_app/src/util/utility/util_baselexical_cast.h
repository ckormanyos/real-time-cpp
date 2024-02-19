///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_BASELEXICAL_CAST_2020_06_28_H // NOLINT(llvm-header-guard)
  #define UTIL_BASELEXICAL_CAST_2020_06_28_H

  #if ((defined(__cplusplus) && (__cplusplus >= 201703L)) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L)))
  #if !(defined(__GNUC__) && defined(__AVR__))
  #define UTIL_BASELEXICAL_CAST_HAS_CHARCONV
  #endif
  #endif

  #if defined(UTIL_BASELEXICAL_CAST_HAS_CHARCONV)
  #include <charconv>
  #include <cstdint>
  #else
  #include <algorithm>
  #include <cstddef>
  #include <cstdint>
  #include <iterator>
  #endif

  namespace util {

  #if defined(UTIL_BASELEXICAL_CAST_HAS_CHARCONV)

  template<typename UnsignedIntegerType,
           const std::uint_fast8_t BaseRepresentation = static_cast<std::uint_fast8_t>(UINT8_C(10)),
           const bool UpperCase = true>
  auto baselexical_cast(const UnsignedIntegerType& u, char* first, char* last) -> const char*
  {
    constexpr auto my_base = static_cast<int>(BaseRepresentation);

    const auto result = std::to_chars(first, last, u, my_base);

    return result.ptr;
  }

  #else

  template<typename OutputIterator,
           const bool UpperCase,
           const std::uint_fast8_t BaseRepresentation>
  struct baselexical_cast_helper
  {
  private:
    using output_value_type = typename std::iterator_traits<OutputIterator>::value_type;

  public:
    static auto extract(output_value_type) noexcept -> output_value_type = delete;
  };

  template<typename OutputIterator,
           const bool UpperCase>
  struct baselexical_cast_helper<OutputIterator, UpperCase, static_cast<std::uint_fast8_t>(UINT8_C(16))>
  {
  private:
    using output_value_type = typename std::iterator_traits<OutputIterator>::value_type;

  public:
    static auto extract(output_value_type c) noexcept -> output_value_type
    {
      if(c <= static_cast<output_value_type>(INT8_C(9)))
      {
        c =
          static_cast<output_value_type>
          (
            c + static_cast<output_value_type>('0')
          );
      }
      else if((c >= static_cast<output_value_type>(0xA)) && (c <= static_cast<output_value_type>(INT8_C(0xF)))) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
      {
        c =
          static_cast<output_value_type>
          (
              static_cast<output_value_type>(UpperCase ? static_cast<output_value_type>('A') : static_cast<output_value_type>('a'))
            + static_cast<output_value_type>(c - static_cast<output_value_type>(INT8_C(0xA)))
          );
      }

      return c;
    }
  };

  template<typename OutputIterator,
           const bool UpperCase>
  struct baselexical_cast_helper<OutputIterator, UpperCase, static_cast<std::uint_fast8_t>(UINT8_C(10))>
  {
  private:
    using output_value_type = typename std::iterator_traits<OutputIterator>::value_type;

  public:
    static auto extract(output_value_type c) noexcept -> output_value_type
    {
      if(c <= static_cast<output_value_type>(INT8_C(9)))
      {
        c =
          static_cast<output_value_type>
          (
            c + static_cast<output_value_type>('0')
          );
      }

      return c;
    }
  };

  template<typename UnsignedIntegerType,
           typename OutputIterator,
           const std::uint_fast8_t BaseRepresentation = static_cast<std::uint_fast8_t>(UINT8_C(10)),
           const bool UpperCase = true>
  auto baselexical_cast(const UnsignedIntegerType& u, OutputIterator out, OutputIterator out_dummy) -> OutputIterator
  {
    static_cast<void>(out_dummy);

    using unsigned_integer_type = UnsignedIntegerType;
    using output_value_type     = typename std::iterator_traits<OutputIterator>::value_type;

    if(u == static_cast<unsigned_integer_type>(UINT8_C(0)))
    {
      *out =
        static_cast<output_value_type>
        (
          baselexical_cast_helper<OutputIterator, UpperCase, BaseRepresentation>::extract(static_cast<output_value_type>(UINT8_C(0)))
        );
    }
    else
    {
      unsigned_integer_type x(u);

      auto out_first = out;

      while(x != static_cast<unsigned_integer_type>(UINT8_C(0))) // NOLINT(altera-id-dependent-backward-branch)
      {
        const auto c =
          static_cast<output_value_type>
          (
            x % static_cast<unsigned_integer_type>(BaseRepresentation)
          );

        *out =
          static_cast<output_value_type>
          (
            baselexical_cast_helper<OutputIterator, UpperCase, BaseRepresentation>::extract(c)
          );

        x =
          static_cast<unsigned_integer_type>
          (
            x / static_cast<unsigned_integer_type>(BaseRepresentation)
          );

        if(x != static_cast<unsigned_integer_type>(UINT8_C(0)))
        {
          ++out;
        }
      }

      std::reverse(out_first, out + static_cast<std::size_t>(UINT8_C(1)));
    }

    return out + static_cast<std::size_t>(UINT8_C(1));
  }

  #endif

  } // namespace util

#endif // UTIL_BASELEXICAL_CAST_2020_06_28_H
