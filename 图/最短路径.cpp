#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph1.h" // 邻接矩阵
//#include "graph2.h" // 邻接表
#include "queue.h"  // 用于为BFS提供辅助队列

/**************************************************************************/
/*                                  BFS                                   */
/**************************************************************************/
typedef int BFSArray[2][MaxVerNum];

void BFSTestInit(Graph &G,BFSArray &array){
	InitGraph(G);
	for(int i=0;i<MaxVerNum;i++){
		array[0][i]=INFINITY;
		array[1][i]=-1;
	}
}

void BFSPrintf(BFSArray array,int length){
	for(int k=0;k<3;k++){
		if(k==0){
			printf("        |");
			for(int i=1;i<length+1;i++)
				printf(" %4d",i);
			printf("\n");
			continue;
		}
		else if(k==1)
			printf("   d[]  |");
		else
			printf(" path[] |");
		for(int i=1;i<length+1;i++){
			printf(" %4.1d",array[k-1][i]);
		}
		printf("\n");
	}
	printf("\n");
}

void BFS_MIN_Distance(Graph G,int u,BFSArray &array){
	bool visited[MaxVerNum]={0};
	LinkQueue Q = InitQueue();
	array[0][u] = 0; // visit
	visited[u] = true;
	EnQueue(Q,u);
	while(!EmptyLinkQueue(Q)){
		DeQueue(Q,u);
		for(int w=FirstNeighbor(G,u);w>=0;w=NextNeighbor(G,u,w)){
			if(!visited[w]){
				array[0][w] = array[0][u]+1; // visit
				array[1][w] = u;             // visit
				visited[w]=true;
				EnQueue(Q,w);
			}
		}
	}
}


/**************************************************************************/
/*                              Dijkstra                                  */
/**************************************************************************/
/*
typedef struct DijArray
{
	bool final[MaxVerNum];  // 是否找到最短路径(默认false)
	double dist[MaxVerNum]; // 最短路径长度(默认INFINITY-65536)
	int path[MaxVerNum];    // 路径前驱(-1表示未改变)
}DijArray;
*/

void DijTestInit(Graph &G,DijArray &array){
	InitGraph(G);
	for(int i=0;i<MaxVerNum;i++){
		array.final[i] = false;
		array.dist[i] = INFINITY;
		array.path[i] = -1;
	}
}

void DijPrintf(DijArray array,int length, int tag){
	// 打印表头
	if(tag==0)
		printf("        |");
	else
		printf("  [%2d]  |",tag);
	for(int i=1;i<length+1;i++)
		printf(" %4d",i);
	printf("\n");
	// 是否找到路径
	printf("  final |");
	for(int i=1;i<length+1;i++)
		printf(" %4d",array.final[i]);
	printf("\n");
	// 最短路径长度
	printf("  dist  |");
	for(int i=1;i<length+1;i++)
		if(array.dist[i]!=INFINITY)
			printf(" %4.1f",array.dist[i]);
		else
			printf(" %4s","x");
	printf("\n");
	// 路径上的前驱
	printf("  path  |");
	for(int i=1;i<length+1;i++){
			printf(" %4d",array.path[i]);
	}
	printf("\n\n");
}

void dijkstra(Graph G,int start,DijArray &array){
	// start是位序,从1开始

	// 初始
	array.final[start] = true;  // 是否找到最短路径
	array.dist[start] = 0;      // 最短路径长度
	array.path[start] = -1;     // 路径前驱(-1表示未改变)
	DijPrintf(array,GetVexnum(G),0);
	// 进行n-1次循环
	double min_dist = INFINITY; // 用来寻找最小值点(值)
	int min_dist_id = 1;        // 用来寻找最小值点(点)
	int last_min_id = start;    // 用来寻找最小值点(上个点)
	int value;                  // 用来更新下一个点(值)
	for(int n=1;n<GetVexnum(G);n++){
		// 寻找dist最小的未标记结点
		min_dist = INFINITY;
		min_dist_id = -1;
		for(int i=1;i<GetVexnum(G)+1;i++){
			if(array.final[i]==true)
				continue;
			if(array.dist[i]<=min_dist){
				min_dist = array.dist[i];
				min_dist_id = i;
			}
		}
		// 标记最小未标记点
		printf(" ->%d\n",min_dist_id);
		array.final[min_dist_id] = true;
		if(array.dist[min_dist_id]+array.dist[last_min_id]<array.dist[min_dist_id])
			array.dist[min_dist_id] = array.dist[min_dist_id]+array.dist[last_min_id];
		array.path[min_dist_id] = last_min_id;
		last_min_id = min_dist_id;
		// 寻找各是否可以进行路径替换
		if(array.dist[min_dist_id]==INFINITY)
			continue;
		for(int next=FirstNeighborValue(G,min_dist_id,value);
			next!=-1;next=NextNeighborValue(G,min_dist_id,next,value)){
			if(array.final[next]==true)
				continue;
			if(array.dist[min_dist_id]+value<array.dist[next]){
				array.dist[next] = array.dist[min_dist_id]+value;
				array.path[next] = min_dist_id;
			}
		}
			
		//printf("[[%d->%d %d]]",min_dist_id,value_min_id,value_min);
		
		// 打印结果
		DijPrintf(array,GetVexnum(G),n);
	}
}

