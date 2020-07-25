# Python

## 1、Python 入门

python主要是用来编写应用程序的高级编程语言.

python是解释型语言,执行时一行一行的翻译成机器码,翻译过程非常耗时，因此运行速度慢.C语言是在运行前就已经被编译成机器码,因此运行快.

编译型语言直接发布编译后的机器码(e.g. windows的exe程序);解释性语言必须将源码发布出去.

**1.进入和退出Python:**

	$ python /*在linux中直接敲击命令python*/
	>>> exit() /*>>>:表明进入python交互式环境.exit():退出python交互式环境*/

python使用最广的解释器是CPython.

**2.运行Python文件(".py"后缀)**

	#!/usr/bin/python
	/*
	在.py文件开头指定使用/usr/bin/python解析脚本,在linux下如果使用"python xxx.py"该语句则会无效.加上
	该句可以让python程序使用"./xxx.py"执行.
	PS:通常有两种指定解释器:
		1)#!/usr/bin/python:直接写死了使用该路径下的python解释,但有时如果python没有被安装到该目录下
		或者希望使用其他版本的python去解释就需要修改脚本.因此这种写法不好;
		2)#!/usr/bin/env python:这种写法会去环境变量PATH指定的第一个python来执行脚本,这种方式比较
		好.扩展性好,且不易出错.
	*/
	$ chmod a+x xxx.py	/*为.py文件增加执行权限(一般注意查看其他脚本的权限,保持一致)*/
	./xxx.py	/*执行*/

**3.输入:raw_input()函数**

	name = raw_input('Please enter your name:')	#提示输入,输入的信息会放到name这一变量中
	print 'hello,', name						#打印出"hello, ...(用户输入的信息)"
	/*
		python 3.x去掉了raw_input(),使用input()函数替代raw_input().即:
		name = input("Please enter your name:")	//返回类型为str
	*/

raw_input()读取的内容永远是以字符串的形式返回,如果需要整数必须:

	birth = int(raw_input('Please input your date of birth'))	
	#出生日期是一个整数,需要使用int进行转换,转换为整型

**4.print函数**

	>>> print 'hello, world' /*输出"hello,world"*/
	>>> print 'The quick brown fox', 'jumps over', 'the lazy dog'
	# 其输出为The quick brown fox jumps over the lazy dog(","会输出空格,但是会忽略","后面的空格)
	/*
		python 3.x的print函数:
		print('The quick brown for', 'jumps over', 'the lazy dog')
		//全部使用双引号或单引号即可.
	*/

***

## 2、Python基础

Python的注释以"#"开头;以":"结尾时,缩进的语句视为代码块.

python使用"\n"换行,还可以用'''...'''表示多行内容(另起一行就是输出另一行)

	>>>print '''line1 
	...line2
	...line3'''		#交互式命令行中输入
	# xxx.py文件中表示为
	print '''line1					两次输出为:line1
	line2									  line2
	line3'''								  line3	#总共3行

### 2.1 数据类型和变量

**1.字符串**

	print('I\'m ok.')	//使用'\'做转义
	print('\\\n\\')
	/* 输出结果:
		\
		\
	*/
	print(r'\\\t\\')	//r''表示''内部的字符串默认不转义.结果为:\\\t\\

**2.布尔值**

Python用"True、Flase"表示布尔值,也用"and/or/not"做与、或、非运算.

	True and False
	True or True
	not False

	1.连续的判断用"and, or, not";
	2.大于某值而小于另一个值(e.g. 50 < a < 60).
	if (50 < a < 60) and (53 < b < 63) \
		and (95 < c < 110):
		...

**3.None(空值)**

None(空值)在Python是一个特殊的值.None不是0(0是有意义的),而是一个特殊的值.

Python属于动态语言(即同一个变量可以被反复的赋值).

**4.变量在计算机内存中的表示**

a = 'ABC'

1)在内存中创建'ABC'字符串;

2)在内存中创建一个名为"a"的变量,并把它指向'ABC'

	a = 'ABC'
	b = a		#创建一个变量b,指向a指向的字符串'ABC'
	a = 'XYZ'
	print b		#b打印出ABC

**5.常量**

Python中常量一般用全部大写字母的变量名表示:
	
	PI = 3.1415926

python3.x的除法

	1./结果为浮点数(即使两个整数恰好整除,结果也是浮点数)
		10 / 3		//结果为:3.333333333333
		9 / 3		//结果为:3.0
	2.//地板除(只取整数)
		10 // 3		//结果为:3
	3.取余
		10 % 3		//结果为:1
	

### 2.2 字符编码

ASCII编码:最早的编码,只有127个字母被编到计算机里(1 byte---8 bits)

Unicode编码:将所有语言统一到一套编码里,用两个字节(2 bytes---16 bits)表示一个字符,部分生僻字4字节.

UTF-8编码:可变长编码(英文字母1字节,汉字3字节),节约存储空间.

**在计算机内存中,使用Unicode编码(稳定).保存到硬盘或者需要传输时,会转换为UTF-8编码(节约存储空间).**

e.g.1:记事本编辑时,从文件读取UTF-8字符被转换为Unicode字符到内存里,编辑完成后,保存时再把Unicode转换为UTF-8保存到文件.

e.g.2:浏览网页时,服务器把动态生成的Unicode内容转换为UTF-8再传输到浏览器.

### 2.3 Python的字符串

字母转换数字函数:ord()和数字转换字母函数:chr()

	>>>ord('A')
	65			#将"A"转换为数字65
	>>>chr(65)
	'A'			#将65转换为字母A

Unicode输出中文:
	
	print u'中文'	#将会输出"中文"

Unicode编码转换为UTF-8编码:

	u'ABC'.encode('utf-8')	#Unicode编码的"ABC"转换为UTF-8编码的"ABC"

UTF-8编码转换为Unicode编码

	'abc'.decode('utf-8')	#将UTF-8编码的"abc"转换为Unicode编码的u'abc'.	#'abc':表示UTF-8编码

字符串长度求取:

	len(u'ABC')		#求Unicode编码的"ABC"字符串的长度(结果为3)
	len('ABC')		#求UTF-8编码的"ABC"字符串的长度(结果为3)

**让Python解释器读取源代码时按照UTF-8编码读取(常用做法,可以兼容代码中的中文)**

	#!/usr/bin/python			#Python可执行程序
	#-*- coding: utf-8 -*-		#指示按照utf-8编码读取源代码

**格式化**

	print 'Hi, %s, you have $%d.' % ('Michael', 1000)	#显示:Hi, Michael, you have $1000.
	print '%2d-%02d' % (3,1)			#显示为" 3-01"(3占2位,不足的捕空;1占2位,不足的捕0)
	print '%.2f' % 3.1415926		#显示为"3.14"(小数点后2位)

	输出形式:print '字符串 %s %d' %('字符串', 整型)

**字符串的format函数**

format函数用于格式化字符串.

	test1 = '{0}, {1}'.format('aaa', 'bbb') //此时test1为"aaa, bbb"
	test2 = '{0} {1}'.format('aaa', 'bbb') //此时test2为"aaa bbb"
	test3 = '{} {}'.format('aaa', 'bbb') //此时test3为"aaa bbb"(会自动按着先后顺序排列)
	test4 = '{1} {0}'.format('aaa', 'bbb') //此时test4为"bbb aaa"
	test5 = '{height}x{width}'.format(height=1920, width=1080)
		//此时test5为"1920x1080"

**字符串的replace函数**

replace函数用于替换对应的字符串.

	string1 = 'abc'
	string2 = string1.replace('a', 'A')	/*将'a'代替为'A',不会改变原来的字符串"abc".因此string1
		指向不变.replace之后相当于新创建了一个字符串"Abc"并赋值给string2.*/

### 2.4 Python中2进制、8进制、10进制、16进制相关转换

	//只有转成10进制才能接收两个参数;转成其他进制的只能接收一个参数
	/************转成10进制**************/
	1.2进制转10进制
	int('1001', 2)	//int:表示需要转成的十进制; '1001':需要转换的源数据; 2:源数据的进制
	结果为:9
	2.16进制转10进制
	int('ff', 16)
	结果为:255
	int('0xab', 16)
	结果为:171
	/************转成其他进制**************/	
	3.10进制转2进制
	bin(10)		//源数据为十进制不需要指定源数据的进制
	结果为'0b1010'	//0b表示二进制
	4.10进制转8进制
	oct(8)
	结果为'010'	//0打头表示8进制
	5.10进制转16进制
	hex(10)
	结果为:'0xa'
	//非10进制转其他进制
	6.16进制转2进制
	bin(0xa)
	结果为'0b1010'
	7.8进制转16进制
	hex(0110)
	结果为'0x48'

### 2.5 Python中字符及字符串相加"+"

	/*单个字符构成一个字符串的方法---"+"*/
	k = 'a' + 'b' + 'c'
	print 'k value: %s' % k		//得到字符串abc

	k = '12345678'	//k表示一个字符串
	v = int(k[6:8] + k[4:6] + k[2:4] + k[0:2], 16)
	//k[6:8]:表示取k字符串的第6、第7两个字符,即78; "+"表示将所取的字符串连接起来变成一个长字符串
	//int('xxx', 16)---表示将16进制数转成10进制
	print 'v value: 0x%x' % v	//将v以16进制输出

### 2.6 Python中的del的使用

python中变量都是引用,del语句作用在变量/对象上,是删除变量对某数据的引用

	1.对普通变量/对象使用del
		a = 1 //对象1被变量a引用.对象1的引用计数器为1
		b = a //对象1被变量b引用.对象1的引用计数器加1
		c = a //对象1被变量c引用.对象1的引用计数器加1
		del a //删除变量a,解除a对1的引用
		del b //删除变量b,解除b对1的引用
		print c //最终变量c仍然引用1
	2.对list元素使用del
		li = [1, 2, 3, 4, 5] //列表本身不包含数据1, 2, 3, 4, 5;而是包含变量: li[0], li[1],...,li[4]
		first = li[0] //first变量引用li[0]变量指定的数据,即1
		del li[0] //删除变量li[0],解除li[0]对1的引用
		print(li) //li[0]变量被删除.因此结果为[2, 3, 4, 5]
		print(first) //输出1

***

## 3、其他一些常用的学习

### 3.1 list和tuple

**list**

list:列表---Python内置的一种数据类型,属于一种有序的集合,可以随时添加/删除其中元素.

	classmates = ['Michael', 'Bob', 'Tracy']	#list变量并初始化
	print (classmates)			#打印输出list变量
	len(classmates)				#获取list元素个数
	classmates[0/1/2]			#list索引	#超出范围会报IndexError的错误
	classmates.append('Adam')	#往末尾添加"Adam"
	classmates.insert(1, 'Jack')#在1的位置插入"Jack"元素
	classmates.pop()			#删除末尾元素
	classmates.pop(1)			#删除索引为1的元素
	classmates[1] = 'Sarah'		#给索引1的位置重新赋值
	L = []
	len(L)			#空list,长度为0
	
**tuple**

tuple与list非常类似,但tuple一旦初始化就不能修改.使用"(...)"识别.

	classmates = ('Michael', 'Bob', 'Tracy')	#tuple变量,不能再修改(因此没有append、insert方法)
	classmates[0/1/2]	#可以获取tuple元素
	t = ()	#空tuple
	t = (1,)	#定义只有一个元素的tuple,必须在1后面加","(e.g. t = (1)默认会认为是t = 1---按小括号计算)
	/*特例*/
	t = ('a', 'b', ['A', 'B'])	#第三个元素为list，因此可以对第三个元素进行重新赋值
	t[2][0] = 'X'	#tuple指向不变,仍然为list.但是list自身中的元素可以改变
	t[2][1] = 'Y'

**切片**

切片:取list或tuple的部分元素.

	L = ['Michael', 'Sarah', 'Tracy', 'Bob', 'Jack']
	//取前3个元素,常规方法
	[L[0], L[1], L[2]]
	//切片方法
	L[0:3]	/*取到3截止,不包括3位置的元素*/
	L[:3]	/*从索引0开始,到3截止.包括L[0],L[1],L[2]三个元素*/
	L[-2:]	/*取倒数元素,L[-2], L[-1]---倒数第一个元素*/
	L[-2:-1]	/*取L[-2],到-1截止(不包括-1索引指向的元素).因此就取一个*/

实例
	
	L=range(100)	/*L=[0, 1, 2,...,99]---0~99的数列*/
	L[:10]		/*取list L中的前10个数(0~9)*/
	L[-10:]		/*取后10个数(90-99)*/
	L[10:20]	/*前10~20之间的数(10~19)*/
	L[:10:2]	/*前10个数中,每两个取一个(0,2,4,6,8)*/
	L[::5]		/*所有数,每5个取一个(0,5,10,...)*/
	L[::]		/*取整个list*/

tuple和字符串也可以使用切片

	// tuple
	(0, 1, 2, 3, 4, 5)[:3]	/*取tuple的前3个(0, 1, 2)---结果仍为tuple*/
	//字符串,一个字符一个元素
	'ABCDEFG'[:3]	/*取前3个字符'ABC'---结果仍为字符串*/
	'ABCDEFG'[::2]	/*每两个取一个'ACEG'*/
	
### 3.2 条件判断和循环

**条件判断**

	age = 20
	if age >= 18:
		print 'adult'
	elif age >= 6:
		print 'teenage'
	else:
		print 'kid'

非零、非空字符串、非空list均为True

**循环**

1)for...in循环

	names = ['Michael', 'Bob', 'Tracy']
	for name in names:
		print name		#依次打印names中的每一个元素

	range(101)	#生成0-100的整型序列
	range(1, 11) //从1开始到11(不包括11).即为: 1,2,3,4,5,6,7,8,9,10
	range(0, 30, 5) //从0开始到30(不包括),步长为5.即为:0,5,15,20,25.

2)while循环

	sum = 0
	n = 99
	while n > 0:	#只要while后的条件满足,就会一直循环.不满足就退出
		sum = sum + n
		n = n - 2
	print sum

### 3.3 dict和set

**dict**

dict:字典,键-值(key-value)存储,具有极快的查找速度.使用"{}"标识.

	d = {'Michael':95, 'Bob':75, 'Tracy':85}	/*初始化指定"key-value"*/
	d['Michael']		//会得到:95
	d['Adam'] = 67		/*在字典中加入key为Adam,value为67的元素.*/
	d['Adam'] = 88		/*多次对一个key放入新的value,后面的会冲掉前面的值*/
	d['Adam']			//会得到88,而非67
	d['Thomas']			//key不存在,dict报错.显示为"KeyError: 'Thomas'"

判断dict中key存在的两种方法

	// Method 1
	'Thomas' in d	/*直接通过"in"判断,不存在返回"False"*/
	// Method 2
	d.get('Thomas')	/*通过dict的"get"方法,不存在返回"None".此时在交互式命令行不会显示结果*/
	d.get('Thomas', -1)	/*不存在返回指定值"-1"*/
	d.pop('Bob')	/*删除"key-value"*/

dict相比于list查找和插入的速度快,但是浪费内存(同时存储"key-value"),是一种以空间换取时间的方法.

在dict中,作为key的对象不能变(不能是list, tuple等).可以是字符串('xxx')、整数.

**set**

set只存储key,不存储value.使用"set([])"标识.

	s = set([1, 2, 3])	/*相比较tuple,增加了"set"标识符,括号中间为一个"list"*/
	s = set([1, 1, 2, 2, 3, 3])	/*自动去掉重复元素,因此最后显示结果为"set([1, 2, 3])"*/
	s.add(4)	/*添加一个元素使用add方法,重复的会去掉*/
	s.remove(4)	/*删除元素*/

	s1 = set([1, 2, 3])
	s2 = set([2, 3, 4])
	s1 & s2		/*数学意义上的交集,显示为"set([2, 3])"*/
	s1 | s2		/*数学意义上的并集,显示为"set([1, 2, 3, 4])"*/

**可变对象和不可变对象**

	a = ['c', 'b', 'a']
	a.sort()	/*排序,最终会显示为"['a', 'b', 'c'],因此list是可变对象"*/
	string1 = 'abc'
	string2 = string1.replace('a', 'A')	/*将'a'代替为'A',不会改变原来的字符串"abc".因此string1
		指向不变.replace之后相当于新创建了一个字符串"Abc"并赋值给string2.因此属于不可变对象.*/

**list中含有多个dict取值的方法:**

	open = [
		{'method': 'DEV_OPEN', 'dev': dev, 'idx': idx, 'mode': os.O_RDWR},
		{'method': 'DEV_SET_FORMAT', 'idx': idx, 'format': 'TS%d'%format...}
	]
	//取open中的第2个并进行赋值
	open[1]['format'] = 'RAW'	//对format进行重新赋值

### 3.4 迭代

list/tuple/dict/str(字符串)等可迭代对象都可以用"for...in"来实现遍历,称这种遍历为迭代(Iteration).

	//list
	names = ['Michael', 'Tracy', 'Bob']
	for name in names:
		print 'name: %s' % name
	//tuple
	words = ('a', 'b', 'c')
	for word in words:
		print 'word: %s' % word	/*如果不行:print 'word:', word*/
	//dict
	d = {'a':1, 'b':2, 'c':3}
	for key in d:	/*遍历dict中的key*/
		print key	/*打印key*/
		print d[key]	/*打印value*/
	/*默认迭代key*/
	for value in d.itervalues():	/*迭代value*/
	for k, v in d.iteritems():		/*迭代key和value*/
	//字符串
	for ch in 'ABC':
		print ch

判断是否为可迭代对象
	
	from collections import Iterable	/*从collections模块引入Iterable*/
	/*
		python 3.x之后使用"from collections import Iterable"会报"DeprecationWarning: Using or
		importing the ABCs from 'collections' instead of from 'collections.abc' is deprecated, 
		and in 3.8 it will stop working.
		解决方法:
		from collections.abc import Iterable
	*/
	isinstance('abc', Iterable)	/*判断字符串是否为可迭代对象.返回"True"*/
	isinstance([1, 2, 3], Iterable)	/*list可迭代,返回"True"*/
	isinstance(123, Iterable)	/*整数不可迭代,返回"False"*/

