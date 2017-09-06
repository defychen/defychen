# Begining Linux Programming(Linux程序设计)
***
## Chapter 1 入门

### 1.1 Unix、Linux和GNU简介

**略**

### 1.2 Linux程序设计

**Linux程序**

	/bin:二进制文件目录,用于存放系统启动时用到的程序;
	/usr/bin:用户二进制目录,用于存放用户使用的标准程序;
	/usr/local/bin:本地二进制文件目录,用于存放软件安装的程序.
	/opt:存放可选的操作系统组件和第三方应用程序.

PATH变量:

	/usr/local/bin:/bin:/usr/bin:.:/home/neil/bin:/usr/X11R6/bin
	标准程序存放位置		当前目录"."	home目录		X视窗系统目录
	Linux使用"/"分割文件中的目录名,windows使用"\"分割

**头文件**

	gcc -I/usr/openwin/include fred.c	//查找非标准位置的头文件(-I"紧跟着路径")	
	//例子
	CFLAGS := -I../c3922_latest/output/build/linux-xxx/drivers/alidrivers/include
	gcc $(CFLAGS) -c $< -o $@

**库文件**

1)库是一组预先编译好的函数的集合.

2)标准系统库文件一般存储在"/lib"和"/usr/lib"目录中.

3)库文件名字总是以"lib"开头,随后部分指明是什么库(libm.a---数序库).

4)".a"传统的静态函数库;".so"共享函数库.

	gcc -o fred fred.c /usr/lib/libm.a	//使用完整库路径搜索库文件(libm.a)
	gcc -o fred fred.c -lm		//标准库路径(usr/lib)中搜索"libm.a"的函数库文件----lm为libm.a的简写方式
	gcc -o x11fred -L/usr/openwin/lib x11fred.c -lX11
	//"-L"增加库搜索路径;  库文件为:libX11

"-L"指定库搜索路径; "-l":指定库文件名

**静态库**

静态库:也叫归档文件(archive),".a"结尾(e.g./usr/lib/libc.a---标准c语言函数库)

创建静态库:

1)使用gcc -c对函数文件进行编译(生成".o"文件)---仅仅只是编译;

2)使用"ar(archive)"命令建议归档文件(即静态库)---ar crv libtest.a xxx.o xxx.o

实例:

	step 1:
	//头文件testlib.h,库文件中的函数的声明
	void fred();
	void bill();
	//第一个源文件fred.c,仅仅只是一个函数.无main函数
	#include <stdio.h>
	#include "testlib.h"
	void fred()
	{
		printf("xxxxx");
	}
	//第二个源文件bill.c,仅仅只是一个函数,无main函数
	#include <stdio.h>
	#include "testlib.h"
	void bill()
	{
		printf("yyyyy");
	}
	
	step 2:
	//仅仅编译两个源文件
	gcc -c fred.c bill.c		//仅仅编译"-c",得到"fred.o和bill.o".无main函数
	
	step 3:
	//使用"ar"创建库文件
	ar crv libtest.a fred.o bill.o	//得到libtest.a的静态库文件
	ranlib libtest.a		//为函数库生成一个内容表(linux中不需要,本身已经做了.但是再做一次也没关系)
	
	step 4:
	//调用程序program.c,会调用库中的函数
	#include <stdlibh>
	#include <testlib.h>
	int main()		//此时才有main函数
	{
		bill();		//调用库中的函数	
		return 0;
	}
	
	step 5:
	//调用库文件编译应用程序
	gcc -c program.c	//先编译program.c文件成为program.o
	gcc -o program program.o libtest.a	//因为库在和源文件在一个目录下,可以这样编译(但库文件必须是完整文件名)
	//通常使用的方法
	gcc -o program program -L. -ltest	//指定非标准库路径.此处"-L."当前目录,"-ltest"查找libtest.a/libtest.so库文件.

	//查看program中包含哪些函数
	nm program	//nm:查看可执行文件、库文件或目标文件包含哪些函数

