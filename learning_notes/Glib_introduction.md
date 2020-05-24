# GLib Introduction

## 1. glib hash库GHashTable的使用实例

### 1.1 hash表介绍

hash表是一种key-value访问的数据结构,hash表存储的数据能够很快捷和方便的去查询.在很多工程项目都需要使用到hash表来存储数据.

### 1.2 glib GHashTable API

**1.g_hash_table_new**

	GHashTable *g_hash_table_new(GHashFunc hash_func, GEqualFunc key_equal_func);
	/*
		funcion:创建hash表;
		param1:创建hash值的函数,为key创建一个hash值.可以使用glib库自带的g_str_hash函数,也可以
			使用自己创建的函数来建立规则;
		param2:用来比较key的函数,用于在哈希表中查找key-value.可以使用glib库自带的g_int_equal;
		return:hash表的句柄.
	*/

**2.g_hash_table_new_full**

	GHashTable *g_hash_table_new_full(GHashFunc hash_func, GEqualFunc key_equal_func,
		GDestroyNotify key_destroy_func, GDestroyNotify value_destroy_func);
	/*
		function:创建hash表,g_hash_table_new进阶版,增加了内存管理--->常用.
		param1:创建hash值的函数,为key创建一个hash值.可以使用glib库自带的g_str_hash函数,也可以
			使用自己创建的函数来建立规则;
		param2:用来比较key的函数,用于在哈希表中查找key-value.可以使用glib库自带的g_int_equal;
		param3:key处理函数,用于释放key;
		param4:value处理函数,用于释放value.
		return:hash表的句柄.
	*/

**3.g_hash_table_insert**

	void g_hash_table_insert(GHashTable *hash_table, gpointer key, gpointer value);
	/*
		function:向hash表中插入key-value;
		param1:hash表的句柄;
		param2:key;
		param3:value;
		return:none.
	*/

**4.g_hash_table_foreach**

	void g_hash_table_foreach(GHashTable *hash_table, GHFunc func, gpointer user_data);
	/*
		function:hash表遍历函数,遍历hash表;
		param1:hash表的句柄;
		param2:回调函数,每遍历到一个key-value就回调该函数,对数据进行处理;
		param3:给回调函数传入的参数;
		return:none.
	*/

**5.g_hash_table_size**

	guint g_hash_table_size(GHashTable *hash_table);
	/*
		function:反汇hash表中key-value对的个数;
		param:hash表的句柄;
		return:key-value对的个数.
	*/

**6.g_hash_table_lookup**

	gpointer h_hash_table_lookup(GHashTable *hash_table, pconstpointer key);
	/*
		function:通过key去查找对应的value.该函数不会去判断这个key是否存在,在使用前要确保key
			不会NULL;
		param1:hash表的句柄;
		param2:输入的key;
		return:value.
	*/

**7.g_hash_table_remove**

	gboolean g_hash_table_remove(GHashTable *hash_table, gconstpointer key);
	/*
		function:删除指定key的key-value对.该函数不会释放key-value对应的内存.使用g_hash_table
			_new_full比较方便,会在删除的时候调用回调函数进行释放.使用g_hash_table_new需要手动去
			释放内存;
		param1:hash表的句柄;
		param2:要删除的key;
		return:true(删除成功),false(删除失败).
	*/

**8.g_hash_table_find**

	gpointer g_hash_table_find(GHashTable *hash_table, GHRFunc predicate, gpointer 
		user_data);
	/*
		function:查找特定的key-value.遍历hash表来回调predicate函数判断自己定义规则的key-value;
		param1:hash表的句柄;
		param2:回调函数,定义特定key-value的规则;
		param3:传入回调函数的参数;
		return:true(找到),false(没找到).
	*/

**9.g_hash_table_replace**

	void g_hash_table_replace(GHashTable *hash_table, gpointer key, gpointer value);
	/*
		function:向hash表中插入key-value.如果插入的key存在会替换原来的key和value.
			g_hash_table_insert只会替换值;
		param1:hash表的句柄;
		param2:插入的key;
		param3:插入的value.
	*/

**10.g_hash_table_get_keys**

	GList *g_hash_table_get_keys(GHashTable *hash_table);
	/*
		function:获取hash表中所有的key;
		param:hash表的句柄;
		return:返回key的链表.
	*/

**11.g_hash_table_get_values**

	GList *g_hash_table_get_value(GHashTable *hast_table);
	/*
		function:获取hash表中所有的value;
		param:hash表的句柄;
		return:返回value的链表.
	*/

### 1.2 glib GHashTable的使用实例

**1.代码**

	#include <stdio.h>
	#include <glib.h>	//glib库头文件
	#include <stdlib.h>
	#include <string.h>

	typedef Struct {
		char key[32];
		char value[32];
	} Node;

	static void display_hash(gpointer key, gpointer value, gpointer user_data)
	{
		printf("user_data: %s\n", user_data);	//gpointer相当于string类型
		printf("key: %s, value: %s\n", key, value);
	}

	static void destroy_key(gpointer key)
	{
		printf("destroy key: %s\n", key);
		//因为不需要释放key,直接清空即可
		memset(key, 0, sizeof(key));
	}

	static void destroy_value(gpointer value)
	{
		printf("destroy value: %s\n", value);
		//因为不需要释放value,直接清空即可
		memset(key, 0, sizeof(value));
	}

	Node *create_node(char *key, char *value)
	{
		Node *node = NULL;
		node = (Node *)malloc(sizeof(Node));
		if (node == NULL)
			return NULL;

		memset(node, 0, sizeof(Node));
		strcpy(node->key, key);
		strcpy(node->value, value);
		return node;
	}

	int main()
	{
		char buff[32] = {0};
		static GHashTable *g_hash = NULL;

		g_hash = g_hash_table_new_full(g_str_hash, g_int_equal, destroy_key, 
			destroy_value);

		Node *node = create_node("name", "defy");
		if (node != NULL)
			g_hash_table_insert(g_hash, node->key, node->value);
		Node *node1 = create_node("age", "18");
		if (node1 != NULL)
			g_hash_table_insert(g_hash, node1->key, node1->value);
		Node *node2 = create_node("sex", "man");
		if (node2 != NULL)
			g_hash_table_insert(g_hash, node2->key, node2->value);
		Node *node3 = create_node("id", "00001");
		if (node3 != NULL)
			g_hash_table_insert(g_hash, node3->key, node3->value);

		memcpy(buff, "this is param", 12);
		if (NULL != g_hash)
			g_hash_table_foreach(g_hash, display_hash, buff);

		printf("----------free hasttable----------\n");
		g_hash_table_destroy(g_hash);
		return 0;
	}

**2.编译**

	gcc main.c `pkg-config --libs --cflags glib-2.0`	//会得到一个a.out的可执行文件

**3.执行**

	./a.out