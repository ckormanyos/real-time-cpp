///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2020 - 2026.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_BASELEXICAL_CAST_2020_06_28_H // NOLINT(llvm-header-guard)
  #define UTIL_BASELEXICAL_CAST_2020_06_28_H

  #include <algorithm>
  #include <array>
  #include <cstddef>
  #include <cstdint>
  #include <type_traits>

  #if ((defined(__cplusplus) && (__cplusplus >= 201703L)) || (defined(_MSVC_LANG) && (_MSVC_LANG >= 201703L))) && !defined(__AVR__)
    #include <charconv>
    #include <system_error>
    #if defined(__cpp_lib_to_chars) && (__cpp_lib_to_chars >= 201611L)
      #define UTIL_BASELEXICAL_CAST_HAS_CHARCONV // NOLINT(cppcoreguidelines-macro-usage)
    #endif
  #endif

  namespace util {

  template<typename UnsignedIntegerType,
           const std::uint_fast8_t BaseRepresentation = static_cast<std::uint_fast8_t>(UINT8_C(10)),
           const bool UpperCase = true>
  auto baselexical_cast(const UnsignedIntegerType& u, char* first, char* last) -> const char*
  {
    using local_integer_type = typename std::remove_cv<UnsignedIntegerType>::type;

    static_assert(std::is_integral<local_integer_type>::value,
                  "baselexical_cast requires an integral input type.");
    static_assert(std::is_unsigned<local_integer_type>::value && (!std::is_same<local_integer_type, bool>::value),
                  "baselexical_cast requires an unsigned, non-bool input type.");
    static_assert((BaseRepresentation >= static_cast<std::uint_fast8_t>(UINT8_C(2)))
                  && (BaseRepresentation <= static_cast<std::uint_fast8_t>(UINT8_C(36))),
                  "BaseRepresentation must be in the range [2, 36].");

    if(first == last)
    {
      return nullptr;
    }

    #if defined(UTIL_BASELEXICAL_CAST_HAS_CHARCONV)
    constexpr auto my_base = static_cast<int>(BaseRepresentation);
    const auto result = std::to_chars(first, last, u, my_base);

    if(result.ec != std::errc { })
    {
      return nullptr;
    }

    if(UpperCase)
    {
      for(auto* p = first; p != result.ptr; ++p)
      {
        if((*p >= 'a') && (*p <= 'z'))
        {
          *p = static_cast<char>(*p - ('a' - 'A'));
        }
      }
    }

    return result.ptr;
    #else
    auto* out = first;
    auto value = static_cast<local_integer_type>(u);
    constexpr auto base = static_cast<local_integer_type>(BaseRepresentation);

    do
    {
      if(out == last)
      {
        return nullptr;
      }

      const auto digit = static_cast<unsigned>(value % base);
      *out++ = static_cast<char>((digit < 10U)
                                 ? (static_cast<unsigned>('0') + digit)
                                 : (static_cast<unsigned>(UpperCase ? 'A' : 'a') + digit - 10U));
      value = static_cast<local_integer_type>(value / base);
    }
    while(value != static_cast<local_integer_type>(UINT8_C(0)));

    std::reverse(first, out);

    return out;
    #endif
  }

  } // namespace util

  #if defined(UTIL_BASELEXICAL_CAST_HAS_CHARCONV)
    #undef UTIL_BASELEXICAL_CAST_HAS_CHARCONV
  #endif

#endif // UTIL_BASELEXICAL_CAST_2020_06_28_H
