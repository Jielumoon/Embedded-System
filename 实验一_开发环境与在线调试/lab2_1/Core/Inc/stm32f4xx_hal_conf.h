/**
  ******************************************************************************
  * @file    stm32f4xx_hal_conf.h
  * @brief   HAL 配置头文件: 通过宏开关定制 HAL 库编译范围
  *          - 板载外部晶振: 25 MHz (HSE_VALUE)
  *          - 仅使能本实验需要的外设模块 (GPIO / RCC / FLASH / PWR / CORTEX)
  ******************************************************************************
  */

#ifndef __STM32F4xx_HAL_CONF_H
#define __STM32F4xx_HAL_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* ---------------------------- 器件头文件 -------------------------------- */
#include "stm32f4xx.h"   /* HAL_StatusTypeDef / uint32_t 等类型定义 */

/* ---------------------------- 晶振与时钟频率 ---------------------------- */
#define HSE_VALUE            ((uint32_t)25000000U)  /*!< 板载 25 MHz 外部晶振 */
#define LSE_VALUE            ((uint32_t)32768U)     /*!< 32.768 kHz 低速外部晶振 */
#define EXTERNAL_CLOCK_VALUE ((uint32_t)8000000U)   /*!< 外部时钟输入 */
#define HSI_VALUE            ((uint32_t)16000000U)  /*!< 16 MHz 内部高速 RC 振荡器 */
#define LSI_VALUE            ((uint32_t)32000U)     /*!< 32 kHz 内部低速 RC 振荡器 */

/* 起振超时 (ms) */
#define HSE_STARTUP_TIMEOUT  ((uint32_t)100U)
#define LSE_STARTUP_TIMEOUT  ((uint32_t)5000U)

/* ------------------------------ 模块裁剪宏 ------------------------------ */
#define HAL_MODULE_ENABLED

#define HAL_GPIO_MODULE_ENABLED
#define HAL_RCC_MODULE_ENABLED
#define HAL_FLASH_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED
#define HAL_CORTEX_MODULE_ENABLED

/* 本实验未使用的外设模块: 全部注释关闭, 遵循最小必要原则 */

/* ---------------------------- HAL 系统配置 ------------------------------ */
#define  VDD_VALUE                   ((uint32_t)3300U)
#define  TICK_INT_PRIORITY           ((uint32_t)0U)
#define  USE_RTOS                    0U
#define  PREFETCH_ENABLE             1U
#define  INSTRUCTION_CACHE_ENABLE    1U
#define  DATA_CACHE_ENABLE           1U

#define  USE_HAL_ADC_REGISTER_CALLBACKS   0U
#define  USE_HAL_CAN_REGISTER_CALLBACKS   0U
#define  USE_HAL_CEC_REGISTER_CALLBACKS   0U
#define  USE_HAL_CRYP_REGISTER_CALLBACKS  0U
#define  USE_HAL_DAC_REGISTER_CALLBACKS   0U
#define  USE_HAL_DCMI_REGISTER_CALLBACKS  0U
#define  USE_HAL_DFSDM_REGISTER_CALLBACKS 0U
#define  USE_HAL_DMA_REGISTER_CALLBACKS   0U
#define  USE_HAL_DMA2D_REGISTER_CALLBACKS 0U
#define  USE_HAL_ETH_REGISTER_CALLBACKS   0U
#define  USE_HAL_EXTI_REGISTER_CALLBACKS  0U
#define  USE_HAL_FMC_REGISTER_CALLBACKS   0U
#define  USE_HAL_HASH_REGISTER_CALLBACKS  0U
#define  USE_HAL_I2C_REGISTER_CALLBACKS   0U
#define  USE_HAL_I2S_REGISTER_CALLBACKS   0U
#define  USE_HAL_IWDG_REGISTER_CALLBACKS  0U
#define  USE_HAL_LPTIM_REGISTER_CALLBACKS 0U
#define  USE_HAL_LTDC_REGISTER_CALLBACKS  0U
#define  USE_HAL_MMC_REGISTER_CALLBACKS   0U
#define  USE_HAL_NAND_REGISTER_CALLBACKS  0U
#define  USE_HAL_NOR_REGISTER_CALLBACKS   0U
#define  USE_HAL_PCCARD_REGISTER_CALLBACKS 0U
#define  USE_HAL_PCD_REGISTER_CALLBACKS   0U
#define  USE_HAL_QSPI_REGISTER_CALLBACKS  0U
#define  USE_HAL_RNG_REGISTER_CALLBACKS   0U
#define  USE_HAL_RTC_REGISTER_CALLBACKS   0U
#define  USE_HAL_SAI_REGISTER_CALLBACKS   0U
#define  USE_HAL_SD_REGISTER_CALLBACKS    0U
#define  USE_HAL_SDRAM_REGISTER_CALLBACKS 0U
#define  USE_HAL_SMARTCARD_REGISTER_CALLBACKS 0U
#define  USE_HAL_SPI_REGISTER_CALLBACKS   0U
#define  USE_HAL_SRAM_REGISTER_CALLBACKS  0U
#define  USE_HAL_TIM_REGISTER_CALLBACKS   0U
#define  USE_HAL_UART_REGISTER_CALLBACKS  0U
#define  USE_HAL_USART_REGISTER_CALLBACKS 0U
#define  USE_HAL_WWDG_REGISTER_CALLBACKS  0U

/* ---------------------------- 断言宏 (默认空) --------------------------- */
#ifdef  USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0U : assert_failed((uint8_t *)__FILE__, __LINE__))
void assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

/* ---------------------------- 模块头文件包含 ---------------------------- */
/* 各模块头文件内部会再包含 stm32f4xx_hal_def.h (HAL_StatusTypeDef / HAL_OK 等) */
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_rcc_ex.h"
#include "stm32f4xx_hal_flash.h"
#include "stm32f4xx_hal_flash_ex.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_exti.h"
#include "stm32f4xx_hal_pwr.h"
#include "stm32f4xx_hal_pwr_ex.h"
#include "stm32f4xx_hal_cortex.h"

#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_CONF_H */
