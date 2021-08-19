#define MaxVerNum 50
#define NONE 0
typedef struct ArcNode
{
    int adjvex;           // 边/弧指向哪个节点
    struct ArcNode *next; // 指向下一条弧的指针
    int value;            // 权值(默认为1)
    // other info
}ArcNode;

typedef struct VNode{
    int data;            // 顶点数据
    ArcNode *first;      // 第一条边/弧
    //data
}VNode,Graph[MaxVerNum],AdjList[MaxVerNum];

// 为了方便,Graph的第一个结点数据存放结点数量

bool AddEdgeDirected(AdjList &G,int x,int y,int value){
    ArcNode *p = NULL;
    ArcNode *q = NULL;
    // 头插x-y
    q = (ArcNode*)malloc(sizeof(ArcNode));
    q->adjvex = y;
    q->value = value;
    p = G[x].first;
    G[x].first = q;
    G[x].first->next = p;
    return true;
}

bool AddEdge(AdjList &G,int x,int y,int value){
    AddEdgeDirected(G,x,y,value);
    AddEdgeDirected(G,y,x,value);
    return true;
}

bool AddNode(AdjList &G,int data){
    ArcNode *p = NULL;
    int count = 1;
    while(G[count].data!=NONE){
        count++;
    }
    G[count].data=data;
    G[0].data++;
    return true;
}

int FirstNeighbor(AdjList G,int v){
    if(G[v].first==NULL)
        return -1;
    else
        return G[v].first->adjvex;
}

int NextNeighbor(AdjList G,int v, int h){
    ArcNode *p=G[v].first;
    while(p!=NULL && p->adjvex!=h)
        p=p->next;
    if(p->next==NULL)
        return -1;
    else
        return p->next->adjvex;
}

void PrintGraph(AdjList G){
    ArcNode *p = NULL;
    for(int i=1;i<MaxVerNum;i++){
        if(G[i].data!=NONE){
            printf(" %d ",G[i].data);
            if(G[i].first!=NULL)
                printf("-> ");
            for(p=G[i].first;p!=NULL;p=p->next)
                printf("%d(%2d) ",p->adjvex,p->value);
            printf("\n");
        }
    }
}

int GetVexnum(AdjList G){
    return G[0].data;
}

void InitGraph(AdjList &G){
    for(int i=0;i<MaxVerNum;i++){
        G[i].data = NONE;
        G[i].first = NULL;
    }
}

void TestInit(AdjList &G){
    // 构建新图
    InitGraph(G);
    // 构建一些边与结点;
    int temp[] = {1,2,3,4,5,6,7,8};
    for(int i=0;i<sizeof(temp)/sizeof(temp[0]);i++)
        G[i+1].data = temp[i];
    G[0].data = 8;
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

    PrintGraph(G);
    printf(
        "\n 1 - 2   3 - 4\n"
        "     | / | / |\n"
        " 5   6 - 7 - 8\n");
}

typedef double FloydCost[MaxVerNum][MaxVerNum];

void GetWeight(Graph G,FloydCost &Cost){
    ArcNode *p = NULL;
    for(int i=1,j=1;i<MaxVerNum;i++){
        if(G[i].data!=NONE){
            j=1;
            for(p=G[i].first;p!=NULL;p=p->next){
                Cost[i][j]=p->value;
                j++;
            }
        }
    }
}