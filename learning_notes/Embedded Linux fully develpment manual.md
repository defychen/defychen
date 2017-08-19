# Embedded Linux Fully Development Manual

# 第1篇 嵌入式Linux开发环境构建篇
***
# 第2篇 ARM9嵌入式系统基础实例篇

## Chapter 5 GPIO接口

### 5.1 GPIO硬件介绍

GPIO(General Purpos I/O ports):通用输入/输出端口.可以通过这些端口输出高低电平/读入引脚状态(高低电平).

S3C2440有130个I/O端口,分为GPA、GPB、...、GPJ.

**5.1.1 通过寄存器来操作GPIO引脚**

1)GPxCON寄存器---配置(Configure)寄存器,即选择引脚功能.

	1)GPACON---每一位对应一根引脚(共23跟引脚).当某个置0时,相应引脚为输出引脚,此时可以在GPADAT中相应为写1或0让该引脚输出
	高/低电平;当某个置1时,相应引脚为地址线/或用于地址控制(此时GPADAT无用).一般GPACON全设为1,用于访问外部存储器件.
	2)GPxCON(B~J):每两位控制一根引脚.00(输入)、01(输出)、10(特殊功能)、11(reserved).

2)GPxDAT寄存器---数据(Data)寄存器,读写引脚.

	1)如果引脚设为输入,读对应的GPxDAT寄存器可知相应引脚的电平的状态为高电平还是低电平.
	2)如果引脚设为输出,写对应的GPxDAT寄存器可令相应的引脚输出高电平或低电平.

3)GPxUP寄存器---上拉(Up)寄存器,保护.

	1)GPxUP某位为1时,相应引脚内部无上拉电阻.
	2)GPxUP某位为0时,相应引脚使用内部上拉电阻.

![](http://i.imgur.com/1DrbR2Z.png)

上拉电阻/下拉电阻作用---当GPIO引脚处于第三态(非输出高低电平(只有在输出才存在),处于高阻态,即相当于没接芯片)时,此时的电平状态有上拉/下拉电阻确定.

**5.1.2 使用软件来访问硬件**

1)访问单个引脚

单个引脚的操作有3中:输出高低电平、检测引脚状态(输入)、中断.---最终都是通过读写寄存器来完成.

![](http://i.imgur.com/9PYXAYH.png)

实例---点亮LED1

	#define GPBCON		(*(volatile unsigned long *)0x56000010)		//GPB的配置寄存器	
	//volatile:确保每次去内存中读取变量的值,而不是从cache或寄存器中读取
	#define GPBDAT		(*(volatile unsigned long *)0x56000014)		//GPB的数据寄存器
	GPBCON = ((GPBCON | (1<<10)) & (~(1<<11)));		//GPBCON的[11:10] = 01为设置GPB5为输出
	GPBDAT &= (~(1<<5))		//GPBDAT[5]=0表示设置GPB5输出低电平,此时点亮LED1.

2)以总线方式访问硬件---Nor Flash

![](http://i.imgur.com/0OPatOe.png)

地址线ADD1~ADDR20,可寻址1MB的大小,因此Nor Flash大小为1MB.

	1)缓冲器作用:提高驱动能力、隔离前后级信号;
	2)Nor Flash(AM29LV800BB)的片选信号使用S3C2410/S3C2440的nGCS0信号.当CPU发出的地址信号处于0x0000_0000~0x07FFF_FFFF时,
	nGCS0信号有效(低电平有效),此时Nor Flash被选中(因为Nor Flash的地址范围刚好在这段区域).
	3)当nGCS0信号有效时,CPU发出的处于Nor Flash的地址范围的地址会送到Nor Flash.当需要写Nor Flash时,nWE信号为低,数据由CPU发给
	Nor Flash;当需要读Nor Flash时,nWE信号为高,数据由Nor Flash发给CPU.
	4)图中的读写地址线16根(D0~D15),因此读写操作都是以16 bit(2 byte)为单位.

