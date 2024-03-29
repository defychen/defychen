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
		para6:指定生成数组的最小维度.
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
	a = np.array([1, 2, 3, 4], dtype = complex)	//dtype:指定元素类型,此处指定元素为复数
	print(a)
	//结果为:
	[1.+0.j 2.+0.j 3.+0.j 4.+0.j]	//复数数组

***

## Chapter 3. NumPy数据类型

### 3.1 NumPy支持的常用数据类型

NumPy支持的常用数据类型如下:

	bool_, int8, int16, int32, int64, uint8, uint16, uint32, uint64, float16, float32, float64,
	complex64(复数), complex128(复数)
	//使用方法:
	import numpy as np
	np.int32	//32-bit有符号整数

### 3.2 数据类型对象(dtype)

数据类型对象:用于描述数组中元素的类型.dtype构造方法:

	numpy.dtype(object, align, copy)
	/*
		para1:数据类型.e.g.
			np.int32:表示元素为int32类型;
			[('age', np.int8)]:'age':表示某一列,元素为int8类型.
		para2:对齐.为true则对齐类似C的结构体--->一般不用填充;
		para3:复制dtype对象.为false则是对内置数据类型对象的引用--->一般不用填充.
	*/

### 3.3 实例

**实例1**

	import numpy as np
	dt = np.dtype(np.int32)	//创建一个int32的dtype对象
	print(dt)
	//结果为:
	int32

**实例2**

	import numpy as np
	dt = np.dtype('i4')	//直接用'i1','i2','i4','i8'可以表示np.int8,np.int16,np.32,np.int64
	print(dt)
	//结果为:
	int32

**实例3**

	import numpy as np
	dt = np.dtype('<i4')	//'<i4':数据类型为小端;'>i4':数据类型为大端.
	print(dt)
	//结果为:
	int32

**实例4**

	import numpy as np
	dt = np.dtype([('age', 'i1'/np.int8)])
		//第一列类型为int8,且可以用array_name['age']直接取用第一列的所有元素
	a = np.array([(10,),(20,),(30,)], dtype = dt)
	print(a)
	print(a['age'])		//取用第一列的元素
	//结果为:
	[(10,) (20,) (30,)]
	[10 20 30]

**实例5**

	import numpy as np
	student = np.dtype([('name', 'S20'), ('age', 'i1'), ('marks', 'f4')])
	/*
		第一列类型为'S20':字符串,显示时前面会有个'b'字母.取第一列可用array_name['name'];
		第二列类型为'i1':int8.取第二列可用array_name['age'];
		第三列类型为'f4':float32(f2,f4,f8表示float16,float32,float64).取第三列可用
			array_name['marks']
	*/
	a = np.array([('abc', 21, 50), ('xyz', 18, 75)], dtype = student)
	print(a)
	print(a['name'], a['age'], a['marks'])
	//结果为:
	[(b'abc', 21, 50.) (b'xyz', 18, 75.)]
	[b'abc' b'xyz'] [21 18] [50. 75.]

***

## Chapter 4. NumPy数组属性

### 4.1 ndarray(数组)对象属性

NumPy的数组中ndarray对象属性如下:

	ndarray.ndim:数组维度的数量;
	ndarray.shape:数组的维度,对于矩阵:n行m列;
	ndarray.size:数组元素的总个数.相当于.shape中n*m的值;
	ndarray.dtype:ndarray对象的元素类型;
	ndarray.itemsize:ndarray对象中每个元素的大小,以字节为单位(因为数组中的元素都是相同类型,因此元素大小都是一样的);
	ndarray.flags:ndarray对象的内存信息;
	ndarray.real:ndarray元素的实部;
	ndarray.imag:ndarray元素的虚部;

### 4.2 ndarray对象属性的使用

**1.ndarray.ndim**

ndarray.ndim:表示数组维度的数量.

	import numpy as np
	a = np.arange(24)	//arange(24):生成一个0~23的数组
	print(a) //结果为:[0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23]
	print(a.ndim)	//输出维度数量,结果为:1
	b = a.reshape(2,4,3)	//调整维度为:2 4 3
	print(b)
	//结果为:
	[[[ 0  1  2]
	  [ 3  4  5]
	  [ 6  7  8]
	  [ 9 10 11]]
	
	[[12 13 14]
	  [15 16 17]
	  [18 19 20]
	  [21 22 23]]]
	print(b.ndim)	//输出维度数量,结果为:3

