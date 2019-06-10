# Ubuntu & Qemu usage

# 1. Ubuntu 16.04 usage

## 1. 忘记root密码解决办法

**方法 1**

如果用户具有sudo权限:

	1.sudo su root	//通过sudo直接切换到root用户
	2.passwd		//重新更改root密码
	/*
		提示:输入新的UNIX密码->重新输入新的UNIX密码->更改root密码成功.
	*/

**方法 2**

用户不具备sudo权限,需要进入GRUB修改kernel镜像启动参数,此处暂时略.

## 2. root用户和普通用户的切换

1.切换到root用户

	1.su root	//切换到root用户,输入root用户密码即可.仍然停在当前目录
	2.su -		//切换到root用户,输入root用户密码即可.同时切换到当前用户的home目录.

2.切换到普通用户

	su defychen		//切换到defychen用户(defychen为普通用户名).

## 3. vim软件的安装

	sudo apt-get install vim
	echo $?		//返回0表示软件安装成功;非0表示出现了问题.

## 4. 检查软件更新情况并将软件进行更新

	1.sudo apt-get update
	/*
		更新/etc/apt/sources.list和/etc/apt/sources.list.d中列出的源的地址.这样才能获取到最新的
		软件包.
	*/
	2.sudo apt-get upgrade
	/*
		升级已安装的所有软件包,将本地的软件版本与update文件更新的版本进行对比从而进行相关升级.因此,执行
		upgrade之前一定要执行update,这样才能保证更新到最新.
	*/

## 5. 关于Ubuntu中出现"Could not get lock /var/lib/dpkg/lock"解决方案

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

## 6. 安装"net-tools"

**1.问题**

刚安装的linux可能在执行"ifconfig"时,没有这个命令.报如下的错误:

	Comand "ifconfig" not found, but can be installed with:
		apt install net-tools
	PS:即没有ifconfig命令.

**2.解决**

	apt install net-tools

## 7. 安装git

	sudo apt-get install git

注意点:
	1.查看git的版本:
	git --version
	2.sudo apt-get下载的文件的目录:
		/var/cache/apt/archives		//但是使用"sudo apt-get install git"没有发现文件
	3.文件下载的目录可以在"/etc/apt/source.list"中指定  --->还没有发现真正的用途

## 8. linux源码下载地址

