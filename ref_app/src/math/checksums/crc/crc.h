///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _CRC_2012_01_23_H_
  #define _CRC_2012_01_23_H_

  #include <array>
  #include <numeric>
  #include <util/utility/util_utype_helper.h>

  template<const std::size_t bits,
           const typename util::utype_helper<bits>::exact_type ini_value,
           const typename util::utype_helper<bits>::exact_type xor_value>
  class crc
  {
  public:
    typedef typename util::utype_helper<bits>::exact_type value_type;
    void process_bytes(const std::uint8_t*, const std::size_t) { }
    value_type checksum() const { return value_type(0U); }

  private:
    crc();
    const crc& operator=(const crc&);
  };

  template<const util::utype_helper<8U>::exact_type ini_value,
           const util::utype_helper<8U>::exact_type xor_value>
  class crc<8U, ini_value, xor_value>
  {
  public:
    typedef typename util::utype_helper<8U>::exact_type value_type;

    crc() : crc_value(ini_value) { }
    crc(const crc& other_crc) : crc_value(other_crc.crc_value) { }

    crc& operator=(const crc& other_crc)
    {
      crc_value = other_crc.crc_value;
      return *this;
    }

    void process_bytes(const std::uint8_t* buffer, const std::size_t byte_count)
    {
      crc_value = std::accumulate(
        buffer,
        buffer + byte_count,
        crc_value,
        [](value_type& crc, const std::uint8_t& by) -> value_type
        {
          const std::size_t index = static_cast<std::size_t>(static_cast<std::uint8_t>(crc ^ by));
          return static_cast<value_type>(table[index]);
        });
    }

    value_type checksum() const { return static_cast<value_type>(crc_value ^ xor_value); }

  private:
    static const std::array<value_type, 256U> table;
    value_type crc_value;
  };

  template<const util::utype_helper<16U>::exact_type ini_value,
           const util::utype_helper<16U>::exact_type xor_value>
  class crc<16U, ini_value, xor_value>
  {
  public:
    typedef typename util::utype_helper<16U>::exact_type value_type;

    crc() : crc_value(ini_value) { }
    crc(const crc& other_crc) : crc_value(other_crc.crc_value) { }

    crc& operator=(const crc& other_crc)
    {
      crc_value = other_crc.crc_value;
      return *this;
    }

    void process_bytes(const std::uint8_t* buffer, const std::size_t byte_count)
    {
      crc_value = std::accumulate(
        buffer,
        buffer + byte_count,
        crc_value,
        [](value_type& crc, const std::uint8_t& by) -> value_type
        {
          const std::size_t index = static_cast<std::size_t>(static_cast<std::uint8_t>((crc >> 8) ^ by));
          crc = static_cast<value_type>((crc << 8) ^ table[index]);
          return crc;
        });
    }

    value_type checksum() const { return static_cast<value_type>(crc_value ^ xor_value); }

  private:
    static const std::array<value_type, 256U> table;
    value_type crc_value;
  };

  template<const util::utype_helper<32U>::exact_type ini_value,
           const util::utype_helper<32U>::exact_type xor_value>
  class crc<32U, ini_value, xor_value>
  {
  public:
    typedef typename util::utype_helper<32U>::exact_type value_type;

    crc() : crc_value(ini_value) { }
    crc(const crc& other_crc) : crc_value(other_crc.crc_value) { }

    crc& operator=(const crc& other_crc)
    {
      crc_value = other_crc.crc_value;
      return *this;
    }

    void process_bytes(const std::uint8_t* buffer, const std::size_t byte_count)
    {
      crc_value = std::accumulate(
        buffer,
        buffer + byte_count,
        crc_value,
        [](value_type& crc,
            const std::uint8_t& by) -> value_type
        {
          const std::size_t index = static_cast<std::size_t>(static_cast<std::uint8_t>(crc ^ by));
          crc = static_cast<value_type>(static_cast<value_type>(crc >> 8) ^ table[index]);
          return crc;
        });
    }

    value_type checksum() const { return static_cast<value_type>(crc_value ^ xor_value); }

  private:
    static const std::array<value_type, 256U> table;
    value_type crc_value;
  };

  template<const util::utype_helper<64U>::exact_type ini_value,
           const util::utype_helper<64U>::exact_type xor_value>
  class crc<64U, ini_value, xor_value>
  {
  public:
    typedef typename util::utype_helper<64U>::exact_type value_type;

    crc() : crc_value(ini_value) { }
    crc(const crc& other_crc) : crc_value(other_crc.crc_value) { }

    crc& operator=(const crc& other_crc)
    {
      crc_value = other_crc.crc_value;
      return *this;
    }

    void process_bytes(const std::uint8_t* buffer, const std::size_t byte_count)
    {
      crc_value = std::accumulate(
        buffer,
        buffer + byte_count,
        crc_value,
        [](value_type& crc, const std::uint8_t& by) -> value_type
        {
          const std::size_t index = static_cast<std::size_t>(static_cast<std::uint8_t>((crc >> 56) ^ by));
          crc = static_cast<value_type>(static_cast<value_type>(crc << 8) ^ table[index]);
          return crc;
        });
    }

    value_type checksum() const { return static_cast<value_type>(crc_value ^ xor_value); }

  private:
    static const std::array<value_type, 256U> table;
    value_type crc_value;
  };

  typedef crc< 8U, 0x0U, 0x0U>                 crc_8_atm_type;
  typedef crc<16U, 0xFFFFU, 0x0U>              crc_ccitt_type;
  typedef crc<32U, 0xFFFFFFFFUL, 0xFFFFFFFFUL> crc_32_type;
  typedef crc<64U, 0x0ULL, 0x0ULL>             crc_64_ecma182_type;

#endif // _CRC_2012_01_23_H_
