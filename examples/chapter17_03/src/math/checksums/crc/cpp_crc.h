///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CPP_CRC_2017_12_16_H_
  #define CPP_CRC_2017_12_16_H_

  #include <math/checksums/crc/cpp_crc_base.h>
  #include <math/checksums/crc/Crc08.h>
  #include <math/checksums/crc/Crc16.h>
  #include <math/checksums/crc/Crc32.h>
  #include <math/checksums/crc/Crc64.h>

  namespace math { namespace checksums { namespace crc {

  class cpp_crc08 final : public cpp_crc_base
  {
  public:
    cpp_crc08() { my_context.Crc08_Value = 0U; }

    cpp_crc08(const cpp_crc08& other_crc) : cpp_crc_base(other_crc),
                                            my_context()
    {
      my_context.Crc08_Value = other_crc.my_context.Crc08_Value;
    }

    virtual ~cpp_crc08() { }

  private:
    Crc08_Context_Type my_context;

    virtual void my_initialize()
    {
      Crc08_Initialize(&my_context);
    }

    virtual void my_process_bytes(const std::uint8_t* data_in,
                                  const std::size_t   data_length)
    {
      Crc08_ProcessBytes(data_in, data_length, &my_context);
    }

    virtual void my_finalize()
    {
      Crc08_Finalize(&my_context);
    }

    virtual       void*  storage()       { return reinterpret_cast<      void*>(&my_context.Crc08_Value); }
    virtual const void*  storage() const { return reinterpret_cast<const void*>(&my_context.Crc08_Value); }
    virtual const void* cstorage() const { return reinterpret_cast<const void*>(&my_context.Crc08_Value); }

    virtual std::uint_fast8_t my_size() const { return 1U; }
  };

  class cpp_crc16 final : public cpp_crc_base
  {
  public:
    cpp_crc16() { my_context.Crc16_Value = 0U; }

    cpp_crc16(const cpp_crc16& other_crc) : cpp_crc_base(other_crc),
                                            my_context()
    {
      my_context.Crc16_Value = other_crc.my_context.Crc16_Value;
    }

    virtual ~cpp_crc16() { }

  private:
    Crc16_Context_Type my_context;

    virtual void my_initialize()
    {
      Crc16_Initialize(&my_context);
    }

    virtual void my_process_bytes(const std::uint8_t* data_in,
                                  const std::size_t   data_length)
    {
      Crc16_ProcessBytes(data_in, data_length, &my_context);
    }

    virtual void my_finalize()
    {
      Crc16_Finalize(&my_context);
    }

    virtual       void*  storage()       { return reinterpret_cast<      void*>(&my_context.Crc16_Value); }
    virtual const void*  storage() const { return reinterpret_cast<const void*>(&my_context.Crc16_Value); }
    virtual const void* cstorage() const { return reinterpret_cast<const void*>(&my_context.Crc16_Value); }

    virtual std::uint_fast8_t my_size() const { return 2U; }
  };

  class cpp_crc32 final : public cpp_crc_base
  {
  public:
    cpp_crc32() { my_context.Crc32_Value = 0U; }

    cpp_crc32(const cpp_crc32& other_crc) : cpp_crc_base(other_crc),
                                            my_context()
    {
      my_context.Crc32_Value = other_crc.my_context.Crc32_Value;
    }

    virtual ~cpp_crc32() { }

  private:
    Crc32_Context_Type my_context;

    virtual void my_initialize()
    {
      Crc32_Initialize(&my_context);
    }

    virtual void my_process_bytes(const std::uint8_t* data_in,
                                  const std::size_t   data_length)
    {
      Crc32_ProcessBytes(data_in, data_length, &my_context);
    }

    virtual void my_finalize()
    {
      Crc32_Finalize(&my_context);
    }

    virtual       void*  storage()       { return reinterpret_cast<      void*>(&my_context.Crc32_Value); }
    virtual const void*  storage() const { return reinterpret_cast<const void*>(&my_context.Crc32_Value); }
    virtual const void* cstorage() const { return reinterpret_cast<const void*>(&my_context.Crc32_Value); }

    virtual std::uint_fast8_t my_size() const { return 4U; }
  };

  class cpp_crc64 final : public cpp_crc_base
  {
  public:
    cpp_crc64() { my_context.Crc64_Value = 0U; }

    cpp_crc64(const cpp_crc64& other_crc) : cpp_crc_base(other_crc),
                                            my_context()
    {
      my_context.Crc64_Value = other_crc.my_context.Crc64_Value;
    }

    virtual ~cpp_crc64() { }

  private:
    Crc64_Context_Type my_context;

    virtual void my_initialize()
    {
      Crc64_Initialize(&my_context);
    }

    virtual void my_process_bytes(const std::uint8_t* data_in,
                                  const std::size_t   data_length)
    {
      Crc64_ProcessBytes(data_in, data_length, &my_context);
    }

    virtual void my_finalize()
    {
      Crc64_Finalize(&my_context);
    }

    virtual       void*  storage()       { return reinterpret_cast<      void*>(&my_context.Crc64_Value); }
    virtual const void*  storage() const { return reinterpret_cast<const void*>(&my_context.Crc64_Value); }
    virtual const void* cstorage() const { return reinterpret_cast<const void*>(&my_context.Crc64_Value); }

    virtual std::uint_fast8_t my_size() const { return 8U; }
  };

  } } } // namespace math::checksums::crc

#endif // CPP_CRC_2017_12_16_H_
