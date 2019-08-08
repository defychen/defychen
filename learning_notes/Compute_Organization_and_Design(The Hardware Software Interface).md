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

硅锭和晶圆:

	硅锭(silicon crystal ingot):一块由硅晶体组成的棒.直径约8-12英寸,长度约12-24英寸;
	晶圆(wafer):厚度不超过0.1英寸的硅锭片,用来制造芯片.

制造流程:

![](images/flow_of_chip_manufacturing.png)

