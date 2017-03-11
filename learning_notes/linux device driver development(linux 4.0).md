# Linux device driver development(linux4.0)
***
## 第一章	linux设备驱动概述及开发环境构建

**驱动针对的对象是存储器和外设,而不是CPU内核,主要分为3个基础大类:**

1)字符设备:必须以串行顺序依次进行设备的访问(e.g. 鼠标、触摸屏等).

2)块设备:顺序任意,以块为单位进行操作(e.g. 硬盘、eMMC等).

3)网络设备:面向网络数据包的发送和接收,主要使用套接字.

字符设备和块设备都会映射到linux文件系统的文件和目录,通过文件系统的系统调用接口open、read、write、close等即可访问.

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
		/*节点下含有多个设备(次设备来区分0~N),container_of可以包含多个同样的设备*/
		dev = container_of(inode->i_cdev, struct light_cdev, cdev);	
		/*para1:inode->i_cdev(表明是字符设备),结构体成员的指针;para2:设备结构体(表明具体是哪个字符设备);
		para3:cdev(为inode->i_cdev结构体成员的类型).通过结构体成员的指针获得设备结构体的指针*/
	
		/*设备结构体作为文件(filp)的私有数据(private_data)，后续的read/write/ioctl/llseek函数通过filp->private_data
		访问设备结构体,体现linux面向对象的设计思想.*/
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
		/*__user:为一个宏,linux中定义的.表明后面的指针指向用户空间.*/
		
		/*通过filp(fd)获得设备结构体*/
		struct light_cdev *dev = filp->private_data;
		/*使用dev进行相关的读操作*/
		
		/*copy_to_user函数
		para1:目标地址e.g.(buf)
		para2:源地址e.g.(&(dev->value))
		返回为不能复制的字节数,成功时返回0;失败返回负值.
		*/
		if(copy_to_user(buf, &(dev->value), 1))
			return -EFAULT;	/*EFAULT:Bad address*/
		...
	}

	/*write function*/
	ssize_t xxx_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
	{
		/*__user:为一个宏,linux中定义的.表明后面的指针指向用户空间.*/
		
		/*通过filp(fd)获得设备结构体*/
		struct light_cdev *dev = filp->private_data;
		/*使用dev进行相关的写操作*/

		/*copy_from_user函数
		para1:目标地址e.g.(&(dev->value))
		para2:源地址e.g.(buf)
		返回为不能复制的字节数,成功时返回0;失败返回负值.
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

	/*llseek  function*/
	loff_t xxx_llseek(struct file *filp, loff_t offset, int orig)
	{
		/*该函数被用户调用后更新文件的当前位置,并返回这一个位置.*/
		/*文件指针:表示当前读/写数据在文件中的位置.
		文件读写指针:指示当前的读写位置(是一个变量)
		*/
		loff_t ret = 0;
		switch(orig) {
		case 0:	/*SEEK_SET:文件头*/
			if(offset < 0) {
				ret = -EINVAL;	/*Invalid argument*/
				break;
			}
			if((unsigned int)offset > GLOBALMEM_SIZE)	/*GLOBALMEM_SIZE:文件的最大值*/
			{
				ret = -EINVAL;
				break;
			}
			filp->f_pos = (unsigned int)offset;	/*更新文件当前位置*/
			ret = filp->f_pos;
			break;
		case 1: /*SEEK_CUR:当前位置*/
		if((filp->f_pos + offset) > GLOBALMEM_SIZE) {
			ret = -EINVAL;
			break;
		}
		if((filp->f_pos + offset) < 0) {
			ret = -EINVAL;
			break;
		}
		filp->f_pos += offset;
		ret = filp->f_pos;
		break;
		default: /*其他情况不支持(包括从文件尾)*/
			ret = -EINVAL;
			break;
		}
		return ret;
	}
	struct file_operations light_fops = {
		.owner = THIS_MODULE,
		.open = xxx_open,
		.release = xxx_release,
		.read = xxx_read,
		.write = xxx_write,
		.ioctl = xxx_ioctl,
		.llseek = xxx_llseek,
	};
	
	/*Module init function*/
	int __init xxx_init(void)
	{
		/*申请设备号*/
		dev_t devno;	/*保存设备号*/
		alloc_chrdev_region(&devno, 0, 1, "led");
		/*light_devp = kmalloc(sizeof(struct light_dev), GFP_KERNEL);
		kmalloc中:para1分配块大小(单位为字节),para2分配标记(GFP_KERNEL:内核空间进程中申请内存).
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

冯 诺依曼结构:指令存储器和数据存储器合并在一起构成一个存储器,因此指令和数据的位宽一样.

哈佛结构:指令和数据分开存储,指令和数据的位宽可以不一样；同时程序(指令)总线和数据总线分开,效率高.

改进的哈佛结构:改进为公用的地址总线和数据总线(程序和数据存储器分时共用这两条总线).数据总线完成程序存储器或数据存储器于CPU的数据交换;地址总线完成寻址程序或数据.

指令集:CPU分为两类(RISC--精简指令集; CISC--复杂指令集).

### 2.2 存储器

#### ROM & Flash
 
ROM:EEPROM完全可以用软件来擦写.

NOR(或非):类SRAM接口,可芯片内执行(execute in place, XIP).

NAND(与非):以块方式访问,不支持芯片内执行.

CFI(Common Flash Interface):公共闪存接口,是一个从NOR flash中读取数据的公开、标准接口,可使用系统软件查询到Flash器件的各种参数.

Flash的编程原理是将1写0,不能将0写1.擦除过程是将所有位都写1.

OTP(One-Time Programmable):一次性可编程存储器,由SoC继承一个eFuse电编程熔丝作为OTP.
#### RAM

DRAM:电荷形式存储,数据存储在电荷中,因为电容器漏电会出现电荷丢失,因此DRAM器件需要定期刷新.

SRAM:静态RAM,晶体管组成,供电保持固定值，没有刷新周期.

DPRAM:双端口RAM,两个处理器之间交互数据.一端写入数据,另一端通过轮询或中断获知并读取其写入的数据.

### 2.3 接口与总线

#### 串口

**Uart是"TTL"电平的串口(并行转串行);RS232是"RS232"电平的串口.**

CPU带的串口为Uart，内部通过CMOS/TTL与RS232电平转换得到RS232串口,所以通常电脑或板子用的串口为RS232.

#### I2C

I2C(内置集成电路):两线式串行总线,用于连接微控制器及其外围设备.两个信号线分别为SDA(数据线)、SCL(时钟线).

**SCL稳定在高电平时,SDA由高电平到低电平的变化将产生一个开始位;由低电平到高电平的变化将产生一个停止位.**

#### SPI

SPI(Serial Peripheral Interface):同步串行外设接口,使CPU与各种外设以串行方式进行通信.一般主控为:SoC,从设备为:外设.

#### USB

USB:通用串行总线.

USB主机控制器(简称USB主机)用于连接USB外设;USB设备适配器(简称USB设备)用于作为其他计算机系统的USB外设(e.g. 手机充当U盘).

USB系统的物理拓扑系统包括:USB主机,USB设备,Hub(USB集线器(其他还有网络Hub)--用于USB扩展，进而可连接多个USB设备).


#### eMMC

eMMC(Embedded Multi Media Card) = NAND Flash + 闪存控制芯片 + 标准接口封装，属于多芯片封装--MCP(Multi-Chip Package).

eMMC接口电压分为1.8V和3.3V两种.SSD(Solid State Disk) = 多个NAND Flash + 多主控(闪存控制芯片) + 缓存, eMMC都为单个.
***
## 第三章 Linux内核及内核编程

内核抢占:一个内核任务可以被抢占,提高系统的实时性.但存在一些不可抢占区间(e.g. 中断上下文、软中断、自旋锁等原子上下文进程).

总线、设备和驱动模型:总线将设备和驱动联系起来.

	总线中的match()函数用来匹配设备和驱动,匹配成功就会执行驱动程序中的probe()函数.

### 3.1 linux内核组成
linux内核主要由:进程调度(SCHED)、内存管理(MM)、虚拟文件系统(VFS)、网络接口(NET)、进程间通信(IPC)五部分组成.

	1)进程调度:处于系统的中心位置,内核中使用task_struct(位于./include/linux/sched.h定义)描述进程.
	2)内存管理:控制多个进程安全地共享主内存区域.
	3)虚拟文件系统:隐藏各种硬件的具体细节,为应用程序操作具体设备提供统一的接口.而且独立于各个具体的文件系统,对各种文件系统(ext2、FAT等)进行抽象.
	4)网络接口:包括网络协议(负责实现网络传输协议)和网络驱动程序(负责与网络硬件设备通信).上层应用程序统一使用套接字接口.
	5)进程间通信:信号量、共享内存、消息队列(System V IPC)、管道、UNIX域套接字等.

### 3.2 linux内核编译及加载

./configs/xxx_defconfig:为某电路板的默认配置,"make xxx_defconfig"为xxx开发板配置内核.

Kconfig(配置文件):给用户提供配置选项的功能.

"make xxx_defconfig"和"make menuconfig"均会写入一个".config"配置文件中.该配置文件记录哪些被编译进内核，哪些被编译为模块.

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

1)目标定义:
	
	obj-y += foo.o	/*由foo.c或foo.s编译得到foo.o并链接进内核(无条件编译)*/
	obj-m += foo.o	/*foo.c作为模块编译, 而obj-n表示不编译*/
2)多文件模块定义:

采用"模块名-y"或"-objs"定义模块的组成文件
	
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
除了"menu...endmenu"这种形成菜单外;依赖关系也有可能形成菜单.

	General setup---位于./init/Kconfig(可以通过make menuconfig中的help找到位置)

choice...endchoice定义选择群菜单:
	
	"选择群菜单"点开之后是下面这种效果:
	(X)Gzip
	()LZMA
	()XZ
	()LZO
	()LZ4

**驱动写好后,Kconfig和Makefile需要的操作:**

1)Kconfig

