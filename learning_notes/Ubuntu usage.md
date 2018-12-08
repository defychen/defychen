# ubuntu 16.04 usage

## 1. 忘记root密码解决办法

**方法 1**

如果用户具有sudo权限:

	1.sudo su root	//通过sudo直接切换到root用户
	2.passwd		//重新更改root密码
	/*
		提示:输入新的UNIX密码->重新输入新的UNIX密码->更改root密码成功.
	*/

**方法 2**

用户不具备sudo权限,需要进入GRUB修改kernel镜像启动参数,此处暂时略.

## 2. root用户和普通用户的切换

1.切换到root用户

	1.su root	//切换到root用户,输入root用户密码即可.仍然停在当前目录
	2.su -		//切换到root用户,输入root用户密码即可.同时切换到当前用户的home目录.

2.切换到普通用户

	su defychen		//切换到defychen用户(defychen为普通用户名).

## 3. vim软件的安装

	sudo apt-get install vim
	echo $?		//返回0表示软件安装成功;非0表示出现了问题.

## 4. 检查软件更新情况并将软件进行更新

	1.sudo apt-get update
	/*
		更新/etc/apt/sources.list和/etc/apt/sources.list.d中列出的源的地址.这样才能获取到最新的
		软件包.
	*/
	2.sudo apt-get upgrade
	/*
		升级已安装的所有软件包,将本地的软件版本与update文件更新的版本进行对比从而进行相关升级.因此,执行
		upgrade之前一定要执行update,这样才能保证更新到最新.
	*/

