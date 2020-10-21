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
# 1. ARM汇编指令

## 1. Auxcode中的boot.S---适配Cortex A7(CA7)

	#define SP_MAX_SIZE		(1024*5)	/*堆大小为5K*/
	#define MONITOR_SP		(1024*1)	/*monitor 堆大小为1K*/

		.globl	sm_vect_table
		/*.globl/.global symbol:声明后面的symbol(sm_vect_table)是全局可见的.*/
		/*.global:使得连接程序(ld)能够识别symbol.也即外部程序可以访问的标签*/
		.func sm_vect_table		/*声明一个函数???*/
	------------------------------------------------------------------------------------------------------
	sm_vect_table:
		/*格式"symbol:"仅仅表示一个标号.此处表示sm的向量表,该表由arm硬件架构已经定义好的.*/
		b	_start
		/*(reset)芯片reset时的处理,第一条指令.此处表示跳转到标号"_start"处执行*/
		b	.
		/*(undefined instruction)未定义指令异常的处理.此处"."表示死循环,跳到自身位置*/
		b	sm_smc_entry
		/*(secure monitor call)调用的处理.此处表示跳转到标号"sm_smc_entry"处执行*/
		b	.
		/*(Prefetch abort)取指异常的处理.此处"."表示死循环,跳到自身位置*/
		b	.
		/*(Data abort)数据访问异常的处理.此处"."表示死循环,跳到自身位置*/
		b	.
		/*(Reserved)保留,其他异常的处理.此处"."表示死循环,跳到自身位置*/
		b	.
		/*(IRQ)中断处理.此处"."表示死循环,跳到自身位置*/
		b	.
		/*(FIQ)快中断处理.此处"."表示死循环,跳到自身位置*/
		.endfunc
		/*函数结束???*/

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
	.globl _start
	/*标号"_start":是GNU链接器用来指定第一个要执行的指令所必须的,全局可见(并且只能出现在一个
		模块中).*/
	_start:
		mrc p15, 0, r0, c0, c0, 5
		/*mrc:读取协处理器中的寄存器数据到ARM处理器的寄存器中.
		  mcr:用于读取ARM处理器的寄存器数据到协处理器的寄存器中.
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
	------------------------------------------------------------------------------------------------------
	init_start:
		bl disable_mmu
		/*bl:带链接的跳转,常用于调用子程序,返回地址自动保存在lr中; b:无条件跳转到标号,无返回.*/
		bl disable_l1_cache			/*disable L1 cache*/
		bl invalidate_l1_icache		/*invalidate L1 icache, tlb, bp array*/

	------------------------------------------------------------------------------------------------------
	disable_mmu:
		dsb	
		/*数据同步屏障,只有完成:1.位于此指令前的所有显式内存访问均完成;2.位于此指令前的所有缓存、
		跳转预测和TLB维护操作全部完成.此指令才会完成.后面可带参数:SY(完整的系统DSB操作),因为是缺
		省情况,可省略.
		*/
		mrc p15, 0, r2, c1, c0, 0
		/*mrc:读取协处理器中的寄存器数据到ARM处理器的寄存器中.
		  mcr:用于读取ARM处理器的寄存器数据到协处理器的寄存器中.
			p15:协处理器p15.CP15协处理器用于系统存储管理.
			0:协处理器将执行的操作的操作码.对于CP15来说,该操作码永远是"0".
			r2:ARM寄存器.mrc时将作为目标寄存器
			第一个c1:协处理器寄存器.协处理器cp15的c1寄存器是一个控制寄存器,其功能包括:
				禁止或使能MMU以及其他与存储系统相关的功能;
				配置存储系统以及ARM处理器中的相关部分工作.
			第二个c0:协处理器的附加寄存器.如果不需要附加信息,则指定为"c0".
			0:操作类型(第二个数(操作码)的附加参数).此处表示类型0.
			该条汇编指令的意思:读取ARM CPU的MMU中的控制位值到ARM寄存器r2里面.
		*/
		bic r2, r2, #0x1
		/*后一个r2与"#"立即数0x1的反码取与,然后写入到第一个r2中.实现"位清除",即r2[0]=0.
		  cp15中的c1[0]=0->disable MMU; c1[0]=1->enable MMU.
		*/
		mcr p15, 0, r2, c1, c0, 0
		/*将清掉[0]=0的r2寄存器的值写入到协处理器p15的c1寄存器.实现disable MMU*/
		isb
		/*确保在ISB指令完成后,才从高速缓存或内存中提取位于该指令后的其他所有指令.默认值为SY,
			完成的系统DMB操作.
		*/
		bx lr	/*bx:带状态切换的跳转指令.此处为返回到调用处.*/
		/*反汇编该段代码:
		800004d8 <disable_mmu>:
		800004d8:	f57ff04f 	dsb	sy
		800004dc:	ee112f10 	mrc	15, 0, r2, cr1, cr0, {0}
		800004e0:	e3c22001 	bic	r2, r2, #1
		800004e4:	ee012f10 	mcr	15, 0, r2, cr1, cr0, {0}
		800004e8:	f57ff06f 	isb	sy
		800004ec:	e12fff1e 	bx	lr
		*/
	------------------------------------------------------------------------------------------------------
	disable_l1_cache:
		mrc p15, 0, r2, c1, c0, 0
		bic r2, r2, #(0x1 << 12)
		/*协处理器p15的c1寄存器的
			[12]=0->disalbe I cache; 
			[12]=1->enable I cache.
		此处为disable I cache.*/
		bic r2, r2, #(0x1 << 2)
		/*协处理器p15的c1寄存器的
			[2]=0->disalbe D cache; 
			[2]=1->enable D cache.
		此处为disable D cache.*/
		mcr p15, 0, r2, c1, c0, 0	
		/*将清掉[2]和[12]的r2寄存器的值写入到协处理器p15的c1寄存器*/
		bx lr	/*bx:带状态切换的跳转指令.此处为返回到调用处.*/
		/*反汇编该段代码:
		800004f0 <disable_l1_cache>:
		800004f0:	ee112f10 	mrc	15, 0, r2, cr1, cr0, {0}
		800004f4:	e3c22a01 	bic	r2, r2, #4096	; 0x1000
		800004f8:	e3c22004 	bic	r2, r2, #4
		800004fc:	ee012f10 	mcr	15, 0, r2, cr1, cr0, {0}
		80000500:	e12fff1e 	bx	lr
		*/
	----------------------------------------------------------------------------------------
	invalidate_l1_icache:
		mov r3, #0	/*往r3寄存器写入立即数0*/
		mcr p15, 0, r3, c8, c7, 0
		/*协处理器p15的c8寄存器是只写寄存器.该条指令是"使无效整个数据和指令TLB"*/
		mcr p15, 0, r3, c7, c5, 0
		/*协处理器p15的c7寄存器是只写寄存器.该条指令是"使无效整个指令cache"*/
		mcr p15, 0, r3, c7, c5, 6
		/*清空整个跳转目标cache.即invalidate BP array.*/
		bx lr	/*bx:带状态切换的跳转指令.此处为返回到调用处.*/
		/*反汇编该段代码:
		80000504 <invalidata_l1_icache>:
		80000504:	e3a03000 	mov	r3, #0
		80000508:	ee083f17 	mcr	15, 0, r3, cr8, cr7, {0}
		8000050c:	ee073f15 	mcr	15, 0, r3, cr7, cr5, {0}
		80000510:	ee073fd5 	mcr	15, 0, r3, cr7, cr5, {6}
		80000514:	e12fff1e 	bx	lr
		*/
	---------------------------------------------------------------------------------------

