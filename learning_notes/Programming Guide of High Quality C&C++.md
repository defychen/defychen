# Programming Guide of High Quality C/C++

## Chapter 1 文件结构

	.h:头文件,用于保存程序的声明(declaration);
	.c:定义(definition)文件,用于保存程序的实现(implementaion).
	.cpp:C++程序的定义文件.

### 1.1 版权和版本的声明

版权和版本的声明位于头文件和定义文件的开头.

	/***********************************************************************************
	* Copyright (c) 2018 xxx Corp. All Rights Reserved
	* xxx(一些公司信息的描述,e.g.公司协议,一些规定)
	* File: xxx.h
	* Description: this file is used to define some macros and structures
	* 		for xxx
	* (其他信息)
	***********************************************************************************/

### 1.2 头文件的结构

头文件包括三部分内容:

1.头文件开头处的版权和版本声明;

2.预处理模块;

3.函数和类结构声明等.

	//版权和版本声明见1.1中的
	
	#ifndef _GRAPHICS_H_	//防止"_GRAPHICS_H_"即头文件graphics.h被重复引用
	#define _GRAPHICS_H_
	
	#include <math.h>	//引用标准库的头文件(编译器将从标准库目录开始搜索)
	...
	#include "myheader.h"	//引用非标准库的头文件(编译将从用户的工作目录开始搜索)
	...
	void Function1(...);	//全局函数声明.
					//(不提倡使用全局变量,头文件中尽量不要出现类似extern int value这类声明.)
	...
	class Box	//类结构声明
	{
	...		//类中只做成员函数的声明,不做定义(也就是成员函数的实现)
	};
	#endif

### 1.3 定义(实现)文件的结构

定义(实现)文件包括三部分内容:

1.定义(实现)文件开头处的版权和版本声明;

2.对一些头文件的引用;

3.程序的实现体(包括数据和代码).

	//版权和版本声明见1.1中的
	
	#include "graphics.h"	//引用头文件

	//全局函数的实现体
	void Function1(...)
	{
		...
	}

	//类成员函数的实现体
	void Box::Draw(...)
	{
		...
	}

### 1.4 目录结构

头文件一般保存于"inc"目录.(inc是include的缩写)

定义(实现)文件一般保存于"src"目录.(src是source的缩写)

如果某些头文件是私有的,不会被用户的程序直接引用,没必要公开其"声明".应该将这些私有的头文件也放在"src"目录.

***

## Chapter 2 程序的版式

### 2.1 空行

1.每个类声明之后、每个函数定义结束之后都要加空行;

	//空行
	void Function1(...)
	{
		...
	}
	//空行
	void Function2(...)
	{
		...
	}
	//空行
	void Function3(...)
	{
		...
	}

2.函数体内,逻辑上密切相关的语句之间不加空行,其他地方用空行分隔.

	//空行
	while(condition)
	{
		statement1;
		//空行
		if (condition)
		{
			statement2;
		}
		else
		{
			statement3;
		}
		//空行
		statement4;
	}
	
### 2.2 代码行

1.一行代码只做一件事情.e.g.只定义一个变量,或只写一条语句.

2.尽可能在定义变量的同时初始化该变量(就近原则).防止引用未被初始化的变量,导致程序错误.

3.if、for、while、do等语句各占一行,不论执行语句有多少都要加{},防止书写失误.

	/*******************************************************/
	int width = 10;
	int height = 10;
	int depth = 10;
	/*******************************************************/
	x = a + b;
	y = c + d;
	z = e + f;
	/*******************************************************/
	if (width < height)
	{
		dosomething();
	}
	/*******************************************************/
	for (initialization; condition; update)
	{
		dosomething();
	}
	//空行
	other();

### 2.3 代码行内的空格

1.关键字之后要留空格(cont、virtual、inline、case,以及if、for、while等);

2."("后紧跟,")"、","、";"前紧跟,且不留空格;

3.","和不是一行结束的";"之后要留空格;

4."="、"+="、">="、"<="、"+"、"*"、"%"、"&&"、"||"、"<<"、"^"等二元操作符的前后应加空格;

