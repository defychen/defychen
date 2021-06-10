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
	sed -i '/CONFIG_POSIX_MQUEUE/c CONFIG_POSIX_MQUEUE=y' board/ali/c3922-demo/linux-m3755-
	demo-new-kernel.config

## 2.dd命令

### 2.1 dd命令详解

dd命令用于将原始块写入到目标块.

**1.命令解析**

	dd if=/dev/zero bs=1024 count=1000000 of=/root/1Gb.file
	/*
		if:输入文件名./dev/zero:无限输入设备,该设备可以无穷尽的输出0;
		bs:block size,块大小(此处为1024B);
		count:块的数量(此处为1000000,近似1M);
		of:输出文件名,写入的目标块(此处为写成一个1Gb.file的块文件).
	*/

**2.实例---用dd命令测试硬盘的最佳块大小**

	dd if=/dev/zero bs=1024 count=1000000 of=/root/1Gb.file
		//测试以1024块大小写入1Gb文件的速度.执行的时候会显示一个速度
	dd if=/dev/zero bs=2048 count=500000 of=/root/1Gb.file
		//测试以2048块大小写入1Gb文件的速度.执行的时候会显示一个速度
	dd if=/dev/zero bs=4096 count=250000 of=/root/1Gb.file
		//测试以4096块大小写入1Gb文件的速度.执行的时候会显示一个速度
	dd if=/dev/zero bs=8192 count=125000 of=/root/1Gb.file
		//测试以8192块大小写入1Gb文件的速度.执行的时候会显示一个速度
	最终通过比较速度,可以得到最佳块大小.

### 2.2 将特定的文件目录烧写到特定的块

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

### 2.3 dd与cp的区别

	1.dd用于对块进行操作,cp则是对文件进行操作;
	2.dd是将原始数据按照数据源的格式原封不动的拷贝到目的地,cp则是将文件和目录拷贝到目的地后按照目的地的
		格式排列新数据.因此在块的启动文件内容,只能用dd,不能用cp.

## 3. tree命令

### 3.1 tree命令

以树状图列出目录的内容,主要用于查看目录结构

**常用的为(更多可以man tree或info tree):**

	tree -L 1/2/3 -d /*显示当前目录下的1/2/3级目录*/
	tree -a /*显示所有文件和目录，对于文件和目录较少可以使用*/

### 3.2 pstree命令

在ubuntu上运行pstree,可以查看进程树.

	pstree	//查看进程树
	init ----------NetworkManger --------dhclient	//init进程,系统的第一个进程.
		...

## 4.uname命令

	uname -r //显示操作系统的发型版本号(e.g.3.2.0-23-generic)
	uname -s //显示系统名(e.g. Linux或者CYGWIN_NI-6.1-WOW64)

## 5.zip命令

GNU zip---gzip(gz)和bzip2(bz2)两种压缩格式，压缩比:gzip>bzip2

1.tar和gzip/bzip2的区别

	1.tar:主要是用于打包,将一堆文件或目录变成一个总的文件;
	2.gzip/bzip2:用于压缩,将一个大的文件经过某种压缩算法变成一个小文件.
	// tar打包后一般会调用gzip/bzip2进行压缩,生成tar.gz/tar.bz2.

	gunzip:将命令行中以.gz/-gz/.z/-z/_z/.Z结尾并具有正确标志头的文件进行解压缩,并以去掉扩展名的解压缩
		文件替换原我呢见.

2.解压方法
	
	1.tar.gz压缩包解压:
	tar -xvzf filename.tar.gz	/*x:解压;v:列出解压出来的文件;z:gz格式;f:后面接文件名*/
	tar -xvzf filename.tar.gz -C directory	//解压到某目录
	2.bz2压缩包解压:
	tar -xvjf filename.tar.bz2	/*x:解压;v:列出解压出来的文件;j:bz2格式;f:后面接文件名*/
	tar -xvjf filename.tar.bz2	//解压到某目录
	3.tar.xz压缩包解压:
	tar -xvJf qemu-2.8.0.tar.xz	/*x:解压;v:列出解压出来的文件;J:xz格式;f:后面接文件名*/
	tar -xvJf qemu-2.8.0.tar.xz //解压打某目录
	4.*.zip压缩包解压:
	unzip -d sourceInsight_downcc.zip ./		//解压*.zip文件到当前目录下
		帮助方法:unzip --help
	5.tar.zst压缩包解压:
	tar -I zstd -xvf archive.tar.zst
	/*
		扩展名.zst表示存档由zstd压缩.
		此处"-I"选项指定压缩/解压缩的格式.
	*/

