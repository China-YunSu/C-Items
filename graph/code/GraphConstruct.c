#include <stdio.h>
#include <malloc.h>

#include "./include/Hash.h"
#include "./include/boolean.h"
#include "./include/GraphConstruct.h"
#include "./include/File.h"
//初始化图

static void DestoryLink(GraphNode **head);

boolean InitGraph(Graph **graph, int capacity) {
	if (graph == NULL || *graph != NULL || capacity <= 0) {
		return FALSE;
	}

	*graph = (Graph *) calloc(sizeof(Graph), 1);

	(*graph)->node = (GraphNode **) calloc(sizeof(GraphNode *), capacity);
	(*graph)->capacity = capacity;

	return TRUE;
}

GraphNode *CreatOneNode(NodeData data) {
	GraphNode *res = (GraphNode *) calloc(sizeof(GraphNode), 1);
	res->data = data;
	res->next = NULL;

	return res;
}

static void DestoryLink(GraphNode **head) {
	GraphNode *del = NULL;
	
	while ((*head != NULL) && (del = (*head))) {
		*head = (*head)->next;
		free(del);
	}
}

void DestoryGraph(Graph **graph) {
	int i = 0;
	if (graph == NULL || *graph == NULL) {
		printf("filed to DestoryGraph");
		return;
	}

	for (i = 0; i < (*graph)->nodeCount; ++i) {	
		DestoryLink(&(*graph)->node[i]);
	}
	
	free((*graph)->node);
	free((*graph));
	*graph = NULL;
}

void Connetion(Graph *graph, HashTable *nameIndex) {
	GraphNode *newNode = NULL;
	int i = 0;
	int index = 0;
	char cityName[16] = {0};
	NodeData data = {0};
	FILE *pf = NULL;
	
	if ((pf = OpenConnectionFile()) == NULL) {
		printf("ConnectionFile文件无法打开\n");
		exit(0);
	}

	for (i = 0; i < graph->nodeCount; ++i) {
		GetCityName(pf, cityName);
		index = HashGet(nameIndex,cityName);
		while (!ReadEnd(pf) ) {
			GetConnectionData(pf,&data.edgeValue, cityName);
			data.tab = HashGet(nameIndex,cityName);
			
			newNode = CreatOneNode(data);
			newNode->next = graph->node[index]->next;  
			graph->node[index]->next = newNode;
			
			++(graph->edgeCount);
		}
	}
	(graph->edgeCount) /= 2;

	fclose(pf);
}

void GetCityData(Graph *graph, HashTable *nameIndex) {
	int i = 0;
	NodeData data = {0};
	FILE *pf = NULL;

	if ((pf = OpenCityInformationFile()) == NULL) {
		printf("CityInformationFile文件无法打开\n");
		return exit(0);
	}

	while (!feof(pf)) {
		data.cityData = InputInformation(pf);
		data.tab = i;
		HashPut(nameIndex,data.cityData.name,i);
		graph->node[i++] = CreatOneNode(data);
		
	}
	graph->nodeCount = i;
	fclose(pf);
}


HashTable *SetGraph(Graph *graph) {
	HashTable *nameIndex = NULL;

	InitHashTable(&nameIndex, 64);
	
	GetCityData(graph, nameIndex);
	Connetion(graph, nameIndex);
	
	return nameIndex;
}

// int main(int argc, char const *argv[]) {
// 
// 	printGraph(graph);

// 	DestoryGraph(&graph);
// 	DestoryHashTable(&nameIndex);

// 	return 0;
// }