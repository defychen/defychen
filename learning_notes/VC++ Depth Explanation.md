# VC++ Depth Explanation

## Chapter 1 Windows程序内部运行机制

### 1.1 API与SDK

API:Application Programming Interface---应用程序编程接口;

	Windows.h---包含编写Windows应用程序主要的Windows API函数

SDK:Software Development Kit---软件开发包.

### 1.2 窗口与句柄

窗口通过窗口句柄(HWND)来标识.

此外还有图标句柄(HICON)、光标句柄(HCURSOR)、画刷句柄(HBRUSH).

### 1.3 消息与消息队列

在Windows中,用户程序可以调用系统的API函数(e.g.fopen库函数打开文件,最终是调用操作系统提供的函数来打开文件).同时系统也可以调用用户程序(该调用是通过消息进行的).

系统调用用户程序:该用户程序也称窗口过程函数,主要用于消息处理.比如用户在窗口中画图的时候,按下鼠标左键.此时,操作系统会感知这一事件,将这一事件包装成一个消息,投递到应用程序的消息队列中.接着系统会自动调用窗口过程函数对消息队列中的消息一一进行响应处理.

**1.消息---MSG结构体来表示**

	typedef struct tagMSG {
		HWND	hwnd;		//消息所属窗口,一个消息都是与某个具体的窗口相关联的
		UINT	message;	//消息的标识符,标识具体消息.消息都是由宏定义的数值来区分.
			//e.g.WM_LBUTTONDOWN(Window Message):表示鼠标左键按下消息,其值为0x0201
			//WM_KEYDOWN:键盘按下; WM_CHAR:字符消息.
		WPARAM	wParam;		//消息附加信息.
		LPARAM	lParam;		//消息附加消息.和wParam配合表示标识的消息信息e.g.用户具体输入的字符
		DWORD	time;		//标识消息投递到消息队列的时间
		POINT	pt;			//标识消息投递到消息队列时鼠标的位置
	}MSG;

**2.消息队列**

消息队列用于存放程序所创建的所有消息.

消息按类型划分为:

1.进队消息:消息由系统投递到消息队列中,并最终由窗口过程函数进行处理.

2.不进队消息:消息直接由系统调用窗口过程进行处理.

### 1.4 WinMain函数

WinMain函数式Windows程序的入口点函数,与DOS程序的入口点函数main函数作用相同.WinMain函数结束或返回,Windows应用程序结束.

**一个实例的步骤---创建一个窗口,并在该窗口中响应键盘及鼠标消息**

	step 1:WinMain函数的定义;
	step 2:创建一个窗口;
	step 3:进行消息循环;
	step 4:编写窗口过程函数---用于处理消息

#### 1.4.1 WinMain函数的定义

WinMain函数原型:

	int WINAPI WinMain(
		HINSTANCE hInstance;	//表示当前运行中的程序的实例句柄.
				//其实就是系统分配给每个运行中的程序一个值.类似于linux的PID.
		HINSTANCE hPrevInstance;	//当前实例的前一个实例的句柄.一般为NULL
		LPSTR	lpCmdLine;	//传递给应用程序的命令行参数.
		int nCmdShow;		//制定程序窗口如何显示(最大化、最小化、隐藏等).
				//该参数不用理会,后续设计窗口时会指定
	);

#### 1.4.2 创建一个窗口

创建一个窗口的步骤:

	1.设计一个窗口类
	2.注册窗口类
	3.创建窗口
	4.显示及更新窗口

**1.设计一个窗口类**

设计窗口类主要是指定一些窗口的特征.窗口类由WNDCLASS结构体描述:

	typedef struct _WNDCLASS {
		UINT	style;	//指定窗口类样式.其值可取为:CS_HREDRAW---当窗口水平方向盘上宽度发生变化时,
			//重绘整个窗口;CS_VREDRAW---垂直方向高度发生变化重绘整个窗口;CS_NOCLOSE---窗口没有关闭
			//按钮;CS_DBCLICKS---双击鼠标时发送鼠标双击消息.CS:Class style.多个取"|"运算.
		WNDPROC	lpfnWndProc;	//函数指针,指向窗口过程函数.
		int		cbClsExtra;	//窗口类类附加内存.一般设为0即可
		int		cbWndExtra;	//窗口类窗口附加内存.一般设为0即可
		HANDLE	hInstance;	//当前运行程序的实例句柄.赋为WinMain函数传进来的hInstance即可
		HICON	hIcon;		//窗口类的图标句柄.如果成员为NULL,系统将会提供一个默认的图标
		HCURSOR	hCursor;	//窗口类的光标句柄.一般使用LoadCursor(...)返回值赋值
		HBRUSH	hbrBackground;	//窗口类的背景画刷句柄.即窗口发生重绘时,系统使用这里指定的画刷
				//来擦除窗口的背景
		LPCTSTR	lpszMenuName;	//是一个空终止的字符串,指定菜单资源的名字.如果为NULL,则窗口没有
				//默认的菜单
		LPCTSTR	lpszClassName;	//是一个空终止的字符串,指定窗口类的名字.赋值一个字符即可
				//e.g.将某种窗口类型命名为"defychen".
	}WNDCLASS;

1.窗口过程函数

是一个回调函数.回调函数不是由函数的实现方直接调用,而是在特定的事件或者条件发生时由另外一方调用,用于对该事件或条件进行相应(在WinMain中用于对消息事件的相应).

	回调函数实现机制及Windows中的实现
	1.定义一个回调函数;
		->定义一个窗口过程函数.
	2.提供函数实现的一方在初始化的时候,将回调函数的函数指针注册给调用者;
		->在设计窗口类时,将窗口过程函数的函数指针赋值给lpfnWndProc成员变量.在之后调用
			RegisterClass(&wndclass)注册窗口类时,系统就有了所编写的窗口过程函数的地址.
	3.当特定的事件或条件发生的时候,调用者使用函数指针调用回调函数对事件进行处理.
		->当应用程序接收到某一个窗口消息时,调用DispatchMessage(&msg)将消息回传给系统.
			系统则利用注册窗口类时的窗口过程函数指针,调用窗口过程函数对消息进行处理.

窗口过程函数的函数定义原型:

	typedef LPESULT (CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	/*
		LRESULT--->实际上是long类型
		CALLBACK--->实际上是__stdcall
		PS:自己定义的窗口过程函数格式必须与WNDPROC相同.
	*/

2.LoadIcon函数加载图标资源---用于赋值给窗口类的图标句柄

	HICON LoadIcon(HINSTANCE hInstance, LPCTSTR lpIconName);
	/*
		para1:加载标准图标时,为NULL.加载自己制作的图标资源时--->需要百度
		para2:实际为CONST CHAR*(字符常量的指针).图标ID是一个整数,需要MAKEINTRESOURCE宏将资源ID
			标识符转换为需要的LPCTSTR类型.标准图标有:IDI_ERROR...
		retval:返回系统分配给某图标的句柄.可以赋值给窗口类的图标句柄.
	*/

3.LoadCursor函数加载光标资源---用于赋值给窗口类的光标句柄

	HCURSOR LoadCursor(HINSTANCE hInstance, LPCTSTR lpCursorName);
	//与LoadIcon相似.标准光标有:IDC_CROSS

4.GetStockObject函数得到系统的标准画刷---用于赋值给窗口类的hbrBackground

	HGDIOBJ GetStockObject(int fnObject);
	/*
		para:制定获取对象的类型.e.g.BLACK_BRUSH--->黑色画刷
		retval:返回多种资源对象的句柄.HGDIOBJ实际为void *,在实际使用时,需要进行类型转换.
		e.g.为hbrBackground成员指定一个黑色画刷的句柄,即用黑色画刷擦除窗口背景.
		wndclass.bhrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	*/

**2.注册窗口类**

将设计的窗口类注册进系统.

	ATOM RegisterClass(CONST WNDCLASS *lpWndClass);
	//para:上一步骤所设计的窗口对象指针

**3.创建窗口---CreateWindow函数**

	HWND CreateWindow(
		LPCTSTR lpClassName,	//窗口类的名称---"defychen"和WNDCLASS中的相同
		LPCTSTR lpWindowName,	//窗口名字.窗口名字会显示在标题栏.
		DWORD dwStyle,	//具体创建的窗口样式.在WNDCLASS中的窗口类样式会应用到所有由
			//该类创建的窗口,此处的窗口样式是指定某个具体的窗口的样式.
		int x,	//若为CW_USEDEFAULT:系统为窗口选择默认左上角,并忽略y参数
		int y,	//指定窗口左上角的x,y坐标.以及窗口的宽度nWidth,高度nHeight
		int nWidth,	//若为CW_USEDEFAULT:系统为窗口选择默认的宽度和高度,并忽略nHeight参数
		int nHeight,
		HWND hWndParent,	//指定父窗口句柄,一般为NULL
		HMENU hMenu,	//指定窗口菜单句柄,一般为NULL
		HANDLE hInstance,	//当前运行中的程序的实例句柄.
		LPVOID lpParam	//附加参数.多数窗口设置为NULL
	);
	//retval:成功返回系统为该窗口分配的句柄;失败返回NULL

窗口样式类型---WS_OVERLAPPEDWINDOW

	#define WS_OVERLAPPEDWINDOW	(WS_OVERLAPPED	| \		//产生一个层叠的窗口
		WS_CAPTION	| \		//创建一个有标题栏的窗口
		WS_SYSMENU	| \		//创建一个在标题栏有系统菜单的窗口,要与WS_CAPTION一起使用
		WS_THICKFRAME	| \	//创建一个具有可调边框的窗口
		WS_MINIMIZEBOX	| \ //创建一个具有最小化按钮的窗口,必须同时设定WS_SYSMENU
		WS_MAXIMIZEBOX	| \ //创建一个具有最大化按钮的窗口,必须同时设定WS_SYSMENU
		)

**4.显示及更新窗口**

1.显示窗口---ShowWindow

	BOOL ShowWindow(
		HWND hWnd;	//CreateWindow返回的窗口句柄
		int nCmdShow;	//指定窗口显示状态
		/*常用的状态:
			SW_HIDE:隐藏窗口并激活其他窗口;
			SW_SHOW:在窗口原来的位置以原来的尺寸激活并并显示窗口;
			SW_SHOWMAXIMIZED:激活窗口并最大化显示;
			SW_SHOWMINIMIZED:激活窗口并最小化显示;
			SW_SHOWNORMAL:正常显示---第一次显示窗口时应设为该值.
		*/
	);

2.更新窗口---UpdateWindow

在调用ShowWindow之后,需要紧接着调用UpdateWindow来刷新窗口.

	BOOL UpdateWindow(
		HWND hWnd;	//CreateWindow返回的窗口句柄
		//UpdateWindow函数通过发送一个WM_PAINT消息来刷新窗口.UpdateWindow会将WM_PAINT消息直接
		//发送给窗口过程函数进行处理,不会放入到消息队列---这样是为了更快做出相应
	);

#### 1.4.3 消息循环

消息循环:不断的从消息队列中取出消息---while循环+GetMessage()函数.取出的消息自动会由窗口过程函数响应.

GetMessage()---从消息队列中取出消息

	BOOL GetMessage(
		LPMSG lpMsg,	//消息(MSG)结构体,从消息队列中取出的消息信息会保存在该结构体中
		HWND hWnd,		//指定接受属于哪个窗口的消息.一般设为NULL,接受所有窗口的窗口消息
		UINT　wMsgFilterMin,	//指定获取消息的最小值,一般设为0即可
		UINT wMsgFilterMax	//指定获取消息的最大值,和前一个同时设为0表示接受所有消息
	);
	/*retval:
		0--->接收到WM_QUIT消息;
		非0值--->接收到除WM_QUIT消息;
		-1--->出错
	*/

**一般编写的消息循环代码如下:**

	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))	//此处只有WM_QUIT消息才会退出,否则为一种死循环
	{
		TranslateMessage(&msg);	//将虚拟键消息转换为字符消息,并会重新投递到消息队列中
		DispatchMessage(&msg);	//分派一个消息到窗口过程,由窗口过程对消息进行处理.
			//DispatchMessage实际是将消息回传给OS,由OS调用窗口过程对消息进行处理
	}

Windows应用程序的消息处理机制:

