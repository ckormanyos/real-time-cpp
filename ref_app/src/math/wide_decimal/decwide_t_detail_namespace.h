///////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2022.                        //
//  Distributed under the Boost Software License,                //
//  Version 1.0. (See accompanying file LICENSE_1_0.txt          //
//  or copy at http://www.boost.org/LICENSE_1_0.txt)             //
///////////////////////////////////////////////////////////////////

#ifndef DECWIDE_T_DETAIL_NAMESPACE_2022_02_15_H // NOLINT(llvm-header-guard)
  #define DECWIDE_T_DETAIL_NAMESPACE_2022_02_15_H

  #if defined(WIDE_DECIMAL_NAMESPACE_BEGIN) || defined(WIDE_DECIMAL_NAMESPACE_END)
    #error internal pre-processor macro already defined
  #endif

  #if defined(WIDE_DECIMAL_NAMESPACE)
    #define WIDE_DECIMAL_NAMESPACE_BEGIN namespace WIDE_DECIMAL_NAMESPACE {   // NOLINT(cppcoreguidelines-macro-usage)
    #define WIDE_DECIMAL_NAMESPACE_END } // namespace WIDE_DECIMAL_NAMESPACE  // NOLINT(cppcoreguidelines-macro-usage)
  #else
    #define WIDE_DECIMAL_NAMESPACE_BEGIN
    #define WIDE_DECIMAL_NAMESPACE_END
  #endif

#endif // DECWIDE_T_DETAIL_NAMESPACE_2022_02_15_H
