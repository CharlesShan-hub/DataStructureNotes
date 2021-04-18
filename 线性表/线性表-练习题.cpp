#include <stdio.h>
#include <stdbool.h>

#define Maxsize 20
typedef struct{
	int data[Maxsize];
	int length;
}SqList;

bool InitList(SqList &L){
	for(int i=0;i<Maxsize;i++)
		L.data[i] = 0;
	L.length=0;
	return true;
}

/* 从顺序表中删除具有最小值的元素(假设唯一),
 并由函数返回被删元素的值. 空出的位置有最后一个
 元素填补, 如顺序表为空, 则显示错误信息并退出运行*/

bool DeleteMin(SqList &L, int &value){
	// 判空
	if(L.length == 0){
		printf("顺序表为空\n");
		return false;
	}
	// 获取最小值
	int min = L.data[0];
	int min_id = 0;
	for(int i=0;i<Maxsize;i++){
		if(min>L.data[i]){
			min = L.data[i];
			min_id = i;
		}
	}
	// 删除元素
	value = L.data[min_id];
	L.data[min_id] = L.data[L.length];
	// 改变长度
	L.length--;
	return true;
}

/* 设计一个高哦小算法, 将顺序表L的所有元素逆置, 
 要求算法的空间复杂度为O(1)*/

bool Inverse(SqList &L){
	// 我采取的方法是, 折叠
	// 不需要逆置
	if(L.length==0||L.length==1){
		return true;
	}
	int temp = 0;
	int boundary = 0;
	// 设置边界
	// 答案中并没有设置boundary, 奇偶数的boundary都可以用
	// L.length/2表示. 因为实际上奇数时只是多了次最中间的对称.
	if(L.length%2==0)
		boundary = L.length/2;
	else
		boundary = (L.length-1)/2;
	// 进行镜像
	for(int i=0;i<boundary;i++){
		temp = L.data[i];
		L.data[i] = L.data[L.length-i-1];
		L.data[L.length-i-1] = temp;
	}
	return true;
}

/* 对长度为n的顺序表L,编写一个时间复杂度为O(n)、
 空间复杂度O(1)的算法,
 该算法删除线性表中所有值为x的数据元素*/

// 这是我的方法, i在前边走, j在后边追.
// count记录个数更改length.
bool DeleteAllX1(SqList &L,int x){
	int count = 0;
	// i跑在前边
	int i=0;
	// j跟在后边
	int j=0;
	// 删除操作
	for(i=0;i<L.length;i++){
		if(L.data[i]==x){
			count++;
			continue;
		}
		L.data[j] = L.data[i];
		j++;
	}
	L.length-= count;
	return true;
}

// 答案方法: 既然用了count就不用记录j了
bool DeleteAllX2(SqList &L,int x){
	int count = 0;
	// 删除操作
	for(int i=0;i<L.length;i++){
		if(L.data[i]==x){
			count++;
			continue;
		}
		L.data[i-count] = L.data[i];
	}
	L.length-= count;
	return true;
}

/* 从有序顺序表中, 删除其值在给定s与t之间(s<t)的所有元素,
 如果s 或 t不合理或顺序表为空, 显示错误并退出.*/

// 我的方法延续了上一题, 我觉得我的方法挺好的, 不过一会儿
// 还是也写上标答吧.
bool DeleteInterval1(SqList &L,int s, int t){
	if(s>=t){
		printf("s应小于t\n");
		return false;
	}
	if(L.length == 0){
		printf("顺序表为空\n");
		return false;
	}
	int count=0;
	for(int i=0;i<L.length;i++){
		if(L.data[i]>s && L.data[i]<t){
			count++;
			continue;
		}
		L.data[i-count] = L.data[i];
	}
	L.length -= count;
	return true;
}

// 答案方法: 注意这是有序表, 所以删除的元素必然是整体!
bool DeleteInterval2(SqList &L,int s, int t){
	if(s>=t){
		printf("s应小于t\n");
		return false;
	}
	if(L.length == 0){
		printf("顺序表为空\n");
		return false;
	}
	// 寻找第一个≥s的元素
	int i=0;
	int j=0;
	/*
	for(i=0;i<L.length;i++){
		if(L.data[i]>=s){
			break;
		}
	}
	*/
	for(i=0;i<L.length&&L.data[i]<s;i++);
	// 判断是否要继续
	if(i>=L.length)
		return true;
	// 寻找最后一个<=t的元素
	for(j=i;j<L.length&&L.data[j]>t;j++);
	// 前移
	for(;j<L.length;i++,j++)
		L.data[i] = L.data[j];
	L.length = i;
	return true;
}

