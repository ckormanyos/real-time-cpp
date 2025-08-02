#ifndef __VIM_H__
#define __VIM_H__

#include <stdint.h>

#define VIM_BASE_ADDRESS            (uintptr_t)0x2FFF0000
#define VIM_GROUP_SIZE              32
#define VIM_NUMBER_OF_32_GROUP      8
#define VIM_TOTAL_SUPPORTED_INT_NUM 256

typedef struct{
  uint32_t vim_group_m_interrupt_raw_status_set;           //offset: 0x00
  uint32_t vim_group_m_interrupt_enabled_status_clear;     //offset: 0x04
  uint32_t vim_group_m_interrupt_enabled_set;              //offset: 0x08
  uint32_t vim_group_m_interrupt_enabled_clear;            //offset: 0x0C
  uint32_t vim_group_m_interrupt_irq_enabled_status_clear; //offset: 0x10
  uint32_t vim_group_m_interrupt_fiq_enabled_status_clear; //offset: 0x14
  uint32_t vim_group_m_interrupt_map;                      //offset: 0x18
  uint32_t vim_group_m_type_map;                           //offset: 0x1C
}vim_group_m_reg;                                          //offset: 0x20


typedef struct{
  uint32_t vim_revision;                                                                           //offset: 0x00
  uint32_t vim_info;                                                                               //offset: 0x04
  uint32_t vim_prioritized_irq;                                                                    //offset: 0x08
  uint32_t vim_prioritized_fiq;                                                                    //offset: 0x0C
  uint32_t vim_irq_group_status;                                                                   //offset: 0x10
  uint32_t vim_fiq_group_status;                                                                   //offset: 0x14
  uint32_t vim_irq_vector_address;                                                                 //offset: 0x18
  uint32_t vim_fiq_vector_address;                                                                 //offset: 0x1C
  uint32_t vim_active_irq;                                                                         //offset: 0x20
  uint32_t vim_active_fiq;                                                                         //offset: 0x24
  uint32_t vim_reserved[2];                                                                        //offset: 0x28
  uint32_t vim_ded_vector_address;                                                                 //offset: 0x30
  vim_group_m_reg vim_group_m[VIM_NUMBER_OF_32_GROUP]            __attribute__((aligned(0x400)));  //offset: 0x400
  uint32_t vim_interrupt_q_priority[VIM_TOTAL_SUPPORTED_INT_NUM] __attribute__((aligned(0x1000))); //offset: 0x1000
  uint32_t vim_interrupt_q_vector[VIM_TOTAL_SUPPORTED_INT_NUM]   __attribute__((aligned(0x2000))); //offset: 0x2000
}vim_reg;

#endif /*__VIM_H__*/
