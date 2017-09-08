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

	pthread_exit(NULL);

**3种异常终止**

6)调用abort,会产生SIGABRT信号

7)接到一个信号

8)最后一个线程对取消(cancellation)请求做出响应 

**在main中,return 0与exit(0)是等价的.**

### 7.3 命令行参数

**echo不会回显第0个参数,在main函数中:argv[argc]是一个空指针---即结尾为空指针**

### 7.4 C程序的存储空间布局

**C程序由以下几部分组成:**

1)正文段---也叫代码段(code segment/text segment):存放代码的地方.通常是可共享的,所以即使频繁执行的程序(e.g.文本编辑器、C编译器和Shell等)也只需一份副本,而且通常设置为只读.保存在磁盘上.

2)初始化数据段---通常称为数据段:包含程序中需要明确赋初值的变量且非0(e.g. int maxcount = 99;).存放程序中已初始化的全局变量(初始化为非0).保存在磁盘上.

3)未初始化数据段(bss段)---也称为常量区或全局区:该段数据不指定初值也可(或者初始化为0).在执行程序之前,内核会将该段中的数据初始化为"0"或"NULL".该段存放未初始化的全局变量,因为不需要指定初值,因此不会保存在磁盘上.

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

### 8.1 进程标识(PID)

进程ID:每个进程都有唯一的一个非负整数标识,该标识称为进程ID.

进程ID复用:当一个进程终止后,其进程ID会被释放成为复用的候选者.Unix采用延迟复用算法---即刚被释放的进程ID不会马上分配给新创建的进程.

**进程各ID号的分配:**

0:属于调度进程,被称为交换进程(swapper).是内核的一部分,不执行任何磁盘上的程序,因此也被称为系统进程.

1:init进程.在"自举(???)"过程结束后由内核调用,负责启动一个Unix系统.该进程程序文件是"/sbin/init".init进程通常会读取与系统有关的初始化文件(/etc/rc*文件或/etc/initab文件,以及在/etc/init.d中的文件(现在主要是这里面的文件)),并将系统引导到一个初始状态(如多用户).init进程不会终止,且是所有孤儿进程的父进程.

**返回进程ID(PID)及其他ID的操作函数:**

	#include <unistd.h>
	pid_t getpid(void);		//retval:调用这个函数的进程的PID
	pid_t getppid(void);	//retval:调用进程的父进程的PID
	uid_t getuid(void);		//retval:调用进程的实际用户ID
	uid_t geteuid(void);	//retval:调用进程的有效用户ID
	gid_t getgid(void);		//retval:调用进程的实际组ID
	git_t getegid(void);	//retval:调用进程的有效组ID

### 8、2 函数fork

创建一个新进程---fork()函数

	#include <unistd.h>
	pid_t fork(void);	//retval:子进程返回0,父进程返回子进程ID;出错返回"-1"
	/*理由:
	1)父进程返回子进程ID:一个进程的子进程可以有多个,但是没有一个函数可以是一个进程获得其所有子进程的ID
	2)子进程中得到返回值0:一个进程只会有一个父进程,可以通过getppid()得到父进程ID---通过ID=0的调度进程可以获得.
	*/

实例:fork函数,在子进程中对变量的修改不会影响父进程中该变量的值.

	#include "apue.h"
	
	int globvar = 6;	//外部变量,在初始化数据段
	char buf[] = "a write to stdout\n";

	int main(void)
	{
		int var;	//自动变量,保存在栈中
		pid_t pid;
		
		var = 88;
		if(write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)	//写到标准输出
		/*sizeof(buf) - 1:避免将终止的null字节写出.
		sizeof():计算包括终止的null字节的缓冲区,因为sizeof中的缓冲区已用字符串进行初始化,其程度是固定的.
			所以sizeof是编译时计算缓冲区长度.
		strlen():计算不包括终止的null字节的字符串长度,但是需要进行一次函数调用.因此是在执行器计算的.
		*/
			err_sys("write error");

		printf("befor fork");	//we don't flush stdout.
		
		if((pid = fork()) < 0)
		{
			err_sys("fork error");
		}else if(pid == 0)	//子进程
		{
			globvar++;	//调整变量值
			var++;
		}else
		{
			sleep(2);	//父进程睡眠2s
		}

		printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
		exit(0);
	}

	//执行的结果
	./a.out		//终端设备是行缓冲
	a write to stdout
	before fork
	pid = 430, glob = 7, var = 89	//子进程的变量值改变了
	pid = 429, glob = 6, var = 88	//父进程的变量值没有改变

	./a.out > temp.out	//输出到文件是全缓冲,处于缓冲区的数据空间会复制到子进程.
						//在调用进程终止时,才会将缓冲区中的内容写到相应文件中
	a write to stdout
	before fork
	pid = 432, glob = 7, var = 89
	before fork
	pid = 431, glob = 6, var = 88

**fork的用法:**

1)一个父进程希望复制自己,使父进程和子进程同时执行不同的代码段.在网络服务器中常用---父进程等待客户端的服务请求,当请求到达时,父进程调用fork,使子进程处理该请求,父进程继续等待下一个服务请求.

2)一个进程要执行不同的程序(shell中常见).e.g.子进程从fork返回后立即调用exec.

### 8.4 函数vfork

**vfork函数不应该再使用.**

### 8.5 函数exit

退出状态(exit status):进程属于正常正常终止方式终止(e.g.return、exit、_exit和_Exit终止等)叫退出状态.

终止状态(termination status):属于异常终止情况终止,内核(不是进程本身)会产生一个指示其异常终止原因的终止状态.

**无论是退出状态还是终止状态,该终止进程的父进程都能用wait或waitpid取得终止状态.**

如果父进程在子进程之前终止,则所有子进程的父进程都改变为init进程(ID=1).该种方式叫做init进程收养.

如果子进程在父进程之前终止,父进程调用wait或waitpid可以获得子进程退出之前的一些信息(子进程ID、终止状态及使用的CPU时间总量等).

内核应该释放终止进程所使用的存储区,关闭所打开的文件.

**僵死进程(zombie):一个已经终止、但父进程尚未对其进行善后处理(获取终止子进程的相关信息(调用wait/waitpid)、释放它占用的资源)的进程称为僵死进程.**

init进程会自动调用wait函数取得子进程的终止状态,因此父进程属于init进程的子进程不存在僵死进程.

### 8.6 函数wait和waitpid

子进程正常或异常终止时,内核会向其父进程发送"SIGCHLD"信号.

**父进程调用wait或waitpid的进程可能发生的情况:**

1)如果其所有子进程都还在运行,则阻塞
	
2)如果任一个子进程已终止,正等待父进程获取其终止状态,则父进程取得其终止状态并立即返回

3)如果该父进程没有任何子进程,则立即出错返回

**wait或waitpid函数:获得进程终止状态**

	#include <sys/wait.h>
	pid_t wait(int *statloc);	//监控所有的子进程
	/*para:整型指针存放进程终止状态,如果不需要则可设为"NULL"; retval:成功返回终止子进程的进程ID,出错返回0或-1.*/
	pid_t waitpid(pid_t pid, int *statloc, int options);
	/*
	para1:监控的子进程的ID:
	pid=-1:任一子进程,此时同wait;
	pid>0:等待的进程ID与pid相等的子进程;
	pid=0:等待组ID等于调用进程组ID的任一子进程;
	pid<-1:等待组ID等于pid绝对值的任一子进程.
	para2:存放进程终止状态; para3:一般为0.
	retval:成功返回终止子进程的进程ID,出错返回0或-1.
	*/

实例:打印进程终止状态的说明

	#include "apue.h"
	#include <sys/wait.h>

	void pr_exit(int status)	//para:wait获得的进程终止状态
	{
		if(WIFEXITED(status))	//解析正常终止状态的宏
			printf("Normal termination, exit status = %d\n", WEXITSTATUS(status));
		else if(WIFSIGNALED(status))	//解析异常退出状态的宏
			printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
		#ifdef WCOREDUMP
				WCOREDUMP(status) ? "(core file generated)": "");
		#else
				"");
		#endif
		else if(WIFSTOPPED(status))	//暂停子进程的状态的宏
			printf("child stopped, signal number = %d\n", WSTOPSIG(status));
	}

