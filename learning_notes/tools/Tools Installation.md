# Tools Installation

# 1. Sublime Text 3搭建Python3 IDE

Sublime text 3主要用于编写代码,使用Sublime text 3搭建Python IDE,之后在Sublime text 3编写的所有Python代码就可以直接运行.

## 1.1 Windows下环境搭建

### step 1 下载安装Sublime text 3

官网下载[Sublime官网](https://www.sublimetext.com/3)

	Version: Build 3143
		OS X (10.7 or later is required)
		Windows - also available as a portable version
		Windows 64 bit - also available as a portable version--->选择这个
		Linux repos - also available as a 64 bit or 32 bit tarball

下载之后,直接解压即可使用.不需要安装.

### step 2 注册Sublime text 3

Help->enter License,输入下面的License信息:

	—– BEGIN LICENSE —–
	Michael Barnes
	Single User License
	EA7E-821385
	8A353C41 872A0D5C DF9B2950 AFF6F667
	C458EA6D 8EA3C286 98D1D650 131A97AB
	AA919AEC EF20E143 B361B1E7 4C8B7F04
	B085E65E 2F5F5360 8489D422 FB8FC1AA
	93F6323C FD7F7544 3F39C318 D95E6480
	FCCC7561 8A4A1741 68FA4223 ADCEDE07
	200C25BE DBBC4855 C4CFB774 C5EC138C
	0FEC1CEF D9DCECEC D3A5DAD1 01316C36
	—— END LICENSE ——

### step 2.5 安装Python 3

略.

### step 3 安装Python 3编译环境

Tools->Build System->New Build System,输入以下内容:

	{
		"encoding": "utf-8",
		"working_dir": "$file_path",
		"shell_cmd": "C:\\Users\\Administrator\\AppData\\Local\\Programs\\Python\\
			Python35-32\\python.exe -u \"$file\"",
		"file_regex": "^[ ]*File \"(...*?)\", line ([0-9]*)",
		"selector": "source.python"
	}

	PS:其中"shell_cmd":"C:\\Users\\...\\python.exe"为Python的安装路径.

然后Ctrl+S保存.保存的文件名为e.g.python352(Python 3.5.2).关闭并重启Sublime text 3,然后选择Tools->Build System->python352即可.

验证:

	1.新建一个Sublime文件;
	2.输入下面的代码:
		print('Hello, python')
	3.保存(必须先保存才能执行)
	4."ctrl+b"执行程序,查看输出效果.

### step 4 安装Package Control

使用ctrl+`(叹号左边的键),输入下面的内容:

	import urllib.request,os; pf = 'Package Control.sublime-package'; ipp = sublime.installed_
	packages_path(); urllib.request.install_opener( urllib.request.build_opener( urllib.reques
	t.ProxyHandler()) ); open(os.path.join(ipp, pf), 'wb').write(urllib.request.urlopen( 'http
	://sublime.wbond.net/' + pf.replace(' ','%20')).read())
	
	PS:上述的内容是连在一起输入的,此处只是为了显示效果才分开.

然后回车,稍等一会就会安装成功.成功安装后,在Preferences下就会有"Package Control"选线.

### step 5 安装Python的输入窗口

Sublime text 3默认没有提供Python的input()的输入窗口,安装一个sublimeREPL的插件即可实现input()输入.


	1.Preferences->Package Control.打开Package Contro输入框;
	2.在输入框中输入:Install Package,选择"Package Control: Install Package"回车.
	3.在新出现的输入框中输入:Sublime REPL,搜索到以后回车进行安装.

验证:

	1.新建一个脚本:
		a = input('Please input an Integer') //使用Python的inpu()函数
		b = int(a)
		if b > 20:
			print('The number is greater than 20.')
		else:
			print('The number is lower than 20.')

	2.运行
		Tools->SublimeREPL->Python->Python-RUN current file
	3.在新打开的页面中输入19.随后打印相应的结果.

PS:运行操作比较复杂,下一步设置快捷键.

### step 6 设置Python 3的快捷键

Preferences->Key Bindings,输入一下内容保存即可:

	{
	"keys":["f5"],
	"caption": "SublimeREPL: Python - RUN current file",
	"command": "run_existing_window_command",
	"args":{"id": "repl_python_run",
	"file": "config/Python/Main.sublime-menu"}
	}

设置好之后,此时F5就是执行程序的快捷键.

参考文章[Sublime text 3 搭建Python3 IDE](https://blog.csdn.net/vertigozz/article/details/54574006)

## 1.2 Linux下环境搭建

略.