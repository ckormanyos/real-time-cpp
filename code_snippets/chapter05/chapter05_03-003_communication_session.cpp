///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_03-003_communication_session.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

class communication
{
public:
  ~communication() = default;

  auto send_byte(const std::uint8_t b) const -> bool
  {
    std::stringstream strm { };

    // Simulate sending a byte on the PC.
    strm << "Sending: " << std::hex << std::showbase << unsigned(b);

    std::cout << strm.str() << std::endl;

    const std::ios::iostate cout_state = std::cout.rdstate();

    const bool send_byte_is_ok = ((cout_state & (std::ios::badbit | std::ios::failbit)) == 0);

    return send_byte_is_ok;
  }

  // Add a template send_uint function.
  template<typename unsigned_type>
  auto send_uint(const unsigned_type& u) const -> bool
  {
    constexpr auto type_is_signed { std::numeric_limits<unsigned_type>::is_signed };

    // Ensure that unsigned_type is unsigned.
    static_assert(type_is_signed == false,
                  "error: type must be unsigned");

    constexpr std::size_t count
      { std::numeric_limits<unsigned_type>::digits/8 };

    std::size_t i { };

    for( ; i < count; ++i)
    {
      const std::uint8_t by
        {static_cast<std::uint8_t>(u >> (i * 8U)) };

      if(!send_byte(by))
      {
        break;
      }
    }

    return (i == count);
  }

  auto recv_byte() const -> std::uint8_t
  {
    return recv_buffer;
  }

private:
  std::uint8_t recv_buffer { };
};

auto start_session(const communication& com) -> bool;

auto start_session(const communication& com) -> bool
{
  constexpr std::uint32_t login_key { UINT32_C(0x12345678) };

  // Send the 32-bit login key.
  const bool start_session_is_ok { com.send_uint(login_key) };

  return start_session_is_ok;
}

auto main() -> int;

auto main() -> int
{
  const communication com { };

  const bool start_session_is_ok { start_session(com) };

  std::stringstream strm { };

  strm << "Result of start_session: " << std::boolalpha << start_session_is_ok;

  std::cout << strm.str() << std::endl;
}