引入两个变量

	for x, y in [(1, 1), (2, 4), (3, 9)]:
		print x, y
	/* 会打印出:
		1 1
		2 4
		3 9
	*/

### 3.5 列表生成式

用于创建列表

	//传统方法
	L = []
	for x in range(1, 11):
		L.append(x * x)	/*生成[1, 4, 9, ..., 100]*/
	//使用列表生成式
	[x * x for x in range(1, 11)]	/*也是生成[1, 4, 9,...,100]*/
	[x * x for x in range(1, 11) if x % 2 == 0]	/*仅偶数平方*/
	//两层循环
	[m + n for m in 'ABC' for n in 'XYZ']
	/*两个str组合的全排列,结果为:
		"AX, AY, AZ, BX, BY, BZ, CX, CY, CZ"
	*/

列出当前目录下所有文件和目录名

	import os	/*导入os模块*/
	[d for d in os.listdir('.')]	/*os.listdir:列出文件和目录,('.')---表示当前目录*/

把list所有字符串中的字符变成小写

	L = ['Hello', 'World', 'IBM', 'Apple']
	[s.lower() for s in L]
	/*
		s.lower():将str字符串的字符变成小写
		s.upper():将str字符串的字符变成大写
	*/
	//list中包含字符串和整数
	L = ['Hello', 'World', 18, 'IBM', 'Apple']
	[s.lower() for s in L if isinstance(s, str)]	/*增加判断是否为字符串*/
	isinstance(s, str)	//判断s是否为字符串.True:表示为字符串;False:不是字符串.
	
***

## 4、函数

### 4.1 内置函数

**1.显示内置的所有函数**

	print (dir(__builtins__))

**2.获得内置函数的帮助信息**

	help(abs)	/*查看求绝对值函数的帮助信息*/
	help(sum)	//获取求和函数的帮助信息

**3.常用函数**

1.abs()绝对值函数

	abs(100)	/*结果为100*/
	abs(-20)		/*结果为20*/
	abs(12.34)	/*结果为12.34*/
	//错误时信息提示
	abs(1, 2)	
	/*TypeError: abs() takes exactly one argument (2 given).abs()接受一个参数,但是给出了两个*/
	abs('a')
	/*TypeError: bad operand type for abs(). 'str'.str是错误的运算(即参数)类型*/

2.sum()求和函数

	print (sum([1,2,3], 10))
	/*
	para1为一个iterable(e.g.list/tuple等);
	para2为一个start值(没有写的话默认为0).
	result为iterable中的值求和+start的值.
	此处的结果为:16
	PS:如果iterable为空,返回的为start的值(e.g.sum([], 10)--->结果为10)
	*/

3.cmp(x, y)比较函数(python 2.x)/operator模块(python 3.x)

	1.python 2.x使用cmp函数比较
		cmp(1, 2)	/*para1 < para2, 返回"-1"*/
		cmp(2, 1)	/*para1 > para2, 返回"1"*/
		cmp(3, 3)	/*para1 = para2, 返回"0"*/
	2.python 3.x使用operator模块比较
		import operator
		print (operator.eq(1, 1))	//等于,返回True
		print (operator.gt(2, 1))	//大于,返回True
		print (operator.lt(1, 2))	//小于,返回True

**4.数据类型转换**

	int('123')		/*字符串转整型,ret为123*/
	int(12.34)		/*浮点转整型,ret为12*/
	float('12.34')	/*字符串转浮点,ret为12.34*/
	str(1.23)		/*浮点转字符串,ret为'1.23'*/
	unicode(100)	/*整型转unicode,ret为u'100'---unicode编码的100*/
	bool(1)			/*非零(或非空)为True*/
	bool('')		/*空字符为False*/
	bool([])		//空list为False

**函数别名**

	a = abs		/*变量a指向函数abs*/
	a(-1)		/*abs别名,相当于abs(-1)*/

### 4.2 定义函数

	def	my_abs(x):		/*定义函数*/
		if x >= 0:
			return x	
			/*return:返回.如果没有return,函数执行完毕后返回"None".---一般应该使用"return xxx"*/
		else:
			return -x

**1.空函数**

	def nop():
		pass	/*pass作为占位符,定义空函数.空函数必须有"pass",常用在定义一个函数的框架.*/

**2.参数检查**

自定义函数一般需要做参数检查处理.

	def my_abs(x):
		if not isinstance(x, (int, float)):		/*只允许整数和浮点数*/
			raise TypeError('bad operand type')	/*抛出错误*/
		if x >= 0:
			return x
		else:
			return -x

**3.斐波拉切数列的函数实现**

	def fib(max):
		n, a, b = 0, 1, 1	/*赋值,会对应的赋值*/
		while n < max:	/*while循环*/
			print a
			a, b = b, a + b	/*赋值,会对应的赋值*/
			n = n + 1
		return a

**4.返回多个值**

其实为一个tuple,按位置赋给对应的变量.

	import math	/*引入math module*/
	
	def move(x, y, step, angle=0):	/*angle带默认参数,放在最后*/
		nx = x + step * math.cos(angle)		/*math module的cos函数"math.cos(angle)"*/
		ny = y - step * math.sin(angle)
		return nx, ny	/*返回nx, ny两个值.会组成一个tuple"(nx, ny)"*/

	// 调用(返回值赋给两个变量)
	x, y = move(100, 100, 60, math.pi / 6)
	print x, y	/*打印"151.961524227 70.0"*/
	// 调用(返回值赋给一个变量)
	r = move(100, 100, 60, math.pi / 6)
	print r		/*打印"(151.961524227 70.0)"一个tuple,因此返回值其实为一个tuple*/

### 4.3 函数的参数

**默认参数**

	def power(x, n=2):	/*默认参数n = 2,默认参数必须置于最后*/
		s = 1
		while n > 0:
			n = n - 1
			s = s * x
		return s
	//调用
	power(5)	/*会使用默认参数计算5的平方*/
	power(5, 2)	/*明确给出计算5的平方*/

	//多个默认参数:学生注册
	def enroll(name, gender, age=6, city='Beijing'):	/*两个默认参数*/
		print 'name: %s' % name
		print 'gender: %s' % gender
		print 'age: %d' % age
		print 'city: %s' % city
	//调用
	enroll('Sarah', 'F')
	enroll('Bob', 'M', 7)	/*依次赋值, 7是赋给age的值*/
	enroll('Adam', 'M', city='Tianjin')	/*age使用默认值,city改变需要明确参数名*/

默认参数使用"list"会出现问题,因此尽量使用不可变对象(None, int，str)

	def add_end(L=[])	/*参数L带有默认值"[]",空的list*/
		L.append('END')
		return L	
	//正常调用不会有问题,因为不使用默认参数
	add_end([1, 2, 3])	/*显示为[1, 2, 3, 'END']*/

	//使用默认参数调用有问题
	add_end()	/*显示为['END']*/
	add_end()	/*再调用依次显示为['END', 'END'].会不断往后面添加'END'*/
	/*原因:默认参数为list是可变对象,每次使用了默认参数后会改变默认参数的值.*/
	//默认参数必须为不可变对象
	def add_end(L=None):	/*None(空)为不可变对象*/
		if L is None:	/*如果使用默认参数,初始化为"[]"*/
			L = []
		L.append('END')
		return L	/*此时不会出错*/

**可变参数**

在Python函数中,传给函数的参数的个数可变称为可变参数的函数.

	//list/tuple作为参数的函数定义,非可变参数
	def calc(numbers):	/*参数为list/tuple,非可变参数*/
		sum = 0
		for n in numbers:
			sum = sum + n * n
		return sum
	//调用,参数必须为list/tuple
	calc([1, 2, 3])		/*使用list,结果为:14*/
	calc((1, 3, 5, 7))	/*使用tuple,结果为:84*/

	//可变参数函数定义
	def calc(*numbers):	/*"*numbers":表示定义了一个可变参数的函数*/
		sum = 0
		for n in numbers:
			sum = sum + n * n
		return sum
	//调用
	calc(1, 2)	/*不能是list/tuple,结果为:5*/
	calc()		/*传入0个参数,结果为:0*/
	//如果参数为list/tuple,可以使用下面方法.方法1:
	nums = [1, 2, 3]
	calc(nums[1], nums[2], nums[3])
	//方法2:
	nums = [1, 2, 3]
	calc(*nums)	/*将list/tuple变成可变参数传入"*nums"*/

**关键字参数(dict)**

	def person(name, age, **kw):	/*关键字参数函数定义"**kw"*/
		print 'name: %s' % name
		print 'age: %d' %age
		print 'other:', kw	/*输出other时不知道类型,使用这种方式比较好*/

	//调用
	person('Michael', 30)	/*关键字参数没传,为空的dict.*/
		/*显示为:name: Micheal age: 30 other: {}/

	person('Bob', 35, city='Beijing')	/*显示为:前面+other: {'city':'Beijing'}---为dict*/
	person('Adam', 45, gender='M', job='Engineer')
		/*显示为:前面+other: {'gender':'M', 'job':'Engineer'}*/
	//dict传入的两种方法.方法1:
	kw={'city':'Beijing', 'job':'Engineer'}
	person('Jack', 24, city=kw['city'], job=kw['job'])
	//方法2:
	person('Jack', 24, **kw)	/*简化写法*/

**参数组合**

	def func(a, b, c=0, *args, **kw):
		/*顺序:必选参数(a,b)、默认参数(c)、可变参数(*args),关键字参数(**kw)*/
	
	//调用
	func(1, 2)	/*a=1,b=2,c=0,args=()空tuple,kw={}空dict*/
	func(1, 2, 3)	/*c=3,其他一样*/
	func(1, 2, 3, 'a', 'b')	/*args=('a', 'b'),其他一样*/
	func(1, 2, 3, 'a', 'b', x=99)
		/*args=('a', 'b'); kw={'x':99}*/

	//比较常用的
	args=(1, 2, 3, 4)
	kw={'x':99}
	func(*args, **kw)	/*a=1,b=2,c=3,args=(4,),kw={'x':99}*/
	/*常用*args:表示可变参数; **kw:表示关键字参数.*/

### 4.4 递归函数

递归函数:在函数内部调用自身本身.

	def fact(n):	/*fact:表示阶乘*/
		if n == 1:
			return 1
		return n * fact(n - 1)	/*函数中调用自身本身*/
	//调用
	fact(1)		/*retval:1*/
	fact(5)		/*retval:120*/

**递归调用定义简单,逻辑清晰,类似循环.**

	//存在的问题
	栈溢出:递归调用内部每调用一次,都需要做入栈操作(函数的参数需要),栈会加一层栈帧.出栈会减一层栈帧.
	一旦递归层数过多,就会出现栈溢出.

**尾递归函数:函数返回时调用自身本身,而且,return语句中不能包含表达式(只有自身函数本身).**

	def fact_iter(num, product):	/*尾递归函数*/
		if num == 1:
			return product	/*返回最终的积*/
		return fact_iter(num - 1, num * product)		
		/*返回递归函数本身,num-1和num*product在调用前被计算,且return中不含表达式*/

	def fact(n):
		return fact_iter(n, 1)	/*为尾递归函数*/

**尾递归函数在带有对尾递归做优化的程序语言中可以防止栈溢出.但是目前大多数语言不支持(包括python).**

***

## 5、函数应用

**高阶函数**

高阶函数:让函数的参数能够接受别的函数.

	def add(x, y, f):	/*函数参数f可以接受"abs"函数*/
		return f(x) + f(y)
	//调用
	add(-5, 6, abs)	/*展开为:abs(-5) + abs(6) = 11*/
	abs函数名也是变量,指向计算绝对值的函数

### 5.1 map/reduce函数

map()函数接收两个参数.一个函数,一个list.map会将函数依次作用于list中的每一个元素,将结果作为新的list返回.

	def f(x):
		return x * x
	map(f, [1, 2, 3, 4, 5, 6, 7, 8, 9])	/*将f函数作用于list中的每一个元素*/
	//返回值为:[1, 4, 9, 16, 25, 36, 49, 64, 81]

实例

	//将list中的所有数字转化为字符串
	map(str, [1, 3, 5, 7, 9])	//结果为:['1', '3', '5', '7', '9']
	/*
		map()默认返回map对象:<map object at 0x005B9FB0>
		如果需要打印的话,需要转成list对象:
			print (list(map(str, [1, 3, 5, 7, 9])))
	*/

reduce()函数接收两个参数.一个函数,一个list.函数从list中取两个参数计算,得到返回值和list中的第三个参数作为函数的参数继续参与计算.直到最后得到返回值.

	from functools import reduce	//python 3.x后,reduce不再在built-in function里.需要import
	reduce(f, [x1, x2, x3, x4]) = f(f(f(x1, x2), x3), x4)

	//求和
	def add(x, y):
		return x + y
	reduce(add, [1, 3, 5, 7, 9])	//最终值为:25.也可以用python内置的sum()函数

	//把序列1, 3, 5, 7, 9变成整数13579
	def fn(x, y):
		return x * 10 + y
	reduce(fn, [1, 3, 5, 7, 9])

