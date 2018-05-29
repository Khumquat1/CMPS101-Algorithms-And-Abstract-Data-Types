//-----------------------------------------------------------------------------
// Kevin Duong
// keduong 
// CMPS101 - PA5
// GraphTest.c
// Test Client for Graph.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"


int main(int argc, char* argv[]){
   int i, n=19;
   List S = newList();
   Graph G = newGraph(n);
   Graph T=NULL, C=NULL;

   for(i=1; i<=n; i++) append(S, i);

   addArc(G, 1,2);
   addArc(G, 1,3);
   addArc(G, 1,5);
   addArc(G, 2,9);
   addArc(G, 3,10);
   addArc(G, 3,1);
   addArc(G, 3,5);
   addArc(G, 4,9);
   addArc(G, 5,7);
   addArc(G, 5,15);
   addArc(G, 6,14);
   addArc(G, 7,18);
   addArc(G, 8,2);
   addArc(G, 9,9);
   addArc(G, 9,13);
   addArc(G, 9,1);
   addArc(G, 10,9);
   addArc(G, 10,4);
   addArc(G, 10,7);
   addArc(G, 11,9);
   addArc(G, 11,12);
   addArc(G, 12,5);
   addArc(G, 12,6);
   addArc(G, 12,11);
   addArc(G, 13,14);
   addArc(G, 14,5);
   addArc(G, 15,13);
   addArc(G, 15,15);
   addArc(G, 16,12);
   addArc(G, 17,14);
   addArc(G, 18,11); 
   addArc(G, 19,7);
   addArc(G, 19,15);
   
   fprintf(stdout,"Adj List representation of G:\n");
   printGraph(stdout, G);
   fprintf(stdout,"\n");

   DFS(G, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "Stack: ");
   printList(stdout, S);
   fprintf(stdout, "\n");
   T = transpose(G);
   C = copyGraph(G);
   fprintf(stdout, "\n");
   fprintf(stdout, "copyGraph: \n");
   printGraph(stdout, C);
   fprintf(stdout, "\n");
   fprintf(stdout, "Transpose: \n");
   printGraph(stdout, T);
   fprintf(stdout, "\n");

   DFS(T, S);
   fprintf(stdout, "\n");
   fprintf(stdout, "x:  d  f  p\n");
   for(i=1; i<=n; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "Stack of Transpose: ");
   printList(stdout, S);
   fprintf(stdout, "\n");

   freeList(&S);
   freeGraph(&G);
   freeGraph(&T);
   freeGraph(&C);
   return(0);
}

