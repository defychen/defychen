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

## 2. linux driver模块调用初始化的优先级分析

在linux driver程序中会出现:module_init、rootfs_initcall、device_initcall宏等.调用不同的模块初始化宏驱动的初始化顺序不同.

在linux的目录:include/linux/init.h和module.h中分别有说明这种宏定义的优先级:

**include/linux/init.h中:**

	#define pure_initcall(fn)				__define_initcall(fn, 0) //最高优先级
	
	#define core_initcall(fn)               __define_initcall(fn, 1)
	#define core_initcall_sync(fn)          __define_initcall(fn, 1s)
	#define postcore_initcall(fn)           __define_initcall(fn, 2)
	#define postcore_initcall_sync(fn)      __define_initcall(fn, 2s)
	#define arch_initcall(fn)               __define_initcall(fn, 3)
	#define arch_initcall_sync(fn)          __define_initcall(fn, 3s)                                                                                                                        
	#define subsys_initcall(fn)             __define_initcall(fn, 4)
	#define subsys_initcall_sync(fn)        __define_initcall(fn, 4s)
	#define fs_initcall(fn)                 __define_initcall(fn, 5)
	#define fs_initcall_sync(fn)            __define_initcall(fn, 5s)
	#define rootfs_initcall(fn)				__define_initcall(fn, rootfs) //经常使用的初始化宏
	#define device_initcall(fn)				__define_initcall(fn, 6) //经常使用的初始化宏
	#define device_initcall_sync(fn)        __define_initcall(fn, 6s)
	#define late_initcall(fn)               __define_initcall(fn, 7)
	#define late_initcall_sync(fn)          __define_initcall(fn, 7s)

	#define __initcall(fn)	device_initcall(fn)

	PS:如果device_initcall(fn)注册的driver需要被优先使用,可以将该宏替换为:rootfs_initcall.
		rootfs_initcall的优先级比device_initcall的高.

**include/linux/module.h中:**

	#define module_init(x)	__initcall(x);	//刚好对应device_initcall,参见init.h

**优先级查看:**

	在将linux编译完了之后,在linux的目录下的:System.map中就有对应的模块优先级标识:
	42108 c37454ec T __initcallrootfs_start 
	42109 c37454f0 t __initcall_otp_initrootfs //表示优先级为rootfs,比6大
	...
	422260 c3745748 t __initcall_dsc_init6 //表示优先级为6
	
		