///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2021.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MATH_TEST_INDEPENDENT_TEST_SYSTEM_MATHLINK_2019_12_29_H_
  #define MATH_TEST_INDEPENDENT_TEST_SYSTEM_MATHLINK_2019_12_29_H_

  #include <array>
  #include <string>
  #include <type_traits>

  #include <math/test/math_test_independent_test_system_base.h>

  extern "C"
  {
    typedef struct ml_environment* WSENV;
    typedef void*                  WSENVPARAM;
    typedef WSENVPARAM             WSEnvironmentParameter;
    typedef WSENV                  WSEnvironment;
    typedef struct MLink*          WSLINK;

    extern void          WSReleaseString (WSLINK, const char*);
    extern WSEnvironment WSInitialize    (WSEnvironmentParameter);
    extern void          WSDeinitialize  (WSEnvironment);
    extern WSLINK        WSOpen          (int, char**);
    extern int           WSClose         (WSLINK);
    extern int           WSNextPacket    (WSLINK);
    extern int           WSNewPacket     (WSLINK);
    extern int           WSPutFunction   (WSLINK, const char*, int);
    extern int           WSPutString     (WSLINK, const char*);
    extern int           WSEndPacket     (WSLINK);
    extern int           WSError         (WSLINK);
    extern int           WSGetString     (WSLINK, const char**);
  }

  namespace math { namespace test {

  namespace detail {

  inline constexpr char* strcpy_unsafe(char* dst, const char* src)
  {
    // Use a local implementation of string copy.
    while((*dst++ = *src++) != char('\0')) { ; }

    return dst;
  }

  inline constexpr std::uint_fast32_t strlen_unsafe(const char* pstr)
  {
    // Use a local implementation of string length.
    std::uint_fast32_t u = 0U;

    while(pstr != nullptr && *pstr != char('\0'))
    {
      ++pstr;
      ++u;
    }

    return u;
  }

  } // namespace detail

  template<const char* PtrStrLocationMathLinkKernel = nullptr>
  class independent_test_system_mathlink
    : public math::test::independent_test_system_base
  {
  private:
    static constexpr int RETURNPKT = 3;

    static constexpr int return_packet_id() { return RETURNPKT; }

  public:
    // This is the computer_algebra_system_mathlink class.
    // It provides access functions to WSTP.

    constexpr independent_test_system_mathlink() noexcept
    {
      my_valid = ((is_open() == false) ? open() : is_open());
    }

    virtual ~independent_test_system_mathlink() noexcept
    {
      const volatile bool close_is_ok = close();

      static_cast<void>(close_is_ok);
    }

    virtual bool is_prime(const char* const pstr_prime_candidate) const override
    {
      // Test with, for eample,
      // PrimeQ[FromDigits["A6BAC43FEE73E832401B1E32417BD0AF",16]]

      const std::string str_cmd = "PrimeQ[FromDigits[\"" + std::string(pstr_prime_candidate) + "\",16]]";

      std::string str_rsp;

      return (send_command(str_cmd, &str_rsp) && (str_rsp == "True"));
    }

    static constexpr bool get_valid() noexcept { return my_valid; }

  private:
    static bool   my_valid;
    static WSENV  env_ptr;
    static WSLINK lnk_ptr;

    static bool send_command(const std::string& str_cmd, std::string* str_rsp)
    {
      const bool suppress_output = (str_rsp == nullptr);

      std::string str_cmd_local = str_cmd;

      if(suppress_output)
      {
        str_cmd_local.push_back(char(';'));
      }

      bool send_command_is_ok = (    put_function("EvaluatePacket", 1)
                                  && put_function("ToExpression", 1)
                                  && put_string(str_cmd_local)
                                  && end_packet());

      if(send_command_is_ok)
      {
        // Skip any packets before the first ReturnPacket.
        for(;;)
        {
          const int next_packet_result = next_packet();

          if(   (next_packet_result == 0)
             || (next_packet_result == return_packet_id()))
          {
            break;
          }

          const int new_packet_result = new_packet();

          static_cast<void>(new_packet_result);

          if(error() != 0)
          {
            send_command_is_ok = false;

            break;
          }
        }
      }

      bool recv_response_is_ok = send_command_is_ok;

      if(send_command_is_ok)
      {
        recv_response_is_ok &= get_string(str_rsp);
      }

      const bool result_is_ok = (send_command_is_ok && recv_response_is_ok);

      return result_is_ok;
    }

    static constexpr WSENV&  global_env_ptr() noexcept { return env_ptr; }
    static constexpr WSLINK& global_lnk_ptr() noexcept { return lnk_ptr; }

    static int  next_packet ()                                 noexcept { return  ::WSNextPacket (global_lnk_ptr()); }
    static int  new_packet  ()                                 noexcept { return  ::WSNewPacket  (global_lnk_ptr()); }
    static bool put_function(const std::string& str, int argc) noexcept { return (::WSPutFunction(global_lnk_ptr(), str.c_str(), argc) != 0); }
    static bool put_string  (const std::string& str)           noexcept { return (::WSPutString  (global_lnk_ptr(), str.c_str()) != 0); }
    static bool end_packet  ()                                 noexcept { return (::WSEndPacket  (global_lnk_ptr()) != 0); }
    static int  error       ()                                 noexcept { return  ::WSError      (global_lnk_ptr()); }

    static bool get_string(std::string* str_rsp)
    {
      const char* s = nullptr;

      const bool get_string_is_ok = (::WSGetString(global_lnk_ptr(), &s) != 0);

      if((str_rsp != nullptr) && (get_string_is_ok == true))
      {
        str_rsp->resize(detail::strlen_unsafe(s));

        std::copy(s, s + str_rsp->size(), str_rsp->begin());
      }

      ::WSReleaseString(global_lnk_ptr(), s);

      return get_string_is_ok;
    }

    static constexpr bool is_open() noexcept
    {
      return (   (global_env_ptr() != nullptr)
              && (global_lnk_ptr() != nullptr));
    }

    static bool open(const char* str_location_math_kernel_user = PtrStrLocationMathLinkKernel) noexcept
    {
      // Initialize the mathlink kernel.
      global_env_ptr() = ::WSInitialize(nullptr);

      if(global_env_ptr() == nullptr)
      {
        ;
      }
      else
      {
        // TBD: Is it possible (or sensible) to Query the Win* registry
        // in order to find the default location of the mathlink kernel.

        // TBD: What about supporting non-Win* platforms like *nix?

        constexpr char str_location_math_kernel_default[] =
          "\"C:\\Program Files\\Wolfram Research\\Mathematica\\12.0\\MathKernel.exe\"";

        // Create a list of constant arguments for opening the mathlink kernel.
        using const_args_strings_type = std::array<std::string, 5U>;

        const const_args_strings_type const_args_strings =
        {{
          std::string("-linkname"),
          ((str_location_math_kernel_user == nullptr) ? std::string(str_location_math_kernel_default)
                                                      : std::string(str_location_math_kernel_user)),
          std::string("-linkmode"),
          std::string("launch"),
          std::string()
        }};

        char* c0 = new char[  64U]; detail::strcpy_unsafe(c0, const_args_strings[0U].c_str());
        char* c1 = new char[1024U]; detail::strcpy_unsafe(c1, const_args_strings[1U].c_str());
        char* c2 = new char[  64U]; detail::strcpy_unsafe(c2, const_args_strings[2U].c_str());
        char* c3 = new char[  64U]; detail::strcpy_unsafe(c3, const_args_strings[3U].c_str());

        // Create a list of non-constant character pointers for opening the mathlink kernel.
        char* nonconst_args_pointers[std::tuple_size<const_args_strings_type>::value] =
        {
          c0, c1, c2, c3, nullptr
        };

        // Open the mathlink kernel.
        global_lnk_ptr() = ::WSOpen(int(const_args_strings.size()), nonconst_args_pointers);

        delete [] c0;
        delete [] c1;
        delete [] c2;
        delete [] c3;

        if(global_lnk_ptr() == nullptr)
        {
          ::WSDeinitialize(global_env_ptr());

          global_env_ptr() = nullptr;
        }
      }

      return is_open();
    }

    static bool close() noexcept
    {
      const bool close_is_ok = is_open();

      if(global_lnk_ptr() != nullptr)
      {
        ::WSClose(global_lnk_ptr());

        global_lnk_ptr() = nullptr;
      }

      if(global_env_ptr() != nullptr)
      {
        ::WSDeinitialize(global_env_ptr());

        global_env_ptr() = nullptr;
      }

      return close_is_ok;
    }
  };

  template<const char* PtrStrLocationMathLinkKernel> bool   math::test::independent_test_system_mathlink<PtrStrLocationMathLinkKernel>::my_valid = false;
  template<const char* PtrStrLocationMathLinkKernel> WSENV  math::test::independent_test_system_mathlink<PtrStrLocationMathLinkKernel>::env_ptr  = nullptr;
  template<const char* PtrStrLocationMathLinkKernel> WSLINK math::test::independent_test_system_mathlink<PtrStrLocationMathLinkKernel>::lnk_ptr  = nullptr;

  } } // namespace math::test

#endif // MATH_TEST_INDEPENDENT_TEST_SYSTEM_MATHLINK_2019_12_29_H_