实例:调用pre_exit,打印终止状态的各种值

	#include "apue.h"
	#include <sys/wait.h>
	
	int main(void)
	{
		pid_t pid;
		int status;
		
		if((pid = fork()) < 0)
			err_sys("fork error");
		else if(pid == 0)	//子进程
			exit(7);	//子进程终止,正常终止

		if(wait(&status) != pid)	//等待子进程终止.父进程中返回子进程的PID,wait返回等待子进程的PID.因此两者会相等
			err_sys("wait error");
		pr_exit(status);	//打印状态值

		if((pid = fork()) < 0)
			err_sys("fork error");
		else if(pid == 0)
			abort();	//子进程异常终止

		if(wait(&status) != pid)
			err_sys("wait error");
		pr_exit(status);

		if((pid = fork()) < 0)
			err_sys("fork error");
		else if(pid == 0)
			status /= 0;	//除0会产生"SIGFPE"信号,一般不会这样做

		if((wait(&status)) != pid)
			err_sys("wait error");
		pr_exit(status);

		return 0;
	}
	
**waitpid可以解决僵死进程,但是感觉用的比较少.**

其他的wait函数包括:waitid,wait3, wait4.

### 8.7 竞争条件

当很多进程都企图对某共享数据进行处理,但是最后的结果取决于进程运行的顺序时,这种叫做发生了竞争条件(race condition).---e.g.在fork创建进程后,父进程先运行还是子进程先运行不确定.

竞争条件实例:

	#include "apue.h"
	static void charatatime(char *);

	int main(void)
	{
		pid_t pid;
		
		if((pid = fork()) < 0)
		{
			err_sys("fork error");
		} else if(pid == 0)
		{
			charatatime("output from child\n");
		} else
		{
			charatatime("output from parent\n");
		}
		return 0;	//或者exit(0);
	}

	static void charatatime(char *str)
	{
		char *ptr;
		int c;
		
		setbuf(stdout, NULL);	//set unbuffered---设置标准输出为不带缓冲的,每输出一个字符调用一次write
		for(ptr = str; (c = *ptr++) != 0; )
			putc(c, stdout);	//一个字符一个字符输出
	}

	//在运行时可能出现:
	case 1:
	ooutput from child
	utput from parent
	case 2:
	output from child
	output from parent

更改为父进程先执行,子进程后执行:

	#include "apue.h"
	static void charatatime(char *);

	int main(void)
	{
		pid_t pid;
		
	+	TELL_WAIT();
	
		if((pid = fork()) < 0)
		{
			err_sys("fork error");
		} else if(pid == 0)
		{
	+	    WAIT_PARENT();		//等待父进程,父进程先执行
			charatatime("output from child\n");
		} else
		{
			charatatime("output from parent\n");
	+       TELL_CHILD(pid);	//通知子进程
		}
		return 0;	//或者exit(0);
	}

	static void charatatime(char *str)
	{
		char *ptr;
		int c;
		
		setbuf(stdout, NULL);	//set unbuffered---设置标准输出为不带缓冲的,每输出一个字符调用一次write
		for(ptr = str; (c = *ptr++) != 0; )
			putc(c, stdout);	//一个字符一个字符输出
	}

### 8.8 exec函数

在fork后的子进程中使用exec函数族,可以载入和运行其他程序(子进程替换原有进程(子进程PID不变),和父进程做不同的事).

**exec函数族**
	
	#include <unistd.h>
	extern char **environ;
	int execl(const char *pathname, const char *arg, ...);
		//"l":希望接收以","分隔的参数列表,列表以NULL指针作为结束标志
	int execlp(const char *filename, const char *arg, ...);
		//"p":接收以NULL结尾的字符串数组的指针,且para1为filename
	int execle(const char *pathname, const char *arg, ..., char *const envp[]);
		//"e":函数传递指定参数envp,允许改变子进程环境.无后缀e,子进程使用当前环境
	int execv(const char *pathname, char *const argv[]);
		//"v":希望接收一个以NULL结尾的字符串数组的指针
	int execvp(const char *filename, char *cosnt argv[]);
		//"p":接收以NULL结尾的字符串数组的指针,且para1为filename
	int execve(const char *pathname, char *const argv[], char *const envp[])
		//"e":函数传递指定参数envp,允许改变子进程环境.无后缀e,子进程使用当前环境

	//所有exec函数成功不返回,失败返回"-1"

**实例**

	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <string.h>
	#include <errno.h>

	int main(int argc, char *argv[])
	{
		//以NULL结尾的字符串数组的指针,适合包含"v"的exec函数参数
		char *arg[] = {"ls", "-a", NULL};

		/*创建子进程并调用函数execl.
		* execl中希望接收以逗号","分隔的参数列表,并以NULL指针为结束标志
		*/
		if(fork() == 0)
		{
			// child process
			printf("1-------------execl-------------\n");
			if(execl("/bin/ls", "ls", "-a", NULL) == -1)		//载入/bin/ls文件,然后执行ls程序
			{
				perror("execl error");
				exit(1);
			}
		}

		/*创建子进程并调用execv
		* execv中希望接收一个以NULL结尾的字符串数组的指针
		*/
		if(fork() == 0)
		{
			// child process
			printf("2-------------execv-------------\n");
			if(execv("/bin/ls", arg) == -1)		//载入/bin/ls文件,然后执行ls程序
			{
				perror("execv error");
				exit(1);
			}
		}

		/*创建子进程并调用execlp
		* execlp中
		* l希望接收以逗号","分隔的参数列表,并以NULL指针为结束标志
		* p是一个以NULL结尾的字符串数组指针.重要是"p"会以path为环境变量查找子程序文件
		*/
		if(fork() == 0)
		{
			printf("3-------------execlp-------------\n");
			if(execlp("ls", "ls", "-a", NULL) == -1)		//载入path下的ls文件,然后执行ls程序
			{
				perror("execlp error");
				exit(1);
			}
		}

		/*创建子进程并调用execvp
		* v希望接收一个以NULL结尾的字符串数组的指针
		* "p"会以path为环境变量查找子程序文件
		*/
		if(fork() == 0)
		{
			printf("4-------------execvp-------------\n");
			if(execvp("ls", arg) == -1)
			{
				perror("execvp error");
				exit(1);
			}
		}

		/*创建子进程并调用execle
		* l希望接收以逗号","分隔的参数列表,并以NULL指针为结束标志
		* e函数传递指定参数envp,允许改变子进程的环境,无后缀时,子进程使用当前程序的环境
		*/
		if(fork() == 0)
		{
			printf("5-------------execle-------------\n");
			if(execle("/bin/ls", "ls， "-a", NULL, NULL) == -1)
			{
				perror("execle error");
				exit(1);
			}
		}

		/*创建子进程并调用execve
		* v希望接收一个以NULL结尾的字符串数组的指针
		* e函数传递指定参数envp,允许改变子进程的环境,无后缀时,子进程使用当前程序的环境
		*/
		if(fork() == 0)
		{
			printf("6-------------execve-------------\n");
			if(execve("/bin/ls", arg, NULL) == -1)	//这个返回需要确定？？
			{
				perror("execve error");
				exit(1);
			}
		}
		return 0;
	}

### 8.9 用户ID和组ID

id命令可以显示真实有效的用户ID(UID)和组ID(GID).UID是对一个用户的单一身份标识,GID则对应多个UID.

id命令的使用方法:

	$ id	//直接在终端输入"id"命令即可
	$ id -a/-G/-g	//也可以"man id"查找帮助

### 8.10 解释器文件

解释器文件(interpreter file):是文本文件,其起始行形式为

	#!pathname [optional-argument]	//#!和pathname之间无空格,且pathname为绝对路径名
	//例子
	#!/bin/sh	//#!和/bin/sh之间无空格

实例:调用exec执行一个解释器文件

	#include <stdio.h>
	#include <sys/wait.h>
	#include <unistd.h>

	int main(void)
	{
		pid_t pid;
		if((pid = fork) < 0)
		{
			perror("fork");
			return -1;
		}else if(pid == 0)
		{
			if(execl("/home/sar/bin/testinterp",
				"testinterp", "myarg1", "MY ARG2", (char *)0) < 0)
				err_sys("execl error");
		}

		if(waitpid(pid, NULL, 0) < 0)	//para2:保存结束状态;retval:成功返回pid,失败返回"-1"
	
		return 0;
	}

	cat /home/sar/bin/testinterp中的内容为:
	#!/home/sar/bin/echoarg foo

	//执行后的结果为:
	/home/sar/bin/echoarg foo /home/sar/bin/testinterp myarg1 MY ARG2

### 8.11 函数system

system()函数调用/bin/sh(通常为一个软连接,指向某个具体的shell---e.g.bash)来执行参数指定的命令.

	#include <stdlib.h>
	int system(const char *command);	
	//para:命令.retval:成功返回command通过exit/return返回的值,失败返回"127"

system()函数执行下面三步操作:

1)fork一个子进程

2)在子进程中调用exec函数去执行command

