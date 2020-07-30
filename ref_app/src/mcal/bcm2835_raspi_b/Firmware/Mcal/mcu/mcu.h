#ifndef _MCU_RPI_ZERO_BCM2835_H_
#define _MCU_RPI_ZERO_BCM2835_H_

#include"Platform_Types.h"


#define  ARM_INTERRUPT_CONTROLLER_BASE       (0x2000B000UL)

#define IRQ_BASIC_PENDING_BASE               (ARM_INTERRUPT_CONTROLLER_BASE + 0x200UL)
#define IRQ_PENDING_1_BASE                   (ARM_INTERRUPT_CONTROLLER_BASE + 0x204UL)
#define IRQ_PENDING_2_BASE                   (ARM_INTERRUPT_CONTROLLER_BASE + 0x208UL)
#define FIQ_CONTROL_BASE                     (ARM_INTERRUPT_CONTROLLER_BASE + 0x20CUL)
#define ENABLE_IRQS_1_BASE                   (ARM_INTERRUPT_CONTROLLER_BASE + 0x210UL)
#define ENABLE_IRQS_2_BASE                   (ARM_INTERRUPT_CONTROLLER_BASE + 0x214UL)
#define ENABLE_BASIC_IRQS_BASE               (ARM_INTERRUPT_CONTROLLER_BASE + 0x218UL)
#define DISABLE_IRQS_1_BASE                  (ARM_INTERRUPT_CONTROLLER_BASE + 0x21CUL)
#define DISABLE_IRQS_2_BASE                  (ARM_INTERRUPT_CONTROLLER_BASE + 0x220UL)
#define DISABLE_BASIC_IRQS_BASE              (ARM_INTERRUPT_CONTROLLER_BASE + 0x224UL)


#define FIQ_CONTROL         ((volatile sFiqCtrl*)FIQ_CONTROL_BASE)
#define ENABLE_BASIC_IRQS   (*(volatile uint32*)ENABLE_BASIC_IRQS_BASE)
#define IRQ_BASIC_PENDING   (*(volatile uint32*)IRQ_BASIC_PENDING_BASE)

typedef union
{
  struct
  {
    uint32 FIQSrc:7;
    uint32  FIQEn:1;
    uint32       :24;
  }bit;
  uint32 reg;
}sFiqCtrl;


#define DISABLE_FIQ_GENERATION    0U
#define ENABLE_FIQ_GENERATION     1U


/*
 * Interrupt assignments (complete BCM2835 interrupts mapping GPU + ARM)
 */

#define ARM_IRQ1_BASE                  0
#define INTERRUPT_TIMER0               (ARM_IRQ1_BASE + 0) /* used by the GPU */
#define INTERRUPT_TIMER1               (ARM_IRQ1_BASE + 1) /* free for ARM, not used by the GPU */
#define INTERRUPT_TIMER2               (ARM_IRQ1_BASE + 2) /* used by the GPU */
#define INTERRUPT_TIMER3               (ARM_IRQ1_BASE + 3) /* free for ARM, not used by the GPU */
#define INTERRUPT_CODEC0               (ARM_IRQ1_BASE + 4)
#define INTERRUPT_CODEC1               (ARM_IRQ1_BASE + 5)
#define INTERRUPT_CODEC2               (ARM_IRQ1_BASE + 6)
#define INTERRUPT_VC_JPEG              (ARM_IRQ1_BASE + 7)
#define INTERRUPT_ISP                  (ARM_IRQ1_BASE + 8)
#define INTERRUPT_VC_USB               (ARM_IRQ1_BASE + 9)
#define INTERRUPT_VC_3D                (ARM_IRQ1_BASE + 10)
#define INTERRUPT_TRANSPOSER           (ARM_IRQ1_BASE + 11)
#define INTERRUPT_MULTICORESYNC0       (ARM_IRQ1_BASE + 12)
#define INTERRUPT_MULTICORESYNC1       (ARM_IRQ1_BASE + 13)
#define INTERRUPT_MULTICORESYNC2       (ARM_IRQ1_BASE + 14)
#define INTERRUPT_MULTICORESYNC3       (ARM_IRQ1_BASE + 15)
#define INTERRUPT_DMA0                 (ARM_IRQ1_BASE + 16)
#define INTERRUPT_DMA1                 (ARM_IRQ1_BASE + 17)
#define INTERRUPT_VC_DMA2              (ARM_IRQ1_BASE + 18)
#define INTERRUPT_VC_DMA3              (ARM_IRQ1_BASE + 19)
#define INTERRUPT_DMA4                 (ARM_IRQ1_BASE + 20)
#define INTERRUPT_DMA5                 (ARM_IRQ1_BASE + 21)
#define INTERRUPT_DMA6                 (ARM_IRQ1_BASE + 22)
#define INTERRUPT_DMA7                 (ARM_IRQ1_BASE + 23)
#define INTERRUPT_DMA8                 (ARM_IRQ1_BASE + 24)
#define INTERRUPT_DMA9                 (ARM_IRQ1_BASE + 25)
#define INTERRUPT_DMA10                (ARM_IRQ1_BASE + 26)
#define INTERRUPT_DMA11                (ARM_IRQ1_BASE + 27)
#define INTERRUPT_DMA12                (ARM_IRQ1_BASE + 28)
#define INTERRUPT_AUX                  (ARM_IRQ1_BASE + 29)
#define INTERRUPT_ARM                  (ARM_IRQ1_BASE + 30)
#define INTERRUPT_VPUDMA               (ARM_IRQ1_BASE + 31)

