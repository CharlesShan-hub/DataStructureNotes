// 队列的链式实现
/**
 * 定义
 * 初始化
 * 判空
 * 增
 * 删
 * 查
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// 定义
typedef struct LNode
{
	int data;
	struct LNode *next;
}LNode;

typedef struct
{
	LNode *front, *rear;	
}LinkQueue;

// 初始化 - 带头节点
void InitQueue1(LinkQueue &Q){
	Q.rear = (LNode*)malloc(sizeof(LNode));
	if(Q.rear == NULL) return;
	Q.front = Q.rear;
	Q.front->next = NULL;
}

// 初始化 - 不带头节点
void InitQueue2(LinkQueue &Q){
	Q.rear = NULL;
	Q.front = Q.rear;
}

// 判空 - 带头节点
bool EmptyLinkQueue1(LinkQueue Q){
	return Q.rear == Q.front;
}

// 判空 - 不带头节点
bool EmptyLinkQueue2(LinkQueue Q){
	return Q.front==NULL;
}

// 进栈 - 带头节点
void EnQueue1(LinkQueue &Q, int x){
	// 创建新节点
	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->next = NULL;
	s->data = x;
	// 尾插
	Q.rear->next = s;
	// 修改尾指针
	Q.rear = s;
}

// 进栈 - 不带头节点
void EnQueue2(LinkQueue &Q, int x){
	// 创建新节点
	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->next = NULL;
	s->data = x;
	// 尾插
	if(Q.rear==NULL){
		Q.rear = s;
		Q.front = s;
	}else{
		Q.rear->next = s;
		Q.rear = s;
	}
}

// 出栈 - 带头节点
bool DeQueue1(LinkQueue &Q,int &x){
	// 空队
	if(Q.rear==Q.front)return false;
	// 获取第一个节点
	LNode *s = Q.front->next;
	// 获取数据并返回
	x = s->data;
	// 改变front
	Q.front->next = s->next;
	// 改变rear - 最后一个节点
	if(s->next==NULL)
		Q.rear = Q.front;
	// 释放第一个节点
	free(s);
	return true;
}

// 出栈 - 不带头节点
bool DeQueue2(LinkQueue &Q,int &x){
	// 空队
	if(Q.front==NULL)
		return false;
	// 获取节点s
	LNode *s = Q.front;
	// 保存数据
	x = Q.front->data;
	// 连接队列
	if(Q.rear==Q.front)
		Q.rear=NULL;
	Q.front = s->next;
	// 删除s
	free(s);
	return true;
}

// 取队列元素 - 带头节点
bool GetFront1(LinkQueue Q,int &x){
	if(Q.rear==Q.front)return false;
	x = Q.front->next->data;
	return true;
}

// 取队列元素 - 不带头节点
bool GetFront2(LinkQueue Q,int &x){
	if(Q.rear==NULL)return false;
	x = Q.front->data;
	return true;
}

int main(){
	int x=0;
	printf("带头节点队列测试\n");
	LinkQueue Q1;
	InitQueue1(Q1);
	printf("是否为空:%d\n",EmptyLinkQueue1(Q1));
	printf("插入 1 ");EnQueue1(Q1,1);
	printf("插入 2 ");EnQueue1(Q1,2);
	printf("插入 3 ");EnQueue1(Q1,3);
	printf("插入 4 ");EnQueue1(Q1,4);
	printf("\n是否为空:%d\n",EmptyLinkQueue1(Q1));
	DeQueue1(Q1,x);printf("出栈 %d ",x);
	DeQueue1(Q1,x);printf("出栈 %d ",x);
	DeQueue1(Q1,x);printf("出栈 %d ",x);
	DeQueue1(Q1,x);printf("出栈 %d ",x);
	printf("\n是否为空:%d\n",EmptyLinkQueue1(Q1));


	printf("\n不带头节点队列测试\n");
	LinkQueue Q2;
	InitQueue2(Q2);
	printf("是否为空:%d\n",EmptyLinkQueue2(Q2));
	printf("插入 1 ");EnQueue2(Q2,1);
	printf("插入 2 ");EnQueue2(Q2,2);
	DeQueue2(Q2,x);printf("出栈 %d ",x);
	printf("插入 3 ");EnQueue2(Q2,3);
	printf("插入 4 ");EnQueue2(Q2,4);
	printf("\n是否为空:%d\n",EmptyLinkQueue2(Q2));
	DeQueue2(Q2,x);printf("出栈 %d ",x);
	DeQueue2(Q2,x);printf("出栈 %d ",x);
	DeQueue2(Q2,x);printf("出栈 %d ",x);
	DeQueue2(Q2,x);printf("出栈 %d ",x);
	printf("\n是否为空:%d\n",EmptyLinkQueue1(Q2));
	return 0;
}