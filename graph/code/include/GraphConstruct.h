#ifndef _GRAPHBASECONPONENT_
#define _GRAPHBASECONPONENT_ 

#include "boolean.h"
#include "File.h"
#include "Hash.h"

typedef struct Data{
 	int edgeValue;
 	int tab;
 	CityData cityData;
}NodeData;

typedef struct GraphNode {
	NodeData data;
	struct GraphNode *next;
}GraphNode;

typedef struct Graph {
	GraphNode **node;
	int nodeCount;
	int edgeCount;
	int capacity;
}Graph;

void DestoryGraph(Graph **graph);
boolean InitGraph(Graph **graph, int capacity);
HashTable *SetGraph(Graph *graph);
void printGraph(Graph *graph);
GraphNode *CreatOneNode(NodeData data);
void GetCityData(Graph *graph, HashTable *nameIndex);
void Connetion(Graph *graph, HashTable *nameIndex);

#endif 