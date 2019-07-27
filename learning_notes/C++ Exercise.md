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