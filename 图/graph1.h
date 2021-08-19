#define MaxVerNum 50
//#define INFINITY -1
#define NONE 0
typedef struct
{
	int Vex[MaxVerNum];            // 顶点
	int Edge[MaxVerNum][MaxVerNum]; // 邻接矩阵
	int vexnum,arcnum;              // 图当前顶点数和边数/弧数
}Graph;

void InitGraph(Graph &G){
	G.vexnum = 0;
	G.arcnum = 0;
}

bool AddEdgeDirected(Graph &G,int x,int y,int value){
    if(value==NONE)
		return false;
	G.Edge[x][y] = value;
    return true;
}

bool AddEdge(Graph &G,int x,int y,int value){
	G.Edge[x][y] = value;
	G.Edge[y][x] = value; 
	return true;
}

bool AddNode(Graph &G,int vex){
	G.Vex[G.vexnum+1] = vex;
	G.vexnum++;
	//for(int i=1;)
	return true;
}

void PrintGraph(Graph G){
	// 上表头
	printf("    ");
	for(int i=1;i<G.vexnum+1;i++)
		printf(" %d",G.Vex[i]);
	printf("\n   |");
	for(int i=1;i<G.vexnum+1;i++)
		printf("--");
	printf("\n");
	// 内容与左表头
	for(int i=1;i<G.vexnum+1;i++){
		printf(" %d |",G.Vex[i]);
		for(int j=1;j<G.vexnum+1;j++){
			if(i==j)
				printf(" \\");
			else if(G.Edge[i][j]==0)
				printf(" .");
			else
				printf(" %d",G.Edge[i][j]);
				
		}
		printf("\n");
	}
}

int FirstNeighbor(Graph G,int v){
	for(int i=1;i<G.vexnum+1;i++)
		if(G.Edge[v][i]!=0)
			return i;
	return -1;
}

int NextNeighbor(Graph G,int v, int h){
	for(int i=h+1;i<G.vexnum+1;i++)
		if(G.Edge[v][i]!=0)
			return i;
	return -1;
}

int FirstNeighborValue(Graph G,int v,int &value){
	for(int i=1;i<G.vexnum+1;i++)
		if(G.Edge[v][i]!=0){
			value = G.Edge[v][i];
			return i;
		}
	return -1;
}

int NextNeighborValue(Graph G,int v, int h,int &value){
	for(int i=h+1;i<G.vexnum+1;i++)
		if(G.Edge[v][i]!=0){
			value = G.Edge[v][i];
			return i;
		}
	return -1;
}

int GetVexnum(Graph G){
    return G.vexnum;
}

void TestInit(Graph &G){
	// 构建新图
	for(int i=0;i<MaxVerNum;i++)
		for(int j=0;j<MaxVerNum;j++)
			G.Edge[i][j] = false;
	G.vexnum = 0;
	G.arcnum = 0;
	// 构建一些边与结点;
	int temp[] = {1,2,3,4,5,6,7,8};
	for(int i=0;i<sizeof(temp)/sizeof(temp[0]);i++)
		G.Vex[i+1] = temp[i];
	//AddEdge(G,5,1,1);
	AddEdge(G,1,2,1);
	AddEdge(G,2,6,1);
	AddEdge(G,6,3,1);
	AddEdge(G,6,7,1);
	AddEdge(G,3,7,1);
	AddEdge(G,3,4,1);
	AddEdge(G,4,7,1);
	AddEdge(G,4,8,1);
	AddEdge(G,7,8,1);
	G.vexnum = 8;
	G.arcnum = 9;

	PrintGraph(G);
	printf(
		"\n 1 - 2   3 - 4\n"
		"     | / | / |\n"
		" 5   6 - 7 - 8\n");
}

typedef double FloydCost[MaxVerNum][MaxVerNum];

void GetWeight(Graph G,FloydCost &Cost){
	for(int i=1;i<GetVexnum(G)+1;i++)
		for(int j=1;j<GetVexnum(G)+1;j++)
			Cost[i][j]=G.Edge[i][j];
}