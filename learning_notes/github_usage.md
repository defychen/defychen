## github usage
****

**1)新建一个目录:**

	mkdir github_push

**2)配置个人信息**

	git config --global user.name "defychen"
	git config --global user.email 894739534@qq.com

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
## git usage

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

## git pull更新时的问题

	Your local changes to the following files would be overwritten by merge
	error: Your local changes to the following files would be overwritten by merge:
		...	/*xxx file*/
	Please, commit your changes or stash them before you can merge.

	Solution method (1)
	使用代码库中的文件完全覆盖本地工作版本
	git reset --hard
	git pull

## github提交错误

	当执行"git pull"时出现下面的提示:
	There is no tracking information for the current branch.
	Please specify which branch you want to merge with.
	See git-pull(1) for details

    git pull <remote> <branch>

	If you wish to set tracking information for this branch you can do so with:

    git branch --set-upstream-to=origin/<branch> master
	
	//原因:本地分支和远程分支没有建立联系.解决:
	git branch --set-upstream-to=origin/master master	/*远程的和本地的分支都为master分支,并建立联系*/

## git打tag

	//方法 1
	git tag PDK1.12.0-20170616
	git push origin PDK1.12.0-20170616
	//方法 2
	git tag -a v0.0.1_20170705C  -m "update viaccess tag"
	git push origin --tags

	查看所打的tag
	git tag