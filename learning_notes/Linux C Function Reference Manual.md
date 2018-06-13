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

## getopt (处理命令行选项参数,只能接短选项)

	#include <unistd.h>
	#include <getopt.h> /*getopt函数所在头文件*/
	int getopt(int argc, char * const argv[], const char *optstring);
	/*
		para1:main()函数传递过来的参数的个数(e.g.argc).
		para2:main()函数传递过来的参数的字符串指针数组(e.g.argv).
		para3:选项字符串,告知getopt()可以处理哪个命令行选项以及选项是否需要参数.
			char *optstring = "ab:c::";
			1.单个字符a -->表示命令行选项a没有参数.
				格式为: ./a.out -a即可,不带命令行选项的参数
			2.单个字符加冒号b: -->表示命令行选项b必须带参数.
				格式为: ./a.out -b 100或者./a.out -b100.其后面带一个命令行选项参数"100".
				像格式:./a.out -b=100是错的.
			3.单个字符加2个冒号c:: -->表示命令行选项c可以带也可以不带参数.
				格式为: ./a.out -c200. --->必须是这种格式,其他格式是错误的.

		retval:
			1.如果选项成功找到,则返回选项字母(e.g.命令行指定了"-a",该函数会返回字母"a".);
			2.如果所有命令行选项解析完毕,返回"-1";
			3.如果遇到命令行选项字符不在optstring中,返回字符"?";
			4.如果遇到丢失命令行选项的参数,返回值依赖于optstring中的第一个字符,
				如果optstring中的第一个字符为":",则直接返回":";否则返回"?"并提示错误信息.
	*/
	//一些重要的变量
	extern char *optarg; //getopt.h中声明的全局变量,在函数中可以直接使用.
		optarg--->指向当前命令行选项所带的参数的指针(为一个字符串).
	extern int optind;	//下一个命令行选项的索引值,即下一个argv指针的索引
	extern int optopt;	//最后一个未知选项
	extern int opterr;	//如果不希望getopt()打印出错信息,则只要将全局变量opterr设为0即可.

**实例**

	#include <stdio.h>
	#include <unistd.h>
	#include <getopt.h>
	int main(int argc, char *argv[])
	{
		int opt;
		char *string = "a::b:c:d";
		while ((opt = getopt(argc, argv, string) != -1)) {
			printf("opt = %c\t\t", opt); //打印getopt返回的命令行选项字母
			printf("optarg = %s\t\t", optarg); //打印出当前命令行选项所带的参数
			printf("optind = %d\t\t", optind); //打印出下一个命令行选项的索引值
			printf("argv[%d] = %s\n", optind, argv[optind]); //打印出下一个命令行选项
		}
	}

	//测试:
	1)./a.out -a100 -b 200 -c 300 -d		//a:可带参数的选项; b,c:必带参数的选项; d:不带参数的选项.
		opt = a		optarg = 100		optind = 2		argv[2] = -b
		opt = b		optarg = 200		optind = 4		argv[4] = -c
		opt = c		optarg = 300		optind = 6		argv[6] = -d
		opt = d		optarg = (null)		optind = 7		argv[7] = (null)
	2)./a.out -a100 -b200 -c300 -d
		opt = a		optarg = 100		optind = 2		argv[2] = -b200
		opt = b		optarg = 200		optind = 3		argv[3] = -c300
		opt = c		optarg = 300		optind = 4		argv[4] = -d
		opt = d		optarg = (null)		optind = 5		argv[5] = (null)
	3)./a.out -a -b 200 -c 300 -d		//命令行选项所带的可选参数没有的情况
		opt = a		optarg = (null)		optind = 2		argv[2] = -b
		opt = b		optarg = 200		optind = 4		argv[4] = -c
		opt = c		optarg = 300		optind = 6		argv[5] = -d
		opt = d		optarg = (null)		optind = 7		argv[7] = (null)
	4)./a.out -a 100 -b 200 -c 300 -d	//命令行选项所带的可选参数错误的情况(-a 100--->格式错误)
		opt = a		optarg = (null)		optind = 2		argv[2] = 100 //optarg为null,错误
		opt = b		optarg = 200		optind = 5		argv[5] = -c
		opt = c		optarg = 300		optind = 7		argv[7] = -d
		opt = d		optarg = (null)		optind = 8		argv[8] = (null)
	5)./a.out -a -b 200 -c				//命令行选项必带参数但是不加参数的错误情况(-c--->后面没有参数)
		opt = a		optarg = (null)		optind = 2		argv[optind] = -b
		opt = b		optarg = 200		optind = 4		argv[optind] = -c
		./opt: optionrequires an argument -- 'c'		//出现错误了
		opt = ?		optarg = (null)		optind = 5		argv[optind] = (null)
	6)./a.out -a -b 200 -e				//输入未定义的命令行选项出错的情况
		opt = a		optarg = (null)		optind = 2		argv[optind] = -b
		opt = b		optarg = 200		optind = 4		argv[optind] = -e
		./opt: invalidoption -- 'e'		//出现错误了
		opt = ?		optarg = (null)		optind = 5		argv[optind] = (null)

