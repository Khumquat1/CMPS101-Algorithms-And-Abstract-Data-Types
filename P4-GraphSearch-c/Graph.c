//-----------------------------------------------------------------------------
// Kevin Duong
// keduong 
// CMPS101 - PA4
// Graph.c
// PA4 Graph ADT with BFS algorithm
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"

// BFS values
#define WHITE 0
#define GRAY 1
#define BLACK 2

// structs --------------------------------------------------------------------

// private GraphObj type
struct GraphObj{
   List* adj;
   int* color;
   int* parent;
   int* distance;
   int order;
   int size;
   int source;
};

// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Graph newGraph(int n){
   Graph G = malloc(sizeof(struct GraphObj));
   G->adj = calloc(n+1,sizeof(List));
   G->color = calloc(n+1,sizeof(int));
   G->parent = calloc(n+1,sizeof(int));
   G->distance = calloc(n+1,sizeof(int));
   G->order = n;
   G->size = 0;
   G->source = NIL;
   
   for(int i =0 ; i< n+1; ++i){
      G->adj[i] = newList();
      G->color[i] = WHITE;
      G->parent[i] = NIL;
      G->distance[i] = INF;
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
      free(clr->distance);
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

// getLength()
// Returns the length of Q.
int getSource(Graph G){
   if( G==NULL ){
      fprintf(stderr,"Graph Err: calling getSource() on NULL Graph reference\n");
      exit(1);
   }
   return(G->source);
}

// getLength()
// Returns the length of Q.
int getParent(Graph G, int u){
   if( 1>u || u > getOrder(G) ){
      fprintf(stderr,"Graph Err: calling getSize() out of bounds\n");
      exit(1);
   }
   return(G->parent[u]);
}
// getDist()
// Return dist from source to vertex
// pre: 1<=u<=getOrder(G)
int getDist(Graph G, int u){
   if(getSource(G) == NIL) return INF;
   if( u<1 || u> getOrder(G) ){
      fprintf(stderr,"Graph Err: calling getDist() out of bounds\n");
      exit(1);
   }
   return(G->distance[u]);
}

// getPath()
// returns path from source to vertex
// pre: 1<=u<=getOrder(G)
void getPath(List L, Graph G, int u){
   if(getSource(G) == NIL){
      fprintf(stderr,"Graph Err: calling getSize() out of bounds\n");
      exit(1);
   }
   if( u<1 || u> getOrder(G) ){
      fprintf(stderr,"Graph Err: calling getSize() out of bounds\n");
      exit(1);
   }
   int sor = G->source;
   if(u == sor) prepend(L, sor);
   else if(G->parent[u] == NIL) append(L, NIL);
   else {
      prepend(L, u);
      getPath(L, G, G->parent[u]);
   }
}


// Manipulation procedures ----------------------------------------------------

// makeNull()
// clears graph 
void makeNull(Graph G){
   for(int i =1; i<getOrder(G);i++){
      clear(G->adj[i]);        
   }
}

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

// BFS()
// Breadth-first check on G given source s
void BFS(Graph G, int s) {
   for(int i = 0; i < (G->order + 1); ++i) {
      G->color[i] = WHITE;
      G->distance[i] = INF;
      G->parent[i] = NIL;
   }
   G->source = s;
   G->color[s] = GRAY;
   G->distance[s] = 0;
   List L = newList();
   prepend(L, s);
   while(length(L) > 0) {
      int item = back(L);
      deleteBack(L);
      List R = G->adj[item];
      moveFront(R);
      while(index(R) > -1) {
         int u = get(R);
         if(G->color[u] == WHITE){
            G->color[u] = GRAY;
            G->distance[u] = G->distance[item] + 1;
            G->parent[u] = item;
            prepend(L, u);
         }
         moveNext(R);
      }
   }
   freeList(&L); 
}


// Other Functions ------------------------------------------------------------

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