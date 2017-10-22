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

