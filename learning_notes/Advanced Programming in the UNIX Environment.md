# Advanced Programming in the UNIX Environment

***

## Chapter 1 UNIX基础知识

### 1.1 UNIX体系结构

操作系统是一种控制计算机硬件资源,提供程序运行环境的软件.这种软件也叫内核(kernel).

内核的接口称为系统调用(system call).公用函数库和shell(两者无交叉)构建在系统调用接口之上,应用程序可以使用公用函数库,也可以直接使用系统调用(位于最外围).

**用于解释脚本的shell位于"/bin/sh or bash or csh or ksh or tcsh等等(ali板子所用的shell是"/bin/sh")"**

/bin下面是一些基本的命令(e.g. mkdir、sh、dd、df等等)

	/*ls命令的简要实现*/
	#include "apue.h"	/*该书实现的头文件,其中包含了很多的头文件及一些函数的声明*/
	#include <dirent.h>	/*POSIX标准定义的unix类目录操作的头文件,包括opendir/readdir等函数*/
	
	int main(int argc, char *argv[])
	{
		DIR *dp;	/*opendir函数返回的指针,相当于fd*/
		struct dirent *dirp;	/*dirent:类目录操作的结构体,指针指向readdir(dp)的返回值*/

		if(argc != 2)	/*执行该程序需要带一个参数,加上程序名即为2*/
			err_quit("usage: ls directory_name");

		if((dp = opendir(argv[1])) == NULL)	/*打开argv[1]指向的目录,返回DIR结构的指针*/
			err_sys("can't open %s", argv[1]);
		while((dirp = readdir(dp)) != NULL)	/*readdir读取目录中的每一个目录项,返回dirent结构指针,没有目录项时返回NULL*/
			printf("%s\n", dirp->d_name);

		closedir(dp);
		exit(0);	/*参数0调用exit,参数0表示正常结束.*/
	}

	/*文件apue.h可以通过网站:http://download.csdn.net/download/li0524158198/6432861下载*/
	/*apue.h位于./apue3/apue3/src.3e/apue.3e/include*/

### 1.2 输入和输出

文件描述符(file descriptor):通常是一个小的非负整数.

	/*将标准输入复制到标准输出*/
	#include "apue.h"
	#define BUFFERSIZE	4096

	int main(void)
	{
		int n;
		char buf[BUFFERSIZE];

		/*
		STDIN_FILENO:标准输入(0)---默认为终端
		STDOUT_FILENO:标准输出(1)---默认终端,使用"> data"重定向到文件data
		STDERR_FILENO:标准错误输出(2)---默认终端  位于头文件<unistd.h>.
		read函数读到尾部返回0,发生读错误时返回-1,成功返回读取的字节数
		*/
		while((n = read(STDIN_FILENO, buf, BUFFERSIZE)) > 0)
			if(write(STDOUT_FILENO, buf, n) != n)
				err_sys("write error");

		if(n < 0)
			err_sys("read error");

		exit(0);
	}
	/*上述程序执行:./a.out > data. 等待输入,按下Ctrl+d---终止输入(使用时可能没响应,清屏下就可以了)*/

	/*the other method*/
	#include "apue.h"	/*stdin & stdout都在头文件<stdio.h>*/
	int main()
	{
		int c;
		while((c = getc(stdin)) != EOF)	/*getc:从标准输入(stdin)读读取一个字符直到EOF(文件尾)*/
			if(putc(c, stdout) == EOF)	/*putc:将一个字符写到标准输出(stdout)*/
				err_sys("output error");

		if(ferror(stdin))	/*标准输入错误*/
			err_sys("input error");

		exit(0);
	}

### 1.3 程序和进程

程序是硬盘中可执行文件.

进程是程序的执行实例(也有的叫task).

**进程ID(process ID):唯一标识每个进程的数字标识符,总是一个非负整数.**

	/*获得进程ID*/
	pid_t main_pid;	/*实际为int类型,在打印时可以使用"%ld"提高可移植性*/
	main_pid = getpid();	/*getpid():获得进程ID*/

