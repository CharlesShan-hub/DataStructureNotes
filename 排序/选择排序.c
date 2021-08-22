#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void ArrayPrint(int A[],int n,int current){
	if(current!=-1)
		printf("-%d> ",current);
	for(int i=0;i<n;i++){
		if(current==-1||current!=i){
			printf(" %2d  ",A[i]);
		}else{
			printf("【%2d】 ",A[i]);
		}
	}
	printf("\n");
}

void SelectSort(int A[],int n){
	int temp;
	for(int i=0;i<n-1;i++){
		int min=i;
		for(int j=i+1;j<n;j++)
			if(A[j]<A[min])
				min=j;
		if(min!=i){
			temp=A[i];
			A[i]=A[min];
			A[min]=temp;
		}
	}
}

void HeadAdjust(int A[], int k, int len){
	A[0]=A[k];
	for(int i=2*k;i<=len; i*=2){
		if(i<len&&A[i]<A[i+1])
			i++;//保证A[i]是最大的孩子
		if(A[0]>=A[i]) break;
		else{
			A[k]=A[i];
			k=i;
		}
		A[k]=A[0];
	}
}

void HeapSort(int A[],int len){
	// BuildMaxHeap - O(n)
	for(int i=len/2;i>0;i--) // 从最后一层到底一层依次进行调整
		HeadAdjust(A,i,len);
	// Sort -O(nlog2n)
	int temp;
	for(int i=len;i>1;i--){
		temp=A[i];
		A[i]=A[1];
		A[1]=temp;
		HeadAdjust(A,1,i-1);
	}
}

int main(){
	printf("直接插入排序\n");
	int A[] = {10,8,6,4,2,9,7,5,3,1};
	ArrayPrint(A,10,-1);
	SelectSort(A,10);
	ArrayPrint(A,10,-1);

	printf("堆排序\n");
	int B[] = {-2,3,4,1,10,7,8,6,5,2,9};//0号位置不存数据
	ArrayPrint(B+1,10,-1);
	HeapSort(B,10);
	ArrayPrint(B+1,10,-1);

	return 0;
}