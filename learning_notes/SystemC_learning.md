# SystemC Leaning

***

## Chapter 1 前言

### 1.1 SystemC的入门

现代片上系统的设计之难源于其复杂性,复杂性催生SystemC(系统级设计语言)和电子系统级设计(Electronic System Level, ESL)方法学.

**1.系统级仿真**

	1.目的:确认设计的体系架构是否恰当、总线是否能够满足吞吐量和实时性要求以及存储器是否被浪费;
	2.时间:系统级仿真先于RTL设计;
	3.语言:一般使用UML,C,C++等.

**2.RTL级设计**

	1.RTL:Register Transfer Level,寄存器传输级;
	2.语言:VHDL和Verilog HDL;
	3.特点:在系统级仿真后面,由于系统级设计使用C/C++,因此需要手工从C/C++代码转换成VHDL/Verilog HDL代码;
	4.效率:手工编写RTL代码效率不高.

**3.ESL设计**

	1.ESL:Electronic System Level,电子系统级设计;
	2.语言:SystemC和C/C++,SystemC是C++的扩展库;
	3.特点:可以进行系统级仿真,速度快,且语言基于现有语言,环境、编译和调试工具可以复用现有的,效率高.

**4.SystemC和System Verilog的使用范围**

	1.SystemC:特别适合于建模体系结构,开发事物处理级(TL)模型和在验证中描述软件的行为;
	2.System Verilog:是进行RTL设计的最佳语言.

### 1.2 一个"Hello, SystemC!"建模实例

	/*1.类定义*/
	#include <iostream>
	#include "systemc.h"	//SystemC的头文件
	SC_MODULE(hello) {
	/*
	SC_MODULE是SystemC中定义的一个宏,表示生成一个类.括号中的"hello"即为类名.
	*/
		SC_CTOR(hello) {
		/*
		SC_CTOR也是一个宏.表示生成构造函数.括号中的"hello"为构造函数名,与类名相同.
			cout << "Hello, SystemC!" << endl;
		*/
		}
	};

	/*2.SystemC的main函数*/
	int sc_main(int argc, char *argv[]) {
		/*sc_main相当于C的main函数,即为入口函数*/
		hello h("hi");	//hello为之前定义的类名,构造一个实例对象
		return 0;
	}

***

## Chapter 2 SystemC基本语法

### 2.1 一个典型的SystemC的程序设计

设计一个宽8位,深256的静态存储器的基本模型.

**头文件定义**

	//sram8x256.h
	#ifndef __SRAM8x256_H__
	#define __SRAM8x256_H__

	#include "systemc.h"
	#include "assert.h"
	
	SC_MODULE(sram8x256)	//模块定义,类似类定义
	{
		sc_in_clk clk;			//输入时钟
		sc_in<bool> wr_en;		//写使能输入端口
		sc_in<sc_uint<8>> wr_data;	//写数据输入端口
		sc_in<sc_uint<8>> addr;		//读写地址输入
		sc_out<sc_uint<8>> rd_data;	//读数据输出端口

		void main()	//进程
		{
			rd_data.write(mem[addr.read()]);
			/*
				addr.read():将地址读出来;
				mem[addr.read()]:取读到地址的数据;
				rd_data.write(mem[addr.read()]):将取到的地址数据写入到读数据输出端口
			*/
			if (wr_en.read())	//读到写数据使能
			{
				mem[addr.read()] = wr_data.read();
				//将写数据输入端口的数据读出来写入到输入的地址
			}
		}

		SC_CTOR(sram8x256)
		{
			mem = new sc_uint<8>[256];	//分配8x256的空间
			assert(mem != NULL);	//断言可以分配到空间
			for (int i = 0; i < 256; ++i)
				mem[i] = 0;	//初始化
			SC_METHOD(main);	//创建方法进程
			sensitive << clk.pos();	//产生激励,上升沿触发
		}

		~sram8x256()
		{
			if (mem) {
				delete mem;	//释放申请的内存
				mem = 0;
			}
		}
	private:
		sc_uint<8> *mem;	//私有mem变量
	};

	#endif

