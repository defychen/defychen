# Verilog HDL

## Chapter 1 引言

### 1.1 Verilog HDL定义

Verilog HDL是一种用于数字逻辑电路设计的硬件描述语言(Hardware Decription Language),可以用来进行数字电路的仿真验证、时序分析、逻辑综合等.

	1.用Verilog HDL描述的电路设计就是该电路的Verilog HDL模型;
	2.Verilog HDL既是一种行为描述语言也是一种结构描述语言.

Verilog HDL模型的建立:既可以用电路的功能描述来建立,也可以用元器件及其之间的连接来建立.

### 1.2 Verilog HDL的发展历史

1.1983年,由GDA(GateWay Design Automation)公司的Phil Moorby首创;

2.1989年,Cadence公司收购了GDA公司.并于1990年公开发表了Verilog HDL;

3.1995年,IEEE制定并公开发表Verilog HDL1364-1995标准;

4.1999年,模拟和数字电路都适用的Verilog标准公开发表.

### 1.3 不同层次的Verilog HDL抽象

Verilog HDL模型可以是实际电路的不同级别的抽象,抽象级别分为5级:

1.系统级(System Level):用高级语言结构(e.g.case语句)实现的设计模块外部性能的模型;

2.算法级(Algorithmic Level):用高级语言结构实现的设计算法模型(写出逻辑表达式);

3.RTL级(Register Transfer Level):描述数据在寄存器之间的流动和如何处理这些数据的模型;

4.门级(Gate Level):描述逻辑门(e.g.与门,非门,或门,与非门,三态门等)以及逻辑门之间连接的模型;

5.开关级(Switch Level):描述器件中三极管和存储节点及其之间连接的模型.

### 1.4 Verilog HDL的特点

1.语言结构上的特点:

	1.形式化地表示电路的行为和结构;
	2.借用C语言的结构和语句;
	3.可在多个层次上对所设计的系统加以描述,语言对设计规模不加任何限制;
	4.具有混合建模能力:一个设计中的各子模块可用不同级别的抽象模型来描述;
	5.基本逻辑门、开关级结构模型均内置于语言中,可直接调用;
	6.易创建用户定义原语(UDP:User Designed Primitive).

2.易学易用.

***

## Chapter 2 Verilog HDL基本结构

### 2.1 一些简单的Verilog HDL例子

**1.8位全加器**

	module adder8(cout, sum, a, b, cin);	//模块名:adder8;端口定义:cout,sum,a,b,cin
		output cout;	//输出端口声明
		output [7:0] sum;	//嵌套在module和endmodule的语句缩进2/4格空格.使用一个tab键即可.
		input [7:0] a, b;
		input cin;
		assign {cout, sum} = a + b + cin;	//功能描述
		/*
			assign语句:无论右边表达式操作数何时发生变化,右边表达式都会重新计算.
						并且在指定的延迟后给左边表达式赋值.
		*/
	endmodule

**2.8位计数器**

	module counter8(out, cout, data, load, cin, clk);
		output [7:0] out;	//IO说明
		output cout;
		input [7:0] data;
		input load, cin, clk;
		reg [7:0] out;	//信号类型说明
		always @(posedge clk)	//功能描述
			begin
				if(load)
					out <= data;	//同步预置数据
				else
					out <= out + cin;	//加1计数
			end
		assign cout = &out & cin;	//前面一个&为缩减运算符;后面一个&为位运算符.
		/*
			若out为8'hFF,cin为1,则cout为1.
		*/
	endmodule

**3.2位比较器**

	module compare2(equal, a, b);
		output equal;
		input [1:0] a, b;
		assign equal = (a == b) ? 1 : 0;	//条件运算
		/*如果a,b相等,则equal取1,否则取0.*/
	endmodule

重要的点:

	<=(非阻塞过程性赋值):将想要赋值给左边的值安排在未来时刻.不等上一个赋值执行完成执行下一个赋值语句.
	=(阻塞过程赋值):按照顺序执行,前一个赋值结束才执行下边的赋值语句.

**4.三态驱动器---门元件例化**

门元件例化:程序通过调用一个在Verilog语言库中现存的实例化元件来实现某逻辑门功能.

	module trist2(out, int, enable);
		output out;
		input in, enable;
		bufifi1 mybuf(out, in, enable);
		/*
			bufif1:门元件关键字.	mybuf:例化的元件名.
		*/
	endmodule

bufif1的真值表:

		Inputs				Output
	In			Enable		 Out
	x			0			 z
	1			1			 1
	0			1			 0
	/*解析:
		1.当enable为0时,无论in为0/1.out均为z;
		2.当enable为1时,out的值取决于in的值.
	*/

**5.三态驱动器---模块元件例化**

模块元件例化:顶层模块(e.g.trist1)调用由某子模块(mytri)定义的实例元件(tri_inst)来实现某功能.

	module trist1(out, in, enalbe);	//顶层模块
		output out;
		input in, enable;
		mytri tri_inst(out, in, enable)s;	//模块例化
	endmodule
	
	module mytri(out, in, enable);	//子模块
		output out;
		input in, enable;
		assign out = enable ? in : 'bz;
		/*
			如果enable为1,则out=in;否则为高阻态('bz:表示高阻态);
		*/
	endmodule

### 2.2 Verilog HDL模块的结构

Verilog模块的结构由在module和endmodule关键词之间的4个部分组成:

	module block1(a, b, c, d);	//端口定义
		input a, b, c;	// I/O说明
		output d;		// I/O说明
		wire x;			//信号类型声明
		assign d = a | x;		//功能描述
		assign x = (b & ~c);	//功能描述
	endmodule

### 2.3 Verilog HDL逻辑功能定义

3种方法描述电路的逻辑功能:

**1.使用assign语句**

assign语句常用于描述组合逻辑.

	assign x = (b & ~c);

**2.使用元件例化(instantiate)**

	and myand3(f, a, b, c);
	/*
		and:门元件关键字;	myand3:例化元件名.
	*/
	
元件例化注意点:

	1.元件例化即是调用Verilog HDL提供的元件;
	2.元件例化包括门元件例化和模块元件例化;
	3.例化元件名必须唯一,避免冲突;
	4.有时例化元件名也可省略.

**3.使用always块语句**

	always @(posedge clk)	//每当时钟上升沿到来时执行一遍块内语句
		begin
			if(load)
				out = data;	//同步预置数据
			else
				out = data + 1 + cin;	//加1计数
		end

always语句注意点:

	1.always语句常用于描述时序逻辑,也可用于描述组合逻辑;
	2.always块可使用if-else或case语句来表示逻辑关系;
	3.always块语句与assign语句是并发执行的.因此,assign语句一定要放在always块语句之外.

### 2.4 Verilog HDL模块的模板(仅考虑用于逻辑综合的部分)

	module <模块名>(<输入/输出端口列表>);
		output 输出端口列表;
		input 输入端口列表;
		/*1.使用assign语句定义逻辑功能*/
		wire 结果信号名;
		assign <结果信号名> = 表达式;
		/*2.使用always块定义逻辑功能*/
		always @(<敏感信号表达式>)
			begin
				/*
					1.过程赋值语句;
					2.if语句;
					3.case语句;
					4.while,repeat,for循环语句;
					5.task,function调用
				*/
			end
		/*3.元件例化*/
		//3.1:模块元件例化
		<module_name> <instance_name>(<port_list>);
		//3.2:门元件例化
		<gate_type_keyword> <instance_name>(<port_list>);
		endmodule