**2.ndarray.shape**

ndarray.shape:表示一个数组的维度,返回一个tuple(行数和列数).也可用于调整数组的大小.

	1.返回一个数组的维度
	import numpy as np
	a = np.array([[1, 2, 3], [4, 5, 6]])
	print(a.shape)
	//结果为:
		(2, 3)
	2.调整数组大小
	import numpy as np
	a = np.array([[1, 2, 3], [4, 5, 6]])
	a.shape = (3, 2)	//调整数组大小为3行2列
	print(a)
	//结果为:
	[[1 2]
	 [3 4]
	 [5 6]]
	PS:也可以使用reshape来调整数组维度:
		b = a.reshape(3, 2)
		print(b)	//结果为一样

**3.ndarray.itemsize**

ndarray.itemize:以字节的形式返回数组中每一个元素的大小.

	import numpy as np
	a = np.array([1, 2, 3, 4, 5], dtype = np.float64)
	print(a)
	print(a.itemsize)	//由于元素类型为float64,所以每个元素的大小为8字节
	//结果为:
	[1. 2. 3. 4. 5.]
	8

**4.ndarray.flags**

ndarray.flags:返回ndarray对象的内存信息.

	import numpy as np
	a = np.array([1, 2, 3, 4, 5], dtype = np.float64)
	print(a.flags)
	//结果为:
		C_CONTIGUOUS : True
		F_CONTIGUOUS : True
		OWNDATA : True
		WRITEABLE : True
		ALIGNED : True
		WRITEBACKIFCOPY : False
		UPDATEIFCOPY : False

***

## Chapter 5. NumPy创建数组

NumPy创建数组一般用ndarray,也可使用下面方式创建特殊的数组.

### 5.1 numpy.empty

numpy.empty方法主要用于创建一个指定形状、数据类型且未初始化的数组.

**1.numpy.empty原型**

	numpy.empty(shape, dtype = float, order = 'C')
	/*
		para1:数组形状,几行几列,用list/tuple说明;
		para2:数据类型,默认为float;
		para3:"C"或"F"两个选项,分别代表:行优先或列优先.
	*/

**2.实例**

	import numpy as np
	x = np.empty([3, 2], dtype = int)	//创建3x2的数组,元素为整型.但是元素值为随机值.
	print(x)
	//结果为:(元素值随机)
	[[6488126 7602290]
	 [6357090 6619251]
	 [6553600       0]]

### 5.2 numpy.zeros

numpy.empty方法主要用于创建一个指定形状、数据类型、数组元素以0来填充的数组.

**1.numpy.zeros原型**

	numpy.zeros(shape, dtype = float, order = 'C')
	/*
		para1:数组形状,几行几列,用list/tuple说明;
		para2:数据类型,默认为float;
		para3:"C"或"F"两个选项,分别代表:行优先或列优先.
	*/

**2.实例**

	1.创建一维的数组
	import numpy as np
	x = np.zeros(5)	//一维数组,总共5个元素,每个都是浮点0.
	print(x)
	//结果为:
		[0. 0. 0. 0. 0.]
	2.2*2的数组
	import numpy as np
	y = np.zeros((2, 2), dtype=[('x', 'i4'), ('y', 'i4')])
	//2x2.每一个元素都是dtype类型(即一个元素中含有两个int32的数据).访问第一个元素类型可用:y['x']访问;
	//访问第二个元素可用:y['y']访问.
	print(y)
	//结果为:
	[[(0, 0) (0, 0)]
	 [(0, 0) (0, 0)]]

### 5.2 numpy.ones

numpy.empty方法主要用于创建一个指定形状、数据类型、数组元素以1来填充的数组.

**1.numpy.ones原型**

	numpy.ones(shape, dtype = float, order = 'C')
	/*
		para1:数组形状,几行几列,用list/tuple说明;
		para2:数据类型,默认为float;
		para3:"C"或"F"两个选项,分别代表:行优先或列优先.
	*/

