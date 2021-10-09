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

