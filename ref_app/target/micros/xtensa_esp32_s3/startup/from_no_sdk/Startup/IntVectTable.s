/******************************************************************************************
  Filename    : IntVectTable.s
  
  Core        : Xtensa LX7
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : Interrupt vector tables for ESP32-S3
  
******************************************************************************************/

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .vector,"ax"
.global _vector_table
.type _vector_table, @function
.align 1024

_vector_table:

        .org _vector_table + 0x00
        WindowVectors:
                        j .

        .org _vector_table + 0x180
        Level2InterruptVector:
                        j .

        .org _vector_table + 0x1c0
        Level3InterruptVector:
                        j irq6_timer1

        .org _vector_table + 0x200
        Level4InterruptVector:
                        j .

        .org _vector_table + 0x240
        Level5InterruptVector:
                        j .

        .org _vector_table + 0x280
        DebugExceptionVector:
                        j .

        .org _vector_table + 0x2c0
        NMIExceptionVector:
                        j .

        .org _vector_table + 0x300
        Level1KernalInterruptVector:
                        j .

        .org _vector_table + 0x340
        Level1UserInterruptVector:
                        j .

        .org _vector_table + 0x3C0
        DoubleExceptionVector:
                        j .

        .org _vector_table + 0x400
        InvalidExceptionVector:
                        j .

            .extern blink_led_c0

irq6_timer1:
             addi sp, sp, -4
             s32i.n a0,  sp, 0
             call0 blink_led
             l32i.n a0,  sp, 0
             addi sp, sp, 4
             rfi 3


.size _vector_table, .-_vector_table

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .text,"ax"
.type enable_irq, @function
.align 4
.global enable_irq

enable_irq:
           wsr a2, INTENABLE
           ret

.size enable_irq, .-enable_irq

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .text,"ax"
.type set_cpu_private_timer1, @function
.align 4
.global set_cpu_private_timer1

set_cpu_private_timer1:
                       movi a11, 0
                       wsr  a11, ccount
                       esync
                       wsr  a2, ccompare1
                       esync
                       ret

.size set_cpu_private_timer1, .-set_cpu_private_timer1

  // software interrupt
  //movi a10, 0x80;
  //wsr.intset a10
  
  //RSIL --> read and set prio level

/*******************************************************************************************
  \brief  
  
  \param  
  
  \return 
********************************************************************************************/
.section  .vector,"ax"
.global _dummy_vector_table
.type _dummy_vector_table, @function
.align 1024

_dummy_vector_table:

    .rept 20   // this loop create the full interrupt vector table (20 vectors of 0x40 each)
      .rept 12 // this loop create 0x40 bytes (5x12 + 4 = size of one interrupt vector)
        j .    // 3-byte op
        nop    // 2-byte op
      .endr
      nop      // 2-byte op
      nop      // 2-byte op
    .endr
.size _dummy_vector_table, .-_dummy_vector_table