/**************************************************************************/
/*                                Floyd                                   */
/**************************************************************************/

typedef double FloydCost[MaxVerNum][MaxVerNum];

typedef int FloydPath[MaxVerNum][MaxVerNum];

void FloydTestInit(Graph &G,FloydCost &Cost,FloydPath &Path){
	InitGraph(G);
	for(int i=0;i<MaxVerNum;i++)
		for(int j=0;j<MaxVerNum;j++){
			if(i==j)
				Cost[i][j] = 0.0;
			else
				Cost[i][j] = INFINITY;
			Path[i][j] = -1;
		}
}

void FloydPrintf(FloydCost Cost,FloydPath Path,int length,int tag){
	if(tag!=-1)
		printf("\n Cost(%d):\n ",tag);
	else
		printf("\n Cost:\n ");
	for(int i=1;i<length+1;i++){
		for(int j=1;j<length+1;j++){
			if(Cost[i][j]==INFINITY)
				printf(" %4s","x");
			else
				printf(" %4.1f",Cost[i][j]);
		}
		printf("\n ");
	}
	
	if(tag!=-1)
		printf("\n Path(%d)\n ",tag);
	else
		printf("\n Path\n ");
	for(int i=1;i<length+1;i++){
		for(int j=1;j<length+1;j++)
			printf(" %2d",Path[i][j]);
		printf("\n ");
	}
}

void floyd(Graph G,FloydCost &Cost,FloydPath &Path){
	for(int k=1; k<GetVexnum(G)+1; k++){
		for(int i=1; i<GetVexnum(G)+1; i++){
			for(int j=1; j<GetVexnum(G)+1; j++){
				if(Cost[i][j]>Cost[i][k]+Cost[k][j]){
					Cost[i][j]=Cost[i][k]+Cost[k][j];
					Path[i][j]=k;
				}
			}
		}
		FloydPrintf(Cost,Path,GetVexnum(G),k);
	}
}

/**************************************************************************/
/*                              Test Init                                 */
/**************************************************************************/

void BFSTestInit1(Graph &G,BFSArray &array){
	BFSTestInit(G,array);
	for(int i=1;i<9;i++)
		AddNode(G,i);
	AddEdge(G,5,1,1);
	AddEdge(G,1,2,1);
	AddEdge(G,2,6,1);
	AddEdge(G,3,6,1);
	AddEdge(G,7,6,1);
	AddEdge(G,3,7,1);
	AddEdge(G,3,4,1);
	AddEdge(G,7,4,1);
	AddEdge(G,7,8,1);
	AddEdge(G,8,4,1);
	PrintGraph(G);
}

void DijTestInit1(Graph &G,DijArray &array,int i){
	DijTestInit(G,array);
	for(int j=1;j<6;j++)
		AddNode(G,j);
	AddEdgeDirected(G,1,2,10);
	AddEdgeDirected(G,1,5,5);
	AddEdgeDirected(G,2,3,1);
	AddEdgeDirected(G,2,5,2);
	AddEdgeDirected(G,3,4,4);
	AddEdgeDirected(G,4,1,7);
	AddEdgeDirected(G,4,3,6);
	AddEdgeDirected(G,5,2,3);
	AddEdgeDirected(G,5,3,9);
	AddEdgeDirected(G,5,4,2);
	PrintGraph(G);
	printf("\n");
	DijPrintf(array,GetVexnum(G),0);
	GetDijWeight(G,array,i);
}

