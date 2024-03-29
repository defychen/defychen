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

***

# 2. Python 3安装BeautifulSoup和requests第三方模块--->不适用了

BeautifulSoup是Python的一个库,主要的功能是从网页中抓取数据.

## 2.1 Windows下BeautifulSoup安装

### 2.1.1 BeautifulSoup下载

[BeautifulSoup官网](https://www.crummy.com/software/BeautifulSoup/)

	在官网上,有"Download Beautiful Soup":
		选择其中的"Beautiful Soup 4.6.0(May 7, 2017)"-->最新版是Beautiful Soup 4.6.
	会直接跳转到"https://www.crummy.com/software/BeautifulSoup/bs4/download/"去下载.
	
	PS:下载完了需要解压到自己定义的一个目录.

### 2.1.2 安装BeautifulSoup

**1.格式转换**

BeautifulSoup默认使用的是Python2格式,因此需要将BeautifulSoup由Python2格式转换为Python3格式.使用Python自带的工具"2to3.py".

	1.工具位置:Python\Tools\Scripts
	2.进入工具位置:
		cd C:\Python34\Tools\Scripts
	3.格式转换:
		./2to3.py -w C:\Python34\beautifulsoup4-4.4.1 //后面的为BeautifulSoup解压的路径.

**2.安装**

进入到BeautifulSoup解压缩的目录,执行下面的命令:

	cd C:\Python34\beautifulsoup4-4.4.1 //进入到BeautifulSoup目录
	python setup.py build //执行setup.py脚本,传入参数为"build"
	python setup.py install //执行setup.py脚本,传入参数为"install"

**3.测试**

	在"cmd.exe"窗口中输入: python //启动python
	输入:from bs4 import BeautifulSoup //没有出现错误则表示安装成功.

## 2.2 Linux下BeautifulSoup安装

**略**

## 2.3 Windows下requests安装

requests是Python实现的简单易用的HTTP库,使用起来比urlib简洁.编写爬虫和测试服务器响应数据时经常会用到.

### 2.3.1 requests下载

[requests官网](http://docs.python-requests.org/en/master/)

	在官网上,顶部有"Release v2.18.4. (Installation)":
		选择其中的"Installation)"会直接跳转到"http://docs.python-requests.org/en/master/user/install
		/#install".在"Get the Source Code"中有"Or, download the tarball:"."tarball"是超链接,可以下载
		"Windows"压缩版本.

		PS:下载完了需要解压到自己定义的一个目录.

	PS:如果英文查不到,在官网主页的左边有"Translations"->选择Chinese,页面就会翻译为中文.

### 2.3.2 安装requests

	1.进入到requests解压的目录
		cd C:\Python34\kennethreitz-requests-cbb0830
	2.安装
		python setup.py install
	3.测试
		在"cmd.exe"窗口中输入: python //启动python
		输入:import requests //没有出现错误则表示安装成功.

## 2.4 Linux下requests安装

**略**

参考文章[Python-Windows下安装BeautifulSoup和requests第三方模块](https://blog.csdn.net/yannanxiu/article/details/50432498)

# 3. Pycharm安装及破解

Pycharm是一款非常好用的python IDE,提供专业版和社区版,专业版收费、社区办免费但是功能没有专业版强大.

## 3.1 Pycharm下载

**1.下载地址**

[下载地址](https://www.jetbrains.com/pycharm/download/previous.html)

**2.版本选择**

选择版本为(Version 2018.2)--->这个版本可以破解(选择左边的专业版).

![](images/pycharm_version.png)

	注意右边的Release时间:July 25,2018--->必须为该版本,否则后面破解不了.

## 3.2 安装

安装选项按照下面的选择:

![](images/pycharm_install.png)

	Create Desktop Shortcut:选择64-bit launcher(64-bit快捷方式);
	Create Associations:勾选上".py",之后的".py"文件就会用Pycharm打开;
	Download and install JRE x86 by JetBrains:勾选上支持JRE运行环境--->支持JRE环境,勾选上即可.

## 3.3 破解

**1.复制破解文件到bin目录**

破解补丁文件位置:

	D:\repository_software\pycharm\JetbrainsCrack-2.8-release-enc.jar

复制该破解文件到安装目录:

	D:\Program Files\JetBrains\PyCharm 2018.2\bin--->复制到安装的bin目录

**2.修改文件**

1.修改bin目录下的"pycharm.exe.vmoptions":

	打开"pycharm.exe.vmoptions"文件,在后面增加:
	-javaagent:D:\Program Files\JetBrains\PyCharm 2018.2\bin\JetbrainsCrack-2.8-release-enc.jar
	//-javaagent:破解文件的路径

2.修改bin目录下的"pycharm64.exe.vmoptions":

	打开"pycharm64.exe.vmoptions"文件,在后面增加:
	-javaagent:D:\Program Files\JetBrains\PyCharm 2018.2\bin\JetbrainsCrack-2.8-release-enc.jar
	//-javaagent:破解文件的路径

## 3.4 激活

启动Pycharm,出现激活窗口.在"Activate code"的提示框下面输入:

该段代码位于"D:\repository_software\pycharm\activate_code.txt"

	{"licenseId":"ThisCrackLicenseId",
	"licenseeName":"11011",
	"assigneeName":"xxx",
	"assigneeEmail":"xxx",
	"licenseRestriction":"xxx",
	"checkConcurrentUse":false,
	"products":[
	{"code":"II","paidUpTo":"2099-12-31"},
	{"code":"DM","paidUpTo":"2099-12-31"},
	{"code":"AC","paidUpTo":"2099-12-31"},
	{"code":"RS0","paidUpTo":"2099-12-31"},
	{"code":"WS","paidUpTo":"2099-12-31"},
	{"code":"DPN","paidUpTo":"2099-12-31"},
	{"code":"RC","paidUpTo":"2099-12-31"},
	{"code":"PS","paidUpTo":"2099-12-31"},
	{"code":"DC","paidUpTo":"2099-12-31"},
	{"code":"RM","paidUpTo":"2099-12-31"},
	{"code":"CL","paidUpTo":"2099-12-31"},
	{"code":"PC","paidUpTo":"2099-12-31"},
	{"code":"DB","paidUpTo":"2099-12-31"},
	{"code":"GO","paidUpTo":"2099-12-31"},
	{"code":"RD","paidUpTo":"2099-12-31"}
	],
	"hash":"2911276/0",
	"gracePeriodDays":7,
	"autoProlongated":false}

