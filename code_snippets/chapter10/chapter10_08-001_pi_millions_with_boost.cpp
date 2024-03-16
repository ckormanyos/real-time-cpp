///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2019 - 2024.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

// chapter10_08-001_pi_millions_with_boost.cpp
// See also: https://godbolt.org/z/5cd4YonWq

// This program can be used to compute millions of digits of pi.
// In fact, it has been used to compute more than one billion
// decimal digits of pi. Boost.Multiprecision is combined with
// GMP (or MPIR) in order to carry out the calculation of pi.

// This program requires inclusion of Boost.Multiprecision
// and linking with GMP (or MPIR on certain targets).

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include <boost/multiprecision/gmp.hpp>

namespace pi { namespace millions { namespace detail {

// *****************************************************************************
// Function    : template<typename float_type>
//               const float_type& calculate_pi_template(const bool print_progress)
//
// Description : Compute pi using a quadratically convergent Gauss AGM,
//               in the Schoenhage variant. For a description of the algorithm,
//               see Algorithm 16.148, Chapter 16, page 236 in the book
//               J. Arndt and C. Haenel, "Pi Unleashed",
//               (Springer Verlag, Heidelberg, 2001).
//
//               The parameter print_progress_to_cout (= true),
//               will print calculation progress to std::cout.
//
//               Book reference for "Pi Unleashed":
//               https://www.springer.com/de/book/9783642567353
//
// *****************************************************************************
template<typename float_type>
const float_type& pi(const bool print_progress = false)
{
  static bool is_init;

  static float_type val_pi;

  if(!is_init)
  {
    is_init = true;

    float_type a (1.0F);
    float_type bB(0.5F);
    float_type s (0.5F);
    float_type t (0.375F);

    // This loop is designed for computing a maximum of a few billion
    // decimal digits of pi. The number of digits roughly doubles
    // with each iteration of the loop. After 20 iterations,
    // the precision is about 2.8 million decimal digits.
    // After 29 iterations, the precision is more than one
    // billion decimal digits.

    for(std::uint_least16_t k = UINT8_C(1); k < UINT8_C(64); ++k)
    {
      using std::sqrt;

      a      += sqrt(bB);
      a      /= 2U;
      val_pi  = a;
      val_pi *= val_pi;
      bB      = (val_pi - t);
      bB     *= 2U;

      const float_type iterate_term((bB - val_pi) * (UINT64_C(1) << k));

      s += iterate_term;

      // Extract the base-10 order of magnitude
      // to estimate the base-10 digits in this
      // iteration.

      // Here, we produce a short printout
      // of the iteration term that is subsequently
      // parsed with a regular expression
      // for extracting the base-10 order.

      using std::ilogb;

      // Assess the number of precise digits from iterate_term.

      const auto ilogb_as_abs_value =
        static_cast<std::uint32_t>
        (
          (std::max)(static_cast<int>(-ilogb(iterate_term)), static_cast<int>(INT8_C(0)))
        );

      const auto digits10_iterate =
        static_cast<std::uint64_t>
        (
          static_cast<std::uint64_t>
          (
            static_cast<std::uint64_t>(ilogb_as_abs_value) * static_cast<std::uint64_t>(UINT16_C(301))
          )
          / static_cast<std::uint64_t>(UINT16_C(1000))
        );

      if(print_progress)
      {
        std::cout << "Base-10 digits of iteration "
                  << std::right
                  << std::setw(3)
                  << k
                  << ": "
                  << std::right
                  << std::setw(12)
                  << digits10_iterate
                  << '\n';
      }

      // Test the approximate base-10 digits
      // of this iteration term.

      // If we have attained at least half or more
      // of the total desired digits with this
      // iteration, the calculation is finished
      // because the change from the next iteration will be
      // insignificantly small.
      BOOST_CONSTEXPR_OR_CONST std::uint64_t digits10_iterate_goal =
        static_cast<std::uint64_t>((static_cast<std::uint64_t>(std::numeric_limits<float_type>::digits10) + 1LL) / 2LL) + 16LL;

      if(digits10_iterate > digits10_iterate_goal)
      {
        break;
      }

      t  = val_pi;
      t += bB;
      t /= 4U;
    }

    if(print_progress)
    {
      std::cout << "Iteration loop done, compute inverse" << '\n';
    }

    val_pi += bB;
    val_pi /= s;

    if(print_progress)
    {
      std::cout << "The pi calculation is done." << '\n';
    }
  }

  return val_pi;
}

template<typename float_type>
std::ostream& report_pi_timing(std::ostream& os, const float elapsed)
{
  return os << "=================================================" << '\n'
            << "Computed "
            << static_cast<std::uint64_t>(std::numeric_limits<float_type>::digits10 - 1)
            << " digits of pi.\n"
            << "Total computation time : "
            << std::fixed
            << std::setprecision(2)
            << elapsed
            << " seconds"
            << '\n'
            << "================================================="
            << '\n';
}

} } } // namespace pi::millions::detail

