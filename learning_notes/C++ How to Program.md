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

### 3.1 定义具有成员函数的类

#### 3.1.1 类定义

	#include <iostream>
	using namespace std;

	class GradeBook		//类名:大写字母开头,随后每个单词首字母也大写.
	{
	public:	//成员访问说明符,其后有一个":"
		void displayMessage()	//函数名:以小写字母开头,随后每个单词首字母大写.
		{
			cout << "Welcome to the Grade Book!" << endl;
		}
	};	//类的定义是以分号";"结束

	int main()
	{
		GradeBook myGradeBook;	//类实例化对象
		myGradeBook.displayMessage();	//对象通过点运算符"."来调用类的成员函数
	}

#### 3.1.2 GradeBook类的UML类图

				GradeBook				//最上层类名
										//中部为类的属性(即成员变量),此处类中无
			+displayMessag()			//最下层为类的成员函数.前面的"+"表示public说明符.

### 3.2 定义具有形参的成员函数

#### 3.2.1 具有形参的成员函数

	#include <iostream>
	#include <string>	//包含C++标准的string类
	using namespace std;

	class GradeBook
	{
	public:
		void displayMessage(string courseName)
		{
			cout << "Welcome to the grade book for\n" << courseName << "!"
				<< endl;
		}
	};

	int main()
	{
		string nameOfCourse;
		/*
			string类型是一种类,string名字与cout一样属于名字空间std.因为使用了:
			using namespace std;因此可以不用写成std::string.
			string变量的初始值(即没有赋值时)是空串(即""),显示时屏幕不显示任何东西.
		*/
		GradeBook myGradeBook;
		cout << "Please enter the course name:" << endl;
		getline(cin, nameOfCourse);
		/*
			cin<<:读取字符,直到遇到第一个空白字符(空格/tab或回车等)为止.
			getline(cin, variable_name):从标准输入(即cin)读取连续字符(包括空格),
				直到遇到换行符为止.将读取的字符放到variable_name中,并丢弃换行符.
			PS:
				1.程序输入过程中,按下的回车键也会输入到输入流中(cin中);
				2.调用getline函数必须#include <string>;
				3.getline也属于名字空间std.
		*/
		cout << endl;
		
		myGradeBook.displayMessage(nameofCourse);
	}

#### 3.2.2 具有形参的成员函数的UML类图

				GradeBook				//最上层类名
										//中部为类的属性(即成员变量),此处类中无
			+displayMessag(courseName : String)
			/*
				1.最下层为类的成员函数.前面的"+"表示public说明符.
				2.形参表示方式:(形参名 : 参数类型).
				3.在UML中,string用String表示.
			*/

### 3.3 含有数据成员、构造函数的类

#### 3.3.1 含有数据成员、构造函数的类

	#include <iostream>
	#include <string>
	using namespace std;

	class GradeBook
	{
	public:
		/*构造函数:
			1.无返回值,函数名与类名相同.可以有参数;
			2.通常声明为public,最好写上.没有就系统会有自动的默认构造函数;
			3.构造函数主要用于对数据成员进行初始化.
		*/
		GradeBook(string name)
		{
			setCourseName(name);	//调用setxxx函数比较好
		}
		
		void setCourseName(string name)
		{
			courseName = name;
		}

		string getCourseName()
		{
			return courseName;
		}

		void displayMessage()
		{
			cout << "Welcome to the grade book for\n" << getCourseName()
				<< "!" << endl;
		}
	private:
		string courseName;	//数据成员(或者成员变量).通常为private.
	};

	int main()
	{
		GradeBook gradeBook1("CS101 Introduction for C++ Programming");
		GradeBook gradeBook2("CS102 Data Structure in C++");
		
		cout << "gradeBook1 created for course: " << gradeBook1.displayMessage()
			<< "\ngradeBook2 created for course: " << gradeBook2.displayMessage()
			<< endl;
	}

#### 3.3.2 含有数据成员、构造函数的类的UML类图

				GradeBook				//最上层类名
			-------------------------------------
			-couseName : String			
			/*
				1.中部为类的属性(即数据成员/成员变量),前面的"-"表示private说明符.
				2.表示方法:(成员变量名 : 变量类型).
				3.在UML中,string用String表示.
			*/
			-------------------------------------
			<<constructor>>+GradeBook(name : String)
			/*
			<<constructor>>:表示构造函数
			*/
			+setCourseName(name : String)
			+getCourseName() : String
			/*
				+getCourseName : String:后面的String表示返回值为string类型
				在UML中,string用String表示.
			*/
			+displayMessag()
			/*
				1.最下层为类的成员函数.前面的"+"表示public说明符.
				2.形参表示方式:(形参名 : 参数类型).
			*/

