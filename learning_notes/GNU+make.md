# Makefile Usage

# 1. Makefile Introduction

## Chapter 1 概述

### 1.1 Make基本知识

通常,一个高级语言的源文件都对应一个目标文件,linux中默认的后缀为".o".

	链接:将多个.o文件,或者.o和库文件链接成可执行程序.linux下的可执行文件的格式为"ELF"格式.
		链接器不会检查函数所在的源文件,只检查所有".o"文件中定义的符号.将".o"文件中使用的函数和其他".o"
		或库文件中相关符号进行合并,对文件中所有的符号进行重排,并链接系统相关文件(e.g.程序启动文件等),最
		终生可执行程序.<font size=4>"ld"</font>是GNU的链接器.
	静态库:文档文件(Archive File),多个.o的集合,后缀".a",使用"ar"工具维护和管理.
	共享库:多个.o的集合,这些".o"文件由编译器按照一种特殊的方式生成共享库.共享库的文件格式为"ELF",
		因此具备可执行条件.共享库中各个成员的地址(变量引用和函数调用)均为相对地址.

### 1.2 GNU make介绍

make通过比较对应文件(规则的目标和依赖)的最后修改时间,来决定哪些文件需要更新.在make读取Makefile以后会建立一个编译过程的描述数据库,该数据库记录了所有各个文件之间的相互关系以及他们的关系描述.对于需要更新的文件make就执行数据库中所记录的相应命令来重建它,不需要更新的make什么也不做.

#### 1.2.1 Makefile规则

Makefile规则描述如下:

	target...:prerequisites...
		command
	target:规则的目标.可以是.o文件,也可以是最后的可执行程序文件.
		对于只有动作而没有依赖的目标称之为"伪目标"phony targets(e.g.clean).
	prerequistites:规则的依赖.生成规则目标所需要的文件名列表.
	comman:规则的命令行.
			1.一个规则可以有多个命令行,每一条命令占一行;
			2.每一个命令行必须以"Tab"键开始."Tab"键告诉make此行是一个命令行.

#### 1.2.2 简单示例

	$sample Makefile
	edit : main.o kbd.o command.o display.o \	//对于较长行使用反斜线(\)分解为多行.且反斜线之后不能有空格.
			insert.o search.o files.o
		cc -o edit main.o kbd.o ... file.o
	main.o : main.c defs.h
		cc -c main.c
	kbd.o : kbd.c defs.h command.h
		cc -c kbd.c
	...
	PS:某个头文件在上一次执行make后被修改,所有包含该头文件的C源文件在本次执行make都会被重新编译.

#### 1.2.3 指定变量

一般使用变量"obj/objs/ojects"等来表示目标中的依赖列表

	objs = main.o kbd.o command.o display.o \		//反斜线(\)之后无空格
		insert.o search.o files.o util.o
	edit : $(objs) //使用objs变量来表示依赖列表
		cc -o edit $(objs)	////使用objs变量来表示依赖列表
		...
	clean:
		rm edit $(objs)

#### 1.2.4 自动推导规则

在使用make编译.c源文件时,make本身存在一个默认的规则(使用"cc -c"来编译.c源文件),自动完成对.c文件的编译生成.o文件.

	#sample Makefile
	objs = main.o kbd.o command.o display.o \
		insert.o search.o files.o
	edit : $(objs) //使用objs变量来表示依赖列表
		cc -o edit $(objs)
	main.o : defs.h //make默认规则包含main.c的依赖,因此此处省略"main.c"的依赖
	kbd.o : defs.h command.h //此处省略"kbd.c"的依赖
	command.o : defs.h command.h //此处省略"command.c"的依赖
	...
	.PHONY : clean
	clean:
		rm edit $(objs)

#### 1.2.4 清除工作目录过程文件

清除编译过程中产生的临时文件的方法

	.PHONY : clean //通过".PHONY"将clean声明为伪目标.避免当存在一个"clean"文件时,clean规则的命令无法执行.
	clean:
		-rm edit $(objs)		//命令行之前使用"-",忽略"rm"的执行错误

***

## Chapter 2 Makefile总述

### 2.1 Makefile内容

**注释"#"**

	1.Makefile中"#"字符后的内容是注释(shell脚本也是这样);
	2.某行第一个非空字符为"#",则该行为注释行;
	3.注释行的结尾如果存在反斜线(\),则下一行也是注释行;
	4.Makefile中如果需要使用字符"#",应该使用"\#"将"#"转义.

**推荐使用Makefile命名**

	一个目录中比较重要的文件命名规则为首字母大写,e.g.:Makefile, README, Changelist

**make -f filename**

	make会自动搜索当前目录下的"GNU make/makefile/Makefile"等makefile文件.如果不存在,可以使用
	"make -f filename" --->将filename作为执行make时需要读取的makefile.

### 2.2 包含其他Makefile文件

**include**

	使用"include"包含其他文件,include会告诉make暂停读取当前的Makefile,转去读取include指定的文件,
	完成后再读取当前的Makefile,include应该书写为独立的一行.
		include filenames...	//finames可以使用通配符
	PS:
		1.include所在行可以使用一个或多个空格开始,但是不要使用tab键开始.
			tab开始的make会将此行作为一个命令行来处理.
		2.include和文件名之间,多个文件名之间使用空格/tab键隔开.行尾的空白字符会被忽略.

**include实例**

	当前目录存在3个.mk文件a.mk, b.mk, c.mk, $(bar)会被扩展为"bish bash"
	include foo *.mk $(bar) //"*.mk"使用了通配符,表示包含当前目录下所有.mk文件
	
	会被展开为:
	include foo a.mk b.mk c.mk bish bash

**-include和sinclude**

	1."-include"表示忽略由于包含文件不存在或无法创建时的错误提示.("-"忽略错误,继续执行)
		Makefile一般用"-include"来代替"include"
	2."sinclude"功能和"-include"一样,但是"sinclude"兼容性更好(GNU支持的方式),因此有时也用
		sinclude代替"-include".

### 2.3 变量MAKEFILE_LIST

	变量MAKEFILE_LIST包含了在make时需要读取的文件名.

### 2.4 变量取值
	
	= 	最基本的赋值
	:=	覆盖之前的值
	?=	如果没有被赋值就等于后面的值
	+=	添加后面的值

**实例**

	//编写一个测试的Makefile
	ifdef DEFINE_VRE
		VRE = "Hello World!"
	endif

	ifeq ($(OPT), define)
		VRE ?= "Hello World! First"
	endif

	ifeq ($(OPT), add)
		VRE += "Kelly"
	endif

	ifeq ($(OPT), recover)
		VRE := "Hello World! Again!"
	endif

	all:
		@echo $(VRE)

	//测试:
	make DEFINE_VRE=true OPT=define	//输出: Hello World!
		?= 因为已经被定义了,变量值不会有改变
	make DEFINE_VRE=true OPT=add	//输出: Hello World! Kelly!
		+= 添加后面的值,因此变量被改变了
	make DEFINE_VRE=true OPT=recover	//输出: Hello World! Again!
		:= 直接会覆盖前面的变量的值
	make DEFINE_VRE= OPT=define		//输出: Hello World! First!
		?= 因为之前没有定义,会赋值为"?="后面的值.
	make DEFINE_VRE= OPT=add		//输出: Kelly!
		+= 添加后面的值,之前变量的值为空
	make DEFINE_VRE= OPT=recover	//输出: Hello World! Again!
		:= 直接会覆盖前面的变量的值