**共享库**

共享库的后缀为".so"---e.g.标准数学库的共享库版本是:/usr/lib/libm.so

共享库优点:

系统只保留共享库的一份副本供需要调用的应用程序使用,磁盘上也仅有一份.

静态库在应用程序每调用一个地方就会有一份副本(多个应用程序调用就会有多份副本).使用共享库程序本身不会包含库函数代码,仅在需要使用时才会被加载到内存中.
***
## Chapter 2 Shell程序设计

**shell默认情况下认为所有变量包含的都是字符串.**

	#!/bin/sh	//指定执行本文件的程序"/bin/sh"

	#first...	//一些注释
	for file in *	//循环遍历
	do
		if grep -q POSIX $file	//在遍历到的每一个文件中($file)查找"POSIX",并且没有任何输出到标准输出"-q表示quit/silent"
		then
			echo $file
		fi
	done

	exit 0	//返回一个退出码.一般的脚本里没有,可有可无.

### 2.1 shell变量

**普通变量---通常使用小写字母做名字**

	#!/bin/sh
	myvar="Hi there"	//1)等号两边不能有空格;2)赋值的值中有空格,必须使用双引号括起来
	
	echo $myvar			//正常显示"Hi there"
	echo "$myvar"		//正常显示"Hi there"
	echo '$myvar'		//单引号显示不正确,不会替换,显示为"$myvar"
	echo \$myvar		//转义了,显示不正确,显示为"$myvar"

	echo Enter some text
	read myvar			//读取用户的输入命令"read",并且存放在myvar中
	
	echo '$myvar' now equals $myvar	//显示为:$myvar now equals Hello World
	exit 0
	
**环境变量---通常使用大写字母做名字**

	$HOME	//home目录
	$PATH	//冒号分隔的搜索命令的目录列表
	$0		//shell脚本的名字		e.g. echo $0	---显示为"-bash",表示使用bash
	$#		//传递给脚本的参数个数
	$$		//shell脚本的进程号

**参数变量---$0、$1、$2...**

	//脚本程序在执行时,即使不带参数.但是$#(传递给脚本的参数个数)也有值,为0.
	./try_var foo bar baz
	在try_var脚本当中解析该参数为:
	1)$0---其值为"./try_var"
	2)$1/$2/$3---其值为"foo"/"bar"/"baz"
	3)$*---其值为"foo bar baz",不包括"$0"
	//访问方式可以为:
	echo "The parameter list were $*"	//显示所有参数变量

### 2.2 条件

	// 方法1:
	if test -f fred.c	//检查fred.c文件是否存在
	then
	...
	fi
	// 方法2:
	if [ -f fred.c ]	; then	//1)[]两边必须有空格; 2)"; then"可以写在同一行
	...
	fi

**条件类型**

1)字符串比较

	string1 = string2 		//如果两个字符串相同结果为真---等号两边必须有空格
	string1 != string2		//如果两个字符串不同结果为真---等号两边必须有空格
	-n string				//如果字符串不为空结果为真
	-z string				//如果字符串为空(null)结果为真

2)算术比较

	expression1 -eq expression2		//如果两个表达式相等结果为真
	expression1 -ne	expression2		//如果两个表达式不等结果为真
	expression1 -gt	expression2		//如果expression1大于expression2结果为真
	expression1 -ge	expression2		//如果expression1大于或等于expression2结果为真
	expression1 -lt	expression2		//如果expression1小于expression2结果为真
	expression1 -le	expression2		//如果expression1小于或等于expression2结果为真
	！ expression					//如果表达式为假结果为真. 取反符"!"和expressionz之间有空格

3)文件测试

	-d file		//如果file是一个目录结果为真
	-f file		//如果file是一个普通文件结果为真
	-r file		//如果file可读结果为真
	-s file		//如果file大小不为0结果为真
	-w file		//如果file可写结果为真
	-x file		//如果file可执行结果为真

