//-----------------------------------------------------------------------------
// Kevin Duong
// keduong 
// CMPS101 - PA5
// Graph.c
// PA5 Graph ADT with DFS algorithm
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// DFS values
#define WHITE 0
#define GRAY 1
#define BLACK 2

// structs --------------------------------------------------------------------

// private GraphObj type
struct GraphObj{
   List* adj;
   int* color;
   int* parent;
   int* discover;
   int* finish;
   int order;
   int size;
};

// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns pointer to new GraphObh
Graph newGraph(int n){
   Graph G = malloc(sizeof(struct GraphObj));
   G->adj = calloc(n+1,sizeof(List));
   G->color = calloc(n+1,sizeof(int));
   G->parent = calloc(n+1,sizeof(int));
   G->discover = calloc(n+1,sizeof(int));
   G->finish = calloc(n+1,sizeof(int));
   G->order = n;
   G->size = 0;
   
   for(int i =0 ; i< n+1; ++i){
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }
   return G;
}

// freeGraph()
// Frees heap memory pointed to by *pG, sets *pG to NULL.
// Private.
void freeGraph(Graph* pG){
   Graph clr = *pG;
   if( pG!=NULL && *pG!=NULL ){
      for(int i =0;i<(clr->order +1);++i){
         freeList(&(clr->adj[i]));
      }
      free(clr->discover);
      free(clr->finish);
      free(clr->parent);
      free(clr->color);
      free(clr->adj);
      free(*pG);
      *pG = NULL;
   }
}

// Access functions -----------------------------------------------------------

// getOrder()
// Returns the value at the front of Q.
// Pre: G!==NULL
int getOrder(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Err: calling getOrder() on NULL Graph reference\n");
      exit(1);
   }
   return(G->order);
}

// getSize()
// Returns the Size of G.
// Pre: G!==NULL
int getSize(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Err: calling getSize() on NULL Graph reference\n");
      exit(1);
   }
   return(G->size);
}

// getParent()
// returns the parent of given vertex
// pre: u>1, u< getOrder(g)
int getParent(Graph G, int u){
   if( 1>u || u > getOrder(G) ){
      fprintf(stderr,"Graph Err: calling getSize() out of bounds\n");
      exit(1);
   }
   return(G->parent[u]);
}

// getDiscover()
// returns the disc time of given vertex
// pre: 1<=u<=getOrder(G)
int getDiscover(Graph G, int u){
   if( u<1 || u> getOrder(G) ){
      fprintf(stderr,"Graph Err: calling getDiscover() out of bounds\n");
      exit(1);
   }
   return(G->discover[u]);
}

// getFinish returns the disc time of given vertex
// pre: 1<=u<=getOrder(G)
int getFinish(Graph G, int u){
   if( u<1 || u> getOrder(G) ){
      fprintf(stderr,"Graph Err: calling getFinish() out of bounds\n");
      exit(1);
   }
   return(G->finish[u]);
}


// Manipulation procedures ----------------------------------------------------

// addEdge()
// add edge to G from u to v
// pre: 1<=u<=getOrder(G), 1 <= v <= getOrder(G)
void addEdge(Graph G, int u, int v){
   if( u<1 || u> getOrder(G) || v<1 || v> getOrder(G) ){
      fprintf(stderr,"Graph Err: calling addEdge() out of bounds\n");
      exit(1);
   } 
   addArc(G,u,v);
   addArc(G,v,u);
   G->size--;
}

// addArc()
// add edge to G from u to v
// pre: 1<=u<=getOrder(G), 1 <= v <= getOrder(G)
void addArc(Graph G, int u, int v){
   if( u<1 || u> getOrder(G) || v<1 || v> getOrder(G) ){
      fprintf(stderr,"Graph Err: calling addArc() out of bounds\n");
      exit(1);
   } 
	List L = G->adj[u];
   moveFront(L);
	while(index(L) > -1 && v > get(L)){
      moveNext(L);
   }
   if(index(L) == -1) append(L,v);
   else insertBefore(L,v);
   G->size++;
}

// visit()
// recursive part of DFS
void Visit(Graph G, List S, int u, int* time) {
  G->color[u] = GRAY;
  G->discover[u] = ++*time;
  moveFront(G->adj[u]);
  while(index(G->adj[u])>= 0){
     int v = get(G->adj[u]);
     if(G->color[v] == WHITE){
        G->parent[v] = u;
        Visit(G,S,v,time);
     }
     moveNext(G->adj[u]);
   }
   G->color[u] = BLACK;
   G->finish[u] = ++*time;
   prepend(S,u);
}

// DFS()
// Depth first check on G in order S
void DFS(Graph G, List S) {
   if(length(S) != getOrder(G)){
      fprintf(stderr, "Graph Error: called DFS() without matching lengths\n");
      exit(1);
   }
   for(int i = 0; i <= getOrder(G); ++i) {
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->discover[i] = UNDEF;
      G->finish[i] = UNDEF;
   }
   int time = 0;
   moveFront(S);
   while(index(S)>=0){
      int u = get(S);
      if (G->color[u] == WHITE){
         Visit(G,S,u, &time);
      }
      moveNext(S);
   }
   for(int j = length(S)/2; j>0; --j) deleteBack(S);
}


// Other Functions ------------------------------------------------------------

// transpose()
// returns transpose of graph G
Graph transpose (Graph G){
   Graph Tpose = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(G); ++i){
      moveFront(G->adj[i]);
      while(index(G->adj[i]) > -1){
         addArc(Tpose, get(G->adj[i]), i);
         moveNext(G->adj[i]);
      }
   }
   return Tpose;
}

// copyGraph()
// returns copy of G
Graph copyGraph(Graph G){
   Graph cpy = newGraph(getOrder(G));
   for(int i = 1; i <= getOrder(G); ++i){
      moveFront(G->adj[i]);
      while(index(G->adj[i])>-1){
         addArc(cpy, i, get(G->adj[i]));
         moveNext(G->adj[i]);
      }
   }
   return cpy;
}

// printGraph()
// prints each row number followed but adj. list for each row
void printGraph(FILE* out, Graph G){
   if( G==NULL || out ==NULL){
      printf("Queue Error: calling printQueue() on NULL Queue reference\n");
      exit(1);
   }

   for(int i = 1; i <= getOrder(G); ++i){
      fprintf(out,"%d: ",i);
      printList(out,G->adj[i]);
      fprintf(out, "\n");
   }
}

