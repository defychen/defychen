# Part 1. The first Android Code(第一行Android代码)

## Chapter 1 开始启程,第一行Android代码

### 1.1 Android的发展和历史

Android是由Andy Rubin创立的一个手机操作系统,后来被Google收购.

Android系统的底层是建立在Linux系统之上.Android平台由操作系统、中间件、用户界面和应用软件4层组成,采用被称为软件叠层(Software Stack)的方式进行构建.Software Stack结构使得层与层之间相互分离,保证层与层之间的低耦合性.

**Android的体系结构(由5部分构成)---由上到下划分**

1.应用程序层

包括一些Android的核心应用程序(e.g.电子邮件客户端、SMS程序、日历、地图、浏览器、联系人等).应用程序都是用Java编写.

2.应用程序框架

应用程序框架位于应用程序层之下,它提供大量的API供开发者调用来开发应用程序.

3.函数库

函数库位于应用程序框架之下,由应用程序框架来调用,应用程序不能直接调用函数库.

	一些重要的函数库:
	1.系统C库:即libc库,从BSF系统派生出来的标准C系统库.
	2.媒体库:基于PacketVideo的OpenCORE.用于支持播放和录制音视频格式以及查看静态图片.
		.包括:MPEG4, H.264, MP3, AAC, AMR, JPG, PNG等多媒体格式.
	3.Surface Manager:管理对显示子系统的访问,并提供对多个应用程序的2D和3D图层机提供无缝整合.
	4.LibWebCore:一个全新的Web浏览器引擎.该引擎为Android浏览器提供支持,也为WebView提供支持.
	5.SGL:底层的2D图形引擎.
	6.3D libraries:基于OpenGL ES 1.0 API实现的3D系统,这套3D库既可以使用硬件加速(硬件系统支持),
		也可以使用高度优化的软件3D加速.
	7.FreeType:位图和向量字体显示.
	8.SQLite:供所有应用程序使用的、功能强大的轻量级关系数据库.

4.Android运行时

Android运行时包括两部分:Android核心库集和Dalvik虚拟机.核心库集提供Jave语言核心库所有使用的大部分功能,Dalvik虚拟机则负责运行Android应用程序.

	每个Android应用程序都运行在单独的Dalvik虚拟机内(即每个Android应用程序对应一条Dalvik进程).
	Dalvik专门针对同时高效运行多个虚拟机进行了优化,方便对应用程序实现隔离.

Java JRV和Android运行时区别:

	1.Java中的JRE(Jave运行时)包括JVM(Java虚拟机)和其他功能函数库
		JVM虚拟机运行的是Jave字节码(.class文件).JVM直接从.class文件或JAR包中加载字节码然后运行.
	2.Android运行时包括Dalvik虚拟机和核心库集.
		Dalvik虚拟机运行的是专有的dex文件(Dalvik Executable文件).Dalvik需要通过DX工具将应用程序的所有
		.class文件编译成.dex文件,最终运行该.dex文件.

Dalvik虚拟机的特点:

	1.适合在移动终端上使用,不需要很快的CPU计算速度和大量的内存空间;
	2.运行专有的.dex文件.dex文件会减少.class文件中的冗余信息,而且会把所有的.class文件整合到一个文件中,
		从而提供运行性能;而且DX工具还会对.dex文件进行一定的性能优化.
	3.基于寄存器实现.大多数虚拟机(JVM)都是基于栈的,而Dalvik虚拟机基于寄存器实现.基于寄存器实现的虚拟
		具有更好的性能表现,但是硬件通用性较差.
	4.Dalvik虚拟机依赖于linux内核提供的核心功能(e.g.线程和底层内存管理)

5.Linux内核

Android系统建立在Linux 2.6之上.

### 1.2 Android的开发环境搭建

#### 1.2.1 Android开发所需软件介绍

**1. Andorid SDK**

Android SDK是Google提供的Android开发工具包,其中包括Android相关的API.在开发Android程序时,需要引入该工具包.

