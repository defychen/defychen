# C Language Skill
***

## 1、malloc函数

void *malloc(size_t size);	//申请一段size字节大小的buffer,返回"void *"

	tVA_DSCR_StbSession *pStbSession;
	pStbSession = (tVA_DSCR_StbSession *)malloc(sizeof(tVA_DSCR_StbSession));

**malloc申请的内存在堆上,释放需要使用free函数.函数中的变量占的空间位于栈上,变量在函数结束后所占的空间会自动释放.**

	//释放malloc申请的内存
	free(pStbSession);
	pStbSession = NULL;	/*释放后需要将指针置空,防止野指针*/

关于在程序运行中出现"double free or corruption (out)：0x0941b450(某个地址)"

	//在程序中free两次会报这个错误
	tVA_DSCR_StbSession *pStbSession = (tVA_DSCR_StbSession *)malloc(sizeof(tVA_DSCR_StbSession));
	free(pStbSession);	/*free第一次*/
	free(pStbSession);	/*free第二次就会报这种错误*/

## 2、指针赋值

	unsigned char key_buffer[16 * 2] = {0};	/*初始化key的数组全部为0*/
	char *pEvenKey = {0xbc, 0x0c, 0x94, 0x1e, 0xbc, 0xd2, 0xa1, 0x3e, 0x89, 0xc9, 
	0x84, 0x6a, 0x51, 0x9e, 0x90, 0x8d};
	char *pOddKey = {0xbc, 0x0c, 0x94, 0x1e, 0xbc, 0xd2, 0xa1, 0x3e, 0x89, 0xc9,
	0x84, 0x6a, 0x51, 0x9e, 0x90, 0x8d};
	/*需要将pEvenKey和pOddKey拷贝给key_buffer*/
	memcpy(key_buffer, pOddKey, 16);	/*odd在前*/
	memcpy(key_buffer + 16, pEvenKey, 16);	/*even在后*/
	/*使用赋值是错误的:
	key_buffer = pOddKey;
	key_buffer + 16 = pEvenKey;	/*这种方式意味着将指针指向的位置变了,而不是copy内容给key_buffer*/
	*/

	//结构体指针赋值
	typedef struct test_device1{
		struct test_device1 *next;
		char name[16];
	}test_device1;

	typedef struct test_device2{
		struct test_device2 *next;
		char name[16];
		int a;
	}test_device2;

	test_device1 *pDevice1;
	test_device2 *pDevice2;
	pDevice1 = (test_device1 *)malloc(sizeof(test_device2));	
	//因为test_device2大小比test_device1大,因此malloc大的结构体
	char a[16] = {"I am Defy Chen"};	//字符串初始化
	memcpy(pDevice1->name, a, 16);
	
	pDevice2 = (test_device1 *)pDevice1;	//将pDevice1指针赋值给pDevice2
	printf("file:%s, func:%s, line:%d, name: %s\n", __FILE__, __func__, __LINE__, pDevice2->name);
	//可以通过pDevice2访问到正确的name.只要name之前的其他成员占用空间一样.
	
## 3、结构体变量赋值

	typedef struct aui_trng_attr {
		unsigned char uc_dev_idx;
	}aui_trng_attr;
	aui_trng_attr attr = {0};	/*声明结构体变量时赋值*/

	/*The second example*/
	typedef struct aui_trng_param {
		unsigned char *puc_rand_output_buffer;
		unsigned long ul_rand_bytes;
	}aui_trng_param;
	aui_trng_param trng_data = {0, 0};	/*puc_rand_output_buffer指针为null, ul_rand_bytes值为0*/

## 4、线程的使用

**va_zapping.c函数**

	#include <pthread.h>	/*包含的线程头文件*/
	...
	typedef struct
	{
		aui_hdl dsc_hdl;	/**/
		pthread_mutex_t va_mutex;	/*linux线程互斥锁,主要用于锁住全局变量*/
		pthread_cond_t dsc_cond;	/*linux线程条件变量,主要用于某个线程等待另一个线程的消息,决定是否继续等待*/
		INT audioFlag;
		INT videoFlag;
	}T_VA_Handle;
	T_VA_Handle *g_pHandle;		/*声明一个全局变量*/

	/*va_zapping.c中g_pHandle的初始化*/
	g_pHandle = (T_VA_Handle *)malloc(sizeof(g_pHandle));
	g_pHandle->dsc_hdl = NULL;
	g_pHandle->audioFlag = 0;
	g_pHandle->videoFlag = 0;
	pthread_mutex_init(&g_pHandle->va_mutex, NULL);	/*初始化互斥锁*/
	pthread_cond_init(&g_pHandle->dsc_cond, NULL);	/*初始化条件变量*/

	pthread_t tid;	/*线程ID*/
	tid = pthread_self();	/*获得线程的ID*/
	printf("Va_zapping pthread: %lu\n", (unsigned long)tid);	/*打印线程ID,为lu(unsigned long)类型*/

	pthread_mutex_lock(&g_pHandle->va_mutex);	/*得到互斥锁,下面的代码需要访问全局变量*/
	if(!g_pHandle->dsc_hdl)
	{
		printf("Execute there: %s, %d\n", __func__, __LINE__);
		pthread_cond_wait(&g_pHandle->dsc_cond, &g_pHandle->va_mutex);
		/*等待条件变量,没有等到会自动释放互斥锁.等待被唤醒*/
	}
	pthread_mutex_unlock(&g_pHandle->va_mutex);	/*释放互斥锁*/

**va_dscr.c函数**
	
	pthread_mutex_lock(&g_pHandle->va_mutex);
	...
	pthread_cond_broadcast(&g_pHandle->dsc_cond);	/*广播条件变量,有等待的地方会被唤醒*/
	pthread_mutex_unlock(&g_pHandle->va_mutex);

