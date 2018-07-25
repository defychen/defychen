# Protobuf Learning

## Chapter 1 Protobuf Introduction

Protobuf(Google Protocol Buffer):是一种轻便高效的结构化数据存储格式,平台无关、语言无关、可扩展,很适合做数据存储或RPC数据交换格式.

	Protobuf目前提供了C++、Java、Python三种语言的API.

Protobuf优点:

1.平台无关,语言无关,可扩展;

2.提供友好的动态库,使用简单;

3.解析速度快,比对应的XML快约20-100倍;

4.序列化数据非常简洁、紧凑,其序列化之后的数据量约为XML的1/3到1/10.

***

## Chapter 2 How to use Protobuf

### Step 1 写一个proto文件(addressbook.proto),定义程序中需要处理的结构化数据

	//Filename: addressbook.proto	//注释,语法类似C++
	
	syntax="proto2";	//表明使用protobuf编译器版本v2,目前最新的为v3
	package addressbook;	//声明一个包名,因为一个proto文件是一个package.
							//主要用来防止不同的消息类型命名冲突,类似于namespace.
	
	message Person {
		/*message:定义protobuf中的结构化数据(关键字),类似于C++的类,但是"}"结束没有";".
			在其中定义需要处理的数据."Person":首字母大写.使用protoc编译后,message会成为不同的类.
		*/
		required string name = 1;
		/*
			声明一个名为name,数据类型为string的required字段.字段标识号为1.
			"required":该字段表示该值必须要设置.
			string:一种标量类型;
			name:字段名;
			1:字段标识号,在消息定义中,每个字段都有唯一的一个数字标识号.这些标识号用来在消息的二进制格式中识别
				各个字段的,一旦开始使用就不能再改变.范围1-(2^29-1).其中[19000-19999]为protobuf预留,不能使用.
		*/
		required int32 id = 2;
		optional string email = 3;
		/*
			optional:该字段表示该值可以有0个或1个值(不超过1个).
		*/

		/*protobuf文件如果要调用该enum,可以使用Person.PhoneType方式.
			C++文件使用的话,用"::".
		*/
		enum PhoneType {	//message内部声明一个enum(也是结束没有";",而且之间的用";"分隔)
			MOBILE = 0;
			HOME = 1;
			WORK = 2;
		}

		message PhoneNumber {
			required string number = 1;
			optional PhoneType type = 2 [default = HOME];
			/*[default = HOME]:为type字段指定一个默认值,当没有为type设值时,其值为HOME.*/
		}

		repeated PhoneNumber phone = 4;
		/*
			repeated:该字段表示该值可以重复任意次(包括0次),类似于C++中的list.
		*/
		
	}

	message AddressBook {
		repeated Person person_info = 1;
	}

### Step 2 proto文件的编译

protoc是proto文件的编译器,可以将proto文件编译成C++, Java, Python三种代码文件.

编译方法:

	protoc -I=$SRC_DIR --cpp/java/python_out=$DST_DIR $SRC_DIR/file.proto
	/*
		protoc:编译器
		-I=PATH或--proto_path=PATH:指定import目录.编译没有import其他proto文件的proto文件可以
			没有该参数
		--cpp/java/python=$DST_DIR:指定目标文件目录.可以是"--cpp/java/python=./"表示当前目录
		$SRC_DIR/file.proto:需要编译的源文件.当前目录可以直接"addressboot.proto"
	*/

1.编译成C++代码文件

	protoc --cpp_out=./ addressbook.proto
	//编译之后在当前目录生成: addressbook.pb.cc 和 addressbook.pb.h

2.编译成java代码文件

	protoc --java_out=./ addressbook.proto
	//编译之后在当前目录得到一个addressbook的目录,其中有Addressbook.java文件

3.编译成python代码文件

	protoc --python_out=./ addressbook.proto
	//编译之后在当前目录下生成addressbook_pb2.py文件

