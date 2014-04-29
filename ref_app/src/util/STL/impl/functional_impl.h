///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2013 - 2014.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _FUNCTIONAL_IMPL_2013_08_30_H_
  #define _FUNCTIONAL_IMPL_2013_08_30_H_

  namespace std
  {
    template<typename argument1,
             typename result>
    struct unary_function
    {
      typedef argument1 first_argument_type;
      typedef result    result_type;
    };

    template<typename argument1,
             typename argument2,
             typename result>
    struct binary_function
    {
      typedef argument1 first_argument_type;
      typedef argument2 second_argument_type;
      typedef result    result_type;
    };

    template<typename operand_type>
    struct plus : public std::binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left + right;
      }
    };

    template<typename operand_type>
    struct minus : public std::binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left - right;
      }
    };

    template<typename operand_type>
    struct multiplies : public std::binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left * right;
      }
    };

    template<typename operand_type>
    struct divides : public std::binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left / right;
      }
    };

    template<typename operand_type>
    struct modulus : public std::binary_function<operand_type, operand_type, operand_type>
    {
      operand_type operator()(const operand_type& left, const operand_type& right) const
      {
        return left % right;
      }
    };

    template<typename function_type>
    class unary_binder : public std::unary_function<typename function_type::second_argument_type,
                                                    typename function_type::result_type>
    {
    public:
      typedef std::unary_function<typename function_type::second_argument_type,
                                  typename function_type::result_type>
      base_type;

      typedef typename base_type::first_argument_type argument_type;
      typedef typename base_type::result_type         result_type;

      unary_binder(const function_type& function,
                   const typename function_type::first_argument_type& left) : operation(function),
                                                                              value    (left) { }

      result_type operator()(const argument_type& right) const
      {
        return (operation(value, right));
      }

      result_type operator()(argument_type& right) const
      {
        return (operation(value, right));
      }

    protected:
      function_type operation;

      typename function_type::first_argument_type value;
    };

    template<typename function_type,
             typename value_type>
    unary_binder<function_type> bind1st(const function_type& function, const value_type& left)
    {
      typename function_type::first_argument_type the_value(left);

      return std::unary_binder<function_type>(function, the_value);
    }
  }

#endif // _FUNCTIONAL_IMPL_2013_08_30_H_
