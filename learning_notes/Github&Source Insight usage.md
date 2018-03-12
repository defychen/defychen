# 1. Github usage

## 1.1 How to use git to commit code
****

**1)新建一个目录:**

	mkdir github_push

**2)配置个人信息**

	//1. 配置全局的用户名和邮箱---此时本机所有的提交都会用这个用户名和邮箱
	git config --global user.name "defychen"
	git config --global user.email 894739534@qq.com
	//全局的配置会修改进"~/.gitconfig"
	内容为:
	[user]
		name = defy.chen
		email = defy.chen@xxx.com
	
	//2. 配置当前的project的用户名和邮箱---此时只会作用于当前的project
	git config user.name "defychen"
	git config user.email 894739534@qq.com

**3)初始化版本仓库(让git管理本地目录):**
	
	git init

**4)添加需要上传到github仓库的文件到该目录**

**5)将文件添加到上传队列:**
	
	git add .	//.代表所有添加的文件

**6)提交缓存(还在本地):**

	git commit -m "Reading note 2017/06/05"	//" "表示注释,方便自我查看

**7)将本地commit后的添加到github仓库:**

	git remote add origin https://github.com/defychen/defychen

**8)push到远程仓库(github仓库):**

	git push origin master	//之后会输入帐号(username),密码(password)
***
## 1.2 git usage

**1)查看历史提交版本**

	git log		/*整个大目录的历史提交版本*/
	git log .	/*查看某个目录的历史提交版本(e.g.buildroot)*/
	git log -p	/*查看最近提交的改动*/
	git log -p ./output/build/alisee.../see/src/lld/sec/m36f/libssec_m32.a	/*查看具体某个文件的历史提交版本*/
	e.g.如果在alidsc目录:
	git log	/*显示./linux-PDK...这个大目录的提交版本*/
	git log .	/*显示alidsc这个目录的提交版本,更精确*/

**2)版本回退**

	git reset --hard commit-number

**3)查看所拉下来的PDK tag指向的分支**

	1)打开所拉下来的tag: 
		vim ./linux/alisee/alisee.mk得到tag号:PDK2.0.0-20170427
	2)切换到alisee的目录:
		cd ./output/build/alisee...
	3)执行命令:
		git branch -a --contain PDK2.0.0-20170427(tag号)
		git branch -a //列出本地分支和远程分支

**4)直接切到某个commit号**
	
	git checkout commit-number
	git log .(查看是否切成功)

**5)查看具体commit号以及该commit与哪个tag关联**

	git log --decorate

**6)丢掉本地的修改**

	git checkout -- .		//针对有时本地修改了,但是不需要提交.而且此时不能执行"git pull"

## 1.3 git pull更新时的问题

	Your local changes to the following files would be overwritten by merge
	error: Your local changes to the following files would be overwritten by merge:
		...	/*xxx file*/
	Please, commit your changes or stash them before you can merge.

	Solution method (1)
	使用代码库中的文件完全覆盖本地工作版本
	git reset --hard
	git pull

## 1.4 github提交错误

	当执行"git pull"时出现下面的提示:
	There is no tracking information for the current branch.
	Please specify which branch you want to merge with.
	See git-pull(1) for details

    git pull <remote> <branch>

	If you wish to set tracking information for this branch you can do so with:

    git branch --set-upstream-to=origin/<branch> master
	
	//原因:本地分支和远程分支没有建立联系.解决:
	git branch --set-upstream-to=origin/master master	/*远程的和本地的分支都为master分支,并建立联系*/

## 1.5 git打tag

	//方法 1
	git tag PDK1.12.0-20170616
	git push origin PDK1.12.0-20170616
	//方法 2
	git tag -a v0.0.1_20170705C  -m "update viaccess tag"
	git push origin --tags

	查看所打的tag
	git tag

## 1.6 git push origin master提交时出现提交不成功

	使用git push origin master推code时出现:Everything up-to-date.一直没有将code的更新push上去
	
	##原因:
		--->可能是因为在使用git commit "xxx"	//添加注释时没成功.
		--->正确的应该是:git commit -m "xxx"	//应该有个"-m"

## 1.7 git查看版本

	git --version		//得到git version 2.3.0

## 1.8 执行git clone提示"fatal: unable to access "clone的地址""

	执行git clone https://github.com/defychen/defychen.git时,出现"fatal: unable to
	access 'https://github.com/defychen/defychen.git': Proxy CONNECT ..."
	
	解决办法:
		将https://github.com/defychen/defychen.git的https换成git即可.

