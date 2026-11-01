/**
  ******************************************************************************
  * @file    main.c
  * @brief   lab2_1: 180 MHz 时钟系统与最小 CMake 工程
  *          - 手工配置 HSE 25MHz + PLL: M=25 N=360 P=2 => SYSCLK 180 MHz
  *          - Over-Drive 超频模式 + Flash 5 等待周期
  *          - LED1(PB1) 低电平点亮, 500ms 交替闪烁验证系统运行
  *          验证: HAL_RCC_GetSysClockFreq() 应返回 180000000
  ******************************************************************************
  */
#include "main.h"

static void SystemClock_Config(void);
static void MX_GPIO_Init(void);

int main(void)
{
    /* 复位所有外设, 初始化 Flash 接口与 SysTick */
    HAL_Init();

    /* 配置系统时钟: 180 MHz */
    SystemClock_Config();

    /* 初始化 GPIO: LED1 = PB1 推挽输出 */
    MX_GPIO_Init();

    while (1U)
    {
        /* LED1 低电平点亮 500ms, 熄灭 500ms 交替 */
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
        HAL_Delay(500U);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
        HAL_Delay(500U);
    }
}

/**
  * @brief  系统时钟配置: HSE 25MHz -> PLL(25/360/2) -> SYSCLK 180MHz
  *         - AHB 不分频: 180 MHz
  *         - APB1 四分频: 45 MHz
  *         - APB2 二分频: 90 MHz
  *         - 使能 Over-Drive 模式, Flash 5 等待周期
  */
static void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /* 使能 PWR 时钟, 电压等级 Scale1 (180MHz 需要) */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* HSE 25MHz, PLL: M=25, N=360, P=2 => VCO=360MHz, SYSCLK=180MHz */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25U;
    RCC_OscInitStruct.PLL.PLLN = 360U;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 8U;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /* 进入 Over-Drive 模式 (高频运行必须) */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        Error_Handler();
    }

    /* 时钟树: SYSCLK=PLL, AHB=1分频, APB1=4分频, APB2=2分频, Flash 5WS */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
  * @brief GPIO 初始化: LED1 = PB1 推挽输出 (低电平点亮)
  */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* 初始状态: 熄灭 */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
}

/**
  * @brief 错误处理: 卡死 (可由 GDB 挂接定位)
  */
void Error_Handler(void)
{
    __disable_irq();
    while (1U)
    {
    }
}
