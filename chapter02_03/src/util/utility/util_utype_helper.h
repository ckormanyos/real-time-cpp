///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_UTYPE_HELPER_2012_01_23_H_
  #define UTIL_UTYPE_HELPER_2012_01_23_H_

  #include <cstdint>

  namespace util
  {
    template<const unsigned utype_bit_count> struct utype_helper
    {
      static_assert(utype_bit_count <= 64U,
                    "the bit count of the unsigned type can not exceed 64");

      typedef std::uint64_t exact_type;
    };

    template<> struct utype_helper<0U> { typedef std::uint8_t exact_type; };
    template<> struct utype_helper<1U> { typedef std::uint8_t exact_type; };
    template<> struct utype_helper<2U> { typedef std::uint8_t exact_type; };
    template<> struct utype_helper<3U> { typedef std::uint8_t exact_type; };
    template<> struct utype_helper<4U> { typedef std::uint8_t exact_type; };
    template<> struct utype_helper<5U> { typedef std::uint8_t exact_type; };
    template<> struct utype_helper<6U> { typedef std::uint8_t exact_type; };
    template<> struct utype_helper<7U> { typedef std::uint8_t exact_type; };
    template<> struct utype_helper<8U> { typedef std::uint8_t exact_type; };

    template<> struct utype_helper<9U>  { typedef std::uint16_t exact_type; };
    template<> struct utype_helper<10U> { typedef std::uint16_t exact_type; };
    template<> struct utype_helper<11U> { typedef std::uint16_t exact_type; };
    template<> struct utype_helper<12U> { typedef std::uint16_t exact_type; };
    template<> struct utype_helper<13U> { typedef std::uint16_t exact_type; };
    template<> struct utype_helper<14U> { typedef std::uint16_t exact_type; };
    template<> struct utype_helper<15U> { typedef std::uint16_t exact_type; };
    template<> struct utype_helper<16U> { typedef std::uint16_t exact_type; };

    template<> struct utype_helper<17U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<18U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<19U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<20U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<21U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<22U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<23U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<24U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<25U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<26U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<27U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<28U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<29U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<30U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<31U> { typedef std::uint32_t exact_type; };
    template<> struct utype_helper<32U> { typedef std::uint32_t exact_type; };
  }

#endif // UTIL_UTYPE_HELPER_2012_01_23_H_