**=和:=的区别**

	1."=":make会将整个Makefile展开后,再决定变量的值.变量的值会是整个Makefile中最后被指定的值.
		x = foo
		y = $(x)bar
		x = xyz
		y的值为"xyz bar",x的值为"xyz"
	2.":=":变量的值决定于变量在Makefile中的位置.
		x := foo
		y := $(x) bar
		x := xyz
		y的值为"foo bar",x的值为"xyz"

***

## Chapter 3 Makefile的规则

shell的使用:

	$#--->传递给脚本的参数个数
	$0--->脚本本身的名字
	$1--->传递给shell脚本的第一个参数
	$2--->传递给shell脚本的第二个参数
	$@--->传递给shell脚本的所有参数的列表
	$*--->以一个单字符串显示所有向脚本传递的参数,参数可以超过9个
	$$--->脚本运行的当前进程ID号
	$?--->显示最后命令的退出状态,0表示没有错误,其他表示有错误.

	/*实例dels.sh*/
	#!/bin/bash
	echo "parameter numbers: $#"
	echo "script name: $0"
	echo "first parameter: $1"
	echo "second parameter: $2"
	echo "argument: $@"
	echo "parameter list: $*"
	echo "process ID: $$"
	echo "exit status: $?"

	//执行:
	./dels.sh 1 2 3
	//结果:
	parameter numbers: 3
	script name: ./dels.sh
	first parameter: 1
	second parameter: 2
	argument: 1 2 3
	parameter list: 1 2 3
	process ID: 69577
	exit status: 0

### 3.1 依赖的类型

常规依赖:
	
	依赖更新后目标就会更新.

order-only依赖:

	1.终极目标不存在,order-only依赖会参与编译;
	2.终极目标存在,order-only依赖无论更新与否,对终极目标的更新不影响.
		此时终极目标的更新仅受常规依赖更新的影响.

常规依赖和order-only依赖通过管道符号"|"分割.

	targets : normal-prerequisites | order-only-prerequisites

实例:

	LIBS = libtest.a
	foo : foo.c | $(LIBS)	//常规依赖 | order-only依赖
		$(CC) $(CFLAGS) $< -o $@ $(LIBS)
	/*
	1.foo不存在,foo.c和$(LIBS)都会参与编译.最后生成foo
	2.foo存在，foo.c的更新会导致foo更新;但$(LIBS)(作为order-only依赖)的更新不会导致foo的更新.
	*/

### 3.2 通配符

Makefile中通配符(e.g.*.c:所有以".c"结尾的文件)只能出现在以下两种场合:

	1.用在规则的目标、依赖中,通配符会进行展开匹配;
		print:*.c //用在规则的依赖中.
			lpr -p $? //$?:此处表示依赖文件中被改变过的所有文件
			touch print
		//此处执行make print的结果是打印当前工作目录下所有的在上一次打印以后被修改过的".c"文件.
	2.用在规则的命令中,规则的命令是在shell中执行的;
		clean:
			rm -rf *.o //用在命令中
	3.其他的Makefile上下文是不可以使用通配符的.	
		objs = *.o	//该变量定义为:objs的值是*.o,非所有的.o文件列表.
		可以改成：objs = $(wildcard *.o) --->表示当前目录下所有的.o文件.

**函数$(wildcard pattern)**

$(wildcard *.c):获取当前工作目录下的所有.c文件,展开是以空格分开.

**$(patsubst %.c, %.o, $(wildcard *.c))分为两步**

1.获取当前工作目录下所有.c文件;

2.将所有.c文件后缀替换为.o.其中的"%"表示匹配一个或者多个字符(也是模式字符).

实例:

	#sample Makefile
	objs := $(patsubst %.c, %.o, $(wildcard *.c))
	foo : $(objs)
		$(CC) -o foo $(objs)

### 3.3 目录搜索

**1.VPATH**

VPATH:作为Makefile的内置变量,指定依赖文件的搜索路径.

实例

	//存在目录prom,prom有子目录src(含有文件sum.c memcp.c),其Makefile如下：

	LIBS = libtest.a
	VPATH = src		//VPATH:指定依赖文件的搜索路径为"src"
	libtest.a : sum.o memcp.o //依赖文件位于prom/src/sum.c; prom/src/memcp.c.
	$(AR) $(ARFLAGS) $@ @^

VPATH会存在下面的问题:

	1.如果prom、src等目录都不存在libtest.a,则会在当前目录(即prom下)创建目标libtest.a;
	2.如果src目录下已经存在libtest.a,则会有下面的问题:
		1.如果依赖文件sum.c和memcp.c都没有被更新,目标不会重建,目标目录不会发生变化;
		2.如果更新了sum.c/memcp.c,此时目标会被重建(在prom目录).此时在src和当前目录(prom)会
			存在两份目标libtest.a.但是只有prom目录下才是最新的.

**2.GPATH**

相当于global的PATH,也是Makefile的内置变量.可以避免VPATH存在的上面的在两个目录都存在目标的问题.

	LIBS = libtest.a
	GPATH = src		//GPATH:指定依赖文件的搜索路径"src",为global的.
	VPATH = src
	//上述的问题2.2会变成--->重建会在src目录下完成(而不是prom目录下).

**3.自动化变量**

	$^:所有的依赖文件
	$@:目标文件
	$<:依赖文件列表的第一个依赖文件

实例:

	main.out:main.o line1.o line2.o
		$(CC) -o $@ $^
		/*等价于:
		$(CC) -o main.out main.o line1.o line2.o
			$@:表示main.out
			$^:表示所有的依赖文件(main.o line1.o line2.o)
		*/
	main.o:main.c line1.h line2.h
		$(CC) -c $<
		/*等价于:
		$(CC) -c main.c
			$<:表示第一个依赖文件(main.c)
		*/
	line1.o:line1.c line1.h
		$(CC) -c $<
		/*等价于:
		$(CC) -c line1.c
			$<:表示第一个依赖文件(line1.c)
		*/
	line2.o:line2.c line2.h
		$(CC) -c $<
		/*等价于:
		$(CC) -c line2.c
			$<:表示第一个依赖文件(line2.c)
		*/

**4.库文件**
	
	foo:foo.c -lcurses	//优先会去搜索目录去寻找libcureses.so,如果没有才会去找libcureses.a
		$(CC) $^ -o $@

### 3.4 Makefile伪目标

伪目标:是为了执行一些命令而定义的一个目标.make 伪目标:其命令是肯定会被执行的.

清除一个中间文件的方法:

	clean:
		rm -rf *.o temp

但是如果在该目录下存在一个clean文件,此时输入"make clean".由于clean没有依赖被认为始终为最新的,因此不会执行clean之后的命令.因此需要显示声明"clean"为伪目标.

	.PHONY:clean //作为".PHONY"的依赖的都是伪目标.
	clean:
		rm -rf *.o temp
	//执行"make clean"时,其后的命令是肯定会被执行的.无论是否存在"clean"这个文件.

**伪目标特殊的应用---可以有自己的依赖**

	all:prog1 prog2 prog3		//all:伪目标.用于完成对依赖的更新.
	.PHONY:all
	prog1:prog1.o util.o
		$(CC) -o prog1 prog1.o util.o
	prog2:prog2.o
		$(CC) -o prog2 prog2.o
	prog3:prog3.o sort.o util.o
		$(CC) -o prog3 prog3.o sort.o util.o

