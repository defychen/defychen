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

	git remote add origin git://github.com/defychen/defychen --->ssh协议通讯
	git remote add origin https://github.com/defychen/defychen --->https协议通讯

**8)push到远程仓库(github仓库):**

	git push origin master	//之后会输入帐号(username),密码(password)
***
## 1.2 git usage

**1)查看历史提交版本**

	git log		/*整个大目录的历史提交版本*/
	git log .	/*查看某个目录的历史提交版本(e.g.buildroot)*/
	git log -p	/*查看最近提交的改动*/
	git log --pretty=oneline /* 每条log以一行显示(即仅显示:commit id和commit注释) */
	git log --graph /* 查看分支合并图 */
	e.g.如果在alidsc目录:
	git log	/*显示./linux-PDK...这个大目录的提交版本*/
	git log .	/*显示alidsc这个目录的提交版本,更精确*/
	git log -p ./output/build/alisee.../see/src/lld/sec/m36f/libssec_m32.a	/*查看具体某个文件的历史提交版本*/

**2)版本回退**

	git reset --hard commit-number //直接回退到某个commit id
	git reset --hard HEAD^
	/*
		HEAD:表示当前版本;
		HEAD^:表示上一个版本;
		HEAD^^:上上个版本(依次类推);
		HEAD~30:回退30个版本.
	*/

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

	git checkout -- .		//针对有时本地修改了,但是不需要提交(也没有add).而且此时不能执行"git pull"

**7)查看代码改动情况**

	git show commit-number	//查看某个commit号的代码改动情况

**8)查看操作的历史记录**

	git reflog	// 可以看到自己之前操作的git命令

**9)比较本地与远程仓库的改动**

	git diff filename //查看自己文件filename的修改情况(与远程仓库比较)

## 1.3 git pull更新时的问题

	1.git pull之后出现:
		There is no tracking information for the current branch.
		Please specify which branch you want to merge with.
		See git-pull(1) for details
		    git pull <remote> <branch>
		If you wish to set tracking information for this branch you can do so with:
		    git branch --set-upstream-to=origin/<branch> SC2.0
		意思是需要指定当前工作目录、工作分支和远程的仓库、分支之间的关系.
		--->解决:
		git branch --set-upstream-to=origin/SC2.0
	2.git pull之后出现:
		Your local changes to the following files would be overwritten by merge
		error: Your local changes to the following files would be overwritten by merge:
			/*
			一系列的文件...	
			*/
		Please, commit your changes or stash them before you can merge.
		Aborting
		意思是本地的文件和远程的不一致,需要merge或者放弃本地修改.
		--->解决:
		1.放弃本地修改,直接覆盖:
			git reset --hard
			git pull
		2.使用stash将未提交的修改都保存起来(放入git的栈中),后续可以再恢复:
			git stash	// 将未提交的修改放入git栈
			git pull 	// 更新
			git stash pop	//更新完后,用git stash pop恢复放入git栈中的内容

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
	查看tag信息:
	git show tagname

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

## 1.9 github与远程通信的两种方式"SSH"和"HTTPS"的区别

	1.远程地址的区别:
	git@github.com:defychen/defychen.git--->对应的ssh协议的远程地址
	https://github.com/defychen/defychen.git--->对应的是https的远程地址
	2.推送的区别:
	https协议每次进行代码提交到远程服务器都需要进行"账号和密码"的输入.
	ssh协议只需要首次进行账号和密码的输入,之后push不再需要输入"账号和密码"

	如果一直用的ssh协议进行代码的提交,突然进行了:
		git clone https://github.com/defychen/defychen.git--->使用了https
	在进行代码提交时会出现"unable to access 'https://github.com/defychen/defychen.git'...";
	此时需要将https换成ssh:
		git remote -v //查看远程的地址
		git remote set-url origin git@github.com:defychen/defychen.git
			//换成ssh通信
		PS:
		git remote set-url --add origin https://github.com/defychen/defychen.git
			//增加一个origin
		git remote set-url --delete origin https://github.com/defychen/defychen.git
			//删掉一个origin

## 1.10 git创建一个新的branch

	1.本地创建分支
		git branch branch_name(自己创建的分支名)
	2.切换到创建的新分支(可以先查看下现在处于什么分支:git branch)
		git checkout branch_name(分支名)	//分支名为最后的那个名字(不需要前面的路径)
		git branch -a
		/*
		显示:
			* branch_name_a	// 前面的"*"表示当前所在的分支
			master
			remotes/origin/HEAD -> origin/master
			remotes/origin/branch_name_b
		*/
		git checkout branch_name_b	//直接切分支即可
	3.添加需要提交到该分支的代码,然后进行提交的相关动作
		git add .
		git commit -m "Create a new branch"
		git push origin branch_name(自己创建的分支名)
	4.查看一下远程仓库有几个分支
		git branch -a	//会显示新创建的分支
	5.合并分支到master分支
		git merge branch1	// 当前应该在master分支,合并branch1到master分支
	6.删除分支
		git branch -d branch1

