//-----------------------------------------------------------------------------
// List.h
// Kevin Duong
// keduong
// 1-27-17
// Header file for List ADT
// Based off Stack.h from examples
//-----------------------------------------------------------------------------

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_


// Exported Type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty Stack object.
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// length()
// returns the number of elements in the List
int length(List L);

// index()
// Returns the index of the cursor, or -1
int index(List L);

// front()
// Returns front element
// Pre: length()>0
int front(List L);

// back()
// Returns back element
// Pre: length()>0
int back(List L);

// get()
// Returns cursor element
// Pre: length()>0, index()>=0
int get(List L);

// equals()
// Checks if List A and List B are equivalent
int equals(List A, List B);


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets list to empty state
void clear(List L);

// moveFront()
// places cursor under the front element, or nothing
void moveFront(List L);

// moveBack()
// Places cursor under back element, or nothing
void moveBack(List L);

// movePrev()
// Move cursor one step forward towards the front
void movePrev(List L);

// moveNext()
// Move cursor one step forward towards the back
void moveNext();

// prepend()
// Insert new element into the list after the front
void prepend(List L, int data);

// append()
// Insert new element into the list after the back
void append(List L, int data);

// insertBefore()
// Insert new element before cursor
// pre: length()>0; index()>=0
void insertBefore(List L, int data);

// insertAfter()
// Insert new element after cursor
// pre: length()>0; index()>=0
void insertAfter(List L, int data);

// deleteFront()
// Delete the front element.
// Pre: length()>=0
void deleteFront(List L);

// deleteBack()
// Delete the back element.
// Pre: length()>=0
void deleteBack(List L);

// delete()
// Delete cursor element
// Pre: length()>0, index()>=0
void delete(List L);

// Other Functions ------------------------------------------------------------

// printList()
// Prints data elements in S on a single line to stdout.
void printList(FILE* out, List L);

// copyList()
// Returns new List with same int. sequence as this list.
List copyList(List L);

#endif