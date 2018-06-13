# driver debugging skill
***
## Q1:driver中的dev_dbg信息的打印：
	
	dev_dbg(s->dsc->dev, "%s\n", __func__);	//打印函数名

**step1: linux端打开dynamic debug:**
	
	buildroot/make linux-menuconfig/kernel hacking/prink and dmesg options/Enable dynamic printk() support

**step2: 板子端:**

1)启动之后清除dmesg:

	dmesg -c > /dev/null		//清除其他的dmesg，便于查看

2)如果文件系统不为read-only，可:
	
	mkdir /dev/debugfs -p	//建立一个用于存放debug文件的地方

否则直接使用"/sys/kernel/debug"目录.

**step3)挂载:**

	mount -t debugfs none /dev/debugfs
	或:mount -t debugfs none /sys/kernel/debug

**4)重定向debug信息:**

	echo -n "file ca_dsc_ioctl.c +p" > /dev/debugfs/dynamic_debug/control	//file为某个文件
	echo -n "module alidsc +p" > /dev/debugfs/dynamic_debug/control			//module为整个dsc模块
	或:echo -n "func dsc_fetch_subdevice +p" > /sys/kernel/debug/dynamic_debug/control	//func为具体的某个函数
	echo -n "module alikl +p" > /dev/debugfs/dynamic_debug/control
	//PS:模块好像有点打印不出来(e.g.aliteeclient没有打印出来过)

**5)dmesg显示调试信息.**

**dev_xxx函数:---用法都是一样的.**

	dev_info():启动过程或者模块加载/卸载过程中的"通知类消息"等,一般只会通知一次.(常用在probe()、remove等函数)
	dev_dbg():使用在普通错误中,如-EINVAL、-ENOMEN等errno发生处,用于调试
	dev_err():使用在严重错误中,如用户无法获得errno或者程序员不容易猜测系统哪里出了问题的地方

**例子:**

	struct ca_dsc_dev {
		...
		struct device *dev;
		...
	};

	struct ca_dsc_session{
		struct ca_dsc_dev *dsc;
		...
	};

	struct ca_dsc_session *s = file->private_data;

	dev_dbg(s->dsc->dev, "%s\n", __func__);
	/*para1:struct device的指针; para2:其他的信息.  (para1和para2之间用","隔开)*/

**dev_dbg在driver probe中是没有效果的,因为此时dynamic printk还不起作用.在probe中应该使用dev_info(通知消息)、dev_err(错误消息).**

**6)调整printk打印等级:**

	//查看打印等级
	cat /proc/sys/kernel/printk		//显示为:7       4       1       7.第一个数字"7"表示等级为7.
	echo 15 > /proc/sys/kernel/printk		//调整等级为"15"

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
	
	1)在头文件中增加对该函数的声明；	//针对引用的函数出现warning较多的情况
	2)在引用该函数的文件头部使用extern声明该函数 e.g. extern UINT32 dsc_see_read_otp(UINT32 addr);	
	//这种情况针对文件中引用未声明函数不多的情况.

**2)warning:'asa_hal_illegal_fun1' defined but not used [-Wunused-function]:**

*该函数正常情况下未使用，但是必须保留，可以使用下面的方法进行相关的声明:*

	static __attribute__((unused)) void cf_illegal_fun1(void)	//__attribute__((unused))加在函数的实现中已经验证可行,
	加在声明中不知是否可行?
	__attribute__((unused)) UINT32 x = 0;	//声明可能不用的变量

**3)warning:passing argument 1 of 'dev_alloc' discards qualifiers from pointer target type**

	"dev_alloc"函数第一个参数的传递,丢弃了指针目标类型的限定(qualifiers:资格,合格)
	处理:
	将"dev_alloc"第一个参数定义中的"const"去掉

## Q4:Conax VSC项目不支持KL gen key

**Conax VSC项目直接在see调用我们KL接口，因此在main调用会直接返回:ALI_CRYPTO_ERROR_OPERATION_NOT_SUPPORTED**

	RET_CODE ce_key_load_rpc(CE_DEVICE *pcedev, OTP_PARAM *pce_otp_info)
	{
		#ifdef _CAS9_VSC_API_ENABLE_	
		/*需要在./C_Support/secure_coding/Elephant/prj/app/demo/combo/sabbat_dual_CAS9_CA_ENABLE_/
			how_to_compile_3505_dual cpu.txt文件中打开宏"_CAS9_VSC_API_ENABLE_"*/
			//CNX SEE Code Hardening, this API returns failed when called from MAIN.
			return ALI_CRYPTO_ERROR_OPERATION_NOT_SUPPORTED;
		#else
			return ce_key_load(pcedev, pce_otp_info);
		#endif
	}