5.对于比较长的for语句和if语句,为了紧凑应当适当的去掉一些空格.e.g.for (i=0; i<10; i++);和if((a<=b) && (c<=d));

	void Func1(int x, int y, int z);
	if (year >= 200)
	if ((a>=b) && (c <= d))
	for (i=0; i<10; i++)
	x = a < b ? a : b;
	int  *x = &y;
	array[5] = 0;
	a.Functio();
	b->Function();

### 2.4 对齐

程序的分界符"{"、"}"应独占一行,并且位于同一列;

	if (condition)
	{
		...
	}
	else
	{
		...
	}

	//嵌套的{}
	{
		...
		{
			...
		}
		...
	}

### 2.5 长行拆分

长表达式要在低优先级操作符处拆分成新行,操作符放在新行之首(以便突出操作符).拆分的新行要进行适当的缩进.

	if ((very_longer_varialbe1 >= very_longer_varialber2)
		&& (very_longer_varialber3 <= very_longer_varialber4)
		&& (very_longer_varialber5 <= very_longer_varialber6))
	{
		dosomething();
	}

	virtual CMatrix CMultiplyMatrix(CMatrix leftMatrix,
									CMatrix rightMatrix);

	for (very_longer_initialization;
		very_longer_condition;
		very_longer_update)
	{
		dosomething();
	}

### 2.6 修饰符的位置

修饰符"*"和"&"应该紧靠变量名.

	char *name;
	int *x, y;	//如果靠近数据类型可能会引起误解,认为此处的y是指针变量.

### 2.7 注释

1.注释的位置应与被描述的代码相邻,可以放在代码的上方或者右方,不可放在下方.

2.当代码比较长,特别是有多重嵌套时,应当在一些段落的结束处加注释,便于阅读.

	/************************************************************************
	* Function: xxx()
	* Description:
	*    This function is used to ...
	* Input:
	*    xxx
	* Output:
	*    xxx
	* Returns:
	*    0:RET_SUCCESS
	*    1:RET_FAILURE
	*************************************************************************/
	void xxx()
	{
		...
	}

	if (...)
	{
		...
		while(...)
		{
			...
		} //end of while
		...
	} //end of if

### 2.8 类的版式

类中设计时,将public类型的函数写在前面,而将private类型的数据写在后面.即使所谓的"以行为为中心"

	class A
	{
		public:
			void Func1(void);
			void Func2(void);
			...
		private:
			int i, j;
			float x, y;
			...
	};

***

## Chapter 3 命名规则

### 3.1 简单的Windows应用程序命名规则

1.类名和函数名用大写字母开头的单词组合而成.

	class Node;					//类名
	class LeafNode;				//类名
	void Draw(void);			//函数名
	void SetValue(int value);	//函数名

2.变量和参数用小写字母开头的单词组合而成.

	BOOL flag;
	int drawMode;

3.常量全用大写的字母,用下划线分割单词.

	const int MAX = 100;
	const int MAX_LENGTH = 100;

4.静态变量+前缀s_(表示static)

	void Init(...)
	{
		static int s_initValue;	//静态变量
		...
	}

5.全局变量+前缀g_(表示global)

	int g_howManyPeople;
	int g_howMuchMoney;

6.类的数据成员+前缀m(表示member)

	void Object::SetValue(int width, int height)
	{
		m_width = width;
		m_height = height;
	}

7.某些软件库中的一些标识符为了避免和其他软件库中的冲突,会为标识符前+反映软件性质的前缀

	OpenGL的所有库函数均以"gl"开头,所有常量(或宏定义)均以"GL"开头

### 3.2 简单的Unix应用程序命名规则

Unix应用的标识符通常采用"小写+下划线"的方式.e.g. add_child.

***

## Chapter 4 表达式和基本语句

### 4.1 if语句

1 布尔变量与零值的比较

不可将布尔变量直接与TRUE、FALSE或者1、0进行比较.

	//因为零值为"假"(FALSE);非零为"真"(TRUE).但是TRUE究竟是什么没有统一的标准.
	
	//布尔与零值比较的标准if语句:(flag为一个bool变量名)
	if (flag)	//表示flag为真
	if (!flag)	//表示flag为假
	
2 整型变量与零值的比较

应当将整型变量用"=="或"!="直接与0比较

	//整型与零值比较的标准if语句:(value为一个int变量名)
	if (value == 0)
	if (value != 0)

3 浮点变量与零值的比较