[国内下载地址](http://ftp.sjtu.edu.cn/sites/ftp.kernel.org/pub/linux/kernel/)

	国内下载地址速度快很多.

[官网地址](https://www.kernel.org/pub/linux/kernel/)

	官网下载很慢.

## 9. gcc下载地址及版本切换

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

## 10. ubuntu版本查看

	1.cat /proc/version		//可以显示当前Linux的版本及gcc的版本信息
	2.uname -a				//也会显示当前Linux的版本,还有当前用户名
	3.lsb_release -a			//会显示当前Ubuntu版本"Ubuntu 18.04.2 LTS"

## 11. rar/unrar工具的安装

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

## 12. wine的安装及使用

### 12.1 安装wine

	apt-get install wine64	//安装64-bit的wine.一般还需要安装wine32
	dpkt --add-architecture i386 	//添加i386体系结构
	apt-get upgrade	//更新包
	apt-get install wine32
	

### 12.2 使用

	wine *.exe

***

# 2. Qemu usage

Qemu是纯软件实现的虚拟化模拟器,几乎可以模拟任何硬件设备(e.g.Qemu模拟出一台能够独立运行操作系统的虚拟机,虚拟机认为自己在和硬件打交道,但其实是和Qemu模拟出来的硬件打交道,Qemu再将这些指令转译给真正的硬件).

	因为Qemu是纯软件实现的,所有的指令都要经过Qemu,性能非常低.所以,在实际中大多数的做法是配合KVM来完成虚
	拟化工作.因为KVM是硬件辅助的虚拟化技术,主要负责比较繁琐的CPU和内存虚拟化,而Qemu则负责I/O虚拟化,两者
	合作各自发挥优势,相得益彰.

## 1. 在Ubuntu系统搭建Qemu模拟ARM

环境:

	Ubuntu:Ubuntu 18.04.2 LTS
	Qemu上运行的内核:Linux 4.8
	Qemu:2.8
	目标系统:以Versatile Express-A9开发板搭建环境

### 1.1 Qemu的下载、编译、安装

**1.下载Qemu**

[qemu 2.8下载地址](http://download.qemu-project.org/qemu-2.8.0.tar.xz)

	下载下来的文件为:qemu-2.8.0.tar.xz

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
	3.安装
		make install	//会安装到系统的"/usr/local/bin/qemu-system-arm"的位置

### 1.2 linux内核编译(在Qemu上运行)

**1.下载并安装gnu交叉编译工具**

	sudo apt-get install gcc-arm-linux-gnueabi
	/*
		一般会下载最新版本gnu交叉编译工具,最新版本gnu对Linux也是有版本支持的.
		本人下载的的gcc版本为"version 7.3.0",不支持3.16版本的linux(会出现很多error),
		需要使用4.x版本的linux.
	*/

**2.内核下载**

可以参考前面"Ubuntu 16.04 usage"中的"8. linux源码下载地址":

	本人下载的地址为:https://mirrors.edge.kernel.org/pub/linux/kernel/v4.x/
	下载的版本为:linux-4.8.tar.gz		//因为最新的gnu交叉编译工具仅支持4.x之后的版本的

**3.解压、配置、编译**

	1.解压
		//Ubuntu 18.04下载的linux会放在/home/defychen/Downloads/linux-4.8.tar.gz
		cp /home/defychen/Downloads/linux-4.8.tar.gz /root/
		cd /root
		tar -xvzf linux-4.8.tar.gz
		cd linux-4.8
	2.配置
		export CROSS_COMPILE=arm-linux-gnueabi-
		export ARM=arm
		make vexpress_defconfig		//所有的config文件放在./arch/arm/configs/目录下
	3.编译
		make -j2
		/*
			1.image:
				编译好的image会在:./arch/arm/boot/zImage.
			2.dtb:
				编译好的dtb会在:./arch/arm/boot/dts/vexpress-v2p-ca9.dtb
		*/

### 1.3 根文件系统的制作

**1.busybox的下载、解压**

[busybox下载地址](https://busybox.net/downloads/)

	方法1:打开上述网址选择"busybox-1.25.0.tar.bz2"进行下载
		//Ubuntu 18.04下载的busybox会放在/home/defychen/Downloads/busybox-1.25.0.tar.bz2
		cp /home/defychen/Downloads/busybox-1.25.0.tar.bz2 /root
		cd /root
		tar -xvjf busybox-1.25.0.tar.bz2
		cd busybox-1.25.0
	方法2:使用命令行下载
		wget http://www.busybox.net/downloads/busybox-1.25.0.tar.bz2 --no-check-certificate
		//没试过,不知道行不行??

**2.配置、编译**

	make defconfig 	//config文件在./configs/下面,但是defconfig没去看到底是哪一个config文件
	make CROSS_COMPILE=arm-linux-gnueabi-	//编译
	make CROSS_COMPILE=arm-linux-gnueabi- install	//安装
	/*
		生成的根文件系统位于:./busybox-1.25.0/_install/,有"bin/linuxrc/sbin/usr"等.
	*/

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

3.创建4个tty终端设备

	cd rootfs/dev
	mknod tty1 c 4 1
	mknod tty2 c 4 2
	mknod tty3 c 4 3
	mknod tty4 c 4 4

4.生成32M大小的镜像,并拷贝文件系统树到镜像文件中

	cd /root
	dd if=/dev/zero of=a9rootfs.ext3 bs=1M count=32
	mkfs.ext3 a9rootfs.ext3
	mkdir tmpfs
	mount -t ext3 a9rootfs.ext3 tmpfs/ -o loop	//将a9rootfs.ext3(为一个文件系统)挂载到tmpfs下
	cp -r rootfs/* tmpfs/
	sudo umount tmpfs	//卸载

### 1.4 运行虚拟机

在终端输入:

	qemu-system-arm -M vexpress-a9 -m 512M -kernel /root/linux-4.8/arch/arm/boot/zImage
		-dtb /root/linux-4.8/arch/arm/boot/dts/vexpress-v2p-ca9.dtb -nographic -append
		"root=/dev/mmcblk0 console=ttyAMA0" -sd a9rootfs.ext3

启动之后即可进入到终端(只运行内核和根文件系统),boot后续增加.