# Run Linux Kernel

# Chapter 1 处理器体系结构

1.ARMv4指令集的处理器架构有ARM7-TDMI,典型的处理器有三星的S3C44B0X;

2.ARMv4T指令集的处理器架构有ARM920T,典型的处理器有三星的S3C2440;

3.ARMv5指令集的处理器架构有ARM926EJ-S,典型的处理器有NXP的i.MX2 Series;

4.ARMv6指令集的处理器架构有ARM11 MPCore.

5.ARMv7指令集处理器系列以Cortex命名,分为A、R、M系列:

	A系列针对大型嵌入式系统(e.g.手机);
	R系列针对实时性系统;
	M系列针对单片机市场.

6.ARMv8-A指令集:

	1.支持64 bit指令集,并且向前兼容ARMv7-A指令集
	2.定义AArch64和AArch32两套运行环境来分别运行64位和32位指令集,软件可动态切换运行环境;
	3.AArch64也称为ARM64; AArch32也称为ARM32.

## 1.精简指令集RISC和复杂指令集CISC的区别

	在实际使用中,20%的简单指令被经常用到,占程序总指令数的80%;而指令集里其余80%的复杂指令很少被用到,只占程序总指令数的20%.
	将指令集和处理器进行重新设计,只保留常用的简单指令.而简单指令大部分时间能在一个cycle内完成,基于这种思想的指令集叫做RISC
	(Reduced Instruction Set Computer)指令集.以前的指令集叫做CISC(Complex Instruction Set Computer)指令集.

## 2.大小端字节序

大端模式:数据的高字节存放在内存的低地址中;低字节存放在内存的高地址中.

	00000430: 1234 5678 0100 1800 53ef 0100 0100 0000
	00000440: c7b6 1100 0000 3400 0000 0000 0100 ffff
	大端模式下,前32位数据读法:0x12345678

小端模式:数据的高字节存放在内存的高地址中;低字节存放在内存的低地址中.

	00000430: 7856 3412 0100 1800 53ef 0100 0100 0000
	00000440: c7b6 1100 0000 3400 0000 0000 0100 ffff
	小端模式下,前32位数据读法:0x12345678

**判断CPU对内存采用大端模式还是小端模式:**

	int checkCPU(void)
	{
		union w
		{
			int a;
			char b;
		}c;
		c.a = 1;
		return (c.b == 1);
		/*
			1.union共用一个存储空间.此处a和b共用一个4 byte的内存空间;
			2.union的存放顺序是所有成员都是从低地址开始存放的.此处的"c.a=1"存放在低地址
			此处判断c.b == 1:
			1)如果为大端模式,此时的"c.a=1"属于低字节会存放在高地址.c.b访问低地址得到的数据为0,返回false.
			2)如果为小端模式,此时的"c.a=1"属于低字节会存放在低地址.c.a访问低地址得到的数据为1,返回true.
		*/
	}

## 3.指令的执行过程相关概念

**1.五级流水线**

	取指(IF)、译码(ID)、执行(EX)、数据内存访问(MEM)和写回(WB).

**2.超标量体系结构(Superscalar Architecture)**

	描述一种微处理器设计理念,能够在一个时钟周期内执行多个指令.

**3.乱序执行(Out-of-Order Execution)**

	CPU采用了允许将多条指令不按程序规定的顺序分开发送给各相应电路单元处理的计数,避免处理器在计算对象不可获取时的等待,
	从而导致流水线停顿.

**4.寄存器重命名(Register Rename)**

	用来避免机器指令或微操作的不必要的顺序化执行,提高处理器的指令集并行能力.思路:当一条指令写一个结果寄存器时不直接写到这个
	结果寄存器中,而是先写到一个中间寄存器过渡,当这条指令提交时再写到结果寄存器中.

**5.分支预测(Branch Predictor)**

	当处理分支指令时(跳转指令),有可能会产生跳转,因为无法确定该指令的下一条指令,进而会打断流水线指令的处理,直到分支指令
	执行完毕.分支预测(Branch Predictor)是处理器在程序分支指令执行前预测其结果.

**6.指令译码器(Instruction Decode)**

	指令由操作码和地址码组成.操作码表示要执行的操作;地址码是操作码执行时的操作对象的地址.
	指令译码器完成操作码和地址码的分析,然后送到下一个步骤完成指令的功能.
	Cortex-A53同时支持3路译码器,即同时执行3条指令译码;Cortex-A9同时支持译码2条指令.

**7.调度单元(Dispatch)**

	调度器负责把指令或微操作指令派发到相应的执行单元去执行.

**8.算术逻辑单元(ALU)**

	处理器的执行单元,进行算术运算、逻辑运算、关系运算等.