**进程控制实例**

	#include "apue.h"
	#include <sys/wait.h>	/*使用wait()和waitpid()函数需要这个头文件*/
	
	int main()
	{
		char buf[MAXLINE];	/*在apue.h中定义*/
		pid_t pid;			/*pid类型,实际为int类型*/
		int status;			/*waitpid函数返回的状态(para2)保存在该变量*/
		
		printf("%% ");		/*输出提示符"%",要输出"%"必须写成"%%"*/
		while(fgets(buf, MAXLINE, stdin) != NULL)	{
		/*
		标准I/O函数:fgets从标准输入读取一行,遇到文件结束符作为行的第一个字符返回null指针
		fgets()函数返回每行以换行符(\n)终止,后随一个null字节.但execlp()函数要求其参数以"null"结束而非"\n"
		*/	
			if(buf[strlen(buf) - 1] == '\n')		/*null是不会计算进长度的*/
				buf[strlen(buf) - 1] = 0;	/*用"null"代替fgets行尾的"\n"*/

			if((pid = fork()) < 0) {
			/*
			fork()调用一次,返回两次.调用进程称为父进程,新创建的为子进程.
			fork在父进程中返回子进程的ID,子进程返回0.
			*/
				err_sys("fork error");
			} else if(pid == 0) { /*子进程*/
				execlp(buf, buf, (char *)0);
				/*
				para1:启动程序的路径名(exec中带"p"的不需要完整的路径,此处用buf也可以)
				para2:执行的命令名(程序名)
				para3:为"(char *)0"即可	
				*/
				err_ret("couldn't execute: %s", buf);
				exit(127);
			}
			/*父进程*/
			/*pid_t waitpid(pid_t pid, int *status, int options);
			para1:子进程ID
			para2:子进程结束状态在status变量
			para3:为0即可
			retval:成功返回子进程ID,否则返回"-1"
			*/
			if((pid = waitpid(pid, &status, 0)) < 0)
				err_sys("waitpid error");
			printf("%% ");	/*继续提示符*/
		}
		exit(0);
	}
	
由于进程内的所有线程共享进程资源,因此在各线程访问共享数据时需要采取一定的同步措施.

### 1.4 出错处理

UNIX/Linux系统函数(系统调用---e.g.open/write/mmap等)出错时,通常返回一个负值,该值会保存在errno中.
	
	/*open调用*/
	fd = open(ALI_SHA_DEV, O_RDWR);
	if(fd < 0) {
		printf("open %s failed: %s\n", ALI_SHA_DEV, strerror(errno));
		/*
		errno:保存错误号
		strerror:将errno映射为一个出错消息字符串,且返回该字符串指针,因此用"%s"输出.该函数在<string.h>中.
		e.g.
		linux中的<errno.h>定义:
		#define	ENOENT	2	/*No such file or directory*/
		当碰到errno为2时,使用"strerror(errno)"会输出"No such file or directory---出错消息" 
		*/
		return ALISLDSC_ERR_CANTOPENDEV;
	}

perror函数:输出一些出错信息

	#include <stdio.h>
	void perror(const char *msg);
	/*输出信息组成:
		msg字符串 + ":" + " " + "errno出错消息" + "换行"
		e.g.: "./a.out: No suce file or directory"
	*/

实例:

	#include "apue.h"
	#include <errno.h>

	int main(int argc, char *argv[])
	{
		fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
		/*fprintf:格式化输出
		para1:文件指针.可以是"stderr:标准错误输出(屏幕)",也可以是"open的fd,输出到某个文件"
		para2:输出格式
		para3:附加参数
		输出信息为"EACCES: Permission denied"
		*/
		errno = ENOENT;
		perror(argv[0]);	/*输出信息为:可执行文件名: errno映射的消息字符串(./test: No suce file or directory)*/
		exit(0);
	}

用户ID和组ID

	printf("uid = %d, gid = %d\n", getuid(), getgid());
	/*
	getuid():获得用户ID,返回一个整型数
	getgid():获得组ID, 返回一个整型数
	*/

### 1.5 信号

进程信号处理方式:

1、忽略信号---一般不使用

2、按系统默认处理---默认方式一般为终止进程

