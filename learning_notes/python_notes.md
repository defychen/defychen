# Python

## 1、Python 入门

python主要是用来编写应用程序的高级编程语言.

python是解释型语言,执行时一行一行的翻译成机器码,翻译过程非常耗时，因此运行速度慢.C语言是在运行前就已经被编译成机器码,因此运行快.

编译型语言直接发布编译后的机器码(e.g. windows的exe程序);解释性语言必须将源码发布出去.

**进入和退出Python:**

	$ python /*在linux中直接敲击命令python*/
	>>> exit() /*>>>:表明进入python交互式环境.exit():退出python交互式环境*/

*python使用最广的解释器是CPython.*

**运行Python文件(".py"后缀)**

	#!/usr/bin/python	/*在.py文件开头指定使用python解析脚本*/
	$ chmod a+x xxx.py	/*为.py文件增加执行权限(一般注意查看其他脚本的权限,保持一致)*/
	./xxx.py	/*执行*/

**输入:raw_input()函数**

	name = raw_input('Please enter your name:')	#提示输入,输入的信息会放到name这一变量中
	print 'hello,', name						#打印出"hello, ...(用户输入的信息)"

raw_input()读取的内容永远是以字符串的形式返回,如果需要整数必须:

	birth = int(raw_input('Please input your date of birth'))	
	#出生日期是一个整数,需要使用int进行转换为整型

**输出打印:**

	>>> print 'hello, world' /*输出"hello,world"*/
	>>> print 'The quick brown fox', 'jumps over', 'the lazy dog'
	# 其输出为The quick brown fox jumps over the lazy dog(","会输出空格,但是会忽略","后面的空格)
***
## 2、Python基础

Pathon的注释以"#"开头;以":"结尾时,缩进的语句视为代码块.

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

**字母转换数字函数:ord()和数字转换字母函数:chr()**

	>>>ord('A')
	65			#将"A"转换为数字65
	>>>chr(65)
	'A'			#将65转换为字母A

Unicode输出中文:
	
	print u'中文'	#将会输出"中文"

**Unicode编码转换为UTF-8编码:**

	u'ABC'.encode('utf-8')	#Unicode编码的"ABC"转换为UTF-8编码的"ABC"

**UTF-8编码转换为Unicode编码**

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
	t = (1,)	#定义只有一个元素的tuple,必须写完后加","(e.g. t = (1)默认会认为是t = 1---按小括号计算)
	/*特例*/
	t = ('a', 'b', ['A', 'B'])	#第三个元素为list，因此可以对第三个元素进行重新赋值
	t[2][0] = 'X'	#tuple指向不便,仍然为list.但是list自身中的元素可以改变
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
	L[-2:-1]	/*取L[-2],到-1截止.因此就取一个*/

实例
	
	L=range(99)	/*L=[0, 1, 2,...,99]---0~99的数列*/
	L[:10]		/*取list L中的前10个数*/
	L[-10:]		/*取后10个数*/
	L[10:20]	/*前11~20个数*/
	L[:10:2]	/*前10个数,每两个取一个*/
	L[::5]		/*所有数,每5个取一个*/
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

*非零、非空字符串、非空list均为True*

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
a
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
	s = set([1, 1, 2, 2, 3, 3])	/*去掉重复元素,因此最后显示结果为"set([1, 2, 3])"*/
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

### 3.4 迭代

list/tuple/dict/str(字符串)等可迭代对象都可以用"for...in"来实现遍历,成这种遍历为迭代(Iteration).

	//list
	names = ['Michael', 'Tracy', 'Bob']
	for name in names:
		print 'name: %s' % name
	//tuple
	words = ('a', 'b', 'c')
	for word in words:
		print 'word: %s' % word	/*如果不行:print 'word:', word*/
	//dict
	d = ['a':1, 'b':2, 'c':3]
	for key in d:	/*判断key是否在dict中*/
		print key	/*打印key*/
		print d['key']	/*打印value*/
	/*默认迭代"key"*/
	for vlaue in d.itervalues():	/*迭代value*/
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
		for n < max:
			print a
			a, b = b, a + b	/*赋值,会对应的赋值*/
			n = n + 1

**返回多个值**

其实为一个tuple,按位置赋给对应的变量.

	import path	/*引入path module*/
	
	def move(x, y, step, angle=0):	/*angle带默认参数,放于最后*/
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

默认参数使用"list"的默认出现问题,因此尽量使用不可变对象(None, int，str)

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

**可变参数(list/tuple)**

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
fand
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
		return reduce(lambda x, y: x * 10 + y, map(char2num, s))---lambda para : expression

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

## 6、模块

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

	#!/usr/bin/python	//制定可执行程序路径
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

	try:	//Python IO的两套库"cStringIO"和"StringIO",接口和功能相同.cStringIO用c下的,速度快.
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
	
	def greeting(name):	//公开greeting函数.借口公开,细节隐藏.
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

		@score.setter	//"@xxx.setter"相当于"xxx.setter",将set方法变成属性
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
		@property	//相当于get_birth,只读属性
		def birth(self):
			return self.__birth
		@birth.setter	//相当于birth_setter,写属性
		def birth(self, value)
			self.__birth = value
		@property
		def age(self):	//相当于get_age,只读属性
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

## Python logging模块

默认情况下,logging将日志打印到屏幕,日志级别是WARNING.级别大小:CRITICAL>ERROR>WARNING>INFO>DEBUG>NOTSET.

**通过logging.basicConfig函数对logging输出进行相关配置**

*针对logging.info('...')不能打印的情况,调整打印级别*

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

**eval()函数**

	params = ['open_keys_test', 'check_set_format', 'check_kl_algo']
	for param in params:	#从list中提取出每一个元素
		if eval('%s(obj, devices)' % param):	#提取出来的param替换s,构成调用函数
			# e.g. open_keys_test(obj, devices)

*eval()函数返回值:成功返回0;失败返回非0*

## Python类及实例的应用

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