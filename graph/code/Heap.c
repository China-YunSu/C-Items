#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "./include/boolean.h"
#include "./include/Heap.h"

static boolean IsHeapEmpty(Heap *heap);
static boolean IsHeapFull(Heap *heap);
static void PreDown(Heap *heap, int index);
static void Heapify(Heap *heap);
static void Swap(HeapItem *dataA,HeapItem *dataB);

static void Swap(HeapItem *dataA,HeapItem *dataB) {
	HeapItem tmp = *dataA;
	*dataA = *dataB;
	*dataB = tmp;
}

HeapItem GetData(Heap *heap) {
	if (heap->count <= 0) {
		return (HeapItem) {-1,-1,-1};
	}

	Swap(&heap->data[0],&heap->data[--heap->count]);
	Heapify(heap);	
	return heap->data[heap->count];
}

static boolean IsHeapFull(Heap *heap) {
	return heap->count >= heap->capacity;
}

static boolean IsHeapEmpty(Heap *heap) {
	return heap->count <= 0;
}

void InitHeap(Heap **heap, int capacity) {
	if (NULL == heap || NULL != *heap) {
		return;
	}
	
	*heap = (Heap *) calloc(sizeof(Heap), 1);
	//TODO Error
	(*heap)->data = (HeapItem *) calloc(sizeof(HeapItem), capacity);
	(*heap)->count = 0;
	(*heap)->capacity = capacity;
}

static void PreDown(Heap *heap, int index) {
	HeapItem data = heap->data[index];
	int parent = 0;
	int minChild = 0;

	for (parent = index; 2 * parent + 1 < heap->count; parent = minChild) {
		minChild = 2 * parent + 1;
		minChild += (minChild + 1 < heap->count && heap->data[minChild].edgeValue > heap->data[minChild + 1].edgeValue);

		if (data.edgeValue <= heap->data[minChild].edgeValue) {
			break;
		}
		else {
			heap->data[parent] = heap->data[minChild];
		}
	}
	heap->data[parent] = data;	
}

static void Heapify(Heap *heap) {
	int index = 0;

	for (index = heap->count / 2 - 1; index >= 0; --index) {
		PreDown(heap,index);
	}
}

void SetHeap(Heap *heap, HeapItem data[], int size) {
	int index = 0;
	int i = 0;
	
	if (NULL == heap || size >= heap->capacity) {
		return;
	}
	
	memcpy(heap->data, data, sizeof(HeapItem) *size);
	heap->count = size;

	Heapify(heap);
}

void Insert(Heap *heap, HeapItem data) {
	int index = 0;

	if (IsHeapFull(heap)) {
		return;
	}

	for (index = heap->count; index / 2 - 1 >= 0 
				&& heap->data[index / 2 - 1].edgeValue > data.edgeValue; index /= 2) {
		heap->data[index] = heap->data[index / 2 - 1];
	}
	heap->data[index] = data;
	++heap->count;
}

void Delete(Heap *heap) {
	int parent = 0;
	HeapItem data = heap->data[heap->count - 1];
	int minChild = 0;

	if (IsHeapEmpty(heap)) {
		return;
	}

	for (parent = 0; 2 * parent + 1 < heap->count; ++parent) {
		minChild = 2 * parent + 1;
		minChild += (minChild + 1 < heap->count && heap->data[minChild].edgeValue > heap->data[minChild + 1].edgeValue);

		if (data.edgeValue <= heap->data[minChild].edgeValue) {
			break;
		}
		else {
			heap->data[parent] = heap->data[minChild];
		}
	}
	heap->data[parent] = data;
	--heap->count;
}

void DestoryHeap(Heap **heap) {
	if (NULL == heap || NULL == *heap) {
		return;
	}

	free((*heap)->data);
	free(*heap);
	*heap = NULL;
}