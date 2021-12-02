# RDMA Learning

# 1. RDMA简介

## 1.1 传统的数据传输

![](images/data_transfer_by_nic_stack.png)

### 1.1.1 传统的数据传输存在的问题:

```
1.传输需要进行多次内存拷贝(e.g. application->OS->NIC的数据搬运),延迟会大幅增加;
2.中断处理需要CPU参与,极为影响性能;
3.内核协议栈是软件操作,性能低下,且大幅占用CPU.
```

### 1.1.2 内核协议栈

![](images/data_transfer_kernel_protocol_stack.png)

### 1.1.3 CPU消耗分布

在传统的网络传输中,数据拷贝和协议栈(TCP/IP stack)的处理消耗了大量的CPU时间和资源.

![](images/cpu_consumption_by_network.png)

## 1.2 RDMA

### 1.2.1 DMA

DMA(Direct memory access,直接内存访问)是一种能力,允许设备与内存之间直接进行数据搬运,而不需要CPU参与.

![](images/dma_transfer_data.png)

```
1.传统模式:通过CPU进行数据copy来移动数据(e.g. CPU将内存中的数据从Buffer1移动到Buffer2中);
2.DMA模式:DMA Engine通过硬件将数据从Buffer1移动到Buffer2,而不需要CPU的参与,大大降低了CPU Copy的开销.
```

### 1.2.2 RDMA

RDMA(Remote direct memory access,远程直接访问内存).利用RDMA技术通过网络将数据直接传入另一台服务器(设备)的某一块内存区域,这种方法几乎不需要消耗本地和对端服务器的CPU资源.

![](images/rdma_flow.png)

在实现上,RDMA实际上是一种智能网卡与软件架构充分优化的远端内存直接高速访问技术.将RDMA协议固化于硬件(即网卡)上,以及支持Zero-copy和Kernel bypass这两种途径来达到高性能的远程直接数据存取的目标.

### 1.2.3 Traditional TCP DMA v.s RDMA

![](images/Traditional_TCP_receiving_data.png)

<img src="images/Traditional_TCP_sending_data.png" style="zoom:80%;" />

![](images/rdma_receiving_data.png)

<img src="images/rdma_sending_data.png"  />

### 1.2.4 RDMA 三种不同的硬件实现

![](images/rdma_hardware_implementation.png)

#### 1.2.4.1 TCP数据包格式

![](images/TCP_data_packet.png)

#### 1.2.4.2 IB协议

InfiniBand(IB):从一开始就支持RDMA的新一代网络协议.这是一种新的网络技术,需要使用支持该技术的网卡和交换机.因此限制了其应用.

IB数据包格式如下:

![](images/IBA_data_packet.png)

#### 1.2.4.3 RoCE协议

RDMA(RDMA Over Converged Ethernet,过融合以太网RoCE):允许通过以太网执行RDMA的网络协议.

```
1.RoCE是在原有IB协议的基础上,将link层的LRH修改为以太网的MAC头,将VCRC修改为FCS,其他报文格式保持原有格式;
2.报文也完全遵循IB协议定义的方式进行解析处理;
3.接收报文时,通过EtherType的值来区分报文是传统以太网报文还是RoCE报文,RoCE的EtherType固定为:0x8915.
```

![](images/RoCE_data_packet.png)

#### 1.2.4.4 RoCE v2协议

尽管RoCE已经将LRH修改为MAC向以太网兼容,但是其网络层仍然是IB的GRH,限制其只能在小网内使用.RoCE v2进行了以下更新:

```
将L3(GRH)修改为IP(v4/v6)+UDP,从而达到在子网间通信的目的.传输层仍然保持不变.
```

#### 1.2.4.5 iWARP协议

iWARP(RDMA over TCP互联网广域RDMA协议):允许通过TCP执行RDMA的网络协议.这允许在标准以太网基础架构(交换机)上使用RDMA,网卡要求是支持iWARP(如果使用CPU offload的话)的NIC.否则,所有iWARP栈都在软件中实现,但是失去了RDMA性能优势.

![](images/iwarp_data_packet.png)

#### 1.2.4.6 RoCE的演进

RoCE的演进归纳为:

```
IB(IB网络)--->RoCE(以太网子网(switch))--->RoCE V2(整个以太网(router))
```

# 2. IB(Infiniband)

## 2.1 IB简介

IBTA(Infiniband贸易协会)成立于1999年,负责指定和维护Infiniband标准.

IB的目的:

```
1.实现CPU和I/O之间的互联通道;
2.超高的性能
	1)高带宽:扩展空间大;
	2)低延迟:低于1us(ns级别)的应用延迟,集群中跨节点应用程序间的快速响应;
	3)低CPU占用及RDMA(远程直接内存访问):打破传统以太网需要CPU和OS介入通讯.
3.提高应用程序性能;
4.高可靠的子网管理器.
```

Infiniband是一个为大规模、易扩展而设计的网络技术.

## 2.2 IB网络结构

![](images/ib_network_structure.png)

IB网络结构包含以下组件:

```
1.HCA(host channel adapter)
2.TCA(target channel adapter)
3.Swtich
4.Router
5.子网管理组件
PS:HCA和TCA必须有一个
```

