# Assembly Instructions

板子的启动流程:

	----------------------------------------------------------------
		step 1				Bootrom		
		1)固化在硬件中,一上电就跳到Bootrom执行
		2)在板子的rom空间中执行,rom可以直接执行代码
		3)初始化CPU的SRAM(准备loader Auxcode)
	----------------------------------------------------------------
		step 2				Auxcode
		1)初始化DDR
		2)引导bootloader
		3)在CPU的SRAM中执行
	----------------------------------------------------------------
		step 3				bootloader
		1)引导kernel(或其他OS)
		2)在DDR中执行
	----------------------------------------------------------------
# ARM

## Auxcode中的boot.S---适配CortexA7(CA7)

	#define SP_MAX_SIZE		(1024*5)	/*堆大小为5K*/
	#define MONITOR_SP		(1024*1)	/*monitor 堆大小为1K*/

		.globl	sm_vect_table	/*.globl/.global symbol:声明后面的symbol(sm_vect_table)是全局可见的.*/
								/*.global:使得连接程序(ld)能够识别symbol.也即外部程序可以访问的标签*/
		.func sm_vect_table		/*声明一个函数???*/
	------------------------------------------------------------------------------------------------------
	sm_vect_table:		/*格式"symbol:"仅仅表示一个标号.此处表示sm的向量表,该表由arm硬件架构已经定义好的.*/
		b	_start		/*(reset)芯片reset时的处理,第一条指令.此处表示跳转到标号"_start"处执行*/
		b	.			/*(undefined instruction)未定义指令异常的处理.此处"."表示死循环,跳到自身位置*/
		b	sm_smc_entry	/*(secure monitor call)调用的处理.此处表示跳转到标号"sm_smc_entry"处执行*/
		b	.			/*(Prefetch abort)取指异常的处理.此处"."表示死循环,跳到自身位置*/
		b	.			/*(Data abort)数据访问异常的处理.此处"."表示死循环,跳到自身位置*/
		b	.			/*(Reserved)保留,其他异常的处理.此处"."表示死循环,跳到自身位置*/
		b	.			/*(IRQ)中断处理.此处"."表示死循环,跳到自身位置*/
		b	.			/*(FIQ)快中断处理.此处"."表示死循环,跳到自身位置*/
		.endfunc		/*函数结束???*/

	/*向量表反汇编:
	80000000 <sm_vect_table>:	//标号.8000_0000是在链接时指定的
	<物理地址>	<机器码>	  <指令>	<跳转到的地址><标号助记符>
	80000000:	ea000006 	b	80000020 <_start>	<reset指令,此时跳转到20的位置>
	80000004:	eafffffe 	b	80000004 <sm_vect_table+0x4>	<跳转到自身,表示死循环>
	80000008:	ea000039 	b	800000f4 <sm_smc_entry>	<secure monitor call,此时跳转到f4的位置>
	8000000c:	eafffffe 	b	8000000c <sm_vect_table+0xc>	<跳转到自身,表示死循环>
	80000010:	eafffffe 	b	80000010 <sm_vect_table+0x10>	<跳转到自身,表示死循环>
	80000014:	eafffffe 	b	80000014 <sm_vect_table+0x14>	<跳转到自身,表示死循环>
	80000018:	eafffffe 	b	80000018 <sm_vect_table+0x18>	<跳转到自身,表示死循环>
	8000001c:	eafffffe 	b	8000001c <sm_vect_table+0x1c>	<跳转到自身,表示死循环>
	*/
	------------------------------------------------------------------------------------------------------
	.globl _start	/*标号"_start":是GNU链接器用来指定第一个要执行的指令所必须的,全局可见(并且只能出现在一个模块中).*/
	_start:
		mrc p15, 0, r0, c0, c0, 5	/*mrc:读取协处理器中的寄存器数据到ARM处理器的寄存器中.
										mcr:用于读取ARM处理器的寄存器数据到协处理器的寄存器中.*/
		/*
			p15:协处理器p15.CP15协处理器用于系统存储管理.
			0:协处理器将执行的操作的操作码.对于CP15来说,该操作码永远是"0".
			r0:ARM寄存器.mrc时将作为目标寄存器
			第一个c0:协处理器寄存器.协处理器cp15的c0寄存器存放的是CPU的ID号.
			第二个c0:协处理器的附加寄存器.如果不需要附加信息,则指定为"c0".
			5:操作类型(第二个数(操作码)的附加参数).此处表示类型5.
			该条汇编指令的意思:读取ARM CPU的ID号(处理器版本号)到ARM寄存器r0里面.
		*/
		and r0, r0, #0x3	/*r0 = r0 & 0x3--->[1:0]CPU的ID位.提取ID位,表示几号CPU.*/
		cmp r0, #0			/*比较r0和0是否相等.确定是否是0号CPU*/
		bne run_secondary	/*如果上述的cmp不相等,跳转到"run_secondary"去执行*/
		b   init_start		/*否则就跳转到"init_start"执行*/

	/*反汇编该段代码:
	80000020 <_start>:
	80000020:	ee100fb0 	mrc	15, 0, r0, cr0, cr0, {5}
	80000024:	e2000003 	and	r0, r0, #3
	80000028:	e3500000 	cmp	r0, #0
	8000002c:	1a000000 	bne	80000034 <run_secondary>
	80000030:	ea000001 	b	8000003c <init_start>
	*/
	------------------------------------------------------------------------------------------------------
	run_secondary:
		wfi		/*wfi:wait for interrupt.让ARM核进入low-power standby模式.*/
		b run_secondary		/*死循环*/
	/*反汇编:
	80000034 <run_secondary>:
	80000034:	e320f003 	wfi
	80000038:	eafffffd 	b	80000034 <run_secondary>
	*/

***
# MIPS


asm volatile(".word 0xebfffffe");断点

md 0x1801008c 4