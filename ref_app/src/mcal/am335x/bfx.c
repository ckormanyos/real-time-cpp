/*
 * Bfx.c
 *
 *  Created on: 18.05.2012
 *      Author: mike
 */

#include "bfx.h"

void Bfx_SetBitMask_u8u8(uint8_t* const Data, uint8_t Mask)
{
	*Data = *Data | Mask;
}

void Bfx_SetBitMask_u16u16(uint16_t* const Data, uint16_t Mask)
{
	*Data = *Data | Mask;
}

void Bfx_SetBitMask_u32u32(uint32_t* const Data, uint32_t Mask)
{
	*Data = *Data | Mask;
}

void Bfx_ClrBitMask_u8u8(uint8_t* const Data, uint8_t Mask)
{
	*Data = *Data & ~Mask;
}

void Bfx_ClrBitMask_u16u16(uint16_t* const Data, uint16_t Mask)
{
	*Data = *Data & ~Mask;
}

void Bfx_ClrBitMask_u32u32(uint32_t* const Data, uint32_t Mask)
{
	*Data = *Data & ~Mask;
}

void Bfx_PutBitsMask_u8u8u8(uint8_t* const Data, uint8_t Pattern, uint8_t Mask)
{
	*Data = (*Data & ~Mask) | (Pattern & Mask);
}

inline void Bfx_PutBitsMask_u16u16u16(uint16_t* const Data, uint16_t Pattern,
		uint16_t Mask)
{
	*Data = (*Data & ~Mask) | (Pattern & Mask);
}

inline void Bfx_PutBitsMask_u32u32u32(uint32_t* const Data, uint32_t Pattern,
		uint32_t Mask)
{
	*Data = (*Data & ~Mask) | (Pattern & Mask);
}

char *itoa(int value, char *s, int radix)
{
	const char *digits = "0123456789abcdefghijklmnopqrstuvwxyz";
	unsigned long ulvalue = value;
	char *p = s, *q = s;
	char temp;
	if (radix == 10 && value < 0) {
		*p++ = '-';
		q = p;
		ulvalue = -value;
	}
	do {
		*p++ = digits[ulvalue % radix];
		ulvalue /= radix;
	} while (ulvalue > 0);
	*p-- = '\0';
	while (q < p) {
		temp = *q;
		*q++ = *p;
		*p-- = temp;
	}
	return s;
}
