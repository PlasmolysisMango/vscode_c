#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1001
#define INFINITY 65535

struct Graph {
    int vertexCount;
    int edgeCount;
    int matrix[MAXSIZE][MAXSIZE];
};
typedef struct Graph *MGraph;

MGraph createGraph();
void Prim(MGraph graph);
int findMinDis(MGraph graph, int dis[]);

int main() {
    MGraph graph = createGraph();
    Prim(graph);
    return 0;
}

MGraph createGraph() {
    int N, M;
    scanf("%d %d", &N, &M);

    MGraph graph = (MGraph) malloc(sizeof(struct Graph));
    graph->vertexCount = N; 
    graph->edgeCount = M;

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            graph->matrix[i][j] = INFINITY;
            // graph->matrix[j][i] = INFINITY;
        }
    }
        
    for (int i = 0; i < M; i++) {
        int x, y, weight;
        scanf("%d %d %d", &x, &y, &weight);
        graph->matrix[x][y] = weight;
        graph->matrix[y][x] = weight;
    }

    return graph;
}

void Prim(MGraph graph) {
    //vCount用于判断是否成功得到MST，totalWeight用于输出结果
    int vCount = 1, totalWeight = 0;

    int dis[MAXSIZE] = {0};     //dis是图中结点到MST的距离，为0表示在MST中
    for (int i = 2; i <= graph->vertexCount; i++)
        dis[i] = graph->matrix[1][i];   //从第一个顶点开始Prim算法

    while (1) {
        int vertex = findMinDis(graph, dis);    //找到距离最近且不在MST中的顶点
        if (vertex == -1) break;                //没找到就返回

        vCount++;                               //顶点数加一
        totalWeight += dis[vertex];             //权重增加
        dis[vertex] = 0;                        //将顶点放入MST中

        for (int i = 1; i <= graph->vertexCount; i++)
            if (dis[i] != 0 && graph->matrix[vertex][i] < INFINITY)
                if (dis[i] > graph->matrix[vertex][i])
                    dis[i] = graph->matrix[vertex][i];  //更新dis数组
    }

    if (vCount < graph->vertexCount) printf("-1\n");    //顶点数不够就错误
    else printf("%d\n", totalWeight);                   //成功生成MST
}

int findMinDis(MGraph graph, int dis[]) {
    int minDis = INFINITY, minVertex = 1;
    for (int i = 1; i <= graph->vertexCount; i++) {
        if (dis[i] != 0 && dis[i] < minDis) {
            minDis = dis[i];
            minVertex = i;
        }
    }
    if (minDis == INFINITY) return -1;
    return minVertex;
}