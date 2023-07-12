//-----------------------------------------------------------------------------
// Tarun Sohal, cruzID: tsohal, pa4
// List.h
// Header file for List ADT (ALTERED TO BE GENERIC)
//-----------------------------------------------------------------------------

#include<stdbool.h>


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty Queue object. 
List newList();

// freeList()
// Frees all heap memory associated with Queue *pQ, and sets *pQ to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L);

// back()
// Returns back element of L. Pre: length()>0
void* back(List L);

// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
void* front(List L);

// getLength()
// Returns the length of L.
int length(List L);

// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L);


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L);

// set()
// Overwrites the cursor element’s data with x
void set(List L, void* x);

// moveFront
// If L is non-empty, sets cursor under the front element (Otherwise does nothing)
void moveFront(List L);

// moveBack
// If L is non-empty, sets cursor under the back element (Otherwise does nothing)
void moveBack(List L);

// movePrev
// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined
// do nothing.
void movePrev(List L);

// moveNext()
// If cursor is defined and not at back, move cursor one step towards the back of L;
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined,
// do nothing.
void moveNext(List L);
// prepend()
// Insert new element into L. If L is nonempty, insertion takes place before front element
void prepend(List L, void* x);

// append()
// Insert new element into L. If L is nonempty, insertion takes place after back element
void append(List L, void* x);

// insertBefore()
// Inserts a new element before cursor (PRE: length>0,index()>=0)
void insertBefore(List L, void* x);

// insertAfter()
// Inserts a new element after cursor (PRE: length>0,index()>=0)
void insertAfter(List L, void* x);

// deleteFront()
// Deletes data at front of Q.
// Pre: !isEmpty(Q)
void deleteFront(List L);

// deleteBack()
// Delete back element. (PRE: length > 0)
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined. (PRE: Length>0,index()>=0)
void delete(List L);
// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list 
// of ints to a file pointed to by out
void printList(FILE* out, List L);

// copyList()
// returns a new List representing the same integer sequence as L
// the cursor in the new list is unefined
List copyList(List L);
