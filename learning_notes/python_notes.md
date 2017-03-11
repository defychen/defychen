# Python

## Python 入门

python主要是用来编写应用程序的高级编程语言.

python是解释型语言,执行时一行一行的翻译成机器码,翻译过程非常耗时，因此运行速度慢.C语言是在运行前就已经被编译成机器码,因此运行快.

编译型语言直接发布编译后的机器码(e.g. windows的exe程序);解释性语言必须将源码发布出去.

**进入和退出Python:**

	$ python /*在linux中直接敲击命令python*/
	>>> exit() /*>>>:表明进入python交互式环境.exit():退出python交互式环境*/

*python使用最广的解释器是CPython.*

**输出打印:**

	>>> print 'hello, world' /*输出"hello,world"*/

**运行Python文件(".py"后缀)**

	#!/usr/bin/python	/*在.py文件开头指定使用python解析脚本*/
	$ chmod a+x xxx.py	/*为.py文件增加执行权限(一般注意查看其他脚本的权限,保持一致)*/
	./xxx.py	/*执行*/

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