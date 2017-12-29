///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_DEVICE_DISPLAY_BASE_2017_12_27_H_
  #define UTIL_DEVICE_DISPLAY_BASE_2017_12_27_H_

  #include <cstdint>
  #include <iterator>

  #include <util/utility/util_noncopyable.h>

  namespace util
  {
    namespace device
    {
      class display_base : private util::noncopyable
      {
      public:
        virtual ~display_base() { }

        bool write(const std::uint8_t value_to_write)
        {
          return do_write(value_to_write);
        }

        bool read(std::uint8_t& value_to_read) const
        {
          return do_read(value_to_read);
        }

      protected:
        display_base() : my_data() { }

        display_base(const std::uint8_t value_to_write) : my_data()
        {
          const bool write_is_ok = write(value_to_write);

          static_cast<void>(write_is_ok);
        }

        void set_data(const std::uint8_t data)  { my_data = data; }

        std::uint8_t get_data() const { return my_data; }

      private:
        std::uint8_t my_data;

        virtual bool do_write(const std::uint8_t value_to_write) = 0;
        virtual bool do_read (std::uint8_t& value_to_read) const = 0;
      };
    }
  }

#endif // UTIL_DEVICE_DISPLAY_BASE_2017_12_27_H_
