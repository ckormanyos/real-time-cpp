#ifndef _GPIO_RPI_ZERO_BCM2835_H_
#define _GPIO_RPI_ZERO_BCM2835_H_

#include"Platform_Types.h"

/***************************************************************************************************/
/* GPIO Function Select Registers (GPFSELn) */
/***************************************************************************************************/

#define GPIO_PIN_X_INPUT                  0U
#define GPIO_PIN_X_OUTPUT                 1U
#define GPIO_PIN_X_ALTERNATE_FUNCTION_5   2U
#define GPIO_PIN_X_ALTERNATE_FUNCTION_4   3U
#define GPIO_PIN_X_ALTERNATE_FUNCTION_0   4U
#define GPIO_PIN_X_ALTERNATE_FUNCTION_1   5U
#define GPIO_PIN_X_ALTERNATE_FUNCTION_2   6U
#define GPIO_PIN_X_ALTERNATE_FUNCTION_3   7U

#define GPFSEL0_ADDR  (0x20200000UL)
#define GPFSEL1_ADDR  (0x20200004UL)
#define GPFSEL2_ADDR  (0x20200008UL)
#define GPFSEL3_ADDR  (0x2020000CUL)
#define GPFSEL4_ADDR  (0x20200010UL)
#define GPFSEL5_ADDR  (0x20200014UL)

#define GPFSEL0  ((volatile sGPFSELn*)(GPFSEL0_ADDR))
#define GPFSEL1  ((volatile sGPFSELn*)(GPFSEL1_ADDR))
#define GPFSEL2  ((volatile sGPFSELn*)(GPFSEL2_ADDR))
#define GPFSEL3  ((volatile sGPFSELn*)(GPFSEL3_ADDR))
#define GPFSEL4  ((volatile sGPFSELn*)(GPFSEL4_ADDR))
#define GPFSEL5  ((volatile sGPFSEL5*)(GPFSEL5_ADDR))

typedef union
{
  struct
  {
    uint32 FSELx0:3;
    uint32 FSELx1:3;
    uint32 FSELx2:3;
    uint32 FSELx3:3;
    uint32 FSELx4:3;
    uint32 FSELx5:3;
    uint32 FSELx6:3;
    uint32 FSELx7:3;
    uint32 FSELx8:3;
    uint32 FSELx9:3;
    uint32       :2;
  }bit;
  uint32 reg;
}sGPFSELn;

typedef union
{
  struct
  {
    uint32 FSELx0:3;
    uint32 FSELx1:3;
    uint32 FSELx2:3;
    uint32 FSELx3:3;
    uint32       :20;
  }bit;
  uint32 reg;
}sGPFSEL5;

/***************************************************************************************************/
/* GPIO Pin Output Set Registers (GPSETn) */
/***************************************************************************************************/

#define GPIO_NO_EFFECT        0U
#define GPIO_SET_GPIO_PIN_X   1U

#define GPSET0_ADDR  (0x2020001CUL)
#define GPSET1_ADDR  (0x20200020UL)

#define GPSET0  ((volatile sGPSET0*)(GPSET0_ADDR))
#define GPSET1  ((volatile sGPSET1*)(GPSET1_ADDR))

typedef union
{
  struct
  {
    uint32 SET0:1;
    uint32 SET1:1;
    uint32 SET2:1;
    uint32 SET3:1;
    uint32 SET4:1;
    uint32 SET5:1;
    uint32 SET6:1;
    uint32 SET7:1;
    uint32 SET8:1;
    uint32 SET9:1;
    uint32 SET10:1;
    uint32 SET11:1;
    uint32 SET12:1;
    uint32 SET13:1;
    uint32 SET14:1;
    uint32 SET15:1;
    uint32 SET16:1;
    uint32 SET17:1;
    uint32 SET18:1;
    uint32 SET19:1;
    uint32 SET20:1;
    uint32 SET21:1;
    uint32 SET22:1;
    uint32 SET23:1;
    uint32 SET24:1;
    uint32 SET25:1;
    uint32 SET26:1;
    uint32 SET27:1;
    uint32 SET28:1;
    uint32 SET29:1;
    uint32 SET30:1;
    uint32 SET31:1;
  }bit;
  uint32 reg;
}sGPSET0;

