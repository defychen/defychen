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
			标识符转换为需要的LPCTSTR类型
		retval:返回系统分配给某图标的句柄.可以赋值给窗口类的图标句柄.
	*/

3.LoadCursor函数加载光标资源---用于赋值给窗口类的光标句柄

	HCURSOR LoadCursor(HINSTANCE hInstance, LPCTSTR lpCursorName);
	//与LoadIcon相似

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

窗口样式类型---WS_OVERLAPPENDWINDOW

	#define WS_OVERLAPPENDWINDOW	(WS_OVERLAPPEND	| \		//产生一个层叠的窗口
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

消息循环:不断的从消息队列中取出消息---while循环+GetMessage()函数.取出的消息自动会由窗口过程函数相应.

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



1.OS接收到应用程序的窗口消息,将消息投递到该应用程序的消息队列中;

2.应用程序在消息循环中调用GetMessage从消息队列中取出一条一条消息,并对消息进行一些预处理.e.g.调用TranslateMessage(&msg)产生新的消息或者直接放弃对某些消息的相应;

3.应用程序调用DispatchMessage(&msg),将消息回传给OS;

4.OS利用WNDCLASS结构体的lpfnWndProc成员保存的窗口过程函数的指针调用窗口过程函数对消息进行处理.

	PS:
	从消息队列中取消息的另外的函数:PeekMessage;发送消息:SendMessage、PostMessage.