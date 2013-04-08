///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _TUPLE_IMPL_2010_02_23_H_
  #define _TUPLE_IMPL_2010_02_23_H_

  #if defined(__GNUC__)
  #pragma GCC system_header
  #endif

  #include "cstddef_impl.h"
  #include "pair_impl.h"
  #include "xutils_impl.h"

  // Implement some of std::tuple for compilers that do not yet support it.
  // This implementation of tuple supports up to 11 template parameters.
  // Do not use variadic templates because they might not be supported either.

  namespace xtuple
  {
    template<const int N,
             typename tuple_type>
    class xtuple_get_helper;

    template<typename tuple_type>
    class xtuple_size_helper;
  }

  namespace std
  {
    template<typename T0  = xutils::xnothing,
             typename T1  = xutils::xnothing,
             typename T2  = xutils::xnothing,
             typename T3  = xutils::xnothing,
             typename T4  = xutils::xnothing,
             typename T5  = xutils::xnothing,
             typename T6  = xutils::xnothing,
             typename T7  = xutils::xnothing,
             typename T8  = xutils::xnothing,
             typename T9  = xutils::xnothing,
             typename T10 = xutils::xnothing>
    class tuple
    {
    public:
      template<const int N, typename tuple_type> friend class xtuple::xtuple_get_helper;
      template<typename tuple_type> friend class xtuple::xtuple_size_helper;

      typedef tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> tuple_type;

      tuple() { }

      explicit tuple(const T0&  p0,
                     const T1&  p1  = T1 (),
                     const T2&  p2  = T2 (),
                     const T3&  p3  = T3 (),
                     const T4&  p4  = T4 (),
                     const T5&  p5  = T5 (),
                     const T6&  p6  = T6 (),
                     const T7&  p7  = T7 (),
                     const T8&  p8  = T8 (),
                     const T9&  p9  = T9 (),
                     const T10& p10 = T10()) : t0 (p0),
                                               t1 (p1),
                                               t2 (p2),
                                               t3 (p3),
                                               t4 (p4),
                                               t5 (p5),
                                               t6 (p6),
                                               t7 (p7),
                                               t8 (p8),
                                               t9 (p9),
                                               t10(p10) { }

      tuple(const tuple_type& t) : t0(t.t0),
                                   t1(t.t1),
                                   t2(t.t2),
                                   t3(t.t3),
                                   t4(t.t4),
                                   t5(t.t5),
                                   t6(t.t6),
                                   t7(t.t7),
                                   t8(t.t8),
                                   t9(t.t9),
                                   t10(t.t10) { }

      template<typename U0, typename U1>
      tuple(const std::pair<U0, U1>& p) : t0 (p.first),
                                          t1 (p.second),
                                          t2 (T2 ()),
                                          t3 (T3 ()),
                                          t4 (T4 ()),
                                          t5 (T5 ()),
                                          t6 (T6 ()),
                                          t7 (T7 ()),
                                          t8 (T8 ()),
                                          t9 (T9 ()),
                                          t10(T10()) { }

      template<typename U0,
               typename U1,
               typename U2,
               typename U3,
               typename U4,
               typename U5,
               typename U6,
               typename U7,
               typename U8,
               typename U9,
               typename U10>
      tuple& operator=(const tuple<U0, U1, U2, U3, U4, U5, U6, U7, U8, U9, U10>& t)
      {
        t0  = T0 (t.t0);
        t1  = T1 (t.t1);
        t2  = T2 (t.t2);
        t3  = T3 (t.t3);
        t4  = T4 (t.t4);
        t5  = T5 (t.t5);
        t6  = T6 (t.t6);
        t7  = T7 (t.t7);
        t8  = T8 (t.t8);
        t9  = T9 (t.t9);
        t10 = T10(t.t10);
        return *this;
      }

      template<typename U0, typename U1>
      tuple& operator=(const std::pair<U0, U1>& p)
      {
        t0  = T0(p.first);
        t1  = T1(p.second);
        t2  = T2();
        t3  = T3();
        t4  = T4();
        t5  = T5();
        t6  = T6();
        t7  = T7();
        t8  = T8();
        t9  = T9();
        t10 = T10();
        return *this;
      }

    private:
      T0 t0; T1 t1; T2 t2; T3 t3; T4 t4; T5 t5; T6 t6; T7 t7; T8 t8; T9 t9; T10 t10;

      typedef T0  type0;
      typedef T1  type1;
      typedef T2  type2;
      typedef T3  type3;
      typedef T4  type4;
      typedef T5  type5;
      typedef T6  type6;
      typedef T7  type7;
      typedef T8  type8;
      typedef T9  type9;
      typedef T10 type10;
    };
  }

  namespace xtuple
  {
    template<const int N, typename tuple_type>
    class xtuple_get_helper { };

    #define MAKE_XTUPLE_GET_HELPER(NUM)                                            \
    template<typename tuple_type> class xtuple_get_helper<NUM, tuple_type>         \
    {                                                                              \
    public:                                                                        \
      typedef typename tuple_type::type##NUM elem_type;                            \
      static       elem_type& get      (      tuple_type& t) { return t.t##NUM ; } \
      static const elem_type& get_const(const tuple_type& t) { return t.t##NUM ; } \
    }

    MAKE_XTUPLE_GET_HELPER(0);
    MAKE_XTUPLE_GET_HELPER(1);
    MAKE_XTUPLE_GET_HELPER(2);
    MAKE_XTUPLE_GET_HELPER(3);
    MAKE_XTUPLE_GET_HELPER(4);
    MAKE_XTUPLE_GET_HELPER(5);
    MAKE_XTUPLE_GET_HELPER(6);
    MAKE_XTUPLE_GET_HELPER(7);
    MAKE_XTUPLE_GET_HELPER(8);
    MAKE_XTUPLE_GET_HELPER(9);
    MAKE_XTUPLE_GET_HELPER(10);

    template<typename T> class xtuple_elem_size_helper                   { public: static const unsigned int value = 1U; };
    template<>           class xtuple_elem_size_helper<xutils::xnothing> { public: static const unsigned int value = 0U; };

    template<typename tuple_type>
    class xtuple_size_helper
    {
    public:
      static const unsigned int value =
          xtuple_elem_size_helper<typename tuple_type::type0>::value
        + xtuple_elem_size_helper<typename tuple_type::type1>::value
        + xtuple_elem_size_helper<typename tuple_type::type2>::value
        + xtuple_elem_size_helper<typename tuple_type::type3>::value
        + xtuple_elem_size_helper<typename tuple_type::type4>::value
        + xtuple_elem_size_helper<typename tuple_type::type5>::value
        + xtuple_elem_size_helper<typename tuple_type::type6>::value
        + xtuple_elem_size_helper<typename tuple_type::type7>::value
        + xtuple_elem_size_helper<typename tuple_type::type8>::value
        + xtuple_elem_size_helper<typename tuple_type::type9>::value
        + xtuple_elem_size_helper<typename tuple_type::type10>::value;
    };
  }

  namespace std
  {
    template<const int N>
    typename xtuple::xtuple_get_helper<N, tuple<> >::elem_type& get(tuple<>& t) { return xtuple::xtuple_get_helper<N, tuple<> >::get(t); }
    template<const int N, typename T0>
    typename xtuple::xtuple_get_helper<N, tuple<T0> >::elem_type& get(tuple<T0>& t) { return xtuple::xtuple_get_helper<N, tuple<T0> >::get(t); }
    template<const int N, typename T0, typename T1>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1> >::elem_type& get(tuple<T0, T1>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1> >::get(t); }
    template<const int N, typename T0, typename T1, typename T2>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2> >::elem_type& get(tuple<T0, T1, T2>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2> >::get(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3> >::elem_type& get(tuple<T0, T1, T2, T3>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3> >::get(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4> >::elem_type& get(tuple<T0, T1, T2, T3, T4>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4> >::get(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5> >::elem_type& get(tuple<T0, T1, T2, T3, T4, T5>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5> >::get(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6> >::elem_type& get(tuple<T0, T1, T2, T3, T4, T5, T6>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6> >::get(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7> >::elem_type& get(tuple<T0, T1, T2, T3, T4, T5, T6, T7>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7> >::get(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> >::elem_type& get(tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> >::get(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >::elem_type& get(tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >::get(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >::elem_type& get(tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >::get(t); }

    template<const int N>
    const typename xtuple::xtuple_get_helper<N, tuple<> >::elem_type& get(const tuple<>& t) { return xtuple::xtuple_get_helper<N, tuple<> >::get_const(t); }
    template<const int N, typename T0>
    const typename xtuple::xtuple_get_helper<N, tuple<T0> >::elem_type& get(const tuple<T0>& t) { return xtuple::xtuple_get_helper<N, tuple<T0> >::get_const(t); }
    template<const int N, typename T0, typename T1>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1> >::elem_type& get(const tuple<T0, T1>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1> >::get_const(t); }
    template<const int N, typename T0, typename T1, typename T2>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2> >::elem_type& get(const tuple<T0, T1, T2>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2> >::get_const(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3> >::elem_type& get(const tuple<T0, T1, T2, T3>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3> >::get_const(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4> >::elem_type& get(const tuple<T0, T1, T2, T3, T4>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4> >::get_const(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5> >::elem_type& get(const tuple<T0, T1, T2, T3, T4, T5>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5> >::get_const(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6> >::elem_type& get(const tuple<T0, T1, T2, T3, T4, T5, T6>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6> >::get_const(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7> >::elem_type& get(const tuple<T0, T1, T2, T3, T4, T5, T6, T7>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7> >::get_const(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> >::elem_type& get(const tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8> >::get_const(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >::elem_type& get(const tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9> >::get_const(t); }
    template<const int N, typename T0, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10>
    const typename xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >::elem_type& get(const tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>& t) { return xtuple::xtuple_get_helper<N, tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> >::get_const(t); }

    template<const int N, typename tuple_type>
    class tuple_element
    {
    public:
      typedef typename xtuple::xtuple_get_helper<N, tuple_type>::elem_type type;
    };

    template<typename tuple_type>
    class tuple_size
    {
    public:
      static const unsigned int value = xtuple::xtuple_size_helper<tuple_type>::value;
    };

    template<typename T0,
             typename T1,
             typename T2,
             typename T3,
             typename T4,
             typename T5,
             typename T6,
             typename T7,
             typename T8,
             typename T9,
             typename T10>
    tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10> make_tuple(const T0&  p0  = T0 (),
                                                                  const T1&  p1  = T1 (),
                                                                  const T2&  p2  = T2 (),
                                                                  const T3&  p3  = T3 (),
                                                                  const T4&  p4  = T4 (),
                                                                  const T5&  p5  = T5 (),
                                                                  const T6&  p6  = T6 (),
                                                                  const T7&  p7  = T7 (),
                                                                  const T8&  p8  = T8 (),
                                                                  const T9&  p9  = T9 (),
                                                                  const T10& p10 = T10())
    {
      return tuple<T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10>(p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
    }
  }

#endif // _TUPLE_IMPL_2010_02_23_H_