## 5、调试程序方法

	1)printf("Execute there: %s, %d\n", __func__, __LINE__);	/*打印出程序执行到的函数和行数*/
	2)getchar();	/*等待终端输入一个字符*/

## 6、数据类型

	unsigned long(无符号数)的数据范围是:0~0xFFFFFFFF.
	当以"%d"打印时(是以有符号数方式打印),0xFFFFFFFF会显示"-1".
	计算方式为,最高位权重为"-1",即为:(-1)*2^31+2^30+3^29+...+=-1
	e.g. 两位(11)时:(-1)*2+1 = -1.
	所以有:0xFFFFFFFF = -1, 0xFFFFFFFE = -1, 0xFFFFFFFD = -3.
	但是当以"%x"方式打印时,就会打印正确的:0xFFFFFFFF.

## 7、写代码时printf输出的技巧

在写代码的过程中经常会有很多信息需要输出,但是当完成代码后又需要去掉这些printf,可以使用下面的"宏"技巧方便调试

	#define VO_DSCR_DEBUG_ENABLE	/*使能DEBUG宏*/
	#ifdef VO_DSCR_DEBUG_ENABLE
	#define VO_DSCR_DEBUG(fmt, args...)	\ /*类似于printf(fmt(格式), args(参数)),一定需要"\"---另起一行*/
		printf("\033[0;32;31mFILE: %s, FUNC: %s, LINE: %d\033[m"fmt, __FILE__, __func__, __LINE__, ##args)
		/*"\033[0;32;31m ... \033[m"---表示使用颜色打印调试信息,但是在做Viaccess Certification时没有成功显示不同颜色*/
		/*__FILE__:显示文件名("e.g.:src/vo_dscr.c").后面的"fmt"表示还可以继续添加后续输出打印,
		"##args"表示可变参数,可以没有参数.即VO_DSCR_DEBUG()除了添加打印头之外还可以按照默认的printf()格式输出*/
	#define VO_DSCR_DUMP(prompt, data, len)	\
		do {\
			int k, l = (len); \
			printf("\033[0;32;32m%s\033[m\n", prompt); \	/*输出提示符"字符串"*/
			for(k=0, k<l; k++){ \
				printf("0x%02x, ", *(BYTE *)((unsigned int)data+k)); \	
				/*data:指针(或数组名);(BYTE *)==(unsigned char *)---无符号字节类型指针*/
				if((k+1)%16==0)	\	/*16个输出一个换行*/
					printf("\n");
			} \
			if(k%16!=0) \	/*打印完成后,如果还有剩下的但又不是16的整数倍,就需要输出一个空格(因为整数倍的上一步的已经输出)*/
				printf("\n"); \
		}while(0)
	#else
	#define VO_DSCR_DEBUG(fmt, args...)   do{}while(0)
	#define VO_DSCR_DUMP(prompt, data, len)   do{}while(0)
	#endif

## 8、open、read函数

	int fd;
	char *buf;	/*buf也可以用数组(e.g.char buf[1024]),用指针必须malloc一段buffer*/
	fd = open("file_name", O_RDONLY);
	if(fd < 0)
	{
		/*some error info*/
		...
	}
	buf = malloc(1024);
	if(!buf)
	{
		...
	}
	if(read(fd, buf, 1024) < 0)
	{
		printf("...%s\n", strerror(errno));
		...
	}

## 9、指向指针的指针使用

	alisl_retcode alislotp_construct(void **handle, alislotp_param_t *param)	/*para1:指向指针的指针参数*/
	{
		alislotp_dev_t *dev = NULL;
		...
		dev = (alistotp_dev_t *)malloc(sizeof(alislotp_dev_t));	/*申请资源*/
		...	/*一系列对dev的操作*/
		*handle = dev;	/*给handle这一指针的指针赋值(如果传进来的为(&dev, para2), 相当于给dev这一个指针赋值)*/
	}
	
	alisl_retcode alislotp_open(void *handle)
	{
		alislotp_dev_t *dev = (alislotp_dev_t *)handle;
		...	/*一系列对dev的操作*/
		/*后面不需要语句
		handle = (void *)dev;
		因此指针是指向一个地址,在转化为dev时,地址不变.*/
	}

	alisl_retcode alislotp_op_read(unsigned long offset, unsigned char *buf, int len)
	{
		void *dev = NULL;	/*声明一个指针*/
		...
		alislotp_construct(&dev, &param);	/*相当于给dev指针赋值*/
		alislotp_open(dev);
		...
	}

**使用指针的好处是:在传递过程中,不需要再对指针重新赋值,只需要改变指针当中的内容即可.**

## 10、kernel中的copy_from/to_user的使用

	struct otp_paras{
		unsigned long offset;	/*otp偏移地址(0x00~0xFF)*/
		unsigned char *buf;		/*otp包含otp的值*/
		int len;		/*buffer大小*/
	};

	static long otp_ioctl(struct file *filp, __u32 cmd, unsigned long arg)
	{
		...
		struct otp_paras para;
		unsigned char *buf = NULL;
		...
		switch(cmd) {
		case ALI_OTP_READ:
		{
			ret = copy_from_user(&para, (void __user *)arg, sizeof(struct otp_paras));
			/*从user space拷贝数据到kernel space
			offset和len被赋值;buf为指向用户空间buf的指针,大小也是有用户空间指定的,用于将数据传递给user space
			因此,copy_from_user一般用于拷贝一些在kernel space能使用的(user space不能用的)数据
			*/
			...
			buf = devm_kzalloc(otp->dev, para.len, GFP_KERNEL);	/*为buf分配kernel的空间*/
			memset(buf, 0, para.len);
			...	/*读数据到buf*/
			ret = copy_to_user(para.buf, buf, para.len);	/*拷贝数据到user space*/
			/*如上所说,para.buf为用户空间的buf*/
			...
			devm_free(otp->dev ,buf);	/*释放kernel space分配的空间*/
			break;
		}
		case ...
		}
	}

## 11、char、short、long的使用

**WORD:字通常为4 byte.**

**DWORD:双字通常为8 byte.**

一般字节、半字、字的定义为:

	typedef unsigned char UINT8;		/*无符号char型定义为UINT8*/
	typedef unsigned short UINT16;	/*无符号short型定义为UINT16*/
	typedef unsigned long UINT32;	/*无符号long型定义为UINT32*/

**字为32 bit(4字节);半字为16 bit(2字节); 字节为8 bit(1字节)**

## 12、driver开发中取某个地址的内容

在driver开发中,经常会遇到取某个地址的内容(一般由宏定义,并带上"volatile")

	#ifndef ARM_AS	/*没有使用ARM核,使用MIPS*/
	#define ALI_CHIP_ID_BASE	(0xb8000000)	/*mips chip_id(芯片ID)的地址*/
	#else
	#define ALI_CHIP_ID_BASE	(0x18000000)	/*arm chip_id(芯片ID)的地址*/
	#endif
	
	/*通过取寄存器地址中的内容来来得到芯片中的一些信息*/
	#define GET_CHIP_ID_DWORD	(*(volatile UINT32 *)ALI_CHIP_ID_BASE)	/*得到ALI_CHIP_ID_BASE的内容得到chip_id*/

	而在otp中烧写在0xb8042000, offset=0的地方的值为"customer_id"---用户ID.

## 13、assert的使用

	#include <assert.h>
	void assert(int expression);	/*assert不是一个函数,为一个宏*/
	/*assert用于计算表达式expression,如果其值为假(即为0),那么它先向stderr打印一条出错信息,然后调用abort终止程序执行.*/
	
	example:
	assert(pointer != NULL);	/*对一个函数的参数进行空指针检查,当出现空指针时,程序会退出,并给出类似
	"Assertion 'pointer != ((void *)0) failed' "的错误*/
	assert(foo > 0);	/*断言一个函数只能在参数foo为正值时才能被调用.*/

**assert只在Debug版本才有效,在Release版本无效,使用下面的方式:**
	
	#include <stdio.h>
	#define NDEBUG	/*禁用assert宏的调用*/
	#include <assert.h>

**NULL的定义**
	
	#define NULL	((void *)0)

## 14、结构体的初始化

	#include <stdio.h>
	struct student_st{
		char c;
		int score;
		const char *name;
	};

	static void show_student(struct student_st *stu)
	{
		printf("c = %c, score = %d, name = %s\n", stu->c, stu->score, stu->name);
	}

	int main(void)
	{
		// method 1:按照成员声明的顺序初始化
		struct student_st s1 = {'A', 91, "Alan"};
		show_student(&s1);

		// method 2:指定初始化,成员顺序可以不定,linux内核多采用此方式
		struct student_st s2 = 
		{
			.name = "YunYun",
			.c = 'B',
			.score = 92,
		};
		show_student(&s2);

		// method 3:指定初始化,成员顺序可以不定
		struct student_st s3 = 
		{
			c : 'C',
			score : 93,
			name : "Wood",
		};
		show_student(&s3);

		return 0;
	}

**结构体数组的初始化**

	// Case 1
	struct city{
		char name[20];
		double population;
		double housing;
		double ave;
	};

	city cities[2] = {
		{"a", 1, 1, 1},
		{"b", 1, 1, 1},
	};	/*定义并初始化*/

	// Case 2
	struct test{
		int a;
		int b;
	};

	test test1[5] = {0};	/*全部成员初始化为0*/---这样初始化会出现warning
	test test1[5] = {{0}};	//这样初始化不会出现warning

## 15、bit位的表示

	// Case 1: using int(有符号的整数)
	struct test{
		int a : 1;
		int b : 2;
		int c : 3;	/*表示结构体中的一个成员占的bit位个数*/
	};

	int main()
	{
		struct test test1 = {1, 3, 7};	
		/*
		a占1 bit,由于为有符号的整数,因此为-1
		b占2 bit,3 = b(11),最高位为符号位,因此为负数.取补码,3差4为1,因此为"-1"
		c占3 bit,7 = b(111),最高位为符号位,因此为负数.取补码,7差8为1,因此为"-1"
		一次类推,6时显示为"-2", 4时显示为"-4".3显示为整数"3".
		*/
		printf("%d, %d, %d, %d\n", test1.a, test1.b, test1.c, test1);	
		/*输出test1时,是输出整个数(即所有bit位组合起来的值)*/
	}

	// Case 2: using unsigned int(使用无符号整数)---都是使用这种方式
	struct test{
		unsigned int a : 1;
		unsigned int b : 2;
		unsinged int c : 3;
	};
	/*使用无符号整数时,可以输出不需转换的值*/

## 16、函数指针的使用

	// Case 1: 基本用法
	typedef void (*FUNC)(int);	/*FUNC为一个函数指针*/
	FUNC pFunc = NULL;	/*声明一个函数指针变量*/
	void glFunc(int a)
		printf("func: %s, line: %d, Value: %d\n", __func__, __LINE__, a);

	int main(void)
	{
		pFunc = glFunc;	/*将一个函数名赋值给函数指针*/
		pFunc(2);	/*通过函数指针可以最终调用函数*/
	}

	// Case 2: 函数指针为结构体当中的成员
	struct test{
		unsigned int a : 1;
		unsigned int b : 2;
		unsinged int c : 3;
		FUNC pFun;	/*函数指针为结构体的成员*/
	};

	struct test test1 = {0};	/*会将整型变量初始化为0,函数指针初始化为NULL*/
	printf("%d, %d, %d, %s\n", test1.a, test1.b, test1.c, test1.pFun);
	test1.pFun = glFun;	/*给结构体成员中的函数指针赋值*/
	test1.pFun(2);	/*通过函数指针调用指向的函数*/

## 17、重复定义(multiple definition of)与重复包含

**重复包含:防止头文件被重复包含.**

	#ifndef	__TEST_H__
	#define __TEST_H__
	...
	#endif	/*__TEST_H__*/

**不能防止头文件中的全局变量被重复引用,因为每个".c"文件都是独立解释的.如果其他文件包含该头文件,就会独立解释.在最终链接时出现重复定义的错误.**

**解决这种重复定义的错误:**

	// 正确的声明全局变量的方法:
	1)在某个".c"文件中声明全局变量;
	/*在otp_api.c文件中声明并初始化以下的全局变量:*/
		OSAL_ID otp_mutex_id = OSAL_INVALID_ID;
	2)在需要引用的头文件中使用"extern"声明该全局变量
	/*在otp_drv.h文件中中使用"extern"声明该全局变量*/
		extern OSAL_ID otp_mutex_id;
	3)在需要引用该全局变量的函数中包含头文件
	/*在otp_api.c、otp_m33.c、otp_m37.c文件中:*/
		#include "otp_drv.h"

