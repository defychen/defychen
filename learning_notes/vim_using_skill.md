# vim使用技巧

## 1. 在windows下编辑的脚本,难免会出现"^M"这样的错误(这种错误是windows下的换行符)

解决办法:

### 方法1 使用vim打开该脚本,然后执行:
	
	:set ff=unix

### 方法2 使用dos2unix命令:

	dos2unix aes_test.py

## 2. vim显示颜色

	1)拷贝.vimrc到自己的home目录,即"~/"
	2)source ~/.vimrc
	3)修改secure CRT配置,在仿真->终端选择"linux",并且勾上"ANSY颜色(A)",可以再尝试勾上"使用颜色方案"

	//修改.bashrc后也需要"source ~/.bashrc"

## 3. linux系统修改PATH环境变量的方法

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

## 4. linux显示所有的环境变量

	env		//命令env

## 5. 查看文件属于windows还是unix的方法

某个文件如果使用了windows下的换行符(\r\n),就属于windows类型的文件.在vim中使用:

	:set fileformat或者:set fileformat?
		//得到"fileformat=dos",即表示该文件属于windows类型的文件.此时需要将
		//换行符转换"dos2unix"