Kconfig在某个目录下编辑好后,需要在./arch/arm/Kconfig中添加:
	
	source "drivers/Kconfig"	/*在"./arch/arm/Kconfig中添加,包括了drivers下面的Kconfig"*/
	source "drivers/alidrivers/modules/Kconfig" /*在"./drivers/Kconfig"中添加,包括了modules下面的Kconfig*/
	/*(drivers/alidrivers/modules/Kconfig)中描述alidsc的菜单信息*/

2)Makefile

	obj-y += alidrivers/modules/		/*在"./drivers/Makefile"中添加,强制(无条件)进入该目录"alidrivers/modules/"*/
	obj-$(CONFIG_ALI_DSC) += alidsc/		/*在"./drivers/alidrivers/modules/Makefile"中添加,根据"$(CONFIG_ALI_DSC)"决
	定是否进入"alidsc/"目录.*/
	obj-$(CONFIG_ALI_DSC) += alidsc.o	/*在"./modules/alidsc"中添加具体的编译命令*/

### 3.4 Linux内核引导

SoC内嵌bootrom,一上电bootrom即运行,其他CPU进入WFI状态等待CPU0唤醒.CPU0中的bootrom会引导bootloader(在ROM中),bootloader引导kernel,在kernel启动阶段CPU0发出中断唤醒其他CPU运行.

内核镜像zImage包括解压算法和被压缩的内核,bootloader引导kernel时利用解压算法解压zImage解出kernel进行引导.

### 3.5 Linux下的C编码特点

**Linux编码风格**

1)命名:下划线为主

	#define PI 3.1415926
	int min_value, max_value;	/*变量名下划线分割*/
	void send_data(void);	/*函数下划线分割*/

2)"{}"使用:
	
	(1)结构体、if/for/while/switch "{"不另起一行, 如果只有一句不要加"{}"
	(2)if...else, else语句不另起一行
	(3)函数另起一行
	(4)switch...case对齐
	(5)空格使用"for ( i = 0; i < 10; i++ ) {"

