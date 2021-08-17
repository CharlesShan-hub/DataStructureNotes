#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
#define INFINITY -1
typedef struct ArcNode
{
	int adjvex;           // 边/弧指向哪个节点
	struct ArcNode *next; // 指向下一条弧的指针
	// other info
};

typedef struct VNode{
	int data;             // 顶点数据
	ArcNode *first;       // 第一条边/弧
}VNode,AdjList[MaxVerNum];

int main(int argc, char const *argv[])
{
	/* code */
	return 0;
}