3、提供信号处理函数捕捉信号---较为常用,方便自己查找问题原因

	#include "apue.h"
	#include <sys/wait.h>	/*使用wait()和waitpid()函数需要这个头文件*/
	
 	+ static void sig_int(int);	/*自己的信号处理函数,para为信号值*/

	int main()
	{
		char buf[MAXLINE];	/*在apue.h中定义*/
		pid_t pid;			/*pid类型,实际为int类型*/
		int status;			/*waitpid函数返回的状态(para2)保存在该变量*/
		
	 + if(signal(SIGINT, sig_int) == SIG_ERR)	
		/*
		信号(此处为中断)与信号处理函数通过signal绑定,一旦"SIGINT"信号触发,会调用"sig_int"信号处理函数,并将信号值(SIGINT=2)作
		为参数传递给信号处理函数; retval:出错返回"SIG_ERR(-1)",	
		*/
	 +     err_sys("signal error");		

		printf("%% ");		/*输出提示符"%",要输出"%"必须写成"%%"*/
		while(fgets(buf, MAXLINE, stdin) != NULL)	{
		/*
		标准I/O函数:fgets从标准输入读取一行,遇到文件结束符作为行的第一个字符返回null指针
		fget()函数返回每行以换行符(\n)终止,后随一个null字节.但execlp()函数要求其参数以"null"结束而非"\n"
		*/	
			if(buf[strlen(buf) - 1] == '\n')
				buf[strlen(buf) - 1] = 0;	/*用"null"代替fgets行尾的"\n"*/

			if((pid = fork()) < 0) {
			/*
			fork()调用一次,返回两次.调用进程称为父进程,新创建的为子进程.
			fork在父进程中返回子进程的ID,子进程返回0.
			*/
				err_sys("fork error");
			} else if(pid == 0) { /*子进程*/
				execlp(buf, buf, (char *)0);
				/*
				para1:启动程序的路径名(exec中带"p"的不需要完整的路径,此处用buf也可以)
				para2:执行的命令名(程序名)
				para3:为"(char *)0"即可	
				*/
				err_ret("couldn't execute: %s", buf);
				exit(127);
			}
			/*父进程*/
			/*pid_t waitpid(pid_t pid, int *status, int options);
			para1:子进程ID
			para2:子进程结束状态在status变量
			para3:为0即可
			retval:成功返回子进程ID,否则返回"-1"
			*/
			if((pid = waitpid(pid, &status, 0)) < 0)
				err_sys("waitpid error");
			printf("%% ");	/*继续提示符*/
		}
		exit(0);
	}
	+ /*信号处理函数*/
	+ void sig_int(int signo)	/*参数为信号值*/
	+ {
	+     printf("interrupt\n");
	+ }

### 1.6 时间值

	cd /usr/include
	time -p grep _POSIX_SOURCE */*.h > /dev/null		/*统计grep查找该文件的时间,并将查找到的信息输出到"/dev/null"*/
	得到的信息为:
		real 1.71	/*时钟时间:我们正常使用的时间*/
		user 0.01	/*用户CPU时间:执行用户指令所用的时间*/
		sys 0.05	/*系统CPU时间:为该进程执行内核程序所经历的时间*/
***
## Chapter 2 UNIX标准及实现

**略**
***
## Chapter 3 文件I/O

### 3.1 文件描述符

文件描述符"0"---标准输入(常用STDIN_FILENO代替),定义在<unistd.h>中

文件描述符"1"---标准输出(常用STDOUT_FILENO代替),定义在<unistd.h>中

文件描述符"2"---标准错误输出(常用STDERR_FILENO代替),定义在<unistd.h>中

### 3.2 函数open和openat

打开/创建一个文件:

retval:成功返回文件描述符(>=0),失败返回"-1"

	#include <fcntl.h>	/*文件的控制头文件, e.g. O_RDWR读写方式打开等*/
	int open(const char *path, int oflag, .../*mode_t mode*/);	/*"...":余下的参数(数量及其类型)是可变*/
	int openat(int fd, const char *path, int oflag, ...);---用的比较少
	/*
	retval:成功返回文件描述符(>=0),失败返回"-1"
	*/	

	e.g.:
	1.open("/dev/dsc0", O_RDWR);
	2.open(const char *path, int oflags, .../*mode_t mode*/);	/*只有当oflags有"| O_CREAT"创建新文件并才生效*/

