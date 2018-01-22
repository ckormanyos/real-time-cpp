///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter05_03-001_communication_nontemplate.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

class communication
{
public:
  communication() { }

  virtual ~communication() { }

  virtual bool send_byte(const std::uint8_t b) const
  {
    // Simulate sending a byte on the PC.
    std::cout << "Sending: "
              << std::hex
              << std::showbase
              << unsigned(b)
              << std::endl;

    const std::ios::iostate cout_state = std::cout.rdstate();

    const bool send_byte_is_ok = ((cout_state & (std::ios::badbit | std::ios::failbit)) == 0);

    return send_byte_is_ok;
  }

  std::uint8_t recv_byte() const
  {
    return recv_buffer;
  }

private:
  std::uint8_t recv_buffer;
};

int main()
{
  communication com;

  const bool send_byte_is_ok = com.send_byte(0x55U);

  std::cout << "Result of send_byte: "
            << std::boolalpha
            << send_byte_is_ok
            << std::endl;
}