实例1---地址对齐的16 bit读操作(2 byte读)

	unsigned short *pwAddr = (unsigned short *)0x2;	//0x2(10)地址.因为CPU上是从ADDR1~ADDR20(ADDR0为0,
		//但没有接到Nor Flash上),因此传到Nor Flash的A0~A19为1,0,...,0.Nor FLash上接收到的地址为0x1(第一个16 bit).
		//但由于Nor Flash是16 bit对齐,因此该地址需要"*2",即最终操作的地址为:0x1*2=0x2.
	unsgined short wVal;
	wVal = *pwAddr;		//读取Nor Flash上0x1位置的数据---真正读取Nor Flash的地址为:0x2(10B),0x3(11B)---一次2byte数据.

	//Nor Flash:因为数据线是16根(外设位宽16),因此在对Nor Flash进行操作时是地址2 byte对齐的,每次读写2 byte数据.
			读写时只需要地址2 byte对齐即可,硬件有自己的转换方法
	//DRAM:数据线32根(位宽32),对DRAM操作时是地址4 byte对齐.每次读写4 byte数据.读写时只需要地址4 byte对齐即可,
			硬件有自己的转换方法.
	//CPU位数:表示CPU一次性可以处理的字节数(e.g.32位CPU一次处理4 byte的数据).

实例2---地址不对齐的16 bit读(会有异常,一般不要这样操作)

	unsigned shor *pwAddr = (unsigned short *)0x1;		//0x1此时不是地址2 byte对齐,会导致异常.
		//要读到0x1位置的数据.需要异常处理函数.先读0x0---得到0x00,0x01两字节数据;在读0x2---得到0x10,0x11量字节数据.
		//再取0x01,0x10组成一个16 bit的数据返回.

实例3---8 bit读操作(地址2 byte对齐)

	unsigned char *pucAddr = (unsigned char *)0x6;	//0x6为2 byte对齐的地址.
	unsigned char ucVal;	//8 bit的数据一般声明为"unsigned char"
	ucVal = *pucAddr;	//pucAddr得到2 byte数据,会将低字节(即0x6地址的数据)赋给变量ucVal.0x7地址的数据丢掉.

实例4---32 bit读操作(地址2 byte对齐)

	unsigned int *pdAddr = (unsigned int *)0x6;	//读取0x6和0x8地址上的数据(32 bit---4 byte)
	unsigned int udwVal;	//32 bit的数据一般声明为"unsigned int"
	udwVal = *pdAddr;


实例5---16 bit写操作

	unsigned short *pwAddr = (unsigned short *)0x6;
	*pwAddr = 0x1234;		//给0x6写入0x1234(16 bit)---只需要给地址中的内容赋值即可.

### 5.2 GPIO操作实例:LED和按键

**实例1---使用汇编代码点亮一个LED**

	/*led_on.S---汇编代码*/
	.text
	.global _start
	_start:
		LDR	R0, =0x56000010		@LDR指令总是由右向左loader(<---).设置R0为GPBCON寄存器.设置寄存器使用"LDR"指令
		MOV R1, #0x00000400		@设置寄存器R1的值为立即数(#标识)0x00000400.设置寄存器为某个值使用"MOV"指令
		STR R1, [R0]			@STR指令总是从左向右(--->).将R1的立即数写入到[R0]寄存器中.
		//上面是配置GPB5用于输出
		LDR R0, =0x56000014		@设置R0为GPBDAT寄存器
		MOV R1, #0x00000000		@让GPBDAT(5)输出0,点亮LED1.如果改变值为0x00000020([5]=1)---熄灭
		STR R1, [R0]			@LED1点亮
	MAIN_LOOP:
		B MAIN_LOOP				@死循环

Makefile内容:

	led_on.bin:led_on.S
		arm-linux-gcc -g -c -o led_on.o led_on.S		//编译
		arm-linux-ld -Ttext 0x00000000 -g led_on.o -o led_on.elf		//连接
		arm-linux-objcopy -O binary -S led_on_elf led_on.bin		
		//将elf格式的可执行文件led_on_elf转成二进制可执行文件led_on.bin

**实例2---使用C语言代码点亮一个LED**

