/** 线性表 - 单链表 - 无头结点
 *  内容包括:
 *  无头结点的单链表的定义
 *  初始化
 *  判空
 *  按位插入
 *  后插操作
 *  指定结点插入
 *  删除操作
 *  删除指定结点
 *  输出操作
 *  销毁操作
 *  求表长
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 链式储存类型定义  
#define InitSize 3 // 默认最大长度
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode, *LinkList;

// 初始化
bool InitList(LinkList &L)
{
	L = NULL;
	return true;
	// 或者直接 return(L=NULL);
}

// 判空
bool Empty(LinkList L)
{
	if(L==NULL)
		return true;
	else
		return false;
	// 或直接: return (L==NULL);
}

// 插入操作
bool ListInsert(LinkList &L, int i, int e)
{
	// i合法性判断
	if(i<1) return false;
	// 插入第一个元素
	if(i==1){
		LNode* s = (LNode*)malloc(sizeof(LNode));
		s->data = e;
		s->next = L;
		L = s;
		return true;
	}
	// 不是第一个元素
	LNode* p = L;
	int count = 1; // 头指针是第零个节点, 没有头指针就是1了
	while(p!=NULL && count<i-1){
		count++;
		p = p->next;
	}
	if(p==NULL) return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

// 输出操作
bool PrintList(LinkList L){
	LNode* p = L;
	if(p==NULL) return false;
	do{
		printf("%d ",p->data);
		p = p->next;
	}while(p!=NULL);
	printf("\n");
	return true;
}

// 后插操作
bool InsertNextNode(LNode* p, int e)
{
	if(p==NULL) return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if(s==NULL) return false; // 内存不足
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
}

// 指定结点插入
bool InsertPriorNode(LNode* p, int e)
{
	// 先后插 (- 把自己的值先赋给后边)
	if(!InsertNextNode(p,p->data)) return false;
	/*
	if(p==NULL) return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if(s==NULL) return false; // 内存不足
	s->data = p->data;
	s->next = p->next;
	p->next = s;
	*/
	// 再交换data
	p->data = e;
	return true;
}

// 删除操作
bool ListDelete(LinkList &L, int i)
{ 
	// 第一个结点
	if(i==1){
		LNode* p = L;
		if(p==NULL) return false;
		if(p->next==NULL){free(p);L=NULL;}
		L = p->next;
		free(p);
		return true;
	}
	// 找到i-1个结点
	LNode* p = L;
	int count=0;
	while(p!=NULL && count<i-2){
		p = p->next;count++;
	}
	if(p==NULL) return false;
	if(p->next==NULL) return false; // p的后继没有后继
	// 删除这个结点
	LNode* d = p->next;
	p->next = d->next;
	free(d);
	return true;
}

// 删除指定结点
bool DeleteNode(LNode* L)
{
	if(L==NULL) return false;
	LNode* p = L->next;
	if(p==NULL){ // L是最后一个
		free(L);
	}else{
		L->data = p->data;
		L->next = p->next;
		free(p);
	}
	return true;
}

// 求表长
int Length(LinkList L)
{
	LNode* p = L;
	int i=0;
	while(p){
		p=p->next; i++;
	}
	return i;
}

// 销毁
void DestroyList(LinkList &L)
{
	LNode* p = L, *q = L;
	while(p){
		q=p;
		p = p->next;
		free(q);
	}
	L=NULL;
}

// 测试部分	
int main(void)
{
	printf("线性表 - 单链表 - 带头结点\n");

	// 单链表 - 带头结点
	LinkList L;

	// 初始化
	printf("初始化\n");
	InitList(L);

	// 判空
	printf("判空 : %d\n",Empty(L));

	// 添加结点
	ListInsert(L, 1, 10);
	ListInsert(L, 1, 5);
	ListInsert(L, 3, 20);
	ListInsert(L, 4, 30);
	ListInsert(L, 5, 40);
	printf("添加结点 : ");
	PrintList(L);

	// 后插操作
	InsertNextNode(L->next,100);// 插到第二个
	printf("后插结点 : ");
	PrintList(L);

	// 删除结点
	ListDelete(L,1);
	printf("删除节点 1 : ");
	PrintList(L);
	ListDelete(L,5);
	printf("删除节点 5 : ");
	PrintList(L);

	// 删除指定结点
	DeleteNode(L->next);
	printf("删除节点 L->next : ");
	PrintList(L);
	DeleteNode(L);
	printf("删除节点 L       : ");
	PrintList(L);

	// 求表长
	printf("求表长 : %d\n",Length(L));

	// 销毁
	DestroyList(L);

	return 0;
}