实例

	#/bin/sh
	if [ -f /bin/bash ]	//测试/bin/bash是一个普通文件
	then
		echo "file /bin/bash exists"
	fi
	
	//测试/bin/bash是一个目录
	if [ -d /bin/bash ]; then
		echo "/bin/bash is a directory"
	else
		echo "/bin/bash is NOT a directory"
	fi

### 2.3 控制结构

**if语句**

	#!/bin/sh
	echo "Is it morning? Please answer yes or no..."
	read timrofday
	if [ "$timeofday" = "yes" ]; then		//"$timeofday":避免空格带来的影响
		echo "Good morning"
	elif [ "$timeofday" = "no" ]; then
		echo "Good afternoon"
	else
		echo "Sorry, "$timeofday" not recognized. Enter yes or no"
		exit 1		//一个错误的返回值
	fi
	exit 0

**for循环**

	#!/bin/sh
	for file in $(ls f*.sh); do		//可以写在一行
		echo $file
	done
	exit 0

	//语法结构
	for variable in value
	do
		...
	done

**while语句**

	#!/bin/sh
	echo "Enter password"
	read trythis
	while [ "$trythis" != "secret" ]; do
		echo "Sorry, try again"
		read trythis
	done
	exit 0

**until语句**

	#!/bin/sh
	
	until who | grep "$1" > /dev/null	//until为假时一直循环;为真跳出循环
	//who:查看linux所有的用户名;grep搜索"$1"参数指定的用户名.如果搜索到结果不为空,此时为真.跳出循环.否则一直循环
	do
		sleep 60	//休眠60s
	done

	echo "****$1 has just logged in****"
	exit 0

**case语句---任意一个匹配都会直接退出case**

	#!/bin/sh
	
	echo "Is it morning? Please answer yes or no"
	read timeofday
	
	case "$timeofday" in
		yes | y | Yes | YES )	//匹配多个,匹配项以")"结尾
			echo "Good morning"
			echo "Up bright and early this morning"
			;;		//两个";;"一个标记前一个匹配项的结束;一个标记后一个匹配项的开始
		n* | N* )
			echo "Good afternoon"
			;;
		*)	//都匹配不成功的默认行为.default
			echo "Sorry, answer not recognized"
			echo "Please answer yes or no"
			exit 1	//default时的退出
	esac		//与case相反
	exit 0
	
**AND列表---&&**

	#!/bin/sh
	
	touch file_one
	rm -rf file_two
	if [ -f file_one ] && echo "hello" && [ -f file_two ] && echo "there"
	//file_one判断成功,会打印"hello"; echo总是返回成功; file_two不存在,判断失败,后面不会执行
	then
		echo "in if"	//不会打印
	else
		echo "in else"	//打印
	fi
	exit 0

**OR列表---||**

	rm -rf file_one	//修改"&&"中的代码
	if [ -f file_one ] || echo "hello" || echo "there"
	//file_one因为不存在,所以判断失败; echo总是返回成功.因此整个条件判断成功

### 2.4 函数

	#!/bin/sh
	yes_or_no(){
		echo "Is your name $* ?"
		while true
		do
			echo -n "Enter yes or no: "
			read x
			case "$x" in
				y | yes) return 0;;
				n | no) return 1;;
				*) echo "Answer yes or no"
			esca
		done
	}

	echo "Original parameters are $*"
	
	if yes_or_no "$1"	//1)会将"$1"参数传进函数; 2)是通过test来测试返回值(返回0表示true;1表示false---shell诡异的地方)
	then
		echo "Hi $1, nice name"
	else
		echo "Never mind"
	fi
	exit 0

	//该程序会显示为:
	./test.sh defy chen
	Original parameters are defy chen
	Is your name defy ?
	Enter yes or no: yes
	Hi defy, nice name		//返回0,shell中的test会为true
	
### 2.5 命令

**break命令**

break命令用于for、while、until循环,只跳出一层循环.

**:命令**

