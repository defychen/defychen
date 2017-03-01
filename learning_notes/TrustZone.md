# ARM TrustZone技术简介

*针对消费电子设备安全的威胁解决方法有以下几种:*

*1)外部硬件安全模块*

	SIM卡具有特定的软硬件特性，保护卡内密钥等资源.但与设备接口通讯速度低,而且不能保护用户界面的安全

*2)内部的硬件安全模块*
	
	将类似的智能卡放到SoC里,Soc里有两个Core,一个普通的app Core和一个安全Core.但两个Core
	通信速度低,而且不能保护用户交互数据.

*3)软件虚拟化*

	虚拟化技术要保护用户界面的安全,需要在GPU控制中加入很多验证,GPU图形性能会有较大影响.

### TrustZone

*ARM针对消费电子设备安全提出的一种架构,其硬件架构是整个系统设计过程中安全体系的扩展.*

	将SoC硬件和软件资源分到两个世界(安全世界和普通世界).AMBA3 AXI总线系统能确保安全世界的
	资源不会被普通世界访问.两个世界也能分时的运行在同一个核上.

**处理器架构**

*每个物理处理器核提供两个虚拟核--非安全核(Non-secure, NS) & 安全核(Secure),两者的切换机制叫"monitor模式".*
	
	1) NS核只能访问NS系统资源，安全核可以访问所有资源.
	2) 普通世界可以通过SMC指令或硬件异常机制(IRQ、FIQ、data abort等)进入到monitor模式



# ARM Security Technology
## Building a Secure System using TrustZone Technology