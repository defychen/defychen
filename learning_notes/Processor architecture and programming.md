# Processor architecture and programming

## Chapter 1. 服务器与处理器

### 1.1 服务器体系结构

#### 1.1.1 服务器的分类

机架式服务器(Rack Server)也称为机架安装服务器(Rack-mounted Server),是服务器主流机械结构之一.

	1.机架式服务器安装在标准的19英寸(1 inch = 2.54 cmd)机架内;
	2.服务器的宽度为19英寸,高度以1U为单位,1U等于1.75英寸(4.45cm).高度通常有1U、2U、4U、8U等规格.1U和2U
		最为常见.

#### 1.1.2 服务器的性能评价

**1.TPC测试基准**

用的很少.

**2.SPEC测试基准**

SPEC指的是标准性能评估机构(Standard Performance Evaluation Corporation).SPEC CPU测试基准通过不同方式度量处理器性能:

	SPECspeed Metrics(SPEC速度测量):测量计算机完成单一任务时间的方式,通过SPECint 2006 benchmark指
		标呈现,用于比较不同计算机完成单一任务的能力;
	SPECrate:衡量在特定时间长度内能够完成多少任务的方式(也叫吞吐率(Throughtput)测量、容量(Capacity)
		测量或速度(Rate)测量),通过SPECint_rate 2006 benchmark指标呈现,评价机器承载大量任务的能力,
		通常用于多CPU系统的评价.

SPEC CPU 2006给出的测试结果有"基础(Base)"和"峰值(Peak)"两种.在基础测试时需要限制编译时的优化参数,以保证测试的公平,而在峰值测试的限制则比较宽松.

SPEC CPU 2017(包含多大43项工业标准的基准测试),主要分为:

	1.针对整数计算的SPECspeed 2017 Integer和SPECrate 2017 Integer测试组;
	2.针对浮点运算的SPECspeed 2017 Floating Point和SPECrate 2017 Floating Point测试组;
	PS:
		1.SPECspeed 2017 Integer和SPECspeed 2017 Floating Point测试组用于比较完整的单一任务在计算
			机系统上的执行时间的测试;
		2.SPECrate 2017 Integer和SPECrate 2017 Floating Point测试组用于吞吐量度量,也即测试单位时
			间的工作任务量.

#### 1.1.3 服务器的可靠性和管理

RAS特性:Reliability(可靠性)、Availabitiy(可用性)、Serviceability(可服务性).

RAS技术可以通过以下方式有效减少故障出现的概率:

	1.在造成系统失效之前检测并修正瞬时错误;
	2.定位和替换失效部件;
	3.提前预测失效,以便在计划的维护时间内更换系统或部件.

### 1.2 服务器处理器

#### 1.2.1 指令流水线

指令内部的并行:一条指令执行时各微操作之间的并行.

指令级并行:并行执行两条或多条指令.

任务级并行:并行执行两个或两个以上的任务(程序段).

作业或程序级并行(最高级):并行执行两个或两个以上的作业或程序.

超标量(superscalar)设计采用多发射技术,在处理器内部设置多条并行执行的指令流水线,通过在每个时钟周期内向执行单元发射多条指令实现指令级并行.

#### 1.2.2 多线程处理器

SMT(Simultaneous Multi-Threading):同时多线程,允许在一个时钟周期内发送来自不同线程的多条指令.

#### 1.2.3 同构多核处理器与异构多核处理器

同构多核处理器(Homogenous Multi-Core):处理器内的所有计算核心结构相同,对位对等;

异构多核处理器(Heterogeneous Multi-Core):处理器通过配置不同特点的核心来优化处理器内部结构,实现处理器性能的最优化,并能有效降低系统功耗.

	e.g. GPU+CPU集成在一颗芯片上.

#### 1.2.4 多核处理器的对称性

对称多处理(Symmetric Multi-Processing, SMP)结构:指处理器片内包含相同结构的核(低位均等),多个核紧密耦合并运行一个统一的操作系统.

非对称多处理结构(Asymmetric Multi-Processing, AMP)结构:异构多核处理器或同构多核运行不同的操作系统.

### 1.3 服务器技术基础

#### 1.3.1 多核系统的存储结构

![](images/multi_cache_structure1.png)

![](images/multi_cache_structure2.png)

**1.片内私有L1 Cache结构**

由L1和L2两级组成(a结构).每个核有自己私有的L1 Cache(分为L1 I-Cache核L1 D-Cache).多核共享L2 Cache,放在处理器之外--->基本已经废弃了.

