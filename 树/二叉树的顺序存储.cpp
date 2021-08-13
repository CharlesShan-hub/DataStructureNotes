#include<stdio.h>
#include<stdbool.h>
#include <math.h>

#define MAXSIZE 100
struct Tree
{
	int value[MAXSIZE];
	bool isEmpty[MAXSIZE];
};

void InitTree(Tree &t){
	for(int i=0;i<MAXSIZE;i++)
		t.isEmpty[i]=true;
}

void TestInit(Tree &t){
	for(int i=1;i<13;i++)//存储1-12在1-12下标（为了让下表与索引一致）
		t.isEmpty[i]=bool(t.value[i]=i);
}

//下面是几个常考基本操作
int FindLeftChildIndex(Tree t,int m){
	if(m*2<=MAXSIZE && t.isEmpty[m*2]==false)
		return m*2;
	else
		return 0;
}

int FindRightChildIndex(Tree t,int m){
	if(m*2+1<=MAXSIZE && t.isEmpty[m*2+1]==false)
		return m*2+1;
	else
		return 0;
}

int FindParentIndex(int m){
	return m/2;
}

int FindLevel(int m){
	return int(log(m)/log(2))+1;
}

int main(){
	Tree t;
	InitTree(t);
	TestInit(t);
	printf("寻找左孩子:3-%d\n",FindLeftChildIndex(t,3));
	printf("寻找右孩子:3-%d\n",FindRightChildIndex(t,3));
	printf("寻找父结点:3-%d\n",FindParentIndex(3));
	printf("寻找所在层:3-%d\n",FindLevel(3));
	printf("寻找所在层:5-%d\n",FindLevel(5));
	printf("寻找所在层:9-%d\n",FindLevel(9));

	return 0;
}