/*
 * \file    gpio_v2.h
 *
 * \brief   This file contains the prototypes of the APIs present in the
 *          device abstraction layer file of GPIO belonging to AM335X SoC.
 *          This also contains some related macros.
 */

/* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 */

#ifndef  _GPIO_V2_H_
#define  _GPIO_V2_H_

#include "hw_gpio_v2.h"

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
**                       MACRO DEFINITIONS                                   
*****************************************************************************/

/* Values used to configure the direction of GPIO pins. */
#define GPIO_DIR_INPUT                   (GPIO_OE_OUTPUTEN_DISABLED)
#define GPIO_DIR_OUTPUT                  (GPIO_OE_OUTPUTEN_ENABLED)

/* Values helping to decide the value on a GPIO pin. */
#define GPIO_PIN_LOW                     (0x0)
#define GPIO_PIN_HIGH                    (0x1)

/* Values denoting the Interrupt Line number to be used. */
#define GPIO_INT_LINE_1                  (0x0)
#define GPIO_INT_LINE_2                  (0x1)

/*
** Values used to enable/disable interrupt generation due to level
** detection on an input GPIO pin.
*/
#define GPIO_INT_TYPE_NO_LEVEL           (0x01)
#define GPIO_INT_TYPE_LEVEL_0            (0x04)
#define GPIO_INT_TYPE_LEVEL_1            (0x08)
#define GPIO_INT_TYPE_BOTH_LEVEL         (0x0C)

/*
** Values used to enable/disable interrupt generation due to edge
** detection on an input GPIO pin.
*/
#define GPIO_INT_TYPE_NO_EDGE            (0x80)
#define GPIO_INT_TYPE_RISE_EDGE          (0x10)
#define GPIO_INT_TYPE_FALL_EDGE          (0x20)
#define GPIO_INT_TYPE_BOTH_EDGE          (0x30)

/* Values used for Idle Mode configurations. */
#define GPIO_IDLE_MODE_FORCE_IDLE        (GPIO_SYSCONFIG_IDLEMODE_FORCEIDLE << \
                                          GPIO_SYSCONFIG_IDLEMODE_SHIFT)
#define GPIO_IDLE_MODE_NO_IDLE           (GPIO_SYSCONFIG_IDLEMODE_NOIDLE << \
                                          GPIO_SYSCONFIG_IDLEMODE_SHIFT)
#define GPIO_IDLE_MODE_SMART_IDLE        (GPIO_SYSCONFIG_IDLEMODE_SMARTIDLE << \
                                          GPIO_SYSCONFIG_IDLEMODE_SHIFT)
#define GPIO_IDLE_MODE_SMART_IDLE_WAKEUP (GPIO_SYSCONFIG_IDLEMODE_SMARTIDLEWAKEUP << \
                                          GPIO_SYSCONFIG_IDLEMODE_SHIFT)

/* Values used to enable/disable Auto-Idle mode. */
#define GPIO_AUTO_IDLE_MODE_ENABLE       (GPIO_SYSCONFIG_AUTOIDLE_AUTOMATIC)
#define GPIO_AUTO_IDLE_MODE_DISABLE      (GPIO_SYSCONFIG_AUTOIDLE_FREERUN)

/* Values used to configure the Gating Ratio. */
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_1  (GPIO_CTRL_GATINGRATIO_N_1 << \
                                          GPIO_CTRL_GATINGRATIO_SHIFT)    
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_2  (GPIO_CTRL_GATINGRATIO_N_2 << \
                                          GPIO_CTRL_GATINGRATIO_SHIFT)
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_4  (GPIO_CTRL_GATINGRATIO_N_4 << \
                                          GPIO_CTRL_GATINGRATIO_SHIFT)
#define GPIO_GR_FUNC_CLK_INTER_CLK_BY_8  (GPIO_CTRL_GATINGRATIO_N_8 << \
                                          GPIO_CTRL_GATINGRATIO_SHIFT)

/* Values used to enable/disable Debouncing feature for an input pin. */
#define GPIO_DEBOUNCE_FUNC_ENABLE        (GPIO_DEBOUNCENABLE_DEBOUNCEENABLE_DEBOUNCE)
#define GPIO_DEBOUNCE_FUNC_DISABLE       (GPIO_DEBOUNCENABLE_DEBOUNCEENABLE_NODEBOUNCE)

/*****************************************************************************
**                       FUNCTION PROTOTYPES                                   
*****************************************************************************/

extern void GPIOModuleReset(unsigned int baseAdd);
extern void GPIOModuleEnable(unsigned int baseAdd);
extern void GPIOModuleDisable(unsigned int baseAdd);
extern void GPIODirModeSet(unsigned int baseAdd,
                           unsigned int pinNumber,
                           unsigned int pinDirection);
extern unsigned int GPIODirModeGet(unsigned int baseAdd,
                                   unsigned int pinNumber);
extern void GPIOPinWrite(unsigned int baseAdd,
                         unsigned int pinNumber,
                         unsigned int pinValue);
extern unsigned int GPIOPinRead(unsigned int baseAdd,
                                unsigned int pinNumber);
extern void GPIOMultiplePinsWrite(unsigned int baseAdd,
                                  unsigned int setMask,
                                  unsigned int clrMask);
extern unsigned int GPIOMultiplePinsRead(unsigned int baseAdd,
                                         unsigned int readMask);
extern void GPIOPinIntEnable(unsigned int baseAdd,
                             unsigned int intLine,
                             unsigned int pinNumber);

extern void GPIOPinIntDisable(unsigned int baseAdd,
                              unsigned int intLine,
                              unsigned int pinNumber);
extern void GPIOIntTypeSet(unsigned int baseAdd,
                           unsigned int pinNumber,
                           unsigned int eventType);
extern unsigned int GPIOIntTypeGet(unsigned int baseAdd,
                                   unsigned int pinNumber);
extern unsigned int GPIOPinIntStatus(unsigned int baseAdd,
                                     unsigned int intLine,
                                     unsigned int pinNumber);
extern void GPIOPinIntClear(unsigned int baseAdd,
                            unsigned int intLine,
                            unsigned int pinNumber);
extern unsigned int GPIORawIntStatus(unsigned int baseAdd,
                                     unsigned int intLine,
                                     unsigned int readMask);
extern void GPIOTriggerPinInt(unsigned int baseAdd,
                              unsigned int intLine,
                              unsigned int pinNumber);
extern void GPIOAutoIdleModeControl(unsigned int baseAdd,
                                    unsigned int modeFlag);
extern void GPIOIdleModeConfigure(unsigned int baseAdd,
                                  unsigned int modeFlag);
extern void GPIOGatingRatioConfigure(unsigned int baseAdd,
                                     unsigned int configFlag);

extern void GPIODebounceFuncControl(unsigned int baseAdd,
                                    unsigned int pinNumber,
                                    unsigned int controlFlag);
extern void GPIODebounceTimeConfig(unsigned int baseAdd,
                                   unsigned int debounceTime);
extern void GPIOEndOfInterruptEnable(unsigned int baseAdd,
                                     unsigned int intLine);
extern unsigned int GPIORevisionInfoGet(unsigned int baseAdd);


#ifdef __cplusplus
}
#endif

#endif

/********************************* End Of File ******************************/
