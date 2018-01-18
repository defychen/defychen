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

### 7.1 内存分配方式

1.在静态存储区分配.

	内存在程序编译的时候就已经分配好,这块内存在程序的运行期间都存在.e.g.全局变量、static变量,常量字符串

2.在栈上创建.

	函数内的局部变量是在栈上创建,函数执行结束自动释放这些存储单元.栈上分配的内存容量有限.

3.从堆上分配,也叫动态内存分配.

	使用malloc或者new申请的内存,需要程序员自己free或delete释放内存.使用灵活,容量一般较大.

### 7.2 常见的内存对策

1.如果指针p是函数的参数,那么在函数的入口处用assert(p != NULL)进行检查;

2.使用malloc或new申请内存后,应该立即检查指针值是否为NULL,防止使用指针值为NULL的内存.

	p = malloc(size);
	if (p == NULL)
	{
		/*some error message*/
	}

3.数组和动态内存一定要赋初值,防止未被初始化的内存作为右值使用.

	p = malloc(size);
	memset(p, 0, size);	//对动态内存进行初始化

4.避免数组或指针的下标越界(多1或少1的情况).

5.动态申请的内存和释放必须配对,防止内存泄漏.

6.用free或delete释放了内存之后,立即将指针设置为NULL,防止产生"野指针".

### 7.3 指针与数组的对比

数组要么在静态存储区被创建(e.g.全局数组),要么在栈上被创建.数组名对应着(而不是指向)一块内存,其地址和容量在生命期内保持不变,只有数组的内容可以改变.

指针是可以随时指向任意类型的内存块,是"可变的".常用指针来操作动态内存.

1.修改内容

	//数组
	char a[] = "hello";	//字符数组a的容量是6个字符,其内容为"hello\0".注意最后有"\0".
	a[0] = 'X';	//数组a的内容是可以修改的.
	cout << a << endl;	//可以正确输出
	
	//指针
	char *p = "world";	//指针p指向常量字符串"world"(位于静态存储区,内容为world\0).
	p[0] = 'X';	//常量字符串的内容是不可以被修改的.编译时不会出错,但是运行时会出错.
	cout << p << endl;

2.内容复制与比较

	//数组
	char a[] = "hello";
	char b[10];
	strcpy(b, a);	//复制字符串
	if (strcmp(b, a) == 0)	//字符串比较

	//指针
	int len = strlen(a);	//求字符串a的长度.为真正的字符数(不包括结束的\0)
	char *p = (char *)malloc(sizeof(char) * (len + 1));	//多分配一个存放"\0"
	strcpy(p, a);
	if (strcmp(p, a) == 0)

3.计算内存容量

	//sizeof可以计算数组的容量(字节数)
	char a[] = "hello world";	//其字节数为12(11+'\0')
	char *p = a;
	cout << sizeof(a) << endl;	//12字节
	cout << sizeof(p) << endl;	//4字节.为计算一个指针变量的字节数.
	//sizeof(char *):为计算一个指针变的字节数,而不是p所指的内容.
	//C/C++没办法知道指针所指的内存容量,除非在申请时记住它.

4.数组作为函数的参数传递

	void func(char a[100])
	{
		cout << sizeof(a) << endl;	//数组会自动退化为同类型的指针.因此为4字节
	}

### 7.4 指针参数传递内存

1.函数的参数是一个指针,该参数指针是不能用来申请动态内存

	void GetMemory(char *p, int num)
	{
		p = (char *)malloc(sizeof(char) * num);
		//指针作为函数参数时,只能修改指针所指向内存的内容,不能为指针参数申请内存.
		//此处申请的内存没有地方会释放,会造成内存泄漏
	}

	void Test(void)
	{
		char *str = NULL;
		GetMemory(str, 100);	//str仍然为NULL
		strcpy(str, "hello");	//运行错误
	}

2.可以使用"指向指针的指针"来作为函数参数申请内存

	void GetMemory2(char **p, int num)
	{
		*p = (char *)malloc(sizeof(char) * num);
		//此处相当于传进来的(**p)的内容(*p)被修改为一段malloc的内存
	}

	void Test2(void)
	{
		char *str = NULL;
		GetMemory2(&str, 100);	//参数为&str,而不是str
		strcpy(str, "hello");
		cout << str << endl;
		free(str);	//释放str指向的内存
	}

3.使用函数的返回值来传递动态内存

	char *GetMemory3(int num)
	{
		char *p = (char *)malloc(sizeof(char) * num);
		return p;
		//指针返回堆内存是可以的,其释放由用户控制
	}

	void Test3(void)
	{
		char *str = NULL;
		str = GetMemory3(100);	//返回的堆内存指针被赋值给了str,此时str指向一段堆内存
		strcpy(str, "hello");
		cout << str << endl;
		free(str);	//释放str指向的内存
	}

