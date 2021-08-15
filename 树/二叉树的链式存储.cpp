#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
typedef struct BiTNode
{
	int data;
	struct BiTNode *lchild;
	struct BiTNode *rchild;
	//struct BiTNode *parent; // 变成了 三叉链表
}BiTNode,*BiTree;


int main(){
	// 定义一颗空树
	BiTree root =NULL;

	// 插入根结点
	root = (BiTree)malloc(sizeof(BiTree));
	root->data = 1;
	root->lchild = NULL;
	root->rchild = NULL;

	// 插入新结点
	BiTNode *q = (BiTNode*)malloc(sizeof(BiTNode));
	q->data = 3;
	q->lchild = NULL;
	q->rchild = NULL;

	root->rchild=q;

	BiTNode *p = (BiTNode*)malloc(sizeof(BiTNode));
	p->data = 2;
	p->lchild = NULL;
	p->rchild = NULL;

	root->lchild=p;

	


	printf("%d %d %d\n",root->data,root->lchild->data,root->rchild->data);
	return 0;
}