# SMMUv3 Learning

## 1. 术语

DVM(Distributed Virtual Memory):广播TLB维护操作的消息的协议.

RC(PCIe的Root Complex),见下图.

![](images/pcie_rc.png)

EP(Endpoint):一个PCIe功能,用于一个SMMU client节点设备的context.

PASID(Process address space ID):一个PASID是一个Endpoint的本地ID,一个系统中一个PASID可能用很多遍.

	PS:PASID除了名字与PE的ASID有点靠近外,其实与ASID完全没关系.

ATS(Address translation service):PCIe提供给远端Endpoint TLB的Address Translation Service.

Split-stage ATS:两阶段页表转换方式.ATS用阶段1页表转换,non-ATS用阶段2页表转换.

PRI(Page request interface):PCIe引入的PRI,是ATS的一个扩展项.允许Endpoint请求OS提供映射了的页面的内存给DMA使用.

ATOS:SMMU用系统可访问的寄存器提供VA-IPA/PA的转换;VATOS提供了次要的寄存器组,用于虚拟机直接使用,只做VA-IPA的转换.

TT(Translation table):页表,ARM架构的.

TTD(Translation table descriptor):也就是PTE.

HTTU(Hardware translation table update):在访问或写入相关页面后,硬件自动更新相关页面的Acess flag/Dirty stats.

SSD(Secure state determination):将client设备的一段数据流与secure/non-secure控制联系起来的方法,确定这段数据流的secure/non-secure设置.

STE(Stream table entry):流表条目.

L1STD:一级STE,用于两级STE.

CD(Context descriptor):Context描述符.

L1CD:一级CD,用于两级CD表.

Client device:由SMMU控制访问系统内存行为能力的设备.

bypass:一种设置,一个阶段的不做任何地址转化,这种直通模式就是使用bypass;如果SMMU没有实现哪一阶段地址转换,那么这个阶段的地址转换就可以认为是Bypass.

Stage N-only:一种对一段数据流的转换设置,两阶段转换只转换一个阶段,另一个Bypass掉,可以是设置成这样,也可以是SMMU被实现成这样.

E2H(EL2 host mode):详见VHE的说明.

TR(Translation request):用于在PCIe ATS的context中,请求SMMU做地址转换.

## 2. 简述