3)在父进程调用wait等待子进程结束

**system函数实现:**

	int system(const char *cmdstring)
	{
		pid_t pid;
		int status;

		if(cmdstring == NULL)
		{
			return (1);	//如果cmdstring为空,返回非0值,一般为1
		}

		if((pid = fork()) < 0)
		{
			status = -1;		//fork失败,返回-1
		}else if(pid == 0)
		{
			execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);	
			//shell的-c选项告诉shell取下一个命令行参数"cmdstring",而且"cmdstring"会解析成各个命令
			_exit(127);	//exec执行失败才会返回127,exec失败才返回现在的进程,成功现在的进程就不存在了			
		}else
		{
			while(waitpid(pid, &status, 0) < 0)
			{
				if(errno != EINTR)	//信号中断
				{
					status = -1;		//信号中断返回-1
					break;
				}
			}
		}
		return status;	//waitpid成功,返回子进程的返回状态
	}

	//system函数的测试
	#include "apue.h"
	#include <sys/wait.h>

	int main(void)
	{
		int status;
		if((status = system("date")) < 0)	//date命令正常运行
			err_sys("system() error");

		pr_exit(status);

		if((status = system("nosuchcommand")) < 0)	//无此命令,会返回127
			err_sys("system() error");

		pr_exit(status);

		if((status = system("who; exit 44")) < 0)	//多个命令正常运行
			err_sys("system() error");

		pr_exit(status);

		return 0;
	}

### 8.12 进程会计

**略**

### 8.13 进程时间

Unix系统维护三个进程时间:

1)时钟时间(墙上时钟时间)

2)用户CPU时间

3)系统CPU时间	---2)和3)合称为CPU时间

使用times()函数可以获得父、子进程的上述3个时间

	#include <sys/times.h>
	clock_t times(struct tms *buf);
	/*retval:成功返回时钟时间,失败返回"-1".其他两个时间保存在参数"buf"中*/

struct tms

	struct tms{
		clock_t tms_utime;	//用户CPU时间
		clock_t tms_stime;	//系统CPU时间
		clock_t tms_cutime;	//子进程用户CPU时间
		clock_t tms_cstime;	//子进程系统CPU时间
	};

**所有的clock_t类型的值,都可以用"sysconf(_SC_CLK_TCK)"转换成秒数---sysconf()函数返回每秒时钟滴答数.**

	#include "apue.h"
	#include <sys/times.h>
	#include "pr_exit.h"

	static void pr_times(clock_t, struct tms *, struct tms *);
	static void do_cmd(char *);

	int main(int argc, char *argv[])
	{
		int i;
		setbuf(stdout, NULL);	//set unbuffered---设置标准输出为不带缓冲的
		for(i = 1; i < argc; i++)
			do_cmd(argv[i]);	//每个命令行参数执行一次

		return 0;
	}

	static void do_cmd(char *cmd)
	{
		struct tms tmsstart, tmssend;
		clock_t start, end;
		int status;

		printf("\ncommand: %s\n", cmd);
		
		if((start = times(&tmsstart)) == -1)		//时钟时间---起始时间
			err_sys("time error");

		if((statuc = system(cmd)) < 0)	//执行command
			err_sys("system() error");

		if((end = system(&tmsend)) == -1)	//时钟时间---结束时间
			err_sys("time error");

		pr_times(end-start, &tmsstart, &tmsend);
		pr_exit(status);
	}

	static void pr_times(clock_t real, struct tms *tmsstart, tms * tmsend)
	{
		static long clktck = 0;
		
		if(clktck == 0)
			if((clktck = sysconf(_SC_CLK_TCK)) < 0)	//所有时间转成秒数
				perror("sysconf");

		printf("real: %7.2f\n", real / (double)clktck);
		printf("user: %7.2f\n", (tmsend->tms_utime - tmsstart->tms_utime) / (double)clktck);
		printf("sys: %7.2f\n", (tmsend->tms_stime - tmsstart->tms_stime) / (double)clktck);
		printf("child user: %7.2f\n", (tmsend->tms_cutime - tmsstart->tms_cutime) / (double)clktck);
		printf("child sys: %7.2f\n", (tmsend->tms_sutime - tmsstart->tms_sutime) / (double)clktck);
	}

	//执行
	./a.out "sleep 5" "date" "man bash > /dev/null"
	//结果
	command: sleep 5
		real: 5.01
		user: 0.00
		sys: 0.00
		child user: 0.00
		child sys: 0.00
	normal termination, exit status = 0
	
	command: date
	Sun Feb 26 18:39:23 EST 2012
		real: 0.00
		user: 0.00
		sys: 0.00
		child user: 0.00
		child sys: 0.00
	normal termination, exit status = 0

	command: man bash > /dev/null
		real: 1.46
		user: 0.00
		sys: 0.00
		child user: 1.32
		child sys: 0.07
	normal termination, exit status = 0
***
## Chapter 9 进程关系

### 9.1 linux终端及终端登录过程

**linux终端**

shell是系统用户界面,提供了内核与用户交互的接口.它接收用户输入的命令并把它送入内核执行,再将结果显示给用户.

物理终端:显示器和键盘等.因为能对系统进行控制,因此也叫物理控制台.

虚拟终端:用软件方法实现多个互不干扰、独立工作的控制台界面,就实现了多个虚拟终端,也叫虚拟控制台.

linux默认启动6个字符界面虚拟终端(tty1~tty6),如果有图形界面则X window在第7个虚拟终端上(tty7).

处于图形界面下,可以通过"Ctrl+Alt+F(1-6)选择不同的终端,选择完后可以看到"login:"提示符",然后输入用户名和密码即可登录.如果按下"Ctrl+Alt+F7"可以回到图形界面.且各个终端互不干扰.

**linux终端登录过程**

1)系统启动后时,内核创建init进程,init进程使系统进入多用户状态.init进程会根据配置文件"/etc/inittab"确定需要打开哪些终端,对每一个允许登录的终端设备,init调用一次fork,所生成的子进程则执行exec(getty)程序.

2)getty为终端设备调用open函数,以读写方式将终端打开.然后getty输出"login:"等信息等待用户输入用户名.

3)用户输入用户名,getty工作完成,然后调用login程序,会让用户输入密码:

	execle("/bin/login", "login", "-p", username, (char *)0, envp);

4)密码验证无误后,login将切换目录到用户的home目录,改变该终端设备的权限以及用户的登录shell:

	execl("/bin/sh", "-sh", (char *)0);

5)登录shell并读取其启动文件(bsh或ksh)

### 9.2 linux网络登录

**略**

### 9.3 进程组

进程组:一个或多个进程的集合.

进程组ID---正整数.

相关函数:

	#include <unistd.h>
	pid_t getgrp(void);	//retval:调用进程的进程组ID
	pid_t getpgid(pid_t pid);	//retval:成功返回pid进程的进程组ID;出错返回-1.
	getpgid(0) = getgrp();	//pid=0表示子进程

