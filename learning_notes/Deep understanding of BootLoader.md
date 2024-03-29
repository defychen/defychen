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

***

## Chapter 2 Linux开发环境

### 2.1 编辑器Vim

#### 2.1.1 Vim的两种基本模式

1.Normal模式:进入Vim后默认处于Normal模式.

2.Insert模式:输入a/A/i/I/o/O进入Insert模式.

	a:在光标所在位置后输入;
	i:在光标所在位置前输入;
	A:在光标所在行的行末输入;
	I:在光标所在行的行首输入;
	o:在光标所在行的往下新增一行输入;
	O:在光标所在行的往上新增一行输入;

Insert模式按Esc可以退回到Normal模式.

#### 2.1.2 Vim的两个常用模式

1.Command-line模式

	/--->正向搜索;
	?--->反向搜索;
	:--->一般命令;
	:set nu--->显示行号;
	:sp--->横向显示两个窗口;
	:vsp--->垂直显示两个窗口.

2.Visual模式

Visual模式进行复制/粘贴非常方便.

	V--->按行选择的Visual模式,底部显示"---VISUAL LINE---"的提示;
	v--->按字符选择的Visual模式,底部显示"---VISUAL---"的提示;
	Ctrl+v--->按块选择的Visual模式,底部显示"---VISUAL BLOCK---"的提示.

#### 2.1.3 Vim下的光标移动

1.普通移动

	h--->左移一个字符;
	j--->上移一行;
	k--->下移一行;
	l--->右移一个字符;
	10h--->左移10个字符;
	15j--->下移15行;
	Ctrl+b--->向上翻页;
	Ctrl+f--->向下翻页.

2.进阶的移动

	0/Home--->移至行首;
	^--->移至行首第一个非空白字符;
	$--->移至行尾;
	G--->移至文档尾部(最后一行的第一个非空白字符处);
	Gg--->移至文档首部(第一行的第一个非空白字符处);
	W--->移至一个word的头部;
	e--->移至后一个word的词尾;
	b--->移至前一个word的词首;
	H--->移至屏幕顶第一个非空白字符;
	M--->移至屏幕中间的第一个非空白字符;
	L--->移至屏幕底第一个非空白字符;
	:n/nG--->移至第n行行首.

