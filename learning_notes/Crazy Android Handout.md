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

**adb shell screencap -p**

Andriod手机的截图命令

	adb shell screencap -p /sdcard/screen.png //截图并保存为手机中的"/sdcard/screen.png"
	adb pull /sdcard/screen.png . //将手机中的图片拷贝到电脑的"."当前目录
	adb shell rm /sdcard/screen.png //删除手机中的图片

**adb shell input swipe src_x src_y tgt_x tgt_y m_time**

滑动手势解锁:起点(src_x, src_y);终点(tgt_x, tgt_y);滑动时间(m_time(ms))

	//滑动
	adb shell input swipe 100 100 200 200 300 //从(100, 100)经过300ms滑动到(200, 200)
	//长按
	adb shell input swipe 100 100 100 100 1000 //在(100, 100)的位置长按1000ms

## 2. dpi、dip、分辨率、屏幕尺寸、px、density关系及换算

### 2.1 概念

**dpi(dot per inch):每英寸的像素数(unit: px/inch),也叫屏幕密度.**

dpi越大,屏幕越清晰(e.g.iPhone 5S的dpi是326; Samsung Note3的dpi是386).

android默认的只有3个dpi:low(120 px/inch); medium(160 px/inch); high(240 px/inch).default值为160.但现在手机一般不会取这种标准值(比如上述的iPhone和Samsung).

计算:

	比如一部手机屏幕4 寸,分辨率:480 * 800, dpi?
	1.对角线的像素个数: sqrt(480^2 + 800^2) = 933
	2.对角线的dpi: 933 / 4 = 233 px/inch
	3.density为: (233 px/inch) /  (160 px/inch) = 1.46
	4.dip为: dip = density px = 1.46 px.

**dip(Density independent pixels):设备无关像素.也有时候叫dp.**

dip一般作为手机的布局单位(一般不直接选择1 px作为单位).

	1.可以认为160 px/inch是一个标准的dpi(其他的以此作为参考);
	2.标准的px的长度为: 1/160 (inch/px);
	3.其他非标准的px的长度(e.g. dpi=320 px/inch).此时长度为: 1/320 (inch/px);
	为了让显示的长度为标准值,选用dip作为单位.上述非标准的手机的dip:
		dip = 2 px--->2 * 1/320 = 1/160(刚好为标准的px长度).

dip = (dpi(px/inch) / 160(px/inch))px = density px

	在实际应用中,相同尺寸的不同手机会存在不同的dpi(e.g.320 px/inch和160 px/inch),也就是对应的px大小不同.
	1.如果在设计应用中选择px作为单位,同一款软件在相同尺寸的不同手机上显示的效果不一样(因为软件的长宽就会不一样).
		(e.g.画2 px长度的Button,在高屏幕密度的手机里就会显示的比较小(因为px小)).
	2.如果选择dip作为单位,两款手机的dip分别为:2 px和1 px(两款手机的px大小比例为1:2).
		(e.g.此时画2 dip长读的Button,两款手机的显示大小会是一样的)

**分辨率(Resolution)**

分辨率是指屏幕上垂直方向和水平方向上的像素个数.(e.g. iPhone 5S的分辨率是1136x640; Samsung Note3的分辨率是1920x1080).

**屏幕尺寸(screen size)**

平常讲的手机屏幕大小,指的是屏幕的对角线长度(单位为inch(英寸)).(e.g. iPhone 5S的屏幕尺寸为4 inch;Samsung Note3的是5.7 inch).

**像素(pixel)**

描述图像的单位(有大小之分).

**density**

其值等于(dpi / (160 px/inch)).作为dip计算的值,后面再加上单位(px)即是dip.

	比如dpi=320 px/inch:其density为: 320/160 = 2; dip = 2 px.

density常用取值为:0.75, 1, 1.5, 2, 