实例---子进程和父进程的进程组ID

	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	int main()
	{
		pid_t pid;
		
		if((pid = fork()) < 0)
		{
			printf("fork error");
		}else if(pid == 0)
		{
			printf("The child process PID is %d.\n", getpid());		//2262
			printf("The Group ID is %d.\n", getgrp());				//2261,进程组ID=父进程ID
			printf("The Group ID is %d.\n", getpgid(0));			//2261,进程组ID=父进程ID
			printf("The Group ID is %d.\n", getpgid(getpid()));		//2261,进程组ID=父进程ID
			exit(0);
		}

		sleep(3);
		printf("The parent process PID is %d.\n", getpid());		//2261
		printf("The Group ID is %d.\n", getgrp());					//2261,父进程为组长进程
	}

一个进程可以为自己或子进程设置进程组ID.

	#include <unistd.h>
	int setpgid(pid_t pid, pid_t pgid);	//将一个进程pid加入一个进程组或创建一个进程组gpid
	//retval:成功返回0,出错返回-1.

实例---父进程改变自身和子进程的组ID

	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>

	int main()
	{
		pit_t pid;
		if((pid = fork()) < 0)
		{
			printf("fork error\n");
		}else if(pid == 0)
		{
			printf("The child process PID is %d.\n", getpid());		//2438
			printf("The Group ID of child is %d.\n", getpgid(0));	//子进程组ID---2437,此时等于父进程ID
			sleep(5);	
			printf("The Group ID of child is changed to %d.\n", getpgid(0));	//子进程组ID改变为子进程本身ID---2438
			exit(0);
		}

		sleep(1);
		setpgid(pid, pid);	//将子进程ID加入到子进程组ID本身,即为设置子进程组ID为子进程本身

		sleep(5);
		printf("The parent process PID is %d.\n", getpid());		//2437
		printf("The parent of parent process PID is %d.\n", getppid());		//2209
		printf("The Group ID of parent is %d.\n", getpgid(0));		//2437
		setpgid(getpid(), getppid());	//改变父进程的组ID为父进程的父进程ID
		printf("The Group ID of parent is changed to %d.\n", getpgid(0));		//2209

		return 0;
	}

### 9.4 会话

会话:一个或多个进程的集合.开始于用户登录,终止于用户退出,此期间所有进程都属于这个会话期.

建立新会话---setsid()函数

	#include <unistd.h>
	pid_t setsid(void);	//retval:成功返回进程组ID，出错返回-1

1)如果调用进程是组长进程,则出错返回

2)如果调用进程不是组长进程,则创建一个新会话.其发生的事情为:

1.先调用fork,父进程终止,子进程调用

2.子进程变成新会话首进程(Session header)

3.子进程成为一个新进场组的组长进程

4.子进程没有控制终端,如果之前有,则会被中断

**组长进程不能成为新会话的首进程,新会话的首进程必定成为组长进程**

会话ID:会话首进程的进程组ID

获取会话ID:getsid()函数

	#include <unistd.h>
	pid_t getsid(pid_t pid);	//retval:成功返回会话首进程的进程组ID,出错返回-1

实例

	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>

	int main()
	{
		pid_t pid;

		if((pid = fork()) < 0){
			printf("fork error");
			exit(1);
		}else if(pid == 0){
			printf("The child process PID is %d.\n", getpid());		//2896
			printf("The Group ID of child is %d.\n", getpgid(0));	//2895
			printf("The Session ID of child is %d.\n", getsid(0));	//2209
			sleep(10);
			setsid();	//子进程非组长进程,子进程成为新会话首进程,且成为组长进程,且该进程组ID等于会话ID
			printf("Changed:\n");
			printf("The child process PID is %d.\n", getpid());		//2896
			printf("The Group ID of child is %d.\n", getpgid(0));	//2896
			printf("The Session ID of child is %d.\n", getsid(0));	//2896
		}

		return 0;
	}

### 9.5 控制终端

会话的领头进程打开一个终端之后,该终端就成为该会话的控制终端

与控制终端建立连接的会话领头进程(session header)称为控制进程

一个会话只能有一个控制终端

**进程属于一个进程组,进程组属于一个会话,会话可能有/没有控制终端.**

### 9.6 作业

Shell分前后台来控制的不是进程而是作业(job)或者进程组(process group).一个前台/后台作业("&")都可以有多个进程组成,Shell可以运行一个前台作业和任意多个后台作业,称为作业控制.

作业与进程组的区别:如果作业中的某个进程又创建了子进程,则子进程不属于作业.一旦作业运行结束,Shell就把自己提到前台.如果原来的前台进程还存在(如果这个子进程还没终止),它自动变为后台进程组.
***
## Chapter 10 信号
***
## Chpater 11 线程

### 11.1 线程的概念

单线程:典型的Unix进程可以看成只有一个控制线程:一个进程在某一时刻只能做一件事情.

多线程:进程拥有多个控制线程,某一时刻可以做多件事情,每个线程处理各自独立的任务.

### 11.2 线程标识

进程ID在整个系统中是唯一的;线程ID不同,线程ID只有在它所属的进程上下文中才有意义.

线程ID使用"pthread_t"数据类型表示,linux中的"pthread_t"就是"unsigned long",其他的系统不一定是.

**线程ID的比较:**

	#include <pthread.h>
	int pthread_equal(pthread_t tid1, pthread_t tid2);	//比较线程tid1和tid2是否相等
	//retval:两个线程ID相等返回非0值;否则返回0.

**获取自身线程ID:**

	#include <pthread.h>
	pthread_t pthread_self(void);	//retval:返回调用线程的线程ID

### 11.3 线程创建

**线程创建函数:**

	#include <pthread.h>
	int ptread_create(pthread_t *tidp, pthread_attr_t *attr, void *(*start_rtn)(void *), void *arg);
	/*
	para1:存放线程ID;	para2:线程属性;		para3:线程函数;
	para4:线程函数的参数,如果需要的参数有多个,将多个参数放入一个结构体,然后传入一个结构体地址
	retval:成功返回0,否则返回错误编号.
	*/

线程创建实例:

	#include <pthread.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>

	pthread_t ntid;		//new pthread id

	void printids(const char *)
	{
		pid_t pid;
		pthread_t tid;

		pid = getpid();			//获取pid
		tid = pthread_self();	//获取线程ID
		printf("%s pid: %lu, tid: %lu, (0x%lx)\n", s, (unsigned long)pid,
			(unsigned long)tid, (unsigned long)tid);
		//pid和tid均取unsigned long---为32bit.		"0x%lx":打印出长整型的16进制
	}

	void *thr_fn(void *arg)
	{
		printids("new thread:");
		return ((void *)0);		//void *的返回可以"return ((void *)0);"
	}

	int main(void)
	{
		int err;
		err = pthread_create(&ntid, NULL, thr_fn, NULL);	//成功返回0,失败返回非0(错误编号)
			//主线程和新创建的线程的执行先后不定
		if(err != 0)
		{
			err_exit(err, "can't create thread");
		}

		printids("main thread:");
		sleep(1);	//主线程休眠.防止主线程退出后,新线程没机会运行,进程就终止了.
		return 0;
	}

### 11.4 线程终止

**1)线程终止的三种方式**

1)线程的return,return值就是线程的退出码

2)线程调用了pthread_exit()函数

	#include <pthread.h>
	void pthread_exit(void *rval_ptr);	//para:线程的终止状态
	//其他线程通过pthread_join函数可以访问到pthread_exit中的参数指针
	int pthread_join(pthread_t thread, void **rval_ptr);	//retval:成功返回0,失败返回错误编号
	//pthread_join会让指定的线程处于阻塞状态,形成一个取消点,以便退出线程
	//pthread_join会把指定的线程置于分离状态,以便资源可以恢复.但是如果线程已经是分离状态,则pthread_join调用会失败,返回EINVAL.

	//线程分离:创建的线程的资源被回收,pthread_join获取不到线程终止状态,此时会出错
	//线程分离函数
	#include <pthread.h>
	int pthread_detach(pthread_t tid);

3)线程可以被同一进程中的其他线程取消

**2)线程取消**

1)定义:线程接收另一个线程发来的终止(取消)请求而强制终止