![](https://i.imgur.com/GvV1Qd4.png)

1.OS接收到应用程序的窗口消息,将消息投递到该应用程序的消息队列中;

2.应用程序在消息循环中调用GetMessage从消息队列中取出一条一条消息,并对消息进行一些预处理.e.g.调用TranslateMessage(&msg)产生新的消息或者直接放弃对某些消息的相应;

3.应用程序调用DispatchMessage(&msg),将消息回传给OS;

4.OS利用WNDCLASS结构体的lpfnWndProc成员保存的窗口过程函数的指针调用窗口过程函数对消息进行处理.

	PS:
	从消息队列中取消息的另外的函数:PeekMessage;发送消息:SendMessage、PostMessage.

#### 1.4.4 编写窗口过程函数

窗口过程函数:处理发送给窗口的消息.

窗口过程函数的声明形式:

	LRESULT CALLBACK WindowProc(	//只能是函数的名字任意,其他必须一样
		HWND hwnd,	//消息的窗口句柄,标识接收消息的特定窗口
		UINT uMsg,	//消息
		WPARAM wParam,	//消息的附加参数
		LPARAM lParam	//消息的附加参数
	);
	//窗口过程函数的名字可以任意,但是其他的必须一致.是因为在设计窗口类时会将窗口过程函数的地址(即指针)赋值给WNDCLASS
	//结构体的lpfnWndProc,系统调用窗口过程函数是通过该地址(指针)来调用,而不是名字.

**窗口过程函数实例**

	LRESULT CALLBACK WinSunProc(
		HWND hwnd,		//handle to window
		UINT uMsg,		//message identifier
		WPARAM wParam,	//first message parameter
		LPARAM lParam,	//second message parameter
	)
	{
		switch(uMsg)	//一般使用switch/case语句确定接收的是什么消息以及如何处理
		{
		case WM_CHAR：	//字符消息.消息是以WM开头
			char szChar[20];
			sprintf(szChar, "char code is %d", wParam);	//wParam存放字符的ASCII码值
			MessageBox(hwnd, szChar, "char", 0);	//弹出一个消息框
			/*
				para1:窗口句柄;	para2:消息框中显示的字符;	para3:标题栏的名字;
				para4:供用户的选择项.
					0--->没有选择项
					MB_YESNO--->需要用于选择yes or no?
				retval:由para4决定
					para4为0--->不需要返回
					para4为MB_YESNO--->有返回值IDYES或者IDNO
			*/
			break;
		case WM_LBUTTONDOWN:	//左键按下
			MessageBox(hwnd, "mouse clicked", "Message", 0);
			HDC hdc;	//DC(Device Context):设备描述表.DC是一个包含设备信息的结构体,Windows平台下所有的图形操作都是
						//利用DC来完成,然后由DC映射到这些物理设备上.HDC为DC的句柄,可以更方便的操作图形资源
			hdc = GetDC(hwnd);	//得到与该窗口对应的DC句柄
			TextOut(hdc, 0, 50, "Programmer Family", strlen("Programmer Family"));
			/*	TextOut:利用DC句柄在指定位置输出一行文字
				para1:DC句柄;	para2,3:x,y坐标.
				para4:需要输出的文字;		para5:输出文字的长度.
			*/
			ReleaseDC(hwnd, hdc);	//释放DC句柄
			/*
				para1:窗口句柄;	para2:DC句柄
			*/
			break;
		case WM_PAINT:	//重新绘制窗口消息.当窗口刚创建、窗口尺寸被改变、最小化后再恢复、被其他窗口遮盖后再显示等,
						//系统均会发出WM_PAINT消息(包括调用UpdateWindow函数)
			HDC hDC;	//DC句柄
			PAINTSTRUCT ps;	//该结构体用于接收绘制的信息,主要用在WM_PAINT中
			hDC = BeginPaint(hwnd, &ps);	//在WM_PAINT中需要使用BeginPaint函数得到DC的句柄.
											//该函数只在WM_PAINT中使用
			/*
				para1:窗口句柄;		para2:PAINTSTRUCT结构体的指针,用于接收绘制的信息
				//在调用BeginPaint时,如果客户区的背景没有被擦除,BeginPaint会发送WM_ERASEBKGGND消息给窗口,
				//系统就会使用WNDCLASS结构体中的hbrBackground成员指定的画刷来擦除背景
			*/
			TextOut(hDC, 0, 0, "Programmer Family", strlen("Programmer Family"));
			EndPaint(hwnd, &ps);	//释放DC句柄
			/*
				para1:窗口句柄;		para2:PAINTSTRUCT结构体的指针
			*/
			break;
		case WM_CLOSE:	//当单击窗口上的关闭按钮时,系统将会给应用程序发送一条WM_CLOSE消息
			if(IDYES == MessageBox(hwnd, "Is it really over?", "Message", MB_YESNO))
			{
				DestroyWindow(hwnd);	//销毁窗口
				//DestroyWindow销毁窗口后会向窗口过程发送WM_DESTROY消息.窗口被销毁了但是应用程序不会退出
				//如果应用程序没有对WM_CLOSE消息进行相应,系统会将该消息传给DefWindowProc(默认的窗口过程),
				//DefWindowProc也会调用DestroyWindow函数来相应该消息
			}
			break;
		case WM_DESTROY:	//捕获窗口被销毁的消息
			PostQuitMessage(0);		//往消息队列中投递WM_QUIT消息.
						//GetMessage只有在收到WM_QUIT消息才会返回0,此时消息循环才结束,程序退出
			/*
				PostQuitMessage的参数将作为WM_QUIT消息的wParam参数,这个值通常用作WinMain函数的返回值.
				因此一般是0.
			*/
			break;
		default:	//对于没有覆盖的消息,调用默认的窗口过程函数进行处理
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
		return 0;
	}

### 1.5 Windows程序实例

在创建好Project和File(C++源代码文件)之后,在File中写入代码:

	/*****************WinMain.cpp******************/
	#include <windows.h>	//windows程序的头文件
	#include <stdio.h>

	LRESULT CALLBACK WinDefyProc(	//窗口过程函数声明.这个函数可以直接从MSDN中copy出来,改一下名字即可
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam
	);

	int WINAPI WinMain(		//WinMain函数,该函数也可以从MSDN中copy出来
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpCmdLine,
		int nCmdShow
	)
	{
		//1. 设计一个窗口类
		WNDCLASS wndcls;
		wndcls.cbClsExtra = 0;
		wndcls.cbWndExtra = 0;
		wndcls.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wndcls.hCursor = LoadCursor(NULL, IDC_CORSS);
		wndcls.hIcon = LoadIcon(NULL, IDI_ERROR);
		wndcls.hInstance = hInstance;	//当前运行的应用程序实例句柄
		wndcls.lpfnWndProc = WinDefyProc;	//窗口过程函数指针
		wndcls.lpszClassName = "defy2017";	//窗口类名字
		wndcls.lpszMenuName = NULL;		//菜单资源的名字,一般为NULL即可
		wndcls.style = CS_HREDRAW | CS_VREDRAW;	//窗口类样式
		
		//2. 注册一个窗口类
		RegisterClass(&wndcls);
		
		//3. 创建窗口
		HWND hwnd;
		hwnd = CreateWindow("defy2017", "Hi, defy", WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, 
					NULL, NULL, hInstance, NULL);

		//4. 显示及刷新窗口
		ShowWindow(hwnd, SW_SHOWNORMAL);
		UpdateWindow(hwnd);

		//5. 消息循环
		MSG msg;
		while (GetMessage(&msg, NULL, 0, 0))
			//para2必须为NULL.否则当当前销毁窗口后窗口句柄变为无效值,GetMessage会返回-1
			//GetMessage()接收到WM_QUIT消息会返回0,此时退出.由PostQuitMessage(0)发出
		{
			TranslateMessage(&msg);		//也就是将不能处理的消息转换一下
			DispatchMessage(&msg);
		}

		return msg.wParam;
	}
	
	//窗口过程函数---相当于新的线程
	LRESULT CALLBACK WinDefyProc(
		HWND hwnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lPARAM
	)
	{
		switch(uMsg)	//switch...case处理消息
		{
		case WM_CHAR:	//接收到字符消息,也就是键盘按下某个字符
			char szChar[20];
			sprintf(szChar, "char code is %d", wParam);
			MessageBox(hwnd, szChar, "char", 0);
			break;
		case WM_LBUTTONDOWN:	//鼠标左键按下
			MessageBox(hwnd, "Mouse clicked", "Message", 0);
			HDC hdc;	//DC句柄
			hdc = GetDC(hwnd);
			TextOut(hdc, 0, 50, "Programmer family", strlen("Programmer family"));
			ReleaseDC(hwnd, hdc);	//释放DC句柄
			break;
		case WM_PAINT:
			HDC hDC;	//不能与上述的hdc同名
			PAINTSTRUCT ps;
			hDC = BeginPaint(hwnd, &ps);	//只能使用BeginPaint获得DC句柄
			TextOut(hDC, 0, 0, "Hi, defy", strlen("Hi, defy")):
			EndPaint(hwnd, &ps);	//释放DC句柄,填写这两个参数会自动释放DC句柄
			break;
		case WM_CLOSE:
			if (IDYES == MessageBox(hwnd, "Is it really close?", "Message", MB_YESNO))
			{
				DestroyWindow(hwnd);
			}
			break;
		case WM_DESTROY:	//销毁窗口消息
			PostQuitMessage(0);	//发送WM_QUIT消息退出消息循环
			break;
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);	//默认窗口过程
		}
		return 0;
	}
***
## Chapter 2 掌握C++

C++相比C的优点:

1.封装性(Encapsulation):把数据和操作数据的函数组织在一起,使得程序结构紧凑,提高类内部数据的安全性;

2.继承性(Inheritance):增加了软件的可扩充性和代码的重用性;

3.多态性(Polymorphism):设计程序时可以对问题更好的抽象,有利于代码的维护和可重用.

### 2.1 结构体与类

**C和C++的结构体特性---结构体都是public,都可以访问.**

	1.C语言的结构体能包含一些变量(包括普通变量、数组、指针等)和一些函数指针.不能明确声明一个函数
		struct test {
			struct test *next;	//指针
			int type;			//普通变量
			int name[16];		//数组
			int (*attach)(void);	//函数指针
		};
	2.C++结构体处理有C语言的特性,还可以包含函数
		#include <iostream.h>	//C++的标准输入输出头文件,类似于C的stdio.h
		struct point {
			int x;
			int y;
			void output(void)	//C++的结构体可以包含函数
			{
				cout << x << endl << y << endl;
				/*
					cout:标准输出,与输出操作符"<<"一起用于输出数据到标准输出上;
					cin:标准输入,与输入操作符">>"一起用于从标准输入读入数据;
					cerr:标注错误输出,与输出操作符"<<"一起用于输出错误信息到标准输出上.
					endl:end of line,表示换行,类似于C语言的"\n".
				*/
			}
		};

		void main()
		{
			point pt;
			pt.x = 0;	//结构体中的所有成员(变量和函数)都是public,在struct外面都可以访问到
			pt.y = 0;
			pt.output();
		}

**C++的类**

类定义:

	class point		//类定义的关键字.
	{
		int x;		//类中的成员默认是private(私有的)
		int y;
		void output(void)
		{
			cout << x << endl << y << endl;
		}
	};	//类的定义与结构体类似

	void main()
	{
		point pt;
		pt.x = 0;	//在类外访问类的私有成员(变量或者函数)会报错.
		pt.y = 0;	//在类外访问类的私有成员(变量或者函数)会报错.
		pt.output();	//在类外访问类的私有成员(变量或者函数)会报错.
	}

### 2.2 C++特性

#### 2.2.1 类与对象

类是描述一类事物以及事物所具有的属性.对象是类的一个实例.

#### 2.2.2 构造函数

构造函数:用来对类中的成员变量进行初始化.

特点:构造函数的名字与类名相同,且没有返回值.可以带参数也可以不带参数.

	#include <iostream.h>
	class point
	{
		public:	//声明下面的成员为public,因此可以在类之外访问
			int x;
			int y;
			point()		//point类的构造函数
			{
				x = 0;
				y = 0;
			}
			void output()
			{
				cout << x << endl << y << endl;
			}
	};

	void main()
	{
		point pt;	//会调用point的构造函数进行初始化
		point.output();		//调用point的成员函数
	}

**默认构造函数:**

1.如果一个类中没有定义任何的构造函数,C++编译器会在某些情况下为该类提供一个默认的不带参数的构造函数.

	提供默认构造函数的情况(前提类没有定义任何的构造函数):
	1.如果类有虚拟成员函数或虚拟继承父类(即有虚拟基类)时,会有默认的构造函数;
	2.如果类的基类有构造函数(用户定义或者默认构造函数),其子类会有默认构造函数;
	3.如果类中有非静态的对象数据成员,会提供默认的构造函数.

2.如果类中定义了构造函数,C++编译器不会再提供默认的构造函数.构造函数可以自己定义有多个,其参数不一样就行.

#### 2.2.3 析构函数

析构函数:当一个对象的生命周期结束时,析构函数会被自动调用,从而释放这个对象所占有的资源.

析构函数形式:

	~类名()---无参数,无返回值,且一个类中只有一个析构函数.

**实例:**

	class Student
	{
		private:	//private成员
			char *pName;
		public:		//public成员
			Student()	//构造函数
			{
				pName = new char[20];	//C++申请内存的方式.new 类型[size]---堆上分配
			}
			~Student()	//析构函数
			{
				delete[] pName;		//C++释放内存的方恨死.delete[] 指针;
			}
	};

**类中定义成员变量时,不能直接给成员变量赋初值:**

	class point
	{
		int x = 0;	//错误,定义成员变量时,不能给成员变量赋初值
		int y;
	};

#### 2.2.4 函数的重载

	#include <iostream.h>
	class point
	{
		public:
			int x;
			int y;
			point()
			{
				x = 0;
				y = 0;
			}
			point(int a, int b)		//多个构造函数,相当于是函数的重载
			{
				x = a;
				y = b;
			}
			void output()
			{
				cout << x << endl << y << endl;
			}
	};
	void main()
	{
		point pt(5, 5);	//构造类对象时传入参数,调用对应参数的构造函数构造对象
		pt.output();	//得到5	5
	}

**重载条件:函数参数类型、参数个数不同.有歧义的函数也不能构成重载.**

	void output()和int output()不构成重载.此处是返回值不同,不满足条件;
	void output(int a, int b =5)和void output(int a)不构成重载.因为有歧义.

#### 2.2.5 this指针

	#include <iostream.h>
	class point
	{
		public:
			int x;
			int y;
			point()
			{
				x = 0;
				y = 0;
			}
			point(int a, int b)
			{
				x = a;
				y = b;
			}
			void output()
			{
				cout << x << endl << y << endl;
			}
			void input(int x, int y)
			{
				x = x;	//由于形参与成员变量名相同,此时成员变量在该函数中不可见.
				y = y;	//解决办法,形参与成员变量名不相同(形参x,y改为a, b即可).还可以使用this指针
			}
	};

	void main()
	{
		point pt(5, 5);	//构造一个对象.此时x=5,y=5
		pt.input(10, 10);	//由于成员变量与形参同名.成员变量不可见.因此该函数是x对自己赋值.
							//没有真正操作到pt对象的成员变量
		pt.output();	//输出为:5 5
	}

**this指针是一个隐含的指针,指向对象本身,代表对象的地址.一个类声明的所有对象调用的成员函数都是在同一处代码段,但是成员变量每个对象都维护自己单独的.**

	//在上例中,对象调用pt.input(10, 10)时,其成员函数除了接受2个实参外,还接收到了pt对象的地址
	//(即this指针,this=&pt).因此对成员变量的访问都被隐含的加上了前缀this->.
	//e.g.point pt(5, 5)->声明对象,此时调用point(int a, int b).
	//对成员的访问:x = a,实际为:this->x = a.表示该对象的x成员变量的访问.
	
	//上例可以改写为:
	void input(int x, int y)
	{
		this->x = x;		//this->x:明确指明对象的x成员变量.此时就不会被覆盖
		this->y = y;		//this->y:明确指明对象的y成员变量.此时就不会被覆盖
	}
	
#### 2.2.6 类的继承

**1.继承**

派生类(Derived class---子类)从基类(Base class---也叫父类)继承,可以继承基类的成员变量和成员方法.

	#include <iostream.h>
	class animal
	{
		public:		//声明为public成员变量或函数
			animal()	//构造函数
			{
				cout << "animal construct" << endl;
			}
			~animal()	//析构函数
			{
				cout << "animal destruct" << endl;
			}
			void eat()
			{
				cout　<< "animal eat" << endl;
			}
			void sleep()
			{
				cout << "animal sleep" << endl;
			}
			void breathe()
			{
				cout << "animal breathe" << endl;
			}
	};

	class fish:public animal	//fish类继承自animal类.":"继承,"public":公有继承,紧接着是类名
	{	//继承了animal类的成员变量和成员方法
		public:
			fish()	//派生类的构造函数.先调用父类的构造函数,再调用子类的构造函数
			{
				cout << "fish construct" << endl;
			}
			~fish()	//派生类的析构函数.先将子类析构,再将父类析构
			{
				cout << "fish desctruct" << endl;
			}
	};

	void main()
	{
		animal an;	//构造基类对象
		fish fh;	
		/*
		打印得到:
		animal construct	//父类先构造
		fish construct		//子类再构造
		fish desctruct		//子类先析构
		animal destruct		//父类再析构
		*/
		//an.eat();
		//fh.eat();
	}

**2.子类中调用父类带参数的构造函数** 

	#include <iostream.h>
	class animal
	{
		public:		//声明为public成员变量或函数
		+	animal(int height, int weight)	//带参数的构造函数构造函数
		+	{
		+		cout << "animal construct" << endl;
		+	}
			...
	};

	class fish:public animal	//fish类继承自animal类.":"继承,"public":公有继承,紧接着是类名
	{	//继承了animal类的成员变量和成员方法
		public:
			fish()	//子类没有声明使用父类带参数的构造函数,因此还是会使用父类的默认构造函数.
			{		//但此时父类只有一个带参数的构造函数,因此编译时会因找不到父类的默认构造函数而出错
				cout << "fish construct" << endl;
			}
			...
	};

	void main()
	{
		fish fh;
	}

针对父类有参数的构造函数,在子类中需要显示的去调用父类的构造函数:

	class fish:public animal
	{
		public:
			fish():animal(400, 300)	//构造fish对象时,传入参数调用带参数的构造函数
			{						//":"初始化,"animal(400, 300)":父类带参数的构造函数
				cout << "fish construct" << endl;
			}
			...
	};

	//上述方法也可用于对类中常量(const)成员进行初始化---一般普通成员变量没有这个必要
	class point
	{
		public:
			point():x(0), y(0)	//在调用构造函数时,初始化常量成员变量x=0,y=0
		private:
			const int x;		//定义常量成员变量x
			const int y;		//定义常量成员变量y
	};

**3.类中成员的访问特性**

	1.public:定义的成员在任何地方都可以被访问;
	2.protected:定义的成员只能在该类及其子类中被访问;
	3.private:定义的成员只能在该类自身中被访问;

	//继承特性
	1.public继承:派生类保持父类中的原来的访问权限(public和protected,private成员不能被派生类继承);
	2.protected继承:基类中的public和protected成员在派生类中都变成protected类型的访问权限;
	3.private继承:没有指定继承权限则为private,此时基类中的public和protected成员全都变成private权限.
	PS:基类中的private成员不能被派生类访问.因此,private成员不能被派生类所继承.

**4.多重继承**

	class 派生类名:访问权限 基类名称, 访问权限 基类名称, 访问权限 基类名称
	e.g.
	class B:public C, public D	//类B是由类C和类D派生的

要注意基类的位置顺序.初始化时是按位置顺序进行初始化的,析构是按位置的反方向进行调用的.

多重继承中基类不能出现同名的成员函数,否则会编译出错:

	#include <iostream.h>
	class B1
	{
		public:
			void output();
	};
	class B2
	{
		public:
			void output();
	};
	void B1::output()	//类函数的实现.返回类型 类名::函数
	{
		cout << "call the class B1" << endl;
	}
	void B2::output()
	{
		cout << "call the class B2" << endl;
	}
	class A:public B1, public B2
	{
		public:
			void show();
	}
	void A::show()
	{
		cout << "call the class A" << endl;
	}
	
	void main()
	{
		A a;
		a.output();	//该语句编译时会出错('A::output' is ambiguous歧义),因为基类B1和B2都有output函数,
					//编译器无法确定使用哪一个基类的output函数.
		a.show();
	}

#### 2.2.7 虚函数与多态性、纯虚函数

**1.虚函数与多态性**

未定义成虚函数时:

	#include <iostream.h>
	class animal
	{
		public:
			void eat()
			{
				cout << "animal eat" << endl;
			}
			void sleep()
			{
				cout << "animal sleep" << endl;
			}
			void breathe()	//breathe未定义成虚函数
			{
				cout << "animal breathe" << endl;
			}
	};
	class fish:public animal
	{
		public:
			void breathe()	//重新定义breathe方法
			{
				cout << "fish bubble" << endl;
			}
	};

	void fn(animal *pAn)	//传进来一个animal类的指针
	{
		pAn->breathe();		//调用animal类中的breathe方法
	}
	void main()
	{
		animal *pAn;
		fish fn;
		pAn = &fn;	//因为派生类由基类派生出来,所以派生类对象也是基类的对象,C++编译器会自动转换,
		//不需要强制转换.但是基类对象却不是派生类对象,如果需要使用必须进行强制转换.
		fn(pAn);	//将fn的地址赋给了pAn,C++编译器进行了类型转换.此时C++编译器认为pAn保存的就是
		//animal对象的地址.因此会调用animal对象的breathe函数.
		//打印的结果为:animal breathe
	}

派生类对象的内存模型:

	this指针----------->-----------------------------

							基类对象所占内存

						----------------------------
				
							派生类对象自身增加的部分

						----------------------------

			派生类对象所占内存包括基类对象所占内存和自身增加部分所占内存.
	上述将fish对象转换为animal类型后,就变成了基类对象所占内存(此处为animal对象所占内存),后续调用即调用
	基类的方法.但如果基类函数前有virtual关键字(即虚函数),C++会采用迟绑定(late binding)技术(即编译时并
	不确定具体调用的函数),而是在运行的时候依据对象的真实类型(非转换类型)来确定调用的函数,这叫C++的多态性.
	没有加virtual关键字,C++编译器在编译时就确定的函数调用称为早起绑定(early binding).

虚函数声明:

	virtual void breathe()	//虚函数声明.由虚函数派生出来的函数都是虚函数
	{
		cout << "animal breathe" << endl;
	}

**C++多态性:在基类的函数前加上virtual关键字,在派生类中重写该函数,运行时会根据对象的实际类型来调用相应的函数.**

**2.纯虚函数**

	virtual void breathe() = 0;	//在虚函数后面加上=0即可.一般没有函数体

纯虚函数目的:让类先有一个操作名称,没有操作内容.由派生类在继承时再给出具体的定义.

虚函数特点:
	
	1.凡是含有纯虚函数的类叫做抽象类.抽象类不能声明对象,只是作为基类为派生类服务.
	2.在派生类中必须完全实现基类的纯虚函数,否则派生类也变成了抽象类,不能实例化对象.
	3.C++多态性是由虚函数来实现的,而不是纯虚函数.
	4.派生类中如果有对基类虚函数的覆盖定义,无论该覆盖定义是否有virtual关键字,派生类中的该函数都是虚函数.
	
#### 2.2.8 函数的覆盖和隐藏

**1.函数的覆盖(override)条件**

	1.基类函数必须是虚函数;
	2.发生覆盖的两个函数要分别位于派生类和基类中;
	3.函数名称与参数列表必须完全相同.
	PS:C++多态性是通过虚函数来实现的,因此函数的覆盖总是和多态关联在一起.在函数覆盖的情况下,
		编译器会在运行时根据对象的实际类型类确定要调用的函数.

**2.函数的隐藏的情况**

	1.派生类的函数与基类的函数完全相同(函数名和参数列表都相同),但是基类的函数没有使用virtual关键字,
		此时基类函数将被隐藏.
	2.派生类的函数与基类的函数同名,但参数列表不同.此时不论基类的函数声明是否有virtual关键字,
		基类函数都将被隐藏.

**实例**

	#include <iostream.h>
	class Base
	{
		public:
			virtual void xfn(int i)	//由虚函数派生出来的都是虚函数
			{
				cout <<　"Base::xfn(int i)" << endl;
			}
			void yfn(float f)
			{
				cout << "Base::yfn(float f)" << endl;
			}
			void zfn()
			{
				cout << "Base::zfn()" << endl;
			}
	};

	class Derived : public Base
	{
		public:
			void xfn(int i)		//覆盖基类的xfn函数
			{
				cout << "Derived::xfn(int i)" << endl;
			}
			void yfn(int c)		//隐藏了基类的yfn函数--->参数类型不一样,无论是否有virtual关键字
			{
				cout << "Derived::yfn(int c)" << endl;
			}
			void zfn()			//隐藏了基类的zfn函数--->因为无virtual关键字
			{
				cout << "Derived::zfn()" << endl;
			}
	};

	void main()
	{
		Derived d;
		
		Base *pB = &d;
		Derived *pD = &d;

		pB->xfn(5);	//因为基类中xfn是虚函数,属于覆盖,因此在运行时确定是调用派生类的xfn.
					//打印出:Derived::xfn(int i)
		pD->xfn(5);	//打印出:Derived::xfn(int i)

		pB->yfn(3.14f);	//属于隐藏.在编译时确定是调用基类的yfn函数,因为已经转换成了基类的对象指针
					//打印出:Base::yfn(float f)
		pD->yfn(3.14f);	//应该是调用派生类的yfn,但是参数不对--->会强制转换吧??
					//打印出:Derived::yfn(int c)
		
		pB->zfn();	//属于隐藏.在编译时确定是调用基类的zfn函数,因为已经转换成了基类的对象指针
					//打印出:Base::zfn()
		pD->zfn();	//打印出:Derived::zfn()
	}

#### 2.2.9 引用

引用是一个变量的别名,需要用另一个变量或对象来初始化自身.必须在声明的时候进行初始化.

	int a = 5;
	int &b = a;	//"&"表示声明一个引用(类型 &引用名 = 变量/对象;).且必须在声明时进行初始化.

引用的特点:

1.引用和用来初始化引用的变量指向同一块内存,因此通过引用或变量可以改变同一块内存中的内容.
	
	int a = 5;
	int &b = a;	//申明引用
	int c = 3;
	b = c;	//此时b和a的值都变成了3

2.引用一旦初始化,就代表一块特定的内存,再也不能代表其他内存.

引用和指针的区别:

1.引用是一个变量或对象的别名.引用的地址就是它所引用的变量或对象的地址,因此引用的地址没有任何意义,C++也没有提供访问引用本身地址的方法.可以认为引用不占用存储空间.

2.指针变量存储地址值,因此需要占用存储空间.且可以随时修改指针变量所保存的地址值,从而可以指向其他内存.

**引用多数用于函数的形参定义上,用以实现和指针一样的功能(改变实参的内存).还可以避免实参占用较大内存时发生值的复制.**

实例---交换两个数据的值

	#include <iostream.h>

	void change(int &a, int &b);	//声明函数的参数为引用

	void main()
	{
		int x = 5;
		int y = 3;
		cout << "original x = " << x << endl;
		cout << "original y = " << y << endl;
		change(x, y);	//因为声明为引用,因此直接传入参数即可.如果为指针,则传入指针(&x, &y).
		cout << "changed x = " << x << endl;
		cout << "changed y = " << y << endl;
	}

	void change(int &a, int &b)	//实现交换两个数据值
	{
		a = a + b;
		b =  a - b;
		a = a - b;
	}

#### 2.2.10 C++类的设计习惯及头文件重复包含问题的解决

1.设计类时分为:头文件(.h文件)和源文件(.cpp文件)

	头文件存放类的定义及类成员函数的声明;源文件存放类中成员函数的实现.

2.解决头文件重复包含的问题,使用条件预处理指令(在头文件定义时操作)

	#ifndef	...	
	#define	...
	#endif

实例---类的设计

	/*1--->animal类的头文件animal.h*/
	#ifndef __ANIMAL_H__	//条件预处理指令.判断__ANIMAL_H__没有定义则定义该宏,并继续往下执行.
	#define __ANIMAL_H__	//如果判断定义了,则直接跳到#endif.避免重复定义
	class animal()
	{
		public:
			animal();
			~animal();
			void eat();
			void sleep();
			virtual void breathe();		//虚函数声明.virtual放在函数的最前面
	};
	#endif

	/*2--->animal类的源文件animal.cpp*/
	#include <iostream.h>
	#include "animal.h"

	animal::animal()	//"::"作用于标识符,用于指明一个函数属于哪个类或一个数据成员属于哪个类.
	{					//"::"如果前面不跟类名(只有::),表示是全局函数(即非成员函数)或者全局数据成员
	}
	...
	void animal::breathe()	//返回类型放在最前面.在头文件中有virtual,但是在源文件中就不必再加virtual.
	{
		cout << "animal breathe" << endl;
	}
***
## Chapter 3 MFC框架程序剖析

MFC(Microsoft Foundation Class,微软基础类库):微软为了简化程序员的开发工作所开发的一套C++类的集合,是一套面向对象的函数库.

### 3.1 基于MFC的程序框架剖析

在MFC中,类的命名都以字母"C"开头.

单文档应用程序中:都有一个CMainFrame类,一个"C+工程名+App"类,一个"C+工程名+Doc"类,一个"C+工程名+View"类.

CMainFrame类:代表应用程序框架窗口.

#### 3.1.1 MFC程序中的WinMain函数

其源码位于:.\Microsoft Visual Studio 10.0\VC\atlmfc\src\mfc\appmodul.cpp中.

	// export WinMain to force linkage to this module
	extern int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		_In_ LPTSTR lpCmdLine, int nCmdShow);
	
	extern "C" int WINAPI
	_tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		_In_ LPTSTR lpCmdLine, int nCmdShow)	//-tWinMain实际上是一个宏,展开就是WinMain.
	#pragma warning(suppress: 4985)
	{
		// call shared/exported WinMain
		return AfxWinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
	}

**1.theApp全局对象**

在test.cpp(工程名.cpp)中,定义了一个应用程序的全局对象:

	// 唯一的一个 CtestApp 对象
	CtestApp theApp;

	//定义该对象的原因:
	theApp表示MFC应用程序本身.每个MFC程序有且仅有一个从应用程序类(CWinApp)派生的类(即CtestApp类)
	CtestApp类有且仅有一个实例化对象(即theApp全局对象)即为MFC程序的实例.

**2.AfxWinMain函数---即为WinMain函数的调用**

该函数位于:.\Microsoft Visual Studio 10.0\VC\atlmfc\src\mfc\winmain.cpp

	Afx前缀的函数代表应用程序框架函数(Application Framework).在MFC中,以Afx为前缀的函数都是全局函数,
	可以在程序的任何地方调用他们.

#### 3.1.2 MFC框架窗口

**step 1.设计和注册窗口---AfxEndDeferRegisterClass函数**

MFC全局函数AfxEndDeferRegisterClass实现窗口类的注册,该函数位于:.\Microsoft Visual Studio 10.0\VC\atlmfc\src\mfc\wincore.cpp

**step 2.创建窗口---调用Cwnd类的CreateEx函数**

CWnd类的CreateEx实现代码位于:.\Microsoft Visual Studio 10.0\VC\atlmfc\src\mfc\wincore.cpp

	MFC中后缀名为Ex的函数都是扩展函数.

**step 3.显示和更新窗口**

在CTestApp(C+工程名+App)中的InitInstance()函数中

	BOOL CtestApp::InitInstance()
	{
		...
		// 唯一的一个窗口已初始化，因此显示它并对其进行更新
		m_pMainWnd->ShowWindow(SW_SHOW);		//显示应用程序框架窗口
		m_pMainWnd->UpdateWindow();		//更新应用程序框架窗口
		...
	}