### 3.3 函数creat

创建一个新文件:

retval:成功返回文件描述符(>=0),失败返回"-1"

	#include <fcntl.h>
	int creat(const char *path, mode_t mode);	/*creat后续只能以"只写"方式打开所创建的文件,因为创建的文件为"空"*/
	creat()等效于---open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
	/*为了能够读写文件,现在常用的为:*/
	open(path, O_RDWR | O_CREAT | O_TRUNC, mode);
		
### 3.4 函数close

关闭一个打开的文件:

retval:成功返回"0",出错返回"-1".

	#include <fcntl.h>
	int close(int fd);

### 3.5 函数lseek

为一个打开文件设置偏移量

retval:成功返回文件偏移量(距离文件头的长度---字节),出错返回"-1"

	#include <unistd.h>	/*unix std的意思(linux编程都需要包含该头文件),包含read/write/getpid等等*/
	off_t lseek(int fd, off_t offset, int whence);
	/*
	1)whence是SEEK_SET(文件头), 将该文件偏移量设置为距文件头offset个字节处
	2)whence是SEEK_CUR(当前位置), 将该文件偏移量设置为当前值+offset(offset可正可负)
	3)whence是SEEK_END(文件尾), 将该文件偏移量设置为文件尾+offset(可正可负)
	*/
	/*确定打开文件当前偏移量或文件长度*/
	off_t currpos;
	off_t length;
	currpos = lseek(fd, 0, SEEK_CUR);	/*当前偏移量*/
	length = lseek(fd, 0, SEEK_END);	/*文件长度*/

如果文件描述符(fd)指向管道、FIFO或网络套接字(socket), lseek返回-1,并将errno设置为"ESPIPE".

**测试标准输入、管道、FIFO等能否设置偏移量**

	#include "apue.h"
	int main()
	{
		if(lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
			printf("cannot seek\n");
		else
			printf("seek OK\n");
		exit(0);
	}
	/*执行该程序时:
		./a.out	< /etc/passwd--->seek OK("<"标准输入,可行)
		cat < /etc/passwd | ./a.out--->cannot seek("|"管道输入,不可以)
		./a.out < /var/spool/cron/FIFO--->cannot seek("FIFO"输入,不可以)	
	*/

*lseek(fd, offset, SEEK_SET);---offset可以大于文件的当前长度,如果采用这种方式在下一次写时将在文件中构成一个空洞,这些空洞的字节都将被读成"0",而且不占磁盘空间.*

	/*od命令查看某文件的实际内容*/
	od -c mk.rule	/*字符方式打印文件内容*/
	0000000   L   I   N   U   X   _   D   I   R       :   =       /   z   h
	0000020   s   a   0   2   2   /   u   s   r   h   o   m   e   /   d   e
	0000040   f   y   .   c   h   e   n   /   r   e   p   o   s   i   t   o
	0000060   r   y   /   w   o   r   k   _   v   i   a   c   c   e   s   s
	0000100   /   b   u   i   l   d   r   o   o   t  \n   C   R   O   S   S
	0000120   _   C   O   M   P   I   L   E       =       $   (   L   I   N
	0000140   U   X   _   D   I   R   )   /   o   u   t   p   u   t   /   h
	0000160   o   s   t   /   o   p   t   /   e   x   t   -   t   o   o   l
	0000200   c   h   a   i   n   /   b   i   n   /   m   i   p   s   -   l
	/*0000200---8进制表示的数*/

### 3.6 函数read

从打开文件中读取数据

retval:成功返回读到的字节数(若从文件尾开始读时返回0),出错返回-1.

	#include <unistd.h>
	ssize_t read(int fd, void *buf, size_t nbytes);
	/*
	ssize_t:返回值为带符号的整型,满足正整数字节数、0、-1(出错)等要求.
	void *:通用指针.
	size_t:不带符号的整型(>=0).
	*/

### 3.7 函数write

向打开的文件写数据

retval:成功返回写入的字节数,出错返回"-1".

	#include <unistd.h>
	ssize_t write(int fd, const void *buf, size_t nbytes);
	/*返回值通常与参数nbytes相同,否则表示出错.*/

### 3.8 文件共享

内核使用3种数据结构表示打开文件---进程表项、文件表项、v节点表项.

1)进程表项:每个进程在进程表中都有一个记录项---进程表项,包含一张打开的文件描述符表.该文件描述符表有多项文件描述符.每个文件描述符为一个矢量,包括fd标志和一个指向文件表项的指针.

