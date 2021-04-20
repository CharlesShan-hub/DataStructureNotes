/** 线性表 - 单链表 - 带头结点
 *  内容包括:
 *  带头结点的单链表的定义
 *  初始化
 *  判空
 *  按位插入
 *  后插操作
 *  指定结点插入
 *  删除操作
 *  删除指定结点
 *  输出操作
 *  按值查找
 *  按位查找
 *  求表长
 *  销毁操作
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 链式储存类型定义  
#define InitSize 3 // 默认最大长度
typedef struct LNode
{
	int data;
	struct LNode *next ;
}LNode, *LinkList;

// 初始化 - 带头结点
bool InitList(LinkList &L)
{
	L = (LNode*)malloc(sizeof(LNode));
	if(L==NULL)
		return false; // 内存不足
	L->next = NULL;
	return true;
}

// 判空
bool Empty(LinkList L)
{
	if(L->next==NULL)
		return true;
	else
		return false;
	// 或直接: return (L->next=NULL);
}

// 按位查找
LNode* GetElem(LinkList L, int i)
{
	// 判断i
	if(i<0) return NULL;
	// 寻找i
	LNode* p = L;
	int j=0;
	while(p && j<i){
		p = p->next;
		j++;
	}
	return p;
}

// 按值查找
LNode* LocateElem(LinkList L, int e)
{
	LNode* p = L->next;
	while(p && p->data!=e)
		p = p->next;
	return p;// 找到后返回该节点指针, 否则返回NULL
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
	//if(!InsertNextNode(p,p->data)) return false;
	if(p==NULL) return false;
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if(s==NULL) return false; // 内存不足
	s->data = p->data;
	s->next = p->next;
	p->next = s;
	// 再交换data
	p->data = e;
	return true;
}

// 按位插入
bool ListInsert(LinkList &L, int i, int e)
{
	// i合法性判断
	if(i<1) return false;
	// 寻找添加位置
	LNode* p = GetElem(L,i-1);
	/*
	LNode* p = L; // 头节点算第零个结点
	int count = 0;
	while(p!=NULL && count<i-1){
		p = p->next; count++; 
	}
	*/
	if(p==NULL) return false;
	// 添加结点
	InsertNextNode(p,e);
	/*
	LNode* s = (LNode*)malloc(sizeof(LNode*));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return true;
	*/
	return true;
}

// 删除操作
bool ListDelete(LinkList &L, int i)
{ 
	// i合法性判断
	if(i<1) return false;
	// 找到i-1个结点
	LNode* p =  (L,i-1);
	/*
	LNode* p = L;
	int count=0;
	while(p!=NULL && count<i-1){
		p = p->next;count++;
	}
	*/
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
	// 用L的下一个节点代替L, 然后释放L的下一个节点
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

// 输出操作
bool PrintList(LinkList L){
	LNode* p = L->next;
	if(p==NULL) return false;
	do{
		printf("%d ",p->data);
		p = p->next;
	}while(p!=NULL);
	printf("\n");
	return true;
}

// 求表长
int Length(LinkList L)
{
	LNode* p = L->next;
	int i=0;
	while(p){
		p=p->next; i++;
	}
	return i;
}

// 销毁
void DestroyList(LinkList &L)
{
	LNode* p = L,*q = L;
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
	ListInsert(L, 2, 20);
	printf("添加结点 : ");
	PrintList(L);

	// 指定结点插入
	InsertPriorNode(L->next->next, 5);  // L是头结点
	printf("指定结点插入 : ");
	PrintList(L);

	// 后插操作
	InsertNextNode(L->next,100);// 插到第二个
	printf("后插结点 : ");
	PrintList(L);

	// 删除结点
	ListDelete(L,4);
	printf("删除节点 4 : ");
	PrintList(L);

	// 删除结点
	DeleteNode(L->next); // L->next是第一项
	printf("删除节点 L->next : ");
	PrintList(L);

	// 求表长
	printf("求表长 : %d\n",Length(L));

	// 销毁
	DestroyList(L);

	return 0;
}