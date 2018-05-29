//Nevan Samadhana
//SID:1539153
//pa4
//FindPath.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#include "Graph.h"
#define MAX_LEN 100

int main(int argc, char* argv[]){
  int n=0;
  int var1, var2;
  int source, destination;
  FILE *in, *out;
  //check command line for correct number of arguments
  if( argc != 3 ){
     printf("Usage: %s <input file> <output file>\n", argv[0]);
     exit(1);
  }

  in = fopen(argv[1],"r");
  out = fopen(argv[2], "w");

  if( in==NULL || out == NULL ){
     printf("Error: one or both files are invalid\n");
     exit(1);
  }

  fscanf(in, "%d", &n); //Read amount of vertices
  Graph graph = newGraph(n); //Make a graph with n vertices

  while(fscanf(in, "%d %d", &var1, &var2)!=EOF){ //While not at the end of the file
    if(var1==0 && var2==0){ //If the values are 0 and 0, break because you have hit the marker
      break;
    }
    addEdge(graph, var1, var2); //Add the edges of each vertice
  }
  printGraph(out, graph); //Print the graph
  fprintf(out ,"\n"); //Print a new line




  while(fscanf(in, "%d %d", &source, &destination)!=EOF){
    if(source==0 && destination==0){
      break;
    }
    List list = newList();
    BFS(graph, source); //Perform breadth first search on each source

    getPath(list, graph, destination); //Get the path from the source to the destination

    if(getDist(graph, destination)==INF){ //If distance is INF, that means there was no path from source to destination
      fprintf(out, "The distance from %d to %d is infinity\n", source, destination);
      fprintf(out, "No %d-%d path exists\n", source, destination);
      fprintf(out, "\n");
    }else{
      fprintf(out, "The distance from %d to %d is %d\n", source, destination, length(list)-1);
      fprintf(out, "A shortest %d-%d path is: ", source, destination);
      printList(out, list); //Prints out the shortest path to the outfile
      fprintf(out, "\n"); //Prints a newline
      fprintf(out, "\n");
    }
    clear(list);
    free(list);
    list = NULL;
  }


  fclose(in); //Close the files
  fclose(out);
  freeGraph(&graph);
  graph=NULL;
  return(0);
}