2)方法:向目标线程发送cancel信号.但是处理cancel信号由目标线程自己决定---忽略(当禁止取消时)、立即终止(在取消点或异步模式下)、运行至cancelation-point(取消点),由不同的cancelation状态决定.

线程接收到cancel信号的缺省处理是继续运行至取消点再处理(退出),或在异步方式下直接退出.

**3)取消点**

pthread_join()、pthread_testcancel()、pthread_cond_wait()、pthread_cond_timewait()、sem_wait()、sigwait()以及read()、write()等会引起阻塞的系统调用都是取消点(cancelation-point),而其他pthread函数不会引起cancelation动作.

**4)与线程相关的pthread函数**
	
	1)int pthread_cancel(pthread_t thread);	//发送终止信号给pthread线程
	//para:线程的ID; retval:成功返回0,失败返回非0.发送成功并不意味着thread会终止

	2)int pthread_setcancelstate(int state, int *oldstate);	//设置本线程对cancel信号的反应---相当于本线程的属性
	//para1---两种值:1)PTHREAD_CANCEL_ENABLE(缺省)---表示接收cancel信号并设为cancel状态;
					2)PTHREAD_CANCEL_DISABLE---忽略cancel信号继续运行
	//para2---不为NULL则存入原来的cancel状态以便恢复.一般为"NULL"

	3)int pthread_setcanceltype(int type, int *oldtype);	//设置本线程取消动作的执行时机---相当于本线程的属性
	//para1---两种值:1)PTHREAD_CANCEL_DEFFERED---表示收到信号后继续运行到下一个取消点再退出
					2)PTHREAD_CANCEL_ASYCHRONOUS---表示收到信号后立即执行取消动作(退出)
	//para1只有当cancel状态为enable时有效.para2:一般为NULL

	4)void pthread_testcancel(void)		//检查本线程是否处于cancel状态.如果是则进行取消动作,否则直接退出.

实例---获取线程的终止状态

	#include "apue.h"
	#include <pthread.h>

	void *thr_fn1(void *arg)
	{
		printf("thread 1 returning\n");
		return ((void *)1);		//线程返回
	}

	void *thr_fn2(void *arg)
	{
		printf("thread 2 exiting\n");
		pthread_exit((void *)2);
	}

	int main(void)
	{
		int err;
		pthread_t tid1, tid2;
		void *tret;

		err = pthread_create(&tid1, NULL, thr_fn1, NULL);
		if(err != 0)
			 err_exit(err, "can't create thread 1\n");

		err = pthread_create(&tid2, NULL, thr_fn2, NULL);
		if(err != 0)
			err_exit(err, "can't create thread 2\n");
		
		err = pthread_join(tid1, &tret);
		if(err != 0)
			err_exit(err, "can't join with thread 1\n");
		printf("thread 1 exit code %ld\n", (long)tret);

		err = pthread_join(tid2, &tret);
		if(err != 0)
			err_exit(err, "can't join with thread 2\n");
		printf("thread 2 exit code %ld\n", (long)tret);
		exit(0);
	}

	//运行的结果:
	thread 1 returning
	thread 2 exiting
	thread 1 exit code 1
	thread 2 exit code 2

**在pthread_create/pthread_exit如果传递结构体参数时:**

1)不要使用栈上的结构体变量(因为栈变量在调用结束后其内存会被自动释放,另作他用);

2)应该使用全局结构或者堆上的内存(即malloc函数分配的结构)

实例---栈变量作为pthread_exit参数出现问题

	#include <apue.h>
	#include <pthread.h>

	struct foo{
		int a, b, c, d;		//可以这样写结构体成员
	};

	void printfoo(const char *s, const struct foo *fp)
	{
		printf("%s", s);
		printf(" structure at 0x%lx\n", (unsigned long)fp);
		printf(" foo.a = %d\n", fp->a);
		printf(" foo.b = %d\n", fp->b);
		printf(" foo.c = %d\n", fp->c);
		printf(" foo.d = %d\n", fp->d);
	}

	void *thr_fn1(void *arg)
	{
		struct foo foo = {1, 2, 3, 4};	//给结构体成员赋值
		
		printfoo("thread 1: \n", &foo);
		pthread_exit((void *)&foo);		//返回void *指针
	}

	void *thr_fn2(void *arg)
	{
		printf("thread 2: ID is %lu\n", (unsigned long)pthread_self());
		pthread_exit((void *)0);
	}

	int main(void)
	{
		int err;
		pthread_t tid1, tid2;
		struct foo *fp;
		
		err = pthread_create(&tid1, NULL, thr_fn1, NULL);
		if(err != 0)
			err_exit(err, "can't create thread\n");
		err = pthread_join(tid1, (void *)&fp);	//栈结构体变量fp得到状态
		if(err != 0)
			err_exit(err, "can't join with thread 1");
		sleep(1);
		printf("parent starting second thread\n");
		err = pthread_create(&tid2, NULL, thr_fn2, NULL);
		if(err != 0)
			err_exit(err, "can't create thread\n");
		sleep(1);
		printfoo("parent: \n", fp);		
		//栈结构体变量fp值可能已经被改变,因此最好不要使用栈变量.定义fp为全局变量或malloc出来(堆变量)
		return 0;
	}

**线程清理处理程序(thread cleanup handler):线程安排它退出时需要调用的函数.**

	#include <pthread.h>
	void pthread_cleanup_push(void (*rtn)(void *), void *arg);	//清理入栈函数
	//para1:清理函数,该函数可以写成"void fun(void *arg);",然后将其函数名传递给清理入栈函数
	//e.g. pthread_cleanup_push(fun, "字符串");
	void pthread_cleanup_pop(int execute);	//清理出栈函数
	//该函数决定清理函数被调用与否.该函数与push必须匹配使用
	
	/*下面三种情况满足任意一种情况清理函数都将被调用:*/
	1)调用pthread_exit()时;
	2)响应取消请求;	//有cancel消息发出并相应
	3)用非"0"execute参数调用pthread_cleanup_pop时

实例---线程清理处理程序

	#include <apue.h>
	#include <pthread.h>

	void cleanup(void *arg)
	{
		printf("cleanup: %s\n", (char *)arg);
	}

	void *thr_fn1(void *arg)
	{
		printf("thread 1 start\n");
		pthread_cleanup_push(cleanup, "thread 1 first handler");
		pthread_cleanup_push(cleanup, "thread 1 second handler");
		printf("thread 1 push complete\n");
		if(arg)
			return((void *)1);
		pthread_cleanup_pop(0);	//参数为0,在此处清理处理函数"cleanup"不会被调用
		pthread_cleanup_pop(0);	//参数为0,在此处清理处理函数"cleanup"不会被调用
		return((void *)1);		//return返回,清理处理函数"cleanup"不会被调用
	}

	void *thr_fn2(void *arg)
	{
		printf("thread 2 start\n");
		pthread_cleanup_push(cleanup, "thread 2 first handler");
		pthread_cleanup_push(cleanup, "thread 2 second handler");
		printf("thread 2 push complete\n");
		if(arg)
			pthread_exit((void *)2);
		pthread_cleanup_pop(0);	//参数为0,在此处清理处理函数"cleanup"不会被调用
		pthread_cleanup_pop(0);	//参数为0,在此处清理处理函数"cleanup"不会被调用
		pthread_exit((void *)2);	//pthread_exit返回,因此会调用清理函数"cleanup"
	}

	int main(void)
	{
		int err;
		pthread_t tid1, tid2;
		void *tret;

		err = pthread_create(&tid1, NULL, thr_fn1, (void *)1);
		if(err != 0)
			err_exit(err, "can't create thread 1\n");
		err = pthread_create(&tid2, NULL, thr_fn2, (void *)1);
		if(err != 0)
			err_exit(err, "can't create thread 2\n");

		err = pthread_join(tid1, &tret);	//获取返回状态
		if(err != 0)
			err_exit(err, "can't join with thread 1\n");
		printf("thread 1 exit code %ld\n", (unsinged long)tret);
		err = pthread_join(tid2, &tret);
		if(err != 0)
			err_exit(err, "can't join with thread 2\n");
		printf("thread 2 exit code %ld\n", (unsigned long)tret);
		exit(0);
	}

	//结果:
	thread 1 start
	thread 1 push complete
	thread 2 start
	thread 2 push complete
	cleanup: thread 2 second handler	//根据栈操作的顺序(先进后出)执行
	cleanup: thread 2 first handler
	thread 1 exit code 1
	thread 2 exit code 2