**2. Eclipse**

Eclipse是开发Android程序的IDE.Google官方也推出了Android Studio,是专门开发Android程序定制的IDE.

**3. ADT**

ADT(Android Development Tools):是Google提供的一个Eclipse插件,用于在Eclipse中提供一个Android开发环境.

安装了ADT,可以联机调试Android程序,模拟手机事件、分析程序性能等等.因为是插件,在Eclipse中在线安装即可.

#### 1.2.2 搭建开发环境

Google提供了一种简便方式,将Android SDK、Eclipse、ADT插件集成到一个SDK工具包.该工具包可在官网下载.

[SDK工具包下载地址](http://developer.android.com/sdk/)

下载好的SDK工具包包括:

	eclipse:包括Eclipse程序(且已经安装好了ADT插件).
	sdk:经过SDK Manager.exe下载好的内容会放在sdk这个目录(包括文档、原码、实例等).
	SDK Manager.exe:Android SDK管理器.双击可下载所需的Android SDK版本,然后进行安装.

Android模拟器的使用(用于模拟Android手机的行为)

	启动Android模拟器->弹出的"Android Virtual Device Manager"窗口选择"New"->
	在Create new Android Virtual Device(AVD)窗口中设置:
		AVD Name: 4.0(创建的虚拟设备的名字)
		Device: 选择3.2"xxx(3.2英寸的屏幕的手机)
		Target: Android 4.0xxx(Android 4.0版本)
		Memory Options: RAM:512(分配512 M的memory)
		SD Card: size:256 MiB(分配256 M的SD Card)
	->然后选择OK->点击"Start"->点击"Launch"就可以启动模拟器了.

### 1.3 第一个Android项目

#### 1.3.1 创建HelloWorld项目

	Eclipse的导航栏中->File->New->Android Application Project,弹出New Android Application对话框:
		Application Name(应用名称):Hello World --->该名称是应用在手机上显示的名称
		Project Name(项目名称):HelloWorld --->该名称是显示在Eclipse中(项目名通常不带空格)
		Package Name(包名):com.test.helloworld --->Android系统通过包名区分不同程序,因此报名必须唯一
		Minumum Required SDK:API 14:... --->程序最低兼容的版本
		Target SDK:API 19:... --->最高版本
		Comiple with:API 14:... --->指定程序使用哪个版本的SDK进行编译
		Theme: None --->程序UI所使用的主题(一般选择None即可)
	->Next->保持默认配置,点击Next->启动图标对话框,保持默认,点击Next->Create Activity对话框
		创建活动界面:选择Blank Activity(空活动类型)
	->点击Next->Blanck Activity对话框填写:
		Activity Name(活动名):HelloWorldActivity
		Layout Name(布局名):hello_world_layout
		Navigation Type(导航类型):None
	->Finish,即可创建成功.

#### 1.3.2 运行HelloWorld

**1.检查模拟器是否还在线**

	Eclipse导航栏->Window->Open Perspective->DDMS,进入到DDMS视图.查看Devices窗口是否存在Online设备
		1)Devices窗口有一个设备显示是Online,模拟器是在线的;
		2)如果窗口中没有设备,重新启动模拟器即可.
		3)如果窗口中有设备,但是显示为Offline(模拟器掉线了),选中设备右击->Reset adb即可.

**2.运行项目**

	点击Eclipse工具栏右侧Java选项回到之前视图->右击HelloWorld项目->Run As->Android Application
	->等待几秒钟,运行就会运行起来->在模拟器中也会存在一个"Hello World"的应用.

#### 1.3.3 分析Hello World程序

**Android目录结构:**

