## 第一章	概述
### 1.1 Make基本知识
*通常，一个高级语言的源文件都对应一个目标文件，linux中默认的后缀为".o"*

**链接:将多个.o文件，或者.o和库文件链接成可执行程序，<font size=4>"ld"</font>是GNU的链接器.**

**静态库:文档文件(Archive File),多个.o的集合，后缀".a",使用"ar"工具维护和管理.**

**共享库:多个.o的集合,.o文件由编译器按照一种特殊的方式生成，各模块地址均为相对地址.**
### 1.2 GNU make介绍

*某个头文件在上一次执行make后被修改,所有包含该头文件的C源文件在本次执行make都会被重新编译*
	
	makefile 规则
	target(目标):prerequisites(依赖)
	(tab)cmd(命令)
**cmd:一个规则可以有多个cmd,每个cmd占一行,以[tab]字符开始**

*一个目标可以没有依赖只有动作(指定的命令),也叫<font size=4>伪目标(phony targets)</font>，e.g.clean*

**Makefile中书写时，使用反斜线(<font size=4>"\\"后面不能有空格</font>)分解多行**

**一般使用变量"obj,objs,ojects等来表示终极目标中的依赖列表"**
	
	objs = main.o kbd.o command.o display.o \(无空格)for
		insert.o search.o files.o util.o
	后面使用"$(objs)"引用这些变量

**清除工作目录过程文件**
	
	.PHONY:clean	//通过.PHONY将clean声明为伪目标,防止当存在一个"clean"文件时，clean规则无法执行
	clean:
		-rm edit $(objs)		//-:忽略rm的执行错误

***
## 第二章	Makefile 总述
### 2.1 Makefile内容
**注释:"#"字符后的内容是注释(shell也是如此)，若某行第一个非空字符为"#",该行为注释行，注释行结尾存在("\\"),下一行也是注释行.**

*"\\#"表示使用字符"#",而非注释.*

*一个目录中比较重要的文件命名规则为首字母大写,e.g.:Makefile, README, Changelist*

### 2.2 包含其他Makefile文件

**使用“include”包含其他文件,include会告诉make暂停读取当前的Makefile,转去读取include指定的文件，完成后在读取当前的Makefile,include应该书写为独立的一行.**

*PS:include以空格开始(不要以[tab]开始--会当作命令)*
	
	include  foo *.mk &(bar)	//bar=bish bash
	等价于:include foo a.mk b.mk c.mk bish bash
**使用“-include”代替“include”--忽略包含文件不存在或无法创建时的错误提示,也可以使用“sininclude”代替"-include".**
*默认变量MAKEFILE_LIST包含在make时读取的文件名*

**Makefile变量取值**
	
	= 	最基本的赋值
	:=	覆盖之前的值
	?=	如果没有被赋值就等于后面的值
	+=	添加后面的值
***
## 第三章	Makefile的规则

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

**常规依赖:更新后目标会更新.**

**order-only依赖:只会在终极目标不存在是参与规则执行,目标存在后无论order-only依赖文件更新与否都不会更新目标(以"|"分割常规依赖和order-only依赖).**

	LIBS = libtest.a
	foo : foo.c | $(LIBS)	// 常规依赖 | order-only依赖
		$(CC) $(CFLAGS) $< -o $@ $(LIBS)
	// 如果foo存在，更新foo.c会导致foo更新，但是更新$(LIBS)不会更新foo
### 3.2 通配符
**变量定义中的通配符不会被展开.**
	
	objs = *.o	//该变量定义为:objs的值是*.o,非所有的.o文件列表
	改成：objs = $(wildcard *.o)

**函数wildcard**

**$(wildcard *.c):获取当前工作目录下的所有.c文件**

**$(patsubst %.c, %.o, $(wildcard *.c)): 1)获取所有.c文件；2)所有.c文件后缀替换为.o.**
	
	objs := $(patsubst %.c, %.o, $(wildcard *.c))	//%匹配一个或者多个字符(也是模式字符)
	foo : $(objs)
		$(CC) -o foo $(objs)