***

# 2. Source Insight usage

## 2.1 设置背景色

	Options->Preferences->Colors->Window Background->设置红(R):204, 绿(G):232, 蓝(U):207

## 2.2 常用快捷键

	Alt+F4--->退出程序(e.g.如果Markdown开了多个页面,会把所有页面都关闭)
	Ctrl+E--->完成语法(e.g.产生小写的情况,还不知道有什么用)
	Ctrl+K--->复制一行------------------------------->挺有用
	Ctrl+Shift+K--->复制从当前字符到最右边一行--------->挺有用
	Ctrl+U--->剪切一行------------------------------->挺有用
	Ctrl+;(分号)--->剪切从当前字符到最右边一行---------->挺有用
	Ctrl+,(逗号)--->剪切从当前位置到下一个字的开头------->挺有用
	Ctrl+W--->关闭文件(e.g.只关闭一个页面)------------->挺有用
	Ctrl+Shift+W--->关闭所有文件
	Alt+L--->激活最左边显示文件内容结构的窗口----------->挺有用
	Ctrl+M--->书签
	Alt+,(逗号)--->后退
	Alt+.(点号)--->向前
	F5/Ctrl+G--->跳转到行---------------------------->挺有用
	PgDn--->下一页----------------------------------->挺有用
	PgUp--->上一页----------------------------------->挺有用
	Ctrl+PgDn--->上半页(向上滚动半屏)------------------>挺有用
	Ctrl+PgUp--->下半页(向下滚动半屏)------------------>挺有用
	Ctrl+Home--->到文件顶部--------------------------->挺有用
	Ctrl+End--->到文件尾部---------------------------->挺有用

## 2.3 必须配置的3个选项

### 2.3.1 Unix文本结尾方式(也就是换行符)设置:

默认的Source Insight是以Window换行符进行代码编辑的,换行时显示的为"\r\n"和Unix下的不同,Unix下的为"\n".因此在Unix/Linux平台,必须设置为Unix换行符(即文本结尾方式).

	Options->Preferences->Files->Default file format
		将"Windows (CR/LF)"改为"Unix (LF)"

### 2.3.2 保存文件时删除多余的空格:

	Options->Preferences->Files->勾选上"Remove extra white space while saving"

### 2.3.3 扩展的tab键(一个tab键扩展成4个空格)

	Options->Document Options->勾选上"Expand tabs",并设置"Tab width"为4.

## 2.4 设置快速定位文件(使用快捷键即可打开文件所在目录)

	Options->Custom Commands.在这个界面里设置:
		1.点击Add->在New command name:输入"see current file".之后会显示在"Command"里面;
		2.在"Run"中输入"exporer/select,%f"--->此处相当于运行的命令;
		3.点击"Keys",在Key Assignments中选中"Custom cmd:see current file"(默认点击keys之后就会选中).
		选择Assign New Keys(添加一个快捷键).在弹出的"Press the key-comination...keys with the key
		or mouse button. Press Esc to cancel."键入"Alt+Q",快捷键建立完毕.然后点击"OK"即可.
		4.之后使用"Alt+Q"就可以打开文件所在目录.

## 2.5 使souce insight支持python语言的方法

	1.需要下载Python.CLF
		目录tools/Python.CLF下已经有了下载好的Python.CLF文件
	2.在source insight中进行如下设置
		Options->Preferences->Languages->点击"Import"->选择下载好的Python.CLF文件
		->在点击"Doc Types"->在弹出的"Document Options"点击"Add Type"->在弹出的"Add
		New Document Type"中输入"Python"->在File filter中的输入"*.py"->在Parsing
		Language中选择"Python Language"即可.

***

# 3. Beyond Compare的使用

## 3.1 换行符文本比较时没有发现有区别,但是显示为"红色",表示有区别

文本中Windows下的换行符与Unix/Linux下的换行符的区别:

	1.在Beyond Compare文本比较时,虽然没有显示出任何文本的区别.但是在文本的上方的信息提示中会有:
		xxx字节(大小的区别) PC/UNIX(文本格式的区别)
	2.有第一步的区别,再查看:会话->会话设置->重要->勾上"比较行尾"->就可以显示出一片红色.
	由此可以确定换行符有差别(一个Windows下的;一个Unix下的).
