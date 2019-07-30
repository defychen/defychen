# C++ Exercise

## Chapter 8. IO库

IO库说明:

	1.iostream处理控制台IO;
	2.fstream处理文件IO;
	3.stringstream完成内存string的IO.

### 8.1 练习1

编写一个函数,接受一个istream &参数,返回值类型也是istream &.从流中读取数据,直到遇到文件结束符停止.

**1.代码**

	#include <iostream>
	#include <stdexcept>
	using namespace std;
	
	istream &f(istream &in)
	{
		int v;
		while (in >> v, !in.eof()) {
			if (in.bad())	//发生丢失,此时需要抛出异常
				throw runtime_error("IO stream error");
			if (in.fail()) {	//发生数据格式错误,需要处理.
				cerr << "data error, please retry:" << endl;
				in.clear();		//清除错误
				in.ignore(100, '\n');	//忽略之后的100个字符,遇到'\n'结束.
				continue;
			}
			cout << v << endl;
		}
		in.clear();
		return in;
	}
	
	int main()
	{
		cout << "Please input some integers, Ctrl+z indicate end!" << endl;
		f(cin);
		return 0;
	}

**2.结果**

	Please input some integers, Ctrl+z indicate end!
	1 2 3 7.3
	1
	2
	3
	7	
	/*
		1.当读取7.3时,由于接受一个整数,先读取7,输出该值;
		2.紧接着读取".3",由于格式错误,因为打印"data error, please retry:",然后忽略100个字符,
			直到遇到'\n'结束;
	*/
	data error, please retry:
	a
	data error, please retry:
	Ctrl+z	//结束

### 8.2 练习2

while (cin >> i)终止情况:

	当遇到文件结束符、IO流错误、或读取了无效的数据该循环会终止.

### 8.3 练习3

编写函数,以读模式打开一个文件,将其内容读入到一个string的vector中.并将每一行作为一个独立的元素存放在vector中.

	#include <iostream>
	#include <fstream>
	#include <vector>
	#include <string>
	using namespace std;

	int main()
	{
		ifstream in("data");	//打开某文件
		if (!in) {
			cerr << "Can not open file!" << endl;
			return -1;
		}

		string line;
		vector<string> words;
		while (getline(in, line)) {	//从文件中读取一行,放在line中
			words.push_back(line);	//添加到vector中
		}
		in.close();	//关闭文件

		vector<string>::const_iterator it = words.begin();
		while (it != words.end()) {	//遍历vector
			cout << *it << endl;
			it++;
		}
		return 0;
	}

### 8.4 练习4

编写函数,以读模式打开一个文件,将其内容读入到一个string的vector中.并将每一个单词作为一个独立的元素存放在vector中.

	将上题的:
		while (getline(cin, line))
	更改为:
		while (cin >> line)
	即可.

### 8.5 练习5

打印一个istringstream对象的内容.

**1.代码**

	#include <iostream>
	#include <sstream>
	#include <string>
	#include <stdexcept>
	using namespace std;

	istream &f(istream &in)
	{
		string v;
		while (in >> v, !in.eof()) {
			if (in.bad())
				throw runtime_error("OI error!");
			if (in.fail()) {
				cerr << "data error, please retry:" << endl;
				in.clear();
				in.ignore(100, '\n');
				continue;
			}
			cout << v << endl;
		}
		in.clear();
		return in;
	}

	int main()
	{
		ostringstream oss;
		oss << "C++ Primer 5th version" << endl;
		istringstream iss(oss.str());
		f(iss);
		return 0;
	}


**2.结果**

	C++
	Primer
	5th
	version

### 8.6 练习6

读取一个文件中的行保存在一个vector<string>中,然后使用istringstream从vector中读取数据元素,每次读取一个单词.

	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	#include <vector>
	using namespace std;

	int main()
	{
		ifstream in("data");
		if (!in) {
			cerr << "Can not open file" << endl;
			return -1;
		}

		string line;
		vector<string> words;
		while (getline(in, line)) {
			words.push_back(line);
		}
		in.close();

		vector<string>::const iterator it = words.begin();
		while (it != words.end()) {
			istringstream iss(*it);	//字符串初始化istringstream
			string word;
			while (iss >> word)
				cout << word << " ";
			cout << endl;
			++it;
		}
		return 0;
	}

