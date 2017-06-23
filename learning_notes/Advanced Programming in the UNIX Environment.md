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
	
 	+ 
 	+ ic void sig_int(int);	/*自己的信号处理函数,para为信号值*/

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

### 4.8 函数chmod、fchmod和fchmodat

用于改变现有文件的访问权限

	#include <sys/stat.h>
	int chmod(const char *pathname, mode_t mode);	/*在指定文件上改变文件权限*/
	int fchmod(int fd, mode_t mode);	/*对打开的文件进程改变文件权限*/
	int fchmodat(int fd, const char *pathname, mode_t mode, int flag);	/*用的较少*/
	/*retval:成功返回0,失败返回"-1"*/

**改变一个文件的权限位,进程的有效用户ID必须等于文件的所有者ID,或者该进程具有超级用户权限.**

mode常量如下:

	S_ISUID			设置用户ID
	S_ISGID			设置组ID
	S_ISVTX			保存正文(粘着位)

	S_IRWXU			用户读、写、执行权限
	S_IR/W/XUSR		用户读/写/执行权限
	S_IRWXG			组读、写、执行权限
	S_IR/W/XGRP		组读/写/执行权限
	S_IRWXO			其他读、写、执行权限
	S_IR/W/XOTH		其他读/写/执行权限

实例

	#include <apue.h>
	int main(void)
	{
		struct stat statbuf;	/*保存文件的信息的结构体*/
		/*关闭组执行权限和设置组ID*/
		if(stat("foo", &statbuf) < 0)	/*获取"foo"文件的信息结构,存放在statbuf的指针中*/
			err_sys("stat error for foo");
		if(chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0) 
		/*为foo关闭组执行权限和设置组ID,此时权限为"-rw-rwSrw"*/
			err_sys("chmod error for foo");

		/*设置绝对权限为"-rw-r--r--"*/
		if(chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)	/*此时权限为"-rw-r--r--"*/
			err_sys("chmod error for bar");
		exit(0);
	}

chmod函数更新的只是i节点最近一次被修改的时间,不会更新修改文件内容的时间."ls -l"列出的是最后修改文件内容的时间.

### 4.9 函数chown、fchown、fchownat和lchown

用于改变文件的用户ID和组ID.

	#inclulde <unistd.h>
	int chown(const char *pathname, uid_t owner, gid_t group);
	int fchown(int fd, uid_t owner, gid_t group);
	int fchownat(int fd, const char *pathname, uid_t owner, gid_t group, int flag);
	int lchown(const char *pathname, uid_t owner, gid_t group);
	/*retval:成功返回0,失败返回"-1"*/

### 4.10 文件长度

struct stat结构成员st_size表示以字节为单位的文件长度(文件包括普通文件、目录文件和符号链接).

普通文件长度可以是0.

目录文件长度是16/512的整数倍.

符号链接文件长度是文件名的实际字节数.e.g.某个文件链接到"usr/lib",此时的符号链接文件长度为"7".

### 4.11 文件截断

在文件尾端截去一些数据以缩短文件.

	#include <unistd.h>
	int truncate(const char *pathname, off_t length);
	int ftruncate(int fd, off_t length);
	/*
	如果该文件长度大于length,就截断超过length的部分;如果该文件长度小于lenght,就增加文件长度,增加的部分都读作0(产生文件空洞)
	retval:成功返回0,失败返回"-1"
	*/

### 4.12 文件系统

UFS:Unix file system(Unix文件系统)

### 4.13 函数link、linkat、unlink、unlinkat和remove

link/linkat创建一个指向现有文件的链接

	#include <unistd.h>
	int link(const char *existingpath, const char *newpath);
	int linkat(int efd, const char *existingpath, int nfd, const char *newpath, int flag);
	/*创建一个新目录项newpath(只创建最后一个分量,路径中的其他部分应当已经存在),并引用现有文件existingpath.
	进而会增加一个文件的链接*/
	/*retval:成功返回0,失败返回"-1"*/

unlink/unlinkat删除一个目录项,并将文件的链接数减1

	#include <unistd.h>
	int unlink(const char *pathname);
	int unlinkat(int fd, const char *pathname, int flag);
	/*成功返回0,失败返回"-1"*/

实例

	#include "apue.h"
	#include <fcntl.h>
	int main(void)
	{
		if(open("tempfile", O_RDWR) < 0)
			err_sys("open error");
		if(unlink("tempfile") < 0)	/*patname为当前路径的文件名*/
			err_sys("unlink error");
		printf("file unlinked\n");	/*打印该句表示:解除文件链接成功,会删除该文件*/
		sleep(15);
		printf("done\n");
		exit(0);
	}

	/*运行:
		df /home	/*查看磁盘使用情况"/home"*/
		./a.out &	/*"&"后台运行程序*/
	*/

