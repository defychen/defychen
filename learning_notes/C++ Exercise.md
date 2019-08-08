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

遍历到vector的中间位置,将满足条件的值插入到vector中.

	#include <iostream>
	#include <vector>
	using namespace std;
	
	int main()
	{
		vector<int> iv = {1, 1, 1, 1, 1};
		int some_val = 1;
	
		vector<int>::iterator iter = iv.begin();
		int org_size = iv.size(), i = 0;
	
		while (i <= org_size / 2) {
			if (*iter == some_val) {
				iter = iv.insert(iter, 2 * some_val);
				/*
					插入到当前iter之前的一个位置.返回前一个位置的迭代器,并赋值给iter;
				*/
				iter++;		//向后移动一次迭代器,移动到插入之前的位置.
				iter++;		//再向后移动一次迭代器,移动到插入之前的后一个位置.
			} else {
				iter++;	//没有值满足条件,直接向后移动迭代器即可.
			}
			i++;
		}
	
		for (iter = iv.begin(); iter != iv.end(); iter++)
			cout << *iter << " ";
		cout << endl;
	}

**向一个vector,string,deque插入一个元素会导致当前指向容器的迭代器、指针和引用失效.要注意进行迭代器的更新.**

### 9.19 练习19

获取vector首元素的方法:

	1.iv.at(0):使用at访问容器的第一个元素.如果vector为空,则会抛出out_of_range异常;
		正确的做法是:先检查容器是否为空,再使用at访问容器的首元素;
	2.iv.[0]:下标运算符.如果vector为空,会导致程序直接退出.
		正确的做法是:先检查下标的合法性,再使用下标运算符;
	3.iv.front():获取首元素.如果vector为空,会导致程序直接退出;
		正确的做法是:先检查容器是否为空,再获取首元素;
	4.*iv.begin();获取首元素.如果vector为空,会导致程序直接退出.
		正确的做法是:先检查容器是否为空,再获取首元素;

### 9.20 练习20

删除vector和list中的元素.

	1.从vector中删除元素时,会导致删除点之后位置的迭代器、引用和指针失效;
	2.erase返回的迭代器指向删除元素之后的位置,将erase返回的迭代器赋值给iter,使其正确向前推进;
	3.虽然list的删除操作不会令迭代器失效,但是还是建议将其看成失效,方便统一.

代码如下:

	#include <iostream>
	#include <vector>
	#include <list>
	using namespace std;
	
	int main()
	{
		int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
		vector<int> iv;
		list<int> il;
	
		iv.assign(ia, ia + 11);
		il.assign(ia, ia + 11);
		
		for (vector<int>::iterator i_iter = iv.begin(); i_iter != iv.end();) {
			if (!(*i_iter & 1))
				i_iter = iv.erase(i_iter);	//删除掉偶数,返回的迭代器赋值给i_iter,使其正确向前推进.
			else
				i_iter++;
		}
	
		for (list<int>::iterator i_iter = il.begin(); i_iter != il.end();) {
			if (*i_iter & 1)
				i_iter = il.erase(i_iter);	//删除掉奇数,返回的迭代器赋值给i_iter,使其正确向前推进.
			else
				i_iter++;
		}
	
		for (vector<int>::iterator i_iter = iv.begin(); i_iter != iv.end(); i_iter++)
			cout << *i_iter << " ";
		cout << endl;
	
		for (list<int>::iterator i_iter = il.begin(); i_iter != il.end(); i_iter++)
			cout << *i_iter << " ";
		cout << endl;
	}

### 9.21 练习21

forward_list<int>的使用:

	1.forward_list是单向链表数据结构,只有前驱节点指向后继节点的指针,没有反向的指针;
	2.forward_list可以高效的从前驱转到后继,但无法从后继转到前驱;
	3.forward_list插入、删除操作都是after形式(即插入、删除给定迭代器的后继):
		1)提供了before_begin获取首元素之前位置的迭代器;
		2)提供了insert_after向某迭代器之后插入元素;
		3)提供了erase_after删除某迭代器之后的元素.