**2.实例**

	1.创建一维的数组
	import numpy as np
	x = np.ones(5)	//一维数组,总共5个元素,每个都是浮点1.
	print(x)
	//结果为:
		[1. 1. 1. 1. 1.]
	2.2*2的数组
	import numpy as np
	y = np.ones((2, 2), dtype=[('x', 'i4'), ('y', 'i4')])
	//2x2.每一个元素都是dtype类型(即一个元素中含有两个int32的数据).访问第一个元素类型可用:y['x']访问;
	//访问第二个元素可用:y['y']访问.
	print(y)
	//结果为:
	[[(1, 1) (1, 1)]
	 [(1, 1) (1, 1)]]

***

## Chapter 6. NumPy从已有的数组创建数组

### 6.1 numpy.asarray

numpy.asarray:从已有的list/tuple/带有list的tuple/带有tuple的list/多维数组等创建数组(即将其转为ndarray).

**1.numpy.asarray原型**

	numpy.asarray(a, dtype = None, order = None)
	/*
		para1:输入参数,可以是:list/tuple/带有list的tuple/带有tuple的list/多维数组;
		para2:数据类型,可选;
		para3:"C"或"F"两个选项,分别代表:行优先或列优先.
	*/

**2.实例---将list转换为ndarray**

	import numpy as np
	x = [1, 2, 3]
	a = np.asarray(x)
	print(a)
	//结果为:[1 2 3]

**3.实例---将tuple转换为ndarray**

	import numpy as np
	x = (1, 2, 3)
	a = np.asarray(x)
	print(a)
	//结果为:[1 2 3]

**4.实例---将带tuple的list转换为ndarray**

	import numpy as np
	x = [(1, 2, 3), (4, 5)]
	a = np.asarray(x)
	print(a)
	//结果为:[(1, 2, 3) (4, 5)]

**5.实例---设置dtype参数**

	import numpy as np
	x = [1, 2, 3]
	a = np.asarray(x, dtype = float)	//设置dtype参数
	print(a)
	//结果为:[1. 2. 3.]

### 6.2 numpy.frombuffer

numpy.frombuffer:接收buffer输入参数,以流的形式读入并转为ndarray对象.

**1.numpy.frombuffer原型**

	numpy.frombuffer(buffer, dtype = float, count = -1, offset = 0)
	/*
		para1:以流的形式读入(e.g.字符串:b'Hello world');
		para2:数据类型,可选;
		/*
			如果para2是字符串的时候,需要是字符串流(即bytestring).python3默认str是Unicode类型,要转
			成bytestring需要在字符串前加上b.
		para3:读取的数据量,默认是-1(读取所有数据);
		para4:读取的起始位置,默认是0.
	*/

**2.实例**

	import numpy as np
	s = b'Hello world'
		//此处一定要在前面加上b,否则在python3中会报错.python2没问题(默认字符串都是byptestring)
	a = np.frombuffer(s, dtype = 'S1')	// 'S1'此处表示字符串
	print(a)
	//结果为:[b'H' b'e' b'l' b'l' b'o' b' ' b'w' b'o' b'r' b'l' b'd']

### 6.3 numpy.fromiter

numpy.fromiter:从可迭代对象(迭代器)中建立ndarray,返回一维数组.

**1.numpy.fromiter原型**

	numpy.fromiter(iterable, dtype, count=-1)
	/*
		para1:可迭代对象(即迭代器)(e.g.list变成迭代器方法:iter(list)即可,其他的tuple/dict类似.但是dict用的比较少);
		para2:数据类型,可选;
		para3:读取的数据量,默认是-1(读取所有数据);
	*/

**2.实例**

	import numpy as np
	list = range(5)
	it = iter(list)	//得到list的迭代器it.
	x = np.fromiter(it, dtype = float)
	print(x)
	//结果为:[0. 1. 2. 3. 4.]

***

## Chapter 7. NumPy从数值范围创建数组

### 7.1 numpy.arange

numpy.arange:创建数值范围并返回adarray对象.

**1.numpy.arange原型**

	numpy.arange(start, stop, step, dtype)
	/*
		根据start与stop指定的范围以及step设定的步长生成一个ndarray.
		para1:起始值,默认为0;
		para2:终止值,无默认值,必须指定;
		para3:步长,默认为1;
		para4:数据类型,可选.
	*/