### 3.3 目录搜索

e.g.存在目录prom, prom有子目录src(含有文件sum.c memcp.c),其Makefile如下：

	LIBS = libtest.a
	VPATH = src		//VPATH为Makefile内置变量
	libtest.a : sum.o memcp.o
	$(AR) $(ARFLAGS) $@ @^

如果prom和src目录都不存在libtest.a,在会在当前目录创建目标libtest.a.如果src目录已经存在目标libtest.a,则会有下面两种情况：

	1.如果依赖sum.c和memcp.c没有被更新,不会重建目标，目标目录不会变化
	2.如果更新了sum.c或memcp.c，执行make，sum.o memcp.o和libtest.a会在当前目录创建,因此在src和当前目录(prom)存在两份终极
		目标libtest.a，只有prom目录下是最新的.

如果需要保持一致，可使用下面的方法:

	LIBS = libtest.a
	GPATH = src		//GPATH指定目录，也是Makefile内置变量
	VPATH = src

**自动化变量**

	$^:所有的依赖文件
	$@:目标文件
	$<:依赖文件列表的第一个依赖文件(依赖列表中每一个都有第一个依赖文件)

**库文件**
	
	foo : foo.c -lcurses		//会去搜索目录去寻找libcureses.so，如果没有会去找libcureses.a
		$(CC) $^ -o $@

### 3.4 Makefile伪目标

*如果当前目录中有clean这一个文件，输入make clean时，clean由于没有依赖被认为是最新，因此不会执行clean之后的命令.为了避免这个问题,明确将clean声明为伪目标，将它作为特殊目标.PHONY的依赖，如下：*

	.PHONY : clean
	clean:
		rm -rf *.o temp

**伪目标可以有自己的依赖**

	all : prog1 prog2 prog3		//all一般作为伪目标的终极目标
	.PHONY : all
	prog1 : prog1.o util.o
		$(CC) -o prog1 prog1.o util.o
	prog2 : prog2.o
		$(CC) -o prog2 prog2.o
	prog3 : prog3.o sort.o util.o
		$(CC) -o prog3 prog3.o sort.o util.o

*在上述中，可以执行:make，make prog1, make prog2...*

	clean:
		rm -f(--force)		//防止缺啥删除文件时出错而退出，使make clean过程失败
		-rm					//也可以防止出错，但是使用前面一种较好
**make中内嵌一个隐含变量"RM",被定义为：RM = rm -f;使用方法"$(RM)".**

### 3.5 强制目标(没有命令或者依赖的目标)

*这种方式一般用于非GNU版本的make中.*

	clean : FORCE		//make会认为FORCE依赖被更新过，因此后面的cmd总会被执行
		$(RM) $(objs)
	FORCE :		//强制目标，无依赖也无命令

### 3.6 Makefile的特殊目标

*伪目标:当make指定某伪目标时(e.g.make clean)，该目标所定义的命令都会无条件执行.*

**.PHONY:**

**目标".PHONY"的所有依赖都被作为伪目标**

**.SUFFIXES:**

**目标".SUFFIXED"的所有依赖指出了一系列在后缀规则中需要检查的后缀名(当前的make需要处理的后缀).**

*.DEFAULT:*

*一个文件作为某个规则的依赖,却不是另一个规则的目标时，Make无法重建此文件，就会执行".DEFAULT"所指定的cmd.*

*.PRECIOUS:*

*其依赖文件在命令的执行中被中断时，make不会删除它们.e.g.:原子不可被中断过程;目标文件仅仅是为了记录重建时间;防止其他麻烦.*

**.SILENT:**

