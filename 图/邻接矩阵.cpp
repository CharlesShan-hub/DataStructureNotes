#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

/**
 * Adjacent(G,x,y):判断是否存在边<x,y>
 * Neighbors(G,x):列出图G中与结点x邻接的边
 * InsertVertex(G,x):插入x
 * DeleteVertex(G,x):删除x
 * AddEdge(G,x,y):插入连接
 * RemoveEdge(G,x,y):删除连接
 * FirstNeighbor(G,x):x的第一个邻接点,不存在返回-1
 * NextNeighbor(G,x,y):x的下一个邻接点(假设y是x的邻接点),如果y是最后一个,返回-1
 * GetEdgeValue(G,x,y):获取<x,y>边的权值
 * SetEdgeValue(G,x,y,v):设置G中边<x,y>边的权值为v
 */

#define MaxVerNum 50
//#define INFINITY -1
typedef struct
{
	char Vex[MaxVerNum];            // 顶点
	bool Edge[MaxVerNum][MaxVerNum]; // 邻接矩阵
	int vexnum,arcnum;              // 图当前顶点数和边数/弧数
}MGraph;

bool AddEdge(MGraph &G,int x,int y){
	G.Edge[x][y] = true;
	G.Edge[y][x] = true; 
	return true;
}

MGraph TestInit(){
	// 构建新图
	MGraph G;
	for(int i=0;i<MaxVerNum;i++)
		for(int j=0;j<MaxVerNum;j++)
			G.Edge[i][j] = false;
	G.vexnum = 0;
	G.arcnum = 0;
	// 构建一些边与结点;
	char temp[] = {'1','2','3','4','5','6','7','8'};
	for(int i=0;i<sizeof(temp)/sizeof(temp[0]);i++)
		G.Vex[i+1] = temp[i];
	//AddEdge(G,5,1);
	AddEdge(G,1,2);
	AddEdge(G,2,6);
	AddEdge(G,6,3);
	AddEdge(G,6,6);
	AddEdge(G,6,7);
	AddEdge(G,3,7);
	AddEdge(G,3,4);
	AddEdge(G,4,7);
	AddEdge(G,4,8);
	AddEdge(G,7,8);
	G.vexnum = 8;
	G.arcnum = 10;

	return G;
}

void PrintGraph(MGraph G){
	// 上表头
	printf("    ");
	for(int i=1;i<G.vexnum+1;i++)
		printf(" %c",G.Vex[i]);
	printf("\n   |");
	for(int i=1;i<G.vexnum+1;i++)
		printf("--");
	printf("\n");
	// 内容与左表头
	for(int i=1;i<G.vexnum+1;i++){
		printf(" %c |",G.Vex[i]);
		for(int j=1;j<G.vexnum+1;j++){
			if(i==j)
				printf(" \\");
			else if(G.Edge[i][j]==true)
				printf(" %d",G.Edge[i][j]);
			else
				printf(" .");
		}
		printf("\n");
	}
}

int FirstNeighbor(MGraph G,int v){
	for(int i=1;i<G.vexnum+1;i++)
		if(G.Edge[v][i]==true)
			return i;
	return -1;
}

int NextNeighbor(MGraph G,int v, int h){
	for(int i=h+1;i<G.vexnum+1;i++)
		if(G.Edge[v][i]==true)
			return i;
	return -1;
}

void visit(int v){
	printf("%d ",v);
}

// 广度优先遍历辅助队列
bool BFSvisited[MaxVerNum]={0};

// 广度优先遍历(顶点)
void BFS(MGraph G, int v, bool init){
	if(init)
		for(int i=1;i<G.vexnum+1;i++)
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
void BFSTraverse(MGraph G){
	for(int i=1;i<G.vexnum+1;i++)
			BFSvisited[i]=false;
	for(int i=1;i<G.vexnum+1;i++)
		if(!BFSvisited[i])
			BFS(G,i,false);
}

// 深度优先遍历辅助队列
bool DFSvisited[MaxVerNum] = {false};

// 深度优先遍历(点)
void DFS(MGraph G, int v, bool init){
	if(init)
		for(int i=1;i<G.vexnum+1;i++)
			DFSvisited[i]=false;
	visit(v);
	DFSvisited[v]=true;
	for(int w=FirstNeighbor(G,v);w>=0;w=NextNeighbor(G,v,w))
		if(!DFSvisited[w])
			DFS(G,w,false);
}

// 深度优先遍历(图)
void DFSTraverse(MGraph G){
	for(int i=1;i<G.vexnum+1;i++)
			DFSvisited[i]=false;
	for(int i=1;i<G.vexnum+1;i++)
		if(!DFSvisited[i])
			DFS(G,i,false);
}

int main(int argc, char const *argv[])
{
	printf("构建测试图:\n");
	MGraph G = TestInit();
	PrintGraph(G);
	printf(
		"\n 1 - 2   3 - 4\n"
		"     | / | / |\n"
		" 5   6 - 7 - 8\n");

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
