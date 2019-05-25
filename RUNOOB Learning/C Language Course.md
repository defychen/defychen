# C Language Course

# 1. C基础教程

## Chapter 1. 简介

## Chapter 2. 环境设置

## Chapter 3. 程序结构

## Chapter 4. 基本语法

## Chapter 5. 数据类型

## Chapter 6. 变量

## Chapter 7. 常量

## Chapter 8. 存储类

## Chapter 9. 运算符

## Chapter 10. 判断

## Chapter 11. 循环

## Chapter 12. 函数

## Chapter 13. 作用域规则

## Chapter 14. 数组

## Chapter 15. enum

## Chapter 16. 指针

## Chapter 17. 函数指针与回调函数

### 17.1 函数指针

函数指针:指向函数的指针变量.函数指针可以调用函数、传递参数.

	typedef int (*func_ptr)(int, int);
	/*
		声明一个函数指针func_ptr类型.指向的函数有两个参数(int,int),返回值为int类型的函数.
		使用方法如下:
		在一个函数里面,需要使用func_ptr声明一个函数指针变量:
			func_ptr f = func;	//使用func_ptr函数指针类型声明一个函数指针变量f,指向func函数.
	*/

实例1---直接在函数内部声明一个函数指针变量指向某个函数:

	#include <stdio.h>

	int max(int x, int y)
	{
		return (x > y ? x : y);
	}
	
	int main()
	{
		int (*p)(int, int) = max;
		/*
			声明一个函数指针变量p,将max函数赋值给该函数指针.
			PS:此处使用max或&max是一样的.
			也可以:
			int (*p)(int, int); //先声明一个函数指针
			p = max;			//在给函数指针赋值
		*/
		int a, b, c, d;
	
		printf("Please input thress number:");
		scanf("%d %d %d", &a, &b, &c);
	
		d = p(p(a, b), c);
		printf("The max number is: %d\n", d);
		return 0;
	}

实例2---先typedef(重定义)一个函数指针类型,再由该类型去声明一个函数指针变量.

	#include <stdio.h>
	
	int max(int x, int y)
	{
		return (x > y ? x : y);
	}
	
	typedef int (*p)(int, int);	//声明一个函数指针类型p
	
	int main()
	{
		p pfunc = max;	//使用函数指针类型定义一个函数指针变量pfunc,并将max赋值给该函数指针变量
		int a, b, c, d;
	
		printf("Please input thress number:");
		scanf("%d %d %d", &a, &b, &c);
	
		d = pfunc(pfunc(a, b), c);
		printf("The max number is: %d\n", d);
		return 0;
	}

### 17.2 回调函数

回调函数:函数指针变量作为某个函数的参数,此时该函数指针指向的函数就叫回调函数(该函数是在某函数中通过函数指针来调用).

知乎的解说:

	你到一个商店买东西,刚好你要的东西没有货.于是你在店员那里留下了你的电话,过了几天店里有货了,店员就打了
	你的电话,然后你接到电话后就到店里去取了货.在这个例子里,你的电话号码就叫回调函数,你把电话留给店员就叫
	登记回调函数,店里后来有货了叫做触发了回调关联的事件,店员给你打电话叫做调用回调函数,你到店里去取货叫做
	响应回调事件.

实例1---直接使用函数指针变量作为函数的参数

	#include <stdlib.h>
	#include <stdio.h>
	
	void populate_array(long *array, size_t arraySize, long (*getNextValue)(void))
	{	
		/*
			"long (*getNextValue)(void)":直接声明了一个函数指针变量getNextValue.
			后面可以直接使用该变量,如下:
		*/
		for (size_t i=0; i<arraySize; i++)
			array[i] = getNextValue();
	}
	
	long getNextRandomValue(void)
	{
		return rand();
	}
	
	int main()
	{
		long myArray[10];
		populate_array(myArray, 10, getNextRandomValue);
		for (int i=0; i<10; i++) {
			printf("%d ", myArray[i]);
		}
	
		printf("\n");
		return 0;
	}

	VS2012运行结果为:41 18467 6334 26500 19169 15724 11478 29358 26962 24464

实例2---先typedef(重定义)一个函数指针类型,再由该类型去声明一个函数指针变量作为函数的参数.

	#include <stdlib.h>
	#include <stdio.h>
	
	typedef long (*p)(void); //声明一个函数指针类型
	
	void populate_array(long *array, size_t arraySize, p getNextValue)
	{
		/*
			p getNextValue:由函数指针类型声明一个函数指针变量,后面使用该变量调用函数.比较符合常规.
		*/
		for (size_t i=0; i<arraySize; i++)
			array[i] = getNextValue();
	}
		
	long getNextRandomValue(void)
	{
		return rand();
	}
	
	int main()
	{
		long myArray[10];
		populate_array(myArray, 10, getNextRandomValue);
		for (int i=0; i<10; i++) {
			printf("%d ", myArray[i]);
		}
		
		printf("\n");
		return 0;
	}

	VS2012运行结果为:41 18467 6334 26500 19169 15724 11478 29358 26962 24464