**头文件只会有声明,不会有定义.**

## 18、linux内核链表

内核链表为双向链表

**1.链表的结构体**

	#include <linux/list.h>	/*list链表的主要实现文件*/
	#include <linux/types.h>	/*linux 3.x以上的包含一些list实现内容*/
	
	struct list_head {
		struct list_head *next, *prev;
	};	/*链表的结构体*/

	/*e.g.
	struct list_head score_head; /*声明一个链表头*/
	*/

**2.创建链表,即初始化链表头**
	
	static inline void INIT_LIST_HEAD(struct list_head *list)
	{
		list->next = list;
		list->prev = list;
	}	
	/*让链表指向自身,即初始化为一个空链表.该static函数在包含该头文件的文件中可以直接使用.
	inline在编译程序调用该函数的地方会展开*/
	
	/*e.g.
	INIT_LIST_HEAD(&score_head);	/*初始化一个空链表,其实就是一个链表头*/
	*/

**3.在链表头插入节点**

	static inline void __list_add(struct list_head *new, 
						struct list_head *prev,
						struct list_head *next)
	{
		next->prev = new;
		new->next = next;
		new->prev = prev;
		prev->next = new;
	}

	static inline void list_add(struct list_head *new, struct list_head *head)
	{
		__list_add(new, head, head->next);	
		/*在head和head->next之间插入new(new节点为链表元素,一般为自己声明的带struct list_head元素的结构体)*/
	}

