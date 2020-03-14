#ifndef _ROUTE_H_
#define _ROUTE_H_ 

#include "GraphConstruct.h"

#define MAXSPACE 30

int GetTargerPath(Graph *graph, int start, int end, int route[][MAXSPACE]);
void InitConnetValue(GraphNode *head, int *connectValue, int count);
int GetNodeValue(GraphNode *graphNode, int tab);
void InitPath(int path[][MAXSPACE], int source,int count);
void PathAppend(int A[], int value);
int *PathCopy(int B[], int A[]);
void DiJkstra(Graph *graph, int source, int connectValue[], int path[][MAXSPACE], int visited[]);

#endif