## Chapter 18. 字符串

C语言中,字符串实际上是使用null字符(即'\0')终止的一堆字符数组.因此,一个字符串的组成字符包括从起始到null结尾之前的字符.

### 18.1 字符串的初始化

	char greeting[6] = {'H', 'e', 'l', 'l', '0', '\0'};	//greeting包含"Hello"和结尾的'\0'
	//也可以写成:
	char greeting[] = "Hello";	//C语言会在初始化数组时自动在末尾加上'\0'.
	//也可以写成:
	char *greeting = "Hello";

此时的占用内存情况:

![](images/char_in_memory.png)

### 18.2 字符串操作函数

1.strcpy(s1, s2)

	strcpy(s1, s2):复制字符串s2到字符串s1.

2.strcat(s1, s2)

	strcat(s1, s2):连接字符串s2到字符串s1的末尾(会自动去掉s1的'\0',然后再连接).

3.strlen(s1)

	strlen(s1):返回字符串s1的长度(即字符数量,结尾的'\0'是不计算在内的).

4.strcmp(s1, s2)

	strcmp(s1, s2):s1和s2是相同的,则返回0;s1<s2则返回小于0;s1>s2则返回大于0.

5.strchr(s1, ch)

	strchr(s1, ch):返回一个指针,指向字符串s1中字符ch第一次出现的位置.

6.strstr(s1, s2)

	strstr(s1, s2):返回一个指针,指向字符串s1中字符串s2第一次出现的位置.

### 18.3 实例

	#include <stdio.h>
	#include <string.h>
	 
	int main ()
	{
		char str1[12] = "Hello";
		char str2[12] = "World";
		char str3[12];
		char *str4 = "helloworld";
		int  len ;
	
		printf("%d \n", strlen(str4));	//结果为:10
		strcpy(str3, str1);
		printf("strcpy( str3, str1) :  %s\n", str3 );	//结果为:Hello
	 
		strcat( str1, str2);
		printf("strcat( str1, str2):   %s\n", str1 );	//结果为:HelloWorld

		len = strlen(str1);
		printf("strlen(str1) :  %d\n", len );	//结果为:10
	 
		return 0;
	}

## Chapter 19. 结构体

### 19.1 结构体定义

**1.常规定义**

	1.既有标签,又有变量:
		struct SIMPLE {	//SIMPLE为结构体标签
			int a;	//结构体成员
			char b;
			double c;
		} s1;	//在定义结构体的同时声明了一个结构体变量s1
	2.无标签,有变量:
		struct {	//由于无标签,后续想在声明一个结构体变量不方便--->此种方法用的比较少
			...
		} s1;	//在定义结构体时声明了一个结构体变量s1
	3.仅有标签,没有定义变量:
		struct SIMPLE {	//SIMPLE为结构体标签
			...
		};
		struct SIMPLE t1, t2[20], *t3;	//使用标签来声明一些结构体变量
		PS:C++中可以直接使用SIMPLE(省略签名的struct).
	4.使用typedef为结构体取一个新的名字:
		typedef struct {
			...
		} Simple2;	//为结构体取一个新的名字Simple2(类似创建一个新类型Simple2)
		Simple2 u1, u2[20], *u3;	//使用新名字来声明一些结构体变量

**2.结构体包含结构体**

	1.包含其他结构体:
		struct COMPLEX {
			char str[100];
			struct SIMPLE a;	//包含其他结构体struct SIMPLE
		};
	2.包含指向自己类型的指针,常用于实现链表和数等:
		struct NODE {
			char str[100];
			struct NODE *next_node;	//包含自身的结构体指针
		};

**3.结构体互相包含--->用的比较少**

	struct B;	//先对结构体B进行不完整声明
	
	struct A {
		struct B *partner;	//结构体A中包含指向结构体B的指针
		...
	};

	struct B {
		struct A *partner;	//A声明完后,在进行B的完整声明.此时包含结构体A的指针
		...
	};

### 19.2 结构体变量的初始化

定义时进行初始化:

	#include <stdio.h>
	
	struct Books {
		char title[50];
		char author[50];
		char subject[100];
		int book_id;
	} book = {"C Program", "RUNOOB", "Program language", 123456};
	// {...}中的内容会依次赋值给结构体中的成员.
	
	int main()
	{
		printf("title: %s\nauthor: %s\nsubject: %s\nbook_id: %d\n", book.title, book.author, 
			book.subject, book.book_id);
	}
	//结果为:
	title: C Program
	author: RUNOOB
	subject: Program language
	book_id: 123456

### 19.3 访问结构体成员

**1.使用运算符"."**

	struct Books {	//结构体定义
		char title[50];
		char author[50];
		char subject[100];
		int book_id;
	};

	struct Books book;	//声明一个结构体变量
	strcpy(book.title, "C Programming");	//访问成员并复制字符串到该成员
	strcpy(book.author, "Defy");
	strcpy(book.subject, "C Programming Tutorial");
	book.book_id = 98456;