3.创建压缩包的方法

	tar -cvz/j/Jf 要创建的压缩包名(filename.tar.gz/bz2/xz) 包含的文件名
	1.创建tar.gz压缩包:
	tar -cvzf test.tar.gz ./test/	/*将test所有文件创建成为一个test.tar.gz的压缩包*/
	2.创建tar.bz2压缩包:
	tar -cvjf test.tar.bz2 ./test/	/*将test所有文件创建成为一个test.tar.bz2的压缩包*/
	3.创建tar.xz压缩包:
	tar -cvJf test.tar.xz ./test/	/*将test所有文件创建成为一个test.tar.xz的压缩包*/
	4.创建*.zip压缩包:
	zip test.zip test.jpng test.png	/*将test.png和test.jpg创建成为一个test.zip压缩包*/
	zip -q -r data.zip /home/data	//将/home/data下面的所有的文件打包压缩到data.zip
		// -q:不显示指令执行过程; -r:递归处理

## 6.重定向

"<"标准输入; "1>"标准输出; "2>"错误输出(包括warning)

	/*将标准输出到normal_output.txt;错误输出到warning.txt*/
	make 1> ../../../normal_output.txt 2> ../../../warning.txt
	make > ../../../see.txt 2>&1	/*">"等同于"1>",将标准输出和错误输出都输出到see.txt*/

## 7.cp命令

1.cp复制文件夹

	cp -r source_file dest_file 

2.cp同时复制".c和.h"文件

	cp -f dir/*.[ch] tgt_dir/	//*.[ch]:匹配.c和.h文件

3.cp -i--->interactive prompt before overwrite(写之前有提示)

	//当执行alias(查看别名)出现"alias cp='cp -i'",此时执行cp -rf不会强制覆盖,会出现提示,
		解决方法(暂时去掉提示)
	\cp -rf src dst	//cp前加上"\"


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

**重定向**

	1)将标准输出和标准错误输出分别重定向到不同的文件中:
		kill -HUP 1234 1> killout.txt 2> killerr.txt
			//将标准输出重定向到killout.txt;将标准错误输出重定向到killerr.txt
		make 1> ok.txt 2> err.txt
			//编译时的标准输出重定向到ok.txt文件;标准错误重定向到err.txt文件.
	2)将标准输出和标准错误输出重定向到同一个文件:
		kill -l 1234 > killouterr.txt 2>&1
			//2--标准错误; >--冲定向; &1--和1(标准输出一样)

**管道**

	ls -l | head -n 5		//显示ls -l的前5行
	grep linux . -nr | more		//按页显示查找到的字符串,没有grep linux . -nr好看

**grep -i**

针对单个字符不区分大小写

	OS := $(shell uname -s) //uname -s:获得系统名
	IS_LINUX := $(shell echo $(OS) | grep -i linux) //不区分大小写
	IS_CYGWIN := $(shell echo $(OS) | grep -i cygwin)
	
	ifdef  IS_LINUX //找到linux字符会等于1
	_LINUX_COM_ENV_ = 1
	else
	ifdef IS_CYGWIN 
	_CYGWIN_COM_ENV_ = 1
	endif
	endif

## 16. which命令

	which命令用于查找并显示给定命令的绝对路径.
	which ls	//显示为"/bin/ls"

## 17. ln命令

	1.建立文件的软链接
	ln -s test.sh test	//-s为建立一个软连接.test.sh:链接的目标的文件, test:新建的链接文件
	ls -l
	/*得到:
	lrwxrwxrwx 1 defy.chen defy.chen    7 Sep  4 20:27 test -> test.sh*
	-rwxrwxr-x 1 defy.chen defy.chen  328 Sep  4 20:04 test.sh*	//目标文件
	*/
	2.建立一个目录的软链接
	source directory:target_file --->需要连接的目标目录
	software link: link_file --->软链接目录(相当于windows下的快捷方式).
	ln -s target_file link_file		
	/*
	注意点:
		1.link(创建的软链接)一定不能提前创建,只需要在"ln -s"指定一个需要的名字即可.
		2.target_file和link_file后面绝对不能有"/"
	*/
	PS:这种方式可以很方便的用于source insight,当更新代码不需要重新更新整个文件夹.

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

