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