## getopt_long函数 (处理命令行选项参数,可以指定长选项,短选项也是支持的).

	#include <unistd.h>
	#include <getopt.h> /*getopt_long函数所在头文件*/
	int getopt_long(int argc, char *const argv[], const char *optstring,
			const struct option *longopts, int *longindex);
	/*
		para1:main()函数传递过来的参数的个数(e.g.argc).
		para2:main()函数传递过来的参数的字符串指针数组(e.g.argv).
		para3:短选项字符串,告知getopt_long()可以处理哪个命令行选项以及选项是否需要参数.
			char *optstring = "ab:c::";
			1.单个字符a -->表示命令行选项a没有参数.
				格式为: ./a.out -a即可,不带命令行选项的参数
			2.单个字符加冒号b: -->表示命令行选项b必须带参数.
				格式为: ./a.out -b 100或者./a.out -b100.其后面带一个命令行选项参数"100".
				像格式:./a.out -b=100是错的.
			3.单个字符加2个冒号c:: -->表示命令行选项c可以带也可以不带参数.
				格式为: ./a.out -c200. --->必须是这种格式,其他格式是错误的.
		para4:指定长选项的名称和属性.为一个指针(即数组),可填充多种长选项.
			struct option {
				const char *name; /*长选项的命令行选项.e.g.该值如果等于"algo",则在命令行中输入:
									./a.out --algo  -->长选项应该使用"--"来指定.*/
				int has_arg;
				/*
					指明长选项的命令行选项是否需要带参数.取值如下:
					no_argument:表明长选项不带参数.e.g. --name, --help.后面没有参数信息
					required_argument:表明长选项必须带参数.e.g.--name defy(后面带一个defy的参数)
					optional_argument:表明长选项的参数是可选的.e.g.--name或--name defy(可带可不带).
				*/
				int *flag;	/*flag=NULL时,返回val(后一个成员执行的值).一般为NULL.*/
				int val;	/*执行函数找到选项时的返回值.e.g.'a',当找到algo时返回a.*/
			};
			实例:
			const struct option loogopts[] = {
				{ .name = "algo", .has_arg = required_argument, .flag = NULL, .val = 'a'},
				{ .name = "key_type", .has_arg = optional_argument, .flag = NULL, .val = 'k'},
				{ .name = "times", .has_arg = optional_argument, .flag = NULL, .val = 't'},
				{ .name = "help", .has_arg = no_argument, .flag = NULL, .val = 'h'},
			};
		para5:如果longindex非空,匹配到的longopts的下标值会保存到该变量中.一般可能不需要保存.

		retval:
			1.如果选项成功找到,则返回选项字母(e.g.命令行指定了"-a",该函数会返回字母"a".);
			2.如果所有命令行选项解析完毕,返回"-1";
			3.如果遇到命令行选项字符不在optstring中,返回字符"?";
			4.如果遇到丢失命令行选项的参数,返回值依赖于optstring中的第一个字符,
				如果optstring中的第一个字符为":",则直接返回":";否则返回"?"并提示错误信息.
	*/

**实例**

	#include <stdio.h>
	#include <unistd.h>
	#include <getopt.h>

	int main(int argc, char *argv[])
	{
		int opt;
		int option_index = 0;
		char *short_options = "r:o::n";
		const struct option long_options[] = {
			{ .name = "regarg", .has_arg = required_argument, .flag = NULL, .val = 'r'},
			{ .name = "optarg", .has_arg = optional_argument, .flag = NULL, .val = 'o'},
			{ .name = "noarg", .has_arg = no_argument, .flag = NULL, .val = 'n'},
		};
		/*
			也可以:
		const struct option long_options[] = {
			{"regarg", required_argument, NULL, 'r'},
			{"optarg", optional_argument, NULL, 'o'},
			{"noarg", no_argument, NULL, 'n'},
		};
		*/
		while ((opt = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
			printf("opt = %c\t\t", opt); //打印出选项的返回值
			printf("optarg = %s\t\t", optarg); //打印出当前命令行选项所带的参数
			printf("optind = %d\t\t", optind); //打印出下一个命令行选项的索引值
			printf("argv[optind] = %s\t\t", argv[optind]); //打印出下一个命令行选项
			printf("option_index = %d\n", option_index); //保存当前long_options的下标值.
		}
	}
	//测试:
	1)./a.out --regarg 100 --optarg=200 --noarg	
		//长选项的可选命令行选项输入形式"--xxx=100",必选选项输入形式"--regarg 100或--regarg=100"
		opt = r		optarg =100		optind = 3   argv[optind] = --optarg=200  option_index = 0
		opt = o		optarg =200		optind = 4   argv[optind] = --noarg        option_index = 1
		opt = n		optarg =(null)	optind = 5    argv[optind] =(null)          option_index = 2
	2)./a.out --regarg 100 --optarg --noarg //可选命令不带参数
		opt = r optarg =100     optind = 3     argv[optind] = --optarg option_index = 0
		opt = o optarg =(null) optind = 4      argv[optind] =--noarg   option_index = 1
		opt = n optarg =(null) optind = 5      argv[optind] =(null)     option_index = 2
	3)./a.out --regarg 100 --optarg 200 --noarg //可选选项命令输入错误(应该为"--optarg=200")
		//不会直接报错,但是参数不会正确解析出来.