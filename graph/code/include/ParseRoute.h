#ifndef _PARSEROUTE_
#define _PARSEROUTE_

#include <stdio.h>

#include "Route.h"
#include "GraphConstruct.h"

#define MINPATH 	0
#define ALLPATH		1
#define MINVALUE 	2

int GetMinPath(int route[][MAXSPACE],int size);
void printRoute(int route[][MAXSPACE],Graph *graph,int size);
int GetMinPath(int route[][MAXSPACE],int size);
void printSpecficPath(Graph *graph,int *route);
void ParseRoute(Graph *graph, int start, int end, int PATHWAY);
void PrintMinValuePath(Graph *graph,int path[]);

#endif