**目标".SLIENT"的依赖文件列表在创建时，不会打印创建这些文件所执行的一些cmd信息.（该目标无cmd）**
	
	.SILENT : 	//没有依赖也没有命令(属于强制目标),在make的执行过程中不会打印任何cmd执行的信息.
	//执行时可以使用:make clean -s/--silent或者make --silent代替上述方式.

### 3.7 模式规则

	files = foo.elc bar.o lose.o
	$(filter %.o, $(files)) : %.o : %.c	//filter过滤出.o文件 %.o:%.c:某个.o依赖于对应的.c文件
		$(CC) -c $(CFLAGS) $< -o $@
	$(filter %.elc, $(files)) : %.elc : %.el	//最终为foo.elc : foo.el(当有较多的相似依赖比较有用)
		cmd
***
## 第四章	规则的命令

### 4.1 命令回显

**命令行以"@"开始会取消回显，否则会回显.make -s/--silent或者目标".SILENT"取消所有回显**

**make的命令行参数"-n"或者"--just-print"会显示所要执行的命令，不会去真正执行这些命令，通常用于调试Makefile.**

### 4.2 命令的执行

**Makefile中同一行的多个命令属于一个shell命令行；在一个独立行的命令是一个shell命令行.不同的shell命令行互不影响.**
	
	foo : bar/lose
		cd bar; gobble lose > ../foo		//";"实现多个命令属于同一个shell命令行;也可以使用"\"连接不同的行形成同一个shell命令行
	//上述的cd到bar这个目录，不会对后面的命令行产生影响，还是处于当前目录.

### 4.3 并行执行命令

*make的help方法: "info make"*

**make的命令行参数"-j n"或者"--jobs n"告诉make同一时刻可以执行n条命令**

### 4.4 命令执行的错误

**有些命令执行失败不一定是执行错误(e.g.mkdir当存在某目录时会失败，但不是错误),可以使用"-mkdir"忽略该失败;也可以使用"make -i/--ignore-errors"忽略.**

**"make -k/--keep-going"可以检查修改文件中哪些文件可以被正确编译，哪些失败(主要用于调试Makefile或者查找源文件错误).**

*如果make失败了,修改错误之后正确的编译方法是:make clean再make.*

### 4.5 中断make的执行

**make在执行命令时如果收到致命信号(ctrl+c),make会删除已经重建的目标文件(e.g.一些".o"文件),确保下一次make时目标文件能够被正确重建.**

### 4.6 make的递归执行

	subsystem:
		cd subdir && $(MAKE)	//进入subdir目录后执行make
	等价于:$(MAKE) -C subdir		//make的-C选项，也是先进入subdir目录再执行make

**变量"MAKE"是"make"程序的文件名.因此如果多个目录下存在Makefile，使用"$(MAKE)"可以执行这些目录下的Makefile.**

**一个变量使用"export"声明后，该变量和变量的值会被加入到当前工作的环境变量中(即在子目录中也可以使用这些变量).**

*unexport取消变量的导出.*

**"make -w/--print-directory"在编译一个目录之前和编译之后给出一些提示信息(e.g.make: Entering directory... & make: Leaving directory...).默认自动打开该选项，取消方法(make -s/--no-print-directory).**

### 4.7 空命令

*只有目标文件(可以存在依赖文件),但没有命令行.*

	target : ;(cmd空)		//不使用重启一行+[tab]的方式,因为[tab]那一行看起来和空行没区别.

*空命令目的:防止make在重建target时查找隐含命令,空命令使用较少.*
***
## 第五章	Makefile中的变量

*推荐变量名全部采用大写方式(e.g. OBJS, CFLAGS),变量的引用使用"$(VAR)"方式.*

### 5.1 变量的定义

**递归展开式变量:通过"="或者define定义的变量，这种变量会在最后使用时才展开，嵌套使用容易死循环.**

	foo = $(bar)	//不会展开，因此可以引用之后定义的bar
	bar = $(ugh)	//不会展开，因此可以引用之后定义的ugh
	ugh = Huh?
	all : ; echo $(foo)		//引用才展开，最后打印:Huh?

