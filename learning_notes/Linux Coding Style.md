# Linux Coding Style(Linux内核驱动的coding style)
***
# Chapter 1 scripts/checkpatch.pl的使用

scripts/checkpatch.pl是一个用来检查代码是否符合内核编码规范的脚本.一般用来检查patch的,但是可以用来检查文件,检查文件需要加上"-f"的选项.

## 1.1 检查代码是否符合规范

实例:(文件名为"print_msg.c")

	void print_msg(int a)
	{
		switch(a) {
			case 1:
				printf("a == 1\n");
				break;
			case 2:
				printf("a == 2\n");
				break;
		}
	}

执行checkpatch.pl的方法

	在linux kernel目录执行(linux的源码目录):
		./scripts/checkpatch.pl -f ~/xxx(print_msg.c所在的目录)/print_msg.c
	or	./buildroot/output/build/linux-xxx/scripts/checkpatch.pl -f 
		~/xxx(print_msg.c direcotry)/print_msg.c
	
	PS:Must be run from the top-level dir. of a kernel tree(该脚本必须运行在linux目录,
	且必须含有"scripts/checkpatch.pl")

实例中的代码检查后会出现以下的结果:

	ERROR: switch and case should be at the same indent(缩进)
	#3: FILE: xxx/print_msg.c:3:
	+       switch(a) {
	+               case 1:
	[...]
	+               case 2:
	
	ERROR: space required before the open parenthesis '('
	#3: FILE: xxx/print_msg.c:3:
	+       switch(a) {
	
	total: 2 errors, 0 warnings, 11 lines checked
	
	xxx/print_msg.c has style problems, please review.
	
	NOTE: If any of the errors are false positives, please report
	      them to the maintainer, see CHECKPATCH in MAINTAINERS.

## 1.2 使用scripts目录下的工具Lindent自动修改缩进问题

需要安装indent工具,一般的不会安装,执行的时候会出现提示:

./scripts/Lindent: 1: ./scripts/Lindent: indent: not found

使用方法:

	./scripts/checkpatch.pl ~/xxx(print_msg.c所在的目录)/print_msg.c	//不需要任何参数
	
执行之后新代码:

	void print_msg(int a)
	{
		switch(a) {
	+	case 1:
			printf("a == 1\n");
			break;
	+	case 2:
			printf("a == 2\n");
			break;
		}
	}	

参考了:[谈谈Linux内核驱动的coding style](http://www.cnblogs.com/wwang/archive/2011/02/24/1960283.html)