## 22.source命令

**source filepath或. filepath(两个一样的功能)**

使当前shell读入路径为filepath的shell文件并依次执行文件中的所有语句,通常用于重新执行刚修改的初始化文件,使之立即生效,而不必注销重新登录.后面的脚本(shell/Makefile等)就可以读取到刚修改过的初始化文件.

	/*test.sh脚本*/
	#!/bin/bash
	A=1
	chmod +x testh.sh
	1)执行./test.sh或sh test.sh-->echo $A-->显示为空,因为A=1并未回传给当前的shell
	2)执行source test.sh或. test.sh-->echo $A-->会显示为1,此时A=1的变量在当前的shell中.	

## 23.ar命令

ar(archive)命令,归档.通常用于将多个目标文件.o进行归档,形成静态库.a文件.静态库.a文件其实就是多个目标文件的集合.

	1.归档,生成静态库
	ar -rcs test.a *.o //将本目录下的所有.o文件归档形成test.a(静态库)
	/*
		-r:在库中替换模块,当插入的模块已经在库中存在,则直接替换同名的模块;
		-c:创建一个库,不管库是否存在,都将创建;
		-s:创建目标文件索引,在创建较大的库时能加快时间.如果不需要创建索引,可以改成-S参数.
	*/
	2.查看静态库中有哪些目标文件(.o)
	ar -vt test.a //显示test.a库中包含的目标文件
	3.将静态库中的目标文件取(解压出来),放在当前目录下
	ar -x test.a //解压静态库

## 24.mips-sde-elf-gcc编译器的编译选项

	linux下使用"gcc -v --help"得到mips的部分的帮助信息(某些没有)
	-EL		Generate little-endian code(采用小端格式). --->一般mips会采用"-EL",mips为小端格式.
	-EB		Generate big-endian code(采用大端格式).
	-mips32r2	Equivalent to -march=mips32r2(等同于"-march=mips32r2"). --->mips的编译器会有这个选项.
			-march=mips32r2:表示mips采用的架构(MIPS ISA:mips的指令集架构).目前的mips的ISA有:
			mips1, mips2, mips3, mips4, mips32, mips32r2, mips64.
	-mdsp	Use revision 1 of the MIPS DSP ASE(使用MIPS DSP ASE第一个修订版本).
	-msoft-float  Do not use floating-point coprocessor instructions. Implement floating-point
			calculations using library calls instead.
			--->不使用浮点协处理器指令,而是通过调用库函数来实现浮点.
	-g		Generate debug information in default format. --->在编译的时候,产生调试信息.
	-O0/O1/O2/O3		Set optimization level to <number>. --->一般设置为"-O1"
					--->设置优化选项级别.-O0表示没有优化; -O1表示缺省值; -O3优先级别最高.
	-Wall	Enable most warning messages. --->显示所有警告信息
	-Wstrict-prototypes		Warn about unprototyped function declarations. --->非函数原型出现警告
			int test(); //函数声明不是一个原型.
			//应该声明为: int test(void);
	-fsigned-char	Make "char" signed by default. --->将char类型设置为signed char
	-fno-builtin-printf		Don't recognize built-in functions that do not begin
			with _builtin_ as prefix. --->printf不会称为built-in函数.避免下断点或调用时出问题.
	-fstack-protector	Use propolice as a stack protection method. --->栈保护,防止栈溢出
	-fstack-protector-all	Use a atack protection method for every function
			--->对所有的函数进行栈保护,防止栈溢出.
	-D		produce assembler debugging messages. --->产生汇编调试信息
	-D<macro>[=<val>]	Define a <macro> with <val> as its value. If just <macro> is given,
			<val> is taken to be 1.
			--->定义一个宏并取后面的val作为宏的值.如果仅仅只是定义宏,该宏取值为1.
	-I<dir>	Add <dir> to the end of the main include path. --->增加头文件的目录<dir>
	-MD		Generate make dependencies and compile.
			--->生成文件的依赖关系文件(存放编译依赖信息.e.g.test.o: test.c test.h).
				依赖文件名为"-o"指定的文件,并添加".d"后缀.若没有指定,则输入的文件作为依赖文件名,
				并添加".d"后缀,同时继续进行后续的编译.
	-MP		Generate phony targets for all headers.
			--->依赖规则中的所有.h依赖项都会生成一个伪目标,该伪目标不依赖其他任何依赖项.该伪目标
			规则可以避免删除了对应的头文件而没有更新"Makefile"匹配新的依赖关系而导致make出错的情况.
	-MMD	Like -MD but ignore system header files.
			--->类似"-MD",忽略系统头文件.
	-shared Create a shared library
			--->创建共享库(即.so).
	-fPIC	作用域编译阶段(PIC:position independent code),告诉编译器产生与位置无关代码,一般配合
		-shared一起使用,生成.so共享库