C程序执行的第一条指令并不在main函数中,在生成一个C程序的可执行文件时,编译器通常会在C代码中加上几个启动文件的代码(e.g. crt1.o、ctri.o、crtend.o等等---都是标准库文件).这些代码主要用于设置C程序的堆栈等,然后再调用main函数.

由于在裸板上启动代码无法运行(此时堆栈等无法设置,main函数无法调用),因此需要自己编写一个设置堆栈、跳转main函数的启动文件.

	//启动文件crt0.S---设置堆栈,跳转到C程序的main函数
	.text
	.global _start
	_start:
		ldr r0, =0x53000000		@r0设为watchdog寄存器地址
		mov r1, #0x0			@r1存放立即数
		str r1, [r0]			@写入0,清watchdog.否则CPU会不断重启
		
		ldr sp, =1024*4			@设置堆栈大小最大到4K.现在可用内存为0~4K---steppingstone
								@nandflash中的代码在复位后会搬到CPU内部的ram中,此ram只有4K

		bl main					@调用C程序中的main函数(跳转).C程序执行前必须设置好栈.
		halt_loop:
			b halt_loop			@死循环

	//C程序led_on_c.c
	#define GPBCON		(*(volatile unsigned long *)0x56000010)
	#define GPBDAT		(*(volatile unsigned long *)0x56000014)

	int main()
	{
		GPBCON = 0x00000400;	//设置GPB5为输出,[11:10]=01
		GPBDAT = 0x00000000;	//GPB5输出0,LED1点亮

		return 0;
	}

	//反汇编:arm-linux-objdump -d a.out...

**实例3---使用按键来控制LED**

	#define GPBCON		(*(volatile unsigned long *)0x56000010)
	#define GPBDAT		(*(volatile unsigned long *)0x56000014)
	#define GPFCON		(*(volatile unsigned long *)0x56000050)
	#define GPFDAT		(*(volatile unsigned long *)0x56000054)
	#define GPGCON		(*(volatile unsigned long *)0x56000060)
	#define GPGDAT		(*(volatile unsigned long *)0x56000054)

	//配置GPB5~8全部为输出
	#define GPB5_OUT	(1<<(5*2))		//配置[11:10]=01---LED1
	#define GPB6_OUT	(1<<(6*2))		//配置[13:12]=01---LED2
	#define GPB7_OUT	(1<<(7*2))		//配置[15:14]=01---LED3
	#define GPB8_OUT	(1<<(8*2))		//配置[17:16]=01---LED4

	//配置GPF2、GPF0、GPG3、GPG11为输入
	#define GPF0_IN		(~(3<<(0*2)))		//配置[01:00]=00---K4
	#define GPF2_IN		(~(3<<(2*2)))		//配置[05:04]=00---K3
	#define GPG3_IN		(~(3<<(3*2)))		//配置[07:06]=00---K2
	#define GPG11_IN	(~(3<<(11*2)))		//配置[23:22]=00---K1

	int main()
	{
		unsigned long dwDat;
		GPBCON |= (GPB5_OUT | GPB6_OUT | GPB7_OUT | GPB8_OUT);	//GPB对应引脚设为输出
		GPFCON |= (GPF0_IN | GPF2_IN);		//GPF对应的引脚设为输入
		GPGCON |= (GPG3_IN | GPG11_IN);		//GPG对应的引脚设为输入

		while(1)
		{
			//检测按下状态
			dwDat = GPGDAT;
			
			if(dwDat & (1<<11))			//表示K1没有被按下
				GPBDAT |= (1<<5);		//LED1熄灭
			else						//表示K1被按下
				GPBDAT &= (~(1<<5));	//点亮LED1

			if(dwDat & (1<<3))			//K2没有被按下
				GPBDAT |= (1<<6);		//LED2熄灭
			else
				GPBDAT &= (~(1<<6));	//点亮LED2

			dwDat = GPFDAT;
			
			if(dwDat & (1<<2))			//K3没有被按下
				GPBDAT |= (1<<7);		//LED3熄灭
			else
				GPBDAT &= (~(1<<7));	//点亮LED3
			
			if(dwDat & (1<<0))			//LED4没有被按下
				GPBDAT |= (1<<8);		//LED4熄灭
			else
				GPBDAT &= (~(1<<8));	//点亮LED4
		}
	
		return 0;
	}
