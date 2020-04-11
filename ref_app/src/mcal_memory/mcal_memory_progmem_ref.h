///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2020.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_MEMORY_PROGMEM_REF_2019_09_15_H_
  #define MCAL_MEMORY_PROGMEM_REF_2019_09_15_H_

  #include <mcal_memory/mcal_memory_progmem_access.h>

  // Implement a specialized reference type for read-only program memory.

  namespace mcal { namespace memory { namespace progmem {

  template<typename ValueType,
           typename AddressType>
  class progmem_ref
  {
  public:
    using address_type = AddressType;
    using value_type   = ValueType;

    explicit progmem_ref(const address_type& address) : my_address(address) { }

    progmem_ref(const progmem_ref& other) : my_address(other.my_address) { }

    ~progmem_ref() = default;

    explicit operator value_type() const
    {
      return read<value_type>(my_address);
    }

  private:
    const address_type my_address;

    progmem_ref() = delete;

    // This class is read only.
    progmem_ref& operator=(const progmem_ref&) = delete;
    progmem_ref& operator=(const value_type&) = delete;

    operator value_type() = delete;
  };

  } } } // namespace mcal::memory::progmem

#endif // MCAL_MEMORY_PROGMEM_REF_2019_09_15_H_
