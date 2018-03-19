# Python

## 1、Python 入门

python主要是用来编写应用程序的高级编程语言.

python是解释型语言,执行时一行一行的翻译成机器码,翻译过程非常耗时，因此运行速度慢.C语言是在运行前就已经被编译成机器码,因此运行快.

编译型语言直接发布编译后的机器码(e.g. windows的exe程序);解释性语言必须将源码发布出去.

**进入和退出Python:**

	$ python /*在linux中直接敲击命令python*/
	>>> exit() /*>>>:表明进入python交互式环境.exit():退出python交互式环境*/

python使用最广的解释器是CPython.

**运行Python文件(".py"后缀)**

	#!/usr/bin/python	/*在.py文件开头指定使用python解析脚本*/
	$ chmod a+x xxx.py	/*为.py文件增加执行权限(一般注意查看其他脚本的权限,保持一致)*/
	./xxx.py	/*执行*/

**输入:raw_input()函数**

	name = raw_input('Please enter your name:')	#提示输入,输入的信息会放到name这一变量中
	print 'hello,', name						#打印出"hello, ...(用户输入的信息)"

raw_input()读取的内容永远是以字符串的形式返回,如果需要整数必须:

	birth = int(raw_input('Please input your date of birth'))	
	#出生日期是一个整数,需要使用int进行转换,转换为整型

**输出打印:**

	>>> print 'hello, world' /*输出"hello,world"*/
	>>> print 'The quick brown fox', 'jumps over', 'the lazy dog'
	# 其输出为The quick brown fox jumps over the lazy dog(","会输出空格,但是会忽略","后面的空格)
***

## 2、Python基础

Python的注释以"#"开头;以":"结尾时,缩进的语句视为代码块.

python使用"\n"换行,还可以用'''...'''表示多行内容(另起一行就是输出另一行)

	>>>print '''line1 
	...line2
	...line3'''		#交互式命令行中输入
	# xxx.py文件中表示为
	print '''line1					两次输出为:line1
	line2									 :line2
	line3'''								 :line3	#总共3行

### 2.1 数据类型和变量

**布尔值**

Python用"True、Flase"表示布尔值,也用"and/or/not"做与、或、非运算.

	True and False
	True or True
	not False

**None(空值)**

None(空值)在Python是一个特殊的值.None不是0(0是有意义的),而是一个特殊的值.

Python属于动态语言(即同一个变量可以被反复的赋值).

**变量在计算机内存中的表示**

a = 'ABC'

1)在内存中创建'ABC'字符串;

2)在内存中创建一个名为"a"的变量,并把它指向'ABC'

	a = 'ABC'
	b = a		#创建一个变量b,指向a指向的字符串'ABC'
	a = 'XYZ'
	print b		#b打印出ABC

Python中常量一般用全部大写字母的变量名表示:
	
	PI = 3.1415926

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

***

## 3、其他一些常用的学习

### 3.1 list和tuple

**list**

list:列表---Python内置的一种数据类型,属于一种有序的集合,可以随时添加/删除其中元素.

	classmates = ['Michael', 'Bob', 'Tracy']	#list变量并初始化
	print classmates			#打印输出list变量
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
	L[0:3]	/*取到3截止,但是不包括3位置的元素*/
	L[:3]	/*从索引0开始,到3截止.包括L[0],L[1],L[2]三个元素*/
	L[-2:]	/*取倒数元素,L[-2], L[-1]---倒数第一个元素*/
	L[-2:-1]	/*取L[-2],到-1截止(不包括-1这个元素).因此就取一个*/

