/** 线性表 - 循环单链表
 *  内容包括:
 *  循环单链表的定义
 *  初始化
 *  判空
 *  是否表尾
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 循环单链表类型定义  
#define InitSize 10 // 默认最大长度
typedef struct LNode
{
	int data;
	struct LNode *next ;
}LNode, *LinkList;

// 初始化
bool InitList(LinkList &L)
{
	L = (LNode*)malloc(sizeof(LNode));
	if(L==NULL) return false;
	L->next = L; // 这里是特点
	return true;
}

// 判空
bool Empty(LinkList L)
{
	if(L->next == L) return true;
	else return false;
}

// 是否表尾
bool isTail(LinkList L, LNode* p)
{
	if(p->next == L) return true;
	else return false;
}

// 节点后插入
// 在不循环的链表中, 下面操作在表尾会出错, 但是在循环链表中就不会出错.
bool InertNextNode(LNode* p,LNode* s){
	s->next = p->next;
	p->next = s;
	return true;
}

// 节点后删除
bool DeleteNextNode(LNode* p){
	if(p->next==NULL)
		return false;
	
	LNode* q = p->next;
	p->next = q->next;
	free(q);
	return true;
}

// 测试
int main(void)
{
	// 声明
	LinkList L;

	// 初始化
	InitList(L);

	// 判空
	printf("判空 : %d\n",Empty(L));

	return 0;
}