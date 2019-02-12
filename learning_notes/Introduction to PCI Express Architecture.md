# Introduction to PCIE Express Architecture

## Chapter 6 PCIe总线的事务层(Transaction Layer)

事务层(Transaction Layer:TL层)是PCIe总线层次结构的最高层,接收PCIe设备核心层的数据请求,并转换为PCIe总线事务(即转成TLP报文).

PCIe中TLP数据路由:

	接收核心层的数据请求(类似AP层:该层不直接属于PCIe总线层次)--->TL层(事务层:生成事务层数据报文,即TLP)
	->DL层(Data Linker Layer(数据链路层):加上Sequence Number前缀和CRC后缀)->MAC(即物理层)

DLLP(Data Link Layer Packet):

	1.DLLP和TLP没有直接关系;
	2.DLLP产生于DL层,终止于DL层,不会传递到TL层;
	3.DLLP不是TLP加上前缀和后缀形成的.

### 6.1 TLP格式