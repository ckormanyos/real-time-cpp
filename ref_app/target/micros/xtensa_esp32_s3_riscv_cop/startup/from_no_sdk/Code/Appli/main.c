/******************************************************************************************
  Filename    : main.c
  
  Core        : RISC-V
  
  MCU         : ESP32-S3
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 22.02.2025
  
  Description : Application main function for ULP-RISC-V Co-processor
  
******************************************************************************************/

//=============================================================================
// Includes
//=============================================================================
#include<stdint.h>

//=============================================================================
// Prototypes
//=============================================================================


//=============================================================================
// Defines
//=============================================================================
/* RTC_GPIO18 */
#define RTC_GPIO_BASE         0xA400ul
#define RTC_GPIO_OUT_REG      *(volatile uint32_t*)(RTC_GPIO_BASE + 0x0000ul)
#define RTC_GPIO_ENABLE_REG   *(volatile uint32_t*)(RTC_GPIO_BASE + 0x000Cul)
#define RTC_GPIO_PIN17_REG    *(volatile uint32_t*)(RTC_GPIO_BASE + 0x006Cul)
#define RTC_IO_RTC_PAD17_REG  *(volatile uint32_t*)(RTC_GPIO_BASE + 0x00C8ul)
#define RTC_GPIO_PIN18_REG    *(volatile uint32_t*)(RTC_GPIO_BASE + 0x0070ul)
#define RTC_IO_RTC_PAD18_REG  *(volatile uint32_t*)(RTC_GPIO_BASE + 0x00CCul)


//=============================================================================
// Macros
//=============================================================================
#define TOGGLE_GPIO18()       RTC_GPIO_OUT_REG ^= (1ul << (10 + 18))
#define TOGGLE_GPIO17()       RTC_GPIO_OUT_REG ^= (1ul << (10 + 17))


//-----------------------------------------------------------------------------------------
/// \brief  main function
///
/// \param  void
///
/// \return void
//-----------------------------------------------------------------------------------------
void main()
{
  /* configure GPIO17 and GPIO18 as output low */
  RTC_IO_RTC_PAD18_REG |= (1ul << 19);
  RTC_GPIO_PIN18_REG    = 0;
  RTC_GPIO_ENABLE_REG  |= (1ul << (10 + 18));
  RTC_IO_RTC_PAD17_REG |= (1ul << 19);
  RTC_GPIO_PIN17_REG    = 0;
  RTC_GPIO_ENABLE_REG  |= (1ul << (10 + 18)) | (1ul << (10 + 17)); 
  RTC_GPIO_OUT_REG = 0;

  for(;;)
  {
     TOGGLE_GPIO17();
     for(uint32_t i=0; i< 0x100000; i++);
  }
}