2)文件表项:所有打开的文件都有一张文件表,包括:文件状态标志(读、写等)、当前文件偏移量、指向v节点表项的指针.

3)v节点表项:每个打开的文件(设备)都有一个v节点结构.v节点包括:文件类型、对该文件的各种操作函数的指针,还有i节点(i-node,索引节点)---i节点包含了文件所有者、长度即实际数据在磁盘的位置指针.---linux没有v节点,只有i节点，实现功能一样.

v节点信息才是最终操作文件的地方,一个文件只有一个v节点表项.

**两个进程打开统一文件时:1)不同的进程表项;2)不同的文件表项;3)相同的v节点表项(同一个文件).**

### 3.9 原子操作

**原子操作(atomic operation):指由多步组成的一个操作.如果该操作原子地执行,则要么执行完所有步骤,要么一步也不执行,不存在只执行所有步骤中的一个子集.**

	e.g.早期Unix不支持open的O_APPEND选项,所以程序会写成:
		step1:
		if(lseek(fd, OD, 2) < 0)	/*position to EOF(定位到文件尾)*/
			err_sys("lseek error");
		step2:
		if(write(fd, buf, 100) != 100)	/*write 100 bytes(向fd写入数据)*/
			err_sys("write error");
	
	如果两个进程同时向一个文件尾写数据,由于一个写操作被分成了两部,可能会出现某一个进程调用到lseek后另一个进程占有了时间片,然后往该文件写数据.写完后第一个进程会按着原本lseek定位的位置写数据,造成数据覆盖.
	使用原子操作,可以将两个步骤合二为一,构成一个操作步骤.使用O_APPEND打开文件就是原子操作.

### 3.10 函数dup和dup2

复制一个现有的文件描述符:

	#include <unistd.h>
	int dup(int fd);	/*返回新的文件描述符,且为最小值*/
	int dup2(int fd, int fd2);	/*复制fd为fd2*/
	/*
	retval:成功返回新的文件描述符,失败返回"-1"
	*/

### 3.11 函数sync、fsync和fdatasync

Unix系统和Linux系统在内核中有缓冲区进行数据缓存(e.g.当向文件写入数据时,内核会先将数据复制到缓冲区,然后排入队列,晚些时候才会写入磁盘---也叫延迟写(delay write)).

*下面三个函数保证磁盘上的文件系统与缓冲区内容一致,可以主动将缓冲区的数据刷入磁盘:*

	#include <unistd.h>
	void sync(void);
	/*只将"修改过"的块缓冲区数据排入写队列,然后返回,不等磁盘写结束.系统的update守护进程会周期性的(30s)调用sync函数,
	命令sync也调用sync函数*/
	int fsync(int fd);
	/*只对"fd"指定的一个文件起作用,并且等待写磁盘结束才返回.一般用于数据库应用程序*/
	int fdatasync(int fd);	/*类似于fsync,但是只作用数据部分*/
	// retval:成功返回0,失败返回"-1"

### 3.12 函数fcntl

改变已经打开文件的属性:

	#include<fcntl.h>
	int fcntl(int fd, int cmd, .../*int arg*/)
	/*cmd的值为:
	1)F_DUPFD或F_DUPFD_CLOEXEC---复制一个已有的文件描述符(用的较少)
	2)F_GETFD或F_SETFD---获取/设置文件描述符标志
	3)F_GETFL或F_SETFL---获取/设置文件状态标志(e.g.O_RDONLY/O_WRONLY/O_RDWR...)
	4)F_GETOWN或F_SETOWN---获取/设置异步I/O所有权
	5)F_GETLK、F_SETLO或F_SETLKW---获取/设置记录锁
		retval:成功返回对应的某个值,失败返回"-1".
	*/