在上述中,执行:

make--->默认会以第一个目标(all)作为终极目标.完成对所有依赖的编译.

make prog1,make prog2...--->完成对单个目标的编译.

**rm -f和-rf的比较**

	clean:
		rm -f(--force)		//防止缺少删除文件时报错而退出,使make clean过程失败
		-rm					//也可以防止出错,但是使用前面一种较好

**RM**

	make中内嵌一个隐含变量"RM",RM即为"rm -f".使用方法为"$(RM)".

### 3.5 强制目标(没有命令或者依赖的目标)

一个规则没有命令或者依赖,且它的目标不是一个存在的文件名.在执行时,该目标始终会被认为是最新的,因此叫做强制目标.而依赖强制目标的目标也总是会被更新.

这种方式一般用于非GNU版本的make中.

	clean:FORCE	//make会认为FORCE依赖被更新过,因此后面的cmd总会被执行
		$(RM) $(objs)
	FORCE:		//强制目标->无依赖也无命令,该目标也不是一个存在的文件名.

### 3.6 Makefile的特殊目标

**.PHONY--->常用**

目标".PHONY"的所有依赖都被是伪目标.

伪目标:当使用make命令行指定某伪目标时(e.g.make clean),该目标所定义的命令都会被无条件执行.

**.SUFFIXES--->用的比较少**

目标".SUFFIXES"的所有依赖指出了一系列在后缀规则中需要检查的后缀名(当前的make需要处理的后缀).

**.DEFAULT--->用的比较少**

一个文件作为某个规则的依赖,却不是另一个规则的目标时,Make无法重建此文件,就会执行".DEFAULT"所指定的cmd.

**.PRECIOUS--->用的比较少**

其依赖文件在命令的执行过程中被中断时,make不会删除它们.e.g. 原子操作过程不可被中断;目标文件仅仅是为了记录重建时间;防止其他麻烦.

**.SILENT--->现在被"make xxx -s/--silent"替换了**

目标".SLIENT"的依赖文件列表在创建时,不会打印创建这些文件所执行的一些cmd信息.(该目标无cmd)
	
	.SILENT: 	//没有依赖也没有命令(属于强制目标),在make的执行过程中不会打印任何cmd执行的信息.
	//执行时可以使用:make clean -s/--silent或者make --silent代替上述方式(不打印任何命令的执行信息).

### 3.7 模式规则

	files = foo.elc bar.o lose.o
	$(filter %.o, $(files)):%.o:%.c	//filter过滤出.o文件--->%.o:%.c:某个.o依赖于对应的.c文件
		$(CC) -c $(CFLAGS) $< -o $@
	$(filter %.elc, $(files)):%.elc:%.el	//最终为foo.elc:foo.el(当有较多的相似依赖比较有用)
		cmd

### 3.8 自动产生依赖

	# activate debug with V=1
	ifeq ($(V), 1)
	Q = 
	else
	Q = @	//如果Q没有定义为1,Q=@:表示不打印任何的编译信息
	endif

	# to generate dependancies between source code and compiled objects
	flags += -MD -MP

	/*
	-MD		Generate make dependencies and compile.
		--->生成文件的依赖关系文件(存放编译依赖信息.e.g.test.o: test.c test.h).
		依赖文件名为"-o"指定的文件,并添加".d"后缀.若没有指定,则输入的文件作为依赖文件名,
		并添加".d"后缀,同时继续进行后续的编译.此处为"test.d"
	-MP		Generate phony targets for all headers.
		--->依赖规则中的所有.h依赖项都会生成一个伪目标,该伪目标不依赖其他任何依赖项.该伪目标
		规则可以避免删除了对应的头文件而没有更新"Makefile"匹配新的依赖关系而导致make出错的情况.
	*/
	-include $(wildcard *.d)

	%.o: %.c
		@echo "Compiling $@" //前面的"@":表示不输出这一条信息"echo xxx"
		$(Q)$(CC) -c $(flags) $(cflags-y) -o $@ $<
		/*
			执行上述命令时,会产生得到自动依赖文件"*.d".
		*/

***

## Chapter 4 规则的命令

空行与空命令行:

	空行:不包含任何字符的一行.在执行规则时,空行将被忽略.
	空命令行:以"Tab"键开始而其后没有任何命令的行.

### 4.1 命令回显

	比如某规则中的命令为:
		target : prerequisites
			echo Start to compile xxxx
	在执行时会得到:
		echo Start to compile xxx //会将命令输出一遍,再执行命令.称为"回显".
			Start to compile xxx

命令行以"@"开始会取消回显.

	比如某规则中的命令为:
		target : prerequisites
			@echo Start to compile xxxx
	在执行时会得到:
			Start to compile xxx
	//不会将命令重新输出一遍,直接执行命令.

make -s/--silent或者目标为".SILENT":都将会取消所有回显.一般使用"@"来控制回显.

make -n/--just-print:

	make的命令行参数"-n/--just-print":
		显示所要执行的命令,不会去真正执行这些命令.常用语调试Makefile.

### 4.2 命令的执行

	1.Makefile中的同一行的多个命令属于一个shell命令行;
		多个命令之前用分号";"分隔.如果需要在不同行连接则";"之后再加上反斜线"\".
	2.书写在独立行的一条命令是一个独立的shell命令行,不同的行互不影响;
	3.cd改变目录只会对当前行产生影响,其后的命令行的工作目录仍然是当前目录(不会受之前的cd影响).
		1.错误的情况
		foo: bar/lose
			cd bar //进入到bar目录,仅在该行有效
			gobble lose > ../foo //想要承接上面的cd命令.但是实际是在当前目录执行.
		2.修改
		foo: bar/lose
			cd bar; gobble lose > ../foo //同一行命令之间使用";"分隔
		3.优化---最佳方案
		foo: bar/lose
			cd bar; \ //使用"; \":便于查看.
			gobble lose > ../foo

### 4.3 make选项

make的help方法:info make/make --help.

make -j/--jobs n:告诉make同一时刻可以有n条命令被执行(并行执行).多条命令同时执行容易出现问题.

make -k/--keep-going:忽略某些错误继续执行.

	可以检查文件中哪些文件可以被正确编译,哪些出错.常用语调试Makefile或查找哪些源文件有编译错误.

make -l 2.5/--max-load=2.5:指定make执行时所占用的最大系统负荷.

make -i/--ignore-errors:忽略所有的命令执行错误.--->命令之前的"-"更灵活,因此"-i"一般不用.

	如果make失败了,修改错误之后正确的编译方法是:先make clean再make.

make -w/--print-direcotry:开始编译一个目录之前或和完成此目录的编译之后给出提示信息.方便追踪make的执行过程.

	e.g.
		make: Entering directory...
		make: Leaving directory...
		默认自动打开该选项,取消方法(make -s/--no-print-directory)

### 4.4 中断make的执行

make在执行命令时如果收到致命信号(ctrl+c),make会删除已经重建的目标文件(e.g.一些".o"文件),确保下一次make时目标文件能够被正确重建.

### 4.5 make的递归执行

	方法1:
	subsystem:
		cd subdir && $(MAKE)	//1.先进入subdir目录; 2.在执行make命令.
	方法2:--->常用
	subsystem:
		$(MAKE) -c subdir	//make的-C选项,也是先进入subdir目录. 再执行make.