**直接展开式变量:使用":="来定义变量,在定义的地方会直接展开(推荐使用这种方式).**

	x := foo	
	y := $(x) bar	//y为foo bar
	x := later		//x重新赋值为later

变量值尾到同行的注释"#"之间的空格是不会被忽略的，因此不能随便使用这种方式注释.

	dir := /foo/bar		#directory...(这种方式注释是不正确的，因为当中的空格是不会被忽略的)

注释内容推荐书写在独立的一行或者多行,可以防止意外情况的发生.

**条件赋值:"?="没有被赋值才会给予赋值，否则不赋值.**

**追加变量值:"+="实现对一个变量的追加操作.**

### 5.2 变量的高级用法

**变量的替换引用**
	
	foo := a.o b.o c.o
	bar := $(foo:%.o=%.c)	//将.o结尾的文件用.c来代替(%--模式匹配字符)

*引用一个没有定义的变量,make默认它的值为空.*

### 5.3 override指示符

**override:防止make命令行变量的值代替Makefile中变量定义的值，一般用于必须需要某个变量时.**

	override CFLAGS += -g	//必须打开调试开关"-g"，此时命令行变量不能取代Makefile变量定义的值.

	ifeq ("$(O)", "output")
	override O:=output_upg	//表示O变量不能被命令行传进来的值代替
	CONFIG_DIR:=$(TOPDIR)/$(O)
	EXTRAMAKEARGS += O=$(O)
	NEED_WRAPPER=y
	endif

define定义变量的语法:define开始,endef结束,之间为所定义的变量值

	define two_lines	//two_line为变量名
	echo foo
	echo $(bar)
	endef

**设置一个"CFLAGS"的环境变量,用来指定一个默认的编译选项.**

*环境变量"SHELL"默认是"/bin/sh":作为命令行的解释程序.可以使用:echo "shell is $(SHELL)"来打印出:shell is /bin/sh.*

### 5.4 模式指定变量

	%.o : CFLAGS += -O //指定为所有的.o文件的编译选项包含"-O"选项,不改变对其他文件类型的编译选项.
***
## 第六章	Makefile的条件执行

*条件表达式:以"ifeq ($(CC), gcc)"开始,"ifeq"和()之间有空格;else;以endif结束.*

### 6.1条件判断语法

**ifeq (arg1, arg2)/"arg1" "arg2"/'arg1' 'arg2':arg1,arg2可以用()/" "/' '包裹,判断两个参数是否相等.**

	ifeq ($(strip $(foo)),)
		text-if-empty
	endif

strip函数:去掉前导和结尾空格,将字符串之间的多个空格变成一个空格.

	data = "  a  b  c"
	$(strip $(data))  //其值为" a b c",因为""包括的整个都被视为字符串,因此去掉字符串之间的多个空格变为一个空格.
	data =    a   b  c
	$(strip $(data))  //其值为"a b c",会去掉前导空格，同时将字符串之间的多个空格变为一个空格.

**ifneq判断两个参数是否不相等(用法和ifeq相同).**

**ifdef VARIABLE:判断一个变量是否定义.只是测试一个变量是否有值,不会对变量进行扩展来判断.**

*除了"VARIABLE = ",其他方式定义均会判断为真,即使引用其他变量后最终VARIABLE的值为空也不会影响其判断为真.因此，如果判断为空使用"ifeq/ifneq."*
***
## 第七章	make的内嵌函数

**函数调用语法: $(FUNCTION ARGUMENTS)**

1)FUNCTION:调用的函数名.前面以"$"引用,都使用"()".

2)ARGUMENTS:函数参数.FUNCTION和ARGUMENTS之间使用一个"空格"分割,多个ARGUMENTS使用","分割.

### 7.1 文本处理函数

**$(subst FROM, TO, TEXT)**

