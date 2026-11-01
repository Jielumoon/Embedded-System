# ============================================================================
# lab2_1 : 180 MHz 时钟系统与最小 CMake 工程构建
# STM32F429IGT6 · Cortex-M4F · HSE 25 MHz
# 工程结构: 底层 HAL 源码打包为静态库 hal, 应用层链接生成 lab2_1.elf
# ============================================================================
cmake_minimum_required(VERSION 3.22)

# ---- 引入 Arm 交叉工具链 (必须在 project 之前, 供编译器探测) ----
include(cmake/gcc-arm-none-eabi.cmake)

project(lab2_1 LANGUAGES C ASM)

# ---- 目标名称 ----
set(TARGET lab2_1)

# ---- 全局编译选项 (C11 / MISRA 友好) ----
add_compile_options(
    -DSTM32F429xx
    -DUSE_HAL_DRIVER
    -std=gnu11
    -Wall
    -Wextra
    -fdata-sections
    -ffunction-sections
)

# ============================================================================
# HAL 静态库: 由 Drivers 下的 HAL 源文件打包
# ============================================================================
file(GLOB HAL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c"
)

add_library(hal STATIC ${HAL_SOURCES})

# HAL / CMSIS / 应用头文件搜索路径
target_include_directories(hal PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include"
    "${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc"
)

# ============================================================================
# 可执行文件: 应用 + 系统源码 + 启动文件
# ============================================================================
add_executable(${TARGET}
    Core/Src/main.c
    Core/Src/stm32f4xx_it.c
    Core/Src/system_stm32f4xx.c
    Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f429xx.s
)

target_link_libraries(${TARGET} PRIVATE hal)

# 链接脚本 + 链接选项: 生成 .map, 使用 nano 精简 C 库
target_link_options(${TARGET} PRIVATE
    -T ${CMAKE_CURRENT_SOURCE_DIR}/STM32F429XX_FLASH.ld
    -Wl,-Map=${TARGET}.map
    --specs=nano.specs
    --specs=nosys.specs
    -Wl,--gc-sections
)

# ---- 构建后生成 .bin 与 .hex 方便烧录 ----
add_custom_command(TARGET ${TARGET} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET}> ${TARGET}.bin
    COMMAND ${CMAKE_OBJCOPY} -O ihex  $<TARGET_FILE:${TARGET}> ${TARGET}.hex
    COMMENT "Generate ${TARGET}.bin / ${TARGET}.hex"
)
