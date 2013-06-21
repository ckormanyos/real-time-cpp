///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _BFX_2013_06_21_H_
  #define _BFX_2013_06_21_H_

  template<typename data_type>
  void Bfx_SetBitMask(data_type* const Data, const data_type Mask)
  {
    *Data = *Data | Mask;
  }

  template<typename data_type>
  void Bfx_ClrBitMask(data_type* const Data, const data_type Mask)
  {
    *Data = *Data & ~Mask;
  }

  template<typename data_type>
  void Bfx_PutBitsMask(data_type* const Data, const data_type Pattern, const data_type Mask)
  {
    *Data = (*Data & ~Mask) | (Pattern & Mask);
  }

#endif // _BFX_2013_06_21_H_
