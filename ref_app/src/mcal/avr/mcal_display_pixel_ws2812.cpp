///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <algorithm>
#include <array>
#include <mcal_cpu.h>
#include <mcal_irq.h>
#include <mcal_port.h>
#include <mcal_reg_access.h>
#include <mcal/mcal_display_pixel.h>

namespace mcal { namespace display { namespace detail {

namespace nop_twiddle
{
  template<const std::uint_fast8_t nop_count>
  struct nop_maker
  {
    static void nops()
    {
      mcal::cpu::nop();

      nop_maker<nop_count - UINT8_C(1)>::nops();
    }
  };

  template<>
  struct nop_maker<UINT8_C(0)>
  {
    static void nops() { }
  };
}

template<const std::uint_least16_t size_value_param>
class pixel_rgb_collection_linear_ws2812;

template<const std::uint8_t      port_addr_param,
         const std::uint_fast8_t port_bpos_param>
class pixel_rgb_ws2812 : public mcal::display::pixel_rgb
{
public:
  typedef mcal::port::port_pin<std::uint8_t,
                               std::uint8_t,
                               port_addr_param,
                               port_bpos_param> display_port_type;

  pixel_rgb_ws2812() : pointer_to_rgb(nullptr)
  {
    display_port_type::set_direction_output();
  }

  virtual ~pixel_rgb_ws2812() { }

  virtual bool set_tone_red  (const std::uint8_t r) { *(pointer_to_rgb + 1U) = r; return true; }
  virtual bool set_tone_green(const std::uint8_t g) { *(pointer_to_rgb + 0U) = g; return true; }
  virtual bool set_tone_blue (const std::uint8_t b) { *(pointer_to_rgb + 2U) = b; return true; }

  virtual bool get_tone_red  (std::uint8_t& r) { r = *(pointer_to_rgb + 1U); return true; }
  virtual bool get_tone_green(std::uint8_t& g) { g = *(pointer_to_rgb + 0U); return true; }
  virtual bool get_tone_blue (std::uint8_t& b) { b = *(pointer_to_rgb + 2U); return true; }

private:
  std::uint8_t* pointer_to_rgb;

  bool allocate(std::uint8_t* p_rgb)
  {
    if(pointer_to_rgb == nullptr)
    {
      pointer_to_rgb = p_rgb;

      return true;
    }
    else
    {
      return false;
    }
  }

  template<const std::uint8_t bit_number_param>
  static void push_data(const std::uint8_t data_value)
  {
    if(std::uint8_t(data_value & (UINT8_C(0x80) >> bit_number_param)) != UINT8_C(0))
    {
      *reinterpret_cast<volatile std::uint8_t*>(port_addr_param) |= std::uint8_t(1U << port_bpos_param);
      nop_twiddle::nop_maker<UINT8_C(8)>::nops();

      *reinterpret_cast<volatile std::uint8_t*>(port_addr_param) &= std::uint8_t(~(1U << port_bpos_param));
      nop_twiddle::nop_maker<UINT8_C(4)>::nops();
    }
    else
    {
      *reinterpret_cast<volatile std::uint8_t*>(port_addr_param) |= std::uint8_t(1U << port_bpos_param);
      nop_twiddle::nop_maker<UINT8_C(3)>::nops();

      *reinterpret_cast<volatile std::uint8_t*>(port_addr_param) &= std::uint8_t(~(1U << port_bpos_param));
      nop_twiddle::nop_maker<UINT8_C(10)>::nops();
    }
  }

  virtual void latch_out() const
  {
    const std::uint8_t tone_red    = *(pointer_to_rgb + 1U);
    const std::uint8_t tone_green  = *(pointer_to_rgb + 0U);
    const std::uint8_t tone_blue   = *(pointer_to_rgb + 2U);

    push_data<UINT8_C(0)>(tone_green);
    push_data<UINT8_C(1)>(tone_green);
    push_data<UINT8_C(2)>(tone_green);
    push_data<UINT8_C(3)>(tone_green);
    push_data<UINT8_C(4)>(tone_green);
    push_data<UINT8_C(5)>(tone_green);
    push_data<UINT8_C(6)>(tone_green);
    push_data<UINT8_C(7)>(tone_green);

    push_data<UINT8_C(0)>(tone_red);
    push_data<UINT8_C(1)>(tone_red);
    push_data<UINT8_C(2)>(tone_red);
    push_data<UINT8_C(3)>(tone_red);
    push_data<UINT8_C(4)>(tone_red);
    push_data<UINT8_C(5)>(tone_red);
    push_data<UINT8_C(6)>(tone_red);
    push_data<UINT8_C(7)>(tone_red);

    push_data<UINT8_C(0)>(tone_blue);
    push_data<UINT8_C(1)>(tone_blue);
    push_data<UINT8_C(2)>(tone_blue);
    push_data<UINT8_C(3)>(tone_blue);
    push_data<UINT8_C(4)>(tone_blue);
    push_data<UINT8_C(5)>(tone_blue);
    push_data<UINT8_C(6)>(tone_blue);
    push_data<UINT8_C(7)>(tone_blue);
  }

