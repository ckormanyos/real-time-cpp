/******************************************************************************************
  Filename    : IntVect.c
  
  Core        : ARM Cortex-M4
  
  SoC         : AM6254
    
  Author      : Chalandi Amine
 
  Owner       : Chalandi Amine
  
  Date        : 29.07.2025
  
  Description : Interrupt vector table
  
******************************************************************************************/

//=============================================================================
// Types definition
//=============================================================================
typedef void (*InterruptHandler)(void);

void UndefinedHandler(void);
void UndefinedHandler(void) { for(;;); }

//=============================================================================
// Functions prototype
//=============================================================================
void Startup_Init(void);
void main_Core1 (void) __attribute__((weak, alias("UndefinedHandler")));

void __STACK_TOP(void);


/* Default interrupts handler */
void NMI(void)                                          __attribute__((weak, alias("UndefinedHandler")));
void HardFault(void)                                    __attribute__((weak, alias("UndefinedHandler")));
void SVCall(void)                                       __attribute__((weak, alias("UndefinedHandler")));
void PendSV(void)                                       __attribute__((weak, alias("UndefinedHandler")));
void SysTickTimer(void)                                 __attribute__((weak, alias("UndefinedHandler")));
void gpiomux_introuter_mcu0_outp_4(void)                __attribute__((weak, alias("UndefinedHandler")));
void gpiomux_introuter_mcu0_outp_5(void)                __attribute__((weak, alias("UndefinedHandler")));
void gpiomux_introuter_mcu0_outp_6(void)                __attribute__((weak, alias("UndefinedHandler")));
void gpiomux_introuter_mcu0_outp_7(void)                __attribute__((weak, alias("UndefinedHandler")));
void timer_mcu0_intr_pend_0(void)                       __attribute__((weak, alias("UndefinedHandler")));
void timer_mcu1_intr_pend_0(void)                       __attribute__((weak, alias("UndefinedHandler")));
void timer_mcu2_intr_pend_0(void)                       __attribute__((weak, alias("UndefinedHandler")));
void timer_mcu3_intr_pend_0(void)                       __attribute__((weak, alias("UndefinedHandler")));
void sa3ss_am62_0_intaggr_vintr_7(void)                 __attribute__((weak, alias("UndefinedHandler")));
void mainreset_request_glue_resetz_sync_stretch_0(void) __attribute__((weak, alias("UndefinedHandler")));
void mainreset_request_glue_porz_sync_stretch_0(void)   __attribute__((weak, alias("UndefinedHandler")));
void esm_am64_mcu_wkup_0_esm_int_cfg_lvl_0(void)        __attribute__((weak, alias("UndefinedHandler")));
void esm_am64_mcu_wkup_0_esm_int_hi_lvl_0(void)         __attribute__((weak, alias("UndefinedHandler")));
void esm_am64_mcu_wkup_0_esm_int_low_lvl_0(void)        __attribute__((weak, alias("UndefinedHandler")));
void MCUSS_MCU0_rat_exp_0(void)                         __attribute__((weak, alias("UndefinedHandler")));
void gpiomux_introuter_outp_34(void)                    __attribute__((weak, alias("UndefinedHandler")));
void gpiomux_introuter_outp_35(void)                    __attribute__((weak, alias("UndefinedHandler")));
void mshsi2c_mcu_0_pointrpend_0(void)                   __attribute__((weak, alias("UndefinedHandler")));
void k3_ddpa_0_ddpa_intr_0(void)                        __attribute__((weak, alias("UndefinedHandler")));
void rti_mcum4_0_intr_wwd_0(void)                       __attribute__((weak, alias("UndefinedHandler")));
void smcu_psc_wrap_wkup_0_psc_allint_0(void)            __attribute__((weak, alias("UndefinedHandler")));
void dcc_mcu0_intr_done_level_0(void)                   __attribute__((weak, alias("UndefinedHandler")));
void spi_mcu_0_intr_spi_0(void)                         __attribute__((weak, alias("UndefinedHandler")));
void spi_mcu_1_intr_spi_0(void)                         __attribute__((weak, alias("UndefinedHandler")));
void usart_mcu_0_usart_irq_0(void)                      __attribute__((weak, alias("UndefinedHandler")));
void mcrc64_mcu_0_int_mcrc_0(void)                      __attribute__((weak, alias("UndefinedHandler")));
void sms_0_sec_out_0(void)                              __attribute__((weak, alias("UndefinedHandler")));
void sms_0_sec_out_1(void)                              __attribute__((weak, alias("UndefinedHandler")));
void vtm_wkup_0_therm_lvl_lt_th0_intr_0(void)           __attribute__((weak, alias("UndefinedHandler")));
void vtm_wkup_0_therm_lvl_gt_th1_intr_0(void)           __attribute__((weak, alias("UndefinedHandler")));
void vtm_wkup_0_therm_lvl_gt_th2_intr_0(void)           __attribute__((weak, alias("UndefinedHandler")));
void mcu_cbass_intr_or_glue_out_0(void)                 __attribute__((weak, alias("UndefinedHandler")));
void dmss0_intaggr_vintr_168(void)                      __attribute__((weak, alias("UndefinedHandler")));
void dmss0_intaggr_vintr_169(void)                      __attribute__((weak, alias("UndefinedHandler")));
void dmss0_intaggr_vintr_170(void)                      __attribute__((weak, alias("UndefinedHandler")));
void dmss0_intaggr_vintr_171(void)                      __attribute__((weak, alias("UndefinedHandler")));
void k3_epwm_0_epwm_etint_0(void)                       __attribute__((weak, alias("UndefinedHandler")));
void k3_epwm_1_epwm_etint_0(void)                       __attribute__((weak, alias("UndefinedHandler")));
void k3_epwm_2_epwm_etint_0(void)                       __attribute__((weak, alias("UndefinedHandler")));
void mcu_access_err_intr_glue_out_0(void)               __attribute__((weak, alias("UndefinedHandler")));
void dss0_dispc_intr_req_0_0(void)                      __attribute__((weak, alias("UndefinedHandler")));
void dss0_dispc_intr_req_1_0(void)                      __attribute__((weak, alias("UndefinedHandler")));
void mcan_mcu0_mcanss_ext_ts_rollover_lvl_int_0(void)   __attribute__((weak, alias("UndefinedHandler")));
void mcan_mcu0_mcanss_mcan_lvl_int_0(void)              __attribute__((weak, alias("UndefinedHandler")));
void mcan_mcu0_mcanss_mcan_lvl_int_1(void)              __attribute__((weak, alias("UndefinedHandler")));
void mcan_mcu1_mcanss_ext_ts_rollover_lvl_int_0(void)   __attribute__((weak, alias("UndefinedHandler")));
void mcan_mcu1_mcanss_mcan_lvl_int_0(void)              __attribute__((weak, alias("UndefinedHandler")));
void mcan_mcu1_mcanss_mcan_lvl_int_1(void)              __attribute__((weak, alias("UndefinedHandler")));
void sms_0_aes_sintrequest_p_0(void)                    __attribute__((weak, alias("UndefinedHandler")));
void sms_0_aes_sintrequest_s_0(void)                    __attribute__((weak, alias("UndefinedHandler")));
void mailbox1_0_mailbox_cluster0_pend_2(void)           __attribute__((weak, alias("UndefinedHandler")));
void icssm0_pr1_host_intr_pend_6(void)                  __attribute__((weak, alias("UndefinedHandler")));
void icssm0_pr1_host_intr_pend_7(void)                  __attribute__((weak, alias("UndefinedHandler")));
void icssm0_iso_reset_protcol_ack_0(void)               __attribute__((weak, alias("UndefinedHandler")));
void dmss0_intaggr_vintr_172(void)                      __attribute__((weak, alias("UndefinedHandler")));
void dmss0_intaggr_vintr_173(void)                      __attribute__((weak, alias("UndefinedHandler")));
void dmss0_intaggr_vintr_174(void)                      __attribute__((weak, alias("UndefinedHandler")));
void dmss0_intaggr_vintr_175(void)                      __attribute__((weak, alias("UndefinedHandler")));
void cmp_event_introuter_0_outp_34(void)                __attribute__((weak, alias("UndefinedHandler")));
void cmp_event_introuter_0_outp_35(void)                __attribute__((weak, alias("UndefinedHandler")));
void cmp_event_introuter_0_outp_36(void)                __attribute__((weak, alias("UndefinedHandler")));
void cmp_event_introuter_0_outp_37(void)                __attribute__((weak, alias("UndefinedHandler")));
void Aggregated_target_side_timeout_interrupt(void)     __attribute__((weak, alias("UndefinedHandler")));
void Aggregated_initiator_side_timeout_interrupt(void)  __attribute__((weak, alias("UndefinedHandler")));

