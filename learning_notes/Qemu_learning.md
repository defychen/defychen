# Qemu learning

# Chapter 1 环境准备

## 1.1 ubuntu环境准备

### 1.1.1 qemu下载地址

[qemu下载地址](https://download.qemu.org)

### 1.1.2 安装lib库

Qemu的编译依赖一些lib库,需要安装好才能编译通过.

	1.pkg-config
		apt install pkg-config
	2.glib-2.48
		apt install libglib2.0-0 libglib2.0-dev
	3.gthread-2.0/pixman
		apt install libpixman-1-dev

ubuntu小技巧:

	apt-cache search 关键字--->帮助找到精确的包名

## 1.2 编译qemu