#### 3.1.3 消息循环

在AfxWinMain函数中:

	int AFXAPI AfxWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	_In_ LPTSTR lpCmdLine, int nCmdShow)
	{
		...
		nReturnCode = pThread->Run();	//完成消息循环任务
	}

#### 3.1.4 窗口过程函数

注册窗口中:

	BOOL AFXAPI AfxEndDeferRegisterClass(LONG fToRegister)
	{
		...
		wndcls.lpfnWndProc = DefWindowProc;	//指定窗口过程函数.
											//MFC采用一种称为消息映射的机制来处理消息
		...
	}

**MFC程序运行过程:**

	1.利用全局应用程序对象theApp启动应用程序;
	2.进入WinMain函数.在AfxWinMain函数中可以获取子类(即CTestApp类的全局对象theApp)的指针,利用该指针
		调用虚函数:InitInstance(实际上是调用theApp的InitInstance函数),完成应用程序的一些初始化工作
		(包括窗口类的注册、创建,窗口的显示和更新).
	3.进入消息循环.MFC采用消息映射机制来处理各种消息,当收到WM_QUIT消息时,退出消息循环,程序结束.

#### 3.1.5 MFC的文档/视类结构

**CTestView类---视类**

	MFC的主框架窗口是整个应用程序外框所包括的部分;而视类窗口(CTestView类)只是主框架窗口中空白的部分.
	且视类窗口始终覆盖在框架窗口之上.

**CTestDoc类---文档类**

**文档/视类结构的应用**

	视类(CTestView类):MFC中数据的显示和修改由视类完成
	文档类(CTestDoc类):MFC中数据的存储和加载由文档类来完成

#### 3.1.6 帮助对话框类

**CAboutDlg类---帮助对话框类**

	CAboutDlg类:显示一个帮助窗口(e.g.菜单栏中的帮助/Help)
	
### 3.2 窗口类、窗口类对象与窗口

::(作用域标识符):以"::"开始的函数表示该函数是一个全局函数.

	BOOL CWnd::ShowWindow(int nCmdShow)
	{
		return ::ShowWindow(m_hWnd, nCmdShow);	//调用全局的Platform SDK的ShowWindow函数.
	}

窗口类对象与窗口关系:

	C++窗口类内部有一个窗口句柄变量.窗口类对象与窗口之间通过该句柄(窗口类中的一个成员变量)维持联系.
	1--->窗口销毁,仅仅表示两者的联系断了.窗口类对象(还有其他成员)的销毁与否看其生命周期是否结束;
	2--->窗口类对象销毁了,与之相关的窗口也将被销毁.因为已经没哟资源可以维持窗口.

**所有的窗口类(包括子类)内部都有一个成员来保存与之相关的窗口句柄.**

	CMainFrame类是框架窗口类,内部有一个框架窗口句柄与框架窗口联系;
	CTestView类是视类,内部有一个视窗口句柄与视窗联系.

#### 3.2.1 在CMainFrame窗口中显示按钮

即在某个窗口中显示另一个窗口(按钮也是一种窗口,CButton类派生于CWnd类).

**在CMainFrame框架类窗口中显示步骤:**

	1.为CMainFrame类添加一个CButton类的成员变量m_btn.用于和按钮窗口建立联系,此时相当于一个全局变量,
		不会出现局部变量因为函数退出而导致窗口销毁;
	2.MFC中窗口创建时都会产生WM_CREATE消息,CMainFrame类提供的OnCreate函数就是用来相应该消息的.
		CButton类的创建按钮窗口函数"Create"就需要在该函数中添加;
		CButton类的Create函数原型:
		BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd *pParantWnd,
			UINT nID);
		/*
			para1:按钮显示的文本;
			para2:按钮风格类型,也包括窗口风格类型;
			para3:按钮控件的大小和位置.一般使用CRect来构造.
				e.g.CRect(0, 0, 100, 100);	//在0,0的位置大小为100, 100
			para4:按钮空间的父窗口.一般使用this即可,表示按钮窗口属于的那个窗口的句柄.
			para5:按钮空间的标识.e.g. 123
		*/
	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		...
		/*在return之前添加*/
		m_btn.Create("按钮", WS_CHILD | BS_DEFPUSHBUTTON, CRect(0, 0, 100, 100), this, 123);
		/*步骤3添加.显示按钮窗口*/
		m_btn.ShowWindow(SW_SHOWNORMAL);
		
		return 0;
	}
	3.需要添加显示按钮窗口,如2中代码.

**框架窗口的客户区和非客户区:**

	1--->标题栏和菜单栏位于非客户区;
	2--->包括工具栏的其他区域都属于客户区.客户区是可以显示东西的.

#### 3.2.2 在CTestView窗口中显示按钮

1.任何一个窗口在创建时都会产生一个WM_CREATE消息.

2.CTestView类没有OnCreate函数去相应WM_CREATE消息,因此需要添加响应WM_CREATE消息的函数.

**在CTestView视类窗口中显示步骤:**

	1.为CTestView类添加一个CButton类的成员变量m_btn;
	2.为CTestView类添加响应WM_CREATE消息的响应函数OnCreate;
	3.在CTestView类的OnCreate响应函数中添加:
	int CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		...
		/*在return之前添加*/
		m_btn.Create("按钮", WS_CHILD | BS_DEFPUSHBUTTON, CRect(0, 0, 100, 100), this, 123);
		/*步骤3添加.显示按钮窗口*/
		m_btn.ShowWindow(SW_SHOWNORMAL);
		
		return 0;
	}
	//在上述程序中,this指针指代CTestView类的对象.视类窗口的父窗口为CMainFrame,得到父窗口指针可用:GetParent()函数.
	
如果希望窗口创建之后立即显示,可以将窗口风格指定为WS_VISIBLE.此时不需要在调用ShowWindow函数.

	m_bt.Create("按钮", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, CRect(0, 0, 100, 100), this, 123);
	//m_btn.ShowWindow(SW_SHOWNORMAL);	//这句代码不再需要.
***
## Chapter 4 简单绘图

### 4.1 MFC消息映射机制

**1. 使用类向导添加消息相应函数:**

	1.在需要添加消息相应函数的类上单击右键,选择类向导,弹出"MFC 类向导"窗口.快捷键:Ctrl+Shift+X
		也可以使用菜单栏:项目->类向导.
	2.在"MFC 类向导"窗口中,需要对"项目"(有多个project才需要选择)、"类名"(需要添加的消息相应函数作用的类)、
		"消息"页(选择需要处理的消息)---双击需要处理的消息会自动生成消息处理函数,并在右侧的"现有处理函数"
		中会显示出来.--->最后单击编辑代码即可定位到添加的消息处理函数处进行编辑.
	3.添加实现代码:
		void CtestView::OnLButtonDown(UINT nFlags, CPoint point)
		{
			// TODO: 在此添加消息处理程序代码和/或调用默认值
			//MessageBox(LPCTSTR("View Clicked1"));		//这种方法会显示乱码
			MessageBox(_T("View Clicked!"));			//正确显示
			CView::OnLButtonDown(nFlags, point);
		}

	在MFC中的MessagBox函数的使用:
		1.原型:int MessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption = (LPCTSTR)0, 
			UINT nType = 0U);
			只需要填充第一个参数即可->需要显示的文字.其他有默认参数
		2.填充第一个参数(需要显示的文字时).需要进行强制转化,否则会编译不通过.
			MessageBox(LPCTSTR("View Clicked!"));	//转化为该种形式会显示乱码.
			解决--->转成_TCHAR类型:
			MessageBox(_T("View Clicked!"));	//需要转换为_T("字符串")才不会有乱码.

如果鼠标左键单击消息在CMainFrame类中添加会没有反应.因为CTestView类(视类)始终覆盖在框架窗口之上.因此:鼠标单击、鼠标移动等操作都只能由视类窗口捕获.不能由框架窗口(CMainFrame类)捕获.

**2. 使用类向导删除已经添加的消息响应函数:---有时多添加了**

	1.打开类向导窗口;
	2.选择"消息"页,在显示的"现有处理程序"中选中需要删除的函数.在右侧点击删除处理程序即可.

**3. MFC消息映射机制剖析---使用类向导添加的消息响应函数内部机制(主要有3处信息)**

1.添加了消息响应函数原型---在头文件中:

	在类的头文件中.e.g.CTestView类的头文件中

	// 生成的消息映射函数
	protected:
		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);	
		//afx_msg是一个宏,表明该函数是一个消息相应函数的声明.
	};

2.添加消息映射宏---在源文件中:

	在类的源文件中.e.g.CTestView类的源文件中:
	
	BEGIN_MESSAGE_MAP(CtestView, CView)	//该宏到END宏定义了该类的消息映射表.
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()	//该宏将鼠标左键按下消息(WM_LBUTTONDOWN)与对应的消息相应函数关联起来.
	END_MESSAGE_MAP()

3.消息响应函数的实现---在源文件中:

	void CtestView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		//MessageBox(LPCTSTR("View Clicked1"));		//这种方法会显示乱码
		MessageBox(_T("View Clicked!"));			//正确显示
		CView::OnLButtonDown(nFlags, point);
	}

虚函数内部剖析:虚函数在系统中存在一个虚函数表(vtable)进行相关的构建.基类的虚函数在应用程序中使用的每个派生类,系统都要为它们分配一个vtable(且不管基类中虚函数是否确实在派生类中被重写).而且vtable表都要为基类的每一个虚函数提供一个4字节的输入项.因此,系统中如果存在较多的虚函数会占据较多的内存资源,对内存资源是一种浪费.

**MFC消息映射机制:在每个能接收和处理消息的类中,会定义一个消息和消息函数静态对照表(也叫消息映射表),并且消息与对应消息处理函数指针是成对出现的.当有消息需要处理时,程序会自动搜索消息静态表,找到对应的消息处理函数进行处理.**

### 4.2 绘制线条

**1. 起点**

鼠标左键按下的位置,需要一个成员变量保存这个位置(CPoint类):

	1.添加一个成员变量(CPoint类),用于保存鼠标左键按下的点;
		CDrawView右键->Add->Add Varialbe->Access选择private/Variable Type输入CPoint/Variable Name输入m_ptOrigin
		添加完后,在构造函数中会自动进行初始化:
		CDrawView::CDrawView()
			: m_ptOrigin(0)		//成员变量的初始化
		{
			// TODO: 在此添加消息处理程序代码和/或调用默认值
			
		}
	2.在鼠标左键按下的响应函数OnLButtonDown保存鼠标按下点的信息.
		void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
		{
			// TODO: 在此添加消息处理程序代码和/或调用默认值
			m_ptOrigin = point;
			CView::OnLButtonDown(nFlags, point);
		}

**2.终点**

鼠标左键弹起的位置,添加WM_LBUTTONUP消息的处理函数

	添加WM_LBUTTONUP消息响应的处理函数
	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		/*
			在该函数中进行划线处理
		*/
		CView::OnLButtonUp(nFlags, point);
	}

#### 4.2.1 利用SDK全局函数实现画线功能

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		
		HDC hdc;	//Windows平台下所有的图形操作都是由DC(Device Context设备描述表)句柄完成.
		hdc = ::GetDC(m_hWnd);	//每个由CWnd类派生的类都有一个m_hWnd成员变量保存窗口句柄
			//全局函数GetDC获得当前窗口的设备描述表
		MoveToEx(hdc, m_ptOrigin.x, m_ptOrigin.y, NULL);
		/*
			//移动到线条的起点
			para1:设备描述表的句柄
			para2 & para3:移动到某个具体的点(x,y坐标)
			para4:指向POING结构体的指针.用于保存移动操作前的鼠标位置.此处需要设为NULL
		*/
		LineTo(hdc, point.x, poing.y);
		/*
			//绘制一条到指定点的线
			para1:设备描述表的句柄
			para2 & para3:线条终点的x,y坐标
		*/
		:ReleaseDC(m_hWnd, hdc);	//释放设备描述表资源

		CView::OnLButtonUp(nFlags, point);
	}

#### 4.2.2 利用MFC的CDC类实现画线功能

MFC提供了一个设备描述表的封装类CDC,CDC类封装了所有与绘图相关的操作.CDC类有一个数据成员m_hDC,保存了DC句柄.

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		
		CDC *pDC = GetDC();	//利用CWnd类的成员GetDC()可获得当前窗口的设备描述表对象的指针
		pDC->MoveTo(m_ptOrigin);		//CDC类的MoveTo函数是移动到具体的某个点.para:CPoint类对象
		pDC->LineTo(point);		//CDC类的LineTo函数划线到某个点.para:CPoint类对象
		ReleaseDC(pDC);		//CWnd类的ReleaseDC(pDC)释放设备描述表资源

		CView::OnLButtonUp(nFlags, point);
	}

#### 4.2.3 利用MFC的CClientDC类实现画线功能

MFC提供的CClientDC类派生于CDC类,并且在构造时会自动调用GetDC()获得设备描述表,析构时自动调用ReleaseDC()函数释放设备描述表资源.

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CClientDC dc(this);	//构造CClientDC对象时,需要一个CWnd类型的指针作为参数表示CClientDC对象属于哪个窗口.
							//即在哪个窗口中绘图.此处this指代CDrawView对象的指针.
		//如果需要在View类的父窗口即CMainFrame类中操作,可以使用CClientDC dc(GetParent());
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		
		CView::OnLButtonUp(nFlags, point);
	}

**CxxxView窗口(视类窗口)与CMainFrame窗口(框架窗口)说明**

	CxxxView窗口只有客户区,即窗口的白色区域部分;
	CMainFrame窗口的客户区是菜单栏以下的所有部分(包括工具栏也属于客户区,因为可以浮动);非客户区是标题栏和菜单栏.
	绘图操作一般在窗口的客户区进行.

#### 4.2.4 利用MFC的CWindowDC类实现画线功能

MFC提供的CWindowDC类也派生与CDC类,并且在构造时会自动调用GetWindowDC()获得设备描述表,析构时自动调用ReleaseDC()释放设备描述表资源.

**CWindowDC对象可以访问到框架窗口的非客户区(即整个窗口),前面几种只能访问到窗口的客户区.**

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CWindowDC dc(GetParent());	//构造CWindowDC对象时,需要一个CWnd类型的指针作为参数表示CWindowDC对象属于哪个窗口.
		//即在哪个窗口中绘图.此处使用GetParent获得CMainFrame对象的指针.只有在CMainFrame窗口中才能看出效果
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);

		CView::OnLButtonUp(nFlags, point);
	}
	//此时可以在框架窗口的标题栏和菜单栏画线

#### 4.2.5 在桌面窗口中划线

CWindownDC对象可以在整个窗口中画线;CWnd类的GetDesktopWindow成员函数可以获得Windows桌面窗口的句柄.

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CWindowDC dc(GetDesktopWindow());	
		//构造CWindowDC对象时,需要一个CWnd类型的指针作为参数表示CWindowDC对象属于哪个窗口.
		//即在哪个窗口中绘图.此处使用GetDesktopWindow获得Windows桌面窗口对象的指针
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);

		CView::OnLButtonUp(nFlags, point);
	}

#### 4.2.6 绘制彩色线条

设备描述表默认是一个黑色画笔,因此绘制的线条都是黑色.如果绘制其他颜色,首先需要创建一个特定颜色的画笔,然后将此画笔选入设备描述表中.接下来绘制的线条颜色就有这个新画笔颜色决定.

**1.创建画笔对象**

	CPen(int nPenStyle, int nWidth, COLORREF crColor);
	/*
		para1:线型---PS_SOLID(实线)、PS_DASH(虚线)、PS_DOT(点线)
		para2:线宽---1(1磅)
		para3:笔的颜色,一般使用RGB宏构建
			COLORREF RGB(BYTE bRed, BYTE bGreeen, BYTE bBlue);
			/*
				三个参数都是BYTE类型,取值为0~255即可.(0,0,0)表示黑色;(255,255,255)表示白色.
			*/
	*/

**2.将画笔对象选入设备描述表中---画笔对象也是GDI对象**

	CPen pen(PS_SOLID, 1, RGB(255, 0, 0));	//红色,实线,1磅的画笔
	CClientDC dc(this);
	CPen *pOldPen = dc.SelectObject(&pen);	//将GDI对象(此处为画笔)选入设备描述表,返回之前的GDI对象(画笔),为了后面的恢复
	...	//一系列的画图操作
	dc.SelectObject(pOldPen);	//将之前的GDI对象选入设备描述表,恢复到先前的状态.

**绘制彩色线条实例**

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));	//红色,实线,1磅
		CClientDC dc(this);
		CPen *pOldPen = dc.SelectObject(&pen);
		dc.MoveTo(m_ptOrigin);
		dc.LineTo(point);
		dc.SelectObject(pOldPen);

		CView::OnLButtonUp(nFlags, point);
	}

注意:画笔的宽度要小于等于1时,虚线线型才有效.

### 4.3 使用画刷绘图

MFC提供的CBrush类用于创建画刷对象.画刷通常用来填充一块区域.

#### 4.3.1 简单画刷

简单画刷,不需要将画刷选入设备描述表.

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CBrush brush(RGB(255, 0, 0));	//创建一个红色画刷
		CClientDC dc(this);
		dc.FillRect(CRect(m_ptOrigin, point), &brush);
		/*
			//利用画刷填充拖曳过程中形成的矩形区域
			para1:RECT结构体或CRect对象的指针,表示填充的矩形.一般使用CRect
				CRect(POINT topLeft, POINT bottomRight);
				/*
					para1 & para2:矩形区域的左上角和右下角两个点.
				*/
			para2:画刷对象的指针
		*/

		CView::OnLButtonUp(nFlags, point);
	}

#### 4.3.2 位图画刷

**1.创建一个位图具有位图资源的CBitmap对象**

	1.添加一个位图资源
	--->Insert--->Resource...--->选择Bitmap--->New--->则可创建一个默认名称为IDB_BITMAP1(该宏对应一个ID值)的位图资源.
		并且可以在Resource View下编辑该位图资源
	2.创建一个位图对象
		CBitmap bitmap;	//创建一个位图对象
	3.为位图对象加载位图资源
		bitmap.LoadBitmap(IDB_BITMAP1);	//para:资源的ID值.IDB_BITMAP1为表示一个资源ID的宏.

**2.构造CBrush类的位图画刷**

	CBrush brush(&bitmap);	//将位图加载到画刷构成位图画刷

**位图画刷实例**

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_BITMAP1);	//已经添加好了一个位图资源IDB_BITMAP1
		CBrush brush(&bitmap);	//创建位图画刷
		CClientDC dc(this);
		dc.FillRect(CRect(m_ptOrigin, point), &brush);
		//利用位图画刷填充矩形区域

		CView::OnLButtonUp(nFlags, point);
	}

#### 4.3.3. 透明画刷

利用CDC类的Rectangle函数绘制矩形

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CClientDC dc(this);
		//绘制矩形
		dc.Rectangle(CRect(m_ptOrigin, point));
		/*
			para:RECT结构体或CRect对象的指针.一般使用CRect函数构建
		*/

		CView::OnLButtonUp(nFlags, point);
	}

**由于设备描述表中有一个默认的白色画刷,绘图时会用该画刷填充矩形区域.因此会出现当有位置重叠时,后面绘制的矩形将先前的矩形遮挡住.**

**创建空画刷---因为无真正的透明画刷**

	1.获取空画刷句柄:
	HGDIOBJ GetStockObject(int fnObject);	//得到系统的标准画刷
	/*
		para:制定获取对象的类型.
			e.g.
				NULL_BRUSH--->空画刷
				BLACK_BRUSH--->黑色画刷
		retval:返回多种资源对象的句柄.HGDIOBJ实际为void *,在实际使用时,需要进行类型转换.一般转换为"(HBRUSH)"即可
	*/
	2.将空画刷句柄转换为画刷对象:---CBrush类的FromHandle静态函数实现
	static CDC *PASCAL FromHandle(HDC hDC);
	/*
		para:DC句柄.HBRUSH属于HDC的一种.
	*/
	
	//综合,创建一个空画刷
	CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
	//访问CBrush类的静态成员函数--->CBrush::FromHandle...

**实例---使用空画刷绘制矩形**

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CClientDC dc(this);
		CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));

		//将空画刷选入设备描述表
		CBrush *pOldBrush = dc.SelectObject(pBrush);
		dc.Rectangle(CRect(m_ptOrigin, point));
		//恢复先前的画刷
		dc.SelectObject(pOldBrush);

		CView::OnLButtonUp(nFlags, point);
	}

**静态成员函数、静态成员变量、非静态成员函数、非静态成员变量**

	1.静态成员函数和静态成员变量属于类本身,在类加载的时候就为他们分配了内存.与有无对象无关.
		可以直接通过类名::函数名或类名::变量名来访问
	2.非静态成员函数和非静态成员变量属于对象的方法和数据,必须先产生类的对象,然后通过类的对象去访问.
		
	//实例
	class point
	{
		public:
			void output()
			{}
			static void init()
			{}
	};
	voia main()
	{
		/*
		Point pt;
		pt.init();	//通过对象访问静态成员函数--->正确
		pt.output();	//通过对象访问非静态成员函数--->正确
		*/
		Point::init();	//直接使用类名访问静态成员函数--->正确
		Point::output();	//直接使用类名访问非静态成员函数--->错误.非静态成员函数属于对象,此时没有分配内存
	}
	3.静态成员函数中是不能调用非静态成员(包括非静态成员函数和非静态成员变量).因为可能还没有分配内存.只能访问静态成员变量.
	4.非静态成员函数可以调用静态静态成员函数
	5.静态成员变量一定要进行初始化,并且在类的定义之外进行初始化.
	int Point::x = 0;
	int Point::y = 0;

### 4.4 绘制连续线条
	
**1.在CDrawView类中增加一个BOOL型的成员变量m_bDraw,用于表明鼠标左键是否被按下.**

	private:
		bool m_bDraw;

	//会在构造函数中被自动初始化为false
	CDrawView::CDrawView()
	: m_bDraw(false)	//初始化bool型变量m_bDraw为false
	, m_bOrigin(0)		//多个成员变量初始化
	{
		// TODO: 在此处添加构造代码
	
	}

