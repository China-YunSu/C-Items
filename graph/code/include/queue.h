#ifndef _QUEUE_H_
#define _QUEUE_H_ 

#include "boolean.h"

typedef struct QUEUE {
	void **data;
	int capacity;
	int head;
	int tail;
	boolean lastAction;
}QUEUE;

#define MAX_QUEUE_CAPACITY 1000

#define OUT 	0
#define IN  	1

boolean InitQueue(QUEUE **queueHead, const int capacity);
void DestoryQueue(QUEUE **queueHead);
boolean IsQueueEmpty(QUEUE *queueHead);
boolean IsQueueFull(QUEUE *queueHead);
boolean EnQueue(QUEUE *queueHead, void *item);
boolean OutQueue(QUEUE *queueHead, void **item);

#endif