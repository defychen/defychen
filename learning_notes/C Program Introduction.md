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

### 2.2 指针特性

#### 2.2.1 数据指针

**1.指针直接操作内存的情况**

1.某I/O芯片被定位在CPU的存储空间而非I/O空间,而且寄存器对应于某特定地址;

2.两个CPU之间以双端口RAM通信,CPU需要在双端口RAM的特定单元(称为mail box)书写内容以在对方CPU产生中断;

3.读取在ROM或FLASH的特定单元所烧录的汉字和英文字模.

**2.指针实例**

	unsigned char *p = (unsigned char *)0xF000FF00; //直接给一个指针赋值一个地址.
	*p = 11; //指针内容赋值

指针自增/自减操作的结果取决于指针指向的数据类型:

	int *p = (int *)0xF000FF00;
	p++(或++p) -> p = p + sizeof(int); //相当于+4
	p--(或--p) -> p = p - sizeof(int); //相当于-4

**3.指针的指针作用(申请内存空间)**

1.错误实例---申请不到内存

	void GetMemory(char *p, int num)
	{
		p = (char *)malloc(sizeof(char) * num);
	}

	void main()
	{
		char *str = NULL;
		GetMemory(str, 100);
		strcpy(str, "hello");
	}
	/*
		实参调用形参时,都是实参的一份拷贝.此处传指针(地址),也是传的地址的一份拷贝,而在GetMemory中malloc
		的内存,改变的是形参以及拷贝的指针的值.但是源指针(即实参指针)并没有被改变.因此此时实参指针仍为NULL.
	*/

2.修改---传指针的指针

	void GetMemory(char **p, int num)
	{
		*p = (char *)malloc(sizeof(char) * num);
	}

	void main()
	{
		char *str = NULL;
		GetMemory(&str, 100);
		strcpy(str, "hello");
		free(str);
	}

3.函数形参传变量,指针,指针的指针比较

	1.传变量:调用形参时,为实参的一份变量的拷贝.如果在函数内修改形参变量并不能体现在源实参变量上;
	2.传指针:调用形参时,为实参的一份指针(地址)的拷贝.如果在函数内修改形参指向的内容可以体现在实参上,
		因为形参(实参的一份拷贝)和实参指向的是同一个地址.但是实参的地址是改不动的(因为是一份拷贝);
	3.传指针的指针:调用形参时,为实参的指针的指针的拷贝.此时可以修改指针的指针里面的内容(即指针).但是
		指针的指针是该不动的(因为是一份拷贝).

#### 2.2.2 函数指针

1.C中的函数名直接对应于函数生成的指令代码在内存中的首地址,因此函数名可以直接赋值给指向函数的指针.

2.调用函数实质为"跳转指令+参数传递处理+返回地址入栈".最核心的操作是将函数生成的目标代码的首地址赋给CPU的PC寄存器.

3.因为函数调用的本质是跳转到某一个地址单元的code去执行,因此可以调用一个"根本不存在的函数实体".

**1.定义一个函数指针---用的较少**

	int (*pAdd)(int, int); //定义一个函数指针pAdd
	int add(int x, int y)
	{
		.../*一个函数*/
	}

	pAdd = add; //函数指针的使用.

**2.定义一个函数指针类型---常用**

	typedef int (*test_func)(int a, int b); //定一个函数指针类型
	
	int add(int x, int y)
	{
		...
	}

	int sum(int x, int y)
	{
		...
	}

	test_func func_add = NULL; //由函数指针类型定义一个函数指针func_add
	func_add = add; //给函数指针赋值
	func_sum = sum; //给函数指针赋值

### 2.3 C语言关键词

#### 2.3.1 const

const主要用于标识只读,防止代码被无意的修改.

const int a:

	const int a; //表示变量a的内容不能被修改,只读属性.

	const int a; //声明时没有被赋值,此时a被自动初始化为0.
	a = 2; //编译时会报错"assignment of read-only variable a"

int const a--->和const int a是一样的功能

