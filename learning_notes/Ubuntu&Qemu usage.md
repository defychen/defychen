# Ubuntu & Qemu usage

# Chapter 1. Ubuntu 18.04工具安装

## 1.1 vim软件的安装

	sudo apt-get install vim
	echo $?		//返回0表示软件安装成功;非0表示出现了问题.

## 1.2 检查软件更新情况并将软件进行更新

	1.sudo apt-get update
	/*
		更新/etc/apt/sources.list和/etc/apt/sources.list.d中列出的源的地址.这样才能获取到最新的
		软件包.
	*/
	2.sudo apt-get upgrade
	/*
		升级已安装的所有软件包,将本地的软件版本与update文件更新的版本进行对比从而进行相关升级.因此,
		执行upgrade之前一定要执行update,这样才能保证更新到最新.
	*/

## 1.3 "net-tools"安装

**1.问题**

刚安装的linux可能在执行"ifconfig"时,没有这个命令.报如下的错误:

	Comand "ifconfig" not found, but can be installed with:
		apt install net-tools
	PS:即没有ifconfig命令.

**2.解决**

	apt install net-tools

## 1.4 git安装

	sudo apt-get install git

注意点:
	1.查看git的版本:
	git --version
	2.sudo apt-get下载的文件的目录:
		/var/cache/apt/archives		//但是使用"sudo apt-get install git"没有发现文件
	3.文件下载的目录可以在"/etc/apt/source.list"中指定  --->还没有发现真正的用途

## 1.5 gcc安装及版本切换

### 1.5.1 自动下载安装gcc

	sudo apt-get install gcc-arm-linux-gnueabi
	/*
		一般会下载最新版本gnu交叉编译工具,最新版本gnu对Linux也是有版本支持的.
		本人安装的18.04版本的ubuntu自动下载的的gcc版本为"version 7.4.0",不支持3.16版本的linux
		(会出现很多error),需要使用4.x版本的linux.
	*/
	sudo apt-get install g++-arm-linux-gnueabi	//安装g++

### 1.5.2 手动安装gcc及版本切换

主要针对需要不同版本的gcc,可以切换gcc版本.

**1.gcc下载地址**