**str(字符串)转换为int---str也为list**

	def fn(x, y):
		return x * 10 + y
	
	def char2num(s):
		return {'0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9}[s]

	reduce(fn, map(char2num, '13579'))	//结果为:13579

	//使用lambda函数简化
	def char2num(s):
		return {'0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9}[s]

	def str2int(s):
		return reduce(lambda x, y: x * 10 + y, map(char2num, s)) //---lambda para : expression

### 5.2 filter函数

filter()接收一个函数和一个list.filter会将函数依次作用于list中的每一个元素,根据返回值为True还是False决定保留还是丢弃该元素.

	//删掉偶数,保留奇数
	def is_odd(n):
		return n % 2 == 1

	filter(is_odd, [1, 2, 4, 5, 6, 9, 10, 15])	//结果为:[1, 5, 9, 15]

	//删掉空字符串
	def not_empty(s):
		return s and s.strip()	
		/*strip:用于移除字符串头尾指定的字符(默认为空格:e.g.' ').此处空字符串会返回False*/
	filter(not_empty, ['A', '', 'B', None, 'C', ' '])

	//尝试下:s = '' print s;以及s = ' ' print s
	
### 5.3 sorted函数

sorted函数为排序函数,从小到大.排序规则是"x>y返回1;x<y返回-1;x==y返回0".也可以接受函数和list,list在前,函数在后.

	//从小到大排序(默认)
	sorted([36, 5, 12, 9, 21])	//排序完:[5, 9, 12, 21, 36]
	//实现倒序排序
	1.python 2.x实现
	def reversed_cmp(x, y):
		if x > y:
			return -1
		if x < y:
			return 1
		return 0
	sorted([36, 5, 12, 9, 21], reversed_cmp)	//结果为:[36, 21, 12, 9, 5]
	//list在前,函数在后.与前面的不一样
	2.python 3.x实现(python 3.x取消了cmp函数,sorted函数调用更简单了):
		print (sorted([36, 5, 12, 9, 21],reverse=True))
		/*
			指定reverse参数为True表示倒序,默认是升序(False).
			结果为:[36, 21, 12, 9, 5]
		*/


字符串排序

	sorted(['bob', 'about', 'Zoo', 'Credit'])	//结果为:['Credit', 'Zoo', 'about', 'bob']
		//默认按着ASCII的大小比较,有大小写之分
	//忽略大小写
	1.python 2.x实现:
	def cmp_ignore_case(s1, s2):
		u1 = s1.upper()	//将字母转变为大写,upper()和lower作用于整个字符串
		u2 = s2.upper()	//将字母转变为大写,upper()和lower作用于整个字符串
		if u1 > u2:
			return 1
		if u1 < u2:
			return -1
		return 0

	sorted(['bob', 'about', 'Zoo', 'Credit'], cmp_ignore_case)
	//结果为:['about', 'bob', 'Credit', 'Zoo']
	2.python 3.x实现:
	print (sorted(['bob', 'about', 'Zoo', 'Credit'], key = lambda x : x.upper()))
	/*
		sorted函数:
			para1为一个list;
			para2为接收一个参数的函数(匿名函数也行),需要用key来指定;
			para3为指定升序/降序,用reverse=False/True来指定(默认升序)
	*/

**字符串转换大小写函数**
	
	s = 'hEllo pYthon'
	print s.upper()			//转变为大写,结果为:HELLO PYTHON
	print s.lower()			//转变为小写,结果为:hello python
	print s.capitalize()	//首字母大写,其余小写,结果为:Hello python
	print s.title()			//所有单词首字母大写,其余小写,结果为:Hello Python

### 5.4 函数作为返回值

	//可变参数的求和
	def calc_sum(*args):	/*"*args"表示可变参数*/
		ax = 0
		for n in args:
			ax = ax + n
		return ax	//返回求和结果

	//不返回求和结果,返回求和函数---即函数作为返回值
	def lazy_sum(*args):
		def sum():
			ax = 0
			for n in args:
				ax = ax + n
			return ax
		return sum	//返回函数名,相关的变量和参数保存在该返回函数中.称为"闭包(closure)"

	//调用
	f = lazy_sum(1, 3, 5, 7, 9)	/*可变参数的调用方式*/
		//此时f相当于函数名"sum".因此如果需要得到结果,必须显示调用下:f()
	f()	//显示调用下函数名

### 5.5 匿名函数---lambda的使用

	map(lambda x : x * x, [1, 2, 3, 4, 5, 6, 7, 8, 9])
	//lambda x : x * x---匿名函数(lambda para : expression(only one expression))

	f = lambda x : x * x	//将匿名函数赋值给一个变量
	f(5)	//通过该变量来调用匿名函数,结果为25

	//匿名函数作为返回值返回
	def build(x, y):
		return lambda: x * x + y * y	
		//此处省略了para,正常的为"return lambda x, y: x * x + y * y"

python对匿名函数的支持有限

***

## 6. 模块

在Python中,一个".py"文件就是一个模块(module).

模块放置在某个文件夹下,该文件夹称为包(package).只要文件夹名字不同,文件夹下的模块名字以及模块中的变量名可以与其他的模块相同.

	abc.py---一个名字叫"abc"的模块
	->mycompany		//顶层目录
		->web	//
			->__init__.py	
		//将"mycompany.web"变成一个包,"__init__.py"可以为空.模块名为"mycompany.web".该文件必须存在
			->utils.py	//模块名为"mycompany.web.utils".
			->www.py		//模块名为"mycompany.web.www"
		->__init__.py//文件夹(包目录)下面的__init__.py将"mycompany"当成一个"包".模块名为"mycompany"
		->abc.py		//模块名为"mycompany.abc"
		->utils.py	//模块名为"mycompany.utils",可以与"mycompany.web.utils"名字,但是模块名不同
		->xyz.py		//模块名为"mycompany.xyz"

### 6.1 导入模块

	#!/usr/bin/python	//指定可执行程序路径
	# -*- coding: utf-8	-*-		//使用utf-8编码

	'a test module'		//注释
	__author__ = 'Defy Chen'	//作者

	import sys	//导入"sys"模块,使用sys变量指向sys模块.sys模块的变量argv为存储所有命令行参数的list.
				//至少有一个元素,执行时".py"文件的名称
	
	def test():
		args = sys.argv		//运行./hello.py时sys.argv就是['hello.py']
		if len(args) == 1:
			print 'Hello, world'
		elif len(args) == 2:	//运行./hello.py Defy时sys.argv就是['hello.py', 'Defy']
			print 'Hello, %s!' % args[1]
		else:
			print 'Too many arguments!'

	if __name__ == '__main__':	//直接运行./hello.py,python中的特殊变量"__name__"就会置为"__main__"
								//而在其他地方导入时,就会判断失败.用于测试该模块的正确性.
		test()

	//执行
	./hello.py defy		//打印出:Hello, defy!
	//在交互环境下,导入hello模块
	$ python
	>>> import hello
	>>>     //没有任何打印,没有调用test()函数
	>>> hello.test()      //调用test函数
	>>> Hello, world      //打印出来了

### 6.2 别名

	1.python 2.x使用:
	try:	//Python IO的两套库"cStringIO"和"StringIO",接口和功能相同.cStringIO用c写的,速度快.
		import cStringIO as StringIO	//优先导入cStringIO作为StringIO,"as"相当于别名
	except ImportError:	//导入失败会捕获到ImportError
		import StringIO	//失败再导入StringIO.后面的代码均可以用StringIO正常工作
	2.python 3.x使用:
	from io import StringIO	//因为python 3.x没有cStringIO,是从io中import进来的.

	//example
	try:
		import json	#python >= 2.6	//注释"#",2.6中有json的库
	except ImportError:
		import simplejson as json #python <= 2.5	//2.6之前独立第三方库

### 6.3 作用域

**1.public/private函数和变量**

	abc, x123, PI	//公开的(public)变量或者函数名,可以直接引用
	__xxx__		//特殊变量(e.g.__author__, __name__等).自己的变量一般不这么定义
	_xxx或__xxx	//非公开的(private)的函数或变量(e.g._abc, __abc).不应该引用private函数或变量

	def _private_1(name):	//定义private的函数,细节被隐藏
		return 'Hello, %s' % name
	def _private_2(name):	//细节被隐藏
		return 'Hi, %s' % name
	
	def greeting(name):	//公开greeting函数.接口公开,细节隐藏.
		if len(name) > 3:
			return _private_1(name)
		else:
			return _private_2(name)

**2.global的用法**

在Python中,函数中定义的变量为本地作用域;而模块中的定义的变量为全局作用域.

函数中定义变量加上"global"可以变为全局作用域;或者使用函数中使用全局变量应该加上"global"修饰符

	1.全局变量且函数内无同名变量
		hehe = 6
		def f():
			print(hehe) //打印出全局变量
		f()
		print(hehe)
		//运行正常输出6和6
	2.全局变量但函数内有同名变量(且先使用后定义)-->会报错
		hehe = 6
		def f():
			print(hehe) //在函数内因为后面定义局部变量.此时会出现引用错误.
			hehe = 2 //Python定义和赋值在一起,此时相当于定义一个局部变量
		f()
		print(hehe)
		//会抛出错误:UnboundLocalError: local variable 'hehe' referenced before assignment
	3.全局变量但函数内有同名变量(且先定义后使用)
		hehe = 6
		def f():
			hehe = 2 //定义了一个局部变量
			print(hehe) //输出局部变量2
		f()
		print(hehe) //输出全局变量
		//运行正常输出2和6
	4.全局变量和函数中使用global修饰
		hehe = 6
		def f():
			global hehe //明确说明在该函数中使用模块内定义的全局变量,该函数所有操作该变量都是用全局变量
			print(hehe) //输出6
			hehe = 3 //全局变量重新赋值为3,此时全局变量值被改变为3.
		f()
		print(hehe) //输出3
		//运行正常输出6和3

**3.模块搜索路径**

	//搜索路径在sys模块的path变量中
	>>>import sys
	>>>sys.path    //为一个list
	//添加自己的搜索目录, method 1
	>>>import sys
	>>>sys.path.append('pathname')    //运行时修改,结束后失效
	//method 2
	设置环境变量PYTHONPATH---不是很清楚

***

## 7. 面向对象编程

	class Student(object):	//类定义,派生于object(所有类都可以派生于object).类名大写字母开头
		def __init__(self, name, score): 
			//类函数必须有个参数self:表示对象本身.调用时不用传递该参数.其他在__init__中的参数必须传递
			self.name = name	//类变量
			self.score = score
		def print_score(self):	//类方法,self不用传,如果有其他参数,按照正常函数传递即可.
			print '%s: %s' % (self.name, self.score)

	//调用
	bart = Student('Bart Simpson', 59)	//实例一个对象
	lisa = Student('Lisa Simpson', 87)	//不需要传递self参数
	bart.print_score()	//调用对象的函数
	lisa.print_score()	//调用对象的函数
	//也可以临时给实例增加数据成员
	bart.age = 8	//age非class的类变量,临时增加的数据成员.仅属于该实例,其他实例没有.
	bart.score = 89	//外部可以自由修改一个实例的public属性

**访问限制---private**

	class Student(object):
		def __init__(self, name, score):
			self.__name = name	//"__"打头表示私有变量,外部不能再访问了
			self.__score = score	//私有变量,外部不能再访问了
		def print_score(self):
			print '%s: %s' % (self.__name, self.__score)	//class内部可以访问private属性
		def get_name(self):
			return self.__name
		def get_score(self):
			return self.__score
		def set_score(self, score):
			if 0 <= score <= 100:	//private可以方便进行参数检查
				self.__score = score
			else:
				raise ValueError('bad score')	//抛出错误
	
### 7.1 继承和多态

	class Animal(object):	//定义一个父类
		def run(self):
			print 'Animal is running...'

	class Dog(Animal):		//Dog类继承自Animal
		def run(self):
			print 'Dog is running...'	//子类run在调用中会覆盖父类的run方法---多态
	class Cat(Animal):
		def run(self):
			print 'Cat is running...'
	
	def run_twice(animal):	//参数接受Animal对象,可以是父类,也可以是父类派生的子类
		animal.run()
		animal.run()

	run_twice(Animal())	//传入Animal对象,调用Animal的run方法
	run_twice(Dog())	//传入Dog对象(也是Animal对象),按照多态会调用Dog的run方法
	run_twice(Cat())	//传入Cat对象(也是Animal对象),按照多态会调用Cat的run方法

**类型判断:type()**

	type(123)
	type('str')
	type(None)
	type(abs)	//判断函数
	type(a)		//判断类(a = Animal())
	
常用在if判断中:

	1.python 2.x用types.String/ListType等来判断某种类型:
	import types	//导入types模块
	type('abc') == types.StringType	//判断是否为字符型,是返回Ture
	type([]) == types.ListType		//判断是否为list,是返回Ture
	type(str) == types.TypeType		//所有类型都是TypeType
	2.python 3.x直接使用str/int/list来判断某种类型:
	print (type('abc') == str)	//返回True
	print (type(123) == int)	//返回True

	//使用isinstance()更简单
	isinstance(d, Dog)	//判断d是否为Dog类,如果是返回True.否则返回False

**dir()函数**

	dir('ABC')	//获得字符串对象的属性和方法

**@property的使用**

@property主要用于简化get/set等的操作,将函数变成属性操作

	class Student(object):
		@property	//单独的"@property"相当于getter_xxx.将get方法变成属性
		def score(self):	//此处相当于"getter_score(self)"
			return self.__score

		@score.setter	//"@xxx.setter"相当于"setter_xxx",将set方法变成属性
		def score(self, value):	//此处相当于"setter_score(self, value)"
			if not isinstance(value, int):
				raise ValueError('score must be integer!')
			if value < 0 or value > 100:
				raise ValueError('score must between 0 ~ 100!')
			self.__score = value

	//实例化
	s = Student()
	s.score = 60	//实际转化为s.set_score(60)
	s.score			//实际转化为s.get_score(),结果为60
	s.score = 9999	//报错

定义读写/只读属性方法

	class Student(object):
		@property	//相当于getter_birth,只读属性
		def birth(self):
			return self.__birth
		@birth.setter	//相当于setter_birth,写属性
		def birth(self, value)
			self.__birth = value
		@property
		def age(self):	//相当于getter_age,只读属性
			return 2017 - self.__birth

**多重继承,也叫Mixin**

	class Animal(object):
		pass

	class Mammal(Animal):	//哺乳类继承自动物类
		pass
	
	class Runnable(object):	//能跑的类
		def run(self):
			print 'running...'

	class Dog(Mammal, Runnable):	//多重继承(Mammal类和Runnable类)
		pass

### 7.2 定制类

**\__str__:用于打印类实例时显示的好看**

	//正常打印类实例
	class Student(object):
		def __init__(self, name):
			self.name = name
	//打印类实例
	>>>print Student('Michael')   //会得到"<__main__.Student object at 109afb190>",不好看
	
	//定义好"__str__()",返回一个好看的字符即可
	class Student(object):
		def __init__(self, name):
			self.name = name
		/* python 2.x使用的__str__(self):不需要返回 */
		def __str__(self):
			print 'Student object (name: %s)' % self.name
		/* python 3.x使用__str__(self):需要返回即return.因此:
		def __str__(self):
			return 'Student object (name: %s)' % self.name
		 */
		
	//打印类实例
	>>>print Student('Michael')   //会得到"Student object (name: Michael)"

	//直接敲变量还是会不好看
	>>>s = Student('Michael')
	>>>s       //依然会不好看"<__main__.Student object at 109afb190>"
	//解决:在类定义最后加上下面一句即可
	__repr__ = __str__		//为调试服务的

**\__iter__:用于类的"for...in"循环,类似list或tuple**

	//斐波那契数列类实现,可以作用于for循环
	class Fib(object):
		def __init__(self):
			self.a, self.b = 0, 1	//初始化头两个数
		def __iter__(self):
			return self			//定义迭代对象.实例本身为迭代对象,故返回自己
		// python 2.x可以使用next(self):拿到循环的下一个值
		def next(self):			//Python中的for循环会不断调用迭代对象的next()方法拿到循环的下一个值
			self.a, self.b = self.b, self.a + self.b	//计算下一个值
			if self.a > 100000:	//循环退出条件
				raise StopIteration()	//抛出"StopIteration;"---终止循环.
					//以前的记录"StopIteration();---后面有分号".但是测试过有没有都正确.没有";"比较和常规.
			return self.a	//返回下一个值
		/* python 3.x改为使用__next__(self):--->其他都一样. */

	//调用
	>>>for n in Fib():
	...		print n
	...	//会打印出斐波那契数列

### 7.3 元类

**type不仅可以做类型判断,还可以通过其创建类**

	>>>def fn(self, name = 'world'):	#1)先定义函数
	...	print ('Hello, %s' % name)
	...
	>>>Hello = type('Hello', (object, ), dict(hello=fn))   #创建Hello class
	>>>h = Hello
	>>>h.hello()     #打印出"Hello, world"

	//2)通过type创建class的方法(type()函数中各参数说明)
	para 1.class的名称---首字母大写的字符串
	para 2.继承tuple---只有一个父类需要写成:(object, )---后面带逗号
	para 3.方法名称与函数绑定---这里将函数fn绑定到方法hello上

使用class创建类最终也是通过type这种方法创建的.

**metaclass---用于创建类.一般不会用**

创建类实例的流程是:先定义metaclass,然后创建类,最后通过类创建实例.

***

## 8、错误、调试和测试

Python的"pdb"以单步方式执行代码.

### 8.1 try...except...finally错误处理机制

	try:
		print 'try...'		//此句打印
		r = 10 / 0			
		//此处除"0"错误,会直接跳到except,后面语句不执行; 2)如果0改成2,后面的语句会执行,并且会跳过
		//except直接执行finally
		print 'result: ', r
	except ZeroDivisionError, e:	//捕获除0错误. "e":保存错误信息---自动保存的
	/* python 3.x改成:
	except ZeroDivisionError as e:
	*/
		print 'except: ', e
	finally:			//有finally时,finally语句块肯定会执行
		print 'finally...'
	print 'END'		//此处语句也会执行
	
	//因此结果为:
	try...
	except: integer division or modulo by zero
	finally...
	END
	//如果0改成2结果为:
	try...
	result: 5
	finally...
	END

**多个except捕获错误及else使用:**

	try:
		print 'try...'
		r = 10 / int('a')	//强制转换int('a')---此处会抛出"ValueError"的错误
		print 'result: ', r
	except ValueError, e:	//捕获ValueError的错误
	/* python 3.x改成:
	except ValueError as e:
	*/
		print 'ValueError: ', e
	except ZeroDivisionError, e:	//除0错误
	/* python 3.x改成:
	except ZeroDivisionError as e:
	*/
		print 'ZeroDivisionError: ', e
	else:	//其实捕获错误相当于条件判断"if",因此没有错误可以使用"else"
		print 'No error!'
	finally:
		print 'finally...'
	print 'END'

**错误类也具有继承关系:**
	
1)ValueError继承自StandardError

2)StandardError继承自BaseException(所有的错误都继承自"BaseException")

实例---try...except跨越多层调用

	def foo(s):
		return 10 / int(s)
	def bar(s):
		return foo(s) * 2
	def main:
		try:
			bar('0')
		except StandardError, e:	//多层调用,但是可以在合适的层次去捕获错误
		/* python 3.x改成:
		except StandardError as e:
		*/
			print 'Error!'
		finally:
			print 'finally...'

	main()	//调用

### 8.2 调用堆栈

显示一些错误跟踪信息:

	Traceback (most recent call last):
		File "err.py", line 11, in <module>
			main()
		File "err.py", line 9, in main
			bar('0')
		File "err.py", line 6, in bar
			return foo(s) * 2
		File "err.py", line 3, in foo
			return 10 / int(s)			//错误最终定位点
	ZeroDivisionError: integer division or modulo by zero	//错误的最终原因

### 8.3 记录错误

Python内置的logging模块记录错误信息,并且可以让程序继续执行下去

	import logging
	
	def foo(s):
		return 10 / int(s)
	def bar(s):
		return foo(s) * 2
	def main():
		try:
			bar('0')
		except StandardError, e:	//捕获标准错误
		/* python 3.x改成:
		except StandardError as e:
		*/
			logging.exception(e)	//调用logging.exception来记录错误信息,程序会继续执行
	main()
	print 'END'	//出现了错误,但是程序会继续执行.该句按照python程序逻辑从上往下会继续执行

logging还可以将错误记录到日志文件,见后面的logging模块.

### 8.4 抛出错误

	class FooError(StandardError):	//需要自己定义错误类
		pass
	
	def foo(s):
		n = int(s)
		if n == 0:
			raise FooError('invalid value: %s' % s)		//抛出错误"raise"
		return 10 / n

一般使用内置的错误类型即可,不需要自己定义错误.

### 8.5 调试

**方法 1---使用print**

使用print,使用之后需要删掉

**方法 2---使用断言assert**

	def foo(s):
		n = int(s)
		assert n != 0, 'n is zero!'
		//1)assert为真,自动跳过该行语句继续执行; 2)为假,抛出"AssertionError"错误并退出
		return 10 / n
	def main():
		foo('0')
	//结果
	Traceback (most recent call last):
	...
	AssertionError: n is zero!	//由于断言为假(失败),抛出该错误

关掉assert断言:
	
	python -O err.py		//加上大写字母"O"---优化选项,关闭assert(所有的assert语句当作pass语句)

**方法 3---logging**

默认情况下,logging将日志打印到屏幕,日志级别是WARNING.

	级别从高到低:CRITICAL>ERROR>WARNING>INFO>DEBUG>NOTSET.

**通过logging.basicConfig函数对logging输出进行相关配置**

针对logging.info('...')不能打印的情况,调整打印级别

    import logging
    logging.basicConfig(level=logging.DEBUG,
                format='%(asctime)s %(filename)s[line:%(lineno)d] %(levelname)s %(message)s',
                datefmt='%a, %d, %b %Y %H:%M:%S',
                filename='ci_debug.log',
                filemode='w')
	/*filename:表示输出的log放置到"ci_debug.log"文件中*/
	logging.debug('This is debug message')
	logging.info('This is info message')
	loggin.warning('This is warning message')

	则在./ci_debug.log文件中内容为:
	...(一些前缀) DEBUG This is debug message
	...(一些前缀) INFO This is info message
	...(一些前缀) WARNING This is warning message