把"TEXT"中的"FROM"字符替换为"TO",返回替换后的新字符串.

	$(subst ee, EE, feet on the street)	//返回值为:fEEt on the strEEt

**$(patsubst PATTERN, REPLACEMENT, TEXT)**

将"TEXT"中符合模式"PATTERN"替换为"REPLACEMENT".一般会使用"%"模式通配符,返回替换后的新字符串.

	$(patsubst %.c, %.o, x.c.c bar.c)	//返回值为:x.c.o bar.o

**$(strip STRINT)**

去掉"STRINT"前导和结尾空格,将字符串之间的多个空格变成一个空格.

	data = "  a  b  c"
	$(strip $(data))  //其值为" a b c",因为""包括的整个都被视为字符串,因此去掉字符串之间的多个空格变为一个空格.
	data =    a   b  c
	$(strip $(data))  //其值为"a b c",会去掉前导空格，同时将字符串之间的多个空格变为一个空格.

**$(findstring FIND, IN)**

搜索"IN",查找"FIND".找到返回"FIND";没找到返回空.

	$(findstring a, a b c)	//返回:a
	$(findstring a, b c)	//返回:空

**$(filter PATTERN..., TEXT)**

*过滤"TEXT"中所有不符合模式"PATTERN"的单词,保留符合此模式"PATTERN"的单词.一般会使用"%"模式通配符.*
	
	sources := foo.c bar.c baz.s ugh.h
	foo := $(sources)
		$(CC) $(filter %.c %.s, $(sources)) -o foo	//返回值为:foo.c bar.c baz.s(过滤掉了ugh.h)

**$(filter-out PATTERN..., TEXT)**

*反过滤,和filter实现的功能相反.*

**$(sort LIST)**

*给"LIST"中的单词以首字母排序(升序),并去掉重复的单词.返回排序并且没有重复的字符串.*

	$(sort foo bar lost foo)	//返回值为:bar foo lost

**$(word N, TEXT)**

*取"TEXT"中的第"N"个单词,返回该单词.如果N大于"TEXT"中的单词数目，返回空;如果N为0,出错.*

	$(word 2, foo bar baz)	//返回值为:bar

**$(wordlist S, E, TEXT)**

*取"TEXT"中从S到E的单词.S/E均从1开始.*

	$(wordlist 2, 3, foo bar baz)	//返回值为:bar baz

**$(words TEXT)**

*计算"TEXT"中单词的数目.*

	$(words foo bar)	//返回值为:2.如果取TEXT中的最后一个单词为:$(word $(words TEXT), TEXT).

**$(firstword NAMES...)**

*取"NAMES"中的第一个单词.*

	$(firstword foo bar)	//返回值为:foo

### 7.2 文件名处理函数

**$(dir NAMES...)**

从文件名序列"NAMES..."中取出各个文件的目录部分(目录部分:文件名最后一个斜线"/"(包括斜线)之前的部分);如果没有斜线就是当前目录(./).

	$(dir src/foo.c hacks)	//返回值为:src/ ./

**$(notdir NAMES...)**

从文件名序列"NAMES..."中取出各个文件的非目录部分(即为文件的具体名字).

	$(notdir src/foo.c hacks)	//返回值为:foo.c hacks

**$(suffix NAMES...)**

从文件名序列"NAMES..."取出各个文件名的后缀(后缀:最后一个以"."开始(包括点号)的部分),如果文件名不包含一个点号(".")则为空.

	$(suffix src/foo.c src-1.0/bar.c hacks)	//返回值:.c .c(hacks的返回为空)

**$(basename NAMES...)**

从文件名序列"NAMES..."取出文件名最后一个点号"."之前的部分(前缀部分),如果没有前缀，返回空.

	$(basename src/foo.c src-1.0/bar.c /home/jack/.font.cache-1 hacks)	//返回值为:src/foo src-1.0/bar /home/jack/.font hacks

**$(addsuffix SUFFIX, NAMES...)**

