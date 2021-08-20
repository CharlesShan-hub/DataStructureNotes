typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode, *LinkStack, *Stack;

// 初始化
bool InitStack(LinkStack &L){
	L = (LNode*)malloc(sizeof(LNode));
	if(L==NULL)
		return false;
	L->next = NULL;
	return true;
}

// 入栈
bool StackPush(LinkStack &L, int x){
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if(s==NULL)return false;
	s->next = L->next;
	s->data = x;
	L->next = s;
	return true;
}

// 出栈
bool StackPop(LinkStack &L,int &x){
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
bool StackEmpty(LinkStack L){
	return L->next==NULL;
}