**2.片内私有L2 Cache结构**

保留私有L1 I-Cache和L1 D-Cache,L2为各个核私有(b结构).多核共享主存.

**3.片内共享L2 Cache结构**

与片内私有L2 Cache结构.区别在于处理器内的私有L2 Cache变为多核共享(c结构).

**4.片内共享L3 Cache结构**

在片内私有L2 Cache结构的基础上增减片内多核共享L3 Cache,使存储系统的性能有了较大的提高(d结构).

#### 1.3.2 多核处理器的Cache一致性

**1.单处理器系统**

Cache一致性问题主要是在内存操作过程中如何保持各级Cache中的数据副本与主存内容的一致--->使用全写法(写穿式)可解决.

**2.多核处理器系统**

1.写数据的共享

某个处理器采用全写法或写回法修改某一个数据块时,会引起其他处理器的Cache中同一副本的不一致--->采用总线监听(Bus Snooping)协议或目录协议(Directory)解决.

2.输入/出活动

如果输入/输出设备直接连接在系统总线上,输入/输出活动也会导致Cache不一致--->采用禁止输入/输出通道解决.

3.核间线程迁移

核间线程迁移就是把一个尚未执行完的线程调度到另一个空间的处理器去执行.这有可能引起Cache的不一致--->采用禁止核间线程迁移来解决.

#### 1.3.3 UMA架构与NUMA架构

参考"Run Linux Kernel.md".

#### 1.3.4 内存顺序模型与内存屏障

略.

#### 1.3.5 服务器虚拟化技术

略.

#### 1.3.6 PCI Express技术

略.

## Chapter 2. ARMv8-A体系结构

### 2.1 ARMv8-A处理单元的核心架构

无论是AArch32还是AArch64,其指令长度都是32-bit(4B).

	AArch32与AArch64的本质区别:
	AArch32指令集使用32-bit寄存器;AArch64指令集使用64-bit寄存器,并使用64-bit计算模式.

#### 2.1.1 ARMv8-A架构的处理器运行模式

**1.ARMv8-A的执行状态**

1.AArch64执行状态

	1.四个异常等级(EL0-EL3);
	2.支持64-bit VA,48-bit/52-bit PA;
	3.提供31个64-bit通用寄存器X0-X30.X30是过程链接寄存器(Procedure Link Register, PLR),还包括一个
		64-bit程序计数器PC,若干堆栈指针寄存器SP和若干异常链接寄存器ELR;
	4.提供了32个128-bit的寄存器支持SIMD向量和标量浮点操作;
	5.提供了一组PSTATE(Process STATE,处理状态)参数,用于指示处理单元的当前状态.

2.AArch32执行状态

	1.支持A32和T32指令集;
	2.支持32-bit VA;
	3.提供13个32-bit通用寄存器和一个32-bit程序计数器PC,堆栈指针寄存器SP及链接寄存器LR;
	4.提供了32个64-bit的寄存器支持增强SIMD向量和标量浮点操作;
	5.提供了一组PSTATE(Process STATE,处理状态)参数,用于指示处理单元的当前状态.

3.状态切换

	AArch64和AArch32状态切换称为交互处理(Interprocessing).

**2.ARMv8-A架构支持的指令集**

	1.AArch64使用A64指令集,该指令集的所有指令均为32-bit等长指令字;
	2.AArch32使用A32指令集,为32-bit等长指令字结构;
	3.T32使用之前的Thumb/Thumb-2指令集,为16-bit/32-bit可变长指令字结构.

A64指令集特点

	1.A64去掉ARMv7的LDM/STM(load multiple/store multiple),指令复杂,不利于设计高效的处理器存储系统;
	2.A64指令集保留很少的条件执行指令,这些指令实现复杂度高,好处不明显;
	3.A64指令集的大部分指令都不再是条件执行指令;
	4.ARMv8-A架构将硬件浮点运算设计为必须部件.

实例:

	A64加法
		AA X0, X1, X2	//将X1+X2的结果送到X0
	A32加法
		ADD W0, W1, W2	//将W1+W2的结果送到W0

**3.ARMv8-A支持的数据类型**

	1.支持8-bit的byte, 16-bit的half-word, 32-bit的word, 64-bit的dword以及128-bit的quardword;
	2.浮点支持half-precision(半精度), single-precision(单精度), double-precision(双精度);
	3.支持2种向量类型(向量数据由多个相同类型的数据组合而成):
		1.增强的SIMD(Advanced SIMD),也就是Neon;
		2.SVE(Scalable Vector Extension,可伸缩向量扩展).