**4.在链表尾插入节点**

	static inline void list_add_tail(struct list_head *new, struct list_head *head)
	{
		__list_add(new, head->prev, head);	//new节点为链表元素,一般为自己声明的带struct list_head元素的结构体
	}

**5.删除节点**

	static inline void __list_del(struct list_head *prev, struct list_head *next)
	{
		next->prev = prev;
		prev->next = next;
	}

	static inline void list_del(struct list_head *entry)
	{
		__list_del(entry->prev, entry->next);
		entry->next = LIST_POISON1;	/*置空*/
		entry->prev = LIST_POISON2; /*置空*/
	}

**6.取出节点**

	#define container_of(ptr, type, member) ({	\
		const typeof(((type *)0)->member)*__mptr = (ptr); 	\
		(type *)((char *)__mptr - offset(type, member)); })

	#define list_entry(ptr, type, member)	\
		container_of(ptr, type, member)

	/*
	ptr:为struct list_head *类型(也就是链表头).一般配合list_for_each(pos, head)遍历使用---会不断更新链表头放在pos里
	type:自己定义的链表类型(自定义链表包含struct list_head *)e.g. struct score,在之前会调用插入节点将自定义类型插入进链表头.
	member:自定义链表包含的内核链表链接域,e.g.list
	*/

**7.遍历链表**

	#define list_for_each(pos, head)	\
		for (pos = (head)->next; pos != (head); pos = pos->next)
	/*
	pos:为struct list_head *类型(链表头类型),会自动不断更新
	head:链表头
	*/

**链表实例**

	/*mylist.c文件*/
	#include <linux/module.h>
	#include <linux/init.h>
	#include <linux/types.h>
	#include <linux/list.h>	/*kernel list header file*/
	
	struct score{
		int num;
		int english;
		int math;
		struct list_head list;	/*kernel list*/
	};

	struct list_head score_head;	/*list head---一般会调用INIT_LIST_HEAD(&score_head);进行初始化*/
	
	/*define three list node, then insert into the list*/
	struct score stu1, stu2, stu3;
	struct list_head *pos;	/*define a pos pointer---保存list_for_each遍历得到的链表头信息*/
	struct score *tmp;	/*define a temporary struct score variable*/

	static int mylist_init(void)
	{
		INIT_LIST_HEAD(&score_head);	/*initialize list head*/

		stu1.num = 1;
		stu1.english = 59;
		stu.math = 99;

		/*insert the node into the list tail*/
		list_add_tail(&(stu1.list), &score_head);	/*using tail insert method*/

		stu2.num = 2;
		stu2.english = 69;
		stu2.math = 98;
		list_add_tail(&(stu2.list), &score_head);

		stu3.num = 3;
		stu3.englisth = 89;
		stu3.math = 97;
		list_add_tail(&(stu3.list), &score_head);

		/*traversal list and print the element*/
		list_for_each(pos, &score_head)
		{
			tmp = list_entry(pos, struct score, list);
			printk(KERN_WARNING "num: %d, english: %d, math: %d\n", tmp->num, tmp->english, tmp->math);
		}
		return 0;
	}

	static void mylist_exit(void)
	{
		/*delete the node*/
		list_del(&(stu1.list));
		list_del(&(stu2.list));
		list_del(&(stu3.list));
		printk(KERN_WARNING "mylist exit success!\n");
	}

	module_init(mylist_init);
	module_exit(mylist_exit);
	MODULE_AUTHOR("Defy Chen");
	MODULE_DESCRIPTION("My list");
	MODULE_LICENSE("GPL");
	MODULE_VERSION("1.0.0");

	/*
	在M3527上insmod时,出现"insmod: can't insert 'mylist.ko': Operation not permitted"
	但是在S3922上是可行的.这是什么原因？
	*/

