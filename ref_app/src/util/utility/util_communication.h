///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_COMMUNICATION_2012_05_31_H
  #define UTIL_COMMUNICATION_2012_05_31_H

  #include <util/utility/util_noncopyable.h>

  #include <algorithm>
  #include <array>
  #include <cstddef>
  #include <cstdint>

  namespace util
  {
    class communication_base : private util::noncopyable // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
    {
    public:
      virtual ~communication_base() = default;

      virtual auto recv(std::uint8_t& byte_to_recv) -> bool = 0;

      virtual auto   select() -> void = 0;
      virtual auto deselect() -> void = 0;

      virtual auto select_channel(const std::size_t) -> bool { return true; }

      template<typename send_iterator_type>
      auto send_n(send_iterator_type first, send_iterator_type last) noexcept -> bool
      {
        bool send_result { true }; // NOLINT(altera-id-dependent-backward-branch)

        while((first != last) && send_result) // NOLINT(altera-id-dependent-backward-branch)
        {
          using send_value_type = typename std::iterator_traits<send_iterator_type>::value_type;

          send_result = (this->send(static_cast<std::uint8_t>(send_value_type(*first++))) && send_result);
        }

        return send_result;
      }

      virtual auto send(const std::uint8_t byte_to_send) noexcept -> bool = 0;

    protected:
      communication_base() = default;

    private:
      template<const std::size_t ChannelCount>
      friend class communication_multi_channel;
    };

    class communication_buffer_depth_one_byte : public communication_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
    {
    public:
      using buffer_type = std::uint8_t;

      ~communication_buffer_depth_one_byte() override = default;

    protected:
      buffer_type recv_buffer { }; // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)

      communication_buffer_depth_one_byte() = default;

    private:
      auto recv(std::uint8_t& byte_to_recv) -> bool override
      {
        byte_to_recv = recv_buffer;

        return true;
      }
    };

    template<const std::size_t ChannelCount>
    class communication_multi_channel : public communication_base // NOLINT(cppcoreguidelines-special-member-functions,hicpp-special-member-functions)
    {
    private:
      static constexpr std::size_t channel_count = ChannelCount;

    public:
      communication_multi_channel() = delete;

      explicit communication_multi_channel(communication_base** p_com_channels)
      {
        std::copy(p_com_channels, p_com_channels + channel_count, my_com_channels.begin()); // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
      }

      ~communication_multi_channel() override = default;

      auto send(const std::uint8_t byte_to_send) noexcept -> bool override
      {
        return my_com_channels[my_index]->send(byte_to_send);
      }

      auto recv(std::uint8_t& byte_to_recv) -> bool override
      {
        return my_com_channels[my_index]->recv(byte_to_recv);
      }

      auto   select() -> void override { my_com_channels[my_index]->select(); }
      auto deselect() -> void override { my_com_channels[my_index]->deselect(); }

      auto select_channel(const std::size_t index) -> bool override
      {
        const bool select_channel_is_ok = (index < channel_count);

        if(select_channel_is_ok)
        {
          my_index = index;
        }

        return select_channel_is_ok;
      }

    private:
      std::array<communication_base*, channel_count> my_com_channels { }; // NOLINT(readability-identifier-naming)
      std::size_t my_index { }; // NOLINT(readability-identifier-naming)

      static_assert(channel_count > 0U, "Error channel_count must be greater than zero.");
    };
  } // namespace util

#endif // UTIL_COMMUNICATION_2012_05_31_H
