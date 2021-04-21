#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*LinkList;

// 不带头节点
bool InitListNH(LinkList &L){
	L = (LNode*)malloc(sizeof(LNode));
	if(!L)
		return false;
	L->next = NULL;
	return true;
}

// 带头节点
bool InitListH(LinkList &L){
	L = (LNode*)malloc(sizeof(LNode));
	if(!L)
		return false;
	L->next = (LNode*)malloc(sizeof(LNode));
	if(!L->next)
		return false;
	L->next->next = NULL;
	return true;
}

// 本函数为了测试功能 - 采取节点后插入
bool GenerateList(LinkList &L){
	LNode *p = L;
	//for(int i=0;i<11;i++){
	for(int i=11;i>0;i--){
		LNode *s = (LNode*)malloc(sizeof(LNode));
		if(!s)
			return false;
		s->next=NULL;
		s->data = i;
		p->next = s;
		p = p->next;
	}
	return true;
}

// 输出操作本函数为了测试功能
bool PrintList(LinkList L){
	printf("PrintList: ");
	LNode* p = L->next;
	if(p==NULL){
		printf("\n");
		return false;
	}
	do{
		printf("%d ",p->data);
		p = p->next;
	}while(p!=NULL);
	printf("\n");
	return true;
}

// 第一题
/* 设计一个递归算法, 删除不带头节点, 并释放其空间, 
 假设值为x的节点不唯一 */
bool DeleteNode(LinkList &L,bool log){
	if(L->next!=NULL){
		// 有下一个节点
		DeleteNode(L->next,log);
		// 现在无下一个节点了
		if(log) printf("free - %d\n",L->data);
		free(L);
	}else{
		// 无下一个节点
		if(log) printf("free - %d\n",L->data);
		free(L);
	}
	return true;
}

// 第二题
/* 在带头节点的单链表L中,删除所有值为x的节点, 并释放其空间.(节点不唯一) */
bool DeleteX(LinkList &L, int x){
	printf("delete %d\n",x);
	LNode* p = L;
	while(p->next!=NULL){
		// p [q] ...
		LNode* q = p->next;
		if(q->data == x){
			// 删除
			if(q->next!=NULL)
				p->next = q->next;
			else
				p->next = NULL;
			free(q);
		}else{
			// 跳过
			p = p->next;
		}
	}
	return true;
}

// 第三题
/* 设L为带头节点的单链表, 编写算法实现从尾到头反向输出那个节点的值. */
bool InverseOutput(LinkList L, bool head){
	if(head){
		if(L->next==NULL)
			return false;
		L = L->next;
	}
	if(L->next==NULL){
		printf("反向输出链表值\n");
		printf("%d ",L->data);
	}
	else{
		InverseOutput(L->next,false);
		printf("%d ",L->data);
	}
	return true;
}

// 第四题
/* 编写带头节点的单链表, 删除最小值节点的高效算法, 最小值唯一 */
bool DeleteMin(LinkList &L){
	// 空表
	if(L->next==NULL)
		return false;
	// 寻找min
	// p -> s -> q
	int min = L->next->data;
	LNode *p,*s,*p_s,*s_s;
	p = L;
	p_s = L;
	s = p->next;
	s_s = p->next;
	while(s != NULL){
		if(s->data < min){
			min = s->data;
			p_s = p;
			s_s = s;
		}
		p = p->next;
		s = s->next;
	}
	// 删除
	if(p_s->next!=NULL){
		p_s->next = s_s->next;
	}
	free(s_s);

	return true;
}

// 第五题
/* 编写在头节点的单链表就地逆置, 所谓“就地”是指是指辅助空间复杂度为O(1) */
bool Inverse(LinkList &L1){
	if(L1->next==NULL)
		return false;
	// 采用头插法, 将链表逆置
	// L1 - q
	LNode* q = L1;
	// L2 - p
	LNode* L2 = L1;
	LNode* p = L2;
	// s 来删除
	LNode* s;
	while(q->next != NULL){
		// 赋值
		printf("%d ",q->data);
		p->next = q->next;
		p->data = q->data;
		// 删除本节点并迭代
		s = p->next;
		p = p->next;
		q = q->next;
		free(s);
	}
	L1 = L2;
	return true;
}

int main(){

	// 第一题
	printf("\n第一题\n");
	LinkList L1;
	InitListNH(L1);
	GenerateList(L1);
	PrintList(L1);
	DeleteNode(L1,true);

	// 第二题
	printf("\n第二题\n");
	LinkList L2;
	InitListNH(L2);
	GenerateList(L2);
	PrintList(L2);
	DeleteX(L2,10);
	DeleteX(L2,5);
	PrintList(L2);
	DeleteNode(L2,false);

	// 第三题
	printf("\n第三题\n");
	LinkList L3;
	InitListNH(L3);
	GenerateList(L3);
	PrintList(L3);
	InverseOutput(L3,true);
	DeleteNode(L3,false);

	// 第四题
	printf("\n\n第四题\n");
	LinkList L4;
	InitListNH(L4);
	GenerateList(L4);
	//L4->next->next->next->data = 0;
	PrintList(L4);
	DeleteMin(L4);
	PrintList(L4);
	DeleteNode(L4,false);

	// 第五题
	printf("\n\n第五题\n");
	LinkList L5;
	InitListNH(L5);
	GenerateList(L5);
	PrintList(L5);
	DeleteNode(L5,false);
	PrintList(L5);

	// 
}


