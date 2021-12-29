/************************************************************************/
/*                          io_macros.h                                 */
/*                                                                      */
/*  Definition of I/O Macros                                            */
/*                                                                      */
/*  Copyright (C) NEC Corporation 2006                                  */
/*                                                                      */
/*  This file was created by DeFiX V1.23                                */
/*                                                                      */
/*  This file is only intended as a sample supplement to NEC tools.     */
/*  Feel free to adapt it to your own needs.                            */
/*  This File is provided 'as is' without warranty of any kind.         */
/*  Neither NEC nor their sales representatives can be held liable      */
/*  of any inconvenience or problem caused by its contents.             */
/*                                                                      */
/*  ------------------------------------------------------------------  */
/*                                                                      */
/*  Adapted by Chris on 21-Oct-2007:                                    */
/*  - Included an 8-bit bitfield structure.                             */
/*  - Modified the code format including spacing, comments, etc.        */
/*                                                                      */
/************************************************************************/

#ifndef __IO_MACROS_H
  #define __IO_MACROS_H

  #ifdef __LANGUAGE_ASM__
   
    #define CAST_UC(x) (x)
    #define CAST_US(x) (x)
    #define CAST_UL(x) (x)
  
  #else

    #define CAST_UC(x) *((volatile unsigned char  *)(x))
    #define CAST_US(x) *((volatile unsigned short *)(x))
    #define CAST_UL(x) *((volatile unsigned long  *)(x))

    struct bitf
    {
      unsigned char bit00 : 1;
      unsigned char bit01 : 1;
      unsigned char bit02 : 1;
      unsigned char bit03 : 1;
      unsigned char bit04 : 1;
      unsigned char bit05 : 1;
      unsigned char bit06 : 1;
      unsigned char bit07 : 1;
      unsigned char bit08 : 1;
      unsigned char bit09 : 1;
      unsigned char bit10 : 1;
      unsigned char bit11 : 1;
      unsigned char bit12 : 1;
      unsigned char bit13 : 1;
      unsigned char bit14 : 1;
      unsigned char bit15 : 1;
    };
  
  #endif // __LANGUAGE_ASM__

#endif // __IO_MACROS_H