remove:对于文件与unlink相同,对于目录与rmdir相同.

	#include <stdio.h>
	int remove(const char *pathname);	/*retval:成功返回0,失败返回"-1"*/

### 4.14 函数rename和renameat

文件或目录重命名(这一函数用的较少)

	#include <stdio.h>
	int rename(const char *oldname, const char *newname);
	int renameat(int oldfd, const char *oldname, int newfd, const char *newname);
	/*retval:成功返回0,失败返回"-1"*/

### 4.15 符号链接

符号链接是对一个文件的间接指针,硬链接直接指向文件的i节点(硬链接限制较多)

实例(符号链接引入死循环)

	mkdir foo
	touch foo/a
	ln -s foo foo/testdir	/*创建符号链接"foo/testdir",链接到foo目录*/
	符号链接显示为:"lrwxrwxrwx ... testdir -> foo"---显示中的的"l"和"->"表明是一个符号链接

	如果遍历这一个目录,会形成死循环(errno为ELOOP)
	"foo" "foo/a" "foo/testdir" "foo/testdir/a" "foo/testdir/testdir" "foo/testdir/testdir/a"...死循环

实例2

	ln -s /no/such/file myfile	/*创建符号链接"myfile",链接到一个不存在的文件*/
	ls myfile	/*ls可以查看到这个文件*/
	cat myfile---No such file or directory	/*试图查看该文件,是一个符号链接,但是链接的文件不存在,因此报错*/
	ls -l myfile		/*可以查看*/

### 4.16 创建和读取符号链接

symlink/symlinkat创建一个符号链接

	#include <unistd.h>
	int symlink(const char *actualpath, const char *sympath);
	int symlinkat(const char *actualpath, int fd, const char *sympath);
	/*创建一个指向actualpath的新目录项sympath,actualpath不要求必须存在*/
	/*retval:成功返回0,失败返回"-1"*/

readlink/readlinkat读取符号链接名字,打开符号链接本身(open会跟随符号链接,即会打开符号链接真正链接的文件)

	#include <unistd.h>
	ssize_t readlink(const char *restrict pathname, char *restrict buf, size_t bufsize);
	ssize_t readlink(int fd, const char *restrict pathname, char *restrict buf, size_t bufsize);
	/*执行成功返回读入buf的字节数.在buf中返回的符号链接的内容不以null字节终止*/

### 4.17 文件的时间

struct stat结构体的3个时间字段

	st_atim		文件数据的最后访问时间		e.g.read可以更改该时间	查看"ls -lu"
	st_mtim		文件数据的最后修改时间		e.g.write可以更改该时间	查看"ls -l"/ls
	st_ctime	i节点状态最后更改时间		e.g.chmod/chown可以更改	查看"ls -lc"

### 4.18 函数futimens、utimensat和utimes

更改一个文件的访问和修改时间

	#include <sys/stat.h>
	int futimens(int fd, const struct timespec times[2]);	/*修改:times[2]应该为"*times",为一个指针*/
	int utimensat(int fd, const char *path, const struct timespec times[2], int flag);
	/*
	para1:文件描述符
	para2:
		struct stat statbuf;
		times[1] = statbuf.st_atim;	/*访问时间*/
		times[2] = statbuf.st_mtim;	/*文件内容修改时间*/
	*/
	/*retval:成功返回0,失败返回"-1"*/

utimes:对路径名进行操作(扩展用的,一般不用)

	#include <sys/time.h>
	int utimes(const char *pathname, const struct timeval times[2]);
	struct timeval{
		time_t tv_sec;	/*seconds秒数*/
		long tv_usec;	/*microseconds微秒*/
	};

实例(open函数使用O_TRUNC将文件长度截断为0,但并不更改其访问和修改时间)

	#include "apue.h"
	#include <fcntl.h>
	int main(int argc, char *argv[])
	{
		int i, fd;
		struct stat statbuf;
		struct timespec times[2];
		for(i = 0; i < argc; i++) {
			/*对多个文件都执行该操作*/
			if(stat(argv[i], &statbuf) < 0) {
				err_ret("%s: stat error\n", argv[i]);
				continue;
			}
			if((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0)	｛/*truncate截断*/
				err_ret("%s: open error\n", argv[i]);
				continue;	
			}
			times[0] = statbuf.st_atim;
			times[2] = statbuf.st_mtim;
			if(futimens(fd, times) < 0)	/*更改访问和修改时间*/
				err_ret("%s: futimens error", argv[i]);
			close(fd);
		}
		exit(0);
	}

	/*
	date ---打印当天时间
	ls -lu filename	---查看最后访问时间
	ls -l filename	---查看内容修改时间
	ls -lc filename	---查看状态更改时间
	*/

### 4.19 函数mkdir、mkdirat和rmdir

