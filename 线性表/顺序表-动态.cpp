/** 线性表 - 顺序表 - 动态分配
 *  内容包括:
 *  顺序储存类型定义
 *  初始化
 *  增加空间
 *  插入操作
 *  删除操作
 *  按值查找
 *  按位查找 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 链式储存类型定义  
#define InitSize 3 // 默认最大长度
typedef struct
{
	int* data;
	int MaxSize,length;
}SeqList;

// 初始化
void InitList(SeqList &L)
{
	// 创造空间(默认InitSize大小)
	L.data = (int*)malloc(sizeof(int)*InitSize); // C type
	// L.data = new int[InitSize]; // C++ type
	// 默认初始值为0
	for(int i=0; i<InitSize; i++)
		L.data[i] = 0;
	//长度为0
	L.length = 0;
	//最大容量
	L.MaxSize = InitSize;
}

// 增加动态数组的长度
void IncreaseSize(SeqList &L, int len)
{
	// 寄存用的指针
	int* temp = L.data;
	// 申请新空间
	L.data = (int*)malloc(sizeof(int)*(len+L.MaxSize));
	// 复制数据
	for(int i=0;i<L.length;i++){
		L.data[i] = temp[i];
	}
	// 增加长度
	L.MaxSize = L.MaxSize+len;
	// 释放原内存
	free(temp);
}

// 插入操作
bool ListInsert(SeqList &L, int i, int e)
{
	// 判断i是否有效
	if(i<1||i>L.length+1){
		printf("invaled i: i=%d,length=%d\n",i,L.length);
		return false;
	}
	// 判断是否栈满
	if(L.length >= L.MaxSize){
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
bool ListDelete(SeqList &L, int i)
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
int GetItem(SeqList L, int i)
{
	//判断i是否有效
	if(i<1||i>L.length){
		printf("invaled i\n");
		return 0;
	}
	return L.data[i-1];
}

// 按值查找 - 返回位序(下标+1)
int LocateElem(SeqList &L, int num)
{
	for(int i=0;i<L.length; i++)
		// 注意如果比较结构类型不能用==
		// 但是考试时可以直接写==
		if(num==L.data[i])
			return i+1; // 注意返回的是位序(下标+1)
	return 0;
}

// 测试部分	
int main(void)
{
	printf("线性表 - 顺序表 - 动态分配\n");

	// 顺序存储 - 动态分配
	SeqList L;

	// 初始化
	InitList(L);

	// 添加节点
	ListInsert(L,1,10);
	ListInsert(L,2,20);
	ListInsert(L,3,30);
	printf("添加节点 : %d,%d,%d\n"\
		,L.data[0],L.data[1],L.data[2]);

	// 申请新节点
	printf("申请两个新节点\n");
	IncreaseSize(L,2);

	// 再添加节点
	ListInsert(L,2,5);
	printf("添加节点 : %d,%d,%d,%d\n"\
		,L.data[0],L.data[1],L.data[2],L.data[3]);

	// 删除结点
	ListDelete(L,1);
	printf("删除节点 : %d,%d,%d\n",L.data[0],L.data[1],L.data[2]);	

	// 按位查找
	printf("按位查找 6位 : "); GetItem(L,6);
	printf("按位查找 1位 : %d\n",GetItem(L,1));

	// 按值查找
	printf("按值查找 30 : %d\n",LocateElem(L,30));

	free(L.data);
	return 0;
}