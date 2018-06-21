# C Program Introduction

## Chapter 1 Compilation preprocessing(编译预处理)

作用:对源程序编译之前做一些处理,生成扩展C源程序.种类如下:

**1.宏定义---#define/#ifdef/#ifndef/#undef**

宏定义只做字符替换,不分配内存空间.因此也不需要类型定义.

	#define TEST_DEFY	(1)	//定义TEST_DEV这个宏的值为1
	
	#ifdef DEBUG_TEST	//如果定义了DEBUG_TEST这个宏
		...
	#else
		...
	#endif
	/*
		#ifdef xxx与#if defined xxx是一样的效果.
		#if !defined DEBUG //前面的"!"可以用来反转条件.即没有定义DEBUG
			...
		#endif
	*/
	#define MICRO 1	//定义宏
	#undef MICRO	//删除前面定义的MICRO宏.

**2.文件包含---#include**

	#include <stdio.h>	//直接搜索标准目录

	#include "test.h"	//先在当前目录搜索,再搜索标准目录.

**3.条件编译---#if--#else--#endif**

	#if 0		//#if condition(如果condition为true,紧接着的代码会执行,否则执行else的代码).此处0为false.
	...	//注释掉某段代码
	#else
	... //开启的代码
	#endif

	PS:还有#elif condition //类似else if,用的比较少.

**4.其他宏定义---#line,#error,#pragma**

	1.#line:用于重新设定__LINE__和__FILE__的内容.
		#line line-number "filename" //指定当前文件名称为"filename",当前行的下一行为"line-number".
	#include <stdio.h> //当前文件名为"test.c"
	
	#line 200 "defy" //指定下一行为第200行,文件名为"defy"
	main()
	{
		printf("line: %d, file: %s\n", __LINE__, __FILE__);
		printf("line: %d, file: %s\n", __LINE__, __FILE__);
		printf("line: %d, file: %s\n", __LINE__, __FILE__);
	}
	/*
		结果为:
			line: 203, file:defy
			line: 204, file:defy
			line: 205, file:defy
	*/

	2.#error:强制编译程序停止编译,主要用于程序调试.
		#error error-message //error-message不需要引号.为一些自定义的错误内容
	#ifdef xxx
	#error xxxis defined. //如果定义了xxx,程序就会被强制停止编译.
	#endif

	3.#pragma:
	#pragma pack(1) //指定数据在内存中的对齐方式为1字节
	struct sample {
		char a;
		double b;
	};
	#pragma pack() //取消对齐方式的指定
	/*
		此处指定了struct sample结构体在编译器处理时按照1字节对齐方式.此时占9字节空间.
		如果没有这样指定,按默认的对齐方式(默认以size最大的那个对齐),因此默认占用16字节.
	*/

**5.宏参数处理---#和##**

	1.#:将后面的宏参数进行字符串化处理:
		#include <stdio.h>
		#define mkstr(s) #s //将s进行字符串化处理
		int main(void)
		{
			printf(mkstd(I like C)); //经过mkstr后会变为:printf("I like C");
			return 0;
		}
	2.##:将两个宏参数链接起来.
	一般用于只有在运行时才能确定要调用哪个函数,可以利用"##"运算符动态地构造要调用函数的名称.
		/* function to convert string to enumeration id */
		#define STR2ENUM_CONV(_enum, ENUM) \
			static int str2 ## _enum (char *str) { \
				int i = 0;		\
				if (!str) {		\
					printf("%s, %d: wrong parameter!\n", __func__, __LINE__); \
					return -1;	\
				}				\
				while (i < NUM_OF_ ## ENUM) {	\
					if (strcmp(str, _enum ## _str[i]) == 0)	\
						break;	\
					i++;		\
				}				\
				if (i == NUM_OF_ ## ENUM) {	\
					printf("%s, %d: wrong parameter!\n", __func__, __LINE__"); \
					return -1;	\
				}				\
				return i;		\
			}

		#define NUM_OF_TEST 0x04
		#define TEST1		0
		#define TEST2		1
		#define TEST3		2
		#define TEST4		3

		const char *test_str[NUM_OF_TEST] = {"test0", "test1", "test2", "test3"};
		STR2ENUM_CONV(test, TEST);

		/*后续调用方式为:
			int index = 0;
			index = str2test("test1"); //可以得到test1在数组中的索引值(此处为1).
		*/
		
**6.预定义宏**

	__DATE__:进行预处理的日期(由%s打印).
	__FILE__:源文件名(由%s打印).
	__LINE__:当前行号(由%d打印).
	__TIME__:源文件编译时间(由%s打印).
	__func__:当前所在函数名(由%s打印).

***

## Chapter 2 Programming practice in C language

### 2.1 位运算

**位运算符:**

	&:按位与;
	|:按位或;
	^:按位异或;
	~:按位取反;
	<<:左移;
	>>:右移.

**左移:**

操作数各位左移,低位补0,高位溢出.

	5 << 2 = 20(十进制数20)

**右移:**

操作数各位右移,移出的低位丢弃,高位如下处理:

	1.对于无符号数和有符号中的整数,直接补0.
		unsigned int a = 5; //101B
		a = a >> 2; //因为a为无符号数,因此a右移之后的值为2(10B).
	2.有符号中的负数(即最高位为1),分为:
		1)逻辑右移:直接高位补0. --->这种系统比较少
		2)算术右移:移完之后最高位补1. --->一般系统均为算术右移(e.g.linux)
			实例:8位二进制数:11001101:
				逻辑右移1位为:[0]1100110
				算术右移1位为:[1]1100110
			
				逻辑右移2位为:[00]110011
				算术右移1位为:[11]110011

**位运算实例---将一个整数(16-bit)按二进制位输出**

	#include <stdio.h>

	int main()
	{
		short num, mask, i;
		printf("Please input an number: ");
		scanf("%d", num);
		mask = 1 << 15; //每个数字都从最高位第15-bit输出
		printf("%d=", num);
		for (i=1; i<=16; i++) {
			putchar((num & mask) ? '1' : '0'); //最高bit为1,putchar输出字符'1';否则输出字符'0'.
			num = num << 1;
			if (i % 4 == 0)
				putchar(','); //输出一个','字符
		}
		printf("\bB\n"); //\b输出一个退格键,去掉最后的','字符.再输出B.
		return 0;
	}

