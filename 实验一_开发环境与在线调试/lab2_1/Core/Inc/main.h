/**
  ******************************************************************************
  * @file    main.h
  * @brief   主程序头文件: 系统时钟宏与公共声明
  ******************************************************************************
  */
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

/* 系统目标主频: 180 MHz */
#define SYSTEM_CLOCK_180MHZ  180000000U

void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