## 19、#pragma pack(4)和#pragma pack(8)对齐原则

**pragma pack(n):指定编译器按照n个字节对齐**

**pragma pack():取消自定义字节对齐方式**

	#pragma pack(4)	/*指定按照4字节对齐*/
		struct One{
			double d;	/*double(8)*/
			char c;		/*char(1) + 3*/---指定了4字节对齐
			int i;		/*int(4)*/
		};	/*总共16字节*/
	#pragma pack()	/*取消自定义字节对齐*/

	#pragma pack(4)
		struct Two{
			char c;		/*char(1) + 3*/---指定了4字节对齐
			double d;	/*double(8)*/
			int i;		/*int(4)*/
		};	/*总共16字节*/
	#pragma pack()
	
	#pragma pack(8)	/*指定按照8字节对齐*/
		struct One{
			double d;	/*double(8)*/
			char c;		/*char(1)*/
			int i;		/*int(4)*/---最终为char(1) + int(4) + 3构成8b字节
		};	/*总共16字节*/
	#pragma pack()

	#pragma pack(8)
		struct Two{
			char c;		/*char(1) + 7*/---指定了8字节
			double d;	/*double(8)*/
			int i;		/*int() + 4*/
		};	/*总共16字节*/
	#pragma pack()

## 20、统计某个数所占的字节数

	typedef unsigned long UINT32;
	UINT32 key_length = 64/128/192/256;
	UINT32 counter = 0;
	counter = key_length >> 5;	/*计算key_length所占的字节数(e.g. 128/32 = 4byte)*/

## 21、枚举变量赋值(当超出枚举定义值时)

	enum PARITY_MODE{
		EVEN_PARITY_MODE = 0,
		ODD_PARITY_MODE = 1,
		AUTO_PARITY_MODE0 = 2,
		AUTO_PARITY_MODE1 = 3,
	};

	enum PARITY_MODE parity_mode;
	parity_mode = 4;	/*不会报错,因为一般编译器会分配一个int大小给enum.所以此时它相当于int类型.*/

## 22、循环左移和右移

	#define ROTL(x, n)	(((x) << (n)) | ((x) >> (32 - (n))))		/*循环左移 "n" bit,针对unsigned long类型*/
	#define ROTR(x, n)	(((x) >> (n)) | ((x) << (32 - (n))))		/*循环右移 "n" bit,针对unsigned long类型*/
	
	/*如果将一个4 byte(32 bit)的数交换字节序(e.g.字节序由:1 2 3 4变成:4 3 2 1)方法*/
	1)循环右移一个字节(8 bit),得到:4 1 2 3--->留下4和2(即第1,3字节)
		ROTR(x, 8) & (0xff00ff00)--->取其中的第1和3字节
	2)循环左移一个字节(8 bit),得到:2 3 4 1--->留下3和1(即取第0,2字节)
		ROTL(x, 8) & (0x00ff00ff)--->取其中的第0和2字节
	3)最后两个步骤取"或",得到交换的字节序
	
	/*总结为:*/
	#define BYTESWAP(x) ((ROTR((x), 8) & 0xff00ff00) | (ROTL((x), 8) & 0x00ff00ff))
	
## 23、memcpy写buffer时出现溢出

	UINT32 src = 0x12345678;	//4 byte,16进制表示的数据
	UINT8  dest = 0;
	//下面的虽然可以正确拷贝,但是可能会出现溢出的warning
	memcpy(&dest, (UINT8 *)&src, sizeof(UINT32));	//会拷贝src中的最后一个字节(0x78)
	//应该改为
	memcpy(&dest, (UINT8 *)&src, sizeof(UINT8));	//修改拷贝大小为1 byte

