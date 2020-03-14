#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "./include/boolean.h"
#include "./include/UnionFindSet.h"

boolean InitUFSet(UFSet **ufSet, int capacity) {
	if (ufSet == NULL || *ufSet != NULL) {
		return FALSE;
	}

	*ufSet = (int *) calloc(sizeof(int), capacity);
	memset(*ufSet, -1, sizeof(int) * capacity);

	return TRUE;
}

void DestoryUFSet(UFSet **ufSet) {
	free(*ufSet);
	*ufSet = NULL;
}

boolean CheckCycle(UFSet *ufSet, int A, int B) {
	int rootA;
	int rootB;

	rootA = Find(ufSet, A);
	rootB = Find(ufSet, B);

	if (rootA == rootB) {
		return TRUE;
	} else {
		Union(ufSet, rootA, rootB);
		return FALSE;
	}
}

int Find(UFSet *ufSet, int A) {
	if (ufSet[A] < 0) {
		return A;
	}
	else {
		return ufSet[A] = Find(ufSet, ufSet[A]); 
	}
}

void Union(UFSet *ufSet, int A, int B) {
	if (ufSet[A] < ufSet[B]) {
		ufSet[A] += ufSet[B];
		ufSet[B] = A;
	}
	else {
		ufSet[B] += ufSet[A];
		ufSet[A] = B;	
	}
}