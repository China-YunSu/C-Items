#include <stdio.h>
#include <malloc.h>

#include "./include/GraphConstruct.h"
#include "./include/Hash.h"
#include "./include/boolean.h"
#include "./include/ModifyGraph.h"

static boolean InsertNode(GraphNode *head,GraphNode *insertNode);
static boolean RemoveLinkNode(GraphNode *head, int tab);
static boolean IsHadNode(GraphNode *head, int tab);
static void DestoryLink(GraphNode *head);

boolean ModifyNodeInformation(Graph *graph, int tabA, int tabB, int value) {
	GraphNode *check = NULL;

	if (tabA < 0 || tabB < 0 || graph == NULL || graph->node[tabA] == NULL) {
		printf("Filed to ModifyNodeInformation\n");
		return FALSE;
	} 

	for (check = graph->node[tabA]->next; check != NULL; check = check->next) {
		if (check->data.tab == tabB) {
			check->data.edgeValue = value;
			return TRUE;
		}
	}

	return FALSE;
}	

boolean DelOneEdge(Graph *graph, int tabA, int tabB) {
	boolean res = TRUE;
	
	if (tabA < 0 || tabB < 0 || graph == NULL) {
		printf("Filed to DelOneEdge\n");
		return FALSE;
	}
	res = RemoveLinkNode(graph->node[tabA], tabB) + RemoveLinkNode(graph->node[tabB], tabA);
	if (res == TRUE * 2) {
		--graph->edgeCount;
		return TRUE;
	}

	return FALSE;
}

boolean IsEmpty(Graph *graph) {
	return graph->nodeCount <= 0;
}

boolean IsFull(Graph *graph) {
	return graph->nodeCount >= graph->capacity;
}

boolean DelOneHead(Graph *graph, HashTable *nameIndex, int tab) {
	int index = 0;
	int row = 0;
	if (tab < 0 || graph == NULL ||IsEmpty(graph)) {
		printf("Filed to DelOneHead\n");
		return FALSE;
	}

	DestoryLink(graph->node[tab]);

	for (row = 0; row < graph->nodeCount; ++row) {
		GraphNode *check = graph->node[row]->next;
		//删除目标行
		if (row == tab) {
			for (index = tab; index + 1 < graph->nodeCount; index++) {
				graph->node[index] = graph->node[index + 1];
				graph->node[index]->data.tab = index;
				  
			}
			--graph->nodeCount;
		}
		//修改节点指向
		while (check != NULL) {
			if (check->data.tab > tab) {
				check->data.tab -= 1;
			}
			check = check->next;
		}
		//删除连接
		graph->edgeCount -= RemoveLinkNode(graph->node[row], tab);
	}
}

boolean AddOneEdge(Graph *graph, int tabA, int tabB, int value) {
	boolean res = TRUE;
	if (tabA < 0 || tabB < 0) {
		printf("Filed to AddOneEdge\n");
		return FALSE;
	}
	
	res += InsertNode(graph->node[tabA],CreatOneNode((NodeData){value,tabB,{0}}));
	res += InsertNode(graph->node[tabB],CreatOneNode((NodeData){value,tabA,{0}}));
	
	if (res == TRUE * 2) {
		--graph->edgeCount;
		return TRUE;
	}

	return FALSE;
}

boolean AddOneNode(Graph *graph, GraphNode addNode, GraphNode node[], int count) {
	int i = 0;
	if (graph == NULL || IsFull(graph)) {
		printf("Filed to AddOneNode\n");
		return FALSE;
	}

	graph->node[graph->nodeCount] = CreatOneNode(addNode.data);

	for (i = 0; i < count; ++i) {
		graph->edgeCount += InsertNode(graph->node[graph->nodeCount],CreatOneNode(node[i].data));
		InsertNode(graph->node[node[i].data.tab],CreatOneNode((NodeData){node[i].data.edgeValue,addNode.data.tab,{0}}));			
	}
	++graph->nodeCount;
}

static boolean IsHadNode(GraphNode *head, int tab) {
	GraphNode *check = head->next;

	while(check != NULL && check->data.tab != tab) {
		check = check->next;
	}	

	return check != NULL;
}

static boolean InsertNode(GraphNode *head,GraphNode *insertNode) {	
	
	if (head == NULL || insertNode == NULL) {
		printf("Filed to InsertNode\n");
		return FALSE;
	}

	if (IsHadNode(head,insertNode->data.tab)) {
		printf("InsertNode : IsHadNode\n");
		return FALSE;
	}
	
	GraphNode *tmp = head->next;
	head->next = insertNode;
	insertNode->next = tmp;
	
	return TRUE;
}

static void DestoryLink(GraphNode *head) {
	GraphNode *del = NULL;
	
	if (head == NULL) {
		return;
	}

	while (head != NULL && (del = head)) {
		head = head->next;
		free(del);
	}
}

static boolean RemoveLinkNode(GraphNode *head, int tab) {
	GraphNode *pre = head;
	GraphNode *cur = head->next;

	if (head == NULL) {
		printf("File to RemoveLinkNode:\n");
	}
	while (cur != NULL && cur->data.tab != tab) {
		pre = cur;
		cur = cur ->next;
	}

	if (cur == NULL)  {
		return FALSE;
	}
	pre->next = cur->next;
	free(cur);
	return TRUE;
}

// int main(int argc, char const *argv[]) {

// 	Graph *graph = NULL;
// 	HashTable *nameIndex = NULL;

// 	char cityA[8] = {0};
// 	char cityB[8] = {0};

// 	InitHashTable(&nameIndex, 1024);	
// 	InitGraph(&graph, 1024);

// 	nameIndex = SetGraph(graph);

// 	printGraph(graph);

// 	printf("ÇëÊäÈëÁ¬½Ó³ÇÊÐ1£º");
// 	scanf("%s", cityA);
// 	printf("ÇëÊäÈëÁ¬½Ó³ÇÊÐ2£º");
// 	scanf("%s", cityB);
// 	printf(" %d ",graph->nodeCount);
// 	printf("%d\n",graph->edgeCount);
// 	AddOneEdge(graph, HashGet(nameIndex,cityA), HashGet(nameIndex,cityB), 90);
// 	printf("finshed");
// 	//DelOneHead(graph, HashGet(nameIndex,cityA));
// 	//DelOneEdge(graph, HashGet(nameIndex,cityA), HashGet(nameIndex,cityB));
// 	printf(" %d ",graph->nodeCount);
// 	printf("%d\n",graph->edgeCount);
	
// 	printGraph(graph);

// 	return 0;
// }