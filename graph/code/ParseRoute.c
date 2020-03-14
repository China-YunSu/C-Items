#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "./include/ParseRoute.h"
#include "./include/GraphConstruct.h"
#include "./include/Route.h"

void printRoute(int route[][MAXSPACE],Graph *graph,int size) {
	int i = 0;
	int j = 0;
	for (i = 0; i < size; ++i) {
		for (j = 1; j < route[i][0] ; ++j) {
			printf("%s->", graph->node[route[i][j]]->data.cityData.name);
		}
		printf("%s\n", graph->node[route[i][j]]->data.cityData.name);
		memset(route[i], -1, (j + 1) * sizeof(int));
	}
}

int GetMinPath(int route[][MAXSPACE],int size) {
	int minIndex = -1;
	int minPath = 0;
	int i = 0;

	for ( i = 0; i < size; ++i) {
		if (minPath <= 0 || minPath > route[i][0]) {
			minPath = route[i][0];
			minIndex = i;
		}
	}

	return minIndex;
}

void printSpecficPath(Graph *graph,int *route) {
	int i = 0;

	for (i = 1; i < route[0]; ++i) {
		printf("%s->", graph->node[route[i]]->data.cityData.name);
	}
	printf("%s\n", graph->node[route[i]]->data.cityData.name);
		
}

void PrintMinValuePath(Graph *graph,int path[]) {
	int i = 0;

	for (i = 0; path[i] >= 0; ++i) {
		
		if (i == 0) {
			printf("%s", graph->node[path[i]]->data.cityData.name);
		} else {
			printf("->%s", graph->node[path[i]]->data.cityData.name);
	
		}
	}
	printf("\n");
}

void ParseRoute(Graph *graph, int start, int end, int PATHWAY) {
	int size = 0;
	int minPath = 0;
	int connectValue[MAXSPACE] = {0};
	int path[MAXSPACE][MAXSPACE] = {0};
	int visited[MAXSPACE] = {0};
	int route[MAXSPACE][MAXSPACE] = {0};
	 
	if (PATHWAY == MINVALUE) {
		DiJkstra(graph, start, connectValue, path, visited);
		PrintMinValuePath(graph,path[end]);
		return;
	}
	memset(route, -1, MAXSPACE * MAXSPACE * sizeof(int));
	size = GetTargerPath(graph, start, end, route);
	if (PATHWAY == MINPATH) {
		printSpecficPath(graph, route[GetMinPath(route,size)]);	
	} else if (PATHWAY == ALLPATH){
		printRoute(route, graph, size);
	}
	
}
