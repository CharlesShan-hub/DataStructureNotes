#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild,*rchild;
	//struct BiTNode *parent; // 变成了 三叉链表
}BiTNode,*BiTree;

// 定义
typedef struct LNode
{
	struct BiTNode *data;
	struct LNode *next;
}LNode;

typedef struct
{
	LNode *front, *rear;	
}LinkQueue;

// 初始化 - 带头节点 - 队列
void InitQueue1(LinkQueue &Q){
	Q.rear = (LNode*)malloc(sizeof(LNode));
	if(Q.rear == NULL) return;
	Q.front = Q.rear;
	Q.front->next = NULL;
}

// 判空 - 带头节点
bool EmptyLinkQueue1(LinkQueue Q){
	return Q.rear == Q.front;
}

// 进栈 - 带头节点
void EnQueue1(LinkQueue &Q, BiTree x){
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
bool DeQueue1(LinkQueue &Q,BiTree &x){
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
bool GetFront1(LinkQueue Q,BiTree &x){
	if(Q.rear==Q.front)return false;
	x = Q.front->next->data;
	return true;
}

void visit(BiTree T){
	printf("%d ",T->data);
}

void PreOrder(BiTree T){
	if(T!=NULL){
		visit(T);
		PreOrder(T->lchild);
		PreOrder(T->rchild);
	}
}

void MidOrder(BiTree T){
	if(T!=NULL){
		MidOrder(T->lchild);
		visit(T);
		MidOrder(T->rchild);
	}
}

void LastOrder(BiTree T){
	if(T!=NULL){
		LastOrder(T->lchild);
		LastOrder(T->rchild);
		visit(T);
	}
}

void LevelOrder(BiTree T){
	if(T!=NULL){
		LinkQueue Q;
		InitQueue1(Q);
		BiTree p;
		EnQueue1(Q,T);
		while(!EmptyLinkQueue1(Q)){
			// 出队
			DeQueue1(Q,p);
			// 访问出队结点
			visit(p);
			// 左右孩子入队
			if(p->lchild!=NULL)
				EnQueue1(Q,p->lchild);
			if(p->rchild!=NULL)
				EnQueue1(Q,p->rchild);
		}
	}
}

void DeleteTree(BiTree &T){
	if(T!=NULL){
		DeleteTree(T->lchild);
		DeleteTree(T->rchild);
		free(T);
	}
}

BiTNode* NewNode(int data){
	BiTNode *T = (BiTNode*)malloc(sizeof(BiTree));
	if(T==NULL){
		printf("Memory run out!");
		return NULL;
	}else{
		printf("Put [%d] at %p\n",data,T);
	}
	T->data = data;
	T->lchild = NULL;
	T->rchild = NULL;
	return T;
}

BiTree LeftInsert(BiTree T, int data){
	if(T==NULL)
		return T;
	BiTNode *p = NewNode(data);
	T->lchild=p;
	return T;
}

BiTree RightInsert(BiTree T, int data){
	if(T==NULL)
		return T;
	BiTNode *p = NewNode(data);
	T->rchild=p;
	return T;
}

BiTree TestInit(){
	BiTree T = NewNode(1);
	LeftInsert(T,2);
	RightInsert(T,3);
	LeftInsert(T->lchild,4);
	RightInsert(T->lchild,5);
	LeftInsert(T->rchild,6);
	RightInsert(T->lchild->lchild,7);
	/**
	 *       A-1
	 *     /  \
	 *    B-2   C-3
	 *   / \    /
	 *  D-4 E-5 F-6
	 *  \
	 *   G-7
	 */
	return T;

}
int main(){
	printf("不知道为啥不能在Mac里跑, 会有Segmentation fault: "
		"11, 所以我就在win里边跑完放的.exe\n");
	printf("构造数:\n");
	BiTree T = TestInit();
	// 先序遍历
	printf("\n先序遍历:");
	PreOrder(T);

	// 中序遍历
	printf("\n中序遍历:");
	MidOrder(T);

	// 后续遍历
	printf("\n后序遍历:");
	LastOrder(T);

	// 层次遍历
	printf("\n层次遍历:");
	LevelOrder(T);

	// 删除
	DeleteTree(T);
	printf("\n");
	
	system("pause");
	return 0;

}