**9.LSQ/LSU部件(Load Store Queue/Unit)**

	将来自CPU的存储器请求发送到存储器子系统,并处理其下存储器子系统的应答数据和消息.

## 4.内存屏障(memory barrier)

**内存访问乱序产生原因**

	1.编译时,编译器优化导致内存乱序访问;
	2.运行时,多CPU间交互引起的内存乱序访问.

**编译时的乱序访问规避**

	#define barrier() asm volatile("": : :"memory")
	/*
		memory:强制gcc编译器假设RAM所有内存单元均被汇编指令修改,此时CPU中的register和cache中的数据作废.
		CPU将不得不在需要的时候重新读取内存中的数据.阻止了CPU读取register或cache中的数据用于去优化指令,
		而不去访问内存.
	*/

## 5.ARM的memory barrier(内存屏障)指令

从ARMv7指令集开始,ARM提供3条内存屏障指令.

**1.DMB(Data Memory Barrier)数据存储屏障**

	该指令可以不带参数.位于此指令前的所有内存访问均完成后,DMB指令才完成.

**2.DSB(Data Synchronization Barrier)数据同步屏障**

	数据同步隔离,比DMB更严格.要求是任何指令都要等待DSB前面的存储访问完成.
	DSB比DMB常用.

**3.ISB(Instructiong Synchronization Barrier)指令同步屏障**

	指令同步隔离,最严格.通常用来保证上下文切换的效果,e.g.更改ASID(Address Space Identifier)、TLB维护操作
	和C15寄存器的修改等.

**内存屏障实例1---两个CPU核同时访问Addr1和Addr2地址**

	Core A:
		str r0, [addr1]	//将寄存器r0的值保存到addr1的地址中.str/ldr指令操作memory第二个参数的格式"[addr]"
		ldr r1, [addr2]	//取addr2中的值放到寄存器r1中

	Core B:
		str r2, [addr2]	//将寄存器r2的值保存到addr2的地址中
		ldr r3, [addr1]	//取addr1中的值放到寄存器r3中

	/*
	因为:1.多级流水线;2.没有指令屏障,3.两个CPU属于并行执行.Core A的寄存器r1和Core B的寄存器r3可能得到一下4种结果:
		1)r1得到旧的值,r3也得到旧的值;
		1)r1得到旧的值,r3也得到新的值;
		1)r1得到新的值,r3也得到旧的值;
		1)r1得到新的值,r3也得到新的值;
	*/

**内存屏障实例2---乱序执行**

	Core A:
		str r0, [msg]	//写r0中的新数据到msg地址
		str r1, [flag]	//flag用来标志新数据可以读

	Core B:
	  poll_loop:
		ldr r1, [flag]	//取flag地址中的数据到r1
		cmp r1, #0		//比较r1中的值与立即数0是否相等.即判断flag有没有置位
		beq	poll_loop	//与0相等,表示没有置位.跳到poll_loop循环.判断不相等的指令:bne
		ldr r0, [msg]	//不相等,读取msg地址的数据到r0

	/*
		Core B可能读取不到最新的数据.因为Core B可能因为乱序执行的原因先读入msg,然后读取flag.处理器并不知道
		msg和flag存在数据依赖性.
		修改如下:
	*/
	Core A:
		str r0, [msg]	//写r0中的新数据到msg地址
	+	dmb				//保证两条store指令的执行顺序
		str r1, [flag]	//flag用来标志新数据可以读

	Core B:
	  poll_loop:
		ldr r1, [flag]	//取flag地址中的数据到r1
		cmp r1, #0		//比较r1中的值与立即数0是否相等.即判断flag有没有置位
		beq	poll_loop	//与0相等,表示没有置位.跳到poll_loop循环.判断不相等的指令:bne
	+	dmb				//保证直到flag置位才读入msg
		ldr r0, [msg]	//不相等,读取msg地址的数据到r0

**内存屏障实例3---写命令到外设寄存器,等待状态变化**

	str r0, [addr]	//写一个命令到外设寄存器(相当于写地址addr)
	dsb				//强制让该命令完成,写进了addr
	poll_loop:
		ldr r1, [flag]	//读取flag,判断是否循环
		cmp r1, #0
		beq poll_loop	//等于0,执行循环

## 6.cache工作方式

