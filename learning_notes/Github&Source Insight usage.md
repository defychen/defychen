# 1. Github usage

## 1. How to use git to commit code
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
## 2. git usage

**1)查看历史提交版本**

	git log		/*整个大目录的历史提交版本*/
	git log .	/*查看某个目录的历史提交版本(e.g.buildroot)*/
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

## 3. git pull更新时的问题

	Your local changes to the following files would be overwritten by merge
	error: Your local changes to the following files would be overwritten by merge:
		...	/*xxx file*/
	Please, commit your changes or stash them before you can merge.

	Solution method (1)
	使用代码库中的文件完全覆盖本地工作版本
	git reset --hard
	git pull

## 4. github提交错误

	当执行"git pull"时出现下面的提示:
	There is no tracking information for the current branch.
	Please specify which branch you want to merge with.
	See git-pull(1) for details

    git pull <remote> <branch>

	If you wish to set tracking information for this branch you can do so with:

    git branch --set-upstream-to=origin/<branch> master
	
	//原因:本地分支和远程分支没有建立联系.解决:
	git branch --set-upstream-to=origin/master master	/*远程的和本地的分支都为master分支,并建立联系*/

## 5. git打tag

	//方法 1
	git tag PDK1.12.0-20170616
	git push origin PDK1.12.0-20170616
	//方法 2
	git tag -a v0.0.1_20170705C  -m "update viaccess tag"
	git push origin --tags

	查看所打的tag
	git tag

## 6. git push origin master提交时出现提交不成功

	使用git push origin master推code时出现:Everything up-to-date.一直没有将code的更新push上去
	
	##原因:
		--->可能是因为在使用git commit "xxx"	//添加注释时没成功.
		--->正确的应该是:git commit -m "xxx"	//应该有个"-m"

## 7. git查看版本

	git --version		//得到git version 2.3.0

***

# 2. Source Insight usage

## 1.设置背景色

	Options->Preferences->Colors->Window Background->设置红(R):204, 绿(G):232, 蓝(U):207

## 2.常用快捷键

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
	