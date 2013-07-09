#ifndef _MCAL_OSC_DETAIL_2013_07_09_H_
  #define _MCAL_OSC_DETAIL_2013_07_09_H_

  namespace mcal
  {
    namespace osc
    {
      namespace detail
      {
        constexpr std::uint32_t modulemode_enable   = std::uint32_t(     0x02UL);
        constexpr std::uint32_t modulemode_mask     = std::uint32_t(     0x03UL);

        constexpr std::uint32_t idlest_func         = std::uint32_t(0x00000000UL);
        constexpr std::uint32_t idlest_mask         = std::uint32_t(0x00030000UL);
      }
    }
  }

#endif // _MCAL_OSC_DETAIL_2013_07_09_H_
