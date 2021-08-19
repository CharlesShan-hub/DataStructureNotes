#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph1.h" // 邻接矩阵
//#include "graph2.h" // 邻接表

typedef double FloydCost[MaxVerNum][MaxVerNum];

typedef int FloydPath[MaxVerNum][MaxVerNum];

void FloydTestInit(Graph &G,FloydCost &Cost,FloydPath &Path){
	// 初始化图
	// 1 - 2
	//  \ / 
	//   3
	InitGraph(G);
	AddNode(G,1);
	AddNode(G,2);
	AddNode(G,3);
	AddEdgeDirected(G,1,2,6);
	AddEdgeDirected(G,2,1,10);
	AddEdgeDirected(G,1,3,13);
	AddEdgeDirected(G,3,1,5);
	AddEdgeDirected(G,2,3,4);

	PrintGraph(G);

	// 初始化辅助数组
	for(int i=0;i<MaxVerNum;i++)
		for(int j=0;j<MaxVerNum;j++){
			Cost[i][j] = 0;
			Path[i][j] = -1;
		}
	GetWeight(G,Cost);
}

void FloydPrintf(FloydCost Cost,FloydPath Path,int length,int tag){
	if(tag!=-1)
		printf("\n Cost(%d):\n ",tag);
	else
		printf("\n Cost:\n ");
	for(int i=1;i<length+1;i++){
		for(int j=1;j<length+1;j++){
			printf(" %4.1f",Cost[i][j]);
		}
		printf("\n ");
	}
	
	if(tag!=-1)
		printf("\n Path(%d)\n ",tag);
	else
		printf("\n Path\n ");
	for(int i=1;i<length+1;i++){
		for(int j=1;j<length+1;j++){
			printf(" %2d",Path[i][j]);
		}
		printf("\n ");
	}
}

void floyd(Graph G,FloydCost &Cost,FloydPath &Path){
	for(int k=1; k<GetVexnum(G)+1; k++){
		for(int i=1; i<GetVexnum(G)+1; i++){
			for(int j=1; j<GetVexnum(G)+1; j++){
				if((Cost[i][j]>Cost[i][k]+Cost[k][j]||fabs(Cost[i][j])<0.000001)&&
					i!=j){
					Cost[i][j]=Cost[i][k]+Cost[k][j];
					Path[i][j]=k;
				}
			}
		}
		FloydPrintf(Cost,Path,GetVexnum(G),k);
	}
}
int main(){
	printf("构建测试图:\n\n");
	Graph G;

	FloydCost Cost; // 用来存储路径权重
	FloydPath Path; // 用来保存经过的结点
	FloydTestInit(G,Cost,Path);
	printf("\nfloyd算法:\n");
	floyd(G,Cost,Path);
	//FloydPrintf(Cost,Path,GetVexnum(G),-1);
	
	return 0;
}