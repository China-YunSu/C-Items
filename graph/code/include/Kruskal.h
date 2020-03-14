#ifndef _KRUSAL_H_
#define _KRUSAL_H_ 

#include "Heap.h"
#include "UnionFindSet.h"
#include "Hash.h"

typedef UFSet VSet;
typedef Heap ESet;

int Kruskal(Graph *graph, Graph **MST,HashTable *nameIndex);

#endif