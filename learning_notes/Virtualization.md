# Virtualization

# 1. VFIO概述

## 1.1 IOMMU

### 1.1.1 IOMMU功能简介

IOMMU主要功能包括DMA Remapping和Interrupt Remapping,此处主要讲解DMA Remapping,Interrupt Remapping暂不涉及.IOMMU与MMU类似,可以将一个设备访问地址转换为存储器地址.

#### 1.1.1.1 有无IOMMU对比

**1. 无IOMMU**

![](images/non-iommu_dma_access.png)

在没有IOMMU的情况下,网卡接收数据时地址转换流程.RC会将网卡请求写入地址addr1直接发送到DDR控制器,然后访问DRAM上的addr1地址,这里的RC对网卡请求地址不做任何转换,网卡访问的地址就是物理地址.

**2. 有IOMMU**

![](images/with-iommu_dma_access.png)

对于有IOMMU的情况,网卡请求写入地址addr1会被IOMMU转换为addr2,然后发送到DDR控制器,最终访问的是DRAM上addr2地址.网卡访问的地址addr1会被IOMMU转换成真正的物理地址addr2,这里可以将addr1理解为虚机地址.

#### 1.1.1.2 虚拟化

![](images/io_virtualization_with-non_iommu_versus.png)

**1.无IOMMU**

没有IOMMU的情况(左图),对于虚机无法实现设备的透传.原因主要有两个:

	1.在没有IOMMU的情况下,设备必须访问真实的物理地址HPA,而虚机可见的是GPA;
	2.如果让虚机填入真正的HPA,那样的话相当于虚机可以直接访问物理地址,会有安全隐患.
	所以针对没有IOMMU的情况,不能用透传的方式,对于设备的直接访问都会有VMM接管,这样就不会对虚机暴露HPA.

**2.有IOMMU**

有IOMMU的情况(右图).虚机可以将GPA直接写入到设备,当设备进行DMA传输时,设备请求地址GPA由IOMMU转换为HPA(硬件自动完成),进而DMA操作真实的物理空间.IOMMU的映射关系是由VMM维护的,HPA对虚机不可见,保障了安全问题,利用IOMMU可实现设备的透传.

	IOMMU可以将设备访问地址映射成真实的物理地址,那么对于右图中的Device A和Device B,IOMMU必须保证两个
	设备映射后的物理空间不能存在交集,否则两个虚机可以相互干扰,这和IOMMU的映射原理有关,后面有讲述.

### 1.1.2 IOMMU作用

IOMMU的主要作用如下:

	1.屏蔽物理地址,起到保护作用.典型应用包括两个:
		1.实现用户态驱动(guest OS的驱动),由于IOMMU的映射功能,使HPA对用户空间不可见;
		2.将设备透传给虚机,HPA对虚机不可见,并将GPA映射为HPA.
	2.IOMMU可以将连续的虚拟地址映射到不连续的多个物理内存片段,与MMU功能类似.

### 1.1.3 IOMMU工作原理

![](images/iommu_operating_principle.png)

	1.IOMMU的主要功能就是完成映射,类似MMU利用页表实现VA->PA的映射,IOMMU也需要用到页表;
	2.设备发起DMA请求时,将自己的Source Identifier(包含Bus、Device、Func)包含在请求中,IOMMU根据这个
		标识,以RTADDR_REG指向空间为基地址,然后利用Bus、Device、Func在Context Table中找到对应的
		Context Entry,即页表首地址,然后利用页表将设备请求的虚拟地址翻译成物理地址.
	PS:
	1.图中红线的部分,是两个Context Entry指向了同一个页表.在虚拟化场景中的典型用法就是这两个Context
		Entry对应的不同PCIe设备属于同一个虚机.
	2.由图中可知,每个具有Source Identifier(包含Bus、Device、Func)的设备都会具有一个Context Entry.如果
		不这样做,所有设备共用同一个页表,隶属于不同虚机的不同GPA就会翻译成相同HPA,会产生问题.

具体地址翻译过程请参考"ARMv8 Architecture Learning.md".

### 1.1.4 Source Identifier