1.src:放置Java代码.刚才创建的HelloWorldActivity文件就在这里.

	HelloWorldActivity活动有如下代码:
		public class HelloWorldActivity extends Activity {
			//继承自Activity(extends),所有活动都继承自Activity
			
			@Override
			protected void onCreate(Bundle savedInstanceState) { //活动被创建时一定调用的方法
				super.onCreate(savedInstanceState);
				setContentView(R.layout.hello_world_layout);
				//给当前活动引入一个hello_world_layout布局
			}

			@Override
			public boolean onCreateOptionsMenu(Menu menu) { //用于创建菜单
				//Inflate the menu; this adds items to the action bar if it is present.
				getMenuInflater().inflate(R.menu.hello_world, menu);
				return true;
			}
			
		}

2.gen:自动生成.不需要修改.

3.assets:存放一些随程序打包的文件,程序运行时会动态读取这些文件.用的很少.

4.bin:编译时自动产生的文件.其中会有"*.apk"文件,为安装到手机上的应用程序.

5.libs:存放第三方的Jar包,在这个目录下的Jar包会自动添加到构建路径中去.

6.res:存放资源.子目录:drawable(存放图片)、layout(存放布局)、values(存放字符串)、menu(存放菜单文件).

	1.在res/layout目录下,有hello_world_layout.xml文件,有如下代码:
		<RelativeLayout xmlns:android="http://schemas.android.com/apk/res/android"
			xmlns:tools="http://schemas.android.com/tools"
			android:layout_width="match_parent"
			android:layout_heigth="match_parent"
			android:paddingBottom="@dimen/activity_vertical_margin"
			android:paddingLeft="@dimen/activity_horizontal_margin"
			android:paddingRight="@dimen/activity_horizontal_margin"
			android:paddingTop="@dimen/activity_vertical_margin"
			tools:context=".HelloWorldActivity" >

			<TextView //布局控件,用于在布局中显示文字
				android:layout_width="wrap_content"
				android:layout_height="wrap_content"
				android:text="@string/hello_world" />
				//引用values/strings.xml中的字符串定义.

		</RelativeLayout>
	2.字符串定义在res/values/strings.xml中:
		<resources>
			<string name="app_name">Hello World</string>
			//应用程序的名字.key:app_name;value:Hello World
			<string name="action_settings">Settings</string>
			<string name="hello_world">Hello world!</string>
			//键-值对应模式.hello_world为key;Hello world!为value
		</resources>
	
	3.引用方法
		1.在代码中通过"R.string.hello_world"来获得字符串
		2.在XML中通过"@string/hello_world"来获得字符串
		e.g.在HelloWorld项目中的图标引用.
		在AndroidManifest.xml中,通过android:icon="@drawable/ic_launcher"来获得.
			

7.AndroidManifest.xml:存放Android项目的配置文件,包括Activity活动注册.

	在AndroidManifest.xml有如下代码:
		<activity
			android:name="com.test.helloworld.HelloWorldActivity"
			android:label="@string/app_name" >
			<intent-filter>
				<action android:name="android.intent.action.MAIN" />
					//表示HelloWorldActivity是这个项目的主活动
				<category android:name="android.intent.category.LAUNCHER" />
					//表示点击应用图标,启动的就是这个活动
			</intent-filter>
		</activity>

	

8.project.properties:通过一行代码指定编译程序时所使用的SDK版本.

### 1.4 Android日志工具的使用

#### 1.4.1 添加LogCat到Eclipse

	Eclipse导航栏的Window->Show View->Other->弹出Show View对话框->展开Android目录
	->选中LogCat子项->点击OK即可.

#### 1.4.2 日志工具Log的使用

1.Log.v():打印级别为verbose(冗长的,累赘的)的信息.Android日志级别最低的一种.

2.Log.d():打印级别为debug.打印一些调试信息.

	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.hello_world_layout);
		Log.d("HelloWorldActivity", "onCreate execute");
		/*
			para1:tag,一般传入当前的类名即可,主要用于对打印信息进行过滤.
			para2:msg,想要打印的具体信息内容.
		*/	
	}

	添加之后重新运行项目.在LogCat中可以看到打印信息.

3.Log.i():打印级别为info.打印一些重要的数据信息.

4.Log.w():打印级别为warn.打印一些警告信息.

5.Log.e():打印级别为error.打印一些错误信息.