## 1.2 AArch64的一些汇编

### 1.2.1 get_cpuid

	get_cpuid:
		mrs		x1, MPIDR_EL1	//读取MPIDR_EL1寄存器的值到x1寄存器
		/*
		1.ARMv8提供了31个64-bit的通用寄存器,分别是x0-x30.每个64-bit的寄存器底32-bit包含32-bit
			的兼容形式,称为w0-w30.读取w不会影响相应的x的高32-bit,但写入w会清零相应的高32-bit;
		2.MPIDR_EL1(Multiprocessor Affinity Register:多处理器关联的寄存器),部分芯片的用法是:
			0b[11:8]:表示cluster_id;
			0b[7:2]:reserved;
			0b[1:0]:每个cluster_id里面的core_id;
		3.mrs:将状态寄存器(cpsr/spsr)或系统协处理器(非cp之类的)的寄存器的值搬移到通用寄存器.
		*/
		and		w0, w1, #0xf00	// get cluster_id
		/*
		w1是x1的低32-bit,将w1的值0x?00取出来放在w0中;
		*/
		lsr		w0, w0, #6		// ((cluster_id >> 8) << 2) = (cluster_id >> 6)
		/*
		1.lsr:logic shift right;
		2.将w0右移6-bit后再存放在w0中.此步的目的:0x?00 >> 6--->0b????00,保持该值为4对齐.
		*/
		and		w1, w1, #0x3	// get core_id in the cluster
		/*
		w1中的0b[1:0]表示core_id,此处取出cluster中的core_id.
		*/
		add		w0, w0, w1		// calculate core_id in the multi-cluster system
		/*
		w0中存放的是cluster_id,以4对齐.w1存放的是core_id,相加即可得到一个真是的cpuid.
		*/