## 24、往一段buffer中填入命令的方法(Command Queue)

	typedef struct dsc_cmdq_io_format_defy
	{
		UINT64 cmd_data:32;	//占32 bit
		UINT64 cmd_byte_en:4;
		UINT64 cmd_index:16;
		UINT64 cmd_type:4;
		UINT64 cmd_reserved:8;
	}DSC_CMDQ_IO_DEFY;	//命令格式

	typedef struct dsc_cmdq_info_defy
	{
		UINT32 cmdq_id;	//command queue id
		UINT32 cmdq_s_ptr;	//start pointer of this id(值当作指针使用)
		UINT32 cmdq_cur_ptr;	//current point of this id(值当作指针使用)
		UINT32 cmdq_size;		//size of cmdq, unit 16 byte
	}DSC_CMDQ_INFO_DEFY;	//控制命令的移动(DSC_CMDQ_IO_DEFY的移动)

	UINT8 cmdq_buf[512] = {0};	//一段512字节大小的buffer---用于填充command
	DSC_CMDQ_INFO_DEFY	cmdq_info_defy;	//
	memset(&cmdq_info_defy, 0x00, sizeof(DSC_CMDQ_INFO_DEFY));
	cmdq_info_defy.cmdq_cur_ptr = (UINT32)cmdq_buf + sizeof(DSC_CMDQ_INFO_IO);	//移动一个IO的位置,保留给CMDQ_ID用
	cmdq_info_defy.cmdq_s_ptr = (UINT32)cmdq_buf;	//起始指针挪到buffer头

	//开始往buffer中填入命令
	DSC_CMDQ_IO_DEFY *pcmdq_io_defy = (DSC_CMDQ_IO_DEFY *)cmdq_info_defy.cmdq_cur_ptr;	//指向同一个地址
	pcmdq_io_defy->cmd_reserved = 0;
	pcmdq_io_defy->cmd_type = DSC_IO_WRITE;	//表示IO写
	pcmdq_io_defy->cmd_index = KEY_MODE_REG;		//寄存器的位置
	pcmdq_io_defy->cmd_byte_en = 0xF;			//表示32 bit的4个字节都有效.一个bit表示对应的一个字节有效
	pcmdq_io_defy->cmd_data = 1;				//写入寄存器的数据
	//上面已经完成了将cmd填入buffer的操作(因为两个指针指向同一个地方,改变一个另一个也会改变)
	cmdq_info_defy.cmdq_cur_ptr += sizeof(DSC_CMDQ_IO_DEFY);	//移动当前指针
	
	memcpy((UINT8 *)&(cmdq_info_defy.cmdq_cur_ptr), pcmdq_io_defy, sizeof(DSC_CMDQ_IO));
	//将上一次的pcmdq_io_defy拷贝到下一个空间中,避免重写.只需要更改某个值即可.

## 25、指针数组初始化为"NULL"

	1)如果是全局的本身已经初始化为NULL
	2)不是全局的可以写个for循环,将数组中的每个元素赋值为NULL
	// example
	int index;		
	void *dscrInfo[16];
	for(index = 0; index < 16; index++)
	{
		dscrInfo[index] = NULL;
	}

## 26、字符串直接打印对应的ASCII码值

	unsigned char msg[] = "HelloWorld!23456";	//一个字符占一个字节
	unsinged int fsize = strlen((char *)msg);	//求取字符串的长度,不包括结尾的"\0".包含在头文件"string.h"
	printf("%d\n", fsize);		//结果为16
	unsinged char *dataBuf = (unsigned char *)malloc(32);
	memset(dataBuf, 0, 32);
	strcpy((char *)dataBuf, (char *)msg);	//将msg中的每一个字符复制到dataBufz中
	//直接按整型打印字符串
	int i;
	for(i = 0; i < 16; i++)
	{
		printf("0x%02x ", msg[i]);	//以16进制打印字符串中的每一个字符
	}

## 27、声明存放16进制数数组

	unsigned char array[16] = {0};	//每个数占一个字节,且都初始化为0

## 28、线程终止

**1)线程终止的三种方式**

1)线程的return,return值就是线程的退出码

2)线程调用了pthread_exit()函数

	pthread_exit((void *)"pthread exit");	//线程主动返回,并且会打印出para中的字符串

3)线程可以被同一进程中的其他线程取消

**2)线程取消**

1)定义:线程接收另一个线程发来的终止(取消)请求而强制终止

2)方法:向目标线程发送cancel信号.但是处理cancel信号由目标线程自己决定---忽略(当禁止取消时)、立即终止(在取消点或异步模式下)、运行至cancelation-point(取消点),由不同的cancelation状态决定.

线程接收到cancel信号的缺省处理是继续运行至取消点再处理(退出),或在异步方式下直接退出.

**3)取消点**

pthread_join()、pthread_testcancel()、pthread_cond_wait()、pthread_cond_timewait()、sem_wait()、sigwait()以及read()、write()等会引起阻塞的系统调用都是取消点(cancelation-point),而其他pthread函数不会引起cancelation动作.

**4)与线程相关的pthread函数**
	
	1)int pthread_cancel(pthread_t thread);	//发送终止信号给pthread线程
	//para:线程的ID; retval:成功返回0,失败返回非0.发送成功并不意味着thread会终止

	2)int pthread_setcancelstate(int state, int *oldstate);	//设置本线程对cancel信号的反应---相当于本线程的属性
	//para1---两种值:1)PTHREAD_CANCEL_ENABLE(缺省)---表示接收cancel信号并设为cancel状态;
					2)PTHREAD_CANCEL_DISABLE---忽略cancel信号继续运行
	//para2---不为NULL则存入原来的cancel状态以便恢复.一般为"NULL"

	3)int pthread_setcanceltype(int type, int *oldtype);	//设置本线程取消动作的执行时机---相当于本线程的属性
	//para1---两种值:1)PTHREAD_CANCEL_DEFFERED---表示收到信号后继续运行到下一个取消点再退出
					2)PTHREAD_CANCEL_ASYCHRONOUS---表示收到信号后立即执行取消动作(退出)
	//para1只有当cancel状态为enable时有效.para2:一般为NULL

	4)void pthread_testcancel(void)		//检查本线程是否处于cancel状态.如果是则进行取消动作,否则直接退出.
	
**5)实例**

	#include <stdio.h>
	#include <stdlib.h>
	#include <pthread.h>
	#include <unistd.h>

	void func(void *arg)
	{
		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);	//允许线程退出
		pthread_setcanceltype(PTHREAD_CANCEL_ASYCHONOUS, NULL);	//设置立即取消
		while(1)
		{
			//operation;
		}
		return;
	}

	int main(int argc, char *argv[])
	{
		pthread_t thrd;	//存放线程ID
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);	//这几行设置为detach,用的比较少
		
		void *s;	//pthread_join中的para2存放

		if(pthread_create(&thrd, &attr, (void *)func, NULL))
		{
			printf("pthread_create error\n");
			return -1;
		}

		if(!pthread_cancel(thrd))	//发送终止信号给thrd线程,发送成功返回0
		{
			printf("pthread_cancel OK!\n");
		}

		sleep(1);

		pthread_join(thrd, &s);		//给线程thrd创建一个取消点,让thrd线程退出
		printf("%s\n", (char *)s);	//打印线程退出的消息
		return 0;
	}

