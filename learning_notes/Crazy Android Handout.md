# Crazy Android Handout(疯狂Android讲义)

## Chapter 1 Android应用与开发环境

***

# Andriod Practical Skills

## 1. ADB命令详解

ADB:Andriod Debug Bridge,是连接Android手机与PC端的桥梁,可以让用户在PC端对手机进行全面的操作.

### 1. adb的下载及安装

待增加

### 2. adb的命令详解

[一份超全超详细的ADB用法大全](http://blog.csdn.net/u010375364/article/details/52344120)

**adb devices**

查看已连接电脑的Android设备.(只有手机开启了USB调试才能使用adb工具)

	adb devices

	List of devices attached
	cf264b8f    device
	emulator-5554   device
	//显示为类似上述信息表明手机和PC端已经正确连接.

**adb start-sever/adb kill-server**

启动/停止adb服务.

**adb version**

查看adb版本.

	adb version

	Android Debug Bridge version 1.0.32
	Revision 09a0d98bebce-android

**adb shell wm size**

得到手机屏幕的分辨率.

	adb shell wm size

	Physical size: 1080x1920 //表示分辨率为:1080px * 1920px

**adb shell wm density**

得到手机屏幕的密度.

	adb shell wm density

	Physical density: 420 //表示设备屏幕分辨率为:420 dpi

**adb shell getprop ro.product.device**

得到device信息

	adb shell getprop ro.product.device

	Ulike2

**adb shell getprop ro.product.model**

得到设备型号.

	adb shell getprop ro.product.model

	Nexus 5 //表示设备型号为Nexus 5

**adb shell getprop ro.build.version.release**

得到Android系统版本

	adb shell getprop ro.build.version.release

	5.0.2 //表示android版本为5.0.2

**adb shell cat /proc/cpuinfo**

得到CPU信息

	adb shell cat /proc/cpuinfo

	Processor       : ARMv7 Processor rev 0 (v7l)
	processor       : 0
	BogoMIPS        : 38.40
	
	processor       : 1
	BogoMIPS        : 38.40
	
	processor       : 2
	BogoMIPS        : 38.40
	
	processor       : 3
	BogoMIPS        : 38.40
	
	Features        : swp half thumb fastmult vfp edsp neon vfpv3 tls vfpv4 idiva idivt
	CPU implementer : 0x51
	CPU architecture: 7
	CPU variant     : 0x2
	CPU part        : 0x06f
	CPU revision    : 0
	
	Hardware        : Qualcomm MSM 8974 HAMMERHEAD (Flattened Device Tree)
	Revision        : 000b
	Serial          : 0000000000000000
	
**adb shell dumpsys battery**

得到电池信息.

	adb shell dumpsys battery

	Current Battery Service state:
		AC powered: false
		USB powered: true
		Wireless powered: false
		status: 2
		health: 2
		present: true
		level: 44		//当前电量.表示剩余44%
		scale: 100		//最大电量
		voltage: 3872
		temperature: 280
		technology: Li-poly



 



