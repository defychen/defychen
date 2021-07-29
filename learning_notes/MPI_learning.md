# MPI Learning

# 1. MPI介绍

## 1.1 MPI简介

多线程是一种便捷的模型,其中每个线程都可以访问其它线程的存储空间.

	1.多线程模型只能在共享存储系统之间移植;
	2.一般来讲,并行机不一定在各处理器之间共享存储,当面向非共享存储系统开发并行程序时,程序的各部分之间需要
		通过来回传递消息的方式通信.

因此,要使得消息传递方式可移植,就需要采用标准的消息传递库.这就促成了MPI(Message Passing Interface,消息传递接口)的面世,MPI是一种被广泛采用的消息传递标准.

MPI是一种基于消息传递的并行编程技术.它不是一种具体的编程语言,而是一种编程接口标准,即接口已经定义好,内部由程序员自己实现.

	1.MPI标准定义了一组具有可移植性的编程接口;
	2.各个厂商或组织遵循这些标准实现自己的MPI软件包,典型的实现包括开放源代码的MPICH、LAM MPI以及不开放
		源代码的Intel MPI;
	3.由于MPI提供了统一的编程接口,程序员只需要设计好并行算法,使用相应的MPI库就可以实现基于消息传递的并
		行计算;
	4.MPI支持多种操作系统,包括大多数的类UNIX(e.g. linux)和Windows系统.

## 1.2 MPICH的安装

MPI是一个标准.它不属于任何一个厂商,不依赖于某个操作系统,也不是一种并行编程语言.不同的厂商和组织遵循着这个标准推出各自的实现,而不同的实现也会有其不同的特点.MPICH是影响最大、用户最多的MPI实现.

### 1.2.1 ubuntu通过命令安装--->这种方法最好

	sudo apt-get install mpich

### 1.2.2 通过下载源码的方式安装--->尽量不要使用这种方法

试过,但是失败了,此处略.

### 1.2.3 windows下的安装

略.

## 1.3 MPI的hello world

### 1.3.1 代码如下

	#include <stdio.h>
	#include <mpi.h>
	
	int main(int argc, char **argv)
	{
		MPI_Init(NULL, NULL);
		int world_size;
		MPI_Comm_size(MPI_COMM_WORLD, &world_size);
		int world_rank;
		MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
		char processor_name[MPI_MAX_PROCESSOR_NAME];
		int name_len;
		MPI_Get_processor_name(processor_name, &name_len);
		printf("Hello world from processor %s, rank %d out of %d processors\n",
			processor_name, world_rank, world_size);
		MPI_Finalize();
		return 0;
	}

#### 1.3.1.1 #include <mpi.h>

要编写MPI程序,必须包含该头文件:

	#include <mpi.h>

#### 1.3.1.2 MPI_init()

MPI_Init用来初始化MPI执行环境,建立多个MPI进程之间的联系,为后续通信做准备.执行改行之后,所有MPI的全局变量和内部变量都会被创建.

	原型:
		MPI_Init(int *argc, char ****argv);
	调用:
		MPI_Init(&argc, &argv)
	当前传入两个NULL,只是保留位置,没有使用上.

	




