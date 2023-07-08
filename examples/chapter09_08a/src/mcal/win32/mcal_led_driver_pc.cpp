///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2017 - 2022.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdint>
#include <thread>

#include <resource.h>

#include <mcal_led_driver_pc.h>
#include <mcal_led_sys_start_interface.h>

namespace
{
  constexpr UINT WM_MESSAGE_FROM_LED_MONOCHROME = (WM_USER + 1);
  constexpr UINT WM_MESSAGE_FROM_LED_RGB        = (WM_USER + 2);

  constexpr COLORREF color_red   = RGB(255U,   0U,   0U);
  constexpr COLORREF color_green = RGB(  0U, 255U,   0U);
  constexpr COLORREF color_blue  = RGB(  0U,   0U, 255U);
  constexpr COLORREF color_gray  = RGB(200U, 200U, 200U);
}

void post_message_led_rgb(const std::uint32_t color)
{
  if(mcal::led::sys_start_interface::my_exit_pc_api_flag() == false)
  {
    PostMessage(mcal::led::driver_pc::instance().get_handle_to_window(),
                WM_MESSAGE_FROM_LED_RGB,
                0U,
                static_cast<LPARAM>(color));
  }
}

void post_message_led_monochrome(const bool is_on)
{
  if(mcal::led::sys_start_interface::my_exit_pc_api_flag() == false)
  {
    ::PostMessage(mcal::led::driver_pc::instance().get_handle_to_window(),
                  WM_MESSAGE_FROM_LED_MONOCHROME,
                  0U,
                  static_cast<LPARAM>(is_on ? 1U : 0U));
  }
}

mcal::led::driver_pc& mcal::led::driver_pc::instance()
{
  static mcal::led::driver_pc driver_pc_instance;

  return driver_pc_instance;
}

bool mcal::led::driver_pc::create_window(HINSTANCE      handle_to_instance,
                                         const char*    window_caption,
                                         const COLORREF initial_rgb_color,
                                         const int      initial_icon_id,
                                         const int      screen_coordinate_x,
                                         const int      screen_coordinate_y,
                                         const int      window_width,
                                         const int      window_height,
                                         const DWORD    basic_style,
                                         const DWORD    extended_style)
{
  my_handle_to_instance = handle_to_instance;

  my_str_class_name = std::string(window_caption);

  {
    WNDCLASS window_class;

    // ******************************************************
    window_class.style         =  static_cast<UINT>(  UINT(CS_HREDRAW)
                                                    | UINT(CS_VREDRAW)
                                                    | UINT(CS_OWNDC));
    window_class.lpfnWndProc   =  my_window_callback;
    window_class.cbClsExtra    =  0;
    window_class.cbWndExtra    =  0;
    window_class.hInstance     =  my_handle_to_instance;
    window_class.hIcon         =  LoadIcon(my_handle_to_instance, MAKEINTRESOURCE(initial_icon_id));
    window_class.hCursor       =  LoadCursor(nullptr, IDC_ARROW);
    window_class.hbrBackground =  (HBRUSH) COLOR_GRAYTEXT;
    window_class.lpszMenuName  =  nullptr;
    window_class.lpszClassName =  my_str_class_name.c_str();

    const WORD register_class_result = RegisterClass(&window_class);

    static_cast<void>(register_class_result);
  }

  my_handle_to_window = CreateWindowEx(extended_style,
                                       my_str_class_name.c_str(),
                                       my_str_class_name.c_str(),
                                       basic_style,
                                       screen_coordinate_x  * scale_x(),
                                       screen_coordinate_y  * scale_y(),
                                       ( 4 + window_width)  * scale_x(),
                                       (12 + window_height) * scale_y(),
                                       nullptr,
                                       nullptr,
                                       my_handle_to_instance,
                                       nullptr);

  bool create_window_is_ok = (my_handle_to_window != nullptr);

  if(create_window_is_ok)
  {
    // Show the window.
    const bool redraw_window_is_ok =
      (RedrawWindow(my_handle_to_window, nullptr, nullptr, 0U) == TRUE);

    create_window_is_ok &= redraw_window_is_ok;

    const bool show_window_result_is_ok =
      (ShowWindow(my_handle_to_window, SW_SHOW) == TRUE);

    create_window_is_ok &= show_window_result_is_ok;

    // Initialize the RGB LED circle in the window with the initial RGB color.
    const bool draw_circle_led_rgb_is_ok =
      (   show_window_result_is_ok
       && draw_circle(100, 100, 72, 1, initial_rgb_color, true));

    create_window_is_ok &= draw_circle_led_rgb_is_ok;

    // Initialize the monochrome LED in the window with green.
    const bool draw_circle_led_monochrome_is_ok =
      (   show_window_result_is_ok
       && draw_circle(290, 100, 72, 1, color_green, true));

    create_window_is_ok &= draw_circle_led_monochrome_is_ok;
  }

  const HWND handle_to_active_window = GetActiveWindow();

  const bool create_window_result = (    create_window_is_ok
                                     && (handle_to_active_window != nullptr)
                                     && (my_handle_to_window == handle_to_active_window));

  return create_window_result;
}