**查看对应gcc的版本**

	./mips-sde-elf-gcc -v/--version
	/*显示结果如下:
	xxx
	gcc version 4.3.3 (Sourcery G++ Lite 4.3-221) //版本为4.3.3
	*/

## 25.mips-sde-elf-ld链接器的链接选项

	-s, --strip-all		Strip all symbols. --->去掉所有的符号表(strip:剥夺).一般在链接中使用
	-n, --nmagic			Do not page align data. --->不做页面对齐数据.一般在链接中使用
	-LDIRECTORY, --libraray-path DIRECTORY		Add DIRECTORY to libraray search path.
			--->增加库搜索的目录.
	-l LIBNAME, --libraray LIBNAME	Search for libraray LIBNAME. --->搜索某个lib库
		-lm	--->搜索libm,即数序库
		-lc --->是libc,即C库.
		-lpthread --->是libpthread,即线程库
		-lgcc --->是libgcc,即gcc库.
		PS:linux的库命名为"libxxx.so","libxxx.a"或"libxxx.la".链接时用"-lxxx",去掉lib和后面的".so".

## 26.mips-sde-elf-objdump反汇编工具的使用

	-D, --disassemble-all	Display assembler contents of all sections
			--->显示整个文件的汇编结果
	-d, --disassemble		Display assembler contents of executable sections
			--->显示可执行部分的汇编结果
	-h						Display the contents of the section headers
			--->显示头文件部分的结果
	-a, --archive-headers	Display archive header information
			--->显示库头文件信息
	-b, --target=BFDNAME	Specify the target object format as BFDNAME
			--->指定等待反汇编文件的格式(e.g. -b binary ->指定反汇编文件的格式为binary)
	-m, --architecture=MACHINE	Specify the target as MACHINE
			--->执行等待反汇编文件的架构(e.g. -m mips或者--architecture=mips)
	-t, --syms Display the contents of the symbol table(s)
			--->显示符号表信息
	//用于:
		dir/mips-sde-elf-objdump -D -b binary --architecture=mips source.abs > target.dis
		//将source.abs文件反汇编成target.dis.此处为反汇编二进制,默认的.out文件不需要--architecture参数.

## 27.ls命令选项

	-i, --node	print the index number of each file. --->得到每个文件的索引数
		建立的软链接可以使用"ls -il"来查看链接的目标
	-lh --->以human显示,会以Byte显示文件大小

### 27.1 统计当前目录下含有的文件数(包括子文件夹)

	ls -lR | grep "^-" | wc -l
	/*
		ls -lR:列出当前目录下所有的文件(包括字目录下的),也包括目录;
		grep "^-":搜索以"-"开头的文件(-在ls列出来的表示文件),即为搜出文件,过滤掉目录;
		wc -l:统计行数并显示.
	*/

### 27.2 统计当前目录下的目录个数(包括子文件夹)

	ls -lR | grep "^d" | wc -l
	/*
		ls -lR:列出当前目录下所有的文件(包括字目录下的),也包括目录;
		grep "^d":搜索以"d"开头的文件(d在ls列出来的表示目录),即为搜出目录,过滤掉文件;
		wc -l:统计行数并显示.
	*/

## 28.rm命令选项

	-f, --force		ignore nonexistent files, never prompt. --->忽略不存在的文件,强制删除
	-r, -R, --recursive	remove directories and their contents recursively.
					--->递归的删除目录和文件
	//删除软链接
	rm -rf soft_link		//没有"/",这个是删除软链接
	rm -rf soft_link/	//加了个"/",这个是删除文件夹

