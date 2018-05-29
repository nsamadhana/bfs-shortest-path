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
  if(1>u || u>getOrder(G)){ //Checks preconditions
    printf("getParent() called with invalid argument");
    exit(1);
  }else{
    if(getSource(G)==NIL){
      return NIL;
    }else{
      return(G->parent[u]);
    }
  }
}

//Returns distance from the source to vertex
int getDist(Graph G, int u){
  if(1>u || u>getOrder(G)){//Checks preconditions
    printf("getDist() called with invalid argument");
    exit(1);
  }else{
    if(getSource(G)==0){
      return INF;
    }else{
      return(G->distance[u]);
    }
  }
}

//Returns the shortest path from the source to vertex u
void getPath(List L, Graph G, int u){ //Employs same recursive logic as printPath()
  if(getSource(G)!=NIL && 1<=u && u<=getOrder(G)){
    if(G->label==u){ //If at the source, append the source and finish/BASE CASE
      append(L,u);
    }else if(G->parent[u]==NIL){ //If no parent exists
      append(L,NIL);
    }else{
      getPath(L,G,getParent(G,u)); //If a parent exists, and parent is not the source, recursive call to getPath
      append(L,u);
    }
  }else{
    printf("getPath() called with either invalid graph or vertex");
    exit(1);
  }
}


//Manipulation processes--------------
void addEdge(Graph G, int u, int v){
  if(u<1 || u>getOrder(G) || v<1|| v>getOrder(G)){//Check preconditions
    printf("Calling addEdge() with invalid vertices.");
    return;
  }
  List A = G->neighbour[u]; //
  List B = G->neighbour[v];
  moveFront(A); //Place the cursor at the front
  for(int i=0;i<=length(A);i++){ //Iterate through each adjacent neighbour contained in the list
    if(index(A)==-1){ //If at the end of the list or list is empty, append
      append(A,v);
      break;
    }else if(get(A)>v){ //If the neighbour is larger, insert before
      insertBefore(A,v);
      break;
    }
    moveNext(A); //Move to the next neighbour
  }

  moveFront(B); //Perform the exact same algorithm for B
  for(int i=0;i<=length(B);i++){
    if(index(B)==-1){
      append(B,u);
      break;
    }else if(get(B)>u){
      insertBefore(B,u);
      break;
    }
    moveNext(B);
  }
  G->size++;
}

//Adds a directed edge from u to v
void addArc(Graph G, int u, int v){
  if(u<1 || u>getOrder(G) || v<1|| v>getOrder(G)){ //Check preconditions
    printf("Calling addEdge() with invalid vertices.");
    return;
  }
  List A = G->neighbour[u]; //Exact same code as addEdge(), but only on one side
  moveFront(A);
  for(int i=0;i<=length(A);i++){
    if(index(A)==-1){
      append(A,v);
      break;
    }else if(get(A)>v){
      insertBefore(A,v);
      break;
    }
    moveNext(A);
  }
  G->size++;

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
      fprintf(out, "%d: ",i);
      printList(out, G->neighbour[i]);
      fprintf(out, "\n");
    }
  }
}