typedef union
{
  struct
  {
    uint32 SET32:1;
    uint32 SET33:1;
    uint32 SET34:1;
    uint32 SET35:1;
    uint32 SET36:1;
    uint32 SET37:1;
    uint32 SET38:1;
    uint32 SET39:1;
    uint32 SET40:1;
    uint32 SET41:1;
    uint32 SET42:1;
    uint32 SET43:1;
    uint32 SET44:1;
    uint32 SET45:1;
    uint32 SET46:1;
    uint32 SET47:1;
    uint32 SET48:1;
    uint32 SET49:1;
    uint32 SET50:1;
    uint32 SET51:1;
    uint32 SET52:1;
    uint32 SET53:1;
    uint32   :10;
  }bit;
  uint32 reg;
}sGPSET1;

/***************************************************************************************************/
/* GPIO Pin Output Clear Registers (GPCLRn) */
/***************************************************************************************************/

#define GPIO_CLEAR_GPIO_PIN_X   1U

#define GPCLR0_ADDR  (0x20200028UL)
#define GPCLR1_ADDR  (0x2020002CUL)

#define GPCLR0  ((volatile sGPCLR0*)(GPCLR0_ADDR))
#define GPCLR1  ((volatile sGPCLR1*)(GPCLR1_ADDR))

typedef union
{
  struct
  {
    uint32 CLR0:1;
    uint32 CLR1:1;
    uint32 CLR2:1;
    uint32 CLR3:1;
    uint32 CLR4:1;
    uint32 CLR5:1;
    uint32 CLR6:1;
    uint32 CLR7:1;
    uint32 CLR8:1;
    uint32 CLR9:1;
    uint32 CLR10:1;
    uint32 CLR11:1;
    uint32 CLR12:1;
    uint32 CLR13:1;
    uint32 CLR14:1;
    uint32 CLR15:1;
    uint32 CLR16:1;
    uint32 CLR17:1;
    uint32 CLR18:1;
    uint32 CLR19:1;
    uint32 CLR20:1;
    uint32 CLR21:1;
    uint32 CLR22:1;
    uint32 CLR23:1;
    uint32 CLR24:1;
    uint32 CLR25:1;
    uint32 CLR26:1;
    uint32 CLR27:1;
    uint32 CLR28:1;
    uint32 CLR29:1;
    uint32 CLR30:1;
    uint32 CLR31:1;
  }bit;
  uint32 reg;
}sGPCLR0;

typedef union
{
  struct
  {
    uint32 CLR32:1;
    uint32 CLR33:1;
    uint32 CLR34:1;
    uint32 CLR35:1;
    uint32 CLR36:1;
    uint32 CLR37:1;
    uint32 CLR38:1;
    uint32 CLR39:1;
    uint32 CLR40:1;
    uint32 CLR41:1;
    uint32 CLR42:1;
    uint32 CLR43:1;
    uint32 CLR44:1;
    uint32 CLR45:1;
    uint32 CLR46:1;
    uint32 CLR47:1;
    uint32 CLR48:1;
    uint32 CLR49:1;
    uint32 CLR50:1;
    uint32 CLR51:1;
    uint32 CLR52:1;
    uint32 CLR53:1;
    uint32   :10;
  }bit;
  uint32 reg;
}sGPCLR1;

/***************************************************************************************************/
/* GPIO Pin Level Registers (GPLEVn) */
/***************************************************************************************************/

#define GPIO_PIN_LEVEL_HIGH     1U
#define GPIO_PIN_LEVEL_LOW      0U

#define GPLEV0_ADDR  (0x20200034UL)
#define GPLEV1_ADDR  (0x20200038UL)

#define GPLEV0  ((volatile sGPLEV0*)(GPLEV0_ADDR))
#define GPLEV1  ((volatile sGPLEV1*)(GPLEV1_ADDR))