bool mcal::led::driver_pc::draw_circle(const int      center_x,
                                       const int      center_y,
                                       const int      radius,
                                       const int      pen_width,
                                       const COLORREF pen_color,
                                       const bool     use_fill)
{
  // Get the handle to the window device context.
  const HDC handle_to_dc = GetDC(my_handle_to_window);

  // Get ready for the return value of this function.
  bool draw_elipse_is_ok = false;

  if(handle_to_dc != nullptr)
  {
    // Create the pen and (if necessary) the brush for drawing the circle.

    const HPEN handle_to_new_pen = CreatePen(PS_SOLID, pen_width, pen_color);
    const HPEN handle_to_old_pen = (HPEN) SelectObject(handle_to_dc, handle_to_new_pen);

    const HBRUSH handle_to_new_brush =
      (use_fill ? static_cast<HBRUSH>(CreateSolidBrush(pen_color))
                : static_cast<HBRUSH>(GetStockObject(NULL_BRUSH)));

    const HBRUSH handle_to_old_brush =
      static_cast<HBRUSH>(SelectObject(handle_to_dc, handle_to_new_brush));

    // Use the Win32 API function Ellipse() for drawing the circle.
    draw_elipse_is_ok = (Ellipse(handle_to_dc,
                                 center_x - radius,
                                 center_y + radius,
                                 center_x + radius,
                                 center_y - radius) == TRUE);

    {
      const BOOL delete_old_pen___is_ok = DeleteObject(SelectObject(handle_to_dc, handle_to_old_pen));
      const BOOL delete_old_brush_is_ok = DeleteObject(SelectObject(handle_to_dc, handle_to_old_brush));

      static_cast<void>(delete_old_pen___is_ok);
      static_cast<void>(delete_old_brush_is_ok);
    }

    const int release_dc_result = ReleaseDC(my_handle_to_window, handle_to_dc);

    static_cast<void>(release_dc_result);
  }

  return ((handle_to_dc != nullptr) && draw_elipse_is_ok);
}

bool mcal::led::driver_pc::set_icon(const int icon_id)
{
  // Set the icon of the application based on the icon ID.

  // Get the previous result of setting the icon.
  const ULONG_PTR previous_set_icon_result =
    GetClassLongPtr(my_handle_to_window, GCLP_HICON);

  const HICON load_icon_result =
    LoadIcon
    (
      my_handle_to_instance,
      MAKEINTRESOURCE(icon_id)
    );

  // Set the new icon.
  const ULONG_PTR set_icon_result =
    SetClassLongPtr(my_handle_to_window,
                    GCLP_HICON,
                    (LONG_PTR) load_icon_result);

  // Verify the result of setting the icon.
  return (set_icon_result == previous_set_icon_result);
}

