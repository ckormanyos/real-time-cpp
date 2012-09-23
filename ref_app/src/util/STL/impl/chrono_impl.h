///////////////////////////////////////////////////////////////////////////////
/// \author (c) Marco Paland (info@paland.com)
///             2011-2012, PALANDesign Hannover, Germany
///
/// \license LGPLv3
/// chrono is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
/// chrono is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser Public License for more details.
/// You should have received a copy of the GNU Lesser Public License
/// along with chrono. If not, see <http://www.gnu.org/licenses/>.
///
///
/// \brief <chrono> implementation of C++11 on Windows(tm)
///
/// This class implements the <chrono> class of C++11 for compilers
/// which do not support this standard.
/// Needs <ratio>, and standard <limits>, <ctime> headers
///
/// To adapt <chrono> to you own system you need to write your own
/// xxx_clock::now() functions and define your clock accuracy in CLOCKS section.
/// This is the only part which is OS dependent!
/// This way you can easily adapt <chrono> to your target system
///
/// \todo - add more specializations of missing common_types for duration arithmetic
///       - some kind of 'enable_if' is missing. So care must be taken to use <chrono> properly!
///
///////////////////////////////////////////////////////////////////////////////

#ifndef _CHRONO_IMPL_2012_06_01_H_
  #define _CHRONO_IMPL_2012_06_01_H_

  #include "limits_impl.h"
  #include "ctime_impl.h"
  #include "cstdint_impl.h"
  #include "ratio_impl.h"

  namespace std
  {
    namespace chrono
    {
      // forward declarations
      template<typename Rep, typename Period>
      struct duration;

      template<class ToDuration, class Rep, class Period>
      inline ToDuration duration_cast(const duration<Rep, Period>& d);

      template<typename Clock, typename Duration = typename Clock::duration>
      struct time_point;

      // duration_values
      template<class _Rep>
      struct duration_values
      {
        static _Rep zero()  { return _Rep(0); }
        static _Rep (max)() { return (std::numeric_limits<_Rep>::max)(); }
        static _Rep (min)() { return (std::numeric_limits<_Rep>::min)(); }
      };

      // TBD: Add more specializations of common_type here
      // common_type is in namespace std::chrono cause its usage is private here
      template<class Tp, class Up>
      struct common_type
      { typedef Tp type; };   // default return is 1. param (Tp) if no specialization is found

      template<typename T>
      struct common_type<T, double>
      { typedef double type; };
      template<typename T>
      struct common_type<double, T>
      { typedef double type; };
      template<>
      struct common_type<double, double>
      { typedef double type; };
      template<>
      struct common_type<double, int64_t>
      { typedef double type; };
      template<>
      struct common_type<int64_t, double>
      { typedef double type; };
      template<typename T>
      struct common_type<T, int64_t>
      { typedef int64_t type; };
      template<typename T>
      struct common_type<int64_t, T>
      { typedef int64_t type; };
      template<>
      struct common_type<int64_t, int64_t>
      { typedef int64_t type; };


      // specialization of common_type (for duration)
      template<typename Rep1, typename Period1, typename Rep2, typename Period2>
      struct common_type<chrono::duration<Rep1, Period1>, chrono::duration<Rep2, Period2> >
      {
      private:
        typedef _static_gcd<Period1::num, Period2::num> _gcd_num;
        typedef _static_gcd<Period1::den, Period2::den> _gcd_den;
        typedef typename common_type<Rep1, Rep2>::type _cr;
        typedef ratio<_gcd_num::value, (Period1::den / _gcd_den::value) * Period2::den> _r;

      public:
        typedef chrono::duration<_cr, _r> type;
      };

      // specialization of common_type (for time_point)
      template<typename Clock, typename Duration1, typename Duration2>
      struct common_type<chrono::time_point<Clock, Duration1>, chrono::time_point<Clock, Duration2> > {
      private:
        typedef typename common_type<Duration1, Duration2>::type _ct;

      public:
        typedef chrono::time_point<Clock, _ct> type;
      };

      template<typename Rep, typename Period>
      struct duration
      {
        typedef Rep    rep;
        typedef Period period;

        duration()
         : rep_() { }

        ~duration() { }

        template <class Rep2>
        explicit duration(const Rep2& r)
         : rep_(static_cast<rep>(r)) { }

        template <class Rep2, class Period2>
        duration(const duration<Rep2, Period2>& d)
         : rep_(duration_cast<duration>(d).count()) { }

        // observer
        const rep count() const
        { return rep_; }

        // arithmetic
        const duration operator+() const
        { return *this; }

        const duration operator-() const
        { return duration(-rep_); }

        duration& operator++()
        { ++rep_; return *this; }

        duration operator++(int)
        { return duration(rep_++); }

        duration& operator--()
        {--rep_; return *this; }

        duration operator--(int)
        { return duration(rep_--); }

        duration& operator+=(const duration& d)
        { rep_ += d.count(); return *this; }

        duration& operator-=(const duration& d)
        { rep_ -= d.count(); return *this; }

        duration& operator*=(const rep& rhs)
        { rep_ *= rhs; return *this; }

        duration& operator/=(const rep& rhs)
        { rep_ /= rhs; return *this; }

        duration& operator%=(const rep& rhs)
        { rep_ %= rhs; return *this; }

        duration& operator%=(const duration& rhs)
        { rep_ %= rhs.count(); return *this; }

        // special values
        static const duration zero()
        { return duration(duration_values<rep>::zero()); }

        static const duration (min)()
        { return duration((duration_values<rep>::min)()); }

        static const duration (max)()
        { return duration((duration_values<rep>::max)()); }

      private:
        rep rep_;
      };


      // non-member arithmetic
      template<class Rep1, class Period1, class Rep2, class Period2>
      inline const typename common_type<duration<Rep1, Period1>, duration<Rep2, Period2> >::type
      operator+(const duration<Rep1, Period1>& lhs,
                const duration<Rep2, Period2>& rhs)
      {
        typedef duration<Rep1, Period1> _dur1;
        typedef duration<Rep2, Period2> _dur2;
        typedef typename common_type<_dur1,_dur2>::type _ct;
        return _ct(lhs) += rhs;
      }

      template<class Rep1, class Period1, class Rep2, class Period2>
      inline const typename common_type<duration<Rep1, Period1>, duration<Rep2, Period2> >::type
      operator-(const duration<Rep1, Period1>& lhs,
                const duration<Rep2, Period2>& rhs)
      {
        typedef duration<Rep1, Period1> _dur1;
        typedef duration<Rep2, Period2> _dur2;
        typedef typename common_type<_dur1,_dur2>::type _ct;
        return _ct(lhs) -= rhs;
      }

      template<typename Rep1, typename Period, typename Rep2>
      inline const duration<typename common_type<Rep1, Rep2>::type, Period>
      operator*(const duration<Rep1, Period>& d,
                const Rep2& s)
      {
        typedef typename common_type<Rep1, Rep2>::type _cr;
        return duration<_cr, Period>(d) *= s;
      }

      template<typename Rep1, typename Rep2, typename Period>
      inline const duration<typename common_type<Rep1, Rep2>::type, Period>
      operator*(const Rep1& s,
                const duration<Rep2, Period>& d)
      {
        return d * s;
      }

      template<typename Rep1, typename Period, typename Rep2>
      inline const duration<typename common_type<Rep1, Rep2>::type, Period>
      operator/(const duration<Rep1, Period>& d, const Rep2& s)
      {
        typedef typename common_type<Rep1, Rep2>::type _cr;
        return duration<_cr, Period>(d) /= s;
      }

      template<typename Rep1, typename Period1, typename Rep2, typename Period2>
      inline const typename common_type<Rep1, Rep2>::type
      operator/(const duration<Rep1, Period1>& lhs,
                const duration<Rep2, Period2>& rhs)
      {
        typedef duration<Rep1, Period1> _dur1;
        typedef duration<Rep2, Period2> _dur2;
        typedef typename common_type<_dur1, _dur2>::type _ct;
        return _ct(lhs).count() / _ct(rhs).count();
      }

      template<typename Rep1, typename Period, typename Rep2>
      inline const duration<typename common_type<Rep1, Rep2>::type, Period>
      operator%(const duration<Rep1, Period>& d,
                const Rep2& s)
      {
        typedef typename common_type<Rep1, Rep2>::type _cr;
        return duration<_cr, Period>(d) %= s;
      }

      template<typename Rep1, typename Period1, typename Rep2, typename Period2>
      inline const typename common_type<duration<Rep1, Period1>, duration<Rep2, Period2> >::type
      operator%(const duration<Rep1, Period1>& lhs,
                const duration<Rep2, Period2>& rhs)
      {
        typedef duration<Rep1, Period1> _dur1;
        typedef duration<Rep2, Period2> _dur2;
        typedef typename common_type<_dur1, _dur2>::type _ct;
        return _ct(lhs) %= rhs;
      }


      // comparisons
      template<typename Rep1, typename Period1, typename Rep2, typename Period2>
      inline bool operator==(const duration<Rep1, Period1>& lhs,
                             const duration<Rep2, Period2>& rhs)
      {
        typedef duration<Rep1, Period1> _dur1;
        typedef duration<Rep2, Period2> _dur2;
        typedef typename common_type<_dur1, _dur2>::type _ct;
        return _ct(lhs).count() == _ct(rhs).count();
      }

      template<typename Rep1, typename Period1, typename Rep2, typename Period2>
      inline bool operator!=(const duration<Rep1, Period1>& lhs,
                             const duration<Rep2, Period2>& rhs)
      {
        return !(lhs == rhs);
      }

      template<typename Rep1, typename Period1, typename Rep2, typename Period2>
      inline bool operator<(const duration<Rep1, Period1>& lhs,
                            const duration<Rep2, Period2>& rhs)
      {
        typedef duration<Rep1, Period1> _dur1;
        typedef duration<Rep2, Period2> _dur2;
        typedef typename common_type<_dur1, _dur2>::type _ct;
        return _ct(lhs).count() < _ct(rhs).count();
      }

      template<typename Rep1, typename Period1, typename Rep2, typename Period2>
      inline bool operator<=(const duration<Rep1, Period1>& lhs,
                             const duration<Rep2, Period2>& rhs)
      {
        return !(rhs < lhs);
      }

      template<typename Rep1, typename Period1, typename Rep2, typename Period2>
      inline bool operator>(const duration<Rep1, Period1>& lhs,
                            const duration<Rep2, Period2>& rhs)
      {
        return rhs < lhs;
      }

      template<typename Rep1, typename Period1, typename Rep2, typename Period2>
      inline bool operator>=(const duration<Rep1, Period1>& lhs,
                             const duration<Rep2, Period2>& rhs)
      {
        return !(lhs < rhs);
      }

      // duration_cast implementation
      template<class ToDuration, class CF, class CR, bool _NumIsOne = false, bool _DenIsOne = false>
      struct _duration_cast_impl {
        template<typename Rep, typename Period>
        static const ToDuration _cast(const duration<Rep, Period>& d)
        {
          return ToDuration(static_cast<typename ToDuration::rep>(static_cast<CR>(d.count()) *
                                                                  static_cast<CR>(CF::num) /
                                                                  static_cast<CR>(CF::den)));
        }
      };

      // duration_cast
      template<class ToDuration, class Rep, class Period>
      inline ToDuration duration_cast(const duration<Rep, Period>& d)
      {
        typedef typename ToDuration::period _to_period;
        typedef typename ToDuration::rep _to_rep;
        typedef ratio_divide<Period, _to_period> _r_div;
        typedef typename _r_div::type _cf;
        typedef typename common_type<_to_rep, Rep>::type _cr;
        typedef _duration_cast_impl<ToDuration, _cf, _cr, _cf::num == 1, _cf::den == 1> _dc;
        return _dc::_cast(d);
      }

      template<class ToDuration, class CF, class CR>
      struct _duration_cast_impl<ToDuration, CF, CR, true, true> {
        template<typename Rep, typename Period>
        static const ToDuration _cast(const duration<Rep, Period>& d)
        {
          return ToDuration(static_cast<typename ToDuration::rep>(d.count()));
        }
      };

      template<class ToDuration, class CF, class CR>
      struct _duration_cast_impl<ToDuration, CF, CR, true, false> {
        template<typename Rep, typename Period>
        static const ToDuration _cast(const duration<Rep, Period>& d)
        {
          return ToDuration(static_cast<typename ToDuration::rep>(static_cast<CR>(d.count()) / static_cast<CR>(CF::den)));
        }
      };

      template<class ToDuration, class CF, class CR>
      struct _duration_cast_impl<ToDuration, CF, CR, false, true> {
        template<typename Rep, typename Period>
        static const ToDuration _cast(const duration<Rep, Period>& d)
        {
          return ToDuration(static_cast<typename ToDuration::rep>(static_cast<CR>(d.count()) * static_cast<CR>(CF::num)));
        }
      };


      // see 20.11.5.7 for type definitions
      // nanoseconds
      typedef duration<int64_t, nano>         nanoseconds;

      // microseconds
      typedef duration<int64_t, micro>        microseconds;

      // milliseconds
      typedef duration<int64_t, milli>        milliseconds;

      // seconds
      typedef duration<int64_t, ratio<1> >    seconds;

      // minutes
      typedef duration<int32_t, ratio<60> >   minutes;

      // hours
      typedef duration<int32_t, ratio<3600> > hours;


      //////////////////////////////////////////////////////////////////////////
      // T I M E   P O I N T
      //

      template<typename Clock, typename Duration>
      struct time_point {
        typedef Clock                     clock;
        typedef Duration                  duration;
        typedef typename duration::rep    rep;
        typedef typename duration::period period;

        time_point()
         : d_(duration::zero())
        { }

        explicit time_point(const duration& d)
         : d_(d)
        { }

        // conversions
        template<class Duration2>
        time_point(const time_point<clock, Duration2>& t)
         : d_(t.time_since_epoch())
        { }

        // observer
        duration time_since_epoch() const
        { return d_; }

        // arithmetic
        time_point& operator+=(const duration& d)
        { d_ += d; return *this; }

        time_point& operator-=(const duration& d)
        { d_ -= d; return *this; }

        // special values
        static const time_point (min)()
        { return time_point((duration::min)()); }

        static const time_point (max)()
        { return time_point((duration::max)()); }

      private:
        duration d_;
      };

      // time_point_cast
      template<typename ToDuration, typename Clock, typename Duration>
      time_point<Clock, ToDuration> time_point_cast(const time_point<Clock, Duration>& t)
      {
        typedef time_point<Clock, ToDuration> _time_point;
        return _time_point(duration_cast<ToDuration>(t.time_since_epoch()));
      }

      // time_point arithmetic
      template<class Clock, class Dur1, class Rep2, class Period2>
      inline time_point<Clock, typename common_type<Dur1, duration<Rep2, Period2> >::type>
      operator+(const time_point<Clock, Dur1>& lhs,
                const duration<Rep2, Period2>& rhs)
      {
        typedef duration<Rep2, Period2> _dur2;
        typedef typename common_type<Dur1, _dur2>::type _ct;
        typedef time_point<Clock, _ct> _time_point;
        return _time_point(lhs) += rhs;
      }

      template<class Rep1, class Period1, class Clock, class Dur2>
      inline time_point<Clock, typename common_type<duration<Rep1, Period1>, Dur2>::type>
      operator+(const duration<Rep1, Period1>& lhs,
                const time_point<Clock, Dur2>& rhs)
      {
        return rhs + lhs;
      }

      template<class Clock, class Dur1, class Rep2, class Period2>
      inline time_point<Clock, typename common_type<Dur1, duration<Rep2, Period2> >::type>
      operator-(const time_point<Clock, Dur1>& lhs,
                const duration<Rep2, Period2>& rhs)
      {
        return lhs + (-rhs);
      }

      template<class Clock, class Dur1, class Dur2>
      inline typename common_type<Dur1, Dur2>::type
      operator-(const time_point<Clock, Dur1>& lhs,
                const time_point<Clock, Dur2>& rhs)
      {
        return lhs.time_since_epoch() - rhs.time_since_epoch();
      }

      // time_point comparisons
      template<class Clock, class Dur1, class Dur2>
      inline bool operator==(const time_point<Clock, Dur1>& lhs,
                             const time_point<Clock, Dur2>& rhs)
      {
        return lhs.time_since_epoch() == rhs.time_since_epoch();
      }

      template<class Clock, class Dur1, class Dur2>
      inline bool operator!=(const time_point<Clock, Dur1>& lhs,
                             const time_point<Clock, Dur2>& rhs)
      {
        return !(lhs == rhs);
      }

      template<class Clock, class Dur1, class Dur2>
      inline bool operator<(const time_point<Clock, Dur1>& lhs,
                            const time_point<Clock, Dur2>& rhs)
      {
        return  lhs.time_since_epoch() < rhs.time_since_epoch();
      }

      template<class Clock, class Dur1, class Dur2>
      inline bool operator<=(const time_point<Clock, Dur1>& lhs,
                             const time_point<Clock, Dur2>& rhs)
      {
        return !(rhs < lhs);
      }

      template<class Clock, class Dur1, class Dur2>
      inline bool operator>(const time_point<Clock, Dur1>& lhs,
                            const time_point<Clock, Dur2>& rhs)
      {
        return rhs < lhs;
      }

      template<class Clock, class Dur1, class Dur2>
      inline bool operator>=(const time_point<Clock, Dur1>& lhs,
                             const time_point<Clock, Dur2>& rhs)
      {
        return !(lhs < rhs);
      }



      //////////////////////////////////////////////////////////////////////////
      // C L O C K S
      //

      class system_clock
      {
      public:
        // defines the accuracy of the (OS) system clock
        typedef chrono::milliseconds                       duration;

        typedef duration::rep                              rep;
        typedef duration::period                           period;
        typedef chrono::time_point<system_clock, duration> time_point;

        static std::time_t to_time_t(const time_point& t)
        {
          return std::time_t(duration_cast<chrono::seconds>(t.time_since_epoch()).count());
        }

        static time_point from_time_t(std::time_t t)
        {
          typedef chrono::time_point<system_clock, seconds> _from;
          return time_point_cast<system_clock::duration>(_from(chrono::seconds(t)));
        }

        // the system clock is not steady, a subsequent call to std::chrono::system_clock::now()
        // may return an earlier time than a previous call, e.g. if the operating system clock is
        // manually adjusted or synchronized with an external clock
        static const bool is_steady = false;

        // !!! PLATFORM AND OS SPECIFIC IMPLEMENTATION !!!
        static time_point now();
      };


      class high_resolution_clock
      {
      public:
        // defines the accuracy of the (hardware) high resolution clock
        typedef chrono::microseconds duration;

        typedef duration::rep rep;
        typedef duration::period period;
        typedef chrono::time_point<high_resolution_clock, duration> time_point;

        static std::time_t to_time_t(const time_point& t)
        {
          return std::time_t(duration_cast<chrono::seconds>(t.time_since_epoch()).count());
        }

        static time_point from_time_t(std::time_t t)
        {
          typedef chrono::time_point<high_resolution_clock, seconds> _from;
          return time_point_cast<high_resolution_clock::duration>(_from(chrono::seconds(t)));
        }

        // performance counter is steady, a subsequent call to std::chrono::high_resolution_clock::now()
        // returns always a later timer than a previous call
        static const bool is_steady = true;

        // !!! PLATFORM AND OS SPECIFIC IMPLEMENTATION !!!
        static time_point now();
      };


      // use high_resolution_clock as steady_clock
      typedef high_resolution_clock steady_clock;
    } // namespace chrono
  } // namespace std

#endif // _CHRONO_IMPL_2012_06_01_H_