### 2.5 关键字

关键字用小写字母定义,常用的如下:

![](images/verilog_key_word_1.png)

![](images/verilog_key_word_2.png)

### 2.6 标识符

1.标识符由字母、数字、下划线和$符号构成,但第一个字符必须是字母或下划线,不能是数字或$符号.

2.Verilog HDL中的变量名是区分大小写的.

### 2.7 编写Verilog HDL源代码的标准

**1.语汇代码编写标准**

1.每个Verilog HDL源文件中只准编写一个顶层模块;

2.源文件名字最好与顶层模块同名;

3.源代码采用层层缩进的格式来写;

4.对接口(e.g.模块参数,端口,任务,函数变量等)需要做必要的注释;

5.常量尽可能多的使用参数定义和宏定义.

		参数定义:
			parameter 参数名1=表达式, 参数名2=表达式,...;
		宏定义:
			`define 宏名 宏内容

**2.综合代码的编写标准**

1.除设计中对速度响应要求比较临界的部分外,都应该避免门级描述;

2.建立一个好的始终策略(e.g.单时钟、多相位时钟,经过门产生的时钟、多时钟域等).保证源代码中时钟和复位信号是干净的(即不是由组合逻辑或没有考虑到的门产生的);

3.建立好的测试策略,使所有触发器都是可复位的,使测试能通过外部管脚进行,又没有冗余的功能;

4.所有源代码都必须遵守并符合在always块语句的4中可综合标准模板之一;

5.描述组合和锁存逻辑的always块,必须在always块开头的控制事件列表中列出所有的输入信号;

6.描述组合逻辑的always块,一定不能有不完全赋值.即所有输出变量必须被各输入值的组合值赋值,不能有例外;

7.描述组合逻辑和锁存逻辑的always块一定不能包含反馈.即在always块中已被定义为输出的寄存器变量绝对不能再在always块中读出来作为输入信号;

8.时钟沿触发的always块必须是单时钟的,且任何异步控制输入(通常是复位或置位信号)必须在控制事件列表中列出;

	e.g.always @(posedge clk or negedge set or negedge reset)

9.避免生成不想要的锁存器.在无时钟的always块中,若有的输出变量被赋了某个信号变量值,而该信号变量并未在该always块的电平敏感控制事件中列出,则会在综合中生成不想要的锁存器.

10.避免生成不想要的触发器.在时钟沿触发的always块中,如果用非阻塞赋值语句对reg型变量赋值;或者当reg型变量经过多次循环其值仍保持不变,则会在综合中生成触发器.

reg型变量生成触发器实例:

![](images/always_reg_assign.png)

	e.g.使用reg型变量生成触发器--->用非阻塞型赋值语句对reg型变量赋值:
	module rw2(clk, d, out1);
		input clk, d;
		output out1;
		reg out1;	//out1为reg型变量
		always @(posedge clk)	//上升沿触发
			out1 <= d;	//非阻塞赋值语句
	endmodule

reg型变量生成组合逻辑,使用电平触发实例:

![](images/level_trigger.png)

	e.g.电平触发
	module rw2(clk, d, out1);
		input clk, d;
		output out1;
		reg out1;
		always @(d)	//电平触发
			out1 <= d;	//非模态对话框阻塞赋值语句
		endmodule

11.所有内部状态寄存器必须是可复位的,这是为了使RTL级和门级描述能够被复位成同一个已知的状态,以便进行门级逻辑验证.

12.一般地,在赋值语句中不能使用延迟,否则是不可综合的.

13.不要使用integer型和time型寄存器,否则将分别总合成32位和64位的总线.

***

## Chapter 3 数据类型及常量、变量

### 3.1 数据类型

数据类型是用来表示数字逻辑电路中的数据存储和传递单元.

#### 3.1.1 数据类型

Verilog HDL共有19种数据类型:

	1.4种基本类型:integer, parameter, reg, wire;
	2.其他类型:large, medium, scalared, small, tri, tri0, tri1, triand, trior,
		trireg, vectored, wand, wor等.

#### 3.1.2 常量

常量包括:

	1.数字(包括整数,x和z值,负数);
	2.parameter常量(也叫符号常量).

**1.整数型常量**

	1.b/B(二进制), d/D(十进制), h/H(十六进制), o/O(八进制).
		e.g.8'b11000101或8'hc5	=>表示8位宽,二/十六进制的数.
	2.如果没有指定位宽(转换为二进制数的宽度),默认为32位.没有指定进制,默认为10进制.

**2.x和z值**

x表示不定值,z表示高阻值.

	1.最左边的x或z具有扩展性:
		8'bzx = 8'bzzzz_zzzx	//最左边的z扩展.
	2."?"是z的另一种表示符号.在case语句中通常使用"?"表示高阻态z:
		case z(select)
			4'b???1:out = a;
			4'b??1?:out = b;
			4'b?1??:out = c;
			4'b1???:out = d;

**3.负数**

位宽前加一个减号表示负数.负数一般用补码表示.

	1.负数补码表示:
		-8'd5 =>表示为:=8'b11111011
	2.较长的数字之间可用(_)隔开:
		16'b1010_1011_1100_1111	//这个表示是合法.
	3.常量未指明位宽,默认为32位:
		-1 = -32'd1 = 32'hFFFFFFFF

**4.parameter常量(符号常量)**

parameter用来定义一个标识符,代表一个常量.

	1.赋值语句右边必须为常数表达式(即只能包含数字或先前定义过的符号常量):
		parameter addrwidth = 16;	//合法常量定义
		parameter addrwidth = datawidth * 2;	//非法,因为datawidth是个变量.
	2.parameter常量常用来定义延迟时间和变量宽度;
	3.parameter参量是本地的,只在定义的模块内有效;
	4.在模块或实例引用时,可通过参数传递改变在被引用模块或实例中已定义过的参数.

**5.模块引用时参数的传递**

格式:

	被引用的模块名 #(para1, para2, ...) 模块实例名(端口列表);

实例:

	module mod(out, ina, inb);	//被引用的模块
		...
		paramter cycle = 8, real_constant = 2.039,
			file = "/user1/jmdong/design/mem_file.dat";
		...
	endmodule

	module test;
		...
		mod #(5, 3.20, "../my_mem.dat") mk(out, ina, inb);	//对模块mod的实例引用
			//传递的参数必须与模块声明时的参数一致
		...
	endmodule

#### 3.1.3 变量

变量的数据类型有19种,常用的为下面3种:

	nets type(网络型), register type(寄存器型), memory type(数组类型)

**1.nets型变量**

定义:输出始终随输入的变化而变化的变量.表示结构实体(如门)之间的物理连接.

常用的nets型变量:

	1.wire, tri:连线类型(两者功能一致);
	2.wor, trior:具有线或特性的连线(两者功能一致);
	3.wand, triand:具有线与特性的连线(两者功能一致);
	4.tri1, tri0:上拉电阻和下拉电阻;
	5.supply1, supply0:电源(逻辑1)和地(逻辑0).

wire型变量:

	1.最常用的nets型变量,常用来表示以assign语句赋值的组合逻辑信号;
	2.模块中的输入/输出信号类型缺省为wire型;

wire型变量的定义:

	wire 数据名1, 数据名2, ..., 数据名n;

wire型向量(总线)定义:

	wire[n-1:0] 数据名1, 数据名2, ..., 数据名m;	//每条总线位宽为n,共有m条总线.

**2.register型变量**

定义:对应具有状态保护作用的电器元件(e.g.触发器、寄存器等).常用来表示过程块语句(e.g.initial, always, task, function)内的指定信号.

常用的register型变量:

	reg:常代表触发器;
	integer:32位带符号整数型变量;
	real:64位带符号实数型变量;
	time:无符号时间变量.

register型变量与nets型变量的区别:

	1.register型变量需要被明确地赋值,并且在被重新赋值前一直保持原值;
	2.register型变量必须通过过程赋值语句赋值,不能通过assign语句赋值;
	3.在过程内被赋值的每个信号必须定义成register型.

reg型变量

	最常用的register型变量.在过程块中被赋值的信号,往往代表触发器(组合逻辑信号也可以);

reg型变量的定义:

	reg 数据名1, 数据名2, ..., 数据名n;

reg型向量(总线)的定义:

	reg[n-1:0] 数据名1, 数据名2, ..., 数据名m;	//每个向量位宽为n,共有m个reg型变量
	reg[4:1] regc, regd;	//regc, regd为4位宽的reg型变量

**3.reg与wire的区别**

reg型变量既可以生成触发器,也可以生成组合逻辑;wire型变量只能生成组合逻辑.

实例1---reg型变量生成组合逻辑

![](images/reg_to_logic.png)

	module rw1(a, b, out1, out);
		input a, b;
		output out1, out2;
		reg out1;	//reg型变量必须通过过程赋值语句赋值
		wire out2;	//wire型变量,需要通过assign赋值
		assign out2 = a;	//连续赋值语句
		always @(b)	//电平触发
			out1 <= ~b;	//过程赋值语句
	endmodule

实例2---reg型变量生成触发器

![](images/reg_to_trigger.png)

	module rw2(clk, d, out1, out2);
		input clk, d;
		output out1, out2;
		reg out1;	//reg型用于触发器
		wire out2;	//wire型
		assign out2 = d & ~out1;	//连续赋值语句
		always @(posedge clk)	//沿触发,一般为上升沿
			begin
				out1 <= d;	//过程赋值语句(过程赋值使用"<="??)
			end
	endmodule

**4.memory型变量---数组**

定义:由若干个相同宽度的reg型向量构成的数组.

memory型变量用途:memory型变量可描述RAM,ROM和reg文件.一般用于存储器建模;

memory型变量定义方法:

	reg[n-1:0] 存储器名[m-1:0];
	//表示:共有m个存储单元,每个存储单元位宽为n.即为m个n位寄存器构成的存储器.

memory型变量与reg型变量的区别:

	1.含义不同:
		reg[n-1:0] rega;	//一个n位的寄存器
		reg memo[n-1:0];	//由n个1位寄存器构成的存储器
	2.赋值方式不同:
		rega = 0;	//n位寄存器所有位清0.合法赋值
		memo[8] = 1;	//存储单元中的第8个寄存器清0.合法赋值
		memo[1023:0] = 0;	//存储器中的0~1023个寄存器都清0.合法赋值
		memo = 0;	//没有指明具体是哪个寄存器.非法赋值.
	即为:memory型变量赋值时,必须指明具体是哪个寄存器(即具体哪个存储单元).

***

## Chapter 4 运算符及表达式

### 4.1 算数运算符

%(求模)运算符要求%两侧均为整数数据.结果值的符号取第一个操作数的符号位??

	-11 % 3 = -2

进行算数运算时,若某个操作数为不定值x,则整个结果也为x.

实例---除法和求模运算的区别

	module arithmetic(clk, a, b, c, d, e);
		output [3:0] c, d;
		output [7:0] e;
		input [3:0] a, b;
		input clk;
		reg [3:0] c, d;	//reg型变量只能在过程块语句中指定信号
		reg [7:0] e;	//reg型变量只能在过程块语句中指定信号
		always @(posedge clk)	//沿触发
			begin
				c = a/b;
				d = a%b;
				e = a*b;
			end
	endmodule

上述例子可以进行仿真,参加PPT.

### 4.2 逻辑运算符

	1.非0是真(1'b1);
	2.零是假(1'b0);
	3.不确定的操作数如4'bxx00--->是不确定的(可能为0,也可能非0),记为1'bx;
	  但是4'bxx11是真(因为肯定有值)--->记为1'b1.

主要的逻辑符号:&&(与), ||(或), !(非).

逻辑运算后的结果为1, 0, x(如果存在某个操作数为x(不确定的)).

实例:

	(a>b) && (b>c);	(a==b) || (x==y); (!a) || (a>b)

### 4.3 位运算符

	~(按位取反);	&(按位与); |(按位或); ^(按位异或); ~^/^~(按位同或).

实例:

	A = 5'b11001, B = 3'b101
	A & B = 5'b00001	//B中不够的最高位补0

实例---&&和&的区别

	module logic_demo(outc, outd, a, b);
		output outc;
		output [3:0] outd;
		input [3:0] a, b;
		assign outc = a && b;
		assign outd = a & b;
	endmodule

上述例子可以进行仿真,参加PPT.

### 4.4 关系运算符

	<; <=; >; >=

在比较时,若有操作数为不确定值x,则返回值为x.

### 4.5 等式运算符

	==(等于); !=(不等于); ===(全等); !==(不全等)

运算结果为1位的逻辑值1或0或x.

==(等于)和===(全等)的区别:

	1.==(等于):两个操作数必须逐位相等,结果才为1;如果某些位存在x或z,则结果为x;
	2.===(全等):两个操作数的相应位必须完全一致(同为1,或0,或x,或z),结果为1,否则为0.
	3.==取值为1,0,x; ===取值为1,0.

===和!==常用语case表达式的判别,又称为"case等式运算符".

==和===的真值表:

![](images/truth_table.png)

实例:

	if (A == 1'bx)
		$display("A is X");	//无论A为什么值,A == 1'bx结果均为x.因此该句不执行.

	if (A === 1'bx)
		$display("A is X");	//当A为不定值x时,A === 1'bx运算结果为1.该语句执行.

### 4.6 缩减运算符---单目运算符

	&(与); ~&(与非); |(或); ~|(或非); ^(异或); ~^, ~^(同或).

运算过程:先将操作数的最低位与第二位进行与&/|/~;再将结果与第三位进行相同运算.直到最高位结束得到结果.

运算结果位1位二进制数.

实例:

	reg [3:0] a;
	b = |a;	//等效为:b = ((a[0] | a[1]) | a[2]) | a[3]

### 4.7 移位运算符

	<<(左移); >>(右移)

无论左移/右移均用0填充.

### 4.8 条件运算符

	xxx = condition ? expr1 : expr2;

实例---mux(数据选择器)

![](images/data_mux.png)

	assign out = sel ? in1 : in0;
	/*
		当sel=1时,out=in1;
		当sel=0时,out=in0.
	*/

### 4.9 位拼接运算符

将两个或多个信号的某些位拼接起来,表示一个整体信号.

	{信号1的某几位, 信号2的某几位, ..., 信号n的某几位}

例1---多个位拼接在一起,构成整体

	{a, b[3:0], w, 3'b101}
	= {a, b[3], b[2], b[1], b[0], w, 1'b1, 1'b0, 1'b1}
	//即构成的一个9位的数.左边为最高位.
	{1, 0} = 64'h00000001_00000000;	//位拼接未指明位数,默认为32位.

例2---进位输出跟和拼接在一起

	output [3:0] sum;	//和
	output cout;		//进位输出
	input [3:0] ina, inb;
	input cin;
	assign {cout, sum} = ina + inb + cin;
	/*
	构成的信号为{cout, sum[3], sum[2], sum[1], sum[0]}.
	因此,此句相当于给cout,sum赋值.cout存放进位,sum存放和.
	*/

例3---重复法和嵌套方法

	1.重复法
	{4{w}} = {w, w, w, w}
	2.嵌套方法
	{b, {3{a, b}}} = {b, {a, b}, {a, b}, {a, b}} = {b,a,b,a,b,a,b}

***

## Chapter 5 语句

### 5.1 赋值语句和块语句

#### 5.1.1 赋值语句

主要分为两类:

	1.连续赋值语句---assign语句,用于对wire型变量赋值,是描述组合逻辑最常用的方法之一.
		assign c = a & b;	//a,b,c均为wire型变量
	2.构成赋值语句---用于对reg型变量赋值,有两种方式:
		1)非阻塞(non-blocking)赋值方式,赋值符号"<=";
			b <= a;
		2)阻塞(blocking)赋值方式,赋值符号"=".
			b = a;

#### 5.1.2 非阻塞赋值与阻塞赋值的区别

**1.非阻塞赋值方式**

非阻塞赋值在块结束时才完成赋值操作.

![](images/verilog_non_blocking_assign.png)

	always @(posedge clk)
		begin
			b <= a;
			c <= b;
		end		//非阻塞赋值在块结束时才完成赋值操作.
	PS:c的值比b的值落后一个时钟周期.

**2.阻塞赋值方式**

阻塞赋值在某语句结束时就完成赋值操作.

![](images/verilog_blocking_assign.png)

	always @(posedge clk)
		begin
			b = a;
			c = b;	//阻塞赋值在该语句结束就完成赋值操作
		end
	PS:在一个块语句中,如果有多条阻塞赋值语句,在前面的赋值语句没有完成之前,后面的语句就
	不能被执行,就像被阻塞了一样,因此被称为阻塞赋值方式.
	此处的c的值与b的值一样.

**3.非阻塞赋值与阻塞赋值方式的主要区别**

1.非阻塞赋值(non-blocking)方式(b<=a):

	1.b的值被赋值成新值a的操作,不是立刻完成的,而是在块结束时才完成;
	2.块内的多条赋值语句在块结束时同时赋值;
	3.硬件有对应的电路.

2.阻塞赋值(blocking)方式(b=a):

	1.b的值立刻被赋成新值a;
	2.完成该赋值语句后才能进行下一句的操作;
	3.硬件没有对应的电路,因而综合结果未知.

**4.使用方式**

	初学时全部使用非阻塞方式即可.

#### 5.1.2 块语句

将多条语句组合在一起.主要有两种方式:

	1.begin-end语句:标识顺序执行的语句;
	2.fork-join语句:标识并行执行的语句.

**1.顺序块--->用begin-end标识的块**

	1.块内的语句是顺序执行的;
	2.每条语句的延迟时间是相对于前一条语句的仿真时间而言的;
	3.直到最后一条语句执行完,程序流程才跳出该顺序块.
	4.块内声明的语句可以是参数声明、reg型变量声明、integer型变量声明、real型变量声明语句.

实例1:

	begin
		b = a;
		c = b;	//c的值为a的值
	end

实例2:

	begin
		b = a;
		#10 c = b;	//延迟10个时间单位
	end
	/*
		1.此处的"#"表示延迟;
		2.在模块调用中的"#"表示参数的传递.
	*/

实例3---用顺序块和延迟控制组合产生一个时序波形

	parameter d = 50;
	reg	[7:0] r;
	begin
		# d r = 'h35; //相对于前一条语句延迟时间d
		# d r = 'hE2;
		# d r = 'h00;
		# d r = 'hF7;
		# d ->end_wave;	//触发事件end_wave
	end

**2.并行块--->用fork-join标识的块**

	1.块内的语句是同时执行的;
	2.块内每条语句的延迟时间是相对于程序流程控制进入到块内时的仿真时间而言的;
	3.延迟时间用于给赋值语句提供时序;
	4.当按时间排序在最后的语句执行完成或一个disable语句执行时,程序流程控制跳出该并行快;
	5.块内声明的语句可以是参数声明、reg型变量声明、integer型变量声明、real型变量声明语句、
		time型变量声明语句和事件(event)声明语句.

实例---用并行块和延迟控制组合产生一个时序波形.

	reg [7:0] r;
	fork
		# 50 r = 'h35;	//延迟50ns
		# 100 r = 'hE2;	//因为是并行.为了相对前一句延迟50ns.因此此处相对公共起点延迟100ns
		# 150 r = 'h00;	//因为是并行.为了相对前一句延迟50ns.因此此处相对公共起点延迟150ns
		# 200 r = 'hF7; //因为是并行.为了相对前一句延迟50ns.因此此处相对公共起点延迟200ns
		# 250 ->end_wave;	//触发事件end_wave.相对公共起点延迟250ns
	join
	
PS:fork-join块内,各条语句可以不按顺序给出(因为是计算绝对时间).但是为了增加可读性,还是按顺序书写比较好.

### 5.2 条件语句

条件语句分为:if-else和case语句.都是顺序语句,应放在always块内.

#### 5.2.1 if-else语句

if-else语句的特点:

	1.if后面的表达式为逻辑表达式、关系表达式或一位的变量;
	2.若表达式的值为0或z,则判定的结果为"假/false";若为1,则结果为"真/true";
	3.语句如果为多句时,一定要用"begin-end"语句括起来,形成一个复合块语句.
	4.if语句可以嵌套,如果嵌套时if与else数目不一致,使用begin-end将单独的if语句括起来,易读.
		if (expression1)
			begin
				if (expression2) statement1;
			end
		else
			statement2;

实例---模为60的BCD码加法计数器

	module count60(qout, cout, data, load, cin, reset, clk);
		output [7:0] qout;
		output cout;
		input [7:0] data;
		input load, cin, reset, clk;
		reg [7:0] qout;
		always @ (posedge clk)	//always块内语句是顺序执行的
			begin
				if (reset)
					qout = 0;		//同步复位
				else if (load)
					qout = data;	//同步置数
				else if (cin)		//如果cin=1,执行+1计数;否则qout保持不变
					begin
						if (qout[3:0] == 9)	//低4位是否为9?
							begin
								qout[3:0] = 0;	//是则回0
								if [qout[7:4] == 5]	//高4位是否为5?
									qout[7:4] = 0;	//是则回0
								else
									qout[7:4] = qout[7:4] + 1;	//高4位不为5,+1
							end
						else
							qout[3:0] = qout[3:0] + 1;	//低4位不为9,+1
					end
				end
			assign cout = ((qout[7:0] == 8'h59) & cin) ? 1 : 0;
			/*
				如果qout[7:0]刚好是8'h59,而且又有+1操作.则产生一个进位输出.
				always块语句和assign语句是并行执行的.
			*/
		endmodule

#### 5.2.2 case语句(多分支语句)

case语句的特点:

	1.当某个控制信号取不同的值时,给另一个输出信号赋不同的值;
	2.case语句常用于多条件译码电路(e.g.译码器、数据选择器、状态机、微处理器的指令译码等);
	3.case语句分为:case, casez, casex.

**1.case语句**

	case (表达式)	//通常为一个信号的某些位
		值1: 语句1;	//具体状态值,因此为常量表达式
		值2: 语句2;
			...
		值n: 语句n;	//各值互不相同,且位宽必须全部相同(且与控制表达是也必须相同).
		default: 语句n+1;	//default可有可无.但只能由一个.
	endcase

**2.casez和casex语句--->case语句的变体**

	1.case语句中,分支表达式每一位值都是确定的(为0或1);
	2.casez语句中,若分支表达式某些位的值为高阻态z,则不考虑对这些位的比较;
	3.casex语句中,若分支表达式某些位的值为z或不定值x,则不考虑对这些位的比较;
	4.分值表达式中,用"?"来标识x或z.

实例---用casez来描述的数据选择器

	module mux_z(out, a, b, c, d, select);
		output out;
		input a, b, c, d;
		input [3:0] select;
		reg out;	//必须声明???
		always @ (select[3:0] or a or b or c or d)
			begin
				casez (select)
					4'b???1: out = a;	//?标识x/z,此处表示高阻态
					4'b??1?: out = b;
					4'b?1??: out = c;
					4'b1???: out = d;
				endcase
			end
	endmodule

**3.条件语句注意事项**

	1.应列出所有条件分支,否则当条件不满足时,编译器会生成一个隐含锁存器保持原值;
		保持原值可用于设计时序电路,如计数器:条件满足时+1,否则保持原值不变.
	2.在组合电路设计中,应该避免生成隐含锁存器.方法为:
		if语句最后加上else项;case语句最后写上default项.

**4.正确使用if语句**

1.生成了不想要的锁存器:

![](images/if_unexpected_latch.png)

	always @ (al or d)
		begin
			if (al)	//此处没有else,因此当al为0时,q保持原值!
				q <= d;
		end

2.不会生成锁存器---一个数据选择器

![](images/if_expected.png)

	always @ (al or d)
		begin
			if (al)
				q <= d;
			else
				q <= 0;	//当al为0时,q等于0!
		end

**5.正确使用case语句**

1.生成了不想要的锁存器:

	always @ (sel[1:0] or a or b) begin
		case (sel[1:0])
			2'b00: q <= a;
			2'b11: q <= b;
		endcase	//当sel为00或11以外的值时,q保持原值!(为锁存)
	end

2.不会生成锁存器---一个数据选择器

	always @ (sel[1:0] or a or b) begin
		case (sel[1:0])
			2'b00: q <= a;
			2'b11: q <= b;
			default: q <= 'b0;	//当sel为00或11以外的值时,q为0.(不会锁存为原值)

### 5.3 循环语句

### 5.3.1 for语句

for语句的结构:

	for (循环变量初值; 循环执行条件; 循环变量增值)
		执行语句

实例1---7人投票器,超过4人投赞成票,则表决通过.

	module vote7(pass, vote);
		output pass;
		input [6:0] vote;
		reg [2:0] sum;	//sum为reg型变量,用于统计赞成的人数
		integer i;
		reg pass;
		always @ (vote)
			begin
				sum = 0;
				for (i=0; i<=6; i=i+1)
					if (vote[i])	//投了赞成票=>即为1
						sum = sum + 1;	//sum增加1
					else;	//保持
				if (sum[2])		//也可以写成:if (sum[2:0] >= 3'd4)
					pass = 1;	//超过4人投赞成票,表决通过
				else
					pass = 0;
			end
	endmodule

实例2---for语句实现两个8位二进制数乘法

	module mult_for(outcome, a, b);
		parameter size = 8;
		output [2*size : 1] outcome;
		input [size : 1] a, b;
		reg [2*size : 1] outcome;
		integer i;
		always @ (a or b) begin
			outcome = 0;
			for (i=1; i<=size; i=i+1)
				if (b[i])
					outcome = outcome + (a << (i-1));	//a左移(i-1)位,后面的用0填充.
				else;
		end
	endmodule

### 5.3.2 repeat语句

连续执行一条或多条语句n次.repeat语句结构如下:

	repeat (循环次数) begin
		执行语句
	end

实例---repeat语句实现两个8位二进制数乘法(不如for语句简单)

	module mult_repeat(outcome, a, b);
		parameter size = 8;
		output [2*size : 1] outcome;
		input [size : 1] a, b;
		reg [2*size : 1] outcome;
		reg [2*size : 1] temp_a;	//存放a左移一位后的结果
		reg [size : 1] temp_b;		//存放b右移一位后的结果
		always @ (a or b) begin
			outcomt = 0;
			temp_a = a;
			temp_b = b;
			repeat (size) begin	//重复执行后面的语句size次
				if (temp_b[1])	//temp_b最低位为1,则执行下面的加法
					outcome = outcome + temp_a;
				else;	//保持原值
				temp_a = temp_a << 1;	//每循环一次,a左移一位
				temp_b = temp_b >> 1;	//每循环一次,b右移一位
			end
		end
	endmodule

### 5.3.3 while语句

while语句结构如下:

	while (条件表达式) begin
		执行语句
	end

实例1---while语句实现对一个8位二进制数中值为1的位进行计数.

	module count1s_while(count, rega, clk);
		output [3:0] count;
		input [7:0] rega;
		input clk;
		reg [3:0] count;
		always @ (posedge clk)
			begin:count1	//count1:应该为一个标号
				reg[7:0] tempreg;	//用作条件表达式
				count = 0;
				tempreg = rega;
				while (tempreg) begin	//非0,执行下面语句
					if (tempreg[0])
						count = cout + 1;	//tempreg最低位为1,统计+1.
					else;
					tempreg = tempreg >> 1;	//右移1位.更改条件表达式的值.
				end
		end
	endmodule

实例2---for语句实现对一个8位二进制数中值为1的位进行计数(更简单)

	module count1s_for_good(count, rega);
		output [3:0] count;
		input [7:0] rega;
		reg [3:0] count;
		always @ (rega)
			begin:block
				integer i;
				count = 0;
				for (i=0; i<=7; i=i+1)
					if (rega[i] == 1)
						count = count + 1;
					else;
			end
	endmodule

PS:while语句只有当循环块有时间控制(即@ (posedge clk))时才可综合!!!!

### 5.3.4 forever语句

无条件连续执行forever后面的语句或语句块.forever语句结构如下:

	forever 语句

forever语句特点:

	1.forever语句常用在测试模块中产生周期性的波形,作为仿真激励信号;
	2.常用disable语句跳出循环;
	3.不同于always语句,不能独立写在程序中,一般用于initial语句块中.

实例

	initial
		begin:Clocking
			clk = 0;
			#10 forever #10 clk = !clk;
		end
	initial
		begin:Stimulus
			...
			disable Clocking;	//停止时钟
		end

### 5.4 结构说明语句

分为4种:

	initial说明语句:只执行一次;
	always说明语句:不断重复执行,直到仿真结束;
	task说明语句:可在程序模块中的一处或多处调用;
	function说明语句:可在程序模块中的一处或多处调用;

#### 5.4.1 always块语句

包含一个或多个声明语句(e.g.过程赋值语句、任务调用、条件语句或循环语句等),在仿真运行的全过程中,在定时控制下被反复执行.

**1.规则**

	1.在always块中被赋值的只能是register型变量(e.g.reg, integer, real, time等);
	2.每个always块在仿真一开始便开始执行,当执行完块中最后一个语句,继续从always块的开头执行.
	3.当always块中包含一个以上的语句时,这些语句必须放在begin-end或fork-join块中:
		always @ (posedge clk or negedge clear) begin
			if (!clear) qout = 0;	//异步清0
			else		qout = 1;	//此处包含if...else至少两个语句,要用begin-end.
		end
	4.always语句必须与一定的时序控制结合在一起才有用,没有时序控制,易形成仿真死锁.
		e.g.生成一个0延迟的无线循环跳变过程---形成仿真死锁:
			always areg = ~areg;

实例1---在测试文件中,生成一个无线延续的信号波形(时钟信号)

	`define half_period 50
	module half_clk_top;
		reg reset, clk;	//输入信号
		wire clk_out;	//输出信号
		always #half_period clk = ~clk;	//生成无线延续,间隔50的时钟信号
			...
	endmodule

