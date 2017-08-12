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
			// TODO Auto-generated method stub
			System.out.println("Hello Java, " + say);	//输出文字信息到控制台
		}
	}
***
## Chapter 3 Java语言基础