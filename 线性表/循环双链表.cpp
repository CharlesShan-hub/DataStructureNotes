/** 线性表 - 循环单链表
 *  内容包括:
 *  循环双链表的定义
 *  初始化
 *  判空
 *  是否表尾
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 循环单链表类型定义  
#define InitSize 10 // 默认最大长度
typedef struct DLNode
{
	int data;
	struct DLNode *prior, *next;
}DLNode, *DLinkList;

// 初始化
bool InitList(DLinkList &L)
{
	L = (DLNode*)malloc(sizeof(DLNode));
	if(L==NULL) return false;
	L->next = L;
	L->prior= L;
	return true;
}

// 判空
bool Empty(DLinkList L)
{
	if(L->next == L) return true;
	else return false;
}

// 是否表尾
bool isTail(DLinkList L, DLNode* p)
{
	if(p->next == L) return true;
	else return false;
}

// 节点后插入
// 在不循环的链表中, 下面操作在表尾会出错, 但是在循环链表中就不会出错.
bool InertNextNode(DLNode* p,DLNode* s){
	s->next = p->next;
	s->prior = p;
	p->next = s;
	p->next->prior = s;
	return true;
}

// 节点后删除
bool DeleteNextNode(DLNode* p){
	if(p->next==NULL)
		return false;
	
	DLNode* q = p->next;
	p->next = q->next;
	if(q->next!=NULL)
		q->next->prior=p;
	free(q);
	return true;
}

// 测试
int main(void)
{
	// 声明
	DLinkList L;

	// 初始化
	InitList(L);

	// 判空
	printf("判空 : %d\n",Empty(L));

	return 0;
}