### 8.7 练习7

调用clear来重置istringstream的状态,然后将istringstream对象通过str成员绑定到不同的字符串.

	#include <iostream>
	#include <sstream>
	#include <string>
	#include <vector>
	using namespace std;
	
	struct PersonInfo {
		string name;
		vector<string> phone_number;
	};
	
	int main()
	{
		string line, word;
		vector<PersonInfo> people;
		istringstream record;
	
		while (getline(cin, line)) {
			PersonInfo info;
			record.clear();	//重复使用istringstream对象时,每次都要调用clear函数来清除状态.
			record.str(line);
			/*
				istringstream的str()成员函数直接使用string对象来作为参数进行读入.
			*/
			record >> info.name;
			while (record >> word)
				info.phone_number.push_back(word);
			people.push_back(info);
		}
		return 0;
	}

### 8.8 练习8

上题8.7中改为从文件中读取数据.

	#include <iostream>
	#include <fstream>
	#include <sstream>
	#include <string>
	#include <vector>
	using namespace std;
	
	struct PersonInfo {
		string name;
		vector<string> phone_number;
	};
	
	string format(const string &s)
	{
		return s;
	}
	
	bool valid(const string &s)
	{
		return true;
	}
	
	int main(int argc, char *argv[])
	{
		string line, word;
		vector<PersonInfo> people;
		istringstream record;
	
		if (argc != 2) {
			cerr << "Please specify filename" << endl;
			return -1;
		}
	
		ifstream in(argv[1]);
		if (!in) {
			cerr << "Can not open file" << endl;
			return -1;
		}
	
		while (getline(in, line)) {
			PersonInfo info;
			record.clear();
			record.str(line);
			record >> info.name;
			while (record >> word)
				info.phone_number.push_back(word);
	
			people.push_back(info);
		}
	
		ostringstream oss;
		for (const auto &entry : people) {
			ostringstream formatted, badNums;
			for (const auto &nums : entry.phone_number) {
				if (!valid(nums)) {
					badNums << " " << nums;
				} else {
					formatted << " " << format(nums);
				}
			}
			if (badNums.str().empty()) {
				/*
					ostringstream对象判断空的方法:
						oss.str().empty();	--->先调用str()转成string,再调用string的emtpy()函数.
				*/
				oss << entry.name << " " << formatted.str() << endl;
			} else {
				cerr << "Input error: " << entry.name << " Invalid numbers " << badNums.str() << endl;
			}
		}
		cout << os.str() << endl;
		/*
			ostringstream的输出方法:
				os.str(); --->先调用str()转成string,然后跟在cout后面即可.
		*/
		return 0;
	}

***

## Chapter 9. 顺序容器

### 9.1 练习1

vector/deque/list使用场景:

	vector:适合于在尾部进行插入和删除操作,在其他位置则不适合;
	deque:适合于在头、尾位置进行插入和删除操作;如果还需要进行频繁随机访问,则deque相比较于list更好;
	list:适合于在任意位置进行快速插入和删除操作.

### 9.2 练习2

定义一个list对象,其元素类型为int的deque.

	#include <list>
	list<deque<int>> a;

### 9.3 练习3

编写函数,参数为两个vector<int>的迭代器和一个int值.在两个迭代器指定的范围中查找给定的值.

	#include <iostream>
	#include <vector>
	using namespace std;
	
	bool search_vec(vector<int>::iterator beg, vector<int>::iterator end, int val)
	{
		for (; beg != end; beg++) {
			if (*beg == val)
				return true;
		}
		return false;
	}
	
	int main()
	{
		vector<int> ivec = {1, 2, 3, 4, 5, 6, 7};
	
		cout << search_vec(ivec.begin(), ivec.end(), 3) << endl;
		cout << search_vec(ivec.begin(), ivec.end(), 8) << endl;
		return 0;
	 }

### 9.4 练习4

