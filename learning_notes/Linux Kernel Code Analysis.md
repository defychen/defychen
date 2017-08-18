# Linux Kernel Code Analysis

## 1. Linux内核编译流程---Linux最顶层的Makefile

Linux内核顶层的Makefile负责编译两类主要的目标:vmlinux和modules.

1.起始位置---标识内核版本信息

	VERSION = 4						//会被导出
	PATCHLEVEL = 4					//会被导出
	SUBLEVEL = 77					//会被导出
	EXTRAVERSION = 	
	NAME = Blurry Fish Butt
	
	export VERSION PATCHLEVEL SUBLEVEL KERNELRELEASE KERNELVERSION		//导出版本信息,其他地方可以引用,用于内核版本控制

指定编译时标准的C编译器编译flag:

	KBUILD_CFLAGS   := -Wall -Wundef -Wstrict-prototypes -Wno-trigraphs \
	                    -fno-strict-aliasing -fno-common \
	                    -Werror-implicit-function-declaration \
	                    -Wno-format-security \
	                    -std=gnu89 $(call cc-option,-fno-PIE)

2.编译vmlinux:

	all: vmlinux	//all在make后没有传递任何编译目标时的默认编译目标

**在某个xxxdriver下需要将warning认为是error可以:**

	/*在文件./driver/xxxdriver/modules/Makefile中*/
	#Warning treated as error in alidrivers
	KBUILD_CFALGS += -Werror		//将warning认为是error