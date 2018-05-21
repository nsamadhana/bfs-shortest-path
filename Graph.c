//Nevan Samadhana
//SID:1539153
//pa4
//Graph.c
#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

//Structs------------------
typedef struct GraphObj{
  int order; //number of vertices
  int size; //number of edges
  int label;
  List *neighbour;
  int *color;
  int *parent;
  int *distance;
} GraphObj;

//Constructor for a graph
Graph newGraph(int n){
  int i;
  Graph nGraph = malloc(sizeof(GraphObj));
  nGraph->order = n; //Set number of vertices to n
  nGraph->size = 0; //Set number of edges to 0
  nGraph->label = 0;
  nGraph->neighbour = calloc(n+1,sizeof(List)); //Calloc memory for each array
  nGraph->color = calloc(n+1, sizeof(int));
  nGraph->parent = calloc(n+1, sizeof(int));
  nGraph->distance = calloc(n+1, sizeof(int));
  for(i=1;i<n+1;i++){
    nGraph->neighbour[i] = newList(); //Populate each indice of the array with an empty List
    nGraph->color[i] = 0;
    nGraph->parent[i] = NIL;
    nGraph->distance[i] = INF;
  }
  return nGraph;
}