typedef union
{
  struct
  {
    uint32 LEV0:1;
    uint32 LEV1:1;
    uint32 LEV2:1;
    uint32 LEV3:1;
    uint32 LEV4:1;
    uint32 LEV5:1;
    uint32 LEV6:1;
    uint32 LEV7:1;
    uint32 LEV8:1;
    uint32 LEV9:1;
    uint32 LEV10:1;
    uint32 LEV11:1;
    uint32 LEV12:1;
    uint32 LEV13:1;
    uint32 LEV14:1;
    uint32 LEV15:1;
    uint32 LEV16:1;
    uint32 LEV17:1;
    uint32 LEV18:1;
    uint32 LEV19:1;
    uint32 LEV20:1;
    uint32 LEV21:1;
    uint32 LEV22:1;
    uint32 LEV23:1;
    uint32 LEV24:1;
    uint32 LEV25:1;
    uint32 LEV26:1;
    uint32 LEV27:1;
    uint32 LEV28:1;
    uint32 LEV29:1;
    uint32 LEV30:1;
    uint32 LEV31:1;
  }bit;
  uint32 reg;
}sGPLEV0;

typedef union
{
  struct
  {
    uint32 LEV32:1;
    uint32 LEV33:1;
    uint32 LEV34:1;
    uint32 LEV35:1;
    uint32 LEV36:1;
    uint32 LEV37:1;
    uint32 LEV38:1;
    uint32 LEV39:1;
    uint32 LEV40:1;
    uint32 LEV41:1;
    uint32 LEV42:1;
    uint32 LEV43:1;
    uint32 LEV44:1;
    uint32 LEV45:1;
    uint32 LEV46:1;
    uint32 LEV47:1;
    uint32 LEV48:1;
    uint32 LEV49:1;
    uint32 LEV50:1;
    uint32 LEV51:1;
    uint32 LEV52:1;
    uint32 LEV53:1;
    uint32   :10;
  }bit;
  uint32 reg;
}sGPLEV1;
/***************************************************************************************************/
/* GPIO Event Detect Status Registers (GPEDSn) */
/***************************************************************************************************/

#define GPIO_EVENT_NOT_DETECTED_ON_GPIO_PIN_X   0U
#define GPIO_EVENT_DETECTED_ON_GPIO_PIN_X       1U

#define GPEDS0  ((volatile sGPEDS0*)(0x20200040UL))
#define GPEDS1  ((volatile sGPEDS1*)(0x20200044UL))

typedef union
{
  struct
  {
    uint32 EDS0:1;
    uint32 EDS1:1;
    uint32 EDS2:1;
    uint32 EDS3:1;
    uint32 EDS4:1;
    uint32 EDS5:1;
    uint32 EDS6:1;
    uint32 EDS7:1;
    uint32 EDS8:1;
    uint32 EDS9:1;
    uint32 EDS10:1;
    uint32 EDS11:1;
    uint32 EDS12:1;
    uint32 EDS13:1;
    uint32 EDS14:1;
    uint32 EDS15:1;
    uint32 EDS16:1;
    uint32 EDS17:1;
    uint32 EDS18:1;
    uint32 EDS19:1;
    uint32 EDS20:1;
    uint32 EDS21:1;
    uint32 EDS22:1;
    uint32 EDS23:1;
    uint32 EDS24:1;
    uint32 EDS25:1;
    uint32 EDS26:1;
    uint32 EDS27:1;
    uint32 EDS28:1;
    uint32 EDS29:1;
    uint32 EDS30:1;
    uint32 EDS31:1;
  }bit;
  uint32 reg;
}sGPEDS0;

typedef union
{
  struct
  {
    uint32 EDS32:1;
    uint32 EDS33:1;
    uint32 EDS34:1;
    uint32 EDS35:1;
    uint32 EDS36:1;
    uint32 EDS37:1;
    uint32 EDS38:1;
    uint32 EDS39:1;
    uint32 EDS40:1;
    uint32 EDS41:1;
    uint32 EDS42:1;
    uint32 EDS43:1;
    uint32 EDS44:1;
    uint32 EDS45:1;
    uint32 EDS46:1;
    uint32 EDS47:1;
    uint32 EDS48:1;
    uint32 EDS49:1;
    uint32 EDS50:1;
    uint32 EDS51:1;
    uint32 EDS52:1;
    uint32 EDS53:1;
    uint32   :10;
  }bit;
  uint32 reg;
}sGPEDS1;

