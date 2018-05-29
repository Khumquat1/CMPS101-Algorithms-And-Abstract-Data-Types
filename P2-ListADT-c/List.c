//-----------------------------------------------------------------------------
// List.c
// Kevin Duong
// keduong
// 1-27-17
// Implementation file for List ADT
// Based off Stack.c from examples
//-----------------------------------------------------------------------------

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data, Node prev, Node next){
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = next;
   N->prev = prev;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = NULL;
   L->length = 0;
   L->index = -1;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      Node N = (*pL)->front;
      while(N != NULL){
         Node clr = N;
         N = N->next;
         free(clr);
      }
      free(*pL);
      *pL = NULL;
   }
}

// Access functions -----------------------------------------------------------

// length()
// returns the number of elements in the List
int length(List L){
   if(L == NULL){
      printf("List Error: called length() on empty List");
      exit(1);
   }
   return L->length;
}

// index()
// Returns the index of the cursor, or -1
int index(List L){
   if(L == NULL){
      printf("List Error: called index() on NULL reference");
      exit(1);
   }
   return L->index;
}

// front()
// Returns the value at the front of L.
// Pre: length()>0
int front(List L){
   if( L==NULL ){
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns back element
// Pre: length()>0
int back(List L){
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}
// get()
// Returns cursor element
// Pre: length()>0, index()>=0
int get(List L){
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling get() on an empty List\n");
      exit(1);
   }
   if(L->index<0){
      printf("List Error: calling get() on undef reference\n");
      exit(1);
   }
   return(L->cursor->data);
}

// equals()
// Checks if List A and List B are equivalent
int equals(List A, List B){
   if(A == NULL || B == NULL) {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   if(A->length != B->length) {
      return 0;
   }
   Node C = A->front;
   Node D = B->front;
   while(C->next != NULL && D->next != NULL) {
      if(C->data != D->data)
         return 0;
      C = C->next;
      D = D->next;
   }
   return 1;
}

// Manipulation procedures ----------------------------------------------------

// clear()
// Resets list to empty state
void clear(List L){
   if (L ==NULL){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   Node N = L->front;
   while(N != NULL){
      Node temp = N;
      free(temp);
      N = N->next;
   }
   L->front = NULL;
   L->back = NULL;
   L->cursor = NULL;
   L->length = 0;
}

// moveFront()
// places cursor under the front element, or nothing
void moveFront(List L){
   if (L ==NULL){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   if(L->length >=1){
      L->cursor = L->front;
      L->index = 0;
   }
}

// moveBack()
// Places cursor under back element, or nothing
void moveBack(List L){
   if (L ==NULL){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   //int N = L->length - 1;
   if(L->length >=1){
      L->cursor = L->back;
      L->index = L->length - 1;
   }
}
// movePrev()
// Move cursor one step forward towards the front
void movePrev(List L) {
   if(L == NULL) {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(L->index != 0) {
      L->cursor = L->cursor->prev;
      --L->index;
   }
   else{
      L->cursor = NULL;
      L->index = -1;
   }
}

// moveNext()
// Move cursor one step forward towards the back
void moveNext(List L) {
   if(L == NULL) {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   int N = L->length -1;
   if(L->index != N) {
      L->cursor = L->cursor->next;
      ++L->index;
   }
   else{
      L->cursor = NULL;
      L->index = -1;
   }
}

// prepend()
// Insert new element into the list after the front
void prepend(List L, int data){
   if (L ==NULL){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   Node N = newNode(data, NULL, L->front);
   if(L->front == NULL)
      L->back = L->front = N;
   else
      L->front = L->front->prev = N;
   L->length++;
}

// append()
// Insert new element into the list after the back
void append(List L, int data){
   if (L ==NULL){
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   Node N = newNode(data, L->back, NULL);
   if(L->front == NULL)
      L-> back = L->front = N;
   else
      L-> back = L->back->next = N;
   L->length++;
}

// insertBefore()
// Insert new element before cursor
// pre: length()>0; index()>=0
void insertBefore(List L, int data){
   if( L==NULL ){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling insertBefore() on an empty List\n");
      exit(1);
   }
   if(L->index<0){
      printf("List Error: calling insertBefore() on undef reference\n");
      exit(1);
   }
   Node N = newNode(data, L->cursor->prev, L->cursor);
   if(L->cursor->prev != NULL)
      L->cursor->prev = L->cursor->prev->next= N;
   else
      L->cursor->prev = L->front = N;
   L->length++;
}

// insertAfter()
// Insert new element after cursor
// pre: length()>0; index()>=0
void insertAfter(List L, int data){
   if( L==NULL ){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling insertAfter() on an empty List\n");
      exit(1);
   }
   if(L->index<0){
      printf("List Error: calling insertAfter() on undef reference\n");
      exit(1);
   }
   Node N = newNode(data, L->cursor, L->cursor->next);
   if(L->cursor->next != NULL)
      L->cursor->next = L->cursor->next->prev= N;
   else
      L->cursor->next = L->back = N;
   L->length++;
}

// deleteFront()
// Delete the front element.
// Pre: length()>=0
void deleteFront(List L){
   if( L==NULL ){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling deleteFront() on an empty List\n");
      exit(1);
   }
   Node N;
   if(L->length > 1){ 
      N = L->front;
      L->front = L->front->next;
      L->front->prev = NULL;
   }
   else{
      N = L->front;
      L->front = L->back = NULL;
      L->cursor = NULL;
   }
   freeNode(&N);
   L->length++;
}
   
// deleteBack()
// Delete the back element.
// Pre: length()>=0
void deleteBack(List L){
   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling deleteBack() on an empty List\n");
      exit(1);
   }
   Node N;
   if(L->length > 1){ 
      N = L->back;
      L->back = L->back->prev;
      L->back->next = NULL;
   }
   else{
      N = L->back;
      L->back = L->front = NULL;
      L->cursor = NULL;
   }
   freeNode(&N);
   L->length++;
}
// delete()
// Delete cursor element
// Pre: length()>0, index()>=0
void delete(List L){
   if( L==NULL ){
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if( L->length <= 0 ){
      printf("List Error: calling delete() on an empty List\n");
      exit(1);
   }
   if(L->index<0){
      printf("List Error: calling delete() on undef reference\n");
      exit(1);
   }
   Node N = L->cursor->prev;
   N->next = L->cursor->next;
   if(N != NULL){
      L->cursor = L->cursor->next;
      L->cursor->prev = N;
   }
   L->length--;
}


// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in S on a single line to stdout.
void printList(FILE* out, List L){
   if( L==NULL ){
      fprintf(out,"Queue Error: calling printList() on NULL List reference\n");
      exit(1);
   }

   Node N = L->front;
   while(N != NULL){
      fprintf(out, "%d ", N->data);
      N = N->next;
   }
}

// copyList()
// Returns new List with same int. sequence as this list.
List copyList(List L){
   List copy = newList();
   Node N = L->front;
   while(N != NULL){
      append(copy, N->data);
      N = N->next;
   }
   return copy;
}