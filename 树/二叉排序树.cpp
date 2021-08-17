#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
typedef struct BSTNode
{
	int data;
	struct BSTNode *lchild,*rchild;
	//bool ltag,rtag; // 左右线索标志
	//struct BSTNode *parent; // 变成了 三叉链表
}BSTNode,*BSTree;

BSTNode* NewNode(int data){
	BSTNode *T = (BSTNode*)malloc(sizeof(BSTNode));
	if(T==NULL){
		//printf("Memory run out!");
		return NULL;
	}else{
		//printf("Put [%d] at %p\n",data,T);
	}
	T->data = data;
	T->lchild = NULL;
	T->rchild = NULL;
	return T;
}

BSTNode *LeftInsert(BSTree T, int data){
	if(T==NULL)
		return T;
	BSTNode *p = NewNode(data);
	T->lchild=p;
	return T;
}

BSTNode *RightInsert(BSTree T, int data){
	if(T==NULL)
		return T;
	BSTNode *p = NewNode(data);
	T->rchild=p;
	return T;
}

BSTree TestInit(){
	BSTree T = NewNode(19);
	LeftInsert(T,13);
	RightInsert(T,50);
	LeftInsert(T->lchild,11);
	LeftInsert(T->rchild,26);
	LeftInsert(T->rchild->lchild,21);
	RightInsert(T->rchild->lchild,30);
	RightInsert(T->rchild,66);
	LeftInsert(T->rchild->rchild,60);
	RightInsert(T->rchild->rchild,70);
	/**
	 *      A-19
	 *     /    \
	 *    B-13  C-50
	 *   /     /    \
	 *  D-11  E-26   F-66
	 *       / \     /  \
	 *   G-21 H-30  I-60 G-70
	 */
	printf("\n初始化:\n"
		"      A-19\n"
		"     /    \\\n"
		"    B-13  C-50\n"
		"   /     /    \\\n"
		"  D-11  E-26   F-66\n"
		"       / \\     /  \\\n"
		"   G-21 H-30  I-60 J-70\n");
	return T;
}

void Visit(BSTNode *T){
	printf("%d ",T->data);
}

void DeleteTree(BSTree &T){
	if(T!=NULL){
		//if(T->ltag==0)
			DeleteTree(T->lchild);
		//if(T->rtag==0)
			DeleteTree(T->rchild);
		free(T);
	}
}

BSTNode *BSTSearch(BSTree T,int data){
	while(T!=NULL && T->data!=data)
		if(data < T->data)
			T=T->lchild;
		else
			T=T->rchild;
	return T;
}

bool BSTInsert(BSTree &q,int data){
	BSTNode *temp = q;
	while(1){
		if(q==NULL){
			q = NewNode(data);
			return true;
		}
		Visit(q);
		if(data < q->data){
			if(q->lchild == NULL){
				q->lchild = NewNode(data);
				q = temp;
				return true;
			}else{
				q = q->lchild;
			}
		}else if(q->data < data){
			if(q->rchild == NULL){
				q->rchild = NewNode(data);
				q = temp;
				return true;
			}else{
				q = q->rchild;
			}
		}else if(q->data == data){
			q = temp;
			return false;
		}
	}
	q = NewNode(data);
	return true;
}

BSTNode *BSTCreat(int arr[],int n){
	BSTree T = NULL;
	for(int count=0;count<n;count++)
		printf("Insert %d - (%d)\n",arr[count],BSTInsert(T,arr[count]));
	//printf("%d\n",T==NULL);
	return T;
}

int main(){
	// 二叉排序树的构建
	printf("二叉排序树的构建\n");
	//BSTree T = TestInit();
	int num[] = {19,13,50,11,26,66,21,30,60,70};
	BSTree T = BSTCreat(num,int(sizeof(num)/sizeof(num[0])));
	printf("\n初始化:\n"
		"      A-19\n"
		"     /    \\\n"
		"    B-13  C-50\n"
		"   /     /    \\\n"
		"  D-11  E-26   F-66\n"
		"       / \\     /  \\\n"
		"   G-21 H-30  I-60 J-70\n");

	// 寻找值为n的结点
	printf("\n寻找值为n的结点\n");
	printf("60是否存在:%d\n",BSTSearch(T,60)!=NULL);
	BSTSearch(T,60);
	printf("71是否存在:%d\n",BSTSearch(T,71)!=NULL);
	BSTSearch(T,60);
	printf("26是否存在:%d\n",BSTSearch(T,26)!=NULL);

	// 插入结点
	printf("\n插入结点\n");
	printf("插入71:");
	BSTInsert(T,71);
	printf("\n插入31:");
	BSTInsert(T,31);
	printf("\n      A-19\n"
		"     /    \\\n"
		"    B-13  C-50\n"
		"   /     /    \\\n"
		"  D-11  E-26   F-66\n"
		"       / \\     /  \\\n"
		"   G-21 H-30  I-60 J-70\n"
		"           \\        \\\n"
		"           K-31     L-71\n");

	DeleteTree(T);

	return 0;
}