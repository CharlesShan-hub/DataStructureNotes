#include<stdio.h>
#include <stdlib.h>
#include<string.h>

//*****************************************
// 下面是链栈的操作
// 定义
typedef struct LNode
{
	double data;
	struct LNode* next;
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
bool Push(LinkStack &L, double x){
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if(s==NULL)return false;
	s->next = L->next;
	s->data = x;
	L->next = s;
	return true;
}

// 出栈
bool Pop(LinkStack &L,double &x){
	if(L->next==NULL)
		return false;
	LNode* s = L->next;
	x = s->data;
	L->next = s->next;
	free(s);
	return true;
}

// 读栈顶
bool GetTop(LinkStack &L,double &x){
	if(L->next==NULL)
		return false;
	x = L->next->data;
	return true;
}

// 判空
bool Empty(LinkStack L){
	return L->next==NULL;
}

//*****************************************
// 下面是计算表达式的函数
// 后缀表达式求值
double CalculateInversePoland(char e[]){
	double s1=0,s2=0,ans=0; // 2 1 -
	LinkStack stack;
	InitLinklist(stack);
	for(int i=0; i<strlen(e); i++){
		//printf("%c\n",e[i]);
		if(e[i]=='+'||e[i]=='-'||e[i]=='*'||e[i]=='/'){
			// 操作符 - 出栈 - 计算 - 入栈
			if(Pop(stack,s1)==false) return 0;
			if(Pop(stack,s2)==false) return 0;
			if(e[i]=='+'){
				ans = s2+s1;
				//printf("%lf + %lf = %lf\n",s2,s1,ans);
			}
			else if(e[i]=='-'){
				ans = s2-s1;
				//printf("%lf - %lf = %lf\n",s2,s1,ans);
			}
			else if(e[i]=='*'){
				ans = s2*s1;
				//printf("%lf * %lf = %lf\n",s2,s1,ans);
			}
			else{
				ans = s2/s1;
				//printf("%lf / %lf = %lf\n",s2,s1,ans);
			}
			Push(stack,ans);

		}else if(e[i]=='0'||e[i]=='1'||e[i]=='2'||e[i]=='3'||e[i]=='4'||
			e[i]=='5'||e[i]=='6'||e[i]=='7'||e[i]=='8'||e[i]=='9'){
			// 数字 - 入栈
			Push(stack,e[i]-48);
		}
	}
	return ans;
}

// 前缀表达式求值
double CalculatePoland(char e[]){
	double s1=0,s2=0,ans=0; 
	int flag=0;
	LinkStack stack;
	InitLinklist(stack);
	for(int i=strlen(e)-1; i!=-1; i--){
		if(e[i]=='+'||e[i]=='-'||e[i]=='*'||e[i]=='/'){
			// 操作符 - 出栈 - 计算 - 入栈
			if(Pop(stack,s2)==false) return 0;
			if(Pop(stack,s1)==false) return 0;
			if(e[i]=='+'){
				ans = s2+s1;
				//printf("%lf + %lf = %lf\n",s2,s1,ans);
			}
			else if(e[i]=='-'){
				ans = s2-s1;
				//printf("%lf - %lf = %lf\n",s2,s1,ans);
			}
			else if(e[i]=='*'){
				ans = s2*s1;
				//printf("%lf * %lf = %lf\n",s2,s1,ans);
			}
			else{
				ans = s2/s1;
				//printf("%lf / %lf = %lf\n",s2,s1,ans);
			}
			Push(stack,ans);

		}else if(e[i]=='0'||e[i]=='1'||e[i]=='2'||e[i]=='3'||e[i]=='4'||
			e[i]=='5'||e[i]=='6'||e[i]=='7'||e[i]=='8'||e[i]=='9'){
			// 数字 - 入栈
			Push(stack,e[i]-48);
		}
	}
	return ans;
}

// 转换成后缀表达式
char* ToInversePoland(char e[]){
	/*
	1. 遇到操作数 ->加入后缀表达式
	2. 遇到‘(’入栈, 遇到‘)’依次弹出站内运算符加入后缀表达式直到‘(’. (注意, 括号不入后缀表达式)
	3. 遇到运算符.  依次弹出运算及高于或等于当前运算符的所有运算符, 直到括号或栈空为止. 然后把当前运算符入栈. 
	4. 处理完所有字符后, 把栈中运算符依次弹出. 
	*/
	return e;
}

// 转换成前缀表达式
char* ToPoland(char e[]){
	return e;
}

int main(){
	char s = "1+(1+2)/3+(2-1)\0";

	char s1[] = "112+3/+21-+\0";
	printf("后缀表达式 %s = %lf\n",s1,CalculateInversePoland(s1));

	char s2[] = "++1/+123-21\0";
	printf("前缀表达式 %s = %lf\n",s2,CalculatePoland(s2));
	return 0;
}