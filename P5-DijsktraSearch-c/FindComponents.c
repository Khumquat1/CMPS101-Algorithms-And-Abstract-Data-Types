//-----------------------------------------------------------------------------
// Kevin Duong
// keduong 
// CMPS101 - PA5
// FindComponent.c
// Client program for PA4 Graph ADT, Runs DFS on G and G' and prints scc
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"

#define MAX_LEN 160

int main(int argc, char * argv[]){

   FILE *in, *out;
   char line[MAX_LEN];
   int numVertex, i, j;

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
   
   // prep Graph and List
   List S = newList();
   for(int a = 1; a<=numVertex; ++a) append(S,a);
   Graph G = newGraph(numVertex);
   
   while( fgets(line, MAX_LEN, in) != NULL){
      sscanf(line,"%d %d", &i, &j);
      if (i == 0 && j == 0) break;
      addArc(G,i,j);
   }
   
   int scc = 0; // ini strongly connected comp.
   DFS(G,S);
   Graph Tpose = transpose(G);
   DFS(Tpose, S);
   moveFront(S);
   while(index(S) >-1){
      if(getParent(Tpose, get(S)) == NIL) scc++;
      moveNext(S);
   }
   List sccL[scc]; // List of size scc found
   for(int b = 0; b <scc; ++b) sccL[b] = newList();
   moveFront(S);
   
   int chk = scc;
   while(index(S) >-1){
      if(getParent(Tpose, get(S)) == NIL) --chk;
      if(chk == scc) break;
      append(sccL[chk],get(S));
      moveNext(S);
   }
   
   // print the results
   fprintf(out, "Adjacency list representation of G:\n");
   printGraph(out,G);
   fprintf(out, "\nG contains %d strongly connected components:", scc);
   for(int e = 0; e<scc; ++e){
      fprintf(out, "\nComponent %d: ",(e+1));
      printList(out, sccL[e]);
      freeList(&(sccL[e]));
   }
   fprintf(out,"\n");

   /* close files and free mem */
   freeGraph(&G);
   freeGraph(&Tpose);
   freeList(&S);
   fclose(in);
   fclose(out);

   return(0);
}