#define ARM_IRQ2_BASE                  32
#define INTERRUPT_HOSTPORT             (ARM_IRQ2_BASE + 0)
#define INTERRUPT_VIDEOSCALER          (ARM_IRQ2_BASE + 1)
#define INTERRUPT_CCP2TX               (ARM_IRQ2_BASE + 2)
#define INTERRUPT_SDC                  (ARM_IRQ2_BASE + 3)
#define INTERRUPT_DSI0                 (ARM_IRQ2_BASE + 4)
#define INTERRUPT_AVE                  (ARM_IRQ2_BASE + 5)
#define INTERRUPT_CAM0                 (ARM_IRQ2_BASE + 6)
#define INTERRUPT_CAM1                 (ARM_IRQ2_BASE + 7)
#define INTERRUPT_HDMI0                (ARM_IRQ2_BASE + 8)
#define INTERRUPT_HDMI1                (ARM_IRQ2_BASE + 9)
#define INTERRUPT_PIXELVALVE1          (ARM_IRQ2_BASE + 10)
#define INTERRUPT_I2CSPISLV            (ARM_IRQ2_BASE + 11)
#define INTERRUPT_DSI1                 (ARM_IRQ2_BASE + 12)
#define INTERRUPT_PWA0                 (ARM_IRQ2_BASE + 13)
#define INTERRUPT_PWA1                 (ARM_IRQ2_BASE + 14)
#define INTERRUPT_CPR                  (ARM_IRQ2_BASE + 15)
#define INTERRUPT_SMI                  (ARM_IRQ2_BASE + 16)
#define INTERRUPT_GPIO0                (ARM_IRQ2_BASE + 17)
#define INTERRUPT_GPIO1                (ARM_IRQ2_BASE + 18)
#define INTERRUPT_GPIO2                (ARM_IRQ2_BASE + 19)
#define INTERRUPT_GPIO3                (ARM_IRQ2_BASE + 20)
#define INTERRUPT_VC_I2C               (ARM_IRQ2_BASE + 21)
#define INTERRUPT_VC_SPI               (ARM_IRQ2_BASE + 22)
#define INTERRUPT_VC_I2SPCM            (ARM_IRQ2_BASE + 23)
#define INTERRUPT_VC_SDIO              (ARM_IRQ2_BASE + 24)
#define INTERRUPT_VC_UART              (ARM_IRQ2_BASE + 25)
#define INTERRUPT_SLIMBUS              (ARM_IRQ2_BASE + 26)
#define INTERRUPT_VEC                  (ARM_IRQ2_BASE + 27)
#define INTERRUPT_CPG                  (ARM_IRQ2_BASE + 28)
#define INTERRUPT_RNG                  (ARM_IRQ2_BASE + 29)
#define INTERRUPT_VC_ARASANSDIO        (ARM_IRQ2_BASE + 30)
#define INTERRUPT_AVSPMON              (ARM_IRQ2_BASE + 31)

#define ARM_IRQ0_BASE                  64
#define INTERRUPT_ARM_TIMER            (ARM_IRQ0_BASE + 0)
#define INTERRUPT_ARM_MAILBOX          (ARM_IRQ0_BASE + 1)
#define INTERRUPT_ARM_DOORBELL_0       (ARM_IRQ0_BASE + 2)
#define INTERRUPT_ARM_DOORBELL_1       (ARM_IRQ0_BASE + 3)
#define INTERRUPT_VPU0_HALTED          (ARM_IRQ0_BASE + 4)
#define INTERRUPT_VPU1_HALTED          (ARM_IRQ0_BASE + 5)
#define INTERRUPT_ILLEGAL_TYPE0        (ARM_IRQ0_BASE + 6)
#define INTERRUPT_ILLEGAL_TYPE1        (ARM_IRQ0_BASE + 7)
#define INTERRUPT_PENDING1             (ARM_IRQ0_BASE + 8)
#define INTERRUPT_PENDING2             (ARM_IRQ0_BASE + 9)
#define INTERRUPT_JPEG                 (ARM_IRQ0_BASE + 10)
#define INTERRUPT_USB                  (ARM_IRQ0_BASE + 11)
#define INTERRUPT_3D                   (ARM_IRQ0_BASE + 12)
#define INTERRUPT_DMA2                 (ARM_IRQ0_BASE + 13)
#define INTERRUPT_DMA3                 (ARM_IRQ0_BASE + 14)
#define INTERRUPT_I2C                  (ARM_IRQ0_BASE + 15)
#define INTERRUPT_SPI                  (ARM_IRQ0_BASE + 16)
#define INTERRUPT_I2SPCM               (ARM_IRQ0_BASE + 17)
#define INTERRUPT_SDIO                 (ARM_IRQ0_BASE + 18)
#define INTERRUPT_UART                 (ARM_IRQ0_BASE + 19)
#define INTERRUPT_ARASANSDIO           (ARM_IRQ0_BASE + 20)

#if defined(__cplusplus)
extern "C"
{
#endif

__attribute__((naked)) void Mcu_WriteBcm2835Register(uint32 address, uint32 value);
__attribute__((naked)) uint32 Mcu_ReadBcm2835Register(uint32 address);

#if defined(__cplusplus)
}
#endif

#endif
