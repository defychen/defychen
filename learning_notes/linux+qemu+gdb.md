# Linux+Qemu+gdb

# 1.先导知识

## 1.1 initramfs

1.initramfs(基于ramfs的临时文件系统):一种以 cpio 格式压缩后的rootfs 文件系统,它通常和 Linux 内核文件一起被打包成
boot.img 作为启动镜像.
2.BootLoader加载boot.img,并启动内核之后.内核接着就对cpio格式的initramfs进行解压,并将解压后得到的rootfs加载进内存,最后内核会检查rootfs中是否存在 init 可执行文件(该init 文件本质上是一个执行的shell 脚本).如果存在,就开始执行init程序并创建Linux系统用户空间PID为1的进程,然后将磁盘中存放根目录内容的分区真正地挂载到/根目录上,最后通过exec chroot . /sbin/init命令来将rootfs中的根目录切换到挂载了实际磁盘分区文件系统中,并执行/sbin/init程序来启动系统中的其他进程和服务.

```
基于ramfs开发initramfs，取代了initrd
```

## 1.2 initrd

1.initrd代指内核启动过程中的一个阶段,临时挂载文件系统,加载硬盘的基础驱动,进而过渡到最终的根文件系统.
2.是早期基于ramdisk生成的临时根文件系统的名称
3.现阶段虽然基于initramfs,但是临时根文件系统也依然存在某些发行版称其为initrd

```
e.g.
	CentOS临时根文件系统命名为:initramfs-`uname -r`.img
	Ubuntu临时根文件系统命名为:initrd-`uname -r`.img
PS:所以,initrd和initramfs是一个东西,只是在不同的linux发行版叫法不同而已.
```

## 1.3 为什么需要initrd/initramfs

1.linux kernel在自身初始化完成之后,需要能够找到并运行第一个用户程序(这个程序通常叫做“init”程序).用户程序存在于文件系统之中,因此,内核必须找到并挂载一个文件系统才可以成功完成系统的引导过程.
2.在grub中提供了一个选项“root=”用来指定第一个文件系统,但随着硬件的发展,很多情况下这个文件系统也许是存放在USB设备,SCSI设备等等多种多样的设备之上.如果需要正确引导,USB或者SCSI驱动模块首先需要运行起来,可是不巧的是,这些驱动程序也是存放在文件系统里,因此会形成一个悖论.
3.为解决此问题,linux kernel提出了一个RAM disk的解决方案,把一些启动所必须的用户程序和驱动模块放在RAM disk中,这个RAM disk看上去和普通的disk一样,有文件系统,有cache.内核启动时,首先把RAM disk挂载起来,等到init程序和一些必要模块运行起来之后,再切到真正的文件系统之中.
4.上面提到的RAM disk的方案实际上就是initrd.如果仔细考虑一下,initrd虽然解决了问题但并不完美.比如:disk有cache机制,对于RAM disk来说,这个cache机制就显得很多余且浪费空间;同时disk需要文件系统,那文件系统(如ext2等)必须被编译进kernel而不能作为模块来使用.
5.linux 2.6 kernel提出了一种新的实现机制,即initramfs.initramfs只是一种RAM filesystem而不是disk.initramfs实际是一个cpio归档,启动所需的用户程序和驱动模块被归档成一个文件.因此,不需要cache,也不需要文件系统.

# 2. 下载并编译内核

参考Ubuntu&Qemu usage的"Chapter 5. 手动升级ubuntu的kernel到最新的版本".

## 2.1 下载内核

下载linux-4.9.263.tar.gz,解压缩得到目录linux-4.9.263.

```
mkdir ~/oslab
cd ~/oslab
wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.9.263.tar.xz #下载
备用链接: https://od.srpr.cc/acgg0/linux-4.9.263.tar.xz
tar -Jvxf linux-4.9.263.tar.xz #解压
```

## 2.2 安装所需的依赖库

可能ubuntu官方镜像源安装下载镜像速度较慢,需要切换镜像源.

```
sudo apt-get install git build-essential libelf-dev xz-utils libssl-dev bc
libncurses5-dev libncursesw5-dev
```

## 2.3 编译

### 2.3.1 编译配置的两种方法

#### 2.3.1.1 精简配置,减少不必要的驱动编译(速度快，存储小)

