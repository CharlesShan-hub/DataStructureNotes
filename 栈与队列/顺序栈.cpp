// 顺序栈 - 两种top
/** 基本操作如下
 * 定义
 * 初始化
 * 判空
*/
#include <stdio.h>

// 定义
#define MaxSize 10
typedef struct
{
	int data[MaxSize];
	int top;
}SqStack;// 顺序栈

/*
// 初始化 - 方案一:top指向最后一个原元素
void InitStack(SqStack &S){
	S.top = -1;
}
*/

// 初始化 - 方案二:top指向下一个要插入的元素
void InitStack(SqStack &S){
	S.top = 0;
}

// 判空 - 方案一:top指向最后一个原元素
/*
bool StackEmpty(SqStack S){
	return S.top==-1;
}
*/

// 判空 - 方案二:top指向下一个要插入的元素
bool StackEmpty(SqStack S){
	return S.top==0;
}

// 进栈 - 方案一:top指向最后一个原元素
/*
bool Push(SqStack &S, int x){
	if(S.top==MaxSize-1)
		return false;
	return S.data[++S.top] = x;
}
*/

// 进栈 - 方案二:top指向下一个要插入的元素
bool Push(SqStack &S, int x){
	if(S.top==MaxSize)
		return false;
	return S.data[S.top++] = x;
}

// 出栈 - 方案一:top指向最后一个原元素
/*
bool Pop(SqStack &S, int &x){
	if(S.top==-1)
		return false;
	return x = S.data[S.top--];
}
*/

// 出栈 - 方案二:top指向下一个要插入的元素
bool Pop(SqStack &S, int &x){
	if(S.top==0)
		return false;
	return x = S.data[--S.top];
}

// 读栈顶 - 方案一:top指向最后一个原元素
/*
bool GetTop(SqStack S, int &x){
	if(S.top==-1)
		return false;
	return x = S.data[S.top];
}
*/

// 读栈顶 - 方案二:top指向下一个要插入的元素
bool GetTop(SqStack S, int &x){
	if(S.top==-1)
		return false;
	return x = S.data[S.top];
}

int main(){
	// 声明顺序栈
	SqStack S;
	// 初始化
	InitStack(S);
	// 进栈
	Push(S,1);
	Push(S,2);
	Push(S,3);
	Push(S,4);
	Push(S,5);
	Push(S,6);
	Push(S,7);
	Push(S,8);
	Push(S,9);
	Push(S,10);
	Push(S,11);
	// 获取栈顶
	int x;
	GetTop(S,x);
	printf("%d\n",x);
	// 出栈
	Pop(S,x);
	printf("%d ",x);
	Pop(S,x);
	printf("%d ",x);
	Pop(S,x);
	printf("%d\n",x);

	return 0;
}