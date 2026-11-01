# ============================================================================
# gcc-arm-none-eabi.cmake
# Arm Cortex-M4F 交叉工具链配置 (arm-none-eabi-gcc >= 10.3)
# 用法: include(cmake/gcc-arm-none-eabi.cmake)
# ============================================================================

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# ---- 工具链可执行文件 ----
set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_OBJCOPY      arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP      arm-none-eabi-objdump)
set(CMAKE_SIZE         arm-none-eabi-size)
set(CMAKE_GDB          arm-none-eabi-gdb)

# ---- 目标 CPU: STM32F429IGT6 基于 Cortex-M4F (ARMv7E-M, 单精度 FPU) ----
set(CPU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# ---- C 编译选项 ----
set(CMAKE_C_FLAGS   "${CPU_FLAGS} -std=gnu11 -Wall -Wextra -fdata-sections -ffunction-sections" CACHE STRING "C flags")
set(CMAKE_CXX_FLAGS "${CPU_FLAGS} -std=gnu++17 -Wall -Wextra -fdata-sections -ffunction-sections" CACHE STRING "CXX flags")
set(CMAKE_ASM_FLAGS "${CPU_FLAGS} -Wall" CACHE STRING "ASM flags")

# ---- 链接选项 (链接脚本由 CMakeLists 传入, 此处仅放 CPU 相关) ----
set(CMAKE_EXE_LINKER_FLAGS "${CPU_FLAGS} -Wl,--gc-sections" CACHE STRING "Linker flags")

# ---- 调试与优化由 CMAKE_BUILD_TYPE 控制 ----
set(CMAKE_C_FLAGS_DEBUG   "${CPU_FLAGS} -O0 -g3 -gdwarf-2" CACHE STRING "")
set(CMAKE_C_FLAGS_RELEASE "${CPU_FLAGS} -O2 -g0" CACHE STRING "")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