//=============================================================================
// Interrupt vector table
//=============================================================================
const InterruptHandler __attribute__((section(".intvect"))) __INTVECT[] =
{
    (InterruptHandler)&__STACK_TOP,
    (InterruptHandler)&Startup_Init,
    (InterruptHandler)&NMI,
    (InterruptHandler)&HardFault,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)&SVCall,
    (InterruptHandler)0,
    (InterruptHandler)0,
    (InterruptHandler)&PendSV,
    (InterruptHandler)&SysTickTimer,
    (InterruptHandler)&gpiomux_introuter_mcu0_outp_4,                //IRQ0
    (InterruptHandler)&gpiomux_introuter_mcu0_outp_5,                //IRQ1
    (InterruptHandler)&gpiomux_introuter_mcu0_outp_6,                //IRQ2
    (InterruptHandler)&gpiomux_introuter_mcu0_outp_7,                //IRQ3
    (InterruptHandler)&timer_mcu0_intr_pend_0,                       //IRQ4
    (InterruptHandler)&timer_mcu1_intr_pend_0,                       //IRQ5
    (InterruptHandler)&timer_mcu2_intr_pend_0,                       //IRQ6
    (InterruptHandler)&timer_mcu3_intr_pend_0,                       //IRQ7
    (InterruptHandler)&sa3ss_am62_0_intaggr_vintr_7,                 //IRQ8
    (InterruptHandler)&mainreset_request_glue_resetz_sync_stretch_0, //IRQ9
    (InterruptHandler)&mainreset_request_glue_porz_sync_stretch_0,   //IRQ10
    (InterruptHandler)&esm_am64_mcu_wkup_0_esm_int_cfg_lvl_0,        //IRQ11
    (InterruptHandler)&esm_am64_mcu_wkup_0_esm_int_hi_lvl_0,         //IRQ12
    (InterruptHandler)&esm_am64_mcu_wkup_0_esm_int_low_lvl_0,        //IRQ13
    (InterruptHandler)&MCUSS_MCU0_rat_exp_0,                         //IRQ14
    (InterruptHandler)&gpiomux_introuter_outp_34,                    //IRQ15
    (InterruptHandler)&gpiomux_introuter_outp_35,                    //IRQ16
    (InterruptHandler)&mshsi2c_mcu_0_pointrpend_0,                   //IRQ17
    (InterruptHandler)&k3_ddpa_0_ddpa_intr_0,                        //IRQ18
    (InterruptHandler)&rti_mcum4_0_intr_wwd_0,                       //IRQ19
    (InterruptHandler)&smcu_psc_wrap_wkup_0_psc_allint_0,            //IRQ20
    (InterruptHandler)&dcc_mcu0_intr_done_level_0,                   //IRQ21
    (InterruptHandler)&spi_mcu_0_intr_spi_0,                         //IRQ22
    (InterruptHandler)&spi_mcu_1_intr_spi_0,                         //IRQ23
    (InterruptHandler)&usart_mcu_0_usart_irq_0,                      //IRQ24
    (InterruptHandler)&mcrc64_mcu_0_int_mcrc_0,                      //IRQ25
    (InterruptHandler)&sms_0_sec_out_0,                              //IRQ26
    (InterruptHandler)&sms_0_sec_out_1,                              //IRQ27
    (InterruptHandler)&vtm_wkup_0_therm_lvl_lt_th0_intr_0,           //IRQ28
    (InterruptHandler)&vtm_wkup_0_therm_lvl_gt_th1_intr_0,           //IRQ29
    (InterruptHandler)&vtm_wkup_0_therm_lvl_gt_th2_intr_0,           //IRQ30
    (InterruptHandler)&mcu_cbass_intr_or_glue_out_0,                 //IRQ31
    (InterruptHandler)&dmss0_intaggr_vintr_168,                      //IRQ32
    (InterruptHandler)&dmss0_intaggr_vintr_169,                      //IRQ33
    (InterruptHandler)&dmss0_intaggr_vintr_170,                      //IRQ34
    (InterruptHandler)&dmss0_intaggr_vintr_171,                      //IRQ35
    (InterruptHandler)&k3_epwm_0_epwm_etint_0,                       //IRQ36
    (InterruptHandler)&k3_epwm_1_epwm_etint_0,                       //IRQ37
    (InterruptHandler)&k3_epwm_2_epwm_etint_0,                       //IRQ38
    (InterruptHandler)&mcu_access_err_intr_glue_out_0,               //IRQ39
    (InterruptHandler)&dss0_dispc_intr_req_0_0,                      //IRQ40
    (InterruptHandler)&dss0_dispc_intr_req_1_0,                      //IRQ41
    (InterruptHandler)&mcan_mcu0_mcanss_ext_ts_rollover_lvl_int_0,   //IRQ42
    (InterruptHandler)&mcan_mcu0_mcanss_mcan_lvl_int_0,              //IRQ43
    (InterruptHandler)&mcan_mcu0_mcanss_mcan_lvl_int_1,              //IRQ44
    (InterruptHandler)&mcan_mcu1_mcanss_ext_ts_rollover_lvl_int_0,   //IRQ45
    (InterruptHandler)&mcan_mcu1_mcanss_mcan_lvl_int_0,              //IRQ46
    (InterruptHandler)&mcan_mcu1_mcanss_mcan_lvl_int_1,              //IRQ47
    (InterruptHandler)&sms_0_aes_sintrequest_p_0,                    //IRQ48
    (InterruptHandler)&sms_0_aes_sintrequest_s_0,                    //IRQ49
    (InterruptHandler)&mailbox1_0_mailbox_cluster0_pend_2,           //IRQ50
    (InterruptHandler)&icssm0_pr1_host_intr_pend_6,                  //IRQ51
    (InterruptHandler)&icssm0_pr1_host_intr_pend_7,                  //IRQ52
    (InterruptHandler)&icssm0_iso_reset_protcol_ack_0,               //IRQ53
    (InterruptHandler)&dmss0_intaggr_vintr_172,                      //IRQ54
    (InterruptHandler)&dmss0_intaggr_vintr_173,                      //IRQ55
    (InterruptHandler)&dmss0_intaggr_vintr_174,                      //IRQ56
    (InterruptHandler)&dmss0_intaggr_vintr_175,                      //IRQ57
    (InterruptHandler)&cmp_event_introuter_0_outp_34,                //IRQ58
    (InterruptHandler)&cmp_event_introuter_0_outp_35,                //IRQ59
    (InterruptHandler)&cmp_event_introuter_0_outp_36,                //IRQ60
    (InterruptHandler)&cmp_event_introuter_0_outp_37,                //IRQ61
    (InterruptHandler)&Aggregated_target_side_timeout_interrupt,     //IRQ62
    (InterruptHandler)&Aggregated_initiator_side_timeout_interrupt   //IRQ63
 };
