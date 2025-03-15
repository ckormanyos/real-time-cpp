/******************************************************************************************
//  Copyright Christopher Kormanyos 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// Originally from:
/******************************************************************************************
  Filename    : IntVectTable.S
  
  Core        : RISC-V
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : interrupt vector table implementation for ULP-RISC-V Co-processor
  
******************************************************************************************/

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section .vector
.type _InterruptVectorTable, @function
.align 4
.extern _IRQ_VECTORS
.globl _InterruptVectorTable

_InterruptVectorTable:
          /* reset vector */
          j _start
          