**GNU C**

linux用的C编译器为GNU C编译器.

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

作用于函数、变量和类型,以便手动优化代码和定制代码检查(方法"__attribute__((noreturn/format/section/aligned/packed))",一般在声明后面添加).

	noreturn:作用于函数,函数不返回.
	unused:作用于函数和变量,表示可能不会用到,避免编译器产生警告信息.
	aligned:作用于变量、结构体、联合体，指定对齐方式.e.g.__attribute__((aligned(4)))
	packed:作用于变量与类型,表示最小可能的对齐或者使用最小的内存.

**(5)内建函数"__builtin"开始**

如果编译时使用"-ansi-pedantic"编译选项,会不使用GNU C扩展语法，容易报错.一般不这么使用.

do{}while(0)主要用于宏，目的是保证宏定义的使用者能无编译错误的使用宏.

### 3.6 工具链

交叉工具链构建比较复杂,一般通过下载得到.

ARM linux工具链解析:
	
	arm-linux-gnueabihf-gcc /*hf:硬浮点(用于加速编译);abi:(application binary interface)应用程序二进制接口.*/

公司一般通过"SSH"链接客户端与服务器.
***
## 第四章 Linux内核模块

内核模块通过(insmod/lsmod/rmmod)进行模块加载/查看/卸载等操作.

"/proc/modules"保存insmod加载的模块信息(cat /proc/modules查看),"lsmod"查看时即是调用该文件.

**"/sys/modules"目录下保存了所有已加载的驱动模块的信息,每个模块都有一个目录.**

modprobe/modprobe -r filename:加载/卸载模块时会同时加载/卸载其依赖模块,比insmod/rmmod功能更强大.

"modinfo 模块名:获得模块信息(author、description、depends等等)."

**内核模块许可证(licnese)包括"GPL"、"GPL v2"、"GPL and addtional rights"、"Dual BSD/GPL"、"Dual MPL/GPL",常用的为"GPL v2".**

linux错误号位置:

1-34号在./include/uapi/asm-generic/errno-base.h

35-133号在./include/uapi/asm-generic/errno.h

512-529号在./include/linux/errno.h

**标识为"__init"的函数如果编译进内核以及定义为"__initdata"的数据，只会在初始化阶段存在,初始化完成后就会释放它们占用的内存.**

**标识为"__exit"的函数如果模块被编译进内核会直接忽略(模块被内置，就不会卸载它了).退出阶段才用的数据可以用"__exitdata"标识.**

### 模块参数及导出符号

**模块参数**

用于向模块传递参数(e.g.insmod xxx.ko args=xxx)

	static char *book_name = "Linux Device Driver";
	module_param(book_name, charp, S_IRUGO);	/*module_param:表明是模块参数(charp:字符指针)*/
	static int book_num = 4000;
	module_param(book_num, int, S_IRUGO);	/*module_param(变量名, 变量类型, 参数读/写权限)*/

模块参数传进模块为一个全局变量,整个模块中都可以引用.同时在"/sys/modules/para"会有模块的参数目录

**导出符号**

导出符号可以被其他模块使用,只需使用前声明下.

	EXPORT_SYMBOL(符号名);	/*可以导出函数名e.g.EXPORT_SYMBOL(func_name);*/
	EXPORT_SYMBOL_GPL(符号名);	/*符合GPL许可的模块*/
***
## 第五章 Linux文件系统与设备文件

### 5.1 linux文件系统操作

**系统调用**

1)创建

	int creat(const char *filename, mode_t mode);	/*filename:创建的文件名;mode:权限(S_I"R/W/X""USR/GRP/OTH"或者S_IRWX"U/G/O")*/
	/*由于filename没有路径可以指定,一般用的比较少*/

2)打开

	int open(const char *pathname, int flags);	/*pathname:文件名(含路径);flags:标志(O_RDONLY、O_WRONLY、O_RDWR、O_NONBLOCK等)*/
	int open(const char *pathname, int flags, mode_t mode); /*针对flags标志为:O_CREATE,融合了create(创建)函数.*/
	
	char dev_name[128] = {"/dev/dsc0"};
	...
	fd = open(dev_name, O_RDWR); /*返回文件描述符fd(为一个int类型),创建成功返回值为非负整数*/
	if (fd < 0)
	{
		/*print some error message...*/
	}

3)读写

	int read(int fd, void *buf, size_t length); /*从fd读length(以字节(size_t)为单位)个字节读到buf缓冲区,返回实际读取的字节数*/
	int write(int fd, const void *buf, size_t length); /*将length字节数据从buf写到fd,返回实际写入的字节数*/	

4)定位

	int lseek(int fd, offset_t offset, int whence);	/*offset:偏移量(其实为int型);返回值为文件读写指针相对文件头的位置*/
	whence取值:
	SEEK_SET(0):文件开头(offset相对文件开头偏移)
	SEEK_CUR(1):文件读写指针当前位置(offset相对当前位置)
	SEEK_END(2):文件末尾(offset相对文件末尾)
	/*取得文件的长度:file_length = lseek(fd, 0, SEEK_END);*/

5)关闭
	close(fd);

一般文件在读取完后面需要加上'\0'结束.

**C库函数操作**

...省略了

### 5.2 Linux文件系统

**Linux文件系统目录结构**

/dev:该目录为系统中包含的设备文件(即设备节点),应用程序通过对该目录下的文件进行读写、控制以访问实际的设备.

/proc:进程、内核信息(CPU、硬盘分区、内存信息等)放置在该目录.proc为伪文件系统proc(不是真正的文件系统)的挂载目录,proc文件系统存在与内存中.

cat /proc/devices:获知系统中注册的设备(字符设备和块设备)

/sys:sysfs文件系统映射到该目录,linux设备驱动模型中的总线、驱动、设备在该目录下有对应的节点.

**linux文件系统与设备驱动**

应用程序与VFS之间的接口是系统调用;VFS与文件系统(ext2/fat/btrfs等)、设备文件(/dev/ttyS1、/dev/sdb1、/dev/dsc0等)、特殊文件系统(/proc、/sys等)--(这些属于同一层次)之间的接口是file_operations结构体成员函数.

