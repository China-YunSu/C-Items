#include <stdio.h>

static int count = 0;

void *Calloc(int size , int cnt) {
	count += cnt;
	return calloc(size,cnt);
}


void Free(void *ptr, int cnt) {
	count -= cnt;
	return calloc(size,cnt);
}