# Visual Studio(2012) Skills

## 1.在Visual Sudio 2012中显示行号

	工具->选项->文本编辑器->C/C++->常规->将行号勾选上.

## 2.当用vs2012打开vs2013或者更高版本的工程时报"工具集未知或丢失"的错误

低版本打开高版本工程报"项目文件包含 ToolsVersion="12.0"。此工具集可能未知或缺失(您可以通过安装相应版本的 MSBuild 来解决该问题)...".解决方法如下:

	调试->xxx(文件名)属性->配置属性->常规->在常规的"平台工具集"中选择"Visual Studio 2012(v110)"即可.

## 3."error LNK2038"的错误解决

当出现"error LNK2038:检测到"RuntimeLibrary"的不匹配项:值"MDd_DynamicDebug"不匹配值"MTd_StaticDeb ug""的错误.

原因:因为几个工程使用的运行库的不一样,需要修改某些工程的运行库设置.

解决:

	打开需要修改的工程->调试->xxx(文件名)属性->配置属性->C/C++->代码生成->运行库中选择
		"多线程调试(/MTd)".

碰到该问题的情况:

	1.配置了SystemC的文件的运行库为"多线程调试(/MTd)";
	2.在编译SystemC.lib时使用的运行库是其他,导致在运行SystemC的文件出现该问题.使用前面方法即可解决.

## 4.VS2012添加SystemC库的支持

**1.下载SystemC库**

[SystemC库下载网址](https://accellera.org/downloads/standards/systemc)

	下载类似SystemC 2.3.3(Include TLM)中的"Core SystemC Language and Examples (tar.gz)".

**2.编译出SystemC.lib**

	1.解压下载的SystemC库(e.g.G:\systemc-2.3.3);
	2.打开"G:\systemc-2.3.3\msvc10\SystemC"目录下的
		"SystemC.sln";
	3.打开之后->生成(B)->生成解决方案.编译成功后(忽略Warning),在"G:\systemc-2.3.3\msvc10\SystemC"
		目录下增加了一个Debug目录,并在Debug目录下生成SystemC.lib.

**3.在VS2012添加SystemC库的支持**

1.新建一个控制台应用程序,并编写:

	#include <iostream>
	#include "systemc.h"	//这些头文件会报不存在
	using namespace std;
	
	SC_MODULE(hello) {
		SC_CTOR(hello) {
			cout << "Hello, SystemC!" << endl;
		}
	};
	
	int sc_main(int argc, char *argv[])
	{
		hello h("hello");
		return 0;
	}

2.添加SystemC库

	1.调试->xxx(文件名)属性->配置属性->C/C++中:
		常规->附加包含目录->选择"G:\systemc-2.3.3\src";
		语言->启用运行时类型信息->选择"是";
		代码生成->运行库->选择"多线程调试(/MTd)";
		命令行->在其他选项中添加"/vmg /D_CRT_SECURE_NO_DEPRECATE";
	2.调试->xxx(文件名)属性->配置属性->链接器中:
		常规->附加库目录->选择"G:\systemc-2.3.3\msvc10\SystemC\Debug";
		输入->附加依赖项->在最后"odbccp32.lib;SystemC.lib;%(AdditionalDependencies)"
			添加上"SystemC.lib".

3.编译运行即可.