**方法 4---pdb**

	//启动
	python -m pdb err.py		//要以"-m pdb"参数启动,会定位到下一行需要执行的代码
	l---命令"l":小写字母"L",查看代码
	n---命令"n":单步执行代码
	p s---命令"p 变量名":查看变量
	q---命令"q":结束调试,退出程序
	c---命令"c":继续运行

**方法 5---pdb.set_trace()**

pdb.set_trace():设置一个断点

	import pdb	//导入pdb模块
	
	s = '0'
	n = int(s)
	pdb.set_trace()		//程序运行到此处会自动暂停并进入pdb调试环境,进而可以用pdb命令调试程序
	print 10 / n

该方法不适合代码较多的场合

### 8.6 单元测试

**略**

### 8.7 文档测试

**暂时没看**

***

## 9 IO编程

同步IO:相当于每个步骤依序进行,后面的必须等待前面的完成(等待过程是阻塞的过程).e.g.CPU输出100M数据只需要0.01s,磁盘接收这100M数据需要10s.同步情况下,CPU会阻塞等待这100M数据写完再往下执行.

异步IO:当某个步骤出现阻塞,后面的程序不会一直等待阻塞的程序执行完毕,而是继续往下执行.e.g.CPU不等待,只是通知磁盘"写",后续代码接着执行.

同步/异步区别在于是否等待IO执行的结果.异步性能高,但是编程模型复杂.因此Python中同步用的比较多.

### 9.1 读文件

磁盘读写文件都是由操作系统提供.其过程为请求操作系统打开一个文件,返回一个文件描述符,然后透过这个文件描述符从文件中读取数据或写入数据到文件中.

**读文件**

	f = open('./defy/test.txt', 'r')	//'r':表示读. 如果文件不存在会抛出"IOError"错误
	f.read()	//一次性把内容全部读到内存,使用字符串"str"对象表示
	f.close()	//关闭文件.出错会抛出"IOError"
	
保证无论出错与否都能关闭文件:

	// method 1
	try:
		f = open('./defy/test.txt', 'r')
		print f.read()	//因为f.read()返回"str"字符串
	finally:	//无论如何finally中的代码都会执行
		if f:	//判断f是否存在,存在返回真
			f.close()
	// method 2
	with open('./defy/test.txt', 'r') as f:
		print f.read()	//这种方法不用调用f.close(),系统自动调用.代码简洁

**read()的变种**

	f.read(size)	//每次读取size个字节的内容
	f.readline()	//每次读取一行内容
	f.readlines()	//一次读取所有内容,并按行返回list---所有行都放入一个list中,可以遍历该list

实例---readlines()

	for line in f.readlines():	//按行遍历读入的内容的list
		print(line.strip())		//将末尾的'\n'去掉

其他模式读文件:

	f = open('./defy/test.jpg', 'rb')	//"rb"模式读二进制文件(e.g.图片、视频等)
	/*非ASCII编码的文本文件以二进制打开后需要转换编码:*/
	f = open('./defy/gbk.txt', 'rb')	//gbk编码的文件
	f.read().decode('gbk')				//读的时候进行gbk解码
	//或者自动解码
	import codecs		//编码自动转换模块
	with codecs.open('./defy/gbk.txt', 'rb', 'gbk') as f:	//gbk编码转换
		f.read()
	
### 9.2 写文件

	f = open('./defy/test.txt', 'w')	//w:写文本文件; 'wb':写二进制文件
	f.write('Hello, world!')		//写入字符串.不会立即写入磁盘,先放在内存缓存起来,空闲时再写入
	f.close()		//关闭文件.此时会把处在缓存中的数据全部写入磁盘

**最保险的方法**

	with open('./defy/test.txt', 'w') as f:
		f.write('Hello, world!')	//这种方法不用调用f.close(),系统自动调用.代码简洁

### 9.3 StringIO和BytesIO

读写数据时,有时不必要在文件中操作.可以直接在内存中进行读写.StringIO就可以在内存中读写str.

**实例1**

	from io import StringIO //导入StringIO
	1.创建一个StringIO
	f = StringIO()
	2.向StringIO中写入数据
	f.write('hello') //往StringIO中写入hello.retval:返回写入的字节数(此次返回5)
	f.write(' ') //此次返回1
	f.write('world!') //此次返回6
	3.获取写入的数据
	print(f.getvalue()) //返回"hello world!"

**实例2**

	from io import StringIO //导入StringIO
	f = StringIO('Hello!\nHi!\nGoodbye!') //可以直接用一个str初始化StringIO.之后可以向读文件一样的读取
	while True:
		s = f.readline() //读取一行的内容
		if s == '': //读到空(没有内容了)
			break
		print(s.strip())

	/*结果为:
		Hello!
		Hi!
		Goodbye!
	*/

***

## 10 Python内置模块

### 10.1 os模块

**1.os模块**

	import os	//导入os模块
	os.name		//操作系统名字(如果为posix---说明系统是linux/Unix/Mac os X; 如果为nt则是windows)
	os.uname()	//获取系统详细信息,windows上没有
	os.environ	//查看操作系统定义的环境变量,为一个dict
	os.getenv('PATH')	//获取环境变量调用"os.getenv('导出的环境变量')"函数
	os.rename('test.txt', 'test.py')	//文件重命名
	os.remove('test.py')				//删除文件

**2.os.path相关函数**

	import os.path
	os.path.abspath('.')	//列出当前目录的绝对路径
	os.path.realpath('.')	//也是列出当前目录的绝对路径
	//在某个目录下创建新目录步骤:
	1)os.path.join('/user/defy', 'testdir')
	/*
		先将新目录的完整路径表示出来.第一个通常为绝对路径(也可以用相对路径).两个路径会合成为一个
		此处为:/user/defy/testdir
	*/
	2)os.mkdir('/user/defy/testdir')			//创建一个目录
	os.rmdir('/user/defy/testdir')
	/*
		删除一个目录,该目录必须为空.如果存在文件可以:
			os.remove(dir_path + '/file_name')	//先把文件删除,再os.rmdir()删除目录.
	*/
	3)os.path.isfile('/user/defy/test.txt') 
	//判断"/user/defy/test.txt"是否是一个存在的文件,如果是返回True,否则返回False.

	//拆分路径
	os.path.split('/user/defy/testdir/file.txt')
	/*拆分得到('/user/defy/testdir', 'file.txt')---最后一级为文件名*/
	//得到扩展名
	os.path.splitext('/user/defy/testdir/file.txt')
	/*得到('/user/defy/testdir/file', '.txt')---最后一级为扩展名*/

	//测试指定文件是否存在
	if os.path.exists('/user/defy/testdir/file.txt'): //文件存在为true,不存在为false.

实例---列出当前目录下的所有目录或所有.py文件

	[x for x in os.listdir('.') if os.path.isdir(x)]	//列出所有目录

	[x for x in os.listdir('.') if os.path.isfile(x) and os.path.splitext(x)[1] == '.py']
	//列出所有的.py文件---os.path.splitext(x)返回的为tuple,因此"os.path.splitext(x)[1]"
	//相当于取后面的扩展名

**3.os.popen函数**

os.popen(cmd):为一个命令(cmd)执行结果打开一个管道.返回值调用read()方法即可将内容(命令执行结果)读出.

	b = os.popen('ls') //为ls命令执行结果打开一个管道,并返回给b
	print b.read() //b.read():将"ls"命令执行结果从b这个管道中读出.

**4.os.getcwd函数**

os.getcwd():获得当前的工作目录

	os.getcwd()相当于linux的命令pwd.

**5.os.chdir函数**

os.chdir(path):change directory(类似linux下的cd命令),切换目录到path.

	//切换到"/usr/defy/test"目录
	os.chdir('/usr/defy/test') //只能使用绝对路径

**6.os.path.isdir函数**

os.path.isdir(pathname):如果pathname是一个存在的目录,返回True;否则返回False.

**7.os.mkdir函数**

os.mkdir(pathname, mode):以权限mode创建一个名叫pathname的目录(如果没有指定mode,则为0777).

	import os
	path = "/usr/defychen/test"
	
	os.mkdir(path, mode = 755)	//创建path目录
	os.mkdir(path) //创建path目录,权限为0777

**8.os.system函数**

os.system(cmd):执行linux下的shell命令.返回命令执行状态.

	os.system('dir') //在windows下执行"dir"相当于linux下的ls.但是由于编码的问题会显示乱码.linux会好点
	//比较好的方法:
	b = os.popen('dir')
	print (b.read())	//也是显示命令执行结果,windows不会出现乱码.

### 10.2 sys模块

**1.sys.platform**

获取当前系统平台.

	在linux命令行输入:python
	>>> import sys
	>>> sys.platform //结果为:linux2--->linux 2.x/3.x/4.x都显示为linux2
	
	windows下执行:
		sys.platform //结果为:win32

**2.sys.version**

获取当前python的版本信息

	在linux命令行输入:python
	>>> import sys
	>>> sys.version //结果为:'2.7.5 (default, Feb 27 2017, 22:30:25) \n[GCC 4.9.4]'
					//表示当前python版本为"2.7.5"

**3.sys.stdout.write**

往标准输出(一般为屏幕)写入字符串,一般配合sys.stdout.flush将字符串从标准输出打印出来

	import sys
	sys.stdout.write('xxxx....')
	sys.stdout.flush()

### 10.3 random模块

	#!/usr/bin/env python
	# -*- coding:utf-8 -*-

	import random

	print(random.random()) 		//随机产生[0, 1)之间的数(e.g. 0.189xxx)
	print(random.randint(1, 6)) //随机产生[1,6]之间的整数(e.g. 2)
	print(random.randrange(1, 3)) //随机产生[1, 3)之间的整数(e.g. 1)
	print(random.randrange(0, 101, 2)) //随机产生[0, 101)步长为2的数,即偶数(e.g. 74)
	print(random.choice("hello")) //从指定字符串中随机取出一个字符(e.g."e")
	print(random.choice([1, 2, 3, 4])) //从列表中随机取出一个元素(e.g.2)
	print(random.choice(("abc", "123", "liu"))) //从tuple中随机取出一个元素(e.g."liu")
	print(random.sample("hello", 3)) //从列表中随机取出3个元素(e.g.'l', 'h', 'o')
	print(random.uniform(1, 10)) //随机产生指定区域的浮点数(e.g.1.2919)

	items = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
	print("洗牌前:", items) //洗牌前: [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]
	random.shuffle(items)  //random.shuffle(list):将列表中的所有元素随机排序
	print("洗牌后:", items) //洗牌后: [6, 9, 2, 7, 1, 3, 8, 5, 4, 0]

### 10.4 shutil模块

shutil:High level file operations(高级的文件操作模块).

os模块提供了对目录/文件的新建、删除、查看文件属性,还提供了对文件以及目录的路径操作.但是os模块没有提供对文件/目录的移动、复制、打包、压缩、解压缩等的操作.shutil就是对os模块这方面的补充.

**1.shutil.copyfileobj(fsrc, fdst, length=16*1024)---需要先打开文件**

从fsrc copy文件内容到fdst,可以指定copy的大小(默认为16*1024字节).但fsrc,fdst必须是已经打开的文件.

	import shutil
	f1 = open('fsrc_pathname', 'r')
	f2 = open('fdst_pathname', 'w+') //以可写方式打开
	shutil.copyfileobj(f1, f2, length=1*1024) //copy 1*1024(即1K)
	shutil.copyfileobj(f1, f2) //copy 16*1024(即16K)

**2.shutil.copyfile(src, dst)---直接指定文件名即可(不需要打开文件)**

从文件名src copy内容到文件名dst,不需要打开文件.

	import shutil
	shutil.copyfile('fsrc_pathname', 'fdst_pathname')

**3.shutil.copymode(src, dst)---仅copy文件的权限.其他都不copy.**

copy src的文件权限到dst.

	1.copy前两个文件的权限: ls -l
		-rw-r--r--. 1 root root 79 May 14 05:17 test1
		-rwxr-xr-x. 1 root root  0 May 14 19:10 test2
	2.实现copy动作
		import shutil
		shutil.copymode('test1', 'test2')
	3.copy后两个文件的权限: ls -l
		-rw-r--r--. 1 root root 79 May 14 05:17 test1
		-rw-r--r--. 1 root root  0 May 14 19:10 test2 //test2的文件权限和test1一样
	PS:如果目标文件为一个不存在的文件会报错

**4.shutil.copystat(src, dst)---copy所有的状态信息(包括:权限,组,用户,时间等)**

copy src的文件状态信息到dst.

	import shutil
	shutil.copystat('fsrc_pathname', 'fdst_pathname')

**5.shutil.copy(src, dst)---copy文件的内容及权限,即先copyfile后copymode**

	import shutil
	shutil.copy('fsrc_pathname', 'fdst_pathname')

**6.shutil.copy2(src, dst)---copy文件的内容及文件的所有状态信息,即先copyfile后copystat**

类似于linux下的cp命令.

	import shutil
	shutil.copy2('fsrc_pathname', 'fdst_pathname')

**7.shutil.copytree(src, dst, symlinks=False, ignore=None)---递归的复制文件内容及状态信息**

类似于linux下的cp -r命令(递归复制).

	1.tree copytree_test/ //目录树
		copytree_test/
		└── test
		    ├── test1
		    ├── test2
		    └── hahaha
	2.shutil.copytree('copytree_test', 'copytree_copy') //得到一个copytree_copy
	3.查看: tree copytree_copy/
		copytree_copy/
		└── test
		    ├── hahaha
		    ├── test1
		    └── test2

**8.shutil.rmtree(path, ignore_errors=False, noerror=None)---递归的删除文件**

类似于linux下的rm -rf命令.

	import shutil
	shutil.rmtree('pathname')

**9.shutil.move(src, dst)---递归的移动文件**

类似于linux下的mv命令(重命名).

	shutil.move('pathname1', 'pathname2')

**10.shutil.make_archive(base_name, format, root_dir=None...)**

base_name:压缩后的文件名或路径名.

format:压缩或打包的格式(e.g.zip, tar, bztar, gztar等)

root_dir:需要打包的源文件/目录.

	import shutil
	shutil.make_archive('mytar', 'gztar', root_dir='copytree_test')

	ls -l
	-rw-r--r--. 1 root   root      0 May 14 21:12 mytar.tar.gz

**11.压缩及解压缩更常用的处理是调用zipfile和tarfile两个模块来处理**

	1.zipfile的使用
		import zipfile
		
		//压缩
		z = zipfile.ZipFile('myzip.zip', 'w') //创建压缩包
		z.write('a.log') //将a.log文件放到压缩包中
		z.write('data.data') //将data.data文件放到压缩包中
		z.close() //关闭创建的压缩包
	
		//解压
		z = zipfile.ZipFile('myzip.zip', 'r')
		z.extractall() //将所有文件解压出来
		z.close()
	2.tarfile的使用
		import tarfile
		
		//压缩
		tar = tarfile.open('mytar.tar', 'w')
		tar.add('/usr/defy/test1.log', arcname='test1.log')
		//将'/usr/defy/test1.log'文件以test1.log名字放到压缩包中
		tar.add('/usr/defy/test2.log', arcname='test2.log')
		//将'/usr/defy/test2.log'文件以test2.log名字放到压缩包中
		tar.close() //关闭创建的压缩包

		//解压
		tar = tarfile.open('mytar.tar', 'r')
		tar.extractall() //可设置解压的地址
		tar.close()

### 10.5 commands模块(python 2.x)/subprocess模块(python 3.x)

**1.commands模块主要用于python 2.x**

python中的commands模块用于调用linux下的shell命令.有3种方法:

	commands.getstatus(cmd)			//返回命令的执行状态
	commands.getoutput(cmd)			//返回执行结果
	commands.getstatusoutput(cmd)	//返回一个tuple,包含执行状态和执行结果

实例---调用shell命令,查看某文件是否存在

	#!/usr/bin/python
	#-*- coding:utf-8 -*-
	
	import commands
	import os
	aa = "hello"
	output = commands.getstatusoutput("find . -name " + aa)
	//在当前路径下查找"hello"文件是否存在
	print output
	/*
		得到:(0, './11/hello')
		0:表示该命令执行成功.类似rm删掉一个不存在的文件,则会得到256的值.
		'./11/hello':表示该文件存在,在路径./11/hello.
	*/
	print os.path.abspath(output[1])
	/*
		os.path.abspath(output[1]):获取查找到的文件的绝对路径.
	*/

**2.subprocess在python 3.x中用于取代commands模块**

	!!/usr/bin/env python
	#-*- coding:utf-8 -*-
	
	import subprocess
	import os
	aa = 'hello'
	output = subprocess.getstatusoutput('find . -name' + aa)

***

## 11 序列化及JSON

需要在不同的编程语言之间传递对象,必须将对象序列化为标准格式(e.g.XML,JSON).但是最好的方法是序列化为JSON.

优点:

1)JSON表示出来就是字符串(易读);

2)可以被所有语言读取,也可以方便的存储到磁盘或者网络传输;

3)速度比XML块,可以直接在Web页面中读取.JSON表示的对象就是标准的JavaScript语言的对象.

### 11.1 JSON类型与Python类型对比

		JSON		Python
		{}			dict
		[]			list
		"string"	'str'或u'unicode'
		1234.56		int/float
		true/false	True/False
		null		None

### 11.2 Python与JSON格式的转换

**json.dumps(Python对象)---Python对象转换为JSON格式(也叫序列化)**

	import json
	d = dict(name='Bob', age=20, score=88)
	json.dumps(d)
	//得到的结果为:{"age":20, "score":88, "name":"Bob"} //JSON的为双引号

