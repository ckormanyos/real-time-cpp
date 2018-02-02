///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CPP_CRC_BASE_2017_12_16_H_
  #define CPP_CRC_BASE_2017_12_16_H_

  #include <algorithm>
  #include <cstdint>

  namespace math { namespace checksums { namespace crc {

  class cpp_crc_base
  {
  public:
    virtual ~cpp_crc_base() = default;

    void initialize()
    {
      my_initialize();
    }

    void process_bytes(const std::uint8_t* data_in,
                       const std::size_t   data_length)
    {
      my_process_bytes(data_in, data_length);
    }

    void finalize()
    {
      my_finalize();
    }

    cpp_crc_base& operator=(const cpp_crc_base& other_crc);

    template<typename value_type>
    value_type get_result()
    {
      value_type result_destination = value_type();

      const void* my_cstorage = cstorage();

      // Make sure the size of the extraction remains
      // within bounds, even if it truncates the result.
      const std::uint_fast8_t result_extraction_size =
        (std::min)(my_size(), std::uint_fast8_t(sizeof(value_type)));

      for(std::uint_fast8_t i = 0U; i < result_extraction_size; ++i)
      {
        // Extract the result of the checksum one byte at a time.
        *(reinterpret_cast<      std::uint8_t*>(&result_destination) + i) =
        *(reinterpret_cast<const std::uint8_t*>(my_cstorage)         + i);
      }

      return result_destination;
    }

    template<typename value_type>
    value_type checksum(const std::uint8_t* data_in,
                        const std::size_t   data_length)
    {
      initialize();

      process_bytes(data_in, data_length);

      finalize();

      const value_type crc_result = get_result<value_type>();

      return crc_result;
    }

  protected:
    cpp_crc_base() = default;

    cpp_crc_base(const cpp_crc_base&) = default;

  private:
    virtual void my_initialize() = 0;

    virtual void my_process_bytes(const std::uint8_t* data_in,
                                  const std::size_t   data_length) = 0;

    virtual void my_finalize() = 0;

    virtual std::uint_fast8_t my_size() const = 0;

    virtual       void*  storage()       = 0;
    virtual const void*  storage() const = 0;
    virtual const void* cstorage() const = 0;
  };

  } } } // namespace math::checksums::crc

#endif // CPP_CRC_BASE_2017_12_16_H_
