# Linux device driver development(linux4.0)
***
## 第一章	linux设备驱动概述及开发环境构建

**驱动针对的对象是存储器和外设,而不是CPU内核,主要分为3个基础大类:**

*1)字符设备:必须以串行顺序依次进行设备的访问(e.g. 鼠标、触摸屏等).*

*2)块设备:顺序任意,以块为单位进行操作(e.g. 硬盘、eMMC等).*

*3)网络设备:面向网络数据包的发送和接收,主要使用套接字.*

*字符设备和块设备都会映射到linux文件系统的文件和目录,通过文件系统的系统调用接口open、read、write、close等即可访问.*

**字符设备在定义设备结构体时,一定会包含字符设备cdev结构体(struct cdev cdev);**

	struct light_cdev {
		struct cdev cdev;	/*字符设备cdev结构体*/
		/*其他设备的信息*/
	};

**字符设备驱动的框架:**

	/*open function*/
	int xxx_open(struct inode *inode, struct file *filp)
	{
		/*inode对应的是设备节点(/dev下面的),e.g. /dev/dsc0*/
		/*open的作用可以理解为:将操作设备使用节点转为使用文件，便于后面全部使用fd来操作*/
		struct light_cdev *dev;	/*设备结构体指针*/
		/*从节点获得设备结构体指针*/
		dev = container_of(inode->i_cdev, struct light_cdev, cdev);
		/*设备结构体作为设备(filp)的私有信息，便于后续的filp(fd)传递*/
		filp->private_data = dev;		
		...
	}

	/*release function*/
	int xxx_release(struct inode *inode, struct file *filp)
	{
		/*释放资源*/
		...
	}
	
	/*read function*/
	ssize_t xxx_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
	{
		/*通过filp(fd)获得设备结构体*/
		struct light_cdev *dev = filp->private_data;
		/*使用dev进行相关的读操作*/
		
		/*copy_to_user函数
		para1:目标地址e.g.(buf)
		para2:源地址e.g.(&(dev->value))
		*/
		if(copy_to_user(buf, &(dev->value), 1))
			return -EFAULT;	/*EFAULT:Bad address*/
		...
	}

	/*write function*/
	ssize_t xxx_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
	{
		/*通过filp(fd)获得设备结构体*/
		struct light_cdev *dev = filp->private_data;
		/*使用dev进行相关的写操作*/

		/*copy_from_user函数
		para1:目标地址e.g.(&(dev->value))
		para2:源地址e.g.(buf)
		*/
		if(copy_to_user(&(dev->value), buf, 1))
			return -EFAULT;	/*(14)EFAULT:Bad address*/
		...
	}

	/*ioctl function*/
	int xxx_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
	{
		/*通过filp(fd)获得设备结构体*/
		struct light_cdev *dev = filp->private_data;
		/*根据cmd，使用dev进行相关操作*/
		switch(cmd) {
		case...
		default:
			-ENOTTY;	/*(25)Not a typewriter*/
		}
		...
	}

	struct file_operations light_fops = {
		.owner = THIS_MODULE,
		.open = xxx_open,
		.release = xxx_release,
		.read = xxx_read,
		.write = xxx_write,
		.ioctl = xxx_ioctl,
	};
	
	/*Module init function*/
	int __init xxx_init(void)
	{
		/*申请设备号*/
		dev_t devno;	/*保存设备号*/
		alloc_chrdev_region(&devno, 0, 1, "led");
		/*light_devp = kmalloc(sizeof(struct light_dev), GFP_KERNEL);
		kmalloc中:para1分配块大小,para2分配标记(GFP_KERNEL:内核空间进程中申请内存).
		kmalloc使用kfree释放,kfree("kmalloc返回的结构体实例e.g. light_devp")
		ENOMEM(12):Out of memory.
		一般分配了内存都会调用memset()进行初始化.
		*/
		/*字符设备初始化*/
		cdev_init(&dev->cdev, &light_fops);	/*para1:设备结构体下的字符设备结构体,para2:文件操作结构体*/
		dev->cdev.owner = THIS_MODULE;
		dev->cdev.ops = &light_fops;
		/*字符设备与设备号链接*/
		cdev_add(&dev->cdev, devno, 1);
		/*其他操作*/
		...
	}

	/*Module exit function*/
	void __init xxx_exit(void)
	{
		/*删除字符设备结构体*/
		cdev_del(&light_devp->cdev);
		/*注销字符设备*/
		unregister_chrdev_region(MKDEV(light_major, 0), 1);	/*para1:设备号;para2:count(设备数量)*/
		/*para1设备号(devno)需要生成*/
	}

	module_init(xxx_init);
	module_exit(xxx_exit);
	
	MODULE_AUTHOR("xxx Corporation");
	MODULE_DESCRIPTION("xxxx");
	MODULE_LICENSE("GPL v2");
	MODULE_VERSION("1.0");