**2.实例---生成0到5的数组**

	import numpy as np
	x = np.arange(5)
	print(x)
	//结果为:[0 1 2 3 4]

**3.实例---设置类型为float**

	import numpy as np
	x = np.arange(5, dtype = float)
	print(x)
	//结果为:[0. 1. 2. 3. 4.]

**4.设置起始值、终止值及步长**

	import numpy as np
	x = np.arange(10, 20, 2)
	print(x)
	//结果为:[10 12 14 16 18]

### 7.2 numpy.linspace

numpy.linsapce:创建一个一维数组,数组是一个等差数列构成的.

**1.numpy.linspace原型**

	numpy.linspace(start, stop, num=50, endpoint=True, retstep=False, dtype=None)
	/*
		创建等差数列.
		para1:起始值;
		para2:终止值,如果endpoint为True,则包含该值,否则不包含;
		para3:数据总数,默认为50;
		para4:是否包含终止值,True包含,False不包含.默认为True(即包含);
		para5:为True则显示间距,否则不显示.默认为False(不显示);
		para6:数据类型,可选.
	*/

**2.实例---起始值为1,终止值为10,总共10个数**

	import numpy as np
	a = np.linspace(1, 10, 10)
	print(a)
	//结果为:[ 1.  2.  3.  4.  5.  6.  7.  8.  9. 10.]

**3.实例---数据元素全是1的数列**

	import numpy as np
	a = np.linspace(1, 1, 10)	//此处起始和终止相同,说明元素全相同
	print(a)
	//结果为:[1. 1. 1. 1. 1. 1. 1. 1. 1. 1.]

**4.实例---endpoint设为False和True的区别**

	1.为True
	import numpy as np
	a = np.linspace(10, 20, 5)
	print(a)
	//结果为:[10.  12.5 15.  17.5 20. ]--->包含终止值进行递增
	2.为False
	import numpy as np
	a = np.linspace(10, 20, 5, endpoint=False)
	print(a)
	//结果为:[10. 12. 14. 16. 18.]--->不包含终止值递增

**5.实例---retstep的使用**

	import numpy as np
	a = np.linspace(1, 10, 10, retstep = True)	//retstep=True:显示间距
	print(a)
	b = np.linspace(1, 10, 10).reshape([10, 1])	//调整维度为10行1列
	print(b)
	//结果为:
	(array([ 1.,  2.,  3.,  4.,  5.,  6.,  7.,  8.,  9., 10.]), 1.0)
	[[ 1.]
	 [ 2.]
	 [ 3.]
	 [ 4.]
	 [ 5.]
	 [ 6.]
	 [ 7.]
	 [ 8.]
	 [ 9.]
	 [10.]]

### 7.3 numpy.logspace

numpy.logspace:创建一个等比数列.

**1.numpy.logspace原型**

	numpy.logspace(start, stop, num=50, endpoint=True, base=10.0, dtype=None)
	/*
		创建等比数列(虽然写的是log,其实是以base为底的指数)
		para1:起始值(最后的结果为:base ** start);
		para2:终止值,如果endpoint为True,则包含该值(包含时结果为:base ** stop),否则不包含;
		para3:数据总数,默认为50;
		para4:是否包含终止值,True包含,False不包含.默认为True(即包含);
		para5:指数的底数;
		para6:数据类型,可选.
	*/

**2.实例---以10为底的指数**

	import numpy as np
	a = np.logspace(1.0, 2.0, num = 10)
	print(a)
	//结果为:
	[ 10.          12.91549665  16.68100537  21.5443469   27.82559402
	35.93813664  46.41588834  59.94842503  77.42636827 100.        ]

**3.实例---以2为底的指数**

	import numpy as np
	a = np.logspace(0, 9, 10, base = 2)	//para3:数据数量为10
	print(a)
	//结果为:[  1.   2.   4.   8.  16.  32.  64. 128. 256. 512.]

***

## Chapter 8. NumPy切片与索引

### 8.1 slice函数用于切片

	import numpy as np
	a = np.arange(10)	//结果为:[0 1 2 3 4 5 6 7 8 9]
	s = slice(2, 7, 2)
	/*
		slice函数:生成一个切片对象.
		para1:切片的start;
		para2:切片的stop;
		para3:切片的step.
		PS:此处为生成一个索引从2开始到7停止(不包含7),间隔为2的slice对象.
	*/
	print(a[s])	//np.arange()生成的数组可以接收一个slice对象.
	//结果为:[2 4 6]

