//Nevan Samadhana
//SID:1539153
//pa4
//Graph.h
//Header file for Graph
#ifndef _Graph_H_Include
#define _Graph_H_Include
#include "List.h"
//Macros------------------
#define INF -1 //Infinity represented as -1
#define NIL -2 //Nil, represented as -2
typedef struct GraphObj* Graph;
Graph newGraph(int n);

void freeGraph(Graph* pG);

int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

void printPath(Graph G, List L, int s, int x);

void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

void printGraph(FILE* out, Graph G);


#endif
