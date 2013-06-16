/*
 * Bfx.h
 *
 *  Created on: 18.05.2012
 *      Author: mike
 */

#ifndef _BFX_H__
#define _BFX_H__

// *****************************************************************************
// includes
// *****************************************************************************

#include <stdint.h>
#include <stdbool.h>

char *itoa(int value, char *s, int radix);

void Bfx_SetBit_u8u8(uint8_t* const, uint8_t);
void Bfx_SetBit_u16u8(uint16_t* const, uint8_t);
void Bfx_SetBit_u32u8(uint32_t* const, uint8_t);

void Bfx_ClrBit_u8u8(uint8_t* const, uint8_t);
void Bfx_ClrBit_u16u8(uint16_t* const, uint8_t);
void Bfx_ClrBit_u32u8(uint32_t* const, uint8_t);

bool Bfx_GetBit_u8u8_u8(uint8_t, uint8_t);
bool Bfx_GetBit_u16u8_u8(uint16_t, uint8_t);
bool Bfx_GetBit_u32u8_u8(uint32_t, uint8_t);

void Bfx_SetBits_u8u8u8u8(uint8_t* const, uint8_t, uint8_t, uint8_t);
void Bfx_SetBits_u16u8u8u8(uint16_t* const, uint8_t, uint8_t, uint8_t);
void Bfx_SetBits_u32u8u8u8(uint32_t* const, uint8_t, uint8_t, uint8_t);

uint8_t Bfx_GetBits_u8u8u8_u8(uint8_t, uint8_t, uint8_t);
uint16_t Bfx_GetBits_u16u8u8_u16(uint16_t, uint8_t, uint8_t);
uint32_t Bfx_GetBits_u32u8u8_u32(uint32_t, uint8_t, uint8_t);

void Bfx_SetBitMask_u8u8(uint8_t* const, uint8_t);
void Bfx_SetBitMask_u16u16(uint16_t* const, uint16_t);
void Bfx_SetBitMask_u32u32(uint32_t* const, uint32_t);

void Bfx_ClrBitMask_u8u8(uint8_t* const, uint8_t);
void Bfx_ClrBitMask_u16u16(uint16_t* const, uint16_t);
void Bfx_ClrBitMask_u32u32(uint32_t* const, uint32_t);

bool Bfx_TstBitMask_u8u8_u8(uint8_t, uint8_t);
bool Bfx_TstBitMask_u16u16_u8(uint16_t, uint16_t);
bool Bfx_TstBitMask_u32u32_u8(uint32_t, uint32_t);

bool Bfx_TstBitLnMask_u8u8_u8(uint8_t, uint8_t);
bool Bfx_TstBitLnMask_u16u16_u8(uint16_t, uint16_t);
bool Bfx_TstBitLnMask_u32u32_u8(uint32_t, uint32_t);

bool Bfx_TstParityEven_u8_u8(uint8_t);
bool Bfx_TstParityEven_u16_u8(uint16_t);
bool Bfx_TstParityEven_u32_u8(uint32_t);

void Bfx_ToogleBits_u8(uint8_t* const);
void Bfx_ToogleBits_u16(uint16_t* const);
void Bfx_ToogleBits_u32(uint32_t* const);

void Bfx_ToogleBitMask_u8u8(uint8_t* const, uint8_t);
void Bfx_ToogleBitMask_u16u16(uint16_t* const, uint16_t);
void Bfx_ToogleBitMask_u32u32(uint32_t* const, uint32_t);

void Bfx_ShiftBitRt_u8u8(uint8_t* const, uint8_t);
void Bfx_ShiftBitRt_u16u8(uint16_t* const, uint8_t);
void Bfx_ShiftBitRt_u32u8(uint32_t* const, uint8_t);

void Bfx_ShiftBitLt_u8u8(uint8_t* const, uint8_t);
void Bfx_ShiftBitLt_u16u8(uint16_t* const, uint8_t);
void Bfx_ShiftBitLt_u32u8(uint32_t* const, uint8_t);

void Bfx_RotBitRt_u8u8(uint8_t* const, uint8_t);
void Bfx_RotBitRt_u16u8(uint16_t* const, uint8_t);
void Bfx_RotBitRt_u32u8(uint32_t* const, uint8_t);

void Bfx_RotBitLt_u8u8(uint8_t* const, uint8_t);
void Bfx_RotBitLt_u16u8(uint16_t* const, uint8_t);
void Bfx_RotBitLt_u32u8(uint32_t* const, uint8_t);

void Bfx_CopyBit_u8u8u8u8(uint8_t* const, uint8_t, uint8_t, uint8_t);
void Bfx_CopyBit_u16u8u16u8(uint16_t* const, uint8_t, uint16_t, uint8_t);
void Bfx_CopyBit_u32u8u32u8(uint32_t* const, uint8_t, uint32_t, uint8_t);

void Bfx_PutBits_u8u8u8u8(uint8_t* const, uint8_t, uint8_t, uint8_t);
void Bfx_PutBits_u16u8u8u16(uint16_t* const, uint8_t, uint8_t, uint16_t);
void Bfx_PutBits_u32u8u8u32(uint32_t* const, uint8_t, uint8_t, uint32_t);

void Bfx_PutBitsMask_u8u8u8(uint8_t* const, uint8_t, uint8_t);
void Bfx_PutBitsMask_u16u16u16(uint16_t* const, uint16_t, uint16_t);
void Bfx_PutBitsMask_u32u32u32(uint32_t* const, uint32_t, uint32_t);

void Bfx_PutBit_u8u8u8(uint8_t* const, uint8_t, bool);
void Bfx_PutBit_u16u8u8(uint16_t* const, uint8_t, bool);
void Bfx_PutBit_u32u8u8(uint32_t* const, uint8_t, bool);

#endif /* _BFX_H__ */