*实例:*

	#include <apue.h>
	#include <fcntl.h>

	int main(int argc, char *argv[])
	{
		int val;
	
		if(argc != 2)
			err_sys("usage: a.out <decriptor#>");

		if((val = fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)	/*atoi:字符转变为整型, 获取atoi(argv[1])文件状态标志值，
		并返回给val*/
			err_sys("fcntl error for fd %d", atoi(argv[1]));

		switch(val & O_ACCMODE)	/*ACCMODE:access mode(也叫屏蔽字),取得访问方式位(O_RDONLY/O_WRONLY/O_RDWR...)*/
		{
			case O_RDONLY:
				printf("read only");
				break;
			case O_WRONLY:
				printf("write only");
				break;
			case O_RDWR:
				printf("read write");
				break;
			default:
				err_dump("unkown access mode");
		}

		if(val & O_APPEND)
			printf(", append");	/*这句话会加在上面打印的后面*/
		if(val & O_NONBLOCK)
			printf(", nonblocking");
		if(val & O_SYNC)
			printf(", synchronous writes");

		#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC) && (O_FSYNC != O_SYNC)	/*使用这种方式决定后面的执行与否*/
			if(val & O_FSYNC)
				printf(", synchronous writes");
		#endif
		
		putchar("\n");	/*输出一个换行符*/
		exit(0);
	}
	
	/*测试情况:
		./a.out 0 < /dev/tty	---read only
		./a.out 1 > demp.foo
		cat temp.foo			---write only
		./a.out 2 2>>temp.foo	---write only, append
		./a.out 5 5<>temp.foo	---read write
	*/

*修改文件描述符*

	val = fcnlt(fd, F_GETFL, 0)	/*先获得文件描述*/
	val |= flags;	/*修改val,需要设置的值*/
	fcnlt(fd, F_SETFL, val)	/*将val设置到fd*/
	
### 3.13 函数ioctl

I/O操作的杂物箱,对没有标准函数可以进行的I/O操作,都可以用ioctl进行操作.

	#include <sys/ioctl.h>	/*linux ioctl的头文件*/
	int ioctl(int fd, int/unsigned long request, ...);	/*...表示的其余参数一般为一个变量或者结构体指针*/
***
## Chapter 4 文件和目录

本章描述文件系统的特征和文件的性质.

### 4.1 函数stat、fstat、fstatat和lstat

获得与文件有关的一些信息:

	#include <sys/stat.h>
	int stat(const char *restrict pathname, struct stat *restrict buf);	
	/*获得与文件(pathname)有关的信息结构,保存在struct stat结构体指针buf
	struct stat buf;
	stat("/etc/passwd", &buf);
	*/
	int fstat(int fd, struct stat *buf);	/*获得用文件描述符fd表示的打开文件的有关信息*/
	int lstat(const char *restrict pathname, struct stat *restrict buf);
	/*与stat类似,但是当文件为一个符号链接时,lstat获得符号链接的有关信息,而不是该符号链接引用的文件的信息.*/
	int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flag);
	/*很复杂,综合了上述几种*/
	//retval:成功返回0,失败返回-1

*stat函数使用最多的地方是"ls -l"命令---获得文件的所有信息*

### 4.2 文件类型

文件类型信息包含在struct stat结构体的st_mode成员中.当用stat、fstat、lstat等函数获得文件的所有信息后(保存在struct stat结构体中,然后取st_mode成员,配合下面的宏可得到具体的文件类型)
	
	S_ISREG()---普通文件
	S_ISDIR()---目录文件
	S_ISCHR()---字符特殊文件
	S_ISBLK()---块特殊文件
	S_ISFIFO()---管道或FIFO
	S_ISLNK()---符号链接
	S_ISSOCK()---套接字
	e.g.S_ISREG(buf.st_mode);

