# Java from Entry to Master

## Chapter 1 初识Java

### 1.1 Jave语言概述

**1.1 Java语言的历史**

Java语言是Sun公司开发的,2009年Sun公司被Oracle公司收购.

Java语言不依赖于任何硬件平台和软件平台---也叫独立于平台.

JDK:Jave Development Kit,Java开发套件.

**1.2 Java开发方向**

1)Java SE:用于桌面程序的开发.是学习Java EE和Java ME的基础.

2)Java EE:用于网页程序的开发.开发一些官方网站.

3)Java ME:用于嵌入式系统程序的开发.

### 1.2 安装及配置JDK

**1.JDK下载---Oracle官网下载**

Oracle[官网](https://www.oracle.com/index.html)

	Menu->Developers->Downloades->往下拉到"Java"->选择"Java(JDK) for Developers"
	->选择"Java Platform (JDK) 10"进行下载
	PS:如果官网下载不下来,可以百度搜索进行下载.

**2.JDK安装**

	1.将JDK安装到"D:\Program Files\Java\jdk-10.0.1";
	2.安装JDK过程中会自动要求安装JRE.JRE安装到"D:\Program Files\Java\jre-10.0.1".

**3.配置JDK**

	右击Computer->Properties->Advanced System settings->Environment Variables
	->在System variables中New一个变量:
			Variable name:"JAVE_HOME";
			Variable value:JDK路径(此处为"D:\Program Files\Java\jdk-10.0.1").
	  在System variables中Edit Path变量:
			在Path变量最后添加JAVE变量"C:\...;%JAVA_HOME%\bin;
	PS:在Windows系统中,环境变量使用英文的分号";"进行分隔;Linux系统中以英文的冒号":"分隔.

**4.测试JDK安装情况**

	在cmd窗口中输入:javac -version
	返回:javac 10.0.1--->表示安装成功.

**Eclipse启动时报"Error Could not create java virtual machine"的错误**

删除"C:\Windows\System 32\"目录下的"java.exe, javaw.exe, javaws.exe"三个文件.

具体查看[Error Could not create java virtual machine](https://blog.csdn.net/mpegfour/article/details/78622946)

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
		java MyApp		//java运行class文件.运行时不能带扩展名,会自动寻找".class"文件
	//最终在DOS控制输出"I can study Java well!"

***

## Chapter 2 熟悉Eclipse开发工具

### 2.1 熟悉Eclipse

Eclipse是IBM公司开发的IDE集成开发工具,是Java集成开发工具之一.

**Eclipse下载及安装**

下载网址[Eclipse](https://www.eclipse.org/downloads/)

	点击Download 64 bit下面的Download Packages->选择"Eclipse IDE for Java Developers"
	点击Windows 64 bit->Select Another Mirror
	->选择China - University of Science and Technology of China
	这种方式是下载了一个压缩包,解压就可以直接使用(不需要安装).

### 2.2 使用Eclipse

**小技巧:**

1)显示行号:

	Java编辑器左侧(靠近行号的地方)右击->Show Line Numbers

2)设置自动补全

	菜单->Window->Preferences->Java->Editor->Content Assist
	->Auto activation triggers for Java:
	默认只有".",在点后后面加上".abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".

3)执行程序:

	左侧Package Explorer选中源文件(e.g.HelloJava.java)->右键->选择Run as->1 Java Application

3)断点:

	在显示行号的位置双击会产生一个断点

4)调试方式运行Java程序(针对打了断点的情况):

	左侧Package Explorer选中源文件(e.g.HelloJava.java)->右键->选择Debug as->1 Java Application

5)调试:

	F6:单步跳过---单步执行,但不进入调用方法内部
	F5:单步跳入---单步执行,会进入调用方法内部执行.