## 2.3 verbs

![](images/verbs_processor_node.png)

verbs用于实现硬件与OS之间交互的接口,功能类似于API.OS通过调用相应的verbs实现表项的建立与注销(create/modify/destroy)或者任务的下发(post send/receive)或者对数据的轮询(poll for completion)等.

## 2.4 一些基本概念

![](images/iba_communication_stack.png)

### 2.4.1 WR

WR(work request):请求任务,用户下发的操作任务,实体为WQE(work queue element, 发音为wookie).

```
WQE包含的内容为:具体的操作类型,地址向量,SGL(scatter-gather list)等信息.
```

### 2.4.2 QP

QP(queue pair):RoCE的基本通信单元,QP特点:

```
1.包含send queue(SQ, 发送队列)和receive queue(RQ, 接收队列).两个队列均为FIFO结构,每个队列都存储了多个WQE;
2.QP之间互相独立,互不影响.
```

QP中存在两个特殊的QP:

```
QP0:用于地址交换(RoCE基于以太网,不支持QP0),通信对象为switch或节点内的通信管理器;
QP1:用于正式通信前建立连接(CM)的报文交换,传输报文为UD类型,payload为MAD报文,主要包含通信时的QPC交互信息.
```

### 2.4.3 QPC

QPC(QP context):QP的上下文,一种数据结构.

```
包含QP的一些基本属性、服务类型、状态、地址向量、队列参数等信息.
```

### 2.4.4 CQE

CQE(completion queue entry, 发音为cookie):用于记录WQE的完成信息.

```
包括WQE的完成状态、消息长度、WQE的指针等.
```

### 2.4.5 CQ

CQ(completion queue):用于存储CQE,为FIFO结构.

```
使用时每个SQ/RQ都需要且只能关联到一个CQ,多个work queue可以共享同一个CQ.
```

### 2.4.6 CQC

CQC(completion queue context):CQ上下文,一种数据结构.

```
包括当前CQ的状态、队列使用情况等信息.
```

### 2.4.7 SRQ

SRQ(shared receive queue):共享的RQ队列.

```
1.为了节省receive queue资源,将多个QP的RQ进行共享使用,内部存储的是receive WQE,每个Q使用时申请WQE;
2.link结构,同样有SRQC与之对应.
```

### 2.4.8 MR

MR(memory region):用于地址转换.

```
1.包含memory的访问属性,VA->PA的转换信息;
2.一个MR对应一个L_KEY,也有可能会有一个R_KEY(取决于是否需要远程访问);
3.L_KEY包含index和key两个部分,index用于索引MR,key作为密钥用于MR内的key匹配;
4.R_KEY的功能与L_KEY类似,主要用于RDMA的远程访问.
```

### 2.4.9 CE

CE(completion event):完成事件,用于实现CQE的汇聚上报.

```
1.用于通过CE轮询CQ,进而获取CQE;
2.每个CQ可以绑定到一个CE的ID,然后通过设置CQE的聚合参数来上报CE给用户.
```

### 2.4.10 AE

AE(asynchronous event):异步事件.

```
用于上报硬件相关的异常和特殊状态.
```

# 3. IB协议层次结构

## 3.1 IB协议层次结构

![](images/IBA_architecture_paylers.png)

IB协议共包含5个层次:

```
1.ULP:upper level protocols,由软件实现.
2.传输层:transport layer,从传输层开始的层次均由硬件实现.ULP与传输层通过verbs进行交互.
3.网络层:network layer
4.链路层:link layer
5.物理层:physical layer
```

# 4. IB基本操作类型

IB包含4种基本操作类型---send, rdma write, rdma read, atomic.

## 4.1 send

send:将本地buffer里的数据(payload)传给对面分配的buffer内,server端所分配的buffer在client是看不到的.

![](images/rdma_send.png)

## 4.2 RDMA write

rdma write:将本地buffer的payload通过与对端协商过来的地址,写入对端相对应的存储空间.其中client端可以知道server端对应的地址信息.

![](images/rdma_write.png)

## 4.3 RDMA read

rdma read:client端将server端的数据读入本地的buffer内的一种操作.client可以知道需要读取的数据在server端的va信息.

![](images/rdma_read.png)

## 4.4 atomic

atomic:类似于read和write操作的结合.

```
1.client同样通过已知的server侧地址,将server端buffer内的数据读出来;
2.将读取到的数据与client侧发过来的数据进行逻辑运算后写回到server侧相同的地址；
3.server侧将内存中的原始数据返回给client,server侧的执行顺序是先读后写.
```

## 4.5 四种操作总结

![](images/rdma_operation.png)

## 4.6 建链

在上述所有的操作类型中,在通信之前,均需要对QPC表项进行同步初始化,该过程称为建链过程.RoCE建链方式有两种:socket和CM(communication management).

```
1.socket建链:通过socket方式建链,即通过传统数据流进行协商通信;
2.CM建链:通过RoCE自带的UD类型报文进行协商.
PS:两种建链方式都是在软件层进行协商的,需要通过特定的协议栈解析.
```