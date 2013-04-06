#ifndef _MCAL_LED_2010_09_14_H_
  #define _MCAL_LED_2010_09_14_H_

  #include <tuple>
  #include <Util/Utility/UtilType.h>
  #include <Util/Utility/UtilNoncopyable.h>

  namespace mcal
  {
    namespace led
    {
      template<const mcal::reg::address_type ADDR, const std::uint_fast16_t BPOS>
      class Led : private util::noncopyable
      {
      private:
        static constexpr  mcal::reg::address_type PDIR = ADDR - 1u;

      public:
        Led()
        {
          mcal::reg::access<std::uint8_t, ADDR, BPOS>::fixed_bit_set();
          mcal::reg::access<std::uint8_t, PDIR, BPOS>::fixed_bit_set();
        }

        void Toggle(void) const
        {
          mcal::reg::access<std::uint8_t, ADDR, BPOS>::fixed_bit_not();
        }
      };

      typedef Led<reg::register_definitions::PORTB, 0u> Led0;
      typedef Led<reg::register_definitions::PORTB, 1u> Led1;
      typedef Led<reg::register_definitions::PORTB, 2u> Led2;
      typedef Led<reg::register_definitions::PORTB, 3u> Led3;

      extern const std::tuple<Led0, Led1, Led2, Led3> TheLeds;
    }
  }

#endif // _MCAL_LED_DRV_2010_09_14_H_