**4.ARMv8-A的异常等级与安全模型**

略.

**5.ARMv8-A的虚拟化架构**

ARMv8-A典型的虚拟化系统的基本架构:

	1.虚拟机(Virtual Machines)由运行在EL1和EL0两个异常等级的软件组成;
	2.运行在EL2异常等级的虚拟机管理器负责在各个虚拟机之间进行切换.虚拟机管理器负责为每个虚拟机分配一个
		虚拟机标识(Virtual Machine Identifier, VMID);
	3.系统中可以运行若干客户操作系统,客户操作系统运行在EL1级虚拟机上;
	4.每个客户操作系统虚拟机上运行的应用程序通常处于EL0异常等级.

**6.ARMv8-A的调试支持**

略.

#### 2.1.2 ARMv8-A架构的寄存器

**1.AArch64状态下的通用寄存器**

1.通用寄存器R0-R30

在汇编语言中被标识为x0-x30.x30是过程链接寄存器(PLR),本质不属于通用寄存器.A64指令集一般使用x0-x29等30个通用寄存器.

	64-bit访问时,通用寄存器名为x0-x30;
	32-bit访问时,通用寄存器名为w0-w30.为x0-x30的低32-bit.读时时直接丢弃高32-bit数据,写时高32-bit被清0.
	e.g.
		x0寄存器的值为:0x8899aabbccddeeff
		w0读时值为:0xccddeeff;
		w0写入0xffffffff后,x0的值为:0x00000000ffffffff.

通用寄存器在任何时刻和任何异常等级下都能被访问.

2.SIMD和浮点寄存器V0-V31

在AArch64执行状态下,处理单元有32个SIMD和浮点寄存器,命名为V0-V31,每个寄存器的位宽为128-bit.这组寄存器独立于通用寄存器,专门用于浮点运算和向量操作.V代表向量(Vector),有时也称为V寄存器.

	128-bit放你问时,寄存器名为Q0-Q31;
	64-bit放你问时,寄存器名为D0-D31;
	32-bit放你问时,寄存器名为S0-S31;
	16-bit放你问时,寄存器名为H0-H31;
	8-bit放你问时,寄存器名为B0-B31;
	低位宽访问时,与w0-w30访问类似.

#### 2.1.3 ARMv8-A架构的异常与中断

根据中断源分为以下4种中断:

**1.共享外设中断(Shared Peripheral Interrupt, SPI)**

外设的这类中断请求可以被连接到任何一个处理器内核(中断号:0~15, 32~1019和4096~5119).

**2.私有外设中断(Private Peripheral Interrupt, PPI)**

只属于某一个处理器内核的外设的中断请求,例如通用定时器的中断请求(中断号:16~31和1056~1119).

**3.软件产生的中断(Software Generated Interrupt, SGI)**

由软件写入中断控制器内的SGI寄存器引发的中断请求,通常用于处理器间通信(中断号:0~15).

**4.特定位置外设中断(Locality-specific Periphral Interrupt, LPI)**

边沿触发的基于消息的中断,其编程模式与其他中断源完全不同(中断号:8192以上).

**MSI**

MSI(Message-Signaled Interrupt-消息信号中断):外设通过向中断控制器中的寄存器执行写操作触发中断请求,不再需要专门的中断请求信号线.一般为LPI中断.

### 2.2 ARMv8-A处理单元的存储系统结构

#### 2.2.1 ARMv8-A架构的内存模型

**1.AArch64地址变换**

内核的地址映射是全局变换,即内核区域对当前运行进程都有效,变换的页面也是全局的;

应用程序地址映射是非全局的,即只针对当前运行的进程,变换的页面是针对进程的.

	ASID(Address Space Identifier,地址空间标识):定义的页面与某个具体进程相关.

**2.TTBR的使用**

	1.AArch64状态下,EL2和EL3运行的程序只能使用TTBR0,没有TTBR1.因此EL2和EL3的虚拟地址范围只能落在:
		0x00000000_00000000--->0x0000FFFF_FFFFFFFF
	2.EL0(用户空间)只能使用TTBR0_EL1,地址范围:
		0x00000000_00000000--->0x0000FFFF_FFFFFFFF
	3.EL1(kernel空间)只能使用TTBR1_EL1,地址范围:
		0xFFFF0000_00000000--->0xFFFFFFFF_FFFFFFFF