void FloydTestInit1(Graph &G,FloydCost &Cost,FloydPath &Path){
	// 初始化图
	// 1 - 2
	//  \ / 
	//   3
	FloydTestInit(G,Cost,Path);
	AddNode(G,1);
	AddNode(G,2);
	AddNode(G,3);
	AddEdgeDirected(G,1,2,6);
	AddEdgeDirected(G,2,1,10);
	AddEdgeDirected(G,1,3,13);
	AddEdgeDirected(G,3,1,5);
	AddEdgeDirected(G,2,3,4);
	PrintGraph(G);
	GetFloWeight(G,Cost);
}

void FloydTestInit2(Graph &G,FloydCost &Cost,FloydPath &Path){
	// 初始化图
	FloydTestInit(G,Cost,Path);
	AddNode(G,1);
	AddNode(G,2);
	AddNode(G,3);
	AddNode(G,4);
	AddNode(G,5);
	AddEdgeDirected(G,3,2,1);
	AddEdgeDirected(G,2,4,1);
	AddEdgeDirected(G,1,3,1);
	AddEdgeDirected(G,2,5,5);
	AddEdgeDirected(G,3,5,7);
	AddEdgeDirected(G,1,5,10);
	AddEdgeDirected(G,4,5,1);
	PrintGraph(G);
	GetFloWeight(G,Cost);
}

void FloydTestInit3(Graph &G,FloydCost &Cost,FloydPath &Path){
	// 初始化图
	FloydTestInit(G,Cost,Path);
	printf(
		"      3         -----------\n"
		" /(7)   (7)\\    |1-3-2:14 |\n"
		"1-(6)-4-(6)-2   |1-4-2:12 |\n"
		" \\(1)   (1)/    |1-5-6-2:3|\n"
		"  5 -(1)- 9     -----------\n\n");
	FloydTestInit(G,Cost,Path);
	for(int i=1;i<7;i++)
		AddNode(G,i);
	AddEdgeDirected(G,1,3,10);
	AddEdgeDirected(G,3,2,10);
	AddEdgeDirected(G,1,4,6);
	AddEdgeDirected(G,4,2,6);
	AddEdgeDirected(G,1,5,1);
	AddEdgeDirected(G,5,6,1);
	AddEdgeDirected(G,6,2,1);
	PrintGraph(G);
	GetFloWeight(G,Cost);
}

int main(){
	/* 测试开关 */
	bool RUN_BFS = true;
	bool RUN_DIJ = true;
	bool RUN_FLO = true;

	/* BFS算法案例 */
	if(RUN_BFS){
		BFSArray bfs_array;   // 用于保存路径与长度

		printf("构建测试图1_1:\n\n");
		Graph G1;
		BFSTestInit1(G1,bfs_array);
		printf("\nBFS算法(2):\n");
		BFS_MIN_Distance(G1,2,bfs_array);
		BFSPrintf(bfs_array,GetVexnum(G1));

		BFSTestInit1(G1,bfs_array);
		printf("\nBFS算法(3):\n");
		BFS_MIN_Distance(G1,3,bfs_array);
		BFSPrintf(bfs_array,GetVexnum(G1));
	}

	/* Dijkstra算法案例 */
	if(RUN_DIJ){
		DijArray dij_array;

		printf("构建测试图2_1:\n\n");
		Graph G2;
		DijPrintf(dij_array,GetVexnum(G2),0);
		DijTestInit1(G2,dij_array,1);
		printf("\nDijkstra算法(开始节点名称—1):\n");
		dijkstra(G2,1,dij_array);
	}


	/* Floyd算法案例 */
	if(RUN_FLO){
		FloydCost Cost; // 用来存储路径权重
		FloydPath Path; // 用来保存经过的结点

		printf("构建测试图1:\n\n");
		Graph G3_1;
		FloydTestInit1(G3_1,Cost,Path);
		printf("\nfloyd算法:\n");
		floyd(G3_1,Cost,Path);

		printf("\n构建测试图2:\n\n");
		Graph G3_2;
		FloydTestInit2(G3_2,Cost,Path);
		printf("\nfloyd算法:\n");
		floyd(G3_2,Cost,Path);

		printf("\n构建测试图3:\n\n");
		Graph G3_3;
		FloydTestInit3(G3_3,Cost,Path);
		printf("\nfloyd算法:\n");
		floyd(G3_3,Cost,Path);
	}
	getchar();
	return 0;
}