**1.变量MAKE**

	1.变量"MAKE"代表make这个应用程序(e.g./usr/bin/make--->使用which make可查找.)
	2.如果多个目录下都存在Makefile,使用$(MAKE) -C可以执行这些目录下的Makefile.

**2.命令行选项的传递**

	主目录的命令行选项在$(MAKE) -c时,会自动通过一个"MAKEFLAGS"变量传递给子目录下的make程序.

**3.export**

	一个变量使用"export"声明后,该变量和变量的值会被加入到当前工作的环境变量中(此时在子目录中也可以使用这些变量).
		1.export某个变量
			export VARIABLE = value
			等价于:
			VARIABLE = value
			export VARIABLE	//export VARIABLE这个变量.
		2.export不带参数
			export	//表示export所有变量.不好控制--->一般不用

**4.unexport**

	unexport VARIABLE	//取消变量导出.常在子目录的Makefile中使用.

### 4.6 定义命令包

命令包包含一组命令,类似于C语言的函数.在需要使用的地方直接调用即可.

	1.定义命令包
	define frobnicate	//define(打头) 包名.
		@echo "frobnicating target $@"	//一些命令(以Tab键打头)
		frob-step-1 $< -o $@-step-1
		frob-step-2 $@-step-1 -o $@
	endef	//endef(结尾)
	2.调用命令包
	frob.out: frob.in
		@$(frobnicate) //$(包名).前面的@(取消回显)会作用到包中的所有的命令.

### 4.7 空命令

只有目标文件(可以存在依赖文件),但没有命令行.

	target: ;	//直接";"表示空命令行.不使用重启一行+[tab]的方式,因为[tab]那一行看起来和空行没区别.

空命令目的:防止make在重建target时查找隐含命令,空命令使用较少.

***

## Chapter 5 Makefile中的变量

变量名是大小写敏感的(即大小写不一样).推荐的命令风格为:

	1.内部定义的一般变量采用小写方式(e.g.表示目标文件列表的变量:objects);
	2.参数列表采用大写方式(e.g.表示编译选项的变量:CFLAGS);
	3.有时候不一定要完全按照上述风格,关键是需要命名风格保持工程的一致性.

变量的引用:

	Makefile中的引用:$(VAR)/${VAR}
	shell中的引用:${VAR}/$VAR

### 5.1 变量的定义

**1.递归展开式变量(=)**

通过"="或者define定义的变量,这种变量会在最后使用时才展开.嵌套使用容易死循环.

	foo = $(bar)	//不会展开,因此可以引用之后定义的bar
	bar = $(ugh)	//不会展开,因此可以引用之后定义的ugh
	ugh = Huh?
	all: ; echo $(foo)		//引用才展开,最后打印"Huh?"

**2.直接展开式变量(:=)**

使用":="来定义变量,在定义的地方会直接展开(推荐使用这种方式).

	x := foo	
	y := $(x) bar	//y为foo bar
	x := later		//x重新赋值为later