**2.在鼠标左键按下消息响应函数中设置该变量为true,在鼠标左键弹起的响应函数中设备为false.**

	void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		m_ptOrigin = point;		//仍然保留起始点
		m_bDraw = true;
		CView::OnLButtonDown(nFlags, point);
	}

	void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		m_bDraw = false;
		CView::OnLButtonUp(nFlags, point);
	}

**3.添加鼠标移动消息(WM_MOUSEMOVE)的响应函数OnMouseMove,并添加相关代码**

	/*
	首先判断鼠标左键按下是否为真,为真表示鼠标左键按下,此时可以进行画线操作.在鼠标移动过程中,
	都是一个一个小点,只需要将这些小点连成线段即可.要注意线段的起点切换.
	*/
	void CtestView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
	
		CClientDC dc(this);
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen *pOldPen = dc.SelectObject(&pen);	//将pen选入到设备描述表

		if (m_bTest == true)
		{
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(point);
			m_bOrigin = point;	//保留当前点为下一次线段的起点
		}
		dc.SelectObject(pOldPen);	//还原原来的画笔	

		CView::OnMouseMove(nFlags, point);
	}

### 4.5 绘制扇形效果的线条

**保持起点不变(鼠标左键按下位置),分别绘制到鼠标移动点的直线,就会出现扇形效果.**

	void CtestView::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
	
		CClientDC dc(this);
		CPen pen(PS_SOLID, 1, RGB(255, 0, 0));
		CPen *pOldPen = dc.SelectObject(&pen);	//将pen选入到设备描述表

		if (m_bTest == true)
		{
			dc.MoveTo(m_ptOrigin);
			dc.LineTo(point);
			//m_bOrigin = point;	//注释掉该行或者删除即可
		}
		dc.SelectObject(pOldPen);	//还原原来的画笔	

		CView::OnMouseMove(nFlags, point);
	}

**绘制带边线的扇形**

	1.添加一个成员变量m_ptOld,用于保存鼠标移动的前一个点.
		private:
			CPoint m_ptOld;
	2.在左键按下响应函数中赋值为当前按下点.
		void CtestView::OnLButtonDown(UINT nFlags, CPoint point)
		{
			// TODO: 在此添加消息处理程序代码和/或调用默认值
			//MessageBox(LPCTSTR("View Clicked1"));
			//MessageBox(_T("View Clicked!"));
			m_bTest = true;
			m_ptOrigin = point;
			m_ptOld = point;
			CView::OnLButtonDown(nFlags, point);
		}
	3.在鼠标移动响应函数中添加代码:
		void CtestView::OnMouseMove(UINT nFlags, CPoint point)
		{
			// TODO: 在此添加消息处理程序代码和/或调用默认值
		
			CClientDC dc(this);
			CPen pen(PS_SOLID, 2, RGB(255, 0, 0));
			CPen *pOldPen = dc.SelectObject(&pen);
		
			if (m_bTest == true)
			{
				dc.MoveTo(m_ptOrigin);
				dc.LineTo(point);
				//m_ptOrigin = point;
				dc.LineTo(m_ptOld);	//画线到前一个点
				m_ptOld = point;		//保留当前点,用作下一条线段的起点
			}
		
			dc.SelectObject(pOldPen);
		
			CView::OnMouseMove(nFlags, point);
		}
		
设置绘图模式函数:SetROP2--->暂时没有使用过.

	int SetROP2(int nDrawMode);
	/*
		para:绘图模式.R2_BLACK、R2_WHITE、R2_MERGENOTPEN
	*/
***
## Chapter 5 文本编程

### 5.1 插入符

插入符(Caret):文本处理程序的编辑窗口中那条闪烁的竖线,用于提示用户输入.

#### 5.1.1 创建文本插入符

利用CWnd类的CreateSolidCaret()函数完成:

	void CreateSolidCaret(int nWidth, int nHeight);
	/*
		para1:指定插入符的宽度(逻辑单位).如果为0,则系统将其设置为系统定义的窗口边界的宽度.
		para2:指定插入符的高度(逻辑单位).如果为0,则系统将其设置为系统定义的窗口边界的高度.
	*/

**实例1---在视类窗口创建一个(10,20)的简单插入符**

	/*因为视类窗口位于框架窗口之上,因此对窗口客户区的鼠标和键盘操作实际上都是在视类窗口上进行的.*/
	step 1:为视类添加WM_CREATE(窗口创建消息)消息的响应函数OnCreate.
	step 2:在OnCreate函数中添加下面的额代码.
	int CtextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;
	
		// TODO:  在此添加您专用的创建代码
		CreateSolidCaret(10, 20);	//创建一个插入符
		ShowCaret();	//显示插入符---一定需要添加,因为插入符初始时是隐藏的.
		return 0;
	}

**实例2---创建一个符合常规的插入符**

实例1创建的插入符看着很别扭.根据文本信息来创建插入符是比较和情理的.

	1.利用CDC类的GetTextMetrics成员函数获得设备描述表中当前字体的度量信息.
		BOOL GetTextMetrics(LPTEXTMETRIC lpMetrics) const;
		/*
			para:保存从设备描述表中获得的当前字体的信息.
			typedef struct tagTEXTMETRICW
			{
			    LONG        tmHeight;	//字体的高度---常用
			    LONG        tmAscent;	//升序高度
			    LONG        tmDescent;	//降序高度
			    LONG        tmInternalLeading;
			    LONG        tmExternalLeading;
			    LONG        tmAveCharWidth;		//平均宽度,因为每个字符的宽度不一样,
				//一般使用平均宽度/8作为插入符的宽度比较合理.
			    LONG        tmMaxCharWidth;		//字符最大宽度
			    LONG        tmWeight;
			    LONG        tmOverhang;
			    LONG        tmDigitizedAspectX;
			    LONG        tmDigitizedAspectY;
			    WCHAR       tmFirstChar;
			    WCHAR       tmLastChar;
			    WCHAR       tmDefaultChar;
			    WCHAR       tmBreakChar;
			    BYTE        tmItalic;
			    BYTE        tmUnderlined;
			    BYTE        tmStruckOut;
			    BYTE        tmPitchAndFamily;
			    BYTE        tmCharSet;
			} TEXTMETRICW, *PTEXTMETRICW, NEAR *NPTEXTMETRICW, FAR *LPTEXTMETRICW;
			
			typedef TEXTMETRICW TEXTMETRIC;
		*/
	2.修改例1代码如下:
	int CtextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;
	
		// TODO:  在此添加您专用的创建代码
		CClientDC dc(this);
		TEXTMETRIC tm;	//保存字体信息
		dc.GetTextMetrics(&tm);		//得到设备描述表中的字体信息,并保存的TEXTMETRIC结构体中
		CreateSolidCaret(tm.tmAveCharWidth / 8, tm.tmHeight);
			//tm.tmAveCharWidth/8:作为宽度是一个比较合理的值.高度和设备描述表中的一样.
		ShowCaret();
		return 0;
	}
	
#### 5.1.2 创建图形插入符

1.创建一个位图资源:

	资源视图下右击text.rc--->选择"添加资源(A)"--->选择Bitmap--->得到一个ID名字叫"IDB_BITMAP1"的位图,
		并进行位图的绘制.

2.为CTextView类添加一个CBitmap的成员变量:

	在CTextView类上右击--->选择添加(添加变量)--->选择访问private/变量类型CBitmap/变量名bitmap.
	/*必须为CTextView类的成员变量,否则需要注意变量的生命周期*/

3.在WM_CREATE消息的响应函数OnCreate中添加如下代码:

	int CtextView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CView::OnCreate(lpCreateStruct) == -1)
			return -1;
	
		// TODO:  在此添加您专用的创建代码
		bitmap.LoadBitmapW(IDB_BITMAP1);	//加载一个bitmap位图资源
		CreateCaret(&bitmap);
		/*
			CWnd类的CreateCaret成员函数用于创建图形插入符.
			void CreateCaret(CBitmap *bitmap);
		*/
		ShowCaret();
		return 0;
	}

### 5.2 窗口重绘

窗口发生重绘时会产生WM_PAINT消息,CTextView类中响应该消息的响应函数是OnDraw()函数.

#### 5.2.1 OnDraw函数

**如果希望输入的图形或文字始终能够显示在窗口上,则输入操作应该在OnDraw函数中处理.**

	CString类支持的操作:
		1)直接在声明变量时初始化
			CString str("VC++ 深入详解");
		2)由字符串赋值
			CString str;
			str = "VC++ 深入详解";
		3)添加字符串资源:
			Ctring str;
			str.LoadString(IDS_STRING101);
			/*
			para为资源视图下,String Table中的ID.可以自己构建.在末尾添加编辑即可.
			*/

实例1---在窗口中输出指定的字符串(OnDraw函数中添加)

	void CtextView::OnDraw(CDC* pDC)
	{
		CtextDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		// TODO: 在此处为本机数据添加绘制代码
		CString str("VC++ 深入详解");
		pDC->TextOut(60, 60, str);	/*在(50,50)的位置显示str字符串*/
	}

实例2---使用添加字符串资源的方法在窗口中输出指定字符串

	void CtextView::OnDraw(CDC* pDC)
	{
		CtextDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		// TODO: 在此处为本机数据添加绘制代码
	
		CString str("VC++ 深入详解");
		pDC->TextOut(60, 60, str);
	
		str.LoadString(IDS_STRING101);
		/*
			IDS_STRING101是自己在String Table中添加的.
		*/
		pDC->TextOutW(0, 200, str);	//(0,200)的位置显示str
	}

### 5.3 路径

设备描述表中有一个路径层(path bracket).

路径层:界定一个范围(特殊区域),主要和裁剪区域共同使用.如果与其他操作有重叠部分,则对其他的操作无影响.路径层利用CDC类的BeginPath和EndPath这两个函数来实现.

**获得字符串显示时所占据的宽度和高度:CDC类的GetTextExtent函数**

	CSize GetTextExtent(const CString& str) const;
	/*
		para:一个字符串.此处为字符串的引用
		retval:CSize类型的对象.CSize包含两个成员:cx, cy(分别表示字符串的宽度和高度).
	*/

CDC类的GetTextMetrics是获得设备描述表中当前字体的度量信息.与GetTextExtent不同.

实例---使用路径层

	void CtextView::OnDraw(CDC* pDC)
	{
		CtextDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		// TODO: 在此处为本机数据添加绘制代码
	
		CString str("VC++ 深入详解");
		pDC->TextOut(60, 60, str);
	
		CSize cs = pDC->GetTextExtent(str);	//得到字符串显示时所占据的宽度和高度
	
		str.LoadString(IDS_STRING101);
		pDC->TextOutW(0, 200, str);
	
		//pDC->BeginPath();
		/*
		如果没有注释掉,表示圈定一个矩形返回.该矩形返回凌驾于其他操作之上,但是不会对其他操作产生影响.
		(即该显示的还是照常显示);
		如果注释掉了,表示绘制一个矩形.由于矩形默认会采用设备描述表中的白色画刷填充,此时只能看到矩形
		区域,前面的字符串("VC++ 深入详解")看不到了.
		*/
		pDC->Rectangle(60, 60, 60 + cs.cx, 60 + cs.cy);
		//pDC->EndPath();
		/*表示结束路径层*/
	}

**裁剪区域(clippint region):一个绘图区域,大小可由自己限定.整个客户区为最大的一个裁剪区域.主要用于和路径层产生一个"排除路径层"或者"只选择路径层显示"的效果.**

CDC类的SelectClipPath函数用于设置裁剪区域和路径层的互操作的形式:

	BOOL SelectClipPath(int nMode);
	/*
		para:指定互操作模式.
			为"RGN_DIFF"---排除设置的路径层区域
			为"RGN_AND"---当前裁剪区域和设置的路径层区域的交集(即只选择路径层显示)
	*/

实例---显示网格,但到设置路径层的位置让网格不穿过所设置的矩形区域/只保留矩形区域的网格

	void CtextView::OnDraw(CDC* pDC)
	{
		CtextDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		// TODO: 在此处为本机数据添加绘制代码
	
		CString str("VC++ 深入详解");
		pDC->TextOut(60, 60, str);
	
		CSize cs = pDC->GetTextExtent(str);
	
		str.LoadString(IDS_STRING101);
		pDC->TextOutW(0, 200, str);
	
		pDC->BeginPath();
		pDC->Rectangle(60, 60, 60 + cs.cx, 60 + cs.cy);
		pDC->EndPath();
	
		pDC->SelectClipPath(RGN_DIFF);
		/*
			RGN_DIFF:后续操作显示当前裁剪区域(整个客户区)排除掉路径层设置的矩形区域.
			但对矩形区域那里原本就显示有的字符串("VC++ 深入详解")无影响.
			如果选择RGN_DIFF:后续操作显示当前裁剪区域(整个客户区)与路径层区域的交集.
			但对矩形区域那里原本就显示有的字符串("VC++ 深入详解")无影响.
		*/
	
		for (int i=0; i<300; i+=10)	//显示一个网格
		{
			pDC->MoveTo(0, i);
			pDC->LineTo(300, i);
			pDC->MoveTo(i, 0);
			pDC->LineTo(i, 300);
		}
	}

### 5.4 字符输入

**1.为CTextView类添加保存插入点的成员变量、保存字符串的成员变量以及鼠标左键按下消息的响应函数:**

	1.添加保存插入点的成员变量m_ptOrigin;
	2.添加保存输入字符串的成员变量m_strLine;
	3.添加鼠标左键按下响应函数,并添加代码:
		void CtextView::OnLButtonDown(UINT nFlags, CPoint point)
		{
			// TODO: 在此添加消息处理程序代码和/或调用默认值
			SetCaretPos(point);	
			/*SetCaretPos:移动插入点为鼠标左键按下的位置.	
				para:插入点.*/
			m_strLine = (_T(""));
			/*当重新设置插入点时,需要清空保存的字符串.
				m_strLine = (_T(""));	//VS2010需要这样清空
			或者使用:
				m_strLine.Empty();	//清空字符串
			*/
			m_ptOrigin = point;	//保存插入点
			CView::OnLButtonDown(nFlags, point);
		}

**2.添加WM_CHAR消息的响应函数,并考虑输入回车字符和退格键(Backspace)的处理.**

	1.添加WM_CHAR消息的响应函数OnChar;
	2.回车键的处理(ASCII码是0x0d)
		输入回车键,插入符换到下一行.此时插入符的横坐标不变,纵坐标加上当前字体高度
		(由DC的GetTextMetrics函数可获得).并清空保存的字符串
	3.退格键的处理(ASCII码是0x08)
		1)设置当前文本颜色为背景色
			COLORREF clr = dc.SetTextColor(dc.GetBkColor());
		2)让当前文本以背景色显示,相当于擦除当前所有文本
			dc.TextOut(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
		3)删掉文本的最后一个字符
			m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);
			/*
			Left:取字符串左边para个字符.
			GetLength:得到字符串的长度.
			*/
		4)将原本的背景色再设置回去
			dc.SetTextColor(clr);
	4.如果是按下其他键,曾增加到字符串中
		m_strLine += (wchar_t)nChar;	//VS2010必须将字符转成"wchar_t"形式.
	5.随着字符的输入移动插入符
		CSize sz = dc.GetTextExtent(m_strLine);	//得到字符串的宽度和高度
		CPoint pt;
		pt.x = m_ptOrigin.x + sz.cx;	//移动横坐标
		pt.y = m_ptOrigin.y;			//纵坐标不变
		SetCaretPos(pt);
	6.将文本重新再输出
		dc.TextOut(m_ptOrigin.x, m_ptOrigin.y, m_strLine);

**实例---OnChar函数代码**
	
	void CtextView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CClientDC dc(this);
		TEXTMETRIC tm;
		dc.GetTextMetrics(&tm);
		if (0x0d == nChar)	//Enter key
		{
			m_strLine.Empty();
			m_ptOrigin.y += tm.tmHeight;
		} else if (0x08 == nChar)	//BackSpace key
		{
			COLORREF clr = dc.SetTextColor(dc.GetBkColor());
			//dc.TextOut(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
			m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);
			dc.SetTextColor(clr);
		} else
		{
			m_strLine += (wchar_t)nChar;
		}
	
		CSize sz = dc.GetTextExtent(m_strLine);
		CPoint pt;
		pt.x = m_ptOrigin.x + sz.cx;
		pt.y = m_ptOrigin.y;
		SetCaretPos(pt);
	
		dc.TextOut(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
		CView::OnChar(nChar, nRepCnt, nFlags);
	}

#### 5.4.1 设置显示的字体

MFC提供的CFont类用来专门设置字体.

1.创建设置CFont字体对象

	CFont font;

2.初始化CFont对象---一般使用CFont类的CreatePointFont成员函数

	BOOL CreatePointFont(int nPointSize, LPCTSTR lpszFaceName, CDC *pDC=NULL);
	/*
		para1:创建字体的高度,单位是一个点的十分之一.e.g.如果该值为120,则是创建一个12个点的字体
		para2:字体的名称.e.g."楷体"、"宋体"等名称.
		para3:CDC对象的指针.用来把para1制定指定的高度转换为逻辑单位.如果该值为空,则使用一个
			屏幕设备描述表来完成这种转换.
	*/

3.将所设置的字体选入设备描述表---使用CDC类的SelectObject成员函数.在结束后并恢复

	CFont *pOldFont = dc.SelectObject(&font);
	...
	dc.SelectObject(pOldFont);	//恢复到之前的字体

实例---在OnChar设置显示的字体为楷体

	void CtextView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		CClientDC dc(this);
	+	CFont font;
	+	font.CreatePointFont(300, (LPCTSTR)"楷体", NULL);	//vs2010中para2需要转换成LPCTSTR
	+	CFont *pOldFont = dc.SelectObject(&font);
		TEXTMETRIC tm;
		dc.GetTextMetrics(&tm);
		if (0x0d == nChar)	//Enter key
		{
			m_strLine.Empty();
			m_ptOrigin.y += tm.tmHeight;
		} else if (0x08 == nChar)	//BackSpace key
		{
			COLORREF clr = dc.SetTextColor(dc.GetBkColor());
			//dc.TextOut(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
			m_strLine = m_strLine.Left(m_strLine.GetLength() - 1);
			dc.SetTextColor(clr);
		} else
		{
			m_strLine += (wchar_t)nChar;
		}
	
		CSize sz = dc.GetTextExtent(m_strLine);
		CPoint pt;
		pt.x = m_ptOrigin.x + sz.cx;
		pt.y = m_ptOrigin.y;
		SetCaretPos(pt);
	
		dc.TextOut(m_ptOrigin.x, m_ptOrigin.y, m_strLine);
	+	dc.SelectObject(pOldFont);
		CView::OnChar(nChar, nRepCnt, nFlags);
	}
	
#### 5.4.2 字幕变色功能的实现

1.设置在指定矩形范围内输出文字---CDC类的DrawText函数实现

	int DrawText(const CString &str, LPRECT lpRect, UINT nFormat);
	/*
		para1:指定要输出的字符串
		para2:指定文字显示范围的矩形
		para3:指定文本输出的格式.
			DT_LEFT--->从字符串的左边开始,逐渐向右输出文字;
			DT_RIGHT--->从字符串的右边开始输出,逐渐向左输出文字;
			DT_CENTER--->从字符串中间字符开始向两边扩展.
	*/

2.在OnCreate函数中添加定时器,用于发出定时器消息---CWnd类的SetTimer成员函数可以设置定时器

	UINT SetTime(UINT nIDEvent, UINT nElapse, void (CALLBACK EXPORT *lpfnTimer)(HWND, UINT, UINT, DWORD));
	/*
		para1:指定一个非零值的定时器标识.用于标识一个定时器,并将该标识返回.后续定时器响应函数中应用该标识可以
			知道具体是哪个定时器;
		para2:指定定时器时间间隔,即每隔多久发送一次定时器消息(WM_TIMER).以毫秒(ms)为单位.
			e.g.该值为1000表示每隔1s发送一次定时器消息;
		para3:一个回调函数,一般指定为NULL即可.表示发出的WM_TIMER消息会放到消息队列中,然后由程序响应此消息的窗口对象来处理.
	*/

	/*在OnCreate函数中设置定时器(响应WM_CREATE消息)*/
	int CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		...
		
		SetTimer(1, 100, NULL);
		/*标识符为1,每个100ms发出一次定时器消息.无回调函数*/
		
		return 0;
	}