与上题一样,但是返回一个迭代器指向找到的元素.

	#include <iostream>
	#include <vector>
	using namespace std;
	
	vector<int>::iterator search_vec(vector<int>::iterator beg, vector<int>::iterator end,
		int val)
	{
		for (; beg != end; beg++) {
			if (*beg == val)
				return beg;	//搜索成功,返回元素对应的迭代器
		}
		return end;	//搜索失败,返回尾后迭代器
	}
	
	int main()
	{
		vector<int> ivec = {1, 2, 3, 4, 5, 6, 7};
	
		cout << search_vec(ivec.begin(), ivec.end(), 3) - ivec.begin() << endl;
			//两个迭代器之间的差(等于元素相距的元素个数)--->结果为:2
		cout << search_vec(ivec.begin(), ivec.end(), 8)  - ivec.begin() << endl;
			////由于没找到,因为返回了ivec.end()--->因此结果为:7(元素总个数)
		return 0;
	 }

### 9.5 练习5

vector、deque与list迭代器的差异:

	1.array,vector和deque的类模板是基于数组的,因此其元素在内存中是连续保存的.可以使用迭代器的大小比较
		(类似指针的大小比较)来体现元素的前后关系.e.g.
			vector<int>::iterator iter1 = vec.begin(), iter2 = vec.end();
			while (iter1 < iter2)	//由于内存连续,这样使用没问题
	2.list和forward_list是基于链表的,迭代器的大小(即指针大小)与元素的前后无直接关系.因此list/forwar_
		list不支持<运算.只支持递增、递减、===即!=运算.e.g.
			 list<int>::iterator iter1 = lst.begin(), iter2 = lst.end();
			while (iter1 < iter2)	//不支持.

### 9.6 练习6

读取和写入list方法:

	1.读取string的list中的元素方法:
		list<string>::value_type	//value_type表示元素类型;
	2.写入string的list中的元素,需要使用非常量的引用类型:
		list<string>::reference

### 9.7 练习7

对象类型说明:

	vector<int v1>;
	const vector<int> v2;
	auto it1 = v1.begin(), it2 = v2.begin();
	auto it3 = v1.cbegin(), it4 = v2.cbegin();
	1.v1是int的vector类型,可以修改v1的内容(包括添加、删除元素及修改元素值等操作);
	2.v2是int的常量vector类型,其内容不能修改(即添加、删除元素及修改元素值均不允许);
	3.v3,v4和v2一样都是const迭代器,const迭代器不能对容器元素进行写访问.

### 9.8 练习8

6中创建和初始化vector对象的方法:

	1.vector<int> ivec;
		/*
			默认初始化,vector为空.size返回0,capacity返回0.适用于在程序运行期间动态添加元素的情况;
		*/
	2.vector<int> ivec2(ivec);
		/*
			ivec2为ivec的拷贝,ivec2具有和ivec相同的容量和元素(容器和元素类型必须是一样的);
			等价方式:
			vector<int> ivec2 = ivec;	//支持直接赋值
		*/
	3.vector<int> ivec = {1, 2, 3.0, 4, 5, 6, 7};
		/*
			ivec为初始化列表中元素的拷贝.列表中的元素必须和ivec指定类型(即int)具有相容性.此处为必须是与
			整形相容的数值类型(e.g.元素列表中的"3.0").
			等价方式:
			vector<int> ivec{1, 2, 3.0, 4, 5, 6, 7};
		*/
	4.vector<int> ivec2(ivec.begin()+2, ivec.end()-1);
		/*
			ivec2初始化为两个迭代器指定范围中的元素的拷贝,元素类型必须与ivec2中指定类型具有相容性.
			初始化为:para1开始到para2前一个元素.此处为{3, 4, 5, 6};
				ivec.end()-1为7,该参数的前一个为6.
			PS:这种初始化方法适用于获取一个序列的子序列.
		*/
	5.vector<int> ivec(7);
		/*
			ivec为含有7个元素vector,每个元素进行缺省值的初始化(int初始化为0,string初始化为空).
			此处为初始化含有7个0的vector.
			PS:这种初始化适用于程序运行期间数量可预知,而元素值需动态获取.
		*/
	6.vector<int> ivec(7, 3);
		/*
			ivec被初始化为还有7个3的vector.
		*/