3.特殊移动

	}--->移至下一个段落首;
	{--->移至上一个段落首;
	%--->匹配'{'、'}'、'['、']'、'('、')',光标停在"("上时按"%",光标会自动跳转到匹配的")"上.

#### 2.1.4 Vim下的复制、粘贴和删除

1.复制

	yy--->复制整行;
	yw--->复制光标所在位置到单词尾的字符(即复制一个单词);
	y$--->复制光标所在位置到行尾;
	y^--->复制光标所在位置到行首;
	5yy--->复制5行;
	5yw--->复制2个单词.

2.粘贴

	p--->粘贴到下一行;
	P--->粘贴到上一行.

3.删除

	x--->删除光标处的单个字符;
	dd--->删除整行;
	dw--->删除光标到单词尾的字符;
	5x--->删除光标向右的3个字符;
	5dd--->向下删除5行.

#### 2.1.5 Vim下的撤销和重复

	u--->撤销;
	Ctrl+v--->重复.

#### 2.1.6 Vim下的查找和替换

1.查找

	/--->自上而下查找;
	?--->自下而上查找.

2.替换

	:s/old/new--->new替换行中首次出现的old;
	:s/old/new/g--->new替换行中所有出现的old;
	:#,#s/old/new/g--->new替换从第#行到第#行出现的old;
	:%s/old/new/g--->new替换整个文档中出现的old;
	:s/old/new/c或:s/old/new/gc--->需要用户在替换时确认.

#### 2.1.7 Vim下的文件的恢复

vim编辑文件时会生成一个临时文件(文件后缀尾.swp),正常退出自动删除,意外退出则不会删除.下一次编辑时处理如下:

	O--->只读打开;
	E--->继续编辑文件,不恢复.swp文件保存的内容;
	R--->恢复上次编辑以后未保存的文件内容(恢复使用这个即可);
	Q--->退出vim;
	D--->删除.swp文件;
	vim -r filename/vim -r filename.swp--->也可以恢复未保存的文件内容.

### 2.2 编译器GCC和交叉编译器

#### 2.2.1 常用编译选项

1.总体选项

	-x language--->指定后续输入文件的语言(C/C++/Ojective-C/assembler/go/Java等);
	-c--->预处理+编译+汇编,不链接;
	-S--->预处理+编译,生成汇编代码;
	-E--->仅预处理;
	-o file--->指定输出的目标文件名称为file.

2.专业选项

	-ansi--->C语言下等价于-std=c90,C++等价于-std=c++98;
	-std=--->确定语言标准(e.g. -std=c++11);
	--ffreestanding--->按独立环境编译,包含声明了"-fno-builtin"选项,没有main函数也可以编译通过.

3.警告选项

	-fsyntax-only--->检查代码中的语法错误,但不产生错误信息;
	-w--->屏蔽所有警告信息;
	-Werror--->所有警告当作错误;
	-Werror=xxx--->指定的警告(xxx)当作错误;
	-Wpedantic--->拒绝所有不遵循ISO C/C++标准的程序;
	-pedantic-errors--->和-Wpedantic类似,但警告当错误处理;
	-Wall--->打开所有类型的语法警告,建议编译时将该选项作为默认选项.

4.调试选项

	-g--->gdb使用该选项做调试用;
	-p--->用于输出profile信息,供分析程序prof使用;
	-pg--->gdb+prifile的用途.

5.优化选项

	-O0--->不做任何优化,减少编译时间,调试时使用该选项可以看到中间变量的值;
	-O1--->第一级优化,优化编译会占用较多的时间和较多的内存,但代码执行快;
	-O2--->第二级优化;
	-O3--->第三级优化(最大优化),调试时不适合使用该参数.

6.目录选项

	-Idir--->头文件搜索路径列表添加dir目录(适用于#inclue "xxx");
	-Ldir--->指定库搜索路径(自己的库),不然只在标准库的目录中找.

7.链接选项

	-llibrary--->指定链接时使用的库;
		gcc -lcurses hello.c	//使用curses库编译程序


### 2.3 常用shell命令和脚本

find/grep/管道在"linux_command_usage.md"中有使用方法.

### 2.4 Make和Makefile

GNU+make有详细的说明.

***

## Chapter 3 ARM体系结构

略.

***

## Chapter 4 ARM指令集

### 4.1 数据处理指令

**1.移动指令**

用于给寄存器设置立即数或在寄存器之间传输数据.

	mov r9, sp	//将sp寄存器中的值复制到r9中
	mov r0, #0	//将寄存器r0的值设为0
	mvn r1, #0	//mvn为取反,将0取反后赋给r1,即将寄存器r1的值设为0xFFFF_FFFF

**2.移位器**

共有5中移位操作:LSL(逻辑左移)、LSR(逻辑右移)、ASR(算数右移)、ROR(循环右移)、RRX(扩展的循环右移).通常与数据处理指令一起使用.

	mov r1, r1, LSL #9	//r1的值逻辑左移9位后仍然赋值给r1(LSL后面直接跟立即数,不能加逗号)

**3.算数指令**

算数指令执行32-bit的有符号和无符号数的加减法.

	inst Rd, Rn, N
	ADC--->带进位的加法		Rd = Rn + N + carry
	ADD--->加法				Rd = Rn + N
	RSB--->反向减法			Rd = N - Rn
	RSC--->带错位的反向减法	Rd = N - Rn - !(carry flag)
	SBC--->带错位的减法		Rd = Rn - N - !(carry flag)
	SUB--->减法				Rd = Rn - N
	//实例
	#define S_FRAME_SIZE	(72)
	sub sp, sp, #S_FRAME_SIZE	//sp = sp - 72
	add r0, sp, #S_FRAME_SIZE	//r0 = sp + 72

**4.使用移位器的算数指令**

	add r0, r1, r1, LSL #2	//r0 = r1 + (r1 << 2),即r0 = r1 * 5

**5.逻辑运算指令**

执行两个源寄存器的逻辑位运算.

	inst Rd, Rn, N
	AND--->逻辑与操作		Rd = Rn & N
	ORR--->逻辑或操作		Rd = Rn | N
	EOR--->逻辑异或操作		Rd = Rn ^ N
	BIC--->逻辑清位操作		Rd = Rn & (~N)
	//实例
	and r1, r0, #0x1f		//r1 = r0 & 0x1f
	orr r0, r0, #0xc0		//r0 = r0 | 0xc0

**6.比较指令**

将寄存器与一个32-bit的数做比较或测试,根据结果更新cpsr的标志位,但不影响其他的寄存器.

	inst Rn, N
	CMN--->否定比较,依照Rn + N的结果来设定标志位
	CMP--->比较,依照Rn - N的结果来设定标志位
	TEQ--->测试两个32-bit的数是否相等,依照Rn ^ N的结果来设定标志位
	TST--->测试一个32-bit的数的位,依照Rn & N的结果来设定标志位
	//实例
	teq r1, #0x1a	//比较r1与0x1a是否相等,并设定标志位

**7.乘法指令**

乘法指令将一对寄存器的值相乘,将结果存入到另一个寄存器中.长乘法累加指令将一对寄存器相乘后得到一个64-bit的值,结果存入一对寄存器中.

乘法指令

	MLA--->乘法和累加
	MLA Rd, Rm, Rs, Rn	// Rd = (Rm * Rs) + Rn
	MUL--->乘法
	MUL Rd, Rm, Rs		// Rd = Rm * Rs

长乘法指令

	inst RdLo, RdHi, Rm, Rs
	SMLAL--->有符号的长乘法累加		[RdHi, RdLo] = [RdHi, RdLo] + (Rm * Rs)
	SMULL--->有符号的长乘法			[RdHi, RdLo] = Rm * Rs
	UMLAL--->无符号的长乘法累加		[RdHi, RdLo] = [RdHi, RdLo] + (Rm * Rs)
	UMULL--->无符号的长乘法			[RdHi, RdLo] = (Rm * Rs)
	//实例
	mla r3, r4, r1, r3	// r3 = (r4 * r1) + r3

### 4.2 分支指令

分支指令用于改变程序执行流程或用于调用子程序.

	B		label		//跳转到label处,PC=label
	BL		label		//带返回的跳转,PC=label,lr=执行BL后下一条指令的地址
	BX		Rm			//跳转并切换状态,PC=Rm & 0xffff_fffe, T=Rm & 1
	BLX		label | Rm	//带返回的分支并切换状态
	PS:地址label是一个偏移量,必须限制约32M范围内.
	//实例
	bl cpu_init_cp15	//带返回的跳转到cpu_init_cpu15的label处

### 4.3 软中断指令

软中断指令会引起软件中断异常,为应用程序进行系统调用提供了一种机制.

	SWI SWI_number(软中断号)
	//实例---在Linux下用汇编实现一个"hello world"
	.data
		msg: .asciz "hello, world\n"
	.text
		.global main
	main:
		push {r0, r1, r2, lr}
		ldr r1, =msg	@address
		mov r0, #1		@stdout
		mov r2, #13		@length
		swi #0x900004	@sys_write
		pop {r0, r1, r2, pc}
	//编译运行
		arm-linux-gnueabi-gcc asmhello.s -o asmhello
	在qemu上运行./asmhello即可.
	PS:0x900004是system write的SWI数,0x900001是system exit的SWI数.

### 4.4 程序状态寄存器指令

ARM提供2条指令来控制程序状态寄存器(psr).

	MRS Rd, <cpsr/spsr>
		将cpsr或spsr的内容传到通用寄存器中--->Rd = psr
	MSR <cpsr/spsr>, Rm
		将通用寄存器的内容传到cpsr或spsr中--->psr = Rm
	MSR <cpsr/spsr>, #immediate
		将立即数的值传到程序状态寄存器中--->psr = 立即数

实例

	mrs r0, cpsr
	and r1, r0, #0x1f	@ get mode bits
	teq r1, #0x1a		@ test form HYP mode
	bicne r0, r0, #0x1f @ clear all mode bits
	orrne r0, r0, #0x13 @ set SVC mode
	orr r0, r0, #0xc0	@ disable FIQ and IRQ
	msr cpsr, r0

### 4.5 协处理器指令

主要是MCR/MRC,可以看"Assembly instructions(arm & mips).md"文档.

### 4.6 加载常量的伪指令

略.

***

## Chapter 5 ARM寻址模式

***

## Chapter 6 编译和链接

GNU binutils包是用于分析目标文件的工具包,包含以下工具:

	ar:创建、修改和取出静态库;
	strings:列出二进制文件内的可显示的字符串;
	strip:删除目标文件中的符号表信息;
	nm:列出目标文件中的符号表中定义的所有符号;
	size:列出目标文件中的节的名字和大小;
	readelf:显示一个目标文件的完整结构(elf头中的所有信息);
	objdump:反汇编目标文件中的.text段中的二进制指令.

ELF(可执行和可链接格式)目标文件分为3中类型:

	1.可重定位文件:包含代码和数据,用于链接成可执行文件或共享目标文件,静态库可归结为可重定位文件
		(静态库实际上是将很多目标文件捆绑在一起后形成一个文件包,再加上一些索引信息);
		实例:linux下的.o文件和.a静态库;
		file Socket.o
		Socket.o: ELF 32-bit LSB relocatable, ARM, version 1 (SYSV), not stripped
	2.可执行文件:包含二进制代码和数据,可以直接复制到存储器执行;
		实例:/bin或/usr/bin目录下的文件;
		file busybox
		busybox: ELF 32-bit LSB executable, ARM, version 1 (SYSV), dynamically linked
		(uses shared libs), stripped
	3.共享目标文件:一种特殊类型的可重定位目标文件,可以在加载或运行时被动态地加载到存储器并链接.
		实例:/linux下的.so文件.
		file libQtGui.so.4.8.2
		libQtGui.so.4.8.4: ELF LSB shared object, ARM, version 1 (SYSV), dynamically
		linked, stripped

### 6.1 ELF文件结构的描述

读取elf文件的工具:readelf,交叉编译时的readelf可能是:arm-linux-gnueabi-readelf

elf读取后会显示头信息,包含了:幻数、机器字节长度、数据存储方式、版本、系统和ABI版本、ELF文件类型、目标硬件平台、硬件平台版本、入口点地址、程序头入口和长度、段头入口、ELF头的长度、程序头的数目、段头的长度、	段头的数目、段头字符串表的索引.

**在vim下以16进制显示elf文件的方法:**

	:%!xxd

### 6.2 段表

一个elf文件包含的主要的段如下:

	.text:代码段,用来存放可执行文件的操作指令,是可执行程序在内存中的镜像;
	.data:数据段,用来存放可执行文件中已初始化的全局变量(初始化为非0),也就是说存放程序static变量和全局变量;
	.rodata:只读数据段,比如prinft语句中的字符串等只读信息;
	.bss:bss段,包含了程序中未初始化的全局变量和初始化为0的全局变量,在内存中bss段全部置0;
		--->区分初始化和未初始化变量是为了空间效率,因为bss段在文件中不占空间,在运行时分配空间.
	堆(heap):用于存放进程运行中动态分配的内存段,大小不固定,可动态扩张或缩减.malloc等新分配内存会被动态添
	加到堆上(堆被扩张);free等释放内存会从堆中剔除(堆被缩减);
	栈(stack):存放程序临时创建的局部变量.栈特别适用于保存/恢复调用现场.

查看段信息:

	readelf -S xxx.o

### 6.3 符号表结构

查看符号表信息:

	readelf -s xxx.o

ld链接器需要使用的符号如下:

	__executable_start:说明程序的起始地址(不是入口地址),是程序最开始的地址;
	__etext、_etext或etext:说明代码段结束地址;
	_edata或edata:说明数据段的结束地址;
	_end或end:说明程序结束地址.

### 6.4 存储空间分配

elf程序的布局思路是:将相同性质的段合并在一起,如下所示:

![](images/layout_of_store.png)

### 6.5 重定位信息

略.

### 6.6 静态链接和重定位

在链接中,函数和变量统称为符号,函数名或变量名就是符号名.

链接器完成的2个主要任务:

	1.符号解析:将每个符号引用和一个符号定义关联起来;
	2.重定位:编译器和汇编器生成从地址0开始的代码段和数据段.链接器通过定义每个符号将符号与一个存储器位置关
		联起来,然后修改所有对这些符号的引用,使得他们指向这个存储器位置,从而重定位这些段.

#### 6.6.1 符号和符号表

nm命令可以显示指定文件中符号的信息.文件可以是:对象文件、可执行文件或库文件.

				nm main.o
				U add
	00000000	D array
	00000000	T main
	....

符号详细说明(即前面字母的含义):

	A--->该符号的值是绝对的,在以后的链接过程中,不允许进行改变.e.g.这样的符号值,常常出现在中断向量表中;
	B--->该符号的值出现在非初始化数据段(BSS)中.e.g.在一个文件中定义全局static int test;
	C--->该符号为common.common symbol是未初始话数据段.e.g.在一个c文件中,定义int test,并且该符号在别的
		地方会被引用,则该符号类型即为C.否则其类型为B;
	G--->该符号位于初始化数据段中.e.g.int a = 2(全局定义);
	I--->该符号是对另一个符号的间接引用;
	N--->该符号是一个debugging符号;
	R--->该符号位于只读数据区.e.g.全局const int test[] = {123, 123},则test就是一个只读数据区的符号;
	  PS:const char *test = “abc”,使用nm得不到符号信息,因为字符串"abc"位于只读存储区,test位于rodata.
	S--->符号位于非初始化数据区;
	T--->该符号位于代码区text section;
	U--->该符号在当前文件中是未定义的,该符号的定义在别的文件中.
	  e.g.当前文件调用另一个文件中定义的函数,在这个被调用的函数中就是未定义的,但是在定义它的文件中类型是T;
	V--->该符号是一个weak object.

***

## Chapter 7 链接脚本

### 7.1 基本概念

ld(链接器):后面必须带一个链接脚本.

	1.查看默认的链接脚本:
	ld/arm-linux-gnueabi-ld -verbose	//显示使用的默认脚本
	2.指定自己的链接脚本
	ld/arm-linux-gnueabi-ld -T			//指定自己的链接脚本

LMA和VMA:

	LMA(Load memory address):代码被加载的地址;
	VMA(Virtual memory address):代码要运行的地址.
	普通的PC:LMA和VMA是一样的,即程序被加载到内存的什么地方,就在什么地方运行;
	嵌入式系统:代码可能会放在Nor Flash中,此时LMA地址就是Nor Flash的地址;但是程序运行需要有个运行地址(
		即VMA),此时需要将代码从LMA拷贝到VMA出,才可正常运行.

### 7.2 简单的链接脚本示例

	SECTIONS	/* SECTIONS命令用于描述输出文件的内存布局 */
	{
		. = 0x10000;
		/* 
		".":位置计数器.此处的地址为0x10000.
		 */
		.text : { *(.text) }
		/*
		".text":定义"text"段.必须带冒号":",后面有一个花括号,列举放入text段的内容.
		{ *(.text) }:"*"匹配任何文件名的通配符.此处表示所有输入文件中的".text"段.
		结合上面的位置计数器,链接器会在输出文件中将".text"的地址设定为0x10000.
		 */
		. = 0x8000000;
		.data : { *(.data) }
		/*
		将".data"段的地址设定为0x8000000.
		 */
		.bss : { *(.bss) }
		/*
		".bss"段的地址为0x8000000加上".data"段的大小.
		*/
	}