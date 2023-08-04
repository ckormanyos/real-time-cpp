///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_08-001_const_com_class.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

#define __attribute__(attr)

namespace mcal
{
  namespace reg
  {
    // Simulate the transmit and receive hardware buffers on the PC.
    std::uint8_t dummy_register_tbuf;
    std::uint8_t dummy_register_rbuf;
  }
}

extern "C"
void com_recv_isr() __attribute__((interrupt));

class communication
{
public:
  communication() : recv_buf(0U),
                    has_recv(false) { }

  ~communication() = default;

  bool send_byte(const std::uint8_t by) const
  {
    // Transmit the byte.
    *tbuf = by;

    return true;
  }

  bool recv_ready() const { return has_recv; }

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

  std::uint8_t recv_buf;
  bool has_recv;

  communication(const communication&) = delete;

  const communication& operator=(const communication&) = delete;

  friend void com_recv_isr();
};

      std::uint8_t* communication::tbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_tbuf);
const std::uint8_t* communication::rbuf = reinterpret_cast<std::uint8_t*>(&mcal::reg::dummy_register_rbuf);

bool wakeup(const communication& com) // Emohasize: com is a comst reference.
{
  // Call the const send_byte function on a const reference.
  return com.send_byte(0x12U);
}

namespace
{
  // Instantiate a constant communication instance.
  const communication com;
}

int main()
{
  const bool wakeup_is_ok = wakeup(com);

  std::cout << std::boolalpha << "wakeup_is_ok: " << wakeup_is_ok << std::endl;
}