### 9.9 练习9

用list<int>/vector<int>初始化一个vector<double>.

	由于容器或者元素类型不一样,不能使用拷贝初始化.可以使用范围初始化:
	--->对于不同或相同的迭代器,只要元素类型具有相容性,就可以使用返回初始化.

	#include <iostream>
	#include <vector>
	#include <list>
	using namespace std;
	
	int main()
	{
		list<int> ilist = {1, 2, 3, 4, 5, 6, 7};
		vector<int> ivec = {7, 6, 5, 4, 3, 2, 1};
		
		vector<double> dvec(ilist.begin(), ilist.end());
		vector<double> dvec1(ivec.begin(), ivec.end());
	
		cout << dvec.capacity() << " " << dvec.size() << " "
			<< dvec[0] << " " << dvec[dvec.size() - 1] << endl;
		cout << dvec1.capacity() << " " << dvec1.size() << " "
			<< dvec1[0] << " " << dvec1[dvec1.size() - 1] << endl;
	}
	//结果为:
		7 7 1 7
		7 7 7 1

### 9.10 练习10

将一个list中的char *指针(指向C风格字符串)元素赋值给一个vector中的string.

	由于list<char *>与vector<string>是不同类型的容器,但是char *可以转换为string,因此可以采用范围
	初始化方式进行赋值.

	#include <iostream>
	#include <vector>
	#include <list>
	using namespace std;
	
	int main()
	{
		//list<char *>slist = {"hello", "world", "!"};
			//C风格字符串在vs2017会报错,暂不知道什么原因.
		list<string> slist = { "hello", "world", "!" };
		vector<string> svec;
	
		svec.assign(slist.begin(),slist.end());
		/*
			定义之后进行赋值使用的方法为:
			svec.assgin();	//容器的assign方法.
		*/
		cout << svec.capacity() << " " << svec.size() << endl;
		//cout << " " << svec[0] << " " << svec[svec.size() - 1] << endl;	//会报错.
	}

### 9.11 练习11

判定两个vector<int>是否相等.

	#include <iostream>
	#include <vector>
	using namespace std;
	
	int main()
	{
		vector<int> ivec = {1, 2, 3, 4, 5, 6, 7};
		vector<int> ivec1 = { 1, 2, 3, 4, 5, 6, 7};
		vector<int> ivec2 = { 1, 2, 3, 4, 5};
		vector<int> ivec3 = { 1, 2, 3, 4, 5, 6, 8};
		vector<int> ivec4 = { 1, 2, 3, 4, 5, 7, 6};
		cout << (ivec == ivec1) << endl;	//输出1
		/*
			相同的容器且元素类型相同可以直接进行比较.
			元素个数及对位的元素相等,则两个vector.否则就不相等.
		*/
		cout << (ivec == ivec2) << endl;	//输出0
		cout << (ivec == ivec3) << endl;	//输出0
		cout << (ivec == ivec4) << endl;	//输出0
		ivec1.push_back(8);
		ivec1.pop_back();	//pop_back:从尾部删除一个元素.
		cout << ivec.capacity() << " " << ivec1.size() << endl;
		cout << (ivec == ivec1) << endl;	//push_back然后再pop_back不影响判断.--->输出1
		return 0;
	}

### 9.12 练习12

比较list<int>和vector<int>中的元素.

	两个容器相等的条件是包含相同个数的元素,且对位元素的值都相等.

	#include <iostream>
	#include <vector>
	#include <list>
	using namespace std;
	
	bool l_v_equal(vector<int> &ivec, list<int> &ilist)
	{
		if (ilist.size() != ivec.size())
			return false;
	
		auto lb = ilist.begin();
		auto le = ilist.end();
		auto vb = ivec.begin();
		for (; lb != le; lb++, vb++) {
			if (*lb != *vb)
				return false;
		}
		return true;
	}
	
	int main()
	{
		vector<int> ivec = { 1, 2, 3, 4, 5, 6, 7};
		list<int> ilist = { 1, 2, 3, 4, 5, 6, 7};
		list<int> ilist1 = { 1, 2, 3, 4, 5};
		list<int> ilist2 = { 1, 2, 3, 4, 5, 6, 8};
		list<int> ilist3 = { 1, 2, 3, 4, 5, 7, 6};
	
		cout << l_v_equal(ivec, ilist) << endl;
		cout << l_v_equal(ivec, ilist1) << endl;
		cout << l_v_equal(ivec, ilist2) << endl;
		cout << l_v_equal(ivec, ilist3) << endl;
	}
	//结果为:
	1
	0
	0
	0

