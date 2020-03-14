@echo off
gcc -c Hash.c -o Hash.o
gcc -c File.c -o File.o
gcc -c GraphConstruct.c -o GraphConstruct.o
gcc -c queue.c -o queue.o
gcc -c UnionFindSet.c -o UnionFindSet.o
gcc -c Heap.c -o Heap.o
gcc -c ModifyGraph.c -o ModifyGraph.o
gcc -c Kruskal.c -o Kruskal.o
gcc -c Route.c -o Route.o
gcc -c ParseRoute.c -o ParseRoute.o

gcc view.c ParseRoute.o Route.o GraphConstruct.o queue.o File.o Hash.o Heap.o Kruskal.o UnionFindSet.o ModifyGraph.o -o view