冒号(:)命令是一个空命令,偶尔用于简化条件逻辑,相当于true的一个别名(while :---相当于while true).---用的比较少.

**continue命令**

continue命令和C语言的用法一样.

**.命令**

略

**echo命令**

	echo -n "string to output"		//-n:去掉结尾换行符

**eval命令**

eval命令是对参数进行求值.

	/*没有使用eval*/
	foo=10
	x=foo
	y='$'$x
	echo $y		//会输出"$foo",因为没有转换为值
	/*使用了eval*/
	foo=10
	x=foo
	eval y='$'$x	//eval对参数求值,并赋给y
	echo $y		//输出数值10

**exec命令**

将当前的shell替换为一个不同的程序---这个命令用的比较少

	exec wall "Thanks for all the fish"		//用wall替换当前的shell,后面的"Thanks..."也不会执行了

**exit n命令**

在shell脚本编程中,退出码0表示成功(在shell的if判断中,0判断为true---shell特殊的地方).

**export命令**

export导出来的变量可以被shell的所有脚本和程序直接引用.

	/*export2 脚本*/
	#!/bin/sh
	
	echo "$foo"		//引用一个没有export出来的变量.属于一个null变量,会打印一个空行
	echo "$bar"		//引用一个export出来的变量,会打印出该变量

	/*export1 脚本*/
	#!/bin/sh
	
	foo="The first meta-syntactic variable"
	export bar="The second meta-syntactic variable"		//export出bar变量,export2 脚本可以接收到
	
	export2		//调用export2 脚本

	//结果
	./export1
										//echo "$foo"属于一个null变量,因此会打印出一个空行
	The second meta-syntactic variable	//打印export出来的bar变量

**expr命令**

expr命令将它的参数当作一个表达式来求值.

	x=`expr $x + 1`	//1)expr计算$x + 1的值; 2)``(反引号):使x取值为"expr $x + 1"计算的结果
	//也可以使用$()替换``---反引号
	x=$(expr $x + 1)

**printf命令**

printf在最新版本的shell才存在,用来代替echo命令.其使用和C/C++中一样.

	printf "%s\n" "hello"		//虽然不带引号的hello也能输出正确值,但是还是需要符合常规的写法
	printf "%s %d\t%s\n" "Hi there" 15 "people"

**return命令**

return是使函数返回.

**set命令**

set是为shell设置参数变量(即可以分离由空格分隔的值,是这些值变为参数变量---e.g.$1、$2、$3...)

	#!/bin/sh
	
	echo the date is $(date)	//打印出当前的日期(Thu Jul 27 14:08:06 CST 2017)
	set $(date)		//将date设置为参数变量
	echo The month is $2	//会打印出(The month is Jul)
	exit 0

**shift命令**

shift命令将所有参数变量左移一个位置(e.g.$2变为$1; $3变为$2.原来的$1的值会被丢弃,$0不变)

	#!/bin/sh
	
	while [ $# != 0 ]; do	//$#代表参数的个数
		echo "The first parameter is: $1, parameter number is: $#"
		shift		//每执行一次会将参数依次左移
	done

	//测试命令:
	./run.sh a b c d e f
	//结果为:
	The first parameter is: a, parameter number is: 6
	The first parameter is: b, parameter number is: 5
	The first parameter is: c, parameter number is: 4
	The first parameter is: d, parameter number is: 3
	The first parameter is: e, parameter number is: 2
	The first parameter is: f, parameter number is: 1

**trap命令**

查看linux信号编号及其关联的名称:
		
	trap -l

**unset命令**

unset命令是从环境中删除变量或函数.

	#!/bin/sh
	
	foo="Hello world"
	echo $foo

	unset foo		//删除foo变量
	echo $foo		//变量已经不存在,此时只输出一个换行符

**find命令**

	find [path] [options] [tests]
	/*例子*/
	find . -name file_name

**grep命令**

	grep 搜索字符串 . -nr		//.:当前目录; -nr:显示行数
***

## Chapter 3 文件操作


	
