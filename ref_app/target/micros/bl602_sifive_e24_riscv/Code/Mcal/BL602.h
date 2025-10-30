
#ifndef BL602_H
#define BL602_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stdint.h"

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
/* ================                                      CLIC Defines                                         ================ */
/* =========================================================================================================================== */
#define CLIC_CTRL_ADDR      0x02000000UL
#define CLIC_MSIP           *(volatile uint32_t*)(CLIC_CTRL_ADDR + 0x0000UL)
#define CLIC_MTIMECMP       *(volatile uint64_t*)(CLIC_CTRL_ADDR + 0x4000UL)
#define CLIC_MTIME          *(volatile uint64_t*)(CLIC_CTRL_ADDR + 0xBFF8UL)
#define CLIC_CLK_GATE       *(volatile uint64_t*)(CLIC_CTRL_ADDR + 0x7FF000UL)


#define CLIC_HART0_ADDR     0x02800000UL
#define CLIC_INTIP           ((volatile uint8_t*)(CLIC_HART0_ADDR + 0x000UL))
#define CLIC_INTIE           ((volatile uint8_t*)(CLIC_HART0_ADDR + 0x400UL))
#define CLIC_INTCFG          ((volatile uint8_t*)(CLIC_HART0_ADDR + 0x800UL))
#define CLIC_CFG             *(volatile uint8_t*)(CLIC_HART0_ADDR + 0xc00UL)

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



/* =========================================================================================================================== */
/* ================                                            rf                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief rf. (rf)
  */

typedef struct {                                /*!< rf Structure                                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< Silicon revision                                                          */
    
    struct {
      __IOM uint32_t rf_id      : 8;            /*!< rf_id                                                                     */
      __IOM uint32_t fw_rev     : 8;            /*!< fw_rev                                                                    */
      __IOM uint32_t hw_rev     : 8;            /*!< hw_rev                                                                    */
            uint32_t            : 8;
    } bit;
  } rf_rev;
  
  union {
    __IOM uint32_t reg;                         /*!< Digital Control                                                           */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t rf_fsm_ctrl_en : 1;        /*!< rf_fsm_ctrl_en                                                            */
      __IOM uint32_t rf_fsm_t2r_cal_mode : 2;   /*!< rf_fsm_t2r_cal_mode                                                       */
      __IOM uint32_t rf_fsm_state : 3;          /*!< rf_fsm_state                                                              */
            uint32_t            : 1;
      __IOM uint32_t rf_rc_state_dbg : 3;       /*!< rf_rc_state_dbg                                                           */
      __IOM uint32_t rf_rc_state_dbg_en : 1;    /*!< rf_rc_state_dbg_en                                                        */
      __IOM uint32_t rf_fsm_st_int_sel : 3;     /*!< rf_fsm_st_int_sel                                                         */
            uint32_t            : 1;
      __IOM uint32_t rf_fsm_st_int : 1;         /*!< rf_fsm_st_int                                                             */
            uint32_t            : 3;
      __IOM uint32_t rf_fsm_st_int_clr : 1;     /*!< rf_fsm_st_int_clr                                                         */
            uint32_t            : 3;
      __IOM uint32_t rf_fsm_st_int_set : 1;     /*!< rf_fsm_st_int_set                                                         */
            uint32_t            : 3;
      __IOM uint32_t rf_rc_state_value : 3;     /*!< rf_rc_state_value                                                         */
            uint32_t            : 1;
    } bit;
  } rf_fsm_ctrl_hw;
  
  union {
    __IOM uint32_t reg;                         /*!< rfsm status reg                                                           */
    
    struct {
      __IOM uint32_t rf_fsm_sw_st : 5;          /*!< rf_fsm_sw_st                                                              */
            uint32_t            : 3;
      __IOM uint32_t rf_fsm_sw_st_vld : 1;      /*!< rf_fsm_sw_st_vld                                                          */
            uint32_t            : 3;
      __IOM uint32_t full_cal_en : 1;           /*!< full_cal_en                                                               */
            uint32_t            : 3;
      __IOM uint32_t inc_cal_timeout : 1;       /*!< inc_cal_timeout                                                           */
            uint32_t            : 3;
      __IOM uint32_t lo_unlocked : 1;           /*!< lo_unlocked                                                               */
            uint32_t            : 11;
    } bit;
  } rf_fsm_ctrl_sw;
  
  union {
    __IOM uint32_t reg;                         /*!< Control logic switch                                                      */
    
    struct {
      __IOM uint32_t pu_ctrl_hw : 1;            /*!< pu_ctrl_hw                                                                */
      __IOM uint32_t rx_gain_ctrl_hw : 1;       /*!< rx_gain_ctrl_hw                                                           */
      __IOM uint32_t tx_gain_ctrl_hw : 1;       /*!< tx_gain_ctrl_hw                                                           */
      __IOM uint32_t lna_ctrl_hw : 1;           /*!< lna_ctrl_hw                                                               */
      __IOM uint32_t rbb_bw_ctrl_hw : 1;        /*!< rbb_bw_ctrl_hw                                                            */
      __IOM uint32_t trxcal_ctrl_hw : 1;        /*!< trxcal_ctrl_hw                                                            */
      __IOM uint32_t lo_ctrl_hw : 1;            /*!< lo_ctrl_hw                                                                */
      __IOM uint32_t inc_acal_ctrl_en_hw : 1;   /*!< inc_acal_ctrl_en_hw                                                       */
      __IOM uint32_t inc_fcal_ctrl_en_hw : 1;   /*!< inc_fcal_ctrl_en_hw                                                       */
      __IOM uint32_t sdm_ctrl_hw : 1;           /*!< sdm_ctrl_hw                                                               */
      __IOM uint32_t rbb_pkdet_en_ctrl_hw : 1;  /*!< rbb_pkdet_en_ctrl_hw                                                      */
      __IOM uint32_t rbb_pkdet_out_rstn_ctrl_hw : 1;/*!< rbb_pkdet_out_rstn_ctrl_hw                                            */
      __IOM uint32_t adda_ctrl_hw : 1;          /*!< adda_ctrl_hw                                                              */
            uint32_t            : 19;
    } bit;
  } rfctrl_hw_en;
  
  union {
    __IOM uint32_t reg;                         /*!< temp_comp.                                                                */
    
    struct {
      __IOM uint32_t const_acal : 8;            /*!< const_acal                                                                */
      __IOM uint32_t const_fcal : 8;            /*!< const_fcal                                                                */
      __IOM uint32_t temp_comp_en : 1;          /*!< temp_comp_en                                                              */
            uint32_t            : 15;
    } bit;
  } temp_comp;
  
  union {
    __IOM uint32_t reg;                         /*!< rfcal_status.                                                             */
    
    struct {
      __IOM uint32_t rcal_status : 2;           /*!< rcal_status                                                               */
      __IOM uint32_t adc_oscal_status : 2;      /*!< adc_oscal_status                                                          */
      __IOM uint32_t fcal_status : 2;           /*!< fcal_status                                                               */
      __IOM uint32_t acal_status : 2;           /*!< acal_status                                                               */
      __IOM uint32_t inc_fcal_status : 2;       /*!< inc_fcal_status                                                           */
      __IOM uint32_t inc_acal_status : 2;       /*!< inc_acal_status                                                           */
      __IOM uint32_t clkpll_cal_status : 2;     /*!< clkpll_cal_status                                                         */
      __IOM uint32_t ros_status : 2;            /*!< ros_status                                                                */
      __IOM uint32_t tos_status : 2;            /*!< tos_status                                                                */
      __IOM uint32_t rccal_status : 2;          /*!< rccal_status                                                              */
      __IOM uint32_t lo_leakcal_status : 2;     /*!< lo_leakcal_status                                                         */
      __IOM uint32_t tiqcal_status_resv : 2;    /*!< tiqcal_status_resv                                                        */
      __IOM uint32_t riqcal_status_resv : 2;    /*!< riqcal_status_resv                                                        */
      __IOM uint32_t pwdet_cal_status : 2;      /*!< pwdet_cal_status                                                          */
      __IOM uint32_t tenscal_status : 2;        /*!< tenscal_status                                                            */
      __IOM uint32_t dpd_status : 2;            /*!< dpd_status                                                                */
    } bit;
  } rfcal_status;
  
  union {
    __IOM uint32_t reg;                         /*!< rfcal_status2.                                                            */
    
    struct {
      __IOM uint32_t dl_rfcal_table_status : 2; /*!< dl_rfcal_table_status                                                     */
            uint32_t            : 30;
    } bit;
  } rfcal_status2;
  
  union {
    __IOM uint32_t reg;                         /*!< Calibration mode register                                                 */
    
    struct {
      __IOM uint32_t rcal_en_resv : 1;          /*!< rcal_en_resv                                                              */
      __IOM uint32_t adc_oscal_en : 1;          /*!< adc_oscal_en                                                              */
      __IOM uint32_t dl_rfcal_table_en : 1;     /*!< dl_rfcal_table_en                                                         */
      __IOM uint32_t fcal_en    : 1;            /*!< fcal_en                                                                   */
      __IOM uint32_t acal_en    : 1;            /*!< acal_en                                                                   */
      __IOM uint32_t fcal_inc_en : 1;           /*!< fcal_inc_en                                                               */
      __IOM uint32_t acal_inc_en : 1;           /*!< acal_inc_en                                                               */
      __IOM uint32_t roscal_inc_en : 1;         /*!< roscal_inc_en                                                             */
      __IOM uint32_t clkpll_cal_en : 1;         /*!< clkpll_cal_en                                                             */
      __IOM uint32_t roscal_en  : 1;            /*!< roscal_en                                                                 */
      __IOM uint32_t toscal_en  : 1;            /*!< toscal_en                                                                 */
      __IOM uint32_t rccal_en   : 1;            /*!< rccal_en                                                                  */
      __IOM uint32_t lo_leakcal_en : 1;         /*!< lo_leakcal_en                                                             */
      __IOM uint32_t tiqcal_en  : 1;            /*!< tiqcal_en                                                                 */
      __IOM uint32_t riqcal_en  : 1;            /*!< riqcal_en                                                                 */
      __IOM uint32_t pwdet_cal_en : 1;          /*!< pwdet_cal_en                                                              */
      __IOM uint32_t tsencal_en : 1;            /*!< tsencal_en                                                                */
      __IOM uint32_t dpd_en     : 1;            /*!< dpd_en                                                                    */
            uint32_t            : 14;
    } bit;
  } rfcal_ctrlen;
  
  union {
    __IOM uint32_t reg;                         /*!< rf calibration state enabl in full cal list                               */
    
    struct {
      __IOM uint32_t rcal_sten_resv : 1;        /*!< rcal_sten_resv                                                            */
      __IOM uint32_t adc_oscal_sten : 1;        /*!< adc_oscal_sten                                                            */
      __IOM uint32_t dl_rfcal_table_sten : 1;   /*!< dl_rfcal_table_sten                                                       */
      __IOM uint32_t fcal_sten  : 1;            /*!< fcal_sten                                                                 */
      __IOM uint32_t acal_sten  : 1;            /*!< acal_sten                                                                 */
      __IOM uint32_t inc_fcal_sten : 1;         /*!< inc_fcal_sten                                                             */
      __IOM uint32_t inc_acal_sten : 1;         /*!< inc_acal_sten                                                             */
      __IOM uint32_t clkpll_cal_sten : 1;       /*!< clkpll_cal_sten                                                           */
      __IOM uint32_t roscal_sten : 1;           /*!< roscal_sten                                                               */
      __IOM uint32_t toscal_sten_resv : 1;      /*!< toscal_sten_resv                                                          */
      __IOM uint32_t rccal_sten : 1;            /*!< rccal_sten                                                                */
      __IOM uint32_t lo_leakcal_sten : 1;       /*!< lo_leakcal_sten                                                           */
      __IOM uint32_t tiqcal_sten : 1;           /*!< tiqcal_sten                                                               */
      __IOM uint32_t riqcal_sten : 1;           /*!< riqcal_sten                                                               */
      __IOM uint32_t pwdet_cal_sten : 1;        /*!< pwdet_cal_sten                                                            */
      __IOM uint32_t tsencal_sten : 1;          /*!< tsencal_sten                                                              */
      __IOM uint32_t dpd_sten   : 1;            /*!< dpd_sten                                                                  */
            uint32_t            : 13;
      __IOM uint32_t rfcal_level : 2;           /*!< rfcal_level                                                               */
    } bit;
  } rfcal_stateen;
  __IOM uint32_t  saradc_resv;                  /*!< SARADC Control Registers                                                  */
  
  union {
    __IOM uint32_t reg;                         /*!< ZRF Control register 0                                                    */
    
    struct {
      __IOM uint32_t aupll_sdm_rst_dly : 2;     /*!< aupll_sdm_rst_dly                                                         */
      __IOM uint32_t lo_sdm_rst_dly : 2;        /*!< lo_sdm_rst_dly                                                            */
            uint32_t            : 4;
      __IOM uint32_t ppu_lead   : 2;            /*!< ppu_lead                                                                  */
      __IOM uint32_t pud_vco_dly : 2;           /*!< pud_vco_dly                                                               */
      __IOM uint32_t pud_iref_dly : 2;          /*!< pud_iref_dly                                                              */
      __IOM uint32_t pud_pa_dly : 2;            /*!< pud_pa_dly                                                                */
            uint32_t            : 11;
      __IOM uint32_t mbg_trim   : 2;            /*!< mbg_trim                                                                  */
            uint32_t            : 3;
    } bit;
  } rf_base_ctrl1;
  __IOM uint32_t  rf_base_ctrl2;                /*!< ZRF Control register 0                                                    */
  
  union {
    __IOM uint32_t reg;                         /*!< pucr1.                                                                    */
    
    struct {
      __IOM uint32_t pu_sfreg   : 1;            /*!< pu_sfreg                                                                  */
            uint32_t            : 7;
      __IOM uint32_t pu_lna     : 1;            /*!< pu_lna                                                                    */
      __IOM uint32_t pu_rmxgm   : 1;            /*!< pu_rmxgm                                                                  */
      __IOM uint32_t pu_rmx     : 1;            /*!< pu_rmx                                                                    */
      __IOM uint32_t pu_rbb     : 1;            /*!< pu_rbb                                                                    */
      __IOM uint32_t pu_adda_ldo : 1;           /*!< pu_adda_ldo                                                               */
      __IOM uint32_t adc_clk_en : 1;            /*!< adc_clk_en                                                                */
      __IOM uint32_t pu_adc     : 1;            /*!< pu_adc                                                                    */
      __IOM uint32_t pu_op_atest : 1;           /*!< pu_op_atest                                                               */
      __IOM uint32_t pu_pa      : 1;            /*!< pu_pa                                                                     */
      __IOM uint32_t pu_tmx     : 1;            /*!< pu_tmx                                                                    */
      __IOM uint32_t pu_tbb     : 1;            /*!< pu_tbb                                                                    */
      __IOM uint32_t pu_dac     : 1;            /*!< pu_dac                                                                    */
      __IOM uint32_t pu_vco     : 1;            /*!< pu_vco                                                                    */
      __IOM uint32_t pu_fbdv    : 1;            /*!< pu_fbdv                                                                   */
      __IOM uint32_t pu_pfd     : 1;            /*!< pu_pfd                                                                    */
      __IOM uint32_t pu_osmx    : 1;            /*!< pu_osmx                                                                   */
      __IOM uint32_t pu_rxbuf   : 1;            /*!< pu_rxbuf                                                                  */
      __IOM uint32_t pu_txbuf   : 1;            /*!< pu_txbuf                                                                  */
      __IOM uint32_t trsw_en    : 1;            /*!< trsw_en                                                                   */
            uint32_t            : 1;
      __IOM uint32_t pu_pkdet   : 1;            /*!< pu_pkdet                                                                  */
      __IOM uint32_t pu_rosdac  : 1;            /*!< pu_rosdac                                                                 */
      __IOM uint32_t pu_pwrmx   : 1;            /*!< pu_pwrmx                                                                  */
      __IOM uint32_t pu_tosdac  : 1;            /*!< pu_tosdac                                                                 */
    } bit;
  } pucr1;
  
  union {
    __IOM uint32_t reg;                         /*!< read only from hardware logic                                             */
    
    struct {
      __IOM uint32_t pu_sfreg_hw : 1;           /*!< pu_sfreg_hw                                                               */
            uint32_t            : 7;
      __IOM uint32_t pu_lna_hw  : 1;            /*!< pu_lna_hw                                                                 */
      __IOM uint32_t pu_rmxgm_hw : 1;           /*!< pu_rmxgm_hw                                                               */
      __IOM uint32_t pu_rmx_hw  : 1;            /*!< pu_rmx_hw                                                                 */
      __IOM uint32_t pu_rbb_hw  : 1;            /*!< pu_rbb_hw                                                                 */
      __IOM uint32_t pu_adda_ldo_hw : 1;        /*!< pu_adda_ldo_hw                                                            */
      __IOM uint32_t adc_clk_en_hw : 1;         /*!< adc_clk_en_hw                                                             */
      __IOM uint32_t pu_adc_hw  : 1;            /*!< pu_adc_hw                                                                 */
            uint32_t            : 1;
      __IOM uint32_t pu_pa_hw   : 1;            /*!< pu_pa_hw                                                                  */
      __IOM uint32_t pu_tmx_hw  : 1;            /*!< pu_tmx_hw                                                                 */
      __IOM uint32_t pu_tbb_hw  : 1;            /*!< pu_tbb_hw                                                                 */
      __IOM uint32_t pu_dac_hw  : 1;            /*!< pu_dac_hw                                                                 */
      __IOM uint32_t pu_vco_hw  : 1;            /*!< pu_vco_hw                                                                 */
      __IOM uint32_t pu_fbdv_hw : 1;            /*!< pu_fbdv_hw                                                                */
      __IOM uint32_t pu_pfd_hw  : 1;            /*!< pu_pfd_hw                                                                 */
      __IOM uint32_t pu_osmx_hw : 1;            /*!< pu_osmx_hw                                                                */
      __IOM uint32_t pu_rxbuf_hw : 1;           /*!< pu_rxbuf_hw                                                               */
      __IOM uint32_t pu_txbuf_hw : 1;           /*!< pu_txbuf_hw                                                               */
      __IOM uint32_t trsw_en_hw : 1;            /*!< trsw_en_hw                                                                */
            uint32_t            : 1;
      __IOM uint32_t pu_pkdet_hw : 1;           /*!< pu_pkdet_hw                                                               */
      __IOM uint32_t pu_rosdac_hw : 1;          /*!< pu_rosdac_hw                                                              */
            uint32_t            : 1;
      __IOM uint32_t pu_tosdac_hw : 1;          /*!< pu_tosdac_hw                                                              */
    } bit;
  } pucr1_hw;
  __IOM uint32_t  pucr2;                        /*!< pucr2.                                                                    */
  __IOM uint32_t  pucr2_hw;                     /*!< pucr2_hw.                                                                 */
  
  union {
    __IOM uint32_t reg;                         /*!< ppu_ctrl_hw.                                                              */
    
    struct {
            uint32_t            : 8;
      __IOM uint32_t ppu_lna_hw : 1;            /*!< ppu_lna_hw                                                                */
      __IOM uint32_t ppu_rmxgm_hw : 1;          /*!< ppu_rmxgm_hw                                                              */
            uint32_t            : 1;
      __IOM uint32_t ppu_rbb_hw : 1;            /*!< ppu_rbb_hw                                                                */
            uint32_t            : 8;
      __IOM uint32_t ppu_vco_hw : 1;            /*!< ppu_vco_hw                                                                */
      __IOM uint32_t ppu_fbdv_hw : 1;           /*!< ppu_fbdv_hw                                                               */
      __IOM uint32_t ppu_pfd_hw : 1;            /*!< ppu_pfd_hw                                                                */
      __IOM uint32_t ppu_osmx_hw : 1;           /*!< ppu_osmx_hw                                                               */
      __IOM uint32_t ppu_rxbuf_hw : 1;          /*!< ppu_rxbuf_hw                                                              */
      __IOM uint32_t ppu_txbuf_hw : 1;          /*!< ppu_txbuf_hw                                                              */
            uint32_t            : 6;
    } bit;
  } ppu_ctrl_hw;
  
  union {
    __IOM uint32_t reg;                         /*!< pud_ctrl_hw.                                                              */
    
    struct {
            uint32_t            : 20;
      __IOM uint32_t pud_vco_hw : 1;            /*!< pud_vco_hw                                                                */
            uint32_t            : 11;
    } bit;
  } pud_ctrl_hw;
  
  union {
    __IOM uint32_t reg;                         /*!< gain control1                                                             */
    
    struct {
      __IOM uint32_t gc_lna     : 3;            /*!< gc_lna                                                                    */
            uint32_t            : 1;
      __IOM uint32_t gc_rmxgm   : 2;            /*!< gc_rmxgm                                                                  */
            uint32_t            : 2;
      __IOM uint32_t gc_rbb1    : 2;            /*!< gc_rbb1                                                                   */
            uint32_t            : 2;
      __IOM uint32_t gc_rbb2    : 3;            /*!< gc_rbb2                                                                   */
            uint32_t            : 1;
      __IOM uint32_t gc_tmx     : 3;            /*!< gc_tmx                                                                    */
            uint32_t            : 1;
      __IOM uint32_t gc_tbb     : 5;            /*!< gc_tbb                                                                    */
            uint32_t            : 3;
      __IOM uint32_t gc_tbb_boost : 2;          /*!< gc_tbb_boost                                                              */
            uint32_t            : 2;
    } bit;
  } trx_gain1;
  
  union {
    __IOM uint32_t reg;                         /*!< trx gain hardware readback                                                */
    
    struct {
      __IOM uint32_t gc_lna_hw  : 3;            /*!< gc_lna_hw                                                                 */
            uint32_t            : 1;
      __IOM uint32_t gc_rmxgm_hw : 2;           /*!< gc_rmxgm_hw                                                               */
            uint32_t            : 2;
      __IOM uint32_t gc_rbb1_hw : 2;            /*!< gc_rbb1_hw                                                                */
            uint32_t            : 2;
      __IOM uint32_t gc_rbb2_hw : 3;            /*!< gc_rbb2_hw                                                                */
            uint32_t            : 1;
      __IOM uint32_t gc_tmx_hw  : 3;            /*!< gc_tmx_hw                                                                 */
            uint32_t            : 1;
      __IOM uint32_t gc_tbb_hw  : 5;            /*!< gc_tbb_hw                                                                 */
            uint32_t            : 3;
      __IOM uint32_t gc_tbb_boost_hw : 2;       /*!< gc_tbb_boost_hw                                                           */
            uint32_t            : 2;
    } bit;
  } trx_gain_hw;
  
  union {
    __IOM uint32_t reg;                         /*!< dc test register                                                          */
    
    struct {
      __IOM uint32_t tmux       : 3;            /*!< tmux                                                                      */
      __IOM uint32_t dc_tp_en   : 1;            /*!< dc_tp_en                                                                  */
      __IOM uint32_t dc_tp_clkpll_en : 1;       /*!< dc_tp_clkpll_en                                                           */
            uint32_t            : 3;
      __IOM uint32_t ten_clkpll : 1;            /*!< ten_clkpll                                                                */
      __IOM uint32_t ten_clkpll_sfreg : 1;      /*!< ten_clkpll_sfreg                                                          */
            uint32_t            : 2;
      __IOM uint32_t ten_rrf_0  : 1;            /*!< ten_rrf_0                                                                 */
      __IOM uint32_t ten_rrf_1  : 1;            /*!< ten_rrf_1                                                                 */
      __IOM uint32_t ten_pa     : 1;            /*!< ten_pa                                                                    */
      __IOM uint32_t ten_tmx    : 1;            /*!< ten_tmx                                                                   */
      __IOM uint32_t ten_tia    : 1;            /*!< ten_tia                                                                   */
      __IOM uint32_t ten_bq     : 1;            /*!< ten_bq                                                                    */
      __IOM uint32_t ten_atest  : 1;            /*!< ten_atest                                                                 */
      __IOM uint32_t ten_tbb    : 1;            /*!< ten_tbb                                                                   */
      __IOM uint32_t ten_adc    : 1;            /*!< ten_adc                                                                   */
      __IOM uint32_t ten_dac_i  : 1;            /*!< ten_dac_i                                                                 */
      __IOM uint32_t ten_dac_q  : 1;            /*!< ten_dac_q                                                                 */
            uint32_t            : 1;
      __IOM uint32_t ten_vco    : 1;            /*!< ten_vco                                                                   */
      __IOM uint32_t ten_pfdcp  : 1;            /*!< ten_pfdcp                                                                 */
      __IOM uint32_t ten_lf     : 1;            /*!< ten_lf                                                                    */
      __IOM uint32_t ten_lodist : 1;            /*!< ten_lodist                                                                */
            uint32_t            : 4;
    } bit;
  } ten_dc;
  
  union {
    __IOM uint32_t reg;                         /*!< digital test register                                                     */
    
    struct {
      __IOM uint32_t dten_clkpll_postdiv_clk : 1;/*!< dten_clkpll_postdiv_clk                                                  */
      __IOM uint32_t dten_clkpll_clk96m : 1;    /*!< dten_clkpll_clk96m                                                        */
      __IOM uint32_t dten_clkpll_clk32m : 1;    /*!< dten_clkpll_clk32m                                                        */
      __IOM uint32_t dten_clkpll_fsdm : 1;      /*!< dten_clkpll_fsdm                                                          */
      __IOM uint32_t dten_clkpll_fref : 1;      /*!< dten_clkpll_fref                                                          */
      __IOM uint32_t dten_clkpll_fin : 1;       /*!< dten_clkpll_fin                                                           */
      __IOM uint32_t dten_lo_fsdm : 1;          /*!< dten_lo_fsdm                                                              */
            uint32_t            : 1;
      __IOM uint32_t dten_lo_fref : 1;          /*!< dten_lo_fref                                                              */
      __IOM uint32_t dtest_pull_down : 1;       /*!< dtest_pull_down                                                           */
            uint32_t            : 13;
      __IOM uint32_t rf_dtest_en : 1;           /*!< rf_dtest_en                                                               */
            uint32_t            : 8;
    } bit;
  } ten_dig;
  
  union {
    __IOM uint32_t reg;                         /*!< ac test register                                                          */
    
    struct {
      __IOM uint32_t atest_op_cc : 4;           /*!< atest_op_cc                                                               */
      __IOM uint32_t atest_dac_en : 1;          /*!< atest_dac_en                                                              */
      __IOM uint32_t atest_in_trx_sw : 1;       /*!< atest_in_trx_sw                                                           */
      __IOM uint32_t atest_in_en : 1;           /*!< atest_in_en                                                               */
            uint32_t            : 1;
      __IOM uint32_t atest_gain_r9 : 2;         /*!< atest_gain_r9                                                             */
      __IOM uint32_t atest_gain_r8 : 2;         /*!< atest_gain_r8                                                             */
      __IOM uint32_t atest_gain_r7 : 2;         /*!< atest_gain_r7                                                             */
      __IOM uint32_t atest_gain_r6 : 2;         /*!< atest_gain_r6                                                             */
      __IOM uint32_t atest_gain_r5 : 3;         /*!< atest_gain_r5                                                             */
            uint32_t            : 1;
      __IOM uint32_t atest_out_en_q : 1;        /*!< atest_out_en_q                                                            */
      __IOM uint32_t atest_out_en_i : 1;        /*!< atest_out_en_i                                                            */
      __IOM uint32_t atest_in_en_q : 1;         /*!< atest_in_en_q                                                             */
      __IOM uint32_t atest_in_en_i : 1;         /*!< atest_in_en_i                                                             */
            uint32_t            : 8;
    } bit;
  } ten_ac;
  __IOM uint32_t  pmip_mv2aon;                  /*!< pmip_mv2aon.                                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< RX normal bias mode registers                                             */
    
    struct {
      __IOM uint32_t vg11_sel   : 2;            /*!< vg11_sel                                                                  */
      __IOM uint32_t vg13_sel   : 2;            /*!< vg13_sel                                                                  */
            uint32_t            : 28;
    } bit;
  } cip;
  
  union {
    __IOM uint32_t reg;                         /*!< pa1.                                                                      */
    
    struct {
      __IOM uint32_t pa_iaq     : 3;            /*!< pa_iaq                                                                    */
      __IOM uint32_t pa_etb_en  : 1;            /*!< pa_etb_en                                                                 */
      __IOM uint32_t pa_iet     : 4;            /*!< pa_iet                                                                    */
      __IOM uint32_t pa_vbcore  : 4;            /*!< pa_vbcore                                                                 */
      __IOM uint32_t pa_vbcas   : 3;            /*!< pa_vbcas                                                                  */
      __IOM uint32_t pa_half_on : 1;            /*!< pa_half_on                                                                */
      __IOM uint32_t pa_ib_fix  : 1;            /*!< pa_ib_fix                                                                 */
      __IOM uint32_t pa_lz_bias_en : 1;         /*!< pa_lz_bias_en                                                             */
      __IOM uint32_t pa_pwrmx_osdac : 4;        /*!< pa_pwrmx_osdac                                                            */
      __IOM uint32_t pa_pwrmx_dac_pn_switch : 1;/*!< pa_pwrmx_dac_pn_switch                                                    */
            uint32_t            : 1;
      __IOM uint32_t pa_pwrmx_bm : 3;           /*!< pa_pwrmx_bm                                                               */
            uint32_t            : 1;
      __IOM uint32_t pa_att_gc  : 4;            /*!< pa_att_gc                                                                 */
    } bit;
  } pa1;
  
  union {
    __IOM uint32_t reg;                         /*!< RX normal bias mode registers                                             */
    
    struct {
            uint32_t            : 3;
      __IOM uint32_t pa_etb_en_hw : 1;          /*!< pa_etb_en_hw                                                              */
      __IOM uint32_t pa_iet_hw  : 4;            /*!< pa_iet_hw                                                                 */
      __IOM uint32_t pa_vbcore_hw : 4;          /*!< pa_vbcore_hw                                                              */
      __IOM uint32_t pa_vbcas_hw : 3;           /*!< pa_vbcas_hw                                                               */
            uint32_t            : 1;
      __IOM uint32_t pa_half_on_hw : 1;         /*!< pa_half_on_hw                                                             */
      __IOM uint32_t pa_ib_fix_hw : 1;          /*!< pa_ib_fix_hw                                                              */
            uint32_t            : 14;
    } bit;
  } pa2;
  
  union {
    __IOM uint32_t reg;                         /*!< tmx.                                                                      */
    
    struct {
      __IOM uint32_t tmx_cs     : 3;            /*!< tmx_cs                                                                    */
            uint32_t            : 1;
      __IOM uint32_t tmx_bm_sw  : 3;            /*!< tmx_bm_sw                                                                 */
            uint32_t            : 1;
      __IOM uint32_t tmx_bm_cas : 3;            /*!< tmx_bm_cas                                                                */
            uint32_t            : 1;
      __IOM uint32_t tmx_bm_cas_bulk : 3;       /*!< tmx_bm_cas_bulk                                                           */
            uint32_t            : 1;
      __IOM uint32_t tx_tsense_en : 1;          /*!< tx_tsense_en                                                              */
            uint32_t            : 15;
    } bit;
  } tmx;
  
  union {
    __IOM uint32_t reg;                         /*!< tbb.                                                                      */
    
    struct {
      __IOM uint32_t tbb_bm_sf  : 2;            /*!< tbb_bm_sf                                                                 */
            uint32_t            : 2;
      __IOM uint32_t tbb_bm_cg  : 2;            /*!< tbb_bm_cg                                                                 */
            uint32_t            : 2;
      __IOM uint32_t tbb_vcm    : 2;            /*!< tbb_vcm                                                                   */
            uint32_t            : 2;
      __IOM uint32_t tbb_cflt   : 2;            /*!< tbb_cflt                                                                  */
      __IOM uint32_t tbb_iq_bias_short : 1;     /*!< tbb_iq_bias_short                                                         */
      __IOM uint32_t tbb_atest_out_en : 1;      /*!< tbb_atest_out_en                                                          */
      __IOM uint32_t tbb_tosdac_q : 6;          /*!< tbb_tosdac_q                                                              */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_i : 6;          /*!< tbb_tosdac_i                                                              */
            uint32_t            : 2;
    } bit;
  } tbb;
  
  union {
    __IOM uint32_t reg;                         /*!< lna.                                                                      */
    
    struct {
      __IOM uint32_t lna_bm     : 4;            /*!< lna_bm                                                                    */
      __IOM uint32_t lna_bm_hw  : 4;            /*!< lna_bm_hw                                                                 */
      __IOM uint32_t lna_load_csw : 4;          /*!< lna_load_csw                                                              */
      __IOM uint32_t lna_load_csw_hw : 4;       /*!< lna_load_csw_hw                                                           */
      __IOM uint32_t lna_rfb_match : 3;         /*!< lna_rfb_match                                                             */
            uint32_t            : 1;
      __IOM uint32_t lna_cap_lg : 2;            /*!< lna_cap_lg                                                                */
            uint32_t            : 2;
      __IOM uint32_t lna_lg_gsel : 3;           /*!< lna_lg_gsel                                                               */
            uint32_t            : 5;
    } bit;
  } lna;
  
  union {
    __IOM uint32_t reg;                         /*!< rmxgm.                                                                    */
    
    struct {
      __IOM uint32_t rmx_bm     : 3;            /*!< rmx_bm                                                                    */
            uint32_t            : 1;
      __IOM uint32_t rmxgm_bm   : 3;            /*!< rmxgm_bm                                                                  */
            uint32_t            : 1;
      __IOM uint32_t rmxgm_10m_mode_en : 1;     /*!< rmxgm_10m_mode_en                                                         */
            uint32_t            : 23;
    } bit;
  } rmxgm;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb1.                                                                     */
    
    struct {
      __IOM uint32_t rosdac_q   : 6;            /*!< rosdac_q                                                                  */
            uint32_t            : 2;
      __IOM uint32_t rosdac_i   : 6;            /*!< rosdac_i                                                                  */
            uint32_t            : 2;
      __IOM uint32_t rosdac_q_hw : 6;           /*!< rosdac_q_hw                                                               */
            uint32_t            : 2;
      __IOM uint32_t rosdac_i_hw : 6;           /*!< rosdac_i_hw                                                               */
            uint32_t            : 1;
      __IOM uint32_t rosdac_range : 1;          /*!< rosdac_range                                                              */
    } bit;
  } rbb1;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb2.                                                                     */
    
    struct {
      __IOM uint32_t rbb_cap2_fc_q : 6;         /*!< rbb_cap2_fc_q                                                             */
            uint32_t            : 2;
      __IOM uint32_t rbb_cap2_fc_i : 6;         /*!< rbb_cap2_fc_i                                                             */
            uint32_t            : 2;
      __IOM uint32_t rbb_cap1_fc_q : 6;         /*!< rbb_cap1_fc_q                                                             */
            uint32_t            : 2;
      __IOM uint32_t rbb_cap1_fc_i : 6;         /*!< rbb_cap1_fc_i                                                             */
            uint32_t            : 2;
    } bit;
  } rbb2;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb3.                                                                     */
    
    struct {
      __IOM uint32_t rbb_bt_mode_hw : 1;        /*!< rbb_bt_mode_hw                                                            */
            uint32_t            : 3;
      __IOM uint32_t rbb_bt_mode : 1;           /*!< rbb_bt_mode                                                               */
      __IOM uint32_t rbb_bt_fif_tune : 2;       /*!< rbb_bt_fif_tune                                                           */
            uint32_t            : 1;
      __IOM uint32_t rbb_deq    : 2;            /*!< rbb_deq                                                                   */
            uint32_t            : 2;
      __IOM uint32_t rbb_bm_op  : 3;            /*!< rbb_bm_op                                                                 */
            uint32_t            : 1;
      __IOM uint32_t rbb_vcm    : 2;            /*!< rbb_vcm                                                                   */
            uint32_t            : 2;
      __IOM uint32_t rbb_bq_iqbias_short : 1;   /*!< rbb_bq_iqbias_short                                                       */
      __IOM uint32_t rbb_tia_iqbias_short : 1;  /*!< rbb_tia_iqbias_short                                                      */
            uint32_t            : 2;
      __IOM uint32_t rbb_bw     : 2;            /*!< rbb_bw                                                                    */
            uint32_t            : 2;
      __IOM uint32_t rxiqcal_en : 1;            /*!< rxiqcal_en                                                                */
            uint32_t            : 2;
      __IOM uint32_t pwr_det_en : 1;            /*!< pwr_det_en                                                                */
    } bit;
  } rbb3;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb4.                                                                     */
    
    struct {
      __IOM uint32_t rbb_pkdet_vth : 4;         /*!< rbb_pkdet_vth                                                             */
      __IOM uint32_t rbb_pkdet_out_rstn : 1;    /*!< rbb_pkdet_out_rstn                                                        */
            uint32_t            : 3;
      __IOM uint32_t rbb_pkdet_en : 1;          /*!< rbb_pkdet_en                                                              */
            uint32_t            : 3;
      __IOM uint32_t rbb_pkdet_out_rstn_hw : 1; /*!< rbb_pkdet_out_rstn_hw                                                     */
            uint32_t            : 3;
      __IOM uint32_t rbb_pkdet_en_hw : 1;       /*!< rbb_pkdet_en_hw                                                           */
            uint32_t            : 3;
      __IOM uint32_t pkdet_out_raw : 1;         /*!< pkdet_out_raw                                                             */
            uint32_t            : 3;
      __IOM uint32_t pkdet_out_latch : 1;       /*!< pkdet_out_latch                                                           */
            uint32_t            : 7;
    } bit;
  } rbb4;
  
  union {
    __IOM uint32_t reg;                         /*!< adda1.                                                                    */
    
    struct {
      __IOM uint32_t dac_dvdd_sel : 2;          /*!< dac_dvdd_sel                                                              */
            uint32_t            : 2;
      __IOM uint32_t dac_bias_sel : 2;          /*!< dac_bias_sel                                                              */
            uint32_t            : 2;
      __IOM uint32_t dac_clk_sel : 2;           /*!< dac_clk_sel                                                               */
            uint32_t            : 2;
      __IOM uint32_t dac_rccalsel : 1;          /*!< dac_rccalsel                                                              */
      __IOM uint32_t dac_clk_sync_inv : 1;      /*!< dac_clk_sync_inv                                                          */
            uint32_t            : 2;
      __IOM uint32_t adda_ldo_byps : 1;         /*!< adda_ldo_byps                                                             */
            uint32_t            : 3;
      __IOM uint32_t adda_ldo_dvdd_sel : 3;     /*!< adda_ldo_dvdd_sel                                                         */
            uint32_t            : 1;
      __IOM uint32_t adda_ldo_dvdd_sel_hw : 3;  /*!< adda_ldo_dvdd_sel_hw                                                      */
            uint32_t            : 5;
    } bit;
  } adda1;
  
  union {
    __IOM uint32_t reg;                         /*!< adda2.                                                                    */
    
    struct {
      __IOM uint32_t adc_vref_sel : 2;          /*!< adc_vref_sel                                                              */
            uint32_t            : 2;
      __IOM uint32_t adc_dly_ctl : 2;           /*!< adc_dly_ctl                                                               */
            uint32_t            : 2;
      __IOM uint32_t adc_dvdd_sel : 2;          /*!< adc_dvdd_sel                                                              */
            uint32_t            : 2;
      __IOM uint32_t adc_sar_ascal_en : 1;      /*!< adc_sar_ascal_en                                                          */
            uint32_t            : 3;
      __IOM uint32_t adc_gt_rm  : 1;            /*!< adc_gt_rm                                                                 */
            uint32_t            : 3;
      __IOM uint32_t adc_clk_sync_inv : 1;      /*!< adc_clk_sync_inv                                                          */
            uint32_t            : 3;
      __IOM uint32_t adc_clk_inv : 1;           /*!< adc_clk_inv                                                               */
            uint32_t            : 3;
      __IOM uint32_t adc_clk_div_sel : 1;       /*!< adc_clk_div_sel                                                           */
            uint32_t            : 3;
    } bit;
  } adda2;
  __IM  uint32_t  RESERVED[3];
  
  union {
    __IOM uint32_t reg;                         /*!< vco1.                                                                     */
    
    struct {
      __IOM uint32_t lo_vco_freq_cw : 8;        /*!< lo_vco_freq_cw                                                            */
      __IOM uint32_t lo_vco_freq_cw_hw : 8;     /*!< lo_vco_freq_cw_hw                                                         */
      __IOM uint32_t lo_vco_idac_cw : 5;        /*!< lo_vco_idac_cw                                                            */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_idac_cw_hw : 5;     /*!< lo_vco_idac_cw_hw                                                         */
            uint32_t            : 3;
    } bit;
  } vco1;
  
  union {
    __IOM uint32_t reg;                         /*!< vco2.                                                                     */
    
    struct {
      __IOM uint32_t lo_vco_vbias_cw : 2;       /*!< lo_vco_vbias_cw                                                           */
            uint32_t            : 2;
      __IOM uint32_t lo_vco_idac_boot : 1;      /*!< lo_vco_idac_boot                                                          */
      __IOM uint32_t lo_vco_short_vbias_filter : 1;/*!< lo_vco_short_vbias_filter                                              */
      __IOM uint32_t lo_vco_short_idac_filter : 1;/*!< lo_vco_short_idac_filter                                                */
            uint32_t            : 1;
      __IOM uint32_t acal_vref_cw : 3;          /*!< acal_vref_cw                                                              */
            uint32_t            : 1;
      __IOM uint32_t acal_vco_ud : 1;           /*!< acal_vco_ud                                                               */
            uint32_t            : 3;
      __IOM uint32_t acal_inc_en_hw : 1;        /*!< acal_inc_en_hw                                                            */
            uint32_t            : 15;
    } bit;
  } vco2;
  
  union {
    __IOM uint32_t reg;                         /*!< vco3.                                                                     */
    
    struct {
      __IOM uint32_t fcal_div   : 16;           /*!< fcal_div                                                                  */
      __IOM uint32_t fcal_cnt_op : 16;          /*!< fcal_cnt_op                                                               */
    } bit;
  } vco3;
  
  union {
    __IOM uint32_t reg;                         /*!< vco4.                                                                     */
    
    struct {
            uint32_t            : 4;
      __IOM uint32_t fcal_cnt_start : 1;        /*!< fcal_cnt_start                                                            */
            uint32_t            : 3;
      __IOM uint32_t fcal_inc_en_hw : 1;        /*!< fcal_inc_en_hw                                                            */
            uint32_t            : 7;
      __IOM uint32_t fcal_inc_large_range : 1;  /*!< fcal_inc_large_range                                                      */
            uint32_t            : 3;
      __IOM uint32_t fcal_cnt_rdy : 1;          /*!< fcal_cnt_rdy                                                              */
            uint32_t            : 3;
      __IOM uint32_t fcal_inc_vctrl_ud : 2;     /*!< fcal_inc_vctrl_ud                                                         */
            uint32_t            : 6;
    } bit;
  } vco4;
  
  union {
    __IOM uint32_t reg;                         /*!< pfdcp.                                                                    */
    
    struct {
      __IOM uint32_t lo_cp_sel  : 1;            /*!< lo_cp_sel                                                                 */
            uint32_t            : 3;
      __IOM uint32_t lo_cp_sel_hw : 1;          /*!< lo_cp_sel_hw                                                              */
            uint32_t            : 3;
      __IOM uint32_t lo_cp_startup_en : 1;      /*!< lo_cp_startup_en                                                          */
            uint32_t            : 3;
      __IOM uint32_t lo_cp_ota_en : 1;          /*!< lo_cp_ota_en                                                              */
            uint32_t            : 3;
      __IOM uint32_t lo_cp_opamp_en : 1;        /*!< lo_cp_opamp_en                                                            */
            uint32_t            : 3;
      __IOM uint32_t lo_cp_hiz  : 1;            /*!< lo_cp_hiz                                                                 */
            uint32_t            : 3;
      __IOM uint32_t lo_pfd_rvdd_boost : 1;     /*!< lo_pfd_rvdd_boost                                                         */
            uint32_t            : 3;
      __IOM uint32_t lo_pfd_rst_csd : 1;        /*!< lo_pfd_rst_csd                                                            */
      __IOM uint32_t lo_pfd_rst_csd_hw : 1;     /*!< lo_pfd_rst_csd_hw                                                         */
            uint32_t            : 2;
    } bit;
  } pfdcp;
  
  union {
    __IOM uint32_t reg;                         /*!< lo.                                                                       */
    
    struct {
      __IOM uint32_t lo_lf_rz_hw : 2;           /*!< lo_lf_rz_hw                                                               */
            uint32_t            : 2;
      __IOM uint32_t lo_lf_r4_hw : 2;           /*!< lo_lf_r4_hw                                                               */
            uint32_t            : 2;
      __IOM uint32_t lo_lf_cz_hw : 2;           /*!< lo_lf_cz_hw                                                               */
            uint32_t            : 2;
      __IOM uint32_t lo_lf_rz   : 2;            /*!< lo_lf_rz                                                                  */
      __IOM uint32_t lo_lf_cz   : 2;            /*!< lo_lf_cz                                                                  */
      __IOM uint32_t lo_lf_r4   : 2;            /*!< lo_lf_r4                                                                  */
      __IOM uint32_t lo_lf_r4_short : 1;        /*!< lo_lf_r4_short                                                            */
            uint32_t            : 1;
      __IOM uint32_t lo_slipped_dn : 1;         /*!< lo_slipped_dn                                                             */
            uint32_t            : 3;
      __IOM uint32_t lo_slipped_up : 1;         /*!< lo_slipped_up                                                             */
            uint32_t            : 7;
    } bit;
  } lo;
  
  union {
    __IOM uint32_t reg;                         /*!< fbdv.                                                                     */
    
    struct {
      __IOM uint32_t lo_fbdv_halfstep_en_hw : 1;/*!< lo_fbdv_halfstep_en_hw                                                    */
            uint32_t            : 3;
      __IOM uint32_t lo_fbdv_halfstep_en : 1;   /*!< lo_fbdv_halfstep_en                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_fbdv_sel_sample_clk : 2;/*!< lo_fbdv_sel_sample_clk                                                    */
            uint32_t            : 2;
      __IOM uint32_t lo_fbdv_sel_fb_clk : 2;    /*!< lo_fbdv_sel_fb_clk                                                        */
            uint32_t            : 2;
      __IOM uint32_t lo_fbdv_rst : 1;           /*!< lo_fbdv_rst                                                               */
            uint32_t            : 3;
      __IOM uint32_t lo_fbdv_rst_hw : 1;        /*!< lo_fbdv_rst_hw                                                            */
            uint32_t            : 11;
    } bit;
  } fbdv;
  
  union {
    __IOM uint32_t reg;                         /*!< lodist.                                                                   */
    
    struct {
      __IOM uint32_t lo_osmx_xgm_boost : 1;     /*!< lo_osmx_xgm_boost                                                         */
            uint32_t            : 3;
      __IOM uint32_t lo_osmx_en_xgm : 1;        /*!< lo_osmx_en_xgm                                                            */
            uint32_t            : 3;
      __IOM uint32_t lo_osmx_fix_cap : 1;       /*!< lo_osmx_fix_cap                                                           */
            uint32_t            : 3;
      __IOM uint32_t lo_osmx_vbuf_stre : 1;     /*!< lo_osmx_vbuf_stre                                                         */
            uint32_t            : 3;
      __IOM uint32_t lo_osmx_capbank_bias : 2;  /*!< lo_osmx_capbank_bias                                                      */
            uint32_t            : 2;
      __IOM uint32_t lo_osmx_cap : 4;           /*!< lo_osmx_cap                                                               */
      __IOM uint32_t lo_lodist_txbuf_stre : 1;  /*!< lo_lodist_txbuf_stre                                                      */
            uint32_t            : 3;
      __IOM uint32_t lo_lodist_rxbuf_stre : 1;  /*!< lo_lodist_rxbuf_stre                                                      */
            uint32_t            : 3;
    } bit;
  } lodist;
  
  union {
    __IOM uint32_t reg;                         /*!< sdm1.                                                                     */
    
    struct {
      __IOM uint32_t lo_sdm_dither_sel_hw : 2;  /*!< lo_sdm_dither_sel_hw                                                      */
            uint32_t            : 2;
      __IOM uint32_t lo_sdm_bypass_hw : 1;      /*!< lo_sdm_bypass_hw                                                          */
            uint32_t            : 3;
      __IOM uint32_t lo_sdm_dither_sel : 2;     /*!< lo_sdm_dither_sel                                                         */
            uint32_t            : 2;
      __IOM uint32_t lo_sdm_bypass : 1;         /*!< lo_sdm_bypass                                                             */
            uint32_t            : 3;
      __IOM uint32_t lo_sdm_rstb : 1;           /*!< lo_sdm_rstb                                                               */
      __IOM uint32_t lo_sdm_rstb_hw : 1;        /*!< lo_sdm_rstb_hw                                                            */
            uint32_t            : 2;
      __IOM uint32_t lo_sdm_flag : 1;           /*!< lo_sdm_flag                                                               */
            uint32_t            : 11;
    } bit;
  } sdm1;
  
  union {
    __IOM uint32_t reg;                         /*!< sdm2.                                                                     */
    
    struct {
      __IOM uint32_t lo_sdmin   : 30;           /*!< lo_sdmin                                                                  */
            uint32_t            : 2;
    } bit;
  } sdm2;
  
  union {
    __IOM uint32_t reg;                         /*!< sdm3.                                                                     */
    
    struct {
      __IOM uint32_t lo_sdmin_hw : 30;          /*!< lo_sdmin_hw                                                               */
            uint32_t            : 2;
    } bit;
  } sdm3;
  __IM  uint32_t  RESERVED1[8];
  
  union {
    __IOM uint32_t reg;                         /*!< rf_resv_reg_0.                                                            */
    
    struct {
      __IOM uint32_t rf_reserved0 : 32;         /*!< rf_reserved0                                                              */
    } bit;
  } rf_resv_reg_0;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_resv_reg_1.                                                            */
    
    struct {
      __IOM uint32_t rf_reserved1 : 32;         /*!< rf_reserved1                                                              */
    } bit;
  } rf_resv_reg_1;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_resv_reg_2.                                                            */
    
    struct {
      __IOM uint32_t rf_reserved2 : 32;         /*!< rf_reserved2                                                              */
    } bit;
  } rf_resv_reg_2;
  
  union {
    __IOM uint32_t reg;                         /*!< rrf_gain_index1.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl0_gc_rmxgm : 2;   /*!< gain_ctrl0_gc_rmxgm                                                       */
      __IOM uint32_t gain_ctrl0_gc_lna : 3;     /*!< gain_ctrl0_gc_lna                                                         */
      __IOM uint32_t gain_ctrl1_gc_rmxgm : 2;   /*!< gain_ctrl1_gc_rmxgm                                                       */
      __IOM uint32_t gain_ctrl1_gc_lna : 3;     /*!< gain_ctrl1_gc_lna                                                         */
      __IOM uint32_t gain_ctrl2_gc_rmxgm : 2;   /*!< gain_ctrl2_gc_rmxgm                                                       */
      __IOM uint32_t gain_ctrl2_gc_lna : 3;     /*!< gain_ctrl2_gc_lna                                                         */
      __IOM uint32_t gain_ctrl3_gc_rmxgm : 2;   /*!< gain_ctrl3_gc_rmxgm                                                       */
      __IOM uint32_t gain_ctrl3_gc_lna : 3;     /*!< gain_ctrl3_gc_lna                                                         */
      __IOM uint32_t gain_ctrl4_gc_rmxgm : 2;   /*!< gain_ctrl4_gc_rmxgm                                                       */
      __IOM uint32_t gain_ctrl4_gc_lna : 3;     /*!< gain_ctrl4_gc_lna                                                         */
      __IOM uint32_t gain_ctrl5_gc_rmxgm : 2;   /*!< gain_ctrl5_gc_rmxgm                                                       */
      __IOM uint32_t gain_ctrl5_gc_lna : 3;     /*!< gain_ctrl5_gc_lna                                                         */
            uint32_t            : 2;
    } bit;
  } rrf_gain_index1;
  
  union {
    __IOM uint32_t reg;                         /*!< rrf_gain_index2.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl8_gc_rmxgm : 2;   /*!< gain_ctrl8_gc_rmxgm                                                       */
      __IOM uint32_t gain_ctrl8_gc_lna : 3;     /*!< gain_ctrl8_gc_lna                                                         */
      __IOM uint32_t gain_ctrl7_gc_rmxgm : 2;   /*!< gain_ctrl7_gc_rmxgm                                                       */
      __IOM uint32_t gain_ctrl7_gc_lna : 3;     /*!< gain_ctrl7_gc_lna                                                         */
      __IOM uint32_t gain_ctrl6_gc_rmxgm : 2;   /*!< gain_ctrl6_gc_rmxgm                                                       */
      __IOM uint32_t gain_ctrl6_gc_lna : 3;     /*!< gain_ctrl6_gc_lna                                                         */
            uint32_t            : 17;
    } bit;
  } rrf_gain_index2;
  
  union {
    __IOM uint32_t reg;                         /*!< lna_ctrl_hw_mux.                                                          */
    
    struct {
      __IOM uint32_t lna_bm_hg  : 4;            /*!< lna_bm_hg                                                                 */
      __IOM uint32_t lna_bm_lg  : 4;            /*!< lna_bm_lg                                                                 */
      __IOM uint32_t lna_load_csw_hg : 4;       /*!< lna_load_csw_hg                                                           */
      __IOM uint32_t lna_load_csw_lg : 4;       /*!< lna_load_csw_lg                                                           */
            uint32_t            : 16;
    } bit;
  } lna_ctrl_hw_mux;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb_gain_index1.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl0_gc_rbb1 : 2;    /*!< gain_ctrl0_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl0_gc_rbb2 : 3;    /*!< gain_ctrl0_gc_rbb2                                                        */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl1_gc_rbb1 : 2;    /*!< gain_ctrl1_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl1_gc_rbb2 : 3;    /*!< gain_ctrl1_gc_rbb2                                                        */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl2_gc_rbb1 : 2;    /*!< gain_ctrl2_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl2_gc_rbb2 : 3;    /*!< gain_ctrl2_gc_rbb2                                                        */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl3_gc_rbb1 : 2;    /*!< gain_ctrl3_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl3_gc_rbb2 : 3;    /*!< gain_ctrl3_gc_rbb2                                                        */
            uint32_t            : 1;
    } bit;
  } rbb_gain_index1;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb_gain_index2.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl4_gc_rbb1 : 2;    /*!< gain_ctrl4_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl4_gc_rbb2 : 3;    /*!< gain_ctrl4_gc_rbb2                                                        */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl5_gc_rbb1 : 2;    /*!< gain_ctrl5_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl5_gc_rbb2 : 3;    /*!< gain_ctrl5_gc_rbb2                                                        */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl6_gc_rbb1 : 2;    /*!< gain_ctrl6_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl6_gc_rbb2 : 3;    /*!< gain_ctrl6_gc_rbb2                                                        */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl7_gc_rbb1 : 2;    /*!< gain_ctrl7_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl7_gc_rbb2 : 3;    /*!< gain_ctrl7_gc_rbb2                                                        */
            uint32_t            : 1;
    } bit;
  } rbb_gain_index2;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb_gain_index3.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl8_gc_rbb1 : 2;    /*!< gain_ctrl8_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl8_gc_rbb2 : 3;    /*!< gain_ctrl8_gc_rbb2                                                        */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl9_gc_rbb1 : 2;    /*!< gain_ctrl9_gc_rbb1                                                        */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl9_gc_rbb2 : 3;    /*!< gain_ctrl9_gc_rbb2                                                        */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl10_gc_rbb1 : 2;   /*!< gain_ctrl10_gc_rbb1                                                       */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl10_gc_rbb2 : 3;   /*!< gain_ctrl10_gc_rbb2                                                       */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl11_gc_rbb1 : 2;   /*!< gain_ctrl11_gc_rbb1                                                       */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl11_gc_rbb2 : 3;   /*!< gain_ctrl11_gc_rbb2                                                       */
            uint32_t            : 1;
    } bit;
  } rbb_gain_index3;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb_gain_index4.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl12_gc_rbb1 : 2;   /*!< gain_ctrl12_gc_rbb1                                                       */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl12_gc_rbb2 : 3;   /*!< gain_ctrl12_gc_rbb2                                                       */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl13_gc_rbb1 : 2;   /*!< gain_ctrl13_gc_rbb1                                                       */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl13_gc_rbb2 : 3;   /*!< gain_ctrl13_gc_rbb2                                                       */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl14_gc_rbb1 : 2;   /*!< gain_ctrl14_gc_rbb1                                                       */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl14_gc_rbb2 : 3;   /*!< gain_ctrl14_gc_rbb2                                                       */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl15_gc_rbb1 : 2;   /*!< gain_ctrl15_gc_rbb1                                                       */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl15_gc_rbb2 : 3;   /*!< gain_ctrl15_gc_rbb2                                                       */
            uint32_t            : 1;
    } bit;
  } rbb_gain_index4;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb_gain_index5.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl16_gc_rbb1 : 2;   /*!< gain_ctrl16_gc_rbb1                                                       */
            uint32_t            : 2;
      __IOM uint32_t gain_ctrl16_gc_rbb2 : 3;   /*!< gain_ctrl16_gc_rbb2                                                       */
            uint32_t            : 25;
    } bit;
  } rbb_gain_index5;
  
  union {
    __IOM uint32_t reg;                         /*!< tbb_gain_index1.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl0_gc_tbb : 5;     /*!< gain_ctrl0_gc_tbb                                                         */
            uint32_t            : 3;
      __IOM uint32_t gain_ctrl0_gc_tmx : 3;     /*!< gain_ctrl0_gc_tmx                                                         */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl0_dac_bias_sel : 2;/*!< gain_ctrl0_dac_bias_sel                                                  */
      __IOM uint32_t gain_ctrl0_gc_tbb_boost : 2;/*!< gain_ctrl0_gc_tbb_boost                                                  */
      __IOM uint32_t gain_ctrl1_gc_tbb : 5;     /*!< gain_ctrl1_gc_tbb                                                         */
            uint32_t            : 3;
      __IOM uint32_t gain_ctrl1_gc_tmx : 3;     /*!< gain_ctrl1_gc_tmx                                                         */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl1_dac_bias_sel : 2;/*!< gain_ctrl1_dac_bias_sel                                                  */
      __IOM uint32_t gain_ctrl1_gc_tbb_boost : 2;/*!< gain_ctrl1_gc_tbb_boost                                                  */
    } bit;
  } tbb_gain_index1;
  
  union {
    __IOM uint32_t reg;                         /*!< tbb_gain_index2.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl2_gc_tbb : 5;     /*!< gain_ctrl2_gc_tbb                                                         */
            uint32_t            : 3;
      __IOM uint32_t gain_ctrl2_gc_tmx : 3;     /*!< gain_ctrl2_gc_tmx                                                         */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl2_dac_bias_sel : 2;/*!< gain_ctrl2_dac_bias_sel                                                  */
      __IOM uint32_t gain_ctrl2_gc_tbb_boost : 2;/*!< gain_ctrl2_gc_tbb_boost                                                  */
      __IOM uint32_t gain_ctrl3_gc_tbb : 5;     /*!< gain_ctrl3_gc_tbb                                                         */
            uint32_t            : 3;
      __IOM uint32_t gain_ctrl3_gc_tmx : 3;     /*!< gain_ctrl3_gc_tmx                                                         */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl3_dac_bias_sel : 2;/*!< gain_ctrl3_dac_bias_sel                                                  */
      __IOM uint32_t gain_ctrl3_gc_tbb_boost : 2;/*!< gain_ctrl3_gc_tbb_boost                                                  */
    } bit;
  } tbb_gain_index2;
  
  union {
    __IOM uint32_t reg;                         /*!< tbb_gain_index3.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl4_gc_tbb : 5;     /*!< gain_ctrl4_gc_tbb                                                         */
            uint32_t            : 3;
      __IOM uint32_t gain_ctrl4_gc_tmx : 3;     /*!< gain_ctrl4_gc_tmx                                                         */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl4_dac_bias_sel : 2;/*!< gain_ctrl4_dac_bias_sel                                                  */
      __IOM uint32_t gain_ctrl4_gc_tbb_boost : 2;/*!< gain_ctrl4_gc_tbb_boost                                                  */
      __IOM uint32_t gain_ctrl5_gc_tbb : 5;     /*!< gain_ctrl5_gc_tbb                                                         */
            uint32_t            : 3;
      __IOM uint32_t gain_ctrl5_gc_tmx : 3;     /*!< gain_ctrl5_gc_tmx                                                         */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl5_dac_bias_sel : 2;/*!< gain_ctrl5_dac_bias_sel                                                  */
      __IOM uint32_t gain_ctrl5_gc_tbb_boost : 2;/*!< gain_ctrl5_gc_tbb_boost                                                  */
    } bit;
  } tbb_gain_index3;
  
  union {
    __IOM uint32_t reg;                         /*!< tbb_gain_index4.                                                          */
    
    struct {
      __IOM uint32_t gain_ctrl6_gc_tbb : 5;     /*!< gain_ctrl6_gc_tbb                                                         */
            uint32_t            : 3;
      __IOM uint32_t gain_ctrl6_gc_tmx : 3;     /*!< gain_ctrl6_gc_tmx                                                         */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl6_dac_bias_sel : 2;/*!< gain_ctrl6_dac_bias_sel                                                  */
      __IOM uint32_t gain_ctrl6_gc_tbb_boost : 2;/*!< gain_ctrl6_gc_tbb_boost                                                  */
      __IOM uint32_t gain_ctrl7_gc_tbb : 5;     /*!< gain_ctrl7_gc_tbb                                                         */
            uint32_t            : 3;
      __IOM uint32_t gain_ctrl7_gc_tmx : 3;     /*!< gain_ctrl7_gc_tmx                                                         */
            uint32_t            : 1;
      __IOM uint32_t gain_ctrl7_dac_bias_sel : 2;/*!< gain_ctrl7_dac_bias_sel                                                  */
      __IOM uint32_t gain_ctrl7_gc_tbb_boost : 2;/*!< gain_ctrl7_gc_tbb_boost                                                  */
    } bit;
  } tbb_gain_index4;
  
  union {
    __IOM uint32_t reg;                         /*!< pa_reg_ctrl_hw1.                                                          */
    
    struct {
            uint32_t            : 12;
      __IOM uint32_t pa_iet_11n : 4;            /*!< pa_iet_11n                                                                */
      __IOM uint32_t pa_vbcore_11n : 4;         /*!< pa_vbcore_11n                                                             */
      __IOM uint32_t pa_vbcas_11n : 3;          /*!< pa_vbcas_11n                                                              */
            uint32_t            : 9;
    } bit;
  } pa_reg_ctrl_hw1;
  
  union {
    __IOM uint32_t reg;                         /*!< pa_reg_ctrl_hw2.                                                          */
    
    struct {
      __IOM uint32_t pa_iet_11g : 4;            /*!< pa_iet_11g                                                                */
      __IOM uint32_t pa_vbcore_11g : 4;         /*!< pa_vbcore_11g                                                             */
      __IOM uint32_t pa_vbcas_11g : 3;          /*!< pa_vbcas_11g                                                              */
            uint32_t            : 1;
      __IOM uint32_t pa_iet_11b : 4;            /*!< pa_iet_11b                                                                */
      __IOM uint32_t pa_vbcore_11b : 4;         /*!< pa_vbcore_11b                                                             */
      __IOM uint32_t pa_vbcas_11b : 3;          /*!< pa_vbcas_11b                                                              */
            uint32_t            : 9;
    } bit;
  } pa_reg_ctrl_hw2;
  
  union {
    __IOM uint32_t reg;                         /*!< pa_reg_wifi_ctrl_hw.                                                      */
    
    struct {
      __IOM uint32_t pa_half_on_wifi : 1;       /*!< pa_half_on_wifi                                                           */
            uint32_t            : 7;
      __IOM uint32_t pa_etb_en_wifi : 1;        /*!< pa_etb_en_wifi                                                            */
            uint32_t            : 7;
      __IOM uint32_t pa_ib_fix_wifi : 1;        /*!< pa_ib_fix_wifi                                                            */
            uint32_t            : 15;
    } bit;
  } pa_reg_wifi_ctrl_hw;
  
  union {
    __IOM uint32_t reg;                         /*!< adda_reg_ctrl_hw.                                                         */
    
    struct {
      __IOM uint32_t adda_ldo_dvdd_sel_rx : 3;  /*!< adda_ldo_dvdd_sel_rx                                                      */
            uint32_t            : 1;
      __IOM uint32_t adda_ldo_dvdd_sel_tx : 3;  /*!< adda_ldo_dvdd_sel_tx                                                      */
            uint32_t            : 25;
    } bit;
  } adda_reg_ctrl_hw;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_reg_ctrl_hw1.                                                          */
    
    struct {
      __IOM uint32_t lo_fbdv_halfstep_en_rx : 1;/*!< lo_fbdv_halfstep_en_rx                                                    */
      __IOM uint32_t lo_fbdv_halfstep_en_tx : 1;/*!< lo_fbdv_halfstep_en_tx                                                    */
      __IOM uint32_t lo_cp_sel_rx : 1;          /*!< lo_cp_sel_rx                                                              */
      __IOM uint32_t lo_cp_sel_tx : 1;          /*!< lo_cp_sel_tx                                                              */
      __IOM uint32_t lo_lf_cz_rx : 2;           /*!< lo_lf_cz_rx                                                               */
            uint32_t            : 2;
      __IOM uint32_t lo_lf_cz_tx : 2;           /*!< lo_lf_cz_tx                                                               */
            uint32_t            : 2;
      __IOM uint32_t lo_lf_rz_rx : 2;           /*!< lo_lf_rz_rx                                                               */
            uint32_t            : 2;
      __IOM uint32_t lo_lf_rz_tx : 2;           /*!< lo_lf_rz_tx                                                               */
            uint32_t            : 2;
      __IOM uint32_t lo_lf_r4_rx : 2;           /*!< lo_lf_r4_rx                                                               */
            uint32_t            : 2;
      __IOM uint32_t lo_lf_r4_tx : 2;           /*!< lo_lf_r4_tx                                                               */
            uint32_t            : 6;
    } bit;
  } lo_reg_ctrl_hw1;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw1.                                                          */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2404 : 5;   /*!< lo_vco_idac_cw_2404                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2404 : 8;   /*!< lo_vco_freq_cw_2404                                                       */
      __IOM uint32_t lo_vco_idac_cw_2408 : 5;   /*!< lo_vco_idac_cw_2408                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2408 : 8;   /*!< lo_vco_freq_cw_2408                                                       */
    } bit;
  } lo_cal_ctrl_hw1;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw2.                                                          */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2412 : 5;   /*!< lo_vco_idac_cw_2412                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2412 : 8;   /*!< lo_vco_freq_cw_2412                                                       */
      __IOM uint32_t lo_vco_idac_cw_2416 : 5;   /*!< lo_vco_idac_cw_2416                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2416 : 8;   /*!< lo_vco_freq_cw_2416                                                       */
    } bit;
  } lo_cal_ctrl_hw2;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw3.                                                          */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2420 : 5;   /*!< lo_vco_idac_cw_2420                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2420 : 8;   /*!< lo_vco_freq_cw_2420                                                       */
      __IOM uint32_t lo_vco_idac_cw_2424 : 5;   /*!< lo_vco_idac_cw_2424                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2424 : 8;   /*!< lo_vco_freq_cw_2424                                                       */
    } bit;
  } lo_cal_ctrl_hw3;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw4.                                                          */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2428 : 5;   /*!< lo_vco_idac_cw_2428                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2428 : 8;   /*!< lo_vco_freq_cw_2428                                                       */
      __IOM uint32_t lo_vco_idac_cw_2432 : 5;   /*!< lo_vco_idac_cw_2432                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2432 : 8;   /*!< lo_vco_freq_cw_2432                                                       */
    } bit;
  } lo_cal_ctrl_hw4;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw5.                                                          */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2436 : 5;   /*!< lo_vco_idac_cw_2436                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2436 : 8;   /*!< lo_vco_freq_cw_2436                                                       */
      __IOM uint32_t lo_vco_idac_cw_2440 : 5;   /*!< lo_vco_idac_cw_2440                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2440 : 8;   /*!< lo_vco_freq_cw_2440                                                       */
    } bit;
  } lo_cal_ctrl_hw5;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw6.                                                          */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2444 : 5;   /*!< lo_vco_idac_cw_2444                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2444 : 8;   /*!< lo_vco_freq_cw_2444                                                       */
      __IOM uint32_t lo_vco_idac_cw_2448 : 5;   /*!< lo_vco_idac_cw_2448                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2448 : 8;   /*!< lo_vco_freq_cw_2448                                                       */
    } bit;
  } lo_cal_ctrl_hw6;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw7.                                                          */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2452 : 5;   /*!< lo_vco_idac_cw_2452                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2452 : 8;   /*!< lo_vco_freq_cw_2452                                                       */
      __IOM uint32_t lo_vco_idac_cw_2456 : 5;   /*!< lo_vco_idac_cw_2456                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2456 : 8;   /*!< lo_vco_freq_cw_2456                                                       */
    } bit;
  } lo_cal_ctrl_hw7;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw8.                                                          */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2460 : 5;   /*!< lo_vco_idac_cw_2460                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2460 : 8;   /*!< lo_vco_freq_cw_2460                                                       */
      __IOM uint32_t lo_vco_idac_cw_2464 : 5;   /*!< lo_vco_idac_cw_2464                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2464 : 8;   /*!< lo_vco_freq_cw_2464                                                       */
    } bit;
  } lo_cal_ctrl_hw8;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw9.                                                          */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2468 : 5;   /*!< lo_vco_idac_cw_2468                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2468 : 8;   /*!< lo_vco_freq_cw_2468                                                       */
      __IOM uint32_t lo_vco_idac_cw_2472 : 5;   /*!< lo_vco_idac_cw_2472                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2472 : 8;   /*!< lo_vco_freq_cw_2472                                                       */
    } bit;
  } lo_cal_ctrl_hw9;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw10.                                                         */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2476 : 5;   /*!< lo_vco_idac_cw_2476                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2476 : 8;   /*!< lo_vco_freq_cw_2476                                                       */
      __IOM uint32_t lo_vco_idac_cw_2480 : 5;   /*!< lo_vco_idac_cw_2480                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2480 : 8;   /*!< lo_vco_freq_cw_2480                                                       */
    } bit;
  } lo_cal_ctrl_hw10;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_cal_ctrl_hw11.                                                         */
    
    struct {
      __IOM uint32_t lo_vco_idac_cw_2484 : 5;   /*!< lo_vco_idac_cw_2484                                                       */
            uint32_t            : 3;
      __IOM uint32_t lo_vco_freq_cw_2484 : 8;   /*!< lo_vco_freq_cw_2484                                                       */
            uint32_t            : 16;
    } bit;
  } lo_cal_ctrl_hw11;
  
  union {
    __IOM uint32_t reg;                         /*!< rosdac_ctrl_hw1.                                                          */
    
    struct {
      __IOM uint32_t rosdac_i_gc0 : 6;          /*!< rosdac_i_gc0                                                              */
            uint32_t            : 2;
      __IOM uint32_t rosdac_q_gc0 : 6;          /*!< rosdac_q_gc0                                                              */
            uint32_t            : 2;
      __IOM uint32_t rosdac_i_gc1 : 6;          /*!< rosdac_i_gc1                                                              */
            uint32_t            : 2;
      __IOM uint32_t rosdac_q_gc1 : 6;          /*!< rosdac_q_gc1                                                              */
            uint32_t            : 2;
    } bit;
  } rosdac_ctrl_hw1;
  
  union {
    __IOM uint32_t reg;                         /*!< rosdac_ctrl_hw2.                                                          */
    
    struct {
      __IOM uint32_t rosdac_i_gc2 : 6;          /*!< rosdac_i_gc2                                                              */
            uint32_t            : 2;
      __IOM uint32_t rosdac_q_gc2 : 6;          /*!< rosdac_q_gc2                                                              */
            uint32_t            : 2;
      __IOM uint32_t rosdac_i_gc3 : 6;          /*!< rosdac_i_gc3                                                              */
            uint32_t            : 2;
      __IOM uint32_t rosdac_q_gc3 : 6;          /*!< rosdac_q_gc3                                                              */
            uint32_t            : 2;
    } bit;
  } rosdac_ctrl_hw2;
  
  union {
    __IOM uint32_t reg;                         /*!< rxiq_ctrl_hw1.                                                            */
    
    struct {
      __IOM uint32_t rx_iq_phase_comp_gc0 : 10; /*!< rx_iq_phase_comp_gc0                                                      */
            uint32_t            : 6;
      __IOM uint32_t rx_iq_gain_comp_gc0 : 11;  /*!< rx_iq_gain_comp_gc0                                                       */
            uint32_t            : 5;
    } bit;
  } rxiq_ctrl_hw1;
  
  union {
    __IOM uint32_t reg;                         /*!< rxiq_ctrl_hw2.                                                            */
    
    struct {
      __IOM uint32_t rx_iq_phase_comp_gc1 : 10; /*!< rx_iq_phase_comp_gc1                                                      */
            uint32_t            : 6;
      __IOM uint32_t rx_iq_gain_comp_gc1 : 11;  /*!< rx_iq_gain_comp_gc1                                                       */
            uint32_t            : 5;
    } bit;
  } rxiq_ctrl_hw2;
  
  union {
    __IOM uint32_t reg;                         /*!< rxiq_ctrl_hw3.                                                            */
    
    struct {
      __IOM uint32_t rx_iq_phase_comp_gc2 : 10; /*!< rx_iq_phase_comp_gc2                                                      */
            uint32_t            : 6;
      __IOM uint32_t rx_iq_gain_comp_gc2 : 11;  /*!< rx_iq_gain_comp_gc2                                                       */
            uint32_t            : 5;
    } bit;
  } rxiq_ctrl_hw3;
  
  union {
    __IOM uint32_t reg;                         /*!< rxiq_ctrl_hw4.                                                            */
    
    struct {
      __IOM uint32_t rx_iq_phase_comp_gc3 : 10; /*!< rx_iq_phase_comp_gc3                                                      */
            uint32_t            : 6;
      __IOM uint32_t rx_iq_gain_comp_gc3 : 11;  /*!< rx_iq_gain_comp_gc3                                                       */
            uint32_t            : 5;
    } bit;
  } rxiq_ctrl_hw4;
  
  union {
    __IOM uint32_t reg;                         /*!< tosdac_ctrl_hw1.                                                          */
    
    struct {
      __IOM uint32_t tbb_tosdac_i_gc0 : 6;      /*!< tbb_tosdac_i_gc0                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_q_gc0 : 6;      /*!< tbb_tosdac_q_gc0                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_i_gc1 : 6;      /*!< tbb_tosdac_i_gc1                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_q_gc1 : 6;      /*!< tbb_tosdac_q_gc1                                                          */
            uint32_t            : 2;
    } bit;
  } tosdac_ctrl_hw1;
  
  union {
    __IOM uint32_t reg;                         /*!< tosdac_ctrl_hw2.                                                          */
    
    struct {
      __IOM uint32_t tbb_tosdac_i_gc2 : 6;      /*!< tbb_tosdac_i_gc2                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_q_gc2 : 6;      /*!< tbb_tosdac_q_gc2                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_i_gc3 : 6;      /*!< tbb_tosdac_i_gc3                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_q_gc3 : 6;      /*!< tbb_tosdac_q_gc3                                                          */
            uint32_t            : 2;
    } bit;
  } tosdac_ctrl_hw2;
  
  union {
    __IOM uint32_t reg;                         /*!< tosdac_ctrl_hw3.                                                          */
    
    struct {
      __IOM uint32_t tbb_tosdac_i_gc4 : 6;      /*!< tbb_tosdac_i_gc4                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_q_gc4 : 6;      /*!< tbb_tosdac_q_gc4                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_i_gc5 : 6;      /*!< tbb_tosdac_i_gc5                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_q_gc5 : 6;      /*!< tbb_tosdac_q_gc5                                                          */
            uint32_t            : 2;
    } bit;
  } tosdac_ctrl_hw3;
  
  union {
    __IOM uint32_t reg;                         /*!< tosdac_ctrl_hw4.                                                          */
    
    struct {
      __IOM uint32_t tbb_tosdac_i_gc6 : 6;      /*!< tbb_tosdac_i_gc6                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_q_gc6 : 6;      /*!< tbb_tosdac_q_gc6                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_i_gc7 : 6;      /*!< tbb_tosdac_i_gc7                                                          */
            uint32_t            : 2;
      __IOM uint32_t tbb_tosdac_q_gc7 : 6;      /*!< tbb_tosdac_q_gc7                                                          */
            uint32_t            : 2;
    } bit;
  } tosdac_ctrl_hw4;
  
  union {
    __IOM uint32_t reg;                         /*!< tx_iq_gain_hw0.                                                           */
    
    struct {
      __IOM uint32_t tx_iq_phase_comp_gc0 : 10; /*!< tx_iq_phase_comp_gc0                                                      */
            uint32_t            : 6;
      __IOM uint32_t tx_iq_gain_comp_gc0 : 11;  /*!< tx_iq_gain_comp_gc0                                                       */
            uint32_t            : 5;
    } bit;
  } tx_iq_gain_hw0;
  
  union {
    __IOM uint32_t reg;                         /*!< tx_iq_gain_hw1.                                                           */
    
    struct {
      __IOM uint32_t tx_iq_phase_comp_gc1 : 10; /*!< tx_iq_phase_comp_gc1                                                      */
            uint32_t            : 6;
      __IOM uint32_t tx_iq_gain_comp_gc1 : 11;  /*!< tx_iq_gain_comp_gc1                                                       */
            uint32_t            : 5;
    } bit;
  } tx_iq_gain_hw1;
  
  union {
    __IOM uint32_t reg;                         /*!< tx_iq_gain_hw2.                                                           */
    
    struct {
      __IOM uint32_t tx_iq_phase_comp_gc2 : 10; /*!< tx_iq_phase_comp_gc2                                                      */
            uint32_t            : 6;
      __IOM uint32_t tx_iq_gain_comp_gc2 : 11;  /*!< tx_iq_gain_comp_gc2                                                       */
            uint32_t            : 5;
    } bit;
  } tx_iq_gain_hw2;
  
  union {
    __IOM uint32_t reg;                         /*!< tx_iq_gain_hw3.                                                           */
    
    struct {
      __IOM uint32_t tx_iq_phase_comp_gc3 : 10; /*!< tx_iq_phase_comp_gc3                                                      */
            uint32_t            : 6;
      __IOM uint32_t tx_iq_gain_comp_gc3 : 11;  /*!< tx_iq_gain_comp_gc3                                                       */
            uint32_t            : 5;
    } bit;
  } tx_iq_gain_hw3;
  
  union {
    __IOM uint32_t reg;                         /*!< tx_iq_gain_hw4.                                                           */
    
    struct {
      __IOM uint32_t tx_iq_phase_comp_gc4 : 10; /*!< tx_iq_phase_comp_gc4                                                      */
            uint32_t            : 6;
      __IOM uint32_t tx_iq_gain_comp_gc4 : 11;  /*!< tx_iq_gain_comp_gc4                                                       */
            uint32_t            : 5;
    } bit;
  } tx_iq_gain_hw4;
  
  union {
    __IOM uint32_t reg;                         /*!< tx_iq_gain_hw5.                                                           */
    
    struct {
      __IOM uint32_t tx_iq_phase_comp_gc5 : 10; /*!< tx_iq_phase_comp_gc5                                                      */
            uint32_t            : 6;
      __IOM uint32_t tx_iq_gain_comp_gc5 : 11;  /*!< tx_iq_gain_comp_gc5                                                       */
            uint32_t            : 5;
    } bit;
  } tx_iq_gain_hw5;
  
  union {
    __IOM uint32_t reg;                         /*!< tx_iq_gain_hw6.                                                           */
    
    struct {
      __IOM uint32_t tx_iq_phase_comp_gc6 : 10; /*!< tx_iq_phase_comp_gc6                                                      */
            uint32_t            : 6;
      __IOM uint32_t tx_iq_gain_comp_gc6 : 11;  /*!< tx_iq_gain_comp_gc6                                                       */
            uint32_t            : 5;
    } bit;
  } tx_iq_gain_hw6;
  
  union {
    __IOM uint32_t reg;                         /*!< tx_iq_gain_hw7.                                                           */
    
    struct {
      __IOM uint32_t tx_iq_phase_comp_gc7 : 10; /*!< tx_iq_phase_comp_gc7                                                      */
            uint32_t            : 6;
      __IOM uint32_t tx_iq_gain_comp_gc7 : 11;  /*!< tx_iq_gain_comp_gc7                                                       */
            uint32_t            : 5;
    } bit;
  } tx_iq_gain_hw7;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_sdm_ctrl_hw1.                                                          */
    
    struct {
      __IOM uint32_t lo_sdm_dither_sel_wlan_2412 : 2;/*!< lo_sdm_dither_sel_wlan_2412                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2417 : 2;/*!< lo_sdm_dither_sel_wlan_2417                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2422 : 2;/*!< lo_sdm_dither_sel_wlan_2422                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2427 : 2;/*!< lo_sdm_dither_sel_wlan_2427                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2432 : 2;/*!< lo_sdm_dither_sel_wlan_2432                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2437 : 2;/*!< lo_sdm_dither_sel_wlan_2437                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2442 : 2;/*!< lo_sdm_dither_sel_wlan_2442                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2447 : 2;/*!< lo_sdm_dither_sel_wlan_2447                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2452 : 2;/*!< lo_sdm_dither_sel_wlan_2452                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2457 : 2;/*!< lo_sdm_dither_sel_wlan_2457                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2462 : 2;/*!< lo_sdm_dither_sel_wlan_2462                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2467 : 2;/*!< lo_sdm_dither_sel_wlan_2467                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2472 : 2;/*!< lo_sdm_dither_sel_wlan_2472                                          */
      __IOM uint32_t lo_sdm_dither_sel_wlan_2484 : 2;/*!< lo_sdm_dither_sel_wlan_2484                                          */
            uint32_t            : 4;
    } bit;
  } lo_sdm_ctrl_hw1;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_sdm_ctrl_hw2.                                                          */
    
    struct {
      __IOM uint32_t lo_sdm_dither_sel_ble_2402 : 2;/*!< lo_sdm_dither_sel_ble_2402                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2404 : 2;/*!< lo_sdm_dither_sel_ble_2404                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2406 : 2;/*!< lo_sdm_dither_sel_ble_2406                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2408 : 2;/*!< lo_sdm_dither_sel_ble_2408                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2410 : 2;/*!< lo_sdm_dither_sel_ble_2410                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2412 : 2;/*!< lo_sdm_dither_sel_ble_2412                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2414 : 2;/*!< lo_sdm_dither_sel_ble_2414                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2416 : 2;/*!< lo_sdm_dither_sel_ble_2416                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2418 : 2;/*!< lo_sdm_dither_sel_ble_2418                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2420 : 2;/*!< lo_sdm_dither_sel_ble_2420                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2422 : 2;/*!< lo_sdm_dither_sel_ble_2422                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2424 : 2;/*!< lo_sdm_dither_sel_ble_2424                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2426 : 2;/*!< lo_sdm_dither_sel_ble_2426                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2428 : 2;/*!< lo_sdm_dither_sel_ble_2428                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2430 : 2;/*!< lo_sdm_dither_sel_ble_2430                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2432 : 2;/*!< lo_sdm_dither_sel_ble_2432                                            */
    } bit;
  } lo_sdm_ctrl_hw2;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_sdm_ctrl_hw3.                                                          */
    
    struct {
      __IOM uint32_t lo_sdm_dither_sel_ble_2434 : 2;/*!< lo_sdm_dither_sel_ble_2434                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2436 : 2;/*!< lo_sdm_dither_sel_ble_2436                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2438 : 2;/*!< lo_sdm_dither_sel_ble_2438                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2440 : 2;/*!< lo_sdm_dither_sel_ble_2440                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2442 : 2;/*!< lo_sdm_dither_sel_ble_2442                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2444 : 2;/*!< lo_sdm_dither_sel_ble_2444                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2446 : 2;/*!< lo_sdm_dither_sel_ble_2446                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2448 : 2;/*!< lo_sdm_dither_sel_ble_2448                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2450 : 2;/*!< lo_sdm_dither_sel_ble_2450                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2452 : 2;/*!< lo_sdm_dither_sel_ble_2452                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2454 : 2;/*!< lo_sdm_dither_sel_ble_2454                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2456 : 2;/*!< lo_sdm_dither_sel_ble_2456                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2458 : 2;/*!< lo_sdm_dither_sel_ble_2458                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2460 : 2;/*!< lo_sdm_dither_sel_ble_2460                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2462 : 2;/*!< lo_sdm_dither_sel_ble_2462                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2464 : 2;/*!< lo_sdm_dither_sel_ble_2464                                            */
    } bit;
  } lo_sdm_ctrl_hw3;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_sdm_ctrl_hw4.                                                          */
    
    struct {
      __IOM uint32_t lo_sdm_dither_sel_ble_2466 : 2;/*!< lo_sdm_dither_sel_ble_2466                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2468 : 2;/*!< lo_sdm_dither_sel_ble_2468                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2470 : 2;/*!< lo_sdm_dither_sel_ble_2470                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2472 : 2;/*!< lo_sdm_dither_sel_ble_2472                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2474 : 2;/*!< lo_sdm_dither_sel_ble_2474                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2476 : 2;/*!< lo_sdm_dither_sel_ble_2476                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2478 : 2;/*!< lo_sdm_dither_sel_ble_2478                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_2480 : 2;/*!< lo_sdm_dither_sel_ble_2480                                            */
      __IOM uint32_t lo_sdm_dither_sel_ble_tx : 2;/*!< lo_sdm_dither_sel_ble_tx                                                */
            uint32_t            : 14;
    } bit;
  } lo_sdm_ctrl_hw4;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_sdm_ctrl_hw5.                                                          */
    
    struct {
      __IOM uint32_t lo_center_freq_mhz : 12;   /*!< lo_center_freq_mhz                                                        */
      __IOM uint32_t lo_sdm_bypass_mode : 6;    /*!< lo_sdm_bypass_mode                                                        */
            uint32_t            : 14;
    } bit;
  } lo_sdm_ctrl_hw5;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_sdm_ctrl_hw6.                                                          */
    
    struct {
      __IOM uint32_t lo_sdmin_center : 29;      /*!< lo_sdmin_center                                                           */
            uint32_t            : 3;
    } bit;
  } lo_sdm_ctrl_hw6;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_sdm_ctrl_hw7.                                                          */
    
    struct {
      __IOM uint32_t lo_sdmin_1m : 20;          /*!< lo_sdmin_1m                                                               */
            uint32_t            : 12;
    } bit;
  } lo_sdm_ctrl_hw7;
  
  union {
    __IOM uint32_t reg;                         /*!< lo_sdm_ctrl_hw8.                                                          */
    
    struct {
      __IOM uint32_t lo_sdmin_if : 20;          /*!< lo_sdmin_if                                                               */
            uint32_t            : 12;
    } bit;
  } lo_sdm_ctrl_hw8;
  
  union {
    __IOM uint32_t reg;                         /*!< rbb_bw_ctrl_hw.                                                           */
    
    struct {
      __IOM uint32_t rbb_bt_mode_ble : 1;       /*!< rbb_bt_mode_ble                                                           */
            uint32_t            : 31;
    } bit;
  } rbb_bw_ctrl_hw;
  __IM  uint32_t  RESERVED2[14];
  
  union {
    __IOM uint32_t reg;                         /*!< singen_ctrl0.                                                             */
    
    struct {
      __IOM uint32_t singen_inc_step1 : 10;     /*!< singen_inc_step1                                                          */
            uint32_t            : 6;
      __IOM uint32_t singen_inc_step0 : 10;     /*!< singen_inc_step0                                                          */
            uint32_t            : 2;
      __IOM uint32_t singen_unsign_en : 1;      /*!< singen_unsign_en                                                          */
      __IOM uint32_t singen_clkdiv_n : 2;       /*!< singen_clkdiv_n                                                           */
      __IOM uint32_t singen_en  : 1;            /*!< singen_en                                                                 */
    } bit;
  } singen_ctrl0;
  
  union {
    __IOM uint32_t reg;                         /*!< singen_ctrl1.                                                             */
    
    struct {
      __IOM uint32_t singen_clkdiv_q : 10;      /*!< singen_clkdiv_q                                                           */
            uint32_t            : 2;
      __IOM uint32_t singen_mode_q : 4;         /*!< singen_mode_q                                                             */
      __IOM uint32_t singen_clkdiv_i : 10;      /*!< singen_clkdiv_i                                                           */
            uint32_t            : 2;
      __IOM uint32_t singen_mode_i : 4;         /*!< singen_mode_i                                                             */
    } bit;
  } singen_ctrl1;
  
  union {
    __IOM uint32_t reg;                         /*!< singen_ctrl2.                                                             */
    
    struct {
      __IOM uint32_t singen_gain_i : 11;        /*!< singen_gain_i                                                             */
            uint32_t            : 1;
      __IOM uint32_t singen_start_addr1_i : 10; /*!< singen_start_addr1_i                                                      */
      __IOM uint32_t singen_start_addr0_i : 10; /*!< singen_start_addr0_i                                                      */
    } bit;
  } singen_ctrl2;
  
  union {
    __IOM uint32_t reg;                         /*!< singen_ctrl3.                                                             */
    
    struct {
      __IOM uint32_t singen_gain_q : 11;        /*!< singen_gain_q                                                             */
            uint32_t            : 1;
      __IOM uint32_t singen_start_addr1_q : 10; /*!< singen_start_addr1_q                                                      */
      __IOM uint32_t singen_start_addr0_q : 10; /*!< singen_start_addr0_q                                                      */
    } bit;
  } singen_ctrl3;
  
  union {
    __IOM uint32_t reg;                         /*!< singen_ctrl4.                                                             */
    
    struct {
      __IOM uint32_t singen_fix_q : 12;         /*!< singen_fix_q                                                              */
      __IOM uint32_t singen_fix_en_q : 1;       /*!< singen_fix_en_q                                                           */
            uint32_t            : 3;
      __IOM uint32_t singen_fix_i : 12;         /*!< singen_fix_i                                                              */
      __IOM uint32_t singen_fix_en_i : 1;       /*!< singen_fix_en_i                                                           */
            uint32_t            : 3;
    } bit;
  } singen_ctrl4;
  
  union {
    __IOM uint32_t reg;                         /*!< rfif_dfe_ctrl0.                                                           */
    
    struct {
      __IOM uint32_t rfckg_rxclk_4s_on : 1;     /*!< rfckg_rxclk_4s_on                                                         */
      __IOM uint32_t rfckg_txclk_4s_on : 1;     /*!< rfckg_txclk_4s_on                                                         */
      __IOM uint32_t rfckg_adc_afifo_inv : 1;   /*!< rfckg_adc_afifo_inv                                                       */
      __IOM uint32_t rfckg_adc_clkout_sel : 1;  /*!< rfckg_adc_clkout_sel                                                      */
      __IOM uint32_t rfckg_dac_afifo_inv : 1;   /*!< rfckg_dac_afifo_inv                                                       */
      __IOM uint32_t rx_dfe_en_4s : 1;          /*!< rx_dfe_en_4s                                                              */
      __IOM uint32_t rx_dfe_en_4s_en : 1;       /*!< rx_dfe_en_4s_en                                                           */
      __IOM uint32_t tx_dfe_en_4s : 1;          /*!< tx_dfe_en_4s                                                              */
      __IOM uint32_t tx_dfe_en_4s_en : 1;       /*!< tx_dfe_en_4s_en                                                           */
      __IOM uint32_t rx_test_sel : 2;           /*!< rx_test_sel                                                               */
      __IOM uint32_t tx_test_sel : 2;           /*!< tx_test_sel                                                               */
      __IOM uint32_t pad_adc_clkout_inv_en : 1; /*!< pad_adc_clkout_inv_en                                                     */
      __IOM uint32_t pad_dac_clkout_inv_en : 1; /*!< pad_dac_clkout_inv_en                                                     */
      __IOM uint32_t rf_ch_ind_ble_4s : 7;      /*!< rf_ch_ind_ble_4s                                                          */
      __IOM uint32_t rf_ch_ind_ble_4s_en : 1;   /*!< rf_ch_ind_ble_4s_en                                                       */
      __IOM uint32_t wifimode_4s : 2;           /*!< wifimode_4s                                                               */
      __IOM uint32_t wifimode_4s_en : 1;        /*!< wifimode_4s_en                                                            */
      __IOM uint32_t bbmode_4s  : 1;            /*!< bbmode_4s                                                                 */
      __IOM uint32_t bbmode_4s_en : 1;          /*!< bbmode_4s_en                                                              */
      __IOM uint32_t test_sel   : 4;            /*!< test_sel                                                                  */
    } bit;
  } rfif_dfe_ctrl0;
  
  union {
    __IOM uint32_t reg;                         /*!< rfif_test_read.                                                           */
    
    struct {
      __IOM uint32_t test_read  : 32;           /*!< test_read                                                                 */
    } bit;
  } rfif_test_read;
  
  union {
    __IOM uint32_t reg;                         /*!< rfif_dig_ctrl.                                                            */
    
    struct {
      __IOM uint32_t test_from_pad_en : 1;      /*!< test_from_pad_en                                                          */
      __IOM uint32_t test_gc_from_pad_en : 1;   /*!< test_gc_from_pad_en                                                       */
      __IOM uint32_t rfckg_rxclk_div2_mode : 1; /*!< rfckg_rxclk_div2_mode                                                     */
      __IOM uint32_t rfif_int_lo_unlocked_mask : 1;/*!< rfif_int_lo_unlocked_mask                                              */
            uint32_t            : 12;
      __IOM uint32_t rfif_ppud_cnt2 : 9;        /*!< rfif_ppud_cnt2                                                            */
      __IOM uint32_t rfif_ppud_cnt1 : 5;        /*!< rfif_ppud_cnt1                                                            */
      __IOM uint32_t rfif_ppud_manaual_en : 1;  /*!< rfif_ppud_manaual_en                                                      */
            uint32_t            : 1;
    } bit;
  } rfif_dig_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_data_temp_0.                                                           */
    
    struct {
      __IOM uint32_t rf_data_temp_0 : 32;       /*!< rf_data_temp_0                                                            */
    } bit;
  } rf_data_temp_0;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_data_temp_1.                                                           */
    
    struct {
      __IOM uint32_t rf_data_temp_1 : 32;       /*!< rf_data_temp_1                                                            */
    } bit;
  } rf_data_temp_1;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_data_temp_2.                                                           */
    
    struct {
      __IOM uint32_t rf_data_temp_2 : 32;       /*!< rf_data_temp_2                                                            */
    } bit;
  } rf_data_temp_2;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_data_temp_3.                                                           */
    
    struct {
      __IOM uint32_t rf_data_temp_3 : 32;       /*!< rf_data_temp_3                                                            */
    } bit;
  } rf_data_temp_3;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_sram_ctrl0.                                                            */
    
    struct {
      __IOM uint32_t rf_sram_link_dly : 16;     /*!< rf_sram_link_dly                                                          */
      __IOM uint32_t rf_sram_link_mode : 2;     /*!< rf_sram_link_mode                                                         */
      __IOM uint32_t rf_sram_swap : 1;          /*!< rf_sram_swap                                                              */
      __IOM uint32_t rf_sram_ext_clr : 1;       /*!< rf_sram_ext_clr                                                           */
            uint32_t            : 12;
    } bit;
  } rf_sram_ctrl0;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_sram_ctrl1.                                                            */
    
    struct {
      __IOM uint32_t rf_sram_adc_done : 1;      /*!< rf_sram_adc_done                                                          */
      __IOM uint32_t rf_sram_adc_en : 1;        /*!< rf_sram_adc_en                                                            */
      __IOM uint32_t rf_sram_adc_loop_en : 1;   /*!< rf_sram_adc_loop_en                                                       */
      __IOM uint32_t rf_sram_adc_sts_clr : 1;   /*!< rf_sram_adc_sts_clr                                                       */
            uint32_t            : 12;
      __IOM uint32_t rf_sram_adc_done_cnt : 16; /*!< rf_sram_adc_done_cnt                                                      */
    } bit;
  } rf_sram_ctrl1;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_sram_ctrl2.                                                            */
    
    struct {
      __IOM uint32_t rf_sram_adc_addr_end : 16; /*!< rf_sram_adc_addr_end                                                      */
      __IOM uint32_t rf_sram_adc_addr_start : 16;/*!< rf_sram_adc_addr_start                                                   */
    } bit;
  } rf_sram_ctrl2;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_sram_ctrl3.                                                            */
    
    struct {
      __IOM uint32_t rf_sram_adc_sts : 32;      /*!< rf_sram_adc_sts                                                           */
    } bit;
  } rf_sram_ctrl3;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_sram_ctrl4.                                                            */
    
    struct {
      __IOM uint32_t rf_sram_dac_done : 1;      /*!< rf_sram_dac_done                                                          */
      __IOM uint32_t rf_sram_dac_en : 1;        /*!< rf_sram_dac_en                                                            */
      __IOM uint32_t rf_sram_dac_loop_en : 1;   /*!< rf_sram_dac_loop_en                                                       */
      __IOM uint32_t rf_sram_dac_sts_clr : 1;   /*!< rf_sram_dac_sts_clr                                                       */
            uint32_t            : 12;
      __IOM uint32_t rf_sram_dac_done_cnt : 16; /*!< rf_sram_dac_done_cnt                                                      */
    } bit;
  } rf_sram_ctrl4;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_sram_ctrl5.                                                            */
    
    struct {
      __IOM uint32_t rf_sram_dac_addr_end : 16; /*!< rf_sram_dac_addr_end                                                      */
      __IOM uint32_t rf_sram_dac_addr_start : 16;/*!< rf_sram_dac_addr_start                                                   */
    } bit;
  } rf_sram_ctrl5;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_sram_ctrl6.                                                            */
    
    struct {
      __IOM uint32_t rf_sram_dac_sts : 32;      /*!< rf_sram_dac_sts                                                           */
    } bit;
  } rf_sram_ctrl6;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_ical_ctrl0.                                                            */
    
    struct {
      __IOM uint32_t rf_ical_r_cnt_n : 10;      /*!< rf_ical_r_cnt_n                                                           */
      __IOM uint32_t rf_ical_a_cnt_n : 10;      /*!< rf_ical_a_cnt_n                                                           */
      __IOM uint32_t rf_ical_f_cnt_n : 10;      /*!< rf_ical_f_cnt_n                                                           */
      __IOM uint32_t rf_ical_a_ud_inv_en : 1;   /*!< rf_ical_a_ud_inv_en                                                       */
      __IOM uint32_t rf_ical_f_ud_inv_en : 1;   /*!< rf_ical_f_ud_inv_en                                                       */
    } bit;
  } rf_ical_ctrl0;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_ical_ctrl1.                                                            */
    
    struct {
      __IOM uint32_t rf_ical_r_avg_n : 5;       /*!< rf_ical_r_avg_n                                                           */
            uint32_t            : 5;
      __IOM uint32_t rf_ical_r_os_q : 10;       /*!< rf_ical_r_os_q                                                            */
      __IOM uint32_t rf_ical_r_os_i : 10;       /*!< rf_ical_r_os_i                                                            */
            uint32_t            : 2;
    } bit;
  } rf_ical_ctrl1;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_ical_ctrl2.                                                            */
    
    struct {
      __IOM uint32_t rf_ical_period_n : 16;     /*!< rf_ical_period_n                                                          */
            uint32_t            : 16;
    } bit;
  } rf_ical_ctrl2;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_fsm_ctrl0.                                                             */
    
    struct {
      __IOM uint32_t rf_ch_ind_wifi : 12;       /*!< rf_ch_ind_wifi                                                            */
            uint32_t            : 20;
    } bit;
  } rf_fsm_ctrl0;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_fsm_ctrl1.                                                             */
    
    struct {
      __IOM uint32_t rf_fsm_lo_time : 16;       /*!< rf_fsm_lo_time                                                            */
      __IOM uint32_t rf_fsm_lo_rdy : 1;         /*!< rf_fsm_lo_rdy                                                             */
      __IOM uint32_t rf_fsm_lo_rdy_rst : 1;     /*!< rf_fsm_lo_rdy_rst                                                         */
      __IOM uint32_t rf_fsm_lo_rdy_4s_1 : 1;    /*!< rf_fsm_lo_rdy_4s_1                                                        */
      __IOM uint32_t rf_fsm_lo_rdy_sbclr : 1;   /*!< rf_fsm_lo_rdy_sbclr                                                       */
      __IOM uint32_t rf_fsm_pu_pa_dly_n : 10;   /*!< rf_fsm_pu_pa_dly_n                                                        */
            uint32_t            : 2;
    } bit;
  } rf_fsm_ctrl1;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_fsm_ctrl2.                                                             */
    
    struct {
      __IOM uint32_t rf_fsm_st_dbg : 3;         /*!< rf_fsm_st_dbg                                                             */
      __IOM uint32_t rf_fsm_st_dbg_en : 1;      /*!< rf_fsm_st_dbg_en                                                          */
      __IOM uint32_t rf_trx_en_ble_4s : 1;      /*!< rf_trx_en_ble_4s                                                          */
      __IOM uint32_t rf_trx_sw_ble_4s : 1;      /*!< rf_trx_sw_ble_4s                                                          */
      __IOM uint32_t rf_trx_ble_4s_en : 1;      /*!< rf_trx_ble_4s_en                                                          */
            uint32_t            : 3;
      __IOM uint32_t rf_fsm_dfe_tx_dly_n : 10;  /*!< rf_fsm_dfe_tx_dly_n                                                       */
      __IOM uint32_t rf_fsm_dfe_rx_dly_n : 10;  /*!< rf_fsm_dfe_rx_dly_n                                                       */
            uint32_t            : 2;
    } bit;
  } rf_fsm_ctrl2;
  
  union {
    __IOM uint32_t reg;                         /*!< rf_pkdet_ctrl0.                                                           */
    
    struct {
      __IOM uint32_t pkdet_out_cnt_sts : 4;     /*!< pkdet_out_cnt_sts                                                         */
      __IOM uint32_t pkdet_out_cnt_en : 1;      /*!< pkdet_out_cnt_en                                                          */
      __IOM uint32_t pkdet_out_mode : 1;        /*!< pkdet_out_mode                                                            */
            uint32_t            : 26;
    } bit;
  } rf_pkdet_ctrl0;
  __IM  uint32_t  RESERVED3[227];
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_0.                                                               */
    
    struct {
      __IOM uint32_t tx_iqc_phase : 10;         /*!< tx_iqc_phase                                                              */
      __IOM uint32_t tx_iqc_phase_en : 1;       /*!< tx_iqc_phase_en                                                           */
            uint32_t            : 1;
      __IOM uint32_t tx_iqc_gain : 11;          /*!< tx_iqc_gain                                                               */
      __IOM uint32_t tx_iqc_gain_en : 1;        /*!< tx_iqc_gain_en                                                            */
      __IOM uint32_t tx_dvga_gain_qdb : 7;      /*!< tx_dvga_gain_qdb                                                          */
      __IOM uint32_t tx_dvga_gain_ctrl_hw : 1;  /*!< tx_dvga_gain_ctrl_hw                                                      */
    } bit;
  } dfe_ctrl_0;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_1.                                                               */
    
    struct {
      __IOM uint32_t tx_dac_os_i : 12;          /*!< tx_dac_os_i                                                               */
            uint32_t            : 4;
      __IOM uint32_t tx_dac_os_q : 12;          /*!< tx_dac_os_q                                                               */
            uint32_t            : 2;
      __IOM uint32_t tx_dac_dat_format : 1;     /*!< tx_dac_dat_format                                                         */
      __IOM uint32_t tx_dac_iq_swap : 1;        /*!< tx_dac_iq_swap                                                            */
    } bit;
  } dfe_ctrl_1;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_2.                                                               */
    
    struct {
      __IOM uint32_t rx_adc_os_i : 10;          /*!< rx_adc_os_i                                                               */
            uint32_t            : 6;
      __IOM uint32_t rx_adc_os_q : 10;          /*!< rx_adc_os_q                                                               */
            uint32_t            : 2;
      __IOM uint32_t rx_adc_dce_flt_en : 1;     /*!< rx_adc_dce_flt_en                                                         */
      __IOM uint32_t rx_adc_low_pow_en : 1;     /*!< rx_adc_low_pow_en                                                         */
      __IOM uint32_t rx_adc_dat_format : 1;     /*!< rx_adc_dat_format                                                         */
      __IOM uint32_t rx_adc_iq_swap : 1;        /*!< rx_adc_iq_swap                                                            */
    } bit;
  } dfe_ctrl_2;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_3.                                                               */
    
    struct {
      __IOM uint32_t rx_adc_4s_i_val : 10;      /*!< rx_adc_4s_i_val                                                           */
      __IOM uint32_t rx_adc_4s_i_en : 1;        /*!< rx_adc_4s_i_en                                                            */
            uint32_t            : 5;
      __IOM uint32_t rx_adc_4s_q_val : 10;      /*!< rx_adc_4s_q_val                                                           */
      __IOM uint32_t rx_adc_4s_q_en : 1;        /*!< rx_adc_4s_q_en                                                            */
            uint32_t            : 5;
    } bit;
  } dfe_ctrl_3;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_4.                                                               */
    
    struct {
      __IOM uint32_t rx_pf_th2  : 10;           /*!< rx_pf_th2                                                                 */
            uint32_t            : 6;
      __IOM uint32_t rx_pf_th1  : 10;           /*!< rx_pf_th1                                                                 */
            uint32_t            : 4;
      __IOM uint32_t rx_pf_q_en : 1;            /*!< rx_pf_q_en                                                                */
      __IOM uint32_t rx_pf_i_en : 1;            /*!< rx_pf_i_en                                                                */
    } bit;
  } dfe_ctrl_4;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_5.                                                               */
    
    struct {
      __IOM uint32_t rx_iqc_phase : 10;         /*!< rx_iqc_phase                                                              */
      __IOM uint32_t rx_iqc_phase_en : 1;       /*!< rx_iqc_phase_en                                                           */
            uint32_t            : 1;
      __IOM uint32_t rx_iqc_gain : 11;          /*!< rx_iqc_gain                                                               */
      __IOM uint32_t rx_iqc_gain_en : 1;        /*!< rx_iqc_gain_en                                                            */
            uint32_t            : 8;
    } bit;
  } dfe_ctrl_5;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_6.                                                               */
    
    struct {
      __IOM uint32_t rx_pm_freqshift_cw : 20;   /*!< rx_pm_freqshift_cw                                                        */
      __IOM uint32_t rx_pm_freqshift_en : 1;    /*!< rx_pm_freqshift_en                                                        */
            uint32_t            : 7;
      __IOM uint32_t rx_pm_done : 1;            /*!< rx_pm_done                                                                */
      __IOM uint32_t rx_pm_en   : 1;            /*!< rx_pm_en                                                                  */
      __IOM uint32_t rx_pm_in_sel : 2;          /*!< rx_pm_in_sel                                                              */
    } bit;
  } dfe_ctrl_6;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_7.                                                               */
    
    struct {
      __IOM uint32_t rx_pm_start_ofs : 16;      /*!< rx_pm_start_ofs                                                           */
      __IOM uint32_t rx_pm_acc_len : 16;        /*!< rx_pm_acc_len                                                             */
    } bit;
  } dfe_ctrl_7;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_8.                                                               */
    
    struct {
      __IOM uint32_t rx_pm_iqacc_i : 25;        /*!< rx_pm_iqacc_i                                                             */
            uint32_t            : 7;
    } bit;
  } dfe_ctrl_8;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_9.                                                               */
    
    struct {
      __IOM uint32_t rx_pm_iqacc_q : 25;        /*!< rx_pm_iqacc_q                                                             */
            uint32_t            : 7;
    } bit;
  } dfe_ctrl_9;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_10.                                                              */
    
    struct {
      __IOM uint32_t dfe_dac_raw_i : 11;        /*!< dfe_dac_raw_i                                                             */
            uint32_t            : 5;
      __IOM uint32_t dfe_dac_raw_q : 11;        /*!< dfe_dac_raw_q                                                             */
            uint32_t            : 5;
    } bit;
  } dfe_ctrl_10;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_11.                                                              */
    
    struct {
      __IOM uint32_t dfe_adc_raw_i : 10;        /*!< dfe_adc_raw_i                                                             */
            uint32_t            : 6;
      __IOM uint32_t dfe_adc_raw_q : 10;        /*!< dfe_adc_raw_q                                                             */
            uint32_t            : 6;
    } bit;
  } dfe_ctrl_11;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_12.                                                              */
    
    struct {
      __IOM uint32_t tx_dvga_gain_qdb_gc0 : 7;  /*!< tx_dvga_gain_qdb_gc0                                                      */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc1 : 7;  /*!< tx_dvga_gain_qdb_gc1                                                      */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc2 : 7;  /*!< tx_dvga_gain_qdb_gc2                                                      */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc3 : 7;  /*!< tx_dvga_gain_qdb_gc3                                                      */
            uint32_t            : 1;
    } bit;
  } dfe_ctrl_12;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_13.                                                              */
    
    struct {
      __IOM uint32_t tx_dvga_gain_qdb_gc4 : 7;  /*!< tx_dvga_gain_qdb_gc4                                                      */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc5 : 7;  /*!< tx_dvga_gain_qdb_gc5                                                      */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc6 : 7;  /*!< tx_dvga_gain_qdb_gc6                                                      */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc7 : 7;  /*!< tx_dvga_gain_qdb_gc7                                                      */
            uint32_t            : 1;
    } bit;
  } dfe_ctrl_13;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_14.                                                              */
    
    struct {
      __IOM uint32_t tx_dvga_gain_qdb_gc8 : 7;  /*!< tx_dvga_gain_qdb_gc8                                                      */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc9 : 7;  /*!< tx_dvga_gain_qdb_gc9                                                      */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc10 : 7; /*!< tx_dvga_gain_qdb_gc10                                                     */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc11 : 7; /*!< tx_dvga_gain_qdb_gc11                                                     */
            uint32_t            : 1;
    } bit;
  } dfe_ctrl_14;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_15.                                                              */
    
    struct {
      __IOM uint32_t tx_dvga_gain_qdb_gc12 : 7; /*!< tx_dvga_gain_qdb_gc12                                                     */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc13 : 7; /*!< tx_dvga_gain_qdb_gc13                                                     */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc14 : 7; /*!< tx_dvga_gain_qdb_gc14                                                     */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_gc15 : 7; /*!< tx_dvga_gain_qdb_gc15                                                     */
            uint32_t            : 1;
    } bit;
  } dfe_ctrl_15;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_16.                                                              */
    
    struct {
      __IOM uint32_t rf_tbb_ind_gc0 : 3;        /*!< rf_tbb_ind_gc0                                                            */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc1 : 3;        /*!< rf_tbb_ind_gc1                                                            */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc2 : 3;        /*!< rf_tbb_ind_gc2                                                            */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc3 : 3;        /*!< rf_tbb_ind_gc3                                                            */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc4 : 3;        /*!< rf_tbb_ind_gc4                                                            */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc5 : 3;        /*!< rf_tbb_ind_gc5                                                            */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc6 : 3;        /*!< rf_tbb_ind_gc6                                                            */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc7 : 3;        /*!< rf_tbb_ind_gc7                                                            */
            uint32_t            : 1;
    } bit;
  } dfe_ctrl_16;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_17.                                                              */
    
    struct {
      __IOM uint32_t rf_tbb_ind_gc8 : 3;        /*!< rf_tbb_ind_gc8                                                            */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc9 : 3;        /*!< rf_tbb_ind_gc9                                                            */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc10 : 3;       /*!< rf_tbb_ind_gc10                                                           */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc11 : 3;       /*!< rf_tbb_ind_gc11                                                           */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc12 : 3;       /*!< rf_tbb_ind_gc12                                                           */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc13 : 3;       /*!< rf_tbb_ind_gc13                                                           */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc14 : 3;       /*!< rf_tbb_ind_gc14                                                           */
            uint32_t            : 1;
      __IOM uint32_t rf_tbb_ind_gc15 : 3;       /*!< rf_tbb_ind_gc15                                                           */
            uint32_t            : 1;
    } bit;
  } dfe_ctrl_17;
  
  union {
    __IOM uint32_t reg;                         /*!< dfe_ctrl_18.                                                              */
    
    struct {
      __IOM uint32_t tx_dvga_gain_qdb_ble_gc0 : 7;/*!< tx_dvga_gain_qdb_ble_gc0                                                */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_ble_gc1 : 7;/*!< tx_dvga_gain_qdb_ble_gc1                                                */
            uint32_t            : 1;
      __IOM uint32_t tx_dvga_gain_qdb_ble_gc2 : 7;/*!< tx_dvga_gain_qdb_ble_gc2                                                */
            uint32_t            : 9;
    } bit;
  } dfe_ctrl_18;
} rf_Type;                                      /*!< Size = 1612 (0x64c)                                                       */



/* =========================================================================================================================== */
/* ================                                           gpip                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief gpip. (gpip)
  */

typedef struct {                                /*!< gpip Structure                                                            */
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_config.                                                             */
    
    struct {
      __IOM uint32_t gpadc_dma_en : 1;          /*!< gpadc_dma_en                                                              */
      __IOM uint32_t gpadc_fifo_clr : 1;        /*!< gpadc_fifo_clr                                                            */
      __IOM uint32_t gpadc_fifo_ne : 1;         /*!< gpadc_fifo_ne                                                             */
      __IOM uint32_t gpadc_fifo_full : 1;       /*!< gpadc_fifo_full                                                           */
      __IOM uint32_t gpadc_rdy  : 1;            /*!< gpadc_rdy                                                                 */
      __IOM uint32_t gpadc_fifo_overrun : 1;    /*!< gpadc_fifo_overrun                                                        */
      __IOM uint32_t gpadc_fifo_underrun : 1;   /*!< gpadc_fifo_underrun                                                       */
            uint32_t            : 1;
      __IOM uint32_t gpadc_rdy_clr : 1;         /*!< gpadc_rdy_clr                                                             */
      __IOM uint32_t gpadc_fifo_overrun_clr : 1;/*!< gpadc_fifo_overrun_clr                                                    */
      __IOM uint32_t gpadc_fifo_underrun_clr : 1;/*!< gpadc_fifo_underrun_clr                                                  */
            uint32_t            : 1;
      __IOM uint32_t gpadc_rdy_mask : 1;        /*!< gpadc_rdy_mask                                                            */
      __IOM uint32_t gpadc_fifo_overrun_mask : 1;/*!< gpadc_fifo_overrun_mask                                                  */
      __IOM uint32_t gpadc_fifo_underrun_mask : 1;/*!< gpadc_fifo_underrun_mask                                                */
            uint32_t            : 1;
      __IOM uint32_t gpadc_fifo_data_count : 6; /*!< gpadc_fifo_data_count                                                     */
      __IOM uint32_t gpadc_fifo_thl : 2;        /*!< gpadc_fifo_thl                                                            */
      __IOM uint32_t rsvd_31_24 : 8;            /*!< rsvd_31_24                                                                */
    } bit;
  } gpadc_config;
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_dma_rdata.                                                          */
    
    struct {
      __IOM uint32_t gpadc_dma_rdata : 26;      /*!< gpadc_dma_rdata                                                           */
      __IOM uint32_t rsvd_31_26 : 6;            /*!< rsvd_31_26                                                                */
    } bit;
  } gpadc_dma_rdata;
  __IM  uint32_t  RESERVED[14];
  
  union {
    __IOM uint32_t reg;                         /*!< gpdac_config.                                                             */
    
    struct {
      __IOM uint32_t gpdac_en   : 1;            /*!< gpdac_en                                                                  */
      __IOM uint32_t gpdac_en2  : 1;            /*!< gpdac_en2                                                                 */
            uint32_t            : 2;
      __IOM uint32_t dsm_mode   : 2;            /*!< dsm_mode                                                                  */
            uint32_t            : 2;
      __IOM uint32_t gpdac_mode : 3;            /*!< gpdac_mode                                                                */
            uint32_t            : 5;
      __IOM uint32_t gpdac_ch_a_sel : 4;        /*!< gpdac_ch_a_sel                                                            */
      __IOM uint32_t gpdac_ch_b_sel : 4;        /*!< gpdac_ch_b_sel                                                            */
      __IOM uint32_t rsvd_31_24 : 8;            /*!< rsvd_31_24                                                                */
    } bit;
  } gpdac_config;
  
  union {
    __IOM uint32_t reg;                         /*!< gpdac_dma_config.                                                         */
    
    struct {
      __IOM uint32_t gpdac_dma_tx_en : 1;       /*!< gpdac_dma_tx_en                                                           */
            uint32_t            : 3;
      __IOM uint32_t gpdac_dma_format : 2;      /*!< gpdac_dma_format                                                          */
            uint32_t            : 26;
    } bit;
  } gpdac_dma_config;
  
  union {
    __IOM uint32_t reg;                         /*!< gpdac_dma_wdata.                                                          */
    
    struct {
      __IOM uint32_t gpdac_dma_wdata : 32;      /*!< gpdac_dma_wdata                                                           */
    } bit;
  } gpdac_dma_wdata;
  
  union {
    __IOM uint32_t reg;                         /*!< gpdac_tx_fifo_status.                                                     */
    
    struct {
      __IOM uint32_t tx_fifo_empty : 1;         /*!< tx_fifo_empty                                                             */
      __IOM uint32_t tx_fifo_full : 1;          /*!< tx_fifo_full                                                              */
      __IOM uint32_t tx_cs      : 2;            /*!< tx_cs                                                                     */
      __IOM uint32_t TxFifoRdPtr : 3;           /*!< TxFifoRdPtr                                                               */
            uint32_t            : 1;
      __IOM uint32_t TxFifoWrPtr : 2;           /*!< TxFifoWrPtr                                                               */
            uint32_t            : 22;
    } bit;
  } gpdac_tx_fifo_status;
} gpip_Type;                                    /*!< Size = 80 (0x50)                                                          */



/* =========================================================================================================================== */
/* ================                                          sec_dbg                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief sec_dbg. (sec_dbg)
  */

typedef struct {                                /*!< sec_dbg Structure                                                         */
  
  union {
    __IOM uint32_t reg;                         /*!< sd_chip_id_low.                                                           */
    
    struct {
      __IOM uint32_t sd_chip_id_low : 32;       /*!< sd_chip_id_low                                                            */
    } bit;
  } sd_chip_id_low;
  
  union {
    __IOM uint32_t reg;                         /*!< sd_chip_id_high.                                                          */
    
    struct {
      __IOM uint32_t sd_chip_id_high : 32;      /*!< sd_chip_id_high                                                           */
    } bit;
  } sd_chip_id_high;
  
  union {
    __IOM uint32_t reg;                         /*!< sd_wifi_mac_low.                                                          */
    
    struct {
      __IOM uint32_t sd_wifi_mac_low : 32;      /*!< sd_wifi_mac_low                                                           */
    } bit;
  } sd_wifi_mac_low;
  
  union {
    __IOM uint32_t reg;                         /*!< sd_wifi_mac_high.                                                         */
    
    struct {
      __IOM uint32_t sd_wifi_mac_high : 32;     /*!< sd_wifi_mac_high                                                          */
    } bit;
  } sd_wifi_mac_high;
  
  union {
    __IOM uint32_t reg;                         /*!< sd_dbg_pwd_low.                                                           */
    
    struct {
      __IOM uint32_t sd_dbg_pwd_low : 32;       /*!< sd_dbg_pwd_low                                                            */
    } bit;
  } sd_dbg_pwd_low;
  
  union {
    __IOM uint32_t reg;                         /*!< sd_dbg_pwd_high.                                                          */
    
    struct {
      __IOM uint32_t sd_dbg_pwd_high : 32;      /*!< sd_dbg_pwd_high                                                           */
    } bit;
  } sd_dbg_pwd_high;
  
  union {
    __IOM uint32_t reg;                         /*!< sd_status.                                                                */
    
    struct {
      __IOM uint32_t sd_dbg_pwd_busy : 1;       /*!< sd_dbg_pwd_busy                                                           */
      __IOM uint32_t sd_dbg_pwd_trig : 1;       /*!< sd_dbg_pwd_trig                                                           */
      __IOM uint32_t sd_dbg_cci_read_en : 1;    /*!< sd_dbg_cci_read_en                                                        */
      __IOM uint32_t sd_dbg_cci_clk_sel : 1;    /*!< sd_dbg_cci_clk_sel                                                        */
      __IOM uint32_t sd_dbg_pwd_cnt : 20;       /*!< sd_dbg_pwd_cnt                                                            */
      __IOM uint32_t sd_dbg_mode : 4;           /*!< sd_dbg_mode                                                               */
      __IOM uint32_t sd_dbg_ena : 4;            /*!< sd_dbg_ena                                                                */
    } bit;
  } sd_status;
  
  union {
    __IOM uint32_t reg;                         /*!< sd_dbg_reserved.                                                          */
    
    struct {
      __IOM uint32_t sd_dbg_reserved : 32;      /*!< sd_dbg_reserved                                                           */
    } bit;
  } sd_dbg_reserved;
} sec_dbg_Type;                                 /*!< Size = 32 (0x20)                                                          */



/* =========================================================================================================================== */
/* ================                                          sec_eng                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief sec_eng. (sec_eng)
  */

typedef struct {                                /*!< sec_eng Structure                                                         */
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_ctrl.                                                            */
    
    struct {
      __IOM uint32_t se_sha_0_busy : 1;         /*!< se_sha_0_busy                                                             */
      __IOM uint32_t se_sha_0_trig_1t : 1;      /*!< se_sha_0_trig_1t                                                          */
      __IOM uint32_t se_sha_0_mode : 3;         /*!< se_sha_0_mode                                                             */
      __IOM uint32_t se_sha_0_en : 1;           /*!< se_sha_0_en                                                               */
      __IOM uint32_t se_sha_0_hash_sel : 1;     /*!< se_sha_0_hash_sel                                                         */
            uint32_t            : 1;
      __IOM uint32_t se_sha_0_int : 1;          /*!< se_sha_0_int                                                              */
      __IOM uint32_t se_sha_0_int_clr_1t : 1;   /*!< se_sha_0_int_clr_1t                                                       */
      __IOM uint32_t se_sha_0_int_set_1t : 1;   /*!< se_sha_0_int_set_1t                                                       */
      __IOM uint32_t se_sha_0_int_mask : 1;     /*!< se_sha_0_int_mask                                                         */
            uint32_t            : 3;
      __IOM uint32_t se_sha_0_link_mode : 1;    /*!< se_sha_0_link_mode                                                        */
      __IOM uint32_t se_sha_0_msg_len : 16;     /*!< se_sha_0_msg_len                                                          */
    } bit;
  } se_sha_0_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_msa.                                                             */
    
    struct {
      __IOM uint32_t se_sha_0_msa : 32;         /*!< se_sha_0_msa                                                              */
    } bit;
  } se_sha_0_msa;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_status.                                                          */
    
    struct {
      __IOM uint32_t se_sha_0_status : 32;      /*!< se_sha_0_status                                                           */
    } bit;
  } se_sha_0_status;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_endian.                                                          */
    
    struct {
      __IOM uint32_t se_sha_0_dout_endian : 1;  /*!< se_sha_0_dout_endian                                                      */
            uint32_t            : 31;
    } bit;
  } se_sha_0_endian;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_l_0.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_l_0 : 32;    /*!< se_sha_0_hash_l_0                                                         */
    } bit;
  } se_sha_0_hash_l_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_l_1.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_l_1 : 32;    /*!< se_sha_0_hash_l_1                                                         */
    } bit;
  } se_sha_0_hash_l_1;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_l_2.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_l_2 : 32;    /*!< se_sha_0_hash_l_2                                                         */
    } bit;
  } se_sha_0_hash_l_2;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_l_3.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_l_3 : 32;    /*!< se_sha_0_hash_l_3                                                         */
    } bit;
  } se_sha_0_hash_l_3;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_l_4.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_l_4 : 32;    /*!< se_sha_0_hash_l_4                                                         */
    } bit;
  } se_sha_0_hash_l_4;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_l_5.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_l_5 : 32;    /*!< se_sha_0_hash_l_5                                                         */
    } bit;
  } se_sha_0_hash_l_5;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_l_6.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_l_6 : 32;    /*!< se_sha_0_hash_l_6                                                         */
    } bit;
  } se_sha_0_hash_l_6;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_l_7.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_l_7 : 32;    /*!< se_sha_0_hash_l_7                                                         */
    } bit;
  } se_sha_0_hash_l_7;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_h_0.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_h_0 : 32;    /*!< se_sha_0_hash_h_0                                                         */
    } bit;
  } se_sha_0_hash_h_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_h_1.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_h_1 : 32;    /*!< se_sha_0_hash_h_1                                                         */
    } bit;
  } se_sha_0_hash_h_1;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_h_2.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_h_2 : 32;    /*!< se_sha_0_hash_h_2                                                         */
    } bit;
  } se_sha_0_hash_h_2;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_h_3.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_h_3 : 32;    /*!< se_sha_0_hash_h_3                                                         */
    } bit;
  } se_sha_0_hash_h_3;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_h_4.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_h_4 : 32;    /*!< se_sha_0_hash_h_4                                                         */
    } bit;
  } se_sha_0_hash_h_4;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_h_5.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_h_5 : 32;    /*!< se_sha_0_hash_h_5                                                         */
    } bit;
  } se_sha_0_hash_h_5;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_h_6.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_h_6 : 32;    /*!< se_sha_0_hash_h_6                                                         */
    } bit;
  } se_sha_0_hash_h_6;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_hash_h_7.                                                        */
    
    struct {
      __IOM uint32_t se_sha_0_hash_h_7 : 32;    /*!< se_sha_0_hash_h_7                                                         */
    } bit;
  } se_sha_0_hash_h_7;
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_link.                                                            */
    
    struct {
      __IOM uint32_t se_sha_0_lca : 32;         /*!< se_sha_0_lca                                                              */
    } bit;
  } se_sha_0_link;
  __IM  uint32_t  RESERVED[42];
  
  union {
    __IOM uint32_t reg;                         /*!< se_sha_0_ctrl_prot.                                                       */
    
    struct {
      __IOM uint32_t se_sha_prot_en : 1;        /*!< se_sha_prot_en                                                            */
      __IOM uint32_t se_sha_id0_en : 1;         /*!< se_sha_id0_en                                                             */
      __IOM uint32_t se_sha_id1_en : 1;         /*!< se_sha_id1_en                                                             */
            uint32_t            : 29;
    } bit;
  } se_sha_0_ctrl_prot;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_ctrl.                                                            */
    
    struct {
      __IOM uint32_t se_aes_0_busy : 1;         /*!< se_aes_0_busy                                                             */
      __IOM uint32_t se_aes_0_trig_1t : 1;      /*!< se_aes_0_trig_1t                                                          */
      __IOM uint32_t se_aes_0_en : 1;           /*!< se_aes_0_en                                                               */
      __IOM uint32_t se_aes_0_mode : 2;         /*!< se_aes_0_mode                                                             */
      __IOM uint32_t se_aes_0_dec_en : 1;       /*!< se_aes_0_dec_en                                                           */
      __IOM uint32_t se_aes_0_dec_key_sel : 1;  /*!< se_aes_0_dec_key_sel                                                      */
      __IOM uint32_t se_aes_0_hw_key_en : 1;    /*!< se_aes_0_hw_key_en                                                        */
      __IOM uint32_t se_aes_0_int : 1;          /*!< se_aes_0_int                                                              */
      __IOM uint32_t se_aes_0_int_clr_1t : 1;   /*!< se_aes_0_int_clr_1t                                                       */
      __IOM uint32_t se_aes_0_int_set_1t : 1;   /*!< se_aes_0_int_set_1t                                                       */
      __IOM uint32_t se_aes_0_int_mask : 1;     /*!< se_aes_0_int_mask                                                         */
      __IOM uint32_t se_aes_0_block_mode : 2;   /*!< se_aes_0_block_mode                                                       */
      __IOM uint32_t se_aes_0_iv_sel : 1;       /*!< se_aes_0_iv_sel                                                           */
      __IOM uint32_t se_aes_0_link_mode : 1;    /*!< se_aes_0_link_mode                                                        */
      __IOM uint32_t se_aes_0_msg_len : 16;     /*!< se_aes_0_msg_len                                                          */
    } bit;
  } se_aes_0_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_msa.                                                             */
    
    struct {
      __IOM uint32_t se_aes_0_msa : 32;         /*!< se_aes_0_msa                                                              */
    } bit;
  } se_aes_0_msa;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_mda.                                                             */
    
    struct {
      __IOM uint32_t se_aes_0_mda : 32;         /*!< se_aes_0_mda                                                              */
    } bit;
  } se_aes_0_mda;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_status.                                                          */
    
    struct {
      __IOM uint32_t se_aes_0_status : 32;      /*!< se_aes_0_status                                                           */
    } bit;
  } se_aes_0_status;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_iv_0.                                                            */
    
    struct {
      __IOM uint32_t se_aes_0_iv_0 : 32;        /*!< se_aes_0_iv_0                                                             */
    } bit;
  } se_aes_0_iv_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_iv_1.                                                            */
    
    struct {
      __IOM uint32_t se_aes_0_iv_1 : 32;        /*!< se_aes_0_iv_1                                                             */
    } bit;
  } se_aes_0_iv_1;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_iv_2.                                                            */
    
    struct {
      __IOM uint32_t se_aes_0_iv_2 : 32;        /*!< se_aes_0_iv_2                                                             */
    } bit;
  } se_aes_0_iv_2;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_iv_3.                                                            */
    
    struct {
      __IOM uint32_t se_aes_0_iv_3 : 32;        /*!< se_aes_0_iv_3                                                             */
    } bit;
  } se_aes_0_iv_3;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_0.                                                           */
    
    struct {
      __IOM uint32_t se_aes_0_key_0 : 32;       /*!< se_aes_0_key_0                                                            */
    } bit;
  } se_aes_0_key_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_1.                                                           */
    
    struct {
      __IOM uint32_t se_aes_0_key_1 : 32;       /*!< se_aes_0_key_1                                                            */
    } bit;
  } se_aes_0_key_1;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_2.                                                           */
    
    struct {
      __IOM uint32_t se_aes_0_key_2 : 32;       /*!< se_aes_0_key_2                                                            */
    } bit;
  } se_aes_0_key_2;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_3.                                                           */
    
    struct {
      __IOM uint32_t se_aes_0_key_3 : 32;       /*!< se_aes_0_key_3                                                            */
    } bit;
  } se_aes_0_key_3;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_4.                                                           */
    
    struct {
      __IOM uint32_t se_aes_0_key_4 : 32;       /*!< se_aes_0_key_4                                                            */
    } bit;
  } se_aes_0_key_4;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_5.                                                           */
    
    struct {
      __IOM uint32_t se_aes_0_key_5 : 32;       /*!< se_aes_0_key_5                                                            */
    } bit;
  } se_aes_0_key_5;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_6.                                                           */
    
    struct {
      __IOM uint32_t se_aes_0_key_6 : 32;       /*!< se_aes_0_key_6                                                            */
    } bit;
  } se_aes_0_key_6;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_7.                                                           */
    
    struct {
      __IOM uint32_t se_aes_0_key_7 : 32;       /*!< se_aes_0_key_7                                                            */
    } bit;
  } se_aes_0_key_7;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_sel_0.                                                       */
    
    struct {
      __IOM uint32_t se_aes_0_key_sel_0 : 2;    /*!< se_aes_0_key_sel_0                                                        */
            uint32_t            : 30;
    } bit;
  } se_aes_0_key_sel_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_key_sel_1.                                                       */
    
    struct {
      __IOM uint32_t se_aes_0_key_sel_1 : 2;    /*!< se_aes_0_key_sel_1                                                        */
            uint32_t            : 30;
    } bit;
  } se_aes_0_key_sel_1;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_endian.                                                          */
    
    struct {
      __IOM uint32_t se_aes_0_dout_endian : 1;  /*!< se_aes_0_dout_endian                                                      */
      __IOM uint32_t se_aes_0_din_endian : 1;   /*!< se_aes_0_din_endian                                                       */
      __IOM uint32_t se_aes_0_key_endian : 1;   /*!< se_aes_0_key_endian                                                       */
      __IOM uint32_t se_aes_0_iv_endian : 1;    /*!< se_aes_0_iv_endian                                                        */
            uint32_t            : 26;
      __IOM uint32_t se_aes_0_ctr_len : 2;      /*!< se_aes_0_ctr_len                                                          */
    } bit;
  } se_aes_0_endian;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_sboot.                                                           */
    
    struct {
      __IOM uint32_t se_aes_0_sboot_key_sel : 1;/*!< se_aes_0_sboot_key_sel                                                    */
            uint32_t            : 31;
    } bit;
  } se_aes_0_sboot;
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_link.                                                            */
    
    struct {
      __IOM uint32_t se_aes_0_lca : 32;         /*!< se_aes_0_lca                                                              */
    } bit;
  } se_aes_0_link;
  __IM  uint32_t  RESERVED1[42];
  
  union {
    __IOM uint32_t reg;                         /*!< se_aes_0_ctrl_prot.                                                       */
    
    struct {
      __IOM uint32_t se_aes_prot_en : 1;        /*!< se_aes_prot_en                                                            */
      __IOM uint32_t se_aes_id0_en : 1;         /*!< se_aes_id0_en                                                             */
      __IOM uint32_t se_aes_id1_en : 1;         /*!< se_aes_id1_en                                                             */
            uint32_t            : 29;
    } bit;
  } se_aes_0_ctrl_prot;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_ctrl_0.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_busy : 1;        /*!< se_trng_0_busy                                                            */
      __IOM uint32_t se_trng_0_trig_1t : 1;     /*!< se_trng_0_trig_1t                                                         */
      __IOM uint32_t se_trng_0_en : 1;          /*!< se_trng_0_en                                                              */
      __IOM uint32_t se_trng_0_dout_clr_1t : 1; /*!< se_trng_0_dout_clr_1t                                                     */
      __IOM uint32_t se_trng_0_ht_error : 1;    /*!< se_trng_0_ht_error                                                        */
            uint32_t            : 3;
      __IOM uint32_t se_trng_0_int : 1;         /*!< se_trng_0_int                                                             */
      __IOM uint32_t se_trng_0_int_clr_1t : 1;  /*!< se_trng_0_int_clr_1t                                                      */
      __IOM uint32_t se_trng_0_int_set_1t : 1;  /*!< se_trng_0_int_set_1t                                                      */
      __IOM uint32_t se_trng_0_int_mask : 1;    /*!< se_trng_0_int_mask                                                        */
            uint32_t            : 1;
      __IOM uint32_t se_trng_0_manual_fun_sel : 1;/*!< se_trng_0_manual_fun_sel                                                */
      __IOM uint32_t se_trng_0_manual_reseed : 1;/*!< se_trng_0_manual_reseed                                                  */
      __IOM uint32_t se_trng_0_manual_en : 1;   /*!< se_trng_0_manual_en                                                       */
            uint32_t            : 16;
    } bit;
  } se_trng_0_ctrl_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_status.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_status : 32;     /*!< se_trng_0_status                                                          */
    } bit;
  } se_trng_0_status;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_dout_0.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_dout_0 : 32;     /*!< se_trng_0_dout_0                                                          */
    } bit;
  } se_trng_0_dout_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_dout_1.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_dout_1 : 32;     /*!< se_trng_0_dout_1                                                          */
    } bit;
  } se_trng_0_dout_1;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_dout_2.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_dout_2 : 32;     /*!< se_trng_0_dout_2                                                          */
    } bit;
  } se_trng_0_dout_2;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_dout_3.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_dout_3 : 32;     /*!< se_trng_0_dout_3                                                          */
    } bit;
  } se_trng_0_dout_3;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_dout_4.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_dout_4 : 32;     /*!< se_trng_0_dout_4                                                          */
    } bit;
  } se_trng_0_dout_4;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_dout_5.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_dout_5 : 32;     /*!< se_trng_0_dout_5                                                          */
    } bit;
  } se_trng_0_dout_5;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_dout_6.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_dout_6 : 32;     /*!< se_trng_0_dout_6                                                          */
    } bit;
  } se_trng_0_dout_6;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_dout_7.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_dout_7 : 32;     /*!< se_trng_0_dout_7                                                          */
    } bit;
  } se_trng_0_dout_7;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_test.                                                           */
    
    struct {
      __IOM uint32_t se_trng_0_test_en : 1;     /*!< se_trng_0_test_en                                                         */
      __IOM uint32_t se_trng_0_cp_test_en : 1;  /*!< se_trng_0_cp_test_en                                                      */
      __IOM uint32_t se_trng_0_cp_bypass : 1;   /*!< se_trng_0_cp_bypass                                                       */
      __IOM uint32_t se_trng_0_ht_dis : 1;      /*!< se_trng_0_ht_dis                                                          */
      __IOM uint32_t se_trng_0_ht_alarm_n : 8;  /*!< se_trng_0_ht_alarm_n                                                      */
            uint32_t            : 20;
    } bit;
  } se_trng_0_test;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_ctrl_1.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_reseed_n_lsb : 32;/*!< se_trng_0_reseed_n_lsb                                                   */
    } bit;
  } se_trng_0_ctrl_1;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_ctrl_2.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_reseed_n_msb : 16;/*!< se_trng_0_reseed_n_msb                                                   */
            uint32_t            : 16;
    } bit;
  } se_trng_0_ctrl_2;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_ctrl_3.                                                         */
    
    struct {
      __IOM uint32_t se_trng_0_cp_ratio : 8;    /*!< se_trng_0_cp_ratio                                                        */
      __IOM uint32_t se_trng_0_ht_rct_c : 8;    /*!< se_trng_0_ht_rct_c                                                        */
      __IOM uint32_t se_trng_0_ht_apt_c : 10;   /*!< se_trng_0_ht_apt_c                                                        */
      __IOM uint32_t se_trng_0_ht_od_en : 1;    /*!< se_trng_0_ht_od_en                                                        */
            uint32_t            : 4;
      __IOM uint32_t se_trng_0_rosc_en : 1;     /*!< se_trng_0_rosc_en                                                         */
    } bit;
  } se_trng_0_ctrl_3;
  __IM  uint32_t  RESERVED2[2];
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_test_out_0.                                                     */
    
    struct {
      __IOM uint32_t se_trng_0_test_out_0 : 32; /*!< se_trng_0_test_out_0                                                      */
    } bit;
  } se_trng_0_test_out_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_test_out_1.                                                     */
    
    struct {
      __IOM uint32_t se_trng_0_test_out_1 : 32; /*!< se_trng_0_test_out_1                                                      */
    } bit;
  } se_trng_0_test_out_1;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_test_out_2.                                                     */
    
    struct {
      __IOM uint32_t se_trng_0_test_out_2 : 32; /*!< se_trng_0_test_out_2                                                      */
    } bit;
  } se_trng_0_test_out_2;
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_test_out_3.                                                     */
    
    struct {
      __IOM uint32_t se_trng_0_test_out_3 : 32; /*!< se_trng_0_test_out_3                                                      */
    } bit;
  } se_trng_0_test_out_3;
  __IM  uint32_t  RESERVED3[43];
  
  union {
    __IOM uint32_t reg;                         /*!< se_trng_0_ctrl_prot.                                                      */
    
    struct {
      __IOM uint32_t se_trng_prot_en : 1;       /*!< se_trng_prot_en                                                           */
      __IOM uint32_t se_trng_id0_en : 1;        /*!< se_trng_id0_en                                                            */
      __IOM uint32_t se_trng_id1_en : 1;        /*!< se_trng_id1_en                                                            */
            uint32_t            : 29;
    } bit;
  } se_trng_0_ctrl_prot;
  
  union {
    __IOM uint32_t reg;                         /*!< se_pka_0_ctrl_0.                                                          */
    
    struct {
      __IOM uint32_t se_pka_0_done : 1;         /*!< se_pka_0_done                                                             */
      __IOM uint32_t se_pka_0_done_clr_1t : 1;  /*!< se_pka_0_done_clr_1t                                                      */
      __IOM uint32_t se_pka_0_busy : 1;         /*!< se_pka_0_busy                                                             */
      __IOM uint32_t se_pka_0_en : 1;           /*!< se_pka_0_en                                                               */
      __IOM uint32_t se_pka_0_prot_md : 4;      /*!< se_pka_0_prot_md                                                          */
      __IOM uint32_t se_pka_0_int : 1;          /*!< se_pka_0_int                                                              */
      __IOM uint32_t se_pka_0_int_clr_1t : 1;   /*!< se_pka_0_int_clr_1t                                                       */
      __IOM uint32_t se_pka_0_int_set : 1;      /*!< se_pka_0_int_set                                                          */
      __IOM uint32_t se_pka_0_int_mask : 1;     /*!< se_pka_0_int_mask                                                         */
      __IOM uint32_t se_pka_0_endian : 1;       /*!< se_pka_0_endian                                                           */
      __IOM uint32_t se_pka_0_ram_clr_md : 1;   /*!< se_pka_0_ram_clr_md                                                       */
            uint32_t            : 2;
      __IOM uint32_t se_pka_0_status_clr_1t : 1;/*!< se_pka_0_status_clr_1t                                                    */
      __IOM uint32_t se_pka_0_status : 15;      /*!< se_pka_0_status                                                           */
    } bit;
  } se_pka_0_ctrl_0;
  __IM  uint32_t  RESERVED4[2];
  
  union {
    __IOM uint32_t reg;                         /*!< se_pka_0_seed.                                                            */
    
    struct {
      __IOM uint32_t se_pka_0_seed : 32;        /*!< se_pka_0_seed                                                             */
    } bit;
  } se_pka_0_seed;
  
  union {
    __IOM uint32_t reg;                         /*!< se_pka_0_ctrl_1.                                                          */
    
    struct {
      __IOM uint32_t se_pka_0_hburst : 3;       /*!< se_pka_0_hburst                                                           */
      __IOM uint32_t se_pka_0_hbypass : 1;      /*!< se_pka_0_hbypass                                                          */
            uint32_t            : 28;
    } bit;
  } se_pka_0_ctrl_1;
  __IM  uint32_t  RESERVED5[11];
  __IOM uint32_t  se_pka_0_rw;                  /*!< se_pka_0_rw.                                                              */
  __IM  uint32_t  RESERVED6[7];
  __IOM uint32_t  se_pka_0_rw_burst;            /*!< se_pka_0_rw_burst.                                                        */
  __IM  uint32_t  RESERVED7[38];
  
  union {
    __IOM uint32_t reg;                         /*!< se_pka_0_ctrl_prot.                                                       */
    
    struct {
      __IOM uint32_t se_pka_prot_en : 1;        /*!< se_pka_prot_en                                                            */
      __IOM uint32_t se_pka_id0_en : 1;         /*!< se_pka_id0_en                                                             */
      __IOM uint32_t se_pka_id1_en : 1;         /*!< se_pka_id1_en                                                             */
            uint32_t            : 29;
    } bit;
  } se_pka_0_ctrl_prot;
  
  union {
    __IOM uint32_t reg;                         /*!< se_cdet_0_ctrl_0.                                                         */
    
    struct {
      __IOM uint32_t se_cdet_0_en : 1;          /*!< se_cdet_0_en                                                              */
      __IOM uint32_t se_cdet_0_error : 1;       /*!< se_cdet_0_error                                                           */
      __IOM uint32_t se_cdet_0_status : 14;     /*!< se_cdet_0_status                                                          */
      __IOM uint32_t se_cdet_0_g_loop_max : 8;  /*!< se_cdet_0_g_loop_max                                                      */
      __IOM uint32_t se_cdet_0_g_loop_min : 8;  /*!< se_cdet_0_g_loop_min                                                      */
    } bit;
  } se_cdet_0_ctrl_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_cdet_0_ctrl_1.                                                         */
    
    struct {
      __IOM uint32_t se_cdet_0_t_loop_n : 8;    /*!< se_cdet_0_t_loop_n                                                        */
      __IOM uint32_t se_cdet_0_t_dly_n : 8;     /*!< se_cdet_0_t_dly_n                                                         */
      __IOM uint32_t se_cdet_0_g_slp_n : 8;     /*!< se_cdet_0_g_slp_n                                                         */
            uint32_t            : 8;
    } bit;
  } se_cdet_0_ctrl_1;
  __IM  uint32_t  RESERVED8[61];
  
  union {
    __IOM uint32_t reg;                         /*!< se_cdet_0_ctrl_prot.                                                      */
    
    struct {
      __IOM uint32_t se_cdet_prot_en : 1;       /*!< se_cdet_prot_en                                                           */
      __IOM uint32_t se_cdet_id0_en : 1;        /*!< se_cdet_id0_en                                                            */
      __IOM uint32_t se_cdet_id1_en : 1;        /*!< se_cdet_id1_en                                                            */
            uint32_t            : 29;
    } bit;
  } se_cdet_0_ctrl_prot;
  
  union {
    __IOM uint32_t reg;                         /*!< se_gmac_0_ctrl_0.                                                         */
    
    struct {
      __IOM uint32_t se_gmac_0_busy : 1;        /*!< se_gmac_0_busy                                                            */
      __IOM uint32_t se_gmac_0_trig_1t : 1;     /*!< se_gmac_0_trig_1t                                                         */
      __IOM uint32_t se_gmac_0_en : 1;          /*!< se_gmac_0_en                                                              */
            uint32_t            : 5;
      __IOM uint32_t se_gmac_0_int : 1;         /*!< se_gmac_0_int                                                             */
      __IOM uint32_t se_gmac_0_int_clr_1t : 1;  /*!< se_gmac_0_int_clr_1t                                                      */
      __IOM uint32_t se_gmac_0_int_set_1t : 1;  /*!< se_gmac_0_int_set_1t                                                      */
      __IOM uint32_t se_gmac_0_int_mask : 1;    /*!< se_gmac_0_int_mask                                                        */
      __IOM uint32_t se_gmac_0_t_endian : 1;    /*!< se_gmac_0_t_endian                                                        */
      __IOM uint32_t se_gmac_0_h_endian : 1;    /*!< se_gmac_0_h_endian                                                        */
      __IOM uint32_t se_gmac_0_x_endian : 1;    /*!< se_gmac_0_x_endian                                                        */
            uint32_t            : 17;
    } bit;
  } se_gmac_0_ctrl_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_gmac_0_lca.                                                            */
    
    struct {
      __IOM uint32_t se_gmac_0_lca : 32;        /*!< se_gmac_0_lca                                                             */
    } bit;
  } se_gmac_0_lca;
  
  union {
    __IOM uint32_t reg;                         /*!< se_gmac_0_status.                                                         */
    
    struct {
      __IOM uint32_t se_gmac_0_status : 32;     /*!< se_gmac_0_status                                                          */
    } bit;
  } se_gmac_0_status;
  __IM  uint32_t  RESERVED9[60];
  
  union {
    __IOM uint32_t reg;                         /*!< se_gmac_0_ctrl_prot.                                                      */
    
    struct {
      __IOM uint32_t se_gmac_prot_en : 1;       /*!< se_gmac_prot_en                                                           */
      __IOM uint32_t se_gmac_id0_en : 1;        /*!< se_gmac_id0_en                                                            */
      __IOM uint32_t se_gmac_id1_en : 1;        /*!< se_gmac_id1_en                                                            */
            uint32_t            : 29;
    } bit;
  } se_gmac_0_ctrl_prot;
  __IM  uint32_t  RESERVED10[576];
  
  union {
    __IOM uint32_t reg;                         /*!< se_ctrl_prot_rd.                                                          */
    
    struct {
      __IOM uint32_t se_sha_prot_en_rd : 1;     /*!< se_sha_prot_en_rd                                                         */
      __IOM uint32_t se_sha_id0_en_rd : 1;      /*!< se_sha_id0_en_rd                                                          */
      __IOM uint32_t se_sha_id1_en_rd : 1;      /*!< se_sha_id1_en_rd                                                          */
            uint32_t            : 1;
      __IOM uint32_t se_aes_prot_en_rd : 1;     /*!< se_aes_prot_en_rd                                                         */
      __IOM uint32_t se_aes_id0_en_rd : 1;      /*!< se_aes_id0_en_rd                                                          */
      __IOM uint32_t se_aes_id1_en_rd : 1;      /*!< se_aes_id1_en_rd                                                          */
            uint32_t            : 1;
      __IOM uint32_t se_trng_prot_en_rd : 1;    /*!< se_trng_prot_en_rd                                                        */
      __IOM uint32_t se_trng_id0_en_rd : 1;     /*!< se_trng_id0_en_rd                                                         */
      __IOM uint32_t se_trng_id1_en_rd : 1;     /*!< se_trng_id1_en_rd                                                         */
            uint32_t            : 1;
      __IOM uint32_t se_pka_prot_en_rd : 1;     /*!< se_pka_prot_en_rd                                                         */
      __IOM uint32_t se_pka_id0_en_rd : 1;      /*!< se_pka_id0_en_rd                                                          */
      __IOM uint32_t se_pka_id1_en_rd : 1;      /*!< se_pka_id1_en_rd                                                          */
            uint32_t            : 1;
      __IOM uint32_t se_cdet_prot_en_rd : 1;    /*!< se_cdet_prot_en_rd                                                        */
      __IOM uint32_t se_cdet_id0_en_rd : 1;     /*!< se_cdet_id0_en_rd                                                         */
      __IOM uint32_t se_cdet_id1_en_rd : 1;     /*!< se_cdet_id1_en_rd                                                         */
            uint32_t            : 1;
      __IOM uint32_t se_gmac_prot_en_rd : 1;    /*!< se_gmac_prot_en_rd                                                        */
      __IOM uint32_t se_gmac_id0_en_rd : 1;     /*!< se_gmac_id0_en_rd                                                         */
      __IOM uint32_t se_gmac_id1_en_rd : 1;     /*!< se_gmac_id1_en_rd                                                         */
            uint32_t            : 8;
      __IOM uint32_t se_dbg_dis : 1;            /*!< se_dbg_dis                                                                */
    } bit;
  } se_ctrl_prot_rd;
  
  union {
    __IOM uint32_t reg;                         /*!< se_ctrl_reserved_0.                                                       */
    
    struct {
      __IOM uint32_t se_ctrl_reserved_0 : 32;   /*!< se_ctrl_reserved_0                                                        */
    } bit;
  } se_ctrl_reserved_0;
  
  union {
    __IOM uint32_t reg;                         /*!< se_ctrl_reserved_1.                                                       */
    
    struct {
      __IOM uint32_t se_ctrl_reserved_1 : 32;   /*!< se_ctrl_reserved_1                                                        */
    } bit;
  } se_ctrl_reserved_1;
  
  union {
    __IOM uint32_t reg;                         /*!< se_ctrl_reserved_2.                                                       */
    
    struct {
      __IOM uint32_t se_ctrl_reserved_2 : 32;   /*!< se_ctrl_reserved_2                                                        */
    } bit;
  } se_ctrl_reserved_2;
} sec_eng_Type;                                 /*!< Size = 3856 (0xf10)                                                       */



/* =========================================================================================================================== */
/* ================                                          tzc_sec                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief tzc_sec. (tzc_sec)
  */

typedef struct {                                /*!< tzc_sec Structure                                                         */
  __IM  uint32_t  RESERVED[16];
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom_ctrl.                                                             */
    
    struct {
      __IOM uint32_t tzc_rom0_r0_id0_en : 1;    /*!< tzc_rom0_r0_id0_en                                                        */
      __IOM uint32_t tzc_rom0_r1_id0_en : 1;    /*!< tzc_rom0_r1_id0_en                                                        */
      __IOM uint32_t tzc_rom1_r0_id0_en : 1;    /*!< tzc_rom1_r0_id0_en                                                        */
      __IOM uint32_t tzc_rom1_r1_id0_en : 1;    /*!< tzc_rom1_r1_id0_en                                                        */
            uint32_t            : 4;
      __IOM uint32_t tzc_rom0_r0_id1_en : 1;    /*!< tzc_rom0_r0_id1_en                                                        */
      __IOM uint32_t tzc_rom0_r1_id1_en : 1;    /*!< tzc_rom0_r1_id1_en                                                        */
      __IOM uint32_t tzc_rom1_r0_id1_en : 1;    /*!< tzc_rom1_r0_id1_en                                                        */
      __IOM uint32_t tzc_rom1_r1_id1_en : 1;    /*!< tzc_rom1_r1_id1_en                                                        */
            uint32_t            : 4;
      __IOM uint32_t tzc_rom0_r0_en : 1;        /*!< tzc_rom0_r0_en                                                            */
      __IOM uint32_t tzc_rom0_r1_en : 1;        /*!< tzc_rom0_r1_en                                                            */
      __IOM uint32_t tzc_rom1_r0_en : 1;        /*!< tzc_rom1_r0_en                                                            */
      __IOM uint32_t tzc_rom1_r1_en : 1;        /*!< tzc_rom1_r1_en                                                            */
            uint32_t            : 4;
      __IOM uint32_t tzc_rom0_r0_lock : 1;      /*!< tzc_rom0_r0_lock                                                          */
      __IOM uint32_t tzc_rom0_r1_lock : 1;      /*!< tzc_rom0_r1_lock                                                          */
      __IOM uint32_t tzc_rom1_r0_lock : 1;      /*!< tzc_rom1_r0_lock                                                          */
      __IOM uint32_t tzc_rom1_r1_lock : 1;      /*!< tzc_rom1_r1_lock                                                          */
      __IOM uint32_t tzc_sboot_done : 4;        /*!< tzc_sboot_done                                                            */
    } bit;
  } tzc_rom_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom0_r0.                                                              */
    
    struct {
      __IOM uint32_t tzc_rom0_r0_end : 16;      /*!< tzc_rom0_r0_end                                                           */
      __IOM uint32_t tzc_rom0_r0_start : 16;    /*!< tzc_rom0_r0_start                                                         */
    } bit;
  } tzc_rom0_r0;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom0_r1.                                                              */
    
    struct {
      __IOM uint32_t tzc_rom0_r1_end : 16;      /*!< tzc_rom0_r1_end                                                           */
      __IOM uint32_t tzc_rom0_r1_start : 16;    /*!< tzc_rom0_r1_start                                                         */
    } bit;
  } tzc_rom0_r1;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom1_r0.                                                              */
    
    struct {
      __IOM uint32_t tzc_rom1_r0_end : 16;      /*!< tzc_rom1_r0_end                                                           */
      __IOM uint32_t tzc_rom1_r0_start : 16;    /*!< tzc_rom1_r0_start                                                         */
    } bit;
  } tzc_rom1_r0;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom1_r1.                                                              */
    
    struct {
      __IOM uint32_t tzc_rom1_r1_end : 16;      /*!< tzc_rom1_r1_end                                                           */
      __IOM uint32_t tzc_rom1_r1_start : 16;    /*!< tzc_rom1_r1_start                                                         */
    } bit;
  } tzc_rom1_r1;
} tzc_sec_Type;                                 /*!< Size = 84 (0x54)                                                          */



/* =========================================================================================================================== */
/* ================                                         tzc_nsec                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief tzc_nsec. (tzc_nsec)
  */

typedef struct {                                /*!< tzc_nsec Structure                                                        */
  __IM  uint32_t  RESERVED[16];
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom_ctrl.                                                             */
    
    struct {
      __IOM uint32_t tzc_rom0_r0_id0_en : 1;    /*!< tzc_rom0_r0_id0_en                                                        */
      __IOM uint32_t tzc_rom0_r1_id0_en : 1;    /*!< tzc_rom0_r1_id0_en                                                        */
      __IOM uint32_t tzc_rom1_r0_id0_en : 1;    /*!< tzc_rom1_r0_id0_en                                                        */
      __IOM uint32_t tzc_rom1_r1_id0_en : 1;    /*!< tzc_rom1_r1_id0_en                                                        */
            uint32_t            : 4;
      __IOM uint32_t tzc_rom0_r0_id1_en : 1;    /*!< tzc_rom0_r0_id1_en                                                        */
      __IOM uint32_t tzc_rom0_r1_id1_en : 1;    /*!< tzc_rom0_r1_id1_en                                                        */
      __IOM uint32_t tzc_rom1_r0_id1_en : 1;    /*!< tzc_rom1_r0_id1_en                                                        */
      __IOM uint32_t tzc_rom1_r1_id1_en : 1;    /*!< tzc_rom1_r1_id1_en                                                        */
            uint32_t            : 4;
      __IOM uint32_t tzc_rom0_r0_en : 1;        /*!< tzc_rom0_r0_en                                                            */
      __IOM uint32_t tzc_rom0_r1_en : 1;        /*!< tzc_rom0_r1_en                                                            */
      __IOM uint32_t tzc_rom1_r0_en : 1;        /*!< tzc_rom1_r0_en                                                            */
      __IOM uint32_t tzc_rom1_r1_en : 1;        /*!< tzc_rom1_r1_en                                                            */
            uint32_t            : 4;
      __IOM uint32_t tzc_rom0_r0_lock : 1;      /*!< tzc_rom0_r0_lock                                                          */
      __IOM uint32_t tzc_rom0_r1_lock : 1;      /*!< tzc_rom0_r1_lock                                                          */
      __IOM uint32_t tzc_rom1_r0_lock : 1;      /*!< tzc_rom1_r0_lock                                                          */
      __IOM uint32_t tzc_rom1_r1_lock : 1;      /*!< tzc_rom1_r1_lock                                                          */
      __IOM uint32_t tzc_sboot_done : 4;        /*!< tzc_sboot_done                                                            */
    } bit;
  } tzc_rom_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom0_r0.                                                              */
    
    struct {
      __IOM uint32_t tzc_rom0_r0_end : 16;      /*!< tzc_rom0_r0_end                                                           */
      __IOM uint32_t tzc_rom0_r0_start : 16;    /*!< tzc_rom0_r0_start                                                         */
    } bit;
  } tzc_rom0_r0;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom0_r1.                                                              */
    
    struct {
      __IOM uint32_t tzc_rom0_r1_end : 16;      /*!< tzc_rom0_r1_end                                                           */
      __IOM uint32_t tzc_rom0_r1_start : 16;    /*!< tzc_rom0_r1_start                                                         */
    } bit;
  } tzc_rom0_r1;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom1_r0.                                                              */
    
    struct {
      __IOM uint32_t tzc_rom1_r0_end : 16;      /*!< tzc_rom1_r0_end                                                           */
      __IOM uint32_t tzc_rom1_r0_start : 16;    /*!< tzc_rom1_r0_start                                                         */
    } bit;
  } tzc_rom1_r0;
  
  union {
    __IOM uint32_t reg;                         /*!< tzc_rom1_r1.                                                              */
    
    struct {
      __IOM uint32_t tzc_rom1_r1_end : 16;      /*!< tzc_rom1_r1_end                                                           */
      __IOM uint32_t tzc_rom1_r1_start : 16;    /*!< tzc_rom1_r1_start                                                         */
    } bit;
  } tzc_rom1_r1;
} tzc_nsec_Type;                                /*!< Size = 84 (0x54)                                                          */



/* =========================================================================================================================== */
/* ================                                         ef_data_0                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief ef_data_0. (ef_data_0)
  */

typedef struct {                                /*!< ef_data_0 Structure                                                       */
  
  union {
    __IOM uint32_t reg;                         /*!< ef_cfg_0.                                                                 */
    
    struct {
      __IOM uint32_t ef_sf_aes_mode : 2;        /*!< ef_sf_aes_mode                                                            */
      __IOM uint32_t ef_sboot_sign_mode : 2;    /*!< ef_sboot_sign_mode                                                        */
      __IOM uint32_t ef_sboot_en : 2;           /*!< ef_sboot_en                                                               */
      __IOM uint32_t ef_cpu1_enc_en : 1;        /*!< ef_cpu1_enc_en                                                            */
      __IOM uint32_t ef_cpu0_enc_en : 1;        /*!< ef_cpu0_enc_en                                                            */
      __IOM uint32_t ef_boot_sel : 4;           /*!< ef_boot_sel                                                               */
      __IOM uint32_t ef_sw_usage_1 : 2;         /*!< ef_sw_usage_1                                                             */
      __IOM uint32_t ef_sdu_dis : 1;            /*!< ef_sdu_dis                                                                */
      __IOM uint32_t ef_ble_dis : 1;            /*!< ef_ble_dis                                                                */
      __IOM uint32_t ef_wifi_dis : 1;           /*!< ef_wifi_dis                                                               */
      __IOM uint32_t ef_0_key_enc_en : 1;       /*!< ef_0_key_enc_en                                                           */
      __IOM uint32_t ef_cam_dis : 1;            /*!< ef_cam_dis                                                                */
      __IOM uint32_t ef_sf_dis  : 1;            /*!< ef_sf_dis                                                                 */
      __IOM uint32_t ef_cpu1_dis : 1;           /*!< ef_cpu1_dis                                                               */
      __IOM uint32_t ef_cpu_rst_dbg_dis : 1;    /*!< ef_cpu_rst_dbg_dis                                                        */
      __IOM uint32_t ef_se_dbg_dis : 1;         /*!< ef_se_dbg_dis                                                             */
      __IOM uint32_t ef_efuse_dbg_dis : 1;      /*!< ef_efuse_dbg_dis                                                          */
      __IOM uint32_t ef_dbg_jtag_1_dis : 2;     /*!< ef_dbg_jtag_1_dis                                                         */
      __IOM uint32_t ef_dbg_jtag_0_dis : 2;     /*!< ef_dbg_jtag_0_dis                                                         */
      __IOM uint32_t ef_dbg_mode : 4;           /*!< ef_dbg_mode                                                               */
    } bit;
  } ef_cfg_0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_dbg_pwd_low.                                                           */
    
    struct {
      __IOM uint32_t ef_dbg_pwd_low : 32;       /*!< ef_dbg_pwd_low                                                            */
    } bit;
  } ef_dbg_pwd_low;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_dbg_pwd_high.                                                          */
    
    struct {
      __IOM uint32_t ef_dbg_pwd_high : 32;      /*!< ef_dbg_pwd_high                                                           */
    } bit;
  } ef_dbg_pwd_high;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_ana_trim_0.                                                            */
    
    struct {
      __IOM uint32_t ef_ana_trim_0 : 32;        /*!< ef_ana_trim_0                                                             */
    } bit;
  } ef_ana_trim_0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_sw_usage_0.                                                            */
    
    struct {
      __IOM uint32_t ef_sw_usage_0 : 32;        /*!< ef_sw_usage_0                                                             */
    } bit;
  } ef_sw_usage_0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_wifi_mac_low.                                                          */
    
    struct {
      __IOM uint32_t ef_wifi_mac_low : 32;      /*!< ef_wifi_mac_low                                                           */
    } bit;
  } ef_wifi_mac_low;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_wifi_mac_high.                                                         */
    
    struct {
      __IOM uint32_t ef_wifi_mac_high : 32;     /*!< ef_wifi_mac_high                                                          */
    } bit;
  } ef_wifi_mac_high;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_0_w0.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_0_w0 : 32;     /*!< ef_key_slot_0_w0                                                          */
    } bit;
  } ef_key_slot_0_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_0_w1.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_0_w1 : 32;     /*!< ef_key_slot_0_w1                                                          */
    } bit;
  } ef_key_slot_0_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_0_w2.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_0_w2 : 32;     /*!< ef_key_slot_0_w2                                                          */
    } bit;
  } ef_key_slot_0_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_0_w3.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_0_w3 : 32;     /*!< ef_key_slot_0_w3                                                          */
    } bit;
  } ef_key_slot_0_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_1_w0.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_1_w0 : 32;     /*!< ef_key_slot_1_w0                                                          */
    } bit;
  } ef_key_slot_1_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_1_w1.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_1_w1 : 32;     /*!< ef_key_slot_1_w1                                                          */
    } bit;
  } ef_key_slot_1_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_1_w2.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_1_w2 : 32;     /*!< ef_key_slot_1_w2                                                          */
    } bit;
  } ef_key_slot_1_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_1_w3.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_1_w3 : 32;     /*!< ef_key_slot_1_w3                                                          */
    } bit;
  } ef_key_slot_1_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_2_w0.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_2_w0 : 32;     /*!< ef_key_slot_2_w0                                                          */
    } bit;
  } ef_key_slot_2_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_2_w1.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_2_w1 : 32;     /*!< ef_key_slot_2_w1                                                          */
    } bit;
  } ef_key_slot_2_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_2_w2.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_2_w2 : 32;     /*!< ef_key_slot_2_w2                                                          */
    } bit;
  } ef_key_slot_2_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_2_w3.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_2_w3 : 32;     /*!< ef_key_slot_2_w3                                                          */
    } bit;
  } ef_key_slot_2_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_3_w0.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_3_w0 : 32;     /*!< ef_key_slot_3_w0                                                          */
    } bit;
  } ef_key_slot_3_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_3_w1.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_3_w1 : 32;     /*!< ef_key_slot_3_w1                                                          */
    } bit;
  } ef_key_slot_3_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_3_w2.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_3_w2 : 32;     /*!< ef_key_slot_3_w2                                                          */
    } bit;
  } ef_key_slot_3_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_3_w3.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_3_w3 : 32;     /*!< ef_key_slot_3_w3                                                          */
    } bit;
  } ef_key_slot_3_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_4_w0.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_4_w0 : 32;     /*!< ef_key_slot_4_w0                                                          */
    } bit;
  } ef_key_slot_4_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_4_w1.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_4_w1 : 32;     /*!< ef_key_slot_4_w1                                                          */
    } bit;
  } ef_key_slot_4_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_4_w2.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_4_w2 : 32;     /*!< ef_key_slot_4_w2                                                          */
    } bit;
  } ef_key_slot_4_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_4_w3.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_4_w3 : 32;     /*!< ef_key_slot_4_w3                                                          */
    } bit;
  } ef_key_slot_4_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_5_w0.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_5_w0 : 32;     /*!< ef_key_slot_5_w0                                                          */
    } bit;
  } ef_key_slot_5_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_5_w1.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_5_w1 : 32;     /*!< ef_key_slot_5_w1                                                          */
    } bit;
  } ef_key_slot_5_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_5_w2.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_5_w2 : 32;     /*!< ef_key_slot_5_w2                                                          */
    } bit;
  } ef_key_slot_5_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_key_slot_5_w3.                                                         */
    
    struct {
      __IOM uint32_t ef_key_slot_5_w3 : 32;     /*!< ef_key_slot_5_w3                                                          */
    } bit;
  } ef_key_slot_5_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_data_0_lock.                                                           */
    
    struct {
      __IOM uint32_t ef_ana_trim_1 : 13;        /*!< ef_ana_trim_1                                                             */
      __IOM uint32_t wr_lock_key_slot_4_l : 1;  /*!< wr_lock_key_slot_4_l                                                      */
      __IOM uint32_t wr_lock_key_slot_5_l : 1;  /*!< wr_lock_key_slot_5_l                                                      */
      __IOM uint32_t wr_lock_boot_mode : 1;     /*!< wr_lock_boot_mode                                                         */
      __IOM uint32_t wr_lock_dbg_pwd : 1;       /*!< wr_lock_dbg_pwd                                                           */
      __IOM uint32_t wr_lock_sw_usage_0 : 1;    /*!< wr_lock_sw_usage_0                                                        */
      __IOM uint32_t wr_lock_wifi_mac : 1;      /*!< wr_lock_wifi_mac                                                          */
      __IOM uint32_t wr_lock_key_slot_0 : 1;    /*!< wr_lock_key_slot_0                                                        */
      __IOM uint32_t wr_lock_key_slot_1 : 1;    /*!< wr_lock_key_slot_1                                                        */
      __IOM uint32_t wr_lock_key_slot_2 : 1;    /*!< wr_lock_key_slot_2                                                        */
      __IOM uint32_t wr_lock_key_slot_3 : 1;    /*!< wr_lock_key_slot_3                                                        */
      __IOM uint32_t wr_lock_key_slot_4_h : 1;  /*!< wr_lock_key_slot_4_h                                                      */
      __IOM uint32_t wr_lock_key_slot_5_h : 1;  /*!< wr_lock_key_slot_5_h                                                      */
      __IOM uint32_t rd_lock_dbg_pwd : 1;       /*!< rd_lock_dbg_pwd                                                           */
      __IOM uint32_t rd_lock_key_slot_0 : 1;    /*!< rd_lock_key_slot_0                                                        */
      __IOM uint32_t rd_lock_key_slot_1 : 1;    /*!< rd_lock_key_slot_1                                                        */
      __IOM uint32_t rd_lock_key_slot_2 : 1;    /*!< rd_lock_key_slot_2                                                        */
      __IOM uint32_t rd_lock_key_slot_3 : 1;    /*!< rd_lock_key_slot_3                                                        */
      __IOM uint32_t rd_lock_key_slot_4 : 1;    /*!< rd_lock_key_slot_4                                                        */
      __IOM uint32_t rd_lock_key_slot_5 : 1;    /*!< rd_lock_key_slot_5                                                        */
    } bit;
  } ef_data_0_lock;
} ef_data_0_Type;                               /*!< Size = 128 (0x80)                                                         */



/* =========================================================================================================================== */
/* ================                                         ef_data_1                                         ================ */
/* =========================================================================================================================== */


/**
  * @brief ef_data_1. (ef_data_1)
  */

typedef struct {                                /*!< ef_data_1 Structure                                                       */
  __IM  uint32_t  RESERVED[32];
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_6_w0.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_6_w0 : 32;    /*!< reg_key_slot_6_w0                                                         */
    } bit;
  } reg_key_slot_6_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_6_w1.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_6_w1 : 32;    /*!< reg_key_slot_6_w1                                                         */
    } bit;
  } reg_key_slot_6_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_6_w2.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_6_w2 : 32;    /*!< reg_key_slot_6_w2                                                         */
    } bit;
  } reg_key_slot_6_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_6_w3.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_6_w3 : 32;    /*!< reg_key_slot_6_w3                                                         */
    } bit;
  } reg_key_slot_6_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_7_w0.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_7_w0 : 32;    /*!< reg_key_slot_7_w0                                                         */
    } bit;
  } reg_key_slot_7_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_7_w1.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_7_w1 : 32;    /*!< reg_key_slot_7_w1                                                         */
    } bit;
  } reg_key_slot_7_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_7_w2.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_7_w2 : 32;    /*!< reg_key_slot_7_w2                                                         */
    } bit;
  } reg_key_slot_7_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_7_w3.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_7_w3 : 32;    /*!< reg_key_slot_7_w3                                                         */
    } bit;
  } reg_key_slot_7_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_8_w0.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_8_w0 : 32;    /*!< reg_key_slot_8_w0                                                         */
    } bit;
  } reg_key_slot_8_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_8_w1.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_8_w1 : 32;    /*!< reg_key_slot_8_w1                                                         */
    } bit;
  } reg_key_slot_8_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_8_w2.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_8_w2 : 32;    /*!< reg_key_slot_8_w2                                                         */
    } bit;
  } reg_key_slot_8_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_8_w3.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_8_w3 : 32;    /*!< reg_key_slot_8_w3                                                         */
    } bit;
  } reg_key_slot_8_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_9_w0.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_9_w0 : 32;    /*!< reg_key_slot_9_w0                                                         */
    } bit;
  } reg_key_slot_9_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_9_w1.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_9_w1 : 32;    /*!< reg_key_slot_9_w1                                                         */
    } bit;
  } reg_key_slot_9_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_9_w2.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_9_w2 : 32;    /*!< reg_key_slot_9_w2                                                         */
    } bit;
  } reg_key_slot_9_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< reg_key_slot_9_w3.                                                        */
    
    struct {
      __IOM uint32_t reg_key_slot_9_w3 : 32;    /*!< reg_key_slot_9_w3                                                         */
    } bit;
  } reg_key_slot_9_w3;
  __IOM uint32_t  reg_key_slot_10_w0;           /*!< reg_key_slot_10_w0.                                                       */
  __IOM uint32_t  reg_key_slot_10_w1;           /*!< reg_key_slot_10_w1.                                                       */
  __IOM uint32_t  reg_key_slot_10_w2;           /*!< reg_key_slot_10_w2.                                                       */
  __IOM uint32_t  reg_key_slot_10_w3;           /*!< reg_key_slot_10_w3.                                                       */
  __IOM uint32_t  reg_key_slot_11_w0;           /*!< reg_key_slot_11_w0.                                                       */
  __IOM uint32_t  reg_key_slot_11_w1;           /*!< reg_key_slot_11_w1.                                                       */
  __IOM uint32_t  reg_key_slot_11_w2;           /*!< reg_key_slot_11_w2.                                                       */
  __IOM uint32_t  reg_key_slot_11_w3;           /*!< reg_key_slot_11_w3.                                                       */
  
  union {
    __IOM uint32_t reg;                         /*!< reg_data_1_lock.                                                          */
    
    struct {
      __IOM uint32_t RESERVED_9_0 : 10;         /*!< RESERVED_9_0                                                              */
      __IOM uint32_t wr_lock_key_slot_6 : 1;    /*!< wr_lock_key_slot_6                                                        */
      __IOM uint32_t wr_lock_key_slot_7 : 1;    /*!< wr_lock_key_slot_7                                                        */
      __IOM uint32_t wr_lock_key_slot_8 : 1;    /*!< wr_lock_key_slot_8                                                        */
      __IOM uint32_t wr_lock_key_slot_9 : 1;    /*!< wr_lock_key_slot_9                                                        */
            uint32_t            : 2;
      __IOM uint32_t RESERVED_25_16 : 10;       /*!< RESERVED_25_16                                                            */
      __IOM uint32_t rd_lock_key_slot_6 : 1;    /*!< rd_lock_key_slot_6                                                        */
      __IOM uint32_t rd_lock_key_slot_7 : 1;    /*!< rd_lock_key_slot_7                                                        */
      __IOM uint32_t rd_lock_key_slot_8 : 1;    /*!< rd_lock_key_slot_8                                                        */
      __IOM uint32_t rd_lock_key_slot_9 : 1;    /*!< rd_lock_key_slot_9                                                        */
            uint32_t            : 2;
    } bit;
  } reg_data_1_lock;
} ef_data_1_Type;                               /*!< Size = 228 (0xe4)                                                         */



/* =========================================================================================================================== */
/* ================                                          ef_ctrl                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief ef_ctrl. (ef_ctrl)
  */

typedef struct {                                /*!< ef_ctrl Structure                                                         */
  __IM  uint32_t  RESERVED[512];
  
  union {
    __IOM uint32_t reg;                         /*!< ef_if_ctrl_0.                                                             */
    
    struct {
      __IOM uint32_t ef_if_0_autoload_p1_done : 1;/*!< ef_if_0_autoload_p1_done                                                */
      __IOM uint32_t ef_if_0_autoload_done : 1; /*!< ef_if_0_autoload_done                                                     */
      __IOM uint32_t ef_if_0_busy : 1;          /*!< ef_if_0_busy                                                              */
      __IOM uint32_t ef_if_0_rw : 1;            /*!< ef_if_0_rw                                                                */
      __IOM uint32_t ef_if_0_trig : 1;          /*!< ef_if_0_trig                                                              */
      __IOM uint32_t ef_if_0_manual_en : 1;     /*!< ef_if_0_manual_en                                                         */
      __IOM uint32_t ef_if_0_cyc_modify : 1;    /*!< ef_if_0_cyc_modify                                                        */
      __IOM uint32_t ef_clk_sahb_data_sel : 1;  /*!< ef_clk_sahb_data_sel                                                      */
      __IOM uint32_t ef_if_prot_code_ctrl : 8;  /*!< ef_if_prot_code_ctrl                                                      */
      __IOM uint32_t ef_if_por_dig : 1;         /*!< ef_if_por_dig                                                             */
      __IOM uint32_t ef_clk_sahb_data_gate : 1; /*!< ef_clk_sahb_data_gate                                                     */
      __IOM uint32_t ef_if_auto_rd_en : 1;      /*!< ef_if_auto_rd_en                                                          */
      __IOM uint32_t ef_if_cyc_modify_lock : 1; /*!< ef_if_cyc_modify_lock                                                     */
      __IOM uint32_t ef_if_0_int : 1;           /*!< ef_if_0_int                                                               */
      __IOM uint32_t ef_if_0_int_clr : 1;       /*!< ef_if_0_int_clr                                                           */
      __IOM uint32_t ef_if_0_int_set : 1;       /*!< ef_if_0_int_set                                                           */
            uint32_t            : 1;
      __IOM uint32_t ef_if_prot_code_cyc : 8;   /*!< ef_if_prot_code_cyc                                                       */
    } bit;
  } ef_if_ctrl_0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_if_cyc_0.                                                              */
    
    struct {
      __IOM uint32_t ef_if_cyc_rd_dmy : 6;      /*!< ef_if_cyc_rd_dmy                                                          */
      __IOM uint32_t ef_if_cyc_rd_dat : 6;      /*!< ef_if_cyc_rd_dat                                                          */
      __IOM uint32_t ef_if_cyc_rd_adr : 6;      /*!< ef_if_cyc_rd_adr                                                          */
      __IOM uint32_t ef_if_cyc_cs : 6;          /*!< ef_if_cyc_cs                                                              */
      __IOM uint32_t ef_if_cyc_pd_cs_s : 8;     /*!< ef_if_cyc_pd_cs_s                                                         */
    } bit;
  } ef_if_cyc_0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_if_cyc_1.                                                              */
    
    struct {
      __IOM uint32_t ef_if_cyc_pi : 6;          /*!< ef_if_cyc_pi                                                              */
      __IOM uint32_t ef_if_cyc_pp : 8;          /*!< ef_if_cyc_pp                                                              */
      __IOM uint32_t ef_if_cyc_wr_adr : 6;      /*!< ef_if_cyc_wr_adr                                                          */
      __IOM uint32_t ef_if_cyc_ps_cs : 6;       /*!< ef_if_cyc_ps_cs                                                           */
      __IOM uint32_t ef_if_cyc_pd_cs_h : 6;     /*!< ef_if_cyc_pd_cs_h                                                         */
    } bit;
  } ef_if_cyc_1;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_if_0_manual.                                                           */
    
    struct {
      __IOM uint32_t ef_if_a    : 10;           /*!< ef_if_a                                                                   */
      __IOM uint32_t ef_if_pd   : 1;            /*!< ef_if_pd                                                                  */
      __IOM uint32_t ef_if_ps   : 1;            /*!< ef_if_ps                                                                  */
      __IOM uint32_t ef_if_strobe : 1;          /*!< ef_if_strobe                                                              */
      __IOM uint32_t ef_if_pgenb : 1;           /*!< ef_if_pgenb                                                               */
      __IOM uint32_t ef_if_load : 1;            /*!< ef_if_load                                                                */
      __IOM uint32_t ef_if_csb  : 1;            /*!< ef_if_csb                                                                 */
      __IOM uint32_t ef_if_0_q  : 8;            /*!< ef_if_0_q                                                                 */
      __IOM uint32_t ef_if_prot_code_manual : 8;/*!< ef_if_prot_code_manual                                                    */
    } bit;
  } ef_if_0_manual;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_if_0_status.                                                           */
    
    struct {
      __IOM uint32_t ef_if_0_status : 32;       /*!< ef_if_0_status                                                            */
    } bit;
  } ef_if_0_status;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_if_cfg_0.                                                              */
    
    struct {
      __IOM uint32_t ef_if_sf_aes_mode : 2;     /*!< ef_if_sf_aes_mode                                                         */
      __IOM uint32_t ef_if_sboot_sign_mode : 2; /*!< ef_if_sboot_sign_mode                                                     */
      __IOM uint32_t ef_if_sboot_en : 2;        /*!< ef_if_sboot_en                                                            */
      __IOM uint32_t ef_if_cpu1_enc_en : 1;     /*!< ef_if_cpu1_enc_en                                                         */
      __IOM uint32_t ef_if_cpu0_enc_en : 1;     /*!< ef_if_cpu0_enc_en                                                         */
      __IOM uint32_t ef_if_boot_sel : 4;        /*!< ef_if_boot_sel                                                            */
      __IOM uint32_t ef_if_sw_usage_1 : 2;      /*!< ef_if_sw_usage_1                                                          */
      __IOM uint32_t ef_if_sdu_dis : 1;         /*!< ef_if_sdu_dis                                                             */
      __IOM uint32_t ef_if_ble_dis : 1;         /*!< ef_if_ble_dis                                                             */
      __IOM uint32_t ef_if_wifi_dis : 1;        /*!< ef_if_wifi_dis                                                            */
      __IOM uint32_t ef_if_0_key_enc_en : 1;    /*!< ef_if_0_key_enc_en                                                        */
      __IOM uint32_t ef_if_cam_dis : 1;         /*!< ef_if_cam_dis                                                             */
      __IOM uint32_t ef_if_sf_dis : 1;          /*!< ef_if_sf_dis                                                              */
      __IOM uint32_t ef_if_cpu1_dis : 1;        /*!< ef_if_cpu1_dis                                                            */
      __IOM uint32_t ef_if_cpu_rst_dbg_dis : 1; /*!< ef_if_cpu_rst_dbg_dis                                                     */
      __IOM uint32_t ef_if_se_dbg_dis : 1;      /*!< ef_if_se_dbg_dis                                                          */
      __IOM uint32_t ef_if_efuse_dbg_dis : 1;   /*!< ef_if_efuse_dbg_dis                                                       */
      __IOM uint32_t ef_if_dbg_jtag_1_dis : 2;  /*!< ef_if_dbg_jtag_1_dis                                                      */
      __IOM uint32_t ef_if_dbg_jtag_0_dis : 2;  /*!< ef_if_dbg_jtag_0_dis                                                      */
      __IOM uint32_t ef_if_dbg_mode : 4;        /*!< ef_if_dbg_mode                                                            */
    } bit;
  } ef_if_cfg_0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_sw_cfg_0.                                                              */
    
    struct {
      __IOM uint32_t ef_sw_sf_aes_mode : 2;     /*!< ef_sw_sf_aes_mode                                                         */
      __IOM uint32_t ef_sw_sboot_sign_mode : 2; /*!< ef_sw_sboot_sign_mode                                                     */
      __IOM uint32_t ef_sw_sboot_en : 2;        /*!< ef_sw_sboot_en                                                            */
      __IOM uint32_t ef_sw_cpu1_enc_en : 1;     /*!< ef_sw_cpu1_enc_en                                                         */
      __IOM uint32_t ef_sw_cpu0_enc_en : 1;     /*!< ef_sw_cpu0_enc_en                                                         */
            uint32_t            : 4;
      __IOM uint32_t ef_sw_sw_usage_1 : 2;      /*!< ef_sw_sw_usage_1                                                          */
      __IOM uint32_t ef_sw_sdu_dis : 1;         /*!< ef_sw_sdu_dis                                                             */
      __IOM uint32_t ef_sw_ble_dis : 1;         /*!< ef_sw_ble_dis                                                             */
      __IOM uint32_t ef_sw_wifi_dis : 1;        /*!< ef_sw_wifi_dis                                                            */
      __IOM uint32_t ef_sw_0_key_enc_en : 1;    /*!< ef_sw_0_key_enc_en                                                        */
      __IOM uint32_t ef_sw_cam_dis : 1;         /*!< ef_sw_cam_dis                                                             */
      __IOM uint32_t ef_sw_sf_dis : 1;          /*!< ef_sw_sf_dis                                                              */
      __IOM uint32_t ef_sw_cpu1_dis : 1;        /*!< ef_sw_cpu1_dis                                                            */
      __IOM uint32_t ef_sw_cpu_rst_dbg_dis : 1; /*!< ef_sw_cpu_rst_dbg_dis                                                     */
      __IOM uint32_t ef_sw_se_dbg_dis : 1;      /*!< ef_sw_se_dbg_dis                                                          */
      __IOM uint32_t ef_sw_efuse_dbg_dis : 1;   /*!< ef_sw_efuse_dbg_dis                                                       */
      __IOM uint32_t ef_sw_dbg_jtag_1_dis : 2;  /*!< ef_sw_dbg_jtag_1_dis                                                      */
      __IOM uint32_t ef_sw_dbg_jtag_0_dis : 2;  /*!< ef_sw_dbg_jtag_0_dis                                                      */
      __IOM uint32_t ef_sw_dbg_mode : 4;        /*!< ef_sw_dbg_mode                                                            */
    } bit;
  } ef_sw_cfg_0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_reserved.                                                              */
    
    struct {
      __IOM uint32_t ef_reserved : 32;          /*!< ef_reserved                                                               */
    } bit;
  } ef_reserved;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_if_ana_trim_0.                                                         */
    
    struct {
      __IOM uint32_t ef_if_ana_trim_0 : 32;     /*!< ef_if_ana_trim_0                                                          */
    } bit;
  } ef_if_ana_trim_0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_if_sw_usage_0.                                                         */
    
    struct {
      __IOM uint32_t ef_if_sw_usage_0 : 32;     /*!< ef_if_sw_usage_0                                                          */
    } bit;
  } ef_if_sw_usage_0;
  __IM  uint32_t  RESERVED1[118];
  
  union {
    __IOM uint32_t reg;                         /*!< ef_crc_ctrl_0.                                                            */
    
    struct {
      __IOM uint32_t ef_crc_busy : 1;           /*!< ef_crc_busy                                                               */
      __IOM uint32_t ef_crc_trig : 1;           /*!< ef_crc_trig                                                               */
      __IOM uint32_t ef_crc_en  : 1;            /*!< ef_crc_en                                                                 */
      __IOM uint32_t ef_crc_mode : 1;           /*!< ef_crc_mode                                                               */
      __IOM uint32_t ef_crc_error : 1;          /*!< ef_crc_error                                                              */
      __IOM uint32_t ef_crc_dout_inv_en : 1;    /*!< ef_crc_dout_inv_en                                                        */
      __IOM uint32_t ef_crc_dout_endian : 1;    /*!< ef_crc_dout_endian                                                        */
      __IOM uint32_t ef_crc_din_endian : 1;     /*!< ef_crc_din_endian                                                         */
      __IOM uint32_t ef_crc_int : 1;            /*!< ef_crc_int                                                                */
      __IOM uint32_t ef_crc_int_clr : 1;        /*!< ef_crc_int_clr                                                            */
      __IOM uint32_t ef_crc_int_set : 1;        /*!< ef_crc_int_set                                                            */
      __IOM uint32_t ef_crc_lock : 1;           /*!< ef_crc_lock                                                               */
            uint32_t            : 4;
      __IOM uint32_t ef_crc_slp_n : 16;         /*!< ef_crc_slp_n                                                              */
    } bit;
  } ef_crc_ctrl_0;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_crc_ctrl_1.                                                            */
    
    struct {
      __IOM uint32_t ef_crc_data_0_en : 32;     /*!< ef_crc_data_0_en                                                          */
    } bit;
  } ef_crc_ctrl_1;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_crc_ctrl_2.                                                            */
    
    struct {
      __IOM uint32_t ef_crc_data_1_en : 32;     /*!< ef_crc_data_1_en                                                          */
    } bit;
  } ef_crc_ctrl_2;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_crc_ctrl_3.                                                            */
    
    struct {
      __IOM uint32_t ef_crc_iv  : 32;           /*!< ef_crc_iv                                                                 */
    } bit;
  } ef_crc_ctrl_3;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_crc_ctrl_4.                                                            */
    
    struct {
      __IOM uint32_t ef_crc_golden : 32;        /*!< ef_crc_golden                                                             */
    } bit;
  } ef_crc_ctrl_4;
  
  union {
    __IOM uint32_t reg;                         /*!< ef_crc_ctrl_5.                                                            */
    
    struct {
      __IOM uint32_t ef_crc_dout : 32;          /*!< ef_crc_dout                                                               */
    } bit;
  } ef_crc_ctrl_5;
} ef_ctrl_Type;                                 /*!< Size = 2584 (0xa18)                                                       */



/* =========================================================================================================================== */
/* ================                                            cci                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief cci. (cci)
  */

typedef struct {                                /*!< cci Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< cci_cfg.                                                                  */
    
    struct {
      __IOM uint32_t cci_en     : 1;            /*!< cci_en                                                                    */
      __IOM uint32_t cci_slv_sel_cci2 : 1;      /*!< cci_slv_sel_cci2                                                          */
      __IOM uint32_t cci_mas_sel_cci2 : 1;      /*!< cci_mas_sel_cci2                                                          */
      __IOM uint32_t cci_mas_hw_mode : 1;       /*!< cci_mas_hw_mode                                                           */
      __IOM uint32_t reg_m_cci_sclk_en : 1;     /*!< reg_m_cci_sclk_en                                                         */
      __IOM uint32_t reg_div_m_cci_sclk : 2;    /*!< reg_div_m_cci_sclk                                                        */
      __IOM uint32_t cfg_cci1_pre_read : 1;     /*!< cfg_cci1_pre_read                                                         */
      __IOM uint32_t reg_scci_clk_inv : 1;      /*!< reg_scci_clk_inv                                                          */
      __IOM uint32_t reg_mcci_clk_inv : 1;      /*!< reg_mcci_clk_inv                                                          */
            uint32_t            : 22;
    } bit;
  } cci_cfg;
  
  union {
    __IOM uint32_t reg;                         /*!< cci_addr.                                                                 */
    
    struct {
      __IOM uint32_t apb_cci_addr : 32;         /*!< apb_cci_addr                                                              */
    } bit;
  } cci_addr;
  
  union {
    __IOM uint32_t reg;                         /*!< cci_wdata.                                                                */
    
    struct {
      __IOM uint32_t apb_cci_wdata : 32;        /*!< apb_cci_wdata                                                             */
    } bit;
  } cci_wdata;
  
  union {
    __IOM uint32_t reg;                         /*!< cci_rdata.                                                                */
    
    struct {
      __IOM uint32_t apb_cci_rdata : 32;        /*!< apb_cci_rdata                                                             */
    } bit;
  } cci_rdata;
  
  union {
    __IOM uint32_t reg;                         /*!< cci_ctl.                                                                  */
    
    struct {
      __IOM uint32_t cci_write_flag : 1;        /*!< cci_write_flag                                                            */
      __IOM uint32_t cci_read_flag : 1;         /*!< cci_read_flag                                                             */
      __IOM uint32_t ahb_state  : 2;            /*!< ahb_state                                                                 */
            uint32_t            : 28;
    } bit;
  } cci_ctl;
} cci_Type;                                     /*!< Size = 20 (0x14)                                                          */



/* =========================================================================================================================== */
/* ================                                            l1c                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief l1c. (l1c)
  */

typedef struct {                                /*!< l1c Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< l1c_config.                                                               */
    
    struct {
      __IOM uint32_t l1c_cacheable : 1;         /*!< l1c_cacheable                                                             */
      __IOM uint32_t l1c_cnt_en : 1;            /*!< l1c_cnt_en                                                                */
      __IOM uint32_t l1c_invalid_en : 1;        /*!< l1c_invalid_en                                                            */
      __IOM uint32_t l1c_invalid_done : 1;      /*!< l1c_invalid_done                                                          */
            uint32_t            : 4;
      __IOM uint32_t l1c_way_dis : 4;           /*!< l1c_way_dis                                                               */
      __IOM uint32_t irom_2t_access : 1;        /*!< irom_2t_access                                                            */
            uint32_t            : 1;
      __IOM uint32_t l1c_bypass : 1;            /*!< l1c_bypass                                                                */
      __IOM uint32_t l1c_bmx_err_en : 1;        /*!< l1c_bmx_err_en                                                            */
      __IOM uint32_t l1c_bmx_arb_mode : 2;      /*!< l1c_bmx_arb_mode                                                          */
            uint32_t            : 2;
      __IOM uint32_t l1c_bmx_timeout_en : 4;    /*!< l1c_bmx_timeout_en                                                        */
      __IOM uint32_t l1c_bmx_busy_option_dis : 1;/*!< l1c_bmx_busy_option_dis                                                  */
      __IOM uint32_t early_resp_dis : 1;        /*!< early_resp_dis                                                            */
      __IOM uint32_t wrap_dis   : 1;            /*!< wrap_dis                                                                  */
            uint32_t            : 5;
    } bit;
  } l1c_config;
  
  union {
    __IOM uint32_t reg;                         /*!< hit_cnt_lsb.                                                              */
    
    struct {
      __IOM uint32_t hit_cnt_lsb : 32;          /*!< hit_cnt_lsb                                                               */
    } bit;
  } hit_cnt_lsb;
  
  union {
    __IOM uint32_t reg;                         /*!< hit_cnt_msb.                                                              */
    
    struct {
      __IOM uint32_t hit_cnt_msb : 32;          /*!< hit_cnt_msb                                                               */
    } bit;
  } hit_cnt_msb;
  
  union {
    __IOM uint32_t reg;                         /*!< miss_cnt.                                                                 */
    
    struct {
      __IOM uint32_t miss_cnt   : 32;           /*!< miss_cnt                                                                  */
    } bit;
  } miss_cnt;
  __IOM uint32_t  l1c_range;                    /*!< l1c_range.                                                                */
  __IM  uint32_t  RESERVED[123];
  
  union {
    __IOM uint32_t reg;                         /*!< l1c_bmx_err_addr_en.                                                      */
    
    struct {
      __IOM uint32_t l1c_bmx_err_addr_dis : 1;  /*!< l1c_bmx_err_addr_dis                                                      */
            uint32_t            : 3;
      __IOM uint32_t l1c_bmx_err_dec : 1;       /*!< l1c_bmx_err_dec                                                           */
      __IOM uint32_t l1c_bmx_err_tz : 1;        /*!< l1c_bmx_err_tz                                                            */
            uint32_t            : 10;
      __IOM uint32_t l1c_hsel_option : 4;       /*!< l1c_hsel_option                                                           */
            uint32_t            : 12;
    } bit;
  } l1c_bmx_err_addr_en;
  
  union {
    __IOM uint32_t reg;                         /*!< l1c_bmx_err_addr.                                                         */
    
    struct {
      __IOM uint32_t l1c_bmx_err_addr : 32;     /*!< l1c_bmx_err_addr                                                          */
    } bit;
  } l1c_bmx_err_addr;
  
  union {
    __IOM uint32_t reg;                         /*!< irom1_misr_dataout_0.                                                     */
    
    struct {
      __IOM uint32_t irom1_misr_dataout_0 : 32; /*!< irom1_misr_dataout_0                                                      */
    } bit;
  } irom1_misr_dataout_0;
  __IOM uint32_t  irom1_misr_dataout_1;         /*!< irom1_misr_dataout_1.                                                     */
  
  union {
    __IOM uint32_t reg;                         /*!< cpu_clk_gate.                                                             */
    
    struct {
      __IOM uint32_t force_e21_clock_on_0 : 1;  /*!< force_e21_clock_on_0                                                      */
      __IOM uint32_t force_e21_clock_on_1 : 1;  /*!< force_e21_clock_on_1                                                      */
      __IOM uint32_t force_e21_clock_on_2 : 1;  /*!< force_e21_clock_on_2                                                      */
            uint32_t            : 29;
    } bit;
  } cpu_clk_gate;
} l1c_Type;                                     /*!< Size = 532 (0x214)                                                        */



/* =========================================================================================================================== */
/* ================                                           uart                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief uart. (uart)
  */

typedef struct {                                /*!< uart Structure                                                            */
  
  union {
    __IOM uint32_t reg;                         /*!< utx_config.                                                               */
    
    struct {
      __IOM uint32_t cr_utx_en  : 1;            /*!< cr_utx_en                                                                 */
      __IOM uint32_t cr_utx_cts_en : 1;         /*!< cr_utx_cts_en                                                             */
      __IOM uint32_t cr_utx_frm_en : 1;         /*!< cr_utx_frm_en                                                             */
            uint32_t            : 1;
      __IOM uint32_t cr_utx_prt_en : 1;         /*!< cr_utx_prt_en                                                             */
      __IOM uint32_t cr_utx_prt_sel : 1;        /*!< cr_utx_prt_sel                                                            */
      __IOM uint32_t cr_utx_ir_en : 1;          /*!< cr_utx_ir_en                                                              */
      __IOM uint32_t cr_utx_ir_inv : 1;         /*!< cr_utx_ir_inv                                                             */
      __IOM uint32_t cr_utx_bit_cnt_d : 3;      /*!< cr_utx_bit_cnt_d                                                          */
            uint32_t            : 1;
      __IOM uint32_t cr_utx_bit_cnt_p : 2;      /*!< cr_utx_bit_cnt_p                                                          */
            uint32_t            : 2;
      __IOM uint32_t cr_utx_len : 16;           /*!< cr_utx_len                                                                */
    } bit;
  } utx_config;
  
  union {
    __IOM uint32_t reg;                         /*!< urx_config.                                                               */
    
    struct {
      __IOM uint32_t cr_urx_en  : 1;            /*!< cr_urx_en                                                                 */
      __IOM uint32_t cr_urx_rts_sw_mode : 1;    /*!< cr_urx_rts_sw_mode                                                        */
      __IOM uint32_t cr_urx_rts_sw_val : 1;     /*!< cr_urx_rts_sw_val                                                         */
      __IOM uint32_t cr_urx_abr_en : 1;         /*!< cr_urx_abr_en                                                             */
      __IOM uint32_t cr_urx_prt_en : 1;         /*!< cr_urx_prt_en                                                             */
      __IOM uint32_t cr_urx_prt_sel : 1;        /*!< cr_urx_prt_sel                                                            */
      __IOM uint32_t cr_urx_ir_en : 1;          /*!< cr_urx_ir_en                                                              */
      __IOM uint32_t cr_urx_ir_inv : 1;         /*!< cr_urx_ir_inv                                                             */
      __IOM uint32_t cr_urx_bit_cnt_d : 3;      /*!< cr_urx_bit_cnt_d                                                          */
      __IOM uint32_t cr_urx_deg_en : 1;         /*!< cr_urx_deg_en                                                             */
      __IOM uint32_t cr_urx_deg_cnt : 4;        /*!< cr_urx_deg_cnt                                                            */
      __IOM uint32_t cr_urx_len : 16;           /*!< cr_urx_len                                                                */
    } bit;
  } urx_config;
  
  union {
    __IOM uint32_t reg;                         /*!< uart_bit_prd.                                                             */
    
    struct {
      __IOM uint32_t cr_utx_bit_prd : 16;       /*!< cr_utx_bit_prd                                                            */
      __IOM uint32_t cr_urx_bit_prd : 16;       /*!< cr_urx_bit_prd                                                            */
    } bit;
  } uart_bit_prd;
  
  union {
    __IOM uint32_t reg;                         /*!< data_config.                                                              */
    
    struct {
      __IOM uint32_t cr_uart_bit_inv : 1;       /*!< cr_uart_bit_inv                                                           */
            uint32_t            : 31;
    } bit;
  } data_config;
  
  union {
    __IOM uint32_t reg;                         /*!< utx_ir_position.                                                          */
    
    struct {
      __IOM uint32_t cr_utx_ir_pos_s : 16;      /*!< cr_utx_ir_pos_s                                                           */
      __IOM uint32_t cr_utx_ir_pos_p : 16;      /*!< cr_utx_ir_pos_p                                                           */
    } bit;
  } utx_ir_position;
  
  union {
    __IOM uint32_t reg;                         /*!< urx_ir_position.                                                          */
    
    struct {
      __IOM uint32_t cr_urx_ir_pos_s : 16;      /*!< cr_urx_ir_pos_s                                                           */
            uint32_t            : 16;
    } bit;
  } urx_ir_position;
  
  union {
    __IOM uint32_t reg;                         /*!< urx_rto_timer.                                                            */
    
    struct {
      __IOM uint32_t cr_urx_rto_value : 8;      /*!< cr_urx_rto_value                                                          */
            uint32_t            : 24;
    } bit;
  } urx_rto_timer;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< UART interrupt status                                                     */
    
    struct {
      __IOM uint32_t utx_end_int : 1;           /*!< utx_end_int                                                               */
      __IOM uint32_t urx_end_int : 1;           /*!< urx_end_int                                                               */
      __IOM uint32_t utx_fifo_int : 1;          /*!< utx_fifo_int                                                              */
      __IOM uint32_t urx_fifo_int : 1;          /*!< urx_fifo_int                                                              */
      __IOM uint32_t urx_rto_int : 1;           /*!< urx_rto_int                                                               */
      __IOM uint32_t urx_pce_int : 1;           /*!< urx_pce_int                                                               */
      __IOM uint32_t utx_fer_int : 1;           /*!< utx_fer_int                                                               */
      __IOM uint32_t urx_fer_int : 1;           /*!< urx_fer_int                                                               */
            uint32_t            : 24;
    } bit;
  } uart_int_sts;
  
  union {
    __IOM uint32_t reg;                         /*!< UART interrupt mask                                                       */
    
    struct {
      __IOM uint32_t cr_utx_end_mask : 1;       /*!< cr_utx_end_mask                                                           */
      __IOM uint32_t cr_urx_end_mask : 1;       /*!< cr_urx_end_mask                                                           */
      __IOM uint32_t cr_utx_fifo_mask : 1;      /*!< cr_utx_fifo_mask                                                          */
      __IOM uint32_t cr_urx_fifo_mask : 1;      /*!< cr_urx_fifo_mask                                                          */
      __IOM uint32_t cr_urx_rto_mask : 1;       /*!< cr_urx_rto_mask                                                           */
      __IOM uint32_t cr_urx_pce_mask : 1;       /*!< cr_urx_pce_mask                                                           */
      __IOM uint32_t cr_utx_fer_mask : 1;       /*!< cr_utx_fer_mask                                                           */
      __IOM uint32_t cr_urx_fer_mask : 1;       /*!< cr_urx_fer_mask                                                           */
            uint32_t            : 24;
    } bit;
  } uart_int_mask;
  
  union {
    __IOM uint32_t reg;                         /*!< UART interrupt clear                                                      */
    
    struct {
      __IOM uint32_t cr_utx_end_clr : 1;        /*!< cr_utx_end_clr                                                            */
      __IOM uint32_t cr_urx_end_clr : 1;        /*!< cr_urx_end_clr                                                            */
      __IOM uint32_t rsvd_2     : 1;            /*!< rsvd_2                                                                    */
      __IOM uint32_t rsvd_3     : 1;            /*!< rsvd_3                                                                    */
      __IOM uint32_t cr_urx_rto_clr : 1;        /*!< cr_urx_rto_clr                                                            */
      __IOM uint32_t cr_urx_pce_clr : 1;        /*!< cr_urx_pce_clr                                                            */
      __IOM uint32_t rsvd_6     : 1;            /*!< rsvd_6                                                                    */
      __IOM uint32_t rsvd_7     : 1;            /*!< rsvd_7                                                                    */
            uint32_t            : 24;
    } bit;
  } uart_int_clear;
  
  union {
    __IOM uint32_t reg;                         /*!< UART interrupt enable                                                     */
    
    struct {
      __IOM uint32_t cr_utx_end_en : 1;         /*!< cr_utx_end_en                                                             */
      __IOM uint32_t cr_urx_end_en : 1;         /*!< cr_urx_end_en                                                             */
      __IOM uint32_t cr_utx_fifo_en : 1;        /*!< cr_utx_fifo_en                                                            */
      __IOM uint32_t cr_urx_fifo_en : 1;        /*!< cr_urx_fifo_en                                                            */
      __IOM uint32_t cr_urx_rto_en : 1;         /*!< cr_urx_rto_en                                                             */
      __IOM uint32_t cr_urx_pce_en : 1;         /*!< cr_urx_pce_en                                                             */
      __IOM uint32_t cr_utx_fer_en : 1;         /*!< cr_utx_fer_en                                                             */
      __IOM uint32_t cr_urx_fer_en : 1;         /*!< cr_urx_fer_en                                                             */
            uint32_t            : 24;
    } bit;
  } uart_int_en;
  
  union {
    __IOM uint32_t reg;                         /*!< uart_status.                                                              */
    
    struct {
      __IOM uint32_t sts_utx_bus_busy : 1;      /*!< sts_utx_bus_busy                                                          */
      __IOM uint32_t sts_urx_bus_busy : 1;      /*!< sts_urx_bus_busy                                                          */
            uint32_t            : 30;
    } bit;
  } uart_status;
  
  union {
    __IOM uint32_t reg;                         /*!< sts_urx_abr_prd.                                                          */
    
    struct {
      __IOM uint32_t sts_urx_abr_prd_start : 16;/*!< sts_urx_abr_prd_start                                                     */
      __IOM uint32_t sts_urx_abr_prd_0x55 : 16; /*!< sts_urx_abr_prd_0x55                                                      */
    } bit;
  } sts_urx_abr_prd;
  __IM  uint32_t  RESERVED1[18];
  
  union {
    __IOM uint32_t reg;                         /*!< uart_fifo_config_0.                                                       */
    
    struct {
      __IOM uint32_t uart_dma_tx_en : 1;        /*!< uart_dma_tx_en                                                            */
      __IOM uint32_t uart_dma_rx_en : 1;        /*!< uart_dma_rx_en                                                            */
      __IOM uint32_t tx_fifo_clr : 1;           /*!< tx_fifo_clr                                                               */
      __IOM uint32_t rx_fifo_clr : 1;           /*!< rx_fifo_clr                                                               */
      __IOM uint32_t tx_fifo_overflow : 1;      /*!< tx_fifo_overflow                                                          */
      __IOM uint32_t tx_fifo_underflow : 1;     /*!< tx_fifo_underflow                                                         */
      __IOM uint32_t rx_fifo_overflow : 1;      /*!< rx_fifo_overflow                                                          */
      __IOM uint32_t rx_fifo_underflow : 1;     /*!< rx_fifo_underflow                                                         */
            uint32_t            : 24;
    } bit;
  } uart_fifo_config_0;
  
  union {
    __IOM uint32_t reg;                         /*!< uart_fifo_config_1.                                                       */
    
    struct {
      __IOM uint32_t tx_fifo_cnt : 6;           /*!< tx_fifo_cnt                                                               */
            uint32_t            : 2;
      __IOM uint32_t rx_fifo_cnt : 6;           /*!< rx_fifo_cnt                                                               */
            uint32_t            : 2;
      __IOM uint32_t tx_fifo_th : 5;            /*!< tx_fifo_th                                                                */
            uint32_t            : 3;
      __IOM uint32_t rx_fifo_th : 5;            /*!< rx_fifo_th                                                                */
            uint32_t            : 3;
    } bit;
  } uart_fifo_config_1;
  
  union {
    __IOM uint32_t reg;                         /*!< uart_fifo_wdata.                                                          */
    
    struct {
      __IOM uint32_t uart_fifo_wdata : 8;       /*!< uart_fifo_wdata                                                           */
            uint32_t            : 24;
    } bit;
  } uart_fifo_wdata;
  
  union {
    __IOM uint32_t reg;                         /*!< uart_fifo_rdata.                                                          */
    
    struct {
      __IOM uint32_t uart_fifo_rdata : 8;       /*!< uart_fifo_rdata                                                           */
            uint32_t            : 24;
    } bit;
  } uart_fifo_rdata;
} uart_Type;                                    /*!< Size = 144 (0x90)                                                         */



/* =========================================================================================================================== */
/* ================                                            spi                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief spi. (spi)
  */

typedef struct {                                /*!< spi Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< spi_config.                                                               */
    
    struct {
      __IOM uint32_t cr_spi_m_en : 1;           /*!< cr_spi_m_en                                                               */
      __IOM uint32_t cr_spi_s_en : 1;           /*!< cr_spi_s_en                                                               */
      __IOM uint32_t cr_spi_frame_size : 2;     /*!< cr_spi_frame_size                                                         */
      __IOM uint32_t cr_spi_sclk_pol : 1;       /*!< cr_spi_sclk_pol                                                           */
      __IOM uint32_t cr_spi_sclk_ph : 1;        /*!< cr_spi_sclk_ph                                                            */
      __IOM uint32_t cr_spi_bit_inv : 1;        /*!< cr_spi_bit_inv                                                            */
      __IOM uint32_t cr_spi_byte_inv : 1;       /*!< cr_spi_byte_inv                                                           */
      __IOM uint32_t cr_spi_rxd_ignr_en : 1;    /*!< cr_spi_rxd_ignr_en                                                        */
      __IOM uint32_t cr_spi_m_cont_en : 1;      /*!< cr_spi_m_cont_en                                                          */
            uint32_t            : 1;
      __IOM uint32_t cr_spi_deg_en : 1;         /*!< cr_spi_deg_en                                                             */
      __IOM uint32_t cr_spi_deg_cnt : 4;        /*!< cr_spi_deg_cnt                                                            */
            uint32_t            : 16;
    } bit;
  } spi_config;
  
  union {
    __IOM uint32_t reg;                         /*!< spi_int_sts.                                                              */
    
    struct {
      __IOM uint32_t spi_end_int : 1;           /*!< spi_end_int                                                               */
      __IOM uint32_t spi_txf_int : 1;           /*!< spi_txf_int                                                               */
      __IOM uint32_t spi_rxf_int : 1;           /*!< spi_rxf_int                                                               */
      __IOM uint32_t spi_sto_int : 1;           /*!< spi_sto_int                                                               */
      __IOM uint32_t spi_txu_int : 1;           /*!< spi_txu_int                                                               */
      __IOM uint32_t spi_fer_int : 1;           /*!< spi_fer_int                                                               */
            uint32_t            : 2;
      __IOM uint32_t cr_spi_end_mask : 1;       /*!< cr_spi_end_mask                                                           */
      __IOM uint32_t cr_spi_txf_mask : 1;       /*!< cr_spi_txf_mask                                                           */
      __IOM uint32_t cr_spi_rxf_mask : 1;       /*!< cr_spi_rxf_mask                                                           */
      __IOM uint32_t cr_spi_sto_mask : 1;       /*!< cr_spi_sto_mask                                                           */
      __IOM uint32_t cr_spi_txu_mask : 1;       /*!< cr_spi_txu_mask                                                           */
      __IOM uint32_t cr_spi_fer_mask : 1;       /*!< cr_spi_fer_mask                                                           */
            uint32_t            : 2;
      __IOM uint32_t cr_spi_end_clr : 1;        /*!< cr_spi_end_clr                                                            */
      __IOM uint32_t rsvd_17    : 1;            /*!< rsvd_17                                                                   */
      __IOM uint32_t rsvd_18    : 1;            /*!< rsvd_18                                                                   */
      __IOM uint32_t cr_spi_sto_clr : 1;        /*!< cr_spi_sto_clr                                                            */
      __IOM uint32_t cr_spi_txu_clr : 1;        /*!< cr_spi_txu_clr                                                            */
      __IOM uint32_t rsvd_21    : 1;            /*!< rsvd_21                                                                   */
            uint32_t            : 2;
      __IOM uint32_t cr_spi_end_en : 1;         /*!< cr_spi_end_en                                                             */
      __IOM uint32_t cr_spi_txf_en : 1;         /*!< cr_spi_txf_en                                                             */
      __IOM uint32_t cr_spi_rxf_en : 1;         /*!< cr_spi_rxf_en                                                             */
      __IOM uint32_t cr_spi_sto_en : 1;         /*!< cr_spi_sto_en                                                             */
      __IOM uint32_t cr_spi_txu_en : 1;         /*!< cr_spi_txu_en                                                             */
      __IOM uint32_t cr_spi_fer_en : 1;         /*!< cr_spi_fer_en                                                             */
            uint32_t            : 2;
    } bit;
  } spi_int_sts;
  
  union {
    __IOM uint32_t reg;                         /*!< spi_bus_busy.                                                             */
    
    struct {
      __IOM uint32_t sts_spi_bus_busy : 1;      /*!< sts_spi_bus_busy                                                          */
            uint32_t            : 31;
    } bit;
  } spi_bus_busy;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< spi_prd_0.                                                                */
    
    struct {
      __IOM uint32_t cr_spi_prd_s : 8;          /*!< cr_spi_prd_s                                                              */
      __IOM uint32_t cr_spi_prd_p : 8;          /*!< cr_spi_prd_p                                                              */
      __IOM uint32_t cr_spi_prd_d_ph_0 : 8;     /*!< cr_spi_prd_d_ph_0                                                         */
      __IOM uint32_t cr_spi_prd_d_ph_1 : 8;     /*!< cr_spi_prd_d_ph_1                                                         */
    } bit;
  } spi_prd_0;
  
  union {
    __IOM uint32_t reg;                         /*!< spi_prd_1.                                                                */
    
    struct {
      __IOM uint32_t cr_spi_prd_i : 8;          /*!< cr_spi_prd_i                                                              */
            uint32_t            : 24;
    } bit;
  } spi_prd_1;
  
  union {
    __IOM uint32_t reg;                         /*!< spi_rxd_ignr.                                                             */
    
    struct {
      __IOM uint32_t cr_spi_rxd_ignr_p : 5;     /*!< cr_spi_rxd_ignr_p                                                         */
            uint32_t            : 11;
      __IOM uint32_t cr_spi_rxd_ignr_s : 5;     /*!< cr_spi_rxd_ignr_s                                                         */
            uint32_t            : 11;
    } bit;
  } spi_rxd_ignr;
  
  union {
    __IOM uint32_t reg;                         /*!< spi_sto_value.                                                            */
    
    struct {
      __IOM uint32_t cr_spi_sto_value : 12;     /*!< cr_spi_sto_value                                                          */
            uint32_t            : 20;
    } bit;
  } spi_sto_value;
  __IM  uint32_t  RESERVED1[24];
  
  union {
    __IOM uint32_t reg;                         /*!< spi_fifo_config_0.                                                        */
    
    struct {
      __IOM uint32_t spi_dma_tx_en : 1;         /*!< spi_dma_tx_en                                                             */
      __IOM uint32_t spi_dma_rx_en : 1;         /*!< spi_dma_rx_en                                                             */
      __IOM uint32_t tx_fifo_clr : 1;           /*!< tx_fifo_clr                                                               */
      __IOM uint32_t rx_fifo_clr : 1;           /*!< rx_fifo_clr                                                               */
      __IOM uint32_t tx_fifo_overflow : 1;      /*!< tx_fifo_overflow                                                          */
      __IOM uint32_t tx_fifo_underflow : 1;     /*!< tx_fifo_underflow                                                         */
      __IOM uint32_t rx_fifo_overflow : 1;      /*!< rx_fifo_overflow                                                          */
      __IOM uint32_t rx_fifo_underflow : 1;     /*!< rx_fifo_underflow                                                         */
            uint32_t            : 24;
    } bit;
  } spi_fifo_config_0;
  
  union {
    __IOM uint32_t reg;                         /*!< spi_fifo_config_1.                                                        */
    
    struct {
      __IOM uint32_t tx_fifo_cnt : 3;           /*!< tx_fifo_cnt                                                               */
            uint32_t            : 5;
      __IOM uint32_t rx_fifo_cnt : 3;           /*!< rx_fifo_cnt                                                               */
            uint32_t            : 5;
      __IOM uint32_t tx_fifo_th : 2;            /*!< tx_fifo_th                                                                */
            uint32_t            : 6;
      __IOM uint32_t rx_fifo_th : 2;            /*!< rx_fifo_th                                                                */
            uint32_t            : 6;
    } bit;
  } spi_fifo_config_1;
  
  union {
    __IOM uint32_t reg;                         /*!< spi_fifo_wdata.                                                           */
    
    struct {
      __IOM uint32_t spi_fifo_wdata : 32;       /*!< spi_fifo_wdata                                                            */
    } bit;
  } spi_fifo_wdata;
  
  union {
    __IOM uint32_t reg;                         /*!< spi_fifo_rdata.                                                           */
    
    struct {
      __IOM uint32_t spi_fifo_rdata : 32;       /*!< spi_fifo_rdata                                                            */
    } bit;
  } spi_fifo_rdata;
} spi_Type;                                     /*!< Size = 144 (0x90)                                                         */



/* =========================================================================================================================== */
/* ================                                            i2c                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief i2c. (i2c)
  */

typedef struct {                                /*!< i2c Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_config.                                                               */
    
    struct {
      __IOM uint32_t cr_i2c_m_en : 1;           /*!< cr_i2c_m_en                                                               */
      __IOM uint32_t cr_i2c_pkt_dir : 1;        /*!< cr_i2c_pkt_dir                                                            */
      __IOM uint32_t cr_i2c_deg_en : 1;         /*!< cr_i2c_deg_en                                                             */
      __IOM uint32_t cr_i2c_scl_sync_en : 1;    /*!< cr_i2c_scl_sync_en                                                        */
      __IOM uint32_t cr_i2c_sub_addr_en : 1;    /*!< cr_i2c_sub_addr_en                                                        */
      __IOM uint32_t cr_i2c_sub_addr_bc : 2;    /*!< cr_i2c_sub_addr_bc                                                        */
            uint32_t            : 1;
      __IOM uint32_t cr_i2c_slv_addr : 7;       /*!< cr_i2c_slv_addr                                                           */
            uint32_t            : 1;
      __IOM uint32_t cr_i2c_pkt_len : 8;        /*!< cr_i2c_pkt_len                                                            */
            uint32_t            : 4;
      __IOM uint32_t cr_i2c_deg_cnt : 4;        /*!< cr_i2c_deg_cnt                                                            */
    } bit;
  } i2c_config;
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_int_sts.                                                              */
    
    struct {
      __IOM uint32_t i2c_end_int : 1;           /*!< i2c_end_int                                                               */
      __IOM uint32_t i2c_txf_int : 1;           /*!< i2c_txf_int                                                               */
      __IOM uint32_t i2c_rxf_int : 1;           /*!< i2c_rxf_int                                                               */
      __IOM uint32_t i2c_nak_int : 1;           /*!< i2c_nak_int                                                               */
      __IOM uint32_t i2c_arb_int : 1;           /*!< i2c_arb_int                                                               */
      __IOM uint32_t i2c_fer_int : 1;           /*!< i2c_fer_int                                                               */
            uint32_t            : 2;
      __IOM uint32_t cr_i2c_end_mask : 1;       /*!< cr_i2c_end_mask                                                           */
      __IOM uint32_t cr_i2c_txf_mask : 1;       /*!< cr_i2c_txf_mask                                                           */
      __IOM uint32_t cr_i2c_rxf_mask : 1;       /*!< cr_i2c_rxf_mask                                                           */
      __IOM uint32_t cr_i2c_nak_mask : 1;       /*!< cr_i2c_nak_mask                                                           */
      __IOM uint32_t cr_i2c_arb_mask : 1;       /*!< cr_i2c_arb_mask                                                           */
      __IOM uint32_t cr_i2c_fer_mask : 1;       /*!< cr_i2c_fer_mask                                                           */
            uint32_t            : 2;
      __IOM uint32_t cr_i2c_end_clr : 1;        /*!< cr_i2c_end_clr                                                            */
      __IOM uint32_t rsvd_17    : 1;            /*!< rsvd_17                                                                   */
      __IOM uint32_t rsvd_18    : 1;            /*!< rsvd_18                                                                   */
      __IOM uint32_t cr_i2c_nak_clr : 1;        /*!< cr_i2c_nak_clr                                                            */
      __IOM uint32_t cr_i2c_arb_clr : 1;        /*!< cr_i2c_arb_clr                                                            */
      __IOM uint32_t rsvd_21    : 1;            /*!< rsvd_21                                                                   */
            uint32_t            : 2;
      __IOM uint32_t cr_i2c_end_en : 1;         /*!< cr_i2c_end_en                                                             */
      __IOM uint32_t cr_i2c_txf_en : 1;         /*!< cr_i2c_txf_en                                                             */
      __IOM uint32_t cr_i2c_rxf_en : 1;         /*!< cr_i2c_rxf_en                                                             */
      __IOM uint32_t cr_i2c_nak_en : 1;         /*!< cr_i2c_nak_en                                                             */
      __IOM uint32_t cr_i2c_arb_en : 1;         /*!< cr_i2c_arb_en                                                             */
      __IOM uint32_t cr_i2c_fer_en : 1;         /*!< cr_i2c_fer_en                                                             */
            uint32_t            : 2;
    } bit;
  } i2c_int_sts;
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_sub_addr.                                                             */
    
    struct {
      __IOM uint32_t cr_i2c_sub_addr_b0 : 8;    /*!< cr_i2c_sub_addr_b0                                                        */
      __IOM uint32_t cr_i2c_sub_addr_b1 : 8;    /*!< cr_i2c_sub_addr_b1                                                        */
      __IOM uint32_t cr_i2c_sub_addr_b2 : 8;    /*!< cr_i2c_sub_addr_b2                                                        */
      __IOM uint32_t cr_i2c_sub_addr_b3 : 8;    /*!< cr_i2c_sub_addr_b3                                                        */
    } bit;
  } i2c_sub_addr;
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_bus_busy.                                                             */
    
    struct {
      __IOM uint32_t sts_i2c_bus_busy : 1;      /*!< sts_i2c_bus_busy                                                          */
      __IOM uint32_t cr_i2c_bus_busy_clr : 1;   /*!< cr_i2c_bus_busy_clr                                                       */
            uint32_t            : 30;
    } bit;
  } i2c_bus_busy;
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_prd_start.                                                            */
    
    struct {
      __IOM uint32_t cr_i2c_prd_s_ph_0 : 8;     /*!< cr_i2c_prd_s_ph_0                                                         */
      __IOM uint32_t cr_i2c_prd_s_ph_1 : 8;     /*!< cr_i2c_prd_s_ph_1                                                         */
      __IOM uint32_t cr_i2c_prd_s_ph_2 : 8;     /*!< cr_i2c_prd_s_ph_2                                                         */
      __IOM uint32_t cr_i2c_prd_s_ph_3 : 8;     /*!< cr_i2c_prd_s_ph_3                                                         */
    } bit;
  } i2c_prd_start;
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_prd_stop.                                                             */
    
    struct {
      __IOM uint32_t cr_i2c_prd_p_ph_0 : 8;     /*!< cr_i2c_prd_p_ph_0                                                         */
      __IOM uint32_t cr_i2c_prd_p_ph_1 : 8;     /*!< cr_i2c_prd_p_ph_1                                                         */
      __IOM uint32_t cr_i2c_prd_p_ph_2 : 8;     /*!< cr_i2c_prd_p_ph_2                                                         */
      __IOM uint32_t cr_i2c_prd_p_ph_3 : 8;     /*!< cr_i2c_prd_p_ph_3                                                         */
    } bit;
  } i2c_prd_stop;
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_prd_data.                                                             */
    
    struct {
      __IOM uint32_t cr_i2c_prd_d_ph_0 : 8;     /*!< cr_i2c_prd_d_ph_0                                                         */
      __IOM uint32_t cr_i2c_prd_d_ph_1 : 8;     /*!< cr_i2c_prd_d_ph_1                                                         */
      __IOM uint32_t cr_i2c_prd_d_ph_2 : 8;     /*!< cr_i2c_prd_d_ph_2                                                         */
      __IOM uint32_t cr_i2c_prd_d_ph_3 : 8;     /*!< cr_i2c_prd_d_ph_3                                                         */
    } bit;
  } i2c_prd_data;
  __IM  uint32_t  RESERVED[25];
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_fifo_config_0.                                                        */
    
    struct {
      __IOM uint32_t i2c_dma_tx_en : 1;         /*!< i2c_dma_tx_en                                                             */
      __IOM uint32_t i2c_dma_rx_en : 1;         /*!< i2c_dma_rx_en                                                             */
      __IOM uint32_t tx_fifo_clr : 1;           /*!< tx_fifo_clr                                                               */
      __IOM uint32_t rx_fifo_clr : 1;           /*!< rx_fifo_clr                                                               */
      __IOM uint32_t tx_fifo_overflow : 1;      /*!< tx_fifo_overflow                                                          */
      __IOM uint32_t tx_fifo_underflow : 1;     /*!< tx_fifo_underflow                                                         */
      __IOM uint32_t rx_fifo_overflow : 1;      /*!< rx_fifo_overflow                                                          */
      __IOM uint32_t rx_fifo_underflow : 1;     /*!< rx_fifo_underflow                                                         */
            uint32_t            : 24;
    } bit;
  } i2c_fifo_config_0;
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_fifo_config_1.                                                        */
    
    struct {
      __IOM uint32_t tx_fifo_cnt : 2;           /*!< tx_fifo_cnt                                                               */
            uint32_t            : 6;
      __IOM uint32_t rx_fifo_cnt : 2;           /*!< rx_fifo_cnt                                                               */
            uint32_t            : 6;
      __IOM uint32_t tx_fifo_th : 1;            /*!< tx_fifo_th                                                                */
            uint32_t            : 7;
      __IOM uint32_t rx_fifo_th : 1;            /*!< rx_fifo_th                                                                */
            uint32_t            : 7;
    } bit;
  } i2c_fifo_config_1;
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_fifo_wdata.                                                           */
    
    struct {
      __IOM uint32_t i2c_fifo_wdata : 32;       /*!< i2c_fifo_wdata                                                            */
    } bit;
  } i2c_fifo_wdata;
  
  union {
    __IOM uint32_t reg;                         /*!< i2c_fifo_rdata.                                                           */
    
    struct {
      __IOM uint32_t i2c_fifo_rdata : 32;       /*!< i2c_fifo_rdata                                                            */
    } bit;
  } i2c_fifo_rdata;
} i2c_Type;                                     /*!< Size = 144 (0x90)                                                         */



/* =========================================================================================================================== */
/* ================                                            pwm                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief pwm. (pwm)
  */

typedef struct {                                /*!< pwm Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< pwm_int_config.                                                           */
    
    struct {
      __IOM uint32_t pwm_interrupt_sts : 6;     /*!< pwm_interrupt_sts                                                         */
            uint32_t            : 2;
      __IOM uint32_t pwm_int_clear : 6;         /*!< pwm_int_clear                                                             */
            uint32_t            : 18;
    } bit;
  } pwm_int_config;
  __IM  uint32_t  RESERVED[7];
  
  union {
    __IOM uint32_t reg;                         /*!< pwm0_clkdiv.                                                              */
    
    struct {
      __IOM uint32_t pwm_clk_div : 16;          /*!< pwm_clk_div                                                               */
            uint32_t            : 16;
    } bit;
  } pwm0_clkdiv;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm0_thre1.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre1  : 16;           /*!< pwm_thre1                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm0_thre1;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm0_thre2.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre2  : 16;           /*!< pwm_thre2                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm0_thre2;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm0_period.                                                              */
    
    struct {
      __IOM uint32_t pwm_period : 16;           /*!< pwm_period                                                                */
            uint32_t            : 16;
    } bit;
  } pwm0_period;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm0_config.                                                              */
    
    struct {
      __IOM uint32_t reg_clk_sel : 2;           /*!< reg_clk_sel                                                               */
      __IOM uint32_t pwm_out_inv : 1;           /*!< pwm_out_inv                                                               */
      __IOM uint32_t pwm_stop_mode : 1;         /*!< pwm_stop_mode                                                             */
      __IOM uint32_t pwm_sw_force_val : 1;      /*!< pwm_sw_force_val                                                          */
      __IOM uint32_t pwm_sw_mode : 1;           /*!< pwm_sw_mode                                                               */
      __IOM uint32_t pwm_stop_en : 1;           /*!< pwm_stop_en                                                               */
      __IOM uint32_t pwm_sts_top : 1;           /*!< pwm_sts_top                                                               */
            uint32_t            : 24;
    } bit;
  } pwm0_config;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm0_interrupt.                                                           */
    
    struct {
      __IOM uint32_t pwm_int_period_cnt : 16;   /*!< pwm_int_period_cnt                                                        */
      __IOM uint32_t pwm_int_enable : 1;        /*!< pwm_int_enable                                                            */
            uint32_t            : 15;
    } bit;
  } pwm0_interrupt;
  __IM  uint32_t  RESERVED1[2];
  
  union {
    __IOM uint32_t reg;                         /*!< pwm1_clkdiv.                                                              */
    
    struct {
      __IOM uint32_t pwm_clk_div : 16;          /*!< pwm_clk_div                                                               */
            uint32_t            : 16;
    } bit;
  } pwm1_clkdiv;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm1_thre1.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre1  : 16;           /*!< pwm_thre1                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm1_thre1;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm1_thre2.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre2  : 16;           /*!< pwm_thre2                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm1_thre2;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm1_period.                                                              */
    
    struct {
      __IOM uint32_t pwm_period : 16;           /*!< pwm_period                                                                */
            uint32_t            : 16;
    } bit;
  } pwm1_period;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm1_config.                                                              */
    
    struct {
      __IOM uint32_t reg_clk_sel : 2;           /*!< reg_clk_sel                                                               */
      __IOM uint32_t pwm_out_inv : 1;           /*!< pwm_out_inv                                                               */
      __IOM uint32_t pwm_stop_mode : 1;         /*!< pwm_stop_mode                                                             */
      __IOM uint32_t pwm_sw_force_val : 1;      /*!< pwm_sw_force_val                                                          */
      __IOM uint32_t pwm_sw_mode : 1;           /*!< pwm_sw_mode                                                               */
      __IOM uint32_t pwm_stop_en : 1;           /*!< pwm_stop_en                                                               */
      __IOM uint32_t pwm_sts_top : 1;           /*!< pwm_sts_top                                                               */
            uint32_t            : 24;
    } bit;
  } pwm1_config;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm1_interrupt.                                                           */
    
    struct {
      __IOM uint32_t pwm_int_period_cnt : 16;   /*!< pwm_int_period_cnt                                                        */
      __IOM uint32_t pwm_int_enable : 1;        /*!< pwm_int_enable                                                            */
            uint32_t            : 15;
    } bit;
  } pwm1_interrupt;
  __IM  uint32_t  RESERVED2[2];
  
  union {
    __IOM uint32_t reg;                         /*!< pwm2_clkdiv.                                                              */
    
    struct {
      __IOM uint32_t pwm_clk_div : 16;          /*!< pwm_clk_div                                                               */
            uint32_t            : 16;
    } bit;
  } pwm2_clkdiv;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm2_thre1.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre1  : 16;           /*!< pwm_thre1                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm2_thre1;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm2_thre2.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre2  : 16;           /*!< pwm_thre2                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm2_thre2;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm2_period.                                                              */
    
    struct {
      __IOM uint32_t pwm_period : 16;           /*!< pwm_period                                                                */
            uint32_t            : 16;
    } bit;
  } pwm2_period;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm2_config.                                                              */
    
    struct {
      __IOM uint32_t reg_clk_sel : 2;           /*!< reg_clk_sel                                                               */
      __IOM uint32_t pwm_out_inv : 1;           /*!< pwm_out_inv                                                               */
      __IOM uint32_t pwm_stop_mode : 1;         /*!< pwm_stop_mode                                                             */
      __IOM uint32_t pwm_sw_force_val : 1;      /*!< pwm_sw_force_val                                                          */
      __IOM uint32_t pwm_sw_mode : 1;           /*!< pwm_sw_mode                                                               */
      __IOM uint32_t pwm_stop_en : 1;           /*!< pwm_stop_en                                                               */
      __IOM uint32_t pwm_sts_top : 1;           /*!< pwm_sts_top                                                               */
            uint32_t            : 24;
    } bit;
  } pwm2_config;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm2_interrupt.                                                           */
    
    struct {
      __IOM uint32_t pwm_int_period_cnt : 16;   /*!< pwm_int_period_cnt                                                        */
      __IOM uint32_t pwm_int_enable : 1;        /*!< pwm_int_enable                                                            */
            uint32_t            : 15;
    } bit;
  } pwm2_interrupt;
  __IM  uint32_t  RESERVED3[2];
  
  union {
    __IOM uint32_t reg;                         /*!< pwm3_clkdiv.                                                              */
    
    struct {
      __IOM uint32_t pwm_clk_div : 16;          /*!< pwm_clk_div                                                               */
            uint32_t            : 16;
    } bit;
  } pwm3_clkdiv;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm3_thre1.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre1  : 16;           /*!< pwm_thre1                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm3_thre1;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm3_thre2.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre2  : 16;           /*!< pwm_thre2                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm3_thre2;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm3_period.                                                              */
    
    struct {
      __IOM uint32_t pwm_period : 16;           /*!< pwm_period                                                                */
            uint32_t            : 16;
    } bit;
  } pwm3_period;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm3_config.                                                              */
    
    struct {
      __IOM uint32_t reg_clk_sel : 2;           /*!< reg_clk_sel                                                               */
      __IOM uint32_t pwm_out_inv : 1;           /*!< pwm_out_inv                                                               */
      __IOM uint32_t pwm_stop_mode : 1;         /*!< pwm_stop_mode                                                             */
      __IOM uint32_t pwm_sw_force_val : 1;      /*!< pwm_sw_force_val                                                          */
      __IOM uint32_t pwm_sw_mode : 1;           /*!< pwm_sw_mode                                                               */
      __IOM uint32_t pwm_stop_en : 1;           /*!< pwm_stop_en                                                               */
      __IOM uint32_t pwm_sts_top : 1;           /*!< pwm_sts_top                                                               */
            uint32_t            : 24;
    } bit;
  } pwm3_config;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm3_interrupt.                                                           */
    
    struct {
      __IOM uint32_t pwm_int_period_cnt : 16;   /*!< pwm_int_period_cnt                                                        */
      __IOM uint32_t pwm_int_enable : 1;        /*!< pwm_int_enable                                                            */
            uint32_t            : 15;
    } bit;
  } pwm3_interrupt;
  __IM  uint32_t  RESERVED4[2];
  
  union {
    __IOM uint32_t reg;                         /*!< pwm4_clkdiv.                                                              */
    
    struct {
      __IOM uint32_t pwm_clk_div : 16;          /*!< pwm_clk_div                                                               */
            uint32_t            : 16;
    } bit;
  } pwm4_clkdiv;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm4_thre1.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre1  : 16;           /*!< pwm_thre1                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm4_thre1;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm4_thre2.                                                               */
    
    struct {
      __IOM uint32_t pwm_thre2  : 16;           /*!< pwm_thre2                                                                 */
            uint32_t            : 16;
    } bit;
  } pwm4_thre2;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm4_period.                                                              */
    
    struct {
      __IOM uint32_t pwm_period : 16;           /*!< pwm_period                                                                */
            uint32_t            : 16;
    } bit;
  } pwm4_period;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm4_config.                                                              */
    
    struct {
      __IOM uint32_t reg_clk_sel : 2;           /*!< reg_clk_sel                                                               */
      __IOM uint32_t pwm_out_inv : 1;           /*!< pwm_out_inv                                                               */
      __IOM uint32_t pwm_stop_mode : 1;         /*!< pwm_stop_mode                                                             */
      __IOM uint32_t pwm_sw_force_val : 1;      /*!< pwm_sw_force_val                                                          */
      __IOM uint32_t pwm_sw_mode : 1;           /*!< pwm_sw_mode                                                               */
      __IOM uint32_t pwm_stop_en : 1;           /*!< pwm_stop_en                                                               */
      __IOM uint32_t pwm_sts_top : 1;           /*!< pwm_sts_top                                                               */
            uint32_t            : 24;
    } bit;
  } pwm4_config;
  
  union {
    __IOM uint32_t reg;                         /*!< pwm4_interrupt.                                                           */
    
    struct {
      __IOM uint32_t pwm_int_period_cnt : 16;   /*!< pwm_int_period_cnt                                                        */
      __IOM uint32_t pwm_int_enable : 1;        /*!< pwm_int_enable                                                            */
            uint32_t            : 15;
    } bit;
  } pwm4_interrupt;
} pwm_Type;                                     /*!< Size = 184 (0xb8)                                                         */



/* =========================================================================================================================== */
/* ================                                           timer                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief timer. (timer)
  */

typedef struct {                                /*!< timer Structure                                                           */
  
  union {
    __IOM uint32_t reg;                         /*!< TCCR.                                                                     */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t cs_1       : 2;            /*!< cs_1                                                                      */
      __IOM uint32_t RESERVED_4 : 1;            /*!< RESERVED_4                                                                */
      __IOM uint32_t cs_2       : 2;            /*!< cs_2                                                                      */
      __IOM uint32_t RESERVED_7 : 1;            /*!< RESERVED_7                                                                */
      __IOM uint32_t cs_wdt     : 2;            /*!< cs_wdt                                                                    */
            uint32_t            : 22;
    } bit;
  } TCCR;
  __IM  uint32_t  RESERVED[3];
  
  union {
    __IOM uint32_t reg;                         /*!< TMR2_0.                                                                   */
    
    struct {
      __IOM uint32_t tmr        : 32;           /*!< tmr                                                                       */
    } bit;
  } TMR2_0;
  
  union {
    __IOM uint32_t reg;                         /*!< TMR2_1.                                                                   */
    
    struct {
      __IOM uint32_t tmr        : 32;           /*!< tmr                                                                       */
    } bit;
  } TMR2_1;
  
  union {
    __IOM uint32_t reg;                         /*!< TMR2_2.                                                                   */
    
    struct {
      __IOM uint32_t tmr        : 32;           /*!< tmr                                                                       */
    } bit;
  } TMR2_2;
  
  union {
    __IOM uint32_t reg;                         /*!< TMR3_0.                                                                   */
    
    struct {
      __IOM uint32_t tmr        : 32;           /*!< tmr                                                                       */
    } bit;
  } TMR3_0;
  
  union {
    __IOM uint32_t reg;                         /*!< TMR3_1.                                                                   */
    
    struct {
      __IOM uint32_t tmr        : 32;           /*!< tmr                                                                       */
    } bit;
  } TMR3_1;
  
  union {
    __IOM uint32_t reg;                         /*!< TMR3_2.                                                                   */
    
    struct {
      __IOM uint32_t tmr        : 32;           /*!< tmr                                                                       */
    } bit;
  } TMR3_2;
  __IM  uint32_t  RESERVED1;
  
  union {
    __IOM uint32_t reg;                         /*!< TCR2.                                                                     */
    
    struct {
      __IOM uint32_t tcr        : 32;           /*!< tcr                                                                       */
    } bit;
  } TCR2;
  
  union {
    __IOM uint32_t reg;                         /*!< TCR3.                                                                     */
    
    struct {
      __IOM uint32_t tcr3_counter : 32;         /*!< tcr3_counter                                                              */
    } bit;
  } TCR3;
  __IM  uint32_t  RESERVED2;
  
  union {
    __IOM uint32_t reg;                         /*!< TMSR2.                                                                    */
    
    struct {
      __IOM uint32_t tmsr_0     : 1;            /*!< tmsr_0                                                                    */
      __IOM uint32_t tmsr_1     : 1;            /*!< tmsr_1                                                                    */
      __IOM uint32_t tmsr_2     : 1;            /*!< tmsr_2                                                                    */
            uint32_t            : 29;
    } bit;
  } TMSR2;
  
  union {
    __IOM uint32_t reg;                         /*!< TMSR3.                                                                    */
    
    struct {
      __IOM uint32_t tmsr_0     : 1;            /*!< tmsr_0                                                                    */
      __IOM uint32_t tmsr_1     : 1;            /*!< tmsr_1                                                                    */
      __IOM uint32_t tmsr_2     : 1;            /*!< tmsr_2                                                                    */
            uint32_t            : 29;
    } bit;
  } TMSR3;
  __IM  uint32_t  RESERVED3;
  
  union {
    __IOM uint32_t reg;                         /*!< TIER2.                                                                    */
    
    struct {
      __IOM uint32_t tier_0     : 1;            /*!< tier_0                                                                    */
      __IOM uint32_t tier_1     : 1;            /*!< tier_1                                                                    */
      __IOM uint32_t tier_2     : 1;            /*!< tier_2                                                                    */
            uint32_t            : 29;
    } bit;
  } TIER2;
  
  union {
    __IOM uint32_t reg;                         /*!< TIER3.                                                                    */
    
    struct {
      __IOM uint32_t tier_0     : 1;            /*!< tier_0                                                                    */
      __IOM uint32_t tier_1     : 1;            /*!< tier_1                                                                    */
      __IOM uint32_t tier_2     : 1;            /*!< tier_2                                                                    */
            uint32_t            : 29;
    } bit;
  } TIER3;
  __IM  uint32_t  RESERVED4;
  
  union {
    __IOM uint32_t reg;                         /*!< TPLVR2.                                                                   */
    
    struct {
      __IOM uint32_t tplvr      : 32;           /*!< tplvr                                                                     */
    } bit;
  } TPLVR2;
  
  union {
    __IOM uint32_t reg;                         /*!< TPLVR3.                                                                   */
    
    struct {
      __IOM uint32_t tplvr      : 32;           /*!< tplvr                                                                     */
    } bit;
  } TPLVR3;
  __IM  uint32_t  RESERVED5;
  
  union {
    __IOM uint32_t reg;                         /*!< TPLCR2.                                                                   */
    
    struct {
      __IOM uint32_t tplcr      : 2;            /*!< tplcr                                                                     */
            uint32_t            : 30;
    } bit;
  } TPLCR2;
  
  union {
    __IOM uint32_t reg;                         /*!< TPLCR3.                                                                   */
    
    struct {
      __IOM uint32_t tplcr      : 2;            /*!< tplcr                                                                     */
            uint32_t            : 30;
    } bit;
  } TPLCR3;
  
  union {
    __IOM uint32_t reg;                         /*!< WMER.                                                                     */
    
    struct {
      __IOM uint32_t we         : 1;            /*!< we                                                                        */
      __IOM uint32_t wrie       : 1;            /*!< wrie                                                                      */
            uint32_t            : 30;
    } bit;
  } WMER;
  
  union {
    __IOM uint32_t reg;                         /*!< WMR.                                                                      */
    
    struct {
      __IOM uint32_t wmr        : 16;           /*!< wmr                                                                       */
            uint32_t            : 16;
    } bit;
  } WMR;
  
  union {
    __IOM uint32_t reg;                         /*!< WVR.                                                                      */
    
    struct {
      __IOM uint32_t wvr        : 16;           /*!< wvr                                                                       */
            uint32_t            : 16;
    } bit;
  } WVR;
  
  union {
    __IOM uint32_t reg;                         /*!< WSR.                                                                      */
    
    struct {
      __IOM uint32_t wts        : 1;            /*!< wts                                                                       */
            uint32_t            : 31;
    } bit;
  } WSR;
  __IM  uint32_t  RESERVED6;
  
  union {
    __IOM uint32_t reg;                         /*!< TICR2.                                                                    */
    
    struct {
      __IOM uint32_t tclr_0     : 1;            /*!< tclr_0                                                                    */
      __IOM uint32_t tclr_1     : 1;            /*!< tclr_1                                                                    */
      __IOM uint32_t tclr_2     : 1;            /*!< tclr_2                                                                    */
            uint32_t            : 29;
    } bit;
  } TICR2;
  
  union {
    __IOM uint32_t reg;                         /*!< TICR3.                                                                    */
    
    struct {
      __IOM uint32_t tclr_0     : 1;            /*!< tclr_0                                                                    */
      __IOM uint32_t tclr_1     : 1;            /*!< tclr_1                                                                    */
      __IOM uint32_t tclr_2     : 1;            /*!< tclr_2                                                                    */
            uint32_t            : 29;
    } bit;
  } TICR3;
  
  union {
    __IOM uint32_t reg;                         /*!< WICR.                                                                     */
    
    struct {
      __IOM uint32_t wiclr      : 1;            /*!< wiclr                                                                     */
            uint32_t            : 31;
    } bit;
  } WICR;
  
  union {
    __IOM uint32_t reg;                         /*!< TCER.                                                                     */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t timer2_en  : 1;            /*!< timer2_en                                                                 */
      __IOM uint32_t timer3_en  : 1;            /*!< timer3_en                                                                 */
            uint32_t            : 29;
    } bit;
  } TCER;
  
  union {
    __IOM uint32_t reg;                         /*!< TCMR.                                                                     */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t timer2_mode : 1;           /*!< timer2_mode                                                               */
      __IOM uint32_t timer3_mode : 1;           /*!< timer3_mode                                                               */
            uint32_t            : 29;
    } bit;
  } TCMR;
  __IM  uint32_t  RESERVED7;
  
  union {
    __IOM uint32_t reg;                         /*!< TILR2.                                                                    */
    
    struct {
      __IOM uint32_t tilr_0     : 1;            /*!< tilr_0                                                                    */
      __IOM uint32_t tilr_1     : 1;            /*!< tilr_1                                                                    */
      __IOM uint32_t tilr_2     : 1;            /*!< tilr_2                                                                    */
            uint32_t            : 29;
    } bit;
  } TILR2;
  
  union {
    __IOM uint32_t reg;                         /*!< TILR3.                                                                    */
    
    struct {
      __IOM uint32_t tilr_0     : 1;            /*!< tilr_0                                                                    */
      __IOM uint32_t tilr_1     : 1;            /*!< tilr_1                                                                    */
      __IOM uint32_t tilr_2     : 1;            /*!< tilr_2                                                                    */
            uint32_t            : 29;
    } bit;
  } TILR3;
  
  union {
    __IOM uint32_t reg;                         /*!< WCR.                                                                      */
    
    struct {
      __IOM uint32_t wcr        : 1;            /*!< wcr                                                                       */
            uint32_t            : 31;
    } bit;
  } WCR;
  
  union {
    __IOM uint32_t reg;                         /*!< WFAR.                                                                     */
    
    struct {
      __IOM uint32_t wfar       : 16;           /*!< wfar                                                                      */
            uint32_t            : 16;
    } bit;
  } WFAR;
  
  union {
    __IOM uint32_t reg;                         /*!< WSAR.                                                                     */
    
    struct {
      __IOM uint32_t wsar       : 16;           /*!< wsar                                                                      */
            uint32_t            : 16;
    } bit;
  } WSAR;
  __IM  uint32_t  RESERVED8;
  
  union {
    __IOM uint32_t reg;                         /*!< TCVWR2.                                                                   */
    
    struct {
      __IOM uint32_t tcvwr      : 32;           /*!< tcvwr                                                                     */
    } bit;
  } TCVWR2;
  
  union {
    __IOM uint32_t reg;                         /*!< TCVWR3.                                                                   */
    
    struct {
      __IOM uint32_t tcvwr      : 32;           /*!< tcvwr                                                                     */
    } bit;
  } TCVWR3;
  __IM  uint32_t  RESERVED9;
  
  union {
    __IOM uint32_t reg;                         /*!< TCVSYN2.                                                                  */
    
    struct {
      __IOM uint32_t tcvsyn2    : 32;           /*!< tcvsyn2                                                                   */
    } bit;
  } TCVSYN2;
  
  union {
    __IOM uint32_t reg;                         /*!< TCVSYN3.                                                                  */
    
    struct {
      __IOM uint32_t tcvsyn3    : 32;           /*!< tcvsyn3                                                                   */
    } bit;
  } TCVSYN3;
  
  union {
    __IOM uint32_t reg;                         /*!< TCDR.                                                                     */
    
    struct {
            uint32_t            : 8;
      __IOM uint32_t tcdr2      : 8;            /*!< tcdr2                                                                     */
      __IOM uint32_t tcdr3      : 8;            /*!< tcdr3                                                                     */
      __IOM uint32_t wcdr       : 8;            /*!< wcdr                                                                      */
    } bit;
  } TCDR;
} timer_Type;                                   /*!< Size = 192 (0xc0)                                                         */



/* =========================================================================================================================== */
/* ================                                            ir                                             ================ */
/* =========================================================================================================================== */


/**
  * @brief ir. (ir)
  */

typedef struct {                                /*!< ir Structure                                                              */
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_config.                                                              */
    
    struct {
      __IOM uint32_t cr_irtx_en : 1;            /*!< cr_irtx_en                                                                */
      __IOM uint32_t cr_irtx_out_inv : 1;       /*!< cr_irtx_out_inv                                                           */
      __IOM uint32_t cr_irtx_mod_en : 1;        /*!< cr_irtx_mod_en                                                            */
      __IOM uint32_t cr_irtx_swm_en : 1;        /*!< cr_irtx_swm_en                                                            */
      __IOM uint32_t cr_irtx_data_en : 1;       /*!< cr_irtx_data_en                                                           */
      __IOM uint32_t cr_irtx_logic0_hl_inv : 1; /*!< cr_irtx_logic0_hl_inv                                                     */
      __IOM uint32_t cr_irtx_logic1_hl_inv : 1; /*!< cr_irtx_logic1_hl_inv                                                     */
            uint32_t            : 1;
      __IOM uint32_t cr_irtx_head_en : 1;       /*!< cr_irtx_head_en                                                           */
      __IOM uint32_t cr_irtx_head_hl_inv : 1;   /*!< cr_irtx_head_hl_inv                                                       */
      __IOM uint32_t cr_irtx_tail_en : 1;       /*!< cr_irtx_tail_en                                                           */
      __IOM uint32_t cr_irtx_tail_hl_inv : 1;   /*!< cr_irtx_tail_hl_inv                                                       */
      __IOM uint32_t cr_irtx_data_num : 6;      /*!< cr_irtx_data_num                                                          */
            uint32_t            : 14;
    } bit;
  } irtx_config;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_int_sts.                                                             */
    
    struct {
      __IOM uint32_t irtx_end_int : 1;          /*!< irtx_end_int                                                              */
            uint32_t            : 7;
      __IOM uint32_t cr_irtx_end_mask : 1;      /*!< cr_irtx_end_mask                                                          */
            uint32_t            : 7;
      __IOM uint32_t cr_irtx_end_clr : 1;       /*!< cr_irtx_end_clr                                                           */
            uint32_t            : 7;
      __IOM uint32_t cr_irtx_end_en : 1;        /*!< cr_irtx_end_en                                                            */
            uint32_t            : 7;
    } bit;
  } irtx_int_sts;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_data_word0.                                                          */
    
    struct {
      __IOM uint32_t cr_irtx_data_word0 : 32;   /*!< cr_irtx_data_word0                                                        */
    } bit;
  } irtx_data_word0;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_data_word1.                                                          */
    
    struct {
      __IOM uint32_t cr_irtx_data_word1 : 32;   /*!< cr_irtx_data_word1                                                        */
    } bit;
  } irtx_data_word1;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_pulse_width.                                                         */
    
    struct {
      __IOM uint32_t cr_irtx_pw_unit : 12;      /*!< cr_irtx_pw_unit                                                           */
            uint32_t            : 4;
      __IOM uint32_t cr_irtx_mod_ph0_w : 8;     /*!< cr_irtx_mod_ph0_w                                                         */
      __IOM uint32_t cr_irtx_mod_ph1_w : 8;     /*!< cr_irtx_mod_ph1_w                                                         */
    } bit;
  } irtx_pulse_width;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_pw.                                                                  */
    
    struct {
      __IOM uint32_t cr_irtx_logic0_ph0_w : 4;  /*!< cr_irtx_logic0_ph0_w                                                      */
      __IOM uint32_t cr_irtx_logic0_ph1_w : 4;  /*!< cr_irtx_logic0_ph1_w                                                      */
      __IOM uint32_t cr_irtx_logic1_ph0_w : 4;  /*!< cr_irtx_logic1_ph0_w                                                      */
      __IOM uint32_t cr_irtx_logic1_ph1_w : 4;  /*!< cr_irtx_logic1_ph1_w                                                      */
      __IOM uint32_t cr_irtx_head_ph0_w : 4;    /*!< cr_irtx_head_ph0_w                                                        */
      __IOM uint32_t cr_irtx_head_ph1_w : 4;    /*!< cr_irtx_head_ph1_w                                                        */
      __IOM uint32_t cr_irtx_tail_ph0_w : 4;    /*!< cr_irtx_tail_ph0_w                                                        */
      __IOM uint32_t cr_irtx_tail_ph1_w : 4;    /*!< cr_irtx_tail_ph1_w                                                        */
    } bit;
  } irtx_pw;
  __IM  uint32_t  RESERVED[10];
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_swm_pw_0.                                                            */
    
    struct {
      __IOM uint32_t cr_irtx_swm_pw_0 : 32;     /*!< cr_irtx_swm_pw_0                                                          */
    } bit;
  } irtx_swm_pw_0;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_swm_pw_1.                                                            */
    
    struct {
      __IOM uint32_t cr_irtx_swm_pw_1 : 32;     /*!< cr_irtx_swm_pw_1                                                          */
    } bit;
  } irtx_swm_pw_1;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_swm_pw_2.                                                            */
    
    struct {
      __IOM uint32_t cr_irtx_swm_pw_2 : 32;     /*!< cr_irtx_swm_pw_2                                                          */
    } bit;
  } irtx_swm_pw_2;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_swm_pw_3.                                                            */
    
    struct {
      __IOM uint32_t cr_irtx_swm_pw_3 : 32;     /*!< cr_irtx_swm_pw_3                                                          */
    } bit;
  } irtx_swm_pw_3;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_swm_pw_4.                                                            */
    
    struct {
      __IOM uint32_t cr_irtx_swm_pw_4 : 32;     /*!< cr_irtx_swm_pw_4                                                          */
    } bit;
  } irtx_swm_pw_4;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_swm_pw_5.                                                            */
    
    struct {
      __IOM uint32_t cr_irtx_swm_pw_5 : 32;     /*!< cr_irtx_swm_pw_5                                                          */
    } bit;
  } irtx_swm_pw_5;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_swm_pw_6.                                                            */
    
    struct {
      __IOM uint32_t cr_irtx_swm_pw_6 : 32;     /*!< cr_irtx_swm_pw_6                                                          */
    } bit;
  } irtx_swm_pw_6;
  
  union {
    __IOM uint32_t reg;                         /*!< irtx_swm_pw_7.                                                            */
    
    struct {
      __IOM uint32_t cr_irtx_swm_pw_7 : 32;     /*!< cr_irtx_swm_pw_7                                                          */
    } bit;
  } irtx_swm_pw_7;
  __IM  uint32_t  RESERVED1[8];
  
  union {
    __IOM uint32_t reg;                         /*!< irrx_config.                                                              */
    
    struct {
      __IOM uint32_t cr_irrx_en : 1;            /*!< cr_irrx_en                                                                */
      __IOM uint32_t cr_irrx_in_inv : 1;        /*!< cr_irrx_in_inv                                                            */
      __IOM uint32_t cr_irrx_mode : 2;          /*!< cr_irrx_mode                                                              */
      __IOM uint32_t cr_irrx_deg_en : 1;        /*!< cr_irrx_deg_en                                                            */
            uint32_t            : 3;
      __IOM uint32_t cr_irrx_deg_cnt : 4;       /*!< cr_irrx_deg_cnt                                                           */
            uint32_t            : 20;
    } bit;
  } irrx_config;
  
  union {
    __IOM uint32_t reg;                         /*!< irrx_int_sts.                                                             */
    
    struct {
      __IOM uint32_t irrx_end_int : 1;          /*!< irrx_end_int                                                              */
            uint32_t            : 7;
      __IOM uint32_t cr_irrx_end_mask : 1;      /*!< cr_irrx_end_mask                                                          */
            uint32_t            : 7;
      __IOM uint32_t cr_irrx_end_clr : 1;       /*!< cr_irrx_end_clr                                                           */
            uint32_t            : 7;
      __IOM uint32_t cr_irrx_end_en : 1;        /*!< cr_irrx_end_en                                                            */
            uint32_t            : 7;
    } bit;
  } irrx_int_sts;
  
  union {
    __IOM uint32_t reg;                         /*!< irrx_pw_config.                                                           */
    
    struct {
      __IOM uint32_t cr_irrx_data_th : 16;      /*!< cr_irrx_data_th                                                           */
      __IOM uint32_t cr_irrx_end_th : 16;       /*!< cr_irrx_end_th                                                            */
    } bit;
  } irrx_pw_config;
  __IM  uint32_t  RESERVED2;
  
  union {
    __IOM uint32_t reg;                         /*!< irrx_data_count.                                                          */
    
    struct {
      __IOM uint32_t sts_irrx_data_cnt : 7;     /*!< sts_irrx_data_cnt                                                         */
            uint32_t            : 25;
    } bit;
  } irrx_data_count;
  
  union {
    __IOM uint32_t reg;                         /*!< irrx_data_word0.                                                          */
    
    struct {
      __IOM uint32_t sts_irrx_data_word0 : 32;  /*!< sts_irrx_data_word0                                                       */
    } bit;
  } irrx_data_word0;
  
  union {
    __IOM uint32_t reg;                         /*!< irrx_data_word1.                                                          */
    
    struct {
      __IOM uint32_t sts_irrx_data_word1 : 32;  /*!< sts_irrx_data_word1                                                       */
    } bit;
  } irrx_data_word1;
  __IM  uint32_t  RESERVED3[9];
  
  union {
    __IOM uint32_t reg;                         /*!< irrx_swm_fifo_config_0.                                                   */
    
    struct {
      __IOM uint32_t rx_fifo_clr : 1;           /*!< rx_fifo_clr                                                               */
            uint32_t            : 1;
      __IOM uint32_t rx_fifo_overflow : 1;      /*!< rx_fifo_overflow                                                          */
      __IOM uint32_t rx_fifo_underflow : 1;     /*!< rx_fifo_underflow                                                         */
      __IOM uint32_t rx_fifo_cnt : 7;           /*!< rx_fifo_cnt                                                               */
            uint32_t            : 21;
    } bit;
  } irrx_swm_fifo_config_0;
  
  union {
    __IOM uint32_t reg;                         /*!< irrx_swm_fifo_rdata.                                                      */
    
    struct {
      __IOM uint32_t rx_fifo_rdata : 16;        /*!< rx_fifo_rdata                                                             */
            uint32_t            : 16;
    } bit;
  } irrx_swm_fifo_rdata;
} ir_Type;                                      /*!< Size = 200 (0xc8)                                                         */



/* =========================================================================================================================== */
/* ================                                            cks                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief cks. (cks)
  */

typedef struct {                                /*!< cks Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< cks_config.                                                               */
    
    struct {
      __IOM uint32_t cr_cks_clr : 1;            /*!< cr_cks_clr                                                                */
      __IOM uint32_t cr_cks_byte_swap : 1;      /*!< cr_cks_byte_swap                                                          */
            uint32_t            : 30;
    } bit;
  } cks_config;
  
  union {
    __IOM uint32_t reg;                         /*!< data_in.                                                                  */
    
    struct {
      __IOM uint32_t data_in    : 8;            /*!< data_in                                                                   */
            uint32_t            : 24;
    } bit;
  } data_in;
  
  union {
    __IOM uint32_t reg;                         /*!< cks_out.                                                                  */
    
    struct {
      __IOM uint32_t cks_out    : 16;           /*!< cks_out                                                                   */
            uint32_t            : 16;
    } bit;
  } cks_out;
} cks_Type;                                     /*!< Size = 12 (0xc)                                                           */



/* =========================================================================================================================== */
/* ================                                          sf_ctrl                                          ================ */
/* =========================================================================================================================== */


/**
  * @brief sf_ctrl. (sf_ctrl)
  */

typedef struct {                                /*!< sf_ctrl Structure                                                         */
  
  union {
    __IOM uint32_t reg;                         /*!< sf_ctrl_0.                                                                */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t sf_clk_sf_rx_inv_sel : 1;  /*!< sf_clk_sf_rx_inv_sel                                                      */
      __IOM uint32_t sf_clk_out_gate_en : 1;    /*!< sf_clk_out_gate_en                                                        */
      __IOM uint32_t sf_clk_out_inv_sel : 1;    /*!< sf_clk_out_inv_sel                                                        */
      __IOM uint32_t sf_clk_sahb_sram_sel : 1;  /*!< sf_clk_sahb_sram_sel                                                      */
            uint32_t            : 2;
      __IOM uint32_t sf_if_read_dly_n : 3;      /*!< sf_if_read_dly_n                                                          */
      __IOM uint32_t sf_if_read_dly_en : 1;     /*!< sf_if_read_dly_en                                                         */
            uint32_t            : 4;
      __IOM uint32_t sf_if_int  : 1;            /*!< sf_if_int                                                                 */
      __IOM uint32_t sf_if_int_clr : 1;         /*!< sf_if_int_clr                                                             */
      __IOM uint32_t sf_if_int_set : 1;         /*!< sf_if_int_set                                                             */
      __IOM uint32_t sf_aes_dly_mode : 1;       /*!< sf_aes_dly_mode                                                           */
      __IOM uint32_t sf_aes_dout_endian : 1;    /*!< sf_aes_dout_endian                                                        */
      __IOM uint32_t sf_aes_ctr_plus_en : 1;    /*!< sf_aes_ctr_plus_en                                                        */
      __IOM uint32_t sf_aes_key_endian : 1;     /*!< sf_aes_key_endian                                                         */
      __IOM uint32_t sf_aes_iv_endian : 1;      /*!< sf_aes_iv_endian                                                          */
      __IOM uint32_t sf_id      : 8;            /*!< sf_id                                                                     */
    } bit;
  } sf_ctrl_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_ctrl_1.                                                                */
    
    struct {
      __IOM uint32_t sf_if_sr_pat_mask : 8;     /*!< sf_if_sr_pat_mask                                                         */
      __IOM uint32_t sf_if_sr_pat : 8;          /*!< sf_if_sr_pat                                                              */
      __IOM uint32_t sf_if_sr_int : 1;          /*!< sf_if_sr_int                                                              */
      __IOM uint32_t sf_if_sr_int_en : 1;       /*!< sf_if_sr_int_en                                                           */
      __IOM uint32_t sf_if_sr_int_set : 1;      /*!< sf_if_sr_int_set                                                          */
            uint32_t            : 1;
      __IOM uint32_t sf_if_0_ack_lat : 3;       /*!< sf_if_0_ack_lat                                                           */
            uint32_t            : 1;
      __IOM uint32_t sf_if_reg_hold : 1;        /*!< sf_if_reg_hold                                                            */
      __IOM uint32_t sf_if_reg_wp : 1;          /*!< sf_if_reg_wp                                                              */
      __IOM uint32_t sf_ahb2sif_stopped : 1;    /*!< sf_ahb2sif_stopped                                                        */
      __IOM uint32_t sf_ahb2sif_stop : 1;       /*!< sf_ahb2sif_stop                                                           */
      __IOM uint32_t sf_if_fn_sel : 1;          /*!< sf_if_fn_sel                                                              */
      __IOM uint32_t sf_if_en   : 1;            /*!< sf_if_en                                                                  */
      __IOM uint32_t sf_ahb2sif_en : 1;         /*!< sf_ahb2sif_en                                                             */
      __IOM uint32_t sf_ahb2sram_en : 1;        /*!< sf_ahb2sram_en                                                            */
    } bit;
  } sf_ctrl_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_sahb_0.                                                             */
    
    struct {
      __IOM uint32_t sf_if_busy : 1;            /*!< sf_if_busy                                                                */
      __IOM uint32_t sf_if_0_trig : 1;          /*!< sf_if_0_trig                                                              */
      __IOM uint32_t sf_if_0_dat_byte : 10;     /*!< sf_if_0_dat_byte                                                          */
      __IOM uint32_t sf_if_0_dmy_byte : 5;      /*!< sf_if_0_dmy_byte                                                          */
      __IOM uint32_t sf_if_0_adr_byte : 3;      /*!< sf_if_0_adr_byte                                                          */
      __IOM uint32_t sf_if_0_cmd_byte : 3;      /*!< sf_if_0_cmd_byte                                                          */
      __IOM uint32_t sf_if_0_dat_rw : 1;        /*!< sf_if_0_dat_rw                                                            */
      __IOM uint32_t sf_if_0_dat_en : 1;        /*!< sf_if_0_dat_en                                                            */
      __IOM uint32_t sf_if_0_dmy_en : 1;        /*!< sf_if_0_dmy_en                                                            */
      __IOM uint32_t sf_if_0_adr_en : 1;        /*!< sf_if_0_adr_en                                                            */
      __IOM uint32_t sf_if_0_cmd_en : 1;        /*!< sf_if_0_cmd_en                                                            */
      __IOM uint32_t sf_if_0_spi_mode : 3;      /*!< sf_if_0_spi_mode                                                          */
      __IOM uint32_t sf_if_0_qpi_mode_en : 1;   /*!< sf_if_0_qpi_mode_en                                                       */
    } bit;
  } sf_if_sahb_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_sahb_1.                                                             */
    
    struct {
      __IOM uint32_t sf_if_0_cmd_buf_0 : 32;    /*!< sf_if_0_cmd_buf_0                                                         */
    } bit;
  } sf_if_sahb_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_sahb_2.                                                             */
    
    struct {
      __IOM uint32_t sf_if_0_cmd_buf_1 : 32;    /*!< sf_if_0_cmd_buf_1                                                         */
    } bit;
  } sf_if_sahb_2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_iahb_0.                                                             */
    
    struct {
            uint32_t            : 12;
      __IOM uint32_t sf_if_1_dmy_byte : 5;      /*!< sf_if_1_dmy_byte                                                          */
      __IOM uint32_t sf_if_1_adr_byte : 3;      /*!< sf_if_1_adr_byte                                                          */
      __IOM uint32_t sf_if_1_cmd_byte : 3;      /*!< sf_if_1_cmd_byte                                                          */
      __IOM uint32_t sf_if_1_dat_rw : 1;        /*!< sf_if_1_dat_rw                                                            */
      __IOM uint32_t sf_if_1_dat_en : 1;        /*!< sf_if_1_dat_en                                                            */
      __IOM uint32_t sf_if_1_dmy_en : 1;        /*!< sf_if_1_dmy_en                                                            */
      __IOM uint32_t sf_if_1_adr_en : 1;        /*!< sf_if_1_adr_en                                                            */
      __IOM uint32_t sf_if_1_cmd_en : 1;        /*!< sf_if_1_cmd_en                                                            */
      __IOM uint32_t sf_if_1_spi_mode : 3;      /*!< sf_if_1_spi_mode                                                          */
      __IOM uint32_t sf_if_1_qpi_mode_en : 1;   /*!< sf_if_1_qpi_mode_en                                                       */
    } bit;
  } sf_if_iahb_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_iahb_1.                                                             */
    
    struct {
      __IOM uint32_t sf_if_1_cmd_buf_0 : 32;    /*!< sf_if_1_cmd_buf_0                                                         */
    } bit;
  } sf_if_iahb_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_iahb_2.                                                             */
    
    struct {
      __IOM uint32_t sf_if_1_cmd_buf_1 : 32;    /*!< sf_if_1_cmd_buf_1                                                         */
    } bit;
  } sf_if_iahb_2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_status_0.                                                           */
    
    struct {
      __IOM uint32_t sf_if_status_0 : 32;       /*!< sf_if_status_0                                                            */
    } bit;
  } sf_if_status_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_status_1.                                                           */
    
    struct {
      __IOM uint32_t sf_if_status_1 : 32;       /*!< sf_if_status_1                                                            */
    } bit;
  } sf_if_status_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes.                                                                   */
    
    struct {
      __IOM uint32_t sf_aes_en  : 1;            /*!< sf_aes_en                                                                 */
      __IOM uint32_t sf_aes_mode : 2;           /*!< sf_aes_mode                                                               */
      __IOM uint32_t sf_aes_pref_trig : 1;      /*!< sf_aes_pref_trig                                                          */
      __IOM uint32_t sf_aes_pref_busy : 1;      /*!< sf_aes_pref_busy                                                          */
      __IOM uint32_t sf_aes_status : 27;        /*!< sf_aes_status                                                             */
    } bit;
  } sf_aes;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_ahb2sif_status.                                                        */
    
    struct {
      __IOM uint32_t sf_ahb2sif_status : 32;    /*!< sf_ahb2sif_status                                                         */
    } bit;
  } sf_ahb2sif_status;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_io_dly_0.                                                           */
    
    struct {
      __IOM uint32_t sf_cs_dly_sel : 2;         /*!< sf_cs_dly_sel                                                             */
            uint32_t            : 6;
      __IOM uint32_t sf_clk_out_dly_sel : 2;    /*!< sf_clk_out_dly_sel                                                        */
            uint32_t            : 16;
      __IOM uint32_t sf_dqs_oe_dly_sel : 2;     /*!< sf_dqs_oe_dly_sel                                                         */
      __IOM uint32_t sf_dqs_di_dly_sel : 2;     /*!< sf_dqs_di_dly_sel                                                         */
      __IOM uint32_t sf_dqs_do_dly_sel : 2;     /*!< sf_dqs_do_dly_sel                                                         */
    } bit;
  } sf_if_io_dly_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_io_dly_1.                                                           */
    
    struct {
      __IOM uint32_t sf_io_0_oe_dly_sel : 2;    /*!< sf_io_0_oe_dly_sel                                                        */
            uint32_t            : 6;
      __IOM uint32_t sf_io_0_di_dly_sel : 2;    /*!< sf_io_0_di_dly_sel                                                        */
            uint32_t            : 6;
      __IOM uint32_t sf_io_0_do_dly_sel : 2;    /*!< sf_io_0_do_dly_sel                                                        */
            uint32_t            : 14;
    } bit;
  } sf_if_io_dly_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_io_dly_2.                                                           */
    
    struct {
      __IOM uint32_t sf_io_1_oe_dly_sel : 2;    /*!< sf_io_1_oe_dly_sel                                                        */
            uint32_t            : 6;
      __IOM uint32_t sf_io_1_di_dly_sel : 2;    /*!< sf_io_1_di_dly_sel                                                        */
            uint32_t            : 6;
      __IOM uint32_t sf_io_1_do_dly_sel : 2;    /*!< sf_io_1_do_dly_sel                                                        */
            uint32_t            : 14;
    } bit;
  } sf_if_io_dly_2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_io_dly_3.                                                           */
    
    struct {
      __IOM uint32_t sf_io_2_oe_dly_sel : 2;    /*!< sf_io_2_oe_dly_sel                                                        */
            uint32_t            : 6;
      __IOM uint32_t sf_io_2_di_dly_sel : 2;    /*!< sf_io_2_di_dly_sel                                                        */
            uint32_t            : 6;
      __IOM uint32_t sf_io_2_do_dly_sel : 2;    /*!< sf_io_2_do_dly_sel                                                        */
            uint32_t            : 14;
    } bit;
  } sf_if_io_dly_3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_io_dly_4.                                                           */
    
    struct {
      __IOM uint32_t sf_io_3_oe_dly_sel : 2;    /*!< sf_io_3_oe_dly_sel                                                        */
            uint32_t            : 6;
      __IOM uint32_t sf_io_3_di_dly_sel : 2;    /*!< sf_io_3_di_dly_sel                                                        */
            uint32_t            : 6;
      __IOM uint32_t sf_io_3_do_dly_sel : 2;    /*!< sf_io_3_do_dly_sel                                                        */
            uint32_t            : 14;
    } bit;
  } sf_if_io_dly_4;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_reserved.                                                              */
    
    struct {
      __IOM uint32_t sf_reserved : 32;          /*!< sf_reserved                                                               */
    } bit;
  } sf_reserved;
  
  union {
    __IOM uint32_t reg;                         /*!< sf2_if_io_dly_0.                                                          */
    
    struct {
      __IOM uint32_t sf2_cs_dly_sel : 2;        /*!< sf2_cs_dly_sel                                                            */
            uint32_t            : 6;
      __IOM uint32_t sf2_clk_out_dly_sel : 2;   /*!< sf2_clk_out_dly_sel                                                       */
            uint32_t            : 16;
      __IOM uint32_t sf2_dqs_oe_dly_sel : 2;    /*!< sf2_dqs_oe_dly_sel                                                        */
      __IOM uint32_t sf2_dqs_di_dly_sel : 2;    /*!< sf2_dqs_di_dly_sel                                                        */
      __IOM uint32_t sf2_dqs_do_dly_sel : 2;    /*!< sf2_dqs_do_dly_sel                                                        */
    } bit;
  } sf2_if_io_dly_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf2_if_io_dly_1.                                                          */
    
    struct {
      __IOM uint32_t sf2_io_0_oe_dly_sel : 2;   /*!< sf2_io_0_oe_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf2_io_0_di_dly_sel : 2;   /*!< sf2_io_0_di_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf2_io_0_do_dly_sel : 2;   /*!< sf2_io_0_do_dly_sel                                                       */
            uint32_t            : 14;
    } bit;
  } sf2_if_io_dly_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf2_if_io_dly_2.                                                          */
    
    struct {
      __IOM uint32_t sf2_io_1_oe_dly_sel : 2;   /*!< sf2_io_1_oe_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf2_io_1_di_dly_sel : 2;   /*!< sf2_io_1_di_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf2_io_1_do_dly_sel : 2;   /*!< sf2_io_1_do_dly_sel                                                       */
            uint32_t            : 14;
    } bit;
  } sf2_if_io_dly_2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf2_if_io_dly_3.                                                          */
    
    struct {
      __IOM uint32_t sf2_io_2_oe_dly_sel : 2;   /*!< sf2_io_2_oe_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf2_io_2_di_dly_sel : 2;   /*!< sf2_io_2_di_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf2_io_2_do_dly_sel : 2;   /*!< sf2_io_2_do_dly_sel                                                       */
            uint32_t            : 14;
    } bit;
  } sf2_if_io_dly_3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf2_if_io_dly_4.                                                          */
    
    struct {
      __IOM uint32_t sf2_io_3_oe_dly_sel : 2;   /*!< sf2_io_3_oe_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf2_io_3_di_dly_sel : 2;   /*!< sf2_io_3_di_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf2_io_3_do_dly_sel : 2;   /*!< sf2_io_3_do_dly_sel                                                       */
            uint32_t            : 14;
    } bit;
  } sf2_if_io_dly_4;
  
  union {
    __IOM uint32_t reg;                         /*!< sf3_if_io_dly_0.                                                          */
    
    struct {
      __IOM uint32_t sf3_cs_dly_sel : 2;        /*!< sf3_cs_dly_sel                                                            */
            uint32_t            : 6;
      __IOM uint32_t sf3_clk_out_dly_sel : 2;   /*!< sf3_clk_out_dly_sel                                                       */
            uint32_t            : 16;
      __IOM uint32_t sf3_dqs_oe_dly_sel : 2;    /*!< sf3_dqs_oe_dly_sel                                                        */
      __IOM uint32_t sf3_dqs_di_dly_sel : 2;    /*!< sf3_dqs_di_dly_sel                                                        */
      __IOM uint32_t sf3_dqs_do_dly_sel : 2;    /*!< sf3_dqs_do_dly_sel                                                        */
    } bit;
  } sf3_if_io_dly_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf3_if_io_dly_1.                                                          */
    
    struct {
      __IOM uint32_t sf3_io_0_oe_dly_sel : 2;   /*!< sf3_io_0_oe_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf3_io_0_di_dly_sel : 2;   /*!< sf3_io_0_di_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf3_io_0_do_dly_sel : 2;   /*!< sf3_io_0_do_dly_sel                                                       */
            uint32_t            : 14;
    } bit;
  } sf3_if_io_dly_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf3_if_io_dly_2.                                                          */
    
    struct {
      __IOM uint32_t sf3_io_1_oe_dly_sel : 2;   /*!< sf3_io_1_oe_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf3_io_1_di_dly_sel : 2;   /*!< sf3_io_1_di_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf3_io_1_do_dly_sel : 2;   /*!< sf3_io_1_do_dly_sel                                                       */
            uint32_t            : 14;
    } bit;
  } sf3_if_io_dly_2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf3_if_io_dly_3.                                                          */
    
    struct {
      __IOM uint32_t sf3_io_2_oe_dly_sel : 2;   /*!< sf3_io_2_oe_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf3_io_2_di_dly_sel : 2;   /*!< sf3_io_2_di_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf3_io_2_do_dly_sel : 2;   /*!< sf3_io_2_do_dly_sel                                                       */
            uint32_t            : 14;
    } bit;
  } sf3_if_io_dly_3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf3_if_io_dly_4.                                                          */
    
    struct {
      __IOM uint32_t sf3_io_3_oe_dly_sel : 2;   /*!< sf3_io_3_oe_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf3_io_3_di_dly_sel : 2;   /*!< sf3_io_3_di_dly_sel                                                       */
            uint32_t            : 6;
      __IOM uint32_t sf3_io_3_do_dly_sel : 2;   /*!< sf3_io_3_do_dly_sel                                                       */
            uint32_t            : 14;
    } bit;
  } sf3_if_io_dly_4;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_ctrl_2.                                                                */
    
    struct {
      __IOM uint32_t sf_if_pad_sel : 2;         /*!< sf_if_pad_sel                                                             */
            uint32_t            : 1;
      __IOM uint32_t sf_if_pad_sel_lock : 1;    /*!< sf_if_pad_sel_lock                                                        */
      __IOM uint32_t sf_if_dtr_en : 1;          /*!< sf_if_dtr_en                                                              */
      __IOM uint32_t sf_if_dqs_en : 1;          /*!< sf_if_dqs_en                                                              */
            uint32_t            : 26;
    } bit;
  } sf_ctrl_2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_ctrl_3.                                                                */
    
    struct {
      __IOM uint32_t sf_cmds_wrap_len : 4;      /*!< sf_cmds_wrap_len                                                          */
      __IOM uint32_t sf_cmds_en : 1;            /*!< sf_cmds_en                                                                */
      __IOM uint32_t sf_cmds_bt_dly : 3;        /*!< sf_cmds_bt_dly                                                            */
      __IOM uint32_t sf_cmds_bt_en : 1;         /*!< sf_cmds_bt_en                                                             */
      __IOM uint32_t sf_cmds_wrap_q_ini : 1;    /*!< sf_cmds_wrap_q_ini                                                        */
      __IOM uint32_t sf_cmds_wrap_mode : 1;     /*!< sf_cmds_wrap_mode                                                         */
            uint32_t            : 18;
      __IOM uint32_t sf_if_1_ack_lat : 3;       /*!< sf_if_1_ack_lat                                                           */
    } bit;
  } sf_ctrl_3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_iahb_3.                                                             */
    
    struct {
            uint32_t            : 12;
      __IOM uint32_t sf_if_2_dmy_byte : 5;      /*!< sf_if_2_dmy_byte                                                          */
      __IOM uint32_t sf_if_2_adr_byte : 3;      /*!< sf_if_2_adr_byte                                                          */
      __IOM uint32_t sf_if_2_cmd_byte : 3;      /*!< sf_if_2_cmd_byte                                                          */
      __IOM uint32_t sf_if_2_dat_rw : 1;        /*!< sf_if_2_dat_rw                                                            */
      __IOM uint32_t sf_if_2_dat_en : 1;        /*!< sf_if_2_dat_en                                                            */
      __IOM uint32_t sf_if_2_dmy_en : 1;        /*!< sf_if_2_dmy_en                                                            */
      __IOM uint32_t sf_if_2_adr_en : 1;        /*!< sf_if_2_adr_en                                                            */
      __IOM uint32_t sf_if_2_cmd_en : 1;        /*!< sf_if_2_cmd_en                                                            */
      __IOM uint32_t sf_if_2_spi_mode : 3;      /*!< sf_if_2_spi_mode                                                          */
      __IOM uint32_t sf_if_2_qpi_mode_en : 1;   /*!< sf_if_2_qpi_mode_en                                                       */
    } bit;
  } sf_if_iahb_3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_iahb_4.                                                             */
    
    struct {
      __IOM uint32_t sf_if_2_cmd_buf_0 : 32;    /*!< sf_if_2_cmd_buf_0                                                         */
    } bit;
  } sf_if_iahb_4;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_iahb_5.                                                             */
    
    struct {
      __IOM uint32_t sf_if_2_cmd_buf_1 : 32;    /*!< sf_if_2_cmd_buf_1                                                         */
    } bit;
  } sf_if_iahb_5;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_iahb_6.                                                             */
    
    struct {
            uint32_t            : 20;
      __IOM uint32_t sf_if_3_cmd_byte : 3;      /*!< sf_if_3_cmd_byte                                                          */
            uint32_t            : 5;
      __IOM uint32_t sf_if_3_spi_mode : 3;      /*!< sf_if_3_spi_mode                                                          */
      __IOM uint32_t sf_if_3_qpi_mode_en : 1;   /*!< sf_if_3_qpi_mode_en                                                       */
    } bit;
  } sf_if_iahb_6;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_if_iahb_7.                                                             */
    
    struct {
      __IOM uint32_t sf_if_3_cmd_buf_0 : 32;    /*!< sf_if_3_cmd_buf_0                                                         */
    } bit;
  } sf_if_iahb_7;
  __IM  uint32_t  RESERVED[29];
  
  union {
    __IOM uint32_t reg;                         /*!< sf_ctrl_prot_en_rd.                                                       */
    
    struct {
      __IOM uint32_t sf_ctrl_prot_en_rd : 1;    /*!< sf_ctrl_prot_en_rd                                                        */
      __IOM uint32_t sf_ctrl_id0_en_rd : 1;     /*!< sf_ctrl_id0_en_rd                                                         */
      __IOM uint32_t sf_ctrl_id1_en_rd : 1;     /*!< sf_ctrl_id1_en_rd                                                         */
            uint32_t            : 27;
      __IOM uint32_t sf_if_0_trig_wr_lock : 1;  /*!< sf_if_0_trig_wr_lock                                                      */
      __IOM uint32_t sf_dbg_dis : 1;            /*!< sf_dbg_dis                                                                */
    } bit;
  } sf_ctrl_prot_en_rd;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_ctrl_prot_en.                                                          */
    
    struct {
      __IOM uint32_t sf_ctrl_prot_en : 1;       /*!< sf_ctrl_prot_en                                                           */
      __IOM uint32_t sf_ctrl_id0_en : 1;        /*!< sf_ctrl_id0_en                                                            */
      __IOM uint32_t sf_ctrl_id1_en : 1;        /*!< sf_ctrl_id1_en                                                            */
            uint32_t            : 29;
    } bit;
  } sf_ctrl_prot_en;
  __IM  uint32_t  RESERVED1[62];
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r0_0.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r0_0 : 32;      /*!< sf_aes_key_r0_0                                                           */
    } bit;
  } sf_aes_key_r0_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r0_1.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r0_1 : 32;      /*!< sf_aes_key_r0_1                                                           */
    } bit;
  } sf_aes_key_r0_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r0_2.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r0_2 : 32;      /*!< sf_aes_key_r0_2                                                           */
    } bit;
  } sf_aes_key_r0_2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r0_3.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r0_3 : 32;      /*!< sf_aes_key_r0_3                                                           */
    } bit;
  } sf_aes_key_r0_3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r0_4.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r0_4 : 32;      /*!< sf_aes_key_r0_4                                                           */
    } bit;
  } sf_aes_key_r0_4;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r0_5.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r0_5 : 32;      /*!< sf_aes_key_r0_5                                                           */
    } bit;
  } sf_aes_key_r0_5;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r0_6.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r0_6 : 32;      /*!< sf_aes_key_r0_6                                                           */
    } bit;
  } sf_aes_key_r0_6;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r0_7.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r0_7 : 32;      /*!< sf_aes_key_r0_7                                                           */
    } bit;
  } sf_aes_key_r0_7;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r0_w0.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r0_w0 : 32;      /*!< sf_aes_iv_r0_w0                                                           */
    } bit;
  } sf_aes_iv_r0_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r0_w1.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r0_w1 : 32;      /*!< sf_aes_iv_r0_w1                                                           */
    } bit;
  } sf_aes_iv_r0_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r0_w2.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r0_w2 : 32;      /*!< sf_aes_iv_r0_w2                                                           */
    } bit;
  } sf_aes_iv_r0_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r0_w3.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r0_w3 : 32;      /*!< sf_aes_iv_r0_w3                                                           */
    } bit;
  } sf_aes_iv_r0_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_cfg_r0.                                                            */
    
    struct {
      __IOM uint32_t sf_aes_region_r0_end : 14; /*!< sf_aes_region_r0_end                                                      */
      __IOM uint32_t sf_aes_region_r0_start : 14;/*!< sf_aes_region_r0_start                                                   */
            uint32_t            : 1;
      __IOM uint32_t sf_aes_region_r0_hw_key_en : 1;/*!< sf_aes_region_r0_hw_key_en                                            */
      __IOM uint32_t sf_aes_region_r0_en : 1;   /*!< sf_aes_region_r0_en                                                       */
      __IOM uint32_t sf_aes_region_r0_lock : 1; /*!< sf_aes_region_r0_lock                                                     */
    } bit;
  } sf_aes_cfg_r0;
  __IM  uint32_t  RESERVED2[51];
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r1_0.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r1_0 : 32;      /*!< sf_aes_key_r1_0                                                           */
    } bit;
  } sf_aes_key_r1_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r1_1.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r1_1 : 32;      /*!< sf_aes_key_r1_1                                                           */
    } bit;
  } sf_aes_key_r1_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r1_2.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r1_2 : 32;      /*!< sf_aes_key_r1_2                                                           */
    } bit;
  } sf_aes_key_r1_2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r1_3.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r1_3 : 32;      /*!< sf_aes_key_r1_3                                                           */
    } bit;
  } sf_aes_key_r1_3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r1_4.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r1_4 : 32;      /*!< sf_aes_key_r1_4                                                           */
    } bit;
  } sf_aes_key_r1_4;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r1_5.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r1_5 : 32;      /*!< sf_aes_key_r1_5                                                           */
    } bit;
  } sf_aes_key_r1_5;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r1_6.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r1_6 : 32;      /*!< sf_aes_key_r1_6                                                           */
    } bit;
  } sf_aes_key_r1_6;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r1_7.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r1_7 : 32;      /*!< sf_aes_key_r1_7                                                           */
    } bit;
  } sf_aes_key_r1_7;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r1_w0.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r1_w0 : 32;      /*!< sf_aes_iv_r1_w0                                                           */
    } bit;
  } sf_aes_iv_r1_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r1_w1.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r1_w1 : 32;      /*!< sf_aes_iv_r1_w1                                                           */
    } bit;
  } sf_aes_iv_r1_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r1_w2.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r1_w2 : 32;      /*!< sf_aes_iv_r1_w2                                                           */
    } bit;
  } sf_aes_iv_r1_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r1_w3.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r1_w3 : 32;      /*!< sf_aes_iv_r1_w3                                                           */
    } bit;
  } sf_aes_iv_r1_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_r1.                                                                */
    
    struct {
      __IOM uint32_t sf_aes_r1_end : 14;        /*!< sf_aes_r1_end                                                             */
      __IOM uint32_t sf_aes_r1_start : 14;      /*!< sf_aes_r1_start                                                           */
            uint32_t            : 1;
      __IOM uint32_t sf_aes_r1_hw_key_en : 1;   /*!< sf_aes_r1_hw_key_en                                                       */
      __IOM uint32_t sf_aes_r1_en : 1;          /*!< sf_aes_r1_en                                                              */
      __IOM uint32_t sf_aes_r1_lock : 1;        /*!< sf_aes_r1_lock                                                            */
    } bit;
  } sf_aes_r1;
  __IM  uint32_t  RESERVED3[51];
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r2_0.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r2_0 : 32;      /*!< sf_aes_key_r2_0                                                           */
    } bit;
  } sf_aes_key_r2_0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r2_1.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r2_1 : 32;      /*!< sf_aes_key_r2_1                                                           */
    } bit;
  } sf_aes_key_r2_1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r2_2.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r2_2 : 32;      /*!< sf_aes_key_r2_2                                                           */
    } bit;
  } sf_aes_key_r2_2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r2_3.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r2_3 : 32;      /*!< sf_aes_key_r2_3                                                           */
    } bit;
  } sf_aes_key_r2_3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r2_4.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r2_4 : 32;      /*!< sf_aes_key_r2_4                                                           */
    } bit;
  } sf_aes_key_r2_4;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r2_5.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r2_5 : 32;      /*!< sf_aes_key_r2_5                                                           */
    } bit;
  } sf_aes_key_r2_5;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r2_6.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r2_6 : 32;      /*!< sf_aes_key_r2_6                                                           */
    } bit;
  } sf_aes_key_r2_6;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_key_r2_7.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_key_r2_7 : 32;      /*!< sf_aes_key_r2_7                                                           */
    } bit;
  } sf_aes_key_r2_7;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r2_w0.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r2_w0 : 32;      /*!< sf_aes_iv_r2_w0                                                           */
    } bit;
  } sf_aes_iv_r2_w0;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r2_w1.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r2_w1 : 32;      /*!< sf_aes_iv_r2_w1                                                           */
    } bit;
  } sf_aes_iv_r2_w1;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r2_w2.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r2_w2 : 32;      /*!< sf_aes_iv_r2_w2                                                           */
    } bit;
  } sf_aes_iv_r2_w2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_iv_r2_w3.                                                          */
    
    struct {
      __IOM uint32_t sf_aes_iv_r2_w3 : 32;      /*!< sf_aes_iv_r2_w3                                                           */
    } bit;
  } sf_aes_iv_r2_w3;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_aes_r2.                                                                */
    
    struct {
      __IOM uint32_t sf_aes_r2_end : 14;        /*!< sf_aes_r2_end                                                             */
      __IOM uint32_t sf_aes_r2_start : 14;      /*!< sf_aes_r2_start                                                           */
            uint32_t            : 1;
      __IOM uint32_t sf_aes_r2_hw_key_en : 1;   /*!< sf_aes_r2_hw_key_en                                                       */
      __IOM uint32_t sf_aes_r2_en : 1;          /*!< sf_aes_r2_en                                                              */
      __IOM uint32_t sf_aes_r2_lock : 1;        /*!< sf_aes_r2_lock                                                            */
    } bit;
  } sf_aes_r2;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_id0_offset.                                                            */
    
    struct {
      __IOM uint32_t sf_id0_offset : 24;        /*!< sf_id0_offset                                                             */
            uint32_t            : 8;
    } bit;
  } sf_id0_offset;
  
  union {
    __IOM uint32_t reg;                         /*!< sf_id1_offset.                                                            */
    
    struct {
      __IOM uint32_t sf_id1_offset : 24;        /*!< sf_id1_offset                                                             */
            uint32_t            : 8;
    } bit;
  } sf_id1_offset;
} sf_ctrl_Type;                                 /*!< Size = 1084 (0x43c)                                                       */



/* =========================================================================================================================== */
/* ================                                            dma                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief dma. (dma)
  */

typedef struct {                                /*!< dma Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_IntStatus.                                                            */
    
    struct {
      __IOM uint32_t IntStatus  : 8;            /*!< IntStatus                                                                 */
            uint32_t            : 24;
    } bit;
  } DMA_IntStatus;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_IntTCStatus.                                                          */
    
    struct {
      __IOM uint32_t IntTCStatus : 8;           /*!< IntTCStatus                                                               */
            uint32_t            : 24;
    } bit;
  } DMA_IntTCStatus;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_IntTCClear.                                                           */
    
    struct {
      __IOM uint32_t IntTCClear : 8;            /*!< IntTCClear                                                                */
            uint32_t            : 24;
    } bit;
  } DMA_IntTCClear;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_IntErrorStatus.                                                       */
    
    struct {
      __IOM uint32_t IntErrorStatus : 8;        /*!< IntErrorStatus                                                            */
            uint32_t            : 24;
    } bit;
  } DMA_IntErrorStatus;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_IntErrClr.                                                            */
    
    struct {
      __IOM uint32_t IntErrClr  : 8;            /*!< IntErrClr                                                                 */
            uint32_t            : 24;
    } bit;
  } DMA_IntErrClr;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_RawIntTCStatus.                                                       */
    
    struct {
      __IOM uint32_t RawIntTCStatus : 8;        /*!< RawIntTCStatus                                                            */
            uint32_t            : 24;
    } bit;
  } DMA_RawIntTCStatus;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_RawIntErrorStatus.                                                    */
    
    struct {
      __IOM uint32_t RawIntErrorStatus : 8;     /*!< RawIntErrorStatus                                                         */
            uint32_t            : 24;
    } bit;
  } DMA_RawIntErrorStatus;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_EnbldChns.                                                            */
    
    struct {
      __IOM uint32_t EnabledChannels : 8;       /*!< EnabledChannels                                                           */
            uint32_t            : 24;
    } bit;
  } DMA_EnbldChns;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_SoftBReq.                                                             */
    
    struct {
      __IOM uint32_t SoftBReq   : 32;           /*!< SoftBReq                                                                  */
    } bit;
  } DMA_SoftBReq;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_SoftSReq.                                                             */
    
    struct {
      __IOM uint32_t SoftSReq   : 32;           /*!< SoftSReq                                                                  */
    } bit;
  } DMA_SoftSReq;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_SoftLBReq.                                                            */
    
    struct {
      __IOM uint32_t SoftLBReq  : 32;           /*!< SoftLBReq                                                                 */
    } bit;
  } DMA_SoftLBReq;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_SoftLSReq.                                                            */
    
    struct {
      __IOM uint32_t SoftLSReq  : 32;           /*!< SoftLSReq                                                                 */
    } bit;
  } DMA_SoftLSReq;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_Top_Config.                                                           */
    
    struct {
      __IOM uint32_t E          : 1;            /*!< E                                                                         */
      __IOM uint32_t M          : 1;            /*!< M                                                                         */
            uint32_t            : 30;
    } bit;
  } DMA_Top_Config;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_Sync.                                                                 */
    
    struct {
      __IOM uint32_t DMA_Sync   : 32;           /*!< DMA_Sync                                                                  */
    } bit;
  } DMA_Sync;
  __IM  uint32_t  RESERVED[50];
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C0SrcAddr.                                                            */
    
    struct {
      __IOM uint32_t SrcAddr    : 32;           /*!< SrcAddr                                                                   */
    } bit;
  } DMA_C0SrcAddr;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C0DstAddr.                                                            */
    
    struct {
      __IOM uint32_t DstAddr    : 32;           /*!< DstAddr                                                                   */
    } bit;
  } DMA_C0DstAddr;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C0LLI.                                                                */
    
    struct {
      __IOM uint32_t LLI        : 32;           /*!< LLI                                                                       */
    } bit;
  } DMA_C0LLI;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C0Control.                                                            */
    
    struct {
      __IOM uint32_t TransferSize : 12;         /*!< TransferSize                                                              */
      __IOM uint32_t SBSize     : 3;            /*!< SBSize                                                                    */
      __IOM uint32_t DBSize     : 3;            /*!< DBSize                                                                    */
      __IOM uint32_t SWidth     : 3;            /*!< SWidth                                                                    */
      __IOM uint32_t DWidth     : 3;            /*!< DWidth                                                                    */
      __IOM uint32_t SLargerD   : 1;            /*!< SLargerD                                                                  */
            uint32_t            : 1;
      __IOM uint32_t SI         : 1;            /*!< SI                                                                        */
      __IOM uint32_t DI         : 1;            /*!< DI                                                                        */
      __IOM uint32_t Prot       : 3;            /*!< Prot                                                                      */
      __IOM uint32_t I          : 1;            /*!< I                                                                         */
    } bit;
  } DMA_C0Control;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C0Config.                                                             */
    
    struct {
      __IOM uint32_t E          : 1;            /*!< E                                                                         */
      __IOM uint32_t SrcPeripheral : 5;         /*!< SrcPeripheral                                                             */
      __IOM uint32_t DstPeripheral : 5;         /*!< DstPeripheral                                                             */
      __IOM uint32_t FlowCntrl  : 3;            /*!< FlowCntrl                                                                 */
      __IOM uint32_t IE         : 1;            /*!< IE                                                                        */
      __IOM uint32_t ITC        : 1;            /*!< ITC                                                                       */
      __IOM uint32_t L          : 1;            /*!< L                                                                         */
      __IOM uint32_t A          : 1;            /*!< A                                                                         */
      __IOM uint32_t H          : 1;            /*!< H                                                                         */
            uint32_t            : 1;
      __IOM uint32_t LLICounter : 10;           /*!< LLICounter                                                                */
            uint32_t            : 2;
    } bit;
  } DMA_C0Config;
  __IM  uint32_t  RESERVED1[59];
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C1SrcAddr.                                                            */
    
    struct {
      __IOM uint32_t SrcAddr    : 32;           /*!< SrcAddr                                                                   */
    } bit;
  } DMA_C1SrcAddr;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C1DstAddr.                                                            */
    
    struct {
      __IOM uint32_t DstAddr    : 32;           /*!< DstAddr                                                                   */
    } bit;
  } DMA_C1DstAddr;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C1LLI.                                                                */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t LLI        : 30;           /*!< LLI                                                                       */
    } bit;
  } DMA_C1LLI;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C1Control.                                                            */
    
    struct {
      __IOM uint32_t TransferSize : 12;         /*!< TransferSize                                                              */
      __IOM uint32_t SBSize     : 3;            /*!< SBSize                                                                    */
      __IOM uint32_t DBSize     : 3;            /*!< DBSize                                                                    */
      __IOM uint32_t SWidth     : 3;            /*!< SWidth                                                                    */
      __IOM uint32_t DWidth     : 3;            /*!< DWidth                                                                    */
            uint32_t            : 2;
      __IOM uint32_t SI         : 1;            /*!< SI                                                                        */
      __IOM uint32_t DI         : 1;            /*!< DI                                                                        */
      __IOM uint32_t Prot       : 3;            /*!< Prot                                                                      */
      __IOM uint32_t I          : 1;            /*!< I                                                                         */
    } bit;
  } DMA_C1Control;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C1Config.                                                             */
    
    struct {
      __IOM uint32_t E          : 1;            /*!< E                                                                         */
      __IOM uint32_t SrcPeripheral : 5;         /*!< SrcPeripheral                                                             */
      __IOM uint32_t DstPeripheral : 5;         /*!< DstPeripheral                                                             */
      __IOM uint32_t FlowCntrl  : 3;            /*!< FlowCntrl                                                                 */
      __IOM uint32_t IE         : 1;            /*!< IE                                                                        */
      __IOM uint32_t ITC        : 1;            /*!< ITC                                                                       */
      __IOM uint32_t L          : 1;            /*!< L                                                                         */
      __IOM uint32_t A          : 1;            /*!< A                                                                         */
      __IOM uint32_t H          : 1;            /*!< H                                                                         */
            uint32_t            : 13;
    } bit;
  } DMA_C1Config;
  __IM  uint32_t  RESERVED2[59];
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C2SrcAddr.                                                            */
    
    struct {
      __IOM uint32_t SrcAddr    : 32;           /*!< SrcAddr                                                                   */
    } bit;
  } DMA_C2SrcAddr;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C2DstAddr.                                                            */
    
    struct {
      __IOM uint32_t DstAddr    : 32;           /*!< DstAddr                                                                   */
    } bit;
  } DMA_C2DstAddr;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C2LLI.                                                                */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t LLI        : 30;           /*!< LLI                                                                       */
    } bit;
  } DMA_C2LLI;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C2Control.                                                            */
    
    struct {
      __IOM uint32_t TransferSize : 12;         /*!< TransferSize                                                              */
      __IOM uint32_t SBSize     : 3;            /*!< SBSize                                                                    */
      __IOM uint32_t DBSize     : 3;            /*!< DBSize                                                                    */
      __IOM uint32_t SWidth     : 3;            /*!< SWidth                                                                    */
      __IOM uint32_t DWidth     : 3;            /*!< DWidth                                                                    */
            uint32_t            : 2;
      __IOM uint32_t SI         : 1;            /*!< SI                                                                        */
      __IOM uint32_t DI         : 1;            /*!< DI                                                                        */
      __IOM uint32_t Prot       : 3;            /*!< Prot                                                                      */
      __IOM uint32_t I          : 1;            /*!< I                                                                         */
    } bit;
  } DMA_C2Control;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C2Config.                                                             */
    
    struct {
      __IOM uint32_t E          : 1;            /*!< E                                                                         */
      __IOM uint32_t SrcPeripheral : 5;         /*!< SrcPeripheral                                                             */
      __IOM uint32_t DstPeripheral : 5;         /*!< DstPeripheral                                                             */
      __IOM uint32_t FlowCntrl  : 3;            /*!< FlowCntrl                                                                 */
      __IOM uint32_t IE         : 1;            /*!< IE                                                                        */
      __IOM uint32_t ITC        : 1;            /*!< ITC                                                                       */
      __IOM uint32_t L          : 1;            /*!< L                                                                         */
      __IOM uint32_t A          : 1;            /*!< A                                                                         */
      __IOM uint32_t H          : 1;            /*!< H                                                                         */
            uint32_t            : 13;
    } bit;
  } DMA_C2Config;
  __IM  uint32_t  RESERVED3[59];
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C3SrcAddr.                                                            */
    
    struct {
      __IOM uint32_t SrcAddr    : 32;           /*!< SrcAddr                                                                   */
    } bit;
  } DMA_C3SrcAddr;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C3DstAddr.                                                            */
    
    struct {
      __IOM uint32_t DstAddr    : 32;           /*!< DstAddr                                                                   */
    } bit;
  } DMA_C3DstAddr;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C3LLI.                                                                */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t LLI        : 30;           /*!< LLI                                                                       */
    } bit;
  } DMA_C3LLI;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C3Control.                                                            */
    
    struct {
      __IOM uint32_t TransferSize : 12;         /*!< TransferSize                                                              */
      __IOM uint32_t SBSize     : 3;            /*!< SBSize                                                                    */
      __IOM uint32_t DBSize     : 3;            /*!< DBSize                                                                    */
      __IOM uint32_t SWidth     : 3;            /*!< SWidth                                                                    */
      __IOM uint32_t DWidth     : 3;            /*!< DWidth                                                                    */
            uint32_t            : 2;
      __IOM uint32_t SI         : 1;            /*!< SI                                                                        */
      __IOM uint32_t DI         : 1;            /*!< DI                                                                        */
      __IOM uint32_t Prot       : 3;            /*!< Prot                                                                      */
      __IOM uint32_t I          : 1;            /*!< I                                                                         */
    } bit;
  } DMA_C3Control;
  
  union {
    __IOM uint32_t reg;                         /*!< DMA_C3Config.                                                             */
    
    struct {
      __IOM uint32_t E          : 1;            /*!< E                                                                         */
      __IOM uint32_t SrcPeripheral : 5;         /*!< SrcPeripheral                                                             */
      __IOM uint32_t DstPeripheral : 5;         /*!< DstPeripheral                                                             */
      __IOM uint32_t FlowCntrl  : 3;            /*!< FlowCntrl                                                                 */
      __IOM uint32_t IE         : 1;            /*!< IE                                                                        */
      __IOM uint32_t ITC        : 1;            /*!< ITC                                                                       */
      __IOM uint32_t L          : 1;            /*!< L                                                                         */
      __IOM uint32_t A          : 1;            /*!< A                                                                         */
      __IOM uint32_t H          : 1;            /*!< H                                                                         */
            uint32_t            : 13;
    } bit;
  } DMA_C3Config;
} dma_Type;                                     /*!< Size = 1044 (0x414)                                                       */



/* =========================================================================================================================== */
/* ================                                            pds                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief pds. (pds)
  */

typedef struct {                                /*!< pds Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< PDS_CTL.                                                                  */
    
    struct {
      __IOM uint32_t pds_start_ps : 1;          /*!< pds_start_ps                                                              */
      __IOM uint32_t cr_sleep_forever : 1;      /*!< cr_sleep_forever                                                          */
      __IOM uint32_t cr_xtal_force_off : 1;     /*!< cr_xtal_force_off                                                         */
      __IOM uint32_t cr_wifi_pds_save_state : 1;/*!< cr_wifi_pds_save_state                                                    */
      __IOM uint32_t cr_pds_pd_dcdc18 : 1;      /*!< cr_pds_pd_dcdc18                                                          */
      __IOM uint32_t cr_pds_pd_bg_sys : 1;      /*!< cr_pds_pd_bg_sys                                                          */
            uint32_t            : 2;
      __IOM uint32_t cr_pds_gate_clk : 1;       /*!< cr_pds_gate_clk                                                           */
      __IOM uint32_t cr_pds_mem_stby : 1;       /*!< cr_pds_mem_stby                                                           */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_iso_en : 1;         /*!< cr_pds_iso_en                                                             */
      __IOM uint32_t cr_pds_wait_xtal_rdy : 1;  /*!< cr_pds_wait_xtal_rdy                                                      */
      __IOM uint32_t cr_pds_pwr_off : 1;        /*!< cr_pds_pwr_off                                                            */
      __IOM uint32_t cr_pds_pd_xtal : 1;        /*!< cr_pds_pd_xtal                                                            */
      __IOM uint32_t cr_pds_soc_enb_force_on : 1;/*!< cr_pds_soc_enb_force_on                                                  */
      __IOM uint32_t cr_pds_rst_soc_en : 1;     /*!< cr_pds_rst_soc_en                                                         */
      __IOM uint32_t cr_pds_rc32m_off_dis : 1;  /*!< cr_pds_rc32m_off_dis                                                      */
      __IOM uint32_t cr_pds_ldo_vsel_en : 1;    /*!< cr_pds_ldo_vsel_en                                                        */
            uint32_t            : 2;
      __IOM uint32_t cr_np_wfi_mask : 1;        /*!< cr_np_wfi_mask                                                            */
      __IOM uint32_t cr_pds_pd_ldo11 : 1;       /*!< cr_pds_pd_ldo11                                                           */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_ldo_vol : 4;        /*!< cr_pds_ldo_vol                                                            */
      __IOM uint32_t cr_pds_ctrl_rf : 2;        /*!< cr_pds_ctrl_rf                                                            */
      __IOM uint32_t cr_pds_ctrl_pll : 2;       /*!< cr_pds_ctrl_pll                                                           */
    } bit;
  } PDS_CTL;
  
  union {
    __IOM uint32_t reg;                         /*!< PDS_TIME1.                                                                */
    
    struct {
      __IOM uint32_t cr_sleep_duration : 32;    /*!< cr_sleep_duration                                                         */
    } bit;
  } PDS_TIME1;
  __IM  uint32_t  RESERVED;
  
  union {
    __IOM uint32_t reg;                         /*!< PDS_INT.                                                                  */
    
    struct {
      __IOM uint32_t ro_pds_wake_int : 1;       /*!< ro_pds_wake_int                                                           */
      __IOM uint32_t ro_pds_irq_in : 1;         /*!< ro_pds_irq_in                                                             */
      __IOM uint32_t ro_pds_rf_done_int : 1;    /*!< ro_pds_rf_done_int                                                        */
      __IOM uint32_t ro_pds_pll_done_int : 1;   /*!< ro_pds_pll_done_int                                                       */
            uint32_t            : 4;
      __IOM uint32_t cr_pds_wake_int_mask : 1;  /*!< cr_pds_wake_int_mask                                                      */
      __IOM uint32_t cr_pds_irq_in_dis : 1;     /*!< cr_pds_irq_in_dis                                                         */
      __IOM uint32_t cr_pds_rf_done_int_mask : 1;/*!< cr_pds_rf_done_int_mask                                                  */
      __IOM uint32_t cr_pds_pll_done_int_mask : 1;/*!< cr_pds_pll_done_int_mask                                                */
            uint32_t            : 4;
      __IOM uint32_t cr_pds_int_clr : 1;        /*!< cr_pds_int_clr                                                            */
            uint32_t            : 15;
    } bit;
  } PDS_INT;
  
  union {
    __IOM uint32_t reg;                         /*!< PDS_CTL2.                                                                 */
    
    struct {
      __IOM uint32_t cr_pds_force_np_pwr_off : 1;/*!< cr_pds_force_np_pwr_off                                                  */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_wb_pwr_off : 1;/*!< cr_pds_force_wb_pwr_off                                                  */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_np_iso_en : 1;/*!< cr_pds_force_np_iso_en                                                    */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_wb_iso_en : 1;/*!< cr_pds_force_wb_iso_en                                                    */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_np_pds_rst : 1;/*!< cr_pds_force_np_pds_rst                                                  */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_wb_pds_rst : 1;/*!< cr_pds_force_wb_pds_rst                                                  */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_np_mem_stby : 1;/*!< cr_pds_force_np_mem_stby                                                */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_wb_mem_stby : 1;/*!< cr_pds_force_wb_mem_stby                                                */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_np_gate_clk : 1;/*!< cr_pds_force_np_gate_clk                                                */
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_wb_gate_clk : 1;/*!< cr_pds_force_wb_gate_clk                                                */
            uint32_t            : 13;
    } bit;
  } PDS_CTL2;
  
  union {
    __IOM uint32_t reg;                         /*!< PDS_CTL3.                                                                 */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t cr_pds_force_misc_pwr_off : 1;/*!< cr_pds_force_misc_pwr_off                                              */
            uint32_t            : 2;
      __IOM uint32_t cr_pds_force_misc_iso_en : 1;/*!< cr_pds_force_misc_iso_en                                                */
            uint32_t            : 2;
      __IOM uint32_t cr_pds_force_misc_pds_rst : 1;/*!< cr_pds_force_misc_pds_rst                                              */
            uint32_t            : 2;
      __IOM uint32_t cr_pds_force_misc_mem_stby : 1;/*!< cr_pds_force_misc_mem_stby                                            */
            uint32_t            : 2;
      __IOM uint32_t cr_pds_force_misc_gate_clk : 1;/*!< cr_pds_force_misc_gate_clk                                            */
            uint32_t            : 10;
      __IOM uint32_t cr_pds_np_iso_en : 1;      /*!< cr_pds_np_iso_en                                                          */
            uint32_t            : 2;
      __IOM uint32_t cr_pds_wb_iso_en : 1;      /*!< cr_pds_wb_iso_en                                                          */
            uint32_t            : 2;
      __IOM uint32_t cr_pds_misc_iso_en : 1;    /*!< cr_pds_misc_iso_en                                                        */
            uint32_t            : 1;
    } bit;
  } PDS_CTL3;
  
  union {
    __IOM uint32_t reg;                         /*!< PDS_CTL4.                                                                 */
    
    struct {
      __IOM uint32_t cr_pds_np_pwr_off : 1;     /*!< cr_pds_np_pwr_off                                                         */
      __IOM uint32_t cr_pds_np_reset : 1;       /*!< cr_pds_np_reset                                                           */
      __IOM uint32_t cr_pds_np_mem_stby : 1;    /*!< cr_pds_np_mem_stby                                                        */
      __IOM uint32_t cr_pds_np_gate_clk : 1;    /*!< cr_pds_np_gate_clk                                                        */
            uint32_t            : 8;
      __IOM uint32_t cr_pds_wb_pwr_off : 1;     /*!< cr_pds_wb_pwr_off                                                         */
      __IOM uint32_t cr_pds_wb_reset : 1;       /*!< cr_pds_wb_reset                                                           */
      __IOM uint32_t cr_pds_wb_mem_stby : 1;    /*!< cr_pds_wb_mem_stby                                                        */
      __IOM uint32_t cr_pds_wb_gate_clk : 1;    /*!< cr_pds_wb_gate_clk                                                        */
            uint32_t            : 8;
      __IOM uint32_t cr_pds_misc_pwr_off : 1;   /*!< cr_pds_misc_pwr_off                                                       */
      __IOM uint32_t cr_pds_misc_reset : 1;     /*!< cr_pds_misc_reset                                                         */
      __IOM uint32_t cr_pds_misc_mem_stby : 1;  /*!< cr_pds_misc_mem_stby                                                      */
      __IOM uint32_t cr_pds_misc_gate_clk : 1;  /*!< cr_pds_misc_gate_clk                                                      */
            uint32_t            : 4;
    } bit;
  } PDS_CTL4;
  
  union {
    __IOM uint32_t reg;                         /*!< pds_stat.                                                                 */
    
    struct {
      __IOM uint32_t ro_pds_state : 4;          /*!< ro_pds_state                                                              */
            uint32_t            : 4;
      __IOM uint32_t ro_pds_rf_state : 4;       /*!< ro_pds_rf_state                                                           */
            uint32_t            : 4;
      __IOM uint32_t ro_pds_pll_state : 2;      /*!< ro_pds_pll_state                                                          */
            uint32_t            : 14;
    } bit;
  } pds_stat;
  
  union {
    __IOM uint32_t reg;                         /*!< pds_ram1.                                                                 */
    
    struct {
      __IOM uint32_t cr_np_sram_pwr : 8;        /*!< cr_np_sram_pwr                                                            */
            uint32_t            : 24;
    } bit;
  } pds_ram1;
  __IM  uint32_t  RESERVED1[183];
  
  union {
    __IOM uint32_t reg;                         /*!< rc32m_ctrl0.                                                              */
    
    struct {
      __IOM uint32_t rc32m_cal_done : 1;        /*!< rc32m_cal_done                                                            */
      __IOM uint32_t rc32m_rdy  : 1;            /*!< rc32m_rdy                                                                 */
      __IOM uint32_t rc32m_cal_inprogress : 1;  /*!< rc32m_cal_inprogress                                                      */
      __IOM uint32_t rc32m_cal_div : 2;         /*!< rc32m_cal_div                                                             */
      __IOM uint32_t rc32m_cal_precharge : 1;   /*!< rc32m_cal_precharge                                                       */
      __IOM uint32_t rc32m_dig_code_fr_cal : 8; /*!< rc32m_dig_code_fr_cal                                                     */
            uint32_t            : 3;
      __IOM uint32_t rc32m_allow_cal : 1;       /*!< rc32m_allow_cal                                                           */
      __IOM uint32_t rc32m_refclk_half : 1;     /*!< rc32m_refclk_half                                                         */
      __IOM uint32_t rc32m_ext_code_en : 1;     /*!< rc32m_ext_code_en                                                         */
      __IOM uint32_t rc32m_cal_en : 1;          /*!< rc32m_cal_en                                                              */
      __IOM uint32_t rc32m_pd   : 1;            /*!< rc32m_pd                                                                  */
      __IOM uint32_t rc32m_code_fr_ext : 8;     /*!< rc32m_code_fr_ext                                                         */
            uint32_t            : 2;
    } bit;
  } rc32m_ctrl0;
  
  union {
    __IOM uint32_t reg;                         /*!< rc32m_ctrl1.                                                              */
    
    struct {
      __IOM uint32_t rc32m_test_en : 1;         /*!< rc32m_test_en                                                             */
      __IOM uint32_t rc32m_soft_rst : 1;        /*!< rc32m_soft_rst                                                            */
      __IOM uint32_t rc32m_clk_soft_rst : 1;    /*!< rc32m_clk_soft_rst                                                        */
      __IOM uint32_t rc32m_clk_inv : 1;         /*!< rc32m_clk_inv                                                             */
      __IOM uint32_t rc32m_clk_force_on : 1;    /*!< rc32m_clk_force_on                                                        */
            uint32_t            : 19;
      __IOM uint32_t rc32m_reserved : 8;        /*!< rc32m_reserved                                                            */
    } bit;
  } rc32m_ctrl1;
  __IM  uint32_t  RESERVED2[62];
  
  union {
    __IOM uint32_t reg;                         /*!< pu_rst_clkpll.                                                            */
    
    struct {
      __IOM uint32_t clkpll_sdm_reset : 1;      /*!< clkpll_sdm_reset                                                          */
      __IOM uint32_t clkpll_reset_postdiv : 1;  /*!< clkpll_reset_postdiv                                                      */
      __IOM uint32_t clkpll_reset_fbdv : 1;     /*!< clkpll_reset_fbdv                                                         */
      __IOM uint32_t clkpll_reset_refdiv : 1;   /*!< clkpll_reset_refdiv                                                       */
      __IOM uint32_t clkpll_pu_postdiv : 1;     /*!< clkpll_pu_postdiv                                                         */
      __IOM uint32_t clkpll_pu_fbdv : 1;        /*!< clkpll_pu_fbdv                                                            */
      __IOM uint32_t clkpll_pu_clamp_op : 1;    /*!< clkpll_pu_clamp_op                                                        */
      __IOM uint32_t clkpll_pu_pfd : 1;         /*!< clkpll_pu_pfd                                                             */
      __IOM uint32_t clkpll_pu_cp : 1;          /*!< clkpll_pu_cp                                                              */
      __IOM uint32_t pu_clkpll_sfreg : 1;       /*!< pu_clkpll_sfreg                                                           */
      __IOM uint32_t pu_clkpll  : 1;            /*!< pu_clkpll                                                                 */
            uint32_t            : 21;
    } bit;
  } pu_rst_clkpll;
  
  union {
    __IOM uint32_t reg;                         /*!< clkpll_top_ctrl.                                                          */
    
    struct {
      __IOM uint32_t clkpll_postdiv : 7;        /*!< clkpll_postdiv                                                            */
            uint32_t            : 1;
      __IOM uint32_t clkpll_refdiv_ratio : 4;   /*!< clkpll_refdiv_ratio                                                       */
      __IOM uint32_t clkpll_xtal_rc32m_sel : 1; /*!< clkpll_xtal_rc32m_sel                                                     */
            uint32_t            : 3;
      __IOM uint32_t clkpll_refclk_sel : 1;     /*!< clkpll_refclk_sel                                                         */
            uint32_t            : 3;
      __IOM uint32_t clkpll_vg11_sel : 2;       /*!< clkpll_vg11_sel                                                           */
            uint32_t            : 2;
      __IOM uint32_t clkpll_vg13_sel : 2;       /*!< clkpll_vg13_sel                                                           */
            uint32_t            : 6;
    } bit;
  } clkpll_top_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< clkpll_cp.                                                                */
    
    struct {
      __IOM uint32_t clkpll_sel_cp_bias : 1;    /*!< clkpll_sel_cp_bias                                                        */
            uint32_t            : 3;
      __IOM uint32_t clkpll_icp_5u : 2;         /*!< clkpll_icp_5u                                                             */
      __IOM uint32_t clkpll_icp_1u : 2;         /*!< clkpll_icp_1u                                                             */
      __IOM uint32_t clkpll_int_frac_sw : 1;    /*!< clkpll_int_frac_sw                                                        */
      __IOM uint32_t clkpll_cp_startup_en : 1;  /*!< clkpll_cp_startup_en                                                      */
      __IOM uint32_t clkpll_cp_opamp_en : 1;    /*!< clkpll_cp_opamp_en                                                        */
            uint32_t            : 21;
    } bit;
  } clkpll_cp;
  
  union {
    __IOM uint32_t reg;                         /*!< clkpll_rz.                                                                */
    
    struct {
      __IOM uint32_t clkpll_c4_en : 1;          /*!< clkpll_c4_en                                                              */
            uint32_t            : 3;
      __IOM uint32_t clkpll_r4  : 2;            /*!< clkpll_r4                                                                 */
            uint32_t            : 2;
      __IOM uint32_t clkpll_r4_short : 1;       /*!< clkpll_r4_short                                                           */
            uint32_t            : 3;
      __IOM uint32_t clkpll_c3  : 2;            /*!< clkpll_c3                                                                 */
      __IOM uint32_t clkpll_cz  : 2;            /*!< clkpll_cz                                                                 */
      __IOM uint32_t clkpll_rz  : 3;            /*!< clkpll_rz                                                                 */
            uint32_t            : 13;
    } bit;
  } clkpll_rz;
  
  union {
    __IOM uint32_t reg;                         /*!< clkpll_fbdv.                                                              */
    
    struct {
      __IOM uint32_t clkpll_sel_sample_clk : 2; /*!< clkpll_sel_sample_clk                                                     */
      __IOM uint32_t clkpll_sel_fb_clk : 2;     /*!< clkpll_sel_fb_clk                                                         */
            uint32_t            : 28;
    } bit;
  } clkpll_fbdv;
  
  union {
    __IOM uint32_t reg;                         /*!< clkpll_vco.                                                               */
    
    struct {
      __IOM uint32_t clkpll_vco_speed : 3;      /*!< clkpll_vco_speed                                                          */
      __IOM uint32_t clkpll_shrtr : 1;          /*!< clkpll_shrtr                                                              */
            uint32_t            : 28;
    } bit;
  } clkpll_vco;
  
  union {
    __IOM uint32_t reg;                         /*!< clkpll_sdm.                                                               */
    
    struct {
      __IOM uint32_t clkpll_sdmin : 24;         /*!< clkpll_sdmin                                                              */
      __IOM uint32_t clkpll_dither_sel : 2;     /*!< clkpll_dither_sel                                                         */
            uint32_t            : 2;
      __IOM uint32_t clkpll_sdm_flag : 1;       /*!< clkpll_sdm_flag                                                           */
      __IOM uint32_t clkpll_sdm_bypass : 1;     /*!< clkpll_sdm_bypass                                                         */
            uint32_t            : 2;
    } bit;
  } clkpll_sdm;
  
  union {
    __IOM uint32_t reg;                         /*!< clkpll_output_en.                                                         */
    
    struct {
      __IOM uint32_t clkpll_en_480m : 1;        /*!< clkpll_en_480m                                                            */
      __IOM uint32_t clkpll_en_240m : 1;        /*!< clkpll_en_240m                                                            */
      __IOM uint32_t clkpll_en_192m : 1;        /*!< clkpll_en_192m                                                            */
      __IOM uint32_t clkpll_en_160m : 1;        /*!< clkpll_en_160m                                                            */
      __IOM uint32_t clkpll_en_120m : 1;        /*!< clkpll_en_120m                                                            */
      __IOM uint32_t clkpll_en_96m : 1;         /*!< clkpll_en_96m                                                             */
      __IOM uint32_t clkpll_en_80m : 1;         /*!< clkpll_en_80m                                                             */
      __IOM uint32_t clkpll_en_48m : 1;         /*!< clkpll_en_48m                                                             */
      __IOM uint32_t clkpll_en_32m : 1;         /*!< clkpll_en_32m                                                             */
      __IOM uint32_t clkpll_en_div2_480m : 1;   /*!< clkpll_en_div2_480m                                                       */
            uint32_t            : 22;
    } bit;
  } clkpll_output_en;
} pds_Type;                                     /*!< Size = 1056 (0x420)                                                       */



/* =========================================================================================================================== */
/* ================                                            HBN                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief HBN. (HBN)
  */

typedef struct {                                /*!< HBN Structure                                                             */
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_CTL.                                                                  */
    
    struct {
      __IOM uint32_t rtc_ctl    : 7;            /*!< rtc_ctl                                                                   */
      __IOM uint32_t hbn_mode   : 1;            /*!< hbn_mode                                                                  */
      __IOM uint32_t trap_mode  : 1;            /*!< trap_mode                                                                 */
      __IOM uint32_t pwrdn_hbn_core : 1;        /*!< pwrdn_hbn_core                                                            */
            uint32_t            : 1;
      __IOM uint32_t pwrdn_hbn_rtc : 1;         /*!< pwrdn_hbn_rtc                                                             */
      __IOM uint32_t sw_rst     : 1;            /*!< sw_rst                                                                    */
      __IOM uint32_t hbn_dis_pwr_off_ldo11 : 1; /*!< hbn_dis_pwr_off_ldo11                                                     */
      __IOM uint32_t hbn_dis_pwr_off_ldo11_rt : 1;/*!< hbn_dis_pwr_off_ldo11_rt                                                */
      __IOM uint32_t hbn_ldo11_rt_vout_sel : 4; /*!< hbn_ldo11_rt_vout_sel                                                     */
      __IOM uint32_t hbn_ldo11_aon_vout_sel : 4;/*!< hbn_ldo11_aon_vout_sel                                                    */
      __IOM uint32_t pu_dcdc18_aon : 1;         /*!< pu_dcdc18_aon                                                             */
      __IOM uint32_t rtc_dly_option : 1;        /*!< rtc_dly_option                                                            */
      __IOM uint32_t pwr_on_option : 1;         /*!< pwr_on_option                                                             */
      __IOM uint32_t sram_slp_option : 1;       /*!< sram_slp_option                                                           */
      __IOM uint32_t sram_slp   : 1;            /*!< sram_slp                                                                  */
      __IOM uint32_t hbn_state  : 4;            /*!< hbn_state                                                                 */
    } bit;
  } HBN_CTL;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_TIME_L.                                                               */
    
    struct {
      __IOM uint32_t hbn_time_l : 32;           /*!< hbn_time_l                                                                */
    } bit;
  } HBN_TIME_L;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_TIME_H.                                                               */
    
    struct {
      __IOM uint32_t hbn_time_h : 8;            /*!< hbn_time_h                                                                */
            uint32_t            : 24;
    } bit;
  } HBN_TIME_H;
  
  union {
    __IOM uint32_t reg;                         /*!< RTC_TIME_L.                                                               */
    
    struct {
      __IOM uint32_t rtc_time_latch_l : 32;     /*!< rtc_time_latch_l                                                          */
    } bit;
  } RTC_TIME_L;
  
  union {
    __IOM uint32_t reg;                         /*!< RTC_TIME_H.                                                               */
    
    struct {
      __IOM uint32_t rtc_time_latch_h : 8;      /*!< rtc_time_latch_h                                                          */
            uint32_t            : 23;
      __IOM uint32_t rtc_time_latch : 1;        /*!< rtc_time_latch                                                            */
    } bit;
  } RTC_TIME_H;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_IRQ_MODE.                                                             */
    
    struct {
      __IOM uint32_t hbn_pin_wakeup_mode : 3;   /*!< hbn_pin_wakeup_mode                                                       */
      __IOM uint32_t hbn_pin_wakeup_mask : 2;   /*!< hbn_pin_wakeup_mask                                                       */
            uint32_t            : 3;
      __IOM uint32_t reg_aon_pad_ie_smt : 1;    /*!< reg_aon_pad_ie_smt                                                        */
            uint32_t            : 7;
      __IOM uint32_t reg_en_hw_pu_pd : 1;       /*!< reg_en_hw_pu_pd                                                           */
            uint32_t            : 1;
      __IOM uint32_t irq_bor_en : 1;            /*!< irq_bor_en                                                                */
            uint32_t            : 1;
      __IOM uint32_t irq_acomp0_en : 2;         /*!< irq_acomp0_en                                                             */
      __IOM uint32_t irq_acomp1_en : 2;         /*!< irq_acomp1_en                                                             */
      __IOM uint32_t pin_wakeup_sel : 3;        /*!< pin_wakeup_sel                                                            */
      __IOM uint32_t pin_wakeup_en : 1;         /*!< pin_wakeup_en                                                             */
            uint32_t            : 4;
    } bit;
  } HBN_IRQ_MODE;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_IRQ_STAT.                                                             */
    
    struct {
      __IOM uint32_t irq_stat   : 32;           /*!< irq_stat                                                                  */
    } bit;
  } HBN_IRQ_STAT;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_IRQ_CLR.                                                              */
    
    struct {
      __IOM uint32_t irq_clr    : 32;           /*!< irq_clr                                                                   */
    } bit;
  } HBN_IRQ_CLR;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_PIR_CFG.                                                              */
    
    struct {
      __IOM uint32_t pir_hpf_sel : 2;           /*!< pir_hpf_sel                                                               */
      __IOM uint32_t pir_lpf_sel : 1;           /*!< pir_lpf_sel                                                               */
            uint32_t            : 1;
      __IOM uint32_t pir_dis    : 2;            /*!< pir_dis                                                                   */
            uint32_t            : 1;
      __IOM uint32_t pir_en     : 1;            /*!< pir_en                                                                    */
      __IOM uint32_t gpadc_cgen : 1;            /*!< gpadc_cgen                                                                */
      __IOM uint32_t gpadc_nosync : 1;          /*!< gpadc_nosync                                                              */
            uint32_t            : 22;
    } bit;
  } HBN_PIR_CFG;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_PIR_VTH.                                                              */
    
    struct {
      __IOM uint32_t pir_vth    : 14;           /*!< pir_vth                                                                   */
            uint32_t            : 18;
    } bit;
  } HBN_PIR_VTH;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_PIR_INTERVAL.                                                         */
    
    struct {
      __IOM uint32_t pir_interval : 12;         /*!< pir_interval                                                              */
            uint32_t            : 20;
    } bit;
  } HBN_PIR_INTERVAL;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_BOR_CFG.                                                              */
    
    struct {
      __IOM uint32_t bor_sel    : 1;            /*!< bor_sel                                                                   */
      __IOM uint32_t bor_vth    : 1;            /*!< bor_vth                                                                   */
      __IOM uint32_t pu_bor     : 1;            /*!< pu_bor                                                                    */
      __IOM uint32_t r_bor_out  : 1;            /*!< r_bor_out                                                                 */
            uint32_t            : 28;
    } bit;
  } HBN_BOR_CFG;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_GLB.                                                                  */
    
    struct {
      __IOM uint32_t hbn_root_clk_sel : 2;      /*!< hbn_root_clk_sel                                                          */
      __IOM uint32_t hbn_uart_clk_sel : 1;      /*!< hbn_uart_clk_sel                                                          */
      __IOM uint32_t hbn_f32k_sel : 2;          /*!< hbn_f32k_sel                                                              */
      __IOM uint32_t hbn_pu_rc32k : 1;          /*!< hbn_pu_rc32k                                                              */
            uint32_t            : 10;
      __IOM uint32_t sw_ldo11soc_vout_sel_aon : 4;/*!< sw_ldo11soc_vout_sel_aon                                                */
            uint32_t            : 4;
      __IOM uint32_t sw_ldo11_rt_vout_sel : 4;  /*!< sw_ldo11_rt_vout_sel                                                      */
      __IOM uint32_t sw_ldo11_aon_vout_sel : 4; /*!< sw_ldo11_aon_vout_sel                                                     */
    } bit;
  } HBN_GLB;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_SRAM.                                                                 */
    
    struct {
            uint32_t            : 6;
      __IOM uint32_t retram_ret : 1;            /*!< retram_ret                                                                */
      __IOM uint32_t retram_slp : 1;            /*!< retram_slp                                                                */
            uint32_t            : 24;
    } bit;
  } HBN_SRAM;
  __IM  uint32_t  RESERVED[50];
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_RSV0.                                                                 */
    
    struct {
      __IOM uint32_t HBN_RSV0   : 32;           /*!< HBN_RSV0                                                                  */
    } bit;
  } HBN_RSV0;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_RSV1.                                                                 */
    
    struct {
      __IOM uint32_t HBN_RSV1   : 32;           /*!< HBN_RSV1                                                                  */
    } bit;
  } HBN_RSV1;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_RSV2.                                                                 */
    
    struct {
      __IOM uint32_t HBN_RSV2   : 32;           /*!< HBN_RSV2                                                                  */
    } bit;
  } HBN_RSV2;
  
  union {
    __IOM uint32_t reg;                         /*!< HBN_RSV3.                                                                 */
    
    struct {
      __IOM uint32_t HBN_RSV3   : 32;           /*!< HBN_RSV3                                                                  */
    } bit;
  } HBN_RSV3;
  __IM  uint32_t  RESERVED1[60];
  
  union {
    __IOM uint32_t reg;                         /*!< rc32k_ctrl0.                                                              */
    
    struct {
      __IOM uint32_t rc32k_cal_done : 1;        /*!< rc32k_cal_done                                                            */
      __IOM uint32_t rc32k_rdy  : 1;            /*!< rc32k_rdy                                                                 */
      __IOM uint32_t rc32k_cal_inprogress : 1;  /*!< rc32k_cal_inprogress                                                      */
      __IOM uint32_t rc32k_cal_div : 2;         /*!< rc32k_cal_div                                                             */
      __IOM uint32_t rc32k_cal_precharge : 1;   /*!< rc32k_cal_precharge                                                       */
      __IOM uint32_t rc32k_dig_code_fr_cal : 10;/*!< rc32k_dig_code_fr_cal                                                     */
      __IOM uint32_t rc32k_vref_dly : 2;        /*!< rc32k_vref_dly                                                            */
      __IOM uint32_t rc32k_allow_cal : 1;       /*!< rc32k_allow_cal                                                           */
      __IOM uint32_t rc32k_ext_code_en : 1;     /*!< rc32k_ext_code_en                                                         */
      __IOM uint32_t rc32k_cal_en : 1;          /*!< rc32k_cal_en                                                              */
            uint32_t            : 1;
      __IOM uint32_t rc32k_code_fr_ext : 10;    /*!< rc32k_code_fr_ext                                                         */
    } bit;
  } rc32k_ctrl0;
  
  union {
    __IOM uint32_t reg;                         /*!< xtal32k.                                                                  */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t xtal32k_ext_sel : 1;       /*!< xtal32k_ext_sel                                                           */
      __IOM uint32_t xtal32k_amp_ctrl : 2;      /*!< xtal32k_amp_ctrl                                                          */
      __IOM uint32_t xtal32k_reg : 2;           /*!< xtal32k_reg                                                               */
      __IOM uint32_t xtal32k_outbuf_stre : 1;   /*!< xtal32k_outbuf_stre                                                       */
      __IOM uint32_t xtal32k_otf_short : 1;     /*!< xtal32k_otf_short                                                         */
      __IOM uint32_t xtal32k_inv_stre : 2;      /*!< xtal32k_inv_stre                                                          */
      __IOM uint32_t xtal32k_capbank : 6;       /*!< xtal32k_capbank                                                           */
      __IOM uint32_t xtal32k_ac_cap_short : 1;  /*!< xtal32k_ac_cap_short                                                      */
      __IOM uint32_t pu_xtal32k_buf : 1;        /*!< pu_xtal32k_buf                                                            */
      __IOM uint32_t pu_xtal32k : 1;            /*!< pu_xtal32k                                                                */
            uint32_t            : 12;
    } bit;
  } xtal32k;
} HBN_Type;                                     /*!< Size = 520 (0x208)                                                        */



/* =========================================================================================================================== */
/* ================                                            AON                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief AON. (AON)
  */

typedef struct {                                /*!< AON Structure                                                             */
  __IM  uint32_t  RESERVED[512];
  
  union {
    __IOM uint32_t reg;                         /*!< aon.                                                                      */
    
    struct {
      __IOM uint32_t aon_resv   : 8;            /*!< aon_resv                                                                  */
            uint32_t            : 4;
      __IOM uint32_t pu_aon_dc_tbuf : 1;        /*!< pu_aon_dc_tbuf                                                            */
            uint32_t            : 7;
      __IOM uint32_t ldo11_rt_pulldown : 1;     /*!< ldo11_rt_pulldown                                                         */
      __IOM uint32_t ldo11_rt_pulldown_sel : 1; /*!< ldo11_rt_pulldown_sel                                                     */
      __IOM uint32_t sw_pu_ldo11_rt : 1;        /*!< sw_pu_ldo11_rt                                                            */
            uint32_t            : 9;
    } bit;
  } aon;
  
  union {
    __IOM uint32_t reg;                         /*!< aon_common.                                                               */
    
    struct {
      __IOM uint32_t tmux_aon   : 3;            /*!< tmux_aon                                                                  */
            uint32_t            : 1;
      __IOM uint32_t ten_aon    : 1;            /*!< ten_aon                                                                   */
      __IOM uint32_t dten_xtal32k : 1;          /*!< dten_xtal32k                                                              */
      __IOM uint32_t ten_xtal32k : 1;           /*!< ten_xtal32k                                                               */
            uint32_t            : 1;
      __IOM uint32_t ten_vddcore_aon : 1;       /*!< ten_vddcore_aon                                                           */
      __IOM uint32_t ten_ldo11soc_aon : 1;      /*!< ten_ldo11soc_aon                                                          */
      __IOM uint32_t ten_dcdc18_0_aon : 1;      /*!< ten_dcdc18_0_aon                                                          */
      __IOM uint32_t ten_dcdc18_1_aon : 1;      /*!< ten_dcdc18_1_aon                                                          */
      __IOM uint32_t ten_bg_sys_aon : 1;        /*!< ten_bg_sys_aon                                                            */
            uint32_t            : 3;
      __IOM uint32_t ten_ldo15rf_aon : 1;       /*!< ten_ldo15rf_aon                                                           */
      __IOM uint32_t ten_xtal_aon : 1;          /*!< ten_xtal_aon                                                              */
      __IOM uint32_t dten_xtal_aon : 1;         /*!< dten_xtal_aon                                                             */
      __IOM uint32_t ten_mbg_aon : 1;           /*!< ten_mbg_aon                                                               */
      __IOM uint32_t ten_cip_misc_aon : 1;      /*!< ten_cip_misc_aon                                                          */
            uint32_t            : 11;
    } bit;
  } aon_common;
  
  union {
    __IOM uint32_t reg;                         /*!< aon_misc.                                                                 */
    
    struct {
      __IOM uint32_t sw_soc_en_aon : 1;         /*!< sw_soc_en_aon                                                             */
      __IOM uint32_t sw_wb_en_aon : 1;          /*!< sw_wb_en_aon                                                              */
            uint32_t            : 30;
    } bit;
  } aon_misc;
  __IM  uint32_t  RESERVED1;
  
  union {
    __IOM uint32_t reg;                         /*!< bg_sys_top.                                                               */
    
    struct {
      __IOM uint32_t pmip_resv  : 8;            /*!< pmip_resv                                                                 */
      __IOM uint32_t pu_bg_sys_aon : 1;         /*!< pu_bg_sys_aon                                                             */
            uint32_t            : 3;
      __IOM uint32_t bg_sys_start_ctrl_aon : 1; /*!< bg_sys_start_ctrl_aon                                                     */
            uint32_t            : 19;
    } bit;
  } bg_sys_top;
  
  union {
    __IOM uint32_t reg;                         /*!< dcdc18_top_0.                                                             */
    
    struct {
            uint32_t            : 1;
      __IOM uint32_t dcdc18_vout_sel_aon : 5;   /*!< dcdc18_vout_sel_aon                                                       */
            uint32_t            : 2;
      __IOM uint32_t dcdc18_vpfm_aon : 4;       /*!< dcdc18_vpfm_aon                                                           */
      __IOM uint32_t dcdc18_osc_2m_mode_aon : 1;/*!< dcdc18_osc_2m_mode_aon                                                    */
            uint32_t            : 3;
      __IOM uint32_t dcdc18_osc_freq_trim_aon : 4;/*!< dcdc18_osc_freq_trim_aon                                                */
      __IOM uint32_t dcdc18_slope_curr_sel_aon : 5;/*!< dcdc18_slope_curr_sel_aon                                              */
      __IOM uint32_t dcdc18_stop_osc_aon : 1;   /*!< dcdc18_stop_osc_aon                                                       */
      __IOM uint32_t dcdc18_slow_osc_aon : 1;   /*!< dcdc18_slow_osc_aon                                                       */
      __IOM uint32_t dcdc18_osc_inhibit_t2_aon : 1;/*!< dcdc18_osc_inhibit_t2_aon                                              */
      __IOM uint32_t dcdc18_sstart_time_aon : 2;/*!< dcdc18_sstart_time_aon                                                    */
            uint32_t            : 1;
      __IOM uint32_t dcdc18_rdy_aon : 1;        /*!< dcdc18_rdy_aon                                                            */
    } bit;
  } dcdc18_top_0;
  
  union {
    __IOM uint32_t reg;                         /*!< dcdc18_top_1.                                                             */
    
    struct {
      __IOM uint32_t dcdc18_force_cs_zvs_aon : 1;/*!< dcdc18_force_cs_zvs_aon                                                  */
      __IOM uint32_t dcdc18_cs_delay_aon : 3;   /*!< dcdc18_cs_delay_aon                                                       */
      __IOM uint32_t dcdc18_zvs_td_opt_aon : 3; /*!< dcdc18_zvs_td_opt_aon                                                     */
            uint32_t            : 1;
      __IOM uint32_t dcdc18_nonoverlap_td_aon : 5;/*!< dcdc18_nonoverlap_td_aon                                                */
            uint32_t            : 3;
      __IOM uint32_t dcdc18_rc_sel_aon : 4;     /*!< dcdc18_rc_sel_aon                                                         */
      __IOM uint32_t dcdc18_chf_sel_aon : 4;    /*!< dcdc18_chf_sel_aon                                                        */
      __IOM uint32_t dcdc18_cfb_sel_aon : 4;    /*!< dcdc18_cfb_sel_aon                                                        */
      __IOM uint32_t dcdc18_en_antiring_aon : 1;/*!< dcdc18_en_antiring_aon                                                    */
      __IOM uint32_t dcdc18_pulldown_aon : 1;   /*!< dcdc18_pulldown_aon                                                       */
            uint32_t            : 2;
    } bit;
  } dcdc18_top_1;
  
  union {
    __IOM uint32_t reg;                         /*!< ldo11soc_and_dctest.                                                      */
    
    struct {
      __IOM uint32_t pu_ldo11soc_aon : 1;       /*!< pu_ldo11soc_aon                                                           */
            uint32_t            : 3;
      __IOM uint32_t ldo11soc_sstart_sel_aon : 1;/*!< ldo11soc_sstart_sel_aon                                                  */
            uint32_t            : 3;
      __IOM uint32_t ldo11soc_sstart_delay_aon : 2;/*!< ldo11soc_sstart_delay_aon                                              */
      __IOM uint32_t ldo11soc_pulldown_aon : 1; /*!< ldo11soc_pulldown_aon                                                     */
      __IOM uint32_t ldo11soc_pulldown_sel_aon : 1;/*!< ldo11soc_pulldown_sel_aon                                              */
      __IOM uint32_t ldo11soc_vth_sel_aon : 2;  /*!< ldo11soc_vth_sel_aon                                                      */
            uint32_t            : 10;
      __IOM uint32_t ldo11soc_cc_aon : 2;       /*!< ldo11soc_cc_aon                                                           */
            uint32_t            : 2;
      __IOM uint32_t ldo11soc_rdy_aon : 1;      /*!< ldo11soc_rdy_aon                                                          */
      __IOM uint32_t ldo11soc_power_good_aon : 1;/*!< ldo11soc_power_good_aon                                                  */
      __IOM uint32_t pu_vddcore_misc_aon : 1;   /*!< pu_vddcore_misc_aon                                                       */
      __IOM uint32_t pmip_dc_tp_out_en_aon : 1; /*!< pmip_dc_tp_out_en_aon                                                     */
    } bit;
  } ldo11soc_and_dctest;
  
  union {
    __IOM uint32_t reg;                         /*!< psw_irrcv.                                                                */
    
    struct {
      __IOM uint32_t pu_ir_psw_aon : 1;         /*!< pu_ir_psw_aon                                                             */
            uint32_t            : 31;
    } bit;
  } psw_irrcv;
  __IM  uint32_t  RESERVED2[23];
  
  union {
    __IOM uint32_t reg;                         /*!< rf_top_aon.                                                               */
    
    struct {
      __IOM uint32_t pu_mbg_aon : 1;            /*!< pu_mbg_aon                                                                */
      __IOM uint32_t pu_ldo15rf_aon : 1;        /*!< pu_ldo15rf_aon                                                            */
      __IOM uint32_t pu_sfreg_aon : 1;          /*!< pu_sfreg_aon                                                              */
            uint32_t            : 1;
      __IOM uint32_t pu_xtal_buf_aon : 1;       /*!< pu_xtal_buf_aon                                                           */
      __IOM uint32_t pu_xtal_aon : 1;           /*!< pu_xtal_aon                                                               */
            uint32_t            : 2;
      __IOM uint32_t ldo15rf_sstart_sel_aon : 1;/*!< ldo15rf_sstart_sel_aon                                                    */
      __IOM uint32_t ldo15rf_sstart_delay_aon : 2;/*!< ldo15rf_sstart_delay_aon                                                */
            uint32_t            : 1;
      __IOM uint32_t ldo15rf_pulldown_aon : 1;  /*!< ldo15rf_pulldown_aon                                                      */
      __IOM uint32_t ldo15rf_pulldown_sel_aon : 1;/*!< ldo15rf_pulldown_sel_aon                                                */
            uint32_t            : 2;
      __IOM uint32_t ldo15rf_vout_sel_aon : 3;  /*!< ldo15rf_vout_sel_aon                                                      */
            uint32_t            : 5;
      __IOM uint32_t ldo15rf_cc_aon : 2;        /*!< ldo15rf_cc_aon                                                            */
            uint32_t            : 2;
      __IOM uint32_t ldo15rf_bypass_aon : 1;    /*!< ldo15rf_bypass_aon                                                        */
            uint32_t            : 3;
    } bit;
  } rf_top_aon;
  
  union {
    __IOM uint32_t reg;                         /*!< xtal_cfg.                                                                 */
    
    struct {
      __IOM uint32_t xtal_bk_aon : 2;           /*!< xtal_bk_aon                                                               */
      __IOM uint32_t xtal_capcode_extra_aon : 1;/*!< xtal_capcode_extra_aon                                                    */
      __IOM uint32_t xtal_ext_sel_aon : 1;      /*!< xtal_ext_sel_aon                                                          */
      __IOM uint32_t xtal_buf_en_aon : 4;       /*!< xtal_buf_en_aon                                                           */
      __IOM uint32_t xtal_buf_hp_aon : 4;       /*!< xtal_buf_hp_aon                                                           */
      __IOM uint32_t xtal_fast_startup_aon : 1; /*!< xtal_fast_startup_aon                                                     */
      __IOM uint32_t xtal_sleep_aon : 1;        /*!< xtal_sleep_aon                                                            */
      __IOM uint32_t xtal_amp_ctrl_aon : 2;     /*!< xtal_amp_ctrl_aon                                                         */
      __IOM uint32_t xtal_capcode_out_aon : 6;  /*!< xtal_capcode_out_aon                                                      */
      __IOM uint32_t xtal_capcode_in_aon : 6;   /*!< xtal_capcode_in_aon                                                       */
      __IOM uint32_t xtal_gm_boost_aon : 2;     /*!< xtal_gm_boost_aon                                                         */
      __IOM uint32_t xtal_rdy_sel_aon : 2;      /*!< xtal_rdy_sel_aon                                                          */
    } bit;
  } xtal_cfg;
  
  union {
    __IOM uint32_t reg;                         /*!< tsen.                                                                     */
    
    struct {
      __IOM uint32_t tsen_refcode_corner : 12;  /*!< tsen_refcode_corner                                                       */
            uint32_t            : 4;
      __IOM uint32_t tsen_refcode_rfcal : 12;   /*!< tsen_refcode_rfcal                                                        */
      __IOM uint32_t xtal_rdy   : 1;            /*!< xtal_rdy                                                                  */
      __IOM uint32_t xtal_inn_cfg_en_aon : 1;   /*!< xtal_inn_cfg_en_aon                                                       */
      __IOM uint32_t xtal_rdy_int_sel_aon : 2;  /*!< xtal_rdy_int_sel_aon                                                      */
    } bit;
  } tsen;
  __IM  uint32_t  RESERVED3[29];
  
  union {
    __IOM uint32_t reg;                         /*!< acomp0_ctrl.                                                              */
    
    struct {
      __IOM uint32_t acomp0_en  : 1;            /*!< acomp0_en                                                                 */
            uint32_t            : 3;
      __IOM uint32_t acomp0_hyst_seln : 3;      /*!< acomp0_hyst_seln                                                          */
      __IOM uint32_t acomp0_hyst_selp : 3;      /*!< acomp0_hyst_selp                                                          */
      __IOM uint32_t acomp0_bias_prog : 2;      /*!< acomp0_bias_prog                                                          */
      __IOM uint32_t acomp0_level_sel : 6;      /*!< acomp0_level_sel                                                          */
      __IOM uint32_t acomp0_neg_sel : 4;        /*!< acomp0_neg_sel                                                            */
      __IOM uint32_t acomp0_pos_sel : 4;        /*!< acomp0_pos_sel                                                            */
      __IOM uint32_t acomp0_muxen : 1;          /*!< acomp0_muxen                                                              */
            uint32_t            : 5;
    } bit;
  } acomp0_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< acomp1_ctrl.                                                              */
    
    struct {
      __IOM uint32_t acomp1_en  : 1;            /*!< acomp1_en                                                                 */
            uint32_t            : 3;
      __IOM uint32_t acomp1_hyst_seln : 3;      /*!< acomp1_hyst_seln                                                          */
      __IOM uint32_t acomp1_hyst_selp : 3;      /*!< acomp1_hyst_selp                                                          */
      __IOM uint32_t acomp1_bias_prog : 2;      /*!< acomp1_bias_prog                                                          */
      __IOM uint32_t acomp1_level_sel : 6;      /*!< acomp1_level_sel                                                          */
      __IOM uint32_t acomp1_neg_sel : 4;        /*!< acomp1_neg_sel                                                            */
      __IOM uint32_t acomp1_pos_sel : 4;        /*!< acomp1_pos_sel                                                            */
      __IOM uint32_t acomp1_muxen : 1;          /*!< acomp1_muxen                                                              */
            uint32_t            : 5;
    } bit;
  } acomp1_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< acomp_ctrl.                                                               */
    
    struct {
      __IOM uint32_t acomp1_rstn_ana : 1;       /*!< acomp1_rstn_ana                                                           */
      __IOM uint32_t acomp0_rstn_ana : 1;       /*!< acomp0_rstn_ana                                                           */
            uint32_t            : 6;
      __IOM uint32_t acomp1_test_en : 1;        /*!< acomp1_test_en                                                            */
      __IOM uint32_t acomp0_test_en : 1;        /*!< acomp0_test_en                                                            */
      __IOM uint32_t acomp1_test_sel : 2;       /*!< acomp1_test_sel                                                           */
      __IOM uint32_t acomp0_test_sel : 2;       /*!< acomp0_test_sel                                                           */
            uint32_t            : 3;
      __IOM uint32_t acomp1_out_raw : 1;        /*!< acomp1_out_raw                                                            */
            uint32_t            : 1;
      __IOM uint32_t acomp0_out_raw : 1;        /*!< acomp0_out_raw                                                            */
            uint32_t            : 4;
      __IOM uint32_t acomp_reserved : 8;        /*!< acomp_reserved                                                            */
    } bit;
  } acomp_ctrl;
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_reg_cmd.                                                            */
    
    struct {
      __IOM uint32_t gpadc_global_en : 1;       /*!< gpadc_global_en                                                           */
      __IOM uint32_t gpadc_conv_start : 1;      /*!< gpadc_conv_start                                                          */
      __IOM uint32_t gpadc_soft_rst : 1;        /*!< gpadc_soft_rst                                                            */
      __IOM uint32_t gpadc_neg_sel : 5;         /*!< gpadc_neg_sel                                                             */
      __IOM uint32_t gpadc_pos_sel : 5;         /*!< gpadc_pos_sel                                                             */
      __IOM uint32_t gpadc_neg_gnd : 1;         /*!< gpadc_neg_gnd                                                             */
      __IOM uint32_t gpadc_micbias_en : 1;      /*!< gpadc_micbias_en                                                          */
      __IOM uint32_t gpadc_micpga_en : 1;       /*!< gpadc_micpga_en                                                           */
      __IOM uint32_t gpadc_byp_micboost : 1;    /*!< gpadc_byp_micboost                                                        */
            uint32_t            : 1;
      __IOM uint32_t gpadc_dwa_en : 1;          /*!< gpadc_dwa_en                                                              */
      __IOM uint32_t gpadc_mic2_diff : 1;       /*!< gpadc_mic2_diff                                                           */
      __IOM uint32_t gpadc_mic1_diff : 1;       /*!< gpadc_mic1_diff                                                           */
      __IOM uint32_t gpadc_mic_pga2_gain : 2;   /*!< gpadc_mic_pga2_gain                                                       */
      __IOM uint32_t gpadc_micboost_32db_en : 1;/*!< gpadc_micboost_32db_en                                                    */
            uint32_t            : 3;
      __IOM uint32_t gpadc_chip_sen_pu : 1;     /*!< gpadc_chip_sen_pu                                                         */
      __IOM uint32_t gpadc_sen_sel : 2;         /*!< gpadc_sen_sel                                                             */
      __IOM uint32_t gpadc_sen_test_en : 1;     /*!< gpadc_sen_test_en                                                         */
            uint32_t            : 1;
    } bit;
  } gpadc_reg_cmd;
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_reg_config1.                                                        */
    
    struct {
      __IOM uint32_t gpadc_cal_os_en : 1;       /*!< gpadc_cal_os_en                                                           */
      __IOM uint32_t gpadc_cont_conv_en : 1;    /*!< gpadc_cont_conv_en                                                        */
      __IOM uint32_t gpadc_res_sel : 3;         /*!< gpadc_res_sel                                                             */
            uint32_t            : 12;
      __IOM uint32_t gpadc_clk_ana_inv : 1;     /*!< gpadc_clk_ana_inv                                                         */
      __IOM uint32_t gpadc_clk_div_ratio : 3;   /*!< gpadc_clk_div_ratio                                                       */
      __IOM uint32_t gpadc_scan_length : 4;     /*!< gpadc_scan_length                                                         */
      __IOM uint32_t gpadc_scan_en : 1;         /*!< gpadc_scan_en                                                             */
      __IOM uint32_t gpadc_dither_en : 1;       /*!< gpadc_dither_en                                                           */
      __IOM uint32_t gpadc_v11_sel : 2;         /*!< gpadc_v11_sel                                                             */
      __IOM uint32_t gpadc_v18_sel : 2;         /*!< gpadc_v18_sel                                                             */
            uint32_t            : 1;
    } bit;
  } gpadc_reg_config1;
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_reg_config2.                                                        */
    
    struct {
            uint32_t            : 2;
      __IOM uint32_t gpadc_diff_mode : 1;       /*!< gpadc_diff_mode                                                           */
      __IOM uint32_t gpadc_vref_sel : 1;        /*!< gpadc_vref_sel                                                            */
      __IOM uint32_t gpadc_vbat_en : 1;         /*!< gpadc_vbat_en                                                             */
      __IOM uint32_t gpadc_tsext_sel : 1;       /*!< gpadc_tsext_sel                                                           */
      __IOM uint32_t gpadc_ts_en : 1;           /*!< gpadc_ts_en                                                               */
      __IOM uint32_t gpadc_pga_vcm : 2;         /*!< gpadc_pga_vcm                                                             */
      __IOM uint32_t gpadc_pga_os_cal : 4;      /*!< gpadc_pga_os_cal                                                          */
      __IOM uint32_t gpadc_pga_en : 1;          /*!< gpadc_pga_en                                                              */
      __IOM uint32_t gpadc_pga_vcmi_en : 1;     /*!< gpadc_pga_vcmi_en                                                         */
      __IOM uint32_t gpadc_chop_mode : 2;       /*!< gpadc_chop_mode                                                           */
      __IOM uint32_t gpadc_bias_sel : 1;        /*!< gpadc_bias_sel                                                            */
      __IOM uint32_t gpadc_test_en : 1;         /*!< gpadc_test_en                                                             */
      __IOM uint32_t gpadc_test_sel : 3;        /*!< gpadc_test_sel                                                            */
      __IOM uint32_t gpadc_pga2_gain : 3;       /*!< gpadc_pga2_gain                                                           */
      __IOM uint32_t gpadc_pga1_gain : 3;       /*!< gpadc_pga1_gain                                                           */
      __IOM uint32_t gpadc_dly_sel : 3;         /*!< gpadc_dly_sel                                                             */
      __IOM uint32_t gpadc_tsvbe_low : 1;       /*!< gpadc_tsvbe_low                                                           */
    } bit;
  } gpadc_reg_config2;
  
  union {
    __IOM uint32_t reg;                         /*!< adc converation sequence 1                                                */
    
    struct {
      __IOM uint32_t gpadc_scan_pos_0 : 5;      /*!< gpadc_scan_pos_0                                                          */
      __IOM uint32_t gpadc_scan_pos_1 : 5;      /*!< gpadc_scan_pos_1                                                          */
      __IOM uint32_t gpadc_scan_pos_2 : 5;      /*!< gpadc_scan_pos_2                                                          */
      __IOM uint32_t gpadc_scan_pos_3 : 5;      /*!< gpadc_scan_pos_3                                                          */
      __IOM uint32_t gpadc_scan_pos_4 : 5;      /*!< gpadc_scan_pos_4                                                          */
      __IOM uint32_t gpadc_scan_pos_5 : 5;      /*!< gpadc_scan_pos_5                                                          */
            uint32_t            : 2;
    } bit;
  } gpadc_reg_scn_pos1;
  
  union {
    __IOM uint32_t reg;                         /*!< adc converation sequence 2                                                */
    
    struct {
      __IOM uint32_t gpadc_scan_pos_6 : 5;      /*!< gpadc_scan_pos_6                                                          */
      __IOM uint32_t gpadc_scan_pos_7 : 5;      /*!< gpadc_scan_pos_7                                                          */
      __IOM uint32_t gpadc_scan_pos_8 : 5;      /*!< gpadc_scan_pos_8                                                          */
      __IOM uint32_t gpadc_scan_pos_9 : 5;      /*!< gpadc_scan_pos_9                                                          */
      __IOM uint32_t gpadc_scan_pos_10 : 5;     /*!< gpadc_scan_pos_10                                                         */
      __IOM uint32_t gpadc_scan_pos_11 : 5;     /*!< gpadc_scan_pos_11                                                         */
            uint32_t            : 2;
    } bit;
  } gpadc_reg_scn_pos2;
  
  union {
    __IOM uint32_t reg;                         /*!< adc converation sequence 3                                                */
    
    struct {
      __IOM uint32_t gpadc_scan_neg_0 : 5;      /*!< gpadc_scan_neg_0                                                          */
      __IOM uint32_t gpadc_scan_neg_1 : 5;      /*!< gpadc_scan_neg_1                                                          */
      __IOM uint32_t gpadc_scan_neg_2 : 5;      /*!< gpadc_scan_neg_2                                                          */
      __IOM uint32_t gpadc_scan_neg_3 : 5;      /*!< gpadc_scan_neg_3                                                          */
      __IOM uint32_t gpadc_scan_neg_4 : 5;      /*!< gpadc_scan_neg_4                                                          */
      __IOM uint32_t gpadc_scan_neg_5 : 5;      /*!< gpadc_scan_neg_5                                                          */
            uint32_t            : 2;
    } bit;
  } gpadc_reg_scn_neg1;
  
  union {
    __IOM uint32_t reg;                         /*!< adc converation sequence 4                                                */
    
    struct {
      __IOM uint32_t gpadc_scan_neg_6 : 5;      /*!< gpadc_scan_neg_6                                                          */
      __IOM uint32_t gpadc_scan_neg_7 : 5;      /*!< gpadc_scan_neg_7                                                          */
      __IOM uint32_t gpadc_scan_neg_8 : 5;      /*!< gpadc_scan_neg_8                                                          */
      __IOM uint32_t gpadc_scan_neg_9 : 5;      /*!< gpadc_scan_neg_9                                                          */
      __IOM uint32_t gpadc_scan_neg_10 : 5;     /*!< gpadc_scan_neg_10                                                         */
      __IOM uint32_t gpadc_scan_neg_11 : 5;     /*!< gpadc_scan_neg_11                                                         */
            uint32_t            : 2;
    } bit;
  } gpadc_reg_scn_neg2;
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_reg_status.                                                         */
    
    struct {
      __IOM uint32_t gpadc_data_rdy : 1;        /*!< gpadc_data_rdy                                                            */
            uint32_t            : 15;
      __IOM uint32_t gpadc_reserved : 16;       /*!< gpadc_reserved                                                            */
    } bit;
  } gpadc_reg_status;
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_reg_isr.                                                            */
    
    struct {
      __IOM uint32_t gpadc_neg_satur : 1;       /*!< gpadc_neg_satur                                                           */
      __IOM uint32_t gpadc_pos_satur : 1;       /*!< gpadc_pos_satur                                                           */
            uint32_t            : 2;
      __IOM uint32_t gpadc_neg_satur_clr : 1;   /*!< gpadc_neg_satur_clr                                                       */
      __IOM uint32_t gpadc_pos_satur_clr : 1;   /*!< gpadc_pos_satur_clr                                                       */
            uint32_t            : 2;
      __IOM uint32_t gpadc_neg_satur_mask : 1;  /*!< gpadc_neg_satur_mask                                                      */
      __IOM uint32_t gpadc_pos_satur_mask : 1;  /*!< gpadc_pos_satur_mask                                                      */
            uint32_t            : 22;
    } bit;
  } gpadc_reg_isr;
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_reg_result.                                                         */
    
    struct {
      __IOM uint32_t gpadc_data_out : 26;       /*!< gpadc_data_out                                                            */
            uint32_t            : 6;
    } bit;
  } gpadc_reg_result;
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_reg_raw_result.                                                     */
    
    struct {
      __IOM uint32_t gpadc_raw_data : 12;       /*!< gpadc_raw_data                                                            */
            uint32_t            : 20;
    } bit;
  } gpadc_reg_raw_result;
  
  union {
    __IOM uint32_t reg;                         /*!< gpadc_reg_define.                                                         */
    
    struct {
      __IOM uint32_t gpadc_os_cal_data : 16;    /*!< gpadc_os_cal_data                                                         */
            uint32_t            : 16;
    } bit;
  } gpadc_reg_define;
  
  union {
    __IOM uint32_t reg;                         /*!< hbncore_resv0.                                                            */
    
    struct {
      __IOM uint32_t hbncore_resv0_data : 32;   /*!< hbncore_resv0_data                                                        */
    } bit;
  } hbncore_resv0;
  
  union {
    __IOM uint32_t reg;                         /*!< hbncore_resv1.                                                            */
    
    struct {
      __IOM uint32_t hbncore_resv1_data : 32;   /*!< hbncore_resv1_data                                                        */
    } bit;
  } hbncore_resv1;
} AON_Type;                                     /*!< Size = 2372 (0x944)                                                       */


/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define glb_BASE                    0x40000000UL
#define rf_BASE                     0x40001000UL
#define gpip_BASE                   0x40002000UL
#define sec_dbg_BASE                0x40003000UL
#define sec_eng_BASE                0x40004000UL
#define tzc_sec_BASE                0x40005000UL
#define tzc_nsec_BASE               0x40006000UL
#define ef_data_0_BASE              0x40007000UL
#define ef_data_1_BASE              0x40007000UL
#define ef_ctrl_BASE                0x40007000UL
#define cci_BASE                    0x40008000UL
#define l1c_BASE                    0x40009000UL
#define uart_BASE                   0x4000A000UL
#define spi_BASE                    0x4000A200UL
#define i2c_BASE                    0x4000A300UL
#define pwm_BASE                    0x4000A400UL
#define timer_BASE                  0x4000A500UL
#define ir_BASE                     0x4000A600UL
#define cks_BASE                    0x4000A000UL
#define sf_ctrl_BASE                0x4000B000UL
#define dma_BASE                    0x4000C000UL
#define pds_BASE                    0x4000E000UL
#define HBN_BASE                    0x4000F000UL
#define AON_BASE                    0x4000F800UL

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define glb                         ((glb_Type*)               glb_BASE)
#define rf                          ((rf_Type*)                rf_BASE)
#define gpip                        ((gpip_Type*)              gpip_BASE)
#define sec_dbg                     ((sec_dbg_Type*)           sec_dbg_BASE)
#define sec_eng                     ((sec_eng_Type*)           sec_eng_BASE)
#define tzc_sec                     ((tzc_sec_Type*)           tzc_sec_BASE)
#define tzc_nsec                    ((tzc_nsec_Type*)          tzc_nsec_BASE)
#define ef_data_0                   ((ef_data_0_Type*)         ef_data_0_BASE)
#define ef_data_1                   ((ef_data_1_Type*)         ef_data_1_BASE)
#define ef_ctrl                     ((ef_ctrl_Type*)           ef_ctrl_BASE)
#define cci                         ((cci_Type*)               cci_BASE)
#define l1c                         ((l1c_Type*)               l1c_BASE)
#define uart                        ((uart_Type*)              uart_BASE)
#define spi                         ((spi_Type*)               spi_BASE)
#define i2c                         ((i2c_Type*)               i2c_BASE)
#define pwm                         ((pwm_Type*)               pwm_BASE)
#define timer                       ((timer_Type*)             timer_BASE)
#define ir                          ((ir_Type*)                ir_BASE)
#define cks                         ((cks_Type*)               cks_BASE)
#define sf_ctrl                     ((sf_ctrl_Type*)           sf_ctrl_BASE)
#define dma                         ((dma_Type*)               dma_BASE)
#define pds                         ((pds_Type*)               pds_BASE)
#define HBN                         ((HBN_Type*)               HBN_BASE)
#define AON                         ((AON_Type*)               AON_BASE)


#ifdef __cplusplus
}
#endif

#endif /* BL602_H */