/* 从顺序表中, 删除其值在给定s与t之间(s<t)的所有元素,
 如果s 或 t不合理或顺序表为空, 显示错误并退出.*/

// WOW! 就是刚才写的 DeleteInterval1!

/* 从有序顺序表中删除所有与其值重复的元素, 
	是比表中所有元素的值都不同*/

// 我这个程序跟答案相比, 兼容了表长为0的情况,
// 而且是从下标为1开始向前对比的, 和答案不一样.
bool DeleteSame1(SqList &L){
	int count = 0;
	for(int i;i<L.length;i++){
		if(i == 0) continue;
		if(L.data[i]==L.data[i-count-1])
			count++;
		else
			L.data[i-count] = L.data[i];
	}
	L.length-=count;
	return true;
}

// 答案方法: 使用了我第三题的i和j的方法
// i在后边, j在前边
bool DeleteSame2(SqList &L){
	if(L.length == 0)
		return false;
	int i,j;
	for(i=0,j=1; j<L.length; j++)
		// 查找下一个与上一个值不同的元素
		if(L.data[i]!=L.data[j])
			// 找到后, 将元素前移
			L.data[++i] = L.data[j];
	L.length = i+1;
	return true;
}

/* 将两个有序顺序表合并为一个新的有序顺序表,
 并由函数返回结果顺序表*/
// 标准答案
bool Merge(SqList A, SqList B, SqList &C){
	// 将A与B merge入C
	if(A.length + B.length > Maxsize){
		printf("Not enough place!\n");
		return false;
	}
	int i=0,j=0,k=0;
	// 循环, 两两比较, 小者存入结果表
	while(i<A.length && j<B.length)
		C.data[k++] = A.data[i]<B.data[j]? A.data[i++]:B.data[j++];
	// 还剩一个没有比较完的顺序表
	while(i<A.length)
		C.data[k++] = A.data[i++];
	while(j<B.length)
		C.data[k++] = B.data[j++];
	C.length = A.length + B.length;
	return true;
}

/* 已知在一维数组A[m+n]中依次存放两个线性表(a1,a2,a3 .. am)
 和(b1,b2,...bn).编写一个函数, 将数组中两个顺序表的位置互换.*/

bool Exchange(SqList &L,int m,int n){
	// abcde1234567
	// 7654321edcba
	// 1234567abcde
	// First we inverse the all list
	for(int i=0;i<L.length/2;i++){
		// a  a+b b
		// b  b   a
		L.data[i] += L.data[L.length-i-1];
		L.data[L.length-i-1] = L.data[i] - L.data[L.length-i-1];
		L.data[i] -= L.data[L.length-i-1];
	}

	// Then inverse the two list
	for(int i=0;i<n/2;i++){
		L.data[i] += L.data[n-i-1];
		L.data[n-i-1] = L.data[i] - L.data[n-i-1];
		L.data[i] -= L.data[n-i-1];
	}
	for(int i=0;i<m/2;i++){
		L.data[i+n] += L.data[L.length-i-1];
		L.data[L.length-i-1] = L.data[i+n] - L.data[L.length-i-1];
		L.data[i+n] -= L.data[L.length-i-1];
	}

	return true;
}

/* 9 10 11 12 13 14*/

// for test
int main(void){
	SqList A;
	InitList(A);
	A.data[0] = 0;
	A.data[1] = 1;
	A.data[2] = 2;
	A.data[3] = 3;
	A.data[4] = 4;
	A.data[5] = 5;
	A.data[6] = 6;
	A.data[7] = 7;
	A.data[8] = 8;
	A.data[9] = 9;
	A.length = 10;

	SqList B;
	InitList(B);
	B.data[0] = 1;
	B.data[1] = 2;
	B.data[2] = 3;
	B.length = 3;

	SqList C;
	InitList(C);
	C.data[0] = 1;
	C.data[1] = 2;
	C.data[2] = 3;
	C.length = 3;

	for(int i=0;i<A.length;i++)
		printf("%d",A.data[i]);
	printf("\n");
	Exchange(A,8,2);
	for(int i=0;i<A.length;i++)
		printf("%d",A.data[i]);
	printf("\n");
}







