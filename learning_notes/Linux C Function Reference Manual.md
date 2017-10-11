# Linux C Function Reference Manual

## isdigit(测试字符是否为阿拉伯数字)---标准c中有

	头文件:	#include <ctype.h>
	int isdigit(int c)
	/*
		检查参数c是否为阿拉伯数字0-9.--->c可以为单个字符
		retval:是阿拉伯数字返回非0;否则返回0
		PS:此为宏定义,非真正函数
	*/
	
	e.g. /*找出str字符串中为阿拉伯数字的字符*/
	#include <ctype.h>
	int main()
	{
		char str[] = "123@#FDsP[e?";	//str结束为NULL(0)
		int i;
		for (i=0; i != 0; i++)
		{
			if (isdigit(str[i]))
				printf("%c is an digit character\n", str[i]);	//会将1,2,3这三个数字打印,其他不会打印
		}

		return 0;
	}

## isalpha(测试字符是否为英文字母)---标准c中有

	头文件:	#include <ctype.h>
	int isdigit(int c)
	/*
		检查参数c是否为英文字母.--->c为单个字符
		retval:是英文字母返回非0;否则返回0
		PS:此为宏定义,非真正函数
		该函数相当于使用(isupper(c) || islower(c)).
	*/
	
	e.g. /*找出str字符串中为阿拉伯数字的字符*/
	#include <ctype.h>
	int main()
	{
		char str[] = "123@#FDsP[e?";	//str结束为NULL(0)
		int i;
		for (i=0; i != 0; i++)
		{
			if (isalpha(str[i]))
				printf("%c is an alphanumeric character\n", str[i]);	//会将F,D,s,P,e打印
		}

		return 0;
	}

## isalnum (测试字符是否为英文或数字)

	头文件:	#include <ctype.h>
	int isalnum(int c);
	/*
		检查参数c是否为英文字母或阿拉伯数字.--->c为单个字符
		retval:是英文字母或阿拉伯数字返回非0;否则返回0
		PS:此为宏定义,非真正函数
		该函数相当于标准c中使用(isalpha(c) || isdigit(c)).
	*/
	e.g. /*找出str字符串中为英文字母或阿拉伯数字的字符*/
	#include <ctype.h>
	int main()
	{
		char str[] = "123@#FDsP[e?";	//str结束为NULL(0)
		int i;
		for (i=0; i != 0; i++)
		{
			if (isalnum(str[i]))
				printf("%c is an alphanumeric character\n", str[i]);	//会将1,2,3,F,D,s,P,e打印
		}

		return 0;
	}

## mmap (建立内存映射)---将内核空间映射到用户空间

	头文件:	#include <unistd.h>
			#include <sys/mman.h>
	void *mmap(void *start, size_t length, int prot, int flags, int fd, off_t offsize);
	/*
		para1:预对应的内存起始地址,通常设为NULL.让系统自动选择地址,对应成功后该地址会返回
		para2:映射的大小
		para3:映射区域的保护方式:
			PROT_EXEC:映射区域可被执行;
			PROT_READ:映射区域可被读取;
			PROT_WRITE:映射区域可被写入;
			PROT_NONE:映射区域不能存取.
		para4:影响映射区域的特定:
			MAP_SHARED:对映射区域写入数据会复制回文件内,而且允许其他映射该文件的进程共享
			MAP_PRIVATE:对该区域的任何修改都不会写回到原来的文件中---一般用于只读打开文件
		para5:fd,open返回的文件描述符
		para6:映射的偏移量.在内核映射时,可以指定任何一段物理地址映射.此时的起始地址可能不是page对齐,
				可以先取page对齐,后续再加上一个偏移.e.g. addr(物理地址) & (~ 4095)	//强制page对齐
				后续映射好之后再:map_addr(映射地址) + (物理地址 & 4095)---4k对齐时留下的偏移
		retval:映射成功返回映射区的起始内存地址,否则返回MAP_FAILED(-1),错误原因存在于errno中.
	*/
	
	e.g. /*利用mmap()来读取/etc/passwd文件内容*/---不常用
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/mman.h>

	int main()
	{
		int fd;
		void *start;
		struct stat sb;		//保存文件的信息
		fd = open("/etc/passwd", O_RDONLY);
		fstat(fd, &sb);		//取得打开的文件信息
		start = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
		/*
			sb.st_size:文件的大小
			para6=0:表示从文件头开始读取
		*/
		if (start == MAP_FAILED)	//映射失败
			return 0;

		printf("%s\n", start);	//打印出映射的文件内容
		munmap(start, sb.st_size);	//解除映射
		close(fd);
	}
	
