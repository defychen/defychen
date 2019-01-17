# SystemC Leaning

***

## Chapter 1 前言

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

