# gem5_learning

## Chapter 1. Unbuntu安装gem5

gem5是一个非常强大的模拟平台,服务于计算机系统架构相关研究(包括系统级架构和处理器微架构).

### 1.1 安装一些依赖文件

运行gem5需要一个依赖文件,包括:g++(4.7及以上版本),python(2.5及以上版本),scons(0.98.1及以上版本),swig(2.0.4及以上版本),zlib,m4,protobuf(2.1及以上版本)等.

### 1.2 安装g++

一般系统已经安装好,查看版本号"g++ -v",没有就执行:

	sudo apt-get install g++

### 1.3 安装python

一般系统自带,查看版本号"python --version".

### 1.4 安装scons

	sudo apt-get install scons
	//查看版本号:
	scons -v

### 1.5 安装swig

	sudo apt-get install swig
	//查看版本号:
	swig -version

### 1.6 安装zlib

zlib一般系统自带,使用"whereis zlib"可以查看到安装的位置.

	sudo apt-get install zlib1g-dev

### 1.7 安装m4

一般系统自带,查看版本号"m4 --version",没有就执行:

	sudo apt-get install m4

### 1.8 安装protobuf-dev和libgoogle-perftools-dev

	sudo apt-get install libprotobuf-dev
	sudo apt-get install libgoogle-perftools-dev

### 1.9 安装mercurial

	sudo apt-get install mercurial

### 1.10 安装build-essential

	sudo apt-get install build-essential

### 1.11 可能需要安装boost

	sudo apt-get install libboost-all-dev

### 1.12 安装gem5

**1.下载gem5压缩包**

[gem5 github地址](https://github.com/gem5/gem5)

	下载下来后,执行:
		unzip defychen-gem5-master.zip	//解压出来

**2.安装gem5**

	切换到gem5解压目录,执行:
		/* 1. 安装ARM版本的gem5 */
		scons build/ARM/gem5.opt
		/* 2.安装X86版本的gem5 */
		scons build/X86/gem5.opt

	