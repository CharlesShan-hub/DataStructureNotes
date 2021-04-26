#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LNode{
	int data;
	struct LNode *next;
}LNode,*LinkList;

typedef struct RDLNode{ // rotate double LNode
	int data;
	struct RDLNode *next,*last;
}RDLNode,*RDLinkList;

typedef struct RLNode{ // 循环单链表
	int data;
	struct RLNode *next;
}RLNode,*RLinkList;

// 不带头节点
bool InitListNH(LinkList &L){ // NH - none head
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

bool RDPrintList(RDLinkList L){
	printf("PrintList: ");
	RDLNode* p = L;
	// 空
	if(p->next==L){
		printf("\n");
		return false;
	}
	// 打印
	while(p->next!=L){
		printf("%d ",p->next->data);
		p = p->next;
	}
	printf("\n");
	return true;
}

bool RPrintList(RLinkList L){
	printf("PrintList: ");
	RLNode* p = L;
	// 空
	if(p->next==L){
		printf("\n");
		return false;
	}
	// 打印
	while(p->next!=L){
		printf("%d ",p->next->data);
		p = p->next;
	}
	printf("\n");
	return true;
}

// 循环双链表的初始化
bool RDInitListH(RDLinkList &L){
	// 头节点
	L = (RDLNode*)malloc(sizeof(RDLNode));
	if(L==NULL)return false;
	L->next = L;
	L->last = L;
	return true;
}

// 循环单链表的初始化
bool RInitListH(RLinkList &L){
	// 头节点
	L = (RLNode*)malloc(sizeof(RLNode));
	if(L==NULL)return false;
	L->next = L;
	return true;
}

// 本函数为了测试功能 - 采取节点后插入(从小到大)
bool RDGenerateList(RDLinkList &L,int from, int to){
	RDLNode *p = L;
	if(from>=to){
		printf("Wrong!");
		return false;
	}
	for(int i=to;i>from;i--){
		// 创造节点s
		RDLNode *s = (RDLNode*)malloc(sizeof(RDLNode));
		if(!s)
			return false;
		s->next=L->next;
		s->data = i-1;
		s->last=L;
		// s插入
		s->next->last = s;
		p->next=s;
	}
	return true;
}

// 本函数为了测试功能 - 采取节点后插入(从大到小)
bool RDGenerateList2(RDLinkList &L,int from, int to){
	RDLNode *p = L;
	if(from<=to){
		printf("Wrong!");
		return false;
	}
	for(int i=to;i<from;i++){
		// 创造节点s
		RDLNode *s = (RDLNode*)malloc(sizeof(RDLNode));
		if(!s)
			return false;
		s->next=L->next;
		s->data = i+1;
		s->last=L;
		// s插入
		s->next->last = s;
		p->next=s;
	}
	return true;
}

// 本函数为了测试功能 - 采取节点后插入(从小到大)
bool RGenerateList(RLinkList &L,int from, int to){
	RLNode *p = L;
	if(from>=to){
		printf("Wrong!");
		return false;
	}
	for(int i=to;i>from;i--){
		// 创造节点s
		RLNode *s = (RLNode*)malloc(sizeof(RLNode));
		if(!s)
			return false;
		s->next=L->next;
		s->data = i-1;
		// s插入
		p->next=s;
	}
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

// 删除循环双链表
bool RDDelete(RDLinkList &L){
	RDLNode *s;
	while(L->next!=L){
		s = L->next;
		L->next = s->next;
		free(s);
	}
	return true;
}

bool RDelete(RLinkList &L){
	RLNode *s;
	while(L->next!=L){
		s = L->next;
		L->next = s->next;
		free(s);
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

// 第16题
/* 两个整数序列A=a1,a2,a3...,am. B=b1,b2,...,bn 已经存入两个单链表中,
 设计一个算法,判断序列B是否是A的连续子序列.*/
bool IsChild(LinkList A, LinkList B){
	if(A->next==NULL || B->next==NULL)
		return false;
	LNode *p = A;
	LNode *q = B;
	while(p->next!=NULL && q->next!=NULL){
		if(p->next->data == q->next->data)
			q = q->next;
		else
			q = B;
		p = p->next;
	}
	if(q->next==NULL)
		return true;
	else
		return false;
}

// 第17题
/* 设计一个算法用于判断带头节点的循环双链表是否对称 */
bool IsSymmetry(RDLinkList L){
	// 1 2 3 4 5 4 3 2 1
	// 1 2 3 4 5 5 4 3 2 1
	RDLNode *p=L,*q=L;
	while(p->next!=L){
		if(p->next->data != q->last->data)
			return false;
		p = p->next;
		q = q->last;
	}
	return true;
}

// 第18题
/* 两个循环单链表, 链表头指针分别为h1,h2, 编写函数将链表2连接到链表h1之后, 
 要求连接后的链表人保持循环链表的形式 */
bool RMerge(RLinkList &h1, RLinkList &h2){
	RLNode *q = h1;
	RLNode *p = h2;
	RLNode *s=NULL;
	// 找到h1最后一项
	while(q->next!=h1)
		q = q->next;
	q->next = h2->next;
	// 把h2连进去
	while(p->next!=h2)
		p = p->next;
	p->next = h1;
	free(h2);
	return true;
}

// 第19题
/* 设有一个带头节点的循环单链表, 其节点值均为正整数, 设计一个算法, 反
 复找出单链表中的节点值最小的节点并输出. 然后将该节点从中删除. 直到单链表空为止. 
 在删除表头节点.*/
bool RDeleteAllMax(RLinkList &L){
	if(L->next == L)
		return false;
	RLNode *p=L;
	RLNode *s=L;
	RLNode *d=L;
	int max_ = L->next->data;
	// 不停地删除
	while(L->next!=L){
		// 初始化
		p=L;
		s=L;
		max_ = L->next->data;
		// 找到最大节点
		while(p->next!=L){
			if(p->next->data >= max_){
				s = p;
				max_ = p->next->data;
			}
			p = p->next;
		}
		// 删除最大节点
		d = s->next;
		s->next = d->next;
		printf("%d ",d->data);
		free(d);
	}
	// 删除头节点
	free(L);
	return true;
}

// 第20题
/* 设头指针为L的带有表头节点的非循环双向链表, 其每个节点中除有pred(前驱),data(数据),next(后继)
 还有一个频度域freq. 在链表被启用前, 其值初始化为0. 链表中进行一次Locate(L,x)运算时,
 另元素职位x的节点中freq域的值+1. 并使此链表中节点保持按访问频度递减顺序排列. 
 同时最近访问的节点排在频度相同的节点前边. 编写符合要求的Loacte(L,x), 返回找到的节点地址,类型为指针.*/
typedef struct LNode20
{
	int data;
	int freq;
	LNode20* pred;
	LNode20* next;
}*LinkList20,LNode20;

bool InitLinkList20(LinkList20 &L){
	L = (LNode20*)malloc(sizeof(LNode20));
	if(L==NULL) return false;
	L->next = NULL;
	L->pred = NULL;
	//L->data = 0;
	//L->freq = 0;
	return true;
}

bool GenerateList20(LinkList20 &L, int from, int to, int step){
	if(from==to || step<=0)return false;
	int i = from;
	LNode20 *s;
	while(1){
		// 判断条件
		if(from < to){
			if(i>=to)
				break;
		}
		else{
			if(i<=to)
				break;
		}
		// 创造节点s
		s = (LNode20*)malloc(sizeof(LNode20));
		if(s==NULL)return false;
		s->data = i;
		s->freq = 0;
		s->next = L->next;
		s->pred = L;
		// 添加节点
		if(s->next!=NULL)
			s->next->pred = s;
		s->pred->next = s;
		// 迭代
		if(from < to)
			i += step;
		else
			i -= step;
	}
	return true;
}

bool PrintList20(LinkList20 L){
	LNode20 *p = L;
	while(p->next!=NULL){
		printf("%d(%d) ",p->next->data,p->next->freq);
		p = p->next;
	}
	printf("\n");
	return true;
}

bool Destroy20(LinkList20 &L){
	LNode20 *s;
	while(L->next!=NULL){
		s = L->next;
		L->next = s->next;
		free(s);
	}
	free(L);
	return true;
}

LNode20* Locate(LinkList20 &L, int x){
	LNode20 *p=L;
	LNode20 *s;
	// 首先找到寻找的节点 data = x
	while(p->next!=NULL){
		if(p->next->data == x){
			s = p->next;
			break;
		}else{
			p = p->next;
		}
	}
	// 进行频度调整
	s->freq += 1;
	p = s;
	if(L->next == s){
		printf("已经在开头");
		return s;
	}
	L->freq = s->freq+1;
	while(p!=L){
		if(p->pred->freq > s->freq){
			// 先把原来的s摘下来
			if(s->next!=NULL)
				s->next->pred = s->pred;
			s->pred->next = s->next;
			// 再把s放到算好的位置
			s->next = p;
			s->pred = p->pred;
			s->next->pred = s;
			s->pred->next = s;
			break;
		}
		p = p->pred;
	}
	L->freq = 0;
	return s;
}

// 第21题
/* 已知一个带有表头节点的单链表, 节点结构为[data,link]
 假设该链表只给出了头指针list, 在不改变链表的前提下,
 请设计一个尽可能高效的算法, 查找链表中倒数第k个位置上的节点(k为正整数).
 查找成功, 算法输出该节点的data域值, 并返回1, 失败返回0 */
// 下面是答案方法!!! - 最优解法
// 给定p,q初始值都是L
// p向右移动k
// q,p一起移动直到p到头, q就是-k
int LocateInverseK(LinkList L,int k){
	if(L->next==NULL || k<=0)return 0;
	LNode *p=L,*q=L;
	for(int i=1;i<k;i++){
		if(p->next==NULL)return 0;
		p = p->next;
	}
	while(p->next!=NULL){
		p = p->next;
		q = q->next;
	}
	printf("The -%d_th is %d\n",k,q->data);
	return 1;
}

// 第22题
/* 假定采用带头节点的单链表保存单词, 当两个单词由相同后缀时,
 可共享相同后缀的储存空间, 例如“loading”和“being” .
 设str1和str2分指向两个单词所在单链表的头节点. 设计一个尽量高效的算法,
 找出str1和str2所指向的两个链表共同后缀的起始位置(例如上边i的位置)*/
// L1和L2是已经合并完的, 题目让找出合并点
typedef struct LNode22
{
	char data;
	struct LNode22* next; 
}LNode22,*LinkList22;

bool GenerateList22(LinkList22 &L1,LinkList22 &L2){
	// L1 - leading
	L1 = (LNode22*)malloc(sizeof(LNode22));
	L1->next = (LNode22*)malloc(sizeof(LNode22));
	L1->next->data = 'l';
	L1->next->next = (LNode22*)malloc(sizeof(LNode22));
	L1->next->next->data = 'e';
	L1->next->next->next = (LNode22*)malloc(sizeof(LNode22));
	L1->next->next->next->data = 'a';
	L1->next->next->next->next = (LNode22*)malloc(sizeof(LNode22));
	L1->next->next->next->next->data = 'd';
	L1->next->next->next->next->next = (LNode22*)malloc(sizeof(LNode22));
	L1->next->next->next->next->next->data = 'i';
	L1->next->next->next->next->next->next = (LNode22*)malloc(sizeof(LNode22));
	L1->next->next->next->next->next->next->data = 'n';
	L1->next->next->next->next->next->next->next = (LNode22*)malloc(sizeof(LNode22));
	L1->next->next->next->next->next->next->next->data = 'g';
	L1->next->next->next->next->next->next->next->next = NULL;

	// L2 - learning
	L2 = (LNode22*)malloc(sizeof(LNode22));
	L2->next = (LNode22*)malloc(sizeof(LNode22));
	L2->next->data = 'l';
	L2->next->next = (LNode22*)malloc(sizeof(LNode22));
	L2->next->next->data = 'e';
	L2->next->next->next = (LNode22*)malloc(sizeof(LNode22));
	L2->next->next->next->data = 'a';
	L2->next->next->next->next = (LNode22*)malloc(sizeof(LNode22));
	L2->next->next->next->next->data = 'r';
	L2->next->next->next->next->next = (LNode22*)malloc(sizeof(LNode22));
	L2->next->next->next->next->next->data = 'n';
	L2->next->next->next->next->next->next = L1->next->next->next->next->next;

	return true;
}

void PrintList22(LinkList22 L){
	LNode22 *p = L;
	while(p->next!=NULL){
		printf("%c",p->next->data);
		p = p->next;
	}
}

int Length22(LinkList22 L){
	int length = 0;
	LNode22 *p = L;
	while(p->next!=NULL){
		length++;
		p = p->next;
	}
	return length;
}

int FindSuffixSubscript(LinkList22 L1, LinkList22 L2){
	int sub=0;
	int len1 = Length22(L1);
	int len2 = Length22(L2);
	LNode22 *p = L1;
	LNode22 *q = L2;
	// 使两个表对齐
	if(len1>len2)
		for(int i=0;i<len1 - len2;i++,sub++)
			p = p->next;
	else
		for(int i=0;i<len2-len1;i++,sub++)
			q = q->next;
	// 找到公共节点
	while(p->next!=NULL){
		if(p->next==q->next){
			break;
		}
		sub++;
		p = p->next;
		q = q->next;
	}
	return sub;
}

// 第23题(2005统考真题)
/* 用单链表保存m个整数, 节点的结构为[data][next],|data|≤n,
 (n为正整数),先要求设计一个时间复杂度尽可能高效的算法, 对于链表中data
 的绝对值相等的节点, 仅保留第一次出现的节点而删除其余绝对值相等的节点.
 例如:[head,21,-15,15,-15,-7,15]->[head,21,-15,-7]*/
int abs(int x){
	return x*(x>0?1:-1);
}
// 我的算法
// 时间复杂度为n^2
bool DeleteAllDouble1(LinkList &L){
	LNode *s,*p=L,*q,*d,*a;
	int flag=0;
	s = (LNode*)malloc(sizeof(LNode));
	if(s==NULL)return false;
	s->next = NULL;
	while(p->next!=NULL){
		// 寻找相等
		for(q=s,flag=0;q->next!=NULL;q=q->next)
			if(abs(p->next->data)==q->next->data){
				flag=1;
				break;
			}
		// 找到相等的情况 - 删除
		if(flag){
			d = p->next;
			p->next = d->next;
			free(d);
		}else{
		// 没找到相等的情况 - 跳过
			a = (LNode*)malloc(sizeof(LNode));
			if(a==NULL)return false;
			a->next = s->next;
			a->data = abs(p->next->data);
			s->next = a;
			p = p->next;
		}
	}
	return true;
}

// 答案算法 时间复杂度 - O(n)
bool DeleteAllDouble2(LinkList &L, int n){
	LNode *p=L,*d;
	int s[n+1];
	for(int i=0; i<n+1; i++){
		s[i]=0;
	}
	while(p->next!=NULL){
		// 找到相等的情况 - 删除
		if(s[abs(p->next->data)]){
			d = p->next;
			p->next = d->next;
			free(d);
		}else{
		// 没找到相等的情况 - 跳过
			s[abs(p->next->data)]=1;
			p = p->next;
		}
	}
	return true;
}

// 第24题
/* 设计一个算法, 判断一个链表是否有环, 如果有,找出换的入口点并返回, 否则返回NULL*/
LNode* HasCircle(LinkList L){
	LNode *p=L->next,*q=L;
	while(p->next!=q){
		// 找到了界限
		if(p->next==NULL)
			return NULL;
		// 总有一天可以转过去
		p = p->next;
	}
	return p;
}

// 第25题
/* 带头节点的单链表L, 设计空间复杂度O(1)的算法, 重排L的各个节点, 得到线性表L‘,
 (a1, an, a2, an-1, a3,...) */
bool ReSorting(LinkList &L){
	if(L->next==NULL)
		return false;
	// 1 2 3 4 5 6 7 8 9 10
	// 1 3 5 7 9
	// 10 8 6 4 2
	// 1 10 2 9 3 8 4 7 5 6
	// 构建新链表
	LinkList L1 = (LNode*)malloc(sizeof(LNode));
	LinkList L2 = (LNode*)malloc(sizeof(LNode));
	if(L1==NULL || L2==NULL)return false;
	L1->next=NULL;
	L2->next=NULL;
	LNode *p = L, *l1=L1, *l2=L2,*s;
	int count = 1;
	while(p->next!=NULL){
		s = p->next;
		p->next = s->next;
		if(count%2==1){
			// 奇数 - 后插法
			l1->next=s;
			s->next = NULL;
			l1 = l1->next;
		}else{
			// 偶数 - 前插法
			s->next = l2->next;
			l2->next=s;
		}
		count++;
	}
	// for test
	PrintList(L1);
	PrintList(L2);
	// 合并
	p = L;
	while(L2->next!=NULL){
		// 一奇一偶的插入
		s = L1->next;
		L1->next = s->next;
		s->next = p->next;
		p->next = s;
		p = p->next;

		s = L2->next;
		L2->next = s->next;
		s->next = p->next;
		p->next = s;
		p = p->next;
	}
	if(L1->next!=NULL){
		s = L1->next;
		L1->next = s->next;
		s->next = p->next;
		p->next = s;
		p = p->next;
	}
	free(L1);
	free(L2);

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
	printf("\n\n第16题\n");
	LinkList L16_1;
	InitListNH(L16_1);
	GenerateList2(L16_1,1,16);
	PrintList(L16_1);
	LinkList L16_2;
	InitListNH(L16_2);
	GenerateList2(L16_2,3,10);
	PrintList(L16_2);
	printf("Is child? - %d\n",IsChild(L16_1,L16_2));
	DeleteNode(L16_1,false);
	DeleteNode(L16_2,false);

	// 第17题
	printf("\n\n第17题\n");
	RDLinkList L17;
	RDInitListH(L17);
	RDGenerateList(L17,1,6); // 1-5
	RDGenerateList2(L17,5,0); // 5-1
	RDPrintList(L17); // 5 4 3 2 1 1 2 3 4 5
	printf("Is Symmetry? - %d\n",IsSymmetry(L17));
	RDDelete(L17);
	RDLinkList L17_2;
	RDInitListH(L17_2);
	RDGenerateList(L17_2,1,6); // 1-5
	RDGenerateList2(L17_2,5,1); // 5-2
	RDPrintList(L17_2); // 5 4 3 2 1 2 3 4 5
	printf("Is Symmetry? - %d\n",IsSymmetry(L17_2));
	RDDelete(L17_2);
	RDLinkList L17_3;
	RDInitListH(L17_3);
	RDGenerateList(L17_3,1,6); // 1-5
	RDGenerateList2(L17_3,5,2); // 5-3
	RDPrintList(L17_3); // 5 4 3 1 2 3 4 5
	printf("Is Symmetry? - %d\n",IsSymmetry(L17_3));
	RDDelete(L17_3);

	// 第18题
	printf("\n\n第18题\n");
	RLinkList L18_1;
	RInitListH(L18_1);
	RGenerateList(L18_1,1,6); 
	RPrintList(L18_1);
	RLinkList L18_2;
	RInitListH(L18_2);
	RGenerateList(L18_2,10,15); 
	RPrintList(L18_2); 
	RMerge(L18_1,L18_2);
	RPrintList(L18_1);
	RDelete(L18_1);

	// 第19题
	printf("\n\n第19题\n");
	RLinkList L19;
	RInitListH(L19);
	RGenerateList(L19,4,8); 
	RGenerateList(L19,1,6); 
	RGenerateList(L19,3,9); 
	RPrintList(L19);
	RDeleteAllMax(L19);
	//RDelete(L19);

	// 第20题
	printf("\n\n第20题\n");
	LinkList20 L20;
	InitLinkList20(L20);
	GenerateList20(L20,1,20,2);
	PrintList20(L20);
	printf("Find - %d\n",Locate(L20,5)->data);
	PrintList20(L20);
	printf("Find - %d\n",Locate(L20,5)->data);
	PrintList20(L20);
	printf("Find - %d\n",Locate(L20,7)->data);
	PrintList20(L20);
	Destroy20(L20);

	// 第21题
	printf("\n\n第21题\n");
	LinkList L21;
	InitListNH(L21);
	GenerateList(L21);
	PrintList(L21);
	LocateInverseK(L21,3);
	DeleteNode(L21,false);

	// 第22题
	printf("\n\n第22题\n");
	LinkList22 L22_1,L22_2;
	GenerateList22(L22_1,L22_2);
	printf("第一个单词:");PrintList22(L22_1);
	printf("\n第二个单词:");PrintList22(L22_2);printf("\n");
	printf("公共节点位置是: %d (相对于第一个单词)\n",
		FindSuffixSubscript(L22_1,L22_2));

	// 第23题
	printf("\n\n第23题\n");
	LinkList L23;
	InitListNH(L23);
	GenerateList(L23);
	L23->next->next->data = L23->next->data;
	L23->next->next->next->next->data = -L23->next->data;
	PrintList(L23);
	//DeleteAllDouble1(L23); // O(n^2)
	DeleteAllDouble2(L23,11); // O(n)
	PrintList(L23);
	DeleteNode(L23,false);

	// 第24题
	printf("\n\n第24题\n");
	LinkList L24_1;
	InitListNH(L24_1);
	GenerateList2(L24_1,1,10);
	PrintList(L24_1);
	printf("是否有环: %d\n",HasCircle(L24_1)!=NULL);
	DeleteNode(L24_1,false);
	LinkList L24_2;
	InitListNH(L24_2);
	GenerateList2(L24_2,1,10);
	PrintList(L24_2);
	// head 1    2     3     4    5     6      7     8      9
	L24_2->next->next->next->next->next->next->next->next->next->next=L24_2;
	printf("是否有环: %d\n",HasCircle(L24_2)!=NULL);
	L24_2->next->next->next->next->next->next->next->next->next->next=NULL;
	DeleteNode(L24_2,false);

	// 第25题
	printf("\n\n第25题\n");
	LinkList L25;
	InitListNH(L25);
	GenerateList2(L25,1,10);
	PrintList(L25);
	ReSorting(L25);
	PrintList(L25);
	DeleteNode(L25,false);
	LinkList L25_2;
	InitListNH(L25_2);
	GenerateList2(L25_2,1,11);
	PrintList(L25_2);
	ReSorting(L25_2);
	PrintList(L25_2);
	DeleteNode(L25_2,false);

	return 0;
}
