//-----------------------------------------------------------------------------
// Kevin Duong
// keduong 
// CMPS101 - PA4
// GraphTest.c
//Test Client for Graph.c
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
   int i, s, max, min, d, n=35;
   List  C = newList(); // central vertices 
   List  P = newList(); // peripheral vertices 
   List  E = newList(); // eccentricities 
   Graph G = NULL;

   // Build graph G 
   G = newGraph(n);
   for(i=1; i<n; i++){
      if( i%7!=0 ) addEdge(G, i, i+1);
      if( i<=28  ) addEdge(G, i, i+7);
   }
   addEdge(G, 9, 31);
   addEdge(G, 17, 13);
   addEdge(G, 14, 33);

   // Print adjacency list representation of G
//         printf("line 46\n");
   printGraph(stdout, G);

   // Calculate the eccentricity of each vertex 
    //     printf("line 49\n");
   for(s=1; s<=n; s++){
    //  printf("in for loop\n");
      BFS(G, s);
      max = getDist(G, 1);
      for(i=2; i<=n; i++){
         d = getDist(G, i);
         max = ( max<d ? d : max );
         //   printf("in for 2ndloop\n");         
      }
      append(E, max);
   }

   // Determine the Radius and Diameter of G, as well as the Central and 
   // Peripheral vertices.
   //   printf("line 61\n");
   append(C, 1);
   append(P, 1);
   min = max = front(E);
   moveFront(E);
   moveNext(E);
   for(i=2; i<=n; i++){
      d = get(E);
      if( d==min ){
         append(C, i);
      }else if( d<min ){
         min = d;
         clear(C);
         append(C, i);
      }
      if( d==max ){
         append(P, i);
      }else if( d>max ){
         max = d;
         clear(P);
         append(P, i);
      }
      moveNext(E);
   }

   // Print results 

   printf("\n");
   printf("Radius = %d\n", min);
   printf("Central vert%s: ", length(C)==1?"ex":"ices");
   printList(stdout, C);
   printf("\n");
   printf("Diameter = %d\n", max);
   printf("Peripheral vert%s: ", length(P)==1?"ex":"ices");
   printList(stdout, P);
   printf("\n");

   // Free objects 
   freeList(&C);
   freeList(&P);
   freeList(&E);
   freeGraph(&G);

   Graph Test = newGraph(150);
   for (int k = 1; k<150;++k){
      if( i%4!=1 ) addEdge(Test, k, 150-k);
      else if( k%2 == 1) addArc(Test, k, 150-k);
   }
   
   for ( int k = 1; k<150;++k){
      BFS(Test,k);
      for(i=1;i<150;++i){
         int dist = getDist(Test,i);
         if(dist != INF) printf("Distance %d=%d: %d\n",k,i,dist);        
      }    
   }
   BFS(Test, 10);
   BFS(Test, 101);
   List adj = newList();
   getPath(adj,Test,99);
   printf("path from 101 to 99: \n");
   printList(stdout,adj);
   printf("\n");
   freeList(&adj);
   freeGraph(&Test);
   return(0);
}