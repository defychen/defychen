# ARMv8 Architecture Reference Manual

# Part A: ARMv8 Architecture Inctrocution and Overview

## Chapter A1: Introction to the ARMv8 Architecture

### A1.1 Architecture profiles

#### A1.1.1 AArch64和AArch32

AArch64、AArch32分别描述了64-bit和32-bit的执行状态.

	AArch64:是64-bit的执行状态.地址保存在64-bit的寄存器中.基本指令集中的指令可以使用64-bit的
		寄存器进行处理.AArch64支持A64指令集.
	AArch32:是32-bit的执行状态.地址保存在32-bit的寄存器中.基本指令集中的指令可以使用32-bit的
		寄存器进行处理.AArch32支持T32和A32指令集.

#### A1.1.2 ARM的三种系列

	A系列:主要在应用(e.g.手机)场景中.
		1.支持基于MMU的VMSA(Virtual Memory System Architecture:虚拟内存系统体系结构);
		2.支持A64, A32和T32指令集.
	R系列:主要应用在要求实时(Real-time)场景中.
		1.支持基于MPU(Memory Protection Unit:内存保护单元)的PMSA(Protected Memory
			System Architecture:受保护内存系统体系结构);
		2.支持A32和T32指令集.
	M系列:主要应用在微控制器(Microcontroller)场景中.
		1.通过硬件寄存器的堆叠实现了为低延迟中断处理而设计的程序员模型,并且支持用高级语言编写
			中断处理程序.
		2.实现R系列的PMSA的一个变体;
		3.支持T32指令集的一个变体.

### A1.2 ARMv8 architectural concepts(ARMv8架构概念)

#### A1.2.1 执行状态

**1.AArch64**

	1.提供31个64-bit的通用寄存器,其中X30是程序连接寄存器;
	2.提供一个64-bit的程序计数器(PC:program counter),堆栈寄存器(SPs:stack pointers)以及异常
		连接寄存器(ELRs:exception link registers);
	3.提供了32个128-bit的寄存器去支持SIMD矢量和标量浮点;
	4.提供了一个A64指令集;
	5.定义了ARMv8异常模型,最多有4个异常级别,EL0-EL3,它们提供了执行特权层次结构;
	6.提供了对64-bit虚拟地址的支持;
	7.定义了包含PE状态的许多进程状态元素(Process state(PSTATE)).A64指令集包含直接操作各种
		PSTATE元素的指令;
	8.使用一个后缀来命名每个系统寄存器,该后缀暗示可以访问寄存器的最低异常级别.

**2.AArch32**

	1.提供13个32-bit通用寄存器,一个PC,SP和LR寄存器.LR寄存器既用作ELR又用作程序连接寄存器.
		一些寄存器具有多个banked instances(空闲实例?),可用于不同的PE模式;
	2.提供一个ELR,用于从Hyp模式(管理员模式)返回异常;
	3.提供了32个64-bit的寄存器去支持高级的SIMD矢量和标量浮点;
	4.提供2个指令集:A32和T32;
	5.支持基于PE模式的ARMv7-A的异常模型,并基于异常级别将其映射到ARMv8的异常模型;
	6.提供对32-bit虚拟寻址的支持;
	7.定义了包含PE状态的许多进程状态元素(Process state(PSTATE))。A32和T32指令集包括直接操作各种
		PSTATE元素的指令,以及通过使用应用程序状态寄存器(APSR:Application Proram Status Register)
		或当前程序状态寄存器(CPSR:Current Program Status Register)访问PSTATE的指令.

#### A1.2.2 The ARM instruction sets(ARM指令集)

ARMv8的指令取决于执行状态:

	AArch64:AArch64状态仅支持一个名为A64的指令集.A64指令集是一个定长指令集,使用32-bit的指令编码.
	AArch32:AArch32状态支持下面两种指令集:
		A32:A32是一个定长指令集,使用32-bit的指令编码;
		T32:T32是一个可变长的指令集,使用16-bit和32-bit指令编码.

#### A1.2.3 System registers(系统寄存器)

1.系统寄存器的命名

	<register_name>_ELx, x可以取值为0, 1, 2, or 3.

2.系统寄存器组成

	1.通用系统控制寄存器;
	2.调试寄存器;
	3.通用时钟寄存器;
	4.性能监视寄存器(可选);
	5.跟踪寄存器(可选);
	6.GIC(Generic Interrupt Controller:通用中断控制器)CPU接口寄存器(可选).

### A1.3 Supported data types(支持的数据类型)

	Byte			8-bit
	Halfword		16-bit
	Word			32-bit
	Doubleword		64-bit
	Quadword		128-bit

# Part B: The AArch64 Application Level Architecture

## Chapter B1: The AArch64 Application Level Programer's Model

## Chapter B2: The AArch64 Application Level Memory Model

# Part C: The AArch64 Instruction Set

## Chapter C1: The A64 Instruction set

## Chapter C2: About the A64 Instruction Descriptions

## Chapter C3: A64 Instruction Set Overview

## Chapter C4: A64 Instruction Set Encoding

## Chapter C5: The A64 System Instruction Class

## Chapter C6: A64 Base Instruction Descriptions

## Chapter C7: A64 Advanced SIMD and Floating-point Instruction Descriptions

# Part D: The AArch64 System Level Architecture

## Chapter D1: The AArch64 System Level Programmer's Model


