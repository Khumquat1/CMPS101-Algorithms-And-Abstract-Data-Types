//-----------------------------------------------------------------------------
// Kevin Duong
// keduong 
// CMPS101 - PA4
// FindPath.c
// Client program for PA4 Graph ADT
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   FILE *in, *out;
   char line[MAX_LEN];
   int numVertex, i, j, a, b;
   a = b = 0;
   

   // check command line for correct number of arguments
   if( argc != 3 ){
      printf("Usage: %s <input file> <output file>\n", argv[0]);
      exit(1);
   }

   // open files for reading and writing 
   in = fopen(argv[1], "r");
   out = fopen(argv[2], "w");
   if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }

   fgets(line,MAX_LEN,in);
   numVertex = i = j = 0;
   sscanf(line, "%d", &numVertex);
   
   // prep Graph and then sent to out
   Graph G = newGraph(numVertex);
   
   while( fgets(line, MAX_LEN, in) != NULL){
      sscanf(line,"%d %d", &i, &j);
      if (i == 0 && j == 0) break;
      addEdge(G,i,j);
   }
 //  printf("made it out\n");
   printGraph(out,G);
//   printf("done printing\n");

   // evaluate distance and path based on BFS results
   while( fgets(line, MAX_LEN, in) != NULL)  {
      sscanf(line, "%d %d", &a, &b);
      if(a == 0 && b == 0) break;
      fprintf(out, "\n");
      BFS(G, a);
      int dist = getDist(G, b);
      fprintf(out, "The distance from %d to %d is ", a, b);
      if(dist == INF)
         fprintf(out, "infinity\n");
      else
         fprintf(out, "%d\n", dist);
      List L = newList();
      getPath(L, G, b);
      if(front(L) == NIL)
         fprintf(out, "No %d-%d path exists", a, b);
      else {
         fprintf(out, "A shortest %d-%d path is: ", a, b);
         printList(out, L);
      }
      freeList(&L);
   }
   fprintf(out, "\n");
//   printf("closed it\n");

   /* close files and free mem */
   freeGraph(&G);
   fclose(in);
   fclose(out);

   return(0);
}