字符设备上层没有文件系统(e.g. ext2),因此字符设备的file_operation由自己的设备驱动提供,像块设备由于文件系统中实现了file_operations,因此设备驱动层看不到file_operations.

**file结构体**

struct file打开文件时创建，然后传递给对文件进行操作的函数(e.g. read/write/ioctl)

struct file结构体中的私有数据指针"private_data",用以指向用于描述设备的结构体.

判断文件打开是以阻塞方式还是非阻塞方式:

	if (file->f_flags & O_NONBLOCK)		/*非阻塞*/
		pr_debug("open: non-blocking\n");
	else
		pr_debug("open: blocking\n");	/*阻塞*/

**inode**

inode是linu管理文件系统的最基本单位,也是文件系统连接任何子目录、文件的桥梁.

	/*从节点(inode)获得设备结构体*/	
	dev = container_of(inode->i_cdev, struct light_cdev, cdev);	/*i_cdev:表示字符设备*/

### 5.3 udev用户空间设备管理

**devfs**

linux 2.4内核中,devfs作为对设备进行管理的文件系统(虚拟文件系统).挂载于/dev目录下,管理该目录下的所有设备.由于存在众多缺点(e.g.运行内核空间),后来没被再使用.

**sysfs**

linux 2.6以后的内核中,作为对设备进行管理的文件系统(虚拟文件系统).挂载与/sys目录下.sysfs是为了展示设备驱动模型中各组件(设备、总线、类等)的层次关系.sysfs可以被user space读写,而udev作为一个工具,利用sysfs提供的信息对dev进行相关的操作.

linux使用struct bus_type、struct device_driver、struct device来描述总线、驱动、设备,位于"./include/linux/device.h",使用时e.g. #include <linux/device.h>

结构体device_driver和device依附于struct bus_type,都包含有struct bus_type指针.struct bus_type中的match()函数将两者捆绑在一起.一旦绑定之后,xxx_driver的probe()函数就会执行(xxx:总线名e.g. platform、pci、i2c、spi、usb、see).

**udev**

udev是一种工具(运行在用户空间),根据系统中的硬件设备状况更新设备文件(即/dev下的设备文件),e.g.动态建立/删除设备文件.

udev有自己的规则更新/dev下的设备文件(e.g. windows连接usb转串口设备时，udev在设备管理器中显示为:usb-serial,可以认为是udev作规则作用的结果. linux中/dev下的dsc0表示dsc设备第0个次设备).

udev需要sysfs、tmpfs的支持,sysfs为udev提供设备入口和uevent通道，tmpfs为udev提供存放设备文件(/dev)的空间.
***
## 第六章 字符设备驱动

### 6.1 Linux字符设备驱动结构

**cdev结构体**

cdev结构体用于描述一个字符设备:

	struct cdev {
		struct kobject kobj;	/*内嵌的kobject对象*/
		struct module *owner;	/*所属模块*/
		struct file_operations *ops;	/*文件操作结构体*/
		struct list_head list;
		dev_t dev;		/*设备号*/
		unsigned int count;
	};

dev_t dev用于描述设备号(32 bit)
	MAJOR(dev_t dev);	/*获得主设备号(12bit)*/
	MINOR(dev_t dev);	/*获得次设备号(20bit)*/
	MKDEV(int major, int minor);	/*利用主设备号和此设备号生成dev_t(设备号)*/

cdev_init():初始化cdev成员,并建立cdev和file_operations之间的联系
	
	void cdev_init(struct cdev *, struct file_operations *);

cdev_alloc():动态申请cdev内存(无论什么内存申请,单位都是字节)

	struct cdev *cdev_alloc(void);	
	/*其源代码中使用到了
	struct cdev *p = kzalloc(sizeof(struct cdev), GFP_KERNEL); /*kzalloc结合kmalloc申请内核内存和memset初始化*/
	kzalloc返回设备结构体的指针--指向分配的内存(单位为字节)
	*/

cdev_add():添加一个cdev设备,在注册时调用

	int cdev_add(struct cdev *, dev_t, unsigned);	/*unsigned:数量. 成功时返回0,失败返回非0值.*/
	/*e.g. cdev_add(&dev->cdev, devno, 1);*/

cdev_del():删除一个cdev设备,在注销时调用

	void cdev_del(struct cdev *);

**分配和释放设备号**

	int register_chrdev_region(dev_t from, unsigned count, const char *name); /*已知设备号(dev_t from);count:数量;
	name:设备名字.dev_t from一般由MKDEV(int major, int minor)构造---因此用的比较少*/
	int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name);
	/*动态申请设备号(申请好的存放在dev_t *dev中),baseminor:次设备号(一般从0开始)*/

	void unregister_chrdev_region(dev_t from, unsigned count);

注册顺序:先申请设备号然后注册设备;注销顺序:先注销设备再释放设备号.

**file_operations结构体**

1) unlocked_ioctl():一般使用".unlocked_ioctl() = xxx_ioctl(),"赋值.提供设备相关控制cmd(命令)的实现.成功返回非负值.

2) mmap():建立内核空间到用户空间(即进程)的虚拟地址空间的映射(即内核内存到用户内存的映射).映射成功后,用户对这段内存的操作直接反应到内核空间(内核内存),同样内核空间对这段内存的操作也直接反应到用户空间. *针对需要大量数据传输的操作效率非常高*

*进程在mmap映射过程中的文件内容的改变不会立即写回到磁盘文件中,写回操作是在调用munmap()后才执行,可以通过调用msync()来实现同步.-----一般用的较少.*

*用户空间的mmap声明:*

	void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offset)
	/*各参数说明:
	start:起始地址,一般为NULL(即为0),表示有内核来指定该内存地址
	length:要映射内存区域的大小
	prot:内存保护标志(PROT_EXEC(页内容可以被执行)、PROT_READ(页内容可以读取)、PROT_WRITE()页可以被写入、PROT_NONE(页不可以被访问))
	flags:指定映射对象的类型,映射选项和映射页是否可以共享.使用"MAP_SHARED"居多,允许其他映射该文件的进程共享.
	fd:文件描述符号(open的返回)
	offset:偏移,通常为0.该值为PAGE_SIZE的整数倍.
	*/