***
## Chapter 6 存储控制器

### 6.1 使用存储控制器访问外设的原理

**1.S3C2410/S3C2440的地址空间**

1.S3C2410/S3C2440按BANK来划分地址空间(每个BANK为128MB),有8个BANK供1GB的地址空间.

2.S3C2410/S3C2440对外引出27根地址线ADDR0~ADDR26,其访问范围为128MB(刚好一个BANK大小).CPU还对外引出8根片选信号线(nGCS0~nGCS7---低电平有效,会选中对应的BANK),对应于BANK0~BANK7(8个BANK),构成1GB的地址空间.

**S3C2410/S3C2440存储控制器地址空间分布图---物理地址空间**

	-----------------------------------------------------------------------------------------------------
					OM[1:0]=01,10		
				---------------------
					Boot Internal
					 SRAM(4KB)								OM[1:0]=00	
	0x4000_0000	---------------------					---------------------
					SROM/SDRAM								SROM/SDRAM				2MB/4MB/8MB/16MB---BANK7
					  (nGCS7)								  (nGCS7)				/32MB/64MB/128MB(可变)
	0x3800_0000	---------------------					---------------------
					SROM/SDRAM								SROM/SDRAM				2MB/4MB/8MB/16MB---BANK6
					  (nGCS6)								  (nGCS6)				/32MB/64MB/128MB(可变)
	0x3000_0000	---------------------					---------------------
					   SROM									    SROM				
					  (nGCS5)								  (nGCS5)				128MB(固定)BANK5
	0x2800_0000	---------------------					---------------------
					   SROM									    SROM				
					  (nGCS4)								  (nGCS4)				128MB(固定)BANK4
	0x2000_0000	---------------------					---------------------
					   SROM										SROM				
					  (nGCS3)								  (nGCS3)				128MB(固定)BANK3
	0x800_0000	---------------------					---------------------
					   SROM										SROM				
					  (nGCS2)								  (nGCS2)				128MB(固定)BANK2
	0x1000_0000	---------------------					---------------------
					   SROM										SROM				
					  (nGCS1)								  (nGCS1)				128MB(固定)BANK1
	0x0800_0000	---------------------					---------------------
					   SROM									Boot Internal				
					  (nGCS0)								  SRAM(4KB)				128MB(固定)BANK0
	0x0000_0000	---------------------					---------------------

		[Not using NAND Flash for Boot ROM]				[Using NAND flash for Boot ROM]
	-----------------------------------------------------------------------------------------------------
	//从上图可以看到,CPU可访问的物理地址为1GB---0~29的地址范围

S3C2410/S3C2440的寄存器地址范围处于0x4800_0000~0x5FFF_FFFF.

	//S3C2440几个重要的功能部件的寄存器地址范围
			---------------------------------------------------
			功能部件				起始地址				结束地址
			---------------------------------------------------
			中断控制器		0x4A00_0000				0x4A00_001C
			---------------------------------------------------
				DMA			0x4B00_0000				0x4B00_00E0
			---------------------------------------------------
			Watchdog		0x5300_0000				0x5300_0008
			---------------------------------------------------
				IIC			0x5400_0000				0x5400_000C
			---------------------------------------------------
				...			...						...
			---------------------------------------------------

**2.物理地址(存储控制器)与外设的关系**

1.外设容量的计算---e.g.Nor Flash

	//Nor Flash有20根地址线,16位的数据线.因此其容量的计算为:
	容量 = 2^20(地址线) * 16(数据位数)bit
	    = 1M * 16bit = 2MB

	//DRAM有13根行地址线,9根列地址线,2根用于L-Bank选择,32位的位宽(其实是两片16位的SDRAM芯片并联形成32位位宽)
	容量 = 2^(13+9+2) * 32(数据位数)bit
		= 16M * 32bit = 64MB

