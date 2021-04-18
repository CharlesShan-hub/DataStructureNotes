/** 线性表 - 顺序表 - 静态分配
 *  内容包括:
 *  顺序储存类型定义
 *  初始化
 *  插入操作
 *  删除操作
 *  按值查找
 *  按位查找
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 顺序储存类型定义
#define MaxSize 15 // 定义最大数量
typedef struct 
{
	int data[MaxSize];
	int length;
}SqList;

// 初始化
void InitList(SqList &L)
{
	// 默认初始值为0
	for(int i=0; i<MaxSize; i++)
		L.data[i] = 0;
	//长度为0
	L.length = 0;
}

// 插入操作
bool ListInsert(SqList &L, int i, int e)
{
	// 判断i是否有效
	if(i<1||i>L.length+1){
		printf("invaled i: i=%d,length=%d\n",i,L.length);
		return false;
	}
	// 判断是否栈满
	if(L.length >= MaxSize){
		printf("full\n");
		return false;
	}
	// 进行元素后移
	for(int j=L.length; j>=i; j--){
		L.data[j] = L.data[j-1];
	}
	// 进行新元素插入
	L.data[i-1] = e;
	// 线性表长度加一
	L.length++;
	return true;
}

// 删除操作
// 删除顺序表中第i（ l<=i<=L.length ）个位置的元素，
// 若成功则返回 true ，否则返回 false
bool ListDelete(SqList &L, int i)
{
	// 判断i是否有效
	if(i<1||i>L.length+1){
		printf("invaled i\n");
		return false;
	}
	// 后面元素前移
	for(int j=i; j<L.length; j++){
		L.data[j-1] = L.data[j];
	}
	// 线性表长减一
	L.length--;
	return true;
}

// 按位查找
int GetItem(SqList L, int i)
{
	//判断i是否有效
	if(i<1||i>L.length){
		printf("invaled i\n");
		return 0;
	}
	return L.data[i-1];
}

// 按值查找 - 返回位序(下标+1)
int LocateElem(SqList &L, int num)
{
	for(int i=0;i<L.length; i++){
		if(num==L.data[i]){
			return i+1;
		}
	}
	return 0;
}

// 测试部分	
int main(void)
{
	printf("线性表 - 顺序表 - 静态分配\n");

	// 顺序存储 - 静态分配
	SqList L;

	// 初始化
	printf("初始化\n");
	InitList(L);

	// 添加节点
	ListInsert(L,1,10);
	ListInsert(L,2,30);
	printf("添加节点 : %d,%d\n"\
		,L.data[0],L.data[1]);

	// 删除结点
	ListDelete(L,1);
	printf("删除节点 : %d\n",L.data[0]);	

	// 按位查找
	printf("按位查找 6位 : "); GetItem(L,6);
	printf("按位查找 1位 : %d\n",GetItem(L,1));

	// 按值查找
	printf("按值查找 30 : %d\n",LocateElem(L,30));

	return 0;
}