### 8.2 直接使用":"来索引

**1.实例---指定start,stop,step**

	import numpy as np
	a = np.arange(10)
	b = a[2:7:2]	//直接使用":"间隔指定start,stop,step--->均为索引的下标信息
	print(b)
	//结果为:[2 4 6]

**2.实例---[]中只防止一个参数,表示指定的索引下标**

	import numpy as np
	a = np.arange(10)
	b = a[5]	//指定索引下标为5的值.此处结果为:5
	print(b)

**3.实例---[:]有一个":",表示从索引开始之后的所有元素(冒号后无数字)或者指定的范围(冒号后有数字)**

	1.无数字
	import numpy as np
	a = np.arange(10)
	b = a[2:]	//表示从索引2开始之后的所有元素,结果为:[2 3 4 5 6 7 8 9]
	print(b)
	2.有数字
	import numpy as np
	a = np.arange(10)
	b = a[2:5]	//表示选取索引2到5(不包括)之间的所有元素,结果为:[2 3 4]
	print(b)

**4.实例---提取多维数组**

	import numpy as np
	a = np.array([[1, 2, 3], [3, 4, 5], [4, 5, 6]])
	print(a)
	/*
		结果为:
			[[1 2 3]
			 [3 4 5]
			 [4 5 6]]
	*/
	b = a[1:]
	print(b)
	/*
		结果为:
		[[3 4 5]
		[4 5 6]]
	*/

***

## Chapter 15. NumPy数学函数

### 15.1 三角函数

**1.sin()/cos()/tan()函数**

	import numpy as np
	a = np.array([0, 30, 45, 60, 90])
	print(np.sin(a * np.pi / 180))
	//结果为:[0.         0.5        0.70710678 0.8660254  1.        ]
	print(np.cos(a * np.pi / 180))
	/*
		结果为:[1.00000000e+00 8.66025404e-01 7.07106781e-01 5.00000000e-01
			6.12323400e-17]
	*/
	print(np.tan(a * np.pi / 180))
	/*
		结果为:[0.00000000e+00 5.77350269e-01 1.00000000e+00 1.73205081e+00
			1.63312394e+16]
	*/

**2.arcsin()/arccos()/arctan()函数及numpy.degrees()**

arcsin()/arccos()/arctan()为反三角函数;numpy.degrees():将弧度转换为角度.

	import numpy as np
	
	a = np.array([0, 30, 45, 60, 90])
	sin = np.sin(a * np.pi / 180)
	print(sin)	//结果为:[0.         0.5        0.70710678 0.8660254  1.        ]
	inv = np.arcsin(sin)
	print(inv)	//反正弦:[0.         0.52359878 0.78539816 1.04719755 1.57079633]
	print(np.degrees(inv))	//将反正弦弧度转换为角度:[ 0. 30. 45. 60. 90.]
	cos = np.cos(a * np.pi / 180)
	print(cos)
	/*
		结果为:[1.00000000e+00 8.66025404e-01 7.07106781e-01 5.00000000e-01
			6.12323400e-17]
	*/
	inv = np.arccos(cos)
	print(inv)	//反余弦:[0.         0.52359878 0.78539816 1.04719755 1.57079633]
	print(np.degrees(inv))	//将反余弦弧度转换为角度:[ 0. 30. 45. 60. 90.]
	tan = np.tan(a * np.pi / 180)
	print(tan)
	/*
		结果为:[0.00000000e+00 5.77350269e-01 1.00000000e+00 1.73205081e+00
			1.63312394e+16]
	*/
	inv = np.arctan(tan)
	print(inv)	//反正切:[0.         0.52359878 0.78539816 1.04719755 1.57079633]
	print(np.degrees(inv))	//将反正切弧度转换为角度:[ 0. 30. 45. 60. 90.]

### 15.2 numpy.around()舍入函数

#### 15.2.1 numpy.around()原型

	numpy.around(a, decimals)
	/*
		para1:数组;
		para2:舍入的小数位数(即保留几位小数进行舍入).默认值为0,如果为负数,则四舍五入到小数点左侧的位置.
	*/

