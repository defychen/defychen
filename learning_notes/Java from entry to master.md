# Java from Entry to Master

## Chapter 1 初识Java

### 1.1 Jave语言概述

**1.1 Java语言的历史**

Java语言是Sun公司开发的,2009年Sun公司被Oracle公司收购.

Java语言不依赖于任何硬件平台和软件平台---也叫独立于平台.

JDK:Jave Development Kit,Jave开发套件.

**1.2 Java开发方向**

1)Java SE:用于桌面程序的开发.是学习Java EE和Java ME的基础.

2)Java EE:用于网页程序的开发.开发一些官方网站.

3)Java ME:用于嵌入式系统程序的开发.

### 1.2 安装及配置JDK

略

### 1.3 简单的Java程序

1)编写源代码---使用记事本即可

	public class MyApp{		//类名MyApp
		public static void main(String[] args){		//main函数
			System.out.println("I can study Java well!");	//输出
		}
	}

	//保存---保存的文件名必须与public class的名字相同,即为"MyApp.java"(.java--java程序扩展名)
	//保存时,带上""可以避免文件自动添加扩展名e.g.保存记事本时输入"MyApp.java",会直接生成MyApp.java文件

2)编译源代码---cmd中

	1)在cmd中切换到MyApp.java保存的路径
		cmd中直接输入"d:"即可切换到d盘. "dir":查看该目录的文件
	2)编译
		javac MyApp.java	//编译MyApp.java.编译时需要带扩展名"java"
		"dir"查看d盘目录会发现多了一个"MyApp.class"文件---即为编译后产生的文件
	3)运行class文件
		java MyApp		//java运行class文件.运行时不需要带扩展名,会自动寻找".class"文件
	//最终在DOS控制输出"I can study Java well!"
***
## Chapter 2 熟悉Eclipse开发工具

### 2.1 熟悉Eclipse

Eclipse是IBM公司开发的IDE集成开发工具,是Java集成开发工具之一.
	
**本机安装的是MyEclipse 10.**

### 2.2 使用Eclipse

**小技巧:**

1)显示行号:

	Java编辑区右键->Preferences->General->Editors->点上Text Editors->选中Show line numbers(显示行号)

2)执行程序:

	左侧Package Explorer选中源文件(e.g.HelloJava.java)->右键->选择Run as->1 Java Application

3)断点:

	在显示行号的位置双击会产生一个断点

4)调试方式运行Java程序(针对打了断点的情况):

	左侧Package Explorer选中源文件(e.g.HelloJava.java)->右键->选择Debug as->1 Java Application

5)调试:

	F6:单步跳过---单步执行,但不进入调用方法内部
	F5:单步跳入---单步执行,会进入调用方法内部执行.

**实例---简单的输出**

	public class HelloJava{		//系统自动生成
		/**
		 * @param args
		 */
		private static String say="I must learn Java well!";	//自己编辑的代码
		public static void main(String[] args){	
			//String[] args:表示字符串数组args,也可以写成String args[]---一般固定使用"String[] args".
			// TODO Auto-generated method stub
			System.out.println("Hello Java, " + say);	//输出文字信息到控制台
		}
	}
***
## Chapter 3 Java语言基础

### 3.1 Java程序基本结构

	package Mr;	//定义类所在的包"Mr",包的关键字"package".
	public class Example{	
		//创建类使用"public class Xxx"---此处类名Example(类名首字母大写).一般类和方法才加上"public"权限
		static int ONE = 1;	//定义类的成员变量
		public static void main(String[] args){	//定义主方法,字符串数组args
			String var = "Hello";	//String:字符串类.创建字符串对象.String---首字母大写,为一个类
			System.out.println(ONE);  //System:系统类名.out是System类提供的一个标准输出流.
			//println是out提供的方法,输出信息
			System.out.println(var);  //控制台输出
		}
	}

### 3.2 基本数据类型

