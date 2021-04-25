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

// 本函数为了测试功能 - 采取节点后插入(从小到大)
bool GenerateList2(LinkList &L,int from, int to){
	LNode *p = L;
	if(from>=to){
		printf("Wrong!");
		return false;
	}
	//for(int i=0;i<11;i++){
	for(int i=from;i<to;i++){
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

// 第九题
/* 给定一个带表头节点的单链表, 设head为头节点, 节点结构为(data, next), data
 为整形元素, next为指针, 试写出算法: 按递增次序输出单链表个节点的数据元素, 并释放
 节点所占空间(要求: 不允许使用数组作为辅助空间)*/
bool DeleteAllMax(LinkList &L){
	if(L->next == NULL)
		return false;
	LNode *q, *p = L;
	LNode *s,*d; //s - save(保存下来最大点前边的那个节点), d - delete(要删除的节点)
	int max;
	while(p->next!=NULL){
		q = L;
		max = p->next->data;
		s = q;
		// 找到max
		while(q->next!=NULL){
			if(p->next->data > max){
				s = q;
				max = p->next->data;
			}
			q = q->next;
		}
		// 删除s
		d = s->next;
		printf("%d ", d->data);
		s->next = s->next->next;
		free(d);
	}
	printf("\n");
	return true;
}

// 第十题
/* 讲一个带有头节点的单链表A分解为两个带有头节点的单链表A,B.
 使得A中含有元表中的序号为偶数的元素, B是奇数的部分, 且保持其相对顺序不变. */
bool DivideToTwo(LinkList L, LinkList &Lo, LinkList &Le){
	if(L->next==NULL)
		return false;
	LNode *p,*s;
	int count;
	LinkList q1=Lo,q2=Le;

	for(p=L,count=1;p->next!=NULL;count++,p=p->next){
		if(count%2==1){
			// 奇数
			s = (LNode*)malloc(sizeof(LNode));
			if(s==NULL)return false;
			s->data = p->next->data;
			s->next = NULL;
			q1->next = s;
			q1 = q1->next;
		}else{
			// 偶数
			s = (LNode*)malloc(sizeof(LNode));
			if(s==NULL)return false;
			s->data = p->next->data;
			s->next = NULL;
			q2->next = s;
			q2 = q2->next;
		}
	}
	return true;
}

// 第11题
/* 设C={a1,b1,a2,b2,...an,bn}为线性表, 采用带头节点的hc单链表存放, 设计一个就地算法
 将其拆分为两个链表, A={a1,b2,c1,...} B={bn,...,b2,b1} */
bool DivideToTwoInverse(LinkList L, LinkList &Lo, LinkList &Le){
	if(L->next==NULL)
		return false;
	// 用来存放生成两个新链表
	LNode *p1=Lo,*p2=Le;
	// 用于生成新节点
	LNode *s;
	// 用于遍历老表
	LNode *q=L;
	int count = 1;
	while(q->next!=NULL){
		if(count%2 == 0){
			// 偶数 - 头插
			s = (LNode*)malloc(sizeof(LNode));
			if(s==NULL)
				return false;
			s->next = p2->next;
			s->data = q->next->data;

			p2->next = s;
		}else{
			// 奇数 - 尾插
			s = (LNode*)malloc(sizeof(LNode));
			if(s==NULL)
				return false;
			s->next = NULL;
			s->data = q->next->data;

			p1->next = s;
			p1 = p1->next;
		}
		q = q->next;
		count++;
	}

	return true;
}

// 第12题
/*有序递增单链表, 有数值相同的元素存在, 若储存方式为单链表, 设计算法去掉数值相同的元素,
 是表中不再有重复的元素, 例如(7,10,10,21,30,43,43,43,51,70)->(7,10,21,30,42,51,70)*/
bool DeleteDouble(LinkList &L){
	if(L->next==NULL)
		return false;
	LNode* p=L,*s;
	while(p->next!=NULL){
		if(p->next->next==NULL)
			break;
		if(p->next->data == p->next->next->data){
			s = p->next;
			p->next = s->next;
			free(s);
		}
		p = p->next;
	}
	return true;
}

// 第13题
/* 假设有两个按元素递增次序排列的单链表, 编写算法, 将两个单链表归并成
 递减的单链表. 并要求利用原来的两个单链表的节点存放归并后的单链表. */
bool MergeAndReverse(LinkList &L1, LinkList &L2){
	// 123456
	// 23456789
	if(L1->next==NULL||L2->next==NULL)
		return false;
	LNode *p = L1;
	LNode *q = L2;
	LNode *s = (LNode*)malloc(sizeof(LNode));
	LNode *t;
	if(s==NULL)return false;
	s->next=NULL;
	
	// 两个表都有内容
	while(p->next!=NULL && q->next!=NULL){
		if(p->next->data <= q->next->data){
			printf("%d ",p->next->data);
			// 将节点释放出来 保存为t(temp)
			t = p->next;
			p->next = t->next;
			// 把t插到s中
			t->next = s->next;
			s->next = t;
		}else{
			printf("%d ",q->next->data);
			// 将节点释放出来 保存为t(temp)
			t = q->next;
			q->next = t->next;
			// 把t插到s中
			t->next = s->next;
			s->next = t;
		}
	}
	// 某一个表有剩余
	while(p->next!=NULL){
		printf("%d ",p->next->data);
		// 将节点释放出来 保存为t(temp)
		t = p->next;
		p->next = t->next;
		// 把t插到s中
		t->next = s->next;
		s->next = t;
	}
	while(q->next!=NULL){
		printf("%d ",q->next->data);
		// 将节点释放出来 保存为t(temp)
		t = q->next;
		q->next = t->next;
		// 把t插到s中
		t->next = s->next;
		s->next = t;
	}

	L1->next = s->next;
	L2->next = s->next;
	printf("\n");
	free(s);
	return true;
}

// 第14题
/* 两个带头节点的递增单链表, 设计算法用公共元素生成L, 不能破坏原链表*/
bool MergeSame(LinkList A, LinkList B, LinkList &L){
	if(A->next==NULL || B->next==NULL || L->next!=NULL)
		return false;
	LNode* p=A,*q=B,*s;
	int last=-1;
	while(q->next!=NULL && p->next!=NULL){
		if(p->next->data < q->next->data){
			if(last==p->next->data){
				s = (LNode*)malloc(sizeof(LNode));
				if(s==NULL)return false;
				s->next = L->next;
				s->data = p->next->data;
				L->next = s;
			}
			last = p->next->data;
			p = p->next;
		}else{
			if(last==q->next->data){
				s = (LNode*)malloc(sizeof(LNode));
				if(s==NULL)return false;
				s->next = L->next;
				s->data = q->next->data;
				L->next = s;
			}
			last = q->next->data;
			q = q->next;
		}
	}
	while(q->next!=NULL){
		if(last==q->next->data){
			LNode *s = (LNode*)malloc(sizeof(LNode));
			if(s==NULL)return false;
			s->next = L->next;
			s->data = q->next->data;
			L->next = s;
		}
		last = q->next->data;
		q = q->next;
	}
	while(p->next!=NULL){
		if(last==p->next->data){
			LNode *s = (LNode*)malloc(sizeof(LNode));
			if(s==NULL)return false;
			s->next = L->next;
			s->data = p->next->data;
			L->next = s;
		}
		last = p->next->data;
		p = p->next;
	}
	return true;
}

// 第15题
/* 两个带头节点的递增单链表, 设计算法用AB交集生成L, 并安放于A*/
bool MergeSameToA(LinkList &A, LinkList B){
	if(A->next==NULL || B->next==NULL)
		return false;

	LNode *p=A, *q=B, *s;
	int last;
	if(A->next->data < B->next->data)
		last = A->next->data-1;
	else
		last = B->next->data-1;

	// 3 4
	// 3 4
	while(p->next!=NULL && q->next!=NULL){
		if(p->next->data < q->next->data){
			if(last != p->next->data){
				last = p->next->data;
				s = p->next;
				p->next = s->next;
				free(s);
			}else{
				last = p->next->data;
				p = p->next;
			}
		}
		else{
			if(last == q->next->data){
				s = (LNode*)malloc(sizeof(LNode));
				if(s==NULL)return false;
				s->next = NULL;
				s->data = q->next->data;
				p->next = s;
				p = p->next;
			}else
				last = q->next->data;
			q = q->next;
		}
	}

	while(p->next!=NULL){
		if(last != p->next->data){
			last = p->next->data;
			s = p->next;
			p->next = s->next;
			free(s);
		}else{
			last = p->next->data;
			p = p->next;
		}
	}
	while(q->next!=NULL){
		if(last == q->next->data){
			s = (LNode*)malloc(sizeof(LNode));
			if(s==NULL)return false;
			s->next = NULL;
			s->data = q->next->data;
			p->next = s;
			p = p->next;
		}else
			last = q->next->data;
		q = q->next;
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
	DeleteAllMax(L9);
	PrintList(L9);
	DeleteNode(L9,false);

	// 第十题
	printf("\n第十题\n");
	LinkList L10;
	InitListNH(L10);
	LinkList L10_1;
	InitListNH(L10_1);
	LinkList L10_2;
	InitListNH(L10_2);
	GenerateList(L10);
	PrintList(L10);
	DivideToTwo(L10,L10_1,L10_2);
	PrintList(L10);
	PrintList(L10_1);
	PrintList(L10_2);
	DeleteNode(L10,false);
	DeleteNode(L10_1,false);
	DeleteNode(L10_2,false);

	// 第11题
	printf("\n第十一题\n");
	LinkList L11;
	InitListNH(L11);
	LinkList L11_1;
	InitListNH(L11_1);
	LinkList L11_2;
	InitListNH(L11_2);
	GenerateList(L11);
	PrintList(L11);
	DivideToTwoInverse(L11,L11_1,L11_2);
	PrintList(L11);
	PrintList(L11_1);
	PrintList(L11_2);
	DeleteNode(L11,false);
	DeleteNode(L11_1,false);
	DeleteNode(L11_2,false);

	// 第12题
	printf("\n\n第12题\n");
	LinkList L12;
	InitListNH(L12);
	GenerateList(L12);
	L12->next->next->data = L12->next->data;
	PrintList(L12);
	DeleteDouble(L12);
	PrintList(L12);
	DeleteNode(L12,false);

	// 第13题
	printf("\n\n第13题\n");
	LinkList L13_1;
	InitListNH(L13_1);
	GenerateList2(L13_1,1,10);
	PrintList(L13_1);
	LinkList L13_2;
	InitListNH(L13_2);
	GenerateList2(L13_2,5,15);
	PrintList(L13_2);
	MergeAndReverse(L13_1,L13_2);
	PrintList(L13_1);
	DeleteNode(L13_1,false);
	//DeleteNode(L13_2,false);

	// 第14题
	printf("\n\n第14题\n");
	LinkList L14_1;
	InitListNH(L14_1);
	GenerateList2(L14_1,1,10);
	PrintList(L14_1);
	LinkList L14_2;
	InitListNH(L14_2);
	GenerateList2(L14_2,5,15);
	PrintList(L14_2);
	LinkList L14_3;
	InitListNH(L14_3);
	MergeSame(L14_1,L14_2,L14_3);
	PrintList(L14_3);
	DeleteNode(L14_1,false);
	DeleteNode(L14_2,false);
	DeleteNode(L14_3,false);

	// 第15题
	printf("\n\n第15题\n");
	LinkList L15_1;
	InitListNH(L15_1);
	GenerateList2(L15_1,5,15);
	PrintList(L15_1);
	LinkList L15_2;
	InitListNH(L15_2);
	GenerateList2(L15_2,1,10);
	PrintList(L15_2);
	MergeSameToA(L15_1,L15_2);
	PrintList(L15_1);
	DeleteNode(L15_1,false);
	DeleteNode(L15_2,false);

	// 第16题
	return 0;
}


