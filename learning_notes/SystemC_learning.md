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

### 1.3 一个二输入与非门建模实例

**1.nand2.h**

	#ifndef __NAND2_H__
	#define __NAND2_H__
	
	#include <systemc.h>
	SC_MODULE(nand2) {
		sc_in<bool> A;		//输入信号A
		sc_in<bool> B;		//输入信号B
		sc_out<bool> F;		//输出信号F
		void do_nand() {
			F = !(A & B);	//与非,得到F的值
		}
	
		SC_CTOR(nand2) {
			SC_METHOD(do_nand);		//SC_METHOD(do_nand):表示进程do_nand
			sensitive << A << B;	//进程do_nand对A,B信号敏感.一旦A,B信号发生变化,则会调用进程一次
		}
	};
	
	#endif

**2.testbench定义**

	#ifndef __TB_H__
	#define __TB_H__
	#include <iostream>
	#include <systemc.h>
	
	SC_MODULE(tb) {
		sc_out<bool> a, b;
		sc_in<bool> f;
		sc_in_clk clk;
		void gen_input(){
			wait(); a = 0; b = 0;
			wait(); a = 0; b = 1;
			wait(); a = 1; b = 0;
			wait(); a = 1; b = 1;
			wait(100);
		}
	
		void display_variable(){
			cout << "a = " << a << ", b = " << b << ", f = " << f << endl;
		}
	
		SC_CTOR(tb){
			SC_CTHREAD(gen_input, clk.pos());
			/*
			SC_CTHREAD(gen_input, clk.pos()):表示含有进程gen_input,且该进程会有clk.pos时钟的上升沿
				触发.
			*/
			SC_METHOD(display_variable); //SC_METHOD(display_variable):表示进程display_variable
			sensitive << f << a << b;
			//进程display_varialbe对f,a,b信号敏感.一旦发生变化,则会调用一次
			dont_initialize();	//不要在仿真零时刻调用进程display_variable,会出错
		}
	};
	
	#endif

**3.测试程序**

	#include <systemc.h>
	#include "nand2.h"
	#include "tb.h"
	
	int sc_main(int argc, char *argv[])
	{
		sc_signal<bool> a, b, f;	//初始值a,b,f均为0
		sc_clock clk("clk", 20, SC_NS);
		nand2 N2("nand2");
		N2.A(a);	//完成端口绑定.N2.A <---> tbl.a
		N2.B(b);	//完成端口绑定.N2.B <---> tbl.b
		N2.F(f);	//完成端口绑定.N2.F <---> tbl.f
	
		tb tbl("tb");
		tbl.clk(clk);
		tbl.a(a);	//端口绑定
		tbl.b(b);	//端口绑定
		tbl.f(f);	//端口绑定
		sc_trace_file *tf = sc_create_vcd_trace_file("nand2");	//sc_trace保存波形文件
		sc_trace(tf, N2.A, "A");
		sc_trace(tf, N2.B, "B");
		sc_trace(tf, N2.F, "F");
		sc_start(200, SC_NS);
		sc_close_vcd_trace_file(tf);
		sc_start(200, SC_NS);
		return 0;
	}

**4.结果**

	a = 0, b = 0, f = 1
	a = 0, b = 1, f = 1
	a = 1, b = 0, f = 1
	a = 1, b = 1, f = 1		//不能理解,难道是因为刚好处在翻转的位置???
	a = 1, b = 1, f = 0

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

