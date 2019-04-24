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

## 5. 关于Ubuntu中出现"Could not get lock /var/lib/dpkg/lock"解决方案

**1.问题**

1.当执行"apt install python-pip(安装python的pip程序,以便可以pip install xxx)"时出错:

2.当执行"apt-get install gcc-arm-linux-gnueabi":下载并安装包时出错:

	E: Could not get lock /var/lib/dpkg/lock - open (11: Resource temporarily unavailable)
	E: Unable to lock the administration directory (/var/lib/dpkg/), is another process
	using it?

**2.原因**

简单描述为:apt还在运行,/var/lib/apt/lists、/var/lib/dpkg、/var/cache/archives会被锁定.导致其他apt操作不会成功.

	出现这个问题可能是有另一个程序正在运行,导致资源被锁不可用.而导致资源被锁的原因可能是上次运行安装或
	更新时没有正常完成,进而出现此状况.

**3.解决办法**

1.查找所有apt相关进程,并杀死:

	1.查找apt相关进程
	ps afx | grep apt
	 3284 pts/0    S+     0:00          \_ grep --color=auto apt
		//该进程自带,不能被kill.后面两个进程需要kill掉.
	 2869 ?        Ss     0:00 /bin/sh /usr/lib/apt/apt.systemd.daily install
	 2873 ?        S      0:00  \_ /bin/sh /usr/lib/apt/apt.systemd.daily lock_is_held install
	2.杀掉apt相关进程
		kill -9 2873
		kill -9 2869

2.删掉锁定的文件:

	1.删除对应目录下的锁文件:
		rm -rf /var/lib/dpkg/lock
	2.强制重新配置软件包:
		dpkg --configure -a
	3.更新软件包源文件
		apt update

**4.重新安装包文件即可**

	1.再次执行"apt install python-pip"	//如果安装python pip
	2.执行"apt-get install gcc-arm-linux-gnueabi"	//安装交叉编译工具链

## 6. 安装"net-tools"

**1.问题**

刚安装的linux可能在执行"ifconfig"时,没有这个命令.报如下的错误:

	Comand "ifconfig" not found, but can be installed with:
		apt install net-tools
	PS:即没有ifconfig命令.

**2.解决**

	apt install net-tools

## 7. 安装git

	sudo apt-get install git

注意点:
	1.查看git的版本:
	git --version
	2.sudo apt-get下载的文件的目录:
		/var/cache/apt/archives		//但是使用"sudo apt-get install git"没有发现文件
	3.文件下载的目录可以在"/etc/apt/source.list"中指定  --->还没有发现真正的用途

