#include<stdio.h>

void Merge(int A[],int low1,int low2,int high){
	int i,j,k,B[high+1];
	for(k=low1;k<=high;k++)
		B[k]=A[k]; // 将A待归并的两个数列拷贝到B中
	for(i=low1,j=low2,k=i;i<low2&&j<=high;k++)
		if(B[i]<=B[j])
			A[k]=B[i++];
		else
			A[k]=B[j++];
	while(i<low2)
		A[k++]=B[i++];
	while(j<=high)
		A[k++]=B[j++];
}

void MergeSort(int A[],int low1,int high){
	int low2;
	if(low1<high){
		low2=(low1+high)/2+1;
		MergeSort(A,low1,low2-1);
		MergeSort(A,low2,high);
		Merge(A,low1,low2,high);
	}
}

void ArrayPrint(int A[],int n,int current){
	if(current!=-1)
		printf("-%d> ",current);
	for(int i=0;i<n;i++){
		if(current==-1||current!=i)
			printf(" %2d  ",A[i]);
		else
			printf("【%2d】 ",A[i]);
	printf("\n");
}

int main(){
	printf("直接插入排序\n");
	int A[] = {10,8,6,4,15,2,9,7,5,3,1,12,11,16,14};
	ArrayPrint(A,16,-1);
	MergeSort(A,0,15);
	ArrayPrint(A,16,-1);
	return 0;
}