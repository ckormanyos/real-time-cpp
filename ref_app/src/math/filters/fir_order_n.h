///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2025.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef FIR_ORDER_N_UNSIGNED_2012_03_27_H_
  #define FIR_ORDER_N_UNSIGNED_2012_03_27_H_

  #include <cstdint>
  #include <array>
  #include <algorithm>

  // TBD: Handle conversion warnings with search and replace or new code generation.

  namespace math { namespace filters {

  template<const std::size_t order,
           const std::size_t resol = 4U,
           typename sample_t = std::int16_t,
           typename value_t  = sample_t,
           typename result_t = sample_t>
  class fir_order_n
  {
  public:
    fir_order_n() { }

    explicit fir_order_n(const sample_t&) { }

    void new_sample(const sample_t&) { }

    result_t get_result() const { return result_t(0); }
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<1U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1);

      const std::int_fast16_t total_weight = B0 + B1;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 2U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<2U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2);

      const std::int_fast16_t total_weight = B0 + B1 + B2;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 3U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<3U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 4U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<4U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 5U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<5U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 6U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<6U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 7U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<7U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 8U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<8U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 9U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<9U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 10U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<10U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 11U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<11U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 12U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<12U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 13U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<13U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 14U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<14U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 15U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<15U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 16U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<16U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 17U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<17U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = (value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 18U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<18U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 19U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<19U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 20U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<20U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 21U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<21U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 22U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<22U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 23U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<23U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 24U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<24U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 25U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<25U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 26U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<26U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 27U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<27U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 28U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<28U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 29U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<29U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 30U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<30U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 31U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<31U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 32U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<32U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 33U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<33U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 34U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<34U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 35U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<35U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 36U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<36U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 37U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<37U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 38U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<38U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 39U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<39U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 40U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<40U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39, const std::int_fast16_t B40>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39) + value_type(data[40U] * B40);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39 + B40;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 41U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<41U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39, const std::int_fast16_t B40, const std::int_fast16_t B41>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39) + value_type(data[40U] * B40) + value_type(data[41U] * B41);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39 + B40 + B41;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 42U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<42U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39, const std::int_fast16_t B40, const std::int_fast16_t B41, const std::int_fast16_t B42>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39) + value_type(data[40U] * B40) + value_type(data[41U] * B41) + value_type(data[42U] * B42);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39 + B40 + B41 + B42;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 43U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<43U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39, const std::int_fast16_t B40, const std::int_fast16_t B41, const std::int_fast16_t B42, const std::int_fast16_t B43>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39) + value_type(data[40U] * B40) + value_type(data[41U] * B41) + value_type(data[42U] * B42) + value_type(data[43U] * B43);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39 + B40 + B41 + B42 + B43;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 44U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<44U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39, const std::int_fast16_t B40, const std::int_fast16_t B41, const std::int_fast16_t B42, const std::int_fast16_t B43, const std::int_fast16_t B44>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39) + value_type(data[40U] * B40) + value_type(data[41U] * B41) + value_type(data[42U] * B42) + value_type(data[43U] * B43) + value_type(data[44U] * B44);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39 + B40 + B41 + B42 + B43 + B44;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 45U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<45U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39, const std::int_fast16_t B40, const std::int_fast16_t B41, const std::int_fast16_t B42, const std::int_fast16_t B43, const std::int_fast16_t B44, const std::int_fast16_t B45>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39) + value_type(data[40U] * B40) + value_type(data[41U] * B41) + value_type(data[42U] * B42) + value_type(data[43U] * B43) + value_type(data[44U] * B44) + value_type(data[45U] * B45);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39 + B40 + B41 + B42 + B43 + B44 + B45;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 46U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<46U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39, const std::int_fast16_t B40, const std::int_fast16_t B41, const std::int_fast16_t B42, const std::int_fast16_t B43, const std::int_fast16_t B44, const std::int_fast16_t B45, const std::int_fast16_t B46>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39) + value_type(data[40U] * B40) + value_type(data[41U] * B41) + value_type(data[42U] * B42) + value_type(data[43U] * B43) + value_type(data[44U] * B44) + value_type(data[45U] * B45) + value_type(data[46U] * B46);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39 + B40 + B41 + B42 + B43 + B44 + B45 + B46;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 47U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<47U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39, const std::int_fast16_t B40, const std::int_fast16_t B41, const std::int_fast16_t B42, const std::int_fast16_t B43, const std::int_fast16_t B44, const std::int_fast16_t B45, const std::int_fast16_t B46, const std::int_fast16_t B47>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39) + value_type(data[40U] * B40) + value_type(data[41U] * B41) + value_type(data[42U] * B42) + value_type(data[43U] * B43) + value_type(data[44U] * B44) + value_type(data[45U] * B45) + value_type(data[46U] * B46) + value_type(data[47U] * B47);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39 + B40 + B41 + B42 + B43 + B44 + B45 + B46 + B47;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 48U> data;
  };

  template<const std::size_t resol,
           typename sample_t,
           typename value_t,
           typename result_t>
  class fir_order_n<48U,
                    resol,
                    sample_t,
                    value_t,
                    result_t>
  {
  public:
    typedef sample_t sample_type;
    typedef value_t  value_type;
    typedef result_t result_type;

    fir_order_n() : result(0)
    {
      std::fill(data.begin(), data.end(), result);
    }

    explicit fir_order_n(const sample_type& x)
      : result(value_type(x) * resol)
    {
      std::fill(data.begin(), data.end(), result);
    }

    template<const std::int_fast16_t B0, const std::int_fast16_t B1, const std::int_fast16_t B2, const std::int_fast16_t B3, const std::int_fast16_t B4, const std::int_fast16_t B5, const std::int_fast16_t B6, const std::int_fast16_t B7, const std::int_fast16_t B8, const std::int_fast16_t B9, const std::int_fast16_t B10, const std::int_fast16_t B11, const std::int_fast16_t B12, const std::int_fast16_t B13, const std::int_fast16_t B14, const std::int_fast16_t B15, const std::int_fast16_t B16, const std::int_fast16_t B17, const std::int_fast16_t B18, const std::int_fast16_t B19, const std::int_fast16_t B20, const std::int_fast16_t B21, const std::int_fast16_t B22, const std::int_fast16_t B23, const std::int_fast16_t B24, const std::int_fast16_t B25, const std::int_fast16_t B26, const std::int_fast16_t B27, const std::int_fast16_t B28, const std::int_fast16_t B29, const std::int_fast16_t B30, const std::int_fast16_t B31, const std::int_fast16_t B32, const std::int_fast16_t B33, const std::int_fast16_t B34, const std::int_fast16_t B35, const std::int_fast16_t B36, const std::int_fast16_t B37, const std::int_fast16_t B38, const std::int_fast16_t B39, const std::int_fast16_t B40, const std::int_fast16_t B41, const std::int_fast16_t B42, const std::int_fast16_t B43, const std::int_fast16_t B44, const std::int_fast16_t B45, const std::int_fast16_t B46, const std::int_fast16_t B47, const std::int_fast16_t B48>
    void new_sample(const sample_type& x)
    {
      // Shift the delay line.
      std::copy(data.begin() + 1U,
                data.end(),
                data.begin());

      // Store the new sample at top of delay line.
      *(data.end() - 1U) = value_type(value_type(x) * value_type(resol));

      // Calculate the FIR algorithm.
      const value_type new_val = value_type(data[0U] * B0) + value_type(data[1U] * B1) + value_type(data[2U] * B2) + value_type(data[3U] * B3) + value_type(data[4U] * B4) + value_type(data[5U] * B5) + value_type(data[6U] * B6) + value_type(data[7U] * B7) + value_type(data[8U] * B8) + value_type(data[9U] * B9) + value_type(data[10U] * B10) + value_type(data[11U] * B11) + value_type(data[12U] * B12) + value_type(data[13U] * B13) + value_type(data[14U] * B14) + value_type(data[15U] * B15) + value_type(data[16U] * B16) + value_type(data[17U] * B17) + value_type(data[18U] * B18) + value_type(data[19U] * B19) + value_type(data[20U] * B20) + value_type(data[21U] * B21) + value_type(data[22U] * B22) + value_type(data[23U] * B23) + value_type(data[24U] * B24) + value_type(data[25U] * B25) + value_type(data[26U] * B26) + value_type(data[27U] * B27) + value_type(data[28U] * B28) + value_type(data[29U] * B29) + value_type(data[30U] * B30) + value_type(data[31U] * B31) + value_type(data[32U] * B32) + value_type(data[33U] * B33) + value_type(data[34U] * B34) + value_type(data[35U] * B35) + value_type(data[36U] * B36) + value_type(data[37U] * B37) + value_type(data[38U] * B38) + value_type(data[39U] * B39) + value_type(data[40U] * B40) + value_type(data[41U] * B41) + value_type(data[42U] * B42) + value_type(data[43U] * B43) + value_type(data[44U] * B44) + value_type(data[45U] * B45) + value_type(data[46U] * B46) + value_type(data[47U] * B47) + value_type(data[48U] * B48);

      const std::int_fast16_t total_weight = B0 + B1 + B2 + B3 + B4 + B5 + B6 + B7 + B8 + B9 + B10 + B11 + B12 + B13 + B14 + B15 + B16 + B17 + B18 + B19 + B20 + B21 + B22 + B23 + B24 + B25 + B26 + B27 + B28 + B29 + B30 + B31 + B32 + B33 + B34 + B35 + B36 + B37 + B38 + B39 + B40 + B41 + B42 + B43 + B44 + B45 + B46 + B47 + B48;
      result = static_cast<result_type>((new_val >= value_type(0)) ? (new_val + (total_weight / 2)) / total_weight : (new_val - (total_weight / 2)) / total_weight);
    }

    result_type get_result() const
    {
      return static_cast<result_type>((result >= result_type(0)) ? (result + result_type(resol / 2U)) / result_type(resol) : (result - result_type(resol / 2U)) / result_type(resol));
    }

  private:
    result_type result;
    std::array<value_type, 49U> data;
  };

  } } // namespace math::filters

#endif // FIR_ORDER_N_UNSIGNED_2012_03_27_H_