mkdir/mkdirat创建目录

	#include <sys/stat.h>
	int mkdir(const char *pathname, mode_t mode);
	int mkdirat(int fd, const char *pathname, mode_t mode);
	/*创建空目录,".和..目录项自动创建".mode由进程的文件模式创建屏蔽字修改*/
	/*retval:成功返回0,失败返回"-1"*/

目录通常至少需要设置一个执行权限,以访问该目录中的文件名.

rmdir删除一个空目录(只包含".和.."的目录),必须是空目录.

	#include <unistd.h>
	int rmdir(const char *pathname);
	/*retval:成功返回0,失败返回"-1"*/

### 4.20 函数chdir、fchdir和getcwd

chdir/fchdir更改当前工作目录

	#include <unistd.h>
	int chdir(const char *pathname);
	int fchidr(int fd);
	/*使用pathname/fd来指定新的工作目录. retval:成功返回0,失败返回"-1"*/

实例

	#include "apue.h"
	int main(void)
	{
		if(chdir("/tmp") < 0)	/*切到"/tmp"目录*/
			err_sys("chdir failed");
		printf("chdir to /tmp succeed\n");
		exit(0);
	}
	/*执行该应用时,可以打印出"chdir to /tmp succeed",但是pwd(属于shell进程)仍然是原来的目录.
	该应用程序与shell程序是两个独立的进程,互不影响*/

getcwd:获得当前工作目录的完整绝对路径名

	#include <unistd.h>
	char *getcwd(char *buf, size_t size);
	/*para1:(缓冲区)用于存放路径名; para2:buf(缓冲区)的长度*/
	/*retval:成功返回buf指针, 失败返回"NULL"*/

实例

	#include "apue.h"
	int mian(void)
	{
		char *ptr;
		size_t size;
		if(chdir("/usr/spool/uncppublic") < 0)	/*切到"/usr/spool/uncppublic"目录*/
			err_sys("chdir failed");
		ptr = path_alloc(&size);	/*给ptr分配size大小的buffer*/
		if(getcwd(ptr, size) == NULL)
			err_sys("getcwd failed");
		printf("cwd = %s\n", ptr);	/*会打印出获得的绝对路径*/
		exit(0);
	}

### 4.21 设备特殊文件

设备号所用的数据类型是基本系统数据类型"dev_t".主设备号表示设备驱动程序,次设备号表示特定的子设备.

文件系统的设备号是struct stat结构体中的"st_dev"成员;字符设备和块设备等实际设备的设备号为"st_rdev".

实例

	#include "apue.h"
	#ifdef SOLARIS
	#include <sys/mkdev.h>
	#endif

	int main(int argc, char *argv[])
	{
		int i;
		struct stat buf;
		for(i = 1; i < argvc; i++){
			printf("%s :", argv[i]);
			if(stat(argv[i], &buf) < 0){
				err_ret("stat error");
				continue;
			}
			printf("dev = %d/%d", major(buf.st_dev), minor(buf.st_dev));
			if(S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode)){
				printf(" (%s) rdev = %d/%d", 
				(S_ISCHR(buf.st_mode)) ? "character" : "block",
				major(buf.st_rdev), minor(buf.st_rdev));	/*判断是否为字符/块设备,并获取字符/块设备的设备号*/
			}
			printf("\n");
		}
		exit(0);
	}

	/dev/tty[01]---shell正则表达式,shell可将其扩展为"/dev/tty0"和"/dev/tty1"
***
## Chapter 5 标准I/O库

**STDIN_FILENO和stdin的区别**

	1)STDIN_FILENO:类型为int,打开文件的描述符(相当于fd---此处为标准输入(值为0)).属于系统调用,调用的函数包括:open/read/write/close等
	e.g.
	n = read(STDIN_FILENO, buf, BUFFERSIZE);	//从键盘输入
	2)stdin:类型为FILE *,标准I/O.属于标准库处理的输入流,由标准库函数调用,包括:fopen/fread/fwrite/fclose/getc等.
	标准库函数最终会调用系统调用(fread内部实现调用了read)
	e.g.
	c = getc(stdin));	//从标准输入流中输入一个字符---键盘

**库函数与系统调用的区别(fopen和open的区别)**

	1)库函数(fopen):属于带缓冲的打开方式(缓冲大小由机器决定),属于高级的IO,标准C函数(可移植),常用于打开普通文件.
	2)系统调用(open):不带缓冲,低级的IO,属于系统函数(属于用户空间).一般用于打开设备文件.

