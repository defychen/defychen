# vim使用技巧

## Chapter 1.vim配置

[一个超强的vim配置文件参考](https://github.com/ma6174/vim)

### 1.1 安装

**1.简易安装方法--->自动化安装,推荐的方法** 

	wget -qO- https://raw.githubusercontent.com/ma6174/vim/master/setup.sh | sh -x
	/*
		1.该命令行的作用:从网址上下载内容,并直接执行.
		2.wget参数:
			-q/--quite:安静模式(无信息输出);
			-O:将网上的文档内容写入xxx;
			wget -qO download.txt https://raw.githubusercontent.com/ma6174/vim/master/setup.sh
			//以安静模式将文档内容写入download.txt文件中.
			-qO-:应该是表示下载下来文档内容直接执行.
		3.sh -x:-x选项表示跟踪并调试shell脚本.
		4.网址:
			其实是:https://github.com/ma6174/vim/blob/master/setup.sh在该网页中选择Raw方式,即
			纯文本(不带格式).这样可以将github文档中的内容直接下载到文件中或者执行.
	*/
	PS:打开上面网址,其内容为:
		#!/bin/bash
		echo "安装将花费一定时间，请耐心等待直到安装完成^_^"
		if which apt-get >/dev/null; then
			sudo apt-get install -y vim vim-gnome ctags xclip astyle python-setuptools
			python-dev git
		elif which yum >/dev/null; then
			sudo yum install -y gcc vim git ctags xclip astyle python-setuptools python-
			devel	
		fi
		
		##Add HomeBrew support on  Mac OS
		if which brew >/dev/null;then
		    echo "You are using HomeBrew tool"
		    brew install vim ctags git astyle
		fi
		
		sudo easy_install -ZU autopep8 
		sudo ln -s /usr/bin/ctags /usr/local/bin/ctags
		mv -f ~/vim ~/vim_old
		cd ~/ && git clone https://github.com/ma6174/vim.git
		mv -f ~/.vim ~/.vim_old
		mv -f ~/vim ~/.vim
		mv -f ~/.vimrc ~/.vimrc_old
		mv -f ~/.vim/.vimrc ~/
		git clone https://github.com/gmarik/vundle.git ~/.vim/bundle/vundle
		echo "ma6174正在努力为您安装bundle程序" > ma6174
		echo "安装完毕将自动退出" >> ma6174
		echo "请耐心等待" >> ma6174
		vim ma6174 -c "BundleInstall" -c "q" -c "q"
		rm ma6174
		echo "安装完成"

**2.手动安装**

没试验过,不知道ok不.但是和前面自动安装步骤是一样的.

	1.安装vim sudo apt-get install vim
	2.安装ctags：sudo apt-get install ctags
	3.安装一些必备程序：sudo apt-get install xclip vim-gnome astyle python-setuptools
	4.python代码格式化工具：sudo easy_install -ZU autopep8
	5.sudo ln -s /usr/bin/ctags /usr/local/bin/ctags
	6.clone配置文件：cd ~/ && git clone git://github.com/ma6174/vim.git
	7.mv ~/vim ~/.vim
	8.mv ~/.vim/.vimrc ~/
	9.clone bundle 程序：git clone https://github.com/gmarik/vundle.git ~/.vim/bundle/vundle
	10.打开vim并执行bundle程序:BundleInstall
	11.重新打开vim即可看到效果

### 1.2 该vim的特点

	1.F5可以编译并执行C/C++/python/java/shell等脚本,F8可进行C/C++代码调试;
	2.C/C++自动插入头文件(文件名/作者/mail/创建时间以及"#ifndef...#define...#endif"等);
		PS:必须执行"gvim/vim test.h"才会有效果,先touch是不行的;
	3.python自动插入"#!/usr/bin/env python, # coding=utf-8";
		PS:必须执行"gvim/vim test.py"才会有效果,先touch是不行的;
	4.映射"Ctrl+A"为全选并复制快捷键,方便复制代码;
	5.F2消除代码中的空行(所有的空行);
	6.F3列出当前文件目录,打开树状文件目录;
	7.支持鼠标选择、方向键移动;
	8.代码高亮、自动缩进、显示行号、显示状态行的;
	9.TAB键触发代码补全功能;
	10.[]/{}/()/""/''等自动补全.

### 1.3 多窗口操作

	在编辑的文件中:
	:sp+文件名--->打开一个新文件,两个文件水平分割窗口;
	:vs+文件名--->打开一个新文件,两个文件垂直分割窗口;
	ctrl+w--->在窗口间切换.

***

## Chapter 2.vim中的问题解决

### 2.1 pyflakes.vim出现错误提示

pyflakes.vim是一个非常好用的python高亮vim插件.

在使用vim编写python脚本时,出现了需要编译的错误,错误提示如下:

![](images/pyflakes_error.png)

	the pyflakes.vim plugin requires Vim to be compiled with +python
	//意思是pyflakes.vim插件需要编译。

**解决方法如下:**

	1.去github重新下载一个pyflakes.vim;
		git clone --recursive git://github.com/kevinw/pyflakes-vim.git
	2.进入git克隆目录,复制./pyflakes-vim/ftplugin下的python到~/.vim/ftplugin目录即可:
		cd ./pyflakes-vim/ftplugin
		cp ./python ~/.vim/ftplugin -rf
	3.再次打开python文件就不会出现错误了.

***

## Chapter 3.vim使用技巧

### 3.1 在windows下编辑的脚本,难免会出现"^M"这样的错误(这种错误是windows下的换行符)

解决办法:

#### 方法1 使用vim打开该脚本,然后执行:
	
	:set ff=unix

#### 方法2 使用dos2unix命令:

	dos2unix aes_test.py

### 3.2 vim显示颜色

	1)拷贝.vimrc到自己的home目录,即"~/"
	2)source ~/.vimrc
	3)修改secure CRT配置,在仿真->终端选择"linux",并且勾上"ANSY颜色(A)",可以再尝试勾上"使用颜色方案"

	//修改.bashrc后也需要"source ~/.bashrc"

### 3.3 linux系统修改PATH环境变量的方法

	1)查看PATH环境变量
	echo $PATH		//显示为:
		/usr/local/sbin:/usr/local/bin:/usr/sbin:...
	2)添加路径到PATH
	export PATH=$PATH:新路径		
	//相当于当前路径+新路径,然后赋值给PATH.此时会覆盖掉原来的PATH变量.export是导出变量,相当于更新PATH
	3)删除PATH中的路径
		1.先查看:	echo $PATH		//e.g.路径1:路径2:路径3:路径4
		2.比如删除路径4,只需要copy路径1/2/3,然后赋值给PATH即可
			export PATH=路径1:路径2:路径3

### 3.4 linux显示所有的环境变量

	env		//命令env

### 3.5 查看文件属于windows还是unix的方法

某个文件如果使用了windows下的换行符(\r\n),就属于windows类型的文件.在vim中使用:

	:set fileformat或者:set fileformat?
		//得到"fileformat=dos",即表示该文件属于windows类型的文件.此时需要将
		//换行符转换"dos2unix"