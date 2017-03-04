# Linux内核设计与实现
## Linux Kernel Development
***
## 第二章 从内核出发

*内核源码(linux主机中的)安装在"/usr/src/linux"目录下--相当于windows的C盘中的System.*

*"/usr/src/linux"下的内核源码树不能用于开发(提供很多linux命令),编译C库时所用的内核版本就链接到这棵树.做开发时，一般是在自己的目录中重新下载一个内核文件(此时,linux主机相当于一个IDE).*

*内核配置以"CONFIG"为前缀.*

**"/dev/null"是一个"黑洞",只写文件,但是写入的内容会永远丢失,从该文件读什么也没有.一般用于重定向处理.**

### 2.1 内核开发的特点

*内核开发不能使用标准C库(libc库),但是常用的C库函数在内核中已经实现,位于"./lib/"下,使用时可以e.g. #include <linux/string.h>*

**内联(inline)函数**

*一般将长度比较短又反复调用的函数定义成内联函数.使用"static inline"加在函数定义头部.*

	static inline void dog(unsigned long tail_size);

*内联函数一般在头文件中定义.如果仅在某一个源文件中使用,也可以定义在该文件开始的地方.*

**条件分支优化(likyly & unlikely)**

*针对某个条件经常成立或者很少成立的情况,用于提升运行性能.*

	if (unlikely(foo)) /*foo绝大多数情况为0(即不成立)*/
	{
		...
	}
	if (likely(foo)) /*foo绝大多数情况不为0(即成立，为真)*/
	{
		...
	}

**内核中没有内存保护机制**

*用户程序进行非法内存访问,内核会发送"SIGSEGV"错误,并结束进程.*

*内核发生内存错误会导致"oops",内核中不应该访问非法内存地址和引用空指针.*

*内核中内存不分页(即每用掉一个字节,物理内存就减少一个字节).*

**不要在内核中使用浮点数**

**内核栈大小固定**

*内存中:段(1MB)、大页(64KB)、小页(4KB)、极小页(1KB).*

## 第三章 进程管理

*调用fork()系统调用可以创建一个新的进程.调用的进程称为父进程,创建的进程称为子进程.调用返回两次(一次返回到父进程,另一次返回子进程).*

**fork()创建进程返回时,子进程先执行(子进程需要调用exec()函数载入可执行程序)，父进程后执行.**

*进程退出执行后是被设置为僵死状态.*

	exit()系统调用用于退出进程的执行
	wait4()系统调用用于父进程查询子进程是否终结

*进程在内核中叫任务(task).*

### 3.1 进程描述符及任务结构

*内核中的进程放置在一个叫任务队列(task list)的双向循环列表中,链表中每一项都是描述进程的结构体.*

**进程描述符(task_struct)**

*进程用"struct task_struct"结构体描述(称为进程描述符),结构位于"./include/linux/sched.h",需要使用时可以e.g. #include <linux/sched.h>*

*task_struct(进程描述符)的"pid_t pid"域(成员)标识具体的进程.*

	pid_t pid;	/*pid:标识进程, pid_t隐含类型(实际为int类型)*/

**进程状态**

*task_struct(进程描述符)的"state"域描述进程当前状态.*
	
	TASK_RUNNING(运行):进程正在执行或在运行队列中等待执行.
	TASK_INTERRUPTIBLE(可中断):进程在睡眠(阻塞),等待某些条件.条件达成或者接收到某信号可以唤醒并切换到TASK_RUNNING.
	TASK_UNINTERRUPTIBLE(不可中断):不会被信号打断，其他和TASK_INTERRUPTIBLE相同,使用的较少.
	TASK_ZOMBIE(僵死):进程已经结束,子进程保留现场，等待父进程调用wait4()将tast_struct(子进程描述符)释放.
	TASK_STOPPED(停止):进程停止(没运行也不能运行).一般在接收到信号(SIGSTOP、SIGTSTP、SIGTTIN、SIGTTOU)时发生.

**进程上下文**

*一般程序在用户空间执行,当程序系统调用或触发某个异常会陷入内核空间,此时"内核代表进程执行"并处于进程上下文.*

**进程家族树**

*获得父进程描述符*

	struct task_struct *my_parent = current->parent;		/*current:表示当前进程(为linux中的一个宏)*/

*获得子进程*

	struct task_struct *task;
	struct list_head *list;
	list_for_each(list, &current->children) {
		task = list_entry(list, struct task_struct, sibling);
		/*task指向当前进程的某个子进程*/
	}

### 3.2 进程创建

**Unix和Linux创建进程的步骤为:**

*1)fork()通过拷贝当前进程创建一个子进程;*

*2)exec()读取可执行文件(载入地址空间)开始运行.*

*linux的fork()使用写时拷贝(copy-on-write)实现--只有在需要写入数据时才将资源copy,在此之前数据只读共享,两个进程共享数据资源.*

*vfork()在子进程运行时,父进程阻塞,直到子进程退出或执行exec()--相当于明确了子进程先执行,父进程后执行.但由于现在fork()采用写时拷贝页也达到相同的效果,因此vfork()使用越来越少.*

**线程**

*线程:计算机独立运行的最小单位,运行时占用的系统资源很少.一个进程可以有多个线程,多个线程共享一个进程的资源.*

*线程相比进程的优势:*

*1)"节俭":进程占据独立的地址空间(独立的资源),多个线程共享一个进程的资源.因此启动的开销远远小于进程.*

*2)"方便的通信机制":进程间占据独立的地址空间,进行数据的传递只能通过通信的方式进行;线程间共享数据空间(资源),因此一个线程的资源可以直接为其他线程使用(但是也会带来危害,同时修改--只能通过互斥等方式避免).*

	#include <pthread.h> /*线程头文件,链接时需要使用库"libpthread.a"*/

	int *thread(void *arg)
	{
		printf("thread id is %d \n", pthread_self()); /*pthread_self:线程id(全局变量)*/
		return NULL;
	}

	int main()
	{
		pthread_t id;
		printf("thread id is %d\n", pthread_id());
		/*pthread_create(pthread_t *pthread, pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
		para1:返回的线程ID
		para2:线程属性(NULL);
		para3:线程创建后需要调用的函数
		para4:传递给线程函数的参数
		*/
		if(!pthread_create(&id, NULL, (void *)thread, NULL)) {
			...
		}
	}
***
## 第四章 进程调度