#### 1.4.3 Log的过滤器及级别的使用

**1.过滤器**

在LogCat窗口左边有"Saved Filters"可以设置过滤信息:

	添加一个过滤器"+"->设置过滤器相关信息:
		Filter Name:data	by Log Tag:data(此时只有Tag名字为data的才会打印出来)

**2.日志级别控制**

在LogCat窗口右边有个"日志级别控制"下拉列表.

***

## Chapter 2 活动(Activity)探究

### 2.1 活动介绍

活动(Activity):是一种可以包含用户界面的组件,主要用于和用户进行交互.一个应用程序可以包含1个/多个活动.

### 2.2 活动的基本用法

新建一个Android项目:

	项目名:ActivityTest
	报名:使用默认值"com.example.activitytest"
	Create Activity中:不勾选Create Activity,准备手动创建活动.

PS:关掉不相干的项目:右击HelloWorld项目->Close Project.

#### 2.2.1 手动创建活动

**1.src目录添加一个包**

此时ActivityTest项目的src目录为空,需要先添加一个包.

	Eclipse导航栏->File->New->Package->在弹出的窗口中填入默认包名"com.example.activitytest"
		->Finish.

**2.为包添加类**

	右击"com.example.activitytest"包->New->Class->弹出新建类的对话框:
		类名:FirstActivity	继承:Activity
		->Finish.

**3.在FirstActivity类中重写onCreate()方法**

	public class FirstActivity extends Activity {
		
		@Override
		protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState); //调用父类的onCreate()方法
		}
	}

#### 2.2.2 创建和加载布局

Android程序的设计讲究逻辑和视图分离,一个活动对应一个布局(布局是用来显示界面内容的).

**1.创建布局文件**

	右击res/layout目录->New->Android XML File->弹出创建布局文件的窗口(New Android XML File窗口)
		File:first_layout ->布局文件命名
		Root Element:选择LinearLayout ->根元素

创建完成后会出现一个"可视化布局编辑器"窗口,在左下方有两个切换卡.

	左边是:Graphical Layout
		当前的可视化布局编辑器,可以预览当前的布局,还可以通过拖曳方式编辑布局.
	右边是:first_layout.xml
		通过XML文件的方式来编辑布局.点击后具有如下代码:
		<LinearLayout xmlnx:android="http://schemas.android.com/apk/res/android"
			android:layout_width="match_parent"
			android:layout_heigth="match_parent"
			andorid:orientation="vertical" >
		</LinearLayout> //布局文件中已经有了LinearLayout元素

		添加按钮元素:
		<LinearLayout xmlnx:android="http://schemas.android.com/apk/res/android"
			android:layout_width="match_parent"
			android:layout_heigth="match_parent"
			andorid:orientation="vertical" >

			<Button
				android:id="@+id/button_1" //android:id是给当前元素定义一个唯一的标识符
				/*
					@id/button_1:是在XML中引用资源的语法.该句为引用id.
					@+id/button_1:是在XML中定义一个id.
				*/
				android:layout_width="match_parent"
				/*
					android:layout_width:指定当前元素的宽度.
					android:layout_width="match_parent":让当前元素和父元素一样宽.
				*/
				android:layout_height="wrap_content"
				/*
					android:layout_height:指定当前元素的高度.
					android:layout_height="wrap_content":表示当前元素的高度只要能刚好包含里面的内容就行.
				*/
				android:text="Button 1"
				/*
					android:text:指定元素中显示的文字内容.
				*/
				/>
		</LinearLayout> //布局文件中已经有了LinearLayout元素

**2.在活动中加载布局**

	public class FirstActivity extends Activity {
		
		@Override
		protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState); //调用父类的onCreate()方法
			setContentView(R.layout.first_layout);
			/*
				setContentView():参数一般为一个布局文件的id.
				项目中添加的任何资源都会在R文件中生成一个相应的资源id.
					引用该资源id的方法:R.layout.first_layout
			*/
		}
	}

