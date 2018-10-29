# C++ How to Program(C++大学教程)

## Chapter 1.计算机、Internet和万维网简介

### 1.1 C++标准库

C++程序由一系列类和函数的构件组成.

学习C++主要学习两方面知识:

	1.C++语言本身;
	2.C++标准库所提供的各种类和函数.

PS:多线程不是标准C++的一部分,需要通过扩展库(e.g.Boost)才可以使用.

### 1.2 典型的C++开发环境

C++程序包括6个阶段:

	1.编辑(edit):编写源代码;
	2.预处理(preprocess):处理"#include,#define,#error,#pragma"等代码;
	3.编译(compile):编译器创建目标代码;
	4.连接(link):连接目标代码和一些库函数或数据等信息,生成可执行文件;
	5.载入(load):载入器将可执行程序载入内存;
	6.执行(execute):CPU读取每条指令并执行.

### 1.3 软件技术

重构(refactoring):是指在保持程序原来功能的基础上,重构代码使代码更加清晰,更加容易维护.

设计模式(design patterns):指能够构造灵活的、可维护的面向对象软件的开发体系.

### 1.4 开源Boost库、TR1和C++0x的概念

Boost C++库:是C++社区成员创建的一个免费开源库.

TR1:是技术报告1.包括一些对C++标准库的修改意见.

C++0x:C++在2003指定的标准.

UML(Unified Modeling Language)统一建模语言:是一种让设计面向对象软件系统的人可以用计算机行业标准符号类表示系统的图形语言.

***

## Chapter 2.C++编程入门

### 2.1 第一个C++程序:打印一行文本

	#include <iostream>	//输入/输出流头文件(e.g.cout, cin, cerr等)--->C++标准头文件.

	int main()
	{
		std::cout << "Welcome to C++!\n";
		/*
		1.std:名字空间std.	std::cout:表示使用名字空间中的cout.
			多数用法为在包含头文件下面使用下面语句:
			using namespace std;就可以直接使用cout/cin/cerr/endl等.
		2.<<:流插入运算符.表示数据流动的方向.此处为字符串往cout(屏幕等)流动,即输出到屏幕.
		*/
		return 0;	//该句也可以省略.
	}

一些常用的转义字符:

	\n:换行;
	\t:水平制表符;
	\r:回车符,光标移动到当前行的开始处,并不转到下一行;
	\a:响铃赋给,系统发出响铃声.

### 2.2 另一个C++程序:两数相加

	#include <iostream>

	int main()
	{
		int number1, number2;
		std::cout << "Enter two integers: ";
		std::cin >> number1 >> number2;
		/*
		std::cin:cin为std中的输入流对象;
		>>:流提取运算符.将从标准输入(使用空格分开)的两个数据分别赋给number1和number2.
		*/
		std::cout << "Sum is" << number1 + number2 << std::endl;
		/*
			std::endl:流运算符,输出一个换行符(end line),并且刷新缓冲区.
			std::endl可以强制显示缓存输出到屏幕.
		*/
	}

### 2.3 std::cout/cin/endl等的使用

**1.方法1:每个需要使用的地方都用std::xxx来写--->比较麻烦.**

	#include <iostream>

	int main()
	{
		std::cin >> ...	;
		std::cout << ... << std::endl;
	}

**2.方法2:在程序开头部分用类似using std::cout/cin/endl;后面可以直接用cout/cin/endl--->稍微简单一点.**

	#include <iostream>

	using std::cout;
	using std::cin;
	using std::endl

	int main()
	{
		cin >> ...;
		cout << ... << endl;	//在之后可以直接使用cin/cout/endl等.
	}

**3.方法3:在程序开头部分用using namespace std(包含std中所有名字);后面可以直接用cout/cin/endl--->最简单.**

	#include <iostream>
	using namespace std;

	int main()
	{
		cin >> ...;
		cout << ... << endl;	//在之后可以直接使用cin/cout/endl等.
	}

***

## Chapter 3.类和对象介绍