*返回值:成功时返回被映射区的指针,munmap返回0.失败时,mmap()返回MAP_FAILED(其值为(void \*)-1),munmap返回-1.*

	int munmap(void *start, size_t length) /*start:起始地址；length:大小*/

内核驱动中的mmap使用:
	
	.mmap = xxx_mmap,	/*file_operations中*/
	static int xxx_mmap(struct file *filp, struct vma_area_struct *vma) /*驱动中的实现*/
	{
		...
		page = virt_to_phys(buffer);	/*buffer:内核中的buffer.得到buffer对应的物理地址(page)*/
		if(remap_pfn_range(vma, vma->vm_start, page>>PAGE_SHIFT, 
			(unsigned long )(vma->vm_end-vma->vm_start), vma->vm_page_prot))
		{
			...(一些错误信息)
		}
		/*remap_pfn_range:
		para1:struct vma_area_struct *vma(vma结构体指针)
		para2:虚拟地址起始地址
		para3:物理地址(page>>PAGE_SHIFT---内核中定义的宏)
		para4:映射空间大小,单位为字节
		para5:给vma要求的"protection"一般直接使用vma->vm_page_prot.如果要求用户空间读数据时不经过cache可以:
		vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);再传入vma->vm_page_prot.
		*/
	}

3)poll调用(主要针对非阻塞I/O)

非阻塞的I/O应用程序常会使用select(用户空间调用)、poll(内核空间)来查询是否可以对设备进行无阻塞的访问.

select(用户空间):监控多个文件,如果没有一个文件满足(读/写)要求,select将会阻塞调用的进程.

	int select(int maxfdp, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, const struct timeval *timeout);
	/*
	maxfdp:需要检查的文件描述符个数(fd的数目),一般为后面三个fd_set中的最大值+1"max(readfds, writefds, exceptfds)+1"
	readfds:检查可读性的一组文件描述符集
	writefds:检查可写性的一组文件描述符集
	exceptfds:检查意外状态的文件描述符集(ps:错误不是意外状态)
	timeout:等待时间(NULL表示无限等待)
	*/

select中任何一个文件满足要求都将返回,正常返回满足要求的文件描述符个数;如果没有满足要求的将会阻塞(进程睡眠)直到超时返回0；中断或出错返回-1.

fd_set的构造:

	fd_set rds/wds/eds;
	void FD_ZERO(fd_set *fdset); /*清空文件描述集*/	e.g.FD_SERO(&rds);
	void FD_SET(int fd, fd_set *fdset); /*添加fd到fdset中*/	e.g.FD_SET(fd, &rds);
	void FD_ISSET(int fd, fd_set *fdset);	/*在调用select后使用它来检测fdset是否发生了变化(置位)*/	FD_ISSET(fd, &rds);
	void FD_CLR(int fd, fd_set *fdset); /*从fdset中清除掉fd*/

poll(内核空间)

返回是否能对设备进行无阻塞读、写访问的掩码.

	unsigned int xxx_poll(struct file *filp, struct poll_table *wait)
	{
		...
		poll_wait(filp, &engine->OutWq, wait);	/*将filp所代表的进程加入到poll_table等待列表(实际上为绑定到poll_table队列
		元素),然后将poll_table等待队列元素添加到engine这个设备结构体的等待队列头部中,等待被唤醒*/
		/*一旦其他的操作导致filp有动作(e.g.往filp中写入数据),将会唤醒engine->OutWq等待队列头部中的所有等待队列元素---即为包含
		的所有进程.然后继续往下执行;如果没有被唤醒则会直到超时(select中的timeout设置的时间)*/
	
		if(have_data)	
			mask |= POLLIN | POLLRDNORM;	/*have_data为真时,poll会返回mask,表明可读*/  /*可写为(POLLOUT | POLLWRNORM)*/
		return mask;
	}

poll函数实现了调用select而阻塞的进程可以被等待队列头部唤醒.**但不会将进程阻塞!!**

**ioctl函数**

对于不支持的命令(cmd),ioctl()函数应该返回"-EINVAL";

ioctl()命令生成:

	#define CA_DSC_BASE	0xc1	/*幻数("type"),8 bit(0-0xff),
	根据./Documentation/ioctl/ioctl_num.txt选择,避免与已经使用的冲突*/
	#define CA_SET_FORMAT	_IOW(CA_DSC_BASE, 1, int/*format*/)		/*命令CA_SET_FORMAT*/
	/* _IOW:表示写(从应用程序角度看);CA_DSC_BASE:type;1:序列号-8 bit(0-0xff);int:size(数据类型字段)
	_IO(type, 序列号)
	_IOR(type, 序列号, 数据类型字段)
	_IOW(type, 序列号, 数据类型字段)
	_IOWR(type, 序列号, 数据类型字段)
	*/
	#define CA_CREATE_KL_KEY	_IOW(CA_DSC_BASE, 2, struct ca_create_kl_key)

**设备节点创建**

设备节点:即是驱动open函数中的inode(或应用程序open函数中的第一个参数),也即是/dev下面的设备文件(设备节点).