***
## 第二章	驱动设计的硬件基础

### 2.1 处理器

*冯 诺依曼结构:指令存储器和数据存储器合并在一起构成一个存储器,因此指令和数据的位宽一样.*

*哈佛结构:指令和数据分开存储,指令和数据的位宽可以不一样；同时程序(指令)总线和数据总线分开,效率高.*

*改进的哈佛结构:改进为公用的地址总线和数据总线(程序和数据存储器分时共用这两条总线).数据总线完成程序存储器或数据存储器于CPU的数据交换;地址总线完成寻址程序或数据.*

*指令集:CPU分为两类(RISC--精简指令集; CISC--复杂指令集).*

### 2.2 存储器

#### ROM & Flash
 
*ROM:EEPROM完全可以用软件来擦写.*

*NOR(或非):类SRAM接口,可芯片内执行(execute in place, XIP).*

*NAND(与非):以块方式访问,不支持芯片内执行.*

*CFI(Common Flash Interface):公共闪存接口,是一个从NOR flash中读取数据的公开、标准接口,可使用系统软件查询到Flash器件的各种参数.*

*Flash的编程原理是将1写0,不能将0写1.擦除过程是将所有位都写1.*

*OTP(One-Time Programmable):一次性可编程存储器,由SoC继承一个eFuse电编程熔丝作为OTP.*
#### RAM

*DRAM:电荷形式存储,数据存储在电荷中,因为电容器漏电会出现电荷丢失,因此DRAM器件需要定期刷新.*

*SRAM:静态RAM,晶体管组成,供电保持固定值，没有刷新周期.*

*DPRAM:双端口RAM,两个处理器之间交互数据.一端写入数据,另一端通过轮询或中断获知并读取其写入的数据.*

### 2.3 接口与总线

#### 串口

**Uart是"TTL"电平的串口(并行转串行);RS232是"RS232"电平的串口.**

*CPU带的串口为Uart，内部通过CMOS/TTL与RS232电平转换得到RS232串口,所以通常电脑或板子用的串口为RS232.*

#### I2C

*I2C(内置集成电路):两线式串行总线,用于连接微控制器及其外围设备.两个信号线分别为SDA(数据线)、SCL(时钟线).*

**SCL稳定在高电平时,SDA由高电平到低电平的变化将产生一个开始位;由低电平到高电平的变化将产生一个停止位.**

#### SPI

*SPI(Serial Peripheral Interface):同步串行外设接口,使CPU与各种外设以串行方式进行通信.一般主控为:SoC,从设备为:外设.*

#### USB

*USB:通用串行总线.*

*USB主机控制器(简称USB主机)用于连接USB外设;USB设备适配器(简称USB设备)用于作为其他计算机系统的USB外设(e.g. 手机充当U盘).*

*USB系统的物理拓扑系统包括:USB主机,USB设备,Hub(USB集线器(其他还有网络Hub)--用于USB扩展，进而可连接多个USB设备).*


#### eMMC

*eMMC(Embedded Multi Media Card) = NAND Flash + 闪存控制芯片 + 标准接口封装，属于多芯片封装--MCP(Multi-Chip Package).*

*eMMC接口电压分为1.8V和3.3V两种.SSD(Solid State Disk) = 多个NAND Flash + 多主控(闪存控制芯片) + 缓存, eMMC都为单个.*
***
## 第三章 Linux内核及内核编程

*内核抢占:一个内核任务可以被抢占,提高系统的实时性.但存在一些不可抢占区间(e.g. 中断上下文、软中断、自旋锁等原子上下文进程).*

*总线、设备和驱动模型:总线将设备和驱动联系起来.*

	总线中的match()函数用来匹配设备和驱动,匹配成功就会执行驱动程序中的probe()函数.

### 3.1 linux内核组成
*linux内核主要由:进程调度(SCHED)、内存管理(MM)、虚拟文件系统(VFS)、网络接口(NET)、进程间通信(IPC)五部分组成.*

	1)进程调度:处于系统的中心位置,内核中使用task_struct(位于./include/linux/sched.h定义)描述进程.
	2)内存管理:控制多个进程安全地共享主内存区域.
	3)虚拟文件系统:隐藏各种硬件的具体细节,为应用程序操作具体设备提供统一的接口.而且独立于各个具体的文件系统,对各种文件系统(ext2、FAT等)进行抽象.
	4)网络接口:包括网络协议(负责实现网络传输协议)和网络驱动程序(负责与网络硬件设备通信).上层应用程序统一使用套接字接口.
	5)进程间通信:信号量、共享内存、消息队列(System V IPC)、管道、UNIX域套接字等.

### 3.2 linux内核编译及加载