```
cd ~/oslab/linux-4.9.263
wget https://raw.githubusercontent.com/ZacharyLiuCS/USTC_OS/master/term2021/lab1/.config
# raw访问可能不畅, 备用链接:
http://222.186.10.65:8080/directlink/3/.config
```

#### 2.3.1.2 内核配置(make menuconfig)详述(编译时间较长，占空间)

```
cd ~/oslab/linux-4.9.263
make menuconfig #本次实验直接选择Save,然后exit
```

#### 2.3.1.3 编译

```
make -j $((`nproc`-1)) # 此处为使用(你的CPU核心数-1)个线程进行编译, 如果虚拟机分配的
cpu数只有1(如Hyper-V默认只分配1核)则需先调整虚拟机分配的核心数.
```

#### 2.3.1.4 make过程可能出现的问题

```
编译内核时遇到 make[1]: *** No rule to make target 'debian/canonicalcerts.pem',
needed by 'certs/x509_certificate_list'. Stop.
解决:
用文本编辑器(vim 或 gedit)打开 PATH-TO-linux-4.9.263/.config文件,找到并注释掉包含CONFIG_SYSTEM_TRUSTED_KEY和
CONFIG_MODULE_SIG_KEY 的两行即可.
解决方案原链接：https://unix.stackexchange.com/questions/293642/attemptingto-compile-kernel-yields-a-certification-error
```

# 3. 准备Qemu

直接安装qemu包即可

```
sudo apt install qemu
# Ubuntu 20.04/20.10 环境下执行以下指令
sudo apt install qemu-system-x86
```

# 4. 制作根文件系统

利用busybox生成根文件系统,并使用qemu启动运行.

## 4.1 下载busybox

```
cd ~/oslab
wget https://busybox.net/downloads/busybox-1.32.1.tar.bz2 #下载
备用链接:https://od.srpr.cc/acgg0/busybox-1.32.1.tar.bz2
tar -jxvf busybox-1.32.1.tar.bz2 #解压
cd ~/oslab/busybox-1.32.1
```

## 4.2 编译busybox

### 4.2.1 修改配置

```
make menuconfig
#修改配置
Setting->
	Build Options
		[*] Build static binary(no share libs)
```

### 4.2.2 编译并安装

```
make -j $((`nproc`-1))
make install
```

### 4.2.3 准备根文件系统

#### 4.2.3.1 创建一些节点

```
cd ~/oslab/busybox-1.32.1/_install
sudo mkdir dev
sudo mknod dev/console c 5 1
sudo mknod dev/ram b 1 0
sudo touch init
```

#### 4.2.3.2 编辑init脚本

在init脚本写入以下内容:

```
vim init
# 写入以下内容
#!/bin/sh
echo "INIT SCRIPT"
mkdir /proc
mkdir /sys
mount -t proc none /proc
mount -t sysfs none /sys
mkdir /tmp
mount -t tmpfs none /tmp
mount -t debugfs none /sys/kernel/debug	# 挂载debugfs
echo -e "\nThis boot took $(cut -d' ' -f1 /proc/uptime) seconds\n"
exec /bin/sh
```

给init脚本增加可执行权限:sudo chmod +x init

#### 4.2.3.3 制作initramfs文件

将busybox下的内容打包归档成cpio文件,以供linux内核做initramfs启动执行.

```
cd ~/oslab/busybox-1.32.1/_install
find . -print0 | cpio --null -ov --format=newc | gzip -9 >
	~/oslab/initramfs-busybox-x64.cpio.gz# 注意：该命令一定要在busybox的 _install目录下执行
PS: 每次修改_install,都要重新执行该命令
```

# 5 运行

## 5.1 以图形界面形式运行

qemu以图形界面,弹出窗口形式运行内核.

```
cd ~/oslab
qemu-system-x86_64 -s -kernel ~/oslab/linux-4.9.263/arch/x86_64/boot/bzImage
-initrd ~/oslab/initramfs-busybox-x64.cpio.gz --append "nokaslr root=/dev/ram init=/init"
```

## 5.2 无界面形式启动

qemu无界面形式启动运行内核,输出重定向到当前shell.

```
cd ~/oslab
qemu-system-x86_64 -s -kernel ~/oslab/linux-4.9.263/arch/x86_64/boot/bzImage
-initrd ~/oslab/initramfs-busybox-x64.cpio.gz --append "nokaslr root=/dev/ram init=/init console=ttyS0"
-nographic
```

