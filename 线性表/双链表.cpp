/** 线性表 - 双链表
 *  内容包括:
 *  双链表的定义
 *  初始化
 *  p结点后插入s结点
 *  删除后继结点
 *  销毁
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 链式储存类型定义  
#define InitSize 5 // 默认最大长度
typedef struct DNode
{
	int data;
	struct DNode *prior, *next;
}DNode, *DLinkList;

// 对比一下单链表定义
/*
typedef struct LNode
{
	int data;
	struct *LNode next;
}LNode, *LinkList;
*/

// 初始化
bool InitDlinklist(DLinkList &L)
{
	L = (DNode*)malloc(sizeof(DNode));
	if(L==NULL) return false; // 内存不足
	L->prior = NULL;
	L->next  = NULL;
	return true;
}

// p结点后插入s结点
//    
//  . - x - .   
//      
//      . - s - .
bool InsertNextDNode(DNode* p, DNode* s)
{
	// 判断p合法
	if(p==NULL || s==NULL) return false;
	// 后插
	if(p->next) // p不是最后一个结点
		// 如果p有后继节点, 要修改后继节点的prime指针
		p->next->prior = s;
	p->next = s; 
	return true;
}

// 删除后继结点
bool DeleteNextDNode(DNode* p)
{
	// 链表: p -> q -> q next
	if(p==NULL) return false;
	DNode* q = q->next;
	if(q==NULL) return false;
	p->next = q->next;
	if(q->next)
		q->next->prior = p;
	free(q);
	return true;
}

// 销毁
void DestoryDList(DLinkList &L)
{
	// 删除L后继结点
	while(L->next)
		DeleteNextDNode(L);
	// 删除L
	free(L);
	L=NULL;
}

int main(void)
{
	printf("线性表 - 双链表\n");

	// 双链表
	DLinkList L;

	// 初始化
	InitDlinklist(L);

	// 销毁
	DestoryDList(L);

	return 0;
}
