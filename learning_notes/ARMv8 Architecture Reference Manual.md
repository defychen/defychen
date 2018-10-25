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