#### 15.2.2 实例

	import numpy as np
	a = np.array([1.0, 5.55, 123, 0.567, 25.532])
	print(a)	//结果为:[  1.      5.55  123.      0.567  25.532]
	print(np.around(a))
	/*
		小数点后保留0位进行舍入.结果为:[  1.   6. 123.   1.  26.]
	*/
	print(np.around(a, decimals = 1))
	/*
		小数点后保留1位进行舍入.结果为:[  1.    5.6 123.    0.6  25.5]
	*/
	print(np.around(a, decimals = -1))
	/*
		舍入到小数点左侧的位置.结果为:[  0.  10. 120.   0.  30.]
	*/

### 15.2 numpy.floor()

向下取整函数.

	import numpy as np
	a = np.array([-1.7, 1.5, -0.2, 0.6, 10])
	print(a)
	print(np.floor(a))
	/*
		向下取整.结果为:[-2.  1. -1.  0. 10.]
	*/

### 15.2 numpy.ceil()

向上取整函数.

	import numpy as np
	a = np.array([-1.7, 1.5, -0.2, 0.6, 10])
	print(a)
	print(np.ceil(a))
	/*
		向上取整.结果为:[-1.  2. -0.  1. 10.]
	*/

***

## Chapter 16. NumPy算术函数

### 16.1 +/-/*//

	import numpy as np
	a = np.arange(9, dtype = np.float_).reshape(3, 3)
	print(a)
	b = np.array([10, 10, 10])	//两个数组运算至少列数相同.
	print(b)
	print(np.add(a, b))
	/*
		np.add():两数组相加.
		结果为:
			[[10. 11. 12.]
			[13. 14. 15.]
			[16. 17. 18.]]
	*/
	print(np.subtract(a, b))
	/*
		np.add():两数组相减.
		结果为:
			[[-10.  -9.  -8.]
			[ -7.  -6.  -5.]
			[ -4.  -3.  -2.]]
	*/
	print(np.multiply(a, b))
	/*
		np.add():两数组相乘.
		结果为:
			[[ 0. 10. 20.]
			[30. 40. 50.]
			[60. 70. 80.]]
	*/
	print(np.divide(a, b))
	/*
		np.add():两数组相除.
		结果为:
			[[0.  0.1 0.2]
			[0.3 0.4 0.5]
			[0.6 0.7 0.8]]
	*/

### 16.2 numpy.reciprocal()

返回参数各个元素的倒数.

	import numpy as np
	a = np.array([0.25, 1.33, 1, 100])
	print(a)
	print(np.reciprocal(a))
	/*
		np.reciprocal():返回参数各个元素的倒数.
		结果为:[4.        0.7518797 1.        0.01     ]
	*/

### 16.3 numpy.power()

指数函数.para1为底,para2(可以为数组,给对应的para1指定幂)为幂.

	import numpy as np
	a = np.array([10, 100, 1000])
	print(a)
	print(np.power(a, 2))
	/*
		np.power(a, 2):表示a数组中各个元素的平方.
		结果为:[    100   10000 1000000]
	*/
	b = np.array([1, 2, 3])
	print(b)
	print(np.power(a, b))
	/*
		np.power(a, b):表示a数组中各个元素的对应b对应元素的幂次方.
		结果为:[        10      10000 1000000000]
	*/

### 16.3 numpy.mod()

对两个数组取余的函数.

	import numpy as np
	a = np.array([10, 20, 30])
	print(a)
	b = np.array([3, 5, 7])
	print(b)
	print(np.mod(a, b))
	/*
		np.mod(a, b):对数组a和b中的对应元素取余.
		结果为:[1 0 2]
	*/

***

## Chapter 20. matplotlib画图

matplotlib是一个python的2D绘图库,可以绘制直方图、功率谱、条形图、散点图等.

### 20.1 matplotlib画图的属性控制

#### 20.1.1 matplotlib的简单使用

1.代码:

	import matplotlib.pyplot as plt
	import numpy as np
	
	x = np.linspace(-1, 1, 50)	//创建一个一维数组,起始值为-1,终值为1,数值个数为50.
	y = 2 * x
	
	plot.plot(x, y)	//matplotlib.pyplot的plot函数用于绘制图形
	plot.show()		//绘制完了之后需要调用show()用于显示.