**json.loads(json格式)---JSON格式转换为Python(也叫反序列化)**

	json_str = '{"age":20, "score":88, "name":"Bob"}'
	/*
		json.loads(para)的参数para必须是str类型,此处使用'{}'为了避免单引号和双引号解析错误,{}外面使用
		双引号("")会报错,因为不能分辨出双引号的匹配.
	*/
	json.loads(json_str)
	//得到的结果为:{'age':20, 'score':88, 'name':'Bob'}

***

## 12 进程和线程

### 12.1 多进程(multiprocessing)

**1)fork方法---windows没有,使用会报"AttributeError: module 'os' has no attribute 'fork'."**

	import os	//os模块
	print 'Process (%s) start...' % os.getpid()		//得到主进程的PID,使用"%d"也可以.也许"%s"兼容性好
	pid = os.fork()		//创建子进程,返回两次
	if pid == 0:
		print 'I am child process (%s) and my parent is %s.' % (os.getpid(), os.getppid())
		//os.getppid()---得到父进程的PID
	else:
		print 'I (%s) just created a child process (%s).' % (os.getpid(), pid)

**2)multiprocessing---跨平台的多进程模块**

	from multiprocessing import Process	//从multiprocessing模块导入Process类,该类用于创建一个子进程
	import os
	
	#子进程执行的函数代码
	def run_proc(name):
		print 'Run child process %s (%s)...' % (name, os.getpid())

	if __name__ == '__main__':
		/*
			直接运行"./hello.py",python中的特殊变量"__name__"就会置为"__main__"在其他地方导入时,
			就会判断失败,用于单独测试某模块的正确性.
		*/
		print 'Parent process %s.' % os.getpid()
		p = Process(target=run_proc, args=('test',))	
		/*
			创建一个进程实例.target:指定子进程需要执行的函数
			args:子进程执行的函数参数,是一个tuple.只有一个时需要加逗号('test',)
		*/
		print 'Process will start.'
		p.start()			//启动子进程
		p.join()			//等待子进程结束再继续往下运行,常用于进程间同步
		print 'Process end.'

**3)进程池Pool---用于批量创建子进程**

	from multiprocessing import Pool
	import os, time, random

	def long_time_task(name):
		print 'Run task %s (%s)...' % (name, os.getpid())
		start = time.time()		//得到当前时间,为秒数
		time.sleep(random.random() * 3)	//random.random()---得到随机值(0~1); time.sleep()进程睡眠
		end = time.time()
		print 'Task %s runs %0.2f seconds.' % (name, (end - start))	//得到运行时间

	if __name__ == '__main__':
		print 'Parent process %s.' % os.getpid()
		p = Pool()		//创建一个进程池p
		for i in range(5):
			p.apply_async(long_time_task, args=(i, ))	
			//进程池指定运行函数使用"p.apply_async(func, args)"
		print 'Waiting for all subprocess done...'
		p.close()	//join之前必须调用close,然后就不能再继续添加新的进程了
		p.join()
		print 'All subprocess done.'

	//结果
	Parent process 669.
	Waiting for all subprocess done...
	Run task 0 (671)...
	Run task 1 (672)...
	Run task 2 (673)...
	Run task 3 (674)...		//后面没有紧跟着task 4,是因为CPU核心数为4,最多同时执行4个进程
	Task 2 runs 0.14 seconds.
	Run task 4 (673)...
	Task 1 runs 0.27 seconds.
	Task 3 runs 0.86 seconds.
	Task 0 runs 1.41 seconds.
	Task 4 runs 1.91 seconds.
	All subprocess done.

**4)进程间通信---Queue/Pipes等方式**

	from multiprocessing import Process, Queue	//使用Queue实现进程间通信
	import os, time, random
	
	#写数据进程执行的代码
	def write(q):
		for value in ['A', 'B', 'C']:
			print 'Put %s to queue...' % value
			q.put(value)		//队列写数据"q.put(...)"
			time.sleep(random.random())

	#读数据进程执行的代码
	def read(q):
		while True:		//死循环
			value = q.get(True)	//参数True会导致:如果队列中没有数据则调用线程暂停,直至有数据才继续
								//如果为False会导致:如果队列中为空,会引发异常.所以一般为True
			print 'Get %s from queue.' % value

	if __name__ == '__main__':
		#父进程创建Queue,并传给子进程
		q = Queue()		//创建Queue
		pw = Process(target=write, args=(q,))
		pr = Process(target=read, args=(q,))
		#启动写进程,写入数据
		pw.start()
		#启动读进程,读取数据
		pr.start()
		#等待pw(写进程)结束
		pw.join()
		#pr(读进程是死循环),需要强行终止
		pr.terminate()		//强行终止死循环进程
	/*结果为:
		Put A to queue...
		Get A from queue.
		Put B to queue...
		Get B from queue.
		Put C to queue...
		Get C from queue.
	*/

### 12.2 多线程---threading模块

	import time, threading		//导入threading(多线程)模块
	
	#新线程执行代码
	def loop():
		print 'thread %s is running...' % threading.current_thread().name
			//任何一个线程都可以通过threading.current_thread().name获得当前线程名
		n = 0
		while n < 5:
			n = n + 1
			print 'thread %s >>> %s' % (threading.current_thread().name, n)
			time.sleep(1)
		print 'thread %s ended.' % threading.current_thread().name

	print 'thread %s is running...' % threading.current_thread().name
	t = threading.Thread(target=loop, name='LoopThread')	//创建线程.Target=线程函数名;name=传递的线程名
	t.start()		//启动线程
	t.join()		//等待子线程结束
	print 'thread %s ended.' % threading.current_thread().name

	//结果:
	thread MainThread is running...		//主线程名字默认为"MainThread"
	thread LoopThread is running...		//如果没有指定name,系统默认名字为"Thread-1", "Thread-2",...	
	thread LoopThread >>> 1
	thread LoopThread >>> 2
	thread LoopThread >>> 3
	thread LoopThread >>> 4
	thread LoopThread >>> 5
	thread LoopThread ended.
	thread MainThread ended.

### 12.3 threading.Lock()---线程锁

多个线程对同一资源(全局变量)访问时,可能会把值修改的混乱.需要增加一个threading.Lock()，让访问该资源按单一线程执行.

	import time, threading
	
	#银行存款
	balance = 0

	lock = threading.Lock()		//线程锁
	
	def change_it(n):
		#先存后取,结果为不便.此处为0.
		global balance	//明确说明在函数中使用之前定义的全局变量balance
		balance = balance + n
		balance = balance - n

	def run_thread(n):		//线程带参数n
		for i in range(1000):
			#change_it函数会修改全局变量,加锁后只允许单线程执行,保护该资源
			lock.acquire()	//获得锁,后面的代码是单线程执行
			try:
				change_it(n)	//调用修改全局变量的函数
			finally:		//finally中的代码肯定会执行,此处目的是释放锁
				lock.release()	//释放锁

	t1 = threading.Thread(target=fun_thread, args=(5,))		//创建带参数的线程
	t2 = threading.Thread(target=fun_thread, args=(8,))
	t1.start()		//启动线程t1
	t2.start()		//启动线程t2
	t1.join()		//等待线程1结束
	t2.join()		//等待线程2结束
	print balance	//结果为0

**操作系统出现硬盘狂响,点窗口无反应是因为开的任务(进程/线程)过多,操作系统忙着切换任务,此时根本没有时间去执行任务.**

***

## 13 摘要算法(SHA/MD5)

Python的hashlib提供了常用的摘要算法(MD5, SHA1等).

摘要算法:又称哈希算法、散列算法.通过一个函数,将任意长度的数据转换成一个长度固定的16进制表示的字符串.

目的:摘要算法通过摘要函数f()对任意长度的数据data计算出固定长度的摘要digest.目的是为了发现源数据是否被篡改过.摘要函数f(data)是一个单向函数,计算f(data)很容易,但通过digest反推data却很难.

实例:---计算一个字符串的MD5值.

	import hashlib
	md5 = hashlib.md5()		//得到hashlib库中的md5函数
	md5.update('how to use md5 in python hashlib?'.encode('utf-8'))
	/*
		md5.update(''):将字符串写入md5的一段buffer---添加字符串
		从python 3.x开始,md5.update('xxx'.encode('utf-8'))--->要将字符串编码成utf-8的编码.
	*/
	print md5.hexdigest()		//md5.hexdigest()---开始计算得到md5值

	//结果为:d26a53750bc40b38b65a520292f69306

分块多次调用update(),最终的md5值都是一样的:

	import hashlib
	md5 = hashlib.md5()
	md5.update('how to use md5 in '.encode('utf-8'))
	md5.update('python hashlib?'.encode('utf-8'))
	print md5.hexdigest()

**MD5:最常见的摘要算法,速度快,生成的长度是32个16进制字符串(32*4 = 128 bit = 16 byte).**

实例---SHA1调用

	import hashlib
	sha1 = hashlib.sha1()	//得到hashlib库中的sha1函数
	sha1.update('how to use sha1 in '.encode('utf-8'))
	sha1.update('python hashlib?'.encode('utf-8'))
	print sha1.hexdigest()		//计算得到sha1值

	//结果为:b752d34ce353e2916e943dc92501021c8f6bca8c

**SHA1:生成的长度是40个16进制的字符串(40*4 = 160 bit = 20 byte).**

**摘要算法不是加密算法,不能用于加密---因为无法通过摘要反推明文.**

***

## 14 网络编程

网络通信:就是两台计算机上的两个进程之间的通信.(e.g.本地浏览器进程与新浪服务器上的某个web服务进程在通信;QQ进程与腾讯的某个服务器上的某个进程在通信).

Python进行网络编程,就是在Python程序本身这个进程内,连接别的服务器进程的通信端口进程通信.

### 14.1 TCP/IP简介

IP地址:每台计算机的唯一标识(对应计算机的网络接口---也就是网卡).

互联网中通过给固定地区分配固定的IP地址,来实现全球的网络互联.处于某个地区内部的互联网,通过给地区的子区域分配IP地址,实现区域内部互联,如果与地区之外的区域通信,可通过分配给该地区的固定IP地址实现通信.

**IP协议:**

1)负责将数据从一台计算机通过网络发送到另一台计算机.数据被分割成一小块一小块,以IP包的形式发送出去.

2)在传输过程中,由于存在多条线路.路由器负责选择一条路径将IP包转发出去.

3)IP包特点是按块发送(IP包),途经多个路由.但不能保证到达,也不能保证顺利到达.

**TCP协议:**

1)建立在IP协议之上.负责在两台计算机之间建立可靠连接,保证数据包顺利到达.

2)TCP协议会通过握手建立连接,然后对每个包编号,确保对方按顺序收到,如果包丢失就重发.

3)其他更高级的协议(HTTP协议、SMTP协议)都是建立在TCP协议之上的.

**IP包的组成:**

1)传输的数据---最基本的组成;

2)源IP地址和目标IP地址---识别通信的计算机;

3)源端口和目标端口---端口用于区分同一台计算机上的不同网络程序,即每个网络程序都会向操作系统申请唯一的端口号.

因此,两个进程在两台计算机之间建立网络连接就需要各自的IP地址和各自的端口号.

### 14.2 TCP编程

socket:表示打开了一个网络连接.

**客户端:**

主动发起连接的叫客户端,被动响应连接的叫服务器.

实例:

	import socket	//导入socket库
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)	
	//创建一个socket,AF_INET:IPv4协议(IPv6---AF_INET6);SOCK_STREAM:面向流的TCP协议
	s.connect(('www.sina.com.cn', 80))	
	/*
		IP地址+端口号.---IP地址可由域名"www.sina.com.cn"自动转换.connect接收一个参数,因此需要将ip
			+端口号组成一个tuple再传进去.
		端口号分类:80 web服务标准端口;25 SMTP服务端口;21 FTP服务端口.
			端口号<1024---Internet标准服务
	s.send('GET / HTTP/1.1\r\nHost: www.sina.com.cn\r\nConnection: close\r\n\r\n')
	//发送数据---此处为请求首页内容.
	
	//接收数据
	buffer = []		//接收数据buffer
	while True:		//死循环
		d = s.recv(1024)	//每次最大接收1K byte数据
		if d:
			buffer.append(d)	//当接收到的数据不为空,添加到buffer
		else:
			break				//为空跳出while
	data = ''.join(buffer)		//将buffer中的数据放到data中
	s.close()		//关闭socket连接
	
	//解析接收到的数据
	header, html = data.split('\r\n\r\n', l)	//????
	print header
	//将接收到的数据写入文件
	with open('sina.html', 'wb') as f:
		f.write(html)		//将html写入sina.html文件,然后直接打开sina.html文件即可	

**服务器:**

1)创建一个基于IPv4和TCP协议的socket:

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

2)绑定监听的IP地址和端口:

	s.bind(('127.0.0.1', 9999))
	/*
	1)IP地址:服务器有多块网卡,每块网卡对应一个IP地址.bind中的IP地址区域填写"0.0.0.0"表示本服务器
		所有的IP地址."127.0.0.1"表示本机地址.此时客户端必须同时在本机运行才能连接上,外部计算机无法连接.
	2)端口:端口号<1024需要管理员权限才能绑定.>1024可以任意绑定.
	3)bind()函数接收一个参数,因此需要将ip+端口号组成一个tuple再传进去.
	*/

3)监听端口:
	
	s.listen(5)	//参数表示最大的连接数量,为设置socket的一种属性.经过这个设置后socket就可以等待客户端的连接了.
	print 'Waiting for connection...'

4)接收客户端连接,并创建线程处理客户端连接:

	while True:		//使用死循环来接收客户端连接
		sock, addr = s.accept()
		/*
			s.accept()等待并返回一个客户端连接.
			sock:表示一个客户端的socket;
			addr:包含客户端的IP地址(此处为127.0.0.1,与服务器相同)和客户端的端口
		*/
		t = threading.Thread(target=tcplink, args=(sock, addr))	//创建处理客户端连接的线程
		t.start()		//启动线程

5)处理客户端连接的线程

	def tcplink(sock, addr):
		print 'Accept new connection from %s:%s...' % addr	//打印出客户端的IP和端口
		sock.send('Welcome')	//给客户端发送欢迎信息
		while True:
			data = sock.recv(1024)	//接收最大数据1024 byte
			time.sleep(1)			//睡眠1s
			if data == 'exit' or not data:	//发送'exit'或没有数据就退出线程循环---进而结束该线程
				break
			sock.send('Hello, %s' % data)	//添加Hello头然后发送给客户端
		sock.close()	//关闭socket
		print 'Connection from %s:%s closed.' % addr

**实例---客户端/服务器的TCP连接**

	//服务器程序:echo_server.py
	#!/usr/bin/python
	//指定python程序的位置,此时可以直接"./echo_server.py"调用,否则必须"python echo_server.py"
	import socket, time, threading	//会使用socket,time,threading等模块
	
	def tcplink(sock, addr):
		print 'Accept a new connection from %s:%s...' % addr
		sock.send('Welcome'.encode())
		/*
			python 3.x之后所有网络/磁盘数据都是基于字节流,因此:
				sock.send('Welcome'.encode()):socket需要将字符串转成字节流来发送.
		*/
		while True:
			data = sock.recv(1024).decode()
			/*
			sock.recv(1024).decode():最大接收2014字节的数据,基于字节流.因此需要转成str用于后续分析.
			*/
			time.sleep(1)
			if data == 'exit' or not data:
				break
			sock.send(('Hello, %s' % data).encode()) //转成字节流
		sock.close()
		print 'Connection from %s:%s closed.' % addr
	
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	#bind ip+port(server)
	s.bind(('127.0.0.1', 9999))		//仅限于本机的连接
	#listen port & set listen attribute.
	s.listen(5)
	print 'Waiting for connection...'
	while True:
		#accept a new connection
		sock, addr = s.accept()
		#create a new threading to deal with TCP connection
		t = threading.Thread(target=tcplink, args=(sock, addr))
		t.start()

	//客户端程序:echo_client.py
	#!/usr/bin/python
	import socket

	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	#create connect
	s.connect(('127.0.0.1', 9999))
	#receive welcome message
	print s.recv(1024).decode() //将字节流转成str
	for data in ['Defy', 'Tracy', 'Sarah']:
		#send data
		s.send(data.encode()) //转成字节流
		print s.recv(1024).decode() //将字节流转成str
	s.send('exit')	//结束发送
	s.close()

**服务器程序会永远accept客户端(一种死循环,无限运行下去),结束客户端需要使用"Ctrl+C"**

### 14.3 UDP编程

**UDP协议特点:**

1)不需要建立连接,只需要知道对方的IP地址和端口号,就可以直接发送数据包;

2)传输数据不如TCP可靠.但是速度比TCP快,适用于要求及时但是不要求可靠到达的场合(e.g.QQ等).

**实例---客户端/服务器的UDP连接**

	//服务器:udp_server.py
	#!/usr/bin/python
	import socket
	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	#bind port
	s.bind(('127.0.0.1', 9999))
	print 'Bind UDP on 9999...'
	#receive data
	while True:
		data, addr = s.recvfrom(1024)
		/*
			服务器端接收数据使用"s.recvfrom(1024)".
			recvfrom(字节数):返回一个tuple,包含data和addr(ip+port)信息.
			tuple不能转成str,因此此处不需要decode().
		*/
		print 'Received from %s:%s...' % addr
		s.sendto(('Hello, %s!' % data).encode(), addr)
		/*
			s.sendto(data.encode(), addr):para1:需要发送的数据;para2:IP+port.data需要转成字节流.
		*/

	//客户端:udp_client.py
	#!/usr/bin/python
	import socket, time
	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	for data in ['Defy', 'Tracy', 'Sarah']:
		#send data to server
		s.sendto(data.encode(), ('127.0.0.1', 9999)) //数据需要转成字节流
		time.sleep(1)	//睡眠1s
		#receive data
		print s.recv(1024).decode()	//客户端接收数据使用"s.recv(1024)",接收纯数据.需要转成str.
	s.close()
	