/***************************************************************************************************/
/* GPIO Rising Edge Detect Enable Registers (GPRENn) */
/***************************************************************************************************/

#define RISING_EDGE_DETECT_DISABLED_ON_GPIO_PIN_X  0U
#define RISING_EDGE_DETECT_ENABLED_ON_GPIO_PIN_X   1U

#define GPREN0  ((volatile sGPREN0*)(0x2020004CUL))
#define GPREN1  ((volatile sGPREN1*)(0x20200050UL))

typedef union
{
  struct
  {
    uint32 REN0:1;
    uint32 REN1:1;
    uint32 REN2:1;
    uint32 REN3:1;
    uint32 REN4:1;
    uint32 REN5:1;
    uint32 REN6:1;
    uint32 REN7:1;
    uint32 REN8:1;
    uint32 REN9:1;
    uint32 REN10:1;
    uint32 REN11:1;
    uint32 REN12:1;
    uint32 REN13:1;
    uint32 REN14:1;
    uint32 REN15:1;
    uint32 REN16:1;
    uint32 REN17:1;
    uint32 REN18:1;
    uint32 REN19:1;
    uint32 REN20:1;
    uint32 REN21:1;
    uint32 REN22:1;
    uint32 REN23:1;
    uint32 REN24:1;
    uint32 REN25:1;
    uint32 REN26:1;
    uint32 REN27:1;
    uint32 REN28:1;
    uint32 REN29:1;
    uint32 REN30:1;
    uint32 REN31:1;
  }bit;
  uint32 reg;
}sGPREN0;

typedef union
{
  struct
  {
    uint32 REN32:1;
    uint32 REN33:1;
    uint32 REN34:1;
    uint32 REN35:1;
    uint32 REN36:1;
    uint32 REN37:1;
    uint32 REN38:1;
    uint32 REN39:1;
    uint32 REN40:1;
    uint32 REN41:1;
    uint32 REN42:1;
    uint32 REN43:1;
    uint32 REN44:1;
    uint32 REN45:1;
    uint32 REN46:1;
    uint32 REN47:1;
    uint32 REN48:1;
    uint32 REN49:1;
    uint32 REN50:1;
    uint32 REN51:1;
    uint32 REN52:1;
    uint32 REN53:1;
    uint32      :10;
  }bit;
  uint32 reg;
}sGPREN1;

/***************************************************************************************************/
/* GPIO Falling Edge Detect Enable Registers (GPRENn) */
/***************************************************************************************************/

#define FALLING_EDGE_DETECT_DISABLED_ON_GPIO_PIN_X  0U
#define FALLING_EDGE_DETECT_ENABLED_ON_GPIO_PIN_X   1U

#define GPFEN0  ((volatile sGPFEN0*)(0x20200058UL))
#define GPFEN1  ((volatile sGPFEN1*)(0x2020005CUL))

typedef union
{
  struct
  {
    uint32 FEN0:1;
    uint32 FEN1:1;
    uint32 FEN2:1;
    uint32 FEN3:1;
    uint32 FEN4:1;
    uint32 FEN5:1;
    uint32 FEN6:1;
    uint32 FEN7:1;
    uint32 FEN8:1;
    uint32 FEN9:1;
    uint32 FEN10:1;
    uint32 FEN11:1;
    uint32 FEN12:1;
    uint32 FEN13:1;
    uint32 FEN14:1;
    uint32 FEN15:1;
    uint32 FEN16:1;
    uint32 FEN17:1;
    uint32 FEN18:1;
    uint32 FEN19:1;
    uint32 FEN20:1;
    uint32 FEN21:1;
    uint32 FEN22:1;
    uint32 FEN23:1;
    uint32 FEN24:1;
    uint32 FEN25:1;
    uint32 FEN26:1;
    uint32 FEN27:1;
    uint32 FEN28:1;
    uint32 FEN29:1;
    uint32 FEN30:1;
    uint32 FEN31:1;
  }bit;
  uint32 reg;
}sGPFEN0;