实例
	
	L=range(99)	/*L=[0, 1, 2,...,99]---0~99的数列*/
	L[:10]		/*取list L中的前10个数(0~9)*/
	L[-10:]		/*取后10个数*/
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
	d['Michael']	#会得到:95
	d['Adam'] = 67		/*通过key放入"key-value"*/
	d['Adam'] = 88		/*多次对一个key放入value,后面的会冲掉前面的值*/
	d['Adam']		#会得到88,而非67
	d['Thomas']		#key不存在,dict报错.显示为"KeyError: 'Thomas'"

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

	s = set([1, 2, 3])	/*相比较tuple,增加了"set"标识符,中间为一个"list"*/
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
	for key in d:	/*编译dict中的key*/
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
	[m + n for m in 'ABC' for n in 'XYZ']	/*两个str组合的全排列*/

列出当前目录下所有文件和目录名

	import os	/*导入os模块*/
	[d for d in os.listdir('.')]	/*os.listdir:列出文件和目录,('.')---表示当前目录*/

把list所有字符串中的字符变成小写

	L = ['Hello', 'World', 'IBM', 'Apple']
	[s.lower() for s in L]	/*s.lower():将str字符串的字符变成小写*/
	//list中包含字符串和整数
	L = ['Hello', 'World', 18, 'IBM', 'Apple']
	[s.lower() for s in L if isinstance(s, str)]	/*增加判断是否为字符串*/
	isinstance(s, str)	//判断s是否为字符串.True:表示为字符串;False:不是字符串.
	
***

## 4、函数

### 4.1 调用函数

查看内置函数的帮助信息

	help(abs)	/*查看求绝对值函数的帮助信息*/

**abs()绝对值函数**

	abs(100)	/*结果为100*/
	abs(-20)		/*结果为20*/
	abs(12.34)	/*结果为12.34*/
	//错误时信息提示
	abs(1, 2)	
	/*TypeError: abs() takes exactly one argument (2 given).abs()接受一个参数,但是给出了两个*/
	abs('a')
	/*TypeError: bad operand type for abs(). 'str'.str是错误的运算(即参数)类型*/

**cmp(x, y)比较函数**

	cmp(1, 2)	/*para1 < para2, 返回"-1"*/
	cmp(2, 1)	/*para1 > para2, 返回"1"*/
	cmp(3, 3)	/*para1 = para2, 返回"0"*/

**数据类型转换**

	int('123')		/*字符串转换为整型,ret为123*/
	int(12.34)		/*浮点转换为整型,ret为12*/
	float('12.34')	/*字符串转换为浮点,ret为12.34*/
	str(1.23)		/*浮点转换为字符串,ret为'1.23'*/
	unicode(100)	/*整型转换为unicode,ret为u'100'---unicode编码的100*/
	bool(1)			/*非零(或空)转换为bool,ret为True*/
	boot('')		/*空转换为bool,ret为False*/

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

**空函数**

	def nop():
		pass	/*pass作为占位符,定义空函数.空函数必须有"pass",常用在定义一个函数的框架.*/

**参数检查**

自定义的函数一般需要做参数检查处理.

	def my_abs(x):
		if not isinstance(x, (int, float)):		/*只允许整数和浮点数*/
			raise TypeError('bad operand type')	/*抛出错误*/
		if x >= 0:
			return x
		else:
			return -x

**斐波拉切数列的函数实现**

	def fib(max):
		n, a, b = 0, 1, 1	/*赋值,会对应的赋值*/
		while n < max:	/*while循环*/
			print a
			a, b = b, a + b	/*赋值,会对应的赋值*/
			n = n + 1

**返回多个值**

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

reduce()函数接收两个参数.一个函数,一个list.函数从list中取两个参数计算,得到返回值和list中的第三个参数作为函数的参数继续参与计算.直到最后得到返回值.

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

	// str2int函数
	def str2int(s):
		def fn(x, y):
			return x * 10 + y
		def char2num(s):
			return {'0':0, '1':1, '2':2, '3':3, '4':4, '5':5, '6':6, '7':7, '8':8, '9':9}[s]
		return reduce(fn, map(char2num, s))

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
	def reversed_cmp(x, y):
		if x > y:
			return -1
		if x < y:
			return 1
		return 0
	sorted([36, 5, 12, 9, 21], reversed_cmp)	//结果为:[36, 21, 12, 9, 5]
	//list在前,函数在后.与前面的不一样