**2.使用运算符"->"--->针对指针**

	struct Books {	//结构体定义
		char title[50];
		char author[50];
		char subject[100];
		int book_id;
	};

	void printBook(struct Books *bookPtr);	//接收一个结构体指针作为参数

	int main()
	{
		struct Books book;	//声明一个结构体变量
		strcpy(book.title, "C Programming");	//访问成员并复制字符串到该成员
		strcpy(book.author, "Defy");
		strcpy(book.subject, "C Programming Tutorial");
		book.book_id = 98456;

		printBook(&book);
	}

	void printBook(struct Books *bookPtr)
	{
		printf("Title: %s\n", bookPtr->title);
		printf("Author: %s\n", bookPtr->author);
		printf("Subject: %s\n", bookPtr->subject);
		printf("book_id: %s\n", bookPtr->book_id);
	}

### 19.4 位域

位域主要用于区分字节中二进制位的作用.可以节省存储空间.

**1.位域的定义和位域变量的说明**

	struct bs {	//位域也是以struct开始,bs为标签
		int a : 8;	//位域列表,表示方法为:类型 位域名:位域宽度(二进制位的个数)
		int b : 2;
		int c : 6;
	} data;		//定义一个位域变量data,共占用2字节.位域a占8-bit,位域b占2-bit,位域c占6-bit.

**2.无名位域(也叫空位域)**

	struct bs {
		unsigned a : 4;
		unsigned   : 4;	//无名位域,仅用于占位(此处占位4-bit),不能使用.更常用的为命名为reserved
		unsigned b : 4;
		unsigned c : 4;
	};

**3.位域的访问--->与结构体类似**

	#include <stdio.h>
	
	struct bs {
		unsigned a : 1;
		unsigned b : 3;
		unsigned c : 4;
	}bit, *pbit;
	
	int main()
	{
		bit.a = 1;	//给位域赋值,不能超过位域的允许范围,即二进制位数表示的范围.此处1-bit,值为0/1
		bit.b = 7;	//此处为3-bit,值为0~7
		bit.c = 15; //此处为4-bit,值为0~15
		printf("%d, %d, %d\n", bit.a, bit.b, bit.c);
		pbit = &bit;
		pbit->a = 0;
		pbit->b &= 3;	//按位域
		pbit->c |= 1;	//按位或
		printf("%d, %d, %d\n", pbit->a, pbit->b, pbit->c);
	}
	//结果为:
	1, 7, 15
	0, 3, 15

## Chapter 20. 联合体(union)

联合体(union)是一种特殊的数据类型,是一种在相同的内存位置存储不同的数据类型.联合体中可包含多个成员,但任何时候只能有一个成员带有正确的值.

### 20.1 定义联合体

	union Data {	//Data:联合体标签名
		int i;
		float f;
		char str[20];
	} data;	//在定义联合体时声明联合体变量data
	/*
		此处表示:在同一时刻,union Data变量(相同的内存位置)能存储整数或浮点数或字符串中的一个.
		联合体占用的内存是最大的成员占用的内存,此处为占用20-byte的内存空间.使用sizeof(data)可以得到.
	*/

### 20.2 访问联合体成员

	#include <stdio.h>
	#include <string.h>
	
	union Data {
		int i;
		float f;
		char str[20];
	};
	
	int main()
	{
		union Data data;
		printf("Memory size occupied by data: %d\n", sizeof(data)); //可以得到联合体占用内存为20
	
		data.i = 10;	//访问联合体变量和结构体类似,指针也可以使用"->"
		printf("data.i : %d\n", data.i);
		data.f = 220.5;
		printf("data.f: %f\n", data.f);
		strcpy(data.str, "C Programming");
		printf("data.str: %s\n", data.str);
	}
	//结果为:
		Memory size occupied by data: 4
		data.i : 10
		data.f: 220.500000
		data.str: C Programming

## Chapter 21. 位域

## Chapter 22. typedef

## Chapter 23. 输入和输出

## Chapter 24. 文件读写

## Chapter 25. 预处理器

## Chapter 26. 头文件

## Chapter 27. 强制类型转换

## Chapter 28. 错误处理

## Chapter 29. 递归

## Chapter 30. 可变参数

## Chapter 31. 内存管理

## Chapter 32. 命令行参数

## Chapter 33. 排序算法

## Chapter 34. 语言实例

## Chapter 35. 经典100例

***

# 2. C标准库

## Chapter 1. <assert.h>

## Chapter 2. <ctype.h>

## Chapter 3. <errno.h>

## Chapter 4. <float.h>

## Chapter 5. <limits.h>

## Chapter 6. <locale.h>

## Chapter 7. <math.h>

## Chapter 8. <setjmp.h>

## Chapter 9. <signal.h>

## Chapter 10. <stdarg.h>

## Chapter 11. <stddef.h>

## Chapter 12. <stdio.h>

## Chapter 13. <stdlib.h>

## Chapter 14. <string.h>

## Chapter 15. <time.h>
