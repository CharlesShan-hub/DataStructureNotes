#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"
#include "graph1.h" // 邻接矩阵
//#include "graph2.h" // 邻接表

/**************************************************************************/
/*                                 Topo                                   */
/**************************************************************************/

typedef struct TopoArray
{
	int indegree[MaxVerNum]; // 当前顶点入度
	int print[MaxVerNum];     // 记录拓扑序列
}TopoArray;

void TopoTestInit(Graph &G,TopoArray &array){
	for(int i=1;i<MaxVerNum;i++){
		array.indegree[i] = GetIndegree(G,i);
		array.print[i] = -1;
	}
}

void TopoPrintf(TopoArray array){
	printf(" Indegree:");
	for(int i=1;i<MaxVerNum;i++){
		if(array.indegree[i]!=-1)
			printf("%2d ",array.indegree[i]);
	}
	printf("\n Path    :");
	for(int i=1;i<MaxVerNum;i++){
		if(array.print[i]!=-1)
			printf("%2d ",array.print[i]);
	}
	printf("\n");
}

bool TopologicalSort(Graph G,TopoArray &array){
	printf("\nInit\n");
	TopoPrintf(array);
	int count=1; // 记录已经输出的定点数

	// 初始化栈,存储入度为0的结点
	Stack S;
	InitStack(S);
	for(int i=1; i<MaxVerNum;i++)
		if(array.indegree[i]==0)
			StackPush(S,i);

	// Topo排序
	int i;
	while(!StackEmpty(S)){
		StackPop(S,i);
		array.print[count++] = i;
		// 将这个结点相连的结点入度都减一
		for(int next=FirstNeighbor(G,i);next!=-1;next=NextNeighbor(G,i,next)){
			//printf("[%d]",next);
			array.indegree[next]--;
			if(array.indegree[next]==0)
				StackPush(S,next);
		}
		printf("\ndel-%d ",i);
		printf("\n");
		TopoPrintf(array);
	}

	// 是否成功
	if(count<GetVexnum(G))
		return false;
	else
		return true;

}

/**************************************************************************/
/*                              Test Init                                 */
/**************************************************************************/

void TopoTestInit1(Graph &G,TopoArray &array){
	InitGraph(G);
	printf(
		" ------>\n"
		"  2 - 4\n"
		" /   / \\\n"
		"1   3 - 5\n\n");
	AddNode(G,1);
	AddNode(G,2);
	AddNode(G,3);
	AddNode(G,4);
	AddNode(G,5);
	AddEdgeDirected(G,1,2,1);
	AddEdgeDirected(G,2,4,1);
	AddEdgeDirected(G,3,4,1);
	AddEdgeDirected(G,4,5,1);
	AddEdgeDirected(G,3,5,1);
	PrintGraph(G);
	TopoTestInit(G,array);
}

int main()
{
	// 拓扑排序
	printf("构建测试图:\n");
	Graph G1;
	TopoArray array;
	TopoTestInit1(G1,array);
	int result = TopologicalSort(G1,array);
	printf("\nsuccess? %d\n",result);

	return 0;
}