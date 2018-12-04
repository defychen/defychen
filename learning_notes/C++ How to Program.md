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

### 6.1 数学库函数

全局函数:非类的成员函数且不使用static声明的函数是全局函数(即一般的函数).

	1.全局函数原型放在一个头文件中,其他需要使用该函数的包含该头文件即可;
	2.数学库头文件<cmath>中的所有函数都是全局函数.

一些数学库函数:

	ceil(x):x取整为不小于x的最小整数.->e.g.ceil(9.2)为10.0;ceil(-9.8)为-9.0
	cos(x):x的余弦.->e.g.cos(0.0)为1.0
	exp(x):指数函数e^x.->e.g.exp(1.0)为2.71828
	fabs(x):x的绝对值.->e.g.fabs(5.1)为5.1;fabs(-8.76)为8.76
	floor(x):x取整为不大于x的最大整数.->e.g.floor(9.2)为9.0;floor(-9.8)为-10.0
	fmod(x, y):x/y的浮点数余数.->e.g.fmod(2.6, 1.2)为0.2
	log(x):x的自然对数.->e.g.log(2.718282)为1.0
	log10(x):x(以10为底)的对数.->e.g.log10(10.0)为1.0
	pow(x, y):x的y次幂(x^y).->e.g.pow(2, 7)为128
	sin(x):x的正弦.->e.g.sin(0.0)为0
	sqrt(x):x的平方根(x非负数).->e.g.sqrt(9.0)为3.0
	tan(x):x的正切.->e.g.tan(0.0)为0

### 6.2 函数原型和实参类型的转换

函数原型(也称为函数声明):包括函数名称、返回类型、形参类型及个数和顺序等.

函数签名:由函数的名字和形参类型部分组成.

	1.函数签名不指定函数的返回类型;
	2.同一作用域内的函数必须有不同的签名.
	3.相同的签名但返回类型不同,会导致编译错误.

实参类型强制转换

	1.实参类型会强制转换成函数原型中声明的形参类型;
	2.从0开始的无符号整数的范围时相应有符号数范围的2倍.

### 6.3 C++标准头文件

在C++中,.h结尾的头文件是旧式的头文件,已经被C++标准头文件所取代了.

C++标准头文件:

	<iostream>:包含C++标准输入和输出的函数原型.
	<iomanip>:包含格式化数据流的流运算符的函数原型.
	<cmath>:包含数学库的函数原型.
	<cstdlib>:包含数转换为文本、文本转换为数、内存分配、随机数及其他各种工具函数的函数原型.
	<ctime>:包含时间和日期的函数原型及类型.
	<vector>,<list>,<deque>,<queue>,<stack>,<map>,<set>,<bitset>:
		包含了实现C++标准库容器的类.在程序执行期间,容器保存数据.
	<cctype>:包含测试字符特定属性(e.g.判断字符是否是数据或标点符号)以及字母大小写转换的函数原型.
	<cstring>:C式字符串处理函数的函数原型.
	<typeinfo>:包含运行时类型识别(在执行时确定数据类型)的类.
	<exception>,<stdexcept>:包含用于异常处理的类.
	<memory>:包含被C++标准库用来向C++标准库容器分配内存的类和函数.
	<fstream>:包含执行由磁盘文件输入和向磁盘文件输出的函数的函数原型.
	<string>:包含C++标准库的string类的定义.
	<sstream>:包含执行由内存字符串输入和向内存字符串输出的函数的函数原型.
	<functional>:包含C++标准库算法所用的类和函数.
	<iterator>:包含访问C++标准库容器中数据的类.
	<algorithm>:包含操作C++标准库容器中数据的函数.
	<cassert>:包含辅助程序调试的添加诊断的宏.
	<cfloat>:包含系统的浮点数长度限制.
	<climits>:包含系统的整数长度限制.
	<cstdio>:包含C式标准输入和输出库函数的函数原型.
	<locale>:包含流处理所用的类和函数,用来处理不同语言自然形式的数据(e.g.货币格式、排序字符串、
		字符表示等等).
	<limits>:包含为各计算机平台定义数字数据类型限制的类.
	<utility>:包含被许多C++标准库头文件所用的类和函数.

### 6.4 随机数生成

#### 6.4.1 rand()函数

rand()函数:生成0~RAND_MAX(定义在<cstdlib>头文件中的符号常量)之间的一个unsigned int数.

	i = rand();	//生成0~RAND_MAX之间的随机数.RAND_MAX最小是32767,两字节表示的最大值.

rand()函数生成的是伪随机数,即程序每次重新执行生成相同的随机数,因为使用相同的种子.

#### 6.4.2 srand()函数

srand()函数:接受一个unsigned int实参,作为rand()函数的种子,可以使程序每次重新执行时生成不同的随机数.

srand()函数也是位于<cstdlib>头文件中.

#### 6.4.3 实例

	#include <iostream>
	#include <cstdlib>
	#include <iomanip>
	using namespace std;

	int main()
	{
		unsigned seed;
		cout << "Enter seed: ";
		cin >> seed;
		srand(seed);	//seed random number generation(种子随机数产生器).
						//将seed变成rand()函数的种子.rand()产生的随机数基于该种子.
		for (int counter=1; counter<=10; counter++)
		{
			cout << setw(10) << (1+rand()%6);	//随机产生1~6之间的数
			if (counter % 5 == 0)
				cout << endl;
		}
	}

	/*
		输入种子:67,得到:
			6 1 4 6 2
			1 6 1 6 4
		输入种子:432,得到:
			4 6 3 1 6
			3 1 5 4 2
		再次输入种子:67,得到:
			6 1 4 6 2
			1 6 1 6 4
		PS:可以证明,种子相同,产生的随机数也是相同的.
	*/

根据机器时间来获取种子值,确保每次的种子都不一样.

	#include <ctime>	//包含time函数原型

	srand(time(0));
	/*
		time(0):返回从格林尼治时间1970年1月1日起到现在的秒数.该值被转换成unsigned类型,
		作为rand函数的种子.因此,每次值都不一样.
	*/


### 6.5 enum枚举简介

enum枚举类型是一组由标识符表示的整型常量.

	enum Status {	//枚举名字为Status.用户自定义的类型名标识符首字母大写.e.g.类名
		CONTINUE,	//枚举默认起始值为0.且常量名只使用大写字母.
		WON,		//后续的枚举值会依次+1.
		LOST
	};	//以大括号开头和结尾.

实例:

	#include <iostream>
	#include <cstdlib>
	#include <ctime>
	using namespace std;

	int rollDice();

	int main()
	{
		enum Status {CONTINUE, WON, LOST};
		int myPoint;
		Status gameStatus;	//枚举变量.可以取值为CONTINUE, WON, LOST.

		srand(time(0));	//以时间作为种子
		int sumOfDice = rollDice();

		switch(sumOfDice)
		{
			case 7:
			case 11:
				gameStatus = WON;	//此处不能直接赋值2(虽然值是一样的),否则会出现编译错误.
									//必须赋枚举中的常量.
				break;
			case 2:
			case 3:
			case 12:
				gameStatus = LOST;
				break;
			default:
				gameStatus = CONTINUE;
				myPoint = sumOfDice;
				cout << "Point is " << myPoint << endl;
				break;
		}

		while (gameStatus == CONTINUE)
		{
			sumOfDice = rollDice();
			if (sumOfDice == myPoint)
				gameStatus = WON;
			else
				if (sumOfDice == 7)
					gameStatus = LOST;
		}

		if (gameStatus == WON)
			cout << "Player wins" << endl;
		else
			cout << "Player loses" << endl;
	}

	int rollDice()
	{
		int die1 = 1 + rand() % 6;
		int die2 = 1 + rand() % 6;

		int sum = die1 + die2;
		cout << "Player rolled " << die1 << "+" << die2
			<< " = " << sum << endl;
		return sum;
	}

