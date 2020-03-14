#ifndef _MODIFYGRAPH_H_
#define _MODIFYGRAPH_H_ 

#include "boolean.h"
#include "GraphConstruct.h"

boolean AddOneNode(Graph *graph, GraphNode addNode, GraphNode node[], int count);
boolean AddOneEdge(Graph *graph, int tabA, int tabB, int value);
boolean DelOneHead(Graph *graph, HashTable *nameIndex, int tab);
boolean DelOneEdge(Graph *graph, int tabA, int taB);
boolean ModifyNodeInformation(Graph *graph, int tabA, int tabB, int value);
boolean IsFull(Graph *graph);
boolean IsEmpty(Graph *graph);

#endif