自动创建设备节点(在cdev_init和cdev_add之后):

	/*class_create可在./driver/class.c中找到原型; device_create可在./driver/core.c中找到原型*/
	
	static struct class *xxx_class;	/*全局变量,xxx_class是一个类,由class_create赋值*/
	static struct device *xxx_device; /*全局变量,xxx_device是由device_create赋值,进行判断device(设备节点)创建成功与否*/
	#define DEVICE_NAME "xxx_device_name" /*xxx_device_name是在/dev目录下显示的设备节点*/
	#define XXX_CLASS_NAME	"xxx_class_name"	/*xxx_class_name是/sys/class目录下的一个类名*/

	xxx_class = class_create(THIS_MODULE, XXX_CLASS_NAME);	/*创建/sys/class目录下"XXX_CLASS_NAME"类名*/ 
	...
	xxx_device = device_create(xxx_class, NULL, devno, NULL, DEVICE_NAME) /*创建设备(节点DEVICE_NAME)*/
	/*
	para1:设备类(struct class *class)
	para2:父亲设备(struct device *parent),一般为NULL
	para3:设备号(dev_t devt)
	para4:数据(void *drvdata),一般为NULL
	para5:在/dev下显示的设备文件名(节点)(const char *fmt)
	*/
	if(xxx_device == NULL){
		/*print some fail message!*/
	}
	
	/*注销device*/
	device_destroy(xxx_class, devno);
	/*注销class*/
	class_destroy(xxx_class);
	
手动创建设备节点

	mknod /dev/globalmem c 230 0	/*mknod:创建命令;/dev/globalmem:节点名;c:字符设备;230:主设备号;0:此设备号*/
***
## 第七章 Linux设备驱动中的并发控制

*多个进程对共享资源的并发访问会导致竞态.*

### 7.1 并发与竟态

并发：指多个执行单元同时、并行的执行.

竟态:多个并发的执行单元对共享资源(硬件资源/软件资源(全局变量、静态变量等))等的访问容易导致竟态.

**竟态可能发生于进程与进程之间(进程抢占)、中断与进程之间(中断服务程序访问进程正在访问的资源)、中断与中断之间(高优先级中断).**

解决竟态的方法是保证对共享资源的互斥访问.

访问共享资源的代码区称为临界区,将临界区以某种互斥机制保护起来(包括中断屏蔽、原子操作、自旋锁、信号量、互斥体等).

### 7.2 编译乱序和执行乱序

**编译乱序**

代码编译后得到的汇编码可能不是严格按照代码的逻辑顺序排布的(特别是使用了"-O2"优化编译选项)

解决:加上编译屏障

	#define barrier() __asm__ __volatile__("":::"memory")	/*汇编时的编译屏障*/

	1)e = d[4095];
	barrier();	/*未加barrier()时,1和3、4句可能会在汇编时乱序,加上之后按照正常的逻辑顺序排布*/
	3)b = a;
	4)c = a;

*volatile的作用*

	volatile int i = 10; /*volatile会告诉编译器,i的值随时可能发生变化，每次使用i的值必须从其地址去读.*/
	int j = i;
	int k = i; /*如果i没有使用volatile修饰,k取到的值就是j读的那次的值(因为j读i的值时没有对i进行任何操作)*/
	/*而使用了volatile修改后,k的赋值是根据i的地址获得i的值之后再赋给k.*/

volatile一般用于修饰register,因为register容易被其他的操作更改其值.

**执行乱序**

即使编译后的指令顺序正确,但是有CPU是"乱序执行(Out-of-Order-Execution)"策略,CPU本质决定的.

内核有一些内存屏障指令来确保执行正序(DMB/DSB/ISB等)----用的比较少.

### 7.3 中断屏蔽

中断屏蔽:单CPU避免竟态的一种简单的方法.将使得中断与进程之间的并发不再发生,进程抢占的并发也不再发生(进程调度依赖于中断来实现).

	local_irq_disable()	/*中断屏蔽*/
	...
	critical section	/*临界区代码*/
	...
	local_irq_enable()	/*中断使能*/

linux的异步I/O、进程调度都依赖于中断,因此不能长时间的屏蔽中断(会导致数据丢失或者系统崩溃).临界区代码需要尽快执行完.

*SMP的多CPU引发的竟态常常使用中断屏蔽+自旋锁.*

local_irq_save(flags)/local_irq_restore(flags)除了禁止/恢复中断操作外,还保存CPU的中断信息.

**禁止/使能中断低半部:local_bh_disable()/local_bh_enalbe().**

### 7.4 原子操作

原子操作保证一个整型数据(整型变量和位)的修改是排他性的.

**操作步骤:**

1)定义一个原子变量(整型),并初始化为1;

2)原子变量减1,并测试是否为0.第一个设备会使得原子变量变为0(为ture);如果再使用一个设备将会导致测试值为非0(为false),则退出.

	static atomic_t xxx_available = ATOMIC_INIT(1);	/*定义原子变量并初始化为1*/

	static int xxx_open(struct inode *inode, struct file *filp)
	{
		...
		if(!atomic_dec_and_test(&xxx_available))	/*原子变量xxx_available-1并测试是否为0,为0表示true则跳出;
		其他值表示已经打开了一个设备,为false,取反后为真,进入后面的代码*/
		{
			atomic_inc(&xxx_available);
			return -EBUSY;	/*已经打开*/
		}
		...
		return 0;
	}

	static int xxx_release(struct inode *inode, struct file *filp)
	{
		atomic_inc(&xxx_available);	/*释放了设备,自增1*/
		return 0;
	}

**整型原子操作相关函数:**

1)定义原子变量并初始化:
	
	atomic_t v = ATOMIC_INIT(i);	/*定义原子变量v并初始化为i*/
	void atomic_set(atomic_t *v, int i);	/*设备原子变量v的值为i*/

2)获取原子变量的值:
	
	atomic_read(atomic_t *v);	/*返回原子变量v的值*/

3)原子变量加/减(+/-)、自增/减:
	
	void atomic_add(int i, atomic_t *v);	/*原子变量v加i*/
	void atomic_sub(int i, atomic_t *v);	/*原子变量v减i*/
	void atomic_inc(atomic_t *v);			/*原子变量v自增1*/
	void atomic_dec(atomic_t *v);			/*原子变量v自减1*/

4)操作并测试/返回:
	
	int atomic_inc_and_test(atomic_t *v);	/*原子变量v自增1并测试是否为0,为0返回true;否则返回false*/
	int atomic_dec_and_test(atomic_t *v);	/*原子变量v自减1并测试是否为0,为0返回true;否则返回false*/
	int atomic_sub_and_test(int i, atomic_t *v);	/*原子变量v减i后并测试是否为0,为0返回true;否则返回false*/
	
	int atomic_add/sub_and_return(int i, atomic_t *v);	/*原子变量v加/减i后返回新值*/
	int atomic_inc/dec(atomic_t *v);	/*原子变量v自增/自减后返回新值*/

