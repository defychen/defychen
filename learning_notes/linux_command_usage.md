#	linux command usage
***
## 1.sed命令

文本处理工具,属于管道命令,以"行"为单位进行处理,可以进行行替换、删除、新增、选取等.

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

## 2.dd命令

烧写文件(kernel,rootfs等等)到特定的区块.

**step1 读取板子各个分区信息:**

/proc目录下保存板子分区信息以及CPU等信息

	cat /proc/mtd	//mtd:各个分区信息(得到比如kernel所在的分区mtd4)
	cat /proc/cpuinfo	//板子的cpu信息(arm架构等等)

**step2 通过nfs挂载需要烧写的已经编译好的文件目录:**

	mkdir /mnt/nfs	//新建挂载目录
	mount -o nolock 192.168.9.202:/zhsa022/usrhome/defy.chen/ /mnt/nfs	//挂载到/mnt/nfs目录

**step3 进行烧写(dd)**

	e.g. /dev/mtdblock4为存放kernel的分区.

切换到需要烧写的已经编译好的文件目录进行烧写
	
	cd /mnt/nfs/buildroot/s3922-2/buildroot/output/images
	dd if=./main_bin.ubo of=/dev/mtdblock4	//if:需要烧写的文件;of:烧写的目标区块.

**step4 烧写完毕，重启:reboot**

## 3. tree命令

以树状图列出目录的内容,主要用于查看目录结构

**常用的为(更多可以man tree或info tree):**

	tree -L 1/2/3 -d /*显示当前目录下的1/2/3级目录*/
	tree -a /*显示所有文件和目录，对于文件和目录较少可以使用*/

## 4.uname -r命令

	uname -r /*查看内核版本信息*/

## 5.zip命令

GNU zip---gzip(gz)和bzip2(bz2)两种压缩格式，压缩比:gzip>bzip2

解压方法:
	
	tar -xvzf filename.tar.gz	/*x:解压;v:列出解压出来的文件;z:gz格式;f:后面接文件名*/
	tar -xvjf filename.tar.bz2	/*x:解压;v:列出解压出来的文件;j:bz2格式;f:后面接文件名*/

创建压缩包的方法:

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

## 13. head命令

	/*
	ts流文件都是二进制文件,像:	47 51 20 30 07 90 00 00 00 1C...	//每个代表一个byte
	一个ts流文件为31182808 byte(ls -l命令显示的文件大小以byte为单位),在ultraEdit中显示为:1DBCFD8数据
	如果需要截取450448 byte,使用head命令截取
	*/
	head -c 450448 xxx.ts > test.ts		//截取xxx.ts中的450448 byte到test.ts中

## 14. nm命令

	nm vodrm_test	//查看函数库、可执行文件或目标文件里包含哪些函数.

## 15. 重定向和管道

	//重定向
	1)将标准输出和标准错误输出分别重定向到不同的文件中:
		kill -HUP 1234 > killout.txt 2> killerr.txt	//将标准输入重定向到killout.txt;将标准错误输出重定向到killerr.txt
	2)将标准输出和标准错误输出重定向到同一个文件:
		kill -l 1234 > killouterr.txt 2>&1		//2--标准错误; >--冲定向; &1--和1(标准输出一样)

	//管道
	ls -l | head -n 5		//显示ls -l的前5行
	grep linux . -nr | more		//按页显示查找到的字符串,没有grep linux . -nr好看

## 16. which命令

	which命令用于查找并显示给定命令的绝对路径.
	which ls	//显示为"/bin/ls"

## 17. ln命令

	//ln为建立某个文件的链接文件
	ln -s test.sh test	//-s为建立一个软连接.test.sh:链接的目标的文件, test:新建的链接文件
	ls -l
	/*得到:
	lrwxrwxrwx 1 defy.chen defy.chen    7 Sep  4 20:27 test -> test.sh*
	-rwxrwxr-x 1 defy.chen defy.chen  328 Sep  4 20:04 test.sh*	//目标文件
	*/

## 18. 查看linux IPC相关的限制

	ipcs -l
	//显示为:
	------ Shared Memory Limits --------
	max number of segments = 4096
	max seg size (kbytes) = 32768
	max total shared memory (kbytes) = 8388608
	min seg size (bytes) = 1
	
	------ Semaphore Limits --------
	max number of arrays = 128
	max semaphores per array = 250
	max semaphores system wide = 32000
	max ops per semop call = 32
	semaphore max value = 32767
	
	------ Messages Limits --------
	max queues system wide = 32768
	max size of message (bytes) = 8192
	default max size of queue (bytes) = 16384 