**例子:打印文件类型**

	#include <apue.h>
	int main(int argc, char *argv[])
	{
		int i;
		struct stat buf;
		char *ptr;

		for(i = 1; i < argc; i++){	/*取每一个命令行参数,进行相关的判断*/
			printf("%s: ", argv[i]);
			if(lstat(argv[i], &buf) < 0)	/*获取每一个命令行参数的文件信息,并保存在buf中*/
			{
				err_ret("lstat error");
				continue;	/*跳过后面,直接进行下一次循环*/
			}
			if(S_ISREG(buf.st_mode))	/*判断为普通文件,成功返回true*/
				ptr = "regular";
			else if(S_ISDIR(buf.st_mode))	/*判断为目录文件,成功返回true*/
				ptr = "directory";
			else if(S_ISCHR(buf.st_mode))	/*判断为字符特殊文件,成功返回true*/
				ptr = "character special";
			else if(S_ISBLK(buf.st_mode))	/*判断为块特殊文件,成功返回true*/
				ptr = "block special";
			else if(S_ISFIFO(buf.st_mode))	/*判断为管道或FIFO文件,成功返回true*/
				ptr = "fifo";
			else if(S_ISLNK(buf.st_mode))	/*判断为符号链接,成功返回true*/
				ptr = "symbolic link";
			else if(S_ISSOCK(buf.st_mode))	/*判断为套接字,成功返回true*/
				ptr = "socket";
			else
				ptr = "** unknown mode **";
			printf("%s\n", ptr);
		}
		exit(0);
	}

	/*程序测试:
		./a.out /etc/passwd /etc /dev/log /dev/tty \
		> /var/lib/oprofile/opd_pipe /dev/sr0 /dev/cdrom
		解析:
		/dev/log(socket文件) /dev/tty(character special) \(末端键入反斜杠,通知shell下一行继续键入命令,下一行提示符">")
		/var/lib/oprofile/opd_pipe(fifo) /dev/sr0(block special) /dev/cdrom(symbolic link)
	*/

### 4.3 设置用户ID和设置组ID

设置用户ID位及设置组ID位都包含在文件的struct stat结构体st_mode成员中,可用宏S_ISUID和S_ISGID测试.

### 4.5 文件的访问权限

st_mode值包含了对文件的访问权限位.所有的文件类型(普通文件、目录、字符特殊文件、块特殊文件等)都有访问权限(access permission)

rule 1:用名字打开任一类型的文件时,对该名字中包含的每一个目录,都应该具有执行权限.

	打开文件/use/include/stdio.h,需要对目录/、/usr和/usr/include具有执行权限.而最终需要对stdio.h文件本身需要什么权限取决于以
	何种模式打开(read/read-write等)
	/*
	读权限:允许我们读目录,获得在该目录中所有文件名的列表
	执行权限:决定我们能够通过某目录(搜索目录)寻找到某个特定文件名.e.g.PATH如果指定了一个不具有执行权限的目录,shell绝不会在该目录
	下找到可执行文件(压根不能通过该目录(即搜索该目录)).*/

rule 2:文件读权限决定我们能否打开该文件进行读操作,与open中的O_RDONLY和O_RDWR有关.

rule 3:文件写权限决定我们能否打开该文件进行写操作,与open中的O_WRONLY和O_RDWR有关.

rule 4:在open函数中对一个文件指定O_TRUNC标志,必须对该文件具有写权限.

rule 5:在一个目录中创建一个新文件,必须对该目录具有写和执行权限.

rule 6:在一个目录中删除一个文件,必须对该目录具有写和执行权限,对该文件本身不需要读、写权限.

rule 7:7个exec函数中任何一个执行某个文件,必须对该文件具有执行权限,而且该文件必须是一个普通文件.

### 4.6 函数access和faccessat

access和faccessat函数是按实际用户ID和实际组ID进行访问权限测试的.

	#include <unistd.h>
	int access(const char *pathname, int mode);	/*para1:测试文件的路径名; mode:权限(R_OK/W_OK/X_OK---读/写/执行权限)*/
	int faccessat(int fd, const char *pathname, int mode, int flag);	/*用的较少*/
	/*retval:成功返回0，失败返回"-1"*/