实例代码:

	#include <iostream>
	#include <forward_list>
	using namespace std;
	
	int main()
	{
		forward_list<int> iflst = {1, 2, 3, 4, 5, 6, 7, 8};
	
		auto prev = iflst.before_begin();
		auto curr = iflst.begin();
	
		while (curr != iflst.end()) {
			if (*curr & 1)
				curr = iflst.erase_after(prev);
				/*
					curr = iflst.erase_after(prev);
					1.将prev之后的元素从forward_list中移除;
					2.返回后一个元素的迭代器,赋值给curr(变成当前迭代器).
				*/
			else {
				prev = curr;	//不满足条件,prev向后移动,curr也向后移动.
				curr++;
			}
		}
	
		for (auto i_iter = iflst.begin(); i_iter != iflst.end(); i_iter++)
			cout << *i_iter << " ";
		cout << endl;
	}

### 9.22 练习22

forward<list>的插入操作:

	#include <iostream>
	#include <forward_list>
	#include <string>
	using namespace std;
	
	void test_and_insert(forward_list<string> &sflst, const string &s1, const string &s2)
	{
		auto prev = sflst.before_begin();
		auto curr = sflst.begin();
		bool inserted = false;
	
		while (curr != sflst.end()) {
			if (*curr == s1) {
				curr = sflst.insert_after(curr, s2);	//在当前位置之后插入s2
				inserted = true;
			}
			prev = curr;
			curr++;
		}
		if (!inserted)
			sflst.insert_after(prev, s2);	//遍历到最后,没有找到插入的位置.则插入到最后.
	}
	
	int main()
	{
		forward_list<string> sflst = {"Hello", "!", "world", "!"};
	
		test_and_insert(sflst, "Hello", "hi");
		for (auto s_iter = sflst.begin(); s_iter != sflst.end(); s_iter++)
			cout << *s_iter << " ";
		cout << endl;
		test_and_insert(sflst, "!", "?");
		for (auto s_iter = sflst.begin(); s_iter != sflst.end(); s_iter++)
			cout << *s_iter << " ";
		cout << endl;
		test_and_insert(sflst, "Bye", "defy");
		for (auto s_iter = sflst.begin(); s_iter != sflst.end(); s_iter++)
			cout << *s_iter << " ";
		cout << endl;
	}
	//结果为:
	Hello hi ! world !
	Hello hi ! ? world ! ?
	Hello hi ! ? world ! ? defy

### 9.23 练习23

vec.resize()操作:

	如果vec有25个元素:
		vec.resize(100):则会在vec末尾添加75个元素,这些元素将进行初始化;
		接着调用vec.resize(10):则会将vec末尾的90个元素删除.

### 9.24 练习24

list和forward_list的注意点:

	list和forward_list与其他容器的一个重要的不同点是:它们的迭代器不支持加减运算.
	因为链表中的元素在内存中不是连续存储的,因此无法直接通过地址的加减在元素间移动.

### 9.25 练习25

vector的capacity和size区别:

	1.capacity()返回已经为vector分配了多大的内存空间(单位为元素大小),即vector可以保存的元素个数;
	2.size()返回vector已经保存了多个元素;
	3.capacity()返回值一定大于或等于size()返回值.

### 9.26 练习26

list或array没有capacity()函数的原因:

	1.list是链表,有新元素时会动态分配一个新节点存放,删除元素时会立刻释放节点空间,因此不需要capacity功能;
	2.array是固定大小数组,内存一次性分配,大小不变,因此也不需要capacity功能.

### 9.27 练习27

从一个vector<char>初始化一个string.

	#include <iostream>
	#include <vector>
	#include <string>
	using namespace std;
	
	int main()
	{
		vector<char> vc = {'H', 'e', 'l', 'l', 'o'};
		string s(vc.data(), vc.size());
		/*
			vc.data():vector的data()函数,返回vector在内存空间的首地址;
			string的构造函数其中的一种形式:s(vc.data(), vc.size()):
				para1:字符数组(此处为vector)的首地址;
				para2:字符数组(此处为vector)的大小.
		*/
		cout << s << endl;
	}

