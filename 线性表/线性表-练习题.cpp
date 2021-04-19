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

/* 线性表(a1,a2,a3, .. an)中的元素递增有序且安顺序储存于计算机内. 设计一个算法
 完成用最少时间,在表中查找数值为x的元素,若找到,则将其后继元素位置互换
 若找不到, 则将其插入表中并使表中元素仍递增有序*/

// 这是我写的, 但是没有在查找中进行插入
bool ExchangeOrInsert1(SqList &L, int x){
	// 合法性
	if(L.length==0)
		// 表中没有元素
		return false;
	if(L.data[L.length]==x)
		// 表尾是x
		return false;
	// 寻找 - 二分查找
	int k = L.length/2;
	int flag = false;
	int i,j;
	for(i=0, j=L.length; i<j;){
		if(L.data[k]==x){
			// 找到了
			int temp = L.data[k];
			L.data[k] = L.data[k+1];
			L.data[k+1] = temp;
			flag = true;
			break;
		}
		else if(L.data[k]>x){
			j = k;
			k = j/2;
			if(j/2==0)
				break;
		}else{
			i = k;
			k += (j-i)/2;
			if((j-i)/2 == 0)
				break;
		}
	}
	printf("%d\n",L.data[k]);
	// 没找到
	if(flag==false){
		if(L.length==Maxsize)
			return false;
		for(i=L.length;i>k+2;i--){
			L.data[i] = L.data[i-1];
		}
		L.data[k+1] = x;
		L.length++;
	}
	return true;
}

// 答案, 同样是折半查找,然后插入
bool ExchangeOrInsert2(SqList &L, int x){
	int low, high=L.length-1, mid;
	while(low<=high){
		mid = (low+high)/2;
		if(L.data[mid]==x)
			break;
		else if(L.data[mid]<x)
			low=mid+1;
		else
			high=mid-1;
	}
	if(L.data[mid]==x && mid !=L.length-1){
		int t = L.data[mid];
		L.data[mid] = L.data[mid+1];
		L.data[mid+1] = t;
	}
	if(low>high){
		int i;
		for(i=L.length-1;i>high;i--)
			L.data[i+1] = L.data[i];
		L.data[i+1] = x;
	}
	L.length++;
	return true;
}

/* 设将n(n>1)个整数存放到一维数组R中, 设计一个在时间
 和空间两方面都尽可能高效的算法
 将R中保存的序列循环左移p(0<p<n)个位置 */
bool Rotate(SqList &L,int p){
	// 123456789
	// 左移4
	// 567891234
	// 步骤
	// 987654321 - 全部反转
	// 567891234 - 分段反转
	// 详见Exchange()
	// 时间复杂度: O(n)
	// 空间复杂度: O(1) - 原地算法
	return true;
}

/* 一个长度L的升序序列S, 在[L/2]个位置的数称为S的中位数,
 例如, S1=(11,13,15,17.19), 中位数是15, 两个序列的中位数是
 含他们所欲元素的升序序列的中位数, 例如S2=(2,4,6,8,20),S1,S2的中位数是11
 现在又两个等长升序序列A和B. 找中位数*/

// 我的方法
// 时间复杂度 O(n)
// 空间复杂度 O(1)
bool FindMid1(SqList S1,SqList S2,int &value){
	int total = S1.length + S2.length;
	if(total==0){
		return false;
	}
	// 寻找中间的 - 两个表可能会有一个读完
	int i,j,count;
	count = (total+1)/2;
	printf("count is %d\n",count);
	for(i=0,j=0;i<S1.length&&j<S2.length;count--){
		if (S1.data[i]<=S2.data[j]){
			value = S1.data[i];
			i++;
			printf("%d S1 new value - %d\n",count,value);
		}
		else{
			value = S2.data[j];
			j++;
			printf("%d S2 new value - %d\n",count,value);
		}
		if(count==0)
			return true;
	}
	// 处理单个表
	while(i<S1.length){
		value = S1.data[i];
		i++;
		count--;
		printf("%d S1 new value - %d\n",count,value);
		if(count == 0)return true;
	}
	while(j<S2.length){
		value = S2.data[j];
		j++;
		count--;
		printf("%d S2 new value - %d\n",count,value);
		if(count == 0)return true;
	}
	return true;
}

