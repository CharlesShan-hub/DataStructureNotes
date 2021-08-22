#include<stdio.h>
#include<stdlib.h>

void ArrayPrint(int A[],int n,int current){
	for(int i=0;i<n;i++){
		if(current==-1||current!=i){
			printf("%2d ",A[i]);
		}else{
			printf("(%2d) ",A[i]);
		}
	}
	printf("\n");
}

// 直接插入排序
void InsertSortDirectly(int A[],int n){
	int j,temp;
	for(int i=1;i<n;i++)
		// 依次处理每个元素(从第二个元素开始处理)
		if(A[i]<A[i-1]){
			temp=A[i];
			// 直接查找
			for(j=i-1; j>=0&&A[j]>temp; j--)
				A[j+1]=A[j];
			A[j+1]=temp;
		}
}

// 折半插入排序
void InsertSortBinary(int A[],int n){
	int temp,low,high,mid;
	for(int i=1;i<n;i++){
		// 依次处理每个元素(从第二个元素开始处理)
		temp=A[i];
		// 折半查找
		for(low=0,high=i-1;!(low>high);){
			mid=(low+high)/2;
			if(A[mid]==temp){
				low=mid+1;
				break;
			}else if(A[mid]>temp)
				high=mid-1;
			else
				low=mid+1;
		}
		// 移动元素
		for(int k=i;k!=mid;k--)
			A[k]=A[k-1];
		printf("%d->%d\n",temp,i);
		A[low] = temp;
		ArrayPrint(A,10,low);
	}
}

// 希尔排序(Shell Sort)
void ShellSort(int A[],int n){
	int d,j,i;
	//A[0]只是暂存单元,不是哨兵,当j<=0时,插入位置已到
	for(d=n/2;d>=1;d=d/2) // 根据d不同分成每一趟
		for(i=d+1;i<=n;++i)
			if(A[i]<A[i-d]){
				A[0]=A[i];
				for(j=i-d;j>0&&A[0]<A[j];j-=d)
					A[j+d] = A[j];
				A[j+d] = A[0];
			}
}

int main(){
	printf("直接插入排序\n");
	int A[] = {1,3,5,7,9,2,4,6,8,10};
	ArrayPrint(A,10,-1);
	InsertSortDirectly(A,10);
	ArrayPrint(A,10,-1);

	printf("\n折半插入排序\n");
	int B[] = {1,3,5,7,9,2,4,6,8,10};
	ArrayPrint(B,10,-1);
	InsertSortBinary(B,10);

	printf("\n希尔排序\n");
	int C[] = {0,8,6,4,2,7,5,3,1};//C[0]是暂存位置
	/**
	 *  8 6 4 2 7 5 3 1
	 *  【1】d=4
	 *  7       8
	 *    5       6
	 *      3       4
	 *        1       2
	 * 
	 *  7 5 3 1 8 6 4 2
	 *  【2】d=2
	 *  3   4   7   8
	 *    1   2   5   6
	 * 
	 *  3 1 4 2 7 5 8 6
	 *  【3】d=1
	 * 
	 *  1 2 3 4 5 6 7 8
	 */
	ArrayPrint(C,9,-1);
	ShellSort(C,8);
	ArrayPrint(C,9,-1);
	return 0;
}