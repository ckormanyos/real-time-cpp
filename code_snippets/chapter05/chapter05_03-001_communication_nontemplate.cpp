///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_03-001_communication_nontemplate.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>

class communication
{
public:
  communication() = default;

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

  auto recv_byte() const -> std::uint8_t
  {
    return recv_buffer;
  }

private:
  std::uint8_t recv_buffer { };
};

auto main() -> int;

auto main() -> int
{
  communication com { };

  const bool send_byte_is_ok { com.send_byte(0x55U) };

  std::stringstream strm { };

  strm << "Result of send_byte: " << std::boolalpha << send_byte_is_ok;

  std::cout << strm.str() << std::endl;
}