### 3.4 接口与实现分离

C++对象通常只包含数据(数据成员/成员变量).编译器仅创建类的成员函数的一份副本,类的所有对象共享同一份副本的成员函数.因此,对象的大小依赖于数据成员所需内存大小.

#### 3.4.1 使用函数原型定义类的接口--->GradeBook.h文件

函数原型是函数的声明,告诉编译器函数的名字、返回类型和形参类型.

	//GradeBook.h
	#include <iostream>
	#include <string>
	using namespace std;

	class GradeBook
	{
	public:
		GradeBook(string name);	//函数原型.可以没有形参名(可选).e.g.GradeBook(string);
		void setCourseName(string name);	//一般会带有,方便编制文档
		string getCourseName();
		void displayMessage();
	private:
		string courseName;	//接口中通常会有数据成员.
							//因为编译器需要知道,以决定为类的每个对象保留多少内存.
	};

#### 3.4.2 在独立的源码文件中定义成员函数--->GradeBook.cpp文件

xxx.cpp文件名通常与接口文件名一样.

	//GradeBook.cpp
	#include <iostream>
	#include <string>
	#include "GradeBook.h"	//必须包含接口声明头文件.""在当前目录下寻找头文件.
	using namespace std;

	/*
		返回类型 类名::成员函数名(形参类型 形参)
		1.构造函数无返回类型,因为前面没有;
		2."::"二元作用域分辨运算符.用于将成员函数绑定到类型.建立两者之间的一个联系.
	*/
	GradeBook::GradeBook(string name)
	{
		setCourseName(name);	//类内部可以直接调用成员.
	}

	void GradeBook::setCourseName(string name)
	{
		courseName = name;
	}

	string GradeBook::getCourseName()
	{
		return courseName;
	}

	void GradeBook::displayMessage()
	{
		cout << "Welcome to the grade book for\n" << getCourseName()
			<< "!" << endl;
	}

#### 3.4.3 测试文件--->test.cpp

	//test.cpp
	#include <iostream>
	#include <string>
	#include "GradeBook.h"
	using namespace std;

	int main()
	{
		GradeBook gradeBook1("CS101 Introduction for C++ Programming");
		GradeBook gradeBook2("CS102 Data Structure in C++");

		cout << "gradeBook1 created for course: " << gradeBook1.getCourseName()
			<< "\ngradeBook2 created for course: " << gradeBook2.getCourseName()
			<< endl;
	}

### 3.5 使用set函数确认数据的有效性(具有检查的类)

#### 3.5.1 类的定义(使用函数原型定义类的接口)--->GradeBook.h文件

不变,与之前的一样.

	//GradeBook.h
	#include <iostream>
	#include <string>
	using namespace std;

	class GradeBook
	{
	public:
		GradeBook(string name);	//函数原型.可以没有形参名(可选).e.g.GradeBook(string);
		void setCourseName(string name);	//一般会带有,方便编制文档
		string getCourseName();
		void displayMessage();
	private:
		string courseName;	//接口中通常会有数据成员.
							//因为编译器需要知道,以决定为类的每个对象保留多少内存.
	};

#### 3.5.2 类成员函数定义(在独立的源码文件中定义成员函数)--->GradeBook.cpp文件

	#include <iostream>
	#include <string>
	#include "GradeBook.h"
	using namespace std;

	GradeBook::GradeBook(string name)
	{
		setCourseName(name);
	}

	void GradeBook::setCourseName(string name)
	{
		if (name.length() <= 25)	//string.length():返回string对象中字符的个数.
		{						//此处为不能超过25个字符
			courseName = name;
		}

		if (name.length() > 25)	//超过25个字符
		{
			courseName = name.substr(0, 25); //此处为取前25个字符
			//string.substr(start, length):从start位置开始,取length个字符并返回.
			//字符串第一个字符为位置0
			cout << "Name \"" << name << "\"exceeds maximum length(25).\n"
				<< "Limiting courseName to first 25 characters.\n" << endl;
		}
	}