字符串排序

	sorted(['bob', 'about', 'Zoo', 'Credit'])	//结果为:['Credit', 'Zoo', 'about', 'bob']
		//默认按着ASCII的大小比较,有大小写之分
	//忽略大小写
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

	try:	//Python IO的两套库"cStringIO"和"StringIO",接口和功能相同.cStringIO用c写的,速度快.
		import cStringIO as StringIO	//优先导入cStringIO作为StringIO,"as"相当于别名
	except ImportError:	//导入失败会捕获到ImportError
		import StringIO	//失败再导入StringIO.后面的代码均可以用StringIO正常工作

	//example
	try:
		import json	#python >= 2.6	//注释"#",2.6中有json的库
	except ImportError:
		import simplejson as json #python <= 2.5	//2.6之前独立第三方库

### 6.3 作用域

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

**模块搜索路径**

	//搜索路径在sys模块的path变量中
	>>>import sys
	>>>sys.path    //为一个list
	//添加自己的搜索目录, method 1
	>>>import sys
	>>>sys.path.append('pathname')    //运行时修改,结束后失效
	//method 2
	设置环境变量PYTHONPATH---不是很清楚
***

## 7、 面向对象编程

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

	import types	//导入types模块
	type('abc') == types.StringType	//判断是否为字符型,是返回Ture
	type([]) == types.ListType		//判断是否为list,是返回Ture
	type(str) == types.TypeType		//所有类型都是TypeType

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

**__str\__:用于打印类实例时显示的好看**

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
		def __str__(self):
			print 'Student object (name: %s)' % self.name
	//打印类实例
	>>>print Student('Michael')   //会得到"Student object (name: Michael)"

	//直接敲变量还是会不好看
	>>>s = Student('Michael')
	>>>s       //依然会不好看"<__main__.Student object at 109afb190>"
	//解决:在类定义最后加上下面一句即可
	__repr__ = __str__		//为调试服务的

**__iter\__:用于类的"for...in"循环,类似list或tuple**

	//斐波那契数列类实现,可以作用于for循环
	class Fib(object):
		def __init__(self):
			self.a, self.b = 0, 1	//初始化头两个数
		def __iter__(self):
			return self			//定义迭代对象.实例本身为迭代对象,故返回自己
		def next(self):			//Python中的for循环会不断调用迭代对象的next()方法拿到循环的下一个值
			self.a, self.b = self.b, self.a + self.b	//计算下一个值
			if self.a > 100000:	//循环退出条件
				raise StopIteration()	//抛出"StopIteration;"---终止循环.
					//以前的记录"StopIteration();---后面有分号".但是测试过有没有都正确.没有";"比较和常规.
			return self.a	//返回下一个值

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
		//1)此处除"0"错误,会直接跳到except,后面语句不执行; 2)如果0改成2,后面的语句会执行,并且会跳过except直接执行finally
		print 'result: ', r
	except ZeroDivisionError, e:	//捕获除0错误. "e":保存错误信息---自动保存的
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
		print 'ValueError: ', e
	except ZeroDivisionError, e:	//除0错误
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
		assert n != 0, 'n is zero!'	//1)assert为真,自动跳过该行语句继续执行; 2)为假,抛出"AssertionError"错误并退出
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

默认情况下,logging将日志打印到屏幕,日志级别是WARNING.级别大小:CRITICAL>ERROR>WARNING>INFO>DEBUG>NOTSET.

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
***

## 10 os模块