**1.整数类型**

	public class Number{
		public static void main(String[] args){
			byte mybyte = 124;			//byte型变量,占用一个字节
			short myshort = 32564;		//short型变量,占用两个字节
			int myint = 45784612;		//int型变量,占用4个字节
			long mylong = 46789451L;	//long型变量,占用8个字节.且必须数字后面有"L/l"---46789451L
			long result = mybyte + myshort + myint + mylong;
			System.out.println("The result of sum: " + result);	//输出结果"92606751"
		}
	}

**2.浮点类型**

	public class SumNumber{
		public static void main(String[] args){
			float f1 = 13.23f;		//单精度浮点型,占用4字节.且必须数字后面有"F/f"---13.23f.
			//虽然占4 byte,但是有效数字只有7 bit.因此一般显示为一个7 位的数据
			double d1 = 4562.12d;	//双精度浮点型,占用8字节.数字后面可以带"D/d"
			double d2 = 45678.1564;	//由于默认浮点型为double,因此也可省略.
			double result = f1 + d1 + d2;
			System.out.println("The result of sum: " + result);	
			//输出结果为"50253.50639954224",显示为16位---因为float转成了double后面会填充一些数据
		}
	}

**3.字符类型**

	publice class Export{
		public static void main(String[] args){
			int i = 'd';	//定义int型变量.可以直接将一个Unicode字符赋值给int型(Java采用Unicode编码)
			char c = 97;	//char型变量,占用2个字节---与C不同的地方
			System.out.println("The Unicode value of d is: " + i);	//都带上"+"不会有问题
				//输出The Unicode value of d is: 100
			System.out.println("The Character of Unicode 97 is: " + c);
				//输出The Character of Unicode 97 is: a
		}
	}

	//输出转义字符
	char char1 = '\\';			//输出一个"\"
	char char2 = '\u2605';		//"\u":Unicode编码.得到Unicode位置2605的字符"★"
	System.out.println("The escape character print: " + char1 + char2);
	//输出多个变量直接后面使用"+ 变量名".结果为The escape character print:\★.

**4.布尔类型**

	boolean b1 = true, b2 = false, b3;	//布尔类型变量b1, b2, b3

### 3.2 变量与常量

java中系统内存划分:系统区(OS)、程序区(Program)、数据区(Data).程序执行时,程序代码(程序中的变量等也会)会加载到内存中的程序区,数据会存储在数据区中---不明白是哪些数据.

**常量**

	public class Part{
		static final double PI = 3.14;	//final限定为一个常量.格式为"static final double XXX"
					//该常量属于类的成员变量,因此必须在定义时就赋初值.否则编译出错
		static int age;	//非final常量,可以在别的地方进行赋值
		public static void main(String[] args){
			final int NUMBER;	//常量一般大写表示,且只能初始化一次.
			NUMBER = 1235;
			age = 22;
			System.out.println("Constant PI value is: " + PI);	//结果为3.14
			System.out.println("NUMBER value is: " + NUMBER);	//结果为1235
			System.out.println("age value is: " + age);			//结果为22
		}
	}

**成员变量**

在类体中定义的变量叫成员变量,成员变量在整个类中都有效.成员变量又分为实例变量和静态变量(加上static).

	public class Var{
		int x = 45;		//实例变量---整个类有效
		static int y = 90;	//静态变量(也叫类变量)---加上了static.
		//static静态变量:有效范围可以跨类,其他类中可以"类名.静态变量"使用(e.g."Var.y")
	}

**局部变量**

	public class Val{
		static int times = 3;	//静态变量(类变量)times
		public static void main(String[] args){
			int times = 4;		//局部变量
			System.out.println("The local variable times value is: " + times);
			//局部变量与静态变量重名,会将静态变量覆盖.此处结果为
			//The local variable times value is: 4
			System.out.println("The static variable times value is: " + Val.times);
			//引用静态变量方法"Val.times".结果为			
			//The static variable times value is: 3
		}
	}

