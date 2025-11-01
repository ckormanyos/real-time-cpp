
#ifndef BL602_H
#define BL602_H

#if 0
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif

#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/* =========================================================================================================================== */
/* ================                                   GPIO FUNC Defines                                       ================ */
/* =========================================================================================================================== */
#define GPIO_FUN_SDIO       1
#define GPIO_FUN_FLASH      2
#define GPIO_FUN_SPI        4
#define GPIO_FUN_I2C        6
#define GPIO_FUN_UART       7
#define GPIO_FUN_PWM        8
#define GPIO_FUN_EXT_PA     9
#define GPIO_FUN_ANALOG     10
#define GPIO_FUN_SWGPIO     11
#define GPIO_FUN_JTAG       14

/* =========================================================================================================================== */
/* ================                                            glb                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief glb. (glb)
  */

typedef struct {                                /*!< glb Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< clk_cfg0.                                                                 */
    
    struct {
      __IOM uint32_t reg_pll_en : 1;            /*!< reg_pll_en                                                                */
      __IOM uint32_t reg_fclk_en : 1;           /*!< reg_fclk_en                                                               */
      __IOM uint32_t reg_hclk_en : 1;           /*!< reg_hclk_en                                                               */
      __IOM uint32_t reg_bclk_en : 1;           /*!< reg_bclk_en                                                               */
      __IOM uint32_t reg_pll_sel : 2;           /*!< reg_pll_sel                                                               */
      __IOM uint32_t hbn_root_clk_sel : 2;      /*!< hbn_root_clk_sel                                                          */
      __IOM uint32_t reg_hclk_div : 8;          /*!< reg_hclk_div                                                              */
      __IOM uint32_t reg_bclk_div : 8;          /*!< reg_bclk_div                                                              */
      __IOM uint32_t fclk_sw_state : 3;         /*!< fclk_sw_state                                                             */
      __IOM uint32_t chip_rdy   : 1;            /*!< chip_rdy                                                                  */
      __IOM uint32_t glb_id     : 4;            /*!< glb_id                                                                    */
    } bit;
  } clk_cfg0;
  
  union {
    __IOM uint32_t reg;                         /*!< clk_cfg1.                                                                 */
    
    struct {
      __IOM uint32_t wifi_mac_core_div : 4;     /*!< wifi_mac_core_div                                                         */
      __IOM uint32_t wifi_mac_wt_div : 4;       /*!< wifi_mac_wt_div                                                           */
            uint32_t            : 8;
      __IOM uint32_t ble_clk_sel : 6;           /*!< ble_clk_sel                                                               */
            uint32_t            : 2;
      __IOM uint32_t ble_en     : 1;            /*!< ble_en                                                                    */
            uint32_t            : 7;
    } bit;
  } clk_cfg1;
  
  union {
    __IOM uint32_t reg;                         /*!< clk_cfg2.                                                                 */
    
    struct {
      __IOM uint32_t uart_clk_div : 3;          /*!< uart_clk_div                                                              */
            uint32_t            : 1;
      __IOM uint32_t uart_clk_en : 1;           /*!< uart_clk_en                                                               */
            uint32_t            : 2;
      __IOM uint32_t hbn_uart_clk_sel : 1;      /*!< hbn_uart_clk_sel                                                          */
      __IOM uint32_t sf_clk_div : 3;            /*!< sf_clk_div                                                                */
      __IOM uint32_t sf_clk_en  : 1;            /*!< sf_clk_en                                                                 */
      __IOM uint32_t sf_clk_sel : 2;            /*!< sf_clk_sel                                                                */
      __IOM uint32_t sf_clk_sel2 : 2;           /*!< sf_clk_sel2                                                               */
      __IOM uint32_t ir_clk_div : 6;            /*!< ir_clk_div                                                                */
            uint32_t            : 1;
      __IOM uint32_t ir_clk_en  : 1;            /*!< ir_clk_en                                                                 */
      __IOM uint32_t dma_clk_en : 8;            /*!< dma_clk_en                                                                */
    } bit;
  } clk_cfg2;
  
  union {
    __IOM uint32_t reg;                         /*!< clk_cfg3.                                                                 */
    
    struct {
      __IOM uint32_t spi_clk_div : 5;           /*!< spi_clk_div                                                               */
            uint32_t            : 3;
      __IOM uint32_t spi_clk_en : 1;            /*!< spi_clk_en                                                                */
            uint32_t            : 7;
      __IOM uint32_t i2c_clk_div : 8;           /*!< i2c_clk_div                                                               */
      __IOM uint32_t i2c_clk_en : 1;            /*!< i2c_clk_en                                                                */
            uint32_t            : 7;
    } bit;
  } clk_cfg3;
  
  union {
    __IOM uint32_t reg;                         /*!< swrst_cfg0.                                                               */
    
    struct {
      __IOM uint32_t swrst_s00  : 1;            /*!< swrst_s00                                                                 */
      __IOM uint32_t swrst_s01  : 1;            /*!< swrst_s01                                                                 */
            uint32_t            : 2;
      __IOM uint32_t swrst_s20  : 1;            /*!< swrst_s20                                                                 */
            uint32_t            : 3;
      __IOM uint32_t swrst_s30  : 1;            /*!< swrst_s30                                                                 */
            uint32_t            : 23;
    } bit;
  } swrst_cfg0;
  
  union {
    __IOM uint32_t reg;                         /*!< swrst_cfg1.                                                               */
    
    struct {
      __IOM uint32_t swrst_s10  : 1;            /*!< swrst_s10                                                                 */
      __IOM uint32_t swrst_s11  : 1;            /*!< swrst_s11                                                                 */
      __IOM uint32_t swrst_s12  : 1;            /*!< swrst_s12                                                                 */
      __IOM uint32_t swrst_s13  : 1;            /*!< swrst_s13                                                                 */
      __IOM uint32_t swrst_s14  : 1;            /*!< swrst_s14                                                                 */
      __IOM uint32_t swrst_s15  : 1;            /*!< swrst_s15                                                                 */
      __IOM uint32_t swrst_s16  : 1;            /*!< swrst_s16                                                                 */
      __IOM uint32_t swrst_s17  : 1;            /*!< swrst_s17                                                                 */
      __IOM uint32_t swrst_s18  : 1;            /*!< swrst_s18                                                                 */
      __IOM uint32_t swrst_s19  : 1;            /*!< swrst_s19                                                                 */
      __IOM uint32_t swrst_s1a  : 1;            /*!< swrst_s1a                                                                 */
      __IOM uint32_t swrst_s1b  : 1;            /*!< swrst_s1b                                                                 */
      __IOM uint32_t swrst_s1c  : 1;            /*!< swrst_s1c                                                                 */
      __IOM uint32_t swrst_s1d  : 1;            /*!< swrst_s1d                                                                 */
      __IOM uint32_t swrst_s1e  : 1;            /*!< swrst_s1e                                                                 */
      __IOM uint32_t swrst_s1f  : 1;            /*!< swrst_s1f                                                                 */
      __IOM uint32_t swrst_s1a0 : 1;            /*!< swrst_s1a0                                                                */
      __IOM uint32_t swrst_s1a1 : 1;            /*!< swrst_s1a1                                                                */
      __IOM uint32_t swrst_s1a2 : 1;            /*!< swrst_s1a2                                                                */
      __IOM uint32_t swrst_s1a3 : 1;            /*!< swrst_s1a3                                                                */
      __IOM uint32_t swrst_s1a4 : 1;            /*!< swrst_s1a4                                                                */
      __IOM uint32_t swrst_s1a5 : 1;            /*!< swrst_s1a5                                                                */
      __IOM uint32_t swrst_s1a6 : 1;            /*!< swrst_s1a6                                                                */
      __IOM uint32_t swrst_s1a7 : 1;            /*!< swrst_s1a7                                                                */
            uint32_t            : 8;
    } bit;
  } swrst_cfg1;
  
  union {
    __IOM uint32_t reg;                         /*!< swrst_cfg2.                                                               */
    
    struct {
      __IOM uint32_t reg_ctrl_pwron_rst : 1;    /*!< reg_ctrl_pwron_rst                                                        */
      __IOM uint32_t reg_ctrl_cpu_reset : 1;    /*!< reg_ctrl_cpu_reset                                                        */
      __IOM uint32_t reg_ctrl_sys_reset : 1;    /*!< reg_ctrl_sys_reset                                                        */
            uint32_t            : 1;
      __IOM uint32_t reg_ctrl_reset_dummy : 4;  /*!< reg_ctrl_reset_dummy                                                      */
            uint32_t            : 16;
      __IOM uint32_t pka_clk_sel : 1;           /*!< pka_clk_sel                                                               */
            uint32_t            : 7;
    } bit;
  } swrst_cfg2;
  __IOM uint32_t  swrst_cfg3;                   /*!< swrst_cfg3.                                                               */
  
  union {
    __IOM uint32_t reg;                         /*!< cgen_cfg0.                                                                */
    
    struct {
      __IOM uint32_t cgen_m     : 8;            /*!< cgen_m                                                                    */
            uint32_t            : 24;
    } bit;
  } cgen_cfg0;
  
  union {
    __IOM uint32_t reg;                         /*!< cgen_cfg1.                                                                */
    
    struct {
      __IOM uint32_t cgen_s1    : 16;           /*!< cgen_s1                                                                   */
      __IOM uint32_t cgen_s1a   : 8;            /*!< cgen_s1a                                                                  */
            uint32_t            : 8;
    } bit;
  } cgen_cfg1;
  
  union {
    __IOM uint32_t reg;                         /*!< cgen_cfg2.                                                                */
    
    struct {
      __IOM uint32_t cgen_s2    : 1;            /*!< cgen_s2                                                                   */
            uint32_t            : 3;
      __IOM uint32_t cgen_s3    : 1;            /*!< cgen_s3                                                                   */
            uint32_t            : 27;
    } bit;
  } cgen_cfg2;
  __IOM uint32_t  cgen_cfg3;                    /*!< cgen_cfg3.                                                                */
  
  union {
    __IOM uint32_t reg;                         /*!< MBIST_CTL.                                                                */
    
    struct {
      __IOM uint32_t irom_mbist_mode : 1;       /*!< irom_mbist_mode                                                           */
      __IOM uint32_t hsram_mbist_mode : 1;      /*!< hsram_mbist_mode                                                          */
      __IOM uint32_t tag_mbist_mode : 1;        /*!< tag_mbist_mode                                                            */
      __IOM uint32_t ocram_mbist_mode : 1;      /*!< ocram_mbist_mode                                                          */
      __IOM uint32_t wifi_mbist_mode : 1;       /*!< wifi_mbist_mode                                                           */
            uint32_t            : 26;
      __IOM uint32_t reg_mbist_rst_n : 1;       /*!< reg_mbist_rst_n                                                           */
    } bit;
  } MBIST_CTL;
  
  union {
    __IOM uint32_t reg;                         /*!< MBIST_STAT.                                                               */
    
    struct {
      __IOM uint32_t irom_mbist_done : 1;       /*!< irom_mbist_done                                                           */
      __IOM uint32_t hsram_mbist_done : 1;      /*!< hsram_mbist_done                                                          */
      __IOM uint32_t tag_mbist_done : 1;        /*!< tag_mbist_done                                                            */
      __IOM uint32_t ocram_mbist_done : 1;      /*!< ocram_mbist_done                                                          */
      __IOM uint32_t wifi_mbist_done : 1;       /*!< wifi_mbist_done                                                           */
            uint32_t            : 11;
      __IOM uint32_t irom_mbist_fail : 1;       /*!< irom_mbist_fail                                                           */
      __IOM uint32_t hsram_mbist_fail : 1;      /*!< hsram_mbist_fail                                                          */
      __IOM uint32_t tag_mbist_fail : 1;        /*!< tag_mbist_fail                                                            */
      __IOM uint32_t ocram_mbist_fail : 1;      /*!< ocram_mbist_fail                                                          */
      __IOM uint32_t wifi_mbist_fail : 1;       /*!< wifi_mbist_fail                                                           */
            uint32_t            : 11;
    } bit;
  } MBIST_STAT;
  __IM  uint32_t  RESERVED[6];
  
  union {
    __IOM uint32_t reg;                         /*!< bmx_cfg1.                                                                 */
    
    struct {
      __IOM uint32_t bmx_timeout_en : 4;        /*!< bmx_timeout_en                                                            */
      __IOM uint32_t bmx_arb_mode : 2;          /*!< bmx_arb_mode                                                              */
            uint32_t            : 2;
      __IOM uint32_t bmx_err_en : 1;            /*!< bmx_err_en                                                                */
      __IOM uint32_t bmx_busy_option_dis : 1;   /*!< bmx_busy_option_dis                                                       */
      __IOM uint32_t bmx_gating_dis : 1;        /*!< bmx_gating_dis                                                            */
            uint32_t            : 1;
      __IOM uint32_t hsel_option : 4;           /*!< hsel_option                                                               */
      __IOM uint32_t pds_apb_cfg : 8;           /*!< pds_apb_cfg                                                               */
      __IOM uint32_t hbn_apb_cfg : 8;           /*!< hbn_apb_cfg                                                               */
    } bit;
  } bmx_cfg1;
  
  union {
    __IOM uint32_t reg;                         /*!< bmx_cfg2.                                                                 */
    
    struct {
      __IOM uint32_t bmx_err_addr_dis : 1;      /*!< bmx_err_addr_dis                                                          */
            uint32_t            : 3;
      __IOM uint32_t bmx_err_dec : 1;           /*!< bmx_err_dec                                                               */
      __IOM uint32_t bmx_err_tz : 1;            /*!< bmx_err_tz                                                                */
            uint32_t            : 22;
      __IOM uint32_t bmx_dbg_sel : 4;           /*!< bmx_dbg_sel                                                               */
    } bit;
  } bmx_cfg2;
  
  union {
    __IOM uint32_t reg;                         /*!< bmx_err_addr.                                                             */
    
    struct {
      __IOM uint32_t bmx_err_addr : 32;         /*!< bmx_err_addr                                                              */
    } bit;
  } bmx_err_addr;
  
  union {
    __IOM uint32_t reg;                         /*!< bmx_dbg_out.                                                              */
    
    struct {
      __IOM uint32_t bmx_dbg_out : 32;          /*!< bmx_dbg_out                                                               */
    } bit;
  } bmx_dbg_out;
  
  union {
    __IOM uint32_t reg;                         /*!< rsv0.                                                                     */
    
    struct {
      __IOM uint32_t rsvd_31_0  : 32;           /*!< rsvd_31_0                                                                 */
    } bit;
  } rsv0;
  
  union {
    __IOM uint32_t reg;                         /*!< rsv1.                                                                     */
    
    struct {
      __IOM uint32_t rsvd_31_0  : 32;           /*!< rsvd_31_0                                                                 */
    } bit;
  } rsv1;
  
  union {
    __IOM uint32_t reg;                         /*!< rsv2.                                                                     */
    
    struct {
      __IOM uint32_t rsvd_31_0  : 32;           /*!< rsvd_31_0                                                                 */
    } bit;
  } rsv2;
  
  union {
    __IOM uint32_t reg;                         /*!< rsv3.                                                                     */
    
    struct {
      __IOM uint32_t rsvd_31_0  : 32;           /*!< rsvd_31_0                                                                 */
    } bit;
  } rsv3;
  
  union {
    __IOM uint32_t reg;                         /*!< sram_ret.                                                                 */
    
    struct {
      __IOM uint32_t reg_sram_ret : 32;         /*!< reg_sram_ret                                                              */
    } bit;
  } sram_ret;
  
  union {
    __IOM uint32_t reg;                         /*!< sram_slp.                                                                 */
    
    struct {
      __IOM uint32_t reg_sram_slp : 32;         /*!< reg_sram_slp                                                              */
    } bit;
  } sram_slp;
  
  union {
    __IOM uint32_t reg;                         /*!< sram_parm.                                                                */
    
    struct {
      __IOM uint32_t reg_sram_parm : 32;        /*!< reg_sram_parm                                                             */
    } bit;
  } sram_parm;
  
  union {
    __IOM uint32_t reg;                         /*!< seam_misc.                                                                */
    
    struct {
      __IOM uint32_t em_sel     : 4;            /*!< em_sel                                                                    */
            uint32_t            : 28;
    } bit;
  } seam_misc;
  
  union {
    __IOM uint32_t reg;                         /*!< glb_parm.                                                                 */
    
    struct {
      __IOM uint32_t reg_bd_en  : 1;            /*!< reg_bd_en                                                                 */
      __IOM uint32_t reg_ext_rst_smt : 1;       /*!< reg_ext_rst_smt                                                           */
      __IOM uint32_t jtag_swap_set : 6;         /*!< jtag_swap_set                                                             */
      __IOM uint32_t swap_sflash_io_3_io_0 : 1; /*!< swap_sflash_io_3_io_0                                                     */
      __IOM uint32_t sel_embedded_sflash : 1;   /*!< sel_embedded_sflash                                                       */
            uint32_t            : 2;
      __IOM uint32_t reg_spi_0_master_mode : 1; /*!< reg_spi_0_master_mode                                                     */
      __IOM uint32_t reg_spi_0_swap : 1;        /*!< reg_spi_0_swap                                                            */
            uint32_t            : 1;
      __IOM uint32_t reg_cci_use_jtag_pin : 1;  /*!< reg_cci_use_jtag_pin                                                      */
      __IOM uint32_t reg_cci_use_sdio_pin : 1;  /*!< reg_cci_use_sdio_pin                                                      */
      __IOM uint32_t p1_adc_test_with_cci : 1;  /*!< p1_adc_test_with_cci                                                      */
      __IOM uint32_t p2_dac_test_with_cci : 1;  /*!< p2_dac_test_with_cci                                                      */
      __IOM uint32_t p3_cci_use_io_2_5 : 1;     /*!< p3_cci_use_io_2_5                                                         */
      __IOM uint32_t p4_adc_test_with_jtag : 1; /*!< p4_adc_test_with_jtag                                                     */
      __IOM uint32_t p5_dac_test_with_jtag : 1; /*!< p5_dac_test_with_jtag                                                     */
      __IOM uint32_t p6_sdio_use_io_0_5 : 1;    /*!< p6_sdio_use_io_0_5                                                        */
      __IOM uint32_t p7_jtag_use_io_2_5 : 1;    /*!< p7_jtag_use_io_2_5                                                        */
      __IOM uint32_t uart_swap_set : 3;         /*!< uart_swap_set                                                             */
            uint32_t            : 5;
    } bit;
  } glb_parm;
  __IM  uint32_t  RESERVED1[3];
  
  union {
    __IOM uint32_t reg;                         /*!< CPU_CLK_CFG.                                                              */
    
    struct {
      __IOM uint32_t cpu_rtc_div : 17;          /*!< cpu_rtc_div                                                               */
            uint32_t            : 1;
      __IOM uint32_t cpu_rtc_en : 1;            /*!< cpu_rtc_en                                                                */
      __IOM uint32_t cpu_rtc_sel : 1;           /*!< cpu_rtc_sel                                                               */
      __IOM uint32_t debug_ndreset_gate : 1;    /*!< debug_ndreset_gate                                                        */
            uint32_t            : 11;
    } bit;
  } CPU_CLK_CFG;
  __IM  uint32_t  RESERVED2[4];
  
  union {
    __IOM uint32_t reg;                         /*!< GPADC_32M_SRC_CTRL.                                                       */
    
    struct {
      __IOM uint32_t gpadc_32m_clk_div : 6;     /*!< gpadc_32m_clk_div                                                         */
            uint32_t            : 1;
      __IOM uint32_t gpadc_32m_clk_sel : 1;     /*!< gpadc_32m_clk_sel                                                         */
      __IOM uint32_t gpadc_32m_div_en : 1;      /*!< gpadc_32m_div_en                                                          */
            uint32_t            : 23;
    } bit;
  } GPADC_32M_SRC_CTRL;
  
  union {
    __IOM uint32_t reg;                         /*!< DIG32K_WAKEUP_CTRL.                                                       */
    
    struct {
      __IOM uint32_t dig_32k_div : 11;          /*!< dig_32k_div                                                               */
            uint32_t            : 1;
      __IOM uint32_t dig_32k_en : 1;            /*!< dig_32k_en                                                                */
      __IOM uint32_t dig_32k_comp : 1;          /*!< dig_32k_comp                                                              */
            uint32_t            : 2;
      __IOM uint32_t dig_512k_div : 7;          /*!< dig_512k_div                                                              */
            uint32_t            : 1;
      __IOM uint32_t dig_512k_en : 1;           /*!< dig_512k_en                                                               */
      __IOM uint32_t dig_512k_comp : 1;         /*!< dig_512k_comp                                                             */
            uint32_t            : 2;
      __IOM uint32_t dig_clk_src_sel : 1;       /*!< dig_clk_src_sel                                                           */
            uint32_t            : 2;
      __IOM uint32_t reg_en_platform_wakeup : 1;/*!< reg_en_platform_wakeup                                                    */
    } bit;
  } DIG32K_WAKEUP_CTRL;
  
  union {
    __IOM uint32_t reg;                         /*!< WIFI_BT_COEX_CTRL.                                                        */
    
    struct {
      __IOM uint32_t coex_bt_channel : 7;       /*!< coex_bt_channel                                                           */
      __IOM uint32_t coex_bt_pti : 4;           /*!< coex_bt_pti                                                               */
      __IOM uint32_t coex_bt_bw : 1;            /*!< coex_bt_bw                                                                */
      __IOM uint32_t en_gpio_bt_coex : 1;       /*!< en_gpio_bt_coex                                                           */
            uint32_t            : 19;
    } bit;
  } WIFI_BT_COEX_CTRL;
  __IM  uint32_t  RESERVED3[4];
  
  union {
    __IOM uint32_t reg;                         /*!< UART_SIG_SEL_0.                                                           */
    
    struct {
      __IOM uint32_t uart_sig_0_sel : 4;        /*!< uart_sig_0_sel                                                            */
      __IOM uint32_t uart_sig_1_sel : 4;        /*!< uart_sig_1_sel                                                            */
      __IOM uint32_t uart_sig_2_sel : 4;        /*!< uart_sig_2_sel                                                            */
      __IOM uint32_t uart_sig_3_sel : 4;        /*!< uart_sig_3_sel                                                            */
      __IOM uint32_t uart_sig_4_sel : 4;        /*!< uart_sig_4_sel                                                            */
      __IOM uint32_t uart_sig_5_sel : 4;        /*!< uart_sig_5_sel                                                            */
      __IOM uint32_t uart_sig_6_sel : 4;        /*!< uart_sig_6_sel                                                            */
      __IOM uint32_t uart_sig_7_sel : 4;        /*!< uart_sig_7_sel                                                            */
    } bit;
  } UART_SIG_SEL_0;
  __IM  uint32_t  RESERVED4[3];
  
  union {
    __IOM uint32_t reg;                         /*!< DBG_SEL_LL.                                                               */
    
    struct {
      __IOM uint32_t reg_dbg_ll_ctrl : 32;      /*!< reg_dbg_ll_ctrl                                                           */
    } bit;
  } DBG_SEL_LL;
  
  union {
    __IOM uint32_t reg;                         /*!< DBG_SEL_LH.                                                               */
    
    struct {
      __IOM uint32_t reg_dbg_lh_ctrl : 32;      /*!< reg_dbg_lh_ctrl                                                           */
    } bit;
  } DBG_SEL_LH;
  
  union {
    __IOM uint32_t reg;                         /*!< DBG_SEL_HL.                                                               */
    
    struct {
      __IOM uint32_t reg_dbg_hl_ctrl : 32;      /*!< reg_dbg_hl_ctrl                                                           */
    } bit;
  } DBG_SEL_HL;
  
  union {
    __IOM uint32_t reg;                         /*!< DBG_SEL_HH.                                                               */
    
    struct {
      __IOM uint32_t reg_dbg_hh_ctrl : 32;      /*!< reg_dbg_hh_ctrl                                                           */
    } bit;
  } DBG_SEL_HH;
  
  union {
    __IOM uint32_t reg;                         /*!< debug.                                                                    */
    
    struct {
      __IOM uint32_t debug_oe   : 1;            /*!< debug_oe                                                                  */
      __IOM uint32_t debug_i    : 31;           /*!< debug_i                                                                   */
    } bit;
  } debug;
  __IM  uint32_t  RESERVED5[7];
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL0.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_0_ie : 1;         /*!< reg_gpio_0_ie                                                             */
      __IOM uint32_t reg_gpio_0_smt : 1;        /*!< reg_gpio_0_smt                                                            */
      __IOM uint32_t reg_gpio_0_drv : 2;        /*!< reg_gpio_0_drv                                                            */
      __IOM uint32_t reg_gpio_0_pu : 1;         /*!< reg_gpio_0_pu                                                             */
      __IOM uint32_t reg_gpio_0_pd : 1;         /*!< reg_gpio_0_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_0_func_sel : 4;   /*!< reg_gpio_0_func_sel                                                       */
      __IOM uint32_t real_gpio_0_func_sel : 4;  /*!< real_gpio_0_func_sel                                                      */
      __IOM uint32_t reg_gpio_1_ie : 1;         /*!< reg_gpio_1_ie                                                             */
      __IOM uint32_t reg_gpio_1_smt : 1;        /*!< reg_gpio_1_smt                                                            */
      __IOM uint32_t reg_gpio_1_drv : 2;        /*!< reg_gpio_1_drv                                                            */
      __IOM uint32_t reg_gpio_1_pu : 1;         /*!< reg_gpio_1_pu                                                             */
      __IOM uint32_t reg_gpio_1_pd : 1;         /*!< reg_gpio_1_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_1_func_sel : 4;   /*!< reg_gpio_1_func_sel                                                       */
      __IOM uint32_t real_gpio_1_func_sel : 4;  /*!< real_gpio_1_func_sel                                                      */
    } bit;
  } GPIO_CFGCTL0;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL1.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_2_ie : 1;         /*!< reg_gpio_2_ie                                                             */
      __IOM uint32_t reg_gpio_2_smt : 1;        /*!< reg_gpio_2_smt                                                            */
      __IOM uint32_t reg_gpio_2_drv : 2;        /*!< reg_gpio_2_drv                                                            */
      __IOM uint32_t reg_gpio_2_pu : 1;         /*!< reg_gpio_2_pu                                                             */
      __IOM uint32_t reg_gpio_2_pd : 1;         /*!< reg_gpio_2_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_2_func_sel : 4;   /*!< reg_gpio_2_func_sel                                                       */
      __IOM uint32_t real_gpio_2_func_sel : 4;  /*!< real_gpio_2_func_sel                                                      */
      __IOM uint32_t reg_gpio_3_ie : 1;         /*!< reg_gpio_3_ie                                                             */
      __IOM uint32_t reg_gpio_3_smt : 1;        /*!< reg_gpio_3_smt                                                            */
      __IOM uint32_t reg_gpio_3_drv : 2;        /*!< reg_gpio_3_drv                                                            */
      __IOM uint32_t reg_gpio_3_pu : 1;         /*!< reg_gpio_3_pu                                                             */
      __IOM uint32_t reg_gpio_3_pd : 1;         /*!< reg_gpio_3_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_3_func_sel : 4;   /*!< reg_gpio_3_func_sel                                                       */
      __IOM uint32_t real_gpio_3_func_sel : 4;  /*!< real_gpio_3_func_sel                                                      */
    } bit;
  } GPIO_CFGCTL1;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL2.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_4_ie : 1;         /*!< reg_gpio_4_ie                                                             */
      __IOM uint32_t reg_gpio_4_smt : 1;        /*!< reg_gpio_4_smt                                                            */
      __IOM uint32_t reg_gpio_4_drv : 2;        /*!< reg_gpio_4_drv                                                            */
      __IOM uint32_t reg_gpio_4_pu : 1;         /*!< reg_gpio_4_pu                                                             */
      __IOM uint32_t reg_gpio_4_pd : 1;         /*!< reg_gpio_4_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_4_func_sel : 4;   /*!< reg_gpio_4_func_sel                                                       */
      __IOM uint32_t real_gpio_4_func_sel : 4;  /*!< real_gpio_4_func_sel                                                      */
      __IOM uint32_t reg_gpio_5_ie : 1;         /*!< reg_gpio_5_ie                                                             */
      __IOM uint32_t reg_gpio_5_smt : 1;        /*!< reg_gpio_5_smt                                                            */
      __IOM uint32_t reg_gpio_5_drv : 2;        /*!< reg_gpio_5_drv                                                            */
      __IOM uint32_t reg_gpio_5_pu : 1;         /*!< reg_gpio_5_pu                                                             */
      __IOM uint32_t reg_gpio_5_pd : 1;         /*!< reg_gpio_5_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_5_func_sel : 4;   /*!< reg_gpio_5_func_sel                                                       */
      __IOM uint32_t real_gpio_5_func_sel : 4;  /*!< real_gpio_5_func_sel                                                      */
    } bit;
  } GPIO_CFGCTL2;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL3.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_6_ie : 1;         /*!< reg_gpio_6_ie                                                             */
      __IOM uint32_t reg_gpio_6_smt : 1;        /*!< reg_gpio_6_smt                                                            */
      __IOM uint32_t reg_gpio_6_drv : 2;        /*!< reg_gpio_6_drv                                                            */
      __IOM uint32_t reg_gpio_6_pu : 1;         /*!< reg_gpio_6_pu                                                             */
      __IOM uint32_t reg_gpio_6_pd : 1;         /*!< reg_gpio_6_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_6_func_sel : 4;   /*!< reg_gpio_6_func_sel                                                       */
            uint32_t            : 4;
      __IOM uint32_t reg_gpio_7_ie : 1;         /*!< reg_gpio_7_ie                                                             */
      __IOM uint32_t reg_gpio_7_smt : 1;        /*!< reg_gpio_7_smt                                                            */
      __IOM uint32_t reg_gpio_7_drv : 2;        /*!< reg_gpio_7_drv                                                            */
      __IOM uint32_t reg_gpio_7_pu : 1;         /*!< reg_gpio_7_pu                                                             */
      __IOM uint32_t reg_gpio_7_pd : 1;         /*!< reg_gpio_7_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_7_func_sel : 4;   /*!< reg_gpio_7_func_sel                                                       */
            uint32_t            : 4;
    } bit;
  } GPIO_CFGCTL3;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL4.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_8_ie : 1;         /*!< reg_gpio_8_ie                                                             */
      __IOM uint32_t reg_gpio_8_smt : 1;        /*!< reg_gpio_8_smt                                                            */
      __IOM uint32_t reg_gpio_8_drv : 2;        /*!< reg_gpio_8_drv                                                            */
      __IOM uint32_t reg_gpio_8_pu : 1;         /*!< reg_gpio_8_pu                                                             */
      __IOM uint32_t reg_gpio_8_pd : 1;         /*!< reg_gpio_8_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_8_func_sel : 4;   /*!< reg_gpio_8_func_sel                                                       */
            uint32_t            : 4;
      __IOM uint32_t reg_gpio_9_ie : 1;         /*!< reg_gpio_9_ie                                                             */
      __IOM uint32_t reg_gpio_9_smt : 1;        /*!< reg_gpio_9_smt                                                            */
      __IOM uint32_t reg_gpio_9_drv : 2;        /*!< reg_gpio_9_drv                                                            */
      __IOM uint32_t reg_gpio_9_pu : 1;         /*!< reg_gpio_9_pu                                                             */
      __IOM uint32_t reg_gpio_9_pd : 1;         /*!< reg_gpio_9_pd                                                             */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_9_func_sel : 4;   /*!< reg_gpio_9_func_sel                                                       */
            uint32_t            : 4;
    } bit;
  } GPIO_CFGCTL4;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL5.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_10_ie : 1;        /*!< reg_gpio_10_ie                                                            */
      __IOM uint32_t reg_gpio_10_smt : 1;       /*!< reg_gpio_10_smt                                                           */
      __IOM uint32_t reg_gpio_10_drv : 2;       /*!< reg_gpio_10_drv                                                           */
      __IOM uint32_t reg_gpio_10_pu : 1;        /*!< reg_gpio_10_pu                                                            */
      __IOM uint32_t reg_gpio_10_pd : 1;        /*!< reg_gpio_10_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_10_func_sel : 4;  /*!< reg_gpio_10_func_sel                                                      */
            uint32_t            : 4;
      __IOM uint32_t reg_gpio_11_ie : 1;        /*!< reg_gpio_11_ie                                                            */
      __IOM uint32_t reg_gpio_11_smt : 1;       /*!< reg_gpio_11_smt                                                           */
      __IOM uint32_t reg_gpio_11_drv : 2;       /*!< reg_gpio_11_drv                                                           */
      __IOM uint32_t reg_gpio_11_pu : 1;        /*!< reg_gpio_11_pu                                                            */
      __IOM uint32_t reg_gpio_11_pd : 1;        /*!< reg_gpio_11_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_11_func_sel : 4;  /*!< reg_gpio_11_func_sel                                                      */
            uint32_t            : 4;
    } bit;
  } GPIO_CFGCTL5;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL6.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_12_ie : 1;        /*!< reg_gpio_12_ie                                                            */
      __IOM uint32_t reg_gpio_12_smt : 1;       /*!< reg_gpio_12_smt                                                           */
      __IOM uint32_t reg_gpio_12_drv : 2;       /*!< reg_gpio_12_drv                                                           */
      __IOM uint32_t reg_gpio_12_pu : 1;        /*!< reg_gpio_12_pu                                                            */
      __IOM uint32_t reg_gpio_12_pd : 1;        /*!< reg_gpio_12_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_12_func_sel : 4;  /*!< reg_gpio_12_func_sel                                                      */
            uint32_t            : 4;
      __IOM uint32_t reg_gpio_13_ie : 1;        /*!< reg_gpio_13_ie                                                            */
      __IOM uint32_t reg_gpio_13_smt : 1;       /*!< reg_gpio_13_smt                                                           */
      __IOM uint32_t reg_gpio_13_drv : 2;       /*!< reg_gpio_13_drv                                                           */
      __IOM uint32_t reg_gpio_13_pu : 1;        /*!< reg_gpio_13_pu                                                            */
      __IOM uint32_t reg_gpio_13_pd : 1;        /*!< reg_gpio_13_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_13_func_sel : 4;  /*!< reg_gpio_13_func_sel                                                      */
            uint32_t            : 4;
    } bit;
  } GPIO_CFGCTL6;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL7.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_14_ie : 1;        /*!< reg_gpio_14_ie                                                            */
      __IOM uint32_t reg_gpio_14_smt : 1;       /*!< reg_gpio_14_smt                                                           */
      __IOM uint32_t reg_gpio_14_drv : 2;       /*!< reg_gpio_14_drv                                                           */
      __IOM uint32_t reg_gpio_14_pu : 1;        /*!< reg_gpio_14_pu                                                            */
      __IOM uint32_t reg_gpio_14_pd : 1;        /*!< reg_gpio_14_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_14_func_sel : 4;  /*!< reg_gpio_14_func_sel                                                      */
            uint32_t            : 4;
      __IOM uint32_t reg_gpio_15_ie : 1;        /*!< reg_gpio_15_ie                                                            */
      __IOM uint32_t reg_gpio_15_smt : 1;       /*!< reg_gpio_15_smt                                                           */
      __IOM uint32_t reg_gpio_15_drv : 2;       /*!< reg_gpio_15_drv                                                           */
      __IOM uint32_t reg_gpio_15_pu : 1;        /*!< reg_gpio_15_pu                                                            */
      __IOM uint32_t reg_gpio_15_pd : 1;        /*!< reg_gpio_15_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_15_func_sel : 4;  /*!< reg_gpio_15_func_sel                                                      */
            uint32_t            : 4;
    } bit;
  } GPIO_CFGCTL7;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL8.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_16_ie : 1;        /*!< reg_gpio_16_ie                                                            */
      __IOM uint32_t reg_gpio_16_smt : 1;       /*!< reg_gpio_16_smt                                                           */
      __IOM uint32_t reg_gpio_16_drv : 2;       /*!< reg_gpio_16_drv                                                           */
      __IOM uint32_t reg_gpio_16_pu : 1;        /*!< reg_gpio_16_pu                                                            */
      __IOM uint32_t reg_gpio_16_pd : 1;        /*!< reg_gpio_16_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_16_func_sel : 4;  /*!< reg_gpio_16_func_sel                                                      */
            uint32_t            : 4;
      __IOM uint32_t reg_gpio_17_ie : 1;        /*!< reg_gpio_17_ie                                                            */
      __IOM uint32_t reg_gpio_17_smt : 1;       /*!< reg_gpio_17_smt                                                           */
      __IOM uint32_t reg_gpio_17_drv : 2;       /*!< reg_gpio_17_drv                                                           */
      __IOM uint32_t reg_gpio_17_pu : 1;        /*!< reg_gpio_17_pu                                                            */
      __IOM uint32_t reg_gpio_17_pd : 1;        /*!< reg_gpio_17_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_17_func_sel : 4;  /*!< reg_gpio_17_func_sel                                                      */
            uint32_t            : 4;
    } bit;
  } GPIO_CFGCTL8;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL9.                                                             */
    
    struct {
      __IOM uint32_t reg_gpio_18_ie : 1;        /*!< reg_gpio_18_ie                                                            */
      __IOM uint32_t reg_gpio_18_smt : 1;       /*!< reg_gpio_18_smt                                                           */
      __IOM uint32_t reg_gpio_18_drv : 2;       /*!< reg_gpio_18_drv                                                           */
      __IOM uint32_t reg_gpio_18_pu : 1;        /*!< reg_gpio_18_pu                                                            */
      __IOM uint32_t reg_gpio_18_pd : 1;        /*!< reg_gpio_18_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_18_func_sel : 4;  /*!< reg_gpio_18_func_sel                                                      */
            uint32_t            : 4;
      __IOM uint32_t reg_gpio_19_ie : 1;        /*!< reg_gpio_19_ie                                                            */
      __IOM uint32_t reg_gpio_19_smt : 1;       /*!< reg_gpio_19_smt                                                           */
      __IOM uint32_t reg_gpio_19_drv : 2;       /*!< reg_gpio_19_drv                                                           */
      __IOM uint32_t reg_gpio_19_pu : 1;        /*!< reg_gpio_19_pu                                                            */
      __IOM uint32_t reg_gpio_19_pd : 1;        /*!< reg_gpio_19_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_19_func_sel : 4;  /*!< reg_gpio_19_func_sel                                                      */
            uint32_t            : 4;
    } bit;
  } GPIO_CFGCTL9;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL10.                                                            */
    
    struct {
      __IOM uint32_t reg_gpio_20_ie : 1;        /*!< reg_gpio_20_ie                                                            */
      __IOM uint32_t reg_gpio_20_smt : 1;       /*!< reg_gpio_20_smt                                                           */
      __IOM uint32_t reg_gpio_20_drv : 2;       /*!< reg_gpio_20_drv                                                           */
      __IOM uint32_t reg_gpio_20_pu : 1;        /*!< reg_gpio_20_pu                                                            */
      __IOM uint32_t reg_gpio_20_pd : 1;        /*!< reg_gpio_20_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_20_func_sel : 4;  /*!< reg_gpio_20_func_sel                                                      */
            uint32_t            : 4;
      __IOM uint32_t reg_gpio_21_ie : 1;        /*!< reg_gpio_21_ie                                                            */
      __IOM uint32_t reg_gpio_21_smt : 1;       /*!< reg_gpio_21_smt                                                           */
      __IOM uint32_t reg_gpio_21_drv : 2;       /*!< reg_gpio_21_drv                                                           */
      __IOM uint32_t reg_gpio_21_pu : 1;        /*!< reg_gpio_21_pu                                                            */
      __IOM uint32_t reg_gpio_21_pd : 1;        /*!< reg_gpio_21_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_21_func_sel : 4;  /*!< reg_gpio_21_func_sel                                                      */
            uint32_t            : 4;
    } bit;
  } GPIO_CFGCTL10;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL11.                                                            */
    
    struct {
      __IOM uint32_t reg_gpio_22_ie : 1;        /*!< reg_gpio_22_ie                                                            */
      __IOM uint32_t reg_gpio_22_smt : 1;       /*!< reg_gpio_22_smt                                                           */
      __IOM uint32_t reg_gpio_22_drv : 2;       /*!< reg_gpio_22_drv                                                           */
      __IOM uint32_t reg_gpio_22_pu : 1;        /*!< reg_gpio_22_pu                                                            */
      __IOM uint32_t reg_gpio_22_pd : 1;        /*!< reg_gpio_22_pd                                                            */
            uint32_t            : 2;
      __IOM uint32_t reg_gpio_22_func_sel : 4;  /*!< reg_gpio_22_func_sel                                                      */
            uint32_t            : 4;
      __IOM uint32_t reg_gpio_23_ie : 1;        /*!< reg_gpio_23_ie                                                            */
      __IOM uint32_t reg_gpio_23_smt : 1;       /*!< reg_gpio_23_smt                                                           */
      __IOM uint32_t reg_gpio_23_drv : 2;       /*!< reg_gpio_23_drv                                                           */
      __IOM uint32_t reg_gpio_23_pu : 1;        /*!< reg_gpio_23_pu                                                            */
      __IOM uint32_t reg_gpio_23_pd : 1;        /*!< reg_gpio_23_pd                                                            */
            uint32_t            : 10;
    } bit;
  } GPIO_CFGCTL11;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL12.                                                            */
    
    struct {
      __IOM uint32_t reg_gpio_24_ie : 1;        /*!< reg_gpio_24_ie                                                            */
      __IOM uint32_t reg_gpio_24_smt : 1;       /*!< reg_gpio_24_smt                                                           */
      __IOM uint32_t reg_gpio_24_drv : 2;       /*!< reg_gpio_24_drv                                                           */
      __IOM uint32_t reg_gpio_24_pu : 1;        /*!< reg_gpio_24_pu                                                            */
      __IOM uint32_t reg_gpio_24_pd : 1;        /*!< reg_gpio_24_pd                                                            */
            uint32_t            : 10;
      __IOM uint32_t reg_gpio_25_ie : 1;        /*!< reg_gpio_25_ie                                                            */
      __IOM uint32_t reg_gpio_25_smt : 1;       /*!< reg_gpio_25_smt                                                           */
      __IOM uint32_t reg_gpio_25_drv : 2;       /*!< reg_gpio_25_drv                                                           */
      __IOM uint32_t reg_gpio_25_pu : 1;        /*!< reg_gpio_25_pu                                                            */
      __IOM uint32_t reg_gpio_25_pd : 1;        /*!< reg_gpio_25_pd                                                            */
            uint32_t            : 10;
    } bit;
  } GPIO_CFGCTL12;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL13.                                                            */
    
    struct {
      __IOM uint32_t reg_gpio_26_ie : 1;        /*!< reg_gpio_26_ie                                                            */
      __IOM uint32_t reg_gpio_26_smt : 1;       /*!< reg_gpio_26_smt                                                           */
      __IOM uint32_t reg_gpio_26_drv : 2;       /*!< reg_gpio_26_drv                                                           */
      __IOM uint32_t reg_gpio_26_pu : 1;        /*!< reg_gpio_26_pu                                                            */
      __IOM uint32_t reg_gpio_26_pd : 1;        /*!< reg_gpio_26_pd                                                            */
            uint32_t            : 10;
      __IOM uint32_t reg_gpio_27_ie : 1;        /*!< reg_gpio_27_ie                                                            */
      __IOM uint32_t reg_gpio_27_smt : 1;       /*!< reg_gpio_27_smt                                                           */
      __IOM uint32_t reg_gpio_27_drv : 2;       /*!< reg_gpio_27_drv                                                           */
      __IOM uint32_t reg_gpio_27_pu : 1;        /*!< reg_gpio_27_pu                                                            */
      __IOM uint32_t reg_gpio_27_pd : 1;        /*!< reg_gpio_27_pd                                                            */
            uint32_t            : 10;
    } bit;
  } GPIO_CFGCTL13;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL14.                                                            */
    
    struct {
      __IOM uint32_t reg_gpio_28_ie : 1;        /*!< reg_gpio_28_ie                                                            */
      __IOM uint32_t reg_gpio_28_smt : 1;       /*!< reg_gpio_28_smt                                                           */
      __IOM uint32_t reg_gpio_28_drv : 2;       /*!< reg_gpio_28_drv                                                           */
      __IOM uint32_t reg_gpio_28_pu : 1;        /*!< reg_gpio_28_pu                                                            */
      __IOM uint32_t reg_gpio_28_pd : 1;        /*!< reg_gpio_28_pd                                                            */
            uint32_t            : 26;
    } bit;
  } GPIO_CFGCTL14;
  __IM  uint32_t  RESERVED6[17];
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL30.                                                            */
    
    struct {
      __IOM uint32_t reg_gpio_0_i : 1;          /*!< reg_gpio_0_i                                                              */
      __IOM uint32_t reg_gpio_1_i : 1;          /*!< reg_gpio_1_i                                                              */
      __IOM uint32_t reg_gpio_2_i : 1;          /*!< reg_gpio_2_i                                                              */
      __IOM uint32_t reg_gpio_3_i : 1;          /*!< reg_gpio_3_i                                                              */
      __IOM uint32_t reg_gpio_4_i : 1;          /*!< reg_gpio_4_i                                                              */
      __IOM uint32_t reg_gpio_5_i : 1;          /*!< reg_gpio_5_i                                                              */
      __IOM uint32_t reg_gpio_6_i : 1;          /*!< reg_gpio_6_i                                                              */
      __IOM uint32_t reg_gpio_7_i : 1;          /*!< reg_gpio_7_i                                                              */
      __IOM uint32_t reg_gpio_8_i : 1;          /*!< reg_gpio_8_i                                                              */
      __IOM uint32_t reg_gpio_9_i : 1;          /*!< reg_gpio_9_i                                                              */
      __IOM uint32_t reg_gpio_10_i : 1;         /*!< reg_gpio_10_i                                                             */
      __IOM uint32_t reg_gpio_11_i : 1;         /*!< reg_gpio_11_i                                                             */
      __IOM uint32_t reg_gpio_12_i : 1;         /*!< reg_gpio_12_i                                                             */
      __IOM uint32_t reg_gpio_13_i : 1;         /*!< reg_gpio_13_i                                                             */
      __IOM uint32_t reg_gpio_14_i : 1;         /*!< reg_gpio_14_i                                                             */
      __IOM uint32_t reg_gpio_15_i : 1;         /*!< reg_gpio_15_i                                                             */
      __IOM uint32_t reg_gpio_16_i : 1;         /*!< reg_gpio_16_i                                                             */
      __IOM uint32_t reg_gpio_17_i : 1;         /*!< reg_gpio_17_i                                                             */
      __IOM uint32_t reg_gpio_18_i : 1;         /*!< reg_gpio_18_i                                                             */
      __IOM uint32_t reg_gpio_19_i : 1;         /*!< reg_gpio_19_i                                                             */
      __IOM uint32_t reg_gpio_20_i : 1;         /*!< reg_gpio_20_i                                                             */
      __IOM uint32_t reg_gpio_21_i : 1;         /*!< reg_gpio_21_i                                                             */
      __IOM uint32_t reg_gpio_22_i : 1;         /*!< reg_gpio_22_i                                                             */
            uint32_t            : 9;
    } bit;
  } GPIO_CFGCTL30;
  __IOM uint32_t  GPIO_CFGCTL31;                /*!< GPIO_CFGCTL31.                                                            */
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL32.                                                            */
    
    struct {
      __IOM uint32_t reg_gpio_0_o : 1;          /*!< reg_gpio_0_o                                                              */
      __IOM uint32_t reg_gpio_1_o : 1;          /*!< reg_gpio_1_o                                                              */
      __IOM uint32_t reg_gpio_2_o : 1;          /*!< reg_gpio_2_o                                                              */
      __IOM uint32_t reg_gpio_3_o : 1;          /*!< reg_gpio_3_o                                                              */
      __IOM uint32_t reg_gpio_4_o : 1;          /*!< reg_gpio_4_o                                                              */
      __IOM uint32_t reg_gpio_5_o : 1;          /*!< reg_gpio_5_o                                                              */
      __IOM uint32_t reg_gpio_6_o : 1;          /*!< reg_gpio_6_o                                                              */
      __IOM uint32_t reg_gpio_7_o : 1;          /*!< reg_gpio_7_o                                                              */
      __IOM uint32_t reg_gpio_8_o : 1;          /*!< reg_gpio_8_o                                                              */
      __IOM uint32_t reg_gpio_9_o : 1;          /*!< reg_gpio_9_o                                                              */
      __IOM uint32_t reg_gpio_10_o : 1;         /*!< reg_gpio_10_o                                                             */
      __IOM uint32_t reg_gpio_11_o : 1;         /*!< reg_gpio_11_o                                                             */
      __IOM uint32_t reg_gpio_12_o : 1;         /*!< reg_gpio_12_o                                                             */
      __IOM uint32_t reg_gpio_13_o : 1;         /*!< reg_gpio_13_o                                                             */
      __IOM uint32_t reg_gpio_14_o : 1;         /*!< reg_gpio_14_o                                                             */
      __IOM uint32_t reg_gpio_15_o : 1;         /*!< reg_gpio_15_o                                                             */
      __IOM uint32_t reg_gpio_16_o : 1;         /*!< reg_gpio_16_o                                                             */
      __IOM uint32_t reg_gpio_17_o : 1;         /*!< reg_gpio_17_o                                                             */
      __IOM uint32_t reg_gpio_18_o : 1;         /*!< reg_gpio_18_o                                                             */
      __IOM uint32_t reg_gpio_19_o : 1;         /*!< reg_gpio_19_o                                                             */
      __IOM uint32_t reg_gpio_20_o : 1;         /*!< reg_gpio_20_o                                                             */
      __IOM uint32_t reg_gpio_21_o : 1;         /*!< reg_gpio_21_o                                                             */
      __IOM uint32_t reg_gpio_22_o : 1;         /*!< reg_gpio_22_o                                                             */
            uint32_t            : 9;
    } bit;
  } GPIO_CFGCTL32;
  __IOM uint32_t  GPIO_CFGCTL33;                /*!< GPIO_CFGCTL33.                                                            */
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_CFGCTL34.                                                            */
    
    struct {
      __IOM uint32_t reg_gpio_0_oe : 1;         /*!< reg_gpio_0_oe                                                             */
      __IOM uint32_t reg_gpio_1_oe : 1;         /*!< reg_gpio_1_oe                                                             */
      __IOM uint32_t reg_gpio_2_oe : 1;         /*!< reg_gpio_2_oe                                                             */
      __IOM uint32_t reg_gpio_3_oe : 1;         /*!< reg_gpio_3_oe                                                             */
      __IOM uint32_t reg_gpio_4_oe : 1;         /*!< reg_gpio_4_oe                                                             */
      __IOM uint32_t reg_gpio_5_oe : 1;         /*!< reg_gpio_5_oe                                                             */
      __IOM uint32_t reg_gpio_6_oe : 1;         /*!< reg_gpio_6_oe                                                             */
      __IOM uint32_t reg_gpio_7_oe : 1;         /*!< reg_gpio_7_oe                                                             */
      __IOM uint32_t reg_gpio_8_oe : 1;         /*!< reg_gpio_8_oe                                                             */
      __IOM uint32_t reg_gpio_9_oe : 1;         /*!< reg_gpio_9_oe                                                             */
      __IOM uint32_t reg_gpio_10_oe : 1;        /*!< reg_gpio_10_oe                                                            */
      __IOM uint32_t reg_gpio_11_oe : 1;        /*!< reg_gpio_11_oe                                                            */
      __IOM uint32_t reg_gpio_12_oe : 1;        /*!< reg_gpio_12_oe                                                            */
      __IOM uint32_t reg_gpio_13_oe : 1;        /*!< reg_gpio_13_oe                                                            */
      __IOM uint32_t reg_gpio_14_oe : 1;        /*!< reg_gpio_14_oe                                                            */
      __IOM uint32_t reg_gpio_15_oe : 1;        /*!< reg_gpio_15_oe                                                            */
      __IOM uint32_t reg_gpio_16_oe : 1;        /*!< reg_gpio_16_oe                                                            */
      __IOM uint32_t reg_gpio_17_oe : 1;        /*!< reg_gpio_17_oe                                                            */
      __IOM uint32_t reg_gpio_18_oe : 1;        /*!< reg_gpio_18_oe                                                            */
      __IOM uint32_t reg_gpio_19_oe : 1;        /*!< reg_gpio_19_oe                                                            */
      __IOM uint32_t reg_gpio_20_oe : 1;        /*!< reg_gpio_20_oe                                                            */
      __IOM uint32_t reg_gpio_21_oe : 1;        /*!< reg_gpio_21_oe                                                            */
      __IOM uint32_t reg_gpio_22_oe : 1;        /*!< reg_gpio_22_oe                                                            */
            uint32_t            : 9;
    } bit;
  } GPIO_CFGCTL34;
  __IOM uint32_t  GPIO_CFGCTL35;                /*!< GPIO_CFGCTL35.                                                            */
  __IM  uint32_t  RESERVED7[2];
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_INT_MASK1.                                                           */
    
    struct {
      __IOM uint32_t reg_gpio_int_mask1 : 32;   /*!< reg_gpio_int_mask1                                                        */
    } bit;
  } GPIO_INT_MASK1;
  __IM  uint32_t  RESERVED8;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_INT_STAT1.                                                           */
    
    struct {
      __IOM uint32_t gpio_int_stat1 : 32;       /*!< gpio_int_stat1                                                            */
    } bit;
  } GPIO_INT_STAT1;
  __IM  uint32_t  RESERVED9;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_INT_CLR1.                                                            */
    
    struct {
      __IOM uint32_t reg_gpio_int_clr1 : 32;    /*!< reg_gpio_int_clr1                                                         */
    } bit;
  } GPIO_INT_CLR1;
  __IM  uint32_t  RESERVED10[3];
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_INT_MODE_SET1.                                                       */
    
    struct {
      __IOM uint32_t reg_gpio_int_mode_set1 : 32;/*!< reg_gpio_int_mode_set1                                                   */
    } bit;
  } GPIO_INT_MODE_SET1;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_INT_MODE_SET2.                                                       */
    
    struct {
      __IOM uint32_t reg_gpio_int_mode_set2 : 32;/*!< reg_gpio_int_mode_set2                                                   */
    } bit;
  } GPIO_INT_MODE_SET2;
  
  union {
    __IOM uint32_t reg;                         /*!< GPIO_INT_MODE_SET3.                                                       */
    
    struct {
      __IOM uint32_t reg_gpio_int_mode_set3 : 32;/*!< reg_gpio_int_mode_set3                                                   */
    } bit;
  } GPIO_INT_MODE_SET3;
  __IM  uint32_t  RESERVED11[22];
  
  union {
    __IOM uint32_t reg;                         /*!< led_driver.                                                               */
    
    struct {
      __IOM uint32_t led_din_reg : 1;           /*!< led_din_reg                                                               */
      __IOM uint32_t led_din_sel : 1;           /*!< led_din_sel                                                               */
      __IOM uint32_t led_din_polarity_sel : 1;  /*!< led_din_polarity_sel                                                      */
            uint32_t            : 1;
      __IOM uint32_t leddrv_ibias : 4;          /*!< leddrv_ibias                                                              */
      __IOM uint32_t ir_rx_gpio_sel : 2;        /*!< ir_rx_gpio_sel                                                            */
            uint32_t            : 21;
      __IOM uint32_t pu_leddrv  : 1;            /*!< pu_leddrv                                                                 */
    } bit;
  } led_driver;
  __IM  uint32_t  RESERVED12[56];
  
  union {
    __IOM uint32_t reg;                         /*!< gpdac_ctrl.                                                               */
    
    struct {
      __IOM uint32_t gpdaca_rstn_ana : 1;       /*!< gpdaca_rstn_ana                                                           */
      __IOM uint32_t gpdacb_rstn_ana : 1;       /*!< gpdacb_rstn_ana                                                           */
            uint32_t            : 5;
      __IOM uint32_t gpdac_test_en : 1;         /*!< gpdac_test_en                                                             */
      __IOM uint32_t gpdac_ref_sel : 1;         /*!< gpdac_ref_sel                                                             */
      __IOM uint32_t gpdac_test_sel : 3;        /*!< gpdac_test_sel                                                            */
            uint32_t            : 12;
      __IOM uint32_t gpdac_reserved : 8;        /*!< gpdac_reserved                                                            */
    } bit;
  } gpdac_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< gpdac_actrl.                                                              */
    
    struct {
      __IOM uint32_t gpdac_a_en : 1;            /*!< gpdac_a_en                                                                */
      __IOM uint32_t gpdac_ioa_en : 1;          /*!< gpdac_ioa_en                                                              */
            uint32_t            : 16;
      __IOM uint32_t gpdac_a_rng : 2;           /*!< gpdac_a_rng                                                               */
      __IOM uint32_t gpdac_a_outmux : 3;        /*!< gpdac_a_outmux                                                            */
            uint32_t            : 9;
    } bit;
  } gpdac_actrl;
  
  union {
    __IOM uint32_t reg;                         /*!< gpdac_bctrl.                                                              */
    
    struct {
      __IOM uint32_t gpdac_b_en : 1;            /*!< gpdac_b_en                                                                */
      __IOM uint32_t gpdac_iob_en : 1;          /*!< gpdac_iob_en                                                              */
            uint32_t            : 16;
      __IOM uint32_t gpdac_b_rng : 2;           /*!< gpdac_b_rng                                                               */
      __IOM uint32_t gpdac_b_outmux : 3;        /*!< gpdac_b_outmux                                                            */
            uint32_t            : 9;
    } bit;
  } gpdac_bctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< gpdac_data.                                                               */
    
    struct {
      __IOM uint32_t gpdac_b_data : 10;         /*!< gpdac_b_data                                                              */
            uint32_t            : 6;
      __IOM uint32_t gpdac_a_data : 10;         /*!< gpdac_a_data                                                              */
            uint32_t            : 6;
    } bit;
  } gpdac_data;
  __IM  uint32_t  RESERVED13[762];
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_glb_ctrl_0.                                                           */
    
    struct {
      __IOM uint32_t tzc_glb_swrst_s00_lock : 1;/*!< tzc_glb_swrst_s00_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s01_lock : 1;/*!< tzc_glb_swrst_s01_lock                                                    */
            uint32_t            : 6;
      __IOM uint32_t tzc_glb_swrst_s30_lock : 1;/*!< tzc_glb_swrst_s30_lock                                                    */
            uint32_t            : 3;
      __IOM uint32_t tzc_glb_ctrl_pwron_rst_lock : 1;/*!< tzc_glb_ctrl_pwron_rst_lock                                          */
      __IOM uint32_t tzc_glb_ctrl_cpu_reset_lock : 1;/*!< tzc_glb_ctrl_cpu_reset_lock                                          */
      __IOM uint32_t tzc_glb_ctrl_sys_reset_lock : 1;/*!< tzc_glb_ctrl_sys_reset_lock                                          */
      __IOM uint32_t tzc_glb_ctrl_ungated_ap_lock : 1;/*!< tzc_glb_ctrl_ungated_ap_lock                                        */
            uint32_t            : 9;
      __IOM uint32_t tzc_glb_misc_lock : 1;     /*!< tzc_glb_misc_lock                                                         */
      __IOM uint32_t tzc_glb_sram_lock : 1;     /*!< tzc_glb_sram_lock                                                         */
      __IOM uint32_t tzc_glb_l2c_lock : 1;      /*!< tzc_glb_l2c_lock                                                          */
      __IOM uint32_t tzc_glb_bmx_lock : 1;      /*!< tzc_glb_bmx_lock                                                          */
      __IOM uint32_t tzc_glb_dbg_lock : 1;      /*!< tzc_glb_dbg_lock                                                          */
      __IOM uint32_t tzc_glb_mbist_lock : 1;    /*!< tzc_glb_mbist_lock                                                        */
      __IOM uint32_t tzc_glb_clk_lock : 1;      /*!< tzc_glb_clk_lock                                                          */
    } bit;
  } tzc_glb_ctrl_0;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_glb_ctrl_1.                                                           */
    
    struct {
      __IOM uint32_t tzc_glb_swrst_s20_lock : 1;/*!< tzc_glb_swrst_s20_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s21_lock : 1;/*!< tzc_glb_swrst_s21_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s22_lock : 1;/*!< tzc_glb_swrst_s22_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s23_lock : 1;/*!< tzc_glb_swrst_s23_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s24_lock : 1;/*!< tzc_glb_swrst_s24_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s25_lock : 1;/*!< tzc_glb_swrst_s25_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s26_lock : 1;/*!< tzc_glb_swrst_s26_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s27_lock : 1;/*!< tzc_glb_swrst_s27_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s28_lock : 1;/*!< tzc_glb_swrst_s28_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s29_lock : 1;/*!< tzc_glb_swrst_s29_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s2a_lock : 1;/*!< tzc_glb_swrst_s2a_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s2b_lock : 1;/*!< tzc_glb_swrst_s2b_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s2c_lock : 1;/*!< tzc_glb_swrst_s2c_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s2d_lock : 1;/*!< tzc_glb_swrst_s2d_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s2e_lock : 1;/*!< tzc_glb_swrst_s2e_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s2f_lock : 1;/*!< tzc_glb_swrst_s2f_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s10_lock : 1;/*!< tzc_glb_swrst_s10_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s11_lock : 1;/*!< tzc_glb_swrst_s11_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s12_lock : 1;/*!< tzc_glb_swrst_s12_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s13_lock : 1;/*!< tzc_glb_swrst_s13_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s14_lock : 1;/*!< tzc_glb_swrst_s14_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s15_lock : 1;/*!< tzc_glb_swrst_s15_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s16_lock : 1;/*!< tzc_glb_swrst_s16_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s17_lock : 1;/*!< tzc_glb_swrst_s17_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s18_lock : 1;/*!< tzc_glb_swrst_s18_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s19_lock : 1;/*!< tzc_glb_swrst_s19_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s1a_lock : 1;/*!< tzc_glb_swrst_s1a_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s1b_lock : 1;/*!< tzc_glb_swrst_s1b_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s1c_lock : 1;/*!< tzc_glb_swrst_s1c_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s1d_lock : 1;/*!< tzc_glb_swrst_s1d_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s1e_lock : 1;/*!< tzc_glb_swrst_s1e_lock                                                    */
      __IOM uint32_t tzc_glb_swrst_s1f_lock : 1;/*!< tzc_glb_swrst_s1f_lock                                                    */
    } bit;
  } tzc_glb_ctrl_1;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_glb_ctrl_2.                                                           */
    
    struct {
      __IOM uint32_t tzc_glb_gpio_0_lock : 1;   /*!< tzc_glb_gpio_0_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_1_lock : 1;   /*!< tzc_glb_gpio_1_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_2_lock : 1;   /*!< tzc_glb_gpio_2_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_3_lock : 1;   /*!< tzc_glb_gpio_3_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_4_lock : 1;   /*!< tzc_glb_gpio_4_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_5_lock : 1;   /*!< tzc_glb_gpio_5_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_6_lock : 1;   /*!< tzc_glb_gpio_6_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_7_lock : 1;   /*!< tzc_glb_gpio_7_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_8_lock : 1;   /*!< tzc_glb_gpio_8_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_9_lock : 1;   /*!< tzc_glb_gpio_9_lock                                                       */
      __IOM uint32_t tzc_glb_gpio_10_lock : 1;  /*!< tzc_glb_gpio_10_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_11_lock : 1;  /*!< tzc_glb_gpio_11_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_12_lock : 1;  /*!< tzc_glb_gpio_12_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_13_lock : 1;  /*!< tzc_glb_gpio_13_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_14_lock : 1;  /*!< tzc_glb_gpio_14_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_15_lock : 1;  /*!< tzc_glb_gpio_15_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_16_lock : 1;  /*!< tzc_glb_gpio_16_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_17_lock : 1;  /*!< tzc_glb_gpio_17_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_18_lock : 1;  /*!< tzc_glb_gpio_18_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_19_lock : 1;  /*!< tzc_glb_gpio_19_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_20_lock : 1;  /*!< tzc_glb_gpio_20_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_21_lock : 1;  /*!< tzc_glb_gpio_21_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_22_lock : 1;  /*!< tzc_glb_gpio_22_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_23_lock : 1;  /*!< tzc_glb_gpio_23_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_24_lock : 1;  /*!< tzc_glb_gpio_24_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_25_lock : 1;  /*!< tzc_glb_gpio_25_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_26_lock : 1;  /*!< tzc_glb_gpio_26_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_27_lock : 1;  /*!< tzc_glb_gpio_27_lock                                                      */
      __IOM uint32_t tzc_glb_gpio_28_lock : 1;  /*!< tzc_glb_gpio_28_lock                                                      */
            uint32_t            : 3;
    } bit;
  } tzc_glb_ctrl_2;
  __IOM uint32_t  tzc_glb_ctrl_3;               /*!< tzc_glb_ctrl_3.                                                           */
} glb_Type;                                     /*!< Size = 3856 (0xf10)                                                       */

#define glb_BASE                    0x40000000UL

#define glb                         ((glb_Type*)               glb_BASE)

#ifdef __cplusplus
}
#endif

#endif

#endif /* BL602_H */