实例2---用always块语句产生T'FF和8位二进制计数器.

	module always_demo(counter, tick, clk);
		output [7:0] counter;
		output	tick;
		input clk;
		reg [7:0] counter;
		reg tick;
		always @ (posedge clk) begin	//每次碰到clk的上升沿就会执行一次
			tick = ~tick;	//每次clk的上升沿翻转一次
			counter = counter + 1;	//每次clk的上升沿计数一次
		end
	endmodule

**2.模板及说明**

1.模板:

	always @ (敏感信号表达式) begin
		//过程赋值语句.reg, integer, real, time等
		//if, case, while, repeat, for, task, function等语句
	end

2.说明:

	1.敏感信号表达式(又称事件表达式或敏感表),当其值改变时,则执行一遍块内语句;
	2.在敏感信号表达式中应列出影响块内取值的所有信号;
	3.敏感信号为多个信号时,中间用关键字or连接;
	4.敏感信号不要为x或z,否则会阻挡进程;
	5.always的时间控制可以为沿触发(描述时序逻辑),也可为电平触发(描述组合逻辑);
	6.关键字posedge表示上升沿触发,negedge表示下降沿触发.

说明实例:

	1.两个沿触发的always块:
		always @ (posedge clock or posedge reset) begin
			...
		end
	2.多个电平触发的always块:
		always @ (a or b or c) begin
			...
		end