const int *a:

	const int *a; //表示a指向的对象为一个常量,不能通过"*a"来修改,但是可以给指针a重新赋值,使其指向不同的对象.
	
	int b = 2;
	const int *a;
	a = &b; //正确的,通过给a赋值,指向b这个对象.
	*a = 3; //编译时会报错"assignment of read-only location '*a'".内容不能被修改.

int * const a:

	int * const a; //表示a地址为一个常量,不能被重新赋值.但是可以修改a的内容.

	int * const a; //如果没有被初始化,系统会自动分配地址(为非空)
	*a = 2; //可以修改该地址指向的内容.

	int b = 2;
	a = &b; //编译时会报错"assignment of read-only variable 'b'"

int const * const a:

	int const * const a; //表示a地址为一个常量(不能更改a指向的地址),
						 //且a指向的值也为一个常量(不能通过*a来修改).

	int b = 2;
	int const * const a = &b; //如果没有被初始化,其值为0.此处为2.

#### 2.3.2 static作用

1.函数体内:声明为static(静态)的变量在该函数被调用过程中维持其值不变;放在静态存储区,因此一直存在,但作用域仍为局部作用域.

2.在模块内(e.g.文件内)但在函数体外:声明为静态的变量可以被模块内所有函数访问,但是不能被模块内其他函数访问;

3.在模块内:一个被声明为静态的函数只能被该模块内的其他函数调用.

### 2.4 编程要点

#### 2.4.1 C程序的存储空间布局

**1.C程序由以下几部分组成:**

1)正文段---也叫代码段(code segment/text segment):存放代码的地方.通常是可共享的,所以即使频繁执行的程序(e.g.文本编辑器、C编译器和Shell等)也只需一份副本,而且通常设置为只读.保存在磁盘上.

2)初始化数据段---通常称为数据段:包含程序中需要明确赋初值的变量且非0(e.g. int maxcount = 99;).存放程序中已初始化的全局变量(初始化为非0).保存在磁盘上.

3)未初始化数据段(bss段)---也称为常量区或全局区:该段数据不指定初值也可(或者初始化为0).在执行程序之前,内核会将该段中的数据初始化为"0"或"NULL".该段存放未初始化的全局变量,因为不需要指定初值,因此不会保存在磁盘上.

4)栈(stack):存放临时变量,函数地址或环境上下文信息等.Stack空间由操作系统自动分配/释放.Stack空间有限.

5)堆(heap):动态存储分配.位于未初始化数据段(bss)和栈(stack)之间.Heap空间由程序员手动分配/释放.Heap是有很大的自由存储区.

**2.C程序存储空间的排布**

			高地址______________
				
				命令行参数和环境变量
				______________
					栈			
				..............
					栈往下增长		
			
					堆往上增长
				..............
					堆
				______________
			
				未初始化数据段	由exec初始化为0---不会保存在磁盘上
					(bss)
				______________
				初始化数据段			由exec从
				______________
				正文					程序中读入
		   低地址______________

#### 2.4.2 数组指针和指针数组

**数组指针**

数组指针为一个指针,指向一个数组.

	int (*p)[n]; //声明一个数组指针p,指针p指向一个一维数组,长度为n.p+1是跨过n个整型数据的长度.

举例:

	char a[MAX]; //一个数组
	char (*pb)[MAX] = &a; //数组指针pb被赋值为&a.类似二维数组.

例子:

	#include <stdio.h>
	void main()
	{
		char a[5] = {'a', 'b', 'c', 'd', '\0'};
		char *p = a;
		char (*point_to_str)[5]; //声明一个数组指针
		point_to_str = &a; //给数组指针赋值
		printf("0x%x\n0x%x\n", &p, &point_to_str); //打印出两个指针的地址.
			/*因为栈是从上往下涨(高地址往低地址涨),因此两个指针的地址为:
				0x1245044
				0x1245040
			*/
		printf("%s\n%s\n", p, point_to_str);
			/*
				结果为:
					abcd
					abcd
			*/
	}

**指针数组**

	int *p[n]; //指针数组.p内部有n个指针类型的数组元素.执行p+1时,指向下一个数组元素.