// 答案方法 -  更快
// 时间复杂度 O(log2n)
// 空间复杂度 O(1)
// a, b是中位数. 
// a = b, a或b是中位数, 结束
// a < b, 舍弃a小的一半,b大的一半
// a > b, 舍弃b小的一半,a大的一半
// 重复上面三个步骤, 直到a = b或两序列都只含一个元素, 较小者是中位数.
bool FindMid2(SqList A, SqList B, int &value){
	int s1=0, d1=S1.length-1, m1;
	int s2=0, d2=S2.length-1, m2;
	// 分别表示序列A,B的首位数,末位数,中位数
	while(s1!=d1||s2!=d2){
		m1=(s1+d1)/2;
		m2=(s2+d2)/2;
		// 
		if(A.data[m1] == B.data[m2]){
			value = A.data[m1];
			return true;
		}
		// A舍前一半, B舍后一半
		// eg.
		// A=[1,2,3,4,5] -> [3,4,5] -> [4,5] -> [4] -> 4
		// B=[6,7,8]     -> [6,7]   -> [6]   -> [6]
		if(A.data[m1] < B.data[m2]){
			// 元素个数为奇数
			if((s1+d1)%2==0){
				s1 = m1;
				d2 = m2;
			// 元素个数为偶数
			}else{
				s1 = m1+1;
				d2 = m2;
			}
		// A舍后一半, B舍前一半
		}else{
			// 元素个数为奇数
			if((s1+d1)%2==0){
				d1 = m1;
				s2 = m2;
			// 元素个数为偶数
			}else{
				d1 = m1;
				s2 = m2+1;
			}
		}
	}
	value = A.data[s1]<B.data[s2] ? A.data[s1]:B.data[s2];
	return true;
}

/* 已知整数序列A=(a0,a1,a2,..,an). 主元素:出现频率大于一半.
 找出主元素, 有返回元素, 无返回-1*/
int FindMain(SqList L){
	if(L.length == 0)
		return false;
	// 计数
	int num=L.data[0],count=1,i;
	for(i=1;i<n;i++){
		if(count==0){
			num = L.data[i];
			count=1;
		}else if(L.data[i]==num){
			count++;
		}else{//L.data[i]!=num
			count--;
		}
	}
	// 检查
	count=0;
	for(i=0;i<L.length;i++)
		if(L.data[i]==num)
			count++;
	if(count*2>=L.length)
		return num;
	else
		return -1;
}

/* 给定一个含n(n≥1)个整数的数组, 涉及一个在时间上尽量
 可能高效的算法. 找出数组中从未出现的最小正整数. 例如,
 [-5,3,2,3]->1; [1,2,3]->4 */
int FindMinInt(SqList L){
	
}

/*13 14*/

// for test
int main(void){
	SqList A;
	InitList(A);
	A.data[0] = 3;
	A.data[1] = 4;
	A.data[2] = 5;
	A.data[3] = 6;
	A.data[4] = 7;
	A.data[5] = 8;
	A.data[6] = 9;
	A.data[7] = 10;
	A.data[8] = 11;
	A.data[9] = 12;
	A.length = 10;

	SqList B;
	InitList(B);
	B.data[0] = 0;
	B.data[1] = 1;
	B.data[2] = 2;
	B.length = 3;

	SqList C;
	InitList(C);
	C.data[0] = 1;
	C.data[1] = 2;
	C.data[2] = 3;
	C.length = 3;

	//for(int i=0;i<A.length;i++)
	//	printf("%d",A.data[i]);
	//printf("\n");
	int num;
	FindMid(A,C,num);
	printf("%d\n",num);
	//for(int i=0;i<A.length;i++)
	//	printf("%d",A.data[i]);
	//printf("\n");
}







