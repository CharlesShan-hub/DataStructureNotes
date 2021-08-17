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

// 初始化 - 带头节点 - 队列
LinkQueue InitQueue(){
	LinkQueue Q;
	Q.rear = (LNode*)malloc(sizeof(LNode));
	//if(Q.rear == NULL) 
	//	return NULL;
	Q.front = Q.rear;
	Q.front->next = NULL;
	return Q;
}

// 判空 - 带头节点
bool EmptyLinkQueue(LinkQueue Q){
	return Q.rear == Q.front;
}

// 进栈 - 带头节点
void EnQueue(LinkQueue &Q, int x){
	// 创建新节点
	LNode *s = (LNode*)malloc(sizeof(LNode));
	s->next = NULL;
	s->data = x;
	// 尾插
	Q.rear->next = s;
	// 修改尾指针
	Q.rear = s;
}

// 出栈 - 带头节点
bool DeQueue(LinkQueue &Q,int &x){
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

// 取队列元素 - 带头节点
bool GetFront(LinkQueue Q,int &x){
	if(Q.rear==Q.front)return false;
	x = Q.front->next->data;
	return true;
}