  template<const std::uint_least16_t size_value_param>
  friend class pixel_rgb_collection_linear_ws2812;
};

typedef pixel_rgb_ws2812<mcal::reg::portb, 0U> pixel_rgb_ws2812_type;

template<const std::uint_least16_t size_value_param>
class pixel_rgb_collection_linear_ws2812 : public mcal::display::pixel_rgb_collection_linear
{
public:
  pixel_rgb_collection_linear_ws2812() : pixel_rgb_collection_linear(size_value_param)
  {
    std::fill(pixel_rgb_ws2812_memory,
              pixel_rgb_ws2812_memory + sizeof(pixel_rgb_ws2812_memory),
              std::uint8_t(0U));

    std::uint8_t* p_rgb = pixel_rgb_ws2812_memory;

    std::for_each(my_pixel_rgb_ws2812_data.begin(),
                  my_pixel_rgb_ws2812_data.end(),
                  [&p_rgb](pixel_rgb_ws2812_type& the_pixel_rgb)
                  {
                    const bool allocate_pixel_is_ok = the_pixel_rgb.allocate(p_rgb);

                    static_cast<void>(allocate_pixel_is_ok);

                    p_rgb += UINT8_C(4);
                  });
  }

  virtual void refresh() const
  {
    mcal::irq::disable_all();

    std::for_each(my_pixel_rgb_ws2812_data.begin(),
                  my_pixel_rgb_ws2812_data.end(),
                  [](const pixel_rgb_ws2812_type& the_pixel_rgb)
                  {
                    the_pixel_rgb.latch_out();
                  });

    mcal::irq::enable_all();
  }

  virtual ~pixel_rgb_collection_linear_ws2812() { }

private:
  std::array<pixel_rgb_ws2812_type, size_value_param> my_pixel_rgb_ws2812_data;

  std::uint8_t pixel_rgb_ws2812_memory[size_value_param * 4U];

  virtual mcal::display::pixel_rgb* at(const std::uint_least16_t i)
  {
    return ((i < my_length) ? &my_pixel_rgb_ws2812_data[i] : &my_pixel_rgb_ws2812_data[0U]);
  }
};

} } } // namespace mcal::display::detail

mcal::display::pixel_rgb_collection_linear& mcal::display::pixel_rgb_collection0()
{
  static detail::pixel_rgb_collection_linear_ws2812<UINT16_C(64)> the_pixel_rgb_collection;

  return the_pixel_rgb_collection;
}


/*

///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <mcal/mcal.h>
#include <mcal/mcal_display_pixel.h>
#include <util/utility/util_time.h>

namespace app
{
  namespace led
  {
    void task_init();
    void task_func();
  }
}

namespace
{
  typedef util::timer<std::uint32_t> timer_type;

  timer_type app_led_timer(timer_type::seconds(1U));
}

void app::led::task_init()
{
  mcal::led::led0.toggle();

  std::uint_least8_t i = UINT8_C(0);

  for( ; i < std::uint8_t(1U * 8U); ++i) { mcal::display::pixel_rgb_collection0().at(i)->set_color(std::uint8_t(255U - (0U * 85U)), std::uint8_t(255U - (3U * 85U)), std::uint8_t(255U - (3U * 85U))); }
  for( ; i < std::uint8_t(2U * 8U); ++i) { mcal::display::pixel_rgb_collection0().at(i)->set_color(std::uint8_t(255U - (1U * 85U)), std::uint8_t(255U - (2U * 85U)), std::uint8_t(255U - (3U * 85U))); }
  for( ; i < std::uint8_t(3U * 8U); ++i) { mcal::display::pixel_rgb_collection0().at(i)->set_color(std::uint8_t(255U - (2U * 85U)), std::uint8_t(255U - (1U * 85U)), std::uint8_t(255U - (3U * 85U))); }
  for( ; i < std::uint8_t(4U * 8U); ++i) { mcal::display::pixel_rgb_collection0().at(i)->set_color(std::uint8_t(255U - (3U * 85U)), std::uint8_t(255U - (0U * 85U)), std::uint8_t(255U - (3U * 85U))); }
  for( ; i < std::uint8_t(5U * 8U); ++i) { mcal::display::pixel_rgb_collection0().at(i)->set_color(std::uint8_t(255U - (3U * 85U)), std::uint8_t(255U - (1U * 85U)), std::uint8_t(255U - (2U * 85U))); }
  for( ; i < std::uint8_t(6U * 8U); ++i) { mcal::display::pixel_rgb_collection0().at(i)->set_color(std::uint8_t(255U - (3U * 85U)), std::uint8_t(255U - (2U * 85U)), std::uint8_t(255U - (1U * 85U))); }
  for( ; i < std::uint8_t(7U * 8U); ++i) { mcal::display::pixel_rgb_collection0().at(i)->set_color(std::uint8_t(255U - (3U * 85U)), std::uint8_t(255U - (3U * 85U)), std::uint8_t(255U - (0U * 85U))); }
  for( ; i < std::uint8_t(8U * 8U); ++i) { mcal::display::pixel_rgb_collection0().at(i)->set_color(std::uint8_t(255U - (2U * 85U)), std::uint8_t(255U - (3U * 85U)), std::uint8_t(255U - (1U * 85U))); }

  mcal::display::pixel_rgb_collection0().refresh();
}

void app::led::task_func()
{
  if(app_led_timer.timeout())
  {
    mcal::display::pixel_rgb_collection0().refresh();

    app_led_timer.start_interval(timer_type::seconds(1U));

    mcal::led::led0.toggle();
  }
}

*/
