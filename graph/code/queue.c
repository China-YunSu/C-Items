#include <stdio.h>
#include <malloc.h>

#include "./include/boolean.h"
#include "./include/queue.h"

boolean InitQueue(QUEUE **queueHead, const int capacity) {
	if (NULL == queueHead || NULL != *queueHead
			|| capacity <= 0 || capacity > MAX_QUEUE_CAPACITY) {
		return FALSE;
	}

	*queueHead = (QUEUE *) calloc(sizeof(QUEUE), 1);
	if (NULL == *queueHead) {
		return FALSE;
	}

	(*queueHead)->data = (void **) calloc(sizeof(void *), capacity);
	if ((*queueHead)->data == NULL) {
		free(*queueHead);
		*queueHead = NULL;
		return FALSE;
	}

	(*queueHead)->capacity = capacity;
	(*queueHead)->head = (*queueHead)->tail= 0;
	(*queueHead)->lastAction = OUT;

	return TRUE;
}

void DestoryQueue(QUEUE **queueHead) {
	if (NULL == queueHead || NULL == *queueHead) {
		return;
	}

	free((*queueHead)->data);
	free(*queueHead);
	*queueHead = NULL;
}

boolean IsQueueEmpty(QUEUE *queueHead) {
	return  NULL != queueHead && queueHead->lastAction == OUT &&
			queueHead->head == queueHead->tail;
}

boolean IsQueueFull(QUEUE *queueHead) {
	return  NULL != queueHead && queueHead->lastAction == IN &&
			queueHead->head == queueHead->tail;
}

boolean EnQueue(QUEUE *queueHead, void *item) {
	if (NULL == queueHead || IsQueueFull(queueHead)) {
		return FALSE;
	} 

	queueHead->data[queueHead->tail] = item;
	queueHead->tail = (queueHead->tail + 1) % queueHead->capacity;
	queueHead->lastAction = IN;

	return TRUE;
}

boolean OutQueue(QUEUE *queueHead, void **item) {
	if (NULL == queueHead || IsQueueEmpty(queueHead)) {
		return FALSE;
	}

	*item = queueHead->data[queueHead->head];
	queueHead->head = (queueHead->head + 1) % queueHead->capacity;
	queueHead->lastAction = OUT;

	return FALSE;
}



