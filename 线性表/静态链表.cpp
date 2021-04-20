/** 线性表 - 静态链表
 *  内容包括:
 *  静态链表的定义
 *  初始化
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 静态链表类型定义  
#define MaxSize 10 // 默认最大长度
typedef struct Node
{
	int data;
	int next;
}SLinkList[MaxSize];

// 初始化
bool InitList(SLinkList &L)
{
	// 去除垃圾值
	for(int i=0; i<MaxSize; i++)
		L[i].next = 0;
	// 设置第一项
	L[0].next = -1;
	return true;
}

int main(void)
{
	// 声明
	SLinkList L;

	// 初始化
	InitList(L);

	return 0;
}

