#ifndef _UTIL_UTYPE_HELPER_2012_01_23_H_
  #define _UTIL_UTYPE_HELPER_2012_01_23_H_

  #include <cstdint>
  #include <cstddef>

  namespace util
  {
    template<const std::size_t> struct utype_helper { typedef std::uint64_t exact; };
    template<> struct utype_helper<0U> { typedef std::uint8_t exact; };
    template<> struct utype_helper<1U> { typedef std::uint8_t exact; };
    template<> struct utype_helper<2U> { typedef std::uint8_t exact; };
    template<> struct utype_helper<3U> { typedef std::uint8_t exact; };
    template<> struct utype_helper<4U> { typedef std::uint8_t exact; };
    template<> struct utype_helper<5U> { typedef std::uint8_t exact; };
    template<> struct utype_helper<6U> { typedef std::uint8_t exact; };
    template<> struct utype_helper<7U> { typedef std::uint8_t exact; };
    template<> struct utype_helper<8U> { typedef std::uint8_t exact; };

    template<> struct utype_helper<9U>  { typedef std::uint16_t exact; };
    template<> struct utype_helper<10U> { typedef std::uint16_t exact; };
    template<> struct utype_helper<11U> { typedef std::uint16_t exact; };
    template<> struct utype_helper<12U> { typedef std::uint16_t exact; };
    template<> struct utype_helper<13U> { typedef std::uint16_t exact; };
    template<> struct utype_helper<14U> { typedef std::uint16_t exact; };
    template<> struct utype_helper<15U> { typedef std::uint16_t exact; };
    template<> struct utype_helper<16U> { typedef std::uint16_t exact; };

    template<> struct utype_helper<17U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<18U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<19U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<20U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<21U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<22U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<23U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<24U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<25U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<26U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<27U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<28U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<29U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<30U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<31U> { typedef std::uint32_t exact; };
    template<> struct utype_helper<32U> { typedef std::uint32_t exact; };
  }

#endif // _UTIL_UTYPE_HELPER_2012_01_23_H_