## Q5:C3921和S3921芯片otp读写区分

在otp_hw.c中的otp_hw_read(...)/otp_hw_write(...)函数中,开始所有芯片都采用64 bit的方式读取key值(0x4d~0x64).需要修改为:

	在前面需要包括头文件:#include <ali_soc_common.h>	/*ali_sys_ic_get_chip_id()在ali_soc.h中定义,但是
	<ali_soc_common.h>中有包含这个头文件*/
	int otp_hw_read(struct otp_dev *otp, unsigned long offset, unsigned char *buf, int len)
	{
		...
		int need_64bit = 0;	/*表示64bit读的变量*/
		unsigned long chip_id = ali_sys_ic_get_chip_id();	/*获得chip_id*/
		unsigned long chip_rev = ali_sys_ic_get_rev_id();	/*获得chip_rev(chip版本)*/
		...
		if(((ALI_S3921 == chip_id) && (chip_rev >= IC_REV_2)) || \	/*IC_REV_2:表示S3921*/
			(ALI_CAP210 == chip_id) || (ALI_C3505 == chip_id) || \
			(ALI_C3922 == chip_id) || (ALI_S3922 == chip_id))
		{
			need_64bit = 1;	/*为"1"表示以64bit方式读/写*/
		}
		...
		for(i = 0; i < tmp_len;) {
			if(need_64bit && IS_BELONG_64BIT_REGION(tmp_offset + i * 4))
			{
				/*处理以64bit方式读*/
			}
			else
			{
				/*处理以32bit方式读*/
			}
		}
	}
	
**IC从C3921B(M3735)开始读取key以64 bit为单位读取,在之前的所有芯片(包括C3921(M3733))都是以32bit为单位读取.**

**目前以64bit为单位读取key的芯片包括:S3921(M3735)、CAP210、C3505、S3922、C3922。之前的芯片都是以32bit为单位读取key.**

## Q6: warning: function declaration isn’t a prototype（函数声明不是原型）的解决办法

	linux驱动中定义一个无参数的函数
	static int mylist_init()
	{
		...
	}
	static void mylist_exit()
	{
		...
	}
	module_init(mylist_init);
	module_exit(mylist_exit);

	编译时出现warning/error:function declaration isn’t a prototype
	
	解决办法:
	static int mylist_init(void)	/*必须在参数中加上"void"*/
	static void mylist_exit(void)	/*必须在参数中加上"void"*/

## Q7:启动时循环出现"i2c IRQ error, pend: 0x00000002"

	在S3922B的板子上烧写image后,启动循环出现:
	
	i2c-ali 18018200.i2c: [__ali_i2c_isr:461]       i2c IRQ error, pend: 0x00000002
	i2c-ali 18018200.i2c: [ali_i2c_start_xfer:777]  [interrupt] xfer one msg fail, msg_len: 1, xfer_len: 0
	i2c-ali 18018200.i2c: [__ali_i2c_isr:461]       i2c IRQ error, pend: 0x00000002
	i2c-ali 18018200.i2c: [ali_i2c_start_xfer:777]  [interrupt] xfer one msg fail, msg_len: 1, xfer_len: 0

	这个问题是因为dvfs(dynamic voltage frequence change):动态电压频率调整会一直通过i2c访问硬件,因为sorting board上
	没有这个硬件模块(部分demo board也没有,我的就没有).一直循环访问,因为没有所以一直报错.

	// 解决
	1)执行"make linux-menuconfig"--->搜索"DVFS"
	2)去掉Device Drivers/ALi drivers selection/Dvfs Drivers和去掉Device Driver/ALi drivers selection/
	Mali-300/400/450 support  --->/Enable Mali dynamically frequency change 
	3)执行"make linux-rebuild all"后重烧kernel

## Q8: ISO C90 forbids mixed declarations and code 警告

	编译的时候经常碰到"ISO C90 forbids mixed declarations and code"警告,其原因是:
		变量定义之前存在一条非变量定义的语句---e.g.
			check_select = 7;	//非变量定义的语句.
			struct test test;	//变量定义.由于之前存在一句非变量定义的语句,因此会报警告.
	解决:
		将非变量定义挪到变量定义之后.
			struct test test;
			check_select = 7;	//该句放到变量定义之后
		在内核中printk()的打印也需要放到变量定义之后.