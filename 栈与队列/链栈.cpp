// 链栈
/**
 * 定义
 * 初始化
 * 入栈
 * 出栈
 * 读栈顶
 * 判空
 */

// 定义
#include <stdio.h>
#include <stdlib.h>
typedef struct LNode
{
	int data;
	LNode* next;
}LNode, *LinkStack;

// 初始化
bool InitLinklist(LinkStack &L){
	L = (LNode*)malloc(sizeof(LNode));
	if(L==NULL)
		return false;
	L->next = NULL;
	return true;
}

// 入栈
bool Push(LinkStack &L, int x){
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if(s==NULL)return false;
	s->next = L->next;
	s->data = x;
	L->next = s;
	return true;
}

// 出栈
bool Pop(LinkStack &L,int &x){
	if(L->next==NULL)
		return false;
	LNode* s = L->next;
	x = s->data;
	L->next = s->next;
	free(s);
	return true;
}

// 读栈顶
bool GetTop(LinkStack &L,int &x){
	if(L->next==NULL)
		return false;
	x = L->next->data;
	return true;
}

// 判空
bool Empty(LinkStack L){
	return L->next==NULL;
}

int main(){
	return 0;
}