运行之后的现象:

```
1.在qemu窗口可以看到成功运行,且进入shell环境;
2.以无图形界面形式启动,输入Ctrl+A再敲X结束模拟进程并关闭qemu(图形界面无效).
```

# 6. gdb+qemu调试内核

## 6.1 gdb简介

gdb是一款终端环境下常用的调试工具.

### 6.1.1 安装gdb

ubuntu下安装gdb:

```
sudo apt install gdb
```

### 6.1.2 调试

```
编译程序时加入-g选项,如: gcc -g -o test test.c
运行gdb调试程序: gdb test
```

### 6.1.3 常用命令

```
r/run 					# 开始执行程序
b/break <location> 		# 在location处添加断点,location可以是代码行数或函数名
b/break <location> if <condition> # 在location处添加断点,仅当caondition条件满足才中断运行
c/continue 				# 继续执行到下一个断点或程序结束
n/next 					# 运行下一行代码,如果遇到函数调用直接跳到调用结束
s/step 					# 运行下一行代码,如果遇到函数调用则进入函数内部逐行执行
ni/nexti 				# 类似next,运行下一行汇编代码(一行c代码可能对应多行汇编代码)
si/stepi 				# 类似step,运行下一行汇编代码
list 					# 显示当前行代码
p/print <expression> 	# 查看表达式expression的值
```

## 6.2 在qemu中启动gdb server

### 6.2.1 以图形界面形式运行+gdb server

```
cd ~/oslab
qemu-system-x86_64 -s -S -kernel ~/oslab/linux-
4.9.263/arch/x86_64/boot/bzImage -initrd ~/oslab/initramfs-busyboxx64.cpio.gz --append "nokaslr root=/dev/ram init=/init"
```

### 6.2.2 无界面形式启动+gdb server

```
cd ~/oslab
qemu-system-x86_64 -s -S -kernel ~/oslab/linux-4.9.263/arch/x86_64/boot/bzImage
-initrd ~/oslab/initramfs-busybox-x64.cpio.gz --append "nokaslr root=/dev/ram init=/init console=ttyS0"
-nographic
```

相比于非gdb调试,只是增加了一个"-S"的参数,参数说明如下:

```
-S:freeze(冻结) CPU at startup (use ’c’ to start execution)
	--->即启动就被gdb接管
-s:shorthand for -gdb tcp::1234 若不想使用1234端口，则可以使用-gdb tcp:xxxx来取代-s选项
	--->用于gdb使用"target remote:1234连接gdb server"
```

## 6.3 建立gdb与gdb server之间的连接
在另外一个终端运行gdb,然后在gdb界面中运行如下命令:

```
gdb					# 执行gdb命令,紧接着会进入gdb.这里一定是在另外一个终端运行,不能在qemu的窗口上输入
target remote:1234 	# 建立gdb和gdb serve之间的连接
c 					# 让qemu上的Linux继续运行
```

此时gdb与qemu已经建立了连接.但是由于没有加载符号表,无法根据符号设置断点.

## 6.4 重新配置Linux,使之携带调试信息

使用Ctrl+A X组合键退出之前打开的qemu终端.重新配置linux,使之携带调试信息:

```
cd ~/oslab/linux-4.9.263/
./scripts/config -e DEBUG_INFO -e GDB_SCRIPTS -d DEBUG_INFO_REDUCED -d DEBUG_INFO_SPLIT -d DEBUG_INFO_DWARF4
```

重新编译

```
make -j $((`proc`-1))
```

## 6.5 加载vmlinux中的符号表并设置断点

### 6.5.1 启动gdb server

如“6.2.1 以图形界面形式运行+gdb server”启动gdb server

### 6.5.2 建立gdb与gdb server之间的连接

在另外一个终端运行gdb,然后在gdb界面中运行如下命令:

```
gdb					# 执行gdb命令,紧接着会进入gdb.这里一定是在另外一个终端运行,不能在qemu的窗口上输入
file ~/oslab/linux-4.9.263/vmlinux	# 加载符号表
target remote:1234 	# 建立gdb和gdb serve之间的连接
```

在gdb界面中设置断点:

```
b start_kernel	# 设置断点
c # 继续运行到断点
l # 查看断点处代码
p init_task # 查看断点处变量值
```