typedef union
{
  struct
  {
    uint32 FEN32:1;
    uint32 FEN33:1;
    uint32 FEN34:1;
    uint32 FEN35:1;
    uint32 FEN36:1;
    uint32 FEN37:1;
    uint32 FEN38:1;
    uint32 FEN39:1;
    uint32 FEN40:1;
    uint32 FEN41:1;
    uint32 FEN42:1;
    uint32 FEN43:1;
    uint32 FEN44:1;
    uint32 FEN45:1;
    uint32 FEN46:1;
    uint32 FEN47:1;
    uint32 FEN48:1;
    uint32 FEN49:1;
    uint32 FEN50:1;
    uint32 FEN51:1;
    uint32 FEN52:1;
    uint32 FEN53:1;
    uint32      :10;
  }bit;
  uint32 reg;
}sGPFEN1;

/***************************************************************************************************/
/* GPIO High Detect Enable Registers (GPHENn) */
/***************************************************************************************************/

#define HIGH_DETECT_DISABLED_ON_GPIO_PIN_X  0U
#define HIGH_DETECT_ENABLED_ON_GPIO_PIN_X   1U

#define GPHEN0  ((volatile sGPHEN0*)(0x20200064UL))
#define GPHEN1  ((volatile sGPHEN1*)(0x20200068UL))

typedef union
{
  struct
  {
    uint32 HEN0:1;
    uint32 HEN1:1;
    uint32 HEN2:1;
    uint32 HEN3:1;
    uint32 HEN4:1;
    uint32 HEN5:1;
    uint32 HEN6:1;
    uint32 HEN7:1;
    uint32 HEN8:1;
    uint32 HEN9:1;
    uint32 HEN10:1;
    uint32 HEN11:1;
    uint32 HEN12:1;
    uint32 HEN13:1;
    uint32 HEN14:1;
    uint32 HEN15:1;
    uint32 HEN16:1;
    uint32 HEN17:1;
    uint32 HEN18:1;
    uint32 HEN19:1;
    uint32 HEN20:1;
    uint32 HEN21:1;
    uint32 HEN22:1;
    uint32 HEN23:1;
    uint32 HEN24:1;
    uint32 HEN25:1;
    uint32 HEN26:1;
    uint32 HEN27:1;
    uint32 HEN28:1;
    uint32 HEN29:1;
    uint32 HEN30:1;
    uint32 HEN31:1;
  }bit;
  uint32 reg;
}sGPHEN0;

typedef union
{
  struct
  {
    uint32 HEN32:1;
    uint32 HEN33:1;
    uint32 HEN34:1;
    uint32 HEN35:1;
    uint32 HEN36:1;
    uint32 HEN37:1;
    uint32 HEN38:1;
    uint32 HEN39:1;
    uint32 HEN40:1;
    uint32 HEN41:1;
    uint32 HEN42:1;
    uint32 HEN43:1;
    uint32 HEN44:1;
    uint32 HEN45:1;
    uint32 HEN46:1;
    uint32 HEN47:1;
    uint32 HEN48:1;
    uint32 HEN49:1;
    uint32 HEN50:1;
    uint32 HEN51:1;
    uint32 HEN52:1;
    uint32 HEN53:1;
    uint32      :10;
  }bit;
  uint32 reg;
}sGPHEN1;

/***************************************************************************************************/
/* GPIO Low Detect Enable Registers (GPLENn) */
/***************************************************************************************************/

#define LOW_DETECT_DISABLED_ON_GPIO_PIN_X  0U
#define LOW_DETECT_ENABLED_ON_GPIO_PIN_X   1U

#define GPLEN0  ((volatile sGPLEN0*)(0x20200070UL))
#define GPLEN1  ((volatile sGPLEN1*)(0x20200074UL))