### 5.1 缓冲及标准I/O的使用

	#include <stdio.h>
	#include <stdlib.h>
	char inbuf[BUFSIZE];	//BUFSIZE常量定义在"stdio.h"中
	int main()
	{
		int a;
		char c;
		/*不带"fflush(stdin)":用于清空标准输入/出缓冲区
		scanf("%d", &a);
		c = getchar();	//获得一个字符
		printf("a = %d, c = %c \n", a, c);

		测试时,输入:123abc.得到的结果为:a = 123, c = a(将整数"123"赋给a,剩下的第一个字符"a"赋给c.)
		*/

		/*带"fflush(stdin)"
		scanf("%d", &a);	//输入的"123abc",会先将整数"123"赋给a
		fflush(stdin);		//清空标准输入,剩下的"abc"会被清空.此时缓冲区没内容---因此必须输入两次
		c = getchar();		//还会等待用户的输入,输入"xyz",将"x"赋给c
		printf("a = %d, c = %c \n", a, c);
		*/

		/*输入流(stdin)与缓冲区关联
		char a[100];
		setbuf(stdin, inbuf);	//标准输入流"stdin"与缓冲区"inbuf"关联
		printf("Input a string: ");
		scanf("%s", a);
		puts(inbuf);	//将缓冲区"inbuf"中的数据输出
		if(0 == fflush(inbuf))	//清空缓冲区"inbuf"
		{
			puts(inbuf);	//此时会输出空
		}
		puts(inbuf);	//还是输出空
		*/
		return 0;
	}

### 5.2 打开流

	#include <stdio.h>
	FILE *fopen(const char *pathname, const char *mode);
	/*para1:指定路径的文件名; para2:打开模式(常量字符串)
	retval:成功返回文件流的指针,出错返回NULL.*/
	/*
	mode: r(只读)、w(只写,且不存在会创建)、a()追加、r+(读写)、w+(读写,且不存在会创建---常用)
	*/
	
	//关闭
	int fclose(FILE *fp);

实例
	
	FILE *fp;
	fd = fopen("hello.txt", "w+");	//以读写方式创建并打开当前目录下的"hello.txt"文件
	//关闭
	fclose(fd);

### 5.3 读写流---不常用

读字符---一次读取一个字符

	#include <stdio.h>
	int getc(FILE *fp);
	int fgetc(FILE *fp);
	int getchar(void);	//用于定位程序执行到哪里---较为常用
	/*retval:成功返回下一个字符;到达文件尾或出错返回EOF(值为-1)*/

写字符---一次写一个字符(使用较少)

	#include <stdio.h>
	int putc(int c, FILE *fp);
	int fputc(int c, FILE *fp);
	int putchar(int c);

实例---用getc和putc将标准输入复制到标准输出:

	#include <stdio.h>
	int main(void)
	{
		int c;
		while((c = getc(stdin)) != EOF)	//从标准输入获得一个字符,并有c来实现定位
			if(putc(c, stdout) == EOF)	//输出获取的字符到标准输出
				err_sys("output error");

		if(ferror(stdin))	//判断标准输入出错
			err_sys("input error");

		exit(0);
	}

### 5.4 整行的I/O读写---常用

读:从fopen打开的流中读一行数据到buf缓冲区

	#include <stdio.h>
	char *fgets(char *buf, int n, FILE *fp);	//从fp这一个流中将一行(不超过n-1)数据读到buf指定的缓冲区中,缓冲大小为"n"
	/*n:指定buf的大小. retval:成功返回buf,到文件尾或出错返回NULL.*/

写:将buf中的数据写入fopen打开的流文件中.

	#include <stdio.h>
	int fputs(const char *buf, FILE *fp);	//将buf中的数据写入fp这一个文件流
	/*retval:成功返回非负值;出错返回"EOF"*/
	
	//fputs会将一个以null字节终止的字符串写到流中.字符串中"xxxx\0"的"\0"为字符串的终止符.

实例:

	#include <stdio.h>
	#define LENGTH 100
	int main()
	{
		FILE *fp;
		char str[LENGTH];
		
		fp = fopen("hello.txt", "w+");	//读写创建并打开文件
		if(fp)	//成功返回文件流的指针,为一个地址.失败返回NULL
		{
			fputs("hello world", fp);	//将字符串写入fp
			fclose(fp);		//关闭fp
		}

		fp = fopen("hello.txt", "r");	//只读方式打开文件
		fgets(str, LENGTH, fp);		//从fp中读一行到str这一个buffer中(str buffer的大小为LENGTH)
		printf("%s\n", str);
		fclose(fp);
	}

