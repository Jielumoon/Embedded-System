/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   中断服务例程实现
  *          - NMI / HardFault 等故障处理进入死循环
  *          - SysTick_Handler() 必须调用 HAL_IncTick() 驱动系统全局时基 uwTick
  ******************************************************************************
  */
#include "main.h"
#include "stm32f4xx_it.h"

/* ============================== 故障处理 ============================== */
void NMI_Handler(void)
{
    while (1U)
    {
    }
}

void HardFault_Handler(void)
{
    while (1U)
    {
    }
}

void MemManage_Handler(void)
{
    while (1U)
    {
    }
}

void BusFault_Handler(void)
{
    while (1U)
    {
    }
}

void UsageFault_Handler(void)
{
    while (1U)
    {
    }
}

/* ============================ 未使用异常 ============================= */
void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

/* ========================= 系统时基 (关键!) ========================== */
void SysTick_Handler(void)
{
    /* 必须调用: 否则 uwTick 恒为 0, HAL_Delay() 将死循环 */
    HAL_IncTick();
}