typedef union
{
  struct
  {
    uint32 LEN0:1;
    uint32 LEN1:1;
    uint32 LEN2:1;
    uint32 LEN3:1;
    uint32 LEN4:1;
    uint32 LEN5:1;
    uint32 LEN6:1;
    uint32 LEN7:1;
    uint32 LEN8:1;
    uint32 LEN9:1;
    uint32 LEN10:1;
    uint32 LEN11:1;
    uint32 LEN12:1;
    uint32 LEN13:1;
    uint32 LEN14:1;
    uint32 LEN15:1;
    uint32 LEN16:1;
    uint32 LEN17:1;
    uint32 LEN18:1;
    uint32 LEN19:1;
    uint32 LEN20:1;
    uint32 LEN21:1;
    uint32 LEN22:1;
    uint32 LEN23:1;
    uint32 LEN24:1;
    uint32 LEN25:1;
    uint32 LEN26:1;
    uint32 LEN27:1;
    uint32 LEN28:1;
    uint32 LEN29:1;
    uint32 LEN30:1;
    uint32 LEN31:1;
  }bit;
  uint32 reg;
}sGPLEN0;

typedef union
{
  struct
  {
    uint32 LEN32:1;
    uint32 LEN33:1;
    uint32 LEN34:1;
    uint32 LEN35:1;
    uint32 LEN36:1;
    uint32 LEN37:1;
    uint32 LEN38:1;
    uint32 LEN39:1;
    uint32 LEN40:1;
    uint32 LEN41:1;
    uint32 LEN42:1;
    uint32 LEN43:1;
    uint32 LEN44:1;
    uint32 LEN45:1;
    uint32 LEN46:1;
    uint32 LEN47:1;
    uint32 LEN48:1;
    uint32 LEN49:1;
    uint32 LEN50:1;
    uint32 LEN51:1;
    uint32 LEN52:1;
    uint32 LEN53:1;
    uint32      :10;
  }bit;
  uint32 reg;
}sGPLEN1;

/***************************************************************************************************/
/* GPIO Asynchronous Rising Edge Detect Enable Registers (GPARENn) */
/***************************************************************************************************/

#define ASYNCHRONOUS_RISING_EDGE_DETECT_DISABLED_ON_GPIO_PIN_X  0U
#define ASYNCHRONOUS_RISING_EDGE_DETECT_ENABLED_ON_GPIO_PIN_X   1U

#define GPAREN0  ((volatile sGPAREN0*)(0x2020007CUL))
#define GPAREN1  ((volatile sGPAREN1*)(0x20200080UL))

typedef union
{
  struct
  {
    uint32 AREN0:1;
    uint32 AREN1:1;
    uint32 AREN2:1;
    uint32 AREN3:1;
    uint32 AREN4:1;
    uint32 AREN5:1;
    uint32 AREN6:1;
    uint32 AREN7:1;
    uint32 AREN8:1;
    uint32 AREN9:1;
    uint32 AREN10:1;
    uint32 AREN11:1;
    uint32 AREN12:1;
    uint32 AREN13:1;
    uint32 AREN14:1;
    uint32 AREN15:1;
    uint32 AREN16:1;
    uint32 AREN17:1;
    uint32 AREN18:1;
    uint32 AREN19:1;
    uint32 AREN20:1;
    uint32 AREN21:1;
    uint32 AREN22:1;
    uint32 AREN23:1;
    uint32 AREN24:1;
    uint32 AREN25:1;
    uint32 AREN26:1;
    uint32 AREN27:1;
    uint32 AREN28:1;
    uint32 AREN29:1;
    uint32 AREN30:1;
    uint32 AREN31:1;
  }bit;
  uint32 reg;
}sGPAREN0;

typedef union
{
  struct
  {
    uint32 AREN32:1;
    uint32 AREN33:1;
    uint32 AREN34:1;
    uint32 AREN35:1;
    uint32 AREN36:1;
    uint32 AREN37:1;
    uint32 AREN38:1;
    uint32 AREN39:1;
    uint32 AREN40:1;
    uint32 AREN41:1;
    uint32 AREN42:1;
    uint32 AREN43:1;
    uint32 AREN44:1;
    uint32 AREN45:1;
    uint32 AREN46:1;
    uint32 AREN47:1;
    uint32 AREN48:1;
    uint32 AREN49:1;
    uint32 AREN50:1;
    uint32 AREN51:1;
    uint32 AREN52:1;
    uint32 AREN53:1;
    uint32      :10;
  }bit;
  uint32 reg;
}sGPAREN1;