## 1.11 git clone指定分支拉代码

	1.不指定分支--->默认是从master branch拉下来
	git clone git@github.com:defychen/defychen.git
	2.指定分支--->从指定分支拉下来
	git clone -b branch_name git@github.com:defychen/defychen.git
	//通过"-b branch_name"来指定分支名.

## 1.12 git stash(储藏)

当需要去修改其他内容时,这时候工作还没有做完,可以通过git stash先临时保存起来,等干完其他的事之后,再回来恢复现场,继续干活.

### 1.12.1 git stash

git stash会把所有未提交的修改(包括暂存的和非暂存的)都保存起来,用于后续恢复当前工作目录.

	git status
		On branch master
		Changes to be committed:
			new file:   style.css
		Changes not staged for commit:
			modified:   index.html
	git stash	// git stash保存在本地,不会推到远程
		Saved working directory and index state WIP on master: 5002d47 our new homepage
		HEAD is now at 5002d47 our new homepage
	git status	//再次查看,没有修改记录
		On branch master
		nothing to commit, working tree clean

	PS:推荐给每个stash增加一个message,用于版本记录.使用:
		git stash save "test-cmd-stash"
			Saved working directory and index state On autoswitch: test-cmd-stash
			HEAD is 296e8d4 remove unnecessary postion reset in onResume function
		git stash list	// 查看已经stash到栈的列表
			stash@{0}: On autoswitch: test-cmd-stash

### 1.12.2 git stash pop

git stash pop弹出stash栈的第一个,用于恢复之前缓存的目录.

	git stash pop	//直接执行即可.

### 1.12.3 git stash apply

应用stash栈的缓存,但不删除stash栈缓存.

	git stash list	// 显示stash栈的列表
		stash@{0}: WIP on master: 049d078 added the index file
		stash@{1}: WIP on master: c264051 Revert "added file_size"
		stash@{2}: WIP on master: 21d80a5 added number to log
	git stash apply stash@{0} 	// 使用某个stash名字
	git stash apply				// 如果后面不带stash名字,默认使用最近的stash,即:stash@{0}

### 1.12.4 git stash drop

移除某个stash缓存.在使用git stash apply xxx时,不会删除缓存,需要用git stash drop来移除.

	git stash list
		stash@{0}: WIP on master: 049d078 added the index file
		stash@{1}: WIP on master: c264051 Revert "added file_size"
		stash@{2}: WIP on master: 21d80a5 added number to log
	git stash drop stash@{0} // 移除stash@{0}

如果要删除所有的stash缓存,可以执行:

	git stash clear	// 删除所有的stash缓存.

***

# 2. Source Insight usage

## 2.1 设置背景色

	Options->Preferences->Colors->Window Background->设置红(R):204, 绿(G):232, 蓝(B):207

## 2.2 常用快捷键

	Alt+F4--->退出程序(e.g.如果Markdown开了多个页面,会把所有页面都关闭)
	Alt+F8--->显示或隐藏左边的"符号窗口(Symbol Window)"
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
		2.在"Run"中输入"ShellExecute open explorer /select,%f"--->此处相当于运行的命令;
		3.点击"Keys",在Key Assignments中选中"Custom cmd:see current file"(默认点击keys之后就会选中).
		选择Assign New Keys(添加一个快捷键).在弹出的"Press the key-comination...keys with the key
		or mouse button. Press Esc to cancel."键入"Alt+Q",快捷键建立完毕.然后点击"OK"即可.
		4.之后使用"Alt+Q"就可以打开文件所在目录.

## 2.5 针对中文在source insight显示为乱码的情况

	在source insight 3.5版本中可以的处理方法:
	方法 1->借助于linux下的iconv命令:
		iconv -f utf-8 -t gb18030 file1.py -o file2.py
		/*
		将uft-8编码的file.py文件转换为gb18030编码的file2.py.
		可以使用iconv --help/iconv --usage查看使用方法
		*/

	方法 2->借助于ultra edit完成转换:
		使用UE打开文件->file->另存为(F12)->在"另存为"对话框中的"编码"选择(ANSI/ASCII)
		(位于保存的右边)->点击保存即可.然后用source insight打开显示的即为正确的中文.

	方法 3->借助于"记事本"完成转换:
		使用"记事本"打开文件->文件->另存为->在"另存为"对话框中的"编码"选择(ANSI)(原本为UTF-8)
		(位于保存的右边)->点击保存即可.然后用source insight打开显示的即为正确的中文.

## 2.6 使souce insight支持python语言的方法

	1.需要下载Python.CLF
		目录tools/Python.CLF下已经有了下载好的Python.CLF文件
	2.在source insight中进行如下设置
		Options->Preferences->Languages->点击"Import"->选择下载好的Python.CLF文件
		->再点击"Doc Types"->在弹出的"Document Options"点击"Add Type"->在弹出的"Add
		New Document Type"中输入"Python"->在File filter中的输入"*.py"->在Parsing
		Language中选择"Python Language"即可.