为文件名序列"NAMES..."中各个文件名添加后缀"SUFFIX".

	$(addsuffix .c, foo bar)	//返回值为:foo.c bar.c

**$(addprefix PREFIX, NAMES...)**

为文件名序列"NAMES..."中各个文件名添加前缀"PREFIX".

	$(addprefix src/, foo bar)	//返回值为:src/foo src/bar
	//例子
	$(addprefix $(OBJS_TMP)/,$(OBJS))	//增加前缀后,其值为$(OBJ_TMP)/$(OBJS)

**$(join LIST1, LIST2)**

将字符串"LIST1"和字符串"LIST2"各个单词一一对应连接(LIST2添加到LIST1之后).不一致的直接返回.

	$(join a b, .c .o)	//返回值为:a.c b.o
	$(join a b c, .c .o)	//f返回值为:a.c b.o c(c属于没有对应,直接返回)

**$(wildcard PATTERN)**

列出当前目录下所有符合模式"PATTERN"格式的文件名,<font size=2>"PATTERN"只能使用shell可识别的通配符"?"(单字符)、"*"(任意字符),不能使用"%".</font>

	$(wildcard *c)	//返回值为:当前目录下所有.c的源文件列表

### 7.3 foreach函数

**$(foreach VAR, LIST, TEXT)**

