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

  namespace util
  {
    class communication_base
    {
    public:
      typedef std::size_t size_type;

      virtual ~communication_base() = default;

      virtual bool send           (const std::uint8_t byte_to_send) = 0;
      virtual bool recv           (std::uint8_t& byte_to_recv) = 0;
      virtual bool select         () const = 0;
      virtual bool deselect       () const = 0;

      virtual bool select_channel(const std::size_t)
      {
        return true;
      }

      template<typename send_iterator_type>
      bool send_n(send_iterator_type first, send_iterator_type last)
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
      bool recv_n(recv_iterator_type first, const size_type count)
      {
        const size_type count_to_recv = count;

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
      communication_base() = default;
    };

    class communication_buffer_depth_one_byte : public communication_base
    {
    public:
      typedef std::uint8_t buffer_type;

      virtual ~communication_buffer_depth_one_byte() = default;

      virtual bool recv(std::uint8_t& byte_to_recv)
      {
        byte_to_recv = recv_buffer;

        return true;
      }

    protected:
      communication_buffer_depth_one_byte()
        : recv_buffer(0U) { }

      buffer_type recv_buffer;
    };

    template<const std::size_t channel_count>
    class communication_multi_channel : public communication_base
    {
    private:
      static_assert(channel_count > 0U, "Error channel_count must be greater than zero.");

    public:
      communication_multi_channel(communication_base** p_com_channels)
        : my_com_channels(),
          my_index       (0U)
      {
        for(std::size_t i = 0U; i < channel_count; ++i)
        {
          my_com_channels[i] = p_com_channels[i];
        }
      }

      ~communication_multi_channel() = default;

      virtual bool send(const std::uint8_t byte_to_send)
      {
        return my_com_channels[my_index]->send(byte_to_send);
      }

      virtual bool recv(std::uint8_t& byte_to_recv)
      {
        return my_com_channels[my_index]->recv(byte_to_recv);
      }

      virtual bool select() const
      {
        return my_com_channels[my_index]->select();
      }

      virtual bool deselect() const
      {
        return my_com_channels[my_index]->deselect();
      }

      virtual bool select_channel(const std::size_t index)
      {
        const bool select_channel_is_ok = (index < channel_count);

        if(select_channel_is_ok)
        {
          my_index = index;
        }

        return select_channel_is_ok;
      }

    private:
      communication_base* my_com_channels[channel_count];
      std::size_t         my_index;

      communication_multi_channel() = delete;
    };
  }

#endif // UTIL_COMMUNICATION_2012_05_31_H_
