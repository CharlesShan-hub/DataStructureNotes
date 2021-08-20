#define MaxVerNum 50
//#define INFINITY -1
#define NONE 0
typedef struct
{
	int Vex[MaxVerNum];                // 顶点
	int Edge[MaxVerNum][MaxVerNum]; // 邻接矩阵
	int vexnum,arcnum;                 // 图当前顶点数和边数/弧数
}Graph;

void InitGraph(Graph &G){
	G.vexnum = 0;
	G.arcnum = 0;
	for(int i=0;i<MaxVerNum;i++){
		G.Vex[i]=0;
		for(int j=0;j<MaxVerNum;j++)
			G.Edge[i][j] = 0;
	}
}

void DeleteNode(Graph &G,int x){
	G.Vex[x] = 0;
	for(int i=1;i<MaxVerNum;i++){
		G.Edge[x][i] = 0;
		G.Edge[i][x] = 0;
	}
	G.vexnum--;
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
	if(G.Vex[vex]!=NONE)
		return false;
	G.Vex[vex] = vex;
	G.vexnum++;
	return true;
}

void PrintGraph(Graph G){
	int temp=0,templ=0,tempr=0;
	// 上表头
	printf("    ");
	for(int i=1;i<G.vexnum+1;i++){
		if(G.Vex[i+temp]==NONE){
			temp++;
			i--;
		}else{
			printf(" %2d",G.Vex[i+temp]);
		}
	}
	printf("\n   |");
	for(int i=1;i<G.vexnum+1;i++)
		printf("---");
	printf("\n");
	// 内容与左表头
	tempr=0;
	for(int i=1;i<G.vexnum+1;i++){
		if(G.Vex[i+tempr]==NONE){
			tempr++;
			i--;
			continue;
		}else
			printf(" %d |",G.Vex[i+tempr]);
		templ=0;
		for(int j=1;j<G.vexnum+1;j++){
			if(G.Vex[j+templ]==NONE){
				templ++;
				j--;
				continue;
			}
			if((i+tempr)==(j+templ))
				printf("  \\");
			else if(G.Edge[i+tempr][j+templ]==INFINITY)
				printf(" .");
			else
				printf(" %2d",G.Edge[i+tempr][j+templ]);
				
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

int GetWeight(Graph G,int i,int j){
	return G.Edge[i][j];
}

int GetIndegree(Graph G,int n){
	if(G.Vex[n]==NONE)
		return -1;
	int count=0;
	for(int i=1;i<MaxVerNum;i++)
		if(G.Edge[i][n]!=0)
			count++;
	return count;
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

void GetFloWeight(Graph G,FloydCost &Cost){
	for(int i=1;i<GetVexnum(G)+1;i++)
		for(int j=1;j<GetVexnum(G)+1;j++){
			if(G.Edge[i][j]!=NONE)
				Cost[i][j]=G.Edge[i][j];
		}
}

typedef struct DijArray
{
	bool final[MaxVerNum];  // 是否找到最短路径
	double dist[MaxVerNum]; // 最短路径长度
	int path[MaxVerNum];    // 路径前驱(-1表示未改变)
}DijArray;

void GetDijWeight(Graph G,DijArray &Array,int n){
    for(int i=1;i<GetVexnum(G)+1;i++)
    	if(G.Edge[n][i]!=0){
    		Array.dist[i]=G.Edge[n][i];
    		Array.path[i]=0;
    	}
}
