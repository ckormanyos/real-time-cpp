///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_BASELEXICAL_CAST_2020_06_28_H // NOLINT(llvm-header-guard)
  #define UTIL_BASELEXICAL_CAST_2020_06_28_H

  #include <cstdint>
  #include <type_traits>

  namespace util {

  template<typename UnsignedIntegerType,
           const std::uint_fast8_t BaseRepresentation = static_cast<std::uint_fast8_t>(UINT8_C(10)),
           const bool UpperCase = true>
  auto baselexical_cast(const UnsignedIntegerType& u, char* first, const char* last) -> const char*;

  template<typename UnsignedIntegerType,
           const std::uint_fast8_t BaseRepresentation,
           const bool UpperCase>
  auto baselexical_cast(const UnsignedIntegerType& u, char* first, const char* last) -> const char*
  {
    using local_integer_type = std::remove_cv_t<UnsignedIntegerType>;

    static_assert(std::is_integral_v<local_integer_type>,
                  "baselexical_cast requires an integral input type.");

    static_assert(std::is_unsigned_v<local_integer_type> && (!std::is_same_v<local_integer_type, bool>),
                  "baselexical_cast requires an unsigned, non-bool input type.");

    static_assert((BaseRepresentation >= static_cast<std::uint_fast8_t>(UINT8_C(2)))
                  && (BaseRepresentation <= static_cast<std::uint_fast8_t>(UINT8_C(36))),
                  "BaseRepresentation must be in the range [2, 36].");

    if(first == last)
    {
      return nullptr;
    }

    auto* out = first;

    auto value = static_cast<local_integer_type>(u);

    constexpr auto base = static_cast<local_integer_type>(BaseRepresentation);

    do
    {
      if(out == last)
      {
        return nullptr;
      }

      const auto digit { static_cast<unsigned>(value % base) };

      *out++ = // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        static_cast<char>
        (
          (digit < 10U) ? (static_cast<unsigned>('0') + digit)                         // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
                        : (static_cast<unsigned>(UpperCase ? 'A' : 'a') + digit - 10U) // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
        );

      value = static_cast<local_integer_type>(value / base);
    }
    while(value != static_cast<local_integer_type>(UINT8_C(0)));

    auto* reverse = out; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

    while(first < --reverse) // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    {
      const auto digit { *first };

      *first++ = *reverse; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

      *reverse = digit;
    }

    return out;
  }

  } // namespace util

#endif // UTIL_BASELEXICAL_CAST_2020_06_28_H