LRESULT CALLBACK mcal::led::driver_pc::my_window_callback(HWND   handle_to_window,
                                                          UINT   message,
                                                          WPARAM w_param,
                                                          LPARAM l_param)
{
  // This is the standard Win32 API callback function.

  if(message == WM_PAINT) { ; }

  if(message == WM_MESSAGE_FROM_LED_MONOCHROME)
  {
    // Toggle the monochrome user LED on and off
    // according to the Boolean input from the application.

    const bool is_on = ((l_param != 0U) ? true : false);

    const bool draw_circle_is_ok =
      instance().draw_circle(290,
                             100,
                              72,
                               1,
                             (is_on ? color_green : color_gray),
                             true);

    static_cast<void>(draw_circle_is_ok);
  }

  if(message == WM_MESSAGE_FROM_LED_RGB)
  {
    // Animate the RGB LED with the colors of the spectrum
    // according to the RGB color input from the application.

    const std::uint8_t hue_r(std::uint8_t(l_param >>  0));
    const std::uint8_t hue_g(std::uint8_t(l_param >>  8));
    const std::uint8_t hue_b(std::uint8_t(l_param >> 16));

    // Handle possible icon transition, if any needs to be performed.
    if((hue_r == UINT8_C(255)) && (hue_g == UINT8_C(  0)) && (hue_b == UINT8_C(  0))) { instance().set_icon(IDI_CIRCLE_RED); }
    if((hue_r == UINT8_C(255)) && (hue_g == UINT8_C(255)) && (hue_b == UINT8_C(  0))) { instance().set_icon(IDI_CIRCLE_YELLOW); }
    if((hue_r == UINT8_C(  0)) && (hue_g == UINT8_C(255)) && (hue_b == UINT8_C(  0))) { instance().set_icon(IDI_CIRCLE_GREEN); }
    if((hue_r == UINT8_C(  0)) && (hue_g == UINT8_C(255)) && (hue_b == UINT8_C(255))) { instance().set_icon(IDI_CIRCLE_CYAN); }
    if((hue_r == UINT8_C(  0)) && (hue_g == UINT8_C(  0)) && (hue_b == UINT8_C(255))) { instance().set_icon(IDI_CIRCLE_BLUE); }
    if((hue_r == UINT8_C(255)) && (hue_g == UINT8_C(  0)) && (hue_b == UINT8_C(255))) { instance().set_icon(IDI_CIRCLE_MAGENTA); }

    const COLORREF rgb_color = RGB(hue_r, hue_g, hue_b);

    const bool draw_circle_is_ok =
      instance().draw_circle(100,
                             100,
                              72,
                               1,
                             rgb_color,
                             true);

    static_cast<void>(draw_circle_is_ok);
  }

  if(message == WM_DESTROY)
  {
    // Set the Win32 API exit flag that is used
    // to exit the sys_start thread.
    mcal::led::sys_start_interface::my_exit_pc_api_flag() = true;

    // Clean up the window and exit the program.
    UnregisterClass(instance().str_class_name().c_str(),
                    instance().get_handle_to_instance());

    PostQuitMessage(0);
  }

  const LRESULT def_window_proc_result =
    DefWindowProc(handle_to_window, message, w_param, l_param);

  return def_window_proc_result;
}

int WINAPI WinMain(HINSTANCE handle_to_instance, HINSTANCE, LPSTR, int)
{
  // This is the standard Win32 API main function.

  // Create the window that contains the circles
  // of the RGB LED and the monochrome LED.
  const bool create_window_is_ok =
    mcal::led::driver_pc::instance().create_window(handle_to_instance,
                                                   "LED Animation chapter09_08a",
                                                   color_red,
                                                   DWORD(IDI_CIRCLE_RED));

  static_cast<void>(create_window_is_ok);

  // Start the main system thread, which is used
  // for work not within the Win32 API.
  // The simulated multitasking environment runs
  // in this thread.

  std::thread sys_start_thread(mcal::led::sys_start_interface::my_sys_start);

  // Detach this process from its spawning thread object.
  sys_start_thread.detach();

  bool get_message_is_ok = true;

  // Enter the Windows message loop.
  while(get_message_is_ok)
  {
    Sleep(0U);

    MSG message;

    const BOOL peek_message_result = PeekMessage(&message, nullptr, 0U, 0U, PM_NOREMOVE);

    const bool peek_message_has_message = (peek_message_result == TRUE);

    if(peek_message_has_message == false)
    {
      Sleep(3U);
    }
    else
    {
      Sleep(0U);

      get_message_is_ok = (GetMessage(&message, nullptr, 0U, 0U) == TRUE);

      if(get_message_is_ok)
      {
        // Process Win32 API messages.
        const bool is_window  = (IsWindow       (mcal::led::driver_pc::instance().get_handle_to_window()) == TRUE);
        const bool is_dlg_msg = (IsDialogMessage(mcal::led::driver_pc::instance().get_handle_to_window(), &message) == TRUE);

        if(   (is_window  == FALSE)
           || (is_dlg_msg == FALSE))
        {
          const bool translate_message_is_ok = (TranslateMessage(&message) == TRUE);
          const bool dispatch__message_is_ok = (DispatchMessage (&message) == TRUE);

          static_cast<void>(translate_message_is_ok);
          static_cast<void>(dispatch__message_is_ok);
        }
      }
    }
  }

  return 0;
}
