#ifndef _UNIONFINDSET_H_
#define _UNIONFINDSET_H_ 

typedef int UFSet;

boolean CheckCycle(UFSet *ufSet, int A, int B);
boolean InitUFSet(UFSet **ufSet, int capacity);
int Find(UFSet *ufSet, int A);
void Union(UFSet *ufSet, int A, int B);
void DestoryUFSet(UFSet **ufSet);

#endif