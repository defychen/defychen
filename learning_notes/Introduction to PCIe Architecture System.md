# Introduction to PCIe Architecture System

## Chapter 6. PCIe总线的事务层

PCIe总线报文(TLP)形成过程:

	1.PCIe总线使用的数据报文首先在TL层(事务层)中形成TLP(事务层数据报文);
	2.TLP在经过DL层(数据链路层)时被加上Sequence Number前缀和CRC后缀,然后发现MAC层(物理层);

PCIe DLLP报文的形成过程:

	1.DL层(数据链路层)还可以产生DLLP(Data Link Layer Packet),DLLP和TLP没有直接关系;
	2.DLLP产生于DL层,终止于DL层,不会传递到TL层,且DLLP不是TLP加上前缀后后缀形成的;
	3.DL层的DLLP报文通过物理层时,需要经过8/10b编码,然后再发送;
	PS:数据接收虽然是发送的逆过程,但是在具体实现上,接收过程和发送过程并不完全相同.

### 6.1 TLP的格式

**1.TLP格式**

![](images/tlp_format.png)

	1.一个完整的TLP由一个或多个TLP Prefix(可选)、TLP头、Data Payload和TLP Digest(可选)组成;
	2.TLP头包含了当前TLP的总线事物类型、路由信息等一系列信息;
	3.Data Payload长度可变,最小为0,最大为1024 DW;
		Data Payload0的情况为:存储器读请求、配置和I/O写完成TLP等.
	4.TLP Digest是可选的,是否需要TLP Digest由TLP头决定.

**2.通用TLP头格式**

![](images/tlp_head_format.png)

	1.TLP头由3个或4个DW组成.第一个DW保存通用TLP头,其他字段与通用TLP头的Type字段相关;
	2.一个通用TLP头由Fmt, Type, TC, Length等字符组成.
	3.如果存储器读写TLP支持64-bit地址,TLP头长度为4DW,否则为3DW(e.g.完成报文的TLP头不包含
		地址信息,使用3DW的TLP头).

#### 6.1.1 通用的TLP头的Fmt字段和Type字段

**1.Fmt字段**

决定TLP的格式,第一个DW的[31:29].

	Fmt[2:0]				TLP格式
	0b000					TLP头大小为3DW,不带数据
	0b001					TLP头大小为4DW,不带数据
	0b010					TLP头大小为3DW,带数据
	0b011					TLP头大小为4DW,带数据
	0b100					TLP Prefix
	其他						Reserved

**2.Type字段**

决定TLP的类型,即PCIe总线支持的总线事务,第一个DW的[28:24].

	TLP类型		Fmt[2:0]		Type[4:0]		描述
	MRd			0b000			0b0 0000		存储器读请求,TLP头大小为3DW,不带数据
				0b001							存储器读请求,TLP头大小为4DW,不带数据

	MRdLk		0b000			0b0 0001		带锁的存储器读请求,TLP头大小为3DW,不带数据(不使用)
				0b001							带锁的存储器读请求,TLP头大小为4DW,不带数据(不使用)

	MWr			0b010			0b0 0000		存储器写请求,TLP头大小为3DW,带数据
				0b011							存储器写请求,TLP头大小为4DW,带数据

	IORd		0b000			0b0 0010		IO读请求,TLP头大小为3DW,不带数据

	IOWr		0b010			0b0 0010		IO写请求,TLP头大小为3DW,带数据

	...

	Cpl			0b000			0b0 1010		完成报文,TLP头大小为3DW,不带数据.包括存储器、配置
												和I/O写完成
	
	CplD		0b001			0b0 1010		带数据的完成报文,TLP头大小为3DW,带数据.包括存储器读
												、I/O读、配置读和原子操作读完成
	...

	PS:MRd使用Non-Posted方式传送,RWr使用Posted方式传送.

#### 6.1.2 TC字段

TC字段表示当前TLP的传送类型(第一个DW的[22:20]),PCIe总线规定了8种传输类型,分别为TC0~TC7.默认为TC0.

	一般使用TC0即可.

#### 6.1.3 Attr字段

Attr字段由3-bit组成(第一个DW的[18]和[13:12]构成3个bit),描述该TLP支持的Ordering和Snoop信息.

	