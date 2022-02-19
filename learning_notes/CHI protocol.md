# CHI protocol

# Chapter 1. CHI基本概念介绍

CHI协议是AMBA的第5代协议,可以说是ACE协议的进化版,将所有的信息传输采用包(packet)的形式来完成.packet里分各个域段来传递不同信息,本质是用于解决多个CPU(RN-F)之间的数据一致性问题.

## 1.1 CHI特点

### 1.1.1 CHI架构

基于CHI协议的系统架构可以包含独立CPU、处理器簇(Cluster)、图形处理器(GPU)、memory控制器、I/O桥、PCIe子系统和CHI互联线(NoC).具有以下特性:

```
1.架构扩展方便;
2.独立的分层实现,包括协议层、网络层和链路层,各自具有不同的功能;
3.基于包传输;
4.HN(Home Node)协调所有的传输请求,包括snoop请求,访问cache和memory;
5.支持64Byte的一致性粒度、Snoop filter和directory、MESI和MOESI cache模型、增加partial和empty cacheline状态;
6.支持Retry机制来管理协议层资源;
7.支持端到端的Qos(Quality of Service);
8.可配置的数据宽度以满足系统需求;
9.支持ARM TrustZone;
10.低功耗信号,可以使能flit级别门控、组件之间的建、断链来支持时钟门控和电源门控、协议层的活动信号来控制电源和时钟.
```

### 1.1.2 CHI层次

CHI层次按功能可以划分为:协议层(Protocol)、网络层(Network)、链路层(Link).

| Layer    | Communication granularity | Primary function                                             |
| -------- | ------------------------- | ------------------------------------------------------------ |
| Protocol | Transaction               | 协议层是CHI架构里的最顶层,协议层功能:<br />1.在协议节点产生并处理请求与响应;<br />2.定义协议节点允许的cache状态和状态转换;<br />3.定义每个请求类型的传输流程;<br />4.管理协议层的流控. |
| Network  | Packet                    | 网络层功能:<br />1.打包协议层信息;<br />2.确定并增加源节点和目的节点的ID到packet中,确保这些packets能正确在互联线上路由. |
| Link     | Flit                      | 链路层功能:<br />1.提供Network devices之间的流控;<br />2.管理链路通道以提供跨网络的无死锁切换. |

### 1.1.3 Topology(拓扑结构)

Crossbar/Ring/Mesh--->待补充.

## 1.2 Terminology(术语)

| terms                     | Explanation                                                  |
| ------------------------- | ------------------------------------------------------------ |
| Transaction               | 一个transaction执行一个单独的操作,如一个transaction可以是读memory或写memory |
| Message                   | 协议层术语.用于定义两个组件之间交换信息的粒度,如Request/Data response/Snoop request.一个数据响应message可能由多个packets组成 |
| Packet                    | 端到端跨越interconnect的传输粒度.一个message可能由一个或多个packets组成,每个packet包含有源和目的节点的ID来保证在interconnect上独立路由 |
| Flit                      | 最小流控单位.一个packet可以由一个或多个flits组成,对于同一个packet的所有flits在interconnect上传输必须遵循同样的路径.对于CHI,所有的packets都是由一个flit组成 |
| Phit                      | 物理层传输单位.一个flit可以由一个或多个phits组成,phit定义为两相邻网络设备之间的一个传输,对于CHI,所有的flits都是由一个phit组成 |
| PoS                       | Point of Serialization.位于ICN内,用于Requests之间的保序      |
| PoC                       | Point of Coherence(一致性节点).用于保证所有访问同一个memory地址的请求都可以得到同一份数据 |
| Downstream cache          | downstream cache是以RN的视角定义的.RN的downstream cache可以通过CHI请求访问 |
| Requester                 | Requester可以指独立产生原始transactions的组件(master),也可以指ICN |
| Completer                 | Completer可以指ICN,也可以是SN                                |
| Master                    | Master是独立产生transactions的agent,和Requester差不多.       |
| Slave                     | Slave是接受transactions的agent.和Completer/Endpoint差不多.   |
| Endpoint                  | slave的另一个名字.指的是一个transaction的最终目的地          |
| Protocol Credit           | 一个P-credit用于保证completer有能力接收一个transaction       |
| Link layer Credit         | 一个L-credit用于保证另一边的link可以接收一个flit             |
| ICN                       | interconnect的简称.用于协议节点之间的通讯的CHI传输机构,ICN可能也包含协议节点,如HN和MN |
| IPA                       | intermediate physical address(中间物理地址).在两级地址系统中,第一级产生IPA,第二级产生物理地址 |
| RN                        | Request Node.产生协议transaction,包含读和写                  |
| HN                        | Home Node.位于ICN,用于接收来自RN的协议transaction,完成相应的一致性操作并返回一个响应 |
| SN                        | Slave Noe.用于接收来自HN的请求,完成相应的操作并返回一个响应  |
| MN                        | 位于ICN,用于接收来自RN的DVM操作,完成相应的操作并返回一个响应 |
| IO Coherent node          | IO一致性节点产生的snoop请求不会导致数据被cache,因此IO一致性节点也不会接收到任何snoop请求 |
| Write-Invalidate protocol | 该协议是指当RN往一个共享地址写数据时,必须先把所有共享的数据备份都无效掉,然后再进行写操作,CHI采用的就是该协议 |
| In a timely manner        | 协议中没有定义在某个绝对的时间后,某件事必须发生,但是及时发生可以使系统效率更高 |
| Don’t Care                | 表示该域段可以设置为任何值,包括非法值和保留值.任何组件收到的包中如果包含设为Don’t care的域段,都必须忽略该域段 |
| Inapplicable              | 表示该域段值不会用于信息处理                                 |