## 29.sudo su root账号切换(root用户和普通用户切换)

当忘记root密码时,用户修改root密码方法:

**方法1:用户具有sudo权限**

如果用户具有sudo权限,则运行:

	1.执行:sudo su root
	//然后输入当前用户的密码
	2.进入到root账户,执行:passwd	//修改root密码
	//输入两次新的root密码.

	PS:用户账户切换
	su //切换到root用户,需要输入root密码
	su defychen	//切换到defychen用户
	PS:在root账户下,输入exit可以快速退出到普通用户.

**方法2:用户不具有sudo权限**

略.

## 30. apt-get

apt-get(Advanced Package Tool:高级安装工具):linux上的软件包管理器.用于自动从互联网的软件仓库中搜索、安装、升级、卸载软件.

	//apt-get命令一般需要root权限执行,因此一般跟着sudo命令.
	sudo apt-get install  gcc-arm-linux-gnueabi	//安装交叉编译工具链
	sudo apt-get update	//更新源
	sudo apt-get upgrade  	//更新已经安装的包
	sudo apt-get remove gcc-arm-linux-gnueabi //卸载安装的交叉编译工具链

## 31. shutdown命令

	shutdown -h now		//马上关机
	shutdown -h 20:30	//20:30准时关机
	shutdown -r now		//马上重启
	shutdown -r 20:30	//20:30准时重启

## 32. /dev/null和/dev/zero的区别

### 32.1 /dev/null

/dev/null:是一个无底洞,可以向该设备输出任何数据,所有写入的内容永远丢失,读是什么也读不到;

	1.禁止标准输出:
		cat $filename > /dev/null	//将cat的标准输出到/dev/null
	2.禁止标准错误输出:
		rm $badname 2> /dev/null	//将不存在文件删除出现的错误输出到/dev/null
	3.禁止标准输出和错误输出:
		cat $filename &> /dev/null	//将标准输出和错误输出都输出到/dev/null

### 32.2 /dev/zero

/dev/zero:是一个伪文件,不断产生null的流(二进制空流).写入数据会直接丢失.主要用于创建一个指定长度的空间.

	dd if=/dev/zero of=/dev/1Gb.file bs=1024 count=1000000
	//创建一个1Gb的文件,文件内容全为二进制空流(0).

## 33. readelf

1.readelf -h

读取可执行文件的elf文件头信息

	readelf -h hello/hello.o/hello.so/hello.a/hello.debug
	读出来之后,可以看到"Type"会不一样:
		hello--->DYN(共享目标文件)
		hello.o--->REL(可重定位文件)
		hello.so--->DYN(共享目标文件)
		hello.a--->REL(可重定位文件)
		hello.debug--->DYN(共享目标文件)

2.readelf -l

显示程序头(段头)信息,没有就不显示.

	readelf -l hello/hello.o/hello.so/hello.a/hello.debug
	读出来之后,可以看到"Type"会不一样:
		hello--->有程序头信息
		hello.o--->无程序头信息
		hello.so--->有程序头信息
		hello.a--->无程序头信息
		hello.debug--->有程序头信息

3.readelf -s

Display the symbol table(显示符号表信息).

	readelf -s xxx.so	//显示xxx.so的符号表信息

## 34. rename

rename常用于批量修改文件名.

### 34.1 批量添加文件扩展名

	$ ls
		1 2 3 4
	$ rename 's/$/.txt' *
	$ ls
		1.txt 2.txt 3.txt 4.txt

### 34.2 批量更改文件扩展名

	$ ls
		1.txt 2.txt 3.txt 4.txt
	$ rename 's/\.txt/\.cc/' *
	$ ls
		1.cc 2.cc 3.cc 4.cc

### 34.3 批量删除文件扩展名

	$ ls
		1.txt 2.txt 3.txt 4.txt
	$ rename 's/\.txt//' *
	$ ls
		1 2 3 4

## 35. grep

### 35.1 grep -i

针对单个字符不区分大小写

	OS := $(shell uname -s) //uname -s:获得系统名
	IS_LINUX := $(shell echo $(OS) | grep -i linux) //不区分大小写
	IS_CYGWIN := $(shell echo $(OS) | grep -i cygwin)