2.物理地址(存储控制器)各个BANK所接外设情况如下:

	-------------------------------------------------------------------------------
	BANKx	外设名称		起始地址			结束地址			大小(byte)		位宽		地址线
	-------------------------------------------------------------------------------
	BANK0	Nor Flash	0x0000_0000		0x001F_FFFF		2M				16		20
	-------------------------------------------------------------------------------
	BANK1	IDE			0x0800_0000		0x0800_000F		16				16		3
	-------------------------------------------------------------------------------
	BANK2	IDE			0x1000_0000		0x1000_000F		16				16		3
	-------------------------------------------------------------------------------
	BANK3	10M网卡		0x1900_0000		0x190F_FFFF		1M				16		20---很奇怪
	-------------------------------------------------------------------------------
	BANK4	10/100M网卡	两个地址0x2000_0000和0x2000_0004					16		1---奇怪
	-------------------------------------------------------------------------------
	BANK5	扩展串口A	0x2800_0000		0x2800_0007		8				8		3---片选决定
	-------------------------------------------------------------------------------
	BANK5	扩展串口B	0x2900_0000		0x2900_0007		8				8		3--片选决定
	-------------------------------------------------------------------------------
	BANK6	SDRAM		0x3000_0000		0x33FF_FFFF		64M				32		13+9+2=24
	-------------------------------------------------------------------------------

3.SDRAM的选择

	1)SDRAM内部是一个存储阵列(如同表格一样).整个表格由行、列划分(13根行地址、9根列地址).
	2)SDRAM内部有4个表格,称为L-Bank(逻辑Bank),由两根地址线控制
	3)搜寻方法是先确定表格,再由行、列确定存储单元,每个存储单元存放4字节数据(4字节对齐).因此才有总容量64MB

### 6.2 存储控制器操作实例: 使用SDRAM

从Nand Flash启动CPU时,CPU会通过内部的硬件将Nand Flash开始的4KB数据复制到CPU内部的RAM中(该段RAM称为Steppingstone,起始地址为0),然后跳转到该段RAM中执行.

程序编写步骤:

1)使用汇编设置好存储控制器,使外接的SDRAM可用---物理地址每段划分及每段的相应配置

2)把程序本身从Steppingstone复制到SDRAM处

3)跳转到SDRAM中执行