**3.注释(#)**

变量值尾到同行的注释"#"之间的空格是不会被忽略的,因此不能随便使用这种方式注释.

	dir := /foo/bar		#directory...(这种方式注释是不正确的,因为当中的空格是不会被忽略的)

注释内容推荐书写在独立的一行或者多行,可以防止意外情况的发生.

**4.条件赋值(?=)**

变量值为空才会赋值,否则不赋值(即不改变原有的值).

	FOO ?= bar	//当$(FOO)为空时赋值为bar;如果$(FOO)有值直接略过,不改变原有的值.
	--->等价于:
	ifeq ($(origin FOO), undefined)
	FOO = bar
	endif

**5.变量追加(+=)**

实现对一个变量的追加操作.

	FOO = bar
	FOO += foo	//此时$(FOO)值为"bar foo"

### 5.2 变量的高级用法

变量的替换引用
	
	foo := a.o b.o c.o
	bar := $(foo:$.o=$.c)	//将.o结尾的文件用.c来代替(%---模式匹配字符)
		//此时$(bar)的值为"a.c b.c c.c"

引用一个没有定义的变量,默认其值为空.

### 5.3 override指示符

**override**

防止执行make时通过命令行指定的变量的值代替Makefile中变量定义的值.

	override CFLAGS += -g	//必须打开调试开关"-g".此时命令行如果指定变量CFLAGS,
							//不会取代Makefile中CFLAGS变量定义的值.

	ifeq ("$(O)", "output")
	override O:=output_upg	//表示变量O不能被命令行传进来的值代替
	CONFIG_DIR:=$(TOPDIR)/$(O)
	EXTRAMAKEARGS += O=$(O)
	NEED_WRAPPER=y
	endif

**define定义变量**

以define开始,endef结束,之间命令为所定义的变量值.

	define two_lines	//two_line为变量名
	echo foo
	echo $(bar)
	endef

**环境变量SHELL**

	命令行的解释程序使用的是环境变量SHELL,该变量$(SHELL)的值为"/bin/sh".
	--->可以使用:echo "shell is $(SHELL)"打印出该环境变量SHELL的值.

### 5.4 模式指定变量

模式指定变量的目的:将一个变量的值指定到所有符合某个模式的目标上.对其他文件不会有影响.

	%.o : CFLAGS += -O
	/*
		%.o--->需要增加某个变量值的目标.此处的模式为"所有以.o结尾的目标文件".
		:--->语法要求
		CFLAGS += -O--->某个变量.
	此处的目的是:指定为所有的.o文件的编译选项增加"-O"选项,不改变对其他文件类型的编译选项.
	*/

***

## Chapter 6 Makefile的条件执行

Makefile的条件判断实例

	...
	libs_for_gcc = -lgnu //libgnu.so或libgnu.a库
		//-l:表示链接lib;gnu:表示libgnu.so/libgnu.a库.链接时使用"-lgnu",去掉"lib"和".so/.a".
	normal_libs = 	//表示库为空
	...
	foo:$(objects)
	ifeq ($(CC), gcc) //条件表达式,判断$(CC)变量与gcc是否相等.--->"ifeq"与后面的"("之间有空格.
		$(CC) -o foo $(objects) $(libs_for_gcc)
	else
		$(CC) -o foo $(objects) $(normal_libs)
	endif
	...

	//改进的方法:
	libs_for_gcc = -lgnu
	normal_libs =
	
	ifeq ($(CC), gcc)
	libs=$(libs_for_gcc)	//ifeq...else...end后面的语句可以定格或有空格,但是不能是tab键.
	else
	libs=$(normal_libs)
	endif
	
	foo:$(objects)
		$(CC) -o $(objects) $(libs)

### 6.1 ifeq

用于判断两个参数是否相等,格式如下几种:

	ifeq (arg1, arge2) --->常用
	ifeq 'arg1' 'arg2'
	ifeq "arg1" "arg2"

ifeq常用语判断一个变量是否为空(不是任何字符).由于变量的展开时可能包含空字符(空格等),一般使用strip函数去掉变量中的空字符.

	ifeq ($(strip $(foo)),) //"$(strip $(foo)):去掉$(foo)中存在的前导和结尾空格.
	...
	endif

strip函数:去掉前导和结尾空格,将字符串之间的多个空格变成一个空格.

	data = "  a  b  c"
	$(strip $(data))  //其值为" a b c",因为""包括的整个都被视为字符串,因此去掉字符串之间的多个空格变为一个空格.
	data =    a   b  c
	$(strip $(data))  //其值为"a b c",会去掉前导空格，同时将字符串之间的多个空格变为一个空格.

### 6.2 ifneq

用于判断两个参数是否不相等,格式如下几种:

	ifneq (arg1, arge2) --->常用
	ifneq 'arg1' 'arg2'
	ifneq "arg1" "arg2"

ifneq用于与ifeq相同.

### 6.3 ifdef

用于判断一个变量是否被定义.

	ifdef $(variable)	//判断variable变量是否被定义
	...
	endif

ifdef只是测试一个变量是否有值,不会对变量进行替换展开来判断变量的值是否为空.除非主动定义"variable="为空,否则赋值或其他操作都会使ifdef返回true.

	1.赋值为空的情况,ifdef返回true
		bar = 
		foo = $(bar)
		ifdef foo
		frobozz = yes
		else
		frobozz = no
		endif
		//此时的frobozz值为yes.
	2.主动定义为空,ifdef返回false
		foo =
		ifdef foo
		frobozz = yes
		else
		frobozz = no
		endif
		//此时的frobozz值为no.

### 6.4 ifndef

与ifdef相反,使用一样.

**判断变量为空一般使用"ifeq/ifneq.**

***

## Chapter 7 make的内嵌函数

**函数调用语法:**

	$(FUNCTION ARGUMENTS) --->常用
	或${FUNCTION ARGUMENTS} --->用的比较少
	
	1.FUNCTION:调用的函数名.一般使用"()","{}"用的比较少.
	2.ARGUMENTS:函数参数.FUNCTION和ARGUMENTS之间使用一个"空格"分割,多个ARGUMENTS使用","分割.

实例---将变量中的空格替换为逗号

	comma:= ,	//comma:表示逗号
	empty:= 
	space:= $(empty) $(empty)
	foo:= a b c
	bar:= $(subst $(space), $(comma), $(foo)) //结果bar的值为a,b,c(会忽略前导和结尾的空格).

### 7.1 文本处理函数

**1.$(subst FROM, TO, TEXT)**

把"TEXT"中的"FROM"字符替换为"TO",返回替换后的新字符串.TEXT中是以空格作为分隔符.

	$(subst ee, EE, feet on the street)	//返回值为:fEEt on the strEEt

**2.$(patsubst PATTERN, REPLACEMENT, TEXT)**

将"TEXT"中符合模式"PATTERN"替换为"REPLACEMENT".一般会使用"%"模式通配符,返回替换后的新字符串.TEXT中是以空格作为分隔符.

	$(patsubst %.c, %.o, x.c.c bar.c)	//返回值为:x.c.o bar.o

	SRC := $(wildcard $(DIR_SRC)/%.c) //SRC表示源目录下的.c文件
	OBJ := $(patsubst %.c, $(DIR_OBJ)/%.o, $(notdir $(SRC))) //OBJ表示所有的.c对应的.o文件.

**3.$(strip TEXT)**

去掉"TEXT"中前导和结尾空格,将字符串之间的多个空格合并成一个空格.

	data = "  a  b  c"
	$(strip $(data))  //其值为" a b c".因为""包括的整个都被视为字符串,因此合并字符串之间的多个空格为一个空格.
	data =    a   b  c
	$(strip $(data))  //其值为"a b c".去掉前导空格,同时将字符串之间的多个空格合并为一个空格.

**4.$(findstring FIND, IN)**

在"IN"中查找"FIND"字符.找到返回"FIND",否则返回空.

	$(findstring a, a b c)	//找到,返回:a
	$(findstring a, b c)	//没找到,返回:空

**5.$(filter PATTERN..., TEXT)**

过滤"TEXT"中所有不符合模式"PATTERN"的单词,保留符合模式"PATTERN"的单词.一般会使用"%"模式通配符.多个PATTERN用空格分开.
	
	sources := foo.c bar.c baz.s ugh.h
	foo:= $(sources)
		$(CC) $(filter %.c %.s, $(sources)) -o foo	//返回值为:foo.c bar.c baz.s(过滤掉了ugh.h)
		//多个PATTERN用空格分开.(e.g.此处的"%.c %s")

**6.$(filter-out PATTERN..., TEXT)**

过滤"TEXT"中所有符合模式"PATTERN"的单词,保留不符合模式"PATTERN"的单词.一般会使用"%"模式匹配符.多个PATTERN用空格分开.

	objects = main1.o foo.o main2.o bar.o
	mains = main1.o main2.o
	$(filter-out $(mains), $(objects)) //去除变量"objects"中"mains"定义的字串.返回值为"foo.o bar.o"

**7.$(sort TEXT)**

给"TEXT"中的单词以首字母排序(升序),并去掉重复的单词.返回排序并且没有重复的字符串.

	$(sort foo bar lost foo)	//返回值为:bar foo lost

**8.$(word N, TEXT)**

取"TEXT"中的第"N"个单词(单词计数从1开始,因此N也从1开始),返回该单词.如果N大于"TEXT"中的单词数目,返回空;如果N为0,出错.

	$(word 3, foo bar baz)	//返回值为:baz.从1开始计数.

**9.$(wordlist S, E, TEXT)**

取"TEXT"中从S到E的单词,S/E均从1开始.

	$(wordlist 2, 3, foo bar baz)	//返回值为:bar baz

**10.$(words TEXT)**

计算"TEXT"中单词的数目.

	$(words foo bar)	//返回值为:2.如果取TEXT中的最后一个单词为:$(word $(words TEXT), TEXT).

**11.$(firstword TEXT)**

取"TEXT"中的第一个单词.

	$(firstword foo bar)	//返回值为:foo

### 7.2 文件名处理函数

**1.$(dir NAMES...)**

从文件名序列"NAMES..."中取出各个文件的目录部分.

目录部分:文件名最后一个斜线"/"(包括斜线)之前的部分;如果没有斜线就是当前目录(./).

	$(dir src/foo.c hacks)	//返回值为:src/ ./

**2.$(notdir NAMES...)**

从文件名序列"NAMES..."中取出各个文件的非目录部分(也就是取出文件的文件名).

	$(notdir src/foo.c hacks)	//返回值为:foo.c hacks

**3.$(suffix NAMES...)**

从文件名序列"NAMES..."取出各个文件名的后缀.

后缀:文件名中最后一个以"."开始(包括点号)的部分,如果文件名中不包含一个点号(".")则为空.

	$(suffix src/foo.c src-1.0/bar.c hacks) //返回值为:".c .c"(hacks的返回值为空)

**4.$(basename NAMES...)**

从文件名序列"NAMES..."取出文件名最后一个点号"."之前的部分(也叫前缀部分),前缀会包含目录部分一直到最后一个点号.如果某个文件没有点号,则整个文件都作为前缀返回.

	$(basename src/foo.c src-1.0/bar.c /home/jack/.font.cache-1 hacks)
		//返回值为"src/foo src-1.0/bar /home/jack/.font hacks"

**5.$(addsuffix SUFFIX, NAMES...)**

为文件名序列"NAMES..."中各个文件名添加后缀"SUFFIX".

	$(addsuffix .c, foo bar)	//返回值为"foo.c bar.c"

**6.$(addprefix PREFIX, NAMES...)**

为文件名序列"NAMES..."中各个文件名添加前缀"PREFIX".

	$(addprefix src/, foo bar)	//返回值为"src/foo src/bar"	
	$(addprefix $(OBJS_TMP)/,$(OBJS))	//增加前缀后,其值为$(OBJ_TMP)/$(OBJS)

**7.$(join LIST1, LIST2)**

将字符串"LIST1"和字符串"LIST2"各个单词一一对应连接(LIST2添加到LIST1之后).单词数目不一致的多出的直接返回.

	$(join a b, .c .o)		//返回值为"a.c b.o"
	$(join a b c, .c .o)	//返回值为"a.c b.o c"--->c属于没有对应,直接返回

**8.$(wildcard PATTERN)**

列出当前目录下所有符合模式"PATTERN"格式的文件名,"PATTERN"只能使用shell可识别的通配符"?"(单字符)、"*"(任意字符),不能使用"%".

	$(wildcard *.c)	//返回值为:当前目录下所有.c的源文件列表

### 7.3 foreach函数

**$(foreach VAR, LIST, TEXT)**

将"LIST"中的单词依次取出赋给"VAR",然后执行"TEXT"表达式."TEXT"中的变量属于递归展开式,只有执行时才会展开.

	dirs := a b c d
	files := $(foreach dir, $(dirs), $(wildcard $(dir)/*)) //等价于"files := $(wildcard a/* b/* c/* d/*)"
	/*下面是在buildroot顶层Makefile中(line:1024)*/
	$(foreach b, $(sort $(notdir $(wildcard $(TOPDIR)/configs/*_defconfig))), \
		printf  " %-35s - Build for %s \\n" $(b) $(b:defconfig=);)
	//说明:wildcard后有可能会带上目录名,因此使用notdir去掉目录.

### 7.4 if函数

**$(if CONDITION, THEN-PART, ELSE-PART)**

如果CONDITION条件成立,则将THEN-PART作为函数的计算表达式并返回;如果CONDITION结果为空,则将ELSE-PART作为函数的计算表达式并返回.

	SUBDIR += $(if $(SRC_DIR), $(SRC_DIR), /home/src)
	//如果"SRC_DIR"变量值不为空,则将"SRC_DIR"目录作为一个子目录;否则将"/home/src"作为一个子目录.

### 7.5 call函数

call函数实现对自定义函数的引用.

**$(call VARIABLE, PARAM, PARAM,...)**

	VARIABLE:该变量表示自定义函数的函数名/
	PARAM...:依次赋值给变量$(1),$(2),...这些变量会当作自定义函数的参数.
		其中$(0)表示函数名本身.$@表示$(1),第一个参数.($(1)和$1是一样的).

实例1:

	reverse = $(2) $(1)
	foo = $(call reverse, a, b)
	/*
		reverse:函数名(此处为一个变量名).
		a, b参数会作为$(1)和$(2)给传进去.因此在reverse中可以通过$(1),$(2)引用.
		foo的值为"ba"--->会去掉空格.
	*/

实例2:

	define target
		echo $@		//此处的$@相当于$1
		echo $@
	endef
	all:
		$(call target, all) //传进去的参数all,是第一个参数$1.
		/*也可以写成:$(call target)--->此时会把all给传进去.*/

	clean:
		$(call target, clean) //传进去的参数clean,是第一个参数$1.
		/*也可以写成:$(call target)--->此时会把clean给传进去.*/

	.PHONY: all clean
	/*
		1.执行make/make all的结果为:
			echo all
			all
			echo all
			all
		2.执行make clean的结果为:
			echo clean
			clean
			echo clean
			clean
	*/

### 7.6 value函数

**$(value VARIABLE)**

不对变量"VARIABLE"进行任何展开操作,直接返回"VARIABLE"代表的文本值(按整体来计算值)->直接展开式变量除外,直接展开式变量会在定义的时候被直接展开.

	FOO = $PATH
	all:
		@echo $(FOO)	//$(FOO)展开为$PATH,因为$P为空.因此打印的值为"ATH"
		@echo $(value FOO)	//不对变量FOO进行展开,返回FOO这个变量所代表的文本值
							//此处为计算$PATH这个整体值,即环境变量的值.

### 7.7 origin函数

**$(origin VARIABLE)**

origin函数查询变量"VARIABLE"从哪里来.返回值分别为:underfined(没定义)/default(内嵌变量)/environment & environment override(系统环境变量)/override(使用override指示符定义)/automatic(自动化变量)/command line(命令行中定义).

实例:

	//一个Makefile文件内容如下:
	ifdef O
	ifeq ("$(origin O)", "command line")	//“ifeq ("两者之间必须有空格.查询变量O是从哪里来的
		BUILD_DIR := $(O)
	endif
	endif

	all :
		@echo $(origin O)	//输出变量O的出处
		@echo $(BUILD_DIR)	//输出变量BUILD_DIR的值

	/*运行1*/
	make
	/*
		因为O没有被定义,因此第一句会输出"undefined".即没有被定义
		BUILD_DIR没有被定义,所以BUILD_DIR为空.会直接输出一个空行
	*/
	/*运行2*/
	make O=/home
	/*
		输入了参数"O=/home".此时$(origin O)会得到"command line"
		BUILD_DIR有定义.因此$(BUILD_DIR)会得到"/home"
	*/
	/*运行3*/
	/*
		如果在Makefile文件中已经写了"O = /home".此时$(origin O)会得到"file"的返回值
	*/
	/*其他的还有:
		1.environment--->export O=/home	//导出了环境变量
		2.default--->略
		3.override--->略
		4.automatic--->略
	*/

实例---buildroot顶层Makefile

	# To put more focus on warnings, be less verbose as default
	# Use 'make V=1' to see the full commands
	ifdef V
		ifeq ("$(origin V)", "command line")
			KBUILD_VERBOSE=$(V)
		endif
	endif

	ifndef KBUILD_VERBOSE
		KBUILD_VERBOSE=0
	endif
	
	ifeq ($(KBUILD_VERBOSE), 1)
		quiet=
		Q=
	ifndef VERBOSE
		VERBOSE=1
	endif
	else
		quiet=quiet_
		Q=@		#此时输出被忽略
	endif

### 7.8 shell函数

**$(shell param)**

实现在Makefile中调用shell命令.函数返回为参数"param"(一般为shell命令)在shell中的执行结果.

	contents := $(shell cat foo)	//contents被赋值为文件"foo"的内容
	files := $(shell echo *.c)		//files被赋值为当前目录下所有的.c文件列表.

### 7.9 info、warning、error函数

info, warning, error函数常用语Makefile中的调试,属于不同的打印级别.

**$(info string)**

级别最低,执行到该位置时,会将string输出,方便定位make执行到哪个位置.

	$(info Make execute to there)
	//执行到该处时会打印出"Make execute to there"

**$(warning string)**

级别medium,执行到该位置时,会将string输出,方便定位make执行到哪个位置--->常用.

	$(warning Make execute to there)
	//执行到该处时会打印出"Make execute to there"

**$(error string)**

级别highest,会产生致命错误,执行到该位置时,会停止当前Makefile的执行.

	$(error Make stop in there)
	//执行到该处时会打印出"Make stop in there",并且直接退出当前的Makefile.

***

## Chapter 8 执行make

### 8.1 make的目标	

部分标准的目标,伪目标,空目标命名:

all:终极目标,一般也是伪目标.

clean:伪目标,删除所有由make创建的文件.

mostlyclean:与clean相似,但不会全部删除(e.g.不删除某些库文件).

distclean/realclean/clobber:与clean相似,但删除的更彻底(e.g.删除编译之前一些系统配置文件,链接文件等).

install:将make成功创建的可执行文件拷贝到shell环境变量"PATH"指定的目录(e.g.应用可执行文件拷贝到"/usr/local/bin",库文件拷贝到"/usr/local/lib").

print:打印出所有被更改的源文件列表.

check/test:对Makefile最后生成的文件进行检查.

### 8.2 make的命令行选项

	-C DIR, --directory=DIR Change to DIRECTORY before doing anything.
		切换到"DIR"目录之后执行make.
	-d	Print lots of debugging information.
		打印出所有的调试信息.
	-j [N], --jobs=[N]	Allow N jobs at once; infinite jobs with no arg.
		指定可同时执行的命令数目(N).没有指定时是不限的命令数目(由编译器自行优化).
	-n, --just-print	Don't actually run any commands; just print them.
		只打印出所要执行的命令,但不执行命令.
	-s, --silent		Don't echo commands.
		取消命令执行过程的打印.
	-v, --version		Print the version number of make and exit.
		查看make的版本信息.
	-h, --help	Print this message and exit.
		打印出帮助信息.

***

## Chapter 9 make的隐含规则

### 9.1 隐含规则的使用

隐含规则提供的依赖文件只是一个最基本的("EXENAME.o"对应"EXENAME.c").如果需要增加某个目标的依赖文件时,要在Makefile中使用"没有命令行"的规则来明确说明.

**如果需要给目标指定明确的重建规则时(即不使用隐含规则),规则描述中就不能省略命令行.**

如果不想让make为一个没有命令行的规则的目标搜索隐含规则，可以使用空命令来实现.

N.s:是不需要预处理的汇编源文件;N.S:是需要预处理的汇编源文件(汇编器为"as")."N.s可由N.S生成.

目标和依赖中均可以有模式匹配字符"%",依赖的"%"取值情况由目标中的"%"决定.

	%.o : %.c	//模式规则,.o文件由对应的.c文件生成.
	%.o : debug.h	//依赖文件中不包含模式字符"%"，表示所有的目标都依赖于"debug.h"这个文件.

### 9.2 自动化变量

1)$@:规则中的目标文件名.

2)$%:规则的目标文件是一个静态库文件时,"$%"代表静态库的一个成员名(e.g.规则的目标为"foo.a(bar.o)"时,那么"$%"的值为"bar.o","$@"的值为"foo.a")

3)$<:规则中的第一个依赖文件名.

4)$?:所有比目标文件更新的依赖文件列表.如果目标是静态库文件名,"$?"代表库成员(.o文件)的更新情况.

5)$^:规则中所有依赖文件列表,"$^"会去掉重复的依赖文件.

6)$+:类似于"$^",但是会保留依赖文件列表中重复出现的依赖文件.

7)$*:代表模式规则中的"茎"(e.g.文件"dir/a.foo.b",当目标的模式为"%.b"时,"%*"的值为"dir/a.foo"---先去掉目录dir/，匹配a.foo;然后再加上目录,最终得到dir/a.foo).