grep时排除指定的文件

	grep "xxx" . -nr --exclude-from=file_name

grep时排除指定的目录

	grep "xxx" . -nr --exclude-dir=dir
	e.g. grep "xxx" . -nr --exclude-dir=.svn	//排除.svn目录搜索字符

### 35.2 grep -E

-E:表示扩展的正则表达式.可用于搜索满足任意关键字或同时满足多个关键字.

**1.满足任意关键字的搜索**

	grep -E "word1|word2|word3" file.txt -nr
	/*
		在文件file.txt中搜索带有word1/word2或word3关键字的行.
		word1|word2|word3:竖线隔开,且不能有空格;
		file.txt:必须指定文件名.
	*/

**2.同时满足多个关键字的搜索**

	grep word1 file.txt | grep word2 | grep word3
	/*
		在文件file.txt中搜索同时带有word1、word2和word3关键字的行.
	*/
	PS:更多使用的是:
		grep "word1.*word2.*word3" file.txt -nr

### 25.3 grep -w

精确匹配.

	//批量删除linux进程
	ps | grep -w "xxx" | awk '{print $1}' | xargs kill -9
	/*
		"xxx":为匹配的字符串
		$1:为进程ID位于匹配后字符串的位置.
	*/

### 25.4 zgrep

zgrep用于查看压缩文件(以tar.gz结尾的文件).

	zgrep "xxxx" yyy.tar.gz -nr	//像grep一样使用即可.

## 36. find命令

	find . -name "april*"
		//在当前目录下查找以april开头的文件
	find . -name "april*" fprint file
		//在当前目录下查找以april开头的文件,并将结果输出到file
	find . -name "ap*" -o -name "may"
		//在当前目录下查找以ap或may开头的文件
	find . -name "tom.txt" -ftype vfat
		//在当前目录下查找名称为"tom.txt"且文件类型为vfat的文件
	find . -name "tom.txt" ! -ftype vfat
		//在当前目录下查找名称为"tom.txt"且文件类型不为vfat的文件
	find . -name "wa*" -type l
		//在当前目录下查找名称为"wa"开头且类型为符号链接的文件
	find /home -empty
		//在home目录下查找大小为0的文件或空目录
	find /home -size +512k
		//在home目录下查找大于512KB的文件
	find /home -size -512k
		//在home目录下查找小于512KB的文件
	find /home -user fred
		//在home目录下查找属于fred这个用户的文件

统计代码量

	find . -name "*.cpp" | xargs wc -l	//统计.cpp的代码量
	find . -name "*.h" | xargs wc -l	//统计.h的代码量

## 37. "./configure --prefix=path"软件安装的路径指定

一般安装软件时会将软件安装到默认的路径(一般为类似/usr/bin路径),如果需要安装到指定路径,方法如下:

	tar -xvzf libffi-3.0.0.tar.gz
	cd libffi-3.0.0
	./configure --prefix=/home/defychen/software
		//"./configure --prefix":在配置的时候指定安装的路径
	make -j12
	make install

## 38. hostname

hostname命令用于显示和设置系统的主机名称.

### 38.1 显示主机名称

	hostname	//结果为:主机名称
	uname		//等价于hostname

### 38.2 查看主机ip地址

	hostname -i		//得到虚拟机ip地址:127.0.0.1,没有虚拟机则是系统的ip地址
	hostname -I		//得到主机ip地址,与ifconfig等价

## 39. numactl命令

查看系统的numa状态.

### 39.1 安装

linux默认是不安装numactl命令,安装方法如下(ubuntu):

	sudo apt install numactl

### 39.2 查看系统numa状态

	numactl --hardware

### 39.3 运行结果解析

	available: 2 nodes (0-1)	//表示2个node
	node 0 cpus: 0 1 2 3 4 5 6 7 16 17 18 19 20 21 22 23	//每个node 16个CPU
	node 0 size: 131037 MB		//每个node占有128GB内存(131037 / 1024 ≈ 128)
	node 0 free: 3019 MB
	node 1 cpus: 8 9 10 11 12 13 14 15 24 25 26 27 28 29 30 31
	node 1 size: 131071 MB
	node 1 free: 9799 MB
	node distances:
	node 0 1
	 0: 10 20
	 1: 20 10

