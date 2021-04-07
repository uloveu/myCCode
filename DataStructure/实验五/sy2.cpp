//广度优先搜索遍历连通图
#include <iostream>
using namespace std;

#define MaxInt 32767
#define MVNum 100
#define MAXQSIZE 100

typedef char VerTexType;
typedef int ArcType;
bool visited_1[MVNum];
bool visited_2[MVNum];

typedef struct
{
    VerTexType vexs[MVNum];
    ArcType arcs[MVNum][MVNum];
    int vexnum, arcnum;
} Graph;

typedef struct
{
    ArcType *base;
    int front;
    int rear;
} sqQueue;

void InitQueue(sqQueue &Q)
{
    Q.base = new ArcType[MAXQSIZE];
    if (!Q.base)
        exit(1);
    Q.front = Q.rear = 0;
}

void EnQueue(sqQueue &Q, ArcType e)
{
    if ((Q.rear + 1) % MAXQSIZE == Q.front)
        return;
    Q.base[Q.rear] = e;
    Q.rear = (Q.rear + 1) % MAXQSIZE;
}

bool QueueEmpty(sqQueue Q)
{
    if (Q.rear == Q.front)
        return true;
    return false;
}

void Dequeue(sqQueue &Q, ArcType &u)
{
    u = Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXQSIZE;
}

int LocateVex(Graph G, VerTexType v)
{
    for (int i = 0; i < G.vexnum; ++i)
        if (G.vexs[i] == v)
            return i;
    return -1;
}

void CreateUDN(Graph &G)
{
    int i, j, k=0;
    cout << "请输入总顶点数，总边数，以空格隔开:";
    cin >> G.vexnum >> G.arcnum;
    cout << endl;
    cout << "输入点的名称，如a" << endl;
    for (i = 0; i < G.vexnum; ++i)
    {
        cout << "请输入第" << (i + 1) << "个点的名称:";
        cin >> G.vexs[i];
    }
    cout << endl;
    for (i = 0; i < G.vexnum; ++i)
    {
        for (j = 0; j < G.vexnum; ++j)
            G.arcs[i][j] = 0;
    }
    cout << "输入边依附的顶点，如a b" << endl;
    for (k = 0; k < G.arcnum; k++)
    {
        VerTexType v1, v2;
        cout << "请输入第" << (k + 1) << "条边依附的顶点:";
        cin >> v1 >> v2;
        i = LocateVex(G, v1);
        j = LocateVex(G, v2);
        G.arcs[i][j] = 1;
        G.arcs[j][i] = G.arcs[i][j];
    }
}

int FirstAdjVex(Graph G, int v)
{
    int i;
    for (i = 0; i < G.vexnum; ++i)
    {
        if (G.arcs[v][i] == 1 && visited_1[i] == false)
            return i;
    }
    return -1;
}

int NextAdjVex(Graph G, int u, int w)
{
    int i;
    for (i = w; i < G.vexnum; ++i)
    {
        if (G.arcs[u][i] == 1 && visited_1[i] == false)
            return i;
    }
    return -1;
}

void DFS_AM(Graph G, int v)
{
    int w;
    cout << G.vexs[v] << "  ";
    visited_2[v] = true;
    for (w = 0; w < G.vexnum; w++)
    {
        if ((G.arcs[v][w] != 0) && (!visited_2[w]))
        {
            DFS_AM(G, w);
        }
    }
}

void BFS(Graph G, int v)
{
    sqQueue Q;
    ArcType u;
    ArcType w;
    cout << G.vexs[v] << "  ";
    visited_1[v] = true;
    InitQueue(Q);
    EnQueue(Q, v);
    while (!QueueEmpty(Q))
    {
        Dequeue(Q, u);
        for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
        {
            if (!visited_1[w])
            {
                cout << G.vexs[w] << "   ";
                visited_1[w] = true;
                EnQueue(Q, w);
            }
        }
    }
}

int main()
{
    Graph G;
    CreateUDN(G);
    cout << endl;
    cout << "无向连通图G创建完成！" << endl;

    cout << "请输入遍历连通图的起始点：";
    int i;
    cin >> i;
    cout << "广度优先搜索遍历连通图结果：" << endl;
    BFS(G, i);
    cout << endl;
    cout << "深度优先搜索遍历连通图结果：" << endl;
    DFS_AM(G, i);
    cout << endl;
    return 0;
}