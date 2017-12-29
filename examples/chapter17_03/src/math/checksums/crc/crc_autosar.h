///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CRC_AUTOSAR_2017_12_16_H_
  #define CRC_AUTOSAR_2017_12_16_H_

  #include <math/checksums/crc/crc_base.h>
  #include <math/checksums/crc/Crc08_Autosar.h>
  #include <math/checksums/crc/Crc16_CcittFalse.h>
  #include <math/checksums/crc/Crc32_Autosar.h>
  #include <math/checksums/crc/Crc64_Xz.h>

  namespace math { namespace checksums { namespace crc {

  class crc08_autosar final : public crc_base
  {
  public:
    crc08_autosar() { crc_context.Crc_Value = 0U; }

    crc08_autosar(const crc08_autosar& other_crc) : crc_base(other_crc),
                                                    crc_context()
    {
      crc_context.Crc_Value = other_crc.crc_context.Crc_Value;
    }

    virtual ~crc08_autosar() { }

  private:
    Crc08_Autosar_Context_Type crc_context;

    virtual void my_initialize()
    {
      Crc08_Autosar_Initialize(&crc_context);
    }

    virtual void my_process_bytes(const std::uint8_t* data_in,
                                  const std::size_t   data_length)
    {
      Crc08_Autosar_ProcessBytes(data_in, data_length, &crc_context);
    }

    virtual void my_finalize()
    {
      Crc08_Autosar_Finalize(&crc_context);
    }

    virtual       void*  storage()       { return reinterpret_cast<      void*>(&crc_context.Crc_Value); }
    virtual const void*  storage() const { return reinterpret_cast<const void*>(&crc_context.Crc_Value); }
    virtual const void* cstorage() const { return reinterpret_cast<const void*>(&crc_context.Crc_Value); }

    virtual std::uint_fast8_t my_size() const { return 1U; }
  };

  class crc16_autosar final : public crc_base
  {
  public:
    crc16_autosar() { crc_context.Crc_Value = 0U; }

    crc16_autosar(const crc16_autosar& other_crc) : crc_base(other_crc),
                                                    crc_context()
    {
      crc_context.Crc_Value = other_crc.crc_context.Crc_Value;
    }

    virtual ~crc16_autosar() { }

  private:
    Crc16_CcittFalse_Context_Type crc_context;

    virtual void my_initialize()
    {
      Crc16_CcittFalse_Initialize(&crc_context);
    }

    virtual void my_process_bytes(const std::uint8_t* data_in,
                                  const std::size_t   data_length)
    {
      Crc16_CcittFalse_ProcessBytes(data_in, data_length, &crc_context);
    }

    virtual void my_finalize()
    {
      Crc16_CcittFalse_Finalize(&crc_context);
    }

    virtual       void*  storage()       { return reinterpret_cast<      void*>(&crc_context.Crc_Value); }
    virtual const void*  storage() const { return reinterpret_cast<const void*>(&crc_context.Crc_Value); }
    virtual const void* cstorage() const { return reinterpret_cast<const void*>(&crc_context.Crc_Value); }

    virtual std::uint_fast8_t my_size() const { return 2U; }
  };

  class crc32_autosar final : public crc_base
  {
  public:
    crc32_autosar() { crc_context.Crc_Value = 0U; }

    crc32_autosar(const crc32_autosar& other_crc) : crc_base(other_crc),
                                                    crc_context()
    {
      crc_context.Crc_Value = other_crc.crc_context.Crc_Value;
    }

    virtual ~crc32_autosar() { }

  private:
    Crc32_Autosar_Context_Type crc_context;

    virtual void my_initialize()
    {
      Crc32_Autosar_Initialize(&crc_context);
    }

    virtual void my_process_bytes(const std::uint8_t* data_in,
                                  const std::size_t   data_length)
    {
      Crc32_Autosar_ProcessBytes(data_in, data_length, &crc_context);
    }

    virtual void my_finalize()
    {
      Crc32_Autosar_Finalize(&crc_context);
    }

    virtual       void*  storage()       { return reinterpret_cast<      void*>(&crc_context.Crc_Value); }
    virtual const void*  storage() const { return reinterpret_cast<const void*>(&crc_context.Crc_Value); }
    virtual const void* cstorage() const { return reinterpret_cast<const void*>(&crc_context.Crc_Value); }

    virtual std::uint_fast8_t my_size() const { return 4U; }
  };

  class crc64_autosar final : public crc_base
  {
  public:
    crc64_autosar() { crc_context.Crc_Value = 0U; }

    crc64_autosar(const crc64_autosar& other_crc) : crc_base(other_crc),
                                                    crc_context()
    {
      crc_context.Crc_Value = other_crc.crc_context.Crc_Value;
    }

    virtual ~crc64_autosar() { }

  private:
    Crc64_Xz_Context_Type crc_context;

    virtual void my_initialize()
    {
      Crc64_Xz_Initialize(&crc_context);
    }

    virtual void my_process_bytes(const std::uint8_t* data_in,
                                  const std::size_t   data_length)
    {
      Crc64_Xz_ProcessBytes(data_in, data_length, &crc_context);
    }

    virtual void my_finalize()
    {
      Crc64_Xz_Finalize(&crc_context);
    }

    virtual       void*  storage()       { return reinterpret_cast<      void*>(&crc_context.Crc_Value); }
    virtual const void*  storage() const { return reinterpret_cast<const void*>(&crc_context.Crc_Value); }
    virtual const void* cstorage() const { return reinterpret_cast<const void*>(&crc_context.Crc_Value); }

    virtual std::uint_fast8_t my_size() const { return 8U; }
  };

  } } } // namespace math::checksums::crc

#endif // CRC_AUTOSAR_2017_12_16_H_
