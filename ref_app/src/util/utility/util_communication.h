#ifndef _UTIL_COMMUNICATION_2012_05_31_H_
  #define _UTIL_COMMUNICATION_2012_05_31_H_

  #include <cstddef>
  #include <cstdint>
  #include <util/utility/util_dynamic_array.h>
  #include <util/memory/util_ring_allocator.h>

  namespace util
  {
    class communication
    {
    public:
      typedef dynamic_array<std::uint8_t, util::ring_allocator<std::uint8_t> > data_type;

      virtual ~communication() { }

      virtual bool send(const std::uint8_t) = 0;
      virtual bool send(const data_type&) = 0;
      virtual bool recv(std::uint8_t&) = 0;
      virtual bool recv(data_type&) = 0;
      virtual std::size_t recv_ready() const = 0;
      virtual bool idle(void) const = 0;

    protected:
      communication() { }
    };
  }

#endif // _UTIL_COMMUNICATION_2012_05_31_H_