/***************************************************************************************************/
/* GPIO Asynchronous Falling Edge Detect Enable Registers (GPRENn) */
/***************************************************************************************************/

#define ASYNCHRONOUS_FALLING_EDGE_DETECT_DISABLED_ON_GPIO_PIN_X  0U
#define ASYNCHRONOUS_FALLING_EDGE_DETECT_ENABLED_ON_GPIO_PIN_X   1U

#define GPAFEN0  ((volatile sGPAFEN0*)(0x20200088UL))
#define GPAFEN1  ((volatile sGPAFEN1*)(0x2020008CUL))

typedef union
{
  struct
  {
    uint32 AFEN0:1;
    uint32 AFEN1:1;
    uint32 AFEN2:1;
    uint32 AFEN3:1;
    uint32 AFEN4:1;
    uint32 AFEN5:1;
    uint32 AFEN6:1;
    uint32 AFEN7:1;
    uint32 AFEN8:1;
    uint32 AFEN9:1;
    uint32 AFEN10:1;
    uint32 AFEN11:1;
    uint32 AFEN12:1;
    uint32 AFEN13:1;
    uint32 AFEN14:1;
    uint32 AFEN15:1;
    uint32 AFEN16:1;
    uint32 AFEN17:1;
    uint32 AFEN18:1;
    uint32 AFEN19:1;
    uint32 AFEN20:1;
    uint32 AFEN21:1;
    uint32 AFEN22:1;
    uint32 AFEN23:1;
    uint32 AFEN24:1;
    uint32 AFEN25:1;
    uint32 AFEN26:1;
    uint32 AFEN27:1;
    uint32 AFEN28:1;
    uint32 AFEN29:1;
    uint32 AFEN30:1;
    uint32 AFEN31:1;
  }bit;
  uint32 reg;
}sGPAFEN0;

typedef union
{
  struct
  {
    uint32 AFEN32:1;
    uint32 AFEN33:1;
    uint32 AFEN34:1;
    uint32 AFEN35:1;
    uint32 AFEN36:1;
    uint32 AFEN37:1;
    uint32 AFEN38:1;
    uint32 AFEN39:1;
    uint32 AFEN40:1;
    uint32 AFEN41:1;
    uint32 AFEN42:1;
    uint32 AFEN43:1;
    uint32 AFEN44:1;
    uint32 AFEN45:1;
    uint32 AFEN46:1;
    uint32 AFEN47:1;
    uint32 AFEN48:1;
    uint32 AFEN49:1;
    uint32 AFEN50:1;
    uint32 AFEN51:1;
    uint32 AFEN52:1;
    uint32 AFEN53:1;
    uint32      :10;
  }bit;
  uint32 reg;
}sGPAFEN1;

/***************************************************************************************************/
/* GPIO Pull-up/down Register (GPPUD) */
/***************************************************************************************************/

#define GPIO_DISABLE_PULL_UP_DOWN      0U
#define GPIO_ENABLE_PULL_DOWN_CONTROL  1U
#define GPIO_ENABLE_PULL_UP_CONTROL    2U
#define GPIO_RESERVED                  3U

#define GPPUD  ((volatile sGPPUD*)(0x20200094UL))

typedef union
{
  struct
  {
    uint32 PUD:2;
    uint32    :30;
  }bit;
  uint32 reg;
}sGPPUD;


/***************************************************************************************************/
/* GPIO Pull-up/down Clock Registers (GPPUDCLKn) */
/***************************************************************************************************/

#define ASSERT_CLOCK_ON_LINE_X   1U

#define GPPUDCLK0     ((volatile sGPPUDCLK0*)(0x20200098UL))
#define GPPUDCLK1     ((volatile sGPPUDCLK1*)(0x2020009CUL))

