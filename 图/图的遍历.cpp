#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph1.h" // 邻接矩阵
//#include "graph2.h" // 邻接表
#include "queue.h"

void visit(int v){
	printf("%d ",v);
}

// 广度优先遍历辅助队列
bool BFSvisited[MaxVerNum]={0};

// 广度优先遍历(顶点)
void BFS(Graph G, int v, bool init){
	if(init)
		for(int i=1;i<GetVexnum(G)+1;i++)
			BFSvisited[i]=false;
	LinkQueue Q = InitQueue();
	visit(v);
	BFSvisited[v]=true;
	EnQueue(Q,v);
	while(!EmptyLinkQueue(Q)){
		DeQueue(Q,v);
		for(int w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w)){
			if(!BFSvisited[w]){
				visit(w);
				BFSvisited[w]=true;
				EnQueue(Q,w);
			}
		}
	}
}

// 广度优先遍历(图)
void BFSTraverse(Graph G){
	for(int i=1;i<GetVexnum(G)+1;i++)
			BFSvisited[i]=false;
	for(int i=1;i<GetVexnum(G)+1;i++)
		if(!BFSvisited[i])
			BFS(G,i,false);
}

// 深度优先遍历辅助队列
bool DFSvisited[MaxVerNum] = {false};

// 深度优先遍历(点)
void DFS(Graph G, int v, bool init){
	if(init)
		for(int i=1;i<GetVexnum(G)+1;i++)
			DFSvisited[i]=false;
	visit(v);
	DFSvisited[v]=true;
	for(int w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w))
		if(!DFSvisited[w])
			DFS(G,w,false);
}

// 深度优先遍历(图)
void DFSTraverse(Graph G){
	for(int i=1;i<GetVexnum(G)+1;i++)
			DFSvisited[i]=false;
	for(int i=1;i<GetVexnum(G)+1;i++)
		if(!DFSvisited[i])
			DFS(G,i,false);
}

int main(int argc, char const *argv[])
{
	printf("构建测试图:\n");
	Graph G;
	TestInit(G);

	printf("\n广度优先遍历(2):");
	BFS(G,2,true);
	printf("\n广度优先遍历(5):");
	BFS(G,5,true);
	printf("\n广度优先遍历(7):");
	BFS(G,7,true);
	printf("\n广度优先遍历(图):");
	BFSTraverse(G);

	printf("\n深度优先遍历(2):");
	DFS(G,2,true);
	printf("\n深度优先遍历(图):");
	DFSTraverse(G);

	printf("\n");
	return 0;
}