## 2.7 source insight恢复Ctrl+a的全选功能

默认source insight的Ctrl+a的功能是全部保存(Save all).需要修改Ctrl+a为全选功能

	Options->Key Assignments->弹出"Key Assignments"窗口:
		1.Command中搜索"Save all",得到"File: Save all",选中可以看到"Keystrokes"中的值为"Ctrl+A";
		2.点击"Assign New Key",弹出"Press the key-comination...keys with the key
		or mouse button. Press Esc to cancel."键入"Ctrl+shift+a",修改"Save all"为快捷键"Ctrl+Shift+A".
		3.在Command中搜索"Select All",得到"Navigation: Select All",此时没有快捷键.
		4.点击"Assign New Key",弹出"Press the key-comination...keys with the key
		or mouse button. Press Esc to cancel."键入"Ctrl+a",修改"Select All"为快捷键"Ctrl+A".

## 2.8 source insight将文件的Tab转换为空格/将空格转换为Tab

	1.空格转换为Tab键:
	全选文件->Edit->Special Edit->Spaces To Tabs
	2.Tab键转换为空格:
	全选文件->Edit->Special Edit->Tabs To Spaces

## 2.9 AStyle代码格式工具在source insight中的使用

AStyle代码格式工具可用于将source insight中的代码风格全部改为符合linux的风格.相关的配置情况如下:

### 1.AStyle下载

[AStyle的下载路径:](https://sourceforge.net/projects/astyle/)

下载之后需要解压到一个指定位置(e.g.D:\AStyle_3.1_windows\AStyle\bin\AStyle.exe).

### 2.在Source Insight中安装AStyle工具

1.打开source insight工程,选择"Options->Custom Conmmands".

2.在Custom Commands窗口中:

	1.点击Add,在New command name中输入:AStyle_C
	2.在Run中输入命令:D:\AStyle_3.1_windows\AStyle\bin\AStyle.exe -n -t --style=linux %f
	3.添加Menu菜单,点击Menu后:
		1.在Command中选择"Custom Cmd: AStyle_C"
		2.在Menu中选择View
		3.然后点击Insert,如果出现Insert不能选择,可以点中Menu Contents中的任何一个,再点击Menu中的View.
		Insert就能选择了.
	4.添加快捷键:
		1.选择"Keys",出现Key Assignments.选中"Custom Cmd: AStyle_C".
		2.选择Assign New Key.在弹出的窗口中输入快捷键"Ctrl+Alt+C".

### 3.使用

正常在View下面有AStyle_C这个菜单,也可以使用Ctrl+Alt+C快捷键使用.

先查看更改代码之后执行菜单是否有效果,可能出现3中情况:

	1.立马产生效果--->我的好像不行
	2.执行之后等一会会出现"xxx.c has been changed outside of the editor. Do you want to reload the file?"
		点击"Yes to All",就会产生变量. --->我的就是这样.
	3.执行之后需要将文件关闭重新打开才会产生变化,不知道是哪里出现了问题.

## 2.10 source insight还原默认配置

1.关闭source insight

2.打开我的文档,找到source insight文件夹(一般在路径:C:\用户(Users)\defy\我的文档(My Documents)\Source Insight)

3.打开Source Insight文件后打开"Settings"文件夹.

4.文件"GLOBAL.CF3"保存即为配置信息.如果需要删除该文件即可恢复到默认配置.

## 2.11 source insight 3.x解决回车换行缩进过度的方法

问题描述参见3.2.

	Options->Document Options->Auto Indenting
		1.在Auto Indent Type选择"Simple"
		2.去掉Smart Indent Options中的选项.

***

# 3. Source Insight 4.x版本的使用

## 3.1 source insight 4.x显示/去掉overview

	Options->Preferences->Display->去掉/勾选Overviews (based on file type)

## 3.2 source insight 4.x解决回车换行缩进过度的方法

在source insight 4.x在回车后,输入"{}".会自动缩进4个空格.影响编辑.解决办法:

	Options->File Type Options->Auto Indenting
		1.在Auto Indent Type选择"Simple"
		2.去掉Smart Indent Options中的选项.

## 3.3 source insight 4.x的项目文件列表正确显示

在source insight 4.x添加项目工程后,右边的project files可能不会正确的显示在右边,操作方法如下:

	菜单栏Panels->勾选上"Project Windows"即可.

***

# 4. Beyond Compare的使用

## 3.1 换行符文本比较时没有发现有区别,但是显示为"红色",表示有区别

文本中Windows下的换行符与Unix/Linux下的换行符的区别:

	1.在Beyond Compare文本比较时,虽然没有显示出任何文本的区别.但是在文本的上方的信息提示中会有:
		xxx字节(大小的区别) PC/UNIX(文本格式的区别)
	2.有第一步的区别,再查看:会话->会话设置->重要->勾上"比较行尾"->就可以显示出一片红色.
	由此可以确定换行符有差别(一个Windows下的;一个Unix下的).