## munmap (解除内存映射)

	头文件:	#include <unistd.h>
			#include <sys/mman.h>
	int munmap(void *start, size_t length);
	/*
		取消参数start所指的映射内存起始地址,大小为length
		para1:mmap返回的指针
		para2:mmap映射的大小
	*/
	e.g. /*参见mmap*/

## tolower (将大写字母转换成小写字母)

	头文件:#include <stdlib.h>
	int tolower(int c);		//可以直接传入一个字母,自动转换为小写字母返回
	e.g.	/*将s字符串内的大写字母转换成小写字母*/
	#include <ctype.h>
	int main()
	{
		char s[]="aBcDeFgH12345;!#$";
		int i;
		printf(“before tolower():%s\n”,s);
		for(i=0; i<sizeof(s); i++)
			s[i]=tolower(s[i]);
		
		printf(“after tolower():%s\n”,s);
		return 0;
	}
	打印得到:
	before tolower():aBcDeFgH12345;!#$
	after tolower():abcdefgh12345;!#$

## toupper (将小写字母转换成大写字母)

	头文件:#include <ctype.h>
	int toupper(int c);		//可以直接传入一个字母,自动转换为大写字母返回
	e.g.	/*将s字符串内的小写字母转换成大写字母*/
	#include <ctype.h>
	int main()
	{
		char s[]="aBcDeFgH12345;!#$";
		int i;
		printf(“before toupper():%s\n”,s);
		for(i=0; i<sizeof(s); i++)
			s[i]=toupper(s[i]);
		
		printf(“after toupper():%s\n”,s);
		return 0;
	}
	打印得到:
	before tolower():aBcDeFgH12345;!#$
	after tolower():ABCDEFGH12345;!#$

## strtol (将字符串转换成长整型数)

	头文件:#include <stdlib.h>
	long int strtol(const char *nptr, char **endptr, int base);
	/*strtol:将字符串转化成长整型数
		para1:要转换的字符串
		para2:表示遇到什么字符结束,一般为NULL或者0.表示遇到空格或回车字符串结束
		para3:字符串表示的数据采用的进制方式,为0表示10进制,但是遇到"0x"前置字符则会使用16进制做转换
	*/
	e.g.	/*将字符串a, b, c分别采用10, 2, 16进制转换成数字*/
	#include <stdlib.h>
	int main()
	{
		char a[]="1000000000";
		char b[]="1000000000";
		char c[]="ffff";
		printf("a=%d\n", strtol(a, NULL, 10));	//会打印出:a=1000000000.字符串a为10进制数
		printf("b=%d\n", strtol(b, NULL, 2));	//会打印出:b=512.字符串b为2进制数,因此为512
		printf("c=%d\n", strtol(c, NULL, 16));	//会打印出:c=65536.字符串c为16进制数,因此为65536
		return 0;
	}

## strtoul (将字符串转换成无符号长整型数)

	头文件:	#include <stdlib.h>
	unsigned long strtoul(const char *nptr, char **endptr, int base);
	//与strtol相似,只是返回的为无符号长整型数

## fflush (更新缓冲区)

	头文件:#include <stdio.h>
	int fflush(FILE *stream);
	//fflush会强迫将缓冲区的数据写回参数stream指定的文件中.
	//如果参数stream为NULL,fflush()会将所有打开的文件数据更新 