typedef union
{
  struct
  {
    uint32 PUDCLK0:1;
    uint32 PUDCLK1:1;
    uint32 PUDCLK2:1;
    uint32 PUDCLK3:1;
    uint32 PUDCLK4:1;
    uint32 PUDCLK5:1;
    uint32 PUDCLK6:1;
    uint32 PUDCLK7:1;
    uint32 PUDCLK8:1;
    uint32 PUDCLK9:1;
    uint32 PUDCLK10:1;
    uint32 PUDCLK11:1;
    uint32 PUDCLK12:1;
    uint32 PUDCLK13:1;
    uint32 PUDCLK14:1;
    uint32 PUDCLK15:1;
    uint32 PUDCLK16:1;
    uint32 PUDCLK17:1;
    uint32 PUDCLK18:1;
    uint32 PUDCLK19:1;
    uint32 PUDCLK20:1;
    uint32 PUDCLK21:1;
    uint32 PUDCLK22:1;
    uint32 PUDCLK23:1;
    uint32 PUDCLK24:1;
    uint32 PUDCLK25:1;
    uint32 PUDCLK26:1;
    uint32 PUDCLK27:1;
    uint32 PUDCLK28:1;
    uint32 PUDCLK29:1;
    uint32 PUDCLK30:1;
    uint32 PUDCLK31:1;
  }bit;
  uint32 reg;
}sGPPUDCLK0;

typedef union
{
  struct
  {
    uint32 PUDCLK32:1;
    uint32 PUDCLK33:1;
    uint32 PUDCLK34:1;
    uint32 PUDCLK35:1;
    uint32 PUDCLK36:1;
    uint32 PUDCLK37:1;
    uint32 PUDCLK38:1;
    uint32 PUDCLK39:1;
    uint32 PUDCLK40:1;
    uint32 PUDCLK41:1;
    uint32 PUDCLK42:1;
    uint32 PUDCLK43:1;
    uint32 PUDCLK44:1;
    uint32 PUDCLK45:1;
    uint32 PUDCLK46:1;
    uint32 PUDCLK47:1;
    uint32 PUDCLK48:1;
    uint32 PUDCLK49:1;
    uint32 PUDCLK50:1;
    uint32 PUDCLK51:1;
    uint32 PUDCLK52:1;
    uint32 PUDCLK53:1;
    uint32      :10;
  }bit;
  uint32 reg;
}sGPPUDCLK1;

/*******************************************************************************************************************
** Defines
*******************************************************************************************************************/

#define GPIO_PIN02_H03      (uint8)(0x02u)
#define GPIO_PIN03_H05      (uint8)(0x03u)
#define GPIO_PIN04_H07      (uint8)(0x04u)
#define GPIO_PIN17_H11      (uint8)(0x17u)
#define GPIO_PIN27_H13      (uint8)(0x27u)
#define GPIO_PIN22_H15      (uint8)(0x22u)
#define GPIO_PIN10_H19      (uint8)(0x10u)
#define GPIO_PIN09_H21      (uint8)(0x09u)
#define GPIO_PIN11_H23      (uint8)(0x11u)
#define GPIO_PIN05_H29      (uint8)(0x05u)
#define GPIO_PIN06_H31      (uint8)(0x06u)
#define GPIO_PIN13_H33      (uint8)(0x13u)
#define GPIO_PIN19_H35      (uint8)(0x19u)
#define GPIO_PIN26_H37      (uint8)(0x26u)
#define GPIO_PIN14_H08      (uint8)(0x14u)
#define GPIO_PIN15_H10      (uint8)(0x15u)
#define GPIO_PIN18_H12      (uint8)(0x18u)
#define GPIO_PIN23_H16      (uint8)(0x23u)
#define GPIO_PIN24_H18      (uint8)(0x24u)
#define GPIO_PIN25_H22      (uint8)(0x25u)
#define GPIO_PIN08_H24      (uint8)(0x08u)
#define GPIO_PIN07_H26      (uint8)(0x07u)
#define GPIO_PIN12_H32      (uint8)(0x12u)
#define GPIO_PIN16_H36      (uint8)(0x16u)
#define GPIO_PIN20_H38      (uint8)(0x20u)
#define GPIO_PIN21_H40      (uint8)(0x21u)

#define GPIO_STATUS_LED     (uint8)(0x47u)

/*******************************************************************************************************************
** Prototypes
*******************************************************************************************************************/

#if defined(__cplusplus)
extern "C"
{
#endif

void gpio_ClrPin(uint8 PortPin);
void gpio_SetPin(uint8 PortPin);

#if defined(__cplusplus)
}
#endif

#endif