**os模块**

	import os	//导入os模块
	os.name		//操作系统名字(如果为posix---说明系统是linux/Unix/Mac os X; 如果为nt则是windows)
	os.uname()	//获取系统详细信息,windows上没有
	os.environ	//查看操作系统定义的环境变量,为一个dict
	os.getenv('PATH')	//获取环境变量调用"os.getenv('导出的环境变量')"函数
	os.rename('test.txt', 'test.py')	//文件重命名
	os.remove('test.py')				//删除文件

**os.path相关函数**

	import os.path
	os.path.abspath('.')	//列出当前目录的绝对路径
	//在某个目录下创建新目录步骤:
	1)os.path.join('/user/defy', 'testdir')		
	//先将新目录的完整路径表示出来.第一个通常为绝对路径(也可以用相对路径).两个路径会合成为一个
	2)os.mkdir('/user/defy/testdir')			//创建一个目录
	os.rmdir('/user/defy/testdir')				//删除一个目录

	//拆分路径
	os.path.split('/user/defy/testdir/file.txt')
	/*拆分得到('/user/defy/testdir', '.file.txt')---最后一级为目录或文件名*/
	//得到扩展名
	os.path.splitext('/user/defy/testdir/file.txt')
	/*得到('/user/defy/testdir/file', '.txt')---最后一级为扩展名*/

实例---列出当前目录下的所有目录或所有.py文件

	[x for x in os.listdir('.') if os.path.isdir(x)]	//列出所有目录
	
	[x for x in os.listdir('.') if os.path.isfile(x) and os.path.splitext(x)[1] == '.py']
	//列出所有的.py文件---os.path.split(x)返回的为tuple,因此"os.path.splitext(x)[1]"相当于取后面的扩展名

**os.popen函数**

os.popen(cmd):为一个命令(cmd)执行结果打开一个管道.再调用.read()方法即可将内容独处.

	b = os.popen('ls') //为ls命令执行结果打开一个管道,并返回给b
	print b.read() //可以将"ls"命令执行结果从b这个管道中读出.

***

## 11 序列化及JSON

**略**

***

## 12 进程和线程

### 12.1 多进程(multiprocessing)

**1)fork方法---windows没有**

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

	if __name__ == '__main__':	//直接运行"./hello.py",python中的特殊变量"__name__"就会置为"__main__"
								//在其他地方导入时,就会判断失败,用于单独测试某模块的正确性
		print 'Parent process %s.' % os.getpid()
		p = Process(target=run_proc, args=('test',))	//创建一个进程实例.target:指定子进程需要执行的函数
											//args:子进程执行的函数参数,是一个tuple.只有一个时需要加逗号('test',)
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
		time.sleep(random.random() * 3)		//random.random()---得到随机值(0~1); time.sleep()进程睡眠
		end = time.time()
		print 'Task %s runs %0.2f seconds.' % (name, (end - start))	//得到运行时间

	if __name__ == '__main__':
		print 'Parent process %s.' % os.getpid()
		p = Pool()		//创建一个进程池p
		for i in range(5):
			p.apply_async(long_time_task, args=(i, ))	//进程池指定运行函数使用"p.apply_async(func, args)"
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
			value = q.get(True)		//参数True会导致:如果队列中没有数据使调用线程暂停,直至有数据会继续
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
	thread MainThread is running...		//主线程名字"MainThread"
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
		#先存后取,结果为不便.(此处仍为0)
		global balance	//表明为全局变量
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
	print balance

**操作系统出现硬盘狂响,点窗口无反应是因为开的任务(进程/线程)过多,操作系统忙着切换任务,此时根本没有时间去执行任务.**

***

## 13 摘要算法(SHA/MD5)

Python的hashlib提供了常用的摘要算法(MD5, SHA1等).

摘要算法:又称哈希算法、散列算法.通过一个函数,将任意长度的数据转换成一个长度固定的16进制表示的字符串.

目的:摘要算法通过摘要函数f()对任意长度的数据data计算出固定长度的摘要digest.目的是为了发现源数据是否被篡改过.摘要函数f(data)是一个单向函数,计算f(data)很容易,但通过digest反推data却很难.