将"LIST"中的单词依次取出赋给"VAR"，然后执行"TEXT"表达式."TEXT"中的变量属于递归展开式,只有执行时才会展开.

	dirs := a b c d
	files := $(foreach dir, $(dirs), $(wildcard $(dir)/*))	//等价于:files := $(wildcard a/* b/* c/* d/*)
	/*下面是在buildroot顶层Makefile中(line:1024)*/
	$(foreach b, $(sort $(nodir $(wildcard $(TOPDIR)/configs/*_defconfig))), \
		printf  " %-35s - Build for %s \\n" $(b) $(b:defconfig=);)
### 7.4 if函数

**$(if CONDITION, THEN-PART, ELSE-PART)**

	SUBDIR += $(if $(SRC_DIR), $(SRC_DIR), /home/src)	//如果"SRC_DIR"变量值不为空，
	则将"SRC_DIR"目录作为一个子目录;否则将"/home/src"作为一个子目录.

### 7.5 call函数

**$(call VARIABLE, PARAM，PARAM,...)**

将参数"PARAM"依次赋值给临时变量$(1),$(2),...(这些变量定义在VARIABLE变量值中).其中$(0)是"VARIABLE"变量本身.

	/*实例1*/
	reverse	= $(2) $(1)
	foo = $(call reverse, a, b)		#返回值为:ba
	/*实例2*/
	define target
		echo $@		#通过call函数传过来的参数被当作$@(目标对象)
		echo $@
	endef			#define...endef规则
	all:
		$(call target, all/$@)		#传进去参数all/$@(也表示all).是第一个参数$1

### 7.6 value函数

**$(value VARIABLE)**

不对变量"VARIABLE"进行任何展开操作,直接返回"VARIABLE"代表的值.

	FOO = $PATH
	all :
		@echo $(FOO)	//返回值为:ATH ($P为空)
		@echo $(value FOO)	//返回值为:$PATH的值即系统环境变量"PATH"的值(因为变量FOO的值为$PATH) 

### 7.7 origin函数

**$(origin VARIABLE)**

origin函数查询变量"VARIABLE"从哪里来.返回值分别为:underfined(没定义)/default(内嵌变量)/environment & environment override(系统环境变量)/override(使用override指示符定义)/automatic(自动化变量)

	/********************实例********************/
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
		因为O没有,因此第一句会输出"undefined".即出处没有被定义
		BUILD_DIR没有定义,所以BUILD_DIR为空.会直接输出一个空行
	*/
	/*运行2*/
	make O=/home
	/*
		输入了参数"O=/home".此时$(origin O)会得到"command line"
		BUILD_DIR有定义.因此$(BUILD_DIR)会得到"/home"
	*/
	/*运行3*/
	/*
		如果在Make文件中已经写了"O = /home".此时$(origin O)会得到"file"的返回值
	*/
	/*其他的还有:
		1.environment--->export O=/home	//导出了环境变量
		2.default--->略
		3.override--->略
		4.automatic--->略
	*/

	/*顶层Makefile中的实例*/
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

函数返回为参数"param"在shell中的执行结果.

	contents := $(shell cat foo)	//contents被赋值为文件"foo"的内容
	files := $(shell echo *.c)	//变量files被赋值为当前目录下所有.c的文件列表

### 7.9 error和warning函数

**$(error text...)**

产生致命错误,并提示"text..."信息给用户,并退出make的执行.

	$(if $(BASE_DIR), , $(error output directory "$(O)" dose not exist))
	//判断BASE_DIR如果为空,产生致命错误,并输出"output directory "$(O)"(的值) does not exit".
	//并退出make的执行.

**$(warning text...)**

类似于error函数.但是不会导致致命错误(make不退出).只是提示"text...",make执行过程继续.

***

## 第八章	执行make

**部分标准的目标,伪目标,空目标命名：**

all:终极目标;

clean:伪目标,删除所有由make创建的文件.

mostlyclean:与clean相似,但不会全部删除.

disclean/realclean/clobber:与clean相似,但删除的更彻底(e.g.编译之前一些系统配置文件,链接文件等).

install:将make成功创建的可执行文件拷贝到shell环境变量"PATH"指定的目录(e.g.应用可执行文件拷贝到"/usr/local/bin",库文件拷贝到"/usr/local/lib").

print:打印出所有被更改的源文件列表.
	
check/test:对Makefile最后生成的文件进行检查.

### 8.1 make替代命令的执行

**make命令行参数为以下时可达到的目的:**

-n/--just-print/--dry-run/recon:只打印过期的目标的重建命令,但不对目标进行重建.

-t/--touch:对过期的目标文件,只更新时间戳,但不对目标文件内容进行更新.

***

## 第九章	make的隐含规则

### 9.1 隐含规则的使用

隐含规则提供的依赖文件只是一个最基本的("EXENAME.o"对应"EXENAME.c").如果需要增加某个目标的依赖文件时,要在Makefile中使用<font size=4>"没有命令行"的规则来明确说明</font>.

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

*其他命令可以使用"ls --help"查看支持的命令行选项.*

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

***

# Makefile碰到的问题
***
## 1.把目录当成文件来操作

	make: execvp: /zhsa022/usrhome/defy.chen/repository/work_viaccess/buildroot: Permission denied
	/*错误原因:If you see an error like this when you run make, it means make is attempting to execute a directory, 
	not a program. Which means you probably have extra spacing in one of your variables in your config/make files.*/
	/*问题描述:将目录当成了文件来操作.原因:是因为在Makefile中指定buildroot路径时,后面多加了一个"空格"*/

## 2.从git上只拉下源码的方法

	make alisee-source		//将alisee的源码拉下来

## 3. cc、gcc、g++、CC的区别

	cc:是Unix系统的C Compiler,为商业软件.在linux下一般是一个符号链接,指向gcc.目前cc使用的很少了.
	gcc:GNU Compiler Collection,GNU编译器套装,包含很多编译器(c、c++、Objective-c、Fortran、Java).一般使用gcc
	g++:g++可以编译C/C++代码.与gcc区别:
		1)".c"文件,gcc当作C程序,gcc当作C++程序.".cpp"两者都认为是C++程序.
		2)对于宏"__cplusplus"---指示编译器将代码按C还是C++语言来解释.如果后缀为.c,并且采用gcc编译器,则该宏是未定义的.
			否则就是已定义的.
	CC:一般是Makefile中的一个名字.


