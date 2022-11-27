///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_CPU_2009_02_14_H_
  #define MCAL_CPU_2009_02_14_H_

  #define MY_PROGMEM

  #include <cstdint>
  #include <type_traits>

  namespace mcal { namespace cpu {

  void init();

  inline void post_init() { }

  inline void nop() { asm volatile("nop"); }

  // SCB D-Cache Invalidate by set-way Register Definitions.
  constexpr auto scb_dcisw_way_pos            = static_cast<std::uint32_t>(30UL);
  constexpr auto scb_dcisw_way_msk            = static_cast<std::uint32_t>(3UL << scb_dcisw_way_pos);
  constexpr auto scb_dcisw_set_pos            = static_cast<std::uint32_t>(5UL);
  constexpr auto scb_dcisw_set_msk            = static_cast<std::uint32_t>(0x1FFUL << scb_dcisw_set_pos);
  constexpr auto scb_ccsidr_numsets_pos       = static_cast<std::uint32_t>(13UL);
  constexpr auto scb_ccsidr_numsets_msk       = static_cast<std::uint32_t>(0x7FFFUL << scb_ccsidr_numsets_pos);
  constexpr auto scb_ccsidr_associativity_pos = static_cast<std::uint32_t>(3UL);
  constexpr auto scb_ccsidr_associativity_msk = static_cast<std::uint32_t>(0x3FFUL << scb_ccsidr_associativity_pos);

  // Bit definitions for FLASH_ACR register.
  constexpr auto flash_acr_latency     = static_cast<std::uint32_t>(UINT8_C(0xF)); // Set to 0xF, but only 0x7 since bit 4 is only kept for legacy purposes.
  constexpr auto flash_acr_latency_0ws = static_cast<std::uint32_t>(UINT8_C(0));   // Wait states 0
  constexpr auto flash_acr_latency_1ws = static_cast<std::uint32_t>(UINT8_C(1));   // Wait states 1
  constexpr auto flash_acr_latency_2ws = static_cast<std::uint32_t>(UINT8_C(2));   // Wait states 2
  constexpr auto flash_acr_latency_3ws = static_cast<std::uint32_t>(UINT8_C(3));   // Wait states 3
  constexpr auto flash_acr_latency_4ws = static_cast<std::uint32_t>(UINT8_C(4));   // Wait states 4
  constexpr auto flash_acr_latency_5ws = static_cast<std::uint32_t>(UINT8_C(5));   // Wait states 5
  constexpr auto flash_acr_latency_6ws = static_cast<std::uint32_t>(UINT8_C(6));   // Wait states 6
  constexpr auto flash_acr_latency_7ws = static_cast<std::uint32_t>(UINT8_C(7));   // Wait states 7

  constexpr auto flash_latency_default = flash_acr_latency_3ws;

  // Cache Size ID Register functions.
  inline constexpr auto ccsidr_ways(std::uint32_t x) -> std::uint32_t {return (((x) & scb_ccsidr_associativity_msk) >> scb_ccsidr_associativity_pos); }
  inline constexpr auto ccsidr_sets(std::uint32_t x) -> std::uint32_t {return (((x) & scb_ccsidr_numsets_msk      ) >> scb_ccsidr_numsets_pos      ); }

  } } // namespace mcal::cpu

#endif // MCAL_CPU_2009_02_14_H_