**算数运算符**

	float number1 = 45.56f;
	int number2 = 152;
	System.out.println("Sum: " + (number1 + number2));	
	//可以在输出中"+(number1 + number2)"---计算后输出结果

**比较运算符**

	int number1 = 4;
	int number2 = 5;
	System.out.println("4 > 5(true or false): " + (number1 > number2));
	//可以直接在输出中"+(number1 > number2)"---得到boolean值.此处显示为"false"

**逻辑运算符**

	public class Calculation{
		public static void main(String[] args){
			int a = 2;
			int a = 5;
			boolean result1 = ((a > b) && (a != b));	//false
			boolean result2 = ((a > b) || (a != b));	//true
			System.out.println("result1: " + result1);	//显示为:result1: false
			System.out.println("result2: " + result2);	//显示为:result2: true
		}
	}

**位运算符**

	~:按位取反
	&:按位与
	|:按位或
	^:按位异或
	<<:左移
	>>:右移(最高位为0补0;为1(表示负数)补1)

**三目运算符**

	int i = 46;
	int j = 97;
	int z = i > j ? 100 : 200;	//判断i>j是否成立,不成立,将200赋给z
	System.out.println("z value: " + z); //输出为z value: 200.

**实例---不用其他变量实现两变量交换**

	import java.util.Scanner;	//导入扫描器
	public class VariableExchange{
		public static void main(String[] args){
			Scanner scan = new Scanner(System.in);	//创建扫描器.System.in---表示系统输入
			System.out.println("Please input Var A value:");
			long A = scan.nextLong();		//取得输入的值.nextLong()方法取得long型变量
			System.out.println("Please input Var B value:");
			long B = scan.nextLong();
			System.out.println("A = " + A + "\tB = " + B);	//连续输出
			System.out.println("After Variable Exchange...");
			A = A ^ B;
			B = B ^ A;	//等价于A ^ B ^ B--->得到A
			A = A ^ B;	//等价于A ^ B ^ A(因为此时的B中已经是A)--->得到B
			System.out.println("A = " + A + "\tB = " + B);
		}
	}

**实例---判断数字奇偶性**

	import java.util.Scanner;
	public class ParityCheck{
		public static void main(String[] args){
			Scanner scan = new Scanner(System.in);
			System.out.println("Please input an interger:");
			long number = scan.nextLong();
			String check = (number % 2 == 0) ? "It's a EVEN value!" : "It's a ODD value";
			System.out.println(check);
		}
	}

**强制类型转换**

	int a  = (int)45.23;	//得到a的值为45.

### 3.3 代码注释和编码规范

**注释**

1)单行注释

	使用"//"进行注释

2)多行注释

	使用"/*...*/"进行注释

3)文档注释

	使用"/** ... */"---比多行注释"/*...*/"多一个"*"

程序中注释要占程序代码总量的20%~50%.

### 3.4 经典范例

**实例1---判断一年是否是闰年**

闰年:能被4整除且不能被100整除或者能被400整除.

	import java.util.Scanner;
	public class LeapYear{
		public static voic main(String[] args){
			Scanner scan = new Scanner(System.in);
			System.out.println("Please input a year:");
			long year = scan.nextLong();
			if((year % 4 == 0 && year / 100 != 0) || (year % 400 == 0)){
				System.out.println(year + "is a leap year!");
			}else{
				System.out.println(year + "is not a leap year!");
			}
		}
	}

**实例2---求球形的体积**

球形的体积公式:V = 4/3 * Pi * r^3

	import java.util.Scanner;
	public class Volume{
		public static void main(String[] args){
			Scanner scan = new Scanner(System.in);
			System.out.println("Please input the radius:");
			double r = scan.nextDouble();
			final double PI = 3.1415926;	//定义一个常量PI
			double volume = 4.0/3.0 * PI * r * r * r;
			System.out.println("The radius of Sphere is: " + r);
			System.out.println("The volume of Sphere is: " + volume);
		}
	}
***
## Chapter 4 Java流程控制