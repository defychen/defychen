#	linux command usage
***
## 1.sed命令

*文本处理工具,属于管道命令,以行为单位进行处理,可以进行行替换、删除、新增、选取等.*

**1)删除某行(不会真正删除某行,只是在屏幕上显示的时少了该行):**
	
	sed '1d' ab.txt	//删除第一行
	sed '$d' ab.txt	//删除最后一行
	sed '1,$d' ab.txt	//删除第一行到最后一行

**2)显示某行:**
	
	sed -n '1p' ab.txt	//-n:表示只有作用那行会显示;p:打印

**3)模式查询:**

	sed -n '/defy/p' ab.txt	//查询包括"defy"的所在行

**4)增加行或字符串:**
	
	sed '1a drink tea' ab.txt	//第一行的下一行增加一行"drink tea"

**5)代替一行或多行:**

	/*只会在屏幕上显示已经修改,但是并没有真正写进文件*/
	sed '1c Hi' ab.txt	//第一行代替为"Hi"
	sed -n '/defy/p' ab.txt | sed 's/defy/bird/g' 	
	/*如果需要写入文件,可以加上"-i"参数*/
	sed -i '1c Hi' ab.txt	/*第一行代替为"Hi",并写入到ab.txt文件*/
	sed -i '49c CONFIG_POSIX_MQUEUE=y' linux-m3755-demo-new-kernel.config		/*打开消息队列的宏*/
	sed -i '/CONFIG_POSIX_MQUEUE/c CONFIG_POSIX_MQUEUE=y' linux-m3755-demo-new-kernel.config /*最好的办法*/
	/*修改ali corp的配置:*/
	sed -i '/CONFIG_POSIX_MQUEUE/c CONFIG_POSIX_MQUEUE=y' board/ali/c3922-demo/linux-m3755-demo-new-kernel.config
***
## 2.dd命令
*烧写文件(kernel,rootfs等等)到特定的区块.*

**step1 读取板子各个分区信息:**

*/proc目录下保存板子分区信息以及CPU等信息*

	cat /proc/mtd	//mtd:各个分区信息(得到比如kernel所在的分区mtd4)
	cat /proc/cpuinfo	//板子的cpu信息(arm架构等等)

**step2 通过nfs挂载需要烧写的已经编译好的文件目录:**

	mkdir /mnt/nfs	//新建挂载目录
	mount -o nolock 192.168.9.202:/zhsa022/usrhome/defy.chen/ /mnt/nfs	//挂载到/mnt/nfs目录

**step3 进行烧写(dd)**

*e.g. /dev/mtdblock4为存放kernel的分区.*

*切换到需要烧写的已经编译好的文件目录进行烧写*
	
	cd /mnt/nfs/buildroot/s3922-2/buildroot/output/images
	dd if=./main_bin.ubo of=/dev/mtdblock4	//if:需要烧写的文件;of:烧写的目标区块.
**step4 烧写完毕，重启:reboot**

## 3. tree命令

*以树状图列出目录的内容,主要用于查看目录结构*

**常用的为(更多可以man tree或info tree):**

	tree -L 1/2/3 -d /*显示当前目录下的1/2/3级目录*/
	tree -a /*显示所有文件和目录，对于文件和目录较少可以使用*/

## 4.uname -r命令

	uname -r /*查看内核版本信息*/

## 5.zip命令

*GNU zip---gzip(gz)和bzip2(bz2)两种压缩格式，压缩比:gzip>bzip2*

*解压方法:*
	
	tar -xvzf filename.tar.gz	/*x:解压;v:列出解压出来的文件;z:gz格式;f:后面接文件名*/
	tar -xvjf filename.tar.bz2	/*x:解压;v:列出解压出来的文件;j:bz2格式;f:后面接文件名*/

*创建压缩包的方法:*

	tar -cvjf 要创建的压缩包名(filename.tar.bz2) 包含的文件名
	tar -cvjf test.tar.bz2 ./test/	/*将test所有文件创建成为一个test.tar.bz2的压缩包*/

**由于一般用的比较多的是"bz2",因此:-xvjf/-cvjf.**

## 6.重定向

*"<"标准输入; "1>"标准输出; "2>"错误输出(包括warning)*

	/*将标准输出到normal_output.txt;错误输出到warning.txt*/
	make 1> ../../../normal_output.txt 2> ../../../warning.txt
	make > ../../../see.txt 2>&1	/*">"等同于"1>",将标准输出和错误输出都输出到see.txt*/

## 7.cp复制文件夹

	cp -r source_file dest_file 