namespace pi { namespace millions {

template<typename float_type>
void print_pi(std::ostream& os)
{
  // Calculate the value of pi. When doing so, print the calculation
  // messages to the console. Use the clock function to obtain the
  // total time of the pi calculation.

  using local_time_point_type =
    std::chrono::high_resolution_clock::time_point;

  const local_time_point_type start = std::chrono::high_resolution_clock::now();
  detail::pi<float_type>(true);
  const local_time_point_type stop  = std::chrono::high_resolution_clock::now();

  // Evaluate the time that was required for the pi calculation.
  const float elapsed =
      static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count())
    / static_cast<float>(1000.0F);

  // Report the time of the pi calculation to the console.
  static_cast<void>(detail::report_pi_timing<float_type>(std::cout, elapsed));

  // Report the time of the pi calculation to the output stream.
  static_cast<void>(detail::report_pi_timing<float_type>(os, elapsed));

  // Report that we are writing the output file.
  std::cout << "Writing the output file." << '\n';

  // Pipe the value of pi into a stringstream object.
  std::stringstream ss;

  // Pipe the value of pi into a stringstream object with full precision.
  ss << std::fixed
     << std::setprecision(std::streamsize(std::numeric_limits<float_type>::digits10) - 1)
     << detail::pi<float_type>();

  // Extract the string value of pi.
  const std::string str_pi(ss.str());

  // Print pi using the following paramater-tunable format.

  // pi = 3.1415926535 8979323846 2643383279 5028841971 6939937510 : 50
  //        5820974944 5923078164 0628620899 8628034825 3421170679 : 100
  //        8214808651 3282306647 0938446095 5058223172 5359408128 : 150
  //        4811174502 8410270193 8521105559 6446229489 5493038196 : 200
  //        ...

  const char pstr_char_set_separator  [] = " ";
  const char pstr_char_group_separator[] = "\n";

  const char* char_set_separator   = pstr_char_set_separator;
  const char* char_group_separator = pstr_char_group_separator;

  BOOST_CONSTEXPR_OR_CONST std::size_t digits_per_set   = 10U;
  BOOST_CONSTEXPR_OR_CONST std::size_t digits_per_line  = digits_per_set * 5U;
  BOOST_CONSTEXPR_OR_CONST std::size_t digits_per_group = digits_per_line * 10U;

  // The digits after the decimal point are grouped
  // in sets of digits_per_set with digits_per_line
  // digits per line. The running-digit count is reported
  // at the end of each line.
  
  // The char_set_separator character string is inserted
  // between sets of digits. Between groups of lines,
  // we insert a char_group_separator character string
  // (which likely might be selected as a newline).

  // For a simple verification of 1,000,000 digits,
  // for example, go to Wolfram Alpha and ask:
  //   1000000th digit of Pi.
  // This prints out 50 digits of pi in the neighborhood
  // of a million digits, with the millionth digit in bold.

  std::string::size_type pos;

  if(   ((pos = str_pi.find(char('3'), 0U)) != std::string::npos)
     && ((pos = str_pi.find(char('.'), 1U)) != std::string::npos)
     && ((pos = str_pi.find(char('1'), 1U)) != std::string::npos))
  {
    ;
  }
  else
  {
    pos = 0U;
  }

  os << "pi = " << str_pi.substr(0U, pos);

  const std::size_t digit_offset = pos;

  // Extract the digits after the decimal point in a loop.
  // Insert spaces, newlines and a running-digit count
  // in order to create a format for comfortable reading.

  bool all_output_streaming_is_finished = false;

  while(all_output_streaming_is_finished == false)
  {
    // Print a set of digits (i.e. having 10 digits per set).
    const std::string str_pi_substring(str_pi.substr(pos, digits_per_set));

    os << str_pi_substring << char_set_separator;

    pos += (std::min)(std::string::size_type(digits_per_set),
                      str_pi_substring.length());

    const std::size_t number_of_digits(pos - digit_offset);

    // Check if all output streaming is finished.
    all_output_streaming_is_finished = (pos >= str_pi.length());

    if(all_output_streaming_is_finished)
    {
      // Write the final digit count.
      // Break from the printing loop.
      // Flush the output stream with std::endl.

      os << ": " << number_of_digits << std::endl;
    }
    else
    {
      const bool this_line_is_finished =
        (std::size_t(number_of_digits % digits_per_line) == std::size_t(0U));

      if(this_line_is_finished)
      {
        // Print the running-digit count and start a new line.
        os << ": " << number_of_digits << std::endl;

        const bool this_group_of_lines_is_finished =
          (std::size_t(number_of_digits % digits_per_group) == std::size_t(0U));

        if(this_group_of_lines_is_finished)
        {
          // Insert a character (which might be a blank line)
          // after a group of lines.
          os << char_group_separator;
        }

        // Insert spaces at the start of the new line.
        os << "       ";
      }
    }
  }
}

} } // namespace pi::millions

int main()
{
  using float_type =
    boost::multiprecision::number<boost::multiprecision::gmp_float<1000001UL>,
                                  boost::multiprecision::et_off>;

  std::ofstream out("pi.out");

  if(out.is_open())
  {
    pi::millions::print_pi<float_type>(out);

    out.close();
  }

  return 0;
}

#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
