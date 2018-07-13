# Deep understanding of Uboot

## Chapter 1 The use and burning of Uboot

### 1.1 环境搭建

一般的开发使用tftp和nfs利用网络进行数据传输.tftp主要用于数据传输,nfs用于挂载跟文件系统.

#### 1.1.1 tftp配置

tftp配置[参考](http://blog.csdn.net/zqixiao_09/article/details/50319877)

tftp分为两种模式:1.交互模式(手动);2.自动模式.

**1.交互模式(手动)**

在Uboot界面输入如下命令:

	tftp 41000000 uImage	/*将tftp主机端的uImage拷贝到芯片内存地址的0x41000000处*/
	tftp 42000000 exynos4412-fs4412.dtb	/*将tftp主机端的dtb文件拷贝到地址0x42000000处*/
	bootm 41000000 - 42000000	/*从0x41000000地址处开始运行*/

**2.自动模式**

设置bootcmd,Uboot在加载成功后,会执行bootcmd命令,自动下载文件并引导内核.

	setenv bootcmd tftp 41000000 uImage \;tftp 42000000 exynos4412-fs4412.dtb \; 
	bootm 41000000 - 42000000	/*和上面在一行.bootcmd如果是多条命令使用"\"分隔.*/
	saveenv

#### 1.1.2 通过NFS挂载根文件系统

NFS服务器的[搭建](http://blog.csdn.net/zqixiao_09/article/details/50337933)

**1.配置NFS**

	1.下载
		sudo apt-get install nfs-kernel-server
	2.配置
		sudo vi /etc/exports	/*打开exports这个文件*/
		在该文件的最后添加nfs共享目录nfsboot:
		/nfsboot *(rw, sync, no_subtree_check)	/*需要确保nfsboot目录存在,且权限是777(包括普通用户).*/
		PS:其他的共享目录设置格式:
		/share_dir *(rw, insecure, sync, no_wdelay, no_subtree_check, insecure_locks,
		no_root_squash)
	3.重启nfs服务
		sudo /etc/init.d/nfs-kernel-server restart
	4.测试方法
		1.直接显示挂载的list
			showmount -e
		结果类似如下:
			/nfsboot *
		2.自己手动挂载
			mount -t nfs 127.0.0.1:/nfsboot /mnt/xxx 	//将nfsboot挂载到/mnt/xxx目录下

**2.拷贝/解压根文件系统**

	cp xxx/rootfs.tar.xz /nfsboot	//拷贝根文件系统到/nfsboot
	cd /nfsboot
	tar xvf rootfs.tar.xz //解压rootfs

**3.设置开发板bootargs**

	setenv bootargs root=/dev/nfs nfsroot=(虚拟机)ip_addr:/nfsboot/rootfs rw console=ttySAC2,115200
		ip=板子ip_addr init=/linuxrc
	saveenv
	PS:
		root=/dev/nfs表示根文件系统在/dev/nfs上;
		nfsroot=ip_addr:/nfsboot/rootfs表示根文件系统所在位置;
		init=/linuxrc表示开机后启动的第一个进程.

### 1.2 常用Uboot命令

进入Uboot命令行:

	在启动时不停的敲Enter,在出现"Hit any key to stop autoboot:  1 "即会进入uboot命令行:
	Hit any key to stop autoboot:  1 	//输入"Enter"
	=>	//出现这种即进入uboot命令行

#### 1.2.1 环境设置命令

**1.查看当前环境变量**

	printenv	//会显示当前所有的环境变量

**2.增加/修改环境变量**

	setenv
	setenv ipaddr 192.168.1.1 ===>设置ip_addr为192.168.1.1

**3.删除环境变量**

	setenv 变量名	//相当于设置变量名为空

**4.常用环境变量的作用**

	ipaddr:开发平台ip(e.g.虚拟机);
	serverip:tftp服务器ip;
	netmask:子网掩码;
	gatewayip:网关;
	bootcmd:启动内核变量(自动启动时执行的命令);
	bootargs:传递给内核的参数(到内核阶段,原环境变量已经不起作用了);
	bootdelay:设置交互延时.

#### 1.2.2 数据传输命令

**1.tftp网络**

	tftp addr file_name	//利用tftp协议传输文件

**2.串口**

	loadb addr	/*利用kermit协议传输文件*/

#### 1.2.3 存储访问命令

**1.内存**

	1.md:显示内存的内容
		md a0000000 //显示地址0x41000000的内容
	2.mm:修改内存值
		mm a0000000
		//会产生如下的情况:
		a0000000 ? 12345678	//输入想修改成的值为"12345678"
		a0000004 ? 12345678	//输入想修改成的值为"12345678"
		//在md查看下修改的情况
		md a0000000 //会显示得到内存已经被修改了
	3.mw:使用指定的数据批量填充内存
		mw a0000000 12345678 10	//从0x41000000地址开始连续0x10个地址写入0x12345678

**2.flash(nand,emmc等外存)**

	1.nand
		nand write 20008000 0 40000 //写nandflash,在0x20008000,offset为0的位置写0x40000大小.
									//后续会需要填写要写入的数据
		nand read 20008000 0 4000 	读nandflash,在0x20008000,offset为0的位置读0x40000大小.
		nand erase 0 40000 //擦除offset为0,大小为0x40000的nandflash的数据.
	2.emmc
		movi write kernel 41000000	//将内存0x41000000的数据写入到emmc的kernel分区
		movi read kernel 41000000	//将emmc的kernel分区中的内容载入到内存0x41000000地址

#### 1.2.4 运行

**1.bootm**

bootm指令是专门用于启动在SDRAM中用Uboot的mkimage工具处理过的内存映像(将pc指针指向内存地址)

**2.go addr**

将pc指针指向内存地址addr.

**3.boot**

重启板子.

#### 1.2.5 其他

**1.fdt print**

打印出dts信息.

	=> fdt print
	/ {
	        #address-cells = <0x00000001>;
	        #size-cells = <0x00000001>;
	        model = "xxxx xxxx";
	        compatible = "xxxx xxxxx";
	        interrupt-parent = <0x00000001>;
	        soc {
	                #address-cells = <0x00000001>;
	                #size-cells = <0x00000001>;
	                device_type = "soc";
	                interrupt-parent = <0x00000002>;
	                compatible = "simple-bus";
	                ranges;

**2.run**

run:运行指定环境变量的内容.

**3.help**

help:查看所有的命令.

### 1.3 下载/烧写略.

***

## Chapter 2 Analysis of Uboot compilation process

### 2.1 Uboot编译方法

在Uboot顶层的README中有说明:

	Selection of Processor Architecture and Board Type:
	---------------------------------------------------
	
	For all supported boards there are ready-to-use default
	configurations available; just type "make <board_name>_defconfig".
	
	Example: For a TQM823L module type:
	
	        cd u-boot
	        make TQM823L_defconfig

**1.编译方法**

	根据说明,执行"make xxx_defconfig"进行配置,然后"make all"即可."xxx_defconfig"位于
		./configs/xxx_defconfig

**2.产生的文件**

	1.u-boot.bin:二进制可执行文件,是最终烧入eMMC中的文件;
	2.u-boot:ELF格式的可执行文件;
	3.u-boot.srec:摩托罗拉式的可执行文件.

### 2.2 Uboot配置,编译过程

#### 2.2.1 configs/xxx_defconfig文件解析

**1.README说明**

根据README中的说明:

	Define this in order to add variables describing the
	U-Boot build configuration to the default environment.
	These will be named arch, cpu, board, vendor, and soc.
	
	Enabling this option will cause the following to be defined:
	
	- CONFIG_SYS_ARCH
	- CONFIG_SYS_CPU
	- CONFIG_SYS_BOARD
	- CONFIG_SYS_VENDOR
	- CONFIG_SYS_SOC

	/*
		定义上述几个信息,Makefile中的arch, cpu, board, vendor, soc会得到赋值.
	*/

**2.xxx_defconfig中的定义**

	CONFIG_SYS_ARCH="arm"
	CONFIG_SYS_CPU="armv7"
	CONFIG_SYS_BOARD="xxx"
	CONFIG_SYS_VENDOR="xxx"
	CONFIG_SYS_SOC="demo-board"
	
	/*
	在这里定义之后,在顶层的Makefile的:
		export ARCH CPU BOARD VENDOR SOC CPUDIR BOARDDIR
		此处的变量ARCH, CPU, BOARD,VENDOR,SOC可以拿到对应的值.
	*/
	
#### 2.2.2 arch/arm下的Makefile解析

	head-y := arch/arm/cpu/$(CPU)/start.o //表示编译$(CPU)下的start.S.此处$(CPU)为armv7.
	...
	libs-y += arch/arm/cpu/$(CPU)/	//表示编译$(CPU)下的Makefile指定的文件.此处为$(CPU)为armv7.

#### 2.2.3 Uboot的driver的Makefile解析

	libs-y += lib/
	libs-$(HAVE_VENDOR_COMMON_LIB) += board/$(VENDOR)/common/
	ifneq ($(CONFIG_ALISTARTER_AUTOBOOT_APP),y)
	        libs-y += board/ali/ali_ci/
	endif
	libs-$(CONFIG_OF_EMBED) += dts/
	libs-y += fs/
	libs-y += net/
	libs-y += disk/
	libs-y += drivers/	//表示编译drivers下的Mafile指定的文件.
	libs-y += drivers/dma/
	libs-y += drivers/gpio/
	libs-y += drivers/i2c/
	libs-y += drivers/mmc/
	libs-y += drivers/mtd/

### 2.3 Uboot编译链接流程

链接脚本位于:

	./arch/arm/cpu/u-boot.lds

**链接流程**

	1.首先编译arch/arm/cpu/$(CPU)/start.S,不同的CPU,可能需要编译cpu/$(CPU)下的其他文件;
	2.然后根据顶层Makefile进入到fs/net/disk/drivers...等其他目录进行编译;
	3.代码段起始地址的指定(按README中的说明):
		- CONFIG_SYS_FLASH_BASE:
				Physical start address of Flash memory.
	
		- CONFIG_SYS_MONITOR_BASE:
				Physical start address of boot monitor code(set by
				make config files to be same as the text base address
				(CONFIG_SYS_TEXT_BASE) used when linking) - same as
				CONFIG_SYS_FLASH_BASE when booting from flash.
		/*
			说明设置"CONFIG_SYS_TEXT_BASE"宏的值就是链接的地址.
		*/
	4.链接:调用u-boot.lds链接脚本进行链接.
	5.将链接后的elf格式的u-boot,转成二进制形式的u-boot.bin.

***

## Chapter 3 Analysis of Uboot compilation process