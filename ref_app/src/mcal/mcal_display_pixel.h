///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2015.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _MCAL_DISPLAY_PIXEL_2015_02_23_H_
  #define _MCAL_DISPLAY_PIXEL_2015_02_23_H_

  #include <cstdint>
  #include <util/utility/util_noncopyable.h>

  namespace mcal { namespace display {

  class pixel_base : private util::noncopyable
  {
  public:
    virtual ~pixel_base() { }

  protected:
    pixel_base() { }
  };

  class pixel_rgb : public pixel_base
  {
  public:
    typedef std::uint32_t color_type;

    virtual ~pixel_rgb() { }

    bool set_color(const color_type& color)
    {
      set_tone_red  (static_cast<std::uint8_t>(color >>  0));
      set_tone_green(static_cast<std::uint8_t>(color >>  8));
      set_tone_blue (static_cast<std::uint8_t>(color >> 16));

      return true;
    }

    bool set_color(const std::uint8_t tone_red, const std::uint8_t tone_green, const std::uint8_t tone_blue)
    {
      set_tone_red  (tone_red);
      set_tone_green(tone_green);
      set_tone_blue (tone_blue);

      return true;
    }

    bool get_color(color_type& color)
    {
      color = color_type();

      std::uint8_t tone_red;
      std::uint8_t tone_green;
      std::uint8_t tone_blue ;

      static_cast<void>(get_tone_red  (tone_red));
      static_cast<void>(get_tone_green(tone_green));
      static_cast<void>(get_tone_blue (tone_blue));

      color =   color_type(color_type(tone_red)   <<  0)
              | color_type(color_type(tone_green) <<  8)
              | color_type(color_type(tone_blue)  << 16);

      return true;
    }

    virtual bool set_tone_red  (const std::uint8_t r) = 0;
    virtual bool set_tone_green(const std::uint8_t g) = 0;
    virtual bool set_tone_blue (const std::uint8_t b) = 0;

    virtual bool get_tone_red  (std::uint8_t& r) = 0;
    virtual bool get_tone_green(std::uint8_t& g) = 0;
    virtual bool get_tone_blue (std::uint8_t& b) = 0;

  protected:
    pixel_rgb(const color_type& color = color_type())
    {
      set_color(color);
    }
  };

  class pixel_rgb_collection_base : private util::noncopyable
  {
  public:
    virtual ~pixel_rgb_collection_base() { }

    virtual void refresh() const = 0;

  protected:
    pixel_rgb_collection_base() { }
  };

  class pixel_rgb_collection_linear : public pixel_rgb_collection_base
  {
  public:
    virtual ~pixel_rgb_collection_linear() { }

    std::uint_least16_t length() const
    {
      return my_length;
    }

    virtual pixel_rgb* at(const std::uint_least16_t) = 0;

  protected:
    const std::uint_least16_t my_length;

    pixel_rgb_collection_linear(const std::uint_least16_t len) : my_length(len) { }
  };

  pixel_rgb_collection_linear& pixel_rgb_collection0();

  } } // namespace mcal::display

#endif // _MCAL_DISPLAY_PIXEL_2015_02_23_H_