**位操作**

	void set_bit(nr, void *addr);	/*设置地址addr的第nr位,即写1*/
	void clear_bit(nr, void *addr);	/*清除地址addr的第nr位,即写0*/
	void change_bit(nr, void *addr);	/*将地址addr的第nr位反转*/
	test_bit(nr, void *addr);	/*返回addr的第nr位*/
	...

### 7.5 自旋锁

自旋锁是一种对临界资源进行互斥访问的手段.特点:如果所被占用,试图获得锁的代码将会一直处于"自旋"状态,等待锁.

**自旋锁的操作步骤:**

	spinloc_t lock;			/*定义一个自旋锁*/
	spin_lock_init(&lock);	/*初始化自旋锁,会调用内容中./include/linux/spinlock.h中宏"spin_lock_init"进行初始化*/
	...
	spin_lock(&lock);		/*获取自旋锁,保护临界区.如果没有获得锁,将会处于自旋,直到锁持有者释放*/
	.../*临界区*/
	spin_unlock(&lock);		/*解锁,释放自旋锁*/

**自旋锁使用例程:**

	int xxx_count = 0;		/*定义设备打开的状态变量,为临界资源.该临界资源会在其他多个地方监控,决定是否执行后续的操作.*/
	spinlock_t lock;	/*一般在设备结构体中*/
	
	int __init xxx_init(void)
	{
		...
		spin_lock_init(&lock);	/*在设备初始化函数中初始化自旋锁*/
		...
	}

	int xxx_open(struct inode *inode, struct file *filp)
	{
		...
		spin_lock(&lock);	/*试图获得锁,该核上操作该临界资源的其他进程被CPU暂时停止调度.其后续代码单独执行,直到释放调度重新启用*/
		if(xxx_count)		/*已经打开了设备*/
		{
			spin_unlock(&lock);	/*释放锁*/
			return -EBUSY;
		}
		xxx_count++;	/*增加使用计数*/
		spin_unlock(&lock);	/*释放锁*/
		...
		return 0;
	}
	
	int xxx_release(struct inode *inode, struct file *filp)
	{
		...
		spin_lock(&lock);
		xxx_count--;	/*减少计数值*/
		spin_unlock(&lock);

		return 0;
	}

*使用技巧:*

由于多核SMP的情况下,自旋锁可以保证临界区不受别的CPU抢占进程打扰(其他CPU上的抢占调度仍然正常运行),本CPU抢占调度禁止.但是还是会受到中断的影响.

	spin_lock_irq() = spin_lock() + local_irq_disable()	/*自旋锁+关中断*/
	spin_unlock_irq() = spin_unlock() + local_irq_enable()	/*释放锁+开中断*/
	spin_lock_irqsave() = spin_lock() + local_irq_save()	/*自旋锁+关中断+保存状态字*/
	spin_unlock_irqrestore() = spin_unlock() + local_irq_restore()	/*释放锁+开中断+恢复状态字*/
	spin_lock_bh() = spin_lock() + local_bh_disable()	/*自旋锁+关底半部*/
	spin_unlock_bh() = spin_unlock() + bh_irq_enable()	/*释放锁+开底半部*/

**一般使用的是:进程上下文中"spin_lock_irqsave()/spin_unlock_irqrestore()",中断上下文中(中断服务程序中)"spin_lock()/spin_unlock()"**

**读写自旋锁**

读写自旋锁对临界资源允许读的并发,写只能有一个进程操作,读和写也不能同时进行.

	rwlock_t lock;			/*定义读写自旋锁rwlock*/
	rwlock_init(&lock);		/*初始化rwlock*/

	read_lock(&lock);		/*读时获取锁,正常每个需要读取临界资源的操作都应该调用读锁定函数*/
	...						/*读临界资源*/
	read_unlock(&lock);		/*释放*/

	write_lock(&lock);		/*写时获取锁,只能有一个进程可获得*/
	...						/*操作临界资源*/
	write_unlock(&lock);

*顺序锁和RCU(读-复制-更新)省略*

### 7.6 信号量

信号量允许多个线程进入临界区.

### 7.7 互斥体

互斥体只允许一个线程进入临界区.
	
	struct mutex my_mutex;		/*定义互斥体my_mutex,一般在设备结构体中*/
	mutex_init(&my_mutex);		/*初始化mutex,一般在xxx_init(模块初始化函数中)*/
	mutex_lock(&my_mutex);		/*获取互斥体mutex,一般在操作临界资源前调用*/
	mutex_unlock(&my_mutex);	/*释放互斥体mutex,对临界资源操作完成后调用*/

**互斥体与自旋锁的区别:**

1)临界区较小,宜用自旋锁;临界区很大,应该使用互斥体

2)互斥体保护的临界区可以包含阻塞代码;自旋锁由于自旋效应,不能用于阻塞的场合.

3)互斥体用于进程上下文;自旋锁可用于中断上下文和进程上下文.

***
## 第八章 Linux设备驱动中的阻塞与非阻塞I/O

阻塞和非阻塞I/O是用户空间对设备的两种访问方式.

阻塞操作:在对设备进行访问时,如果所请求的资源不能得到满足时,则挂起进程(进程睡眠)直到可操作的条件满足后再进行后续操作.

非阻塞操作:如果对设备的请求不能满足时,并不挂起(睡眠).要么放弃;要么一直不停的查询,直到可以进行操作为止.