更优的方法:

	//先拷贝,再使用"=="比较两个vector.
	bool l_v_equal(vector<int> &ivec, list<int> &ilist)
	{
		vector<int> ivec_copy(ilist.begin(), ilist.end());
		return (ivec_copy == ivec);
	}	

### 9.13 练习13

两个容器使用关系运算符(<, >等)的限制:

	if (container1 < container)使用的限制:
	1.容器类型必须相同,元素类型也必须相同;
	2.元素类型必须支持"<"/">"等运算符.

### 9.14 练习14

向deque添加元素.

	#include <iostream>
	#include <string>
	#include <deque>
	using namespace std;

	int main()
	{
		deque<string> sdeq;
		string word;
		while (cin >> word)
			sdeq.push_back(word);	//deque的push_front是往首位置添加新元素.会导致顺序相反.

		//遍历
		for (auto siter = sdeq.begin(); siter != sdeq.end(); siter++)
			cout <<*siter << endl;
	}

### 9.15 练习15

向list添加元素--->方法与deque相似.

	#include <iostream>
	#include <list>
	using namespace std;

	int main()
	{
		list<string> slist;
		string word;
		while (cin >> word)
			slist.push_back(word);	//deque的push_front是往首位置添加新元素.会导致顺序相反.

		//遍历
		for (auto siter = slist.begin(); siter != slist.end(); siter++)
			cout <<*siter << endl;
	}

### 9.16 练习16

将一个list<int>中奇数元素拷贝到一个deque,偶数元素拷贝到另一个deque.

	#include <iostream>
	#include <deque>
	#include <list>
	using namespace std;
	
	int main()
	{
		list<int> ilist = { 1, 2, 3, 4, 5, 6, 7, 8};
		deque<int> odd_deq, even_deq;
	
		for (auto int_iter = ilist.cbegin(); int_iter != ilist.cend(); int_iter++) {
			if (*int_iter & 1)	//奇偶性判断,此处与"*int_iter % 2"等价.
				odd_deq.push_back(*int_iter);
			else
				even_deq.push_back(*int_iter);
		}
	
		cout << "Odd value: ";
		for (auto int_iter = odd_deq.cbegin(); int_iter != odd_deq.cend(); int_iter++)
			cout << *int_iter << " ";
		cout << endl;
	
		cout << "Even value: ";
		for (auto int_iter = even_deq.cbegin(); int_iter != even_deq.cend(); int_iter++)
			cout << *int_iter << " ";
		cout << endl;
	}
	//结果为:
	Odd value: 1 3 5 7
	Even value: 2 4 6 8

### 9.17 练习17

insert成员函数的使用.

	#include <iostream>
	#include <vector>
	#include <string>
	using namespace std;
	
	int main()
	{
		vector<string> svec;
		string word;
		auto str_iter = svec.begin();
		while (cin >> word)
			str_iter = svec.insert(str_iter, word);
			/*
				vector,list等的insert方法:
					para1:插入的位置,为一个迭代器的值;
					para2:插入的元素;
					retval:将元素插入到para1迭代器指定的元素之前,并返回指向新插入的元素的迭代器.
				此处每次插入之后str_iter都指向首元素,即往首位置插入.
			*/
	
		for (auto str_iter = svec.cbegin(); str_iter != svec.cend(); str_iter++)
			cout << *str_iter << endl;
	}

**PS:vector/deque的insert方法少用,因为会移动元素,性能很差.使用list的insert方法不存在这个问题.**

### 9.18 练习18

### 9.19 练习19

### 9.20 练习20

### 9.21 练习21

### 9.22 练习22

### 9.23 练习23

### 9.24 练习24