#### 3.5.3 测试文件--->test.cpp

	#include <iostream>
	#include <string>
	#include "GradeBook.h"
	using namespace std;

	int main()
	{
		GradeBook gradeBook1("CS101 Introduction to Programming in C++");
		GradeBook gradeBook2("CS102 C++ Data Structures");

		cout << "gradBook1's initial course name is: "
			<< gradeBook1.getCourseName()
			<< "\ngradeBook2's initial course name is: "
			<< gradeBook2.getCourseName() << endl;

		gradeBook1.setCourseName("CS101 C++ Programming");

		cout << "\ngradeBook1's course name is: "
			<< gradeBook1.getCourseName()
			<< "\ngradeBook2's course name is: "
			<< gradeBook2.getCourseName() << endl;
	}

	/*
		结果为:
		Name "CS101 Introduction to Programming in C++" exceeds maximum length(25).
		Limiting courseName to first 25 characters.
		
		gradBook1's initial course name is: CS101 Introduction to Pro
		gradeBook2's initial course name is: CS102 C++ Data Structures

		gradeBook1's course name is: CS101 C++ Programming
		gradeBook2's course name is: CS102 C++ Data Structures
	*/

***

## Chapter 4.控制语句(Part I)

### 4.1 伪代码

伪代码(pseudocode)是一种人为的、非正式的语言.目的是帮助程序员不必受C++语法细节的束缚而开发算法(相当于算法思想).

伪代码通常只描述可执行语句(executable statement)(即能引起特定动作的语句).

	int counter;	//声明语句不属于可执行语句.因此伪代码通常不包含声明语句.

当前开发用的伪代码比较少,后续有需要再深入.

### 4.2 控制结构

#### 4.2.1 一些注意点 

1.C++的关键字都只包含小写字母.

2.C++提供bool(布尔)类型,取值为true/false(也是C++的关键字).

3.条件运算符(?:).

	1.条件运算符是C++中唯一的三元运算符(ternary operator),即需要3个操作数;
	2.条件运算符优先级比较低,最好使用括号括起来.

4.if...else:应该把最有可能为true的条件放在开始,提升效率.

5.a++/++a(自增/自减)中间不能有空格.

#### 4.2.2 实例---标记控制的循环

标记控制:使用一个标记值(也称为信号值、标志值)的特殊值,指示数据输入结束.

标记控制的循环:循环次数在开始执行之前是未知的,由标记值来控制循环结束,也称为不定数循环.

实例:标记控制的循环

**1.类的定义--->GradeBook.h文件**

	#include <string>
	using namespace std;

	class GradeBook
	{
	public:
		GradeBook(string);
		void setCourseName(string);
		string getCourseName();
		void displayMessage();
		void determineClassAverage();
	private:
		string courseName;
	};

**2.类的实现--->GradeBook.cpp文件**

	#include <iostream>
	#include <iomanip>
	#include "GradeBoo.h"
	using namespace std;

	GradeBook::GradeBook(string name)
	{
		setCourseName(name);
	}

	void GradeBook::setCourseName(string name)
	{
		if (name.length() <= 25)
			courseName = name;
		else	//if name is longer than 25 characters
		{
			courseName = name.substr(0, 25);	//从0开始,截取25个字符
			cout << "Name \"" << name << "\" exceeds maximum length (25).\n"
				<< "Limiting courseName is first 25 characters.\n" << endl;
		}
	}

	string GradeBook::getCourseName()
	{
		return couseName;
	}

	void GradeBook::displayMessage()
	{
		cout << "Welcome to the grade book for\n" << getCourseName() << "!\n"
			<< endl;
	}

	void GradeBook::determineClassAverage()
	{
		int total;
		int gradeCounter;
		int grade;
		double average;

		total = 0;
		gradeCounter = 0;

		cout << "Enter grade or -1 to quit: ";
		cin >> grade;

		while (grade != -1)
		{
			total = total + grade;
			gradeCounter += 1;
			
			cout << "Enter grade or -1 to quit: ";
			cin >> grade;
		}

		if (gradeCounter != 0)
		{
			average = static_cast<double>(total) / gradeCounter;
			/*
			static_cast<类型>(变量):一元强制类型转换运算符.将变量强制转换为某类型.
			static_cast<double>(total):此处用于将total转换为一个临时的double浮点值.存储在total
				中的仍是一个int型数据.
			强制类型转换运算符优先级仅次于圆括号.
			*/

			cout << "\nTotal of all " << gradeCounter << "grades entered is "
				<< total << endl;
			cout << "Class average is " << setprecisions(2) << fixed << average
				<< endl;
			/*
			1.参数化的流运算符:
				1.setprecision(2):名为参数化的流运算符(带有参数2).指定后面double类型变量
				average输出时的精度(即显示小数后2位数字(四舍五入原则));
				2.不显示指定浮点精度时,默认的浮点数精度为6位数字的精度;
				3.参数化的流运算符包含的头文件为:#include <iomanip>.
			2.无参数化的流运算符:
				1.endl/fixed:属于无参数化的流运算符(后面不带参数);
				2.fixed:控制浮点数以定点格式输出(即强制浮点数显示指定数量的位数,此处为小数点后2位);
					e.g.如果为整数88,以setprecision(2)及fixed显示为:88.00.非定点为88
				3.showpoint:强制浮点数将小数点输出(e.g.88会输出为88.);
				4.无参数化的流运算符包含的头文件为:#include <iostream>.
			*/
		}
		else
			cout << "No grades were entered" << endl;
	}