#### 2.2.3 在AndroidManifest文件中注册

注册代码:

	<manifest xmlns:android="http://schemas.android.com/apk/res/android"
		package="com.example.activitytest"
		android:versionCode="1"
		android:versionName="1.0" >
		<uses-sdk
			android:minSdkVersion="14"
			android:targetSdkVersion="19" />
		<application
			android:allowBackup="true"
			android:icon="@drawable/ic_launcher"
			android:label="@string/app_name"
			android:theme="@style/AppTheme" >
			<activity //活动的注册要放在application标签内
				android:name=".FirstActivity"
				/*
					android:name:指定具体注册哪一个活动.
					此处的".FirstActivity":是"com.example.activitytest.FirstActivity"的缩写,
					前面的package属性执行了程序的包名"com.example.activitytest",注册活动时这部
					分可以省略.
				*/
				android:label="This is FirstActivity" >
				/*
					android:label:指定活动中标题栏的内容(标题栏显示在界面的最顶部).
					label也会成为启动器(Launcher)中应用程序显示的名称.
				*/
				<intent-filter>
					<action android:name="android.intent.action.MAIN" />
					<category android:name="android.intent.category.LAUNCHER" />
				/*
					固定写法,让FirstActivity成为这个程序的主活动.
				*/
				</intent-filter>
			</activity>
		</application>
	</manifest>

#### 2.2.4 隐藏标题栏

标题栏在屏幕最顶部,会占用屏幕空间,使得内容区域变小.一般会将其隐藏.

	public class FirstActivity extends Activity {
		
		@Override
		protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState); //调用父类的onCreate()方法
			requestWindowFeature(Window.FEATURE_NO_TITLE);
			/*
				在活动中不显示标题栏.必须在setContentView之前.
			*/
			setContentView(R.layout.first_layout);
			/*
				setContentView():参数一般为一个布局文件的id.
				项目中添加的任何资源都会在R文件中生成一个相应的资源id.
					引用该资源id的方法:R.layout.first_layout
			*/
		}
	}

#### 2.2.5 在活动中使用Toast

Toast是Android系统的一种提醒方式,在程序中可以使用它将一个短小的消息通知给用户,这些消息在一段时间后会自动消失,并且不会占用屏幕空间.

点击按钮后弹出一个Toast(Toast需要一个触发点):

	public class FirstActivity extends Activity {
		
		@Override
		protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState); //调用父类的onCreate()方法
			requestWindowFeature(Window.FEATURE_NO_TITLE);
			/*
				在活动中不显示标题栏.必须在setContentView之前.
			*/
			setContentView(R.layout.first_layout);
			/*
				setContentView():参数一般为一个布局文件的id.
				项目中添加的任何资源都会在R文件中生成一个相应的资源id.
					引用该资源id的方法:R.layout.first_layout
			*/
			Button button1 = (Button)findViewById(R.id.button_1);
			/*
				findViewById():通过资源id获取在布局文件中定义的元素.
				findViewById()返回的是一个View对象,要转成Button对象.
			*/
			button1.setOnClickListener(new OnClickListener() {
				/*
				button1.setOnClickListener():注册一个监听器.
				new OnclickListener() {xxx}:表示实例化一个监听器.内部的代码重写了
					监听器的onClick()方法.点击按钮时就会执行onClick()方法.
				*/
				@Override
				public void onClick(View v) {
					Toast.makeText(FirstActivity.this, "You clicked Button 1",
						Toast.LENGTH_SHORT).show();
					/*
						Toast.makeText():Toast的静态方法.通过静态方法创建一个Toast对象.
						para1:Toast的上下文(Context),由于活动对象本身就是一个Context对象,
							此处传入FirstActivity.this即可;
						para2:Toast显示的文本内容;
						para3:Toast显示的时长.
							Toast.LENGTH_SHORT ->短时长;
							Toast.LENGTH_LONG  ->长时长.
					*/
				}
			});
		}
	}

***

# Part 2. Andriod Practical Skills

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

