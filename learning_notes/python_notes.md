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

	d = {'Michael':95, 'Bob':75, 'Tracy':85}
	d['Michael']	#会得到:95



***
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