### Step 3 使用C++测试程序测试proto生成的C++文件

	/*main.cc文件*/
	#include <iostream>
	#include "addressbook.pb.h"	//由addressbook.proto生成的c++头文件

	int main(int argc, const char *argv[])
	{
		addressbook::AddressBook person;
			//addressbook为proto文件名.AddressBook为其中的message名
		addressbook::Person *pi = person.add_person_info();
			/*
			person.add_person_info():person_info为addressbook::AddressBook这个message的repeated字段信息.
			此处为Person增加一个节点.返回值为(addressbook::Person *)
			*/
		
		pi->set_name("defy");
			/*Person这个message含有"string name"字段.set_xxx为设值.此处必须为string类型.*/
		pi->set_id(1219);
			/*Person这个message含有"int32 id"字段.set_xxx为设值.此处必须为int32类型.*/
		std::cout << "before clear(), id = " << pi->id() << std::endl;
			/*pi->id():为得到id值.*/
		pi->clear_id();
			/*clear_xxx():使其变为默认值.int32为0*/
		std::cout << "after clear(), id = " << pi->id() << std::endl;
		pi->set_id(1087);
		if (!pi->has_email())
		{
			/*has_xxx():判断是否设置了值.*/
			pi->set_email("defy@126.com");
		}

		addressbook::Person::PhoneNumber *pn = pi->add_phone();
			/*pi->add_phone():phone为addressbook::Person这个message的repeated字段信息.
			此处为PhoneNumber增加一个节点.返回值为(addressbook::Person::PhoneNumber *)
			*/
		pn->set_number("210-8888-8888");
		pn = pi->add_phone();	//又增加一个节点
		pn->set_number("138-8888-8888");
		pn->set_type(addressbook::Person::MOBILE);
			//设置enum值,可以直接选择.没有选择的则使用默认值.

		uint32_t size = person.ByteSize();	//ByteSize():获取person这个二进制字节序的大小
		unsigned char byteArray[size];
		person.SerializeToArray[byteArray, size];
			//将person这个message序列化输出到数组

		addressbook::Addressbook help_person;
		help_person.ParseFromArray[byteArray, size];
			//从数组中序列化输入到message(help_person)
		addressbook::Person help_pi = help_person.person_info(0);
			//help_person.person_info(0):获取repeated下的0节点的信息.

		std::cout << "*********************" << std::endl;
		std::cout << "id:		" << help_pi.id() << std::endl;
		std::cout << "name:		" << help_pi.name() << std::endl;
		std::cout << "email:	" << help_pi.email() << std::endl;

		for (int i=0; i<help_pi.phone_size(); i++)
		{
			/*help_pi.phone_size():获取repeated节点的大小(xxx_size)."xxx"为repeated节点.*/
			//auto help_pn = help_pi.mutable_phone(i); //测试没有通过,auto是C++的关键字
			addressbook::Person::PhoneNumber *help_pn = help_pi.mutable_phone(i);
			/*mutable_xxx(i):获取repeated下的i节点的信息.
				help_pi.mutable_phone(i)和help_pi.phone(i)功能是一样的.
			*/
			std::cout << "phone_type:	" << help_pn->type() << std::endl;
			std::cout << "phone_number:	" << help_pn->number() << std::endl;
		}
		std::cout << "*********************" << std::endl;
		return 0;
	}

### Step 4 编译C++测试代码生成可执行代码

编译格式

	g++ main.cc xxx.pb.cc -I $INCLUDE_PATH -L $LIB_PATH -lprotobuf -pthread
	/*必须要加上"-lprotobuf -pthread"*/

编译成可执行代码

	g++ main.cc addressbook.pb.cc -I $INCLUDE_PATH -L $LIB_PATH -lprotobuf -pthread
	/*
		或者:g++ main.cc addressbook.pb.cc -lprotobuf -pthread也是可行的.
	*/

输出的结果:

	before clear(), id = 1219
	after clear(), id = 0
	************************
	id:             1087
	name:           defy
	email:  defy@126.com
	phone_type:     1
	phone_number:   021-8888-8888
	phone_type:     0
	phone_number:   138-8888-8888
	************************

***

## Chapter 3 The Common API of Protobuf(Protobuf常用的API)

1.protoc为message中的每个required字段和optional字段定义的一些API:

	TypeName xxx() const;	//获取字段的值(e.g.help_pi.id()).获取的值可以是int32, string等.
	bool has_xxx();		//判断是否设置了值(e.g.if (!pi->has_email())).
	void set_xxx(const TypeName &);	//设置值(e.g.pi->set_id(1219);).
	void clear_xxx();	//使其变为默认值(e.g.pi->clear_id();).

2.为repeated字段定义的一些API:

	TypeName *add_xxx();	//增加节点(e.g.addressbook::Person::PhoneNumber *pn = pi->add_phone();).
	TypeName xxx(int) const;	//获取指定序号的节点
					//(e.g.addressbook::Person help_pi = help_person.person_info(0);)
	TypeName *mutable_xxx(int);	//获取指定序号的节点(但是返回的值指针)
					//(e.g.addressbook::Person::PhoneNumber *help_pn = help_pi.mutable_phone(i);)
	int xxx_size();	//获取节点的数量(e.g.i<help_pi.phone_size())

3.protoc常用的序列化函数:

	bool SerializeToOstream(std::ostream *output) const;	//输出到输出流
	bool SerializeToString(string *output) const;	//输出到string
	bool SerializeToArray(void *data, int size) const;	//输出到数组(字节流)
		//e.g.person.SerializeToArray[byteArray, size];

4.protoc常用的反序列化函数:

	bool ParseFromIstream(std::istream *input);	//从输入流解析
	bool ParseFromString(const string &data);	//从string解析
	bool ParseFromArray(const void *data, int size);	//从数组(字节流)解析
		//e.g.help_person.ParseFromArray[byteArray, size];

5.其他常用的函数:

	bool IsInitialized();	//检查是否所有的required字段都被设置值
	size_t ByteSize() const;	//获取二进制字节序的大小.常用语序列化之前.
		//e.g.uint32_t size = person.ByteSize();