[arm-linux-gcc历史版本下载地址](https://releases.linaro.org/components/toolchain/binaries/)

	Linaro的官网(https://www.linaro.org/downloads/)--->拉到下面的"Linaro Toolchain"--->
		点击"GNU cross-toolchain binary archives"--->弹出页面中可以选择历史版本.

**2.版本切换方法**

	//Ubuntu 18.04.2 LTS默认会使用gcc version 7.3.0.如果要切换为4.9.4的版本
	1.下载4.9.4的gcc版本
		网址"https://releases.linaro.org/components/toolchain/binaries/"--->选择"4.9-2017.01"
		--->选择"arm-linux-gnueabi"--->选择"gcc-linaro-4.9.4-2017.01-i686_arm-linux-
			gnueabi.tar.xz"
	2.解压
		tar -xvJf gcc-linaro-4.9.4-2017.01-i686_arm-linux-gnueabi.tar.xz
		mv gcc-linaro-4.9.4-2017.01-i686_arm-linux-gnueabi arm-linux-gcc arm-linux-gcc
		mv arm-linux-gcc /home/defychen/
		PS:gcc的编译器在目录"/home/defychen/arm-linux-gcc/bin/"
	3.修改.bashrc/profile
		1.仅在当前目录下有效方法:
			1.打开/root/.bashrc(root用户)和/home/defychen/.bashrc(普通用户)文件,增加下面信息:
				export PATH=/home/defychen/arm-linux-gcc/bin:$PATH
				//放在PATH环境变量的前面,可以保证肯定有效;放在后面如果PATH变量中有gcc版本,则后面的不会用
			2.让路径生效
				source /root/.bashrc
				source /home/defychen/.bashrc
		2.开机就有效(一直有效)方法:
			在/etc/profile中写入:
				export PATH=/home/defychen/arm-linux-gcc/bin:$PATH
				source /etc/profile	//如果开机,会先扫描该文件.并使能该路径

**3.gcc版本查看**

终端输入:

	arm-linux-gnueabi-gcc -v
	arm-linux-gnueabi-gcc --version

**4.g++编译实例---gcc类似的**

1.源文件hello.cpp

	#include <iostream>
	using namespace std;
	
	int main(int argc, char *argv[])
	{
		cout << "hello world" << endl;
		return 0;
	}

2.编译

	1.编译出可执行程序
		g++ hello.cpp -o hello
	2.编译出带调试信息的可执行程序	
		g++ -g hello.cpp -o hello.debug		//执行./hello.debug即可
	3.仅编译,不链接(编译出目标文件.o)
		g++ -c hello.cpp hello.o
	4.编译出动态链接库(也叫共享库文件,即.so)--->由.o编译成.so
		g++ -shared -fPCI -o hello.so hello.o
	5.编译出静态库(即.a)--->由.o压缩成.a
		ar -r hello.a hello.o

## 1.6 ubuntu版本查看

	1.cat /proc/version		//可以显示当前Linux的版本及gcc的版本信息
	2.uname -a				//也会显示当前Linux的版本,还有当前用户名
	3.lsb_release -a			//会显示当前Ubuntu版本"Ubuntu 18.04.2 LTS"

## 1.7 rar/unrar工具的安装

如果需要解压的包为.rar格式,则需要使用unrar命令:

	sudo apt-get install rar unrar

rar/unrar命令的使用:

	1.rar创建一个*.rar包:
	rar a test.rar test.jpg test.png	//将test.jpg和test.png压缩成一个rar包
	2.unrar解压一个*.rar包:
	unrar e test.rar	//解压在当前目录
	unrar x test.rar test	//解压到test目录下
	3.rar和unrar的使用帮助:
	rar -?
	unrar -?

## 1.8 wine的安装及使用

### 1.8.1 安装wine

	apt-get install wine64	//安装64-bit的wine.一般还需要安装wine32
	dpkt --add-architecture i386 	//添加i386体系结构
	apt-get upgrade	//更新包
	apt-get install wine32

### 1.8.2 使用wine

	wine *.exe

## 1.9 python的安装

### 1.9.1 python的安装

**1.安装python2.x**

	apt install python		//安装python2
	启动方法: python

**2.安装python3.x**

	apt install python3		//安装python3
	启动方法: python3

### 1.9.2 python的pip工具的安装

	apt install python-pip

## 1.10 linux源码下载地址

[国内下载地址](http://ftp.sjtu.edu.cn/sites/ftp.kernel.org/pub/linux/kernel/)

	国内下载地址速度快很多.

[官网地址](https://www.kernel.org/pub/linux/kernel/)

	官网下载很慢.

## 1.11 更改软件源

ubuntu经常会需要执行更新操作,使用官方的软件源更新会很慢.因此需要更改软件源为国内,这样更新会快很多.

	打开/etc/apt/sources.list文件,在该文件开头添加以下内容:
	#东北大学：
	deb-src http://mirror.neu.edu.cn/ubuntu/ xenial main restricted #Added by software-
		properties
	deb http://mirror.neu.edu.cn/ubuntu/ xenial main restricted
	deb-src http://mirror.neu.edu.cn/ubuntu/ xenial restricted multiverse universe #Added by
		 software-properties
	deb http://mirror.neu.edu.cn/ubuntu/ xenial-updates main restricted
	deb-src http://mirror.neu.edu.cn/ubuntu/ xenial-updates main restricted multiverse 
		universe #Added by software-properties
	deb http://mirror.neu.edu.cn/ubuntu/ xenial universe
	deb http://mirror.neu.edu.cn/ubuntu/ xenial-updates universe
	deb http://mirror.neu.edu.cn/ubuntu/ xenial multiverse
	deb http://mirror.neu.edu.cn/ubuntu/ xenial-updates multiverse
	deb http://mirror.neu.edu.cn/ubuntu/ xenial-backports main restricted universe multiverse
	deb-src http://mirror.neu.edu.cn/ubuntu/ xenial-backports main restricted universe
		multiverse #Added by software-properties
	deb http://archive.canonical.com/ubuntu xenial partner
	deb-src http://archive.canonical.com/ubuntu xenial partner
	deb http://mirror.neu.edu.cn/ubuntu/ xenial-security main restricted
	deb-src http://mirror.neu.edu.cn/ubuntu/ xenial-security main restricted multiverse 
		universe #Added by software-properties
	deb http://mirror.neu.edu.cn/ubuntu/ xenial-security universe
	deb http://mirror.neu.edu.cn/ubuntu/ xenial-security multiverse
	#清华大学
	# deb cdrom:[Ubuntu 16.04 LTS _Xenial Xerus_ - Release amd64 (20160420.1)]/ xenial main 
		restricted
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial main restricted
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-updates main restricted
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial universe
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-updates universe
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial multiverse
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-updates multiverse
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-backports main restricted universe 
		multiverse
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-security main restricted
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-security universe
	deb http://mirrors.tuna.tsinghua.edu.cn/ubuntu/ xenial-security multiverse
	#阿里云
	# deb cdrom:[Ubuntu 16.04 LTS _Xenial Xerus_ - Release amd64 (20160420.1)]/ xenial main
		restricted
	deb-src http://archive.ubuntu.com/ubuntu xenial main restricted #Added by software-
		properties
	deb http://mirrors.aliyun.com/ubuntu/ xenial main restricted
	deb-src http://mirrors.aliyun.com/ubuntu/ xenial main restricted multiverse
		universe #Added by software-properties
	deb http://mirrors.aliyun.com/ubuntu/ xenial-updates main restricted
	deb-src http://mirrors.aliyun.com/ubuntu/ xenial-updates main restricted multiverse
		universe #Added by software-properties
	deb http://mirrors.aliyun.com/ubuntu/ xenial universe
	deb http://mirrors.aliyun.com/ubuntu/ xenial-updates universe
	deb http://mirrors.aliyun.com/ubuntu/ xenial multiverse
	deb http://mirrors.aliyun.com/ubuntu/ xenial-updates multiverse
	deb http://mirrors.aliyun.com/ubuntu/ xenial-backports main restricted universe
		multiverse
	deb-src http://mirrors.aliyun.com/ubuntu/ xenial-backports main restricted
		universe multiverse #Added by software-properties
	deb http://archive.canonical.com/ubuntu xenial partner
	deb-src http://archive.canonical.com/ubuntu xenial partner
	deb http://mirrors.aliyun.com/ubuntu/ xenial-security main restricted
	deb-src http://mirrors.aliyun.com/ubuntu/ xenial-security main restricted multiverse 
		universe #Added by software-properties
	deb http://mirrors.aliyun.com/ubuntu/ xenial-security universe
	deb http://mirrors.aliyun.com/ubuntu/ xenial-security multiverse

/etc/apt/sources.list表示apt install时,ubuntu会从这些站点下载软件包到本地并进行安装.

## 1.12 安装u-boot-tools

uboot-tools是将Image转成u-boot可以引导的镜像文件格式.

安装方法:

	apt install u-boot-tools

## 1.13 安装tree

tree用于查看目录结构,默认是不安装的.

	apt install tree

***

# Chapter 2. Ubuntu 18.04问题方法

## 2.1 忘记root密码解决办法

**方法 1**

如果用户具有sudo权限:

	1.sudo su root	//通过sudo直接切换到root用户
	2.passwd		//重新更改root密码
	/*
		提示:输入新的UNIX密码->重新输入新的UNIX密码->更改root密码成功.
	*/

**方法 2**

用户不具备sudo权限,需要进入GRUB修改kernel镜像启动参数,此处暂时略.

## 2.2 root用户和普通用户的切换

1.切换到root用户

	1.su root	//切换到root用户,输入root用户密码即可.仍然停在当前目录
	2.su -		//切换到root用户,输入root用户密码即可.同时切换到当前用户的home目录.

2.切换到普通用户

	su defychen		//切换到defychen用户(defychen为普通用户名).

## 2.3 关于Ubuntu中出现"Could not get lock /var/lib/dpkg/lock"解决方案

**1.问题**

1.当执行"apt install python-pip(安装python的pip程序,以便可以pip install xxx)"时出错:

2.当执行"apt-get install gcc-arm-linux-gnueabi":下载并安装包时出错:

	E: Could not get lock /var/lib/dpkg/lock - open (11: Resource temporarily unavailable)
	E: Unable to lock the administration directory (/var/lib/dpkg/), is another process
	using it?

**2.原因**

简单描述为:apt还在运行,/var/lib/apt/lists、/var/lib/dpkg、/var/cache/archives会被锁定.导致其他apt操作不会成功.

	出现这个问题可能是有另一个程序正在运行,导致资源被锁不可用.而导致资源被锁的原因可能是上次运行安装或
	更新时没有正常完成,进而出现此状况.

**3.解决办法**

1.查找所有apt相关进程,并杀死:

	1.查找apt相关进程
	ps afx | grep apt
	 3284 pts/0    S+     0:00          \_ grep --color=auto apt
		//该进程自带,不能被kill.后面两个进程需要kill掉.
	 2869 ?        Ss     0:00 /bin/sh /usr/lib/apt/apt.systemd.daily install
	 2873 ?        S      0:00  \_ /bin/sh /usr/lib/apt/apt.systemd.daily lock_is_held install
	2.杀掉apt相关进程
		kill -9 2873
		kill -9 2869

2.删掉锁定的文件:

	1.删除对应目录下的锁文件:
		rm -rf /var/lib/dpkg/lock
	2.强制重新配置软件包:
		dpkg --configure -a
	3.更新软件包源文件
		apt update

**4.重新安装包文件即可**

	1.再次执行"apt install python-pip"	//如果安装python pip
	2.执行"apt-get install gcc-arm-linux-gnueabi"	//安装交叉编译工具链

## 2.4 Ubuntu 18.04无法连接到WiFi的解决方案

Ubuntu18.04安装后可能会出现找不到Wifi,不能连接到Wifi.

### 2.4.1 插入网线,使用DSL宽带拨号上网

因为需要联网下载一些东西:

**1.创建一个连接点**

	1.点击桌面左边的"文件"菜单(一个图标),打开一个类似Windows资源管理器的东西;
	2.选择"其他位置",出现"计算机",依次点选"计算机"->usr->share->applications->
		选择"Network Connections",弹出"网络连接窗口";
	3.点击"以太网"->点击左下角的"+",增加一个以太网连接,出现的选择连接类型:选择"DSL/PPPoE",点击创建.
		弹出一个"编辑DSL连接"的窗口;
	4.在"DSL/PPPoE"页面中填写以下设置:
		Parent interface:选择网卡"enp3s0"--->Ubuntu 18.04网卡变成了enp3s0
		PPP界面:不填写
		用户名:输入网络的账户(e.g.1001)
		服务:不填写
		密码:输入网路的密码(e.g.21004)		
	  在"常规"页面中勾选前两个选项:
		1.勾选"可用时自动链接到这个网络";
		2.勾选"所有用户都可以连接到这个网络"
	5.点击保存即可.

**2.连接到网络**

第一步设置好之后右上角就会出现"有线连接"的标识,但是带一个问号.

	打开ubuntu的设置->选择"网络":
		在"有线连接"下面会显示"已连接-100Mb/秒",点击该行右边的"设置"选项->在弹出的"有线"窗口中->
		在详细信息页面中去掉"自动连接"选项->点击应用.
		在"蓝牙"下面的"PPP"变得打开.此时也会自动连上宽带.

### 2.4.2 更改软件源

	点击桌面左下角的"显示应用程序"->选择"软件和更新"->在"Ubuntu软件"的页面中更改"下载自"的站点为合适的
	站点(本人选择"其他站点"->中国->mirros.huaweicloud.com)->系统可能会自动更新索引,让其更新即可.

### 2.4.3 添加附加驱动

	同样在"软件和更新"里->切换到"附加驱动"选项卡->据说能搜到对应的无线网卡(我的没有,只有网卡驱动会
	在一段时间之后出现,没有也没关系,该步跳过即可).
	PS:需要注意BIOS是否位于UEFI且开启了secure boot,必须把secure boot关掉,因为专用驱动是闭源的.而
	ubuntu是开源的,开源组织认为"闭源系统是不安全的",所以闭源的软件在开启secure boot的时候是不能启用的.
	--->acer笔记本关闭secure boot方法:
		1.F2进入到BIOS;
		2.切换到"Security",然后按"↓"箭头,选择"Set Supervisor Password",设置管理员密码(也是超级用户
		密码),该密码今后在进入BIOS时需要输入.我设置了acer的密码为"123456";
		3.然后切换到"Boot",按键盘的按"↓"箭头选择Secure Boot,回车在弹出的界面中点击Disabled;
			--->但是我的acer电脑没有secure boot这个选项...
		4.保存退出.
		PS:我没有设置成功secure boot也没有关系.可以跳过该步. 

### 2.4.4 安装bcmwl-kernel-source

2.4.3步可能执行不成功.在终端(调出终端窗口快捷键:Ctrl+Alt+T)执行下面的命令:

	sudo apt-get update
	sudo apt-get install bcmwl-kernel-source
	/*
	用于安装无线网卡驱动,网卡属于Broadcom,查看所有的pci设备(包括无线网卡):
		lspci	//显示pci设备
		如果出现"Ethernet Controller:: Broadcom Limited Netlink BCM57780 Gigabit Ethernet PCIe
			...",即表示网卡属于Broadcom.
	即属于Broadcom的网卡可用该方法安装驱动.
	*/

这步执行完成后,可能等很长时间就有了Wifi标识.

### 2.4.5 在/etc/modprobe.d/blacklist.con加入命令(我加入了,但是后面又注释掉了)

	1.打开blacklist.conf
		sudo vim /etc/modprobe.d/blacklist.conf
	2.在最后一行加入下面的命令
		blacklist acer-wmi	//加上之后,我后面又注视掉才成功.
	
PS:总结起来,"2.4.4"步最重要.执行完等5-6分钟应该就有Wifi标识了.

## 2.5 Ubuntu 16.04小技巧

1.打开终端操作

	1.打开一个终端
		Ctrl+Alt+T
	2.在一个终端的基础上重新增加一个终端(两个终端并排排列)
		Ctrl+Shift+T
	3.切换终端
		Alt+1	//切换到1终端
		Alt+2	//切换到2终端

2.设置屏幕不息屏

	/* 1.ubuntu 16.04设置方法 */
	点击左上角的设置图标--->选择"System Settings"--->点击"Brightness & Lock"--->在"Turn screen off
		when inactive for":选择"Never"(表示从不息屏)
	/* 2.ubuntu 19.04设置方法 */
	右键--->Settings--->选择"Privacy"--->点击"Screen Lock",将On切换为Off即可.

3.隐藏左侧的菜单项

	/* 1.ubuntu 16.04设置方法 */
	点击左上角的设置图标--->选择"Appearance"--->切换到"Behavior"页--->在"Auto-hide the Launcher"
		选择打开(即ON)即可--->此时左侧的菜单项就会隐藏
	PS:显示左侧菜单项方法:按下"win"键即可显示.
	/* 2.ubuntu 19.04设置方法 */
	右键--->Change Backgound--->Dock--->将"Auto-hide the Dock"打开即可.

***

# 3. Qemu usage

Qemu是纯软件实现的虚拟化模拟器,几乎可以模拟任何硬件设备(e.g.Qemu模拟出一台能够独立运行操作系统的虚拟机,虚拟机认为自己在和硬件打交道,但其实是和Qemu模拟出来的硬件打交道,Qemu再将这些指令转译给真正的硬件).

	因为Qemu是纯软件实现的,所有的指令都要经过Qemu,性能非常低.所以,在实际中大多数的做法是配合KVM来完成虚
	拟化工作.因为KVM是硬件辅助的虚拟化技术,主要负责比较繁琐的CPU和内存虚拟化,而Qemu则负责I/O虚拟化,两者
	合作各自发挥优势,相得益彰.

## 3.1 在Ubuntu系统搭建Qemu模拟ARM(一)--->只运行内核和根文件系统

环境:

	Ubuntu:Ubuntu 18.04.2 LTS
	Qemu上运行的内核:Linux 4.8
	Qemu:2.8
	目标系统:以Versatile Express-A9开发板搭建环境

### 3.1.1 Qemu的下载、编译、安装

**1.下载Qemu**

[qemu 2.8下载地址](http://download.qemu-project.org/qemu-2.8.0.tar.xz)

	下载下来的文件为:qemu-2.8.0.tar.xz
	ubuntu下载方法:
		wget http://download.qemu-project.org/qemu-2.8.0.tar.xz

**2.下载并安装Qemu安装时所需要的工具软件包**

	sudo apt-get install zlib1g-dev
	sudo apt-get install libglib2.0-dev
	sudo apt-get install autoconf automake libtool
	sudo apt-get install libsdl1.2-dev
	PS:网上资料说2.7还需要安装下面的包(2.8我安装Qemu时并不需要下面的包),作为一个参考:
	sudo apt-get install libglib2.0-0	//感觉不需要,有了"libglib2.0-dev"
	sudo apt-get install flex bison		//没试过

**3.解压Qemu源码包**

	//Ubuntu 18.04下载的Qemu会放在/home/defychen/Downloads/qemu-2.8.0.tar.xz
	cp qemu-2.8.0.tar.xz /root/
	cd /root
	tar -xvJf qemu-2.8.0.tar.xz		//使用-xvJf解压"tar.xz"文件
	cd qemu-2.8.0

**4.配置、编译、安装**

全部操作均在qemu目录下完成(安装需要root权限,因此最好全部在root下操作):

	1.配置
		./configure --target-list=arm-softmmu --audio-drv-list=
		/*
			--audio-drv-list必须加,否则运行时会报告有关audio的错误:
			audio:Could not init `oss' audio driver --->我暂时没碰到
		*/
	2.编译
		make
		/*
		编译时,可能出现的问题:
		1."util/memfd.c:43:12:error: static declaration of ‘memfd_create’ follows non-staticdeclaration"
		--->解决办法:
			打开util/memfd.c,将memfd_create函数名重命名为:tmp_memfd_create即可.
		2."qga/commands-posix.c:634: undefined reference to `minor'"
		--->解决方法:
			打开qga/commands-posix.c,在commands.posix.c文件中加上头文件<sys/sysmacros.h>即可.
		*/
	3.安装
		make install	//会安装到系统的"/usr/local/bin/qemu-system-arm"的位置
	4.查看qemu版本
		qemu-img -V		//大写的"v",会显示"qemu-img version 2.8.0 xxx"
		qemu-system-arm --version
		/*
			只能用"--version,单纯的"-v"不支持.显示结果为:
			QEMU emulator version 2.8.0 xxx
		*/
	5.查看qemu支持的开发板
		qemu-system-arm -M help
		/*
			会显示支持的开发板,其中包括:
			vexpress-a15		ARM Versatile Express for Cortex-A15		//支持A15
			vexpress-a9		ARM Versatile Express for Cortex-A9		//支持A9--->支持最好的一个
		*/

### 3.1.2 linux内核编译(在Qemu上运行)

**1.下载并安装gnu交叉编译工具**

	sudo apt-get install gcc-arm-linux-gnueabi
	/*
		一般会下载最新版本gnu交叉编译工具,最新版本gnu对Linux也是有版本支持的.
		本人下载的的gcc版本为"version 7.3.0",不支持3.16版本的linux(会出现很多error),
		需要使用4.x版本的linux.
	*/

**2.内核下载**

可以参考前面"1.10 linux源码下载地址"地址进行下载:

	本人下载的地址为:http://ftp.sjtu.edu.cn/sites/ftp.kernel.org/pub/linux/kernel/v4.x/
	下载的版本为:linux-4.8.tar.gz		//因为最新的gnu交叉编译工具仅支持4.x之后的版本的

版本下载原则:

	1.首先到"https://www.kernel.org"查看当前linux版本信息,选择版本为"longterm"的作为下载项;
		e.g.longterm:	4.4.189		//表示linux社区依旧在维护该版本
	2.到"http://ftp.sjtu.edu.cn/sites/ftp.kernel.org/pub/linux/kernel/v4.x/"国内下载源去下载
		对应版本即可.

**3.解压、配置、编译**

	1.解压
		//Ubuntu 18.04下载的linux会放在/home/defychen/Downloads/linux-4.8.tar.gz
		cp /home/defychen/Downloads/linux-4.8.tar.gz /root/
		cd /root
		tar -xvzf linux-4.8.tar.gz
		cd linux-4.8
	2.配置
		1.配置交叉编译器
		export CROSS_COMPILE=arm-linux-gnueabi-
		export ARCH=arm
		/*
			如果一般用arm架构,且交叉编译器一般不变,可:
			进入linux源代码目录,修改顶层的Makefile(搜索CROSS_COMPILE):
				...
				# Note: Some architectures assign CROSS_COMPILE in their arch/*/Makefile
				ARCH			?= arm
				//默认的为:ARCH			?= $(SUBARCH)
				CROSS_COMPILE	?= arm-linux-gnueabi-
				//默认的为:CROSS_COMPILE	?= $(CONFIG_CROSS_COMPILE:"%"=%)
			PS:有时候修改了不行,只能用第一种export方法.
		*/
		2.配置编译参数
		make vexpress_defconfig
		/*
			1.linux支持的arm开发板信息查看目录为:./arch/arm/
				其中包括"mach-vexpress"--->为支持的vexpress-a9
			2.linux支持的arm开发板的所有的config文件目录为:./arch/arm/configs/
				其中包括"vexpress_defconfig",此处配置编译参数即选择该配置文件.

	3.编译
		make -j2 	//2线程编译(使用make zImage j2是一样的效果)
		/*
			1.image:
				编译好的image会在:./arch/arm/boot/zImage.
			2.dtb:
				编译好的dtb会在:./arch/arm/boot/dts/vexpress-v2p-ca9.dtb
				PS:./arch/arm/boot/dts/下存放了linux支持的各种arm开发板的dts文件
		*/
	4.编译内核模块--->可不执行
		make modules -j4
	5.编译dts--->可不执行(make -j2会将该步一起执行)
		make dtbs

### 3.1.3 根文件系统的制作

busybox:一个集成100多个linux常用命令和工具的软件,是一个特别适合制作嵌入式文件系统的软件工具.

**1.busybox的下载、解压**

[busybox下载地址](https://busybox.net/downloads/)

	方法1:打开上述网址选择"busybox-1.25.0.tar.bz2"进行下载
		//Ubuntu 18.04下载的busybox会放在/home/defychen/Downloads/busybox-1.25.0.tar.bz2
		cp /home/defychen/Downloads/busybox-1.25.0.tar.bz2 /root
		cd /root
		tar -xvjf busybox-1.25.0.tar.bz2
		cd busybox-1.25.0
	方法2:使用命令行下载
		wget https://www.busybox.net/downloads/busybox-1.25.0.tar.bz2 --no-check-certificate
		//没试过,不知道行不行??

**2.配置、编译**

	make defconfig 	//config文件在./configs/下面,但是defconfig没去看到底是哪一个config文件
	make CROSS_COMPILE=arm-linux-gnueabi-	//编译
	make CROSS_COMPILE=arm-linux-gnueabi- install	//安装
	/*
		生成的根文件系统位于:./busybox-1.25.0/_install/,有"bin/linuxrc/sbin/usr"等.
	*/

配置其他选项(执行make menuconfig)时可能会出现"fatal error: curses.h:没有那个文件或目录":

	原因:是因为ubuntu系统中缺少一个套间ncurses devel,将此套间安装即可.
	解决方法:
		apt-get install libncurses5-dev

**3.制作根目录**

1.创建必要的目录

	cd /root
	mkdir rootfs
	cd rootfs
	mkdir lib	//创建一个lib目录
	mkdir dev	//创建一个dev目录

2.拷贝busybox编译产生的目录和文件,以及编译器自带的lib文件

	cp /root/busybox-1.25.0/_install/* rootfs/ -r	//递归拷贝
	cp -P /usr/arm-linux-gnueabi/lib/* rootfs/lib/
	/*
		/usr/arm-linux-gnueabi/lib/下面放的是编译器自带的lib文件
	*/

3.创建/dev下面的相关节点

	cd rootfs/dev
	1.创建4个tty终端设备(串口节点)
		mknod tty1 c 4 1	//另一种:mknod -m 666 tty1 c 4 1--->效果是一样的.
		mknod tty2 c 4 2
		mknod tty3 c 4 3
		mknod tty4 c 4 4
	2.创建控制台节点
		mknod console c 5 1	//另一种:mknod -m 666 console c 5 1--->效果是一样的.
	3.创建null节点
		mknod null c 1 3	//另一种:mknod -m 666 null c 1 3--->效果是一样的.

4.生成32M大小的镜像,并拷贝文件系统树到镜像文件中

	cd /root
	1.生成一个a9rootfs.ext的镜像文件(32M大小)
		dd if=/dev/zero of=a9rootfs.ext3 bs=1M count=32
	2.格式化为ext3文件系统
		mkfs.ext3 a9rootfs.ext3
	3.创建挂载点,并进行挂载
		mkdir tmpfs
		mount -t ext3 a9rootfs.ext3 tmpfs/ -o loop	//将a9rootfs.ext3(ext3的文件系统)挂载到tmpfs下
	4.拷贝所需的文件系统到挂载点
		cp -r rootfs/* tmpfs/
	5.卸载
		sudo umount tmpfs	//卸载

5.运行起来之后会出现"Can't run '/etc/init.d/rcS': No such file or directory"

	解决方法:
	1.在rootfs下面创建/etc/init.d/rcS文件:
		cd rootfs
		mkdir etc/init.d -p	//创建多级目录
		cd etc/init.d/
		touch rcS
		chmod a+x rcS
		vim rcS
	2.在rcS文件中写入:
		echo "---------------------------------"
		echo "  Welcome to A9 vexpress borad   "
		echo "---------------------------------"
		PS:这些内容在最后即将进入终端时会显示出来.
	3.挂载a9rootfs.ext3(SD卡),将新的rcS文件拷贝进去
		mount -t ext3 a9rootfs.ext3 tmpfs/ -o loop
		cp ./rootfs/etc tmpfs/ -rf
		umount tmpfs	//卸载
	4.重启就不会再出现这个问题了.

### 3.1.4 运行虚拟机

**1.运行方法**

在终端输入:

	qemu-system-arm -M vexpress-a9 -m 512M -kernel /root/linux-4.8/arch/arm/boot/zImage
	-dtb /root/linux-4.8/arch/arm/boot/dts/vexpress-v2p-ca9.dtb -nographic -append
	"root=/dev/mmcblk0 console=ttyAMA0" -sd a9rootfs.ext3

	参数解析:
		-M:表示Machine;
		-m:表示memory.

也可写成一个脚本(qemu.sh):

	#!/usr/bin/sh
	qemu-system-arm -M vexpress-a9 -m 512M -kernel /root/linux-4.8/arch/arm/boot/zImage
	-dtb /root/linux-4.8/arch/arm/boot/dts/vexpress-v2p-ca9.dtb -nographic -append
	"root=/dev/mmcblk0 console=ttyAMA0" -sd a9rootfs.ext3

启动之后即可进入到终端(只运行内核和根文件系统),boot后续增加.

### 3.1.5 退出虚拟机

方法1--->这个方法可能不会奏效

	先按Ctrl+A,然后再按X.就会出现"QEMU: Terminated",退出qemu.

方法2--->这个方法肯定有效

	另外打开一个终端,执行:
		ps -a	//查看所有进程
		kill qemu的PID	//qemu的PID是qemu-system-arm进程的PID.

## 3.2 在Ubuntu系统搭建Qemu模拟ARM(二)--->u-boot启动kernel

### 3.2.1 Qemu启动u-boot的制作

**1.u-boot的下载、解压**

[u-boot下载地址](http://ftp.denx.de/pub/u-boot)

	方法1:打开上述网址选择"u-boot-2017.05.tar.bz2"进行下载
		//Ubuntu 18.04下载的u-boot会放在/home/defychen/Downloads/u-boot-2017.05.tar.bz2
		cp /home/defychen/Downloads/u-boot-2017.05.tar.bz2 /root
		cd /root
		tar -xvjf u-boot-2017.05.tar.bz2
		cd u-boot-2017.05
	方法2:使用命令行下载
		wget http://ftp.denx.de/pub/u-boot/u-boot-2017.05.tar.bz2 --no-check-certificate
		//试过,好像不行.需要再次确认.

**2.配置、编译**

	1.配置
		1.配置交叉编译器
		export CROSS_COMPILE=arm-linux-gnueabi-
		export ARCH=arm
		/*
			如果一般用arm架构,且交叉编译器一般不变,可:
			1.修改CROSS_COMPILE
			进入u-boot源代码目录,修改顶层的Makefile(搜索CROSS_COMPILE):
				...
				# set default to nothing for native builds
				ifeq ($(HOSTARCH),$(ARCH))
				CROSS_COMPILE	?= arm-linux-gnueabi-
				//默认的为:CROSS_COMPILE	?=
				endif
			2.修改ARCH
			进入u-boot源代码目录,修改顶层的config.mk(搜索ARCH):
				ARCH := arm
				//默认的为:ARCH := $(CONFIG_SYS_ARCH:"%"=%)
			PS:有时候修改了不行,只能用第一种export方法.
		*/
		2.配置编译参数
		make vexpress_ca9x4_defconfig
		/*
			u-boot支持的开发板的所有的config文件目录为:./configs/
				其中包括"vexpress_ca9x4_defconfig",此处配置编译参数即选择该配置文件.
		*/

	3.编译
		make -j4 	//4线程编译
		/*
			u-boot:
				编译好的u-boot会在:./u-boot.
		*/

**3.单独启动u-boot**

	#!/usr/bin/sh
	qemu-system-arm -M vexpress-a9 -m 512M -kernel /root/u-boot-2017.05/u-boot -nographic

**4.u-boot中的命令**

	在u-boot启动显示"Hit any key to stop autoboot"敲击Enter后,即可进入到u-boot命令行:
	1.	print ipaddr	//显示u-boot的ip地址--->刚编译好看不到ip地址?
	2.	print			//显示所有的u-boot的变量值

### 3.2.2 Qemu网络功能设置

**1.配置Qemu与Ubuntu主机的网路连接**

1.环境网络连接情况

	1.虚拟机与主机使用NAT方式连接;
	2.Qemu与Ubuntu虚拟机采用桥接(bridge)进行通信(需要Ubuntu主机内核tun/tap模块的支持).

2.配置

	1.Ubuntu安装工具包:
		apt install uml-utilities bridge-utils
	2.创建tun设备文件:
		tun设备文件位于: /dev/net/tun	--->我的自动就创建好了,因此不用再创建了
	3.修改/etc/network/interfaces文件,内容如下:
		# interfaces(5) file used by ifup(8) and ifdown(8)
		auto lo
		iface to inet loopback

		//下面的代码是新增的
		auto ens33		//ens33网络为ifconfig显示的网卡信息
		auto br0
		iface br0 inet dhcp
		bridge_ports ens33
	4.配置/etc/qemu-ifup、/etc/qemu-ifdown脚本--->可能有些有自动生成,但是我的没有
		1./etc/qemu-ifup内容如下:
			#!/bin/sh
	
			echo sudo tunctl -u $(id -un) -t $1
			sudo tunctl -u $(id -un) -t $1
			
			echo sudo ifconfig $1 0.0.0.0 promisc up
			sudo ifconfig $1 0.0.0.0 promisc up
			
			echo sudo brctl addif br0 $1
			sudo brctl addif br0 $1
			
			echo brctl show
			brctl show
			
			sudo ifconfig br0 192.168.33.135
			//此处的ip:我的是与虚拟机主机ifconfig中的ip一致,不确定是否有问题?
		2./etc/qemu-ifdown内容如下:
			#!/bin/sh

			echo sudo brctl delif br0 $1
			sudo brctl delif br0 $1
			
			echo sudo tunctl -d $1
			sudo tunctl -d $1
			 
			echo brctl show
			brctl show
	5.重启虚拟机即可.

**2.主机TFTP工具安装**

1.安装tftp工具

	apt-get install tftp-hpa tftpd-hpa xinetd

2.修改配置文件:/etc/default/tftpd-hpa

	TFTP_USERNAME="tftp"
	TFTP_DIRECTORY="/home/defychen/tftpboot"
	TFTP_ADDRESS="0.0.0.0:69"
	TFTP_OPTIONS="-l -c -s"

3.创建tftp目录(步骤2中指定"TFTP_DIRECTORY")

	mkdir /home/defychen/tftpboot
	chmod 777 /home/defychen/tftpboot

4.重启tftp服务

	/etc/init.d/tftpd-hpa restart

**3.自动化引导需修改u-boot和kernel**

1.u-boot修改的地方:

	1.打开u-boot目录下的:./include/configs/vexpress_common.h,修改代码如下:
		/* Basic enviroment settings */
		//注释掉原始的
		/*#define CONFIG_BOOTCOMMAND \
				"run distro_bootcmd; " \
				"run bootflash; "
		*/
		//修改为:
		#define CONFIG_BOOTCOMMAND \
				"tftp 0x60003000 uImage; tftp 0x60500000 vexpress-v2p-ca9.dtb; \
				setenv bootargs 'root=/dev/mmcblk0 console=ttyAMA0'; \
				bootm 0x60003000 - 0x60500000; "
				//此处"0x60003000 - 0x60500000"必须有空格隔开,没有是引导不起来的
		//新增的Netmask
		/*Netmask*/
		#define CONFIG_IPADDR 192.168.33.196	//板卡的ip地址,需要与虚拟机主机在同一网段
		#define CONFIG_NETMASK 255.255.255.0
		#define CONFIG_SERVERIP 192.168.33.135	//虚拟机主机的ip地址
	2.重新编译
		export CROSS_COMPILE=arm-linux-gnueabi-
		export ARCH=arm
		make vexpress_ca9x4_defconfig
		make -j4
	3.拷贝编译好的u-boot到tftpboot目录
		cp u-boot /home/defychen/tftpboot/

2.linux需要修改的地方

	1.进入linux目录,执行编译:
		make LOADADDR=0x60003000 uImage -j4		//指定uImage加载地址
	2.拷贝uImage/dtb到tftpboot目录
		cp arch/arm/boot/uImage /home/defychen/tftpboot/
		cp arch/arm/boot/dts/vexpress-v2p-ca9.dtb /home/defychen/tftpboot/

**4.修改tftpboot下的启动脚本**

	#!/bin/sh
	qemu-system-arm -M vexpress-a9 -m 512M \
		-kernel u-boot -nographic     \
		-net nic,vlan=0 -net tap,vlan=0,ifname=tap0 \
		-sd a9rootfs.ext3

**5.启动即可**

	./qemu-uboot.sh

## 3.3 在Ubuntu系统搭建Qemu模拟ARM(三)--->挂载NFS文件系统

NFS文件系统是一种网络文件系统,两个机器之间可通过NFS实现网络共享.

### 3.3.1 Ubuntu主机HOST支持NFS服务

**1.安装nfs server**

	apt install nfs-kernel-server	//Ubuntu主机是作为nfs的server端,板卡作为client端

**2.配置NFS(即设置NFS共享)**

	在/etc/exports文件中添加:
	/home/defychen/repository_develop/rootfs *(rw,sync,no_root_squash,no_subtree_check)
	/*
		/home/defychen/repository_develop/rootfs:根文件系统所在的目录,通过NFS实现共享;
		rw:两个机器均可可读写;
		sync:同步;
		no_root_squash:指示板卡访问主机的文件系统目录可以以root用户访问;
		no_subtree_check:不检查根文件系统子目录.
		PS:(rw,sync,no_root_squash,no_subtree_check)--->中间无空格.
	*/

**3.开启NFS服务**

	/etc/init.d/rpcbind restart
	/etc/init.d/nfs-kernel-server restart

### 3.3.2 u-boot修改bootargs启动参数

1.修改u-boot目录下的./include/configs/vexpress_common.h:

	//修改为:
	#define CONFIG_BOOTCOMMAND \
			"tftp 0x60003000 uImage; tftp 0x60500000 vexpress-v2p-ca9.dtb; \
			setenv bootargs 'root=/dev/nfs rw \
			nfsroot=192.168.33.135:/home/defychen/repository_develop/rootfs init=/linuxrc \
			ip=192.168.33.196 console=ttyAMA0'; \
			bootm 0x60003000 - 0x60500000; "
	/*
		1.root=/dev/nfs表示根文件系统是NFS形式;而root=/dev/mmcblk0表示根文件系统是在SD中;
		2.nfsroot=192.168.33.135:/home/defychen/repository_develop/rootfs:
			表示根文件系统所在服务器的位置;
		4.ip=192.168.33.196:表示板卡的ip地址;
		3.此处"0x60003000 - 0x60500000"必须有空格隔开,没有是引导不起来的.
	*/
	//新增的Netmask
	/*Netmask*/
	#define CONFIG_IPADDR 192.168.33.196	//板卡的ip地址,需要与虚拟机主机在同一网段
	#define CONFIG_NETMASK 255.255.255.0
	#define CONFIG_SERVERIP 192.168.33.135	//虚拟机主机的ip地址

2.编译

	make -j4

3.拷贝到tftboot目录

	cp u-boot /home/defychen/tftpboot

### 3.3.3 内核支持挂载NFS文件系统

1.配置menuconfig以支持NFS文件系统

	在linux下执行:make menuconfig,接着勾选下面几个选项(好像默认是选上的):
		File Systems--->
			[*]Network File Systems
				<*> NFS client support
				<*> NFS client support for NFS versoin 2
				<*> NFS client support for NFS versoin 3
				...
				<*> Root file system on NFS

2.编译

	make uImage -j4

3.拷贝到tftpboot目录

	cp arch/arm/boot/uImage /home/defychen/tftpboot
	cp arch/arm/boot/dts/vexpress-v2p-ca9.dtb /home/defychen/tftpboot/

### 3.3.4 启动Qemu及板卡

1.启动脚本与之前可以一样

	#!/bin/sh
	qemu-system-arm -M vexpress-a9 -m 512M \
		-kernel u-boot -nographic     \
		-net nic,vlan=0 -net tap,vlan=0,ifname=tap0 \
		-sd a9rootfs.ext3	//该行可去掉,因为不会看sd卡中的文件系统

### 3.3.5 测试

1.板卡端测试

	在板卡的文件系统目录下新建一个文件:
		touch hello	//此时在ubuntu主机端的/home/defychen/repository_develop/rootfs可以看到该文件.

2.ubuntu主机端测试

	在ubuntu主机端删掉刚刚创建的文件:
		cd /home/defychen/repository_develop/rootfs
		rm hello //此时在在板卡端可以看到该文件已经没了

### 3.3.6 问题及解决方法

问题:在ubuntu 19.04上,在uboot启动时,使用nfs挂载NFS时会出现以下问题:

	VFS: Unable to mount root fs via NFS, trying floppy. 
	VFS: Cannot open root device “nfs” or unknown-block(2,0): error -6 
	Please append a correct “root=” boot option; here are the available partitions: 
	1f00 256 mtdblock0 (driver?) 
	1f01 128 mtdblock1 (driver?) 
	1f02 2048 mtdblock2 (driver?) 
	1f03 259712 mtdblock3 (driver?) 
	Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block

解决:

	1.原因:ubuntu 17.10之后nfs默认就只支持协议3和协议4,但是uboot默认启动的是协议2;
	2.解决:使ubuntu 19.04的nfs支持协议2,在文件"/etc/default/nfs-kernel-server"末尾加上一句:
		RPCNFSDOPTS="--nfs-version 2,3,4 --debug --syslog"
		
		改完之后内容如下:
		# Number of servers to start up
		RPCNFSDCOUNT=8
		
		# Runtime priority of server (see nice(1))
		RPCNFSDPRIORITY=0
		
		# Options for rpc.mountd.
		# If you have a port-based firewall, you might want to set up
		# a fixed port here using the --port option. For more information, 
		# see rpc.mountd(8) or http://wiki.debian.org/SecuringNFS
		# To disable NFSv4 on the server, specify '--no-nfs-version 4' here
		RPCMOUNTDOPTS="--manage-gids"
		
		# Do you want to start the svcgssd daemon? It is only required for Kerberos
		# exports. Valid alternatives are "yes" and "no"; the default is "no".
		NEED_SVCGSSD=""
		
		# Options for rpc.svcgssd.
		RPCSVCGSSDOPTS=""
		RPCNFSDOPTS="--nfs-version 2,3,4 --debug --syslog"	//增加的一句话
	3.重启nfs服务器即可
		/etc/init.d/rpcbind restart
		/etc/init.d/nfs-kernel-server restart

## 3.4 在Ubuntu系统搭建Qemu模拟ARM(四)--->完善根文件系统

**1.目的**

	1.增加内核的各种用户接口;
	2.reboot功能的添加

**2.添加步骤**
	
	在板卡的根文件系统中:
	1.新建etc目录:
		添加inittab、init.d/rcS、fstab、profile
		PS:该目录可在./plugin/下面有,直接拷贝,修改profile为显示自己希望的前缀:
			PS1='defychen@vexpress:\w # '
			export PS1
	2.新建tmp、sys、var、proc目录--->仅创建即可,不需要有内容
	3.启动qemu即可.

**3.根文件系统启动流程**

...

## 3.5 在Ubuntu系统搭建Qemu模拟ARM(五)--->在板卡上运行应用和驱动程序

略.