### 5.5 二进制I/O---一次读/写一个完整的结构

	#include <stdio.h>
	size_t fread(void *ptr, size_t size, size_t count, FILE *fp);
	size_t fwrite(const void *ptr, size_t size, size_t count, FILE *fp);
	/*
	para1:从fp读数据到ptr或者将ptr的数据写入到fp
	para2:ptr这一数据或结构的大小(使用sizeof求大小)
	para3:读/写的元素个数
	*/

	//写数组
	FILE *fp;
	int buffer[] = {1, 2, 3, 4};
	if((fp = fopen("myfile.txt", "w")) == NULL)
	{
		...
	}
	fwrite(buffer, sizeof(int), 4, fp);	//一次写入操作
	fclose(fp);
	//读数组
	FILE *fp;	
	int buffer[4] = {0};
	if((fp = fopen("myfile", "w")) == NULL)
	{
		...
	}
	fread(buffer, sizeof(int), 4, fp);	//一次读取
	fclose(fp);

读写结构体实例

	//写结构体数据到文件
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>

	typedef struct{
		int age;
		char name[30];
	}people;

	int main()
	{
		FILE *fp;
		int i;
		people per[3];
		per[0].age = 20;
		per[1].age = 18;
		per[2].age = 21;
		strcpy(per[0].name, "li");	//strcpy(dest, src):赋值src字符串到dest
		strcpy(per[1].name, "wang");
		strcpy(per[2].name, "zhang");

		if((fp = fopen("myfile.txt", "wb")) == NULL)
		{
			printf("open file fail\n");
			exit(0);
		}

		for(i = 0; i < 3; i++)	//一次写入fp
		{
			if(fwrite(&per[i], sizeof(people), 1, fp) != 1)	//成功返回写入的个数
				printf("write file fail");
		}
		fclose(fp);
		return 0;
	}

	//读结构体数据
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	typedef struct{
		int age;
		char name[30];
	}people;

	int main()
	{
		FILE *fp;
		people per;
		if((fp = fopen("myfile.txt", "rb")) == NULL)
		{
			printf("open file fail");
			exit(0);
		}

		while((fread(&per, sizeof(people), 1, fp)) == 1)	//读到数据就printf,否则退出
		{
			printf("%d %s\n", per.age, per.name);
		}

		fclose(fp);
		return 0;
	}
	
### 5.6 ftell、fseek、fprintf、fscanf的使用

	#include <stdio.h>
	//ftell:显示当前文件的位置
	long ftell(FILE *fp);	//retval:成功返回当前文件位置指示,失败返回"-1"
	//fseek:重新定位文件的指针
	int fseek(FILE *fp, long offset, int whence);	//retval:成功返回0,失败返回"-1"
					//whence:SEEK_SET(文件头)、SEEK_CUR(当前位置)、SEEK_END(文件尾)
	//fprintf:格式化输出到流
	int fprintf(FILE *fp, const char *format, ...);	//retval:成功返回输出的字符数,失败返回负值
		//输出时,都当作字符来处理(包括整数和字符),e.g.(整数123是3个字符---一个整数一个字符)
	//fscanf:将流中的数据格式化输出到变量
	int fscanf(FILE *fp, const char *format, ...);	//retval:成功返回输出到变量的项数,失败返回"-1"

实例

	#include <stdio.h>
	int main()
	{
		int a = 123;
		FILE *fp = fopen("myData.txt", "w");	//写方式打开,没有会创建
		printf("LINE: %d, position: %ld\n", __LINE__, ftell(fp));
		//情况1:向流中输入整型数	
		fprintf(fp, "%d", a);	//会将123输入到fp中,且会变成一个一个的字符
		//情况2:向流中输入字符串
		fprintf(fp, "123");		//会将123输入到fp中,且会变成一个一个的字符
		printf("LINE: %d, position: %ld\n", __LINE__, ftell(fp));	//上述两种情况的位置是一样的,都是"3"
		
		fprintf(fp, "%d", 456);	//会将456输入到fp中,且会变成一个一个的字符
		printf("LINE: %d, position: %ld\n", __LINE__, ftell(fp));	//结果为"6"
		fclose(fp);

		int b;
		fp = fopen("myData.txt", "r");
		printf("LINE: %d, position: %ld\n", __LINE__, ftell(fp));	//读指针从头开始,因此此处为"0"
		fscanf(fp, "%d", &b);	//将流fp中的数据输出到变量"b"
		printf("LINE: %d, position: %ld\n", __LINE__, ftell(fp));	//读指针由fscanf更改到末尾,因此此处为"6"
		printf("LINE: %d, a: %d\n", __LINE__, b);	//此时b的值为123456
		fclose(fp);

		int c[10] = {0};
		fp = fopen("yourData.txt", "wb");	//二进制写方式打开,没有会创建
		printf("LINE: %d, position: %ld\n", __LINE__, ftell(fp));	//位置为"0"
		fwrite(c, sizeof(c), 1, fp);	//将c数组中的数据写入到fp
		printf("LINE: %d, position: %ld\n", __LINE__, ftell(fp));	
				//写入的数据为整型数组数据,每个占4byte.因此总共40 byte.此处为"40"
		fclose(fp);

		int d[10];
		fp = fopen("yourData.txt", "rb");
		printf("LINE: %d, position: %ld\n", __LINE__, ftell(fp));	//读指针从头开始,因此此处为"0"
		fread(d, sizeof(d), 1, fp);		
		printf("LINE: %d, position: %ld\n", __LINE__, ftell(fp));	//读指针更新到末尾,因此此处
		fclose(fp);
		
		return 0;
	}