**3 测试文件--->test.cpp**

	#include "GradeBook.h"	//因为这个头文件包含了iostream等头文件

	int main()
	{
		GradeBook myGradeBook("CS101 C++ Programming");

		myGradeBook.displayMessage();
		myGradeBook.determineClassAverage();
	}

**4.结果**

	Welcome to the grade book for
	CS101 C++ Programming
	
	Enter grade or -1 to quit: 97
	Enter grade or -1 to quit: 88
	Enter grade or -1 to quit: 72
	Enter grade or -1 to quit: -1

	Total of all 3 grades entered is 257
	Class average is 85.67	//保留小数点后2位,85.66666四舍五入得到85.67.

### 4.3 浮点数精度及存储空间

float/double类型

	1.float类型表示单精度浮点数,在32位系统中具有7位有效数字;
	2.double类型表示双精度浮点数,存储空间是float的2倍,在32位系统中具有15位有效数字;
	3.C++源代码中键入的所有浮点数默认均为double类型,因此程序员多用double类型表示浮点数;
	4.double比float表示数字更精确;
	5.计算机存储的浮点值是一个近似值,不能当做准确值来用(e.g.比较两个浮点数是否相等).

***

## Chapter 5.控制语句(Part II)

#### 5.1 一些注意点

1.在while/for语句的条件中使用终值,并使用"<=",有助于避免差1的错误.

	e.g.打印1~10的循环.循环条件为:counter <= 10(终值).counter从1开始.

2.逗号表达式在C++运算符中优先级最低.逗号表达式的值和类型是列表最右边的子表达式的值和类型.

3.switch(expression)中的expression(可以为字符常量和整数常量的组合),只要计算结果为一个整数常量即可.

### 5.2 cmath头文件及setw流运算符使用实例

	#include <iostream>
	#include <cmath>	//standard C++ math library
	#include <iomanip>	//setw()/setprecision()等参数化的流运算符的头文件
	using namespace std;

	int main()
	{
		double amount;
		double principal = 1000;
		doulbe rate = 0.05;	//也可以写成".05"

		cout << "Year" << setw(21) << "Amount on deposit" << endl;
		/*
		setw(number):设置下一个输出值占的域宽.仅对接下来的输出值有用.
		setw(4):占4个字符位置,如果后面的字符小于4个字符,输出默认右对齐.如果大于,则输出实际宽度.
		如果要左对齐,则:cout << left << ...(其他输出).
			left:无参数流运算符(在<iostream>中),指代后面的输出左对齐.
			right:无参数流运算符(在<iostream>中),指代后面的输出右对齐(默认即为右对齐).
		*/
		cout << fixed << setprecision(2);
		/*
		fixed/setprecision(2):粘性设置,对后面的输出一直有用.
		*/
		
		//计算10年的存款额
		for (int year=1; year<=10; year++)
		{
			amount = principal * pow(1 + rate, year);
			/*
			pow(x, y):计算x的y次幂.x,y均为double类型实参,返回值也为double类型.
			pow():需要包含<cmath>头文件.
			PS:
				1.1+rate可以提到外面,提升程序效率;
				2.在金融方面的计算使用float/double类型不是太精确.
			*/
			cout << setw(4) << year << setw(21) << amount << endl;
		}
	}

### 5.3 cin.get()及忽略换行、制表、空格符实例