3.添加响应WM_TIMER消息的响应函数OnTimer,并添加一个保存矩形宽度值不断增加的成员变量m_nWidth.

	1.添加一个保存矩形宽度值不断增加的成员变量m_nWidth;
	2.添加响应WM_TIMER消息的响应函数OnTimer,并在OnTimer中添加处理代码
	void CTextView::OnTimer(UINT nIDEvent)
	{
		m_nWidth += 5;	//按5个像素点增加

		CClientDC dc(this);
		TEXTMETRIC tm;	//保存设备描述表中的字体信息
		dc.GetTextMetrics(&tm);
		CRect rect;
		rect.left = 0;
		rect.top = 200;		//左上角点
		rect.right = m_nWidth;	//宽度不断变化
		rect.bottom = rect.top + tm.tmHeight;	//高度不变

		dc.SetTextColor(RGB(255, 0, 0));	//设置字体颜色为红色
		CString str;
		str.LoadString(IDS_STRING101);
		/*IDS_STRING101是自己在String Table中添加的*/
		dc.DrawText(str, rect, DT_LEFT);	//从字符串的左边开始,逐渐向右输出文字

		CView::OnTimer(nIDEvent);
	}

	--------------------------------------------------------------
	/*设置右对齐显示*/
	void CTextView::OnTimer(UINT nIDEvent)
	{
		m_nWidth += 5;	//按5个像素点增加

		CClientDC dc(this);
		TEXTMETRIC tm;	//保存设备描述表中的字体信息
		dc.GetTextMetrics(&tm);
		CRect rect;
		rect.left = 0;
		rect.top = 200;		//左上角点
		rect.right = m_nWidth;	//宽度不断变化
		rect.bottom = rect.top + tm.tmHeight;	//高度不变

		dc.SetTextColor(RGB(255, 0, 0));	//设置字体颜色为红色
		CString str;
		str.LoadString(IDS_STRING101);
		/*IDS_STRING101是自己在String Table中添加的*/
		dc.DrawText(str, rect, DT_LEFT);	//从字符串的左边开始,逐渐向右输出文字

	+	rect.top = 150;
	+	rect.bottom = rect.top + tm.tmHeight;
	+	dc.DrawText(str, rect, DT_RIGHT);

		CView::OnTimer(nIDEvent);
	}

	--------------------------------------------------------------
	/*设置当颜色变色完设置为另一种颜色*/
	/*设置右对齐显示*/
	void CTextView::OnTimer(UINT nIDEvent)
	{
		m_nWidth += 5;	//按5个像素点增加

		CClientDC dc(this);
		TEXTMETRIC tm;	//保存设备描述表中的字体信息
		dc.GetTextMetrics(&tm);
		CRect rect;
		rect.left = 0;
		rect.top = 200;		//左上角点
		rect.right = m_nWidth;	//宽度不断变化
		rect.bottom = rect.top + tm.tmHeight;	//高度不变

		dc.SetTextColor(RGB(255, 0, 0));	//设置字体颜色为红色
		CString str;
		str.LoadString(IDS_STRING101);
		/*IDS_STRING101是自己在String Table中添加的*/
		dc.DrawText(str, rect, DT_LEFT);	//从字符串的左边开始,逐渐向右输出文字

		rect.top = 150;
		rect.bottom = rect.top + tm.tmHeight;
		dc.DrawText(str, rect, DT_RIGHT);

		CSize sz = dc.GetTextExtent(str);	//得到字符串的宽度和高度信息
		if (m_nWitdh > sz.cx)	//当矩形宽度超过字符串的宽度时设置为另一种颜色
		{
			m_nWidth = 0;
			dc.SetTextColor(RGB(0, 255, 0));	//设置文本颜色为绿色
			dc.TextOut(0, 200, str);
		}

		CView::OnTimer(nIDEvent);
	}
***
## Chapter 6 菜单

### 6.1 菜单命令响应函数

**添加一个菜单项,并添加响应函数**

	1.在资源视图下,双击"Menu->Menu.rc->Menu->IDR_MAINFRAME"菜单资源
		(前面Menu是新建的MFC文件名是Menu);
	2.在右侧显示的菜单编辑器中.在"帮助"菜单后右键->新插入(I)即可得到一个新的菜单项.需要如下设置;
		在属性窗口中(如没有可以右键选择属性):
		1.Caption--->输入该菜单的名字;
		2.Popup--->选择False(决定是否是弹出菜单,像文件、编辑、视图等顶层菜单),表示不是弹出式菜单;
		3.ID--->IDM_TEST(M表示菜单Menu,后面加上该菜单的名字).
			e.g.IDC--->Cursor(光标);IDI--->Icon(图标)
	3.添加该菜单项的响应函数:
		1.打开类向导(Class Wizard),快捷键Ctrl+Shift+x.
		2.项目选择Menu;类名选择CMainFrame;命令中对象ID(B):选择IDM_TEST;
			消息(S)选择COMMAND.在底部成员函数(M)会显示创建的响应函数的相关信息.
		3.选择编辑代码(E)定位到所添加的成员函数位置.
	4.在响应函数中添加如下代码:
		void CMainFrame::OnTest()
		{
			// TODO: 在此添加命令处理程序代码
			MessageBox(_T("MainFrame clicked!"));	//弹出一个消息框.
		}

**菜单分类:**

	1.弹出式菜单(Popup设置为True的菜单).MFC中的顶层菜单.e.g.文件、编辑、查看等.也叫子菜单
		由于设置了Popup为True,因此这种菜单不能响应命令.而且其ID项也不能修改(灰色显示)
	2.菜单项(Popup设置为False的菜单).MFC子菜单下面的各个菜单.e.g.文件菜单下面的新建菜单.
		这种菜单的ID可以输入和修改

### 6.2 菜单命令的路由

#### 6.2.1 程序类对菜单命令的响应顺序

CMenuApp类和CMenuDoc都不是从CWnd类派生的,因此他们都没有MessageBox成员函数.如果需要弹出消息对话框,可以使用全局的MessageBox(::MessageBox)或者应用程序框架的函数:AfxMessageBox(也是全局函数).声明如下:

	int AfxMessageBox(LPCTSTR lpszText, UINT nType=MB_OK, UINT nIDHelp=0);
	/*因为后两个参数都有默认值,因此一般只需要给第一个参数赋值需要显示的字符串即可.*/
	e.g.
	1.在CMenuApp类的OnTest函数添加:
		AfxMessageBox(_T("App clicked!"));
	2.在CMenuDoc类的OnTest函数添加:
		AfxMessageBox(_T("Doc clicked!"));

CMenuView类和CMainFrame类都是直接从CWnd类派生的,因此可以直接使用MessageBox函数.

**菜单项命令响应顺序依次是:视类、文档类、框架类、应用程序类.一般在框架类添加菜单命令的响应函数.**

#### 6.2.2 Windows消息的分类

Windows消息主要分为三类:

	1)标准消息--->除了WM_COMMAND之外,其他所有以"WM_"开头的消息都是标准消息.从CWnd派生的类都可以接收到这类消息.
	2)命令消息--->来自菜单、加速键或工具栏按钮的消息.此类消息以WM_COMMAND形式呈现.
		MFC中,通过菜单项标识(ID)来区分不同的命令消息;在SDK中,通过消息的wParam参数来识别.从CCmdTarget派生的类,
		都可以接收命令消息.
	3)通告消息--->由控件产生的消息.e.g.按钮的单击、列表框的选择等都会产生这类消息,目的是为了向其父窗口(通常是对话框)
		通知事件的发生.这类消息也是以WM_COMMAND形式呈现.从CCmdTarget派生的类,都可以接收此类消息.
	
	PS:
	1->由于CWnd类派生于CCmdTarget类.因此从CWnd派生的类(e.g.CFramwork类和CxxxView类)可以接收全部类型的消息;
	2->对于只从CCmdTarget派生的类(e.g.CxxxDoc类和CxxxApp类),他们只能接收命令消息和通告消息,不能接收标准消息.

#### 6.2.3 菜单命令的路由

**使用类向导添加Test菜单项的命令响应函数内部机制(主要有3处信息)**

1.添加了命令消息响应函数原型---在头文件中:

	在类的头文件中.e.g.CTestView类的头文件中

	// 生成的消息映射函数
	protected:
		DECLARE_MESSAGE_MAP()
	public:
		afx_msg void OnTest();	
		//afx_msg是一个宏,表明该函数是一个消息相应函数的声明.
	};

2.添加消息映射宏---在源文件中:

	在类的源文件中.e.g.CTestView类的源文件中:
	
	BEGIN_MESSAGE_MAP(CtestView, CView)	//该宏到END宏定义了该类的消息映射表.
	ON_COMMAND(IDM_TEST, OnTest)	//添加了ON_COMMAND宏,将菜单ID号与命令响应函数关联起来.
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	END_MESSAGE_MAP()

3.命令消息响应函数的实现---在源文件中:

	void CtestView::OnTest()
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值

	}

**菜单命令消息路由的具体过程:当点击某个菜单项时,最先接收到这个菜单命令消息的是框架类.框架类把接收到的这个消息交给它的子窗口,即视类,由视类首先进行处理.视类首先根据命令消息映射机制查找自身是否对此消息进行了响应,如果响应了,就调用响应函数对这个消息进行处理,消息路由过程结束;如果没有响应就交给文档类,文档类也进行一样的操作,响应了就结束,没有响应就把这个消息交还给视类,视类又把消息交还给框架类.框架类也进行一样的操作,响应了就结束,没有响应就交给应用程序类,由应用程序类做最后的处理.**

### 6.3 基本菜单操作

菜单项:可以通过菜单项的标识ID或者位置索引(从0开始)进行访问(e.g.文件下面的新建菜单就是菜单项).

子菜单:只能通过索引号进行访问,因为子菜单没有标识号(e.g.文件、编辑等都属于子菜单).

主菜单:整个菜单条就是主菜单,主菜单属于框架窗口.

#### 6.3.1 标记菜单

标记菜单:菜单项前面带有一个对号(√)的叫标记菜单.

由于主菜单属于框架窗口的一部分,因此需要在框架类窗口创建完成之后再去访问菜单对象,即需要在CMainFrame类的OnCreate函数的最后(return之前实现标记菜单的功能).

**为文件子菜单中的新建菜单项添加标记步骤:**

	1.获得程序的菜单栏(即主菜单),使用CWnd的成员函数:GetMenu()来实现
		CMenu *GetMenu() const;	//返回指向菜单栏(即主菜单)的指针
	2.获得子菜单:通过指向菜单栏的指针获得指向某个索引号的子菜单的指针,通过CMenu类的GetSubMenu()成员函数实现
		CMenu *GetSubMenu(int nPos) const;
		/*
			para:子菜单的索引号(从0开始)
			retval:返回指向由参数nPos指定的子菜单的指针.
		*/
	3.对某个菜单项添加/移除标记:通过子菜单对其下的菜单项进行添加/移除标记的操作.通过CMenu类的CheckMenuItem成员函数实现
		UINT CheckMenuItem(UINT nIDCheckItem, UINT nCheck);
		/*
			para1:使用索引号或者命令ID来指定需要处理的菜单项,选择由第二个参数决定.
			para2:指定怎样设置菜单项以及如何定位菜单项的位置.取值为:
				MF_CHECKED:设置菜单项的复选标记,即为标记菜单;
				MF_UNCHECKED:移除菜单项的复选标记
				MF_BYPOSITION:指定通过菜单项的位置来访问菜单项,即第一个参数为菜单项的索引号
				MF_BYCOMMAND:指定通过菜单项的命令ID来访问菜单项,即第一个参数为菜单项的命令ID
		*/

实例1---通过索引号为"文件"子菜单中的新建菜单项添加标记

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		...
		/*在return之前添加*/
		GetMenu()->GetSubMenu(0)->CheckMenuItem(0, MF_BYPOSITION | MF_CHECKED);
		/*
			文件子菜单的索引号为0.文件下的新建菜单项的索引号也为0
		*/
		
		return 0;
	}

实例2---通过菜单项标识为"文件"子菜单中的新建菜单项添加标记

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		...
		/*在return之前添加*/
		GetMenu()->GetSubMenu(0)->CheckMenuItem(ID_FILE_NEW, MF_BYCOMMAND | MF_CHECKED);

		return 0;
	}

#### 6.3.2 默认菜单项

默认菜单项:子菜单下有某个菜单项(只有一个)以粗体形式显示的就是该子菜单的默认菜单项.

默认菜单项的实现,利用CMenu类的SetDefaultItem成员函数实现

	BOOL SetDefaultItem(UINT uItem, BOOL fByPos = FALSE);
	/*
		para1:使用索引号或命令ID来指定需要设置为默认菜单项的菜单项,选择由第二个参数决定.
		para2:
			FALSE->第一个参数是菜单项的标识(即命令ID)
			TRUE->第一个参数为位置索引(即索引号)
	*/

实例1---通过索引号设置"文件"子菜单中的打开菜单项为默认菜单项

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		...
		/*在return之前添加*/
		GetMenu()->GetSubMenu(0)->CheckMenuItem(0, MF_BYPOSITION | MF_CHECKED);
		GetMenu()->GetSubMenu(0)->SetDefaultItem(1, TRUE);		
		
		return 0;
	}

实例2---通过菜单项标识设置"文件"子菜单中的打开菜单项为默认菜单项

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		...
		/*在return之前添加*/
		GetMenu()->GetSubMenu(0)->CheckMenuItem(0, MF_BYPOSITION | MF_CHECKED);
		GetMenu()->GetSubMenu(0)->SetDefaultItem(ID_FILE_OPEN, FALSE);
		/*打开菜单项标识为:ID_FILE_OPEN*/		
		
		return 0;
	}

**需要注意的点:**
	
	1.菜单项索引号的计算:分隔栏在菜单项中是占据一个索引位置的;
	2.一个子菜单中的菜单项中只有一个默认菜单项.

#### 6.3.3 图形标记菜单

图形标记菜单:菜单项前面带有图形的叫做图形标记菜单.

设置"打开"子菜单下的"新建"菜单项为图形标记菜单步骤:

	1.为CMainFrame类添加一个CBitmap类型的成员变量m_bitmap
	2.为m_bitmap成员变量加载位图资源
		m_bitmap.LoadBitmap(IDB_BITMAP1);	//IDB_BITMAP1是自己创建的位图资源
	3.调整位图资源的尺寸
		int GetSystemMetrics(int nIndex);	//得到图形标记菜单上显示位图的尺寸大小值
		/*
			para:
				SM_CXMENUCHECK:此时返回值为标记图形的宽度.即位图资源的宽度应该设置为该值
				SM_CYMENUCHECK:此时返回值为标记图形的高度.即位图资源的高度应该设置为该值
		*/
		e.g.
		CString str;
		str.Format(_T("x=%d, y=%d"), GetSystemMetrics(SM_CXMENUCHECK), GetSystemMetrics(SM_CYMENUCHECK));
		/*上述必须转换"_T",否则会报错:
		error C2664: “void ATL::CStringT<BaseType,StringTraits>::Format(const wchar_t 
		*,...)”: 不能将参数 1 从“const char [3]”转换为“const wchar_t *”. 
		*/
		/*str.Format():按照一定的格式将结果保存到str中.*/
		MessageBox(_T(str));	//此时可以打印出位图资源应该有的宽度和高度.
		
		PS:通过拖动改变位图资源的大小和上面MessageBox大小一样.拖动时右下角有一格用于显示当前位图的大小.
	4.将指定的位图与菜单项关联起来,利用CMenu类的SetMenuItemBitmaps函数实现
		BOOL SetMenuItemBitmaps(UINT nPosition, UINT nFlags, 
			const CBitmap *pBmpUnchecked, const CBitmap *pBmpChecked);
		/*
			para1:取值由第二个参数决定.
			para2:
				MF_BYCOMMAND-->para1是菜单项标识(ID)
				MF_BYPOSITION-->para1是菜单项的位置索引
			para3:指定取消菜单项选中状态时显示的位图
			para4:指定选中菜单项时显示的位图
		*/

实例---设置"打开"子菜单下的"新建"菜单项为图形标记菜单

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		...
		/*在return之前添加*/
		GetMenu()->GetSubMenu(0)->CheckMenuItem(0, MF_BYPOSITION | MF_CHECKED);
		GetMenu()->GetSubMenu(0)->SetDefaultItem(ID_FILE_OPEN, FALSE);
		/*打开菜单项标识为:ID_FILE_OPEN*/
		CString str;
		str.Format(_T("x=%d, y=%d"), GetSystemMetrics(SM_CXMENUCHECK), GetSystemMetrics(SM_CYMENUCHECK));
		/*上述必须转换"_T",否则会报错:
		error C2664: “void ATL::CStringT<BaseType,StringTraits>::Format(const wchar_t 
		*,...)”: 不能将参数 1 从“const char [3]”转换为“const wchar_t *”. 
		*/
		MessageBox(str);	//调整好了位图资源的大小,上述显示标记图形的宽度和高度可以省略.

		m_bitmap.LoadBitmap(IDB_BITMAP1);
		GetMenu()->GetSubMenu(0)->SetMenuItemBitmaps(0, MF_BYPOSITION, &m_bitmap, &m_bitmap);
		
		return 0;
	}

#### 6.3.4 禁用菜单项

禁用某个菜单项的步骤:

	1.在CMainFrame类的构造函数中把m_bAutoMenuEnable成员变量设置为FALSE;
		此时就不需要对ON_UPDATE_COMMAND_UI或ON_COMMAND消息进行响应处理,CMenu类的
		EnableMenuItem函数(禁用菜单项的函数)就能够正常工作.
	2.禁用某个菜单项,利用CMenu类的EnalbeMenuItem函数来实现
		UINT EnableMenuItem(UINT nIDEnableItem, UINT nEnable);
		/*
			para1:由第二个参数决定;
			para2:
				MY_BYCOMMAND->指定第一个参数为菜单项的标识ID;
				MY_BYPOSITION->指定第一个参数为菜单项的位置索引;
				MF_DISABLED->禁用菜单项VS2010显示为灰色
				MF_ENABLED->使菜单项可用,用户可以选择这个菜单项;
				MF_GRAYED->禁用菜单项,灰色显示
			PS:
			para2中,一般MF_DISABLED和MF_GRAYED一起使用.
		*/

实例1---通过索引号禁用"文件"子菜单中的打开菜单项

	/*已经在构造函数中将m_bAutoMenuEnable成员变量设置为FALSE*/

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;
	
		if (!m_wndStatusBar.Create(this))
		{
			TRACE0("未能创建状态栏\n");
			return -1;      // 未能创建
		}
		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	
		GetMenu()->GetSubMenu(0)->EnableMenuItem(1, MF_BYPOSITION | MF_DISABLED | MF_GRAYED);
	
		return 0;
	}

实例2---通过菜单项标识禁用"文件"子菜单中的打开菜单项

	/*已经在构造函数中将m_bAutoMenuEnable成员变量设置为FALSE*/

	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;
	
		if (!m_wndStatusBar.Create(this))
		{
			TRACE0("未能创建状态栏\n");
			return -1;      // 未能创建
		}
		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_FILE_OPEN, 
				MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
	
		return 0;
	}

#### 6.3.5 移除和装载菜单

移除菜单:

	调用CWnd类的SetMenu函数实现:
		BOOL SetMenu(CMenu *pMenu);
		/*
			para:CMenu类型的指针,指向一个新菜单对象.如果为NULL,则表示移除当前菜单.
		*/
	
	e.g.在CMainFrame类的OnCreate函数中设置移除菜单
	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;
	
		if (!m_wndStatusBar.Create(this))
		{
			TRACE0("未能创建状态栏\n");
			return -1;      // 未能创建
		}
		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_FILE_OPEN, 
				MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		SetMenu(NULL);	//移除菜单
		
		return 0;
	}
	

重新装载菜单步骤:

	1.在CMainFrame类中定义一个CMenu菜单对象的成员变量m_menu;
	2.为CMenu对象加载一个菜单资源:
		m_menu.LoadMenu(IDR_MAINFRAME);	//IDR_MAINFRAME是在资源视图->Menu下显示的菜单资源ID.
	3.调用CWnd类的SetMenu函数实现重新装载菜单
		SetMenu(&m_menu);

	e.g.在CMainFrame类的OnCreate函数中设置移除菜单后重新状态菜单
	int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;
	
		if (!m_wndStatusBar.Create(this))
		{
			TRACE0("未能创建状态栏\n");
			return -1;      // 未能创建
		}
		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_FILE_OPEN, 
				MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		SetMenu(NULL);	//移除菜单
		
		m_menu.LoadMenu(IDR_MAINFRAME);
		SetMenu(&m_menu);
		
		return 0;
	}

	//如果在OnCreate函数中声明局部变量menu,可以使用CMenu类的Detach函数实现菜单句柄与菜单对象分离.
	//此时菜单对象的销毁不会影响到菜单句柄.同样可以得到和定义成员变量一样的效果
		int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
	{
		if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
			return -1;
	
		if (!m_wndStatusBar.Create(this))
		{
			TRACE0("未能创建状态栏\n");
			return -1;      // 未能创建
		}
		m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));
	
		GetMenu()->GetSubMenu(0)->EnableMenuItem(ID_FILE_OPEN, 
				MF_BYCOMMAND | MF_DISABLED | MF_GRAYED);
		SetMenu(NULL);	//移除菜单
		
		CMenu menu;
		menu.LoadMenu(IDR_MAINFRAME);
		SetMenu(&menu);
		menu.Detach();	//菜单对象与菜单句柄分离
		
		return 0;
	}

#### 6.3.6 MFC菜单命令更新机制

设置菜单项的状态方法---最好的方法

	1.通过类向导(Class Wizard)为一个菜单项添加UPDATE_COMMAND_UI消息响应函数.
	2.在响应函数中对菜单项的状态进行设置
		void CMainFrame::OnUpdateEditCut(CCmdUI *pCmdUI)
		{
			// TODO: 在此添加命令更新用户界面处理程序代码
			/*
				利用CCmdUI的指针,可以决定一个菜单项是否可以使用(Enable函数)、
				是否有标记,还可以改变菜单项的文本.
			*/
			pCmdUI->Enable(TRUE);
			/*
				Enable函数设置一个菜单项是否可以使用:
					para=TRUE--->表示菜单项可用
					para=FALSE--->表示禁用该菜单项
			*/
			/*
				CCmdUI类的其他成员变量:
					pCmdUI->m_nID:表示当前菜单项、工具栏按钮的标识ID;
					pCmdUI->m_nIndex:表示当前菜单项的位置索引.
			*/
		}

**工具栏按钮和菜单栏中的某个菜单项相关联:只要将他们的ID设置为同一个标识即可.**

由于工具栏上计算位置索引和菜单栏中某个菜单项计算位置索引可能不一致.因此在引用菜单栏中菜单项或工具栏中的工具按钮最好使用菜单项标识(e.g.ID_EDIT_CUT--->剪切)

#### 6.3.7 快捷菜单

快捷菜单也叫右键菜单,是单击鼠标右键弹出的菜单.

