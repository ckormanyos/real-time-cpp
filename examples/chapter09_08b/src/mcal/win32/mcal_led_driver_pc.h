///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2018.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MCAL_LED_DRIVER_PC_2017_11_20_H_
  #define MCAL_LED_DRIVER_PC_2017_11_20_H_

  #include <string>

  #include <windows.h>

  #include <mcal_led_monochrome_pc.h>
  #include <mcal_led_rgb_pc.h>

  namespace mcal { namespace led {

  class driver_pc final
  {
  public:
    driver_pc() = default;

    auto get_handle_to_window() const -> const HWND { return my_handle_to_window; }

    auto create_window(HINSTANCE      handle_to_instance,                        // Handle to window instance
                       const char*    window_caption,                            // Window caption
                       const COLORREF initial_rgb_color,                         // Initial RGB color
                       const int      initial_icon_id,                           // ID of initial icon
                       const int      screen_coordinate_x =   250,               // Screen coordinate X
                       const int      screen_coordinate_y =   150,               // Screen coordinate Y
                       const int      window_width        =   400,               // Window width
                       const int      window_height       =   210,               // Window height
                       const DWORD    basic_style         =  (  WS_MINIMIZEBOX
                                                              | WS_CAPTION
                                                              | WS_POPUP
                                                              | WS_SYSMENU),     // Window basic style
                       const DWORD    extended_style      =   0U) -> bool;       // Window extended style

    static auto instance() -> driver_pc&;

  private:
    HWND        my_handle_to_window   { nullptr };
    HINSTANCE   my_handle_to_instance { nullptr };
    std::string my_str_class_name     { };

    static auto scale_x() -> int { return 1; }
    static auto scale_y() -> int { return 1; }

    auto str_class_name() const -> const std::string& { return my_str_class_name; }

    auto get_handle_to_instance() const -> const HINSTANCE { return my_handle_to_instance; }

    auto draw_circle(const int      center_x,
                     const int      center_y,
                     const int      radius,
                     const int      pen_width,
                     const COLORREF pen_color,
                     const bool     use_fill) -> bool;

    auto set_icon(const int icon_id) -> bool;

    // This is the standard Win32 API callback function.
    static LRESULT CALLBACK my_window_callback(HWND   handle_to_window,
                                               UINT   message,
                                               WPARAM w_param,
                                               LPARAM l_param);
  };

  } } // namespace mcal::led

#endif // MCAL_LED_DRIVER_PC_2017_11_20_H_
