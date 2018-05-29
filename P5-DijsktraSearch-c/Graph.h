//-----------------------------------------------------------------------------
// Kevin Duong
// keduong 
// CMPS101 - PA5
// Graph.h
// Prototypes for Graph
//-----------------------------------------------------------------------------
#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <stdio.h>
#include "List.h"
#define UNDEF -3
#define NIL 0


/*** structs ***/ 
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

#endif