///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2023.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef UTIL_NONCOPYABLE_2008_12_16_H // NOLINT(llvm-header-guard)
  #define UTIL_NONCOPYABLE_2008_12_16_H

  // Taken (with slight modification) from boost::noncopyable.

  namespace util {
  namespace my_noncopyable_namespace {

  class noncopyable
  {
  protected:
    noncopyable() = default;  // LCOV_EXCL_LINE
    ~noncopyable() = default; // LCOV_EXCL_LINE

  private:
    // Emphasize: The following members are private.
    noncopyable(const noncopyable&) = delete; // NOLINT(hicpp-use-equals-delete,modernize-use-equals-delete)
    noncopyable(noncopyable&&)      = delete; // NOLINT(hicpp-use-equals-delete,modernize-use-equals-delete)

    auto operator=(const noncopyable&) -> noncopyable& = delete; // NOLINT(hicpp-use-equals-delete,modernize-use-equals-delete)
    auto operator=(noncopyable&&)      -> noncopyable& = delete; // NOLINT(hicpp-use-equals-delete,modernize-use-equals-delete)
  };

  } // namespace my_noncopyable_namespace

  using noncopyable = my_noncopyable_namespace::noncopyable;

  } // namespace util

#endif // UTIL_NONCOPYABLE_2008_12_16_H
