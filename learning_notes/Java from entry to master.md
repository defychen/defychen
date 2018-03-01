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
			long mylong = 46789451L;	//long型变量,占用8个字节.且数字后面必须有"L/l"---46789451L
			long result = mybyte + myshort + myint + mylong;
			System.out.println("The result of sum: " + result);	//输出结果"92606751"
		}
	}

**2.浮点类型**

	public class SumNumber{
		public static void main(String[] args){
			float f1 = 13.23f;		//单精度浮点型,占用4字节.且数字后面必须有"F/f"---13.23f.
			//虽然占4 byte,但是有效数字只有7 bit.因此一般显示为一个7位的数据
			double d1 = 4562.12d;	//双精度浮点型,占用8字节.数字后面可以带"D/d"
			double d2 = 45678.1564;	//由于默认浮点型为double,因此也可省略.
			double result = f1 + d1 + d2;
			System.out.println("The result of sum: " + result);	
			//输出结果为"50253.50639954224",显示为16位---因为float转成了double后面会填充一些数据
		}
	}

**3.字符类型**

	public class Export{
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
	PS:escape原意为逃跑,在此处为转义的意思.

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
			//成员方法中的常量可以在定义之后再进行初始化(与类的成员变量不同的地方),但也只能初始化一次.
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
			int b = 5;
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
	public class LeapYear{	//leap year:闰年.
		public static voic main(String[] args){
			Scanner scan = new Scanner(System.in);
			System.out.println("Please input a year:");
			long year = scan.nextLong();
			if((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
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

### 4.1 复合语句

复合语句"{}"以整个语句块为单位,相当于一条语句.

	public class Compound{	//类的"{}"也可以认为是一个复合语句
		public static void main(String[] args){	//main方法"{}"是一个复合语句
			int y = 40;
			System.out.println("Print y value: " + y);
			int z = 245;
			boolean b;
			{	//复合语句
				b = y > z;
				System.out.println("y > z,is this true: " + b);
			}
		}
	}

### 4.2 条件语句

**实例1---验证用户登录信息的合法性**

使用if...else if...else实现

	import java.util.Scanner;
	public class CheckLogin{
		public static void main(String[] args){
			Scanner scan = new Scanner(System.in);
			System.out.println("Please input login name:");
			String username = scan.nextLine();	//接收一行用户输入名
			System.out.println("Please input login password:");
			String password = scan.nextLine();
			if(!username.equals("mr")){
				//String.equals("xxx")方法,判断变量存储的字符是否为"xxx",是返回true,否返回false
				//此处用于验证,因此取反
				System.out.println("Invalid login name.");
			} else if(!password.equals("mrsoft")){
				System.out.println("Invalid login password");
			} else {
				System.out.println("Congrantulations, Login succeed!");
			}
		}
	}

**实例2---为新员工分配部门**

	import java.util.Scanner;
	public class Example{
		public static void main(String[] args){
			Scanner scan = new Scanner(System.in);
			System.out.println("Please Input the name of the new employee:");
			String name = scan.nextLine();
			System.out.println("Please input the Program language of the employee:");
			String language = scan.nextLine();
			switch(language.hashCode()){ //计算字符串的hash值,调用String.hashCode()方法即可
				case 3254818:	//java的哈希值
				case 2301506:	//Java的哈希值
				case 2269730:	//JAVA的哈希值
					System.out.println("Employee"+name+"will be assigned to Java department.");
					break;
				case 3104:		//C#的哈希值
				case 2112:		//C#的哈希值
					System.out.println("Employee"+name+"will be assigned to C# department.");
					break;
				case -709190099:		//Asp.net的哈希值?
				case 955463181:		//Asp.net的哈希值?
				case 9745901:		//Aap.net的哈希值?
					System.out.println("Employee"+name+"will be assigned to Asp.net department.");
					break;
				default:
					System.out.println("Our company don't need"+language+
						"program language developer.");
			}
		}
	}

### 4.3 循环语句

foreach语句:是for语句的简化版本,主要用于遍历数组.在Java 5之后增加的语法.所有的foreach语句都可以改写为for语句形式.

语法格式:

	for(元素变量x : 遍历对象obj) {	//相当于将对象obj(一般为数组名即可)进行遍历,遍历得到的每个值都存放到x中.
		//因此,x不用进行初始化.
		使用x的Java语句;
	}

foreach语句的使用---遍历一个一维数组.

	public class Repetition{
		public static void main(String[] args){
			int arr[] = {7, 10, 1};	//定义一个一维数组
			System.out.println("The element in the array is:");
			foreach(int x : arr){
				System.out.println(x+"\t");
			}
		}
	}

**实例1---使用while循环遍历数组**

	public class ErgodicArray{	//ergodic:遍历
		public static void main(String[] args){
			String[] aves = new String[] {"白鹭","丹顶鹤","黄鹂","鹦鹉","乌鸦","喜鹊","布谷鸟",
				"灰纹鸟","百灵鸟"};
			/*
			创建一个数组并初始化方法:
				xxx(类型)[] 变量名 = new xxx(类型)[]{"初始化信息"};
			*/
			int index = 0;
			System.out.println("我的花园有很多鸟,种类包括: ");
			while(index < aves.length){ //String.length是可以得到数组的长度(即元素个数)
				System.out.print(aves[index++]+" ");
				/*
				System.out.print()不换行
				System.out.println()换行.
				*/
			}
		}
	}

**实例2---使用for循环输出九九乘法表**

	public class MultiplicationTable{	//multiplication:乘法
		public static void main(String[] args){
			for(int i=1; i<9; i++){
				for(int j=1; j<=i; j++){
					System.out.print(j+"*"+i+"="+j*i+"\t");
				}
				System.out.println();	//输出一个换行符
			}
		}
	}

### 4.4 跳转语句

**1.break语句**

break语句只会跳出自己所在的那一层循环(只能跳出一层).

	public class MultiplicationTable{
		public static void main(String[] args){
			int a = 0;
			for(int i=0; i<=9; i++){
				for(int j=0; j<=9; j++){
					break; //会将最里层的for直接跳出去,因此后面的不执行.
					a++;
				}
				a++; //会执行10次
			}
			System.out.println("The value is: " + a); //值为10
		}
	}

**2.continue语句**

continue语句只会跳过自己所在的那一层后面的语句,进行下一次循环.

	public class ContinueDemo{
		public static void main(String[] args){
			int i= 0;
			System.out.println("All the odd number among 10:");
			while(i < 10){
				i++;
				if (i % 2 == 0){
					continue;	//偶数直接跳过
				}
				System.out.print(i + " ");	//输出所有奇数的值
			}
		}
	}

**实例1---终止循环体(终止单层和双层循环)**

	public class BreakCyc{
		public static void main(String[] args){
			System.out.println("\n-----------终止单层循环--------------");
			String[] array=new String[]{"白鹭","丹顶鹤","黄鹂","鹦鹉","乌鸦","喜鹊","老鹰",
			"布谷鸟","老鹰","灰纹鸟","老鹰","百灵鸟"};
			System.out.println("在你发现第一只老鹰之前,告诉我都有什么鸟.");
			foreach(String bird : array){
				if (bird.equals("老鹰"))
					break;
				System.out.print("有: " + bird + " ");
			}

			System.out.println("\n-----------终止双层层循环--------------");
			int[][] myScores=new int[][]{{67,78,63,22,66},
				{55,68,78,95,44},{95,97,92,93,81}}; //二维数组的声明int[][] myScores...
			System.out.println("这次考试成绩:\n 数学 \t语文 \t英语 \t美术 \t历史");
			No1:foreach(int[] first : myScores){ //No1:类似标号,标识这一层循环
				foreach(int second : first){
					System.out.print(i + "\t");
					if (i < 60){
						System.out.println("\n等等, "+i+"分的是什么?这个为什么不及格?");
						break No1;	//标识跳出No1这一层循环,即为最外层循环
					}
				}
				System.out.println();
			}
		}
	}

**实例2---循环体的过滤器(continue的使用)**

	public class CycFilter{
		public static void main(String[] args){
			String[] array=new String[]{"白鹭","丹顶鹤","黄鹂","鹦鹉","乌鸦","喜鹊","老鹰",
				"布谷鸟","老鹰","灰纹鸟","老鹰","百灵鸟"};
			System.out.println("在我的花园里有很多鸟类,但是最近来了几只老鹰,请帮我把他们抓走.");
			int eagleCount = 0;
			foreach(String bird : array){
				if (bird.equals("老鹰")){
					System.out.println("发现一只老鹰,已经抓到笼子里.");
					eagleCount++;
					continue; //直接结束本次循环
				}
				System.out.println("搜索鸟类,发现了:" + bird);
			}
			System.out.println("一共捉到了: "+eagleCount+"只老鹰.");
		}
	}

### 4.5 经典范例

**1.使用for循环输出空心的菱形**

略

**2.使用for循环输出杨辉三角**

略

***

## Chapter 5 Java数组

### 5.1 一维数组

**5.1.1 创建一维数组**

方法

	方法1
	int arr[];	//数组元素类型 数组名字[] (单个的"[]"表示要创建的数组为一维数组)
	方法2
	String[] str; //数组元素类型[] 数组名字

为数组分配内存

	arr = new int[5]; //数组名字 = new 数组元素类型[数组元素个数]
	PS:使用new关键字为数组分配内存时,数组中各个元素的初始化值都为0

声明一维数组并分配内存

	int month[] = new int[12];	//前面的中括号不可以填写内容,否则会出错.

**5.1.2 初始化一维数组**

	方法1:
	int arr[] = new int[]{1, 2, 3, 5, 25}; //创建5个元素的数组,其值为1, 2, 3, 5, 25
	方法2:
	int arr2[] = {34, 23, 12, 6}; //创建4个元素的数组,其值依次为34, 23, 12, 6.此时省略了new int等.

**实例1---一维数组求和**

	public class SumNum{
		public static void main(String[] args){
			int[] num = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
			int sum = 0;
			System.out.println("The sum of array: ");
			for(int i=0; i<10; i++){
				if(i==9){
					System.out.println(num[i] + "="); //输出一个"="
				}else{
					System.out.println(num[i] + "+"); //输出一个"+"
				}
				sum = sum + num[i];
			}
			System.out.println(sum); //输出和
		}
	}

**实例2---获取一维数组的最小值**

	public class MinNum{
		public static void main(String[] args){
			int[] num = {8, 3, 4, 1, 6, 10};
			System.out.println("输出一维数组: ");
			for(int i=0; i<num.length; i++){ //求数组的长度"num.length"
				System.out.print(num[i] + " ");
			}
			int min = num[0];
			for(int j=0; j<num.length-1; j++){
				if(min > num[j+1]){
					min = num[j+1];
				}
			}
			System.out.println("\n一维数组的最小值为: " + min);
		}
	}

### 5.2 二维数组

**5.2.1 创建**

创建

	int arr[][];
	
为二维数组分配内存

	1.每一维分配相同的内存
	a = new int[2][4];
	2.每一维单独分配内存
	a = new int[2][];
	a[0] = new int[2];	//a[0]这个一维分配2内存
	a[1] = new int[3];	//a[1]这个一维分配3内存

**5.2.2 初始化**

	int myarr[][] = {{12, 0}, {45, 10}};

**实例---输出一个3行4列所有元素都为0的矩阵**

	public class Matrix{
		public static void main(String[] args){
			int a[][] = new int[3][4]; //创建成功默认会所有元素初始化为0
			System.out.println("输出3行4列的数组: ");
			for(int i=0; i<a.length; i++){
				for(int j=0; j<a[i].length; j++){
					System.out.print(a[i][j] + " ");
				}
				System.out.println();	//输出一个空格
			}
		}
	}

### 5.3 数组综合应用实例

####实例1---对矩阵进行转置运算

转置即为行变为列,列变为行.

	public class ArrayRowColumnSwap{
		public static void main(String[] args){
			int arr[][] = new int[][]{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}; //二维数组
			System.out.println("转置前的矩阵是: ");
			printArray(arr);
			int arr2[][] = new int[arr.length][arr.length]; //3*3的矩阵
			for(int i=0; i<arr.length; i++){ //转置就是行变为列,列变为行
				for(int j=0; j<arr[i].length; j++){
					arr2[j][i] = arr[i][j];
				}
			}
			System.out.println("转置后的矩阵是: ");
			printArray(arr2);
		}
		private static void printArray(int[][] arr){
			for(int i=0; i<arr.length; i++){
				for(int j=0; j<arr[i].length; j++){
					System.out.print(arr[i][j] + " ");
				}
				System.out.println();
			}
		}
	}

####实例2---求方阵的逆

方阵的逆即为方阵主对角线上所有元素的和(Trace of the Matrix).逆同时也是方阵所有特征值之和.

	public class ArrayRowColumnSwap{
		public static void main(String[] args){
			int arr[][] = new int[][]{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}; //二维数组
			int tr = 0;
			System.out.println("方阵arr[][]是: ");
			for(int i=0; i<arr.length; i++){
				for(int j=0; j<arr[i].length; j++){
					System.out.print(arr[i][j] + " ");
				}
				System.out.println();
			}
			for(int i=0; i<arr.length; i++){
				tr += arr[i][i];
			}
			System.out.println("方阵arr[][]的逆是: " + tr);
	}

### 5.4 数组的基本操作

#### 5.4.1 使用foreach遍历二维数组

	public class Tautog{
		public static void main(String[] args){
			int arr[] = {{3, 4, 3}, {1, 2}};
			System.out.println("二维数组元素是: ");
			for(int x[] : arr){	//foreach语句遍历数组
				for(int e : x){
					System.out.print(e + " ");
				}
				System.out.println();
			}
		}
	}

#### 5.4.2 填充替换数组元素

**1.fill(int[] a, int value)**

a:需要进行替换的数组名; value:替换到数组的值. retval:填充后的数组.

	import java.util.Arrays; //导入java.util.Arrays类.数组操作是调用该类的方法
	public class Swap{
		public static void main(String[] args){
			int arr[] = new int[5];
			Array.fill(arr, 8);	//全部填充为8
			for(int i=0; i<arr.length; i++){
				System.out.print("第"+(i+1)+"个元素是:"+arr[i]);
			}
		}
	}

**2.fill(int[] a, int fromIndex, int toIndex, int value)**

a:需要进行填充的数组名; fromIndex:填充的起始下标; toIndex:填充的结束下标(不包括); value:填充到的数组的值; retval:填充后的数组. PS:如果索引值大于填充数组的长度,会报ArrayIndexOutOfBoundsException(数组越界异常).

	import java.util.Arrays; //导入java.util.Arrays类
	public class Displace{
		public static void main(String[] args){
			int arr[] = new int[]{45, 12, 2, 10, 1};
			Arrays.fill(arr, 1, 3, 8); //替换arr[1],arr[2]为8
			for(int i=0; i<arr.length; i++){
				System.out.print("第"+(i+1)+"个元素是:"+arr[i]);
			}
		}
	}

#### 5.4.3 对数组进行排序

**Arrays.sort(obj)**

sort对任意数组进行升序排序; obj:进行升序排序的数组名称. retval:排序后的数组.

	import java.util.Arrays;
	public class Taxis{
		public static void main(String[] args){
			int arr[] = new int[]{23, 42, 12, 8, 5, 10};
			System.out.println("原一维数组是: ");
			for(int i=0; i<arr.length; i++){
				System.out.print(arr[i] + " ");
			}
			Arrays.sort(arr);
			System.out.println("\n升序排列后的数组是: ");
			for(int i=0; i<arr.length; i++){
				System.out.print(arr[i] + " ");
			}
		}
	}

#### 5.4.4 复制数组

**1.copyOf(arr, int newlength)**

复制数组到长度为newlength的数组.

arr:要进行复制的数组; newlength:新数组的长度.如果新数组长度大于arr的长度,则用0填充;如果小于就会截取. retval:复制后的数组.

	import java.util.Arrays;
	public class Cope{
		public static void main(String[] args){
			int arr[] = new int[]{23, 42, 12};
			System.out.println("复制前的数组: ");
			for(int i=0; i<arr.length; i++){
				System.out.print(arr[i] + " ");
			}
			int newarr[] = Arrays.copyOf(arr, 5); //newarr长度为5,复制arr数据到新数组.
			System.out.println("复制后的数组: ");
			for(int i=0; i<newarr.length; i++){
				System.out.print(newarr[i] + " ");
			}
		}
	}

**2.copyOfRange(arr, int fromIndex, int toIndex)**

复制数组arr[fromIndex]到下标为toIndex的数组值到新数组,toIndex可以超出原数组的长度,超出的会填充为0.

arr:原数组; fromIndex:起始复制下标; toIndex:终止下标/超出(视为指定长度). retval:新数组.

	import java.util.Arrays;
	public class Repeat{
		public static void main(String[] args){
			int arr[] = new int[]{23, 42, 12, 84, 10};
			System.out.println("原来的数组: ");
			for(int i=0; i<arr.length; i++){
				System.out.print(arr[i] + " ");
			}
			int newarr[] = Arrays.copyOfRange(arr, 0, 3); //复制23, 42, 12.
			System.out.println("\n新数组: ");
			for(int i=0; i<newarr.length; i++){
				System.out.print(newarr[i] + " ");
			}
		}
	}

#### 5.4.5 范例

**1.一维、二维数组所占内存比较**

	public class OneArrayMemory{
		public static void main(String[] args){
			int num1 = 1024*1024*2;
			int[] arr1 = new int[num1];
			for(int i=0; i<arr1.length; i++){
				arr1[i]=1;
			}
			//计算内存总数(以MB为单位)
			long memory1 = Runtime.getRuntime().totalMemory()/1024/1024;
			System.out.println("一维数组占用内存为: " + memory1); //为15MB
			int num2 = 1024*1024;
			int[][] arr2 = new int[num2][2];
			for(int i=0; i<num2; i++){
				arr2[i][0] = 1;
				arr2[i][1] = 1;
			}
			//计算内存总数(以MB为单位)
			long memory2 = Runtime.getRumtime().totalMemory()/1024/1024;
			System.out.println("二维数组占用内存为: " + memory2); //为30MB
		}
	}

**2.使用插入排序法排序**

	public class InsertSort{
		public static void main(String[] args){
			int[] array = new int[]{20, 40, 90, 30, 80, 70, 50};
			System.out.println("排序前: ");
			for(int i=0; i<array.length; i++){
				System.out.print(array[i] + " ");
			}
			int tmp;
			int j;
			for(int i=1; i<array.length; i++){
				for(j=i-1; j>=0 && array[j]>tmp; j--){
					array[j+1]=array[j]; //数据往后移动.以便找到位置
				}
				array[j+1] = tmp; //找到位置插入数据
			}
			System.out.println("排序后: ");
			for(int i=0; i<array.length; i++){
				System.out.print(array[i] + " ");
			}
		}
	}

***

## Chapter 6 字符串

### 6.1 创建字符串

**1.String():创建一个字符串**

	String s = new String(); //创建一个空串

**2.String(char a[]):用一个字符数组a创建一个字符串**

	char a[] = {'g', 'o', 'o', 'd'};
	String s = new String(a); //等价于String s = new String("good");

**3.String(char a[], int offset, int length):提取一个字符数组a(从offset开始,提取length长)创建一个字符串**

	char a[] = {'s', 't', 'u', 'd', 'e', 'n', 't'};
	String s = new String(a, 2, 4); //等价于String s = new String("udent");

### 6.2 字符串操作

#### 6.2.1 字符串连接

字符串连接使用"+"进行连接

**1.字符串与字符串连接**

	String s1 = new String("Hello");
	String s2 = new String("world");
	String s3 = s1 + " " + s2; //将s1和s2连接后的结果赋值给s3(此时s3为"Hello world")

**2.字符串与其他数据类型连接**

	public class link{
		public static void main(String[] args){
			int booktime = 4;
			float practice = 2.5f;
			System.out.println("我每天要花费" + bootime + "小时看书;" + practice +
				"小时上机练习"); //字符串与整型数,浮点数连接.此时会将其他数据类型转换为字符串类型.
		}
	}

#### 6.2.2 获取字符串信息

**1.获取字符串长度---String.length()**

	String s = "We are students";
	System.out.println("字符串的长度是: " + s.length()); //结果为15

**2.获取指定字符的索引位置**

1.indexOf("s")方法:搜索字符串,得到某个字符首次出现的位置.如果没有检索到字符,则返回-1.

	public class Select{
		public static void main(String[] args){
			String s = "We are students";
			System.out.println("字符s在字符串中首次出现的位置是: " + s.indexOf("s"));
			//字符s首次出现的位置在7.索引是从0开始.
		}
	}

2.lastIndexOf("s")方法:搜索字符串,得到某个字符最后出现的位置.如果没有检索到字符,则返回-1.

	String s = "We are students";
	System.out.println("字符s在字符串中最后出现的位置是: " + s.lastIndexOf("s"));
	//字符s最后出现的位置在14.所以从0开始.
	PS:如果lastIndexOf(" ");如果参数为空字符串" ",则返回字符串的长度(和length方法相同)

**3.获取指定索引位置的字符---String.charAt(int index)**

	String s = "hello world";
	char mychar = s.charAt(6); //得到索引位置为6的字符.该字符为"w"

#### 6.2.3 去除字符串中的空格

**1.去除字符串的前导、尾部空格String.trim()**

	public class Blank{
		public static void main(String[] args){
			String s1 = "    Jave class    "; //前后各4个空格.总长18个字符
			String s2 = s1.trim(); //去掉前导、尾部空格
			System.out.println("原始字符串的长度: " + s1.length());
			System.out.println("去掉前导、尾部空格的字符串长度: " + s2.length()); //此时长度为10.
		}
	}

**2.去除字符串中的所有空格**

1.StringTokenizer()方法:使用分割和追加实现去除空格.

StringTokenizer(String str, String delim); 

说明: str:要去除空格的字符串; delim:需要去掉的字符(此处为空格);  retval: StringTokenizer

	import jave.util.StringTokenizer;	//包声明
	public class StringTo{
		public static void main(String[] args){
			String text = "  We are students  ";
			System.out.println("原字符串是: " + text);
			StringTokenizer st = new StringTokenizer(text, " "); //使用空格分割字符串
			StringBuffer sb = new StringBuffer();	//定义字符串缓冲对象.字符串生成器
			int i = 1;
			while(st.hasMoreTokens()){ //一个空格表示一个Token.判断是否还有空格
				i++;
				sb.append(st.nextToken()); //取从当前的Token到下一个Token之间的字符串进行追加
			}
			System.out.println("去掉字符串中的空格之后的字符串是: ");
			System.out.println(sb.toString()); //将StringBuffer转成字符串(sb.toString()).结果为"Wearestudents"
		}
	}	

2.replaceAll()方法:将空格用""替换

str.replaceAll(String regex, String replacement)

str:要处理的字符串; regex:str中想要被替换的字符串; replacement:新字符串,用于替换regex.

	String s = " J a v a 编 程 词 典 ";
	s = s.replacement(" ", ""); //将空格用没有空格替换,即去掉空格
	System.out.println("去掉空格后的字符串: " + s); //得到"Java编程词典"