// 队列的顺序实现 - 两种方案
/**
 * 定义
 * 初始化
 * 判空
 * 增
 * 删
 * 查
 */

#include<stdio.h>

// 定义
#define MaxSize 10
typedef struct
{
	int data[MaxSize];
	int front,rear;
}SqQueue1;// 会浪费一个空间

typedef struct
{
	int data[MaxSize];
	int front,rear;
	int size;
}SqQueue2; // 不会浪费空间

typedef struct
{
	int data[MaxSize];
	int front,rear;
	int tag; 
	// 当最近一次是删除时, tag==0, - 只有删除才能导致队空,
	// 当最近一次是添加时, tag==1; - 只有插入再能导致队满.
	// 队满条件: Q.rear==Q.front && Q.tag=1;
	// 队空条件: Q.rear==Q.front && Q.tag=0;
}SqQueue3; // 不会浪费空间

// 初始化
bool InitSqQueue1(SqQueue1 &Q){
	Q.front = 0;
	Q.rear = 0;
	return true;
}
// 队尾指针可能指向下一个要插入的元素, 也可以能指向最后一个内容, 考试时要注意

bool InitSqQueue2(SqQueue2 &Q){
	Q.front = 0;
	Q.rear = 0;
	Q.size = 0;
	return true;
}

// 判空
bool EmptySqQueue1(SqQueue1 Q){
	return Q.front == Q.rear;
}

bool EmptySqQueue2(SqQueue2 Q){
	return Q.size == 0;
}

// 插入
bool EnQueue1(SqQueue1 &Q, int x){
	// 队满
	if((Q.rear+1)%MaxSize == Q.front) return false;
	// 插入
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear+1)%MaxSize;//取余运算
	return true;
}

bool EnQueue2(SqQueue2 &Q, int x){
	// 队满
	if(Q.size==MaxSize) return false;
	// 插入
	Q.data[Q.rear] = x;
	Q.rear = (Q.rear+1)%MaxSize;//取余运算
	Q.size++;
	return true;
}

// 出队
bool DeQueue1(SqQueue1 &Q, int &x){
	// 队空
	if(Q.rear == Q.front) return false;
	// 删除
	x = Q.data[Q.front];
	Q.front = (Q.front+1)%MaxSize;
	return true;
}

bool DeQueue2(SqQueue2 &Q, int &x){
	// 队空
	if(Q.size == 0) return false;
	// 删除
	x = Q.data[Q.front];
	Q.front = (Q.front+1)%MaxSize;
	Q.size--;
	return true;
}

// 获取队头
bool GetHead1(SqQueue1 &Q, int &x){
	// 队空
	if(Q.rear == Q.front) return false;
	// 删除
	x = Q.data[Q.front];
	return true;
}

bool GetHead2(SqQueue2 &Q, int &x){
	// 队空
	if(Q.rear == Q.front) return false;
	// 删除
	x = Q.data[Q.front];
	return true;
}

int main(){
	SqQueue1 Q;
	InitSqQueue1(Q);
	EnQueue1(Q,1);
	EnQueue1(Q,2);
	EnQueue1(Q,3);

	return 0;
}