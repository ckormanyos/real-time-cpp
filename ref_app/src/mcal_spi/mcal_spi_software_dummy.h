#ifndef MCAL_SPI_SOFTWARE_DUMMY_2020_04_10_H_
  #define MCAL_SPI_SOFTWARE_DUMMY_2020_04_10_H_

  #include <util/utility/util_communication.h>
  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace spi {

  class spi_software_dummy : private util::noncopyable,
                             public util::communication_buffer_depth_one_byte
  {
  private:
    using base_class_type = util::communication_buffer_depth_one_byte;

  public:
    // This class implements a dummy SPI with no real functionality.

    spi_software_dummy() = default;

    virtual ~spi_software_dummy() = default;

    virtual bool send(const std::uint8_t byte_to_send)
    {
      static_cast<void>(byte_to_send);

      base_class_type::recv_buffer = 0U;

      return true;
    }

    virtual bool idle() const
    {
      return true;
    }
  };

  } } // namespace mcal::spi

#endif // MCAL_SPI_SOFTWARE_DUMMY_2020_04_10_H_