**某个规则使用了双冒号"::",即为最终规则(也叫双冒号规则).最终规则要求:只有依赖文件明确存在时才能被应用(执行),即使依赖可以由隐含规则创建也不能被应用.**

***

## 第十章	使用make更新静态库文件

静态库文件也叫"文档文件",是一些".o"文件的集合，使用工具"ar"对静态库进行维护管理.

**库成员作为目标的书写方式:"ARCHIVE(MEMBER)"即'库(成员)'.只能出现在规则的目标和依赖文件中,不能出现在规则的cmd中.**

库成员作为目标只能使用"ar"命令或者其他可以对库成员进行操作的命令.

	foolib(hack.o) : hack.o
		ar cr foolib hack.o	//将"hack.o"成员纳入库"foolib"
	foolib(*.o)	//表示库"foolib"所有的.o成员(*为shell的通配符)

**给静态库新增一个成员".o"的过程(使用"ar"可以自动完成下面的步骤):**

1)将该成员".o"拷贝到静态库;

2)更新静态库的符号索引表.

**make静态库时不要使用"-j"选项(并行执行选项),否则会造成静态库的损坏.**

***

### 其他信息

**make -v/--version:打印make版本和版权信息**

**make -h/--help:列出make支持的所有命令行选项**

**make V=1:查看详细的编译信息.**

