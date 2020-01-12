# Example Chapter06_01
# Integer Types Having Fixed Widths and Prime Numbers

Example chapter06_01 illustrates certain optimization
techniques through the calculation of a standard
CRC32 checksum (cycle redundancy check).

# CRC-32/MPEG-2

For this example, we select the popular CRC-32/MPEG-2.
A potential C++11 implementation is shown in the code below.
The CRC32 calculation is performed with a table-driven
method based on 4-bit nibbles. The table is also shown below.

```
template<typename input_iterator>
std::uint32_t crc32_mpeg2(input_iterator first,
                          input_iterator last)
{
  // Name            : CRC-32/MPEG-2
  // Polynomial      : 0x04C11DB7
  // Initial value   : 0xFFFFFFFF
  // Test: '1'...'9' : 0x0376E6E7

  // ISO/IEC 13818-1:2000
  // Recommendation H.222.0 Annex A

  // CRC32/MPEG2 Table based on nibbles.
  constexpr std::array<std::uint32_t, 16U> table =
  {{
    UINT32_C(0x00000000), UINT32_C(0x04C11DB7),
    UINT32_C(0x09823B6E), UINT32_C(0x0D4326D9),
    UINT32_C(0x130476DC), UINT32_C(0x17C56B6B),
    UINT32_C(0x1A864DB2), UINT32_C(0x1E475005),
    UINT32_C(0x2608EDB8), UINT32_C(0x22C9F00F),
    UINT32_C(0x2F8AD6D6), UINT32_C(0x2B4BCB61),
    UINT32_C(0x350C9B64), UINT32_C(0x31CD86D3),
    UINT32_C(0x3C8EA00A), UINT32_C(0x384FBDBD)
  }};

  // Set the initial value and loop through the input data stream.

  std::uint32_t crc = UINT32_C(0xFFFFFFFF);

  for( ; first != last; ++first)
  {
    const std::uint_fast8_t the_byte = uint_fast8_t((*first) & UINT8_C(0xFF));

    std::uint_fast8_t index;

    // Perform the CRC32/MPEG2 algorithm.
    index = ((std::uint_fast8_t(crc >> 28)) ^ (std::uint_fast8_t(the_byte >>  4))) & UINT8_C(0x0F);

    crc   = std::uint32_t(std::uint32_t(crc << 4) & UINT32_C(0xFFFFFFF0)) ^ table[index];

    index = ((std::uint_fast8_t(crc >> 28)) ^ (std::uint_fast8_t(the_byte))) & UINT8_C(0x0F);

    crc   = std::uint32_t(std::uint32_t(crc << 4) & UINT32_C(0xFFFFFFF0)) ^ table[index];
  }

  return crc;
}
```

# Application Description

One of the standard tests of a CRC is to compute the checksum
of the digits
<img src="https://render.githubusercontent.com/render/math?math=1{\ldots}9">,
where the digits are not decimal values but the ASCII representations
instead. In other words, the CRC is computed of

```
static const std::array<std::uint8_t, 9U> app_benchmark_crc_data =
{{
  0x31U, 0x32U, 0x33U, 0x34U, 0x35U, 0x36U, 0x37U, 0x38U, 0x39U
}};
```

for which the wxpected result is
<img src="https://render.githubusercontent.com/render/math?math=1{\ldots}9">.

# CRC Catalog

Look here for a very complete and up-to-date
[CRC catalog](http://http://reveng.sourceforge.net/crc-catalogue/).