## 29、宏判断

	#if defined(MACOS)			//如果定义了宏"MACOS"
	#include <sys/syslimits.h>
	#elif defined(SOLARIS)		//如果定义了宏"SOLARIS"
	#include <limits.h>
	#elif defined(BSD)			//如果定义了宏"BSD"
	#include <sys/param.h>
	#endif

## 30、UINT32和UINT8的对齐及存放

	typedef unsigned long UINT32;
	typedef unsigned char UINT8;
	
	UINT32 a = 0x12345678;
	
	printf("0x%x, 0x%x, 0x%x\n", &a, (&a)+1, ((UINT8 *)&a)+1);
	//结果为:7fc4fa40, 7fc4fa44, 7fc4fa41.
	//解析:UINT32---32位的数据为4字节对齐,因此其地址每次增加4
	//UINT8---8位的数据为1字节对齐,因此其地址每次增加1.按照小端格式,低地址存放低字节数据.即:
	//7fc4fa40---78, 7fc4fa41---56, 7fc4fa42---23, 7fc4fa43---01.每个地址存放一个字节的数据.

	printf("0x%2x 0x%2x 0x%2x 0x%2x\n", *((UINT8 *)&a), *(((UINT8 *)&a)+1), *(((UINT8 *)&a)+2),
		 *(((UINT8 *)&a)+3));
	//所有的地址都是32 bit的.UINT32表示4字节的数据,每个地址只存一个字节的数据.因此UINT32占用连续四个地址.
	//(UINT8 *)&a:表示将4字节对齐的a强制转为1字节对齐,然后访问每个地址的数据.

**单字节与4字节对齐的相互转化**

	UINT32 a = 0x12345678;
	UINT8 b[4] = {0};
	//4字节转化为单字节操作
	memcpy(b, (UINT8 *)&a, sizeof(UINT32));	//拷贝4字节数据到b数组中
	printf("The array data is: b[0] = %2x, b[1] = %2x, b[2] = %2x, b[3] = %2x\n",
			b[0], b[1], b[2], b[3]);

	//单字节转化为4字节操作
	memcpy((UINT32 *)a, &a, sizeof(UINT32));
	printf("The array data is: b[0] = %2x, b[1] = %2x, b[2] = %2x, b[3] = %2x\n",
			b[0], b[1], b[2], b[3]);

	//结果都为:78 56 34 12
## 31、#ifdef __cplusplus...的使用

	#ifdef __cplusplus	//"__cplusplus"是cpp中自定义宏,这个宏表明这是一段cpp的代码
	extern "C" {	//如果是一段cpp代码,extern "C"{...}表明这段代码使用"C"来编译链接(C和C++编译链接不一样)
	#endif
	...
	#ifdef __cplusplus
	}
	#endif

## 32、结构体中数组的赋值

	struct test{
		unsigned int test_element[2];
	};
	
	struct test myTest = {
		0x12345678, 0x87654321,
	};	//会自动填充结构体中数组的每一个元素

	printf("Test result: 0x%x, 0x%x\n", myTest.test_element[0], myTest.test_element[1]);
	//会打印出:Test result: 0x12345678, 0x87654321

## 33、数组中指定对应元素的值

	unsigned char test[] = {
		[5] = 4,		//指定test[5]=4---第6个元素值为4
		[4] = 6,		//指定test[4]=6---第5个元素值为6
		[3] = 3,		//指定test[3]=3---第4个元素值为3
						//指定的值之间用分号","分隔.其他没有被指定的都被初始化为"0"
	};

## 34、指针和结构体指针所占空间的大小

	struct test_device{
		struct test_device *next;	//为一个结构体指针,属于指针.在32 bit机器中占4 byte
		char *p;					//指针,在32 bit机器中占4 byte
		char w;						//声明一个字符,单独打印是占一个byte.但是在此结构体中对自动4 byte对齐,因此占4byte
		/*
		char w[7];					//如果为这种情况,默认是7byte.但是放在对齐中会采用对齐方式存储(8 byte).
		*/
		unsigned int (*)open(void);	//函数指针,也是占4 byte
		unsigned int type;			//占4 byte
	};

	printf("size: %d\n", sizeof(struct test_device));	//大小为20 byte

**sizeof()求指针和数组的区别**
	
	unsigned char test[128] = {0};
	unsigned char *pTest = NULL;
	printf("array size: %d, pointer size: %d\n", sizeof(test), sizeof(pTest));
	//结果为:array size: 128, pointer size: 4.
	/*解析:
		1)sizeof(数组名):此时为统计数组的大小
		2)sizeof(指针):此时为计算指针本身所占用的空间,4 byte.---此处的指针包括结构体指针	
	*/	

## 35、求字符串长度的函数strlen

	char a[] = {"I am Defy Chen"};	//总共占14个字符
	printf("strlen: %d\n", strlen(a));	//strlen求出的长度为14.如果需要访问最后一个字符:a[strlen(a)-1];

## 36、char字符相加

	char a = 0;
	a = a + 1;	//或者a = a + (char)1;
	printf("value: %d\n", a);	//得到的值为1---正确相加.

## 37、union和struct的初始化

	union test_union{
		int a;
		char b;
	};

	struct test_struct{
		int a;
		char b;
	};

	union test_union test1 = {0};	//联合体变量直接初始化为"{0}".
	struct test_struct test1 = {0};	//结构体变量直接初始化为"{0}".
	union test_union *pTest1 = NULL;	//联合体指针直接初始化为NULL
	struct test_struct *pTest2 = NULL;	//结构体指针直接初始化为NULL

