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

void freeGraph(Graph* pG){//Frees memory associated with a graph
  int i;
  for(i=1; i<(*pG)->order+1;i++){
    if(i==0){
      free((*pG)->neighbour[0]);
    }else{
      List *pointer; //pointer that will be used to point to the
      pointer = &(*pG)->neighbour[i];
      freeList(pointer);
    }
  }
  free((*pG)->color); //Free up memory of the arrays
  free((*pG)->parent);
  free((*pG)->distance);
  free(*pG);
  *pG = NULL;
}

//Returns the number of vertices
int getOrder(Graph G){
  if(getSource(G)==0){
    return NIL;
  }else{
    return(G->order);
  }
}

//Returns the number of edges
int getSize(Graph G){
  if(getSource(G)==0){
    return NIL;
  }else{
    return(G->size);
  }
}

//Returns the source
int getSource(Graph G){
  if(G->label==0){
    return NIL;
  }else{
    return(G->label);
  }
}

//Returns parent of a vertex
int getParent(Graph G, int u){
  if(getSource(G)==NIL){
    return NIL;
  }else{
    return(G->parent[u]);
  }
}

//Returns distance from the source to vertex
int getDist(Graph G, int u){
  if(getSource(G)==0){
    return INF;
  }else{
    return(G->distance[u]);
  }
}

//Returns the shortest path from the source to vertex u
void getPath(List L, Graph G, int u){ //Employs same recursive logic as printPath()
  int source = G->label;
  printPath(G,L,source,u);
}

//Helper method for getPath
void printPath(Graph G, List L, int s, int x){
  if(x==s){
    append(L,s);
  }else if(G->parent[x]==NIL){ //No path exists
    printf("No s-x path exists");
    return;
  }else{
    printPath(G,L,s,G->parent[x]);
    append(L,G->parent[x]);
  }
}

//Manipulation processes--------------
void addEdge(Graph G, int u, int v){
  List A = G->neighbour[u];
  List B = G->neighbour[v];

  if(length(A)==0){ //If there is nothing in A, just add v
    append(A,v);
  }else{
    moveFront(A);
    int val = get(A);
    while(index(A)!=-1){
      if(v<val){
        insertBefore(A,v);
        G->size++;
        break;
      }
      if(v>val){
        append(A, v);
        G->size++;
        break;
      }
      moveNext(A);
      val = get(A);
    }
  }
  //Perform the same things for the second list
  if(length(B)==0){ //If there is nothing in A, just add v
    append(B,u);
  }else{
    moveFront(B); //Places cursor at the Front
    int val = get(B);
    while(index(B)!=-1){
      if(u<val){
        insertBefore(B,u);
        G->size++;
        break;
      }
      if(u>val){
        append(B, u);
        G->size++;
        break;
      }
      moveNext(B);
      val = get(B);
    }
  }

}

//Adds a directed edge from u to v
void addArc(Graph G, int u, int v){
  List A = G->neighbour[u];
  if(length(A)==0){ //If there is nothing in A, just add v
    append(A,v);
  }else{
    moveFront(A);
    int val = get(A);
    while(index(A)!=-1){
      if(v<val){
        insertBefore(A,v);
        G->size++;
        break;
      }
      if(v>val){
        append(A, v);
        G->size++;
        break;
      }
      moveNext(A);
      val = get(A);
    }
  }
}

//Performs breadth first search on a graph
void BFS(Graph G, int s){
  List queue = newList();
  for(int x=1;x<G->order+1;x++){ //Initialization/Populating cells
    G->color[x]=0;
    G->parent[x]=NIL;
    G->distance[x]=INF;
  }
  G->label = s; //Set the source
  G->color[s] = 1; //Color source as gray
  G->distance[s] = 0; //Set distance from root to source as 0
  append(queue,s); //Push source onto queue

  while(length(queue)>0){
    int temp = front(queue); //Get the value at the front of the queue first before dequeing
    deleteFront(queue);
    moveFront(G->neighbour[temp]);
    for(int i=0;i<length(G->neighbour[temp]);i++){
      int adj = get(G->neighbour[temp]);
      if(G->color[adj]==0){ //If adjacent vertex is white/undiscovered
        G->color[adj]=1; //Set to gray
        G->distance[adj] = G->distance[temp]+1; //Set the distance to parents distance plus 1
        G->parent[adj] = temp; //Set the parent
        append(queue,adj); //Push the item onto the queue
      }
      moveNext(G->neighbour[temp]); //Move to the next adjacent item
    }
    G->color[temp]=2; //After checking all adjacent edges, color black
  }
  freeList(&queue); //Free up space of the associated queue
}

//Resets a graph to its original empty state
void makeNull(Graph G){
  for(int i=1;i<G->order+1;i++){
    clear(G->neighbour[i]);
    G->color[i] = 0;
    G->parent[i] = NIL;
    G->distance[i] = INF;
  }
  G->size = 0;
  G->label = 0;
}

//Prints out the graph
void printGraph(FILE* out, Graph G){
  if(G==NULL){
    printf("Calling printGraph upon a null graph reference");
    return;
  }else{
    for(int i=1; i<G->order+1; i++){
      printf("%d: ",i);
      printList(out, G->neighbour[i]);
      printf("\n");
    }
  }
}
