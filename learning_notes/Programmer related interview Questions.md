# Programmer related interview Questions

## 1. 赋值语句

### Q1

	int i = 1;
	void main()
	{
		int i = i;
	}

	/*
		此处应该是:	main()里的i是一个未定义值.
		main()里的i不是1,它和main()外的i无关.是一个未定义值.
	*/

### Q2

	#include <iostream>
	using namespace std;
	int main()
	{
		int x = 2, y, z;
		x *= (y = z = 5);	//x的值为:2 * 5 = 10
		cout << x << endl;	//结果为:10
		x =3;
		x == ( y = z);	//该句仅仅只是比较,不会更改x的值
		cout << x << endl;	//x的值不便,仍然为:10
		x = (y == z);	//x取值为y与z比较的布尔值.y与z相等,返回布尔值true(即1),因此x的值为"1".
		cout << x << endl;	//结果为:1
		x = (y & z);	//y与z按位取与,得到的结果赋值给z.y与z相等(为3),因此结果为3.
		cout << x << endl;	//结果为:3
		x = (y && z);	//y与z取与运算,y和z都为3,为true.因此x为true,其值为"1"
		cout << x << endl;	//结果为:1
		y = 4;
		x = (y | z);	//y为4,z为3,按位取与.结果为111(即7).
		cout << x << endl;	//结果为:7
		x = (y || z);	//y与z取或运算,y(4)和z(3)都为true.因此x为true,其值为"1"
		cout << x << endl;	//结果为:1
	}

### Q3.

	#include <iostream>
	using namespace std;
	int func(int x)
	{
		int count = 0;
		while (x) {
			count++;
			x = x & (x - 1); //每次会将x的最高一个bit给mask掉.因此是为计算x转换为二进制后含有1的数量.
		}
		return count;
	}

	int main()
	{
		cout << func(9999) << endl;
		return 0;
	}

	/*使用短除法可以计算得到:
		9999转成二进制后结果为:10011100001111.
		因此答案为:8.
	*/

## 2. i++

### Q1.

	1.程序1
	#include <iostream>
	using namespace std;
	int main()
	{
		int a, x;
		for (a=0, x=0; a<=1 && !x++; a++) {
			a++;
		}
		cout << a << x << endl;
		return 0;
	}
	/*
		1.开始a=0, x=0.做判断"!x++"为真,但是x的值为1.
		2.执行for中的a++,此时a为1.
		3.执行循环变量的++(即a++).之后a变为2.
		因此最后结果为:2 1
	*/

	2.程序2
	#include <iostream>
	using namespace std;
	int main()
	{
		int a, x;
		for (a=0, x=0; a<=1 && !x++;) {
			a++;
		}
		cout << a << x << endl;
		return 0;
	}
	/*
		1.开始a=0, x=0.做判断"!x++"为真,但是x的值为1.
		2.执行for中的a++,此时a为1.
		3.判断条件,第一个条件"a<=1"满足.判断第二个"!x++",虽然不满足,但是x执行了"++".因此x的值为2.
		因此最后的结果为:1 2
	*/

### Q2.

	#include <stdio.h>
	void main()
	{
		int i = 2;
		printf("%d, %d, %d, %d\n", i++, ++i, i, i++);
		printf("%d\n", i);
	}

	/*
		1.printf的执行顺序是从右到左.
		2.VC++6.0是整条语句结束以后才会将延后的操作更新.
		因此从右到左运算:
		i++ ---> 先使用i(i=2),结果为2.i的自增之后在本条语句结束后才会得到更新.
		i	---> i=2,结果为2.
		++i	---> 先进行++(i=3),因此结果为3.
		i++	---> 因为i=3,i++会延后操作.因此此时结果为3.
		下一行会将上一行所有的自增操作得到更新,因此结果为5.
	*/