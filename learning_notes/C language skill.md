# C Language Skill
***

## 1、malloc函数

void *malloc(size_t size);	//申请一段size字节大小的buffer,返回"void *"

	tVA_DSCR_StbSession *pStbSession;
	pStbSession = (tVA_DSCR_StbSession *)malloc(sizeof(tVA_DSCR_StbSession));

## 2、指针赋值

	char *puc_key;
	char *pEvenKey = {0xbc, 0x0c, 0x94, 0x1e, 0xbc, 0xd2, 0xa1, 0x3e, 0x89, 0xc9, 
	0x84, 0x6a, 0x51, 0x9e, 0x90, 0x8d};
	char *pOddKey = {0xbc, 0x0c, 0x94, 0x1e, 0xbc, 0xd2, 0xa1, 0x3e, 0x89, 0xc9,
	0x84, 0x6a, 0x51, 0x9e, 0x90, 0x8d};
	/*需要将pEvenKey和pOddKey拷贝给puc_key*/
	memcpy(puc_key, pOddKey, 16);
	memcpy(puc_key + 16, pEvenKey, 16);
	/*使用赋值是错误的:
	puc_key = pOddKey;
	puc_key + 16 = pEvenKey;	/*这种方式意味着将指针指向的位置变了,而不是copy内容给puc_key*/
	*/
	
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

**字(WORD):2个字节组成一个字.**

**双字(DWORD):4个字节组成一个双字.**

一般字节、字、双字的定义为:

	typedef unsigned char BYTE;		/*无符号char型定义为字节*/
	typedef unsigned short WORD;	/*无符号short型定义为字*/
	typedef unsigned long DWORD;	/*无符号long型定义为双字*/

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

	test test1[5] = {0};	/*全部成员初始化为0*/

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

**2.创建链表,即初始化链表**
	
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
		__list_add(new, head, head->next);	/*在head和head->next之间插入new*/
	}

**4.在链表尾插入节点**

	static inline void list_add_tail(struct list_head *new, struct list_head *head)
	{
		__list_add(new, head->prev, head);
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
	ptr:为struct list_head *类型,一般配合list_for_each(pos, head)遍历使用
	type:自己定义的链表类型(自定义链表包含struct list_head *),e.g. struct score.
	member:自定义链表包含的内核链表链接域,e.g.list
	*/

**7.遍历链表**

	#define list_for_each(pos, head)	\
		for (pos = (head)->next; pos != (head); pos = pos->next)
	/*
	pos:为struct list_head *类型,自动更新
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

	struct list_head score_head;	/*list head*/
	
	/*define three list node, then insert into the list*/
	struct score stu1, stu2, stu3;
	struct list_head *pos;	/*define a pos pointer*/
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