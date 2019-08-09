# Compute Organization and Design(The Hardware/Software Interface)

## Chapter 1 计算机概要与技术

### 1.1 引言

#### 1.1.1 常用容量表示方法

1.KB/MB/GB/TB/PB/EB/ZB/YB的意思

	KB(kilobyte):数值为10^3;
	MB(megabyte):数值为10^6;
	GB(gigabyte):数值为10^9;
	TB(terabyte):数值为10^12;
	PB(petabyte):数值为10^15;
	EB(exabyte):数值为10^18;
	ZB(zettabyte):数值为10^21;
	YB(yottabyte):数值为10^24.

2.KiB/MiB/GiB/TiB/PiB/EiB/ZiB/YiB的意思

	KiB(kibibyte):数值为2^10;
	MiB(mebibyte):数值为2^20;
	GiB(gibibyte):数值为2^30;
	TiB(tebibyte):数值为2^40;
	PiB(pebibyte):数值为2^50;
	EiB(exbibyte):数值为2^60;
	ZiB(zebibyte):数值为2^70;
	YiB(yobibyte):数值为2^80.

#### 1.1.2 一些常用概念

	1.PMD(Personal Mobile Device):个人移动设备;
		e.g.智能手机或平板电脑;
	2.云计算(cloud computing):替代传统的服务器,建立在WSG(Warehouse Scale Compute:仓储规模计算机)巨
	型数据中心之上.Amazon和Google构建了含有100 000台服务器的WSG,一些公司可以租用其中不部分为PMD提供软
	件服务,而不用自己构建WSG;
	3.SaaS(Software as a Service):软件即服务,在网络上以服务的方式提供软件和数据.运行方式通常不是在本地
	设备上运行所有的二进制代码,而是通过诸如运行在本地客户端的浏览器等小程序登录到远程服务器上执行.
		e.g.Web搜索和社交网络.

### 1.2 计算机系统结构中的8个伟大思想

	1.面向摩尔定律的设计;
	2.使用抽象简化设计;
	3.加速大概率事件;
	4.通过并行提高性能;
	5.通过流水线提高性能;
	6.通过预测提高性能;
	7.存储器层次;
	8.通过冗余提高可靠性.

### 1.3 制造技术相关概念

#### 1.3.1 概念

**1.晶体管(transistor)**

晶体管:一种由电信号控制的简单开关.

**2.集成电路(IC:ingerated circuit)**

集成电路:由成千上万个晶体管组成的芯片.

**3.超大规模集成电路(VLSI:very large-scale integrated circuit)**

超大规模集成电路:由数十万到数百万晶体管组成的电路.

#### 1.3.2 芯片制造

用化学方法对硅添加某些材料,是硅的某些区域转变为:

	1.良好的导电体(类似细微的铜线或铝线);
	2.良好的绝缘体(类似塑料或玻璃膜);
	3.可控的导电体或绝缘体(类似开关).

制造流程:

![](images/flow_of_chip_manufacturing.png)

硅锭/晶圆/Die/Socket:

	1.硅锭(silicon crystal ingot):一块由硅晶体组成的棒.直径约8-12英寸,长度约12-24英寸;
	2.晶圆(wafer):厚度不超过0.1英寸的硅锭片,用来制造芯片;
	3.Die:从晶圆(wafer)上切割下来的一个个的小方块(方形的原因是便于切割),并在该Die上面将逻辑电路刻在
		上面构成真正的Die.如果Die的面积足够小,wafer的利用率可以接近于100%;
	4.Socket:将1个或N个CPU Die封装起来形成一个CPU Package,也叫CPU Socket;
	PS:Die的大小越大,CPU Die出错的概率越高,良品率也越低,成本相应就越高.

