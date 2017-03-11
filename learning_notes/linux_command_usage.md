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
	sed '1c Hi' ab.txt	//第一行代替为"Hi"
	sed -n '/defy/p' ab.txt | sed 's/defy/bird/g' 
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
	
	tar -xvzf filename.tar.gz	/*x:解压;v:列车解压出来的文件;z:gz格式;f:后面接文件名*/
	tar -xvjf filename.tar.bz2	/*x:解压;v:列车解压出来的文件;j:bz2格式;f:后面接文件名*/

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