**程序代码**

	//head.S:设置SDRAM,将程序复制到SDRAM,然后跳转到SDRAM继续执行
	.equ		MEM_CTL_BASE		0x48000000		//存储控制寄存器基址---用于配置每个BANK的作用
	.equ		SDRAM_BASE			0x30000000		//SDRAM的基址(物理地址)
	
	.text
	.global _start
	_start:
		bl disable_watch_dog		@关闭watchdog,否则CPU会不断重启
									@代码段的起始地址(0x3000_0000-在Makefile中指定),SDRAM中的位置.
		bl memsetup					@设置存储控制器---0x3000_0004(4 byte对齐??).在steppingstone里是4
		bl copy_steppintstone_to_sdram	@复制代码到SDRAM中---0x3000_0008
		ldr pc, =on_sdram			@跳到SDRAM继续执行---0x3000_000C.on_sdram在连接时会被确定为0x3000_0010
	on_sdram:						
		ldr sp, =0x34000000			@设置栈---解析该指令时,其地址会解析为:0x3000_0010.
		bl main						@跳转到main函数执行

	halt_loop:
		b halt_loop

	/*后面的指令都是由位置无关的指令跳转到,因为全部在steppingstone里执行*/
	disable_watch_dog:			@bl跳转是位置无关的相对跳转指令,因此这些均在Steppingstone里执行---无地址信息
		mov r1, #0x53000000		@watchdog寄存器0x5300_0000,该指令等价于ldr r1, =0x53000000.此时r1=0x5300_0000
		mov r2, #0x0			@r2=0x0
		str r2, [r1]			@将r2的值(0x0)写入到[r1]这个地址里,即让0x5300_0000里的值为0x0.
		mov pc, lr				@让PC指针指向lr(链接位置).每次跳转会将返回地址放入lr指令.因此返回只需要mov pc, lr即可

	copy_steppingstone_to_sdram:
		@复制steppingstone的4KB数据到SDRAM中
		@steppingstone的起始地址为0x0000_0000，SDRAM的起始地址为0x3000_0000
		mov r1, #0				@r1保存steppingstone中的地址
		ldr r2, =SDRAM_BASE		@r2保存SDRAM中的地址
		mov r3, #4*1024			@r3保存steppingstone的终止地址(即4K处的地址)
	1:		@实现循环
		ldr r4, [r1], #4		@实现将r1的4 byte数据复制到r4,并让r1地址+4
		str r4, [r2], #4		@实现将r4的4 byte数据复制到r2,并让r2地址+4
		//上面两步实现将steppingstone的数据以4 byte为单位复制到SDRAM
		cmp r1, r3				@检测r1地址与r3是否相等,决定数据是否复制完成
		bne 1b					@bne:检测结果不为0,1b:跳转到1
		mov pc, lr				@返回

	/*初始化SDRAM*/
	memsetup:		@配置存储控制器的寄存器以便使用SDRAM等外设---使用物理地址挂上的设备需要配置存储控制器的一些寄存器
		mov r1, #MEM_CTL_BASE	@存储控制器的13个寄存器的起始地址
		adrl r2, mem_cfg_val	@adr:指定地址,后面的l:表示数据为long.相当于r2存放mem_cfg_val标号的地址地址
		add r3, r1, #52			@r1+52(13*4---13个寄存器,每个寄存器4byte).然后存放到r3.此时r3为存储控制器的终止地址
	1:	@实现循环
		ldr r4, [r2], #4		@复制r2的4 byte到r4,并让r2地址+4
		str r4, [r1], #4		@复制r4的4 byte到r1,并让r1地址+4
		cmp r1, r3				@判断是否设置完13个寄存器
		bne 1b					@没有完成,继续
		mov pc, lr				@返回

	.align 4		@声明为4 byte对齐
	mem_cfg_val:
		@ 存储控制器13个寄存器的设置值
		.long	0x22011110			@BWSON寄存器的设置值
		.long	0x00000700			@BANKCON0寄存器的设置值
		.long	0x00000700			@BANKCON1寄存器的设置值
		.long	0x00000700			@BANKCON2寄存器的设置值
		.long	0x00000700			@BANKCON3寄存器的设置值
		.long	0x00000700			@BANKCON4寄存器的设置值
		.long	0x00000700			@BANKCON5寄存器的设置值
		.long	0x00018005			@BANKCON6寄存器的设置值
		.long	0x00018005			@BANKCON1寄存器的设置值
		.long	0x008C07A3			@REFRESH寄存器的设置值
		.long	0x000000B1			@BANKSIZE寄存器的设置值
		.long	0x00000030			@MRSRB6寄存器的设置值
		.long	0x00000030			@MRSRB7寄存器的设置值

**Makefile**

	sdram.bin : head.S leds.c		//leds.c与之前的一样
		arm-linux-gcc -c -o head.o head.S
		arm-linu-gcc -c -o leds.o leds.c
		arm-linux-ld -Ttext 0x30000000 head.o leds.o -o sdram.elf
		//arm-linux-ld:指定链接; -Ttext 0x3000000:指定代码段起始地址
		arm-linux-objcopy -O binary -S sdram_elf sdram.bin	//复制sdram_elf成sdram.bin
		arm-linux-objdump -D -m arm sdram_elf > sdram.dis	//反汇编
	clean:
		rm -f sdram.dis sdram.bin sdram_elf *.o
***
## Chapter 9 中断体系结构

### 9.1 S3C2410/S3C2440中断体系结构

**1.ARM体系CPU的7种工作模式**

1)用户模式(usr):ARM处理器正常的程序执行状态;

2)快速中断模式(fiq):用于高速数据传输或通道处理;

3)中断模式(irq):用于通用的中断处理;

4)管理模式(svc):操作系统使用的保护模式;

5)数据访问终止模式(abt):当数据/指令预取终止时进入该模式,用于虚拟存储及存储保护;

6)系统模式(sys):运行具有特权的操作系统任务;

