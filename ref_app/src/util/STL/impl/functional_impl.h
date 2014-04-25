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
    template<typename argument1, typename argument2, typename result>
    struct binary_function
    {
      typedef argument1 first_argument_type;
      typedef argument2 second_argument_type;
      typedef result    result_type;
    };

    template<typename operand_type>
    struct plus : public binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left + right;
      }
    };

    template<typename operand_type>
    struct minus : public binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left - right;
      }
    };

    template<typename operand_type>
    struct multiplies : public binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left * right;
      }
    };

    template<typename operand_type>
    struct divides : public binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left / right;
      }
    };

    template<typename operand_type>
    struct modulus : public binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left % right;
      }
    };
  }

#endif // _FUNCTIONAL_IMPL_2013_08_30_H_

