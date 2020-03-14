#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <limits.h>

#include "./include/GraphConstruct.h"
#include "./include/queue.h"
#include "./include/Route.h"

typedef struct Arg {
	GraphNode **graphNode;
	int start;
	int end;
	int (*route)[MAXSPACE];
	int *visited;
	int size;
}Arg;

static void DFS(Arg *args, int visit, int index);
// boolean DoSomething(Arg *args);

// static boolean BFS(Arg *args, QUEUE *queue) {
// 	GraphNode *check = NULL;
// 	int index = args->start;
// 	int i = 0;

// 	EnQueue(queue, (void *)args->graphNode[index]);
// 	args->visited[index] = 1;
// 	while (args->route[args->size][i] != args->end && !IsQueueEmpty(queue)) {
// 		OutQueue(queue, (void **)&check);
// 		args->route[args->size][i++] = check->data.tab;
// 		while (check != NULL && ((check = check->next) != NULL)) {
// 			if ((index = check->data.tab) == args->end) {
// 				args->route[args->size][i] = args->end;
// 			}
// 			if (!args->visited[index]) {
// 				EnQueue(queue, (void *)args->graphNode[index]);
// 				args->visited[index] = 1;
// 			}
// 		}
// 	}
// 	return args->route[args->size++][i] == args->end;
// }

static void DFS(Arg *args, int visit, int index) {
	GraphNode *check = NULL;
	if (visit == args->end) {
		// args->size = index;
		// DoSomething(args);
		args->route[args->size][0] = index - 1;
		memcpy(args->route[args->size + 1],args->route[args->size], sizeof(int) * (index + 1));
		++args->size;
	}
	
	for (check = args->graphNode[visit]; check != NULL; check = check->next) {
		if ((index == 1 && check->data.tab != args->start)) {
			 continue;
		}
		
		if (!args->visited[check->data.tab]) {
			
			args->route[args->size][index] = check->data.tab;
			args->visited[check->data.tab] = 1;
		
			DFS(args, check->data.tab, index + 1);
		
			args->route[args->size][index] = -1;
			args->visited[check->data.tab] = 0;
		}
	}
}

// boolean DoSomething(Arg *args) {
// 	int i = 0;
// 	int index = 0;

// 	if (args->size <= 0) {
// 		return FALSE;
// 	}

// 	for (i = 0; i < args->size; ++i) {
// 		for (index = 0; args->route[i][index] > -1; ++index) {
// 			if (index != 0) {
// 				printf("->%s", args->graphNode[args->route[i][index]]->data.cityData.name);		
// 			} else {		
// 				printf("%s", args->graphNode[args->route[i][index]]->data.cityData.name);				
// 			} 
// 		}
// 		printf("\n");
// 	}
// 	return TRUE;
// }

void InitConnetValue(GraphNode *head, int *connectValue, int count) {
	int i = 0;

	for (; i < count; ++i) {
		connectValue[i] = GetNodeValue(head, i);	
	}
}

int GetNodeValue(GraphNode *graphNode, int tab) {
	GraphNode *check = NULL;

	for (check = graphNode->next; check != NULL; check = check->next) {
		if (check->data.tab == tab) {
			break;
		}
	} 
	return check != NULL ? check->data.edgeValue : INT_MAX;
}

void InitPath(int path[][MAXSPACE], int source,int count) {
	int i = 0;

	for (i = 0; i < count; ++i) {
		memset(path[i],-1,sizeof(int) * count);
		path[i][0] = source;	
	}

}

void PathAppend(int A[], int value) {
	int i = -1;

	while (A[++i] >= 0);

	A[i] = value;
}

int *PathCopy(int B[], int A[]) {
	int i = 0;

	for (i = 0; A[i] >= 0; ++i){
		B[i] = A[i];
	}

	return B;
}

void DiJkstra(Graph *graph, int source, int connectValue[], int path[][MAXSPACE], int visited[]) {
	int i = 0;
	int k = 0;
	GraphNode *connectNode = NULL;

	InitConnetValue(graph->node[source],connectValue, MAXSPACE);
	InitPath(path,source, MAXSPACE);
 
	visited[source] = 1;
	for (k = 1; k < graph->nodeCount; ++k) {
		int min = INT_MAX;
		int index = -1;
		for (i = (source + 1) % graph->nodeCount; i != source; i = (i + 1) % graph->nodeCount ) {
			if (visited[i] == 0 && connectValue[i] < min) {
				min = connectValue[i];
				index = i;
			}
		}
		PathAppend(path[index], index);
		visited[index] = 1;
		connectNode = graph->node[index]->next;
		while (connectNode != NULL) {
			if (visited[connectNode->data.tab] == 0 
					&& connectNode->data.edgeValue + connectValue[index] < connectValue[connectNode->data.tab]) {
				connectValue[connectNode->data.tab] = connectNode->data.edgeValue + connectValue[index];
				PathCopy(path[connectNode->data.tab], path[index]);
			}
			connectNode = connectNode->next;
		}
	}
}

// for (i = 1; i < graph->nodeCount; ++i)
// // void DestoryPath(int **path,int cnt) {
// // 	int i = 0;
// // 	for (i = 0; i < cnt; ++i) {
// // 		free(path[i]);
// // 	}
// // 	free(path);

// }

int GetTargerPath(Graph *graph, int start, int end, int route[][MAXSPACE]) {
	Arg args = {
		graph->node,		//GraphNode **graphNode;
		start,				// int start;
		end,				// int end;
		route,				// int *route;
		NULL,				// int *visited;
		0,					// int size;
	};
	
	// InitHashTable(&nameIndex, 1024);	
	//InitGraph(&graph, 1024);

	//nameIndex = SetGraph(graph);

	//printGraph(graph);

	// printf("请输入起点城市：");
	// scanf("%s",start);
	
	// printf("请输入终点城市：");
	// scanf("%s",end);
	args.visited = (int *) calloc(sizeof (int), graph->nodeCount);

	DFS(&args, start, 1);
 	// if (server == MINPATH) {
 	// 	QUEUE *queue = NULL;
		// InitQueue(&queue,900);	
 		
 	// 	BFS(&args,queue);

 	// 	DestoryQueue(&queue);
 	// }
 	
 		
	// if ( == 0) {
	// 	printf("%s城市无法到达\n",args.graphNode[args.end]->data.cityData.name);
	// } else {
	// 	//DoSomething(&args);
	// }

	//DestoryHashTable(&nameIndex);
	//DestoryGraph(&graph);
	free(args.visited);
	return args.size;
}