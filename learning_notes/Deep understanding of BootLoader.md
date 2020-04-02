# Deep Understanding of BootLoader

## Chapter 1 BootLoader的概念

### 1.1 BootLoader的角色

	1.BootLoader提供最初的初始化代码(初始化代码由处理器体系结构下的汇编语言写成),初始化单板;
	2.BootLoader完成基本的处理器和平台的初始化之后,开始引导操作系统.主要是定位、加载操作系统,并将控制权
		转交给操作系统.

### 1.2 BootLoader的来历

BootLoader=Boot(引导)+Loader(加载器).

Boot是BootStrap(鞋带)的缩写,来源于一句谚语"Pull oneself up by one's own bootstraps"(拖着鞋带把自己拉起来).因为早期计算机存在一个问题:

	必须先运行成,计算机才能启动;但是计算机不启动就无法运行程序.后来人们想到办法将一段小程序装进内存,之后
	计算机就能正常运行了.

**1.存储技术**

1.ROM(Read only memory)

	根据能否擦除分为:ROM、PROM、EPROM和EEPROM等.

2.RAM(Random access memory)

	根据存储单元的工作原理分为:SRAM(静态随机存储器)和DRAM(动态随机存储器).
	SRAM的存取速度要比DRAM快,但价格高.在计算机中,SRAM常用作cache,DRAM用作内存.

3.Flash memory(闪存)

闪存是一种高密度、非易失性的读/写半导体存储器.既有EEPROM的特点,又有RAM的特点,是一种全新的存储结构.

	Flash主要有两种:Nor Flash(由Intel开发的)和Nand Flash(由东芝开发的).
	1.Nor Flash带有SRAM接口,可通过地址进行存寻址,可以容易的存取内部的每一个字节,可以XIP(片内执行),即应
		用程序可以直接在Nor Flash内运行;
	2.Nand Flash使用复杂的I/O来串行存取数据,读写操作都是块操作,无法做到XIP;
	3.Nor Flash的读取速度比Nand Flash稍快,但写入速度慢很多;
	4.Nand Flash的存储密度比Nor Flash更高,成本更低;
	5.很多嵌入式单板使用小容量的Nor Flash来运行启动代码,使用Nand Flash存储其他信息.

### 1.3 BootLoader的概念

不同体系下的BootLoader.

![](images/bootload_under_different_architecture.png)

**1.PC的引导流程**

![](images/loader_flow_of_pc.png)

## Chapter 2 Linux开发环境