### 6.6 存储类别

存储类别和作用域的区别:

	存储类别:标识符的存储类别决定了标识符在内存中存在的时间;
	作用域:标识符的作用域是指标识符在程序中可以被引用的范围.

存储类别说明符包括:auto, register, extern, mutable(与类一起使用)和static.

存储类别分为静态存储类别(static)和自动存储类别(automatic).

	自动存储类别变量特点:程序执行到定义的位置创建,退出程序块时自动销毁.包括auto, register声明的变量.
	静态存储类别变量特点:一直存在于整个程序的执行过程中.包括extern, static声明的变量和函数.

#### 6.6.1 自动存储类别

**1.局部变量**

局部变量和形参都是自动存储类别的,可以在前面加auto来声明,一般省略auto.

	auto double x;	//声明自动存储类别变量x,一般省略auto.写成doulbe x;

**2.寄存器变量**

程序的机器语言版本中的数据一般都是加载到寄存器中进行计算和其他处理的.

声明形式如下:

	register int counter = 1;
	/*
		1.该定义建议整型变量counter放在计算机的一个寄存器中;
		2.寄存器变量声明频繁使用的变量;
		3.现在的优化编译器能够自动识别频繁使用的变量,会自动将这些变量放到寄存器中.
		PS:因此,现在register基本不用了.
	*/

register现在基本不用了.

#### 6.6.2 静态存储类别

extern和static用于给静态存储类别的变量和函数声明标识符.在整个程序执行过程中都存储,开始执行时就会被分配空间,而且是一次性初始化.

**1.extern函数或变量**

extern函数或变量:包括全局变量和全局函数.

	全局函数:不属于任何类的函数都是全局函数.一般不用extern修饰.如果其他文件需要引用,可以放到头文件中
		或者使用extern表示外部可以引用(此时与作用域相关,与存储类别无关).
	全局变量:把变量放在所有类和所有函数外部来创建的是全局变量.全局变量一般仅在本文件中使用.

**2.static变量**

static变量指使用static声明的局部变量,会一直保留调用之后的值.

	对于int的static变量,没有显示初始化会被自动初始化为0.建议显示初始化.

### 6.7 作用域规则

1.全局名字空间作用域(global namespace scope):声明于所有函数和类之外的标识符.在本文件内是已知的,可访问的;其他文件不行.

	包括:函数之外的全局变量、函数定义和函数原型.

2.函数作用域(function scope):标签(err:)是唯一具有函数作用域的标识符.仅在函数内引用,一般配合goto使用.

	xxx function()
	{
		if (xxx)
			goto err;
	err:	//函数作用域
		...
	}

3.局部作用域(local scope):语句块内声明的标识符,包括局部变量和函数形参.如果出现内、外层有相同名字的标识符,内层的会隐藏外层的标识符.

	static声明的局部变量具有局部作用域,但是在整个程序执行期间都存在.

4.函数原型作用域(function prototype scope):指代函数原型中形参的标识符.函数原型中的形参列表不需要形参名,仅需要类型即可(因为编译器也会忽略形参名).

### 6.8 内联函数

内联函数:在函数定义中把限定符inline放在函数返回类型前面的函数叫内联函数.

	内联函数"建议"编译器在适当的地方生成函数代码的副本以避免函数调用.因此在程序中会存在多份内联
	函数代码的副本,程序会变大.

内联函数适合于小的、经常调用的函数.可以减少调用的开销.

实例:

	#include <iostream>
	using namespace std;

	inline double cube(const double side)	//const修饰符告诉编译器不修改变量side的值
	{
		return side * side * side;
	}

	int main()
	{
		double sideValue;
		cout << "Enter the side length of your cude: ";
		cin >> sideValue;
		cout << "Volume of cube with side " << sideValue
			<< " is " << cube(sideValue) << endl;
	}

### 6.9 引用

#### 6.9.1 按值传递

按值传递(pass-by-value):按值传递形参时,会在函数调用堆栈上拷贝一份实参值的副本,然后将该副本传递给被调用函数进行运算.如果有大的数据项需要传递时,拷贝实参就需要花费大量的时间和内存.

#### 6.9.2 按引用传递

引用传递(pass-by-reference):形参是对实参的引用,指向同一个内存,不需要拷贝.而且被调用函数可以直接操作到实参的数据.可能具有破坏性.

引用传递具有破坏性.因此一般会使用const限定符防止被调用函数对实参的修改.

#### 6.9.3 按值传递和按引用传递实例

	#include <iostream>
	using namespace std;

	int squareByValue(int);	//函数原型,可以不带形参名.按值传递
	void squareByReference(int &);	//引用传递:类型 &.

	int main()
	{
		int x = 2;
		int z = 4;

		cout << "x = " << x << "before squareByValue\n";	//x = 2
		cout << "Value returned by squareByValue: "
			<< squareByValue(x) << endl;	//打出来4.
		cout << "x = " << x << "after squareByValue\n";		//x = 2

		cout << "z = " << z << "before squareByReference" << endl;	//z = 4
		squareByReference(z);
		cout << "z = " << z << "after squareByReference" << endl;	//z = 16
	}

	int squareByValue(int number)
	{
		return number *= number;
	}

	void squareByReference(int &numberRef)	//形参引用在原型和定义出均需要"&"符号
	{
		numberRef *= numberRef;
	}

#### 6.9.4 引用作为变量别名

	int count = 1;
	int &cRef = count;	//创建变量count的引用cRef.
	/*
		1.在引用变量声明时就必须完成初始化;
		2.并且不能再指定为其他变量的别名.
	*/
	cRef++;	//别名上的操作与实际变量是一样的.此处相当于:count++.

### 6.10 默认实参

	1.默认实参必须是形参列表中最靠右边的形参;
	2.默认实参应该在函数名第一次出现时指定,后续不用再指定.一般在函数原型中指定.

实例:

	#include <iostream>
	using namespace std;

	int boxVolume(int length = 1, int width = 1, int height = 1);	//默认实参在函数原型中指定

	int main()
	{
		cout << "The default box volume is: " << boxVolume();
		cout << "\n\nThe volume of box with length 10, \n"
			<< "width 1 and height 1 is: " << boxVolume(10);	//10
		cout << "\n\nThe volume of box with length 10, \n"
			<< "width 5 and height 1 is: " << boxVolume(10, 5);	//50
		cout << "\n\nThe volume of box with length 10, \n"
			<< "width 5 and height 2 is: " << boxVolume(10, 5, 2)	//100
			<< endl;
	}

	int boxVolume(int length, int width, int height)	//不需要再指定默认实参值了
	{
		return length * width * height;
	}

### 6.11 一元作用域分辨运算符

一元作用域分辨运算符(::):用于当局部变量和全局变量具有相同名字时访问全局变量.

	不能使用(::)访问外层语句块中具有相同名字的局部变量.

实例:

	#include <iostream>
	using namespace std;

	int number = 7;	//全局变量

	int main()
	{
		double number = 10.5;	//局部变量
		cout << "Local double value of number = " << number		//显示10.5
			<< "\nglobal int value of number = " << ::number << endl;	//显示7
	}

总是使用(::)来引用全局变量会更易于阅读和理解.

### 6.12 函数重载

