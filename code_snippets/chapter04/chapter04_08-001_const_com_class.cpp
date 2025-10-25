///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_08-001_const_com_class.cpp

#include <cstdint>
#include <format>
#include <iomanip>
#include <iostream>
#include <string>

#define __attribute__(attr)

namespace mcal
{
  namespace reg
  {
    // Simulate the transmit and receive hardware buffers on the PC.
    std::uint8_t dummy_register_tbuf { };
    std::uint8_t dummy_register_rbuf { };
  }
}

class communication
{
public:
  communication() = default;

  ~communication() = default;

  auto send_byte(const std::uint8_t by) const -> bool
  {
    // Transmit the byte.
    *tbuf = by;

    return true;
  }

  auto recv_ready() const -> bool { return has_recv; }

  std::uint8_t recv_byte()
  {
    if(has_recv)
    {
      has_recv = false;

      recv_buf = *rbuf;

      return recv_buf;
    }

    return 0U;
  }

private:
  static       std::uint8_t* tbuf;
  static const std::uint8_t* rbuf;

  std::uint8_t recv_buf { };
  bool has_recv { };

  communication(const communication&) = delete;

  const communication& operator=(const communication&) = delete;
};

      std::uint8_t* communication::tbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_tbuf);
const std::uint8_t* communication::rbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_rbuf);

auto wakeup(const communication& com) -> bool // Emphasize: com is a comst reference.
{
  // Call the const send_byte function on a const reference.
  return com.send_byte(UINT8_C(0x12));
}

namespace
{
  // Instantiate a constant communication instance.
  const communication com { };
}

int main()
{
  const bool wakeup_is_ok { wakeup(com) };

  const std::string str_wakeup = std::format("wakeup_is_ok: {}", wakeup_is_ok);

  std::cout << str_wakeup << std::endl;
}
