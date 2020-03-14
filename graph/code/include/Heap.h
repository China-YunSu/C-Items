#ifndef _HEAP_H_
#define _HEAP_H_ 

#include "boolean.h"

typedef struct HeapItem {
	int vA;
	int vB;
	int edgeValue;
}HeapItem;

typedef struct Heap {
	HeapItem *data;
	int count;
	int capacity;	
}Heap;

void Insert(Heap *heap, HeapItem data);
void SetHeap(Heap *heap, HeapItem data[], int size);
void Delete(Heap *heap);
void DestoryHeap(Heap **heap);
void InitHeap(Heap **heap, int capacity);
HeapItem GetData(Heap *heap);

#endif