***

## 15 常用的第三方模块

### 15.1 模块安装相关操作

#### 15.1.1 模块安装方法

在windows(cmd窗口)或linux下输入下面命令,即可安装所需模块

	pip install module_name

#### 15.1.2 查看已经安装的模块

	pip freeze	//查看已经安装的模块

### 15.2 PIL库

**1.pip**

pip:python中安装第三方模块的包管理工具,通过它,就能安装编程时常用的一些模块.

正常在安装python时选中"Install launcher for all users(recommanded)"会将pip安装上,直接安装PyCharm时可能没有安装pip.安装pip的方法如下:

[pip下载地址](https://pypi.org/project/pip/#downloads)

	1.从下载地址下载对应版本的pip(python 3.x下载最新即可);
	2.解压出来到某一目录;
	3.打开cmd窗口,切换到pip解压的目录.输入:
		python setup.py install
		//确保在命令行中python命令可用,如果不可用,需要添加到windows的环境变量PATH中.
	4.将安装后的pip命令添加到windows的PATH中:
		右键"我的电脑"->属性->高级系统设置->环境变量->在"系统变量"的Path后面添加:
		xxx;G:\Programs (x86)\Python\Python3.7;;G:\Programs (x86)\Python\Python3.7\Scripts
		//前面一个为Python程序的目录,后一个为pip程序(命令)的目录(安装后会在python的scripts目录中)
		
**2.PIL**

PIL:Python Imaging Library.是Python平台的图像处理标准库.

Pillow:基于PIL,处理Python 3.x的图形图像库.PIL只能处理到Python 2.x, Pillow模块能处理到Python 3.x.

**3.图像的坐标表示**

图像中左上角是坐标原点(0, 0),X轴是从左到右增长.Y轴是从上到下增长.

#### 15.2.1 Python、PIL、Pillow相关模块的安装

**1.下载**

Python下载地址[Python下载地址](https://www.python.org/downloads/)

	版本介绍:
	Download Windows x86 web-based installer --> (32位的网页版,需要联网)
	Download Windows x86 executable installer --> (32位的本地安装版,可执行程序.一般选择这种)
	Download Windows x86 embeddable zip file --> (32位的嵌入式版本,可以集成到其他应用中)
	Download Windows x86-64 web-based installer --> (64位的网页版,需要联网)
	Download Windows x86-64 executable installer --> (64位的本地安装版,可执行程序.一般选择这种)
	Download Windows x86-64 embeddable zip file --> (64位的嵌入式版本,可以集成到其他应用中)
	Download Windows help file --> (帮助文档)

**2.安装**

	安装Python时,需要注意:
		1.在第一个向导页中勾选"Add Python 3.7 to PATH";
			--->可以将路径添加到环境变量中
		2.Customize Installation之后的在第二个向导页中勾选"pip(默认是勾选)"
			--->安装包管理工具"pip"
		3.安装pillow
			在cmd中执行"pip install Pillow",就会自动安装Pillow.

#### 15.2.2 PIL库的使用简介

**1.操作图像**

1.图像缩放操作

	#!/usr/bin/python
	#-*- coding: utf-8 -*-
	from PIL import Image
	
	#打开一个图像文件
	im = Image.open('/users/defy/test.jpg') //绝对路径,尝试过相对路径会报错
	pix = im.load() 
	//load()方法可以得到整个的像素信息.pix内部为由width和height确定的像素点.
	//每个像素点都是由R,G,B构成
	#获得图像尺寸
	w, h = im.size //得到图像的宽,高-->size后面没有"()"
	#输出像素信息
	for x in range(w):
		for y in range(h):
			print pix[x, y] //输出每个像素点构成的R,G,B值
			r, g, b = pix[x, y] //也可以这样得到r,g,b的值
	#缩略
	im.thumbnail((w//2, h//2)) 
		/*
		"//"在python 3.x中表示整除; "/":表示浮点除法;
		Image.thumbnail((xxx)):接收一个参数,因此需要将w//2,h//2组成一个tuple.
		Image.thumbnail:按照宽、高对图形进行缩略.在缩略时,保持图片的宽高比例.
		*/
	#保存图片
	im.save('/user/defy/thumbnai.jpg', 'jpeg')
		//para1:文件名; para2:格式. 因为xxx.jpg就是jpeg格式,

2.图像模糊效果

	#!/usr/bin/python
	#-*- coding: utf-8 -*-
	from PIL import Image, ImageFilter
	im = Image.open('/user/defy/test.jpg')
	im = im.filter(ImageFilter.BLUR)
	/*
		im.filter():过滤.配合ImageFilter的滤波方法实现图像的滤波
		常用的滤波方法:
			ImageFilter.BLUR:模糊滤波
			ImageFilter.CONTOUR:轮廓滤波
			ImageFilter.DETAIL:细节滤波
			ImageFilter.SMOOTH:平滑滤波
	*/

**2.绘制图像**

1.生成字母验证码

	#!/usr/bin/python
	# -*- coding: utf-8 -*-

	from PIL import Image, ImageDraw, ImageFont, ImageFilter
	import random //随机数模块

	#generate random character
	def rndChar():
		rndSeed = random.randint(1,3)	//产生[1,3]的随机整数
		if rndSeed == 1:	//用于产生随机数字
			return chr(random.randint(48, 57))
		elif rndSeed == 2:	//用于产生大写字母
			return chr(random.randint(65, 90)) //random.randint(a, b):生成a~b的随机数
			//chr:数字转换字母函数.此处将ASCII码(65~90)转换为大写字母(A~Z)
		else:	//用于产生小写字母
			return chr(random.randint(97, 122))
	
	#generate random color1
	def rndColor1():
		return (random.randint(64, 255), random.randint(64, 255), random.randint(64, 255))
		//验证码的底色
	
	#generate random color2
	def rndColor2():
		return (random.randint(32, 127), random.randint(32, 127), random.randint(32, 127))
		//验证码字体的颜色

	#240 * 60
	width = 60 * 4 //验证码宽: 240
	height = 60 //验证码高: 60

	image = Image.new('RGB', (width, height), (255, 255, 255))
		/*
		para1:mode,此处表示为RGB模式;
		para2:size
		para3:color
		*/

	#create font objects
	font = ImageFont.truetype('/usr/defychen/arial.ttf', 36)
		/*
		创建字体对象.
		para1:应用字体的名字(绝对路径). arial.ttf字体可以通过windows路径(C:\Windows\Fonts)
			下面拷贝到所需要的路径.
		para2:字体大小.此处为36号
		*/

	#create Draw object
	draw = ImageDraw.Draw(image) //相当于一个画笔.可以画点/写文字
	#fill each pixel
	for x in range(width):
		for y in range(height):
			draw.point((x, y), fill=rndcolor1())
			/*
			画单独的一个点(填充一个像素点):
				para1:点坐标.(x, y):一个list
				para2:fill=填充的颜色坐标(x, x, x)
			*/

	#print the text
	for t in range(4):
		draw.text((60 * t + 10, 10), rndChar(), fill=rndColor2(), font = font)
		/*
			画文字(输出文字):
				para1:点坐标.表示从那里开始输出文字
				para2:文字.此处为一个随机的字母
				para3:填充颜色坐标.
				para4:字体.
		*/

	#fuzzy processing(模糊处理)
	image2 = image.filter(ImageFilter.BLUR)
	image2.save('/usr/defychen/code.jpg', 'jpeg')

#### 15.2.3 PIL库中Image模块的使用

**1.新建一个空白图片文件**

	#!/usr/bin/python
	# -*- coding: utf-8 -*-

	width = 60 * 4 //宽度
	heigth = 60 //高度
	from PIL import Image
	im = Image.new('RGB', (widht, height), "white")
		/*
		para1:mode,此处表示为RGB模式;
		para2:size
		para3:color.此处使用"white"字符串表示白色.也可以使用(255, 255, 255),RGB这种模式.
		*/

**2.保存图片文件**

	im.save('/user/defy/thumbnai.jpg', 'jpeg')
	//para1:文件名; para2:格式. xxx.jpg就是jpeg格式,

#### 15.2.4 PIL库中ImageDraw模块的使用

ImageDraw模块主要用于对image进行相关的操作.

**1.ImageDraw.Draw(image)**

ImageDraw.Draw(image):创建一个用来对image进行操作的对象.后续的所有操作都必须先创建这个对象.

	drawObject = ImageDraw.Draw(im)

**2.drawObject.line([x1, y1, x2, y2], options)**

以(x1, y1)为起点,(x2, y2)为终点画一条线.options包含fill选项指定线条的颜色(e.g.fill=2->表示颜色;width=3->表示线条的宽度).

[x1, y1, x2, y2]也可以写成:(x1, y1, x2, y2); [(x1, y1), (x2, y2)]; ((x1, y1) + (x2, y2))等.

	#!/usr/bin/python
	# -*- coding: utf-8 -*-

	from PIL import Image, ImageDraw

	width = 60 * 4
	height = 60
	
	im = Image.new('RGB', (width, height), (255, 255, 255))
	
	drawObject = ImageDraw.Draw(image) //创建ImageDraw对象
	drawObject.line((60, 20, 60, 40), fill = 2, width = 3) //画一条竖线
	drawObject.line([60, 20, 180, 20], fill = 128) //画一条横线
	drawObject.line((180, 20), (180, 40), "black") //画一条竖线.颜色为黑色
	drawObject.line((60, 40) + (180, 40), fill = "yellow") //画一条横线.颜色为黄色

	im.save('/usr/defychen/code.jpg', 'jpeg')

**3.drawObject.ellipse([x1, y1, x2, y2], options)**

以(x1,y1)和(x2, y2)为坐标画圆/椭圆. options中的fill指定填充圆/椭圆的颜色; outline指定圆的颜色(圆的外轮廓)

	drawObject.ellipse((60, 20) + (180, 40), fill = 'blue')
	//以蓝色填充以(60, 20)和(180, 40)构成的椭圆.

#### 15.2.5 PIL库中ImageFont模块的使用

### 15.3 subprocess模块

**1.subprocess模块的Popen类的实例介绍**

subprocess用于创建一个新的进程执行另外的程序,并与其进行通信.获取标准的输入、标准输出、标准错误以及返回码等.

subprocess模块中定义了一个Popen类,用于创建子进程.

	res = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
	/*
		创建一个Popen类的对象->res
		cmd:创建的子进程需要执行的命令/程序.(e.g.['ls -al'], ['ipconfig', '-all'], 
			或者某个可执行程序).可以为字符串或者字符列表(字符列表会组成一个命令).
		subprocess.PIPE:表示透过PIPE与子进程通信(输入,输出或者标准错误输出)
		subprocess.STDOUT:此处将标准错误直接通过标准输出流进行输出.
	*/

**2.Popen类的方法及属性**

1.Popen.pid:获取创建的子进程的ID

2.Popen.returncode:获取子进程的返回值.如果进行未结束,将返回None.

3.Popen.communicate(input=None):获取output(output存在在一个tuple中),包括stdout和stderr.input为stdin,一般为None即可.

	sout, serr = res.communicate()
	/*
	sout:是一些标准输出的信息,是个文件对象.要读取需要"obj.stdout.read()"
	serr:是一些标准错误的信息(一些string信息)
	*/

	#!/usr/bin/python
	# -*- coding:utf-8 -*-
	import subprocess
	import os
	p = Popen('/home/app', stdin = subprocess.PIPE, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	p.stdin.write('3 \n') //从标准输入写入信息
	p.stdin.write('4 \n')
	print p.stdout.read() //读出标准输出

4.poll():检查子进程是否结束.

5.wait():等待子进程结束.

**3.实例---打开一个只有ip地址的文本文件,ping该ip地址,将ping写结果写入ping.txt文件**

	#!/usr/bin/python
	# -*- coding:utf-8 -*-

	import subprocess
	import os
	class Shell(object):
		def runCmd(self, cmd):
			res = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, 
				stderr=subporcess.STDOUT) //linux下shell=True必须有
			sout, serr = res.communicate()
			return res.returncode, sout, serr, res.pid

	shell = Shell()
	fp = open('/usr/defychen/ip.txt', 'r')
	ipList = fp.readlines()
	fp.close()

	fp = open('/usr/defychen/ping.txt', 'a')
	print ipList
	for i in ipList:
		i = i.strip() //提取
		result = shell.runCmd('ping' + i) //ping某个ip地址
		if result[0] == 0: //成功执行
			w = i + ': 0'
			fp.write(w + '\n')
		else:
			w = i + ': 1'
			fp.write(w + '\n')

	fp.close()

### 15.4 platform模块

platform模块用来访问平台的相关属性

	import platform
	
	platform.machine() //返回平台架构(e.g.'x86_64')
	platform.node() //返回主机名(e.g.zhsa01)
	platform.platform() //返回系统版本(e.g.Linux-3.2.0-23-generic-...)
	platform.processor() //返回处理器名称
	platform.system() //返回系统名称(e.g."Windows"/"Linux")

### 15.5 xlrd,xlwt模块

Python一般使用xlrd(excel read)来读取Excel文件,使用xlwt(excel write)来写Excel文件.

#### 15.5.1 安装xlrd,xlwt模块

	pip install xlrd
	pip install xlwt

### 15.6 requests模块

requests模块主要用于网络访问.由于使用人性化,因此它比urlib,urlib2,httplib,httplib2更有优势.

#### 15.6.1 安装requests模块

	pip install requests

#### 15.6.2 使用requests模块

	#!/usr/bin/python
	# -*- coding:utf-8 -*-
	import requests		//导入requests模块
	
	file = r"D:\repository\data\bs4.txt"
	/*
		在windows下,对于路径名有特殊的识别.只有下面两种方法可以被正确识别:
			1)r"D:\repository\data\bs4.txt"	//这种路径肯定能别识别(前面带r/R进行转义)
			2)"D:\\repository\data\bs4.txt"	//使用两个反斜杠(有时候能识别,有时候不能识别)
			推荐使用第一种.
	*/
	res = requests.get('https://www.sina.com.cn/')
	/*
	requests.get('url'):抓取请求的url中的数据.
		url可以通过输入网站"www.sina.com"->网页中右击选择"审查元素"->Network->
		刷新下网页->在Name中选择"www.sina.com.cn"->在Headers页的General下存在:
			Request URL:https://www.sina.com.cn/	//请求的url
			Request Method:GET	//请求的方法为get,因此此处为get
	所请求的数据会存放在res中.
	*/
	res.encoding = 'utf-8'
	/*
	因为python不知道请求的网页的编码,因此会自动使用默认的编码格式"ISO-8859-1".查看编码格式方法为:
		res.encoding	//得到结果为"ISO-8859-1"
	此处使用:res.encoding = 'utf-8'	//将编码设为utf-8
	*/
	#print res.text.encode('gbk', 'ignore')
	/*
	由于Windows系统的cmd使用的编码是CP936,即GBK编码.python解释器需要将Unicode字符编码为GBK,然后
	才能在cmd中显示出来.但是Unicode编码中常会包含一些GBK编码无法显示的字符,此时会提示"'gbk' codec
	can't encode"的错误.因此使用:
		res.text.encode('gbk', 'ignore')	//表示忽略GBK无法编码的字符.
		print res.text.encode('gbk', 'ignore')	//显示请求网页响应的数据.即Response中的消息.
	*/
	#print file		//打印文件路径名,可以验证windows下文件识别
	with open(file, 'w') as f:	//以写的方式打开文件,如果不带r(转义)会报错.
		f.write(res.text.encode('gbk', 'ignore'))	//将响应的html消息写入到文件中.
	

***

## 16. Python的正则表达式

Python的re模块就是正则表达式(Regular Expressions).

	import re	//引入正则表达式模块

### 16.1 常用的字符含义

	.		匹配任意字符,除换行符"\n"之外	a.c			abc(匹配可以为a,b...任意字符)
	*		匹配前一个字符0次或者多次		abc*		ab;abccc(匹配"c"0次或多次)
	+		匹配前一个字符1次或多次		abc+		abc;abccc(匹配"c"1次或多次)
	?		匹配前一个字符0次或1次			abc?		ab;abc(匹配"c"1次或多次)
	^		匹配字符串开头				???(怎么使用)
	$		匹配字符串末尾				???(怎么使用)
	{m}		匹配前一个字符m次				ab{2}c		abbc(b为2次)
	{m,n}	匹配前一个字符m到n次			ab{1,2}c	abc;abbc(b出现1次或者2次)
	()		匹配括号中的表达式				(abc)		abc(匹配abc)
	[]		表示一组字符

	\s		匹配空白字符					a\sc		a c(中间一个空白字符)
	\S		匹配非空白字符				a\S			axc(x不能为空白字符)
	\d		匹配数字(0-9)					a\dc		a1c(\d为一个数字0-9)
	\D		匹配非数字(不是0-9)
	\w		任何字符(A-Z,a-z,0-9,_)		a\wc		abc(\w为一个字符)	
	\.		匹配"."这个字符				a\.txt		a.txt

### 16.2 re模块的函数

**1.re.findall(pattern, string)**

找到所有的匹配,并返回一个匹配列表

实例1:

	import re
	text = 'JGod is a handsome boy, but he is a ider'
	print re.findall(r'\w*o\w*', text) //查找含有"o"字符的单词
	//结果为:['JGod', 'handsome', 'boy']

实例2:

	import re
	m_findall = re.findall('[0-9]+', '12345 is the first number, 23456 is the second')
	print (m_findall)
	//结果为:
	['12345', '23456']	//[0-9]:表示0-9的任意数字;"+"表示匹配前一个字符一次或多次,此处为多次.

**2.re.search(pattern, string)**

在给定的字符串中string寻找,并返回"第一个"成功匹配字符串

实例1:

	import re
	a = re.search(r'(\d+)x(\d+)', '1080x1920')
	print (a)
	print (a.group(0))
	print (a.group(1))
	print (a.group(2))
	print (a.groups())
	//结果为:
	1080x1920
	1080
	1920
	('1080', '1920')

**3.re.match(pattern, string, flags=0)**

re.match从字符串的起始位置开始匹配一个模式,如果起始位置匹配不成功,则返回None.pattern为正则表达式,string为原始字符串,flags用来控制正则表达式的匹配方式(e.g.是否区分大小写、多行匹配等).

实例1:

	import re
	m = re.match('www', 'www.baidu.com')
	print ("Result: ", m)
	print ("Start and End: ", m.span())
	print ("The start position: ", m.start())
	print ("The end position: ", m.end())
	//结果为:
	Result:  <re.Match object; span=(0, 3), match='www'>
	Start and End:  (0, 3)	//m.span():存放起始和终点位置
	The start position:  0	//match起始从0开始
	The end position:  3	//3:表示匹配上了位置0,1,2处的三个字符

实例2:

	import re
	line = "Fat cats are smarter than dogs, is it right?"
	m = re.match(r'(.*) are (.*?) dogs', line)
		//此处的r表示raw string,表示不会对引号内部的反斜线"\"做特殊处理.
	print ("The sentence of match: ", m.group(0))	//group(0):表示匹配的整句话
	print ("The first result of match: ", m.group(1))	//group(1):第一个匹配的结果
	print ("The second result of match: ", m.group(2))	//group(2):第二个匹配的结果
	print ("The result list of match: ", m.groups())	//groups():表示匹配列表
	//结果为:
	The sentence of match:  Fat cats are smarter than dogs
	The first result of match:  Fat cats
		--->(.*):此处表示匹配前一个字符(为任意字符)多次,且匹配尽量多的字符
	The second result of match:  smarter than
		--->(.*?):前面的.*表示匹配前一个字符(为任意字符)多次,(?)表示匹配尽量少的字符
	The result list of match:  ('Fat cats', 'smarter than')

	/*测试:
	m = re.match(r'(.*) are (.*?)', line)
	此时m.group(2)为空,因为可以匹配零次,后面也没限制;
	m = re.match(r'(.*) are (.*?)', line)
	此时m.group(2)为"smarter than dogs, is it right?",因为会匹配的尽可能的多.
	*/

### 16.3 re模块的函数实例

#### 16.3.1 匹配科学计数法

	#!/usr/bin/python
	#-*- coding: utf-8 -*-
	import re
	total_data = ['0.0012', '5e-04']
	res_data = []

	regex = r'\d+\.?\d*'	//能匹配类似"0.0012"的数据
	regex1 = r'\d+(e-\d+)?'	//能匹配类似"5e-04"此类的科学计数法的数据
	for data in total_data:
		res1 = re.findall(regex, data)
		if float(res1[0]) > 1:	//针对科学计数法的数据
			/*
				1.如果数据为"0.0012",res1[0]会直接得到该数据;
				2.如果数据为"5e-04",res1[0]会得到一个5.因此需要下一步提取后面的"e-04".
				PS:此处只能使用float(res1[0]),使用int(res1[0])会报:
					invalid literal for int() with base 10:xxx
			*/
			res2 = re.findall(regex1, data)	//得到后面的"e-04"
			res_data.append(float(res1[0]+res2[0]))	//将5和e-04组合起来,放到res_data中
		else:
			res_data.append(float(res1[0]))
	print (res_data)	//python 3.x需要括起来.

***

## 17. Python中常用的函数

### 17.1 enumerate函数

enumearte函数遍历序列中的元素以及他们的下标:

	//1. 用于tuple
	for i, j in enumerate(('a', 'b', 'c')):
		print i, j
		//得到结果为:
		0 a
		1 b
		2 c
	//2. 用于list
	for i, j in enumerate([1, 2, 3]):
		print i, j
		//得到结果为:
		0 1
		1 2
		2 3
	//3. 用于dict
	for i, j in enumerate({'a':1, 'b':2}):
		print i, j
		//得到结果为:
		0 a		//打印出key和对应的下表.如果要得到value需要key,value
		1 b
	//4. 用于string
	for i, j in enumerate('abc'):
		print i, j
		//得到结果为:
		0 a
		1 b
		2 


### 17.2 eval()函数

	params = ['open_keys_test', 'check_set_format', 'check_kl_algo']
	for param in params:	#从list中提取出每一个元素
		if eval('%s(obj, devices)' % param):	#提取出来的param替换s,构成调用函数
			# e.g. open_keys_test(obj, devices)
		
eval()函数返回值:成功返回0;失败返回非0

### 17.3 max(list)函数

max(list)函数返回给定参数的最大值(按照ASCII码表进行比较).

	1.字符串
		a = '1, 2, 3, 4' //类型为字符串
		max(a) //返回'4',最大的字符串
	2.数字列表
		a = [1, 2, 3, 4]
		max(a) //返回4
	3.由tuple构成的list.先比较tuple中的第一个元素,相同再比较第二个元素
		a = [(1, 2), (2, 3), (3, 1)]
		max(a) //返回(3, 1)
	4.tuple中第一个元素相同,比较第二个元素
		a = [(1, 3), (2, 2), (3, 1), (3, 2)]
		max(a) //返回(3, 2)
	5.字符与数字比较
		a = [(1, 3), (2, 2), (3, 1), (3, 'b'), ('a', 1)]
		max(a) //返回('a', 1)->字母的ASCII码值比数字大

### 17.4 sum()函数

sum(list, num)对list进行求和后再加上num(num可省略)

	sum([0, 1, 2]) //结果为3
	sum((2, 3, 4), 1) //tuple计算总和后再加1.结果为:10
	sum([0, 1, 2, 3, 4], 2) //list计算总和后再加2.结果为:12
	
### 17.5 len()函数

len(list)返回字符、list、tuple等的长度或元素个数.

	1.字符串
	str = "runoob"
	len(str) //字符串长度(也即字符串个数)为:6
	2.元素个数
	l = [1, 2, 3, 4, 5]
	len(l) //list元素个数为: 5

### 17.6 round()函数

round(x, n)返回浮点数x的四舍五入值, n表示保留几位小数(如果没有默认保留1位小数).

	round(2.234) //结果为2.0(默认保留1位小数)
	round(2.235, 2) //结果为2.23,保留2位小数(但是5也会舍去,只有大于5才会进1)
	round(2.236, 2) //结果为2.24.

### 17.7 any()/all()函数

**any**

any(list/tuple):list/tuple中的元素全部为0或''或False返回False;其他返回True.

PS:any([])空列表返回False; any(())空tuple返回False.

	1.list
	any(['a', 'b', 'c', 'd']) //返回True
	any(['a', 'b', '', 'd']) //返回True.存在一个空的元素
	any([0, '', False]) //返回False.全部元素为0或''或False
	2.tuple
	any(('a', 'b', 'c', 'd')) //返回True
	any(('a', 'b', '', 'd')) //返回True.存在一个空的元素
	any((0, '', False)) //返回False.全部元素为0或''或False
	3.空list或空tuple
	any([]) //空列表返回False
	any(()) //空tuple返回False

**all**

all(list/tuple):list/tuple全部元素都不是0,'',False返回True;否则返回False.

PS:all([])空列表返回True; all(())空tuple返回True.

	1.list
	all(['a', 'b', 'c', 'd']) //返回True.全部元素都不是0,'',False
	all(['a', 'b', '', 'd']) //返回False.存在一个空的元素
	any([0, '', False]) //返回False.全部元素为0或''或False
	2.tuple
	all(('a', 'b', 'c', 'd')) //返回True.全部元素都不是0,'',False
	all(('a', 'b', '', 'd')) //返回False.存在一个空的元素
	all((0, '', False)) //返回False.全部元素为0或''或False
	3.空list或空tuple
	all([]) //空列表返回True
	all(()) //空tuple返回True

### 17.8 time相关函数

time.time():返回当前时间的时间戳(从1970纪元后经过的浮点秒数).

	import time
	
	print "time.time(): %f " % time.time() //结果为:1523498680.14(经过的秒数)
	print time.localtime(time.time) //返回本地时间,但是不好阅读
		/*time.struct_time(tm_year=2018, tm_mon=4, tm_mday=12, tm_hour=10, tm_min=4, 
		tm_sec=57, tm_wday=3, tm_yday=102, tm_isdst=0) */
	print time.asctime(time.localtime(time.time())) //返回本地时间,便于阅读
		//Thu Apr 12 10:05:22 2018

### 17.9 sqrt()函数

sqrt(x):返回x的平方根.

	import math
	print "math.sqrt(100): ", math.sqrt(100) //返回100

**相关的特殊算术运算符**

	1.**:幂
		x**y:返回x的y次幂
		2**5 //结果为32
		3**3 //结果为27
	2./:除以(python2时整数是整除;python3是单纯的除法)
		9 / 2 //python2结果为4;python3结果为4.5
		9.0 / 2 //结果为4.5(有小数就是除法,无论python2还是python3)
	3.%:取模(取余数)
		20 % 10 //结果为0
		20.1 % 10 //结果为0.100000...
	4.//整除(全为整数则结果为整数;有小数则结果为整除值但是带.00(这样的小数))
		9 // 2 //结果为4
		9.0 // 2.0 //结果为也为4.0
	5.print ('defy'*2)	//表示defy循环2次再进行输出,输出结果为"defydefy"

***

## 18. Python对象的文档字符串(DocString):__doc__的写法及输出

文档字符串(DocString)作用:

1.可以用于说明某个Python程序或者函数的使用方法;

2.配合docopt分析命令行参数,并进行DocString中定义的字符匹配.

**1.说明Python程序/函数的使用方法**

	1.说明程序的使用方法
	""" //开始指示符:表示的是DocString.也可以用'''(单引号).一般使用3个双引号.
	Usage:
		tickets [-gdtkz] <from> <to> <date>
	
	Options:
		-h, --help		Display Help Menu
		-g				High Speed Train
		-d				Middle Speed Train
		-t				Special Speed Train
		-k				Speed Train
		-z				Directly to the Destination

	Example:
		tickets Beijing Shanghai 2018-04-19
		tickets -dg Chengdu Nanjing 2018-04-19
	""" //结束指示符.两个中间的即为DocString

	print (__doc__) //直接使用"__doc__",是得到整个程序的DocString,即在"""..."""的内容
	/*可以直接打印出:
	Usage:
        tickets [-gdtkz] <from> <to> <date>

	Options:
	        -h, --help      Display Help Menu
	        -g                      High Speed Railway
	        -d                      Middle Speed Railway
	        -t                      Specail Speed Railway
	        -k                      Speed Railway
	        -z                      Directly to the Destination
	
	Example
	        tickets Beijing Shanghai 2018-04-19
	        tickets -dg Chengdu Nanjing 2018-04-19

	*/

	2.在函数中的说明信息
	def inputxy():
		"""
			This is the test doc.
		"""
		print("Hello world")
	inputxy() //调用函数
	print(inputxy.__doc__) //打印函数的说明信息(e.g.函数名.__doc__)

	/*会得到:
		Hello world
		This is the test doc.
	*/

**2.配合docopt分析命令行参数**

docopt:Python 3的命令行参数解析工具.

	""" //开始指示符:表示的是DocString.也可以用'''(单引号).一般使用3个双引号.
	Usage:
		tickets [-gdtkz] <from> <to> <date>
	/*
	Usage:作为使用方法的说明.其后的信息可以作为命令行参数的匹配.
		[-abc]:每个元素在dict中形成一个Bool值.
			如果命令行参数包含其中的元素,则会在dict中得到一个True的值;否则为False.
			(e.g.命令行输入了:-a.则在字典中有: {'-a':True, ...})
		<xxx>:形成dict中的元素值.
			(e.g.命令行输入:成都.则在字典中有:{'<from>':'成都', ...})
	*/

	Options:
		-h, --help		Display Help Menu
		-g				High Speed Train
		-d				Middle Speed Train
		-t				Special Speed Train
		-k				Speed Train
		-z				Directly to the Destination

	Example:
		tickets Beijing Shanghai 2018-04-19
		tickets -dg Chengdu Nanjing 2018-04-19
	""" //结束指示符.两个中间的即为DocString

	from docopt from docopt //导入docopt(命令行解析工具)
	
	def cli():
		"""command-line interface"""
		arguments = docopt(__doc__)
		print(arguments)

	if __name__ == '__main__':
		cli()

***

## 19. 其他一些常用的技巧

### 19.1 python中的__all__的作用

**__all__定义其他模块只能使用本模块中特定的变量或函数**

1.foo.py文件--->定义__all__变量

	#!/usr/bin/env python
	# -*- coding: utf-8 -*-
	__all__ = ['bar', 'baz']
	/*
		定义模块变量,当其他文件import该模块后,只能找到__all__中存在的变量或函数,使用其他的会报错.
	*/
	waz = 5	//本模块可以定义其他的变量,但是其他模块不能调用该变量.
	bar = 10
	def baz():
		return 'baz'

2.run-foo.py--->使用__all__变量

	#!/usr/bin/env python
	# -*- coding: utf-8 -*-
	from foo import *
	print(bar)	//打印出10,因为__all__中含有该变量
	print(baz)	//输出baz函数的地址,因为__all__中含有该函数
	print(baz())	//输出baz函数调用结果(即'baz'),因为__all__中含有该函数

	print(waz)	//会报错"NameError: name 'waz' is not defined.".因为__all__中没有该变量或函数
	PS:如果foo.py文件中"__all__ = ['bar', 'baz']"去掉或注释,则运行正常.

### 19.2 python计算以2为底的对数

	from math import log
	log(x, 2)
	/*
		para1:所需要计算的数;
		para2:底数.
	*/

***

### Python类及实例的应用

	class Test(object):		/*Test:类名; object:从"object"继承,所有类都可以从object继承*/
		def __init__(self, name, root):	/*__init__函数,在创建实例对象时会调用*/
			/*self:指代实例自身,任何调用均不需要传递该参数; name和root为调用者传进来的参数*/
			self.testCaseName = name
			self.webRoot = root

	args = []
	args.append(name)			/*list末尾增加name元素*/
	args.append(self.webRoot)	/*list末尾增加webRoot元素*/
	return Test(*args)			/* "*args" 相当于一个list; "**args" 相当于一个dict*/
		/*此时会将"name和webRoot"传递给Test类的"__init__"函数*/

## Appendix 实例

### 1. Analysis of wechat_jump mini program

**auto_adb.py**

	# -*- coding: utf-8 -*-
	import os
	import subprocess
	import platform

	/*
		Q:类名如果取名为auto_adb和文件名相同,后续的:
		from common.auto_adb import auto_adb
		adb = auto_adb() //此处容易产生歧义
		M:改名为adb,后续就不会有这个问题
		from common.auto_adb import auto_adb
		adb = auto_adb.adb() //这样比较清晰
	*/
	class adb():
		def __init__(self):
			try:
				adb_path = 'adb'
				subprocess.Popen([adb_path], stdout=subprocess.PIPE, 
					stderr=subprocess.PIPE)
				self.adb_path = adb_path
			except OSError: //操作系统错误(e.g.[Errno 22] Invalid argument:...)
				if platform.system() == 'Windows': //Windows平台
					adb_path = os.path.join('Tools', 'adb', 'adb.exe')
					//'Tools'为相对路径.合并后的路径为:'Tools\\adb\adb.exe'(从当前目录开始)
					try:
						subprocess.Popen([adb.path], stdout=subprocess.PIPE, 
								stderr=subprocess.PIPE)
						self.adb_path = adb_path
					except OSError:
						pass
				else: //Linux平台
					try:
						subprocess.Popen([adb], stdout=subprocess.PIPE, 
							stderr=subprocess.PIPE)
					except OSError:
						pass
				print('Please install ADB driver and config the environ variable')
				print('xxxx')
				exit(1)

		def get_screen(self):
			process = os.popen(self.adb_path + 'shell wm size')
				//相当于执行"adb shell wm size".执行后的结果会放到process中
			output = process.read() //将执行的结果read出来
			return output

		def run(self, raw_command):
			command = '{} {}'.format(self.adb_path, raw_command) //由adb path和command构成完整的命令
			process = os.popen(command)
			output = process.read() //将执行的结果read出来
			return output

		def test_device(self):
			print('check device is connected or not...')
			command_list = [self.path, 'devices']
			process = subprocess.Popen(command_list, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
			output = process.communicate() //output为一个tuple,里面包含stdout和stderr
			if output.decode('utf8') == 'List of devices attached\n\n':
				/*
					正常显示应该类似下面这种:
					List of devices attached //仅仅只有这一句是不正常的
					cf264b8f    device
					emulator-5554   device
				*/
				print('can not find devices')
				print('adb output:')
				for each in output:
					print(each.decode('utft-8'))
			print('device is connected...')
			print('adb output:')
			for each in output:
				print(each.decode('utf-8'))

		def test_density(self): //获得手机屏幕的密度
			process = subprocess.Popen(self.adb_path + 'shell wm density')
				//相当于执行"adb shell wm density".执行后的结果会放到process中
			output = process.read() //将执行的结果read出来
			return output
	
		def test_device_detail(self): //获得设备信息
			process = subprocess.Popen(self.adb_path + 'shell getprop ro.product.device')
			output = process.read()
			return output

		def test_device_os(self): //获得android系统版本
			process = subprocess.Popen(self.adb_path + 'shell getprop ro.build.version.release')
			output = process.read()
			return output

		def adb_path(self): //获得adb路径
			return self.adb_path
			
**config.py**

	# -*- coding:utf-8 -*-
	'''
	读取配置文件和屏幕分辨率
	'''
	import os, sys, json, re
	from common.auto_adb import auto_adb
	
	adb = auto_adb.adb()

	def open_accordant_config():
		'''
		调用配置文件
		'''
		screen_size = _get_screen_size()
		#config_file = "{path}/config/{screen_size}/config.json".format(
			//可以自动选择"screen_size(屏幕分辨率)"下的config文件
		config_file = "{path}/config/huawei/honor9_config.json".format(
			path=sys.path[0], //sys.path[0]:得到当前文件的路径.相当于pwd
			screen_size=screen_size //对应的屏幕分辨率,用于选择配置文件
		)

		//从当前目录直接获取配置文件
		here = sys.path[0] //当前路径(pwd)
		for file in os.listdir(here): //listdir:列出当前路径下的所有文件(包括目录)
			if re.match(r'(.+)\.json', file):	//匹配.json文件
				file_name = os.path.join(here, file) //构成完成路径
				with open(file_name, 'r') as f:	//打开文件
					print("Load config file from {}".format(file_name))
					return json.load(f) //json对象的load

		//读取根据分辨率查找到的配置文件
		if os.path.exists(config_file):
			with open(config_file, 'r') as f:
				print("Load config file from {}".format(config_file))
				return json.load(f)
		else:
			with open('{}/config/default.json'.format(sys.path[0]), 'r') as f:
				//使用默认的配置文件
				print("Load default config")
				return json.load(f)

	def _get_screen_size():
		size_str = abd.get_screen() //得到的字符结果为"Physical size: 1080x1920"
		m = re.search(r'(\d+)x(\d+)', size_str) //匹配到"1080x1920"
		if m:
			return '{heigth}x{width}'.format(heigth=m.group(2), width=m.group(1))
			//return为"1920x1080"
		return '1920x1080'
		
**debug.py**

	# -*- coding: utf-8 -*-
	import os, sys, shutil, math
	from PIL import ImageDraw
	import platform
	if platform.system() == 'Windows':
		os.chdir(os.getcwd().replace('\\common', '')) //将最后的common替换为空,相当于移动到上一层目录
		path_split = "\\" //Windows以"\\"为分隔???
	else:
		os.chdir(os.getcwd().replace('/common', '')) //将最后的common替换为空,相当于移动到上一层目录
		path_split = '/'

	try:
		from common.auto_adb import auto_adb
	except Exception as ex: //捕获异常(Exception当作ex,用于输出)
		print(ex)
		print('Please run the script in the root directory')
		print('Please check whether the common folder exists under the root directory')
		exit(1)
	screenshot_backup_dir = 'screenshot_backups'
	adb = auto_adb.adb()

	def make_debug_dir(screenshot_backup_dir):
		if not os.path.isdir(screenshot_backup_dir):
			os.mkdir(screenshot_backup_dir) //创建目录,权限为0777

	def backup_screenshot(ts):
		make_debug_dir(screenshot_backup_dir)
		shutil.copy('{}{}autojump.png'.format(os.getcwd(), path_split),
				os.path.join(os.getcwd(), screenshot_backup_dir, 
								str(ts), '.png'))

	def save_debug_screenshot(ts, im, piece_x, piece_y, board_x, board_y):
		'''
		对debug图片加上注释
		'''
		make_debug_dir(screenshot_back_dir)
		draw = ImageDraw.Draw(im)
		draw.line((piece_x, piece_y) + (board_x, board_y), fill = 2, width = 3)
		draw.line((piece_x, 0, piece_x, im.size[1]), fill = (255, 0, 0))
		draw.line((0, piece_y, im.size[0], piece_y), fill = (255, 0, 0))
		draw.line((board_x, 0, board_x, im.size[1]), fill = (0, 0, 255))
		draw.line((0, board_y, im.size[0], board_y), fill = (0, 0, 255))
		draw.ellipse((piece_x - 10, piece_y - 10, piece_x + 10, piece_y + 10), 
			fill = (255, 0, 0)) //画椭圆
		draw.ellipse((board_x - 10, board_y - 10, board_x + 10, board_y + 10),
			fill = (0, 0, 255))
		del draw
		im.save(os.path.join(os.getcwd(), screenshot_backup_dir, 
						'#' + str(ts) + '.png'))

	def dump_device_info():
		'''
		显示设备信息
		'''
		size_str = adb.get_screen() //1080x1920
		device_str = adb.test_device_detail() //device信息
		phone_os_str = adb.test_device_os() //os版本
		density_str = adb.test_density() //dpi(每英寸的像素数)
		print("""*******   
		Screen: {size}
		Density: {dpi}
		Device: {device}
		Phons OS: {phone_os}
		Host OS: {host_os}
		Python: {python}
		*******""".format(
			size = size_str.replace('\n', ''), //将换行符替换为空格
			dpi = density_str.replace('\n', ''),
			device = device_str.replace('\n', ''),
			phone_os = phons_os_str.replace('\n', ''),
			host_os = sys.platform, //获取当前系统版本(e.g.linux2(所有的linux版本都显示为linux2))
			python = sys.version //获取当前python的版本
		))

**screenshot.py---截图代码**

	# -*- coding:utf-8 -*-
	'''
	手机屏幕截图代码
	'''
	import subprocess
	import os, sys
	from PIL import Image
	from io import StringIO

	try:
		from common.auto_adb import auto_adb
	except Exception as ex:
		print(ex)
		print('Please run the script in the root directory')
		print('Please check whether the common folder exists under the root direcotry')
		exit(1)
	adb = auto_adb.adb() //使用auto_adb.py中的adb()类
	SCREENSHOT_WAY = 3 //截图方法(总共0-3 四种)

	def pull_screenshot():
		'''
		获取屏幕截图,0 1 2 3 四种方法
		'''
		global SCREENSHOT_WAY //使用全局变量"SCREENSHOT_WAY"
		if 1 <= SCREENSHOT_WAY <= 3:
			process = subprocess.Popen(adb.adb_path + 'shell creencap -p', 
				shell = True, stdout = subprocess.PIPE) 
				//adb shell screencap -p:Android程序中的截图命令
			binary_screenshot = process.stdout.read()
				//obj.stdout具有文件属性,可以直接read.保存到binary_screenshot中
			if SCREENSHOT_WAY == 2:
				binary_screenshot = binary_screenshot.replace(b'\r\n', b'\n')
				//将文件中的'\n'替换为'\r\n'
			elif SCREENSHOT_WAY == 1:
				binary_screenshot = binary_screenshot.replace(b'\r\r\b', b'\n')
			return Image.open(StringIO(binary_screenshot))
				//StringIO将位于内存中的str转变成类似一个文件,可以进行open,read,write等操作
		elif SCREENSHOT_WAY == 0:
			adb.run('shell screencap -p /sdcard/autojump.png')
				//将截图保存到"/sdcard/autojump.png"
			adb.run('pull /sdcard/autojump.png .')
				//将图片"/sdcard/autojump.png"拷贝到电脑"."当前目录
			return Image.open('./autojump.png') //打开图片
			
	def check_screenshot():
		'''
		检查获取截图的方式
		'''
		global SCREENSHOT_WAY
		if os.path.isfile('autojump.png'): //检查文件是否存在,存在返回True;不存在返回False
			try:
				os.remove('autojump.png') //删除autojump.png文件
			except Exception:
				pass
		if SCREENSHOT_WAY < 0:
			print('Don't support such device')
			sys.exit()
			//sys.exit()退出会引发SystemExit异常,可以捕获该异常做清理工作.比较优雅
		try:
			im = pull_screenshot()
			im.load() //得到像素信息(e.g. pix = im.load() )
			im.close() //关闭
			print('采用方式 { } 获取截图'.format(SCREENSHOT_WAY))
		except Exception:
			SCREENSHOT_WAY -= 1
			check_screenshot()

**wechat_jump_auto.py**

	# -*- coding: utf-8 -*-

	import math, re, random, sys, time
	from PIL import Image //Python Image Library(python图像库)
	from six.moves import input //

	if sys.version_info.major != 3:
		print('Please use python version 3.x')
		exit(1) //退出
	try:
		from common import debug, config, screenshot, UnicodeStreamFilter
		from common.auto_adb import auto_adb
	except Exception as ex: //捕获异常(Exception当作ex,用于输出)
		print(ex)
		print('Please run the script in the root directory')
		print('Please check whether the common folder exists under the root directory')
		exit(1)
	#adb = auto_adb() //此句改为:
	adb = auto_adb.adb() //使用auto_adb.py中的adb()类
	
	VERSION = "1.1.4"

	DEBUG_SWITCH = True //for debug
	adb.test_device()

	config = config.open_accordant_config() //从config的json文件中取到配置信息
	under_game_score_y = config['under_game_score_y']
	// 长按的时间系数
	press_coefficient = config['press_coefficient']
	// 1/2的棋子底座的高度
	piece_base_height_1_2 = config['piece_base_height_1_2']
	// 棋子的宽度
	piece_body_width = config['piece_body_width']
	// 图形中圆球的直径.有说到可以用直线测量像素...
	head_diameter = config.get['head_diameter']
	if head_diameter == None:
		density_str = adb.test_density() //获得dpi(每英寸的像素数)
		matches =re.search(r'\d+', density_str) //提取到数字
		density_val = int(matches.group(0)) //拿到第一个值
		head_diameter = density_val / 8 //为什么是"/8"????

	def set_button_position(im):
		'''
		设置滑动的起始和终点坐标
		'''
		global swipe_x1, swipe_y2, swipe_x2, swipe_y2
		w, h = im.size
		left = int(w / 2)
		top = int(1584 * (h / 1920.0))
		left = int(random.uniform(left - 200, left + 200)) 
		//random.uniform在left-200, left+200之间随机取出一个浮点值.然后再取整
		top = int(random.uniform(top - 200, top + 200))
		after_otp = int(random.uniform(top - 200, top + 200))
		after_left = int(random.uniform(left - 200, left + 200))
		swipe_x1, swipe_y1, swipe_x2, swipe_y2 = left, top, after_left, after_top

	def jump(distance, delta_piece_y):
		'''
		根据得到的距离计算出按压的时间(不知道是如何计算得到的)
		'''
		//将程序计算的长度转换为截图上图片的实际距离
		scale = 0.945 * 2 / head_diameter
		actural_distance = distance * scale * (math.sqrt(6) / 2)
		//根据图片实际距离转换为按压时间
		press_time = (-945 + math.sqrt(945 ** 2 + 4 * 105 *
						36 * actual_distance)) / (2 * 105) * 1000
		press_time *= press_coefficient
		press_time = max(press_time, 200) //200ms为最小的按压时间
		press_time = int(press_time)

		cmd = 'shell input swipe {x1} {y1} {x2} {y2} {duration}'.format(
				x1 = swipe_x1,
				y1 = swipe_y1,
				x2 = swipe_x2,
				y2 = swipe_y2,
				duration = press_time + delta_piece_y
		)
		print(cmd)
		adb.run(cmd) //执行滑动操作(其中有滑动时间,即为按压时间)
		return press_time

	def find_piece_and_board(im):
		'''
		找到关键坐标
		'''
		w, h = im.size //得到图像的宽,高
		points = [] //所有满足像素的点集合
		piece_y_max = 0
		board_x = 0
		board_y = 0
		scan_x_border = int(w/8) //扫描棋子时的左边界
		scan_start_y = 0 //扫描时的起始y坐标
		im_pixel = im.load() //得到所有像素点信息
		
		//在高度方向的中间1/3,以50 px为步长,寻找scan_start_y
		for i in range(int(h / 3), int(h * 2 / 3), 50):
			last_pixel = im_pixel[0, i] //保存起始像素点,用于比较
			for j in range(1, w):
				pixel = im_pixel[j, i] //当前像素点
				//像素点不同,找到scan_start_y
				if pixel != last_pixel
					scan_start_y = i - 50
					break
			if scan_start_y: //该值不为0,跳出循环
				break
		print('start can Y axis: {}'.format(scan_start_y))

		//从scan_start_y开始扫描,棋子位于屏幕的上半部分(1/3~2/3)
		for i in range(scan_star_y, int(h * 2 / 3)):
			for j in range(scan_x_border, w - scan_x_border): 
				//扫描x从左边的1/8 width到距离右边1/8 width的范围.
				pixel = im_pixel[j, i] //保存像素点,用于判断
				if (50 < pixel[0] < 60) \
					and (53 < pixel[1] < 63) \
					and (95 < pixel[2] < 110):
				//像素点的G,R,B值分别为上述值.该值表示一个偏黑的灰色
				points.append((j, i)) //增加满足要求的一个像素点
				piece_y_max = max(i, piece_y_max) //找到最大的y值
		
		bottom_x = [x for x, y in points if y == piece_y_max] //最低那条线的点的横坐标
		if not bottom_x: //判断list是否为空
			return 0, 0, 0, 0, 0

		piece_x = int(sum(bottom_x) / len(bottom_x)) //求x值的中间值
		piece_y = piece_y_max - piece_base_height_1_2 //上移棋子底盘高度的一半
		
		if piece_x < w /2: //棋子在屏幕的左边
			board_x_start = piece_x //以棋子的中心作为棋盘扫描的起点
			board_x_end = w //终点是屏幕的宽度
		else: //棋子在屏幕的右边
			board_x_start = 0 //从屏幕的最左边(0)作为棋盘扫描的起点
			board_x_end = board_x //终点为棋子的中心

		for i in range(int(h / 3), int(h * 2 / 3)): //高度的1/3~2/3
			last_pixel = im_pixel[0, i] //保存像素点,用于判断
			if board_x or board_y:
				break
			board_x_sum = 0
			board_x_c = 0

			for j in range(int(board_start), int(board_x_end)): //扫描x坐标
				pixel = im_pixel[j, i]
				if abs(j - piece_x) < piece_body_width: //宽度差小于棋子的宽度,重新增加
					continue

				/*
				1.检查当前像素与背景像素有差别;
				2.检查y轴下面的5个像素,防止干扰*/
				ver_pixel = im_pixel[j, i + 5]
				if abs(pixel[0] - last_pixel[0]) \
						+ abs(pixel[1] - last_pixel[1]) \
						+ abs(pixel[2] - last_pixel[2]) > 10 \
						and abs(ver_pixel[0] - last_pixel[0]) \
						+ abs(ver_pixel[1] - last_pixel[1]) \
						+ abs(ver_pixel[2] - last_pixel[2]) > 10:
					board_x_sum += j
					board_x_c += 1
			if board_x_sum:
				board_x = board_x_sum / board_x_c //求的棋盘宽度方向上的中点
		
		last_pixel = im_pixel[board_x, i]

		center_x = w / 2 + (24 / 1080) * w //游戏的对称中心计算方法
		center_y = h / 2 + (17 / 1920) * h //游戏的对称中心计算方法
		if piece_x > center_x: //棋子在游戏对称中心的右边
			board_y = round((25.5 / 43.5) * (board_x - center_x) + center_y)
			/*
			25.5/43.5--->等于tan(30).
			由游戏的对称中心点做一条30度的辅助线,与x=board_x的交点即为棋盘的中心位置.
			*/
			delta_piece_y = piece_y - round((25.5 / 43.5) * (piece_x - center_x) + center_y)
			/*
			微调值计算
			*/
		else:
			board_y = round(-(25.5 / 43.5) * (board_x - center_x) + center_y)
			delta_piece_y = piece_y - round(-(25.5 / 43.5) * (piece_x - center_x) + center_y)

		if not all((board_x, board_y)):
			return 0, 0, 0, 0, 0
		return piece_x, piece_y, board_x, board_y, delta_piece_y

	def yes_or_no():
		'''
		检查是否已经为启动程序做好准备
		'''
		while True: //死循环
			yes_or_no = str(input('请确保手机打开了ADB并连接了电脑, '
								'然后打开跳一跳并【开始游戏】后在使用本程序,确定开始? [y/n]:'))
			if yes_or_no == 'y':
				break;
			elif yes_or_no == 'n':
				print('谢谢使用', end='') //end='':表示末尾不换行,加一个空格.
				exit(0) //exit(0):无错误退出程序. exit(1):有错误退出程序
			else:
				print('请重新输入')

	def main():
		'''
		main函数
		'''
		print('程序版本号:{}'.format(VERSION))
		print('激活窗口并按Ctrl+C组合键退出')
		debug.dump_device_info()
		screenshot.check_screenshot()

		i, next_rest, next_rest_time = (0, random.randrange(3, 10),
										random.randrange(5, 10))

		while True:
			im = screenshot.pull_screenshot() //抓到截图
			//从截取的图片中获取棋子和board的位置
			piece_x, piece_y, board_x, board_y, delta_piece_y = find_piece_and_board(im)
			ts = int(time.time()) //得到当前时间(1970到现在经过的秒数)
			print(ts, piece_x, piece_y, board_x, board_y)
			//设置点击的位置
			set_button_position(im)
			//准备开始跳跃
			jump(math.sqrt((board_x - piece_x) ** 2 + (board_y - piece_y) ** 2), delta_piece_y)
			if DEBUG_SWITH: //debug开关打开
				debug.save_debug_screenshot(ts, im, piece_x, piece_y, board_x, board_y)

				debug.backup_screenshot(ts)
			im.close()
			i += 1
			if i == next_rest: //休息
				print('已经连续打了 {} 下,休息 {} 秒'.format(i, next_rest_time))
				for j in range(next_rest_time):
					sys.stdout.write('\r程序将在 {} 秒后继续'.format(next_rest_time - j))
					sys.stdout.flush()
					time.sleep(1)
				print('\n继续')
				i, next_rest, next_rest_time = (0, random.randrange(30, 100),
											random.randrange(10, 16))
			//为了保证截图的稳定性,多延迟一会
			time.sleep(random.uniform(1.2, 1.4)) //取1.2~1.4之间的随机浮点数

	if __name__ == '__main__':
		try:
			yes_or_no()
			main()
		except KeyboardInterrupt: //捕获"Ctrl+c"中断程序的异常
			adb.run('kill-server') //执行adb kill-server:终止adb服务
			print('\n谢谢使用', end='')
			exit(0)

### 2. Train Tickets Query Tool



