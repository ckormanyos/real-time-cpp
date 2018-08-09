///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// chapter04_08-002_nonconst_com_class.cpp

#include <cstdint>
#include <iomanip>
#include <iostream>

#define __attribute__(a)

static std::uint8_t dummy_register_tbuf;
static std::uint8_t dummy_register_rbuf;

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
    *reinterpret_cast<std::uint8_t*>(tbuf) = by;

    // Simulate a receive interrupt event on the PC.
    com_recv_isr();

    return true;
  }

  bool recv_ready() const { return has_recv; }

  std::uint8_t recv_byte()
  {
    if(has_recv)
    {
      has_recv = false;

      return recv_buf;
    }

    return 0U;
  }

private:
  static constexpr std::uint8_t* tbuf = &dummy_register_tbuf;
  static constexpr std::uint8_t* rbuf = &dummy_register_rbuf;

  std::uint8_t recv_buf;
  bool has_recv;

  communication(const communication&) = delete;
  const communication& operator=(const communication&)
    = delete;

  friend void com_recv_isr();
};

bool wakeup(const communication& com)
{
  // OK. Call a const member of a const reference.
  return com.send_byte(0x12U);
}

bool login(communication& com)
{
  // OK. Call the const send_byte on a const reference.
  const bool wakeup_is_ok = wakeup(com);

  if(wakeup_is_ok)
  {
    // Compiler error!
    return (com.recv_byte() == 0x34U);
  }
  else
  {
    return false;
  }
}

namespace
{
  // A non-constant communication instance.
  communication com;
}

extern "C"
void com_recv_isr() __attribute__((interrupt))
{
  // Simulate a receive interrupt handler on the PC.
  com.recv_buf = 0x34U;

  com.has_recv = true;
}

int main()
{
  const bool login_is_ok = login(com);

  std::cout << std::boolalpha << "login_is_ok: " << login_is_ok << std::endl;
}