6)File->New->创建时只有Project, Example, Others三个.

	刚解压好的Eclipse在新建时,可能只有Project, Example, Others三个选择.
	添加其他Java Project, Package, Class等选项方法:
	Window->Perspective->Customize Perspective.
	在Menu Visibility选项卡中,点击File->New,勾选需要显示的菜单项.
		常用的:Java Project, Package, Class, Interface, Source Folder, Enum,
		Annotation, Java Working Set, Scrapbook Page, Task, Folder, File,
		Untitled Text File等.
	再一次:File->New就会有那些选项.

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
		//创建类使用"public class Xxx"---此处类名Example(类名首字母大写).一般类和方法才加上
		//"public"权限
		static int ONE = 1;	//定义类的成员变量
		public static void main(String[] args){	//定义主方法,字符串数组args
			String var = "Hello";	//String:字符串类.创建字符串对象.String---首字母大写,为一个类
			System.out.println(ONE);  //System:系统类名.out是System类提供的一个标准输出流.
			//println是out提供的方法,输出信息
			System.out.println(var);  //控制台输出
		}
	}
	PS:类名必须和文件名相同(e.g.新建的java文件名为Hello1,则类名必须为Hello1),否则会报错.

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
			scan.close(); //需要将scan关闭掉.
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
			scan.close();
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
			scan.close();
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
			scan.close();
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
				//String类的equals("xxx")方法,判断变量存储的字符是否为"xxx",是返回true,否返回false
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
			switch(language.hashCode()){ //计算字符串的hash值,调用String的hashCode()方法即可
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

foreach语法:是for语句的简化版本,主要用于遍历数组.在Java 5之后增加的语法.所有的foreach语句都可以改写为for语句形式.

语法格式:

	for(元素变量x : 遍历对象obj) {	//相当于将对象obj(一般为数组名即可)进行遍历,
	//遍历得到的每个值都存放到x中.注意:仍然是以for开头.不是"foreach"
		//因此,x不用进行初始化.
		使用x的Java语句;
	}

foreach语法的使用---遍历一个一维数组.

	public class Repetition{
		public static void main(String[] args){
			int arr[] = {7, 10, 1};	//定义一个一维数组
			System.out.println("The element in the array is:");
			for(int x : arr){ //以for开头,一个一个遍历数组
				System.out.print(x+"\t"); //不换行
			}
		}
	}

**实例1---使用while循环遍历数组**

	public class ErgodicArray{	//ergodic:遍历
		public static void main(String[] args){
			String[] aves = new String[] {"白鹭","丹顶鹤","黄鹂","鹦鹉","乌鸦","喜鹊","布谷鸟",
				"灰纹鸟","百灵鸟"};
			/*
			创建一个数组并初始化的方法:
				类型[] 变量名 = new 类型[]{"初始化信息"};
			*/
			int index = 0;
			System.out.println("我的花园有很多鸟,种类包括: ");
			while(index < aves.length){ //String的length变量是可以得到字符串数组的长度(即元素个数)
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
			for(String bird : array){
				if (bird.equals("老鹰"))
					break;
				System.out.print("有: " + bird + " ");
			}

			System.out.println("\n-----------终止双层层循环--------------");
			int[][] myScores=new int[][]{{67,78,63,22,66},
				{55,68,78,95,44},{95,97,92,93,81}}; //二维数组的声明int[][] myScores...
			System.out.println("这次考试成绩:\n 数学 \t语文 \t英语 \t美术 \t历史");
			No1:for(int[] first : myScores){ //No1:类似标号,标识这一层循环
				for(int second : first){
					System.out.print(second + "\t");
					if (second < 60){
						System.out.println("\n等等, "+second+"分的是什么?这个为什么不及格?");
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
					System.out.print(num[i] + "="); //输出一个"="
				}else{
					System.out.print(num[i] + "+"); //输出一个"+"
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
			for(int x[] : arr){	//foreach方法遍历数组
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
			Arrays.fill(arr, 8);	//全部填充为8
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

复制数组arr到长度为newlength的数组.返回一个复制后的新数组.

arr:要进行复制的数组; newlength:新数组的长度.如果新数组长度大于arr的长度,则用0填充;如果小于就会截取. retval:复制后的新数组.

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

arr:原数组; fromIndex:起始复制下标; toIndex:终止下标/超出(视为指定长度),不包括toIndex这个元素. retval:新数组.

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
			System.out.println("一维数组占用内存为: " + memory1); //为15MB.实际情况好像不是这样
			int num2 = 1024*1024;
			int[][] arr2 = new int[num2][2];
			for(int i=0; i<num2; i++){
				arr2[i][0] = 1;
				arr2[i][1] = 1;
			}
			//计算内存总数(以MB为单位)
			long memory2 = Runtime.getRumtime().totalMemory()/1024/1024;
			System.out.println("二维数组占用内存为: " + memory2); //为30MB.实际情况好像不是这样
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
				tmp = array[i];
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
	String s = new String(a, 2, 4); //等价于String s = new String("uden");

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

**1.获取字符串长度---String的length()方法**

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
	//字符s最后出现的位置在14.索引从0开始.
	PS:如果lastIndexOf("");如果参数为空字符串""(不是空格字符串),则返回字符串的长度(和length方法相同)

**3.获取指定索引位置的字符---String的charAt(int index)方法**

	String s = "hello world";
	char mychar = s.charAt(6); //得到索引位置为6的字符.该字符为"w"

#### 6.2.3 去除字符串中的空格

**1.去除字符串的前导、尾部空格String的trim()方法**

	public class Blank{
		public static void main(String[] args){
			String s1 = "    Jave class    "; //前后各4个空格.总长18个字符
			String s2 = s1.trim(); //去掉前导、尾部空格
			System.out.println("原始字符串的长度: " + s1.length());
			System.out.println("去掉前导、尾部空格的字符串长度: " + s2.length()); //此时长度为10.
		}
	}

**2.去除字符串中的所有空格**

1.StringTokenizer()方法:使用某个字符(e.g.空格)来分割字符串.

StringTokenizer(String str, String delim);

说明: str:待分割的字符串; delim:分割字符(此处为空格);  retval: StringTokenizer(有分割标记的字符串)

	import java.util.StringTokenizer;	//包声明
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
			System.out.println(sb.toString()); //将StringBuffer转成字符串(sb.toString()).
											//结果为"Wearestudents"
		}
	}	

2.replaceAll()方法:将空格用""替换

str.replaceAll(String regex, String replacement)

str:要处理的字符串; regex:str中想要被替换的字符串; replacement:新字符串,用于替换regex.

	String s = " J a v a 编 程 词 典 ";
	s = s.replaceAll(" ", ""); //将空格用非空格替换,即去掉空格
	System.out.println("去掉空格后的字符串: " + s); //得到"Java编程词典"

#### 6.2.4 字符串替换(严格区分大小写)

**1.replace()方法:替换所有与指定字符串相匹配的字符串.**

str.replace(String regex, String replacement);

regex:想要被替换的字符串; replacement:新字符串,用来替换regex. retval:返回替换后的字符串.

	String s = "bad bad study";
	String news = s.replace("bad", "good"); //此时news为"good good study"(全部替换了)

**2.replaceFirst()方法:替换第一个匹配的字符串.**

str.replaceFirst(String regex, String replacement);

regex:想要被替换的字符串; replacement:新字符串,用来替换regex. retval:返回替换后的字符串.

	String s = "bad bad study";
	s = s.replaceFirst("bad", "good"); //此时s为"good bad study"(仅第一个匹配的字符串被替换了)

#### 6.2.5 判断字符串

**1.判断字符串是否相等**

1.equals()方法:严格区分大小写的比较两个字符串是否相等.

str.equals(String otherstr);

str:参与比较的一个字符串对象; otherstr:参与比较的另一个字符串对象; retval:返回boolean类型.

2.equalsIgnoreCase()方法:忽略大小写的比较两个字符串是否相等.

str.equalsIgnoreCase(String otherstr);

str:参与比较的一个字符串对象; otherstr:参与比较的另一个字符串对象; retval:返回boolean类型.

实例---"=="、equals和equalsIgnoreCase区别

	public class Opinion{
		public static void main(String[] args){
			String s1 = new String("I am a student");
			String s2 = new String("I am a student");
			String s3 = new String("I AM A STUDENT");
			String s4 = s1;

			boolean b1 = (s1 == s2); //"=="比较的是两个的内存位置,因为s1,s2内存位置不相同因此为"false"
			boolean b2 = (s1 == s4); //相同的位置,因此为"true"
			boolean b3 = s1.equals(s2); //比较的是内容,大小写都相同,因此为"true"
			boolean b4 = s1.equals(s3); //比较的是内容,大小写不同,因此为"false"
			boolean b5 = s1.equalsIgnoreCase(s2); //比较的是内容,忽略大小写,为"true"
			boolean b6 = s1.equalsIgnoreCase(s3); //比较的是内容,忽略大小写,为"true"
			
			System.out.println("s1 == s2: " + b1);
			System.out.println("s1 == s4: " + b2);
			System.out.println("s1 equals s2: " + b3);
			System.out.println("s1 equals s3: " + b4);
			System.out.println("s1 equalsIgnoreCase s2: " + b5);
			System.out.println("s1 equalsIgnoreCase s3: " + b6);
		}
	}

**2.判断字符串的开始与结尾**

1.startsWith()方法:判断当前字符串对象是否以参数指定的字符串开始.

str.startsWith(String prefix);

prefix:指作为前缀的字符串; retval:返回boolean类型

2.endsWith()方法:判断当前字符串对象是否以参数指定的字符串结尾.

str.endsWith(String suffix);

suffix:指作为后缀的字符串; retval:返回boolean类型.

实例---判断变量是否以指定的字符串开始和结尾.

	public class StartOrEnd{
		public static void main(String[] args){
			String num1 = "22045612";
			String num2 = "21304578";

			boolean b1 = num1.startsWith("22"); //因为num1是以"22"开始,为true
			boolean b2 = num1.endsWith("78"); //num1不是以"78"结尾,为false
			boolean b3 = num2.startsWith("22"); //num2不是以"22"开始,为false
			boolean b4 = num2.endsWith("78"); //num2是以"78"结尾,为true
		}
	}

#### 6.2.6 字母大小写转换

**1.toLowerCase()方法**

将字符串中的大写字母转换为小写字母(数字和非字符等不受影响.)

str.toLowerCase();

str:要进行转换的字符串; retval:转成小写后的字符串

**2.toUpperCase()方法**

将字符串中的小写字母转换为大写字母(数字和非字符等不受影响.)

str.toUpperCase();

str:要进行转换的字符串; retval:转成大写后的字符串.

实例---字符串的大小写转换

	public class UpAndLower{
		public static void main(String[] args){
			String s = new String("abc DEF");
			String news1 = s.toLowerCase(); //此时news1为"abc def"
			String news2 = s.toUpperCase(); //此时news2为"ABC DEF"
			...
		}
	}

#### 6.2.7 字符串分割

**1.split(String sign)方法**

用指定的分割符对字符串进行分割.

str.split(String sign);

sign:分割字符串用的分割符; retval:分割后的字符串,应该存放在一个字符串数组中.

实例---对字符串进行分割

	public class Division{
		public static void main(String[] args){
			String s = new String("abc, def, ghi, gkl");
			String[] news = s.split(","); //用逗号分割,分割出来4份
			System.out.println("分割后的字符串是: ");
			for(int i=0; i<news.length; i++){
				System.out.println(news[i]);
			}
		}
	}
	/*会得到: 
		abc
		def
		ghi
		gkl
	*/

**2.split(String sign, int limit)方法**

用指定的分割符(sign)对字符串进行分割,并限定分割的份数.

str.split(String sign, int limit);

sign:分割字符串用的分割符; limit:限制的分割份数. retval:分割后的字符串,应该存放在一个字符串数组中.

实例---限制分割份数的分割

	public class Division2{
		public static void main(String[] args){
			String s = new String("abc, def, ghi, gkl");
			String[] news2 = s.split(",", 2); //分割为2份,分割符为","(逗号)
			for(int i=0; i<news.length; i++){
				System.out.println("分割一次后的字符串是: ");
				System.out.println(news2[i]);
			}
		}
	}

	PS:定义多个分割符使用"|".e.g. ",|="(表示逗号或等于号); "，|。"(表示逗号或句号)

**实例---判断字符串是否是数字格式(全部是数字)**

	public class CheckNumber{
		public static void main(String[] args){
			String s = "12312312";
			if(CheckNumber.IsNumber(s)){ //调用类的方法"类名.类方法(...)"
				System.out.println(s + " 是数字格式");
			}else{
				System.out.println(s + " 不是数字格式");
			}
		}
		public static boolean IsNumber(String str){
			char[] c = str.toCharArray(); //将字符串转为字符数组(str.toCharArray())
			for(int i=0; i<c.length; i++){
				if(Character.isDigit(c[i])){
				//判断字符是否是数字:Character.isDigit(字符),是返回true;不是返回false.
					continue;
				}else{
					return false;
				}
			}
			return true;
		}
	}

### 6.3 格式化字符串

**1.日期格式化**

	import java.util.Date; //Date包,可以获取时间信息
	import java.util.Locale; //Locale包,可以设置本地为"US/CN"
	public class Example{
		public static void main(String[] args){
			Date today = new Date(); //声明一个Date对象,获取到时间信息
			String a = String.format(Locale.US, "%tb", today);
			//para1:设置本地为US(美国); "%tb":表示格式化为"月份缩写格式".即为格式化为月份的英文缩写
			String b = String.format(Local.US, "%tB", today);
			//para1:设置本地为US(美国); "%tB":表示格式化为"月份全写格式".即为格式化为月份的英文全写
			String c = String.format("%ta", today);
			//"%ta":表示格式化为星期简称格式
			String d = String.format("%tA", today);
			//"%tA":表示格式化为星期全称格式
			String e = String.format("%tY", today);
			//"%tY":表示格式化为4位的年份值
			String f = String.format("%ty", today);
			//"%ty":表示格式化为2位的年份值
			String g = String.format("%tm", today);
			//"%tm":表示格式化为2位的月份值
			String h = String.format("%td", today);
			//"%td":表示格式化为2位的日期值
			String i = String.format("%te", today);
			//"%te":表示格式化为1位的日期值
			...
		}
	}

**2.时间格式化**

	import java.util.Date;
	public class GetTime{
		public static void main(String[] args){
			Date date = new Date();
			System.out.println("默认时间格式: " + date); //Wed Feb 14 16:28:48 CST 2018
			System.out.println("2位数字的24小时制的小时: " + String.format("%tH", date));
			//"%tH":2位数字24小时制的小时(00~24).此处为16
			System.out.println("2位数字的12小时制的小时: " + String.format("%tI", date));
			//"%tI":2位数字的12小时制的小时.此处为04.
			System.out.println("2位数字的24小时制的小时: " + String.format("%tk", date));
			//"%tk":2位数字24小时制的小时(0~24:前面的0会省略).此处为16
			System.out.println("2位数字的12小时制的小时: " + String.format("%tl", date));
			//"%tl":2位数字的12小时制的小时(0~12:前面的0会省略).此处为4.
			System.out.println("两位数字的分钟: " + String.format("%tM", date));
			//"%tM":2位数字的分钟.此处为28
			System.out.println("两位数字中的秒钟: " + String.format("%tS", date));
			//"%tS":2位数字中的秒钟.此处为48
			System.out.println("时区缩写: " + String.format("%tZ", date));
			//"%tZ":时区缩写.此处为"CST"
			System.out.println("上午还是下午: " + String.format("%tp", date));
			//"%tp":上午或下午标记.此处为"下午"
		}
	}

**3.日期时间组合格式化**

	%tF--->"年-月-日"格式(4位的年份)----->2008-03-25
	%tD--->"月/日/年"格式(2位的年份)----->03/25/08
	%tc--->全部日期和时间信息------------>星期二 三月 25 15:20:00 CST 2008
	%tr--->"时:分:秒 PM/AM"格式(12时制)->03:22:06 下午
	%tT--->"时:分:秒"格式(24小时制)------->15:23:50
	%tR--->"时:分"格式(24小时制)---------->15:25

**4.常规类型格式化**

	%b--->格式化为boolean类型
	%s--->格式化为String类型
	%c--->格式化为字符类型
	%d--->格式化为10进制整数
	%0--->格式化为8进制整数
	%x--->格式化为16进制整数

	public class General{
		public static void main(String[] args){
			String str1 = String.format("%d", 400/2);
			//格式化为10进制整数.结果(200)存放在String类型中
			String str2 = String.format("%b", 3 > 5);
			//格式化为boolean类型,结果(false)存放在String类型中
			String str3 = String.format("%x", 200);
			//格式化为16进制整数.结果(c8)存放在String类型中
			...
		}
	}

实例---将金额格式化成大写

略

实例---将数字格式化成货币格式

略.

### 6.4 正则表达式

略

### 6.5 字符串生成器

略

***

## Chapter 7 类和对象

### 7.1 面向对象

类:是同一类事物的统称.封装对象的属性(成员变量表示)和行为(成员方法表示)的载体.

面向对象的特点:

1.封装:将同一类事物的特性与功能包装在一起,对外暴露调用的接口.

2.继承:从已有的类中派生出新的类,新的类能吸收已有类的数据属性和行为,并能扩展新的能力.

3.多态:同一个类的不同子类对象对同一个方法的调用产生不同的结果.主要体现在重写与重载两方面.

	package com.defy;

	/*人的类*/
	public class Person{
		public void cut(){
		}

		public static void main(String[] args){
			Person player = new Player(); //不同子类对象
			Person cooker = new Cooker(); //不同子类对象
			Person cuter = new Cuter(); //不同子类对象

			player.cut();
			cooker.cut();
			cuter.cut();
		}
	}

	/*演员*/
	class Player extends Person{ //extends:继承的关键字
		/*重写父类方法*/
		public void cut(){
			System.out.println("停止演戏");
		}
	}

	/*厨师*/
	class Cooker extends Person{ //extends:继承的关键字
		/*重写父类方法*/
		public void cut(){
			System.out.println("开始切菜");
		}
	}

	/*理发师*/
	class Cuter extends Person{ //extends:继承的关键字
		/*重写父类方法*/
		public void cut(){
			System.out.println("开始剪头发");
		}
	}
	//运行结果:
	停止演戏
	开始切菜
	开始剪头发

### 7.2 类
	
实例---自定义图书类

	1.新建一个名为com.book的package;
	2.再建立一个名为Book的class,然后编写代码:

	package com.book;	//package name

	public class Book{
		private String title; //成员变量
		private String author; //成员变量
		private double price; //成员变量

		/*静态成员:static声明的变量、常量和方法称为静态成员.
			1.静态成员属于类所有,所有的对象共享类的静态成员;
			2.静态成员在本类或其他类中调用方法:"类名.静态类成员";
			3.静态方法中不可以使用this关键字;
			4.静态方法中不可以直接调用非静态方法;
			5.类的方法中的局部变量不可以声明为static;
			6.非静态成员方法可以调用静态成员方法.
		*/
		static int book_num = 5;

		public Book(String title, String author, double price){
			//构造方法(1,无返回值;2,函数名与类名相同)
			this.title = title; 
			this.author = author;
			this.price = price;
			/*
			this:this引用就是一个对象的引用(可以认为指代的就是构造的对象)
			this可以调用类的成员变量和方法.也可以直接当作构造方法使用:
			this("《Java从入门到精通》", "xxx科技", 59.8);
				//此处this相当于Book(构造方法)
			*/
		}

		public String getTitle(){ //成员函数
			/*成员方法中定义的变量为局部变量
			e.g.在该方法中定义: int id = 0; //为局部变量
			*/
			return title; //此处相当于省略了this(实际上为:this.title);
		}

		public String getAuthor(){ //成员函数
			return author;
		}

		public double getPrice(){ //成员函数
			return price;
		}
	}

测试类

	1.在com.book的package下新建一个名为Test的类;
	2.在New Java Class的导航栏中选中"public static void main(String[] args)",
		将会自动创建main方法.
	3.编写代码,引入Book package.

	package com.book;	//package name
	import com.book.Book;	//引入包里面的具体哪个类

	public class Test{
		public static void main(String[] args){
			/*
				main方法称为主方法(静态的(static)、没有返回值(void)、
				形参为数组(String[] args))
			*/
			Book book = new Book("《Java从入门到精通》", "xxx科技", 59.8);
			System.out.println("书名: " + book.getTitle());
			System.out.println("作者: " + book.getAuthor());
			System.out.println("价格: " + book.getPrice() + "元");

			System.out.println("书本数量: " + Book.book_num); //调用静态常量
		}
	}

权限修饰符的说明

	private->本类:可见;	  同package的其他类或子类:不可见;	其他package的类或子类:不可见
	protected->本类:可见;	  同package的其他类或子类:可见;	其他package的类或子类:不可见
	public->本类:可见;	  同package的其他类或子类:可见;	其他package的类或子类:可见

### 7.3 对象

1.创建:使用"new"操作符;

2.访问:访问对象的属性和行为使用"对象.类成员"(静态成员除了使用"类名.静态成员"之外,也可以使用"对象.静态成员")

3.对象销毁:Java语言拥有一套完整的垃圾回收机制,Java的垃圾回收器将自动回收无用的被占用的内存资源(不需要手动回收).

实例---统计图书销量

	package com.book
	public class Book{
		private static int counter = 0; //静态私有成员
		public Book(String title){ //构造函数
			System.out.println("售出图书: " + title);
			counter++;
		}

		public static int getCounter(){
			return counter; //统计得到售出的图书数量
		}
	}

	//在项目中创建Test类,在main方法中创建Book对象并得到售出图书数量
	package com.book;
	import java.util.Random;	//Random函数需要import
	import com.book.Book;

	public class Test{
		public static void main(String[] args){
			String[] titles = {"《Java从入门到精通》", "《Java编程词典》", "《视频学Java》"};
			for(int i=0; i<5; i++){
				new Book(titles[new Random().nextInt(3)]);
				/*
					new Random():创建一个随机数
					nextInt(3):限制数据为整型,且范围在0 ~ 3(不包括3,即为:0,1,2)
				*/
			}
			System.out.println("总共销售了" + Book.getCounter() + "本图书!");
		}
	}

实例---单例模式的应用

单例模式:实例化的对象只有一个叫单例模式.

	public class Emperor{
		private static Emperor emperor = null; //对象的初始化可以被赋值为"null"
		private Emperor() { //将构造方法私有,此时只能在类内部进行对象的创建
		}
		public static Emperor getInstance(){
			if(emperor == null){
				emperor = new Emperor(); //对象为null时,创建一个对象.
			}
			return emperor; //否则就直接返回已经拥有的对象.保证唯一(单例)
		}
		public void getName(){
			System.out.println("我是皇帝--->Defy");
		}
	}
	//在项目中创建Test类,在main方法中调用静态getInstance方法创建Emperor对象并输出名字
	public class Test{
		public static void main(String[] args){
			System.out.println("创建皇帝1对象: ");
			Emperor emperor1 = Emperor.getInstance();
			emperor1.getName();
			System.out.println("创建皇帝2对象: ");
			Emperor emperor2 = Emperor.getInstance();
			emperor2.getName();
			System.out.println("创建皇帝3对象: ");
			Emperor emperor3 = Emperor.getInstance();
			emperor3.getName();
		}
		//所有得到的结果都是一样---单实例(单例模式)
	}

***

## Chapter 8 接口、继承与多态

### 8.1 接口

Java语言只支持单重继承,不支持多继承(即一个类只能有一个父类).但Java提供的接口可以实现类的多重继承功能.

#### 8.1.1 接口的定义

	[修饰符] interface 接口名 [extends 父接口列表] {
		[public] [static] [final] 变量;
		[public] [abstract] 方法;
	}
	/*
	修饰符:可选参数,指定接口的访问权限.可选值为public.如果省略则使用默认的访问权限.
	接口名:必选参数,为合法的Java标识符.一般首字母大写.
	extends 父接口列表:可选参数.指定要定义的接口继承于哪个父接口.
	方法:接口中的方法只有定义没有实现.
	*/

定义一个用于计算面积的接口

	//File->New->Interface,创建接口.
	package com.inter;

	public interface InterfaceCalculate {
		final float PI = 3.14159f;	//定义PI常量
		float getArea(float r);		//定义一个计算圆面积的方法getArea
		float getCircumference(float r);	//定义一个计算圆周长的方法getCircumference
		//接口中的方法只有定义没有实现
	}

PS:Java接口文件的文件名必须与接口名相同.

#### 8.1.2 接口的实现

一般在类中对接口进行实现.

	[修饰符] class 类名 [extends 父类名] [implements 接口名列表]
	/*
	修饰符:可选参数,指定接口的访问权限.可选值为public,abstract和final.
	类名:必选参数,为合法的Java标识符.一般首字母大写.
	extends 父类名:可选参数,指定要定义的类继承于哪个父类.
	implements 接口名列表:可选参数,指定该类实现哪些接口.如果存在多个接口名,
		各个接口名使用逗号","分隔.
	//在类中实现接口时,方法必须与接口中的定义完全一致,并且必须实现接口中定义的所有方法.
		但是方法实现时的权限(public,private,protected等)可以由类自己定义.
	*/

定义一个类Cire,实现计算面积的接口InterfaceCalculate.

	package com.inter;
	import com.inter.InterfaceCalculate;

	public class Cire implements InterfaceCalculate {
		public float getArea(float r) {
			float area = PI * r * r;
			return area;
		}

		public float getCircumference(float r) {
			float circumference = 2 * PI * r;
			return circumference;
		}
	}
	//PS:还需要创建一个测试类进行测试.

一个类中如果实现多个接口的冲突解决:

	1.如果出现变量冲突(即多个接口中定义相同变量名的变量),使用"接口名.变量"来访问不同接口中的变量;
	2.如果出现方法名冲突(即多个接口中定义相同的方法名),只实现一个方法即可.

#### 8.1.3 范例1:图片的不同格式保存

1.编写ImageSaver接口

	package com.picture;

	public interface ImageSaver {
		void save(); //保存图片的接口
	}

2.创建GIFSaver类,实现ImageSaver接口

	package com.picture;
	import com.picture.ImageSaver;

	public class GIFSaver implements ImageSaver {
		@Override
		public void save() {
			System.out.println("Save the picture as GIF formt!");
		}
	}

3.编写测试类

	package com.picture;
	import com.picture.GIFSaver;
	
	public class Test {
	
		public static void main(String[] args) {
			GIFSaver imageSaver = new GIFSaver();
			imageSaver.save();
		}
	}

#### 8.1.4 范例2:为汽车增加GPS定位功能

1.创建Car类

	package com.gpscar;

	public class Car {
		private String name;	//汽车名称
		private double speed;	//汽车速度

		public void setName(String name) {
			this.name = name;
		}
		public void setSpeed(double speed) {
			this.speed = speed;
		}
		
		public String getName() {
			return name;
		}
		public double getSpeed() {
			return speed;
		}

		@Override
		public String toString() {
			//每个类都继承自Object类,Object类提供了toString方法,此处为重写
			StringBuilder sb = new StringBuilder();
			//String,StringBuilder,StringBuffer都为字符串处理类
			sb.append("name: " + name + ","); //append方法:增加字符串
			sb.append("speed: " + spped + "kl/m");
			return sb.toString();	//String的toString方法,返回字符串类对象(即字符串信息).
		}
	}

2.编写GPS接口

	package com.gpscar;
	import java.awt.Point; //import Point类

	public interface GPS {
		Point getLocationg();	//返回Point类对象
	}

3.编写GPSCar类,继承Car类并实现GPS接口

	package com.gpscar;
	import com.gpscar.Car;
	import com.gpscar.GPS;
	import java.awt.Point;

	public class GPSCar extends Car implements GPS {
		@Override
		public Point getLocation() {
			Point point = new Point();
			point.setLocation(super.getSpeed(), super.getSpeed());
			/*
			Point类的setLocation返回,用于设置点的坐标信息
			super:得到当前类的对象的父类.
			super.getSpeed():引用当前对象的父类的成员函数.即Car类的getSpeed()函数
			*/
			return point;
		}
		@Override
		public String toString() {	//重写Object类的toString函数
			StringBuilder sb = new StringBuilder();
			sb.append(super.toString);
			/*
			引用当前对象的父类的成员函数.即Car类的重写的toString()函数
			*/
			sb.append(", location: (" + getLocation().x + ", " + getLocation().y + ")");
			return sb.toString();	//String的toString方法,返回字符串类对象(即字符串信息).
		}
	}

4.编写测试类

	package com.gpscar;
	import com.gpscar.GPSCar;

	public class Test {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		GPSCar car = new GPSCar();
		car.setName("Adui");
		car.setSpeed(60.0);
		System.out.println(car);
		//System.out.println打印对象,会调用对象的toString函数.
	}
	}


### 8.2 继承

#### 8.2.1 继承的实现

1.编写父类Bird

	package com.animal;

	public class Bird {
		String color = "white";
		String skin = "feather";
	}

2.编写子类Pigeon,继承自Bird

	package com.animal;
	import com.animal.Bird;

	public class Pigeon extends Bird {
		public static void main(String[] args) {
			Pigeon pigeon = new Pigeon();
			System.out.println(pigeon.color);	//继承自Bird类,因此具有父类的color变量
		}
	}

#### 8.2.2 继承中的重写

如果子类的方法与父类的完全相同(方法名,参数等完全相同),称为子类重写了父类的方法.也叫覆盖.

1.编写父类Animal

	package com.animal;

	public class Animal {
		public Animal() {
		}

		public void cry() {
			System.out.println("Aniaml cries...");
		}
	}

2.编写子类Dog,重写父类的cry()方法

	public class Dog extends Animal {
		public Dog() {
		}

		public void cry() {
			System.out.println("Dog barking...");
		}
	}

3.编写子类Cat,重写父类的cry()方法

	public class Cat extends Animal {
		public Cat() {
		}

		public void cry() {
			System.out.println("Cat meow...");
		}
	}

4.编写Sheep类,不定义任何方法.构造方法也不定义,会调用父类的构造方法进行构造.

	public class Sheep extends Animal {
	}

5.创建一个Zoo类,进行测试

	package com.animal;
	import com.animal.Animal;

	public class Zoo {
		public static void main(String[] args) {
			Dog dog = new Dog();	//创建对象并分配内存
			dog.cry();
			Cat cat = new Cat();
			cat.cry();
			Sheep sheep = new Sheep();
			sheep.cry();
		}
	}

#### 8.2.3 super关键字

子类可以继承父类的非私有的(非private限制的)成员变量和成员方法.如果子类的成员变量或成员方法与父类相同,父类的会被隐藏(方法也叫重写/覆盖).子类想要访问父类的成员变量或成员方法,可以使用super关键字.

**1.调用父类的构造方法**

必须在子类的构造方法中使用super关键字来调用.

	super([参数列表]);	//在子类的构造方法中使用

编写父类Beast

	public class Beast {
		String skin = "";
		public Beast() {
		}

		public Beast(String strSkin) {	//带参数的构造方法
			skin = strSkin;
		}

		public void move() {
			System.out.println("running...");
		}
	}

编写子类Tiger

	public class Tiger extends Bease {
		public Tiger() {
			super("stripe"); //super调用父类的构造方法
		}
	}

**2.操作被隐藏的成员变量和被重写的成员方法**

	super.成员变量;
	super.成员方法([参数列表]);

子类Tiger改变父类Beast的成员变量skin的值

	super.skin = "stripe";

子类Tiger访问父类的成员方法move()

	super.move();

#### 8.2.4 范例3: 经理与员工的差异

1.创建Employee类

	package com.employee;
	import java.util.Date;

	public class Employee {
		private String name;
		private double salary;
		private Date birthday;

		public String getName() {
			return name;
		}
		public void setName(String name) {
			this.name = name;	//this指代创建的对象
		}
		
		public double getSalary() {
			return salary;
		}
		public void setSalary(double salary) {
			this.salary = salary;
		}

		public Date getBirthday() {
			return birthday;
		}
		public void setBirthday(Date birthday) {
			this.birthday = birthday;
		}
	}

2.创建Manager类,继承自Employee.

	package com.employee;
	import com.employee.Employee;

	public class Manager extends Employee {
		private double bonus;	//经理的奖金
		public double getBonus() {
			return bonus;
		}
		public void setBonus(double bonus) {
			this.bonus = bonus;
		}
	}

3.创建Test测试类

	package com.employee;
	import com.employee.Employee;
	import com.employee.Manager;
	import java.util.Date;

	public class Test {
		public static void main(String[] args) {
			Employee employee = new Employee();
			employee.setName("Java");
			employee.setSalary(100);
			employee.setBirthday(new Date());

			Manager manager = new Manager();
			manager.setName("Defy");
			manager.setSalary(3000);
			manager.setBirthday(new Date());
			manager.setBonus(2000);
			
			System.out.println("Employee name: " + employee.getName());
			System.out.println("Employee salary: " + employee.getSalary());
			System.out.println("Employee birthday: " + employee.getBirthday());
			System.out.println("Manager name: " + Manager.getName());
			System.out.println("Manager salary: " + Manager.getSalary());
			System.out.println("Manager birthday: " + Manager.getBirthday());
			System.out.println("Manager bonus: " + Manager.getBonus());
		}
	}

#### 8.2.5 范例4: 重写父类中的方法

1.创建Employee类

	public class Employee {
		public String getInfo() {
			return "Parent class: I am emplyee!"
		}
	}

2.创建Manager类,继承自Employee

	public class Manager extends Employee {
		@Override
		public String getInfo() {
			return "Child class: I am manager!"
		}
	}

### 8.3 多态

#### 8.3.1 多态

类的多态性由重载(Overloading)和重写(Overriding)来实现.

重载(Overloading):一个类中出现多个方法名相同,但参数个数或参数类型不同的方法.

	方法返回值的类型不是区分重载的标志.

重写(Overriding):子类和父类的方法完全相同,子类中的会覆盖掉父类中的方法.

方法的重载实例:

	public class Calculate {
		final float PI = 3.14159f;

		/* Get circle area */
		public float getArea(float r) {
			float area = PI * r * r;
			return area;
		}

		/* Get rectangle area */
		public float getArea(float l, float w) {	//Overloading getArea function
			float area = l * w;
			return area;
		}

		/* Draw an arbitrary shape */
		public void draw(int num) {
			System.out.println(" Draw" + num + "arbitrary shapes");
		}

		/* Draw specify shape */
		public void draw(String shape) {	//Overloading draw function
			System.out.println("Draw" + shape);
		}

		public static void main(String[] args) {
			Calculate calculate = new Calculater();
			float l = 20;
			float w = 30;
			float areaRectangle = calculate.getArea(l, w);
			System.out.println("A rectangle area with length " + l + 
				" and width " + w + " is " + areaRectangle);
			float r = 7;
			float areaCirc = calculate.getArea(r);
			System.out.println("A circle area with radius " + r + " is " + areaCirc);
			int num = 7;
			calculate.draw(num);
			calculate.draw("Triangle");
		}
	}

#### 8.3.2 范例5: 计算几何图形的面积

1.创建一个Shape抽象类

	package com.area;

	public abstract class Shape {	//abstract class:抽象类
		public String getName() {
			return this.getClass().getSimpleName();
			/*
				this.getClass():得到类的完整名.包含package信息
				this.getClass().getSimpleName():只取类的完整名中的最后的类名.
			*/
		}

		public abstract double getArea();	//获得面积的抽象函数原型
	}

2.创建Circle类,继承自Shape类

	package com.area;
	import com.area.Shape;

	public class Circle extends Shape {
		private double radius;
		public Circle(double radius) {
			this.radius = radius;
		}

		@Override
		public double getArea() {
			return Math.PI *Math.pow(radius, 2); //pwd(x, y)--->表示x的y次方
		}
	}

3.创建Rectangle类,继承自Shape类

	package com.area;
	import com.area.Shape;

	public class Rectangle extends Shape {
		private double length;
		private double width;
		public Rectangle(double length, double width) {
			this.length = length;
			this.width = width;
		}

		@Override
		public double getArea() {
			return length * width;
		}
	}

4.创建Test类,用于测试

	package com.area;
	import com.area.Circle;
	import com.area.Rectangle;

	public class Test {
		public static void main(String[] args) {
			Circle circle = new Circle(1);
			System.out.println("The name of the graph: " + circle.getName());
			System.out.println("The area of the graph: " + circle.getArea());
			Rectangle rectangle = new Rectangle(1, 1);
			System.out.println("The name of the graph: " + rectangle.getName());
			System.out.println("The area of the graph: " + rectangle.getArea());
		}
	}

#### 8.3.2 范例6: 简单的汽车销售市场

1.创建Car抽象类

	package com.carbusiness;

	public abstract class Car {
		public abstract String getInfo();
	}

2.创建BMW类,继承自Car

	package com.carbusiness;
	import com.carbusiness.Car;

	public class BMW extends Car {
		@Override
		public String getInfo() {
			return "BMW";
		}
	}

3.创建Benz类,继承自Car

	package com.carbusiness;
	import com.carbusiness.Car;

	public class Benz extends Car {
		@Override
		public String getInfo() {
			return "Benz";
		}
	}

4.创建一个CarFactory类,定义静态方法getCar()--->用于创建汽车对象

	package com.carbusiness;
	import com.carbusiness.BMW;
	import com.carbusiness.Benz;

	public class CarFactory {
		public static Car getCar(String name) {
			if (name.equalsIgnoreCase("BMW")) {
				return new BMW();
			} else if (name.equalsIgnoreCase("Benz")) {
				return new Benz();
			} else {
				return null;	//Java中的空为null.
			}
		}
	}

5.创建Customer类,用于测试.

	package com.carbusiness;
	import com.carbusiness.Car;
	import com.carbusiness.CarFactory;

	public class Customer {
		public static void main(String[] args) {
			System.out.println("Customer wants to buy BMW: ");
			Car bmw = CarFactory.getCar("BMW");
			System.out.println("Car extraction: " + bmw.getInfo());
			System.out.println("Customer wants to buy Benz: ");
			Car benz = CarFactory.getCar("Benz");
			System.out.println("Car extraction: " + benz.getInfo());
		}
	}

***

## Chapter 9 类的高级特性

### 9.1 抽象类

1.创建抽象类Fruit

	abstract class Fruit {	//抽象类的定义"public(可省略) abstract class 类名"
		public String color;
		public Fruit() {
			color = "green";
		}
		/*定义抽象方法*/
		public abstract void harvest(); 
		/*抽象方法定义
			public abstract void(类型) func_name(param);
			1.抽象方法只有原型,没有实现.因此必须在子类中进行重写.
			2.抽象方法只能使用使用public/protected修饰,不能使用private/static修饰.
				private不能被子类继承;static属于类所有,因为抽象类无实体信息,因此不能使用static.
			3.包含一个或多个抽象方法的类必须定义为抽象类.
		*/
	}

2.创建子类Apple,继承自Fruit类.

	public class Apple extends Fruit {
		@Override	//重写抽象类的抽象方法harvest().
		public void harvest() {
			System.out.println("The apple has been harvested!");
		}
	}

3.创建子类Orange,继承自Fruit类.

	public class Orange extends Fruit {
		@Override
		public void harvest() {
			System.out.println("The orange has been harvested!");
		}
	}

4.创建测试类Test.

	public class Test {
		public static void main(String[] args) {
			System.out.println("The result of calling the harvest function of the 
				Apple class: ");
			Apple apple = new Apple();
			apple.harvest();
			System.out.println("The result of calling the harvested function of the
				Orange class: ");
			Orange orange = new Orange();
			orange.harvest();
		}
	}

### 9.2 内部类

#### 9.2.1 成员内部类

成员内部类:表示在类中声明一个类的成员.也可以叫内部类.
	
	成员内部类的特点:
	1.内部类可以直接访问外部类的成员方法和成员变量(即使声明为private的也可以被直接访问);
	2.内部类的实例一定要绑定在外部类的实例上.
	3.内部类可以访问外部类的成员,但是反之则不行.

**1.内部类的创建**

	public class OuterClass {
		InnerClass in = new InnerClass();	//在外部类中实例化内部类对象
		public void ouf() {
			in.inf();	//在外部类调用内部类方法
		}

		public InnerClass doit() {
			in.y = 4;	//在外部类访问内部类的成员变量
			return new InnerClass();
		}

		class InnerClass {
			InnerClass() {
			}
			public void inf() { //内部类的成员方法
			}
			int y = 0;	//内部类的成员变量
		}

		public static void main(String[] args) {
			OuterClass out = new OuterClass();
			OuterClass.InnerClass in = out.diot();
			/*
			内部类的对象实例化必须在外部类或外部类的非静态方法中实现
			1.外部类中实现:
				上述的:InnerClass in = new InnerClass();
			2.外部类的非静态方法中实现:
				上述的:public InnerClass diot();
			3.使用"外部类实例化对象.new 内部类"进行实例
				OuterClass out = new OuterClass();
				OuterClass.InnerClass in = out.new InnerClass();
			*/
		}
	}

**2.使用this关键字获取内部类与外部类的引用--->内/外部类的成员变量相同**

	public class OuterClass {
		private int x;
		private class InnerClass {
			private int x = 9;
			public void diot(int x) {
				x++;					//x为形参变量
				this.x++;				//this.x为内部类的成员变量x
				OuterClass.this.x++;	//OuterClass.this.x为外部类的成员变量x
			}
		}
	}

#### 9.2.2 局部内部类

局部内部类是指在类的方法中定义的类,其作用范围仅限于该方法.

	public class SellOutClass {
		private String name;
		public SellOutClass() {
			name = "apple";
		}

		public void sell(int price) {
			class Apple {	//局部内部类.属于方法sell的一部分,并非SellOutClass类的一部分.
				int innerPrice = 0;
				public Apple(int price) {
					innerPrice = price;
				}
				public void price() {
					System.out.println("Start to sell: " + name);
					System.out.println("Price is: " + innerPrice + "￥");
				}
			}

			Apple apple = new Apple(price);
			apple.price();
		}
		public static void main(String[] args) {
			SellOutClass sample = new SellOutClass();
			sample.sell(100);
		}
	}

#### 9.2.3 匿名内部类

匿名内部类就是没有名字的内部类.

	匿名内部类规则:
		1.匿名内部类不能定义任何静态成员、方法;
		2.匿名内部类中的方法不能是抽象的;
		3.匿名内部类必须实现接口或抽象父类的所有抽象方法;
		4.匿名内部类访问的外部类成员变量或成员方法必须用static修饰.

**1.接口**

	public interface Inner {
		public String say();
	}

**2.抽象类**

	public abstract class Inner1 implements Inner {
	}

**3.普通类**

	public class Inner2 implements Inner {
		public String say() {
			return "This is Inner2";
		}
	}

**4.匿名内部类,extends(继承)自某个类或implement(实现)声明的接口**

	public class Outer {
		public static String s1 = "This is s1 in Outer";
		public static String s2 = "This is s2 in Outer";
		private static String s3 = "This is s3 in Outer";

		public void method1(Inner inner) {
			System.out.println(inner.say());
		}

		private static String method2() {
			return "This is method2 in Outer";
		}

		public static void main(String[] args) {
			Outer outer = new Outer();

			/*Inner为接口*/
			outer.method1(new Inner() {
				String s1 = "This is s1 in Inner"; //匿名内部类与外部类相同变量s1.
				public String say() {
					return s1; //会使用内部类的变量
				}
				/*
					匿名内部类实现接口不需要implements.自动会匹配为implements interface_name.
				*/
			});

			/*Inner1为抽下类*/
			outer.method1(new Inner1() {
				String s2 = "This is s2 in Inner1";
				
				public String say() {	//为什么不需要"@Override"
					return Outer.s2; //在内部变量名相同时使用"类名.变量名"可以访问外部类声明为stataic的变量.
				}
				/*
					匿名内部类继承抽象不需要extends.自动会匹配为extends class_name.
				*/
			});

			/*Inner2为普通类*/
			outer.method1(new Inner2() {
				public String say() {
					return s3;	//可以直接访问外部类声明为static的public/private/protected变量
				}
			});

			/*Inner2为普通类*/
			outer.metho1(new Inner2() {
				public String say() {
					return method2();	//访问外部类的私有成员方法
				}
			});
		}
	}

	/*结果:
		This is s1 in Inner
		This is s2 in Outer
		This is s3 in Outer
		This is method2 in Outer
	*/

匿名内部类编译后会生成四个文件: Outer$1.class, Outer$2.class, Outer$3.class, Outer$4.class.

	匿名内部类的命名:外部类名$n.class

#### 9.2.4 静态内部类

用的比较少(略).

#### 9.2.5 内部类的继承

略.

#### 9.2.6 局部内部类设置闹钟

[Java类/package使用手册](http://tool.oschina.net/apidocs/apidoc?api=jdk-zh)

1.创建AlarmClock类

	import java.awt.Toolkit; //java工具箱
	import java.awt.event.ActionEvent;
	import java.awt.event.ActionListener;
	import java.text.SimpleDateFormat;
	import java.util.Date;

	import javax.swing.Timer;	//在指定时间触发ActionEvent(事件).

	public class AlarmClock {
		private int dedaly;	//延迟时间
		private boolean flag;	//是否要发出声音

		public AlarmClock(int delay, boolean flag) {
			this.delay = delay;
			this.flag = flag;
		}

		public void start() {
			class Printer implements ActionListener {	//局部内部类
				@Override
				public void actionPerformed(ActionEvent e) {
					SimpleDateFormat format = new SimpleDateFormat("k:m:s");
					String result = format.format(new Date());
					System.out.println("Current time: " + result);
					if (flag) {
						Toolkit.getDefaultToolkit().beep();
						/*
							Toolkit.getDefaultToolkit():得到默认工具包.
							Toolkit.getDefaultToolkit().beep():发出一个嘟嘟声.
						*/
					}
				}
			}
			new Timer(delay, new Printer()).start();	//delay单位为ms.
		}
	}
	
2.创建Test类

	import com.clock.AlarmClock;
	import javax.swing.JOptionPane; //弹出标准对话框

	public class Test {
		public static void main(String[] args) {
			AlarmClock clock = new AlarmClock(1000, true);
			clock.start();
			JOptionPane.showMessageDialog(null, "是否退出?"); //显示一个对话框
			System.exit(0);
		}
	}