### 9.28 练习28

往string中添加字符.

	#include <iostream>
	#include <string>
	using namespace std;
	
	void input_string(string &s)
	{
		s.reserve(100);	//预先为string保留100字符的空间.string和vector一样,具有reserve成员函数.
		char c;
		while (cin >> c)
			s.push_back(c);	//string和容器一样,具有push_back()向尾部添加字符.
	}
	
	int main()
	{
		string s;
		input_string(s);
		cout << s << endl;
	}

### 9.29 练习29

字符串中参数替换.

	#include <iostream>
	#include <string>
	using namespace std;
	
	void replace_string(string &s, const string &oldStr, const string &newStr)
	{
		int l = s.size();
		if (!l)
			return;
	
		auto str_iter = s.begin();
		while (str_iter != s.end()) {
			auto str_iter1 = str_iter;
			auto str_iter2 = oldStr.begin();
			while (str_iter2 != oldStr.end() && (*str_iter1 == *str_iter2)) {
				//检查每一个字符是否都相等
				str_iter1++;
				str_iter2++;
			}
	
			if (str_iter2 == oldStr.end()) {	//到达字符串结尾,表示查找到对应字符.
				str_iter = s.erase(str_iter, str_iter1);	//删除从起始到结束点的字符串
				if (newStr.size()) {
					str_iter2 = newStr.end();
					do {
						str_iter2--;	//取待插入字符串尾部一一插入
						str_iter = s.insert(str_iter, *str_iter2);
						//必须一个字符一个字符的插入才能保证顺序
					} while (str_iter2 > newStr.begin());
				}
				str_iter += newStr.size();
			} else {
				str_iter++;
			}
		}
	}
	
	int main()
	{
		string s = "tho thru tho!";
		replace_string(s, "thru", "through");
		cout << s << endl;
		replace_string(s, "tho", "though");
		cout << s << endl;
	}
	//结果为:
	tho through tho!
	though through though!

### 9.30 练习30

使用string的find()和replace()来实现29题练习.

	#include <iostream>
	#include <string>
	using namespace std;
	
	void replace_string(string &s, const string &oldStr, const string &newStr)
	{
		int pos = 0;
		while ((pos = s.find(oldStr, pos)) != string::npos) {
			/*
				string的find函数:
					para1:待查找的字符串(字符串整体查找);
					para2:查找的起始点,默认为从0开始.
				retval:返回匹配的字符串的起始点.
				string::npos:表示查找到末尾没有查找到的值.
			*/
			s.replace(pos, oldStr.size(), newStr);
			/*
				string的replace函数:
					para1:替换的起始点;
					para2:替换字符串的大小;
					para3:替换的新字符串.
				PS:即将从起始点para1开始的para2大小替换为para3.
			*/
			pos += newStr.size();	//pos往后移动newStr.size()个单位
		}
	}
	
	int main()
	{
		string s = "tho thru tho!";
		replace_string(s, "thru", "through");
		cout << s << endl;
		replace_string(s, "tho", "though");
		cout << s << endl;
	}

### 9.31 练习31

string的insert和append函数的使用.

	#include <iostream>
	#include <string>
	using namespace std;
	
	void name_string(string &name, const string &prefix, const string &suffix)
	{
		name.insert(name.begin(), 1, ' ');	
		/*
			begin()位置插入一个' '.也可以使用:
			name.insert(0, " ");	//表示在0的位置之前插入一个空格
		*/
		name.insert(name.begin(), prefix.begin(), prefix.end());
		/*
			begin()位置插入prefix.begin()到prefix.end()之间的字符串.也可以使用:
			name.insert(0, prefix);	//表示在0的位置之前插入一个prefix字符串
		*/
		name.append(" ");	
		/*
			append()在末尾插入一个" ".也可以使用:
			name.insert(name.size(), " "); //表示在name.size()即末尾位置插入一个空格
		*/
		name.append(suffix.begin(), suffix.end());
		/*
			append()在末尾插入suffix.begin()到suffix.end()之间的字符串.也可以使用:
			name.insert(name.size(), suffix); //表示在name.size()即末尾位置插入suffix字符串
		*/
	}
	
	int main()
	{
		string s = "James Bond";
		name_string(s, "Mr.", "II");
		cout << s << endl;
		s = "M";
		name_string(s, "Mrs.", "III");
		cout << s << endl;
	}

