#ifndef _CRC_2012_01_23_H_
  #define _CRC_2012_01_23_H_

  #include <array>
  #include <numeric>
  #include <util/utility/util_utype_helper.h>

  template<const std::size_t bits,
            const typename util::utype_helper<bits>::exact ini_value,
            const typename util::utype_helper<bits>::exact xor_value>
  class crc
  {
  public:
    typedef typename util::utype_helper<bits>::exact value_type;
    void process_bytes(const std::uint8_t*, const std::size_t) { }
    value_type checksum() const { return value_type(0U); }

  private:
    crc();
  };

  template<const util::utype_helper<8U>::exact ini_value,
           const util::utype_helper<8U>::exact xor_value>
  class crc<8U, ini_value, xor_value>
  {
  public:
    typedef typename util::utype_helper<8U>::exact value_type;

    crc() : crc_value(ini_value) { }

    void process_bytes(const std::uint8_t* buffer, const std::size_t byte_count)
    {
      crc_value = std::accumulate(
        buffer,
        buffer + byte_count,
        crc_value,
        [](std::uint8_t& crc,
            const std::uint8_t& by) -> std::uint8_t
        {
          const std::uint8_t index = crc ^ by;
          return table[index];
        });
    }

    value_type checksum() const { return crc_value ^ xor_value; }

  private:
    static const std::array<value_type, 256U> table;
    value_type crc_value;
  };

  template<const util::utype_helper<16U>::exact ini_value,
           const util::utype_helper<16U>::exact xor_value>
  class crc<16U, ini_value, xor_value>
  {
  public:
    typedef typename util::utype_helper<16U>::exact value_type;

    crc() : crc_value(ini_value) { }

    void process_bytes(const std::uint8_t* buffer, const std::size_t byte_count)
    {
      crc_value = std::accumulate(
        buffer,
        buffer + byte_count,
        crc_value,
        [](std::uint16_t& crc,
            const std::uint8_t& by) -> std::uint16_t
        {
          const std::uint8_t index = (crc >> 8) ^ by;
          crc = (crc << 8) ^ table[index];
          return crc;
        });
    }

    value_type checksum() const { return crc_value ^ xor_value; }

  private:
    static const std::array<value_type, 256U> table;
    value_type crc_value;
  };

  template<const util::utype_helper<32U>::exact ini_value,
           const util::utype_helper<32U>::exact xor_value>
  class crc<32U, ini_value, xor_value>
  {
  public:
    typedef typename util::utype_helper<32U>::exact value_type;

    crc() : crc_value(ini_value) { }

    void process_bytes(const std::uint8_t* buffer, const std::size_t byte_count)
    {
      crc_value = std::accumulate(
        buffer,
        buffer + byte_count,
        crc_value,
        [](std::uint32_t& crc,
            const std::uint8_t& by) -> std::uint32_t
        {
          const std::uint8_t index = static_cast<std::uint8_t>(crc ^ by);
          crc =   static_cast<std::uint32_t>(crc >> 8)
                  ^ table[index];
          return crc;
        });
    }

    value_type checksum() const { return crc_value ^ xor_value; }

  private:
    static const std::array<value_type, 256U> table;
    value_type crc_value;
  };

  template<const util::utype_helper<64U>::exact ini_value,
           const util::utype_helper<64U>::exact xor_value>
  class crc<64U, ini_value, xor_value>
  {
  public:
    typedef typename util::utype_helper<64U>::exact value_type;

    crc() : crc_value(ini_value) { }

    void process_bytes(const std::uint8_t* buffer, const std::size_t byte_count)
    {
      crc_value = std::accumulate(
        buffer,
        buffer + byte_count,
        crc_value,
        [](std::uint64_t& crc,
            const std::uint8_t& by) -> std::uint64_t
        {
          const std::uint8_t index = static_cast<std::uint8_t>((crc >> 56) ^ by);
          crc =   static_cast<std::uint64_t>(crc << 8)
                ^ table[index];
          return crc;
        });
    }

    value_type checksum() const { return crc_value ^ xor_value; }

  private:
    static const std::array<value_type, 256U> table;
    value_type crc_value;
  };

  typedef crc<8U, 0x0U, 0x0U> crc_8_atm_type;
  typedef crc<16U, 0xFFFFU, 0x0U> crc_ccitt_type;
  typedef crc<32U, 0xFFFFFFFFUL, 0xFFFFFFFFUL> crc_32_type;
  typedef crc<64U, 0x0ULL, 0x0ULL> crc_64_ecma182_type;

#endif // _CRC_2012_01_23_H_