## 8.linux版本控制

	#include <linux/version.h>	/*进行版本选择时,必须有这个头文件*/
	
	#if LINUX_VERSION_CODE > KERNEL_VERSION(3,3,0)
	#include <asm/switch_to.h>	/*当版本>3.3.0时选择"asm/switch_to.h"头文件*/
	#else
	#include <asm/system.h>		/*版本<3.30时使用"asm/system.h"*/
	#endif

## 9.ali corp自动挂载方式

	#!/bin/sh
	ifconfig eth0 down
	ifconfig eth0 hw ether de:ad:be:ef:f1:f5
	ifconfig eth0 up
 	udhcpc
	mkdir /mnt/nfs
	mount -t nfs -o nolock 192.168.9.202:/zhsa022/usrhome/defy.chen/gitwork/ci/ref /mnt/nfs
	/*
		-t nfs:是以nfs形式挂载
		-o nolock:nfs mount默认选项包含文件锁,因此使用"-o nolock"
	*/

## 10.shell脚本

	#!/bin/sh
	#Scriptname: choice_script
	echo "script usage"
	echo "1.Play clear stream for VA_DMX"
	echo "2.Play scramble stream for VA_DSCR"
	echo "3.Play scramble stream for VA_SCHIP"
	echo "Please choice the number..."	#提示让用户输入选择项
	read select							#接收用户的选择
	if [ $select = 1 ]; then			#如果用户选择了"1"
		if [ ! -f "../../stream/choice.txt" ]; then		#如果文件不存在,就创建
			touch "../../stream/choice.txt"
			echo 1 > ../../stream/choice.txt			#将1重定向到文件,">"覆盖方式; ">>"追加方式
		else
			echo 1 > ../../stream/choice.txt
		fi
	elif [ $select = 2 ]; then			#用于选择了"2"
		if [ ! -f "../../stream/choice.txt" ]; then		
			touch "../../stream/choice.txt"
			echo 2 > ../../stream/choice.txt
		else
			echo 2 > ../../stream/choice.txt
		fi
	elif [ $select = 3 ]; then			#用户选择了"3"
		if [ ! -f "../../stream/choice.txt" ]; then
			touche "../../stream/choice.txt"
			echo 3 > ../../stream/choice.txt
		else
			echo 3 > ../../stream/choice.txt
		fi
	else
		echo "The choice is wrong, please run this script again!"
		exit 1	#强制退出
	fi
	echo "Thank you for your choice"

## 11. vim的使用

**替换**

	:s/old/new			---将光标所在行的第一个old替换为new
	:s/old/new/g		---将光标所在行的所有old替换为new
	:%s/old/new/gc		---全文执行替换"后面c表示询问是否替换,可以不带c"
	:3,10s/old/new/gic	---3到10行执行替换,"i忽略大小写,c询问"	
	
## 12. df命令

查看硬盘使用情况

	df -hl
	//得到的信息如下:
	Filesystem      Size  Used Avail Use% Mounted on
	df: `/var/lib/lightdm/.gvfs': Permission denied
	/dev/sda1        93G   64G   25G  72% /
	udev             63G  4.0K   63G   1% /dev
	tmpfs            26G   25M   26G   1% /run
	none            5.0M     0  5.0M   0% /run/lock
	none             63G  232K   63G   1% /run/shm
	none            100M     0  100M   0% /run/user
	/dev/sdb1       7.3T  6.6T  371G  95% /zhsa022	---硬盘使用
	/dev/sda3       651G  358G  261G  58% /zhsa021	---硬盘使用
	cgroups          63G     0   63G   0% /sys/fs/cgroup

## 13、head命令

	/*
	ts流文件都是二进制文件,像:	47 51 20 30 07 90 00 00 00 1C...	//每个代表一个byte
	一个ts流文件为31182808 byte(ls -l命令显示的文件大小以byte为单位),在ultraEdit中显示为:1DBCFD8数据
	如果需要截取450448 byte,使用head命令截取
	*/
	head -c 450448 xxx.ts > test.ts		//截取xxx.ts中的450448 byte到test.ts中

## 14、nm命令

	nm vodrm_test	//查看函数库、可执行文件或目标文件里包含哪些函数.

## 15、重定向和管道

	//重定向
	1)将标准输出和标准错误输出分别重定向到不同的文件中:
		kill -HUP 1234 > killout.txt 2> killerr.txt	//将标准输入重定向到killout.txt;将标准错误输出重定向到killerr.txt
	2)将标准输出和标准错误输出重定向到同一个文件:
		kill -l 1234 > killouterr.txt 2>&1		//2--标准错误; >--冲定向; &1--和1(标准输出一样)

	//管道
	ls -l | head -n 5		//显示ls -l的前5行
	grep linux . -nr | more		//按页显示查找到的字符串,没有grep linux . -nr好看

## 16、which命令

	which命令用于查找并显示给定命令的绝对路径.
	which ls	//显示为"/bin/ls"

## 13. wget命令