### 9.32 练习32

练习在string "ab2c3d7R4E6"中查找出数字和字母.

	#include <iostream>
	#include <string>
	using namespace std;
	
	void find_char(string &s, const string &chars)
	{
		cout << "Find " << chars << " sin " << s << endl;
		string::size_type pos = 0;	//查找的位置
		while ((pos = s.find_first_of(chars, pos)) != string::npos) {
			/*
				string的find_first_of:
					para1:查找的给定字符集合,即在s中查找para1给定的字符集合中的字符;
					para2:查找的起始位置;
					retval:查找到字符的位置.
			*/
			cout << "pos: " << pos << ", char: " << s[pos] << endl;
			pos++;
		}
	}
	
	int main()
	{
		string s = "ab2c3d7R4E6";
		cout << "Find all number in " << s << endl;
		find_char(s, "0123456789");
		cout << endl << "Find all characters in" << s << endl;
		find_char(s, "abcdefghijklmnopqrstuvwxyz" \
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	}

**s.find_first_of和s.find_first_not_of**

	1.s.find_first_of(chars, pos):在s中查找位于集合chars中首次出现的字符;
	2.s.find_first_not_of(chars, pos):在s中查找不在集合chars中首次出现的字符;
	PS:find_first_of和find_first_not_of属于补集的查找关系.

### 9.33 练习33

字符串到数值的类型转换.

	1.字符串转整型(stoi):
	#include <iostream>
	#include <string>
	#include <vector>
	using namespace std;
	
	int main()
	{
		vector<string> vs = {"123", "+456", "-789"};
		int sum = 0;
	
		for (auto str_iter = vs.begin(); str_iter != vs.end(); str_iter++)
			sum += stoi(*str_iter);
		cout << "Sum: " << sum << endl;
	}
	//结果为:
		Sum: -210
	2.字符串转浮点数(stof):
	#include <iostream>
	#include <string>
	#include <vector>
	using namespace std;
	
	int main()
	{
		vector<string> vs = {"12.3", "-4.56", "+7.8e-2"};
		float sum = 0;
	
		for (auto str_iter = vs.begin(); str_iter != vs.end(); str_iter++)
			sum += stof(*str_iter);
		cout << "Sum: " << sum << endl;
	}
	//结果为:
		Sum: 7.818

### 9.34 练习34

年、月、日的解析.

date.h头文件:

	#ifndef __DATE_H__
	#define __DATE_H__
	
	#include <iostream>
	#include <string>
	#include <stdexcept>
	using namespace std;
	
	const string month_name[] = {"January", "February", "March", "April",
		"May", "June", "July", "August", "September", "October", "November", "December"};
	const string month_abbr[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug",
		"Sep", "Oct", "Nov", "Dec"};
	const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	class date {
	public:
		friend ostream& operator<<(ostream &, const date&);
		date() = default;
		date(string &ds);
		unsigned y() const 
		{
			return year;
		}
		unsigned m() const
		{
			return month;
		}
		unsigned d() const
		{
			return day;
		}
	private:
		unsigned year, month, day;
	};
	
	inline int get_month(string &ds, int &end_of_month)
	{
		int i, j;
		for (i = 0; i < 12; i++) {
			for (j = 0; j < month_abbr[i].size(); j++)
				if (ds[j] != month_abbr[i][j])
					break;
	
			if (j == month_abbr[i].size())
				break;
		
		}
	
		if (i == 12)
			throw invalid_argument("Invalid month");
	
		if (ds[j] == ' ') {
			end_of_month = j + 1;
			return i + 1;
		}
	
		for (; j < month_name[i].size(); j++)
			if (ds[j] != month_name[i][j])
				break;
	
		if (j == month_name[i].size() && ds[j] == ' ') {
			end_of_month = j + 1;
			return i + 1;
		}
		throw invalid_argument("Invalid month");
	}
	
	inline int get_day(string &ds, int month, int &p)
	{
		size_t q;
		int day = stoi(ds.substr(p), &q);
		/*
			stoi(ds.substr(p), &q):
				para1:字符串数字.
				para2:保存字符串数字后的非数字的索引,相对p开始的位置(即为一个相对位置);
				retval:返回转换后的数字.
			ds.substr():表示从p位置开始取字符串.
		*/
		if (day < 1 || day > days[month])
			throw invalid_argument("Invalid date");
		p += q;
		return day;
	}
	
	inline int get_year(string &ds, int &p)
	{
		size_t q;
		int year = stoi(ds.substr(p), &q);
		if (p + q < ds.size())
			throw invalid_argument("Invalid ending");
		return year;
	}
	
	date::date(string &ds)
	{
		int p;
		size_t q;
		if ((p = ds.find_first_of("0123456789")) == string::npos)
			throw invalid_argument("No number, invalid date");
	
		if (p > 0) {
			month = get_month(ds, p);
			day = get_day(ds, month, p);
			if (ds[p] != ' ' && ds[p] != ',') {
				throw invalid_argument("Invalid blank");
			}
			p++;
			year = get_year(ds, p);
		}
		else {
			month = stoi(ds, &q);
			p = q;
			if (month < 1 || month > 12)
				throw invalid_argument("Invalid month");
			if (ds[p++] != '/')
				throw invalid_argument("Invalid blank");
			day = get_day(ds, month, p);
			if (ds[p++] != '/')
				throw invalid_argument("Invalid blank");
			year = get_year(ds, p);
		}
	}
	
	ostream &operator<<(ostream &out, const date &d)
	{
		out << d.y() << " year," << d.m() << " month," << d.d() << " day" << endl;
		return out;
	}
	
	#endif

测试程序:

	#include <iostream>
	#include <string>
	#include "date.h"
	using namespace std;
	
	int main()
	{
		string dates[] = {"Jan 1,2014", "February 1 2014", "3/1/2014",
					//"3 1 2014",
					};
	
		try {
			for (auto ds : dates) {
				date d1(ds);
				cout << d1;
			}
		} catch (invalid_argument e) {
			cout << e.what() << endl;
		}
	}

***

## Chapter 15. 面向对象程序设计

### 15.1 练习1

虚成员:

	1.在类中声明为virtual的成员,基类希望这种成员在派生类中被重定义;
	2.类中除了构造函数外,其他任意非static成员都可以成为虚成员.

### 15.2 练习2

protected与private访问说明符的区别:

	1.protected是受保护的访问标号,protected成员可以被该类的成员、友元(函数)和派生类成员(非友元)访问,但
		不可以被该类的普通用户访问(e.g.该类声明的对象则不可以访问protected成员);
	2.private表示私有成员,只能被基类的成员和友元访问,派生类不能访问.

### 15.3 练习3

静态类型和动态类型的定义:

	1.静态类型是声明变量时的类型或表达式生成的类型,在编译时已经确定;
	2.动态类型是变量或表达式表示的内存中的对象的类型,直到运行时才能知道.
		e.g. Quote *pQuote = new Bulk_quote;
		1.指针pQuote的静态类型是Quoter,编译时已经确定;
		2.指针pQuoter的动态类型是Bulk_quote,直到运行时才能知道该指针指向的是基类还是派生类.
	PS:如果一个变量是指针或者引用,则其静态类型和动态类型可能不一致;否则一个变量非指针也非引用,则其静态类型
		和动态类型永远一致.e.g.
			Bulk_quote bulk;
			Quote *pQuote = &bulk;	//pQuote为指针,静态类型与动态不一致;
			Quote &rQuote = bulk;	//rQuote为引用,静态类型与动态不一致.

### 15.4 练习4

虚函数练习:

1.class Quote

	class Quote
	{
	public:
		Quote() = default;
		Quote(const string &book, double sales_price) :
			bookNo(book), price(sales_price) {}
		string isbn() const
		{
			return bookNo;
		}
		virtual double net_price(size_t n) const	//虚函数
		{
			return n * price;
		}
		virtual void debug()
		{
			cout << "bookNo = " << bookNo << " price = " << price << endl;
		}
		virtual ~Quote() = default;
	private:
		string bookNo;
	protected:
		double price = 0.0;
	};

2.class Bulk_quote

	class Bulk_quote : public Quote
	{
	public:
		Bulk_quote(const string &book = "", double sales_price = 0, size_t qty = 0, double 
		disc_rate = 0) :
			Quote(book, sales_price), min_qty(qty), discount(disc_rate) {}
		
		double net_price(size_t cnt) const
		{
			if (cnt > min_qty)
				return cnt * (1 - discount) * price;
			else
				return cnt * price;
		}
		virtual void debug()
		{
			Quote::debug();	//引用基类的成员函数方法
			cout << "min_qty = " << min_qty << " discount = " << discount << endl;
		}
	private:
		size_t min_qty;
		double discount;
	};

### 15.5 练习5

override和final使用场景:

1.override

	1.在基类中声明virtual成员函数形式:
		virtual void draw() const;
	2.基类中声明了virtual成员函数,派生类为了程序清晰可读.最好在派生类中也将该成员函数声明为virtual,且使用
	override关键词进行检查:
		virtual void draw() const override;
		/*
		1.派生类中也使用virtual关键词;
		2.派生类中后面使用override关键词,用于检查基类中是否存在一个相同函数签名的成员函数,不存在就报错.
			达到检查的目的;
		*/
	3.对于基类中virtual成员函数,派生类也可以不添加virtual,默认继承而来的也是virtual类型,只是不易读.

2.final

	如果将某个成员函数定义成final,则不允许后续的派生类来覆盖这个函数,否则会报错.

### 15.6 练习6

继承的运用:

	#include <iostream>
	using namespace std;
	
	class Base
	{
	public:
		void pub_mem();
	protected:
		int prot_mem;
	private:
		char priv_mem;
	};
	
	struct Pub_Derv : public Base
	{
		int f()
		{
			return prot_mem;
		}
		void memfcn(Base &b)
		{
			b = *this;
			cout << "Pub_Derv" << endl;
		}
	};
	
	struct Priv_Derv : private Base
	{
		int f1() const
		{
			return prot_mem;
			//private继承只能访问基类中public/protected成员函数/变量,基类中的private不能被访问.
		}
		void memfcn(Base &b)
		{
			b = *this;
			/*
				直接继承(无论以public/protected/private),派生类的成员函数和友元都可以使用派生类对象向
				基类的转换.
			*/
			cout << "Priv_Derv" << endl;
		}
	};
	
	struct Prot_Derv : protected Base
	{
		int f2()
		{
			return prot_mem;
		}
		void memfcn(Base &b)
		{
			b = *this;
			cout << "Prot_Derv" << endl;
		}
	};
	
	struct Derived_from_Public : public Pub_Derv
	{
		int use_base()
		{
			return prot_mem;
		}
		void memfcn(Base &b)
		{
			b = *this;
			cout << "Derived_from_Public" << endl;
		}
	};
	
	#if 0
	struct Derived_from_Private : private Priv_Derv
	{
		int use_base()
		{
			return prot_mem;
			//private继承派生出任何类,不能访问基类中的任何成员.
		}
		void memfcn(Base &b)
		{
			b = *this;
			//private继承派生出任何类,不能使用派生类对象向基类的转换.
			cout << "Derived_from_Private" << endl;
		}
	};
	#endif
	
	struct Derived_from_Protected : protected Prot_Derv
	{
		int use_base()
		{
			return prot_mem;
		}
		void memfcn(Base &b)
		{
			b = *this;
			//protected继承派生出protected类,其中的成员函数或友元也是可以使用派生类对象向基类的转换.
			cout << "Derived_from_Protected" << endl;
		}
	};
	
	int main()
	{
		Pub_Derv d1;
		Priv_Derv d2;
		Prot_Derv d3;
		Derived_from_Public dd1;
		//Derived_from_Private dd2;
		Derived_from_Protected dd3;
		Base base;
		Base *p = new Base;
		p = &d1;
		//p = &d2;
		//p = &d3;
		p = &dd1;
		//p = &dd2;
		//p = &dd3;
		d1.memfcn(base);
		//d2.memfcn(base);
		d3.memfcn(base);
		dd1.memfcn(base);
		//dd2.memfcn(base);
		dd3.memfcn(base);
		return 0;
	}
	结果为:
	Pub_Derv
	Priv_Derv
	Prot_Derv
	Derived_from_Public
	Derived_from_Protected

### 15.7 练习7

虚析构函数:

	虚析构函数:基类使用的类应具有虚虚构函数,以保证在删除指向派生类对象的基类指针时,根据指针实际指向的
	对象所属的类型运行适当的析构函数.

### 15.8 练习8

C++11智能指针unique_ptr, shared_ptr的使用.

	1.C++11中有unique_ptr, shared_ptr与weak_ptr等智能指针(smart pointer),定义在<memory>中;
	2.智能指针可以对动态资源进行管理,保证任何情况下,已构造的对象能够被销毁.避免内存泄漏;
	3.指针指针位于<memory>头文件中.

**1.unique_ptr**

unique_ptr对对象持有独有权,即同一时刻只能有一个unique_ptr指向给定对象.

	#include <iostream>
	#include <memory>
	
	void test()
	{
		std::unique_ptr<int> up1(new int(11));	//不能复制的unique_ptr.指向11的内容
		//std::unique_ptr<int> up2 = up1;		//错误,unique_ptr只能有一个指向给定对象
		std::cout << *up1 << std::endl;			// 11
	
		std::unique_ptr<int> up3 = std::move(up1);	//up1移除,p3是数据11的唯一的unique_ptr
	
		std::cout << *up3 << std::endl;			// 11
		//std::cout << *up1 << std::endl;		//错误
		up3.reset();		//显示释放内存
		up1.reset();		//不能导致运行时错误
		//std::cout << *up3 << std::endl;	//up3已经释放,错误
	
		std::unique_ptr<int> up4(new int(22));	//不能复制的unique_ptr.指向22的内容
		up4.reset(new int(44));		//重新指向44,绑定动态对象
		std::cout << *up4 << std::endl;		// 44
	
		up4 = nullptr;		//显示销毁所指对象,up4变为空指针.与up4.reset()等价
	
		std::unique_ptr<int> up5(new int(55));
		int *p = up5.release();		//释放控制权,不会释放内存
		std::cout << *p << std::endl;	// 55
		//std::cout << *up5 << std::endl;	//控制权已经释放,错误.
		delete p;
	}
	
	int main()
	{
		test();
		system("pause");
	}
	//结果为:
	11
	11
	44
	55

**2.shared_ptr**

shared_ptr是允许多个shared_ptr指针指向同一个对象(底层通过引用计数实现).

	#include <iostream>
	#include <memory>
	
	void test()
	{
		std::shared_ptr<int> sp1(new int(22));
		std::shared_ptr<int> sp2 = sp1;		//两个shared_ptr指向同一个对象
		std::cout << "count: " << sp2.use_count() << std::endl;
		// shared_ptr指针的.use_count():打印引用计数.此处为2.
	
		std::cout << *sp1 << std::endl;
		std::cout << *sp2 << std::endl;
	
		sp1.reset();	//显示让引用计数减一
		std::cout << "count: " << sp2.use_count() << std::endl;		// 1
		std::cout << *sp2 << std::endl;		// 22
	}
	
	int main()
	{
		test();
		system("pause");
	}
	//结果为:
	count: 2
	22
	22
	count: 1
	22

**3.weak_ptr**

略.

***

## Chapter 16. 模板与泛型编程