*./configs/xxx_defconfig:为某电路板的默认配置,"make xxx_defconfig"为xxx开发板配置内核.*

*Kconfig(配置文件):给用户提供配置选项的功能.*

*"make xxx_defconfig"和"make menuconfig"均会写入一个".config"配置文件中.该配置文件记录哪些被编译进内核，哪些被编译为模块.*

**运行make menuconfig时,首先分析与体系结构对应的./arch/xxx/Kconfig文件(xxx为传入的ARCH参数).该Kconfig文件包含一些与体系结构相关的配置项和配置菜单,还通过source语句引入一系列的Kconfig(e.g. source "net/Kconfig"),这样一层一层的引入形成menuconfig的菜单结构.**

### 3.3 Kconfig和Makefile

**Kconfig:提供界面中的配置选项.**

	config TTY_PRINTK	/*提供给Makefile中的编译项,Makefile中会自动变为"CONFIG_TTY_PRINTK"*/
		tristate "TTY driver to output user messages via printk"	/*tristate后面的内容为在菜单中显示的字符串*/
		/*tristate:三态(编译入内核(Y),不编译(N),编译为模块(M));bool:两态(编译入内核(Y),不编译(N))*/
		/*上述的提示信息也是使用如下格式代替:
		tristate
		prompt "TTY driver to output user messages via printk"
		*/
		depends on EXPERT && TTY	/*依赖项*/
		default n	/*默认值*/
		---help---	/*后面全为帮助信息*/
		....

**Makefile中编译项为:**

	obj-$(CONFIG_TTY_PRINTK)	+= ttyprintk.o 
	/*CONFIG_TTY_PRINTK配置为"Y/M",等同于"obj-y/obj-m",则会编译"ttyprintk.c",分别为"编译进内核"或生成模块"ttyprintk.ko"
	;如果配置为"N",等同于obj-n,不编译ttyprintk.c*/

**内核中的Makefile语法:**

*1)目标定义:*
	
	obj-y += foo.o	/*由foo.c或foo.s编译得到foo.o并链接进内核(无条件编译)*/
	obj-m += foo.o	/*foo.c作为模块编译, 而obj-n表示不编译*/
*2)多文件模块定义:*

*采用"模块名-y"或"-objs"定义模块的组成文件*
	
	obj-$(CONFIG_EXT2_FS) += ext2.o
	ext2-y := balloc.o dir.o file.o fsync.o ialloc.o ... /*模块名字ext2,由balloc.o dir.o file.o...等等链接
	生成ext2.o最终编译进内核或成为"ext2.ko"模块文件*/
	ext2-$(CONFIG_EXT2_FS_POSIX_ACL) += acl.o	
	/*如果CONFIG_EXT2_FS_POSIX_ACL被选择,将编译acl.c得到acl.o并链接进ext2.o*/

**菜单结构:**

	menu "Network device support"	/*menu和endmenu之间的都会成为"Network device support"下的子菜单*/
		depends on NET	/*且会继承依赖关系(menu一般仅仅是一个菜单,没有对应真实的配置选项)*/
	config NETDEVICES	/*子菜单*/
		...
	endmenu
/*除了"menu...endmenu"这种形成菜单外;依赖关系也有可能形成菜单.*/

	General setup---位于./init/Kconfig(可以通过make menuconfig中的help找到位置)

*choice...endchoice定义选择群菜单:*
	
	"选择群菜单"点开之后是下面这种效果:
	(X)Gzip
	()LZMA
	()XZ
	()LZO
	()LZ4

**驱动写好后,Kconfig和Makefile需要的操作:**

*1)Kconfig*

*Kconfig在某个目录下编辑好后,需要在./arch/arm/Kconfig中添加:*
	
	source "drivers/Kconfig"	/*在"./arch/arm/Kconfig中添加,包括了drivers下面的Kconfig"*/
	source "drivers/alidrivers/modules/Kconfig" /*在"./drivers/Kconfig"中添加,包括了modules下面的Kconfig*/
	/*(drivers/alidrivers/modules/Kconfig)中描述alidsc的菜单信息*/

*2)Makefile*

	obj-y += alidrivers/modules/		/*在"./drivers/Makefile"中添加,强制(无条件)进入该目录"alidrivers/modules/"*/
	obj-$(CONFIG_ALI_DSC) += alidsc/		/*在"./drivers/alidrivers/modules/Makefile"中添加,根据"$(CONFIG_ALI_DSC)"决
	定是否进入"alidsc/"目录.*/
	obj-$(CONFIG_ALI_DSC) += alidsc.o	/*在"./modules/alidsc"中添加具体的编译命令*/

### 3.4 Linux内核引导

*SoC内嵌bootrom,一上电bootrom即运行,其他CPU进入WFI状态等待CPU0唤醒.CPU0中的bootrom会引导bootloader,bootloader引导kernel,在kernel启动阶段CPU0发出中断唤醒其他CPU运行.*

