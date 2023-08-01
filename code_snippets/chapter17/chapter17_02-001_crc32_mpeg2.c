/*//////////////////////////////////////////////////////////*/
/*  Copyright Christopher Kormanyos 2017 - 2023.            */
/*  Distributed under the Boost Software License,           */
/*  Version 1.0. (See accompanying file LICENSE_1_0.txt     */
/*  or copy at http://www.boost.org/LICENSE_1_0.txt)        */
/*//////////////////////////////////////////////////////////*/

/* chapter17_02-001_crc32_mpeg2.c */

/* See also https://godbolt.org/z/PeM54nnEW */

/* This is in a C file. */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

uint32_t Crc32_Mpeg2(const uint8_t* DataIn,
                     const size_t DataLength);

uint32_t Crc32_Mpeg2(const uint8_t* DataIn,
                     const size_t DataLength)
{
  /* Name            : CRC32/MPEG-2  */
  /* Polynomial      : 0x04C1'1DB7   */
  /* Initial value   : 0xFFFF'FFFF   */
  /* Test: '1'...'9' : 0x0376'E6E7   */

  /* See also ISO/IEC 13818-1:2000,  */
  /* Recommendation H.222.0 Annex A. */

  /* Set the initial value. */
  uint32_t CrcResult = UINT32_C(0xFFFFFFFF);

  size_t LoopCnt;

  /* Loop through the input data stream */
  for(LoopCnt = 0U; LoopCnt < DataLength; ++LoopCnt)
  {
    /* CRC32/MPEG2 Table based on nibbles. */
    static const uint32_t Crc32_Mpeg2_Table[16U] =
    {
      UINT32_C(0x00000000), UINT32_C(0x04C11DB7),
      UINT32_C(0x09823B6E), UINT32_C(0x0D4326D9),
      UINT32_C(0x130476DC), UINT32_C(0x17C56B6B),
      UINT32_C(0x1A864DB2), UINT32_C(0x1E475005),
      UINT32_C(0x2608EDB8), UINT32_C(0x22C9F00F),
      UINT32_C(0x2F8AD6D6), UINT32_C(0x2B4BCB61),
      UINT32_C(0x350C9B64), UINT32_C(0x31CD86D3),
      UINT32_C(0x3C8EA00A), UINT32_C(0x384FBDBD)
    };

    const uint8_t DataByte = DataIn[LoopCnt];

    /* Perform the CRC32/MPEG2 algorithm. */
    uint_fast8_t DataIndex =
        (  ((uint_fast8_t) (CrcResult >> 28U))
         ^ ((uint_fast8_t) (DataByte  >>  4U)))
      & UINT8_C(0x0F);

    CrcResult =
        (uint32_t) (  (uint32_t) (CrcResult << 4U)
                    & UINT32_C(0xFFFFFFF0))
      ^ Crc32_Mpeg2_Table[DataIndex];

    DataIndex =
        (((uint_fast8_t) (CrcResult >> 28U))
      ^  ((uint_fast8_t) (DataByte))) & UINT8_C(0x0F);

    CrcResult =
        (uint32_t) (  (uint32_t) (CrcResult << 4U)
                    & UINT32_C(0xFFFFFFF0))
      ^ Crc32_Mpeg2_Table[DataIndex];
  }

  return CrcResult;
}

int main(void)
{
  static const uint8_t TestData[9U] =
  {
    0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U
  };

  static const uint32_t ControlValue = UINT32_C(0x0376E6E7);

  const uint32_t TestResult = Crc32_Mpeg2(TestData, 9U);

  const bool TestResultIsOk =
    (bool) ((TestResult == ControlValue) ? true : false);

  if(TestResultIsOk == true)
  {
    printf("CRC32 test result is: OK\n");
  }
  else
  {
    printf("CRC32 test result is: Not OK\n");
  }

  return ((TestResultIsOk == true) ? 0 : -1);
}