其他命令可以使用"ls --help"查看支持的命令行选项.

**使用工具"automake"可以帮助我们创建一个遵循GNU make约定的Makefile.**

**命令行选项变量"CFLAGS"一般放在选项的最后.**

***

## 第十一章 Makefile的实际应用

### 1.Makefile变量和shell变量的区别

在Makefile中定义的变量属于Makefile变量.在Makefile如果要使用shell变量,最好前面带上shell的标识符.

	/*在Makefile中*/
	GIT_VERSION := $(shell git --version | awk '{print $$3}' | awk -F '.' '{print $$1$$2}')
	/*
		shell表示后面的命令为shell命令.  "$$3":在Makefile中明确为shell中的变量,此处为第三个参数.
		awk -F '.'表示分隔符为".".
		git --version:得到"git version 2.3.0"
		此处命令得到GIT_VERSION为23
	*/
	GIT_VERSION_CHECK := $(shell if [ $(GIT_VERSION) -ge 23 ] ; then echo true; else echo false; fi)

### 2.编译内核模块的Makefile中的($(KERNELRELEASE))

	在编译内核模块时,通常的Makefile写法如下:
	ifneq ($(KERNELRELEASE), )	//KERNELRELEASE是在内核源码的顶层Makefile中定义的一个变量,在第一次读取此
		//Makefile时,KERNELRELEASE没有被定义.此时make将会执行else之后的内容
		//ifneq后面必须有空格.
	obj-m += alibsf.o	//这些语法属于kbuild语法,由内核的kbuild去解析.此处表示要生成alibsf.ko
	alibsf-y := bsf_core.o bsf_ioctl.o bsf_rpc.o
	else
	KDIR := .../linux-directory		//表示内核源码目录
	all:
		make -C $(KDIR) M=$(shell pwd) modules	//make -C:表示跳转到内核源码下读取那里的Makefile.
			//M=$(shell pwd):表示返回到当前目录继续执行. 后面的modules编译为模块时所带参数
		//可能需要指定ARCH和CROSS_COMPLIE,此时应该
		make -C $(KDIR) M=$(shell pwd) modules ARCH=arm CROSS_COMPILE=$(CROSS_COM)
			//执行ARCH和CORSS_COMPILE
	clean:	//删除一些临时文件
		rm -rf *.mod.c
		rm -rf *.ko .*.ko.cmd
		rm -rf *.o .*.o.cmd
		rm -rf modules.*
		rm -rf .tmp_versions *.symvers
	endif