函数重载(function overloading):函数名字相同,但形参不同(包括类型,个数,顺序等不同形式).此时会形成不同的签名.

	函数重载通常用于创建执行相似任务,在作用于不同数据类型(即形参不同)的具有相同名字的多个函数.

实例:

	#include <iostream>
	using namespace std;

	int square(int x)	//形参为int类型
	{
		cout << "square of integer " << x << " is ";
		return x * x;
	}

	double square(double y)	//形参为double类型
	{
		cout << "square of double " <<　y << " is ";
		return y * y;
	}

	int main()
	{
		cout << square(7);	//会调用int形参的函数
		cout << endl;
		cout << square(7.5);	//会调用double形参的函数
		cout << endl;
	}

PS:main函数不能被重载.

### 6.13 函数模板

如果对于每种数据类型程序逻辑和操作都是相同的,那么使用函数模板(function template)可以更简便地对函数进行重载.

1.函数模板头文件->maximum.h

	template <class T>
	/*
		template:声明定义函数模板.
		<class/typename T>:模板形参列表,可以有多个形参,但均由class/typename开头.
			T:占位符,用于指代基本数据类型或用户自定义类型.
	*/
	T maximun(T value1, T value2, T value3)	//函数maximum有三个参数.
	{										//后续的例化T可以被真正的数据类型或自定义类型所代替
		T maximumValue = value1;

		if (value2 > maximumValue)
			maximumValue = value2;

		if (value3 > maximumValue)
			maximumValue = value3;

		return maximumValue;
	}

2.函数模板测试文件

	#include <iostream>
	#include "maximum.h"	//包含函数模板头文件
	using namespace std;

	int main()
	{
		int int1, int int2, int int3;

		cout << "Input three integer value: ";
		cin >> int1 >> int2 >> int3;
		cout << "The maximum integer value is: "
			<< maximum(int1, int2, int3);	//会将int代替函数模板中的T,并例化一个函数.

		doulbe double1, double2, double3;
		cout << "\n\nInput three doulbe value: ";
		cin >> double1 >> double2 >> double3;
		cout << "The maximum doulbe value is: "
			<< maximum(double1, double2, double3); //会将double代替函数模板中的T,并例化一个函数.

		char char1, char2, char3;
		cout << "\n\nInput three char value: ";
		cin >> char1 >> char2 >> char3;
		cout << "The maximum doulbe value is: "
			<< maximum(char1, char2, char3); //会将char代替函数模板中的T,并例化一个函数.
	}

PS:1.618--->黄金比例.

***

## Chapter 7.数组和vector

### 7.1 数组的初始化

	int a[10] = {0};	//数组第一个元素显示初始化为0,之后的没有指明默认为0.
	int b[10] = {};		//全部没有指明,表示都为0.
	int c[5] = {1, 2, 3, 4, 5};	//表示c[0]~c[4]分别为:1, 2, 3, 4, 5
	int d[] = {1, 2, 3, 4, 5};	//表示数组d有5个元素(由元素个数确定数组大小),分别为:1, 2, 3, 4, 5

C++对数组不提供边界检查机制(e.g.访问了越界了(c[5]),不会产生警告).

### 7.2 常量

	const int arraySize = 10;	//const声明常量,且必须在声明时进行初始化.

常量在函数中的使用:

	#include <iostream>
	using namespace std;
	
	int main()
	{
		const int arraySize = 5;
		int total = 0;
		
		int n[arraySize] = {1, 2, 3, 4, 5};
		for (int i=0; i<arraySize; i++)
			total += n[i];

		cout << "Total of array element: " << total << endl;
	}

### 7.3 静态局部数组和自动局部数组

**1.静态局部数组**

静态局部数组:static应用于局部数组声明,数组就不会在每次函数被调用时都进行创建和初始化,也不会在该函数结束时被销毁.在大型数组时,可以提高性能.

	const int arraySize = 10;

	void xxx_fun(xxx)
	{
		static int array[arraySize];	//声明静态局部数组.默认会被初始化为全0.
		...
	}

**2.自动局部数组**

自动局部数组:不带static声明,一般地声明均为自动局部数组.自动创建和销毁.

	int n[10];	//自动局部数组
	for (int i=1; i<=10; i++)
		n[i] = 0;

### 7.4 将数组传递给函数

1.实例:

	#include <iostream>
	#include <iomanip>
	using namespace std;

	void modifyArray(int [], int);	//数组传递给函数
	/*
	函数原型,可以写成:
		void modifyArray(int arrayName[], int arraySize);
	但C++编译器会忽略函数原型中形参的变量名称.原型只是告诉编译器调用时实参的个数和每个实参的类型.
	*/
	void modifyElement(int);	//原型中省略形参变量名.

	int main()
	{
		const int arraySize = 5;
		int a[arraySize] = {0, 1, 2, 3, 4};
		cout << "Effects of passing entire array by reference: "
			<< "\n\nThe values of the original array are:\n";

		for (int i=0; i<arraySize; i++)
			cout << setw(3) << a[i];
		cout << endl;

		modifyArray(a, arraySize);
		cout << "The values of the modified array are:\n";
		
		for (int j=0; j<arraySize; j++)
			cout << setw(3) << a[j];	//结果为:0 2 4 6 8

		cout << "\n\nEffects of passing entire array by value: "
			<< "\n\na[3] before modifyElement: " << a[3] << endl;
		modifyElement(a[3]);
		cout << "na[3] after modifyElement: " << a[3] << endl;	//不变,仍为6
	}

	void modifyArray(int b[], int sizeOfArray)	//C++是按引用传递数组到函数,因此会改变原数组值.
	{
		for (int k=0; k<sizeOfArray; k++)
			b[k] *= 2;
	}

	void modifyElement(int e)	//不会改变原来的值
	{
		cout << "Value of element in modifyElement: " << (e *= 2) << endl;
	}

2.防止被调用函数修改调用者的数组值.

	void keepArray(const int []);	//函数原型.使用const防止修改调用者的数组值.

	void keepArray(const int b[])	//函数实现
	{
		...
	}

### 7.5 采用线性查找法查找数组

线性查找法:将目标值与数组中的每个元素进行比较,如果相等得到数组元素对应的下标;否则出错打印或者返回-1.

线性查找法适合于小型数组或未排序的数组.

### 7.6 采用插值排序法排序数组

实例:

	#include <iostream>
	#include <iomanip>
	using namespace std;

	int main()
	{
		const int arraySize = 10;
		int data[arraySize] = {34, 56, 4, 10, 77, 51, 93, 30, 5, 32};
		int insertVal;

		cout << "Unsorted array:\n";
		for (int i=0; i<arraySize; i++)
			cout << setw(4) << data[i];

		//插入排序
		for (int next=1; next<arraySize; next++)
		{
			insertVal = data[next];
			int insertPos = next;
			while ((insertPos>0) && (data[insertPos-1]>insertVal))
			{
				data[insertPos] = data[insertPos - 1];
				insertPos--; 
			}
			data[insertPos] = insertVal;
		}

		cout << "\nSorted array:\n";
		for (int i=0; i<arraySize; i++)
			cout << setw(4) << data[i];
		cout << endl;
	}

插入排序的优点:易于编码,但是速度慢.

### 7.7 多维数组

1.初始化:

	int a[2][2] = {{1, 2}, {3, 4}};
	int b[2][2] = {1, 2, 3, 4};	//1,2属于b[1]; 3,4属于b[2].
	int c[2][2] = {{1}, {3}};	//c[1]中有1,0; c[2]中有3,0