## 19. md5sum命令

	md5sum命令用于生成和较验文件的md5值.只要文件内容相同(与文件名无关),其md5值就会相同.
	md5值是一个128位(16 byte)的二进制数据.一般显示为32个16进制的的数.
	
	md5sum filename		//计算filename文件的md5值
	
	md5sum命令的配置,在busybox中配置:
		--->make busybox-menuconfig->Coreutils->md5sum

## 20.awk命令

awk是一个强大的文本分析工具.awk是把文件逐行读入,以空格为默认分隔符进行切片,切片的部分再进行各种分析处理.awk适合于一行当中多个列(由空格或者tab键分隔).

语法格式:

	awk '{对数据处理的动作}'	filename
	last -n 5		//取出登录者的数据前5行
	//结果为:	
	martin.z pts/76       p8-martin-zhu.al Fri Dec  8 11:36   still logged in   
	steve.ch pts/46       p8-steve-chen.al Fri Dec  8 11:35   still logged in   
	steve.ch pts/26       p8-steve-chen.al Fri Dec  8 11:34   still logged in   
	martin.z pts/25       p8-martin-zhu.al Fri Dec  8 11:30   still logged in   
	wei.l    pts/71       10.8.7.81        Fri Dec  8 11:26   still logged in
	取出账户和登录者的IP,且帐号与IP之间以[tab]隔开:
	last -n 5 | awk '{print $1 "\t" $3}'		//tab键使用"\t"表示
	//$0:表示整行;	$1:表示第一列(空格或tab键分开的)

**实例1---awk基本应用**

	//一个待处理的文件"grade.txt"
	M.Tansley     05/99     48311     Green     8     40     44
	J.Lulu     06/99     48317     green     9     24     26
	P.Bunny     02/99     48     Yellow     12     35     28
	J.Troll     07/99     4842     Brown-3     12     26     26
	L.Tansley     05/99     4712     Brown-2     12     30     28

	awk '{print $0}' grade.txt	//输出整个文件.使用$0输出整个文件
	awk '{print $1, $4}' grade.txt	//输出第1列和第4列.中间的,表示以空格分开;如果是"\t"是使用tab分开
	awk 'BEGIN {print "Name     Defy\n------------------------"}
	> {print $1 "\t" $4}' grade.txt
	/*BEGIN表示表头,会输出Name     Defy; \n表示换行*/

**实例2---与正则表达式结合**

	/*输出$4中包含Brown的所有整行*/
	awk '$4 ~/Brown/ {print $0}' grade.txt
	/*输出$3中等于48的所有整行*/
	awk '$3== "48" {print $0}' grade.txt	//试过48不带""也是可以的
	/*不包括*/
	awk '$4 !~ /Brown/ {print $0}' grade.txt
	/*不等于*/
	awk '$4 != "Brown-2" {print $0}' grade.txt

**实例3---padding脚本**

	#!/bin/bash
	file_size = `ls -l $1 | awk '{print $5}'`	
	#"``"在键盘1的左边.	$1:表示需要padding的脚本.		$5表示文件的大小
	echo $file_size		#打印出文件大小
	residual_size = `expr $file_size % 16`	#%取余16
	echo $residual_size
	padding_size = `expr 16 - $residual_size`	#需要padding的大小
	echo $padding_size
	if [ $padding_size -eq 16]; then		#表示residual为0,不需要padding
		echo No need to padding!
	else
		for(i = 0; i < padding_size; i++); do
			print '\xff' >> $1	#输出一个"\xff"十六进制的ff到文件结尾
			echo padding $i byte	#输出padding了多少次
		done
	fi

**实例4---"-F"参数指定分隔符**

	pwd
	//得到"/zhsa122/usrhome/defy.chen/repository/Riscure/buildroot_Riscure/output/build"
	
	pwd | awk -F/ '{print $0}'	//原样打印路径(和pwd相同)
	pwd | awk -F/ '{print $1}	//指定分隔符为"/".结果为空.因为第一个参数为空
	pwd | awk -F/ '{print $2}'	//得到"zhsa122".第二个参数

## 20.type命令

type:用来显示指定命令的类型.

	type ls
	//ls is aliased to `ls --color=auto':表示为一个"命令别名"
	type gcc
	//gcc is /usr/local/gcc-4.9.1/bin/gcc:指示命令的路径
	type -p gcc		//只显示路径(path)
	///usr/local/gcc-4.9.1/bin/gcc

## 21.echo命令

	//echo等追加到文件末尾
	1.覆盖	echo "..." > filename
	2.追加	echo "..." >> filename

## 13. wget命令