***
## Chapter 6 系统数据文件和信息

### 6.1 口令文件---/etc/passwd

	//口令文件内容如下(以":"分隔)
	root:x:0:0:root:/root:/bin/bash
	...
	defy.chen:x:1132:1132:defy.chen,S5100,8256:/zhsa022/usrhome/defy.chen:/bin/bash
	//各字段含义
	注册名:口令:用户标识符:组标识符:用户名:用户主目录:命令解释程序
	//分析
	1.注册名(login_name):"defy.chen"或"root",同一系统中注册名唯一
	2.口令(passwd):口令保存在"/etc/shadow"文件中(root用户才能读取),在/etc/passwd中用"x"代替
	3.用户标识符(UID):为一个数值,linux系统中唯一用户标识,与注册名一一对应.注册名用户使用方便,UID linux系统使用方便
	4.组标识符(GID):为一个数值,用户工作组标识,表示用户属于哪个组
	5.用户名(user_name):包含用户的有关信息,此处为"名字,部门,分机号"
	6.用户主目录(home_directory):用户的工作目录
	7.命令解释程序(shell):可执行程序

### 6.2 阴影口令---/etc/shadow

	//阴影口令文件内容如下(以":"分隔)
	情况一:
	root:!:16492:0:9999:7:::
	情况二:
	root:$6$c4tgZV1o$...:16492:0:99999:7:::
	//各字段含义
	账户名:密码:修改日期:密码不可改的天数:密码需要修改的期限:修改期限前N天发出警告:密码过期宽限:帐号失效日期:保留
	//分析
	1.账户名:root
	2.密码:"!"表示无密码.密码字符串格式"$id$salt$encrypted",此处"id=6使用sha-512";"salt"随机字符串,增加破解难度;
		"encrypted"加密后的数据
	3.修改日期:上一次修改密码距离1970-01-01的天数
	4.密码不可改的天数:为8表示距离上一次更改8天内不能再更新,为0随时可以更改
	5.密码休要修改的期限:若为12345表示距离1970-01-01的12345天内必须修改密码,为99999则永远不用改
	6.修改期限前N天发出警告:距离截至日期前N天会向用户发出警告
	7.密码过期宽限:若为M表示帐号过期M内可以修改密码
	8.帐号失效日期:若为X表示距离1970-01-01的X天之后帐号失效
	9.保留:暂时没用

### 6.3 组文件---/etc/group

略

### 6.4 其他数据文件

	/etc/services:记录网络服务器所提供服务的数据文件
	/etc/protocols:记录协议信息的数据文件
	/etc/networks:记录网路信息的数据文件
	/etc/hosts:主机

### 6.5 系统表示

	uname	//获得与主机和操作系统有关的信息
	uname -a		//打印所有信息,可通过"uname --help"得到帮助
	hostname	//获取主机名---得到结果"zhsa02"

### 6.6 时间和日期例程---即时间编程

**1)时间类型**

1.格林威治时间:也叫UTC或者GMT时间.其时间刚好属于东西半球的分界线,刚好选自英国伦敦的本地时间.

2.本地时间(local time):地球分为24个时区,每个时区都有自己的本地时间.北京时区为东八区,故领先UTC八个小时.

	//计算方法
	UTC + 时区差(东区为正) = local time(本地时间)		//如果为西区为负,相当于"-"
	Date: Thurs, 31 Dec 2009 04:32:22 +0800		//北京时间
	//UTC时间为:0432 - 0800 + 2400 = 2032---即前一天的晚上8点32分,即
	UTC(Data: Wed, 30 Dec 2009 20:32:22 +0000	//UTC时间

3.linux内核时间(日历时间):从标准时间1970年1月1日0点以来所经历的秒数.

获取时间步骤:

	1)先得到日历时间
	2)再将日历时间转换为本里时间或者格林威治时间.

**2)时间有关的结构体**

1.struct tm---时间的主要结构体(常用)
	struct tm{
		int tm_sec;		//秒数
		int tm_min;		//分钟值
		int tm_hour;	//小时值
		int tm_mday;	//本月第几日	
		int tm_mon;		//本年第几月
		int tm_year;	//tm_year+1900 = 哪一年???
		int tm_wday;	//本周第几日
		int tm_yday;	//本年第几日
		int tm_isdst;	//日光节约时间
	};

2.struct timeval---秒数计算(精度低)---常用
	struct timeval{
		time_t tv_sec;	//秒数
		long tv_usec;	//微秒
	};