4.函数返回值不能返回"栈内存",因为栈内存在函数结束就自动被释放掉

	char *GetString(void)
	{
		char p[] = "hello world";
		return p;	//返回栈内存,编译器会将提出警告
	}

	void Test4(void)
	{
		char *str = NULL;
		str = GetString4();	//str也不是NULL指针,但是内容不是"hello world"而是垃圾
		cout << str << endl;
	}

5.指针指向常量字符串,位于静态存储区(属于"只读"内存块),在程序生命周期内恒定不变

	char *GetString2(void)
	{
		char *p = "hello world";
		return p;	//指针指向常量字符串,位于静态存储区,在程序生命周期内恒定不变
	}

	void Test4(void)
	{
		char *str = NULL;
		str = GetString2();	//str永远不变
		cout << str << endl;
	}
	
### 7.5 野指针

free掉的指针只是将指针所指向的内存给释放掉,但是指针本身并没有被干掉.指针代表的地址仍然不变(非NULL),只是该地址所对应的内存是垃圾,此时指针成了"野指针".

	char *p = (char *)malloc(100);
	strcpy(p, "hello");
	free(p);	//p所指的内存被释放,但是p所指的地址仍然不变
	...
	if (p != NULL)	//此时(p!=NULL)会成立,没有起到防错作用
	{
		strcpy(p, "world");	//出错
	}

1.指针变量在创建的同时应当被初始化.要么为NULL,要么指向合法的内存.

	char *p = NULL;
	char *str = (char *)malloc(100);

2.指针被free或delete后,应该置为NULL.

3.指针超越了变量的作用范围.

	class A
	{
		public:
			void func(void)
			{
				cout << "func of class A" << endl;
			}
	};

	void Test(void)
	{
		A *p;
		{
			A a;
			p = &a;	//{}构成一个语句块,语句块中的局部变量到"}"被自动释放.
		}
		p->func();	//由于a已经消失,p指向a,p成了"野指针".
	}

### 7.6 malloc/free和new/delete的区别

malloc/free是C++/C的库函数,new/delete是C++的运算符.都可用于动态内存的申请和释放.

对于内部数据类型(e.g.int,char...等),malloc/free和new/delete并无区别;

对于非内部数据类型(e.g.类类型等),new执行时会自动调用类的构造函数申请内存并完成初始化,delete执行时会自动调用类的析构函数清除内容并释放内存.malloc和free不具备该功能.

	class Obj
	{
		public:
			Obj(void){cout << "Initialization" << endl;}
			~Obj(void){cout << "Destroy" << endl;}
		void Initialize(void){cout << "Initialization" << endl;}
		void Destroy(void){cout << "Destroy" << endl;}
	};
	/*使用malloc/free的方式*/
	void UseMallocFree(void)
	{
		Obj *a = (Obj *)malloc(sizeof(Obj));	//malloc动态申请内存	
		a->Initialize();		//调用类的初始化函数完成初始化
		...
		a->Destroy();	//调用类的析构函数完成清除工作
		free(a);	//释放内存
	}
	/*使用new/delete的方式*/
	void UseNewDelete(void)
	{
		Obj *a = new Obj;	//会自动调用类的构造函数完成申请动态内存并初始化
		...
		delete a;	//会自动调用类的析构函数完成清除并释放内存
	}

### 7.7 内存耗尽处理

如果在申请动态内存时找不到足够大的内存块,malloc和new将返回NULL指针,宣告内存申请失败.失败处理方式:

1.判断指针是否为NULL,如果是则马上用return语句终止本函数

	void func(void)
	{
		A *a = new A;
		if (a == NULL)
		{
			/*释放多处申请的内存在return*/
			return;	//如果有多处申请了内存,必须先释放再return
		}
	}

2.判断指针是否为NULL,如果是则马上用exit(1)来终止整个程序的运行

	void func(void)
	{
		A *a = new A;
		if (a == NULL)
		{
			cout << "Memory Exhausted" << endl;	//exhausted:耗尽,筋疲力尽
			exit(1);	//终止整个程序的运行
		}
		...
	}

"内存耗尽"测试程序

	void main(void)
	{
		float *p = NULL;
		while(TRUE)
		{
			p = new float[1000000];	//申请1000000个float大小的内存
			cout << "eat memory" << endl;
			if (p == NULL)
			{
				exit(1);	//耗尽了就退出了整个程序
			}
		}
	}
	//这个程序会无休止的运行下去,因为操作系统支持"虚拟内存",内存用完了,自动会用硬盘空间顶替.
	//此时,硬盘会咯吱咯吱的响,但是系统对键盘、鼠标毫无反应.

### 7.8 malloc/free的使用要点

malloc函数原型

	void *malloc(size_t size);