不可将浮点变量用"=="或"!="与任何数字比较,应该设法转化为">="或"<="形式.

	//浮点与零值比较的标准if语句:(x为一个浮点变量名)
	if ((x>=-EPSINON) && (x<=EPSINON))	//EPSINON是允许的误差(即精度)

4 指针变量与零值的比较

应当将指针变量用"=="或"!="与NULL比较(尽管NULL的值与0相同,但是两者意义不同)

	//指针与零值比较的标准if语句:(p为一个指针变量名)
	if (p == NULL)	//p与NULL显示比较,强调p是一个指针
	if (p != NULL)

	PS:不要写成
	if (p)	//容易让人误解p是布尔变量
	if (!p)
	if (p == 0)	//容易让人误解p是整型变量
	if (p != 0)

### 4.2 循环语句的效率

1.多重循环中,如果可能,应当将循环多次的放在循环的最内层;循环少次的放在最外层,减少CPU跨切循环层的次数.

	//错误
	for (row=0; row<100; row++)
	{
		for (col=0; col<5; col++)
		{
			sum = sum + a[row][col];
		}
	}
	//正确
	for (col=0; col<5; col++)
	{
		for (row=0; row<100; row++)
		{
			sum = sum + a[row][col];
		}
	}

2.如果循环体内存在逻辑判断,并且循环次数很大,宜将逻辑判断移到循环体的外面.

	//效率低但程序简洁.次数大时是错误
	for (i=0; i<N; i++)
	{
		if (condition)
			dosomething();
		else
			dootherthing();
	}
	//效率高但程序不简洁.次数大时是正确
	if (condition)
	{
		for (i=0; i<N; i++)
			dosomething();
	}
	else
	{
		for (i=0; i<N; i++)
			dootherthing();
	}

### 4.3 for语句的循环控制变量

1.for循环体内不要修改循环变量

2.for循环的循环控制变量的取值采用"半开半闭区间"写法

	//半开半闭区间写法(0 =< x < N)---正确
	for (int x=0; x<N; x++)
	{
		...
	}

	//闭区间写法(0 =< x <= N-1)---错误
	for (int x=0; x<=N-1; x++)
	{
		...
	}

### 4.4 switch语句

	switch(varialbe)
	{
		case value1:
			...
			break;		//每一个case都应该加break,除非有意需要这样做(需要执行后面的case)
		case value2:
			...
			break;
		...
			default:	//default也是需要的
				break;
	}

### 4.5 goto语句

	{
		...
		{
			...
			{
				...
				goto error;	//能从多重循环体中直接跳出去,不需要多次的break语句
			}
		}
	}
	error:
		...
	PS:goto应该少用,但不是禁用.

***

## Chapter 5 常量

C语言用#define来定义常量(称为宏常量);C++语言一般使用const来定义常量(当然也可以用#define来定义)

	#define定义的宏常量是全局的.

### 5.1 const和#define定义常量的比较

1.const常量有数据类型,宏常量是没有数据类型的.编译器可以对const常量进行数据类型安全检查,对#define的常量只进行字符替换,替换时可能会产生意料不到的错误(边际效应).

2.有些集成化的调试工具可以对const常量进行调试,但不能对宏常量进行调试.

C++程序中,只是用const常量而不使用宏常量,const常量完全取代了宏常量.

### 5.2 常量定义规则

需要对外公开的常量放在头文件中,不需要对开公开的常量放在定义(实现)文件的头部.

	//密切相关的常量的处理
	const float RADIUS = 100;
	const float DIAMETER = RADIUS * 2;

### 5.3 类中的常量

1.类中的const数据成员

const数据成员只在某个对象的生存期内是常量,但对整个类而言却是可变的.因为类可以创建多个对象,不同的对象其const数据成员的值可以不同.

	//类是没有常量概念的,类的const数据成员属于某个对象.因此不能在类的声明中初始化const数据成员
	class A
	{
		const int SIZE = 100;	//错误,类的声明中不能初始化const数据成员
		int array[SIZE];	//错误,未知的SIZE
	};
	
	/*************************************************************************/
	//const数据成员的初始化只能在类的构造函数的初始化表中进行.
	class A
	{
		...
		A(int size);	//构造函数
		const int SIZE;	//const成员变量
	};

	A::A(int size)	: SIZE(size)	//构造函数的初始化表.SIZE会被赋值为size.
	{
		...
	}
	A a(100);	//对象a的SIZE的值为100
	A b(200);	//对象b的SIZE的值为200