### 11.4 线程同步

内存与寄存器的操作步骤:

1)从内存单元读入寄存器;

2)在寄存器中对变量进行操作;

3)将新值写回内存单元.

线程同步:两个或多个线程试图在同一时间修改同一变量.

**1)互斥量**

使用mutex(互斥量)保护数据,确保同一时间只有一个线程访问数据.得到锁的线程会正常执行,而其他试图获取锁的线程会处于阻塞状态.

互斥量的声明、初始化以及销毁:

	#include <pthread.h>
	pthread_mutex_t mutex;	//声明一个互斥量
	int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);	//互斥量初始化函数
	//para1:声明的互斥量; para2:互斥量属性,可以为"NULL"
	int pthread_mutex_destroy(pthread_mutex_t *mutex);	//销毁互斥量
	//如果动态分配的互斥量(使用malloc函数),在释放内存前要调用"pthread_mutex_destroy"销毁该互斥量
	//retval:所有函数成功返回0;失败返回错误编号

获取/释放互斥量(加锁/解锁):

	#include <pthread.h>
	int pthread_mutex_lock(pthread_mutex_t *mutex);		//加锁
	int pthread_mutex_trylock(pthread_mutex_t *mutex);	//尝试对互斥量加锁.成功就获得锁;失败返回EBUSY---用的比较少
	int pthread_mutex_unlock(pthread_mutex_t *mutex);	//释放锁
	//retval:所有函数成功返回0;失败返回错误编号

实例---使用互斥量保护数据结构

	#include <pthread.h>
	#include <stdlib.h>

	struct foo{
		int f_count;	//互斥量使用计数
		pthread_mutex_t f_lock;	//互斥量
		int f_id;
		...
	};

	/*为带互斥量的结构体分配空间*/
	struct foo* foo_alloc(int id)
	{
		struct foo *fp;
		if((fp = (struct foo *)malloc(sizeof(struct foo))) != NULL)
		{
			fp->f_count = 1;
			fp->f_id = id;
			/*初始化互斥量*/
			if(pthread_mutex_init(&fp->f_lock, NULL) != 0)
			{
				free(fp);	//互斥量初始化失败,将malloc的内存释放
				return (NULL);
			}
			...		//其他初始化
		}

		return fp;
	}

	/*对互斥量增加引用计数*/
	void foo_hold(struct foo *fp)
	{
		pthread_mutex_lock(&fp->f_lock);
		fp->f_count++;
		pthread_mutex_unlock(&fp->f_lock);
	}

	/*减少互斥量的引用计数,如果为0则销毁互斥量*/
	void foo_rele(struct foo *fp)
	{
		pthread_mutex_lock(&fp->f_lock);
		if(--fp->f_count == 0)	//最后一次引用,就销毁,并且释放malloc的内存
		{
			pthread_mutex_unlock(&fp->f_lock);
			pthread_mutex_destroy(&fp->f_lock);
			free(fp);	//free掉malloc的内存
		}else
		{
			pthread_mutex_unlock(&fp->f_lock);
		}
	}

**2)避免死锁**

使用多个互斥量时需要以相同的顺序加锁,从而避免死锁.

例子---使用两个互斥量避免死锁

	#include <stdlib.h>
	#include <pthread.h>

	#define NHASH		29
	#define HASH(id)	(((unsigned long)id)%NHASH)

	pthread_mutex_t hasklock = PTHREAD_MUTEX_INITIALIZER;	//静态初始化

	struct foo{
		int 			f_count;	//有hashlock保护
		pthread_mutex_t f_lock;
		int 			f_id;
		struct foo		*f_next;	//构成链表,有hasklock保护
		...		//其他成员
	};

	struct foo *fh[NHASH];

	struct foo *foo_alloc(int id)	//分配空间
	{
		struct foo *fp;
		int idx;
		if((fp = (struct foo *)malloc(sizeof(struct foo))) != NULL)
		{
			fp->f_count = 1;
			fp->f_id = id;
			if(pthread_mutex_init(&fp->f_lock, NULL) != 0)
			{
				free(fp);
				return NULL;
			}
			idx = HASH(id);
			pthread_mutex_lock(&hashlock);
			fp->f_next = fh[idx];
			fh[idx] = fp;	//链表指向自身
			pthread_mutex_lock(&fp->f_lock);		//先用动态锁锁住
			pthread_mutex_unlock(&hashlock);	//然后释放hasklock
			...	//其他初始化
			pthread_muex_unlock(&fp->f_lock);
		}
		return fp;
	}

	struct foo *foo_find(int id)	//寻找链表中已经存在的对象
	{
		struct foo *fp;
		pthread_mutex_lock(&hashlock);	//用hashlock锁住
		for(fp = fh[HASH(id)]; fp != NULL; fp = fp->next)
		{
			if(fp->f_id == id)	//找到对象
			{
				fp->f_count++;
				break;
			}
		}
		pthread_mutex_unlock(&hashlock);
		return fp;
	}

	void foo_rele(struct foo *fp)	//从链表中释放fp对象
	{
		struct foo *tfp;
		int idx;
		pthread_mutex_lock(&hashlock);
		if(--fp->f_count == 0)	//计数为0,需要释放对应的fp
		{
			idx = HASH(fp->f_id);
			tfp = fh[idx];	//散列表中的元素
			if(tfp == fp)
			{
				fh[idx] = fp->next;
			}else
			{
				while(tfp->f_next != fp)
					tfp = tfp->next;
				tfp->next = fp->next;
			}
			pthread_mutex_unlock(&hashlock);
			pthread_mutex_destroy(&fp->f_lock);
			free(fp);
		}else
		{
			pthread_mutex_unlock(&hashlock):
		}
	}

**3)函数pthread_mutex_timedlock**

	#include <pthread.h>
	#include <time.h>
	int pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *tsptr);
	//para2:线程的阻塞时间(是一个绝对时间,非相对时间)---用的比较少
	//retval:成功返回0,失败返回错误编号

**4)读写锁**

读写锁有三种模式:读模式加锁状态,写模式加锁状态,不加锁状态.

读写锁特点:

1)一次只有一个线程占有写模式读写锁,但是一次允许多个线程同时占有读模式读写锁;

2)如果读写锁是写加锁状态时,在解锁之前,所有试图获取这个锁的线程都将被阻塞;

3)如果读写锁是读加锁状态时,所以试图以读模式获取锁的线程都可以获得访问权,但是以写模式获取锁的线程都将被阻塞.

4)当读写锁处于读模式锁住状态,如果有一个线程试图以写模式获取锁.此时读写锁通常会阻塞随后试图以读模式获取锁的请求.避免读模式长期占用锁.