实例:---计算一个字符串的MD5值.

	import hashlib
	md5 = hashlib.md5()		//得到hashlib库中的md5函数
	md5.update('how to use md5 in python hashlib?')		//md5.update(''):将字符串写入md5的一段buffer---添加字符串
	print md5.hexdigest()		//md5.hexdigest()---开始计算得到md5值

	//结果为:d26a53750bc40b38b65a520292f69306

分块多次调用update(),最终的md5值都是一样的:
	import hashlib
	md5 = hashlib.md5()
	md5.update('how to use md5 in ')
	md5.update('python hashlib?')
	print md5.hexdigest()

**MD5:最常见的摘要算法,速度快,生成的长度是32个16进制字符串(32*4 = 128 bit = 16 byte).**

实例---SHA1调用

	import hashlib
	sha1 = hashlib.sha1()	//得到hashlib库中的sha1函数
	sha1.update('how to use sha1 in ')
	sha1.update('python hashlib?')
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
	s.connect(('www.sina.com.cn', 80))	//IP地址+端口号.---IP地址可由域名"www.sina.com.cn"自动转换
	//端口号分类:80 web服务标准端口;25 SMTP服务端口;21 FTP服务端口.端口号<1024---Internet标准服务端口;>1024可以任意使用.
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
	//1)IP地址:服务器有多块网卡,每块网卡对应一个IP地址.bind中的IP地址区域填写"0.0.0.0"表示本服务器所有的IP地址.
		"127.0.0.1"表示本机地址.此时客户端必须同时在本机运行才能连接上,外部计算机无法连接.
	//2)端口:端口号<1024需要管理员权限才能绑定.>1024可以任意绑定

3)监听端口:
	
	s.listen(5)	//参数表示最大的连接数量,为设置socket的一种属性.经过这个设置后socket就可以等待客户端的连接了.
	print 'Waiting for connection...'

4)接收客户端连接,并创建线程处理客户端连接:

	while True:		//使用死循环来接收客户端连接
		sock, addr = s.accept()		//s.accept()等待并返回一个客户端连接.
		//sock:表示一个客户端的socket; addr:包含客户端的IP地址(此处为127.0.0.1,与服务器相同)和客户端的端口
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
	#!/usr/bin/python	//指定python程序的位置,此时可以直接"./echo_server.py"调用,否则必须"python echo_server.py"
	import socket, time, threading	//会使用socket,time,threading等模块
	
	def tcplink(sock, addr):
		print 'Accept a new connection from %s:%s...' % addr
		sock.send('Welcome')
		while True:
			data = sock.recv(1024)
			time.sleep(1)
			if data == 'exit' or not data:
				break
			sock.send('Hello, %s' % data)
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
	print s.recv(1024)
	for data in ['Defy', 'Tracy', 'Sarah']:
		#send data
		s.send(data)
		print s.recv(1024)
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
		data, addr = s.recvfrom(1024)	//服务器端接收数据使用"s.recvfrom(1024)"
		print 'Received from %s:%s...' % addr
		s.sendto('Hello, %s!' % data, addr)	//s.sendto(data, addr).参数1:需要发送的数据;参数2:IP+端口

	//客户端:udp_client.py
	#!/usr/bin/python
	import socket, time
	s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
	for data in ['Defy', 'Tracy', 'Sarah']:
		#send data to server
		s.sendto(data, ('127.0.0.1', 9999))
		time.sleep(1)	//睡眠1s
		#receive data
		print s.recv(1024)	//客户端接收数据使用"s.recv(1024)"
	s.close()
	
***

## 15 常用的第三方模块

### 15.1 PIL模块

pip:python中安装第三方模块的包管理工具,通过它,就能安装编程时常用的一些模块.

PIL:Python Imaging Library.是Python平台的图像处理标准库.