## 38、对于定义了但是没有使用的变量/函数warning的清除

	//在编译时,经常会碰到有变量/函数定义了但是没有地方使用(但是又需要保留,因为有特殊的场合使用,一般不使用)
	__attribute__((unused)) UINT32 ret_val = 0;		//定义了变量但是不会使用,可用于清除warning和secure coding的报错
	static __attribute__((unused)) void xxx_fun(void)	//定义了函数但是不会使用
	{
		...
	}

## 39. 在二维数组中*a, a, a[0], a[0][0], a[1], &a[1]的区别

	在二维数组a[x][y]中:
	1)*a:表示以a[0][0]为首元素的一维数组.可带一个索引:(*a)[i]即a[0][i]
	2)a:表示以a[0][0]为首元素的二维数组.可带两个索引:a[i][j]
	3)a[0]:同*a---一维数组
	4)a[0][0]:首元素
	5)a[1]:表示以a[1][0]为首元素的一维数组.可带一个索引
	6)&a[1]:表示以a[1][0]为首元素的二维数组.可带两个索引:(&a[1])[i][j]即a[1+i][j]

	//e.g.
	static unsigned char protectingKey[4][16] = {  
			{0},				
			{0},
			{0},
			{0}
	};
	unsigned char pk1[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	unsigned char pk2[16] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};

	memcpy(&protectingKey[0], pk1,16);	//将pk1拷贝到以protectingkey[0][0]为首元素的二维数组中
	//此处用:memcpy(protectingkey[0], pk1, 16);	---将pk1拷贝到以protectingkey[0][0]为首元素的一维数组中 
	memcpy(&protectingKey[1], pk2,16);	//将pk2拷贝到以protectingkey[1][0]为首元素的二维数组中
	//此处用:memcpy(protectingkey[1], pk2, 16);	---将pk2拷贝到以protectingkey[1][0]为首元素的一维数组中
	//上述两种方法得到的结果一样
	/*
	最终protectingkey[4][16] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
		{0},
		{0}
	};
	*/

## 40. define宏定义中的#, ##, @#和\符号

**1.#---字符串化操作符**
	
将宏定义传入的参数名转换成用一对双引号括起来(" ")的参数名字符串

	#define example(test)	#test
	/*C++方式:
	string str = example(abc);		//会展开成:string str = "abc";	---C语言没有string类型
	*/
	//C方式
	char str[] = example(abc);		//会展开成:char str[] = "abc";	---C语言正确的方式
	char str1[] = example( abc  def );	//结果为:"abc def"---开头和末尾的空格忽略,中间的多个空格只保留一个

**2.##---符号连接操作符**

将宏定义的多个形参名连接成一个实际的形参名

	//Enumeration conversation functions
	#define STR2ENUM_CONV(_enum, ENUM) static int str2 ## _enum(char *str) {\	//连接
		int i=0; \
		if(!str) \
			{printf("%s@%d -> wrong parameter\n", __func__, __LINE__);return -1;}\
		while (i<NUM_OF_ ## ENUM) {\	//连接
			if (strcmp(str, _enum ## _str[i]) == 0) break; \	//注意比较字符串的定义
			i++; \
		} \
		if (i == NUM_OF_ ## ENUM) {\	//连接
			printf("wrong parameter %s\n", str); \
			return -1; \
		} \
		return i; }
	//使用1---ALGO
	#define NUM_OF_ALGO 2
	static char *algo_str[NUM_OF_ALGO] = {"TDES", "AES"};	//比较字符串的定义
	STR2ENUM(algo, ALGO)		//无分哈
	//使用2---MODE
	#define NUM_OF_MODE 2
	static char *mode_str[NUM_OF_MODE] = {"ENCRYPT", "DECRYPT"};
	STR2ENUM(mode, MODE)		//无分号

**3.@#---字符化操作符**

将宏定义传入的单字符参数转换成字符,并用一对单引号(' ')括起来

	#define makechar(x)		@#x
	char a = makechar(b);		//展开后变成:a = 'b';

**4.\---行继续操作符**

当定义的宏不能用一行表达完整时,可以用"\"表示下一行继续此宏的定义

	//如上述"2.##"中的应用

## 41. #undef的使用

	#undef是在后面取消以前定义的宏定义
	//例子
	#define MAX 100
	int a = MAX;
	//如果后面不需要MAX这个宏,但是还是需要这个变量名.可以:
	#undef MAX	//取消MAX之前的宏定义
	int MAX = 0;	//重新定义变量MAX

## 42. sprintf函数

把格式化的数据写入某个字符串(buffer).

	//函数原型
	int sprintf(char *buffer, const char *format [, argument]...);	//返回值:字符串长度(strlen)
	//实例:
	char test[20] = 0;
	char *t = "I";
	char *r = "linux";
	int len = 0;
	len = sprintf(test, "%s love %s", t, r);
	printf("func: %s, line: %d, len: %d, str: %s\n", __func__, __LINE__, len, test);
	//打印出来为:func: ..., line: ..., len: 12, str: I love linux		//长度为12
	
	//如果在sprintf中加上了\n,则len为13
	len = sprintf(test, "%s love %s\n", t, r);

## 43. 字符的+

	printf("%c, %c\n", '0', '0' + (char)1);	//会打印出来:0, 1---表示字符增加了1. PS:不加(char)也可以,自动会进行转换
	printf("%d, %d\n", '0', '0' + (char)1);	//会打印出来:48, 49---字符对应的ASCII码值
	printf("%c, %c\n", '0', '0' + '1');		//会打印出来:0, a---字符的相加.0-48,1-49,最终得到97的字符"a"
	printf("%d, %d\n", '0', '0' + '1');		//会打印出来:48, 97