2.类中的枚举常量

	class A
	{
		...
		enum {SIZE1 = 100, SIZE2 = 200};	//枚举常量.该常量属于该类
		int array1[SIZE1];
		int array2[SIZE2];
	};

	PS:枚举常量是不会占用对象的存储空间,在编译时被全部求值.
		枚举常量的特点:它隐含的数据类型是整型.

***

## Chapter 6 函数设计

### 6.1 参数的规则

1.参数的书写要完整

	void SetValue(int width, int height);	//good
	void SetValue(int, int);			//bad
	float GetValue(void);				//good
	float GetValue();					//bad

2.参数命名要恰当,顺寻要合理

一般的拷贝函数是目的参数在前,源参数在后.而且如果参数仅做输入用,还应该在类型前+const,防止被意外修改.

	void StringCopy(char *strDestination, const char *strSource);

3.如果是以值传递,C++中使用"const &"参数形式.其实是通过引用来传递,效率高.

4.避免参数过多(<=5为好),不要使用类型和数目不确定的参数(e.g.printf函数)

### 6.1 返回值的规则

不要省略返回值的类型

	C语言中,凡没有返回值类型说明的函数,一律自动按整型处理.但容易被误解为void类型.

### 6.2 函数内部实现的规则

return语句不可返回指向"栈内存"的"指针"或者"引用",因为该内存在函数体结束时被自动销毁

	char *func(void)
	{
		char str[] = "hello world";	//str的内存位于栈上
		...
		return str;	//错误.str会被销毁
	}

	/********************/
	int temp = x + y;
	return temp;	//这种属于返回一个整型的值,因此不会有问题.

### 6.3 使用断言

程序的Debug版本:用于内部调试.

程序的Release版本:用于发行给用户使用.

断言assert是仅在Debug版本中起作用的宏,用于检查"不应该"发生的情况.如果assert的参数为假,程序就会中止;为真程序正常运行.

	void *memcpy(void *pvTo, const void *pvFrom, size_t size)
	{
		assert((pvTo!=NULL) && (pvFrom!=NULL));	//使用断言
		byte *pbTo = (byte *)pvTo;	//防止改变pvTo的地址
		byte *pbFrom = (byte *)pvFrom;	//防止改变pvFrom的地址
		while(size-- > 0)
		{
			*(pbTo++) = *(pbFrom++);
			/*
				*pbTo++ = *pbFrom++;
			也正确,因为pbTo++优先级高于*.
			*/
		}
		return pvTo;
	}

	PS:断言assert不是函数,而是宏.

断言assert一般在函数的入口处,用于检查参数的有效性(合法性).

### 6.4 引用和指针

	int m;
	int &n = m;	//n是m的引用(别名).n和m是一个东西.

引用的规则:

1.引用被创建的同时必须被初始化;

2.引用必须与合法的存储单元关联,不能有NULL引用;

3.一旦引用被初始化,就不能改变引用的关系.

	int i = 5;
	int j = 6;
	int &k = i;
	k = j;	//此时k和i的值都变成了6.

**1.值传递**

	void func1(int x)
	{
		x = x + 10;	//func1函数体中的x是外部传进来变量的一份拷贝.改变该x的值不会影响外部变量
	}

	...
	int n = 0;
	func1(n);
	cout << "n = " << n << endl;	//此时n=0;

**2.指针传递**

	void func2(int *x)
	{
		(*x) = (*x) + 10;	//func1函数体中的x是指向外部变量的指针.改变该指针内容会导致外部变量的值发生改变
	}

	...
	int n = 0;
	func2(&n);
	cout << "n = " << n << endl;	//此时n=10;

**3.引用传递**

	void func3(int &x)
	{
		x = x + 10;	//func1函数体中的x是外部变量的引用.此时x和外部变量是同一个东西,改变x外部变量也会改变
	}

	...
	int n = 0;
	func3(n);
	cout << "n = " << n << endl;	//此时n=10;

***

## Chapter 7 内存管理

***

## Chapter 7 内存管理