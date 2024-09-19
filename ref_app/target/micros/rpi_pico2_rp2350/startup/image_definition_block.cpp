///////////////////////////////////////////////////////////////////////////////
//  Copyright Amine Chalandi 2024.
//  Copyright Christopher Kormanyos 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

/******************************************************************************************
  Filename    : image_definition_block.c
  
  Core        : ARM Cortex-M33
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 29.08.2024
  
  Description : Image definition block for Raspberry Pi Pico 2
  
******************************************************************************************/

#include <stdint.h>

extern "C"
const uint32_t __attribute__((section(".image_start_block"), used, aligned(4))) image_definition_block[] =
{
  UINT32_C(0xFFFFDED3),
  UINT32_C(0x10210142),
  UINT32_C(0x000001FF),
  UINT32_C(0x00000000),
  UINT32_C(0xAB123579)
};
