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
	// 判空
	if(L1->next==NULL)
		return false;
	// 采用头插法, 将链表逆置
	// L2 - p
	LNode* L2 = (LNode*)malloc(sizeof(LNode));
	if(L2==NULL)
		return false;
	LNode* p;
	// s 来删除
	LNode* s = NULL;
	while(L1->next!=NULL){
		// 赋值给新节点 - p
		//printf("-%d ",L1->next->data);
		p = (LNode*)malloc(sizeof(LNode));
		if(p==NULL)
			return false;
		p->data = L1->next->data;
		p->next = L2->next;
		L2->next = p;
		// 删除老节点
		s = L1->next;
		if(s->next!=NULL){
			L1->next = s->next;
		}else{
			L1->next = NULL;
		}
		free(s);
	}
	// 重新赋值
	L1->next = L2->next;
	free(L2);

	return true;
}

// 第六题
/* 有一个带有头节点的单链表L, 设计一个算法使其元素递增有序 */
bool AddSort(LinkList &L){
	// 判空或就一个元素
	if(L->next==NULL||L->next->next==NULL)
		return false;
	// 递增 - 第一轮
	// * -> * -> * -> * 
	LNode *p = L;
	int temp,count=0,in_count=0;
	while(p->next->next!=NULL){
		if(p->next->data > p->next->next->data){
			temp = p->next->next->data;
			p->next->next->data = p->next->data;
			p->next->data = temp;
		}
		p = p->next;
		count++;
	}
	for(int i=count; i>0; i--){
		p = L;
		in_count = i;
		while(in_count){
			if(p->next->data > p->next->next->data){
				temp = p->next->next->data;
				p->next->next->data = p->next->data;
				p->next->data = temp;
			}
			p = p->next;
			in_count--;
		}
	}
	return true;
}

// 第七题
/* 设在一个带表头节点的单链表中所有元素节点的数据之无序, 试编写一个函数,
 删除表中所有介于给定的两个值(只为函数参数给出)之间的元素的元素(若存在). */
bool DeleteInXY(LinkList &L,int min,int max){
	if(min>=max)
		return false;
	if(L->next==NULL)
		return false;
	// 开始删除!
	LNode *s, *p=L;
	while(p->next!=NULL){
		if(p->next->data > min && p->next->data < max){
			s = p->next;
			p->next = p->next->next;
			free(s);
		}else{
			p = p->next;
		}
	}
	return false;
}

// 第八题
/* 给定两个单链表, 编写算法找出两个链表的公共个节点 */
// (L1)*-*-*-*-*-*-*-*-*
//     (L2)*-*-*-*/
bool FindSharedNode(LinkList L1, LinkList L2, LNode* public_){
	// 先看是否有公共节点 - 分别计算两个长度
	if(L1->next==NULL || L2->next==NULL)
		return false;
	int len1 = 0,len2 = 0;
	LNode *p = L1, *q = L2;
	for(len1=0; p->next!=NULL; len1++,p=p->next);
	for(len2=0; q->next!=NULL; len2++,q=q->next);
	printf("%d %d",len1,len2);
	if(len1 == len2 && p != q)
		return false;
	// 有公共节点的情况
	// Step1 - 先对其两链表
	p = L1, q = L2;
	int count = 0;
	if(len1 > len2){
		for(int i=0;i<len1-len2;i++)
			p=p->next;
		count = len1 - len2;
	}
	else{
		for(int i=0;i<len1-len2;i++)
			q=q->next;
		count = len2 - len1;
	}
	// Step2 - 从对齐处开始寻找
	for(int i=count; i>0; i--){
		if(q->next == p->next && q->next!=NULL)
			public_ = p->next;
		else{
			p = p->next;
			q = q->next;
		}
	}
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
	Inverse(L5);
	PrintList(L5);
	DeleteNode(L5,false);

	// 第六题
	printf("\n\n第六题\n");
	LinkList L6;
	InitListNH(L6);
	GenerateList(L6);
	PrintList(L6);
	AddSort(L6);
	PrintList(L6);
	DeleteNode(L6,false);

	// 第七题
	printf("\n\n第七题\n");
	LinkList L7;
	InitListNH(L7);
	GenerateList(L7);
	PrintList(L7);
	DeleteInXY(L7,3,7);
	PrintList(L7);
	DeleteNode(L7,false);

	// 第八题
	printf("\n\n第八题\n");
	LinkList L8_1,L8_2,L8_3;
	InitListNH(L8_1);
	InitListNH(L8_2);
	GenerateList(L8_1);
	GenerateList(L8_2);
	FindSharedNode(L8_1,L8_2,L8_3);
	DeleteNode(L8_1,false);
	DeleteNode(L8_2,false);

	// 第九题
	printf("\n\n第九题\n");
	LinkList L9;
	InitListNH(L9);
	GenerateList(L9);
	PrintList(L9);
	DeleteInXY(L9,3,7);
	PrintList(L9);
	DeleteNode(L9,false);

	return 0;
}