内嵌汇编实现

	uint32_t get_core_id(void)
	{
		uint32_t core_id = 0;
		uint64_t reg_val = 0;
		asm volatile("mrs %0, mpidr_el1" : "=r"(reg_val));
		/*
		mrs %0  //编译器会自动选择一个空闲的CPU寄存器来装载reg_val变量的地址(mov必须带寄存器);
            	//理解为:该空闲寄存器就代表该变量.
    	: "=r"(reg_val)   //"=r"(reg_val):有"="是output;"r"(x):无"="是input;前面的":"是修饰;
                //此处表示将mpidr_el1中的值读出来给到reg_val.
    	完整的语法应该是:
        	asm volatile("mov %0, r15" : "=r"(x) : "r"(xxx));
    	此处由于没有input,因此后面的":"也省略了.
	}

### 1.2.2 页表配置解析

	InitMem:
		LDR		x0, =page_table_base	/*page_table_base在*.ld文件中有定义,0x81000000*/
		/*
		此处将0x8100_0000(一个地址)放到x0寄存器.
		*/
		LDR		x1, =0x0060000000000001	/* device memory:0x0000_0000~0x3fff_ffff */
		STR		x1, [x0, 0x00]		/* 将x1的值存放到x0寄存器中的内容(为一个地址)+0x00的内存中 */	
		/*
		整个过程为:给0x0000_0000~0x3fff_ffff配置页表属性,0x0060000000000001值的解析:
			0b[1:0]=0b01:表示block,此处表示1GB的block页表;
			0b[4:2]:attr index,用于索引MAIR_ELx寄存器(我们用EL3),该寄存器的索引决定了内存的属性,
				具体请看下面分析;
			0b[47:12]:下一级页表的地址--->4k granule size是[47:12],16k/64k与4k不一样;
			其他位段省略.
		*/
		LDR		x1, =0x0060000040000609	/* non-cacheable memory:0x4000_0000~0x7fff_ffff */
		STR		x1, [x0, 0x08]		/* 将x1的值存放到x0寄存器中的内容(为一个地址)+0x08的内存中 */	
		/*
			0b[4:2]值为2.
		*/
		LDR		x1, =0x0000000080000605	/* cacheable memory:0x8000_0000~0xbfff_ffff */
		STR		x1, [x0, 0x10]		/* 将x1的值存放到x0寄存器中的内容(为一个地址)+0x10的内存中 */	
		/*
			0b[4:2]值为1.
		*/
		LDR		x1, =0x00000000c0000605	/* cacheable memory:0xc000_0000~0xffff_ffff */
		STR		x1, [x0, 0x18]		/* 将x1的值存放到x0寄存器中的内容(为一个地址)+0x18的内存中 */	
		/*
			0b[4:2]值为1.
		*/
		LDR		x1, =0x0060000100000601	/* device memory:0x1_0000_0000~0x1_3fff_ffff */
		STR		x1, [x0, 0x20]		/* 将x1的值存放到x0寄存器中的内容(为一个地址)+0x20的内存中 */	
		/*
			0b[4:2]值为0.
		*/
	
		MSR		TTBR0_EL3, x0		/* 将x0寄存器的值(页表基地址)写入TTBR0_EL3 */
		LDR		x1, =0x44ff04
		MSR		MAIR_EL3, x1		/* MAIR_EL3每个字节表示一种memattr */
		/*
		此处只给了byte0/1/2配置了memattr,其他的默认为0.
			byte0=0x4:Device-nGnRE memory;
			byte1=0xff:Normal memory,还有其他的信息,参考reference manual;
			byte2=0x44:Normal memory.
		MAIR_EL3使用页表的0b[4:2]去索引,总共3-bit,可以索引8个byte.
		*/

		LDR		x1, =0x8084251e
		MSR		TCR_EL3, x1		/* Translation Control Register(EL3) */
		/*
		0b[5:0]:T0SZ,控制内存可访问范围大小,为2^(64-T0SZ).
		此处为0x1e(30):表示内存可访问大小为2^34,即16GB.
		PS:之前的值为0x20,此时大小为4GB,导致访问超过4GB就出问题了.
		*/

		MRS		x1, SCTLR_EL3
		MOV		x2, #1805
		ORR		x1, x1, x2
		MSR		SCTLR_EL3, x1
		/*
		SCTLR_EL3:System Control Register(EL3).
		0b[0]:MMU Enable for EL3 stage 1 address translation.
		不确定有没有影响,之前为0,后来改为了1.
		*/

***
# 2. MIPS汇编指令

实现在某个指定位置下一个断点的操作:

		la 	t0, 0xa01ffff0
		la 	t1, defy_test
		lw 	t2, (t1)
		sw 	t2, (t0)
		addiu 	t1, t1, 4
		lw 	t2, (t1)
		sw 	t2, 4(t0)

	defy_test:
		nop
		.word 0x1000ffff

反汇编得到:

	80000214:	3c098000 	lui	t1,0x8000
	80000218:	25290230 	addiu	t1,t1,560
	8000021c:	8d2a0000 	lw	t2,0(t1)
	80000220:	ad0a0000 	sw	t2,0(t0)
	80000224:	25290004 	addiu	t1,t1,4
	80000228:	8d2a0000 	lw	t2,0(t1)
	8000022c:	ad0a0004 	sw	t2,4(t0)
	
	80000230 <defy_test>:
	80000230:	00000000 	nop
	80000234:	1000ffff 	b	80000234 <defy_test+0x4>
	80000238:	3c088001 	lui	t0,0x8001
	8000023c:	2508ae68 	addiu	t0,t0,-20888
	80000240:	01000008 	jr	t0
	80000244:	00000000 	nop

# 3. 内嵌汇编

## 3.1 ARM内嵌汇编

### 3.1.1 内嵌汇编断点指令

	asm volatile(".word 0xebfffffe");	//ARM的断点

### 3.1.2 内嵌汇编操作PC指针

	//获取PC指针
	#define get_pc(x) {asm volatile("mov %0, r15" :"=r"(x));}
	/*
		mov %0	//编译器会自动选择一个空闲的CPU寄存器来装载x变量的地址(mov必须带寄存器);
				//理解为:该空闲寄存器就代表该变量.
		: "=r"(x)	//"=r"(x):有"="是output;"r"(x):无"="是input;前面的":"是修饰;
					//此处为代表output为x,即输出r15寄存器中的值给x.也即得到PC指针
		完整的语法应该是:
			asm volatile("mov %0, r15" : "=r"(x) : "r"(xxx));
		此处由于没有input,因此后面的":"也省略了.
	*/
	//操作PC指针
	#define set_pc(x) {asm volatile("mov r15, %0" ::"r"(x));}
	//此处没有output,但是中间的":"必须要有,才出现两个":"连着.

## 3.2 MIPS内嵌汇编

### 3.2.1 内嵌汇编断点指令

	asm volatile(".word 0x1000ffff; nop");	//MIPS的断点

### 3.2.2 协处理器0(CP0)的功能及操作指令

**1. 协处理器0(CP0)---系统控制协处理器**

	标号	寄存器助记符/名称		功能描述							备注
	0	Index			TLB阵列的入口索引					与MMU、TLB有关
	1	Random			产生TLB阵列的随机入口索引			与MMU、TLB有关
	2	EntryLo0		偶数虚拟页的入口地址的低位部分		与MMU、TLB有关
	3	EntryLo1		奇数虚拟页的入口地址的低位部分		与MMU、TLB有关
	4	Context			指向内存虚拟页表入口地址的指针		与MMU、TLB有关
	5	PageMask		控制TLB入口中可变页面的大小		与MMU、TLB有关
	6	Wired			控制固定的TLB入口的数目			与MMU、TLB有关
	7	保留		
	8	BadVAddr		记录最近一次地址相关异常的地址	
	9	Count			处理器记数周期
	10	EntryHi			TLB入口地址的高位部分				与MMU、TLB有关
	11	Compare			定时中断控制	
	12	Status			处理器状态和控制寄存器	
	13	Cause			保存上一次异常原因	
	14	EPC				保存上一次异常时的程序计数器	
	15	PRId			处理器标志和版本	
	16	Config			配置寄存器，用来设置CPU的参数	
	17	LLAddr			加载链接指令要加载的数据存储器地址	
	18	WatchLo			观测点watchpoint地址的低位部分		与调试有关
	19	WatchHi			观测点watchpoint地址的高位部分		与调试有关
	20	保留		
	21	保留		
	22	保留		
	23	Debug			调试控制和异常状况	与调试有关
	24	DEPC			上一次调试异常的程序计数器			与调试有关
	25	保留		
	26	ErrCtl			控制Cache指令访问数据和SPRAM		与Cache有关
	27	保留		
	28	TagLo/DataLo	Cache中Tag接口的低位部分			与Cache有关
	29	保留		
	30	ErrorEPC		上一次系统错误时的程序计数器	
	31	DESAVE			用于调试处理的暂停寄存器			与调试有关

	PS:CP0的9号寄存器($9)里面保存处理器记数周期,该值任何时刻点都不会相同.可当做一个随机值.

**2. 协处理器0(CP0)操作指令**

	mfc0:从协处理器0(CP0)的某个寄存器复制数据到通用寄存器
	mtc0:从通用寄存器复制数据到协处理器0(CP0)的某个寄存器

**3. 通过CP0的9号寄存器($9)获取随机值的内嵌汇编**

	#define get_random(val) \
		do { \
			asm volatile("mfc0 %0, $9" : "=r"(val)); \
		}while(0)

	/*
		mfc0 %0	//编译器会自动选择一个空闲的CPU通用寄存器来装载val变量的地址.
				//理解为:该空闲寄存器就代表该变量.
		$9	//表示协处理器0(CP0)的9号寄存器.存放的是处理器记数周期,作为一个随机值.
		: "=r"(val)	//语法格式mfc0 %0, $9 :"=r"(val)->output:"r"(val)->input:修饰
					//此处为代表output为val,即输出CP0的$9寄存器中的值给val.也即得到一个随机值
		//PS:如果后面的input没有,中间的":"可以不需要
	*/
md 0x1801008c 4