2.结果

![](images/matplotlib_easy_usage.png)

#### 20.1.2 figure对象的使用

在matplotlib中,默认弹出一个图表(一个图表是一个figure对象).可以指定创建多个figure对象,方法如下:

1.代码

	import matplotlib.pyplot as plt
	import numpy as np
	
	x = np.linspace(-1, 1, 50)
	y1 = x ** 2		//表示x的平方
	y2 = x * 2
	plt.figure()	//创建一个图表,绘制下面的图形
	plt.plot(x, y1)
	
	plt.figure(num = 3, figsize=(10, 5))
	/*
		创建第二个图表,绘制后面的图形.
		num = 3:默认标题显示从figure1开始递增,此处指定显示标题为figure3;
		figsize=(10, 5):表示指定窗口的大小.
	*/
	plt.plot(x, y2)
	plt.show()

2.结果为:

![](images/figure_uasge.png)

3.指定线相关属性

	plt.plot(x, y2, colod = 'red', linewidth = 3.0, linestyle = '--')
	//指定颜色为红色,线宽为3.0,线型为'--'

PS:Pycharm plot绘制多个figure时会出现多个图在同一个窗口中,设置plot独立窗口显示方法:

	File->Settings->Tools->Python Scientific->去掉Show plots in tool window选项即可.

#### 20.1.3 坐标轴的使用

1.限制坐标轴的范围

	import matplotlib.pyplot as plt
	import numpy as np
	
	x = np.linspace(-1, 1, 50)
	y = x * 2
	plt.plot(x, y)
	plt.xlim((0, 1))	//限制x坐标在(0, 1)之间.plt.xlim()参数为一个dict
	plt.ylim((0, 2))	//限制y坐标在(0, 2)之间.plt.ylim()参数为一个dict
	plt.show()

2.结果

![](images/matplotlib_limit_xy.png)

3.给坐标轴设置名称

	import matplotlib.pyplot as plt
	import numpy as np
	
	x = np.linspace(-1, 1, 50)
	y = x * 2
	plt.xlabel("x'slabel")	//设置x坐标轴名称为"x'slabel"
	plt.ylabel("y'slabel")	//设置y坐标轴名称为"xy'slabel"
	plt.plot(x, y)
	plt.show()

4.结果

![](images/matplotlib_xy_label.png)

5.更换坐标轴单位

	import matplotlib.pyplot as plt
	import numpy as np
	
	x = np.linspace(-1, 1, 50)
	y = x * 2
	new_ticks = np.linspace(-1, 2, 5)
	plt.xticks(new_ticks)	//更换x坐标为(-1, 2, 5)
	plt.yticks([-2, -1, 0, 1, 2], [r'$really\ bad$', r'$b$', r'$c\ \alpha$', 'd', 'good'])
	/*
	给y坐标更换名称,即:
		y坐标为-2时,更换为r'$really\ bad$'--->前后$表示中间为字符串,"\ "转译为空格.显示为really bad;
		y坐标为-1时,更换为r'$b$'--->前后$表示中间为字符串,显示为b;
		y坐标为-0时,更换为r'$c\ \alpha$'--->前后$表示中间为字符串,\alpha转译为希腊字母α,显示为c α;
		y坐标为1时,更换为'd'--->显示为字符d;
		y坐标为2时,更换为'good'--->显示为字符串good;
	*/
	plt.plot(x, y)
	plt.show()

6.结果

![](images/matplotlib_change_xy.png)

#### 20.1.4 legend图例的使用

