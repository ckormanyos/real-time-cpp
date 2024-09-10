/******************************************************************************************
  Filename    : image_definition_block.c
  
  Core        : ARM Cortex-M33
  
  MCU         : RP2350
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 29.08.2024
  
  Description : Image definition block for Raspberry Pi Pico 2
  
******************************************************************************************/

#include "stdint.h"

const uint32_t __attribute__((section(".image_start_block"), aligned(4))) image_definition_Block[] =
{
    0xffffded3,
    0x10210142,
    0x000001ff,
    0x00000000,
    0xab123579
};