2.多维数组传递给函数

	const int columns = 4;

	void printArray(const int a[][columns])	//形参为多维数组,除了第一个维大小不需要有,
	{										//后面的所有维必须有大小.
		...
	}

### 7.8 二位数组的GradeBook类

**1.类的定义--->GradeBook.h文件**

	#include <string>
	using namespace std;

	class GradeBook
	{
	public:
		static const int students = 10;	//静态常量
		static const int tests = 3;

		GradeBook(string, const int [][tests]);
		void setCourseName(string);
		string getCourseName();
		void displayMessage();
		void processGrades();
		int getMinumum();
		int getMaximum();
		double getAverage(const int[], const int);
		void outputBarChart();
		void outputGrades();
	private:
		string courseName;
		int grades[students][tests];
	};

**2.类的实现--->GradeBook.cpp文件**

	#include <iostream>
	#include <iomanip>
	#include "GradeBook.h"
	using namespace std;

	GradeBook::GradeBook(string name, const int gradesArray[][tests])
	{
		setCourseName(name);
		
		for (int student=0; student<students; student++)
			for (int test=0; test<tests; test++)
				grades[student][test] = gradesArray[student][test];
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

	void GradeBook::processGrades()
	{
		outputGrades();

		cout << "\nThe lowest grade in the grade book is " << getMinumum()
			<< "\nThe highest grade in the grade book is " << getMaximun() << endl;

		outputBarChart();
	}

	int GradeBook::getMinumum()
	{
		int lowGrade = 100;

		for (int student=0; student<students; student++)
		{
			for (int test=0; test<tests; test++)
			{
				if (grades[student][test] < lowGrade)
					lowGrade = grades[student][test];
			}
		}
	}
	int GradeBook::getMaximum()
	{
		int highGrade = 0;

		for (int student=0; student<students; student++)
		{
			for (int test=0; test<tests; test++)
			{
				if (grades[student][test] > highGrade)
					highGrade = grades[student][test];
			}
		}
	}

	double GradeBook::getAverage(const int setOfGrades[], const int countOfGrades)
	{
		int total = 0;
		for (int count=0; count<countOfGrades; count++)
			total += setofGrades[count];

		return static_cast<double>(total) / countOfGrades;
	}

	void GradeBook::outputBarChart()
	{
		cout << "\nOverall grade distribution: " << endl;

		const int frequencySize = 11;
		int frequency[frequencySize] = {};	//初始化为0
		for (int student=0; student<students; student++)
			for (int test=0; test<tests; test++)
				++frequency[grades[student][test] / 10];
		
		for (int count=0; count<frequencySize; count++)
		{
			if (count == 0)
				cout << "0-9: "
			else if (count == 10)
				cout << "100: "
			else
				cout << count * 10 <<　"-" << (count*10 + 9) << ": ";

			for (int stars=0; stars<frequency[count]; start++)
				cout << "*";

			cout << endl;
		}
	}

	void GradeBook::outputGrades()
	{
		cout << "\nThe grades are:\n\n";
		cout << "            ";	//用作对齐处理.12个空格
		
		for (int test=0; test<tests; test++)
			cout << "Test " << test + 1 << "  ";

		cout << "Average" << endl;

		for (int student=0; student<students; student++)
		{
			cout << "Student " << setw(2) << student + 1;

			for (int test=0; test<tests; test++)
				cout << setw(8) << grades[student][test];

			double average = getAverage(grades[student], tests);
			cout << setw(9) << setprecision(2) << fixed << average << endl;
		}
	}

**3 测试文件--->test.cpp**

	#include "GradeBook.h"	//因为这个头文件包含了iostream等头文件

	int main()
	{
		int gradeArray[GradeBook::students][GradeBook::tests] =
			{
				{87, 96, 70},
				{68, 87, 90},
				{94, 100, 90},
				{100, 81, 82},
				{83, 65, 85},
				{78, 87, 65},
				{91, 94, 100},
				{76, 72, 84},
				{87, 93, 73}
			};
		/*
			类中static声明的变量属于类本身,类的所有对象共享static变量.可以在成员函数中直接访问.
			在其他函数中(比如此处),可以透过:类名::static变量来访问.即GradeBook::students.
			Q:在其他函数中是否可以通过对象.static变量来访问呢???
		*/

		GradeBook myGradeBook("CS101 Introduction to C++ Programming", gradeArray);

		myGradeBook.displayMessage();
		myGradeBook.processGrades();
	}

### 7.9 C++标准库类模板vector

C++标准库类模板vector,表示一种更健壮的、有很多附加能力的数组.

标准类模板vector在头文件<vector>中定义,属于std名字空间.

实例:

	#include <iostream>
	#include <iomanip>
	#include <vector>
	using namespace std;

	void outputVector(const vecotr<int> &);
	/*
		vecotr<int>:表示一种能力更强大的数组.此处表示一种能力更强大的数组的引用,
			并且不能修改其中的数组元素(const属性).
	*/
	void inputVecotr(vector<int> &);	//函数原型

	int main()
	{
		vector<int> integers1(7);	//创建存储int值的vector对象,integers1含有7个元素.
		vector<int> integers2(10);	//创建存储int值的vector对象,integers2含有10个元素.

		cout << "Size of vector integers1 is " << integers1.size()
			<< "\nvector after initialization:" << endl;
		/*
			vector对象的size()函数:获取对象的大小(即元素个数).
			vector<int>对象,默认的元素值全为0.
		*/
		outputVetor(integers1);
		cout << "Size of vector integers2 is " << integers2.size()
			<< "\nvector after initialization:" << endl;
		outputVector(integers2);

		cout << "\nEnter 17 integers:" << endl;
		inputVector(integers1);
		inputVector(integers2);

		cout << "\nAfter input, the vectors contain:\n"
			<< "integers1:" << endl;
		outputVector(integers1);
		cout << "integers2:" << endl;
		outputVector(integers2);
		
		cout << "\nEvaluating: integers1 != integers2" << endl;

		if (integers1 != integers2)
			cout << "integers1 and integers2 are not equal!" << endl;
		//vector<int>对象可以直接比较大小.内容(元素和大小)相同,则两个vector对象相等,否则不等.

		vector<int> integers3(integers1);
		//创建一个vector3对象,并用integers1的一个副本初始化该对象.此时会调用vector的复制
		//构造函数来执行复制操作

		cout << "Size of vector integers3 is " << integers3.size()
			<< "\nvector after initialization:" << endl;
		outputVector(integers3);

		cout << "\nAssigning integers2 to integers1:" << endl;
		integers1 = integers2;	//可以直接使用赋值运算符将一个vector对象赋值给另一个vector对象
		cout << "integers1:" << endl;
		outputVector(integers1);
		cout << "integers2:" << endl;
		outputVector(integers2);

		cout << "\nEvaluating: integers1 == integers2" << endl;
		if (integers1 == integers2)
			cout << "integers1 and integers2 are equal" << endl;

		cout << "\nintegers1[5] is " << integers1[5];
		//vector对象可以直接像数组一样取数组元素.同样也不提供边界检查.

		cout << "\n\nAssigning 1000 to integers1[5]" << endl;
		integers1[5] = 1000;	//像数组一样赋值
		cout << "integers1:" << endl;
		outputVector(integers1);

		cout << "\nAttempt to assign 1000 to integers1.at(15)" << endl;
		integers1.at(15) = 1000;
		/*
			vector对象的at函数类似取元素[],但是提供边界检查.如果at()中的参数是非法的,
				则会抛出一个异常.
			此处at(15):15超出了vector对象的长度,抛出异常.
		*/
	}

	void outputVector(const vector<int> &array)
	{
		size_t i;	//size_t:unsigned int类型.
					//因为vector对象的size()函数返回的是size_t类型.防止类型不同出现警告信息
		for (i=0; i<array.size(); i++)
		{
			cout << setw(12) << array[i];
			if ((i+1) % 4 == 0)
				cout << endl;
		}
		if (i % 4 != 0)
			cout << endl;
	}

	void inputVector(vector<int> &array)
	{
		for (size_t i=0; i<array.size(); i++)
			cin >> array[i];
	}

***

## Chapter 15.标准库的容器和迭代器

### 15.1 标准模板库(STL)简介

STL定义了强大的、基于模板的、可复用的组件,实现了许多通用的数据结构以及处理这些数据结构的算法.

**1.容器(container)**

是一种流行的模板数据结构.是能存放几乎所有类型的数据的数据结构.包括:

	首类容器、适配器和近容器.

常用的容器例子:array, vector(动态的可变长度的数据), list(双向链表), deque(双端队列).

**2.迭代器(iterator)**

STL迭代器与指针有着类似的属性,用于操作STL容器的元素.

**3.算法(algorithm)**

STL算法是对容器执行通用操作的函数模板.比如对容器执行:搜索, 排序或比较元素等操作,就具有专门的函数提供调用.

STL中的算法大部分是使用迭代器来访问容器中的元素,因此一个容器所支持的迭代器类型就决定了这个容器是否可以用于某一个特定的算法.

### 15.2 容器简介

容器可以分为4类:序列容器(sequence container)、有序关联容器(ordered associative container)、无序关联容器(unordered associative container)和容器适配器(container adapter).

**1.各类容器包含的类型**

	1.序列容器
		array:固定大小,直接访问任意元素;
		deque:从头部或尾部进行快速插入和删除操作,直接访问任意元素;
		forward_list:单链表,在任意位置快速插入和删除操作.C++11标准新出的容器;
		list:双向链表,在任意位置快速插入和删除操作;
		vector:从尾进行快速插入和删除操作,直接访问任意元素.
	2.有序关联容器(key按顺序保存)
		set:快速查找,无重复元素;
		multiset:快速查找,可有重复元素;
		map:一对一映射,无重复元素,基于key快速查找;
		multimap:一对一映射,可有重复元素,基于key快速查找.
	3.无序关联容器
		unordered_set:快速查找,无重复元素;
		unordered_multiset:快速查找,可有重复元素;
		unordered_map:一对一映射,无重复元素,基于key快速查找;
		unordered_multimap:一对一映射,可有重复元素,基于key快速查找.
	4.容器适配器
		stack(栈):后进先出(LIFO);
		queue(队列):先进先出(FIFO);
		priority_queue(优先级队列):优先级最高的元素先出.

**2.各类容器特点**

	1.序列容器
		描述线性的数据结构.
	2.关联容器
		描述非线性的数据结构,可以快速锁定其中的元素.
		存储值的集合或key-value对.关联容器中得key是不可变的(不能被修改的).
	3.容器适配器
		是在序列容器的基础上加上某些约束条件得到.包括stack和queue.
	PS:
		序列容器和关联容器一起成为首类容器;
		string类型类似线性容器,但是只能存储字符数据.

**3.STL容器的通用函数**

	1.默认构造函数
		对容器进行默认初始化的构造函数.
	2.拷贝构造函数
		将容器初始化为同类型已有容器的副本的构造函数.
	3.转移构造函数
		将一个已经在某容器中的元素转移到同类型的新容器中.
	4.析构函数
		在容器不再需要时执行清理工作.
	5.empty
		判断容器是否为空.即没有元素返回true,有则返回false.
	6.insert
		在容器中插入一个元素.
	7.size
		返回当前容器中得元素个数.
	8.copy operator =
		把一个容器赋值给另一个
	9.move operator =
		将元素从一个容器移动到另一个容器.
	10.operator <
		若第一个容器小于第二个容器则返回true,否则返回false.
	11.operator <=
		若第一个容器小于或等于第二个容器则返回true,否则返回false.
	12.operator >
		若第一个容器大于第二个容器则返回true,否则返回false.
	13.operator >=
		若第一个容器大于或等于第二个容器则返回true,否则返回false.
	14.operator ==
		若第一个容器等于第二个容器则返回true,否则返回false.
	15.false operator != 
		若第一个容器不等于第二个容器则返回true,否则返回false.
	16.swap
		交换两个容器中得元素.
	17.max_size
		返回一个容器中得最大元素个数.
	18.begin
		返回引用容器中第一个元素的iterator或const_iterator.该函数有两个版本.
	19.end
		返回引用容器中末端之后位置的iterator或const_iterator.该函数有两个版本.
	20.cbegin--->C++11新加的
		返回引用容器第一个元素的const_iterator
	21.cend--->C++11新加的
		返回引用容器末端之后位置的const_iterator
	22.rbegin
		返回引用容器末端位置的reverse_iterator或const_reverse_iterator.该函数有两个版本.
	23.rend
		返回引用容器第一个元素之前位置的reverse_iterator或const_reverse_iterator.该函数有两个版本.
	24.crbegin--->C++11新加的
		返回引用容器末端的const_reverse_iterator.
	25.crend--->C++11新加的
		返回引用容器第一个元素之前位置的const_reverse_iterator.
	26.erase
		删除容器中的一个或多个元素.
	27.clear
		删除容器中所有元素.

PS:

	1.priority_queue没有提供重载的<,<=,>,>=,==和!=运算符;
	2.无序关联容器没有提供重载的<,<=,>和>=运算符;
	3.forward_list没有提供成员函数rbegin,rend,crbegin和crend.
	
**4.首类容器的通用typedef**

首类容器中通用的typedef(用于为过长的类型名创建别名)主要用于基于模板的变量、函数参数以及返回的声明中使用.主要的typedef如下:

	allocator_type:用来分配容器内存的对象的类型--->什么意思???
	value_type:容器中元素的类型;
	reference:对容器中元素的类型的引用;
	const_reference:对容器中元素的类型的常量引用;
	pointer:指向容器中元素的类型的指针;
	const_pointer:指向容器中元素的类型的常量指针;
	iterator:指向容器中元素的类型的迭代器;
	const_iterator:指向容器中元素的类型的常量迭代器;
	reverse_iterator:指向容器中元素的类型的反向迭代器;
	const_reverse_iterator:指向容器中元素的类型的常量反向迭代器;
	difference_type:两个引用相同容器的迭代器之差的类型;
	size_type:用于计算容器中的项目数及索引序列容器的类型.

### 15.3 迭代器简介

实例---使用istream_iterator输入,ostream_iterator输出.

	#include <iostream>
	#include <iterator>
	using namespace std;
	
	int main()
	{
		cout << "Enter two integers: ";
	
		istream_iterator<int> inputInt(cin);
		//创建一个istream_iterator迭代器对象,从标准输入cin以类型安全的方式输入int类型的数值.
	
		int number1 = *inputInt;	//引用迭代器inputInt读取cin中的第一个整数,并赋值给number1
		++inputInt;
		//迭代器inputInt移动到输入流的下一个位置.使用++inputInt性能较好,不会创建临时对象.
		int number2 = *inputInt;	//引用迭代器inputInt读取cin中的第二个整数,并赋值给number2
	
		ostream_iterator<int> outputInt(cout);
		//创建一个ostream_iterator迭代器对象,向标准输出cout以类型安全的方式输出int类型的数值.
		
		cout << "The sum is: ";
		*outputInt = number1 + number2;	//使用*outputInt将这个整数送到cout输出.
		//如果要输出另一个数值,需要使用++outputInt进行递增操作.
		cout << endl;
	}

### 15.4 算法简介

作用在容器元素上的算法只是间接地通过迭代器来实现.

### 15.5 序列容器

C++序列容器包括:array,vector,deque,list和forward_list.

	array,vector和deque的类模板是基于数组的;
	list和forward_list是基于链表的.

使用情况:

	vector适用于在尾部进行插入操作;
	deque适用于在容器前后两端进行插入和删除操作;
	list适用于在中间或两端进行插入和删除操作.

#### 15.5.1 序列容器vector

vector是一种占用连续内存地址的数据结构,与数组类似.适合于需要执行随机存储.

	当一个vector的内存空间耗尽时,系统会分配一个更大的连续空间给到vector,病将原先的数据复制到新的空间,
	并把原空间释放.

实例1---使用vector和迭代器

	#include <iostream>
	#include <vector>
	using namespace std;
	
	template<typename T>
	void printVector(const vector<T> &integers2);	//函数模板
	
	int main()
	{
		const size_t SIZE = 6;
		int values[SIZE] = {1, 2, 3, 4, 5, 6};
		vector<int> integers;	//创建vector类模板的integers实例来保存int型的值.
	
		cout << "The initial size of integers is: " << integers.size()
			<< "\nThe initial capacity of integers is: " << integers.capacity();
		/*
		vector的size()成员函数返回当前容器中存储的元素个数.
		vector的capacity()成员函数返回了vector为容纳更多元素调整空间前可以存储的元素数.即当前的
			vector空间大小.
		PS:此处均为0, 0.
		*/
	
		integers.push_back(2);	//从vector末端插入元素.
		integers.push_back(3);
		integers.push_back(4);
	
		cout << "\nThe size of integers is: " << integers.size()
			<< "\nThe capacity of integers is: " << integers.capacity();
		/*
		一般capacity大于等于size.如果capacity过大,可以调用resize()成员函数来控制空间大小.
		*/
		cout << "\n\nOutput build-in array using pointer notation: ";
	
		for (const int *ptr = begin(values); ptr != end(values); ++ptr)
			cout << *ptr << ' ';
		/*
		begin(values):返回指向数组第一个元素的迭代器(数组中的指针可以视为迭代器);
		end(values):返回指向数组末端后一位的迭代器.
		ptr != end(values):检测指针是否到达数组的末端.
		begin/end函数也可以将容器作为参数输入.
		*/
	
		cout << "\nOutput vector using iterator notation: ";
		printVector(integers);
		cout << "\nReversed contents of vector integers: ";
	
		for (auto reverseIterator = integers.crbegin();
			reverseIterator != integers.crend(); ++reverseIterator)
			cout << *reverseIterator << ' ';
		/*反向遍历vector.*/
	
		cout << endl;
	}
	
	template<typename T>
	void printVector(const vector<T> &integers2)
	{
		for (auto constIterator = integers2.cbegin();
			constIterator != integers2.cend(); ++constIterator)
			cout << *constIterator << ' ';
		/*
		integers2.cbegin():返回指向容器的第一个元素的const_iterator(常量迭代器).
		auto:推断控制变量的类型.
		integers2.cend():返回指向容器的最后一个元素之后的const_iterator.
		constIterator != integers2.cend():检测迭代器是否达到vector末端.
		
		该语句也可以由下面语句替换:
		for (auto const &item : integers2)	//用的比较少???
			cout << item << ' ';
		*/
	}

实例2---vector的元素操作函数

	#include <iostream>
	#include <array>
	#include <vector>
	#include <algorithm>
	#include <iterator>
	#include <stdexcept>
	using namespace std;
	
	int main()
	{
		const size_t SIZE = 6;
		array<int, SIZE> values = { 1, 2, 3, 4, 5, 6 };
		vector<int> integers(values.cbegin(), values.cend());
		/*
		使用array的cbegin()到cend()(cend()指向values中最后一个元素之后的位置)位置(不包括cend()位置)
		的内容来初始化integers变量.
		*/
		ostream_iterator<int> output(cout, " ");
		/*
		ostream_iterator<int>是一个类型安全的输出机制.
		para1:指定输出流,即cout; para2:指定输出值之前的分隔符,此处为一个空格.
		*/
		
		cout << "Vector integers contains: ";
		copy(integers.cbegin(), integers.cend(), output);
		/*
		copy算法位于<algorithm>.
		para1迭代器参数指定的元素到para2迭代器参数(不包括)之间的所有元素拷贝到第三个参数迭代器(即输出
		迭代器).
		*/
	
		cout << "\nFirst element of integers: " << integers.front()
			<< "\nLast element of integers: " << integers.back();
		/*
		integers.front():vector的第一个元素;
		integers.back():vector的最后一个元素.
		*/
	
		integers[0] = 7;
		integers.at(2) = 10;
	
		integers.insert(integers.cbegin() + 1, 22);
		/*
		插入22到第一个迭代器参数指定的位置.本例中即为:下标为1的位置.其他元素会往后移.
		*/
	
		cout << "\n\nContents of vector integers after changes: ";
		copy(integers.cbegin(), integers.cend(), output);
	
		try
		{
			integers.at(100) = 777;
			/*
			vector的at()成员函数有边界检查,检查参数值是否在vector的下标范围内,不在则抛出out_of_range
			异常.定义在<stdexcept>中.
			异常类型:
				1.out_of_range:超过下标范围;
				2.invalid_argument:参数无效;
				3.length_error:试图创建过长的容器、字符串等;
				4.bad_alloc:内存不够导致new内存失败.
			*/
		}
		catch (out_of_range &outOfRange)	//捕获到out_of_range异常.
		{
			cout << "\n\nException: " << outOfRange.what();	
			//打印出异常的字符.会输出"invalid vector<T> subscript".
		}
	
		integers.erase(integers.cbegin());
		/*
			从容器中删除迭代器参数指向的元素.
		*/
		cout << "\n\nVector integers after erasing first element: ";
		copy(integers.cbegin(), integers.cend(), output);
	
		integers.erase(integers.cbegin(), integers.cend());
		/*
			从容器中删除第一个迭代器参数到第二个迭代器参数(不包括)之间的所有元素.
		*/
		cout << "\nAfter erasing all elements, vector integers "
			<< (integers.empty() ? "is" : "is not") << " empty";
		/*
			integers.empty():判断vector是否为空.为空返回true,非空返回false.
		*/
	
		integers.insert(integers.cbegin(), values.cbegin(), values.cend());
		/*
			para1:插入的迭代器位置;
			para2和para3:某一序列的开始和结束位置.结束位置为最后一个元素的后一个位置,插入操作不包含
			该位置.
		*/
		cout << "\n\nContents of vector integers before clear: ";
		copy(integers.cbegin(), integers.cend(), output);
	
		integers.clear();	//清空vector.clear或者erase都不会将内存返回给系统.
		cout << "\nAfter clear, vector integers "
			<< (integers.empty() ? "is" : "is not") << " empty" << endl;
	}

#### 15.5.2 序列容器list

实例---list的成员函数

	#include <iostream>
	#include <array>
	#include <list>
	#include <algorithm>
	#include <iterator>
	using namespace std;
	
	template<typename T>
	void printList(const list<T> &listRef);
	
	int main()
	{
		const size_t SIZE = 4;
		array<int, SIZE> ints = { 2,6,4,8 };
		list<int> values;
		list<int> otherValues;
	
		values.push_front(1);	//从头部插入整数值
		values.push_front(2);
		values.push_back(4);	//从尾部插入整数值
		values.push_back(3);
	
		cout << "values contains: ";
		printList(values);
	
		values.sort();	//sort函数对list中的元素进行升序排序
		cout << "\nvalues after sorting contains: ";
		printList(values);
	
		otherValues.insert(otherValues.cbegin(), ints.cbegin(), ints.cend());
		cout << "\nAfter insert, otherValues contains: ";
		printList(otherValues);
	
		values.splice(values.cend(), otherValues);
		/*
			list的splice函数删除para2容器中的元素,并把元素插入到para1迭代器参数指定的位置之前.
			此处为最后一个元素的后一个位置之前,即为紧跟着最后一个元素.
		*/
		cout << "\nAfter splice, values contains: ";
		printList(values);
	
		values.sort();
		cout << "\nAfter sort, values contains: ";
		printList(values);
	
		otherValues.insert(otherValues.cbegin(), ints.cbegin(), ints.cend());
		otherValues.sort();
		cout << "\nAfter insert and sort, otherValues contains: ";
		printList(otherValues);
	
		values.merge(otherValues);
		/*
			merge函数:将para list的元素删除,并把元素按以排序的顺序插入到values中.
			merge函数调用前,两个list必须已经使用相同的顺序排过一次序.
		*/
		cout << "\nAfter merge:\nValues contains: ";
		printList(values);
		cout << "\notherValues contains: ";
		printList(otherValues);
	
		values.pop_front();	//删除list中的第一个元素
		values.pop_back();	//删除list中的最后一个元素
		cout << "\nAfter pop_front and pop_back:\nvalues contains: ";
		printList(values);
	
		values.unique();	//删除list中重复的元素
		cout << "\nAfter unique, values contains: ";
		printList(values);
	
		values.swap(otherValues);	//交换两个list
		cout << "\nAfter swap:\nvalues contains: ";
		printList(values);
		cout << "\notherValues contains: ";
		printList(otherValues);
	
		values.assign(otherValues.cbegin(), otherValues.cend());
		/*
			用迭代器参数指定的起始位置和结束位置之间的内容取代某容器中原有的内容.
		*/
		cout << "\nAfter assign, values contains: ";
		printList(values);
	
		values.merge(otherValues);
		cout << "\nAfter merge, values contains: ";
		printList(values);
	
		values.remove(4);	//删除所有值为4的元素
		cout << "\nAfter remove(4), values contains: ";
		printList(values);
		cout << endl;
	}
	
	template<typename T>
	void printList(const list<T> &listRef)
	{
		if (listRef.empty())
			cout << "List is empty";
		else
		{
			ostream_iterator<T> output(cout, " ");
			copy(listRef.cbegin(), listRef.cend(), output);
		}
	}

#### 15.5.3 序列容器deque

deque的内存分布不连续.

	#include <iostream>
	#include <deque>
	#include <algorithm>
	#include <iterator>
	using namespace std;
	
	int main()
	{
		deque<double> values;
		ostream_iterator<double> output(cout, " ");
	
		values.push_front(2.2);	//从头部插入double值
		values.push_front(3.5);
		values.push_back(1.1);	//从尾部插入double值
	
		cout << "value contains: ";
	
		for (size_t i = 0; i < values.size(); ++i)
			cout << values[i] << ' ';	//支持类似vector使用下标来访问元素.
	
		values.pop_front();	//删除deque中得第一个元素
		cout << "\nAfter pop_front, values contains: ";
		copy(values.cbegin(), values.cend(), output);
	
		values[1] = 5.4;
		cout << "\nAfter values[1] = 5.4, values contains: ";
		copy(values.cbegin(), values.cend(), output);
		cout << endl;
	}

### 15.6 关联容器

有序关联容器:multiset, set, multimap, map.

无序关联容器:unordered_multiset, unordered_set, unordered_multimap, unordered_map.

### 15.6.1 关联容器multiset

multiset位于<set>,允许出现重复的关键字.

	#include <array>
	#include <iostream>
	#include <set>
	#include <algorithm>
	#include <iterator>
	using namespace std;
	
	int main()
	{
		const size_t SIZE = 10;
		array<int, SIZE> a = { 7, 22, 9, 1, 18, 30, 100, 22, 85, 13 };
		multiset<int, less<int>> intMultiset;
		/*
			less<int>为函数对象.此处表示创建按照升序排序的multiset的整数对象.
			递增顺序是multiset的默认顺序,因此less<int>也可省略.
		*/
		ostream_iterator<int> output(cout, " ");
	
		cout << "There are currently " << intMultiset.count(15)
			<< " values of 15 in the multiset\n";
		/*
			intMultiset.count(15):表示计算值为15的个数.
		*/
	
		intMultiset.insert(15);	//在multiset中插入15.
		intMultiset.insert(15);
		cout << "After inserts, there are " << intMultiset.count(15)
			<< " values of 15 in the multiset\n\n";
	
		auto result = intMultiset.find(15);
		/*
			intMultiset.find(15):返回一个指向15最早出现的iterator会const_iterator.
			没找到则返回一个与intMultiset.end()相同的迭代器.
		*/
	
		if (result != intMultiset.end())
			cout << "Found value 15\n";
	
		result = intMultiset.find(20);
		/*
			此处没找到,因此返回一个与intMultiset.end()相同的迭代器.
		*/
	
		if (result == intMultiset.end())
			cout << "Did not find value 20\n";
	
		intMultiset.insert(a.cbegin(), a.cend());
		/*
			把array对象a的元素插入到intMultiset中.
		*/
		cout << "\nAfter insert, intMultiset contains:\n";
		copy(intMultiset.cbegin(), intMultiset.cend(), output);
	
		cout << "\n\nLower bound of 22: "
			<< *(intMultiset.lower_bound(22));
		/*
		intMutiset.lower_bound(22):确定intMultiset中22最早出现的位置(是一个迭代器),类似cbegin.
		因此此处*(intMutiset.lower_bound(22))为22.
		*/
		cout << "\nUpper bound of 22: " << *(intMultiset.upper_bound(22));
		/*
		intMutiset.upper_bound(22):确定intMultiset中22最后出现的位置的后一个位置(是一个迭代器),
		类似cend.因此此处*(intMutiset.upper_bound(22))为30.
		*/
	
		auto p = intMultiset.equal_range(22);
		/*
		intMultiset.equal_range(22):返回一个包含函数lower_bound和upper_bound返回值的pair对象.
		*/
		cout << "\n\nequal_range of 22: " << "\nLower bound: "
			<< *(p.first) << "\nUpper bound: " << *(p.second);
		/*
		p.first:相当于intMutiset.lower_bound(22);
		p.second:相当于intMutiset.upper_bound(22).
		*/
		cout << endl;
	}

### 15.6.2 关联容器set

set位于<set>,仅有唯一的关键字.如果插入一个重复的关键字,则会忽略该关键字.

	#include <array>
	#include <iostream>
	#include <set>
	#include <algorithm>
	#include <iterator>
	using namespace std;
	
	int main()
	{
		const size_t SIZE = 5;
		array<double, SIZE> a = { 2.1, 4.2, 9.5, 2.1, 3.7 };
		set<double, less<double>> doubleSet(a.begin(), a.end());
		/*
		使用函数对象less<double>创建递增排列的doublez值集合doubleSet.
		*/
		ostream_iterator<double> output(cout, " ");
	
		cout << "doubleSet contains: ";
		copy(doubleSet.cbegin(), doubleSet.cend(), output);
	
		auto p = doubleSet.insert(13.8);
		cout << "\n\n" << *(p.first)
			<< (p.second ? " was" : " was not") << " inserted";
		/*
		doubleSet.insert(13.8):返回值为一个pair对象.
		p.first:表示指向插入项的const_iterator;
		p.second:表示是否插入成功的bool值(插入项不在集合中则为true,否则为false).
		*/
		cout << "\ndoubleSet contains: ";
		copy(doubleSet.begin(), doubleSet.end(), output);
	
		p = doubleSet.insert(9.5);
		cout << "\n\n" << *(p.first)
			<< (p.second ? " was" : " was not") << " inserted";
		/*
			因为9.5在集合中,因此返回false.
		*/
		cout << "\ndoubleSet contains: ";
		copy(doubleSet.begin(), doubleSet.end(), output);
		cout << endl;
	}

### 15.6.3 关联容器multimap

multimap用于快速存取key-value值对,以pair对象存取.multimap允许多个key对应一个value.位于<map>.

	#include <iostream>
	#include <map>
	using namespace std;
	
	int main()
	{
		multimap<int, double, less<int>> pairs;
		/*
			创建key是int,value为double,升序排序的multimap对象pairs.
		*/
		cout << "There are currently " << pairs.count(15)
			<< " pairs with key 15 in the multimap\n";
	
		pairs.insert(make_pair(15, 2.7));
		/*
			make_pair(15, 2.7):创建一个pair对象.该pair对象的first为15,second为2.7.
			此处也可以被简写为:
			pairs.insert({15, 2.7});	//类似python的dict.
		*/
		pairs.insert(make_pair(15, 99.3));
	
		cout << "After inserts, there are " << pairs.count(15)
			<< " pairs with key 15\n\n";
		/*
		pairs.count(15):统计key为15的key-value的个数.
		*/
	
		pairs.insert(make_pair(30, 111.11));
		pairs.insert(make_pair(10, 22.22));
		pairs.insert(make_pair(25, 33.333));
		pairs.insert(make_pair(20, 9.345));
		pairs.insert(make_pair(5, 77.54));
	
		cout << "Multimap pairs contains:\nKey\tValue\n";
	
		for (auto mapItem : pairs)
			cout << mapItem.first << "\t" << mapItem.second << "\n";
		cout << endl;
	}

### 15.6.4 关联容器map

map用于快速存取唯一的key-value值对,以pair对象存取.map中的key-value一对一映射.位于<map>.

	#include <iostream>
	#include <map>
	using namespace std;

	int main()
	{
		map<int, double, less<int>> pairs;
	
		pairs.insert(make_pair(15, 2.7));
		pairs.insert(make_pair(30, 111.11));
		pairs.insert(make_pair(5, 1010.1));
		pairs.insert(make_pair(10, 22.22));
		pairs.insert(make_pair(25, 33.333));
		pairs.insert(make_pair(5, 77.54));	//重复的key-value不会插入进去.
		pairs.insert(make_pair(20, 9.345));
		pairs.insert(make_pair(15, 99.3));
	
		cout << "pairs contains:\nKey\tValue\n";
	
		for (auto mapItem : pairs)
			cout << mapItem.first << "\t" << mapItem.second << "\n";
	
		pairs[25] = 9999.99;	//下标引用key,如果key存在则会将value替换.
		pairs[40] = 8765.43;	//下标引用key,key不存在则在map中插入新的key-value对.
	
		cout << "\nAfter subscript operation, pairs contains:\nKey\tValue\n";
	
		for (auto mapItem : pairs)
			cout << mapItem.first << "\t" << mapItem.second << "\n";
	
		cout << endl;
	}

### 15.7 容器适配器

容器适配器包括:stack, queue和priority_queue.

	1.适配器不是首类容器,没有提供真正用于存储元素的数据结构实现,而且不支持迭代器;
	2.适配器支持成员函数push和pop;
	3.适配器一般配合序列容器一起使用.
		stack<int, vector<int>> xxx;

#### 15.7.1 适配器stack

stack:后进先出.可以使用deque,vector,list等来实现.头文件<stack>.

	#include <iostream>
	#include <stack>
	#include <vector>
	#include <list>
	using namespace std;
	
	template<typename T>
	void pushElements(T &stackRef);
	
	template<typename T>
	void popElements(T &stackRef);
	
	int main()
	{
		stack<int> intDequeStack;
		/*
			stack需要使用一种容器来存储数据(e.g.deque,vector,list等).
			此处使用默认的deque.
		*/
		stack<int, vector<int>> intVectorStack;	//使用vector来实现stack
		stack<int, list<int>> intListStack;		//使用list来实现stack
	
		cout << "Pushing onto intDequeStack: ";
		pushElements(intDequeStack);
		cout << "\nPushing onto intVectorStack: ";
		pushElements(intVectorStack);
		cout << "\nPushing onto intListStack: ";
		pushElements(intListStack);
		cout << endl << endl;
	
		cout << "Popping from intDequeStack: ";
		popElements(intDequeStack);
		cout << "\nPopping from intVectorStack: ";
		popElements(intVectorStack);
		cout << "\nPopping from intListStack: ";
		popElements(intListStack);
		cout << endl;
	}
	
	template<typename T>
	void pushElements(T &stackRef)
	{
		for (int i = 0; i < 10; ++i)
		{
			stackRef.push(i);	//push(i):把元素插入到stack顶端.
			cout << stackRef.top() << ' ';	//top():获得stack顶端元素引用.
		}
	}
	
	template<typename T>
	void popElements(T &stackRef)
	{
		while (!stackRef.empty())	//empty():判断stack是否为空,为空返回true,非空返回false.
		{
			cout << stackRef.top() << ' ';
			stackRef.pop();	//pop():从顶端删除元素.
			/*
				stack.size():获得stack内元素个数.
			*/
		}
	}

#### 15.7.2 适配器queue

queue:队列,先进先出.可以用list或deque(默认)来实现.头文件<queue>.

	#include <iostream>
	#include <queue>
	using namespace std;
	
	int main()
	{
		queue<double> values;
	
		values.push(3.2);	//push(3.2):往queue的末端插入元素.
		values.push(9.8);
		values.push(5.4);
	
		cout << "Popping from values: ";
	
		while (!values.empty())	//empty():判断queue是否为空.空返回true,非空返回false.
		{
			cout << values.front() << ' ';	//front():获得queue的第一个元素
			values.pop();	//pop():从queue的头部删除元素
			/*
				back():获得queue的最后一个元素;
				size():获得queue中元素个数.
			*/
		}
	
		cout << endl;
	}

#### 15.7.3 适配器priority_queue

priority_queue按序插入元素和在头部删除元素.使用vector和deque实现.当元素插入到priority_queue中时,会自动按照优先顺序排序(使用堆排序)---默认为less<T>,即递增排序.优先级最高的元素首先被删除.

	#include <iostream>
	#include <queue>
	using namespace std;
	
	int main()
	{
		priority_queue<double> priorities;
		//实例存储double值的priority_queue.默认使用less<T>递增排序.
	
		priorities.push(3.2);	//push(3.2):插入元素.
		priorities.push(9.8);
		priorities.push(5.4);
	
		cout << "Popping from priorities: ";
	
		while (!priorities.empty())	//empty():判断priority_queue是否为空.为空返回true,
		{							//非空返回false.
			cout << priorities.top() << ' ';	//top():获得优先级最高的元素
			priorities.pop();	//弹出优先级最高的元素
		}
		cout << endl;
	}
	PS:
		结果为:Popping from priorities: 9.8 5.4 3.2

### 15.8 bitset类

略.

***

## Chapter 16.