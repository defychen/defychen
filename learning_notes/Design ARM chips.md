# Design ARM chips

## Chapter 1 概述---MCU整体项目介绍

## 1.1 MCU参考设计

1.工艺

	40nm technology(工艺)

2.ARM M3 MCU design(设计)

	Gate count: 160K
	Memory: 17个
	ADC: 1个
	PLL: 1个
	PS:always on--->表示不掉电,一直存在(RTC就必须是always on的状态)

3.PADs

	1.30 IO PADs
	2.16 PG(Power ground) PADs

4.主频

	100MHz

5.Die Size

	1.6605mm2

6.Physical DRC clean

7.封装

	当引脚 < 48 pin时,选用QFP封装(引脚分布在芯片四周). --->(百科上说是一般引脚数在100以上)

### 1.2 RTOS

国外主要有:

	mbed OS, Free RTOS

国内主要有:

	RT-Thread, AliOS Things, Huawei Lite OS.

### 1.3 Cortex-M处理器介绍

**1.ARMv7-M系列**

	低端:
		Cortex-M0和Cortex-M0+:采用2级流水线;
	中端:
		Cortex-M3和Cortex-M4:采用3级流水线.M4增加了DSP,支持浮点运算(FPM),s在100MHz左右;
	高端:
		Cortex-M7:6/7级流水线,总线为AXI.性能强.接近Cortex-R系列.在200-4/500MHz.

**2.ARMv8-M系列**

	低端:
		Cortex-M23:在M0的基础上,增加了TrustZone机制.
	中端:
		Cortex-M33:在M3/M4的基础上,增加了TrustZone机制.
	高端:
		暂无.
	PS:TrustZone之前一直用于Cortex-A/Cortex-R系列.因为后面的Cortex-M系列会用于IoT市场,
		因此从ARMv8开始Cortex-M系列增加了TrustZone.

国内做的比较好的MCU厂家是:GigaDevice和MM32 MCU.可以和STM32 pin to pin兼容.

### 1.4 Cortex-M3总线介绍

ICode Bus, DCode Bus, System Bus均为AHB-Lite Bus.

外设(e.g.UART, WDT, I2C, SPI, GPIO, SYS_CTRL)均采用AHB-APB Bus.

### 1.5 MCU的电压介绍

1.IO的电压:采用1.8V.

2.Core/Bus等的电压:1.1V.

3.外设(e.g.ADC, ROM, RAM, PLL)等的电压:2.4V.

### 1.6 MCU的工作时钟域

1.MCU内部(e.g.BOOT_ROM, Flash, SRAM, AHB Bus)工作在96MHz;

2.MCU的外设(e.g.APB, WDT, GPIO, I2C等)工作在48MHz;

3.RTC(特殊的一个IP)工作在1KHz.

***

## Chapter 2 RTL设计




