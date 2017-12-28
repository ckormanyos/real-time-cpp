///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_COMMUNICATION_2012_05_31_H_
  #define UTIL_COMMUNICATION_2012_05_31_H_

  #include <algorithm>
  #include <cstddef>
  #include <cstdint>
  #include <util/utility/util_circular_buffer.h>

  namespace util
  {
    class communication_base
    {
    public:
      typedef std::size_t size_type;

      virtual ~communication_base() { }

      virtual bool send           (const std::uint8_t byte_to_send) = 0;
      virtual bool recv           (std::uint8_t& byte_to_recv) = 0;
      virtual size_type recv_ready() const = 0;
      virtual bool idle           () const = 0;

      template<typename send_iterator_type>
      bool send_n(send_iterator_type first,
                  send_iterator_type last)
      {
        bool send_result = true;

        while(first != last)
        {
          typedef typename
          std::iterator_traits<send_iterator_type>::value_type
          send_value_type;

          const send_value_type value(*first);

          send_result &= send(std::uint8_t(value));

          ++first;
        }

        return send_result;
      }

      template<typename recv_iterator_type>
      bool recv_n(recv_iterator_type first,
                  size_type count)
      {
        const size_type count_to_recv = (std::min)(count, recv_ready());

        recv_iterator_type last = first + count_to_recv;

        bool recv_result = true;

        while(first != last)
        {
          std::uint8_t byte_to_recv;

          recv_result &= recv(byte_to_recv);

          typedef typename
          std::iterator_traits<recv_iterator_type>::value_type
          recv_value_type;

          *first = recv_value_type(byte_to_recv);

          ++first;
        }

        return recv_result;
      }

      template<typename recv_iterator_type>
      bool recv_n(recv_iterator_type first, recv_iterator_type last)
      {
        const size_type count_to_recv = size_type(std::distance(first, last));

        return recv_n(first, count_to_recv);
      }

    protected:
      communication_base() { }
    };

    template<const std::size_t buffer_size = 16U>
    class communication : public communication_base
    {
    public:
      typedef util::circular_buffer<std::uint8_t, buffer_size> buffer_type;

      virtual ~communication();

    protected:
      communication() : send_buffer(),
                        recv_buffer() { }

      buffer_type send_buffer;
      buffer_type recv_buffer;
    };

    template<const std::size_t buffer_size>
    communication<buffer_size>::~communication() { }
  }

#endif // UTIL_COMMUNICATION_2012_05_31_H_