读写锁初始化及销毁:

	#include <pthread.h>
	int pthread_rwlock_init(pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
	//初始化读写锁.	para2:读写锁属性
	int pthread_rwlock_destroy(pthread_rwlock_t *rwlock);	//销毁读写锁
	//retval:成功返回0;失败返回错误编号

读/写模式获取读写锁及释放锁:

	#include <pthread.h>
	int pthread_rwlock_rdlock(pthread_rwlock_t *rwlock);	//读模式获取读写锁
	int pthread_rwlock_wrlock(pthread_rwlock_t *rwlock);	//写模式获取读写锁
	int pthread_rwlock_unlock(pthread_rwlock_t *rwlock);	//释放读写锁
	//retval:成功返回0;失败返回错误编码

	int pthread_rwlock_tryrdlock(pthread_rwlock_t *rwlock);	
	//尝试以读模式获得读写锁,成功就获取读写锁并返回0;失败不阻塞返回错误EBUSY
	int ptrehad_rwlock_trywrlock(pthread_rwlock_t *rwlock);
	//尝试以写模式获得读写锁,成功就获取读写锁并返回0;失败不阻塞返回错误EBUSY

实例---使用读写锁

	#include <stdlib.h>
	#include <pthread.h>
	struct job{
		struct job *j_next;
		struct job *j_prev;
		pthread_t j_id;		//线程ID,告知哪个线程处理这个job
		...		//其他成员
	};

	struct queue{	//工作队列
		struct job *q_head;
		struct job *q_tail;
		pthread_rwlock_t q_lock;	//读写锁
	};

	//初始化一个工作队列
	int queue_init(struct queue *qp)
	{
		int err;
		qp->q_head = NULL;
		qp->q_tail = NULL;
		err = pthread_rwlock_init(&qp->q_lock, NULL);	//初始化读写锁
		if(err != 0)
			return err;
		...	//其他初始化
		return 0;
	}

	//在队列头部插入工作
	void job_insert(struct queue *qp, struct job *jp)
	{
		pthread_rwlock_wrlock(&qp->q_lock);	//以写模式获取读写锁
		jp->j_next = qp->q_head;		//next指向头
		jp->j_prev = NULL;			//prev指向NULL
		if(qp->q_head != NULL)
			qp->q_head->j_prev = jp;		//head的prev指向jp
		else
			qp->q_tail = gp;		//表示链表list为空
		qp->q_head = jp;		//head指向新的jp
		pthread_rwlock_unlock(&qp->q_lock);	//释放读写锁
	}

	//在队列尾部插入job
	void job_append(struct queue *qp, struct job *jp)
	{
		pthread_rwlock_wrlock(&qp->q_lock):
		jp->j_next = NULL;		//next指向NULL
		jp->prev = qp->q_tail;	//prev指向尾
		if(qp->q_tail != NULL)
			qp->q_tail->next = jp;	//tail的next指向jp
		else
			qp->q_head = jp;		//空链表list
		qp->q_tail = jp;
		pthread_rwlock_unlock(&qp->q_lock);
	}

	//从一个队列中移除job
	void job_remove(struct queue *qp, struct job *jp)
	{
		pthread_rwlock_wrlock(&qp->q_lock);
		if(jp == qp->q_head)
		{
			qp->q_head = jp->j_next;
			if(qp->q_tail == jp)
				qp->q_tail = NULL;
			else
				jp->j_next->j_prev = jp->prev;
		}else if(jp == qp->q_tail)
		{
			qp->q_tail = jp->j_prev;
			jp->j_prev->j_next = jp->j_next;
		}else
		{
			jp->j_prev->j_next = jp->j_next;
			jp->j_next->j_prev = jp->j_prev;
		}
		pthread_rwlock_unlock(&qp->q_lock);
	}

	//对于一个给定的线程ID找到对应job
	struct job *job_find(struct queue *qp, pthread_t id)
	{
		struct job *job;
		if(pthread_rwlock_rdlock(&qp->q_lock) != 0)
			return NULL;
		for(jp = qp->head; jp != NULL; jp = jp->j_next)
			if(pthread_equal(jp->j_id, id))
				break;

		pthread_rwlock_unlock(&qp->q_lock);
		return jp;
	}

**5)超时的读写锁**

	#include <pthread.h>
	#include <time.h>
	int pthread_rwlock_timedrdlock(pthread_rwlock_t *rwlock, const struct timespec *tsptr);
	int pthread_rwlock_timedwrlock(pthread_rwlock_t *rwlock, const struct timespec *tsptr);
	//para2:线程的阻塞时间(是一个绝对时间,非相对时间)---用的比较少
	//retval:成功返回0,失败返回错误编号

**6)条件变量**

条件变量是线程同步的一种机制.条件变量与互斥量一起使用,允许线程等待特定的条件发生.

条件变量的初始化及销毁:

	#include <pthread.h>
	pthread_cont_t cond;	//表示一个条件变量
	int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
	//初始化条件变量;		para2:条件变量属性,可以为"NULL"
	int pthread_cond_destroy(pthread_cond_t *cond);	//销毁一个条件变量
	//retval:成功返回0,失败返回错误编号

条件变量的等待:
	
	#include <pthread.h>
	int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
	//等待条件,此时会对互斥量进行解锁,线程进入休眠同时会不断检测条件.一旦条件满足该函数会返回互斥量再次被锁住
	int pthread_cond_timedwait(pthread_cont_d *cond, pthread_mutex_t *mutex, const struct timespec *tsptr);
	//超时条件变量
	//retval:成功返回0,失败返回错误编号

条件变量的发送(唤醒休眠的等待进程):

	#include <pthread.h>
	int pthread_cond_signal(pthread_cond_t *cond);	//唤醒一个以上的线程
	int pthread_cond_broadcast(pthread_cond_t *cond);	//唤醒所有的等待条件的线程
	//retval:成功返回0;失败返回错误编号

实例---条件变量的使用

	#include <pthread.h>
	struct msg{
		struct msg *m_next;
		...	//其他结构体成员
	};

	struct msg *workq;

	pthread_cond_t qready = PTHREAD_COND_INITIALIZER;	//静态条件变量初始化
	pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;	//静态互斥量初始化

	void process_msg(void)
	{
		struct msg *mp;
		for(;;)
		{
			pthread_mutex_lock(&qlock);
			while(workq == NULL)	//workq作为条件变量
				pthread_cond_wait(&qready, &qlock);	//等待条件变量
			mp = workq;
			workq = mp->m_next;
			pthread_mutex_unlock(&qlock);
			//会继续处理下一个msg
		}
	}

	void enqueue_msg(struct msg *mp)
	{
		pthread_mutex_lock(&qlock);
		mp->m_next = workq;
		workq = mp;
		pthread_mutex_unlock(&qlock);	//锁可以放到信号发送之后,此处因为发送信号不需要占用互斥量
		pthread_cond_signal(&qready);
	}

***
## Chpater 12 线程控制

***
## Chapter 15 进程间通信

### 15.9 共享存储(内存)---SHM

共享存储(内存)允许两个或多个进程共享一个给定的存储区.因为数据不需要在客户进程和服务器进程之间复制,因此这是最快的一种IPC(进程间通信).

要求:多个进程之间需要同步的访问给定的存储区.一般使用信号量进行共享存储访问的同步.

**内核为每个共享存储段维护着一个结构,该结构描述共享存储段的一些属性:**

	struct shmid_ds {	//描述共享存储段属性的结构体
		struct ipc_perm	shm_perm;		/*共享存储段的权限*/
		size_t			shm_segsz;		/*共享存储段的大小(byte为单位)*/
		pid_t			shm_lpid;		/*一般为创建的子进程的PID*/
		pid_t			shm_cpid;		/*创建者的PID,一般为父进程的PID*/
		shmatt_t		shm_nattach;	/*当前attach的数量,一般为使用共享存储的进程数量*/
		time_t			shm_atime;		/*最后attach的时间*/
		time_t			shm_dtime;		/*最后detach的时间*/
		time_t			shm_ctime;		/*最后改变的时间*/
		...		//还有其他的一些属性
	};

**1.shmget函数---产生一段共享存储区,得到一个共享存储标识符**

	#include <sys/shm.h>	//使用共享存储函数所需的头文件
	int shmget(key_t key, size_t size, int flag);	//产生一段共享存储区
	/*
		para1:键值.其取值:
			1.IPC_PRIVATE(即0):会建立新的共享存储区
			2.由ftok函数创建一个键值
			#include <sys/ipc.h>	//使用ftok函数所需的头文件
			key_t ftok(const char *path, int id);	//将path和id构成一个键值
			e.g. key = ftok("./tmp", 0x03);
		para2:共享存储段的大小.获取其他已经创建好的共享存储则为0
		para3:标志参数,其取值为:
			1.0:取已经存在的共享存储标识符.常用在某个函数已经建立了一段共享存储区,后面的文件/函数使用它
			2.IPC_CREAT:如果内核中不存在键值与key相等的共享存储区,在新建一段共享存储;如果存在则直接返回共享存储的标识符
			3.IPC_CREAT | IPC_EXCL:如果内核中不存在键值与key相等的共享存储,则新建一个消息队列;如果存在则报错
			4.IPC_CREAT | IPC_EXCL | 0600:加上对象的存储权限.

		retval:成功返回共享存储的ID;出错返回-1
	*/

