# Chapter 1 初识cmake

## 1.1 cmake背景

cmake的流行归功于KDE4(2008-01-11发布)的开发,之前的KDE版本使用autotools,在KDE4后完全使用cmake进行构建.

```
KDE是一个用于UNIX工作站的现代化桌面环境.其他的桌面环境包括:Unity,GNOME,XFCE,LXDE等.
```

## 1.2 cmake特点

cmake具有如下特点:

```
1.开放源代码,使用类BSD许可发布
2.跨平台,并可生成native编译配置文件:
	在Linux/Unix平台,生成makefile
	在苹果平台,可以生成xcode
	在Windows平台,可以生成MSVC的工程文件
3.能够管理大型项目,KDE4就是最好的证明
4.简化编译构建过程和编译过程:
	make的工具链非常简单--->cmake+make
5.高效性:
	CMake构建KDE4的kdelibs要比使用autotools来构建KDE3.5.6的kdelibs快40%,主要是因为cmake在工具链中没有libtool
6.可扩展性
	可以为cmake编写特定功能的模块,扩展cmake功能
```

## 1.3 cmake安装

cmake目前已经成为各大linux发行版提供的组件,一般不需要安装.如果需要安装,ubuntu安装方法:

```
apt install cmake	// 我的ubuntu 16.x默认没有安装cmake,手动安装即可.
```

# Chapter 2 初试cmake

新建一个测试目录:cmake_test

## 2.1 源代码及编译脚本

在cmake_test目录下建立main.c和CMakeLists.txt(名字必须是这样的).

### 2.1.1 源代码main.c

main.c内容如下:

```
#include <stdio.h>
int main()
{
	printf("Hello world!\n");
	return 0;
}
```

### 2.1.2 编译脚本CMakeLists.txt

CMakeLists.txt内容如下:

```
PROJECT (HELLO)
SET(SRC_LIST main.c)
MESSAGE(STATUS "This is BINARY dir " ${HELLO_BINARY_DIR})	//变量的取值使用${}
MESSAGE(STATUS "This is SOURCE dir " ${HELLO_SOURCE_DIR})
ADD_EXECUTABLE(hello ${SRC_LIST})
```

## 2.2 构建、编译、运行

### 2.2.1 构建

在cmake_test目录下执行:

```
cmake .	//“.”:表示在当前目录下
```

执行后会输出如下信息:

```
-- The C compiler identification is GNU 5.4.0
-- The CXX compiler identification is GNU 5.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- This is BINARY dir /home/defychen/repository_test/cmake_test
-- This is SOURCE dir /home/defychen/repository_test/cmake_test
-- Configuring done
-- Generating done
-- Build files have been written to: /home/defychen/repository_test/cmake_test
```

构建成功后会在目录下自动生成下面几个文件:

```
CMakeCache.txt\CMakeFiles(目录)\cmake_install.cmake\Makefile
```

### 2.2.2 编译

构建成功后会自动生成Makefile,编译只需要再执行"make"即可.会输出如下信息:

```
Scanning dependencies of target hello
[ 50%] Building C object CMakeFiles/hello.dir/main.c.o
[100%] Linking C executable hello
[100%] Built target hello
```

如果需要显示make执行的详细过程,可以执行:

```
make VERBOSE=1
```

此时在当前目录下会生成可执行文件"hello".

### 2.2.3 执行

运行生成的"hello"

```
./hello
```

输出:

```
Hello world!
```

### 2.2.4 CMakeLists.txt语法解析

#### 2.2.4.1 PROJECT语法

PROJECT用于对工程进行设置.

```
PROJECT(projectname [CXX][C][Java])
/*
	projectname:定义工程名称,名称指定后会隐式的生成两个cmake变量:projectname_BINARY_DIR和projectname_SOURCE_DIR.
		上述代码会自动生成2个cmake变量:HELLO_BINARY_DIR和HELLO_SOURCE_DIR.
		上述代码采用内部编译,因此两个变量的值为:
		${HELLO_BINARY_DIR}--->/home/defychen/repository_test/cmake_test
		${HELLO_SOURCE_DIR}--->/home/defychen/repository_test/cmake_test
		如果是外部编译,两个变量的值就会不一样.
		cmake系统也预定义了PROJECT_BINARY_DIR和PROJECT_SOURCE_DIR变量,与projectname_BINARY/SOURCE_DIR是一样的.
		--->今后使用:PROJECT_BINARy_DIR和PROJECT_SOURCE_DIR,这样修改了工程名,不需要修改变量名.
	[CXX][C][Java]:指定工程支持的语言,默认表示支持所有语言,因此一般省略.
*/
```

#### 2.2.4.2 SET语法

SET用于定义变量.

```
SET(VAR [VALUE] [CACHE TYPE DOCSTRING[FORCE]])
/*
	VAR:变量名
	[VALUE]:变量值.
*/
SET(SRC_LIST main.c test.c)	// 定义SRC_LIST变量,指代源文件列表(多个源文件用空格分隔)
```

#### 2.2.4.3 MESSAGE语法

MESSAGE用于向终端输出用户定义的信息.

```
MESSAGE([SEND_ERROR | STATUS | FATAL_ERROR]"message to display")
/*
	para1:消息级别.
		SEND_ERROR:产生错误,生成过程被跳过;
		STATUS:后面的字符串加上前缀"--";
		FATAL_ERROR:立即终止cmake过程.
	para2:字符串,需要输出的信息.
*/
```

#### 2.2.4.4 ADD_EXECUTABLE语法

定义生成的可执行文件名及相关的源文件列表.

```
ADD_EXECUTABLE(exec_name src_list)
/*
	para1:可执行文件名;
	para2:依赖的源文件列表
*/
ADD_EXECUTABLE(hello ${SRC_LIST})	//表示生成的可执行文件是hello,由其后的源文件编译得到.
```

### 2.3 工程清理

与经典的autotools系列工具一样,只需要运行:

```
make clean	//只会将将生成的可执行文件删掉,其他生成的文件不会被删掉.
```

cmake不能使用make distclean.

### 2.4 内部构建(in-source build)和外部构建(out-of-source build)

#### 2.4.1 in-source build

```
上述的构建方式是一种in-source build,此时会在源代码目录下生成很多临时文件,不美观.现代工程更多的采用out-of-source build.
```

#### 2.4.1 out-of-source build

方法如下:

```
1.清除构建的中间文件
    make clean	//删掉可执行文件
    rm -rf CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
2.创建build目录
	mkdir build
3.构建
	cd build
	cmake ..	//因为CMakeLists.txt在上一层目录
	//执行后,在build目录就会生成所需要的中间临时文件
4.编译
	make	//在build目录make即可,编译后在build目录会生成可执行文件hello
5.执行
	./hello
```

out-of-source build的特点:

```
1.对原有工程无影响,所有的编译动作发生在build目录;
2.PROJECT_SOURCE_DIR变量的值为:/home/defychen/repository_test/cmake_test
3.PROJECT_BINARY_DIR变量的值为:/home/defychen/repository_test/cmake_test/build
```













































