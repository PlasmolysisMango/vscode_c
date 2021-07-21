/* 邻接矩阵存储 - 多源最短路算法 */

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
#define INFINITY 65535
#define ERROR -1
#define true 1
#define false 0

typedef int bool;
typedef int Vertex;
typedef int WeightType;

typedef struct GNode
{
    int Ne, Nv;
    WeightType G[MaxVertexNum][MaxVertexNum];
} * MGraph;

bool Floyd( MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum] )
{
    Vertex i, j, k;

    /* 初始化 */
    for ( i=0; i<Graph->Nv; i++ )
        for( j=0; j<Graph->Nv; j++ ) {
            D[i][j] = Graph->G[i][j];
            path[i][j] = -1;
        }

    for( k=0; k<Graph->Nv; k++ )
        for( i=0; i<Graph->Nv; i++ )
            for( j=0; j<Graph->Nv; j++ )
                if( D[i][k] + D[k][j] < D[i][j] ) {
                    D[i][j] = D[i][k] + D[k][j];
                    if ( i==j && D[i][j]<0 ) /* 若发现负值圈 */
                        return false; /* 不能正确解决，返回错误标记 */
                    path[i][j] = k;
                }
    return true; /* 算法执行完毕，返回正确标记 */
}