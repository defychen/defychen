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

SMMU的行为与PE的MMU类似,在系统I/O设备的DMA请求发到系统之前进行地址转换(SMMU只为DMA工作).

![](images/smmu_in_dma_traffic.png)

### 2.1 描述

	1.对DMA的地址进行转换是为了隔离或快捷:
		为了将设备通讯与转换相关联,还要区分SMMU背后不同的设备,转换请求还需要除了地址、R/W、权限以外的额外
		属性(即需要一个分辨某个流的属性);
		不同的流在逻辑上与不同的设备相关联,SMMU可以对不同的流实现不同的转换或检查,即使一个系统中只有一个
		client设备,SMMU的概念仍然不会变,只有一个流与该设备对应.
	2.一个系统中可能有很多个SMMU,一个SMMU可能为1个或多个设备做转换;
	3.SMMU支持2阶段页表转换的方式与PE的MMU相似:
		1阶段VA->IPA,2阶段IPA->PA;
		1阶段转换主要是为了在一个VM内的DMA隔离,2阶段一般在支持虚拟化扩展的设备实现将DMA设备虚拟化到VM内.

### 2.2 SMMUv3.2特性

SMMUv3提供了支持PCIE Root Complexes的特性,并通过支持大量并行转换context来支持其他潜在大量I/O的系统.主要特性如下:

	1.基于内存的配置结构,支持大量的流;
	2.具体实现可仅1阶段、仅2阶段或两阶段页表转换,从寄存器里可以查到具体配置,其他根据实现选配的参数也可以
		查到;
	3.最高16bit ASID;
	4.最高16位VMID;
	5.根据ARMv8.1虚拟内存系统架构实现地址转换和保护.SMMU转换表可与PE们共享,允许软件选择共享页表或SMMU
		私有页表;
	6.49bit VA,符合ARMv8-A的2x48bit转换表输入大小.

选配特性:

	1.可支持aarch32 LPAE页表格式和aarch64页表格式;
	2.支持安全域的流;
	3.广播TLB失效;
	4.HTTU可能仅支持硬件更新Access flag或同时支持硬件更新Access flag和Dirty state,也可以没有HTTU;
	5.兼容Root Complex的PCIE ATS和PRI;
	6.4K,16K和64K页表粒度,建议基于服务器的系统架构实现应实现两阶段页表转换并使用64KB页表,与PE相对齐.

其他:

	1.可以支持52bit VA、IPA、PA;
	2.Page-Based Hardware Attribute;
	3.2阶段页表的EL0 vs EL1 execute never控制;
	4.ARMv8.2中的PE的概念Common not Private(CnP)并不适用于SMMU架构,所有SMMU转换都按common处理.

## 3. SMMU在系统中的位置

下图中有两种SMMU的使用方式:

	1.一种使用方式是两个client设备经SMMU从系统取数据,设备的DMA可以使用VA、IPA或是其他总线地址,SMMU将这地
		址转换成PA;
	2.另一种使用方式是SMMU与PCIE的Root Complex一对一的接到了一起,Root Complex自己管着一票Endpoints,
		SMMU给出了一个ATS port来支持PCIE的ATS和PRI,当然,这个ATS也可能是兼容其他非PCIE设备的相近功能.

![](images/smmu_placement_in_an_example_system.png)

### 3.1 SMMU在系统中的位置要求

	1.正在发生的对slave设备的访问不能避过SMMU:
		一般来说,master在SMMU后面,就像PE在MMU后面一样.因此进行中的对slave设备的访问需要master的SMMU
		调和,如果master没有SMMU,那么他的DMA就可以有全系统访问能力,因此其DMA需要软件设置,这种情况下,只有
		最高权限才能进行设置;
	2.SMMU有自己的程序接口:
		接受系统软件的设置和维护,并且每个SMMU都要单独设置,SMMU也能访问自己的设置,比如TTW;SMMU自行访问
		内存的通道是否与其client设备共享由具体实现决定;
	3.ARM推荐项:
		1.SMMU桥接I/O设备的DMA地址应该到系统或物理地址;
		2.SMMU应该放在设备master或是I/O与系统之间;
		3.MMU不应该串联到一起,就是说,SMMU到内存或其他slave设备不应经过另一个SMMU;
	4.一致性:
		1.系统的SMMU master接口想要实现IO一致行,从而为SMMU的client设备提供IO一致性访问;
		2.SMMU slave接口对从设备来的数据流不需要任何一致性支持;
		3.由于在传出方向上没有地址转换,因此侦听流量不能从系统到达客户端设备,因此无法将全一致性设备放在
			SMMU后面;
		4.将SMMU作为包含全一致性缓存的复杂设备的一部分是可行的,就像PE的MMU一样;不过这意味着缓存就需要
			用物理地址做标签.
