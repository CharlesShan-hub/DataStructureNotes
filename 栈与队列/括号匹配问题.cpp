#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#define MaxSize 20
typedef struct{
	char data[MaxSize];
	int top;
}SqStack;

// 初始化
void InitStack(SqStack &S){
	S.top=-1;
}

// 判断栈是否为空
bool EmptyStack(SqStack S){
	return S.top==-1;
}

// 入栈
bool Push(SqStack &S, char x){
	return S.top==MaxSize-1 ? false : S.data[++S.top]=x;
}

// 出栈
bool Pop(SqStack &S,char &x){
	return S.top==-1 ? false : x=S.data[S.top--];
}

/*
考试时这样写
#define MaxSize 20
typedef struct{
	char data[MaxSize];
	int top;
}SqStack;

// 初始化栈
void InitStack(SqStack &S)

// 判断栈是否为空
bool EmptyStack(SqStack S)

// 入栈
bool Push(SqStack &S,char x)

// 出栈
bool Pop(SqStack &S,charchar &x)

*/

bool BracketCheck(char str[]){
	SqStack S;
	InitStack(S);
	char x;
	for(int i=0;i<strlen(str);i++){
		printf("%c",str[i]);
		if(str[i]=='('||str[i]=='['||str[i]=='{')
			Push(S,str[i]);
		if(str[i]==')'||str[i]==']'||str[i]=='}'){
			if(EmptyStack(S))
				return false;
			Pop(S,x);
			if(str[i]==')' && x!='(') return false;
			if(str[i]==']' && x!='[') return false;
			if(str[i]=='}' && x!='{') return false;
		}
	}
	return EmptyStack(S);
}

int main(){
	char *a;
	strcpy(a,"{}[]");
	printf("\n判断匹配: %d\n",BracketCheck(a));
	return 0;
}