**阻塞时进程会睡眠,让出CPU资源给其他进程,睡眠的进程会放入一个等待队列中等待被唤醒.**

	/*阻塞的读串口的一个字符*/
	char buf;
	fd = open("/dev/ttyS1", O_RDWR);	/*默认会以阻塞方式打开*/
	...
	ret = read(fd, &buf, 1);	/*阻塞读一个字符,只有读到才会返回.否则会一直阻塞在这里*/
	if(ret)
	printf("%c\n", buf);

	/*非阻塞的读串口的一个字符*/
	char buf;
	fd = open("/dev/ttyS1", O_RDWR | O_NONBLOCK);	/*非阻塞方式打开*/
	...
	while(read(fd, &buf, 1) != 1)	/*由于为非阻塞,没读到也会返回.因此判断如果没有读到就在此处循环,直到读到一个字符*/
		continue;
	printf("%c\n", buf);

### 8.1 等待队列

*等待队列用于实现阻塞进程的唤醒.*

**等待队列的一些操作:**

1)定义"等待队列头部"

	wait_queue_head_t my_queue;

2)初始化"等待队列头部"

	init_waitqueue_head(&my_queue);

3)定义等待队列元素(该元素要放进等待队列中)

	DECLARE_WAITQUEUE(name, tsk);	/*定义一个等待队列元素,并与进程tsk绑定*/
	DECLARE_WAITQUEUE(name, current);	/*定义一个等待队列元素,并与当前进程绑定*/

4)添加/移除等待队列元素到/从等待队列头部

	void add/remove_wait_queue(wait_queue_head_t *q, wait_queue_t *wait);
	/*
	para1:等待队列头部;	para2:等待队列元素
	*/

5)等待事件(事件没发生就一直阻塞)

	wait_event(queue, condition);	/*condition满足时,queue代表的等待队列头部中的队列被唤醒(进程唤醒了与否????)*/
	wait_event_interruptible(queue, condition);		/*可以被中断信号打断*/
	wait_event_timeout(queue, condition, timeout);	/*timeout:阻塞等待的超时时间(以jiffy为单位)*/
	wait_event_interruptible_timeout(queue, condition, timeout);	/*结合中断、超时*/

6)唤醒队列

	void wake_up(wait_queue_head_t *queue);	/*唤醒以queue为等待队列头部中的与等待队列元素绑定的所有进程*/
	void wake_up_interruptible(wait_queue_head_t *queue);

7)在等待队列上睡眠

	sleep_on(wait_queue_head_t *queue);		/*queue为等待队列头部中的与等待队列元素绑定的所有进程睡眠,
	并且处于TASK_UNINTERRUPTIBLE*/
	interruptible_sleep_on(wait_queue_head_t *queue);

**实例:**

	ssizt_t xxx_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
	{
		...
		DECLARE_WAITQUEUE(wait, current);	/*定义一个等待队列元素,并与当前进程绑定*/
		add_wait_queue(&xxx_wait, &wait);	/*添加wait到等待队列头部xxx_wait*/

		/*等待设备缓冲可写*/
		do {
			avail = device_writable(...);	/*是否可写*/
			if(availe < 0) {	/*不可写*/
				if(filp->f_flags & O_NONBLOCK) { /*非阻塞*/
					ret = -EAGAIN;
					goto out;
				}
				__set_current_state(TASK_INTERRUPTIBLE);	/*改变进程状态:TASK_INTERRUPTIBLE*/
				schedule();			/*调度其他进程执行*/ /*当队列被唤醒时,可以调度到该进程*/
				if(signal_pending(current)){ /*signal_pending:检测当前队列的唤醒是否为信号唤醒,如果是返回非0.否则返回0.*/
					ret = -ERESTARTSYS;	/*重启系统*/
					goto out;
				}
			}
		}while(avail < 0);	/*不可写一直循环*/

		/*可写设备了,写设备*/
		device_write(...);
	out:
	remove_wait_queue(&xxx_wait, &wait);	/*将wait元素移除xxx_wait等待队列头部*/
	set_current_state(TASK_RUNNING);		/*设置进程状态为:TASK_RUNNING*/
	return ret;
	}

### 8.2 轮询操作

参见:select/poll操作

***
## 第十一章 内存与I/O访问

### Cache & DMA

**Cache原理:**

Cache:CPU缓存,位于CPU与内存之间的临时存储器.容量比内存小得多但交换速度比内存快得多.通常cache与主存在一定范围内保持适当的比例关系,cache的命中率90%以上(一般比例为4:1000)e.g. 128KB cache映射32MB内存;256KB可映射64MB内存.

**cache一致性问题:**

CPU需要操作的数据和结果优先从cache中拿或者写回到cache.

1)外设对内存数据的修改不能保证cache同样得到更新;

2)处理器对cache中内容的修改不能保证内存中的数据得到更新.

cache一致性问题最终解释为:cache中数据与内存中数据需要是一致的.

处理cache与DRAM存取一致性方法:

	贯穿读出式(Look Through):CPU首先请求cache，如果命中，切断主存请求;不命中,请求DRAM.
	旁路读出式(Look Aside):CPU同时请求cache和DRAM，cache速度快，如果命中cache将数据送给CPU的同时切断CPU对DRAM的请求;
	否则cache不做任何动作，CPU访问DRAM.
	写穿式(Write Through):CPU写到cache的同时也写入DRAM.
	回写式(Copy Back):一般只写到cache,当cache中的数据得到更新而DRAM中数据不变,cache中会设置一个标记.当cache中的数据再
	一次准备更新前会将cache中的数据写入DRAM中，进而才更新.

**DMA原理:**

DMA:无需CPU参与,让外设与内存直接进行双向数据传输的硬件机制.是一种内存与外设之间进行数据传输的方式.

**Cache与DMA的一致性问题**

1)外设数据到CPU:DMA将外设数据传到DRAM，cache中保留的仍是旧数据,CPU从cache中拿到错误的数据.
	
	解决:CPU在读取cache中的数据之前,先进行cache_invalidate作用,保证从DRAM读取数据到cache再到CPU.

2)CPU数据到外设:CPU处理的数据结果存放到cache，此时cache中的数据还没写回到DRAM;DMA从DRAM中取数据送到外设取到的为错误的数据.

	解决:DMA处理之前先进行cache_flush(刷新数据到DRAM),保证DMA取到的数据为最新的数据.
