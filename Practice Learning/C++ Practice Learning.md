# C++ Practice Learning

## 1. LRU缓存算法C++实现

### 1.1 说明

LRU(最近最少使用算法):将最近不常用的缓存数据淘汰掉,是一种Cache替换算法.

### 1.2 算法逻辑

	1.新数据会插入到链表头部;
	2.当缓存数据被访问,该缓存数据移动到链表头部;
	3.当新数据插入时到达缓存上限,将尾部数据删除掉(即最近最少使用的),新数据放在链表头部.

### 1.3 代码实现

	#include<iostream>
	#include<map>  
	using namespace std;
	
	
	//** 链表节点结构体
	
	struct ListNode
	{
		int m_key;                //key,value 形式方便map存储。
		int m_value;
		ListNode* pPre;
		ListNode* pNext;
	
		ListNode(int key, int value)
		{
			m_key = key;
			m_value = value;
			pPre = NULL;
			pNext = NULL;
		}
	};
	
	//*  LRU缓存实现类  双向链表。
	class LRUCache
	{
	public:
		//** 构造函数初始化缓存大小
		LRUCache(int size)
		{
			m_capacity = size;
			pHead == NULL;
			pTail == NULL;
		}
	
		~LRUCache()
		{
			//**  一定要注意，map释放内存时，先释放内部new的内存，在释放map的内存
			map<int, ListNode*>::iterator it = mp.begin();
			for (; it != mp.end();)
			{
				delete it->second;
				it->second = NULL;
				mp.erase(it++);    //** 注意：一定要这样写，it++ 放在其他任何一个地方都会导致其迭代器失效。
			}
			delete pHead;
			pHead == NULL;
			delete pTail;
			pTail == NULL;
	
		}
		//** 这里只是移除，并不删除节点
		void Remove(ListNode* pNode)
		{
			// 如果是头节点
			if (pNode->pPre == NULL)
			{
				pHead = pNode->pNext;
				pHead->pPre = NULL;
			}
	
			// 如果是尾节点
			if (pNode->pNext == NULL)
			{
				pTail = pNode->pPre;
				pTail->pNext = NULL;
			}
	
			else
			{
				pNode->pPre->pNext = pNode->pNext;
				pNode->pNext->pPre = pNode->pPre;
			}
	
		}
		//  将节点放到头部，最近用过的数据要放在队头。
		void SetHead(ListNode* pNode)
		{
			pNode->pNext = pHead;
			pNode->pPre = NULL;
			if (pHead == NULL)
			{
				pHead = pNode;
			}
			else
			{
				pHead->pPre = pNode;
				pHead = pNode;
	
			}
			if (pTail == NULL)
			{
				pTail = pHead;
			}
		}
		// * 插入数据，如果存在就只更新数据
		void Set(int key, int value)
		{
			map<int, ListNode*>::iterator it = mp.find(key);
			if (it != mp.end())
			{
				ListNode* Node = it->second;
				Node->m_value = value;
				Remove(Node);
				SetHead(Node);
			}
			else
			{
				ListNode* NewNode = new ListNode(key, value);
				if (mp.size() >= m_capacity)
				{
					map<int, ListNode*>::iterator it = mp.find(pTail->m_key);
					//从链表移除
					Remove(pTail);
					//删除指针指向的内存
					delete it->second;
					//删除map元素
					mp.erase(it);
				}
				//放到头部
				SetHead(NewNode);
				mp[key] = NewNode;
	
			}
		}
	
	
	
		//获取缓存里的数据
		int Get(int key)
		{
			map<int, ListNode*>::iterator it = mp.find(key);
			if (it != mp.end())
			{
				ListNode* Node = it->second;
				Remove(Node);
				SetHead(Node);
				return Node->m_value;
			}
			else
			{
				return -1;       //这里不太好，有可能取得值也为-1
			}
		}
	
		int GetSize()
		{
			return mp.size();
		}
	
	private:
		int m_capacity;    //缓存容量
		ListNode* pHead;   //头节点
		ListNode* pTail;   //尾节点
		map<int, ListNode*>  mp;   //mp用来存数据，达到find为o(1)级别。
	
	};
	
	int main()
	{
		LRUCache* lruCache = new LRUCache(3);
		lruCache->Set(1, 1);
		lruCache->Set(2, 3);
		cout << lruCache->GetSize() << endl;
		lruCache->Set(3, 5);
		cout << lruCache->GetSize() << endl;
		cout << lruCache->Get(1) << endl;
		lruCache->Set(6, 3);
		cout << lruCache->GetSize() << endl;
		cout << lruCache->Get(3) << endl;
		cout << lruCache->Get(1) << endl;
		cout << lruCache->Get(2) << endl;
	
		return 0;
	
	}