3.struct timespec---秒数计算(精度高)
	struct timespec{
		time_t tv_sec;	//秒数
		long tv_nsec;	//纳秒
	};

**3)时间函数---获取时间**

1)获取日历时间---time(NULL);不填应该也可以?---暂时理解为必须填上.

	#include <stdio.h>
	#include <time.h>	//关于时间的头文件
	int main()
	{
		time_t seconds = 0;
		seconds = time((time_t *)NULL);		//获得从1970-01-01 0点到现在所经历的秒数.
		printf("seconds = %d\n", seconds);
		return 0;
	}

2)将日历时间转换为格林威治时间---不直观

	struct tm *gmtime(const time_t *timep);	//将日历时间转换为格林威治时间,保存在"struct tm"中

3)将日历时间转换为本地时间---不直观

	struct tm *localtime(const time_t *timep);	//将日历时间转换为本地时间,保存在"struct tm"中

实例

	#include <stdio.h>
	#include <time.h>
	int main()
	{
		struct tm *gm_local;
		time_t t;
		t = time(NULL);	//获取日历时间
		gm_local = localtime(&t);	//转换为本地时间,并保存在struct tm结构中
		printf("local hour is: %d\n", gm_local->tm_hour);	//打印本地时间的小时数
		gm_local = gmtime(&t);		//转换为格林威治时间,并保存在struct tm结构中
		printf("UTC hour is: %d\n", gm_local->tm_hour);		//打印格林威治时间的小时数
		return 0;
	}

**4)直观的显示时间**

1)将日历时间转换为本地时间的字符串形式

	char *ctime(const time_t *timep);
	//步骤:
	1)使用time()函数获取日历时间
	2)使用ctime()函数直接将日历时间转换为本地时间字符串形式

2)将格林威治时间转换为字符串形式

	char *asctime(const struct tm *tm);	//tm为格林威治时间
	//步骤:
	1)使用time()函数获取日历时间
	2)使用gmtime()函数将日历时间转换为格林威治时间
	3)使用asctime()函数将tm格式的格林威治时间转换为字符串

实例

	#include <stdio.h>
	#include <time.h>	//ISO C99标准时间头文件
	int main()
	{
		time_t t;
		struct tm *gmt;
		char *lt_string;	//local time string(本地时间字符串)
		char *gm_string;	//格林威治时间字符串形式

		t = time(NULL);		//获取日历时间
		lt_string = ctime(&t);	//获取得到本地时间字符串
		gmt = gmtime(&t);	//获取格林威治时间
		gm_string = asctime(gmt);	//将格林威治时间转换为字符串形式
		printf("local time: %s\n", lt_strimg);
		printf("gm time: %s\n", gm_string);
		return 0;
	}

**5)获取从今日凌晨到现在的时间差**

	int gettimeofday(struct timeval *tv, struct timezone *tz);	//获取从凌晨到现在的时间差,常用语计算事件耗时
	/*
	para1:存放时间差,以struct timeval结构存放; para2:常设置为NULL
	*/

实例---计算函数function()的耗时

	#include <sys/time.h>	//Linux系统日期头文件,内部包含"time.h"
	#include <stdio.h>
	#include <stdlib.h>
	#include <math.h>

	void function()
	{
		unsigned int i, j;
		unsigned long y = 0;
		for(i = 0; i < 1000; i++)
			for(j = 0; j < 1000; j++)
				y++;
	}

	int main()
	{
		struct timeval tpstart, tpend;
		double timeuse;
		gettimeofday(&tpstart, NULL);
		function();
		gettimeofday(&tpend, NULL);
		timeuse = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
		timeuse /= 1000000;
		printf("Used time: %f\n", timeuse);
		return 0;
	}

**6)延时函数**

1.使程序睡眠n秒

	unsigned int sleep(unsigned int n);

2.使程序睡眠n微秒

	void usleep(unsigned long n);
*** 
## Chapter 7 进程环境

**main启动**

当内核执行C程序时,在调用main前先调用一个特殊的启动例程.可执行程序将此启动例程指定为程序的起始地址,接着启动例程从内核取出命令行参数和环境变量,然后执行main函数.

### 7.1 main函数原型

	int main(int argc, char *argv[]);
	//argc:命令行参数个数; argv:指向命令行参数的各个指针所构成的数组.

### 7.2 进程终止

**5种正常终止**

1)main中return

2)调用exit(0)

3)调用_exit或_Exit

4)最后一个线程从启动例程返回

5)从最后一个线程调用pthread_exit

**3种异常终止**

6)调用abort

7)接到一个信号

8)最后一个线程对取消请求做出响应 

**在main中,return 0与exit(0)是等价的.**

### 7.3 命令行参数