### 3.buildroot中的.mk中的语法

	ALIAS_CODE_DIR = $(@D)/codes	//$(@D):从git上拉下来的目录
	ALIAS_INSTALL_DIR = $(ALIAS_CODE_DIR)/install

	ifneq ($(BR2_ENVIRONMENT_CUSTOMER), y)	//非release的时候
	define ALIAS_BUILD_CMDS
		$(MAKE) clean -C $(ALIAS_CODE_DIR)
		$(MAKE) $(ALIAS_MAKE_FLAGS) -C $(@D)/codes	//进入到该目录下编译
		$(MAKE) $(ALIAS_MAKE_FLAGS) -C $(@D)/alibsf
	endef
	
	define ALIAS_INSTALL_TARGET_CMDS
		@mkdir -p $(TARGET_DIR)/app/as
		$(INSTALL) -m 0755 -D $(ALIAS_INSTALL_DIR)/* $(TARGET_DIR)/app/as
			//拷贝到目标目录
		# Install alibsf module to target directory
		rm -rf $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/extra
		mkdir -p $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/extra
		$(INSTALL) -m 0755 -D $(@D)/alibsf/alibsf.ko $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/extra
		if grep -q "extra/alibsf.ko" $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/modules.dep; then 	\
			//then结尾后应该是"空格+tab然后再\":一定要注意此处
			echo "alibsf has been install";	\	//结尾后应该是tab然后在\
		else	\	//结尾后应该是tab然后在\
			echo "extra/alibsf.ko:" >> $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/modules.dep;	\
				//结尾后应该是tab然后在\
			echo "extra/alibsf.ko" >> $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/modules.order;	\
				//结尾后应该是tab然后在\
		fi
	endef
	endif

### 4.linux下的modprobe:module ath.ko not found in modules.dep

	编辑modules.dep.此文件一般在"./lib/modules/$(LINUX_VERSION_PROBED)/modules.dep"
	在后面增加:
	echo "extra/alibsf.ko:" >> $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/modules.dep
	echo "extra/alibsf.ko" >> $(TARGET_DIR)/lib/modules/$(LINUX_VERSION_PROBED)/modules.order
	PS:如上的问题3.
	modprobe也是通过rmmod进行删除.

### 5.在Makefile中使用echo增加调试信息

在Makefile中使用echo增加调试信息时,echo只能在"target:"后面的语句中使用,其前面必须是tab键.

	test: a b
		@echo "xxxxx" //echo必须是在"target:"后面的语句,且以tab键开头.

	PS:如果echo在其他地方,就会报"Makefile: x:*** missing separator. Stop."的错误.

***

## Chapter 12 Makefile碰到的问题

***

## 1.把目录当成文件来操作

	make: execvp: /zhsa022/usrhome/defy.chen/repository/work_viaccess/buildroot: Permission denied
	/*错误原因:If you see an error like this when you run make, it means make is attempting to 
	execute a directory, not a program. Which means you probably have extra spacing in one of 
	your variables in your config/make files.*/
	/*问题描述:将目录当成了文件来操作.原因:是因为在Makefile中指定buildroot路径时,后面多加了一个"空格"*/

## 2.从git上只拉下源码的方法

	make alisee-source		//将alisee的源码拉下来

## 3.cc、gcc、g++、CC的区别

	cc:是Unix系统的C Compiler,为商业软件.在linux下一般是一个符号链接,指向gcc.目前cc使用的很少了.
	gcc:GNU Compiler Collection,GNU编译器套装,包含很多编译器(c、c++、Objective-c、Fortran、Java).一般使用gcc
	g++:g++可以编译C/C++代码.与gcc区别:
		1)".c"文件,gcc当作C程序,gcc当作C++程序.".cpp"两者都认为是C++程序.
		2)对于宏"__cplusplus"---指示编译器将代码按C还是C++语言来解释.如果后缀为.c,并且采用gcc编译器,则该宏是未定义的.
			否则就是已定义的.
	CC:一般是Makefile中的一个名字.

## 4.make的时候出现"empty variable name"

是因为在执行"make"的时候,某个参数在赋值时"="左边出现了空格

	make -C $(LINUX_SRC) SUBDIRS = $(shell pwd) modules
	/*
	因为SUBDIRS赋值时,等号左边有空格,因此会报"empty variable name"的错误.

	如果右边有空格,会报:
		*** Error during update of the kernel configuration.
		
		make[3]: *** [silentoldconfig] Error 1
		make[2]: *** [silentoldconfig] Error 2
		make[1]: Nothing to be done for `hello_module'.
		make[1]: *** No rule to make target `include/config/auto.conf', needed xxx'.
		Stop.
		make[1]: Leaving directory `/usr/src/linux-headers-2.6.35-22-generic'
		make: *** [all] Error 2
	*/

***

# 2. Makefile Example

## 2.1 编写应用的Makefile实例

	1.在顶层目录建立一个mk.rule的文件,用于存放cross compile和cflags:
		LINUX_DIR := /*linux的路径*/
		CROSS_COMPILE = /*交叉编译工具的路径*/
		CC := $(CROSS_COMPILE)gcc //选择交叉编译工具中的gcc
		CFLAGS := -O2 -I$(LINUX_DIR)/... /*一些头文件路径*/
		CFLAGS += $(WARNINGS) $(OPTIMIZE) $(DEFS) //加上一个编译选项
	2.新建一个存放应用代码的文件(e.g.test1),在该文件下建立如下文件/文件夹:
		1.src 	/*存放应用程序的源代码*/
		2.obj	/*存放编译后产生的.o文件*/
		3.Makefile /*编译规则,其内容如下:*/
			CUR_DIR = $(shell pwd)
			TOP_DIR = $(CUR_DIR)/..
			DIR_SRC = $(CUR_DIR)/src
			DIR_OBJ = $(CUR_DIR)/obj
			DIR_BIN = $(CUR_DIR)/bin

			include $(TOP_DIR)/mk.rule

			TARGET := test

			$(shell if [ ! -d $(DIR_OBJ) ]; then mkdir $(DIR_OBJ); fi ;)
			$(shell if [ ! -d $(DIR_BIN) ]; then mkdir $(DIR_BIN); fi ;)
			
			SRC = $(wildcard $(DIR_SRC)/*.c)
			OBJ = $(patsubst %.c, $(DIR_OBJ)/%.o, $(notdir $(SRC)))

			TARGET_BIN = $(DIR_BIN)/$(TARGET)

			$(TARGET_BIN):$(OBJ)
				$(CC) $(OBJ) -o $@

			$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c
				$(CC) $(CFLAGS) -c $< -o $@

			.PHONY: clean all

			clean:
				find $(DIR_OBJ) -name *.o -exec rm -rf {} \;
				rm -rf $(DIR_BIN)
			
			all:$(TARGET_BIN)
	3.最终产生的应用位于"bin/"下.

***

# 3. Shell Script Usage

## 1.dirname的使用

dirname得到某个文件的目录.

	/*getpath.sh脚本内容如下*/
	PATH_ROOT=$1
	CUR_DIR=$(cd "$(dirname "$0")"; pwd)
	cd $PATH_ROOT
	ROOT_PATH=$(cd "$(dirname "$0")"; pwd)

	/*
	如果执行"./getpath.sh ../../.."
	此时传进去的$0为"./getpath.sh"; $1为"../../../"
	dirname "$0":取$0的目录(取的是相对路径),即为"."
	执行cd "$(dirname "$0")"等价于"cd .",仍然在当前目录.
	因此上述只要切换到某个目录,pwd就取到了该目录的路径.
	*/