**3.Device空间特点**

	1.device空间是non-cacheable,且是外部可共享的;
	2.device空间分为3个属性:
		G(Gathering):表示是否可聚合,即多次的读写存储器访问是否可以合并为单一的事务;
		R(Reordering):表示乱序,即是否允许乱序执行;
		E(Early Write Acknowledgement):表示是否允许提前返回写完成响应,即如果数据写到缓冲区后,可以提前
		回写完成响应,否则必须等到写操作完成才能结束.
	3.device属性组合:
		一般使用4种属性组合:Device-nGnRnE(最严格)、Device-nGnRE、Device-nGRE和Device-GRE(最宽松).

##### 2.2.2 SMMU

略.

#### 2.2.3 ARMv8-A的服务器特性

略.

## Chapter 3. 鲲鹏处理器片上系统架构

RequesterID:PCIe中的请求者标识.

PASID(Process Address Space ID,进程地址空间标识):某个请求者标识的进程地址空间标识,通常与内核中的不同进程的地址空间相关.

StreamID(数据流标识):是SMMU中用于检索地址转换表的索引.

DeviceID(设备标识):是ARM的GIC中的中断翻译服务(ITS部件)用于检索中断翻译表的索引.

对应关系:

	RequesterID--->StreamID;
	PASID[15:0]--->SubStreamID;
	RequesterID == SMU StreamID == ITS DeviceID

## Chapter 4. 鲲鹏软件生态和架构

### 4.1 半导体厂商的业务模式

**1.Intel模式**

集成芯片设计和制造.

**2.Fabless(无晶圆)模式**

像NVIDIA、AMD那样,只设计芯片,物理制造交给代工厂(e.g. 台积电、三星电子、UMC联电、GlobalFoundries等).

### 4.2 ARM许可证授权的3种类型

**1.POP授权(Processor Optimization Pack,处理器优化包/物理IP包)**

等级最低的,客户可以直接购买使用ARM优化过的处理器方案,适用于需要ARM处理器却没有能力自己实现的客户.授权费用低,但是处理器类型、代工厂、工艺等都是ARM规定好的,自由发挥的空间很小.

**2.处理器授权**

使用ARM设计的微处理器或GPU的授权.ARM提供有关如何在硅片上实现设计的准则,但如何将设计变成芯片,如配置哪些模块、哪些外设、多少个核心、多少缓存、多高频率、什么工艺、谁来代工等问题,则由客户自行决定.

**3.架构/指令集授权**

等级最高的授权.ARM向客户授权某种架构(e.g.ARMv7,ARMv8),客户可以随意采用该架构并按自己的意愿设计SoC,如对ARM架构进行改造,甚至可以对指令集进行扩展和缩减.授权费用很高,会与ARM公司自己设计的公版处理器构成竞争.

	主要公司:苹果的Swift,Cyclone,Bionic;高通的Scorpion,Krait,Kyro;华为的麒麟,鲲鹏等.

### 4.3 ACPI

ACPI(Advanced Configuration and Power Management Interface,高级配置和电源管理接口):BIOS运行过程种,生成这些表格.然后linux访问ACPI表格来获得一些硬件的内存地址.主要在PC和服务器领域中使用.

**1.linux内核硬件设备探测的方式**

1.通过内核代码静态描述实现

	赢编码方式,早期的linux在arch/arm/plat-xxx和arch/arm/mach-xxx下有很多冗余代码.2011年开始改用
		Device Tree(DT)方式.

2.通过Device Tree进行静态匹配和加载

3.通过BIOS ACPI表进行动态配置和加载

4.通过总线自动枚举

	适合可以支持自动枚举的总线上的设备(e.g. PCI总线和USB总线).

**2.ACPI表的查看**

1.ACPI表的目录

	所有的ACPI表位于:/sys/firmware/acpi/tables

2.复制表到*.aml

	sudo cat /sys/firmware/acpi/tables/DSDT > /usr/xxx/DSDT.aml

3.安装软件iasl

	sudo apt-get install iasl

4.进行转换

	iasl -d DSDT.aml

5.这样可以在当前目录下发现所要的ACPI表文件

	vim DSDT.dsl

PS:DSDT(Differentiated System Description Table):是ACPI规范的一部分,包含了所有和基本系统不同的设备的信息.