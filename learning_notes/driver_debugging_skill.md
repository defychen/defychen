# driver debugging skill
***
## Q1:driver中的dev_dbg信息的打印：
	
	dev_dbg(s->dsc->dev, "%s\n", __func__);	//打印函数名
**step1: linux端打开dynamic debug:**
	
	buildroot/make linux-menuconfig/kernel hacking/prink and dmesg options/Enable dynamic printk() support

**step2: 板子端:**

*1)启动之后清除dmesg:*

	dmesg -c > /dev/null		//清除其他的dmesg，便于查看

*2)如果文件系统不为read-only，可:*
	
	mkdir /dev/debugfs -p	//建立一个用于存放debug文件的地方

*否则直接使用"/sys/kernel/debug"目录.*

**3)挂载:**

	mount -t debugfs none /dev/debugfs
	或:mount -t debugfs none /sys/kernel/debug

**4)重定向debug信息:**

	echo -n "file ca_dsc_ioctl.c +p" > /dev/debugfs/dynamic_debug/control	//file为某个文件
	或:echo -n "func dsc_fetch_subdevice +p" > /sys/kernel/debug/dynamic_debug/control	//func为具体的某个函数

**5)dmesg显示调试信息.**
***
## Q2:"字节对齐"/"2字节对齐"/"4字节对齐"/"8字节对齐":

**1)字节对齐:内存默认即为字节对齐,即内存地址默认为"+1"递增.**

**2)2字节对齐:内存地址需要"+2"递增,判断方法:**
	
	#define 2BYTE_ALIGN 1
	addr & 2BYTE_ALIGN	//2字节对齐时,递增为"10 100 110 1000",最低位必须为0,因此只需要对最低位进行判断即可.

**3)4字节对齐:内存地址需要"+4"递增,判断方法:**

	#define 4BYTE_ALIGN 3
	addr & 4BYTE_ALIGN	//4字节对齐时,递增为"100 1000 1100 10000",最低2位必须为0,因此需要对最低2位进行判断.

**4)8字节对齐:内存地址需要"+8"递增,判断方法:**

	#define 4BYTE_ALIGN 7
	addr & 4BYTE_ALIGN	//8字节对齐时,递增为"1000 10000 11000 100000",最低3位必须为0,因此需要对最低3位进行判断.
***
## Q3:Warning clean时出现的种种warning清除方法：

**1)warning:implicit declaration of function 'xxx' [-Wimplicit-function-declaration]：**
	
*函数'xxx'在.c文件中定义了，但是没有在与之关联的.h文件中声明.	//makefile在make时是直接找.o文件，.h文件会忽略，因为只是warning.*
	
	1.在头文件中增加对该函数的声明；	//针对引用的函数出现warning较多的情况
	2.在引用该函数的文件头部使用extern声明该函数 e.g. extern UINT32 dsc_see_read_otp(UINT32 addr);	
	//这种情况针对文件中引用未声明函数不多的情况.

**2)warning:'asa_hal_illegal_fun1' defined but not used [-Wunused-function]:**

*该函数正常情况下未使用，但是必须保留，可以使用下面的方法进行相关的声明:*

	static __attribute__((unused)) void cf_illegal_fun1(void)	//__attribute__((unused))加在函数的实现中已经验证可行,加
	在声明中不知是否可行?
	__attribute__((unused)) UINT32 x = 0;	//声明可能不用的变量
	