实例

	#include "apue.h"
	#include <fcntl.h>

	int main(int argc, char *argv[])
	{
		if(argc != 2)
			err_quit("usage: a.out <pathname>");
		if(access(argv[1], R_OK) < 0)	/*测试argv[1]文件访问权限*/
			err_ret("access error for %s", argv[1]);
		else
			printf("read access OK\n");
		if(open(argv[1], O_RDONLY) < 0)
			err_ret("open error for %s", argv[1]);
		else
			printf("open for reading OK\n");
		exit(0);
	}

	/*
	测试:
	./a.out a.out	/*输出:read access OK和open for reading OK*/
	/*上述因为权限为"-rwxrwxr-x",可用于读访问*/
	./a.out /etc/shadow	/*输出:access error for /etc/shadow: Permission denied和open error for /etc/shadow: 
	Permission denied*/
	su -		/*切换到超级用户,因为下面的权限更改需要的root权限下操作*/
	/*上述因为权限为"-r-------- 1 root", 而且属于root用户.而a.out这一可执行文件属于普通用户*/
	chown root a.out	/*更改a.out这一文件为root用户ID*/
	chmod u+s a.out		/*设置SUID位,此时a.out程序可以访问root用户的文件*/
	exit	/*退出超级用户,恢复普通用户进行测试*/
	./a.out /etc/shadow	/*输出access error for /etc/shadow: Permission denied和open for reading OK*/
	/*access访问权限不够是因为:使用实际用户ID(普通登录用户)去访问属于root用户的文件,因此不能访问, 
	而open是因为用该程序(a.out)去访问该文件(/etc/shadow),此时两者都属于root用户,可以访问成功*/
	*/

**Linux进程中的各ID**

1)实际用户ID和实际组ID:linux以某个用户名登录时(e.g."defy.chen"),在linux上运行的所有命令的实际用户ID或组ID都是"defy.chen"的uid/gid

2)有效用户ID和有效用户组ID:进程用来决定我们对资源的访问权限.一般情况下,有效等于实际.但是当SUID(设置用户ID位)/SGID(设置组ID位),有效用户/组ID等于文件的所有者的uid/文件所有者的gid.不再是实际用户/组ID.

	命令"id"可以查看当前登录用户的uid,gid及groups---即实际ID	
	设置SUID和SGID方法:
	chown gkh test---设置test文件的所有者为gkh
	chgrp gkh test---设置test文件的所属组为gkh
	chmod u+s test---设置SUID(此时有效用户ID不等于实际用户ID)
	chmod g+s test---设置SGID(此时有效组ID不等于实际组ID)

### 4.7 函数umask

umask函数为进程设置文件模式创建屏蔽字(即屏蔽文件的某些权限---将某位置"1"即为取消该权限)

	#include <sys/stat.h>	/*与文件有关的头文件*/
	mode_t umask(mode_t cmask);	/*cmask值为: S_IR/W/XUSR、S_IR/W/XGRP、S_IR/W/XOTH,也可以为0表示什么都不屏蔽*/

实例

	#include "apue.h"
	#include <fcntl.h>
	
	#define RWRWRW	(S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)		/*linux中默认新创建的文件权限*/

	int main(void)
	{
		umask(0);	/*表示什么权限都不取消*/
		if(creat("foo", RWRWRW) < 0) /*foo文件权限为"-rw-rw-rw-"*/
			err_sys("creat error for foo");
		umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);	/*禁止文件的所属组和其他用户的读、写权限*/
		if(creat("bar", RWRWRW) < 0)	/**bar文件权限为"-rw-------"/
			err_sys("creat error for bar");
		exit(0);
	}

**在linux中运行的进程(e.g. a.out)其父进程都是shell进程,在a.out中使用umask函数更改权限不会影响到shell中的权限.shell可以使用umask命令更改当前创建文件的权限**

	/*linux默认新创建文件的权限为"-rw-rw-rw-"*/
	umask	/*显示当前文件模式创建屏蔽字(即新创建的文件的会取消的权限)---一般为002(数字格式)*/
	umask -S		/*显示符号格式"u=rwx, g=rwx, o=rx"---将o的w权限给取消了*/
	umask 027	/*更改文件模式创建屏蔽字(更改为"取消所属组的写、其他用户的全部权限")*/
	umask -S		/*显示为"u=rwx, g=rx, o="*/
