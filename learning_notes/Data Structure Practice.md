# Data Struture Practice

## 1. 一般线性表的合并

算法思想:遍历表A和表B,查看B的每一个元素是否在A中.若不在,则将B中的该元素插入到A的表尾,A表的表长+1.

时间复杂度和A, B的长度有关.为O(m * n).

代码如下:

	#include <stdio.h>
	#include <stdlib.h> //malloc函数需要

	#define MAX 100

	typedef struct {
		int *elem;
		int length;
	}SqList;

	/* Initialization */
	int InitSqList(SqList *L) //必须传递指针,传递引用会报错(SqList &L)--->报错.
	{
		L->elem = (int *)malloc(sizeof(int) * MAX);
		if (!L->elem) {
			return 0;
		} else {
			L->Length = 0;
			return 1;
		}
	}

	/* Get list length*/
	int ListLength(SqList L)
	{
		return L.length;
	}

	/* Travel List */
	void TraveList(SqList *L)
	{
		int i = 0;
		for (i=0; i<L.length; i++) {
			printf(%d ), L->elem[i];
		}
		printf("\n");
	}

	/* Create List */
	void CreateList(SqList *L)
	{
		int len, e, i;
		printf("Please input the list length: ");
		scanf("%d", &len);
		printf("Please input the element:\n");
		for (i=0; i<len; i++) {
			scanf("%d", &e);
			L->elem[i] = e; //输入一连串的数字后,会一个一个取进e中.然后放进elem数组中.
			L->length = i + 1;
		}
	}

	/* Combine the two list*/
	void Combine(SqList *A, SqList *B)
	{
		int i, j, exists;

		for (i=0; i<B->length; i++) {
			exists = 0;
			for (j=0; j<A->length; j++) {
				if (A->elem[j] == B->elem[i])
					exists = 1;
			}

			if (!exists) //A不存在B的元素,加入A中
				A->elem[A->length++] = B->elem[i];
		}
	}

	int main()
	{
		SqList A, B;

		if (!SqList(&A)) {
			printf("List A initiliazation fail\n");
			return -1;
		} else {
			printf("List A initialization success\n");
		}

		if (!SqList(&B)) {
			printf("List B initiliazation fail\n");
			return -1;
		} else {
			printf("List B initialization success\n");
		}

		CreateList(&A);
		printf("List length: %d\n", A.length);
		TraveList(&A);

		CreateList(&B);

		printf("After combination:\n");
		Combine(&A, &B);
		TraveList(&A);

		if (A.elem)
			free(A.elem);

		if (B.elem)
			free(B.elem);

		return 0;
	}

***

## 2. 单链表实现学生信息管理系统

