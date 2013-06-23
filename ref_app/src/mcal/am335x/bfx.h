///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _BFX_2013_06_21_H_
  #define _BFX_2013_06_21_H_

  template<typename data_type>
  inline void bfx_set_bit_mask(data_type* data, const data_type mask)
  {
    *data = data_type(*data | mask);
  }

  template<typename data_type>
  inline void bfx_clear_bit_mask(data_type* data, const data_type mask)
  {
    *data = data_type(*data & data_type(~mask));
  }

  template<typename data_type>
  inline void bfx_clear_and_set_bit_mask(data_type* data, const data_type pattern, const data_type mask)
  {
    *data = data_type(data_type(*data & data_type(~mask)) | data_type(pattern & mask));
  }

#endif // _BFX_2013_06_21_H_