**echo不会回显第0个参数,在main函数中:argv[argc]是一个空指针---即结尾为空指针**

### 7.4 C程序的存储空间布局

**C程序由以下几部分组成:**

1)正文段---也叫代码段(code segment/text segment):存放代码的地方.通常是可共享的,所以即使频繁执行的程序(e.g.文本编辑器、C编译器和Shell等)也只需一份副本,而且通常设置为只读.保存在磁盘上.

2)初始化数据段---通常称为数据段:包含程序中需要明确赋初值的变量(e.g. int maxcount = 99;).存放程序中已初始化的全局变量.保存在磁盘上.

3)未初始化数据段(bss段)---也称为常量区或全局区:该段数据不指定初值也可.在执行程序之前,内核会将该段中的数据初始化为"0"或"NULL".该段存放未初始化的全局变量,因为不需要指定初值,因此不会保存在磁盘上.

4)栈(stack):存放临时变量,函数地址或环境上下文信息等.

5)堆(heap):动态存储分配.位于未初始化数据段(bss)和栈(stack)之间.

**C程序存储空间的排布**

			高地址______________
				
				命令行参数和环境变量
				______________
					栈			
				..............
					栈往下增长		
			
					堆往上增长
				..............
					堆
				______________
			
				未初始化数据段	由exec初始化为0---不会保存在磁盘上
					(bss)
				______________
				初始化数据段			由exec从
				______________
				正文					程序中读入
		   低地址______________

**size命令可以报告一个程序的正文段、数据段(初始化数据段)和bss(未初始化数据段)的长度(字节为单位):**

	size out/vodrm_test
	text    data     bss     dec     hex filename
	265389   14712   14932  295033   48079 output/vodrm_test

### 7.5 存储空间分配

C程序有3个用于存储空间动态分配的函数:

	#include <stdlib.h>
	void *malloc(size_t size);	//分配指定字节数(size)的存储区,存储的初始值不确定.因此需要"memset();"
	void *calloc(size_t num, size_t size);	//分配num个长度为size的连续空间(即num*size个字节大小),并且每个字节都初始化为0.
	void *realloc(void *ptr, size_t newsize);	//增加或减少以前分配区的长度,新增的区域初始值不确定.---用的较少
	void free(void *ptr);	//释放malloc/calloc/realloc分配的内存
	ptr = NULL;	//一般free掉后需要将指针置空,防止野指针

	//calloc()实例
	#include <stdio.h>
	#include <stdlib.h>

	int main()
	{
		int i, n;
		int *pData;

		printf("Please input the numbers of you want: ");
		scanf("%d", &i);

		pData = (int *)calloc(i, sizeof(int));	//calloc()主要为数组指针分配空间
		if(!pData)
			exit(1);	//出错返回

		for(n = 0; n < i; n++)
		{
			printf("Please input the #%d number:", n + 1);	//printf后面的scanf会自动换行
			scanf("%d", &pData[n]);
		}

		printf("The numbers you have input are:");
		for(n = 0; n < i; n++)
			printf("%d", pData[n]);

		free(pData);
		pData = NULL;
	
		return 0;
	}

**泄漏(leakage)**

如果一个进程调用malloc函数,但却忘记调用free函数释放使用的空间.该进程占用的存储空间就会连续不断增加,称为内存泄漏(leakage).

### 7.6 函数setjmp和longjmp

在C中,goto语句是不能跨越函数的.而能够实现函数跳转功能的是"setjmp和longjmp"

	#include <setjmp.h>	//包含setjmp和longjmp函数的头文件
	int setjmp(jmp_buf envbuf);	//para:缓冲区envbuf保存系统堆栈的内容,以便后续longjmp函数使用.setjmp函数初次启用返回"0"
	void longjmp(jmp_buf envbuf, int val);
	//para1:参数envbuf是由setjmp函数所保存的堆栈环境;para2:参数val设置setjmp函数的返回值.
	//longjmp执行后跳转到保存envbuf参数的setjmp函数调用处,此时setjmp函数返回值就是"val"

实例

	#include <stdio.h>
	#include <setjmp.h>

	static jmp_buf buf;	//保存堆栈环境

	void second(void)
	{
		printf("second\n");
		longjmp(buf, 1);	//调回到setjmp的调用处,设置setjmp的返回值为"1"
	}

	void first(void)
	{
		second();
		printf("first\n");	//该行不会执行
	}

	int main()
	{
		if(!setjmp(buf))	//初次调用这个函数返回"0"
		{
			first();	//初次调用会进入该流程
		}else
		{
			printf("main\n");	//从longjmp跳回,setjmp返回"1".因此进入此行
		}
	}

	//上述程序输出:
	second
	main

### 7.7 资源限制

**略**
***
## Chapter 8 进程控制



***
## Chapter 9 进程关系


	