添加快捷菜单步骤:

	1.为Menu程序增加一个新的菜单资源IDR_MENU1,并编辑该菜单资源
		1.快捷菜单显示时,顶级菜单是不出现的.因此可以设置任意文本(e.g.设置Caption为defy).同时只需要设置一个菜单项即可
			(abc这一个子菜单即可),一般顶级菜单popup为True,标识为
		2.在子菜单下添加两个菜单项
			菜单1.Caption为"显示",ID为IDM_SHOW;
			菜单2.Caption为"退出",ID为IDM_EXIT.
	2.给CMenuView类添加WM_RBUTTONDOWN(即右键按下)的消息响应函数,并添加实现代码:
		/*因为视类始终会覆盖在框架类之上,鼠标操作消息框架类捕捉不到*/

		void CtestView::OnRButtonDown(UINT nFlags, CPoint point)
		{
			// TODO: 在此添加消息处理程序代码和/或调用默认值
			CMenu menu;
			menu.LoadMenu(IDR_MENU1);	//加载一个菜单资源
			CMenu *pPopup = menu.GetSubMenu(0);	//得到菜单资源的第0个子菜单

			ClientToScreen(&point);	//将客户区坐标转换为屏幕坐标
			/*
				屏幕坐标:以PC显示屏左上角为原点的坐标;
				客户区坐标:以程序运行时客户区的左上角
				因为后面的TrackPopupMenu是使用屏幕坐标,因此需要进行转换.
			*/

			pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
			/*
				TrackPopupMenu用于显示快捷菜单,函数原型为:
				BOOL TrackPopupMenu(UINT nFlags, int x, int y, CWnd *pWnd, LPCRECT lpRect = NULL);
				/*
				para1:指定菜单在屏幕上显示的位置.TPM_LEFTALIGN(左对齐),TPM_RIGHTBUTTON(右键按下的位置).
				para2 & para3:指定快捷菜单显示位置处的x坐标和y坐标.
				para4:拥有快捷菜单的窗口对象,在CMenuView类中只需要指定为this即可.
				para5:指定一块矩形区域,如果用户在该矩形区域内单击鼠标,快捷菜单仍保持显示,否则快捷菜单消失.
					默认为NULL.一般不需要指定,保持默认值(NULL)即可.
				*/
			*/
			CView::OnLButtonDown(nFlags, point);
		}
	3.为Menu程序添加快捷菜单上菜单项的命令响应函数,与前述的给子菜单下的菜单项添加命令响应函数一样:
		void CtestView::OnShow()
		{
			// TODO: 在此添加消息处理程序代码和/或调用默认值
			MessageBox(_T("View Show"));
		}

### 6.4 动态菜单操作

**暂时没看**

***

## Chapter 7 对话框(一)

### 7.1 对话框基本知识

对话框是一个窗口,因此派生于CWnd类.在对话框上可以放置各种各样的标准控件和扩展控件.

#### 7.1.1 常用控件介绍

MFC中,所有控件都派生于CWnd类,因此控件也属于窗口.

**常用控件**

	------------------------------------------------------------------------------
		控件								功能							对应控件类
	------------------------------------------------------------------------------
	静态文本框(Static Text)	显示文本,一般不接受输入信息					Static
	图像控件(Picture)		显示位图、图标、方框和图元文件,一般			Static
								不接受输入信
	编辑框(Edit Box)			编辑正文,支持单行和多行编辑					CEdit
	按钮(CButton)			响应用户输入,触发相应事件					CButton
	复选框(Check Box)		用作标记选择,选中、未选中和不确定三种状态		CButton
	单选按钮(Radio Button)	从两个或多个中选择一个						CButton
	组框(Group Box)			显示正文和方框,将相关的空间组织在一起		CButton
	列表框(List Box)			显示一个列表,用户可以从列表中选择一项或多项	CListBox
	组合框(Combo Box)		编辑框+列表框,有简易式、下拉式和下拉列表式	CComboBox
	滚动条(Scroll Bar)		从一个预定义范围中选取一个有效值			CScrollBar
	------------------------------------------------------------------------------

#### 7.1.2 对话框的种类

**模态对话框**

模态对话框是指当其显示时,程序会暂停执行,直到关闭这个对话框,才能继续执行其他任务.

**非模态对话框**

非模态对话框当其显示时,允许转而执行程序中的其他任务,可以不用关闭这个对话框.

### 7.2 对话框的创建和显示

**模态对话框创建的步骤:**

	/*在一个单文档程序中,单击菜单栏一个子菜单弹出一个模态对话框*/
	1.添加一个对话框资源
		在资源视图下添加一个对话框资源.ID为IDD_DIALOG1;更改其Caption(对话框显示的名字)为Defy.
	2.将创建的对话框资源和一个对话框类关联(MFC中,对资源的操作都是通过一个与资源相关联的类来完成)
		1.选中创建的对话框--->右键--->添加类
		2.在"MFC添加类向导"中输入相关联类的信息:
			类名:输入要创建的类名.e.g.CTestDlg--->类名以C打头.
			基类:选择基类为CDialog
			.h文件和.cpp文件会自动创建
		3.创建的对话框类的函数说明:
			/*DoDataExchange:用来完成对话框数据的交换和校验.*/
			void CTestDlg::DoDataExchange(CDataExchange* pDX)
			{
				CDialog::DoDataExchange(pDX);
			}
	3.为单文档程序创建一个子菜单
		Caption:CTestDlg;	Popup:False;	ID:IDM_DIALOG.
	4.为上述创建的子菜单添加COMMAND消息响应函数OnDialog(),有CxxView类捕捉到
		method 1:直接在子菜单上右键->选择"添加事件处理程序";
		method 2:使用类向导,ID选择IDM_DIALOG.
	5.在响应函数中添加显示模态对话框的代码:
		void CMenuView::OnDialog()
		{
			// TODO: 在此添加命令处理程序代码
			CTestDlg dlg;	//CTestDlg是创建的和对话框关联的对话框类
			dlg.DoModal();	//DoModal()函数显示一个模态对话框
		}
	6.在CxxxView中添加包含CTestDlg类的头文件
		#include "TestDlg.h"	//去掉头部的"C"

**非模态对话框**

略.因为非模态对话框用的比较少.

### 7.3 动态创建按钮

动态创建按钮步骤:

	1.在对话框上添加一个按钮(Button)控件.
		Caption:Add; ID:IDC_BTN_ADD
	2.添加该Add按钮的单击响应函数.在类向导中:
		类选择:CTestDlg(基于对话框类);	命令选择:IDC_BTN_ADD; 消息选择:BN_CLICKED(单击消息)
	3.在单击响应函数OnClickedBtnAdd中添加实现代码:
		void CTestDlg::OnClickedBtnAdd()
		{
			// TODO: 在此添加控件通知处理程序代码
			if (!m_btn.m_hWnd)	//m_btn为创建的CButton的成员变量.此处用于判断按钮是否已经创建
			{
				m_btn.Create(_T("New"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, 
					CRect(0, 0, 100, 100), this, 123);	//创建一个按钮
			}else
			{
				m_btn.DestroyWindow();	//如果已经创建按钮,就销毁.
				//m_btn.m_hWnd = NULL;	//销毁之后,按钮对象的句柄会被置空.因此不需要再置空.
			}
		}

### 7.4 控件的访问

#### 7.4.1 静态文本控件的操作

创建一个静态文本控件"Number1:",当点击到这个静态文本控件,使其文本变为"数值1:".

	1.创建一个静态文本控件(即Static Text控件),并修改属性:
		Caption:"Number1:";	Notify:True(否则不能通告消息(e.g.响应鼠标单击消息))
		ID:IDC_NUMBER1(必须修改ID,因为所有的静态文本控件默认ID都一样,不改在类向导中没有该ID).
	2.在类向导中添加响应单击的消息响应函数:
		命令:IDC_NUMBER1;	消息:STN_CLICKED(鼠标单击消息)
	3.在单击消息响应函数OnClickedNumber1中添加实现代码:
		void CTestDlg::OnClickedNumber1()
		{
			// TODO: 在此添加控件通知处理程序代码
			CString str;
			if (GetDlgItem(IDC_NUMBER1)->GetWindowText(str), str == "Number1:")
			{
				/*
					CWnd *GetDlgItem(int nID) const;	//得到控件对象
					GetWindowText(str);	//得到控件对象中的文本,并存放到CString中
					逗号表达式的结果是最后一个表达式的返回值.

					SetWindowText(_T("xxx"));	//使用字符串设置成控件对象的文本.
				*/
				GetDlgItem(IDC_NUMBER1)->SetWindowText(_T("数值1:"));
			}else
			{
				GetDlgItem(IDC_NUMBER1)->SetWindowText(_T("Number1:"));
			}
		}

#### 7.4.2 编辑框控件的操作---实现简单的加法运算

**步骤:**

1.添加3个静态文本控件,分别命名为"Number1:"、"Number2:"、"Sum:";

2.添加3个编辑框控件,修改其ID为"IDC_ EDIT1"、"IDC_ EDIT2"、"IDC_EDIT3";

3.添加一个按钮控件:

	1.在对话框上添加一个按钮(Button)控件.
		Caption:Add; ID:IDC_BTN_ADD
	2.添加该Add按钮的单击响应函数.在类向导中:
		类选择:CTestDlg(基于对话框类);	命令选择:IDC_BTN_ADD; 消息选择:BN_CLICKED(单击消息)
	3.在单击响应函数OnClickedBtnAdd中添加实现代码:

**实现的第一种方式:**

	void CTestDlg::OnClickedBtnAdd()
	{
		int num1, num2, num3;	//用于保存编辑框中字符串转换后的值
		TCHAR ch1[10], ch2[10], ch3[10];	//用于保存编辑框中的字符串,VS2010需要使用TCHAR
		
		GetDlgItem(IDC_EDIT1)->GetWidowText(ch1, 10);	//para1:接收文本缓冲区的指针;para2:保存在缓冲区的最大字符数
		GetDlgItem(IDC_EDIT2)->GetWindowText(ch2, 10);

		num1 = _ttoi(ch1);	//将数字组成的字符串转换为相应的数值
		num2 = _ttoi(ch2);

		num3 = num1 + num2;
		_itot(num3, ch3, 10);	//表示将num3以10进制的形式形成字符串保存在ch3中
		GetDlgItem(IDC_EDIT3)->SetWindowText((LPCTSTR)ch3);	//将转换后的字符串写入到IDC_EDIT3编辑框中
	}

**实现的第二种方式:**

	void CTestDlg::OnClickedBtnAdd()
	{
		int num1, num2, num3;
		CString str1, str2, str3;	//用于保存编辑框中的字符串
		
		GetDlgItem(IDC_EDIT1)->GetWindowText(str1);	//从编辑框中读到的字符串保存到str1中
		GetDlgItem(IDC_EDIT2)->GetWindowText(str2);

		num1 = _ttoi(str1);
		num2 = _ttoi(str2);
		num3 = num1 + num2;
		str3.Format(_T("%d"), num3);	//将num3以10进制的形式形成字符串保存到str3中
		/*上述必须转换"_T",否则会报错:
		error C2664: “void ATL::CStringT<BaseType,StringTraits>::Format(const wchar_t 
		*,...)”: 不能将参数 1 从“const char [3]”转换为“const wchar_t *”. 
		*/
		GetDlgItem(IDC_EDIT3)->SetWindowText(str3);
	}

**实现的第三种方式:---编辑框与Value类别的成员变量关联**

1.编辑框与int成员变量关联

	打开类向导窗口->切换到"成员变量"页->在控件ID中选择"IDC_EDIT1"->选择添加变量
		成员变量名称:m_num1; 类别:Value(表示为值); 变量类型:int(选择整型,则可以直接运算)
	其他两个类似

相关联后自动添加的代码:

	1.三个成员变量以及在构造函数中进行了初始化
	2.在DoDataExchange函数中:
		void CTestDlg::DoDataExchange(CDataExchange* pDX)
		{
			CDialog::DoDataExchange(pDX);
			DDX_Text(pDX, IDC_EDIT1, m_num1);	//实现对话框控件与类成员变量关联
				//DDX---Dialog Data Exchange,对话框数据交换
				//DDV---Dialog Data Validate,对话框数据校验
			DDX_Text(pDX, IDC_EDIT2, m_num2);
			DDX_Text(pDX, IDC_EDIT3, m_num3);
		}
		/*DoDataExchange实现对话框数据的交换和校验,如果需要获取对话框数据或者设置对话框控件
		(也就是让数据生效)必须调用DoDataExchange函数.但是程序代码不是直接调用该函数,而是
		调用UpdateData函数,进而自动去调用DoataExchange函数*/
		BOOL UpdateData(BOOL bSaveAndValidate = TRUE);
		/*
			para:为TRUE时,表示正在获取对话框的数据;为FALSE时,表示设置对话框控件.
		*/

2.OnClickedBtnAdd函数中代码实现

	void CTestDlg::OnClickedBtnAdd()
	{
		UpdateData(TRUE);	//获取对话框控件的数据
		m_num3 = m_num1 + m_num2;
		UpdateData(FALSE);	//设置对话框控件的数据(更新)
	}

还可以在关联时设置输入数据的范围.

**实现的第四种方式:---编辑框与Control类别的成员变量关联**

1.编辑框与CEdit成员变量关联

	打开类向导窗口->切换到"成员变量"页->在控件ID中选择"IDC_EDIT1"->选择添加变量
		成员变量名称:m_edit1; 类别:Control(表示为控件类型); 变量类型:CEdit(选择编辑框类)
		CEdit类派生于CWnd类.
	其他两个类似

相关联后自动添加的代码:

	1.三个成员变量以及在构造函数中进行了初始化
	2.在DoDataExchange函数中:
		void CTestDlg::DoDataExchange(CDataExchange* pDX)
		{
			CDialog::DoDataExchange(pDX);
			DDX_Control(pDX, IDC_EDIT1, m_edit1);	//实现对话框控件与CEdit变量关联
				//DDX---Dialog Data Exchange,对话框数据交换
				//DDV---Dialog Data Validate,对话框数据校验
			DDX_Control(pDX, IDC_EDIT2, m_edit2);
			DDX_Control(pDX, IDC_EDIT3, m_edit3);
		}

2.OnClickedBtnAdd函数中代码实现

	void CTestDlg::OnClickedBtnAdd()
	{
		int num1, num2, num3;
		TCHAR ch1[10], ch2[10], ch3[10];
		m_edit1.GetWindowText(ch1, 10);	//因为CEdit类派生于CWnd类,因此可以直接使用GetWindowText
		m_edit2.GetWindowText(ch2, 10);

		num1 = _ttoi(ch1);
		num2 = _ttoi(ch2);
		num3 = num1 + num2;
		
		_itot(ch3, num3, 10);
		m_edit3.SetWindowText((LPCTSTR)ch3);
	}

### 7.5 对话框伸缩功能的实现

**实现步骤:**

1.添加一个按钮,并修改属性:

	ID为:IDC_BUTTON1
	Caption为:收缩<<		当用户单击此按钮后,切除对话框的一部分,并将此按钮文本更改为"扩展>>"

2.为上述按钮添加单击(BN_CLICKED)消息响应函数OnClickedBtn1,先实现单击后文本发生变化的代码:

	void CTestDlg::OnClickedBtn1()
	{
		if(GetDlgItem(IDC_BUTTON1)->GetWindowText(str), str == "收缩<<")
		{
			GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("扩展>>"));
		}else
		{
			GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("收缩<<"));
		}
	}

3.在对话框中添加一个分割条,用来划分对话框中要动态切除的部分:

	1.使用VC++提供的图像控件(Picture control)拉出一条线,用来划分对话框要动态切除的部分
		属性设置为:
			ID:IDC_SEPARATOR	Sunken:选择True(此时分隔条呈现出一种下陷的状态)
			Visible:设置为False
	2.获得对话框的原始位置
		static CRect rectLarge;
		GetWindowRect(&rectLarge);	//在对话框类中调用GetWindowRect可以得到对话框的大小信息,并保存到&rectLarge中
	3.获得切除后的对话框的大小和位置
		static CRect rectSmall;	//保存切除后对话框的大小
		
		if(rectLarge.IsRectNull)	//仅执行一次,后续代码用于获取切除前和切除后的对话框大小信息
		{
			CRect rectSeparator;	//保存分隔条的大小信息
			GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator);	//获取分隔条的大小信息

			rectSmall.left = rectLarge.left;
			rectSmall.top = rectLarge.top;
			rectSmall.right = rectLarge.right;
			rectSmall.bottom = rectLarge.bottom;	//只需要更改右下角的纵坐标即可
		}

		CRect判断一个矩形是否为空的两个成员函数:
			1.IsRectEmpty():如果矩形的宽度和高度都为0或是负值则说明矩形为空,返回True,非0值;否则返回0.
			2.IsRectNull():如果矩形的左上角和右下角的四个坐标值都是0则说明矩形为空,返回True,非0值;否则返回0.
			e.g.
				CRect rect1(10, 10, 10, 10);
				CRect rect2(0, 0, 0, 0);
				rect1.IsRectEmpty();	//返回True,非0值
				rect1.IsRectNull();		//返回False,0值
				rect2.IsRectEmpty();	//返回True,非0值
				rect2.IsRectNull();		//返回True,非0值
	4.根据按钮单击情况来更改对话框的大小
		if(str == "收缩<<")
		{
			SetWindowPos(NULL, 0, 0, rectSmall.Width(), rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
		}
		else
		{
			SetWindowPos(NULL, 0, 0， rectLarge.Width(), rectLarge.Height(), SWP_NOMOVE | SWP_NOZORDER);
		}

		/*
			BOOL SetWindowPos(const CWnd *pWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);
			//设置窗口的位置和大小
			/*
				para1:标识一个CWnd对象,以Z次序排序的窗口中位于当前窗口前面的那个窗口对象.一般为NULL即可;
				para2 & para3:窗口左上角的x和y坐标;
				para4 & para5:窗口的宽度和高度;
				para6:设定窗口的尺寸和定位,取值如下:
					SWP_NOMOVE:维持窗口当前位置,将忽略x和y参数
					SWP_NOZORDER:维持当前的Z次序,将忽略pWndInsertAfter参数
			*/
		*/
	
4.实现代码:

	void CTestDlg::OnClickedBtn1()
	{
		if(GetDlgItem(IDC_BUTTON1)->GetWindowText(str), str == "收缩<<")
		{
			GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("扩展>>"));
		}else
		{
			GetDlgItem(IDC_BUTTON1)->SetWindowText(_T("收缩<<"));
		}

		static CRect rectLarge;
		static CRect rectSmall;
		
		if(rectLarge.IsRectNull())
		{
			CRect rectSeparator;
			GetWindowRect(&rectLarge);
			GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator);

			rectSmall.left = rectLarge.left;
			rectSmall.top = rectLarge.top;
			rectSmall.right = rectLarge.right;
			rectSmall.bottom = rectSeparator.bottom;
		}

		if(str == "收缩<<")
		{
			SetWindowPos(NULL, 0, 0, rectSmall.Width(), rectSmall.Height(), SWP_NOMOVE | SWP_NOZORDER);
		}
		else
		{
			SetWindowPos(NULL, 0, 0, rectLarge.Width(), rectLarge.Height(), SWP_NOMOVE | SWP_NOZORDER);
		}
	}

### 7.6 输入焦点的传递

**实现光标在第一个编辑框中,当按下Enter键光标移动到下一个编辑框中**

1.设置一个默认按钮(Enter键按下,是由默认按钮响应):

	本例中,OK按钮是默认按钮.因为其Default Button设置为True.可以更改其他按钮为默认按钮

2.为OK按钮添加消息响应函数(重写OK按钮的消息响应函数)---为了屏蔽掉默认的Enter键关闭对话框

	void CTestDlg::OnBnClickOK()
	{
		//...
		//CDialog::OnOK();	//屏蔽掉默认的按下Enter键关闭对话框的功能
	}

3.实现代码---实现光标的循环移动

	void CTestDlg::OnBnClickOK()
	{
		//...
		GetNextDlgTabItem(GetFocus())->SetFocus();
		/*
			CWnd *GetNextDlgTabItem(CWnd *pWndCtl, BOOL bPrevious = FALSE) const;
			/*
				该函数会按照各子控件的Tab序号循环地查找下一个窗口.
				para1:当前窗口指针;
				para2:使用默认时,表示取下一个窗口;如果为TRUE时表示取前一个窗口.
			*/
			GetFocus():返回当前焦点所在窗口的指针
			SetFocus():设置得到窗口为焦点所在
		*/
		//CDialog::OnOK();	//屏蔽掉默认的按下Enter键关闭对话框的功能
	}

	/*Tab顺序:
		打开对话框资源编辑器,选择格式(D)菜单->Tab键顺序菜单项(或者Ctrl+D),单击即可显示各个控件的Tab序号
		改变Tab序号,只需要双击控件即可.
	*/

PS:对话框中存在默认按钮,当按下Enter键会调用默认按钮的消息响应函数;如果不存在,就会调用虚拟的ID为IDOK的消息响应函数,即虚拟的"OnxxxOk"函数,因此在实际应用中可以将ID为IDOK的按钮删掉,保留消息响应函数.

***

## Chapter 8 对话框(二)

### 8.1 "逃跑"按钮的实现

1.创建一个基于对话框的应用程序:Catchme, 并删除其上自动创建的所有控件.

2.在对话框资源窗口上添加两个按钮控件:

	1.添加一个按钮控件,修改Caption为:Can you catch me?
	2.复制第一个按钮控件,设置其Visible为False(避免两个同时显示),并进行对齐的相关操作
	PS:修改字体在对话框大窗口属性窗口中的Font中设置.

3.创建一个CNewButton的新类,用于响应鼠标移动消息,隐藏按钮

	打开类向导窗口,选择右边的添加类.
		类名:CNewButton;		基类:CButton

4.为对话框中的两个按钮添加成员变量

	在资源视图下,选择需要添加变量的按钮->右键选择添加变量->并设置:
		访问:private;		变量类型输入:CNewButton;	变量名:m_btn1  & m_btn2
	PS:VS2010会自动添加CNewButton的头文件

5.为新创建的CNewButton类添加鼠标移动消息以及一个CNewButton *类型的成员变量

	1.为CNewButton类添加鼠标移动消息
		void CNewButton::OnMouseMove(UINT nFlags, CPoint point)
		{
			// TODO: 在此添加消息处理程序代码和/或调用默认值
	
			CButton::OnMouseMoves(nFlags, point);
		}
	2.添加一个CNewButton * m_pBtn的成员变量
		右键CNewButton类名->添加、添加变量
			访问设置为:public;	变量类型:CNewButton;	变量名:m_pBtn
		PS:m_pBtn用于两个按钮互相保存对方的地址