代码如下:

	#include <stdio.h>
	#include <stdlib.h>
	
	#define MAX 100
	
	typedef struct {
		char name[20];
		char stu_num[20];
		int age;
		float score;
	}Student;
	
	
	typedef struct LNode {
		Student data;
		struct LNode *next;
	}LNode, *LinkList;
	
	/* Initialization */
	int InitList(LinkList *L)
	{
		*L = (LinkList)malloc(sizeof(struct LNode));
		if (!(*L))
			return 0;
			
		(*L)->next = NULL;
		return 1;
	}
	
	/* Check list is empty or not */
	int ListEmpty(LinkList *L)
	{
		if ((*L)->next == NULL) {
			return 1; /* The list is empty. */
		} else {
			return 0; /* The list is not empty. */
		}
	}
	
	/* Get the list length */
	int ListLength(LinkList L)
	{
		int length = 0;
		struct LNode *p = NULL;
		p = L->next;
	
		while (p) {
			p = p->next;
			length++;
		}
	
		return length;
	}
	
	/* Trave List */
	void TraveList(LinkList L)
	{
		struct LNode *p = NULL;
		p = L->next;
		printf("The List as follows:\n");
		while (p) {
			printf("%s %s %d %.2f", p->data.name, p->data.stu_num, p->data.age, p->data.score);
			printf("\n");
			p = p->next;
		}
	}
	
	/* Insert operation */
	int ListInsert(LinkList *L, int pos, Student *e)
	{
		struct LNode *p = NULL;
		int j = 0;
		p = *L;
	
		while (p && j < pos - 1) {
			p = p->next;
			++j;
		}
	
		if (!p || (j > pos - 1))
			return 0;
	
		struct LNode *s = NULL;
		s = (struct LNode *)malloc(sizeof(struct LNode));
		s->data = *e;
		s->next = p->next;
		p->next = s;
		return 1;
	}
	
	/* Delete List element */
	int ListDelete(LinkList *L, int pos, Student *e)
	{
		struct LNode *p = NULL, *q = NULL;
		int j = 0;
		p = *L;
	
		while (p && j < pos - 1) {
			p = p->next;
			++j;
		}
	
		if ((!p->next) || (j > pos - 1))
			return 0;
	
		q = p->next;
		p->next = q->next;
		*e = q->data;
		free(q);
		return 1;
	}
	
	/* Create List in head */
	void CreateListHead(LinkList *L, int n)
	{
		int i = 0;
		*L = (LinkList)malloc(sizeof(struct LNode));
		if (!(*L))
			return;
	
		(*L)->next = NULL;
		printf("Please input the element info: \n");
		for (i=n; i>0; i--) {
			printf("Please input the %d element: \n", i);
			struct LNode *p = NULL;
			p = (struct LNode *)malloc(sizeof(struct LNode));
			printf("Please input the name:");
			scanf("%s", &p->data.name);
			printf("Please input the number:");
			scanf("%s", &p->data.stu_num);
			printf("Please input the age:");
			scanf("%d", &p->data.age);
			printf("Please input the score:");
			scanf("%f", &p->data.score);
			p->next = (*L)->next;
			(*L)->next = p;
		}
	}
	
	/* Create List in rear */
	void CreateListRear(LinkList *L, int n)
	{
		int i = 0;
		(*L) = (LinkList)malloc(sizeof(struct LNode));
		if (!(*L))
			return;
	
		(*L)->next = NULL;
		struct LNode *r;
		r = *L;
		printf("Please input the element info: \n");
		for (i=0; i<n; i++) {
			printf("Please input the %d element: \n", i);
			struct LNode *p = NULL;
			p = (struct LNode *)malloc(sizeof(struct LNode));
			printf("Please input the name:");
			scanf("%s", &p->data.name);
			printf("Please input the number:");
			scanf("%s", &p->data.stu_num);
			printf("Please input the age:");
			scanf("%d", &p->data.age);
			printf("Please input the score:");
			scanf("%f", &p->data.score);
			p->next = NULL;
			r->next = p;
			r = p;
		}
	}
	
	int main()
	{
		LinkList L;
	
		printf("1. Initialization List\n");
		printf("2. Create List\n");
		printf("3. Insert operation\n");
		printf("4. Delete operation\n");
		printf("0. Quit\n");
	
		int choose = -1;
		while (choose != 0) {
			printf("Please selete the operation:\n");
			scanf("%d", &choose);
			switch(choose) {
			case 1: {
				if (InitList(&L)) {
					printf("The List initialization success!\n");
				} else {
					printf("The List initialization fail!\n");
					return -1;
				}
				break;
			}
			case 2: {
				printf("1. Create List in head\n");
				printf("2. Create List in rear\n");
				printf("Please choose one choice:\n");
				int choose1;
				scanf("%d", &choose1);
				switch(choose1) {
				case 1: {
					printf("Please input the length of the List: \n");
					int n;
					scanf("%d", &n);
					CreateListHead(&L, n);
					TraveList(L);
					break;
				}
				case 2: {
					printf("Please input the length of the List: \n");
					int n;
					scanf("%d", &n);
					CreateListRear(&L, n);
					TraveList(L);
					break;
				}
				}
				break;
			}
			case 3: {
				printf("Please input the position and student info: \n");
				int pos;
				scanf("%d", &pos);
	
				Student stu;
				printf("Please input the name: ");
				scanf("%s", &stu.name);
				printf("Please input the number: ");
				scanf("%s", &stu.stu_num);
				printf("Please input the age: ");
				scanf("%d", &stu.age);
				printf("Please input the score: ");
				scanf("%f", &stu.score);
	
				if (ListInsert(&L, pos, &stu)) {
					printf("Insert success!\n");
					TraveList(L);
				} else {
					printf("Insert fail!\n");
					return -1;
				}
				break;
			}
			case 4: {
				printf("Please specify the pos: \n");
				int pos;
				scanf("%d", &pos);
	
				Student stu;
	
				if (ListDelete(&L, pos, &stu)) {
					printf("Delete success!\n");
					printf("The info of delete element are: \n");
					printf("%s %s %d %.2f\n", stu.name, stu.stu_num, stu.age, stu.score);
					TraveList(L);
				} else {
					printf("Delete fail!\n");
				}
				break;
			}
			}
		}
	
		return 0;
	}