Pillow:基于PIL,处理Python 3.x的图形图像库.PIL只能处理到Python 2.x, Pillow模块能处理到Python 3.x.

#### 15.1.1 Python、PIL、Pillow相关模块的安装

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

#### 15.1.2 PIL模块的使用

**1.操作图像**

1.图像缩放操作

	#!/usr/bin/python
	#-*- coding: utf-8 -*-
	from PIL import Image
	
	#打开一个图像文件
	im = Image.open('/users/defy/test.jpg') //绝对路径,尝试过相对路径会报错
	#获得图像尺寸
	w, h = im.size //得到图像的宽,高
	im.thumbnail(w//2, h//2) //"//"在python 3.x中表示整除; "/":表示浮点除法
		//Image.thumbnail:按照宽、高对图形进行缩略.在缩略时,保持图片的宽高比例.
	#保存图片
	im.save('/user/defy/thumbnai.jpg', 'jpeg')
		//para1:文件名; para2:格式. 因为xxx.jpg就是jpeg格式,

2.图像模糊效果

	#!/usr/bin/python
	#-*- coding: utf-8 -*-
	from PIL import Image, ImageFilter
	im2 = Image.open('/user/defy/test.jpg')
	im2 = im.filter(ImageFilter.BLUR)
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
		return chr(random.randint(65, 90)) //random.randint(a, b):生成a~b的随机数
		//chr:数字转换字母函数.此处将ASCII码(65~90)转换为大写字母(A~Z)
	
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
	image = image.filter(ImageFilter.BLUR)
	image.save('/usr/defychen/code.jpg', 'jpeg')

### 15.2 subprocess模块

**1.subprocess模块的Popen类的实例介绍**

subprocess用于创建一个新的进程执行另外的程序,并与其进行通信.获取标准的输入、标准输出、标准错误以及返回码等.

subprocess模块中定义了一个Popen类,用于创建子进程.

	res = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
	/*
		创建一个Popen类的对象->res
		cmd:创建的子进程需要执行的命令/程序.(e.g.['ls -al'], ['ipconfig', '-all'], 
			或者某个可执行程序)
		subprocess.PIPE:表示透过PIPE与子进程通信(输入,输出或者标准错误输出)
		subprocess.STDOUT:此处将标准错误直接通过标准输出流进行输出.
	*/

**2.Popen类的方法及属性**

1.Popen.pid:获取创建的子进程的ID

2.Popen.returncode:获取子进程的返回值.如果进行未结束,将返回None.

3.Popen.communicate(input=None):获取output(output存在在一个tuple中),包括stdout和stderr.input为stdin,一般为None即可.

	sout, serr = res.communicate()

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

### 15.3 platform模块

platform模块用来访问平台的相关属性

	import platform
	
	platform.machine() //返回平台架构(e.g.'x86_64')
	platform.node() //返回主机名(e.g.zhsa01)
	platform.platform() //返回系统版本(e.g.Linux-3.2.0-23-generic-...)
	platform.processor() //返回处理器名称
	platform.system() //返回系统名称(e.g."Windows"/"Linux")

***

## 16. Python中常用的函数

### 16.1 enumerate函数

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


**eval()函数**

	params = ['open_keys_test', 'check_set_format', 'check_kl_algo']
	for param in params:	#从list中提取出每一个元素
		if eval('%s(obj, devices)' % param):	#提取出来的param替换s,构成调用函数
			# e.g. open_keys_test(obj, devices)

*eval()函数返回值:成功返回0;失败返回非0*

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

	class auto_adb():
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
		from common.auto_adb impot auto_adb
	except Exception as ex: //捕获异常(Exception当作ex,用于输出)
		print(ex)
		print('Please run the script in the root directory')
		print('Please check whether the common folder exists under the root directory')
		exit(1)
	adb = auto_adb()
	VERSION = "1.1.4"

	DEBUG_SWITCH = True //for debug
	adb.test_device()