6.在对话框CCatchmeDlg的OnInitDialog函数中保存按钮相互的地址

	BOOL CCatchmeDlg::OnInitDialog()
	{
		CDialogEx::OnInitDialog();
	
		// 将“关于...”菜单项添加到系统菜单中。
		...
		// TODO: 在此添加额外的初始化代码
	
		m_btn1.m_pBtn = &m_btn2;	//保存按钮相互的地址,m_pBtn是public才能访问
		m_btn2.m_pBtn = &m_btn1;	//保存按钮相互的地址,m_pBtn是public才能访问
	
		return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
	}

	//OnInitDialog函数是WM_INITDIALOG消息的响应函数,该消息是在对话框要显示之前发送的.

7.在CNewButton类的OnMouseMove函数中实现隐藏和显示代码:

	void CNewButton::OnMouseMove(UINT nFlags, CPoint point)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		ShowWindow(SW_HIDE);	//自身隐藏
		m_pBtn->ShowWindow(SW_SHOW);		//对方显示
		CButton::OnMouseMove(nFlags, point);
	}

### 8.2 属性表单和向导的创建

一个属性表单由一个或多个属性页组成.

#### 8.2.1 创建属性页

1.创建属性页

	资源视图下的Dialog右键->添加资源->点开Dialog前的"+"号->选择IDD_PROPPAGE_LARGE(属性页也属于对话框)
	创建3个属性页,并设置为:
		1.	ID:IDD_PROP1;	Caption:Page1
		2.	ID:IDD_PROP2;	Caption:Page2
		3.	ID:IDD_PROP3;	Caption:Page3

2.编辑3个属性页

	属性页1:
		1.添加一个组框(Group Box)---组框用来起一个分组的作用,可以放相关的一些选项放置到一个组框中.
			组框的Caption:Please choose your career:
		2.在组框中放置3个单选按钮(Radio Button)
			单选按钮1的Caption:Programmer
			单选按钮2的Caption:System Engineer
			单选按钮3的Caption:Project Manager
		3.在属性页上添加一个列表框控件(List Box),可以排列一些字符串提供给用户进行选择
		4.在列表框控件上放置一个静态文本控件:
			Caption为:Please select lacation:
		5.调整控件位置,使控件变得美观
	属性页2:
		1.添加一个组框(Group Box)---组框用来起一个分组的作用,可以放相关的一些选项放置到一个组框中.
			组框的Caption:Please choose your hobby:
		2.在组框中添加4个复选框(Check Box),设置Caption分别为:
			Football、Basketball、Volleyball、Swimming.
	属性页3:
		1.添加一个组合框(Combo Box),修改组合框的大小方法:
			选中组合框->鼠标移动到右边向下的位置,但出现"上下拉动的一个图标",单击左键->会出现另一个"上下拉动的一个图标",
			拉动该图标即可改变组合框下拉空间的大小.
		组合框的类型(Type属性):
			Simple(简易式):包含一个编辑框和一个总是显示的列表框;
			Dropdown(下拉式):与Simple的区别是,仅当单击下拉箭头后,列表框才会弹出;
			Drop List(下拉列表式):编辑框只读,只能从下拉列表中选择内容.---常用
		2.在组合框上方放置一个静态文本控件:
			Caption为:Please select your salary:
	PS:使用Format(格式)菜单->Test Dialog(测试对话框)可以测试所设计的属性页(或对话框)显示效果.
		快捷键"Ctrl+T",退出"Esc".

3.为每个属性页关联一个属性页类

	在资源试图下选择属性页1->右键添加类,并编辑:
		类名:CProp1;		基类:CPropertyPage.	看看ID是:IDD_PROP1
	同样方法为IDD_PROP2和IDD_PROP3分别添加新类:CProp2和CProp3.

#### 8.2.2 创建属性表单

1.添加一个属性表单类

	打开类向导窗口,选择右边的添加类.
		类名:CPropSheet;		基类:CPropertySheet

2.在属性表单类中创建3个属性页的成员变量,并将属性页对象添加到属性表单中

	1.在属性表单类上单击右键->选择添加3个成员变量:
		访问:private;		变量类型输入:CProp1;	变量名:m_prop1
		访问:private;		变量类型输入:CProp2;	变量名:m_prop2
		访问:private;		变量类型输入:CProp3;	变量名:m_prop3
	//会自动添加三个属性页的头文件
	2.在属性表单类的构造函数中将属性页添加进去:
		void AddPage(CPropertyPage *pPage);
		/*para:指向需要添加到属性表单中的属性页对象*/
	
		//代码如下,两个构造函数都添加
		CPropSheet::CPropSheet(UINT nIDCaption, CWnd *pParentWnd, UINT iSelectPage)
			:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
		{
			AddPage(&m_prop1);
			AddPage(&m_prop2);
			AddPage(&m_prop3);
		}

		CPropSheet::CPropSheet(LPCTSTR pszCaption, CWnd *pParentWnd, UINT iSelectPage)
			:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
		{
			AddPage(&m_prop1);
			AddPage(&m_prop2);
			AddPage(&m_prop3);
		}

3.创建一个菜单项,并设置单击时显示属性表单

	//全部基于CxxxView(试图类)添加
	1.添加一个菜单项
		Caption:属性表单;	ID:IDM_PROPERTYSHEET;	Pop-up设置为False
	2.为该菜单项添加单击响应函数:OnPropertysheet,并添加实现代码:
		void CxxxView::OnPropertysheet()
		{
			CPropSheet propSheet("属性表单");	//利用传递属性表单标题的构造函数创建属性表单对象
			propSheet.DoModal();		//显示一个模态属性表单
		}
		//需要包含属性表单类的头文件
		/*
			#include "PropSheet.h" 
		*/

#### 8.2.3 向导的创建

1.将属性表单显示改成向导显示:
		
	void CxxxView::OnPropertysheet()
	{
		CPropSheet propSheet("属性表单");	//利用传递属性表单标题的构造函数创建属性表单对象
		propSheet.SetWizardMode();		//设置显示为向导形式
		propSheet.DoModal();		//显示一个模态属性表单
	}
	//此时显示不是太合常规,需要修改

2.为各个属性页重写OnSetActive虚函数---当属性页被选中时,应用程序框架就会调用属性页的OnSetActive函数

	/*
		属性表单类CPropertySheet类的SetWizardButtons成员函数用于设置向导对话框上的按钮
		void SetWizardButtons(DWORD dwFlags);
		/*
		para的取值:
			PSWIZB_BACK:设置一个"上一步"按钮
			PSWIZB_NEXT:设置一个"下一步"按钮
			PSWIZB_FINISH:设置一个"完成"按钮
			PSWIZB_DISABLEDFINISH:设置一个"禁用的完成"按钮
		*/
	*/
	属性页1:	CProp1类的OnSetActive函数
		BOOL CProp1::OnSetActive()
		{
			((CPropertySheet *)GetParent())->SetWizardButtons(PSWIZB_NEXT);	//只有下一步按钮
			//属性页的父窗口为属性表单窗口(GetParent),并且需要进行强制转换.
			return CPropertyPage::OnSetActive();
		}
	属性页2:	CProp2类的OnSetActive函数
		BOOL CProp2::OnSetActive()
		{
			((CPropertySheet *)GetParent())->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			//有上一步和下一步按钮
			//属性页的父窗口为属性表单窗口(GetParent),并且需要进行强制转换.
			return CPropertyPage::OnSetActive();
		}
	属性页3:	CProp3类的OnSetActive函数
		BOOL CProp2::OnSetActive()
		{
			((CPropertySheet *)GetParent())->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);
			//有上一步和完成按钮
			//属性页的父窗口为属性表单窗口(GetParent),并且需要进行强制转换.
			return CPropertyPage::OnSetActive();
		}

**第一个属性页的处理**

1.单选按钮的处理

	1.设置第一个单选按钮(IDC_RADIO1)的Group属性为True,此时三个单选按钮构成一个Group.如果没有设置在类向导中的
		CProp1类中看不到该ID
	2.打开类向导,为第一个单选按钮(IDC_RADIO1)添加一个成员变量:
		变量名:m_occuption	类别:Value	类型:int
		//此时在构造函数中会自动将该成员变量初始化为-1.且三个单选按钮构成一组:
		选中第一个单选按钮,m_occupation=0;
		选中第二个单选按钮,m_occupation=1;
		选中第三个单选按钮,m_occupation=2;
		//如果值为-1,说明用户没有选择单选按钮

2.进入下一个属性页的判断处理

	/*当用户单击"下一步"按钮后,程序将会调用OnWizardNext这个虚函数.该函数如果返回0,自动进入下一个属性页;
		如果返回-1,将禁止属性页发生变更.*/
	1.为属性页重写OnWizardNext虚函数
	2.添加实现代码
		LPRESULT CProp1::OnWizardNext()
		{
			UpdateData();	//从控件得到成员变量的值.默认参数为TRUE
			if(m_occupation == -1)
			{
				MessageBox(_T("Please choose your career!"));
				return -1;
			}
			return CPropertyPage::OnWizardNext();
		}

3.添加工作地点

	1.为CProp1类添加WM_INITDIALOG消息响应函数OnInitDialog,用于向列表框中增加一些工作地点
	2.列表框对应的MFC类是:CListBox,其成员函数:AddString用于向列表框添加字符串
	3.实现代码
		BOOL CProp1::OnInitDialog()
		{
			...
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("北京"));
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("天津"));
			((CListBox*)GetDlgItem(IDC_LIST1))->AddString(_T("上海"));
			return TRUE;
		}

4.工作地点的处理

	1.打开类向导,为列表框(IDC_LIST1)添加一个成员变量:
		变量名:m_workAddr	类别:Value	类型:CString
		//默认在构造函数中会进行初始化
	2.职业和工作地点的完整判断
		LPRESULT CProp1::OnWizardNext()
		{
			UpdateData();	//从控件得到成员变量的值.默认参数为TRUE
			if(m_occupation == -1)
			{
				MessageBox(_T("Please choose your career!"));
				return -1;
			}
			if(m_workAddr == _T(""))
			{
				MessageBox(_T("Please select your work location!"));
				return -1;
			}
			return CPropertyPage::OnWizardNext();
		}

**第二个属性页的处理**

1.为4个复选框控件各自关联一个成员变量

	ID:IDC_CHECK1	成员变量:m_football		类别:Value	类型:BOOL
	ID:IDC_CHECK2	成员变量:m_basketball	类别:Value	类型:BOOL
	ID:IDC_CHECK3	成员变量:m_volleyball	类别:Value	类型:BOOL
	ID:IDC_CHECK4	成员变量:m_swim			类别:Value	类型:BOOL
	//选中时为TRUE,否则为FALSE

2.为属性页重写OnWizardNext虚函数

	LPRESULT CProp2::OnWizardNext()
	{
		UpdateData();	//从控件得到成员变量的值.默认参数为TRUE
		if(m_footbal || m_basketball || m_volleyball || m_swim)	//任何一个为True就可以进入下一个属性页
			return CPropertyPage::OnWizardNext();
		else
		{
			MessageBox("Please choose your hobby!");
			return -1;
		}
	}

**第三个属性页的处理**

组合框对应的MFC类是CComboBox,其成员函数AddString用于向组合框控件的列表框中添加字符串选项