## 40. lspci

lspci用于查看系统中拥有的pci设备,执行后结果如下.

	00:00.0 Host bridge: Intel Corporation 82845 845 (Brookdale) Chipset Host Bridge (rev 04)
	00:01.0 PCI bridge: Intel Corporation 82845 845 (Brookdale) Chipset AGP Bridge(rev 04)
	00:1d.0 USB Controller: Intel Corporation 82801CA/CAM USB (Hub #1) (rev 02)
	00:1d.1 USB Controller: Intel Corporation 82801CA/CAM USB (Hub #2) (rev 02)
	00:1e.0 PCI bridge: Intel Corporation 82801 Mobile PCI Bridge (rev 42)
	00:1f.0 ISA bridge: Intel Corporation 82801CAM ISA Bridge (LPC) (rev 02)
	00:1f.1 IDE interface: Intel Corporation 82801CAM IDE U100 (rev 02)
	00:1f.3 SMBus: Intel Corporation 82801CA/CAM SMBus Controller (rev 02)
	00:1f.5 Multimedia audio controller:Intel Corporation 82801CA/CAM AC'97 Audio Controller (rev 02)
	00:1f.6 Modem: Intel Corporation 82801CA/CAM AC'97 Modem Controller (rev 02)
	01:00.0 VGA compatible controller: nVidia Corporation NV17 [GeForce4 420 Go](rev a3)
	02:00.0 FireWire (IEEE 1394): VIA Technologies, Inc. IEEE 1394 Host Controller(rev 46)
	02:01.0 Ethernet controller: Realtek Semiconductor Co., Ltd. RTL-8139/8139C/8139C+(rev 10)
	02:04.0 CardBus bridge: O2 Micro, Inc. OZ6933 Cardbus Controller (rev 01)
	02:04.1 CardBus bridge: O2 Micro, Inc. OZ6933 Cardbus Controller (rev 01)

lspci命令输出(格式为XX:YY.Z)解析如下:

	XX:PCI bus number. A PCI domain can host up to 256 buses;
	YY:PCI device number. Each bus can connect to a maximum of 32 PCI devices;
	Z:Function number. Each device implement up to 8 functions.

## 41. lscpu

查看cpu信息.lscpu从sysfs和/proc/cpuinfo中收集CPU体系结构信息.

## 42. chgrp和chown

### 42.1 chgrp(change group)--->改变文件所属用户组

	sudo chgrp -R defychen file	//如果文件file属于root组,需要切换为普通用户组,可以执行sudo chgrp.
	//-R:表示递归.此处为将属于root组的file改变为属于defychen用户组.

### 42.2 chown(change owner)--->改变文件拥有者

	sudo chown -R defychen file	//如果文件file拥有者属于root组,需要切换为普通用户,可以执行sudo chown.
	//-R:表示递归.此处为将属于root的file改变为属于defychen用户.

## 43 dmidecode命令

dmidecode命令可以获取有关硬件方面的信息.dmidecode是将DMI数据库中的信息解码,以可读的文本方式显示.

### 43.1 直接查看厂商信息

	dmidecode -s system-product-name //查看当前linux是跑在虚拟机还是物理机上
	/*
		1.显示为"VMware Virtual Platform"--->VMWare Workstation虚拟机;
		2.显示为"VirtualBox"--->VirtualBox虚拟机;
		3.显示为"KVM"--->Qemu with KVM虚拟机;
		4.显示为"Bochs"--->Qemu(emulated)虚拟机;
		5.显示为"HVM domU"--->Intel的Xen虚拟机;
		6.显示为"D06"--->华为kunpeng物理机;
		7.显示为"R282-Z90-00"--->GIGABYTE主板,物理机.
	*/

### 43.2 查看整个系统信息(信息更详细)

	dmidecode -t system

## 44 strip命令

	strip -s	// Remove all symbol and relocation information
		--->移除所有的符号表及重定位信息,对于.a文件(静态库)在链接时会出错
	strip -x	// Remove all non-global symbols
		--->移除所有非global的符号表,在release软件时可以对.so这样操作
	strip -K	// Do not strip symbol
		--->保留指定的符号表,这样做会导致构建脚本与代码间的耦合性更强,不推荐这样做.

## 13. wget命令