输入的内容如下:

	1. Initialization List
	2. Create List
	3. Insert operation
	4. Delete operation
	0. Quit
	Please selete the operation:
	1
	The List initialization success!
	Please selete the operation:
	2
	1. Create List in head
	2. Create List in rear
	Please choose one choice:
	1
	Please input the length of the List: 
	3
	Please input the element info: 
	Please input the 3 element: 
	Please input the name:aa
	Please input the number:12
	Please input the age:32
	Please input the score:56
	Please input the 2 element: 
	Please input the name:bb
	Please input the number:13
	Please input the age:35
	Please input the score:64
	Please input the 1 element: 
	Please input the name:cc
	Please input the number:14
	Please input the age:63
	Please input the score:21
	The List as follows:
	cc 14 63 21.00
	bb 13 35 64.00
	aa 12 32 56.00
	Please selete the operation:
	3
	Please input the position and student info: 
	2
	Please input the name: dd
	Please input the number: 15
	Please input the age: 23
	Please input the score: 68
	Insert success!
	The List as follows:
	cc 14 63 21.00
	dd 15 23 68.00
	bb 13 64 64.00
	aa 12 32 56.00
	Please selete the operation:
	4
	Please specify the pos: 
	2
	Delete success!
	The info of delete element are: 
	dd 15 23 68.00
	The List as follows:
	cc 14 63 21.00
	bb 13 64 64.00
	aa 12 32 56.00
	Please selete the operation:
	0

***

## 3. 创建二叉树

前序遍历输入格式为:"abc##de#g##f###".(每个"#"表示子树截止,有几个表示截止几个).

	数据格式:
	前序遍历:abcdegf
	中序遍历:cbegdfa
	后序遍历:cgefdba

代码如下:

	#include <stdio.h>
	#include <stdlib.h>
	
	typedef struct BiTNode {
		char data;
		struct BiTNode *lchild, *rchild;
	}BiTNode, *BiTree;
	
	/* Preorder create Binary Tree */
	void CreateBiTree(BiTree *T)
	{
		char ch;
		scanf("%c", &ch); /* Only get one char per once. */
		if (ch == '#') {
			*T = NULL;
		} else {
			*T = (BiTree)malloc(sizeof(BiTNode));
			(*T)->data = ch;
			CreateBiTree(&((*T)->lchild)); /* Create left tree. */
			CreateBiTree(&((*T)->rchild)); /* Create right tree. */
		}
	}
	
	/* Inorder Traverse Binary Tree */
	void InorderTraveBiTree(BiTree T)
	{
		if (T) {
			InorderTraveBiTree(T->lchild);
			printf("%c", T->data);
			InorderTraveBiTree(T->rchild);
		}
	}
	
	int main()
	{
		BiTree T;
		printf("Please input Binary Tree value:(abc##...):\n");
		CreateBiTree(&T);
		InorderTraveBiTree(T);
		printf("\n");
		return 0;
	}

***

## 4. 十进制数向任何进制的数转换

使用栈实现10进制的数向任何进制的数转换.

代码如下:

	#include <stdio.h>
	#include <stdlib.h>
	
	#define MAX 100
	
	typedef struct {
		int *base; /* The bottom of the stack. */
		int *top; /* The top of the stack. */
		int stacksize;
	}SqStack;
	
	/* Init the stack */
	int InitStack(SqStack *S)
	{
		S->base = (int *)malloc(MAX);
		if (!S->base)
			return -1;
	
		S->top = S->base;
		S->stacksize = MAX;
		return 0;
	}
	
	/* Check the stack is empty or not */
	int IsEmpty(SqStack *S)
	{
		if (S->top == S->base) {
			return 1; /* The stack is empty. */
		} else {
			return 0; /* The stack is not empty. */
		}
	}
	
	/* Push element into the stack */
	int Push(SqStack *S, int e)
	{
		if (S->top - S->base == S->stacksize)
			return -1;
	
		*(S->top++) = e;
		return 0;
	}
	
	/* Pop element from the stack */
	int Pop(SqStack *S, int *e)
	{
		if (S->top == S->base)
			return -1;
	
		*e = *(--S->top);
		return 0;
	}
	
	/* Convert decimal to any hexadecimal */
	void Conversion(SqStack *S, int decimal, int hexadecimal)
	{
		while(decimal) {
			Push(S, decimal % hexadecimal);
			decimal = decimal / hexadecimal;
		}
	
		while(!IsEmpty(S)) {
			int e;
			Pop(S, &e);
			printf("%d", e);
		}
	}
	
	int main()
	{
		SqStack S;
		int decimal, hexadecimal;
	
		if (InitStack(&S)) {
			printf("The stack initialization fail!\n");
		} else {
			printf("The stack initialization success!\n");
		}
	
		printf("Please input the number and hexadecimal:");
		scanf("%d %d", &decimal, &hexadecimal);
		Conversion(&S, decimal, hexadecimal);
		printf("\n");
	
		return 0;
	}
	
测试如下:

	./test
	The stack initialization success!
	Please input the number and hexadecimal:12 2
	1100

***

## 5. 