**2.shmctl函数---对共享存储段进行管理**

	#include <sys/shm.h>
	int shmctl(int shmid, int cmd, struct shmid_ds *buf);
	/*
		para1:shmget返回的shmid
		para2:表示需要执行的操作,其取值为:
			1.IPC_STAT:得到共享存储的状态,把共享存储的shmid_ds结构(属性)复制到buf中,以便后续处理
			2.IPC_SET:改变共享存储的状态,将buf所指的shmid_ds结构中uid、gid、mode复制到共享存储的shmid_ds结构中
			3.IPC_RMID:删除这段共享存储区

		retval:成功返回0.出错返回-1.
	*/

**3.shmat函数---把共享存储区映射到调用进程的地址空间**

	#include <sys/shm.h>
	void *shmat(int shmid, const void *addr, int flag);
	/*
		para1:shmget返回的shmid
		para2:一般为NULL,表示让内核自己决定一个合适的位置,系统选择一个合适的地址
		para3:指定读/写权限
			1.SHM_RDONLY---以只读连接此段.表示此段共享存储区只读
			2.0---表示读写方式连接此段.表示此段共享存储区可读写

		retval:成功返回指向共享存储段的指针,透过该指针可以操作共享存储段.出错返回-1.
	*/

**4.shmdt函数---断开共享存储的连接**

	#include <sys/shm.h>
	int shmdt(const void *addr);	//断开共享存储区与调用进程的地址空间的映射
	/*
		para:调用shmat返回的共享存储段的指针
		
		retval:成功返回0.出错返回-1.
	*/

**实例1---父子进程通信**

	/*shm.c---父子进程通信*/
	#include <stdio.h>
	#include <string.h>
	#include <unistd.h>
	#include <sys/ipc.h>
	#include <sys/shm.h>
	#include <error.h>

	#define SIZE 	1024

	int main(int argc, char **argv)
	{
		int shmid;
		char *shmaddr;			//存放共享存储映射到进程地址空间的指针
		struct shmid_ds buf;	//存放共享存储的一些属性
		int flag = 0;
		int pid;

		shmid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT | 0600);
		if (shmid == -1)
		{
			printf("shmget error\n");
			return -1;
		}
		pid = fork();	//创建子进程
		if (pid == 0)	//子进程代码
		{
			shmaddr = (char *)shmat(shmid, NULL, 0);	//将共享存储映射到进程地址空间
			if ((int)shmaddr == -1)		//虽然返回void *,但是出错返回-1.因此需要强制转换
			{
				printf("shmat error\n");
				return -1;
			}
			strcpy(shmaddr, "Hi, I am child process!\n");	//往共享存储区中复制字符串
			shmdt(shmaddr);		//断开共享存储区与调用进程地址空间的映射
			return 0;
		}else if(pid > 0)	//父进程代码.pid为子进程的pid
		{
			sleep(3);	//让子进程先执行
			flag = shmctl(shmid, IPC_STAT, &buf);	//对共享存储区进行管理
			if (flag == -1)
			{
				printf("shmctl error\n");
				return -1;
			}
			
			//打印出共享存储区的一些信息
			printf("shm_segsz = %d bytes\n", buf.shm_segsz);	//共享存储区的大小,此处为1024
			printf("parent pid: %d, shm_cpid = %d\n", getpid(), buf.shm_cpid);
				//获得父进程的pid和创建者的pid,此处均为父进程的pid
			printf("child pid: %d, shm_lpid = %d\n", pid, buf.shm_lpid);
				//子进程的pid和shm_lpid.均为子进程的pid
			
			shmaddr = (char *)shmat(shmid, NULL, 0);	//将共享存储映射到进程地址空间
			if ((int)shmaddr == -1)
			{
				printf("shmat error\n");
				return -1;
			}
			printf("%s\n", shmaddr);	//打印出共享存储区的内容.此处为"Hi, I am child process!"
			shmdt(shmaddr);		//断开共享存储区与调用进程地址空间的映射
			shmctl(shmid, IPC_RMID, NULL);	//删除共享存储区
		}

		return 0;
	}

**实例2---多进程读写**

1.写共享存储进程代码

	//shmwrite.c---写共享存储代码
	#include <stdio.h>
	#include <sys/ipc.h>
	#include <unistd.h>
	#include <string.h>
	#include <sys/shm.h>
	#include <sys/types.h>

	typedef struct{
		char name[8];
		int age;
	}people;

	int main(int argc, char **argv)
	{
		int shm_id, i;
		key_t key;
		char temp[8];
		people *p_map;
		char pathname[30];
		
		strcpy(pathname, "./temp");
		key = ftok(pathname, 0x03);		//创建一个键值.成功返回键值,出错返回-1
		if (key == -1)
		{
			printf("ftok error\n");
			return -1;
		}
		printf("key value: %d\n", key);
		shm_id = shmget(key, 4096, IPC_CREAT | IPC_EXCL | 0600);
		if (shm_id == -1)
		{
			printf("shmget error\n");
			return -1;
		}
		printf("shm_id value: %d\n", shm_id);
		p_map = (people *)shmat(shmid, NULL, 0);
		if ((int)p_map == -1)
		{
			printf("shmat error\n");
			return -1;
		}
		memset(temp, 0x00, sizeof(temp));	//sizeof(temp):求数组的大小
		strcpy(temp, "test");
		temp[4] = '0';	//第5个字符为0
		for(i=0; i<3; i++)
		{
			temp[4] += 1;	//或者temp[4] += (char)1;千万不能是:temp[4] += '1';---错误
			strncpy((p_map+i)->name, temp, 5);	//拷贝temp中的内容到共享内存区域
			(p_map+i)->age = i;
		}
		
		//断开共享存储区与调用进程地址空间的映射
		shmdt(p_map);
		return 0;
	}

2.读共享存储进程代码

	//shmread.c---读共享存储代码
	#include <stdio.h>
	#include <unistd.h>
	#include <string.h>
	#include <sys/ipc.h>
	#include <sys/types.h>
	#include <sys/shm.h>
	
	typedef struct {
		char name[8];
		int age;
	}people;

	int main(int argc, char **argv)
	{
		int shm_id, i;
		key_t key;
		people *p_map;
		char pathname[30];

		strcpy(pathname, "./temp");
		key = ftok(pathname, 0x03);
		if (key == -1)
		{
			printf("ftok error\n");
			return -1;
		}
		printf("key value: %d\n", key);
		shm_id = shmget(key, 0, 0);		//para2=0---获取已经创建好的共享存储
		if (shm_id == -1)
		{
			printf("shmget error\n");
			return -1;
		}
		printf("shm_id value: %d\n", shm_id);
		p_map = (people *)shmat(shm_id, NULL, 0);
		if ((int)p_map == -1)
		{
			printf("shmat error\n");
			return -1;
		}
		for (i=0; i<3; i++)
		{
			printf("name: %s\n", (p_map+i)->name);	//如果为:(*(p_map+i)).name也正确,相当于将指针转成了一个变量
			printf("age: %d\n", (p_map+i)->age);		//如果为:(*(p_map+i)).age也正确,相当于将指针转成了一个变量
		}
		
		if (shmdt(p_map) == -1)
		{
			printf("shmdt error\n");
			return -1;
		}
		return 0;	//因为最终没有删除掉共享存储,所以会一直存在.
	}

3.编译并执行

	gcc shmwrite.c -o shmwrite
	gcc shmread.c -o shmread

	1---执行./shmwrite得到结果:
	key = 51460524
	shm_id = 294912
	2---执行./shmread得到结果:
	key = 51460524
	shm_id = 294912
	name: test1
	age = 0
	name: test2
	age = 1
	name: test3
	age = 2
	3---再次执行./shmwrite就会报错:
	key=50453281
	shmget error: File exists
	//因为共享存储已经存在,代码中也没有删除掉
	4---需要手动用命令行删掉共享存储
	ipcrm -m 294912		//后面为共享存储ID