**1.类的定义--->GradeBook.h文件**

	#include <string>
	using namespace std;

	class GradeBook
	{
	public:
		GradeBook(string);
		void setCourseName(string);
		string getCourseName();
		void displayMessage();
		void inputGrades();
		void displayGradeReport();
	private:
		string courseName;
		int aCount;
		int bCount;
		int cCount;
		int dCount;
		int fCount;
	};

**2.类的实现--->GradeBook.cpp文件**

	#include <iostream>
	#include <iomanip>
	#include "GradeBoo.h"
	using namespace std;

	GradeBook::GradeBook(string name)
	{
		setCourseName(name);
		aCount = 0;	//构造函数中做初始化
		bCount = 0;
		cCount = 0;
		dCount = 0;
		fCount = 0;
	}

	void GradeBook::setCourseName(string name)
	{
		if (name.length() <= 25)
			courseName = name;
		else	//if name is longer than 25 characters
		{
			courseName = name.substr(0, 25);	//从0开始,截取25个字符
			cout << "Name \"" << name << "\" exceeds maximum length (25).\n"
				<< "Limiting courseName is first 25 characters.\n" << endl;
		}
	}

	string GradeBook::getCourseName()
	{
		return couseName;
	}

	void GradeBook::displayMessage()
	{
		cout << "Welcome to the grade book for\n" << getCourseName() << "!\n"
			<< endl;
	}

	void GradeBook::inputGrades()
	{
		int grade;
		
		cout << "Enter the letter grades." << endl		//输入字母成绩
			<< "Enter the EOF character to end input." << endl;

		while ((grade = cin.get()) != EOF)
		{
		/*
		1.cin.get():从键盘读取一个字符,并保存到grade变量中.因为字符可以直接转换为整型,因此此处使用
			int型的grade保存.为了后面的EOF.
		2.EOF(end-of-file):
			1.标记"文件结束"的一个符号.是一个符号整数常量,一般取值为-1,但也不一定;
			2.EOF在linux下的组合键为:Ctrl+d;在windows下的组合键为:Ctrl+z.有时可能按下组合键后还需要
				按一次回车键;
			3.EOF定义在<iostream>头文件中.
		此处表示:用户键入回车键时,字符由cin.get()函数读入,一次读入一个字符.如果输入的为文件结束的组合键,
				则跳出循环,否则一直循环.
		*/
			switch(grade)
			{
				case 'A':
				case 'a':
					aCount++;
					break;
				case 'B':
				case 'b':
					bCount++;
					break;
				case 'C':
				case 'c':
					cCount++;
					break;
				case 'D':
				case 'd':
					dCount++;
					break;
				case 'F':
				case 'f':
					fCount++;
					break;
				case '\n':	//换行符
				case '\t':	//tab键
				case ' ':	//空格
					break;	//均忽略
				default:
					cout << "Incorrect letter grade entered."
						<< "Enter a new grade" << endl;
					break;					
			}
		}
	}

	void GradeBook::displayGradeReport()
	{
		cout << "\n\nNumbers of students who received each letter grade:"
			<< "\nA: " << aCount
			<< "\nB: " << bCount
			<< "\nC: " << cCount
			<< "\nD: " << dCount
			<< "\nF: " << fCount
			<< endl;
	}

**3 测试文件--->test.cpp**

	#include "GradeBook.h"	//因为这个头文件包含了iostream等头文件

	int main()
	{
		GradeBook myGradeBook("CS101 C++ Programming");

		myGradeBook.displayMessage();
		myGradeBook.inputGrade();
		myGradeBook.displayGradeReport();
	}

**4.结果**

	Welcome to the grade book for
	CS101 C++ Programming!

	Enter the letter grades.
	Enter the EOF character is end input.
	a
	B
	c
	C
	A
	d
	f
	C
	E
	Incorrect letter grade entered.Enter a new grade
	D
	A
	b
	^Z	//Ctrl+z

	
	Numbers of students who received each letter grade:
	A: 3
	B: 2
	C: 3
	D: 2
	F: 1

### 5.4 输出true/false(非1/0)的实例

默认情况下,布尔值true/false由cout<<输出会显示为1/0.

	#include <iostream>
	using namespace std;

	int main()
	{
		cout << boolalpha << "true && false: " << (true && false);
		/*
		boolalpha:流运算符,指定布尔表达式的值应该显示为true或者false的形式.为粘性设置,对后面的
					输出一直有用.
		此处会显示为:true && false: false
		*/
	}

***

## Chapter 6.函数和递归入门

