# 嵌入式系统与应用 · 实验一

**实验名称：** STM32F429 开发环境搭建、命令行构建与在线调试

## 一、实验内容

- 交叉编译工具链版本核验；
- 使用 CMake + Ninja 构建 Debug / Release 固件；
- 使用 OpenOCD 烧录、GDB 远程在线调试；
- 对比 Debug 与 Release 固件体积；
- 使用 VS Code + clangd 配置图形化开发环境；
- 通过 GDB 观察 GPIOB 的 MODER / ODR 寄存器随 LED1 翻转。

## 二、目录结构

```text
Embedded-System\
├─ README.md
├─ .gitignore
├─ 实验一_开发环境与在线调试\
│  ├─ lab2_1\                         # 完整 STM32F429 工程
│  └─ 上板操作手册.md
└─ 预编译固件\
   ├─ 实验一_lab2_1.bin               # Debug，5996 字节
   └─ 实验一_lab2_1.hex
```

## 三、构建与烧录

在 PowerShell 中执行：

```powershell
cd '.\实验一_开发环境与在线调试\lab2_1'

cmake --preset debug
cmake --build --preset debug

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg `
  -c "program build/Debug/lab2_1.bin 0x08000000 verify reset exit"
```

Release 构建：

```powershell
cmake --preset release
cmake --build --preset release
```

## 四、验收现象

开发板上电后，LED1（PB1，低电平点亮）以 **1 Hz** 稳定闪烁：

- 亮 500 ms；
- 灭 500 ms。

实测 Debug 固件 5996 字节，Release 固件 4376 字节，Release 比 Debug 小约 27%。

## 五、链接脚本修复说明

首次烧录后 LED1 不闪，定位到 `STM32F429XX_FLASH.ld` 的两处问题：

1. F429 主 SRAM 只有 192 KB（64 KB CCM 位于 `0x10000000`），原脚本把 `0x20000000` 处写成 256 KB，导致初始栈顶 `_estack = 0x20040000` 越界。已改为 `LENGTH = 192K`，栈顶为 `0x20030000`。
2. 链接使用 `--gc-sections`，但 `.text` 未 `KEEP(.init/.fini)`，`crtn.o` 的收尾代码被删除，`_init` 只有压栈没有出栈，`__libc_init_array` 无法返回。已加入 `KEEP(*(.init))` / `KEEP(*(.fini))`，并补齐 `.preinit_array` / `.init_array` / `.fini_array` 段。

修复后重新构建、烧录，LED1 恢复正常 1 Hz 闪烁。

## 六、公开内容与隐私

本仓库仅公开工程代码、构建配置、技术说明和示例固件。实验报告及其截图仅在本地保存，不纳入版本控制。

提交前请检查文件内容、文件名和 Git 提交者信息，避免包含姓名、学号、班级、邮箱、本机用户名或绝对路径。不要强制添加已被忽略的报告、截图和个人资料。
