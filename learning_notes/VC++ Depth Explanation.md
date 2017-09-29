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
	