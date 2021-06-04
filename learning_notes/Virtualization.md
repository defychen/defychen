# Virtualization

# 1. VFIO概述

## 1.1 IOMMU

### 1.1.1 IOMMU功能简介

IOMMU主要功能包括DMA Remapping和Interrupt Remapping,此处主要讲解DMA Remapping,Interrupt Remapping暂不涉及.IOMMU与MMU类似,可以将一个设备访问地址转换为存储器地址.

### 1.1.2 有无IOMMU对比

#### 1.1.2.1 无IOMMU

![](images/non-iommu_dma_access.png)

在没有IOMMU的情况下,网卡接收数据时地址转换流程.RC会将网卡请求写入地址addr1直接发送到DDR控制器,然后访问DRAM上的addr1地址,这里的RC对网卡请求地址不做任何转换,网卡访问的地址就是物理地址.

#### 1.1.2.2 有IOMMU

![](images/with-iommu_dma_access.png)

对于有IOMMU的情况,网卡请求写入地址addr1会被IOMMU转换为addr2,然后发送到DDR控制器,最终访问的是DRAM上addr2地址.网卡访问的地址addr1会被IOMMU转换成真正的物理地址addr2,这里可以将addr1理解为虚机地址.

### 1.1.3 虚拟化

![](images/io_virtualization_with-non_iommu_versus.png)

#### 1.1.3.1 无IOMMU

没有IOMMU的情况(左图),对于虚机无法实现设备的透传.原因主要有两个:

	1.在没有IOMMU的情况下,设备必须访问真实的物理地址HPA,而虚机可见的是GPA;
	2.如果让虚机填入真正的HPA,那样的话相当于虚机可以直接访问物理地址,会有安全隐患.
	所以针对没有IOMMU的情况,不能用透传的方式,对于设备的直接访问都会有VMM接管,这样就不会对虚机暴露HPA.

#### 1.1.3.2 有IOMMU

有IOMMU的情况(右图).虚机可以将GPA直接写入到设备,当设备进行DMA传输时,设备请求地址GPA由IOMMU转换为HPA(硬件自动完成),进而DMA操作真实的物理空间.IOMMU的映射关系是由VMM维护的,HPA对虚机不可见,保障了安全问题,利用IOMMU可实现设备的透传.

	IOMMU可以将设备访问地址映射成真实的物理地址,那么对于右图中的Device A和Device B,IOMMU必须保证两个
	设备映射后的物理空间不能存在交集,否则两个虚机可以相互干扰,这和IOMMU的映射原理有关,后面有讲述.