//-----------------------------------------------------------------------------
// pa4
// Tarun Sohal, CruzID: tsohal
// List.C (ALTERED TO BE GENERIC)
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   void* data;
   Node next;
   Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
   Node front;
   Node cursor;
   Node back;
   int length;
   int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* data){
   Node N = malloc(sizeof(NodeObj));
   N->data = data; // need to malloc data for void*
   N->next = NULL;
   N->prev = NULL; 
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty Queue object.
List newList(){
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1; //default value for undefined index
   return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL){
   if(pL!=NULL && *pL!=NULL) { 
      while( !isEmpty(*pL) ) { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------


// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L) {
   return L->index;
}

// back()
// Returns POINTER to back element of L. Pre: length()>0
void* back(List L) {
   if( L==NULL ){
      printf("List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(isEmpty(L)) {
      printf("List Error: called back() on empty list\n");
      exit(EXIT_FAILURE);
   }
return L->back->data;
}

// get()
// Returns POINTER to  cursor element of L. Pre: length()>0, index()>=0
void* get(List L) {
   if( L==NULL ){
      printf("List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(isEmpty(L)) {
      printf("List Error: called get() on empty list\n");
      exit(EXIT_FAILURE);
   }
return L->cursor->data;
}

// front()
// Returns POINTER to the value at the front of Q.
// Pre: !isEmpty(Q)
void* front(List L) {
   if( L==NULL ){
      printf("List Error: calling getFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(isEmpty(L)) {
      printf("List Error: called back() on empty list\n");
      exit(EXIT_FAILURE);
   }
return L->front->data;
}

// length()
// Returns the length of Q.
int length(List L) {
   if( L==NULL ){
      printf("List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length);
}

// isEmpty()
// Returns true if L is empty, otherwise returns false.
bool isEmpty(List L) {
   if(L==NULL) {
      printf("List Error: calling isEmpty() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->length==0);
}
//isCursorSet()
//returns true if index of L is set, otherwise returns false
bool isIndex(List L) {
   if(L==NULL) {
      printf("List Error: calling isIndex() on a NUll List reference\n");
      exit(EXIT_FAILURE);
   }
   return(L->index!=-1);
}



// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L) {
   //check to see if pointer is null
   if(L != NULL) {
      //empty list by using deleteFront
      while(!isEmpty(L)) {
         deleteFront(L);
      }
   }
}

// set()
// Overwrites the cursor element’s data with x
void set(List L, void* x) {
   //check to see if list is empty
   if(isEmpty(L)) {
      printf("List Error: calling set() on empty list\n");
      exit(EXIT_FAILURE);
   }
   //check to see if cursor is set
   if(!(isIndex(L))) {
      printf("List Error: calling set() on a list with no cursor\n");
      exit(EXIT_FAILURE);
   }
   //overwrite the data
   L->cursor->data = x;
}

// moveFront
// If L is non-empty, sets cursor under the front element (Otherwise does nothing)
void moveFront(List L) {
   //check to see if L is nonempty
   if(isEmpty(L)) {
      printf("List Error: calling moveFront() on an empty list\n");
      exit(EXIT_FAILURE);
   }
   //set cursor to front node of list
   L->cursor = L->front;
   //set index to correct place
   L->index = 0;
}

// moveBack
// If L is non-empty, sets cursor under the back element (Otherwise does nothing)
void moveBack(List L) {
    //check to see if L is nonempty
   if(isEmpty(L)) {
      printf("List Error: calling moveBack() on an empty list\n");
      exit(EXIT_FAILURE);
   }
   //set cursor to back node of list
   L->cursor = L->back;
   //set index to correct place
   L->index = L->length-1;
}

// movePrev
// If cursor is defined and not at front, move cursor one step toward the front of L;
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined
// do nothing.
void movePrev(List L) {
   //if cursor is defined
   if(isIndex(L)) {
      // If cursor is not at front, move cursor one step toward the front of L;
      if(L->front !=L->cursor) {
         L->cursor = L->cursor->prev;
         L->index--;
      }
      // if cursor is at front, cursor becomes undefined;
      else if(L->front ==L->cursor) {
         L->index = -1;
         L->cursor = NULL;
      }
   }
   //else, do nothing
   else {
      printf("List Error: calling movePrev on undefined cursor\n");
      exit(EXIT_FAILURE);
   }
}

// moveNext()
// If cursor is defined and not at back, move cursor one step towards the back of L;
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined,
// do nothing.
void moveNext(List L) {
   //if cursor is defined
   if(isIndex(L)) {
      if(L->cursor != L->back) {
      // If cursor is not at back, move cursor one step towards the back of L
         L->cursor = L->cursor->next;
         L->index++;
      }
      //If cursor is at back, cursor becomes undefined
      else if (L->cursor == L->back) {
         L->cursor = NULL;
         L->index = -1;
      }
   }
   //else, do nothing
   else {
      printf("List Error: calling moveNext on undefined cursor\n");
      exit(EXIT_FAILURE);
   }
}
// prepend()
// Insert new element into L. If L is nonempty, insertion takes place before front element
void prepend(List L, void* x) {
   //create new node with data x
   Node N = newNode(x);
   if(L == NULL) {
      printf("List Error: Called prepend() on NULL reference\n");
      exit(EXIT_FAILURE);
   }
   if(!isEmpty(L)) {
      //set N's next node to front of list
      N->next = L->front;
      //set front of list's previous node to N
      L->front->prev = N;
      //set front of list to N
      L->front = N;
      //if cursor is defined, move up 1
      if(isIndex(L)) {
         L->index++;
      }
   } else {
      L->front = L->back = N;
   }
   L->length++;
}

// append()
// Insert new element into L. If L is nonempty, insertion takes place after back element
void append(List L, void* x) {
   //create a new node
   Node N = newNode(x);
   if(L == NULL) {
      printf("List Error: Called append() on NULL reference\n");
      exit(EXIT_FAILURE);
   }
   //case where list isn't empty
   if(!isEmpty(L)) {
      //set N's previous node to back of list
      N->prev = L->back;
      //set back of list's next node to N
      L->back->next = N;
      //set back of list to point to N 
      L->back = N;
   //case where list is empty
   } else {
      L->front = L->back = N;
   }
   L->length++;
}

// insertBefore()
// Inserts a new element before cursor (PRE: length>0,index()>=0)
void insertBefore(List L, void* x) {
   if(isEmpty(L)) {
      printf("List Error: calling insertBefore() on an empty list");
      exit(EXIT_FAILURE);
   }
   if(!isIndex(L)) {
      printf("List Error: calling insertBefore() on an undefined index");
      exit(EXIT_FAILURE);
   }
   //check to see if insert aligns with prepend
   if(L->cursor == L->front) {
      prepend(L,x);
   } else {
      //create a new node
      Node N = newNode(x);
      //set back node to point to N
      L->cursor->prev->next = N;
      //set N's prev node to point to back node
      N->prev  = L->cursor->prev;
      //set cursor's prev to point to N
      L->cursor->prev = N;
      //set N's next node to point to cursor
      N->next = L->cursor;
      L->length++;
      //set index to correct place
      L->index++;
   }
   //set index to correct place
}

// insertAfter()
// Inserts a new element after cursor (PRE: length>0,index()>=0)
void insertAfter(List L, void* x) {
   if(isEmpty(L)) {
      printf("List Error: calling insertBefore() on an empty list");
      exit(EXIT_FAILURE);
   }
   if(!isIndex(L)) {
      printf("List Error: calling insertBefore() on an undefined index");
      exit(EXIT_FAILURE);
   }
   //check to see if cursor aligns with append
   if(L->cursor == L->back) {
      append(L,x);
   } else {
      //create a new node
      Node N = newNode(x);
      //set cursor's next previous node to point to N
      L->cursor->next->prev = N;
      //set N's next and prev
      N->next = L->cursor->next;
      N->prev = L->cursor;
      //set L's next node to cursor
      L->cursor->next = N;
      L->length++;
      }
}

// deleteFront()
// Deletes data at front of Q.
// Pre: !isEmpty(L)
void deleteFront(List L) {
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling deleteFront on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(EXIT_FAILURE);
   }
   N = L->front;
   //if cursor is at front of list
   if(L->cursor == L->front) {
      L->cursor = NULL;
      L->index = -1;
   }
   if(length(L)>1 ) { 
      L->front->next->prev = NULL;
      L->front = L->front->next;
      //set index to right place
      if(isIndex(L)) {
         L->index--;
      } 
   }else{ 
      L->front = L->cursor = L->back = NULL; 
      L->cursor = NULL;
      L->index = -1;
   }
   L->length--;
   freeNode(&N);
}

// deleteBack()
// Delete back element. (PRE: length > 0)
void deleteBack(List L) {
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling deleteBack on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteBack on an empty List\n");
      exit(EXIT_FAILURE);
   }
   N = L->back;
   //if cursor is at back element and is deleted
   if(L->cursor == L->back) {
      L->cursor = NULL;
      L->index = -1;
   }
   if(length(L)>1 ) {
      //set the next back's prev node to NULL
      L->back->prev->next = NULL;
      //change List's back
      L->back = L->back->prev;
   } else {
      L->back = L->cursor = L->front = NULL;
      L->index = -1;
   }
   L->length--;
   freeNode(&N);
   //need to account for when cursor is deleted
}

// delete()
// Delete cursor element, making cursor undefined. (PRE: Length>0,index()>=0)
void delete(List L) {
   Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling delete on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if(isEmpty(L) ){
      printf("List Error: calling delete on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if(!isIndex(L)) {
      printf("List Error: calling delete on undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   //point N to cursor node
   N = L->cursor;
   //case where cursor is at front
   if(L->cursor ==L->front) {
      deleteFront(L);
   }
   //case where cursor is at back
   else if(L->cursor == L->back) {
      deleteBack(L);
   }
   //normal case where nodes sandwhich cursor
   else {
      //link nodes that sandwich cursor to each other
      L->cursor->next->prev = L->cursor->prev;
      L->cursor->prev->next = L->cursor->next;
      L->length--;
      //free memory associated with N
      freeNode(&N);
   }
   //cursor always becomes undefined
   L->cursor = NULL;
   L->index = -1;
}
// Other Functions ------------------------------------------------------------

// printList()
// Prints a string representation of L consisting of a space separated list 
// of ints to a file pointed to by out
// void printList(FILE* out, List L) {
//    //check to see if List is empty
//    if(isEmpty(L)) {
//       //just print a newline
//       printf("\n");
//    } else {  
//       //saves index for later
//       int x = index(L);
//       //move cursor to front of list
//       moveFront(L);
//       //while list isn't empty, use moveForward and cursor to get data
//       for(int i = 0; i < length(L); i++) {
//          int data = get(L);
//          //print out data to out
//          fprintf(out,"%d",data);
//          fprintf(out," ");
//          //move to next element
//          moveNext(L);
//       }
//       //set cursor back to original place
//       moveFront(L);
//       for(int i = 0; i < x; i++) {
//          moveNext(L);
//       }
//    }
// }