cache使用的地址编码方式和主存储器的类似,因此处理器可以使用访问主存储器的地址编码访问cache.

	处理器在访问存储器时,会把地址同时传递给TLB和cache.
	1.TLB(Translation Lookaside Buffer):用于存储虚拟地址到物理地址转换的小缓存,处理器先使用EPN(effective page
		number)在TLB中进行查找最终的RPN(Real Page Number).如果这期间发生TLB miss,处理器需要重新查询页表.如果
		TLB Hit,此时可以很快得到合适的RPN,并得到相应的物理地址.
	2.cache:
		1)物理内存通过物理地址PA标识,内存块用PA+SIZE表示.在读取内存时,CPU会将内存块按照cache line的大小load到
		cache中.而需要的内存块应该是被包含在这段load的内存中.在编程时,尽量将结构设计为cache line对齐,一次加载完
		成.而在访问下一个结构体时,可以直接访问另一个cache line,避免冲突.
		2)cache编码地址(或者物理编码地址)被分为三个部分:tag+index+offset.
			index:是物理地址在cache这个数组中的索引,此时可以得到cache line
				整个cache相当于一个一维数组,由多个cache line构成.
				cache line的大小一般为32 byte,也有的是64 byte.
			offset:是物理地址在cache line中的偏移量
				因为数据load时是按照cache line的大小进行load.
			tag:用于判断cache line中存放的数据是否和处理器想要的一致.
			新的架构:
			set(组):相同的cache line构成一个组.
			way(路):路相当于整个cache多了若干层.在组相连的cache中,同一个index又多了4/8 way.
				进一步扩大cache范围,提高cache命中效率.
	3.cache Hit和cache miss:
		将cache line中存放的地址和通过虚实地址转换得到的物理进行比较.如果相同并且状态为匹配,就会发生cache hit.
		通过offset等即可获得所需数据.如果发生cache miss,处理器需要用物理地址进一步访问主存储器来获得数据,并将
		数据填充到相应的cache line中.
	
## 7.cache映射方式---direct mapping, set-associative, full-associative

**1.direct mappin(直接映射)**

每个组只有一行cache line时(即只有一个层级---1 way),称为直接映射高速缓存.

	一个简单的cache中:
		1.只有4行cache line,每行4个字(word,一个word 4byte,一行共16 byte),总共cache大小为64 byte.
		2.cache控制器使用编码地址的bit[3:2]来选择cache line中的字(总共4个字);使用bit[5:4]来选择index
		(即选择4行cache line中的哪一行);其他bit用于存储标记值(tag)
	//出现的情况:
	[5:4]相同的地址会映射到同一个cache line中,当操作地址数据时,会出现频繁的cache line数据换入换出,导致
	严重的cache颠簸(cache thrashing).

	/*实例*/
	void add_array(int *data1, int *data2, int *result, int size)
	{
		int i;
		for (i=0; i<size; i++) {
			result[i] = data1[i] + data2[i];
		}
	}
	如果result, data1, data2分别指向0x00, 0x40, 0x80地址,这三个地址的[5:4]相同,因此处于同一个cache line
	step 1:读data1即0x40地址数据时,不在cache中,所以读取主存的0x40到0x4f(因为cache line大小为16 byte)地址
		的数据填充到cache line中;
	step 2:读data2即0x80地址数据时.因为0x80和0x40映射到同一个cache line,此时0x80地址数据不在cache line中,
		所以需要读取主存0x80到0x8f地址的数据填充到cache line中,cache line发生替换操作;
	step 3:result写入0x00地址时,先写到cache line中.因此也会在同一个cache line发生替换操作.
	因此这段代码发生了严重的cache颠簸,性能会很糟糕.

**2.set associative(组相联)**

增加一个way的概念(相当于多了层,由平面构成立体结构).

	2路组相联cache:
		1.每个路(way)包括4行cache line,即每个面由4行cache line;
		2.2路组相联表明有两个面,每一路都是一样的.
		3.每个组(set)有2个cache line可以提供cache line替换---因为有2路,相同的index有2个完全一样的cache line
	此时地址0x00,0x40,0x80可以映射到同一个组(相同的index构成)中任意一个cache line.当cache line要发生替换操作时,
	就有50%的概率可以不被替换,较少cache颠簸.

## 8.32 KB的4路组相联的cache

	在Cortex-A7和Cortex-A9的处理器上有32 KB的4路组相联的cache:
	cache大小:32 KB;		way:4路;		cache line:32 Byte
	1.每一路的大小:	way_size = 32/4 = 8(KB)	//即每个面为8KB
	2.每一路含有的cache line数量:	num_cache_line = 8KB/32B = 256
	
	cache的编码地址address排布:
	[4:0]---选择cache line中的数据(cache line大小为32B).[4:2]寻址8个字;[1:0]寻址每个字中的字节;
	[12:5]---用于索引(Index)选择每一路上的cache line.
	[31:13]---用作标记位(tag)

## 9.