Intel和AMD芯片区别:

	1.Intel Xeon系列(服务器芯片)将整个CPU Socket做到一个CPU Die上.优点是:CP内部直接各组件的连接是片内
		总线互联,有更多资源共享(e.g.所有的CPU内核共享L3),整体的性能更高;缺点是成本大,价格高.
	2.AMD EYPC CPU每个CPU Socket有4个CPU Die,每个CPU Die包含4个CPU 内核.CPU Die之间通过片外总线
		(Infinity Fabric)互联,不同Die上的CPU内核不能共享CPU Cache.这种分布导致虽然单Core与Intel差不
		多,性能却赶不上Intel Xeon处理器.但是好处是便宜.

### 1.4 性能

#### 1.4.1 性能度量

**1.个人计算机与数据中心的区别**

个人计算机关心的是响应时间(response time),数据中心关心的是吞吐率(throughout).

	响应时间:也叫执行时间(execution time),是计算机完成某任务所需的总时间(包括硬盘访问、内存访问、IO
		活动、操作系统开销和CPU执行时间等);
	吞吐率:也叫带宽(bandwidth),表示单位时间内完成的任务数量.

**2.CPU时钟周期(clock cycle)和时钟频率(clock rate)**

	CPU时钟周期为250ps,对应的CPU时钟频率为4GHz.

#### 1.4.2 CPU的性能

CPU的性能度量方法是:一个程序的CPU执行时间,执行时间越短,CPU的性能越好;反之越差.

一个程序的CPU执行时间公式:

	1.一个程序的CPU执行时间 = 一个程序的CPU时钟周期数 x CPU的时钟周期
	2.一个程序的CPU执行时间 = 一个程序的CPU时钟周期数 / CPU的时钟频率

实例:

	某程序在一台时钟频率为2GHz的计算机A上运行需10s.在B上通过提高时钟频率,希望运行时间缩短为6s,但是周期数
	会提升为A的1.2倍.求B的时钟频率提高到多少?
		1.程序在A上运行的时间 = 周期数 / 频率
			即:10s = 周期数 / 2GHz	=> 周期数 = 10s * 2GHz
		2.程序在B上运行的时间 = 周期数 / 频率
			即:6s = 1.2周期数 / f	=> f = (1.2 * 10s * 2G) / 6s = 4GHz
		因此:B的时钟频率需要提高为A的2倍.

#### 1.4.3 指令的性能

	1.一个程序的CPU时钟周期数 = 程序的指令数 x 每条指令的平均时钟周期数(即CPI);
	2.CPI(clock cycle per instruction):一个程序全部指令所用时钟周期数的平均值.

实例:

	一个程序使用相同指令集.在时钟周期为250ps的A计算机上的CPI为2.0;而在时钟周期为500ps的B计算机上的CPI
		为1.2.求哪台计算机的速度更快?
	1.程序在A上的运行时间 = 周期数 * 周期; 而:周期数 = I(指令数) * CPI
		因此: 在A上运行时间 = I * 2.0 * 250ps = 500I
	2.程序在B上的运行时间 = 周期数 * 周期; 而:周期数 = I(指令数) * CPI
		因此: 在B上运行时间 = I * 1.2 * 500ps = 600I
	因此:对该程序A是B的1.2倍.

#### 1.4.4 经典的CPU性能公式

	1.CPU时间 = 指令数 x CPI X CPU时钟周期
	2.CPU时间 = 指令数 x CPI / CPU时钟频率

有时候也用IPC来代替CPI:

	IPC(instruction per clock cyle):表示每个时钟周期可执行的指令数,为CPI的倒数.

### 1.5 衡量CPU的基准

#### 1.5.1 SPEC CPU基准测试程序

1.benchmark

基准测试程序,用于比较计算机性能的程序.

2.SPECint2006--->最新的为SPECint2017

整数基准程序集.描述为:

![](images/spec2006_description.png)

3.SPECfp2006

浮点基准程序集.

#### 1.5.2 SPEC功耗基准测试程序

SPECpower

评估功耗的基准测试程序.

***

## Chapter 2 指令:计算机的语言