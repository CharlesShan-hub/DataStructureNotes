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

void BubbleSort(int A[],int n){
	bool flag=true;
	int temp;
	for(int i=0;i<n-1;i++){
		flag = true;
		for(int j=n-1;j>i;j--){
			if(A[j-1]>A[j]){
				temp=A[j-1];
				A[j-1] = A[j];
				A[j] = temp;
				flag=false;
			}
		}
		ArrayPrint(A,n,i);
		if(flag)
			return;
	}
}

// 快速排序-用第一个元素将序列分成左右两部分
int FastSortPatition(int A[],int low, int high){
	int pivot=A[low];//基准/枢轴
	while(low<high){
		// 左边空了,找一个比枢轴小的放左边
		while(low<high&&A[high]>=pivot) --high;
		A[low]=A[high];
		// 右边空了,找一个比枢轴大的放右边
		while(low<high&&A[low]<=pivot) ++low;
		A[high]=A[low];
	}
	A[low]=pivot;//A[low]==A[high]
	return low;
}
// 快速排序
void FastSort(int A[],int low,int high,int level,int n){//level和n是为了print
	if(low<high){
		int pivotpos=FastSortPatition(A,low,high); //划分
		printf("[%d] %d-%d-%d\n",level++,low,pivotpos,high);
		ArrayPrint(A,n,pivotpos);
		FastSort(A,low,pivotpos-1,level,n);
		FastSort(A,pivotpos+1,high,level,n);
	}else if(low==high){
		ArrayPrint(A,n,low);
	}
}

int main(){
	printf("直接插入排序\n");
	int A[] = {10,8,6,4,2,9,7,5,3,1};
	ArrayPrint(A,10,-1);
	BubbleSort(A,10);
	ArrayPrint(A,10,-1);

	printf("\n快速排序\n");
	int B[] = {49,38,65,97,76,13,27,49};
	ArrayPrint(B,8,-1);
	FastSort(B,0,7,1,8);
	
	printf("\n快速排序\n");
	int C[] = {3,4,1,2,5};
	ArrayPrint(C,5,-1);
	FastSort(C,0,4,1,5);
	return 0;
}