用malloc申请一块长度为length的整数类型的内存程序:

	int *p = (int *)malloc(sizeof(int) * length);
	/*
		注意点:
		1.类型转换.因为malloc返回的类型为"void *",需要进行显示的类型转换
		2.malloc申请内存时,不识别申请的内存是什么类型,它只关心内存的字节数.因此使用sizeof(类型)*length来申请.	
	*/

测试各种类型所占的字节数:

	cout << sizeof(char) << endl;
	cout << sizeof(unsigned char) << endl;
	cout << sizeof(int) << endl;
	cout << sizeof(unsigned int) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(unsigned long) << endl;
	cout << sizeof(float) << endl;
	cout << sizeof(double) << endl;
	cout << sizeof(void *) << endl;

free的函数原型

	void free(void *memblock);

使用

	free(p);	//p为malloc申请后赋值的指针
	/*
		注意点:
		1.如果p是NULL指针,则free对p无论操作多少次都不会出问题;
		2.如果p不是NULL指针,那么对p连续操作两次就会导致程序运行错误.
	*/

### 7.9 new/delete的使用要点

	class Obj
	{
		public:
			Obj(void);	//无参数的构造函数
			Obj(int x);	//带一个参数的构造函数
		...
	};

	void Test(void)
	{
		Obj *a = new Obj;	//调用无参数的构造函数
		Obj *b = new Ojb(1);	//调用带一个参数的构造函数.初值为1
		...
		...
		delete a;
		delete b;
	}

如果用new来创建对象数组,则只能使用无参数的构造函数.

	Obj *objects = new Obj[100];	//创建100个动态对象
	//错误的写法:
	Obj *objects = new Obj[100](1);	//这种写法是错误的

delete释放数组对象

	delete []objects;	//正确的写法
	delete objects;		//错误的写法.相当于只delete objects[0],其他99没有被释放掉.

***

## Chapter 8 C++函数高级特性

待看

***

## Chapter 9 类的构造函数、析构函数与赋值函数

待看

***

## Chapter 10 类的继承与组合

待看

***

## Chapter 11 其他编程经验

**1 使用const提高函数的健壮性**

使用const关键,不仅仅是const常量.而是表示被const修饰的东西受到强制保护,可以预防意外的变动,提高程序的健壮性.

1.1 const修饰函数的参数

const只能修饰输入参数,不能修饰输出参数(否则参数将失去输出功能).

	1.const修饰指针传递输入参数,防止意外地改动该指针,起到保护作用
		void StringCopy(char *strDestination, const char *strSource);
		//此时,如果函数体试图改动strSource的内容,编译器将指出错误.

	2.对于非内部数据类型的输入参数,应该将"值传递"的方式改为"const引用传递",可以提高效率
		void func(A a);	改为 void func(const A &a);
		//对于非内部数据类型的"值传递",由于函数将需要产生临时对象复制该参数,需要消耗临时对象的构造、复制、析构时间.
		//采用"引用传递"仅借用下参数的别名,不需要产生临时对象.在加上const修饰,防止参数被修改.达到与值传递相同的目的

	3.对于内部数据类型的输入参数,"值传递"就不需要改为"const引用传递"
		void func(int x); 不应该改为 void func(const int &x);
		//因为内部数据类型在复制临时参数时,不需要构造、析构的时间.复制也很快,因此没有必要.

1.2 const修饰函数的返回值

const修改函数的指针返回值,表示函数的返回值(即指针)的内容不能被修改,而且该返回值只能被赋值给加const修饰的同类型指针.

	const char *GetString(void);
	//正确调用
	const char *str = GetString();
	//错误的调用
	char *str = GetString();	//出现编译错误

对于函数返回值采用"值传递方式",因为函数会把返回值复制到外部临时的存储变量中,此时加const修饰无意义.

	const int GetInt(void);	//加const无必要
	const A GetA(void);		//加const无必要

1.3 const修饰成员函数

任何不会修改数据成员的函数都应该声明为const类型.如果在编写const成员函数时,不慎修改了数据成员,或者调用了其他非const成员函数,编译器将指出错误,这样可以提高程序的健壮性.

	class Stack
	{
		public:
			void Push(int elem);
			int Pop(void);
			int GetCount(void)	const;	//const成员函数,此时该函数不能修改数据成员,
										//也不能调用非const成员函数
		private:
			int m_num;
			int m_data[100];
	};

	int Stack::GetCount(void) const
	{
		++m_num;	//编译错误,const成员函数企图修改数据成员m_num
		Pop();		//编译错误,const成员函数企图调用非const函数
		return m_num;
	}

**2 程序效率**

程序的时间效率是指运行速度,空间效率是指程序占用内存或外村的状况.

全局效率是指站在整个系统的角度上考虑的效率,局部效率是指站在模块或函数的角度上考虑的效率.

***