# NumPy Course

## Chapter 0. NumPy简介

### 1. NumPy简介

NumPy(Numerical Python)是Python语言的一个扩展程序库,支持大量的维度数组与矩阵运算,也针对数组运算提供了大量的数学函数库.

NumPy是一个运行速度非常快的数学库,主要用于数组计算,包含:

	1.一个强大的N维数组对象ndarray;
	2.广播功能函数;
	3.整合C/C++/Fortran代码的工具;
	4.线性代数、傅里叶变换、随机数生成等功能.

### 2. NumPy应用

NumPy通常与SciPy(Scientific Python)和Matplotlib(绘图库)一起使用,这种组合广泛用于替代MatLab.是一个强大的科学计算环境,有助于我们通过Python学习数据科学或者机器学习等.

	1.SciPy:一个开源的Python算法库和数学工具包,包含的模块有:
		最优化、线性代数、积分、插值、特殊函数、快速傅里叶变换、信号处理和图像处理、常微分方程求解和其他科学与
		工程中常用的计算;
	2.Matplotlib:Python和NumPy的可视化操作界面.

***

## Chapter 1. NumPy安装

### 1.1 NumPy安装

**1.Windows的安装**

1.cmd下的安装

	pip install numpy scipy matplotlib pandas

2.pycharm的安装

	File->Settings->Project:xxx->点击"Project Interpreter"
	1.如果在cmd中安装了,在右边的框框中就会显示有"numpy",也可以进行第2步再安装一次;
	2.如果没有,点击右边的"+",增加package.在搜索中输入"numpy/scipy...",点击下面的"Install Package".
		安装即可.
	PS:安装经常会出现不成功的,使用pip安装稳妥点.

**2.linux下的安装**

略.

### 1.2 NumPy的测试

	from numpy import *		//导入numpy库
	print(eye(4))
	//结果为:--->输出一个对角矩阵
	[[1. 0. 0. 0.]
	 [0. 1. 0. 0.]
	 [0. 0. 1. 0.]
	 [0. 0. 0. 1.]]

***

## Chapter 2. NumPy ndarray对象

ndarray对象:n维数组对象,一系列同类型数据的集合,以0下标开始进行集合中元素的索引.

### 2.1 创建ndarray

创建ndarray只需要调用NumPy的array函数即可:

	numpy.array(object, dtype = None, copy = True, order = None, subok = false, ndmin = 0)
	/*
		para1:数组或嵌套的数列(e.g.一个list);
		para2:数组元素的数据类型,可选;
		para3:对象是否需要复制,可选
		para4:创建数组的样式(C为行方向,F为列方向,A为任意方向(默认));
		para5:默认返回一个与基类类型一致的数组;
		para6:指定生成数组维度.
	*/

### 2.2 实例

**实例1**

	import numpy as np
	a = np.array([1, 2, 3, 4])	//接收一个list
	print(a)
	//结果为:
	[1 2 3 4]	//生成一个一维数组

**实例2**

	import numpy as np
	a = np.array([[1, 2], [3, 4]])	//接收一个list(元素也为list),此时为二维数组
	print(a)
	//结果为:
	[[1 2]
	 [3 4]]		//生成一个二维数组

**实例3**

	import numpy as np
	a = np.array([1, 2, 3, 4], ndmin=2)	//ndmin=2:指定生成一个二维数组
	print(a)
	//结果为:
	[[1 2 3 4]]		//第二维为空

**实例4**

	import numpy as np
	a = np.array([1, 2, 3, 4], dtype = complex)	//dtype:指定元素类型,此处指定元素为虚数
	print(a)
	//结果为:
	[1.+0.j 2.+0.j 3.+0.j 4.+0.j]	//虚数数组