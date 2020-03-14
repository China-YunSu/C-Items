#include <stdio.h>
#include <malloc.h>

#include "./include/GraphConstruct.h"
#include "./include/Heap.h"
#include "./include/Hash.h"
#include "./include/UnionFindSet.h"
#include "./include/ModifyGraph.h"
#include "./include/Kruskal.h"

static void InitESet(ESet **eSet, Graph *graph);
static void InitESet(ESet **eSet, Graph *graph);

void InitVSet(VSet **vSet,Graph *graph) {
	InitUFSet(vSet,graph->nodeCount);
}

void InitESet(ESet **eSet, Graph *graph) {
	int i = 0;
	int t = 0;
	GraphNode *node = NULL;
	HeapItem *data = (HeapItem *) calloc(sizeof(HeapItem) , graph->edgeCount);
	int *visted = (int *) calloc(sizeof(int) , graph->nodeCount);
	InitHeap(eSet, graph->edgeCount + 1);

	for (i = 0; i < graph->nodeCount; ++i) {
		node = graph->node[i]->next;
		visted[i] = 0;
		while(node != NULL) {
			if (!visted[node->data.tab]){
				data[t].vA = graph->node[i]->data.tab;
				data[t].vB = node->data.tab;
				data[t++].edgeValue = node->data.edgeValue;
			}
			node = node->next;
		}
		visted[i] = 1;
	}
	SetHeap(*eSet, data, graph->edgeCount);

	free(visted);
	free(data);
}

void CopyCityData(Graph *MST, Graph *graph, HashTable *nameIndex) {
	int i = graph->nodeCount;
	NodeData data = {0};
	
	for (i = 0; i < graph->nodeCount; ++i) {
		data.cityData = graph->node[i]->data.cityData;
		data.tab = graph->node[i]->data.tab;
		MST->node[i] = CreatOneNode(data);
	}
	MST->nodeCount = i;
}

int Kruskal(Graph *graph, Graph **MST,HashTable *nameIndex) {
	ESet *eSet = NULL;
	VSet *vSet = NULL;

	int edgeValue = 0;
	int Ecount = 0;

	HeapItem Edata = {0};

	InitESet(&eSet,graph);
	InitVSet(&vSet,graph);
	InitGraph(MST, graph->nodeCount);
	CopyCityData(*MST, graph,nameIndex);

	while (Ecount < graph->nodeCount - 1) {
		Edata = GetData(eSet);
		if (Edata.edgeValue < 0) {
			break;
		}
		if (!CheckCycle(vSet,Edata.vA,Edata.vB)) {
			AddOneEdge(*MST, graph->node[Edata.vA]->data.tab
				,graph->node[Edata.vB]->data.tab, Edata.edgeValue);
			edgeValue += Edata.edgeValue;
		 	++Ecount;
		}

	}
	
	if (Ecount < graph->nodeCount - 1) {
		edgeValue = -1;
	}

	DestoryUFSet(&vSet);
	DestoryHeap(&eSet);
	
	return edgeValue;
}