1.为CProp1类添加WM_INITDIALOG消息响应函数OnInitDialog,用于向组合框中增加一些薪资选项

	BOOL CProp1::OnInitDialog()
	{
		...
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("1000元以下"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("1000-2000元"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("2000-3000元"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("3000元以上"));
		return TRUE;
	}

2.取消组合框的自动排序,并且设置组合框中一个默认选项

	1.设置组合框的sort属性为False---取消自动排序,按照添加顺序显示
	2.设置一个默认选项
		int SetCurSel(int nSelect);	//从组合框的列表框中选择一项显示在组合框的编辑框中
		/*para:指定选择项的索引位置
			=0:第一个索引项(从0开始)
			=-1:清空该组合框的编辑框中的内容
		*/

3.实现代码

	BOOL CProp1::OnInitDialog()
	{
		...
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("1000元以下"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("1000-2000元"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("2000-3000元"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->AddString(_T("3000元以上"));
		((CComboBox*)GetDlgItem(IDC_COMBO1))->SetCurSel(0);	//有了默认选项,就需要再判断用户是否进行了选择
		return TRUE;
	}

4.为后续保存用户选择需要添加的操作

	1.添加一个CString类型的成员变量:m_strSalary,用于接收用户的选择
	2.2.为属性页重写OnWizardFinish虚函数
		LPRESULT CProp3::OnWizardFinish()
		{
			int index;
			index = ((CComboBox *)GetDlgItem(IDC_COMBO1))->GetCurSel();
			//GetCurSel():得到组合框的列表框中当前选中项的位置,一个索引值
			((CComboBox *)GetDlgItem(IDC_COMBO1))->GetLBText(index, m_strSalary);
			/*GetLBText():从组合框的列表框中指定位置处(index)得到一个字符串,
				并保存到para2(CString m_strSalary)中*/

			return CPropertyPage::OnWizardFinish();
		}

#### 8.2.4 接收用户在向导中所做的选择

1.在CxxxView类(视类)中接收用户的选择,为视类添加保存的成员变量

	-------------------------------------------------------------------------
		页面			用户的选择		对应视类成员变量类型		变量名
	-------------------------------------------------------------------------
		属性页1		careeer			int					m_iOccupation			
	-------------------------------------------------------------------------
		属性页1		location		CString				m_strWorkAddr
	-------------------------------------------------------------------------
		属性页2		hobby			BOOL				m_bLike[4]
	-------------------------------------------------------------------------
		属性页3		salary			CString				m_strSalary
	-------------------------------------------------------------------------
	//构造函数中会自动初始化

2.在视类中实现代码

	/*
	一般情况下,CPropertySheet类的DoModal函数的返回值是IDOK或IDCANCEL.但如果属性表单被创建为向导后,
	该函数的返回值将是ID_WIZFINISH或IDCANCEL
	*/
	void CxxxView::OnPropertysheet()
	{
		CPropSheet propSheet("属性表单");	//利用传递属性表单标题的构造函数创建属性表单对象
		propSheet.SetWizardMode();		//设置显示为向导形式
		if(ID_WIZFINISH == propSheet.DoModal())
		{
			m_iOccupation = propSheet.m_prop1.m_occupation;
			m_strWorkAddr = propSheet.m_prop1.m_workAddr;
			m_bLike[0] = propSheet.m_prop2.m_football;
			m_bLike[1] = propSheet.m_prop2.m_basketball;
			m_bLike[2] = propSheet.m_prop2.m_volleyball;
			m_bLike[3] = propSheet.m_prop2.m_swim;
			m_strSalary = propSheet.m_prop3.m_strSalary;
			Invalidate();	//让视类无效,从而会引起窗口重绘.进而可以让OnDraw捕获,完成这些信息的输出
		}
	}

3.OnDraw函数的输出

	void CxxxView::OnDraw(CDC* pDC)
	{
		CtextDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		if (!pDoc)
			return;
		// TODO: 在此处为本机数据添加绘制代码
		CFont font;
		font.CreatePointFont(300, (LPCTSTR)"楷体", NULL);	//vs2010中para2需要转换成LPCTSTR

		CFont *pOldFont;
		pOldFont = pDC->SelectObject(&font);

		CString strTemp;
		strTemp = "Your career: ";
		
		switch(m_iOccupation)
		{
			case 0:
				strTemp += "Programmer";
				break;
			case 1:
				strTemp += "System Engineer";
				break;
			case 2:
				strTemp += "Project Manager";
				break;
			default:
				break;
		}
		pDC->TextOut(0, 0, strTemp);

		strTemp = "Your work location: ";
		strTemp += m_strWorkAddr;

		TEXTMETRIC tm;
		pDC->GetTextMetrics(&tm);

		pDC->TextOut(0, tm.tmHeight, strTemp);	//下一行输出

		strTemp = "Your hobby: ";
		if(m_bLike[0])
		{
			strTemp += "football ";
		}
		if(m_bLike[1])
		{
			strTemp += "basketball ";
		}
		if(m_bLike[2])
		{
			strTemp += "volleyball ";
		}
		if(m_bLike[3])
		{
			strTemp += "swim ";
		}
		pDC->TextOut(0, tm.tmHeight * 2, strTemp);	//第三行输出

		strTemp = "Your salary level: ";
		strTemp += m_strSalary;
		pDC->TextOut(0, tm.tmHeight * 3, strTemp);

		pDC->SelectObject(pOldFont);		//恢复原来的字体
	}
***
## Chapter 9 定制应用程序外观

**略**

***

## Chapter 10 绘图控制



***
## Chapter 11 绘图控制

***

# Example

## Chapter 1. Crypto_Tool Developing

### Step 1. 创建一个基于对话框的Crypto_Tool对话框

	文件->新建->项目->名称为"Crypto_Tool"->应用程序类型页中
		应用程序类型:基于对话框; MFC的使用:在静态库中使用MFC(E)
	->主框架样式:勾选上"粗框架"和"系统菜单",其他去掉.
	->生成的类:选择CMFCrypto_ToolDlg的基类"CDialog"

### Step 2. 构建对话框上的各种图标

1.Static Text(静态文本)

	1.拖动一个"Static Text",设置Caption属性为"Algo";
	2.拖动一个"Static Text",设置Caption属性为"Mode";
	3.拖动一个"Static Text",设置Caption属性为"Crypto";
	4.拖动一个"Static Text",设置Caption属性为"Key";
	5.拖动一个"Static Text",设置Caption属性为"IV";
	6.拖动一个"Static Text",设置Caption属性为"Input";
	7.拖动一个"Static Text",设置Caption属性为"Output";

2.Combo Box(组合框)

	1.在Algo右边添加一个"Combo Box",设置ID为"IDC_COMBO_ALGO"
		在外观下的"Type"可以选择"Combo Box",一般为默认的"Dropdown"即可.看着比较舒服
		在行为下的"Sort"一定要设置为"False",否则在添加"Combo选择项时会自动排序"
	2.在Mode右边添加一个"Combo Box",设置ID为"IDC_COMBO_MODE"
	3.在Crypto右边添加一个"Combo Box",设置ID为"IDC_COMBO_CRYPTO"

	PS:在行为下的"Sort"一定要设置为"False",否则在添加"Combo选择项时会自动排序"

3.Edit Control(编辑框)

	1.在Key的右边添加一个"Edit Control",设置ID为"IDC_EDIT_KEY"
		在行为下的"Multiline"选择"True"--->支持多行输入
		在外部下的"Auto HScroll"选择"False"
		在外部下的"Vertical Scroll"选择"True"--->垂直滚动条
		在外部下的"Horizontal Scroll"选择"False"--->水平滚动条
	2.在IV的右边添加一个"Edit Control",设置ID为"IDC_EDIT_IV"
		可以直接复制key右边的,属性也会直接复制过来
	3.在Input的下方添加一个"Edit Control",设置ID为"IDC_EDIT_INPUT"
	4.在Output的下方添加一个"Edit Control",设置ID为"IDC_EDIT_OUTPUT"

4.Button(按钮)

	添加一个按钮,用于计算加解密.设置Caption为"Calc",ID为"IDC_BTN_CALC"

5.调整各个图标位置,使其变得美观

### Step 3. 实现在Combo Box(组合框)中添加选项以及增加"Calc"按钮的消息处理函数

1.为Combo Box(组合框)添加选项

	//在OnInitDialog()函数中实现添加选项的功能
	BOOL CCrypto_ToolDlg::OnInitDialog()
	{
		CDialog::OnInitDialog();
	
		// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
		//  执行此操作
		SetIcon(m_hIcon, TRUE);			// 设置大图标
		SetIcon(m_hIcon, FALSE);		// 设置小图标
	
		// TODO: 在此添加额外的初始化代码
		((CComboBox *)GetDlgItem(IDC_COMBO_ALGO))->AddString(_T("AES"));
		((CComboBox *)GetDlgItem(IDC_COMBO_ALGO))->AddString(_T("TDES"));
		((CComboBox *)GetDlgItem(IDC_COMBO_ALGO))->SetCurSel(0);
		//设置默认选项,有了默认选项,显示对话框会比较好看
		//Combo Box一定要设置"Sort"为False,显示才会按照添加的顺序显示

		((CComboBox *)GetDlgItem(IDC_COMBO_MODE))->AddString(_T("ECB"));	
		((CComboBox *)GetDlgItem(IDC_COMBO_MODE))->AddString(_T("CBC"));
		((CComboBox *)GetDlgItem(IDC_COMBO_MODE))->AddString(_T("CTR"));
		((CComboBox *)GetDlgItem(IDC_COMBO_MODE))->SetCurSel(0);
	
		((CComboBox *)GetDlgItem(IDC_COMBO_CRYPTO))->AddString(_T("Encrypt"));
		((CComboBox *)GetDlgItem(IDC_COMBO_CRYPTO))->AddString(_T("Decrypt"));
		((CComboBox *)GetDlgItem(IDC_COMBO_CRYPTO))->SetCurSel(0);
	
		return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
	}

2.为"Calc"按钮添加消息处理函数

	点击"Calc"按钮,右键->添加事件处理函数->选择默认即可
	函数名为:
	void CCrypto_ToolDlg::OnBnClickedBtnCalc()

### Step 4. 实现"Calc"按钮的消息处理函数

	static void str2char(unsigned char *ch, CString str, int &length)
	{
		int pos = 0;
		int count = 0;	//用于统计字符串中字节个数
		//CString test;
		int i = 0;
		int num = 0;
		pos = str.Find(_T(' '));	//查找CString中的空格,找到了返回空格所在的位置.没找到返回-1
		//test.Format(_T("%d"), pos);	//将返回空格的位置pos格式化成CString,以便后续输出
		//AfxMessageBox(_T("Execute to there"));
		//AfxMessageBox(test);	//非对话框类/单文档窗口类的函数应该调用"AfxMessageBox"输出
	
		while (pos != -1)
		{
			count++;
			CString field = str.Left(pos);	//取str字符串从最左边到pos位置所有的字符串(也就是一个字节)
			//AfxMessageBox(field);	//打印出取出的字符串,主要用于调试
			//field = _T("0x") + field;	//两个字符串可以直接使用"+"进行连接
			num = _tcstol(field.GetBuffer(0), NULL, 16);
			/*
				_tcstol(const wchar_t *nptr, wchar_t **endptr, int base);
				para1:表示要进行扫描的字符串指针.此处field.GetBuffer(0):读出CString的内容.
					GetBuffer真正作用是返回一个可写的缓冲指针,如果有写的动作后面必须调用ReleaseBuffer.
				para2:存储扫描后无法转化的剩余字符串(e.g.转换8进制时,类似a,b这种字符是转换不了的.就存储在
					该参数中).
				para3:转化的进制(e.g.2,8, 10,16等)
				retval:返回转化后对应的值.
			*/
	
			ch[i] = num;	//存储到数组里
			i++;
			str = str.Right(str.GetLength() - pos - 1);	//去掉已经取出来的存储到字符数组中的字符
			pos = str.Find(_T(' '));
		}
		length = count;	//保存统计出来的字节数
	}
	
	static void char2str(CString &str, const unsigned char *buf, int length)
	{
		CString temp = _T("");
		int i = 0;
		for (; i < length; i++)
		{
			temp.Format(_T("0x%02x"), buf[i]);	//转成"0x"16进制后放到CString中
			str += temp;
			str += _T(",");	//增加分隔符","
			if ((i+1)%8 == 0)	//为8的整数倍就换行
			{
				str += _T("\r\n");	//\r:return; \n:next
				/*
					Linux:\n表示回车+换行;
					Windows:\r\n表示回车+换行;
					Mac:\r表示回车+换行.
				*/
			}
		}
		//AfxMessageBox(str);
	}
	
	void CCrypto_ToolDlg::OnBnClickedBtnCalc()
	{
		// TODO: 在此添加控件通知处理程序代码
		CString input, iv, key;
		CString iv_show, key_show, input_show, output_show;
		unsigned char input_buf[2048]={0};
		unsigned char output_buf[2048]={0};
		unsigned char iv_buf[32] = {0};
		unsigned char key_buf[16] = {0};
		int input_length = 0;
		int key_length = 0;
		int iv_length = 0;

		int size = 0;
		int num = 0;
		//int pos;
		//CString resToken;
		//int curPos = 0;
		CString str;

		GetDlgItem(IDC_EDIT_INPUT)->GetWindowText(input);	//得到input编辑框IDC_EDIT_INPUT的字符串信息
		GetDlgItem(IDC_EDIT_IV)->GetWindowText(iv);	//得到IV编辑框IDC_EDIT_IV的字符串信息
		GetDlgItem(IDC_EDIT_KEY)->GetWindowText(key);	//得到key编辑框IDC_EDIT_KEY的字符串信息
	
		/*Transfer "CString" to "char *" */
		str2char(iv_buf, iv, iv_length);
		str2char(key_buf, key, key_length);
		str2char(input_buf, input, input_length);
		Aes Aes_test(16, key_buf);	//调用AES的函数,设置key
	
		/*Transfer "char *" to "CString" */
		char2str(iv_show, iv_buf, iv_length);
		char2str(key_show, key_buf, key_length);
		Aes_test.InvCipher(input_buf, output_buf);
		char2str(output_show, output_buf, input_length);
		char2str(input_show, input_buf, input_length);
	
		GetDlgItem(IDC_EDIT_INPUT)->SetWindowText(input_show);
		GetDlgItem(IDC_EDIT_KEY)->SetWindowText(key_show);
		GetDlgItem(IDC_EDIT_IV)->SetWindowText(iv_show);
		GetDlgItem(IDC_EDIT_OUTPUT)->SetWindowText(output_show);
	}

### Step 5. 添加一个AES调用的类

1.新建一个Aes的类

	在类视图下右击->添加->类->出现的"添加类窗口"点击添加->在"一般C++类向导"下输入:
		类名:Aes,会自动生成".h文件"和".cpp文件".采用默认即可.

2.在Aes.h文件中复制如下代码(该代码由网上下载得到):

	#pragma once
	//enum KeySize { Bits128, Bits192, Bits256 };  //key size, in bits, for construtor
	#define Bits128	16
	#define Bits192	24
	#define Bits256	32
	
	static unsigned char AesSbox[16*16]=
	{// populate the Sbox matrix
		/* 0     1     2     3     4     5     6     7     8     9     a     b     c     d     
		e     f */
		/*0*/  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 
		0xd7, 0xab, 0x76,
		/*1*/  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 
		0xa4, 0x72, 0xc0,
		/*2*/  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 
		0xd8, 0x31, 0x15,
		/*3*/  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 
		0x27, 0xb2, 0x75,
		/*4*/  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 
		0xe3, 0x2f, 0x84,
		/*5*/  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 
		0x4c, 0x58, 0xcf,
		/*6*/  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 
		0x3c, 0x9f, 0xa8,
		/*7*/  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 
		0xff, 0xf3, 0xd2,
		/*8*/  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 
		0x5d, 0x19, 0x73,
		/*9*/  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 
		0x5e, 0x0b, 0xdb,
		/*a*/  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 
		0x95, 0xe4, 0x79,
		/*b*/  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 
		0x7a, 0xae, 0x08,
		/*c*/  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 
		0xbd, 0x8b, 0x8a,
		/*d*/  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 
		0xc1, 0x1d, 0x9e,
		/*e*/  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 
		0x55, 0x28, 0xdf,
		/*f*/  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 
		0x54, 0xbb, 0x16
	};
	
	static unsigned char AesiSbox[16*16]=
	{
		// populate the iSbox matrix
		/* 0     1     2     3     4     5     6     7     8     9     a     b     c     d     
		e     f */
		/*0*/  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 
		0xf3, 0xd7, 0xfb,
		/*1*/  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 
		0xde, 0xe9, 0xcb,
		/*2*/  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 
		0xfa, 0xc3, 0x4e,
		/*3*/  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 
		0x8b, 0xd1, 0x25,
		/*4*/  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 
		0x65, 0xb6, 0x92,
		/*5*/  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 
		0x8d, 0x9d, 0x84,
		/*6*/  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 
		0xb3, 0x45, 0x06,
		/*7*/  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 
		0x13, 0x8a, 0x6b,
		/*8*/  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 
		0xb4, 0xe6, 0x73,
		/*9*/  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 
		0x75, 0xdf, 0x6e,
		/*a*/  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 
		0x18, 0xbe, 0x1b,
		/*b*/  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 
		0xcd, 0x5a, 0xf4,
		/*c*/  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 
		0x80, 0xec, 0x5f,
		/*d*/  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 
		0xc9, 0x9c, 0xef,
		/*e*/  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 
		0x53, 0x99, 0x61,
		/*f*/  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 
		0x21, 0x0c, 0x7d
	};
	static unsigned char AesRcon[11*4]=
	{
		0x00, 0x00, 0x00, 0x00,  
		0x01, 0x00, 0x00, 0x00,
		0x02, 0x00, 0x00, 0x00,
		0x04, 0x00, 0x00, 0x00,
		0x08, 0x00, 0x00, 0x00,
		0x10, 0x00, 0x00, 0x00,
		0x20, 0x00, 0x00, 0x00,
		0x40, 0x00, 0x00, 0x00,
		0x80, 0x00, 0x00, 0x00,
		0x1b, 0x00, 0x00, 0x00,
		0x36, 0x00, 0x00, 0x00
	};
	
	class Aes  //Advanced Encryption Standard
	{
	public:
		~Aes();
		Aes();
		Aes(int keySize, unsigned char* keyBytes);
		unsigned char State[4][4];
		void Cipher(unsigned char* input, unsigned char* output);  //encipher 16-bit input
		void InvCipher(unsigned char* input, unsigned char* output);  //decipher 16-bit input
	private:
		int Nb;         //block size in 32-bit words.  Always 4 for AES.  (128 bits).
		int Nk;         //key size in 32-bit words.  4, 6, 8.  (128, 192, 256 bits).
		int Nr;         //number of rounds. 10, 12, 14.
	
		unsigned char key[32];
		unsigned char w[16*15];
	
		void SetNbNkNr(int keySize);
		void AddRoundKey(int round);      //轮密钥加
		void SubBytes();                  //S盒字节代换
		void InvSubBytes();               //逆S盒字节代换
		void ShiftRows();                 //行移位
		void InvShiftRows();
		void MixColumns();                //列混淆
		void InvMixColumns();
		unsigned char gfmultby01(unsigned char b);
		unsigned char gfmultby02(unsigned char b);
		unsigned char gfmultby03(unsigned char b);
		unsigned char gfmultby09(unsigned char b);
		unsigned char gfmultby0b(unsigned char b);
		unsigned char gfmultby0d(unsigned char b);
		unsigned char gfmultby0e(unsigned char b);
		void KeyExpansion();              //密钥扩展
		unsigned char* SubWord(unsigned char* word);        //密钥S盒字代换
		unsigned char* RotWord(unsigned char* word);        //密钥移位
		//Dump();
		//DumpKey();
		//	DumpTwoByTwo(char* a); 
	};

2.在Aes.cpp文件中复制如下代码(该代码由网上下载得到):

	#include "stdafx.h"
	#include "Aes.h"
	
	
	Aes::Aes(void)
	{
	
	}
	
	
	Aes::~Aes(void)
	{
	
	}
	
	////////////////////////////////////////////////////////////////////////////////////
	//构造函数
	Aes::Aes(int keysize,unsigned char* keyBytes)
	{
		SetNbNkNr(keysize);                 //设置密钥块数，轮数 
		memcpy(key,keyBytes,keysize);		//字符串拷贝函数，把keyBytes的keysize个字符复制到key中
		KeyExpansion();						//密钥扩展，必须提前做的初始化
	}
	///////////////////////////////////////////////////////////////////////////////////
	void Aes::SetNbNkNr(int keySize)
	{
		Nb=4;
		if(keySize=Bits128)
		{
			Nk=4;   //4*4字节，128位密钥，10轮加密
			Nr=10;
		}
		else if(keySize=Bits192)
		{
			Nk=6;   //6*4字节，192位密钥，12轮加密
			Nr=12;
		}
		else if(keySize=Bits256)
		{
			Nk=8;   //8*4字节，256位密钥，14轮加密
			Nr=14;
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
	void Aes::KeyExpansion()
	{
		int row;
		memset(w,0,16*15);
		for(row=0;row<Nk;row++)     //拷贝seed 密钥
		{
			w[4*row+0] =  key[4*row];
			w[4*row+1] =  key[4*row+1];
			w[4*row+2] =  key[4*row+2];
			w[4*row+3] =  key[4*row+3];
		}
		byte* temp = new byte[4];
		for(row=Nk;row<4*(Nr+1);row++)
		{
			temp[0]=w[4*row-4];    //当前列的前一列  
			temp[1]=w[4*row-3];
			temp[2]=w[4*row-2];
			temp[3]=w[4*row-1];
			if(row%Nk==0)          //逢nk时，nk的倍数时，对当前列的前一列作特殊处理
			{
				temp=SubWord(RotWord(temp));   //先移位，再代换，最后和轮常量异或
				temp[0] = (byte)((int)temp[0] ^ (int) AesRcon[4*(row/Nk)+0]); //Rcon为异或轮常数
				temp[1] = (byte)((int)temp[1] ^ (int) AesRcon[4*(row/Nk)+1]);
				temp[2] = (byte)((int)temp[2] ^ (int) AesRcon[4*(row/Nk)+2]);
				temp[3] = (byte)((int)temp[3] ^ (int) AesRcon[4*(row/Nk)+3]);
			}
			else if ( Nk > 6 && (row % Nk == 4) )  //这个还没有搞清楚
			{
				temp = SubWord(temp);
			}
	
			// w[row] = w[row-Nk] xor temp
			w[4*row+0] = (byte) ( (int) w[4*(row-Nk)+0] ^ (int)temp[0] );
			w[4*row+1] = (byte) ( (int) w[4*(row-Nk)+1] ^ (int)temp[1] );
			w[4*row+2] = (byte) ( (int) w[4*(row-Nk)+2] ^ (int)temp[2] );
			w[4*row+3] = (byte) ( (int) w[4*(row-Nk)+3] ^ (int)temp[3] );
		}  // for loop
	
	}
	/////////////////////////////////////////////////////////////////////////////////
	//密钥移位函数
	unsigned char* Aes::RotWord(unsigned char* word)
	{
		byte* temp = new byte[4];
		temp[0] = word[1];
		temp[1] = word[2];
		temp[2] = word[3];
		temp[3] = word[0];
		return temp;
	}
	//////////////////////////////////////////////////////////////////////////////////
	//密钥字代换函数
	unsigned char* Aes::SubWord(unsigned char* word)
	{
		byte* temp = new byte[4];
		for(int j=0;j<4;j++)
		{
			temp[j] = AesSbox[16*(word[j] >> 4)+(word[j] & 0x0f)]; 
			//实际上也可以写成AesSbox[[j]];因为两者相等，j是一个8比特的数
		}  //>>为右移运算符，向右移动4位，得到的高4位是行值。&是按位与运算.
		return temp;                                               
	}
	/////////////////////////////////////////////////////////////////////////////////
	//Aes加密函数
	void Aes::Cipher(unsigned char* input, unsigned char* output)
	{
		int i;
		memset(&State[0][0],0,16);
		for(i=0;i<4*Nb;i++)                 //这里是先写列后写行的，即输入是一列一列的进来的
		{
			State[i%4][i/4]=input[i];	//换成先写行后写列也是可以的，只要在输出时也是这样就可以了
		}
		AddRoundKey(0);						//轮密钥加
	
		for (int round = 1; round <= (Nr - 1); round++) //main round loop
		{
			SubBytes();						//字节代换
			ShiftRows();					//行移位
			MixColumns();					//列混淆
			AddRoundKey(round);				//轮密钥加
		}  // main round loop
	
		SubBytes();							//字节代换
		ShiftRows();						//行移位
		AddRoundKey(Nr);					//轮密钥加
	
		// output = state
		for (i = 0; i < (4 * Nb); i++)
		{
			output[i] =  State[i % 4][ i / 4];
		}
	
	}

	///////////////////////////////////////////////////////////////////////////////
	//Aes解密函数
	void Aes::InvCipher(unsigned char* input,unsigned char* output)
	{
		int i;
		memset(&State[0][0],0,16);
		for (i = 0; i < (4 * Nb); i++)
		{
			State[i % 4][ i / 4] = input[i];
		}
	
		AddRoundKey(Nr);
	
		for (int round = Nr-1; round >= 1; round--)  //main round loop
		{
			InvShiftRows();
			InvSubBytes();
			AddRoundKey(round);
			InvMixColumns();
		}  // end main round loop for InvCipher
	
		InvShiftRows();
		InvSubBytes();
		AddRoundKey(0);
	
		// output = state
		for (i = 0; i < (4 * Nb); i++)
		{
			output[i] =  State[i % 4][ i / 4];
		}
	}
	////////////////////////////////////////////////////////////////////////////////
	//轮密钥加
	void Aes::AddRoundKey(int round)
	{
		int i,j;  //i行 j列           //因为密钥w是一列一列排列的，即 k0 k4 k8 k12
		for(j=0;j<4;j++)			  //k1 k5 k9 k13
		{							  //k2 k6 k10 k14
			for(i=0;i<4;i++)		  //k3 k7 k11 k15
			{					//所以i行j列的下标是4*((round*4)+j)+i即16*round+4*j+i
				State[i][j]=(unsigned char)((int)State[i][j]^(int)w[4*((round*4)+j)+i]);  
				//State是状态，w是轮密钥。两个数组进行异或
			}
		}
	}
	///////////////////////////////////////////////////////////////////////////////////
	//字节代换函数
	void Aes::SubBytes()             //Page 103
	{
		int i,j;
		for(j=0;j<4;j++)
		{
			for(i=0;i<4;i++)
			{
				State[i][j]=AesSbox[State[i][j]];
				//因为 16*(State[i][j]>>4)+State[i][j]&0x0f=State[i][j]
			}
		}
	}
	void Aes::InvSubBytes()
	{
		int i,j;
		for(j=0;j<4;j++)
		{
			for(i=0;i<4;i++)
			{
				State[i][j]=AesiSbox[State[i][j]]; 
				//因为 16*(State[i][j]>>4)+State[i][j]&0x0f=State[i][j]，这是逆S盒
			}
		}
	
	}
	/////////////////////////////////////////////////////////////////////////////////
	void Aes::ShiftRows()
	{
		unsigned char temp[4*4];            //Page105
		int i,j;
		for(j=0;j<4;j++)
		{
			for(i=0;i<4;i++)
			{
				temp[4*i+j]=State[i][j];
			}
		}
		for(i=1;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				if(i==1)State[i][j]=temp[4*i+(j+1)%4];			//第一行左移1位
				else if(i==2)State[i][j]=temp[4*i+(j+2)%4];		//第二行左移2位
				else if(i==3)State[i][j]=temp[4*i+(j+3)%4];		//第三行左移3位
			}
		}
	
	}
	void Aes::InvShiftRows()
	{
		unsigned char temp[4*4];
		int i,j;
		for(j=0;j<4;j++)
		{
			for(i=0;i<4;i++)
			{
				temp[4*i+j]=State[i][j];
			}
		}
		for(i=1;i<4;i++)
		{
			for(j=0;j<4;j++)
			{
				//if(i==1)State[i][j]=temp[4*i+(j-1)%4];
				//在此犯了一个错误-1%4=-1而不是3，所以采用了下面再加一个4的做法
				if(i==1)State[i][j]=temp[4*i+(j+3)%4];		//第一行右移1位 j-1+4=j+3
				else if(i==2)State[i][j]=temp[4*i+(j+2)%4];	//第二行右移2位 j-2+4=j+2
				else if(i==3)State[i][j]=temp[4*i+(j+1)%4];	//第三行右移3位 j-3+4=j+2
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////
	void Aes::MixColumns()
	{
		unsigned char temp[4*4];
		int i,j;
		for(j=0;j<4;j++)                        //2 3 1 1  列混淆矩阵  Page107
		{										//1 2 3 1
			for(i=0;i<4;i++)					//1 1 2 3
			{									//3 1 1 2
				temp[4*i+j]=State[i][j];
			}
		}
		for(j=0;j<4;j++)
		{
			State[0][j] = (unsigned char)((int)gfmultby02(temp[0+j]) ^ 
			(int)gfmultby03(temp[4*1+j]) ^ (int)gfmultby01(temp[4*2+j]) ^ 
			(int)gfmultby01(temp[4*3+j]));
			State[1][j] = (unsigned char) ((int)gfmultby01(temp[0+j]) ^ 
			(int)gfmultby02(temp[4*1+j]) ^ (int)gfmultby03(temp[4*2+j]) ^ 
			(int)gfmultby01(temp[4*3+j]));
			State[2][j] = (unsigned char) ((int)gfmultby01(temp[0+j]) ^ 
			(int)gfmultby01(temp[4*1+j]) ^ (int)gfmultby02(temp[4*2+j]) ^ 
			(int)gfmultby03(temp[4*3+j]));
			State[3][j] = (unsigned char) ((int)gfmultby03(temp[0+j]) ^ 
			(int)gfmultby01(temp[4*1+j]) ^ (int)gfmultby01(temp[4*2+j]) ^ 
			(int)gfmultby02(temp[4*3+j]) );
		}
	
	}
	void Aes::InvMixColumns()
	{
		unsigned char temp[4*4];
		int i,j;
		for (i = 0; i < 4; i++)  // copy State into temp[]
		{
			for (j = 0; j < 4; j++)               	//0e 0b 0d 09   逆变换矩阵 Page108
			{										//09 0e 0b 0d
				temp[4*i+j] =  State[i][j];			//0d 09 0e 0b
			}										//0b 0d 09 0e
		}
	
		for (j = 0; j < 4; j++)
		{
			State[0][j] = (unsigned char) ((int)gfmultby0e(temp[j]) ^ 
			(int)gfmultby0b(temp[4+j]) ^ (int)gfmultby0d(temp[4*2+j]) ^ 
			(int)gfmultby09(temp[4*3+j]));
			State[1][j] = (unsigned char) ((int)gfmultby09(temp[j]) ^ 
			(int)gfmultby0e(temp[4+j]) ^ (int)gfmultby0b(temp[4*2+j]) ^ 
			(int)gfmultby0d(temp[4*3+j]));
			State[2][j] = (unsigned char) ((int)gfmultby0d(temp[j]) ^ 
			(int)gfmultby09(temp[4+j]) ^ (int)gfmultby0e(temp[4*2+j]) ^ 
			(int)gfmultby0b(temp[4*3+j]));
			State[3][j] = (unsigned char) ((int)gfmultby0b(temp[j]) ^ 
			(int)gfmultby0d(temp[4+j]) ^ (int)gfmultby09(temp[4*2+j]) ^ 
			(int)gfmultby0e(temp[4*3+j]));
		}
	}
	
	/////////////////////////////////////////////////////////////////////////////////
	unsigned char Aes::gfmultby01(unsigned char b)
	{
		return b;
	}
	unsigned char Aes::gfmultby02(unsigned char b)
	{
		if (b < 0x80)
			return (unsigned char)(int)(b <<1);
		else
			return (unsigned char)( (int)(b << 1) ^ (int)(0x1b) );
	}
	
	unsigned char Aes::gfmultby03(unsigned char b)
	{
		return (unsigned char) ( (int)gfmultby02(b) ^ (int)b );
	}
	
	unsigned char Aes::gfmultby09(unsigned char b)
	{
		return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^ (int)b );
	}
	
	unsigned char Aes::gfmultby0b(unsigned char b)
	{
		return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
			(int)gfmultby02(b) ^ (int)b );
	}
	
	unsigned char Aes::gfmultby0d(unsigned char b)
	{
		return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
			(int)gfmultby02(gfmultby02(b)) ^ (int)(b) );
	}
	
	unsigned char Aes::gfmultby0e(unsigned char b)
	{
		return (unsigned char)( (int)gfmultby02(gfmultby02(gfmultby02(b))) ^
			(int)gfmultby02(gfmultby02(b)) ^(int)gfmultby02(b) );
	}
	////////////////////////////////////////////////////////////////////////////////
