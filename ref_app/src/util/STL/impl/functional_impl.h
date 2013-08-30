///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _FUNCTIONAL_IMPL_2013_08_30_H_
  #define _FUNCTIONAL_IMPL_2013_08_30_H_

  namespace std
  {
    template<typename operand_type>
    struct plus
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return operand_type(left + right);
      }
    };

    template<typename operand_type>
    struct minus
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return operand_type(left - right);
      }
    };

    template<typename operand_type>
    struct multiplies
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return operand_type(left * right);
      }
    };

    template<typename operand_type>
    struct divides
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return operand_type(left / right);
      }
    };

    template<typename operand_type>
    struct modulus
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return operand_type(left % right);
      }
    };
  }

#endif // _FUNCTIONAL_IMPL_2013_08_30_H_

