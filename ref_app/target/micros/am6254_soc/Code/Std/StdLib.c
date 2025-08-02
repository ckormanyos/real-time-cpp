#include <stdio.h>
#include <stdint.h>
#include <string.h>


//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void *memset(void *str, int c, size_t n)
{
  uint8_t *ptr = (uint8_t *)str;
  uint32_t value = (uint8_t)c;

  // Set value to repeat the byte across a 32-bit word
  value |= value << 8;
  value |= value << 16;

  // Align to the next 32-bit boundary
  while (((uintptr_t)ptr & 3) && n > 0) {
      *ptr++ = (uint8_t)c;
      n--;
  }

  // Set memory in 32-bit chunks
  uint32_t *ptr32 = (uint32_t *)ptr;
  while (n >= 4) {
      *ptr32++ = value;
      n -= 4;
  }

  // Handle any remaining bytes
  ptr = (uint8_t *)ptr32;
  while (n > 0) {
      *ptr++ = (uint8_t)c;
      n--;
  }

  return str;
}

//-----------------------------------------------------------------------------
/// \brief
///
/// \descr
///
/// \param
///
/// \return
//-----------------------------------------------------------------------------
void * memcpy (void* dest, const void * src, size_t n)
{
  uint8_t *d = (uint8_t *)dest;
  const uint8_t *s = (const uint8_t *)src;

  // Align destination to the next 32-bit boundary
  while (((uintptr_t)d & 3) && n > 0) {
      *d++ = *s++;
      n--;
  }

  // Copy memory in 32-bit chunks
  uint32_t *d32 = (uint32_t *)d;
  const uint32_t *s32 = (const uint32_t *)s;
  while (n >= 4) {
      *d32++ = *s32++;
      n -= 4;
  }

  // Handle any remaining bytes
  d = (uint8_t *)d32;
  s = (const uint8_t *)s32;
  while (n > 0) {
      *d++ = *s++;
      n--;
  }

  return dest;
}