**3.可综合性问题**

always块语句是用于综合过程最有用的语句之一,为了得到最好的综合结果,必须按照下面的模板来编写:

模板1:

	always @ (Inputs)	//所有输入信号必须列出,用or隔开
		begin
			...		//组合逻辑关系
		end

模板2:

	always @ (Inputs)	//所有输入信号必须列出,用or隔开
		begin
			if (Enable) begin
				...		//锁存动作
			end
		end

模板3:

	always @ (posedge Clock)	//Clock only(只有时钟)
		begin
			...		//同步动作
		end

模板4:

	always @ (posedge Clock or negedge Reset) //Clock and Reset only(有时钟和复位信号)
		begin
			if (~Reset)		//测试异步复位电平是否有效
				...			//异步动作
			else
				...			//同步动作
		end					//可产生触发器和组合逻辑

**4.注意点**

1.当always块有多个敏感信号时,一定要采用if...else if语句,不能采用并列的if语句.否则会造成一个寄存器有多个时钟驱动,出现编译错误.

	always @ (posedge min_clk or negedge reset) begin
		if (reset)
			min <= 0;
		else if (min = 8'h59)	//当reset无效且min=8'h59时(此处一定不能写成if)
			begin
				min <= 0;
				h_clk <= 1;
			end
	end

2.通常采用异步清0.只有在时钟周期很小或清0信号为电平信号时(容易捕捉到清0信号)才采用同步清0.

#### 5.4.2 initial语句

1.initial语句的用途

	1.在仿真的初始状态对各变量进行初始化;
	2.在测试文件中生成激励波形作为电路的仿真信号.

2.initial语句的格式

	initial
		begin
			...
		end

实例1---利用initial语句生成激励波形

	initial
		begin
			inputs = 'b000000;
			#10 inputs = 'b011001;	//#10表示delay 10.
			#10 inputs = 'b011011;
			#10 inputs = 'b011000;
			#10 inputs = 'b001000;
		end

实例2---对各变量进行初始化

	...
	parameter size = 16;
	reg [3:0] addr;
	reg reg1;
	reg [7:0] memory[0:15];	//16个8位存储器
	initial	//对各变量进行初始化
		begin
			reg1 = 0;
			for (addr=0; addr<size; addr=addr+1)
				memory[addr] = 0;
		end
	...

#### 5.4.3 task语句

1.task语句用途

	1.对一些信号进行一些运算并输出多个结果(即有多个输出变量)时,宜采用任务结构;
	2.利用任务来帮助实现结构化的模块设计,将批量的操作以任务的形式独立出来,使设计简单明了.

2.task的定义及调用

	1.定义
		task task_name;
			端口及数据类型声明语句;
			其他语句;
		endtask
	2.调用
		task_name (端口1, 端口2, ...);

3.注意点

	1.任务的定义和调用必须在一个module模块内;
	2.任务呗调用时,需列出端口名列表,且必须与定义中的I/O一一对应;
	3.一个任务可以调用其他任务和函数.

4.实例1---任务的定义与调用说明

	1.定义
		task my_task;
			input a, b;
			inout c;
			output d, e;
				...	//任务中的语句
			c = foo1;
			d = foo2;	//对任务的输出变量赋值
			e = foo3;
		endtask

	2.调用
		my_task(v,w,x,y,z);
	/*
		1.任务启动时,由v,w,x传入的变量赋给a,b,c;
		2.任务完成后,输出通过c,d,e赋给x,y,z.
	*/

5.实例2---4个4位二进制输入数据的冒泡排序及测试代码

	1.冒泡排序
	module sort4(ra, rb, rc, rd, a, b, c, d);
		output [3:0] ra, rb, rc, rd;
		input [3:0] a, b, c, d;
		reg [3:0] ra, rb, rc, rd;
		reg [3:0] va, vb, vc, vd;	//中间变量,存放两个数据交换的结果
		always @ (a or b or c or d)
			begin
				{va, vb, vc, vd} = {a, b, c, d};	//赋初值
				sort2(va, vc);	//va,vc比较,较小值存入va
				sort2(vb, vd);	//vb,vd比较,较小值存入vb
				sort2(va, vb);	//va,vb比较,较小值存入va(va为最小值)
				sort2(vc, vd);	//vc,vd比较,较小值存入vc(vd为最大值)
				sort2(vb, vc);	//vb,vc比较,较小值存入vb
				{ra, rb, rc, rd} = {va, vb, vc, vd};
			end
		task sort2;	//任务:比较两个数,按从小到大的顺序排序
			inout [3:0] x, y;	//双向类型
			reg [3:0] tmp;
			if (x > y)
				begin
					tmp = x;	//x,y内容交换.要求顺序执行,采用阻塞赋值方式
					x = y;
					y = tmp;
				end
			else;
		endtask
	endmodule

	2.测试代码
		'timescale 1ns/100ps
		'include "./sort4.v"
		module task_top;
			reg [3:0] a, b, c, d;
			wire [3:0] ra, rb, rc, rd;
			initial	//赋予激励
				begin
					a = 0;
					b = 0;
					c = 0;
					d = 0;
					repeat(5)	//循环5次
						begin
							#100 a = {$random} % 15;
								 b = {$random} % 15;
								 c = {$random} % 15;
								 d = {$random} % 15;
								/*
								1.$random为系统任务,返回一个32位的带符号的随机数;
								2.用法:$random % b(b>0),得到一个范围在-(b+1)~(b-1)
									之间的随机数.
								3.{$random}%15通过位拼接操作,产生一个0~14之间的随机数.
								*/
						end
						#100 $stop;	//暂停仿真
				end
			sort4 my_sort4(.ra(ra),.rb(rb),.rc(rc),.rd(rd),.a(a),.b(b),.c(c),.d(d));
		endmodule

#### 5.4.4 function语句

函数在模块内部定义,通常在本模块中调用.任务只能在同一模块内定义与调用.

**1.函数定义**

	function [7:0](返回值为位宽或类型说明) gefun(函数名);
		input [7:0] x;	//输入变量(端口声明)
		...
		gefun = count;	//函数名(也是内部寄存器):将输出赋值给函数名,作为返回值.
	endfunction

**2.函数调用**

	assign number = gefun(rega);	//对函数的调用

**3.函数的使用规则**

	1.函数的定义不能包含任何时间控制语句(e.g.用延迟#,事件控制@或等待wait标识的语句);
	2.函数不能调用任务;
	3.定义函数时至少要有一个输入参量.且不能有任何output,inout变量;
	4.函数定义中必须有一条赋值语句,将结果值赋给内部寄存器(也是函数名).

**4.实例**

实例1---利用函数对一个8位二进制数中为0的位进行计数.

	module count0s_function(number, rega);
		output [7:0] number;
		input [7:0] rega;

		function [7:0] gefun;
			input [7:0] x;	//只有输入变量(即input变量)
			reg [7:0] count;
			integer i;
			begin
				count = 0;
				for (i=0; i<=7; i=i+1)
					if (x[i] == 1'b0)
						count = count + 1;
					else;
				gefun = count;	//gefun:函数名(内部寄存器)
			end
		endfunction
		
		assign number = gefun(rega);	//rega对应函数的输入变量
	endmodule

实例2---阶乘运算函数

	module tryfunct(result, clk, reset, n);
		function [31:0] factorial;
			input [3:0] op;
			reg [3:0] ina;
			begin
				factorial = op ? 1 : 0;
				for (inta=2; ina<=op; ina=ina+1)
					factorial = ina * factorial;	//factorial:既是函数名又是内部寄存器.
			end
		endfunction

		output [31:0] result;
		input [3:0] n;
		input reset, clk;
		reg [31:0] result;
		
		always @ (posedge clk)	//clk的上升沿触发同步运算
			begin
				if (!reset)
					result <= 0;
				else
					result <= factorial(n);	//函数的调用
			end
	endmodule

tryfunct.v的测试模块

	`include "./tryfunct.v"
	`timescale 1ns/100ps
	`define clk_cycle 50
	
	module tryfuncttop;
		reg [3:0] n, i;
		reg reset, clk;
		wire [31:0] result;
		initial	//对变量进行初始化,并生成激励波形
			begin
				n = 0;
				reset = i;
				clk = 0;
				#100 reset = 0;
				#100 reset = 1;
				for (i=0; i<=15; i=i+1)
					begin
						#200 n = i;
					end
				#100 $stop;
			end
		always #`clk_cycle clk = ~clk;	//产生时钟波形
		
		tryfunct tryfunct(.clk(clk), .n(n), .result(result), .reset(reset));
		//模块元件例化
	endmodule

**5.task与function语句的区别**

略.

### 5.5 编译预处理语句

编译预处理语句是以"`"开头.在编译时,编译系统先对编译预处理语句进行预处理,然后将处理结果和源程序一起进行编译.

#### 5.5.1 `define语句

**1.格式**

	`define 宏名 宏内容

**2.说明**

	1.宏名一般用大写字母,用以区分变量名;
	2.宏名有效范围为定义命令之后到源程序结束;
	3.引用已定义的宏名前面必须加上"`",即为"`宏名";
	4.宏名和宏内容必须在同一行中声明.
	5.宏定义不是语句,不必在行末加分号.加了会一起置换.

**3.实例**

实例---宏的层层置换

	module test;
		reg a, b, c;
		wire out;
		`define aa a+b
		`define cc c+`aa	//引用已定义的宏名`aa来定义宏cc
		assign out = `cc	//展开后的语句为:assign out = c + a + b;
		...
	endmodule

#### 5.5.2 `include语句

包含另一个源文件的全部内容.在包含的地方直接替换.

实例---用`include语句设计16位加法器

1.adder模块(adder.v)

	module adder(cout, sum, a, b, cin);
		output cout;
		parameter size = 1;
		output [size-1:0] sum;
		input [size-1:0] a, b;
		input cin;
		assign {cout, sum} = a + b + cin;
	endmodule

2.adder16模块(adder16.v)

	`include "adder.v"	//包含adder.v文件
	module adder16(cout, sum, a, b, cin);
		output cout;
		parameter my_size = 16;
		output [my_size-1:0] sum;
		input [my_size-1:0] a, b;
		input cin;
		adder #{my_size} my_adder(cout, sum, a, b, cin);	//使用adder模块
		/*#{my_size}:此处表示用my_size替换模块adder中的size(为parameter常量)*/
	endmodule

#### 5.5.3 `timescale语句

timescale(时间尺度语句):用于定义跟在该命令后模块的时间单位和时间精度.

**1.格式**

	`timescale 时间单位/时间精度

**2说明**

	1.时间单位:用于定义模块中仿真时间和延迟时间的基准单位;
	2.时间精度:用来声明该模块的仿真时间和延迟时间的精确程度.
	3.时间精度至少要和时间单位一样精确;
	4.时间精度值不能大于时间单位值;
		`timescale 1ps/1ns	//非法
		`timescale 1ns/1ps	//合法
	5.时间单位和时间精度数字必须是整数(e.g.1, 10, 100等);
	6.单位为:
		s,ms,us,ns,ps(皮秒),fs(毫皮秒).

**3.实例**

实例---`timescale语句应用实例

	`timescale 10ns/1ns	//时间单位为10ns,时间精度为1ns
	...
	reg sel;
	initial
		begin
			#10 sel = 0;	//在10ns*10时刻,sel变量被赋值为0
			#10 sel = 1;	//在10ns*20时刻,sel变量被赋值为1(顺序执行的,中间差#10)
		end
	...

### 5.6 语句的顺序执行与并行执行

#### 5.6.1 语句的顺序执行

**1.顺序执行的特点**

	1.在always模块内,逻辑按书写的顺序执行;	=>因此随意颠倒always模块的语句可能导致结果不同.
	2.阻塞赋值语句当本语句结束时即完成赋值操作.

**2.顺序执行模块实例**

实例1---两波形相反

	module serial1(q, a, clk);
		output q, a;
		input clk;
		reg q, a;
		always @ (posedge clk)
			begin
				q = ~q;	//阻塞赋值语句.对前一时刻的q值取反
				a = ~q;	//对当前时刻的q值取反.因此两波形相反
			end
	endmodule

实例2---两波形相同

	module serial2(q, a, clk);
		output q, a;
		input clk;
		reg q, a;
		always @ (posedge clk)
			begin
				a = ~q;	//对前一时刻q值取反
				q = ~q;	//对前一时刻q值取反.因此两波形相同
			end
	endmodule
	
#### 5.6.1 语句的并行执行

**1.并行执行的特点**

	always模块、assign语句、实例元件都是同时(并行)执行的.因此他们在程序中的先后顺序对结果无影响.

**2.并行执行模块实例**

实例1---两波形相同

	module parall1(q, a, clk);
		output q, a;
		input clk;
		reg q, a;
		always @ (posedge clk)
			begin
				q = ~q;
			end
		always @ (posedge clk)	//两个always模块并行执行.波形相同
			begin
				a = ~q;
			end
	endmodule

实例2---两波形相同

	module parall2(q, a, clk);
		output q, a;
		input clk;
		reg q, a;
		always @ (posedge clk)
			begin
				a = ~q;
			end
		always @ (posedge clk)	//两个always模块并行执行.波形相同
			begin
				q = ~q;
			end
	endmodule

### 5.7 不同抽象级别的Verilog HDL模型

Verilog HDL模型的多种级别的描述:

	1.系统级(System Level):用高级语言结构(e.g.case语句)实现的设计模块外部性能的模型;
	2.算法级(Algorithmic Level):用高级语言结构实现的设计算法模型;
		--->使用逻辑表达式.
	3.RTL级(Register Transfer Level):描述数据在寄存器之间流动和如何处理这些数据的模型;
		--->常用.
	4.门级(Gate Level):描述逻辑门(e.g.与门、非门、或门、与非门、三态门等)以及逻辑门之间连接的模型;
	5.开关机(Switch Level):描述器件中三极管和存储节点及其之间连接的模型.

#### 5.7.1 Verilog HDL的门级描述

**1.特点**

	1.使用逻辑门和开关进行描述,模型最直观;
	2.所建立的硬件模型是可仿真的,也是可综合的;
	3.门类型的关键字常用的如下:
		not, and, nand, or, nor, xor, xnor, buf, bufif1, bufif0,
		notif1, notif0(及各种三态门)
	4.门级描述不适于描述复杂的系统.
	PS:在模块中写端口列表时,输出信号应列在最前面.

**2.实例---使用门原语实现4选1数据选择器**

逻辑电路图如下:

![](images/4_1_multiplexer.png)

真值表如下:

![](images/truth_table_4_1_multiplexer.png)

代码:

	//4_1 multiplexer using gate primitive.
	module mymux(out, in1, in2, in3, in4, ctrl1, ctrl2);
		output out;
		input in1, in2, in3, in4, ctrl1, ctrl2;
		wire notctrl1, notctrl2, w, x, y, z;
		not(notctrl1, ctrl1);	//ctrl1取反后存放在notctrl1中
		not(notctrl2, ctrl2);	//ctrl2取反后存放在notctrl2中
		and(w, in1, notctrl1, notctrl2);	//in1,notctrl1,notctrl2做与运算后存放在w中
		and(x, in2, notctrl1, ctrl2);	//in2,notctrl1,ctrl2做与运算后存放在x中
		and(y, in3, ctrl1, notctrl2);	//in3,ctrl1,notctrl2做与运算后存放在y中
		and(z, in4, ctrl1, ctrl2);	//in4,ctrl1,ctrl2做与运算后存放在z中
		or(out, w, x, y, z);	//w,x,y,z做或运算后存放在out中
	endmodule

#### 5.7.2 Verilog HDL的行为级描述(包括系统级、算法级、RTL级)

**1.逻辑功能描述---算法级**

实例---用逻辑表达式实现4选1数据选择器

	module mux4_1(out, in1, in2, in3, in4, ctrl1, ctrl2);
		output out;
		input in1, in2, in3, in4, ctrl1, ctrl2;
		assign out = (in1 & ~ctrl1 & ~ctrl2) |	//~:按位取反;!:取非运算.
						(in2 & ~ctrl1 & ctrl2) |
						(in3 & ctrl1 & ~ctrl2) |
						(in4 & ctrl1 & ctrl2);
	endmodule

**2.case语句描述---系统级**

只需要知道输入与输出间的真值表.比调用门原语和采用逻辑功能描述更简洁.

实例---用case语句描述4选1数据选择器(case语句应放在always块内)

	module mux4_1(out, in1, in2, in3, in4, ctrl1, ctrl2);
		output out;
		input in1, in2, in3, in4, ctrl1, ctrl2;
		reg out;
		always @ (in1 or in2 or in3 or in4 or ctrl1 or ctrl2)
			case({ctrl1, ctrl2})	//case语句应放在always块内
				2'b00: out = in1;
				2'b01: out = in2;
				2'b10: out = in3;
				2'b11: out = in4;
				default: out = 1'bx;
			endcase
	endmodule

**3.条件运算符描述---算法级**

只需要知道输入与输出间的真值表.

实例---用条件云算法描述4选1数据选择器

	module mux4_1(out, in1, in2, in3, in4, ctrl1, ctrl2);
		output out;
		input in1, in2, in3, in4, ctrl1, ctrl2;
		assign out = ctrl1 ? (ctrl2?in4:in3) : (ctrl2?in2:in1);
	endmodule

PS:采用逻辑表达式或case语句描述代码更简单,也更抽象.且耗用器件资源更多.

#### 5.7.3 小结

1.采用的描述级别越高,设计越容易,程序代码越简单.但耗用器件资源越多.对特定综合器,可能无法将某些抽象级别高德描述转换为电路;

2.门级描述的硬件模型可仿真、综合,且系统速度快;

3.一般使用算法级(写出逻辑表达式)或RTL级来描述逻辑功能,应避免采用门级描述,除非对系统速度要求比较高的场合才采用门级描述.

4.当器件容量有限时,为减少器件资源的耗用,应少用if-else语句和case语句,尽量直接使用逻辑表达式来描述系统的逻辑功能.

5.用case语句代替if-else语句也可以减少器件使用.

### 5.8 设计技巧

1.一个变量不能在多个always块中被赋值(所有的always块之间都是并行执行);

2.当输出信号为总线信号时,一定要在I/O说明中指明其位宽.没有标明位宽,就不会被当成总线信号.

	output [4:0] run_cnt;	//一定要指明位宽
	reg [4:0] run_cnt;	//同时reg声明时也需要.

3.区分阻塞赋值和非阻塞赋值.建议均采用非阻塞赋值语句.