*内核镜像zImage包括解压算法和被压缩的内核,bootloader引导kernel时利用解压算法解压zImage解出kernel进行引导.*

### 3.5 Linux下的C编码特点

**Linux编码风格**

*1)命名:下划线为主*

	#define PI 3.1415926
	int min_value, max_value;	/*变量名下划线分割*/
	void send_data(void);	/*函数下划线分割*/

*2)"{}"使用:*
	
	(1)结构体、if/for/while/switch "{"不另起一行, 如果只有一句不要加"{}"
	(2)if...else, else语句不另起一行
	(3)函数另起一行
	(4)switch...case对齐
	(5)空格使用"for ( i = 0; i < 10; i++ ) {"

**GNU C**

*linux用的C编译器为GNU C编译器.*

**(1)可变参数宏(宏可以接受可变数目的参数)**

	#define pr_debug(fmt, arg...) \
				printk(fmt, ##arg)	/*"##"为了处理arg不代表任何参数的情况,GNU C与预处理器会丢弃前面的逗号*/

**(2)结构体初始化**

	struct file_operations ext2_file_operations = {
		.llseek			= generic_file_llseek,
		...	
	};

**(3)当前函数名"__func__"**

	void example(void)
	{
		printf("This is a function: %s", __function__);
	}

**(4)特殊属性声明**

*作用于函数、变量和类型,以便手动优化代码和定制代码检查(方法"__attribute__((noreturn/format/section/aligned/packed))",一般在声明后面添加).*

	noreturn:作用于函数,函数不返回.
	unused:作用于函数和变量,表示可能不会用到,避免编译器产生警告信息.
	aligned:作用于变量、结构体、联合体，指定对齐方式.e.g.__attribute__((aligned(4)))
	packed:作用于变量与类型,表示最小可能的对齐或者使用最小的内存.

**(5)内建函数"__builtin"开始**

*如果编译时使用"-ansi-pedantic"编译选项,会不使用GNU C扩展语法，容易报错.一般不这么使用.*

*do{}while(0)主要用于宏，目的是保证宏定义的使用者能无编译错误的使用宏.*

### 3.6 工具链

*交叉工具链构建比较复杂,一般通过下载得到.*

*ARM linux工具链解析:*
	
	arm-linux-gnueabihf-gcc /*hf:硬浮点(用于加速编译);abi:(application binary interface)应用程序二进制接口.*/

*公司一般通过"SSH"链接客户端与服务器.*
***
## 第十一章 内存与I/O访问

### Cache & DMA

**Cache原理:**

*Cache:CPU缓存,位于CPU与内存之间的临时存储器.容量比内存小得多但交换速度比内存快得多.通常cache与主存在一定范围内保持适当的比例关系,cache的命中率90%以上(一般比例为4:1000)e.g. 128KB cache映射32MB内存;256KB可映射64MB内存.*

**cache一致性问题:**

*CPU需要操作的数据和结果优先从cache中拿或者写回到cache.*

*1)外设对内存数据的修改不能保证cache同样得到更新;*

*2)处理器对cache中内容的修改不能保证内存中的数据得到更新.*

*cache一致性问题最终解释为:cache中数据与内存中数据需要是一致的.*

*处理cache与DRAM存取一致性方法:*

	贯穿读出式(Look Through):CPU首先请求cache，如果命中，切断主存请求;不命中,请求DRAM.
	旁路读出式(Look Aside):CPU同时请求cache和DRAM，cache速度快，如果命中cache将数据送给CPU的同时切断CPU对DRAM的请求;
	否则cache不做任何动作，CPU访问DRAM.
	写穿式(Write Through):CPU写到cache的同时也写入DRAM.
	回写式(Copy Back):一般只写到cache,当cache中的数据得到更新而DRAM中数据不变,cache中会设置一个标记.当cache中的数据再
	一次准备更新前会将cache中的数据写入DRAM中，进而才更新.

**DMA原理:**

*DMA:无需CPU参与,让外设与内存直接进行双向数据传输的硬件机制.是一种内存与外设之间进行数据传输的方式.*

**Cache与DMA的一致性问题**

*1)外设数据到CPU:DMA将外设数据传到DRAM，cache中保留的仍是旧数据,CPU从cache中拿到错误的数据.*
	
	解决:CPU在读取cache中的数据之前,先进行cache_invalidate作用,保证从DRAM读取数据到cache再到CPU.

*2)CPU数据到外设:CPU处理的数据结果存放到cache，此时cache中的数据还没写回到DRAM;DMA从DRAM中取数据送到外设取到的为错误的数据.*

	解决:DMA处理之前先进行cache_flush(刷新数据到DRAM),保证DMA取到的数据为最新的数据.