7)未定义指令终止模式(und):当未定义的指令执行时进入该模式,用于支持硬件协处理器的软件仿真.

	除了用户模式(大多数程序运行于此)外,其他6种模式都属于特权模式(主要用于处理中断、异常或者访问了被保护的系统资源).

ARM CPU两种工作状态:

1.ARM状态:CPU执行32 bit字对齐(32 bit对齐)的ARM指令;	---一般CPU运行在ARM状态.

2.Thumb状态:CPU执行16 bit半字对齐(16 bit对齐)的Thumb指令.

ARM920T有31个通用寄存器和6个程序状态寄存器(32位,属于CPU的寄存器).37个寄存器被分为7组,不同的模式下可以使用不同的特定寄存器.

![](http://i.imgur.com/E55h87j.png)

	1---37个寄存器:
		1---31个通用寄存器:
		r0 ~ r15(PC)---16个
		r8_fiq ~ r14_fiq---7个,用于快速中断模式
		r13_svc ~ r14_svr---2个,用于管理模式
		r13_abt ~ r14_abt---2个,用于数据访问终止模式
		r13_irq ~ r14_irq---2个,用于中断模式
		r13_und ~ r14_und---2个,用于未定义指令终止模式
		2---6个程序状态寄存器
		CPSR---(Current Program Status Register):当前程序状态寄存器
		SPSR_fiq, SPSR_svc, SPSR_abt, SPSR_irq, SPSR_und---(Saved Program Status Register):程序保存状态寄存器
	2---特殊寄存器说明
		r13---栈指针寄存器(sp),用于保存栈指针
		r14---链接寄存器(lr),用于子程序返回,保存前一个工作模式r15寄存器中的值.
		r15---程序计数器(pc指针).
	3---CPSR某些位说明(32位寄存器)
		[4:0]---用于模式选择
			10000---用于模式
			10001---快速中断模式
			10010---中断模式
			10011---管理模式
			10111---数据访问终止模式
			11111---系统模式
		[5]---T位,用于选择CPU工作状态
			= 1---Thumb状态
			= 0---ARM状态,一般为0
		[6]---F位,用于禁止/使能快速中断
			= 1---禁止快速中断(关快速中断)
			= 0---使能快速中断(开快速中断)
		[7]---I位,用于禁止/使能中断
			= 1---禁止中断(关普通中断)
			= 0---使能中断(开普通中断)

**CPU异常的处理过程**

	//进入异常CPU所做的事情
	1)在异常工作模式的lr寄存器(r14)保存前一个工作模式的下一条将执行指令的地址(一般这个地址为当前PC+4或者+8);
	2)将CPSR的值复制到异常模式的SPSR中;
	3)将CPSR的工作模式位[4:0]设为对应的异常模式
	4)令PC值等于该异常模式在异常向量表中的地址,也就是跳去异常向量中的相应指令
	
	//从异常返回CPU所做的事情
	1)将异常模式中的lr寄存器中的值减去一个适当的值然后赋给PC寄存器;
	2)将异常模式中的SPSR的值赋给CPSR.

**2.S3C2410/S3C2440中断控制器**

CPU运行过程中,检测外设发生某些不预期事件的方法:

1)查询方式:程序循环的检测设备的状态并做出相应的反应.---占用CPU资源高,浪费资源

2)中断方式:当某事件发生时,硬件会设置某个寄存器;CPU在执行完每一个指令时,通过硬件查看该寄存器的状态,如果状态改变了就中断当前程序流程,跳转到一个固定的地址处理该事件,处理完后返回继续执行被中断的程序.---实现复杂,效率高

中断处理过程:

	1)中断控制器汇集外设发出的中断信号,并告诉CPU;
	2)CPU保存当前程序运行环境(各个寄存器),调用中断服务程序(ISR---Interrupt Service Routine)来处理中断;
	3)在ISR中通过读取中断控制器、外设相关寄存器识别具体中断,进行相应处理;
	4)清理中断:通过读写中断控制器、外设相关寄存器来清理中断;
	5)恢复被中断程序,继续执行.