1.代码

	import matplotlib.pyplot as plt
	import numpy as np
	
	x = np.linspace(-1, 1, 50)
	y1 = x * 2
	y2 = x ** 2
	
	l1, = plt.plot(x, y1, label = 'linear line')
	/*
		plt.plot():返回的是一个list,因此"l1,"后面需要逗号.
	*/
	l2, = plt.plot(x, y2, color = 'red', linewidth = 1.0, linestyle = '--', label = 'square 
		line')
	plt.legend(loc = 'upper right')
	/*
		loc:指定图例的位置:
			best:系统指定的最佳位置;
			upper right:右上角;
			upper left:左上角;
			lower left:左下角;
			lower right:右下角;
			right:靠右;
			center left:左中;
			center right:右中;
			lower center:中下;
			upper center:中上;
			center:中间位置.
	*/
	plt.show()

2.结果

![](images/legend_usage.png)

### 20.2 matplotlib画图类型

#### 20.2.1 scatter散点图

1.代码

	import matplotlib.pyplot as plt
	import numpy as np
	
	n = 1024
	X = np.random.normal(0, 1, n)
	/*
		para1:loc,正态分布的均值;
		para2:scale,正态分布的标准差(scale越大越矮胖,越小越瘦高);
		para3:size,输出的点数.
		np.random.normal(0, 1, 1024)即为标准正态分布.也可以简写为:
			np.random.normal(1024)--->默认均值为0,标准差为1.
	*/
	Y = np.random.normal(0, 1, n)
	T = np.arctan2(Y, X)	//--->此处不知道是干嘛用的????
	plt.scatter(X, Y, s = 75, c = T, alpha = 0.5)
	/*
		plt.scatter():采用scatter绘制点.采用X,Y作为输入点,颜色c为T,透明度alpha为50%.
	*/
	plt.xlim((-1.5, 1.5))	//设置x轴显示范围为(-1.5, 1.5)
	plt.xticks([])	//xticks()函数隐藏x坐标轴.
	plt.yticks((-1.5, 1.5))
	plt.yticks([])	//yticks()函数隐藏y坐标轴.
	plt.show()

2.结果

![](images/scatter_figure.png)

#### 20.2.2 柱状图

--->用于机器学习.

### 20.3 在一个窗口中绘制多图

#### 20.3.1 使用subplot函数

1.代码

	import matplotlib.pyplot as plt
	plt.figure(figsize = (6, 5))	//设置窗口大小为高6,长5.
	
	ax1 = plt.subplot(3, 1, 1)
	//绘制子图(行,列,编号).此处为:3行1列,第一个图.
	ax1.set_title("ax1 title")
	plt.plot([0, 1], [0, 1])	//此处为绘制[0,1]和[0,1]一一对应.即正比例函数
	
	ax2 = plt.subplot(3, 3, 4)	//此处为3行3列,第4个图.即第2行的第1个图(每行3个).
	ax2.set_title("ax2 title")
	
	ax3 = plt.subplot(3, 3, 5)	//此处为3行3列,第5个图.即第2行的第2个图(每行3个).
	ax4 = plt.subplot(336)		//336写法和(3, 3, 6)一样.此处为第2行的第3个图(每行3个).
	ax5 = plt.subplot(3, 2, 5)
	//此处为3行2列,第5个图.第3行的第1个图(每行3个,第5个图刚好是第3行第1个).
	ax6 = plt.subplot(326)
	//此处为3行2列,第6个图.第3行的第2个图(每行3个,第6个图刚好是第3行第2个).
	plt.show()

2.结果

![](images/subplot_usage.png)

#### 20.3.2 次坐标轴

1.代码

	import matplotlib.pyplot as plt
	import numpy as np
	
	x = np.arange(0, 10, 0.1)
	y1 = 0.05 * x ** 2
	y2 = -1 * y1
	
	fig, ax1 = plt.subplots()
	/*
		figure:整个图像为一个figure对象;
		axes:一个figure对象可以包含多个axes对象,每个axes对象都拥有自己坐标系统的绘图区域
			(类似由axes来标识子图).
		plt.subplots(nrows = n, ncols = m)--->绘制n * m个子图.返回一个figure对象和axes对象tuple.
			默认为1 * 1,即只有一个子图.
	*/
	ax2 = ax1.twinx()
	/*
		ax1.twinx():添加y轴的坐标轴;
		ax2.twiny():添加x轴的坐标轴.返回另一套坐标系统,但是子图是和ax1共用的.
	*/
	ax1.plot(x, y1, 'g-')
	ax2.plot(x, y2, 'b-')
	
	ax1.set_xlabel('X data')
	ax1.set_ylabel('Y1 data', color = 'g')
	ax2.set_ylabel('Y2 data', color = 'b')	//为另一套坐标系统添加y轴标签.
	plt.show()

2.结果

![](images/add_twinx.png)

**其他暂略,参考笔记如下网址:**

[参考笔记](https://blog.csdn.net/gaotihong/article/details/80983937)