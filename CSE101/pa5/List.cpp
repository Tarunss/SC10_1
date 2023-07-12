//-----------------------------------------------------------------------------
// tsohal
// List ADT
// Implementation of a List ADT in C++
//-----------------------------------------------------------------------------
#include<string>
#include<iostream>
#include<stdexcept>
#include"List.h"


// Private Constructor --------------------------------------------------------

// we have typedef'd listElement as an int for now
// Node constructor
List::Node::Node(ListElement x){
   data = x;
   next = nullptr;
   prev = nullptr;
}


// Class Constructors & Destructors -------------------------------------------

// Creates new List in the empty state.
List::List(){
   Node* F = new Node(0);
   Node* B = new Node(0);
   frontDummy = F;
   backDummy = B;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   pos_cursor = 0;
   num_elements = 0;
}

// Copy constructor.
List::List(const List& L){

   // make this an empty List
   Node* F = new Node(0);
   Node* B = new Node(0);
   frontDummy = F;
   backDummy = B;
   frontDummy->next = backDummy;
   backDummy->prev = frontDummy;
   beforeCursor = frontDummy;
   afterCursor = backDummy;
   // if S is non-empty, load its elements into this new List
   if(L.frontDummy->next != L.backDummy) {
      Node* N = L.frontDummy->next;
      Node* M = new Node(N->data);
      frontDummy->next = M;
      M->next = backDummy;
      M->prev = frontDummy;
      backDummy->prev = M;
      while(N->next != L.backDummy) {
         N = N->next;
         M->next = new Node(N->data);
         M->next->prev = M;
         M = M->next;
         backDummy->prev = M;
         M->next = backDummy;
      }
      num_elements = L.num_elements;
      //put cursor in right place
      moveFront();
      while(pos_cursor != L.pos_cursor) {
         moveNext();
      }
   }
   else {
      //list is empty, set cursor appropriately
      beforeCursor = backDummy;
      afterCursor = frontDummy;
      num_elements = 0;
      pos_cursor = 0;
   }
}

// Destructor
List::~List(){
   //delete all the elements in the List
   // while(num_elements>0 ){
   //    Node* N = frontDummy;
   //    frontDummy = N->next;
   //    //num_elements--;
   //    delete N;
   // }
   clear();
    delete frontDummy;
    delete backDummy;
   // delete afterCursor;
   // delete beforeCursor;
}


// Access functions -----------------------------------------------------------
// length()
   // Returns the length of this List.
   int List::length() const{
      return num_elements;
   }

   // front()
   // Returns the front element in this List.
   // pre: length()>0
   ListElement List::front() const {
      if(length() <= 0) {
         throw std::length_error("error: calling front() on empty list\n");
      }
      return frontDummy->next->data;
   }

   // back()
   // Returns the back element in this List.
   // pre: length()>0
   ListElement List:: back() const {
      if(num_elements <= 0) {
         throw std::length_error("error: calling back() on empty list\n");
      }
      return backDummy->prev->data;
   }

   // position()
   // Returns the position of cursor in this List: 0 <= position() <= length().
   int List::position() const {
      if(!(0 <= pos_cursor || pos_cursor <= num_elements)) {
         throw std::range_error("error: position(): pos_cursor out of bounds");
      }
      return pos_cursor;
   }

   // peekNext()
   // Returns the element after the cursor.
   // pre: position()<length()
   ListElement List::peekNext() const {
      if(pos_cursor >= num_elements) {
         throw std::range_error("error: peekNext(): pos_cursor >= num_elements\n");
      }
      return afterCursor->data;
   }

   // peekPrev()
   // Returns the element before the cursor.
   // pre: position()>0
   ListElement List::peekPrev() const {
      if(pos_cursor <= 0) {
         throw std::range_error("error: peekPrev(): pos_cursor <= num_elements\n");
      }
      return beforeCursor->data;
   }


   // Manipulation procedures -------------------------------------------------

   // clear()
   // Deletes all elements in this List, setting it to the empty state.
   void List::clear() {
      //just call eraseAfter alot I guess
      //td::cout<<"IN CLEAR FUNCITON"<<std::endl;
         //std::cout<<"IN CLEAR FUNCITON"<<std::endl;
         int x = num_elements;
         //std::cout<<"IN CLEAR FUNCITON"<<std::endl;
         moveFront();
         for(int i = 0; i < x; i++) {
            moveFront();
            eraseAfter();
         //std::cout<<"ERASING "<<std::endl;
         }
   }  

   // moveFront()
   // Moves cursor to position 0 in this List.
   void List::moveFront() {
      //set pos_cursor to 0
       pos_cursor = 0;
       //set the afterCursor to first element
       afterCursor = frontDummy->next;
       beforeCursor = frontDummy;
   }

   // moveBack()
   // Moves cursor to position length() in this List.
   void List::moveBack() {
      //set pos_cursor to length
      pos_cursor = num_elements;
      //set beforeCursor to length - 1
      beforeCursor = backDummy->prev;
      afterCursor = backDummy;
   }

   // moveNext()
   // Advances cursor to next higher position. Returns the List element that
   // was passed over. 
   // pre: position()<length() 
   ListElement List:: moveNext() {
      if(pos_cursor >= num_elements) {
         throw std::range_error("error: moveNext(): pos_cursor >= num_elements\n");
      }
      //basically, we increment both before and aftercursor
      
      //regular case:
      if(afterCursor->next != nullptr) {
         afterCursor = afterCursor->next;
      }
      if(beforeCursor->next != afterCursor) {
      beforeCursor = beforeCursor->next;
      }
      pos_cursor++;
      return beforeCursor->data;
   }

   // movePrev()
   // Advances cursor to next lower position. Returns the List element that
   // was passed over. 
   // pre: position()>0
   ListElement List:: movePrev() {
      if(pos_cursor <= 0) {
         throw std::range_error("error: movePrev(): pos_cursor <= 0\n");
      }
      //case where position is at back

      if(beforeCursor->prev != nullptr) {
         beforeCursor = beforeCursor->prev;
      }
      if(afterCursor->prev != beforeCursor) {
         afterCursor = afterCursor->prev;
      }
      pos_cursor--;
      return afterCursor->data;
   }
//For all insertions, the case where the list is empty must be accounted for
   // insertAfter()
   // Inserts x after cursor.
   void List::insertAfter(ListElement x) {
      //create a new node
      Node* N = new Node(x);
      //case where list is empty
      if(frontDummy->next == backDummy) {
        //std::cout<<"inserting into empty list.." <<N->data<<std::endl;
        N->next = backDummy;
        N->prev = frontDummy;
        frontDummy->next = N;
        backDummy->prev = N;
        //change where cursor lies after insert
        afterCursor = backDummy->prev;
        beforeCursor = frontDummy;
      }
      else {
         //std::cout<<"inserting into non empty list..." <<N->data<<std::endl;
         beforeCursor->next = N;
         N->prev = beforeCursor;
         N->next = afterCursor;
         afterCursor->prev = N;
         //change where cursor lies
         afterCursor = afterCursor->prev;
      }
      num_elements++;
   }

   // insertBefore()
   // Inserts x before cursor.
   void List::insertBefore(ListElement x) {
      Node* N = new Node(x);
      if(frontDummy->next == backDummy) {
        N->next = backDummy;
        N->prev = frontDummy;
        frontDummy->next = N;
        backDummy->prev = N;
        //change where cursor lies
        afterCursor = backDummy;
        beforeCursor = frontDummy->next;
        pos_cursor++;
      }
      else {
         //same as insertAfter, however pos_cursor increases and cursors are incremented
         beforeCursor->next = N;
         N->prev = beforeCursor;
         N->next = afterCursor;
         afterCursor->prev = N;
         //change where cursor lies
         beforeCursor = beforeCursor->next;
         pos_cursor++;
      }
      num_elements++;
   }

   // setAfter()
   // Overwrites the List element after the cursor with x.
   // pre: position()<length()
   void List::setAfter(ListElement x) {
      if(!(pos_cursor < num_elements)) {
         throw std::range_error("error: setAfter(): position >= length\n");
      }
      //sets aftercursor data with x
      afterCursor->data = x;
   }

   // setBefore()
   // Overwrites the List element before the cursor with x.
   // pre: position()>0
   void List::setBefore(ListElement x) {
      if(!(pos_cursor > 0)) {
         throw std::range_error("error: setBefore(): position <= 0\n");
      }
      //sets beforeCursor data with x
      beforeCursor->data = x;
   }

   // eraseAfter()
   // Deletes element after cursor.
   // pre: position()<length()
   void List::eraseAfter() {
      if(!(pos_cursor < num_elements)) {
         throw std::range_error("error: eraseAfter(): position >= length\n");
      }
      if(num_elements != 0) {
         Node* N = afterCursor;
         beforeCursor->next = afterCursor->next;
         afterCursor->next->prev = beforeCursor;
         afterCursor = afterCursor->next;
         num_elements--;
         delete N;
      }
   }

   // eraseBefore()
   // Deletes element before cursor.
   // pre: position()>0
   void List::eraseBefore() {
      if(!(pos_cursor > 0)) {
         throw std::range_error("error: eraseBefore(): position <= 0\n");
      }
      if(num_elements > 1) {
         Node* N = beforeCursor;
         afterCursor->prev = beforeCursor->prev;
         beforeCursor->prev->next = afterCursor;
         beforeCursor = beforeCursor->prev;
         num_elements--;
         pos_cursor--;
         //std::cout<<N->data <<std::endl;
         delete N;
      } else if(num_elements == 1) {
         Node* N = frontDummy->next;
         afterCursor = backDummy;
         beforeCursor = frontDummy;
         num_elements--;
         pos_cursor = 0;
         //std::cout<<N->data <<std::endl;
         delete N;
      }
   }


   // Other Functions ---------------------------------------------------------

   // findNext()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction front-to-back) for the first occurrence of element x. If x
   // is found, places the cursor immediately after the found element, then 
   // returns the final cursor position. If x is not found, places the cursor 
   // at position length(), and returns -1. 
   int List::findNext(ListElement x) {
      //if the cursor is at the back of list, return -1
      if(afterCursor == backDummy) {
         return -1;
      }
      //else, move cursor, and check to see if it is x
      while (pos_cursor < num_elements) {
         int a = moveNext();
         if(a == x) {
            return pos_cursor;
         }
      }
      return -1;
   }

   // findPrev()
   // Starting from the current cursor position, performs a linear search (in 
   // the direction back-to-front) for the first occurrence of element x. If x
   // is found, places the cursor immediately before the found element, then
   // returns the final cursor position. If x is not found, places the cursor 
   // at position 0, and returns -1. 
   int List::findPrev(ListElement x) {
      if(beforeCursor == frontDummy) {
         return -1;
      }
      //else, move cursor, and check to see if it is x
      while (pos_cursor > 0) {
         int a = movePrev();
         if(a == x) {
            return pos_cursor;
         }
      }
      return -1;
   }

   // cleanup()
   // Removes any repeated elements in this List, leaving only unique elements.
   // The order of the remaining elements is obtained by retaining the frontmost 
   // occurrance of each element, and removing all other occurances. The cursor 
   // is not moved with respect to the retained elements, i.e. it lies between 
   // the same two retained elements that it did before cleanup() was called.
   void List::cleanup() {
      int original_pos = pos_cursor;
      //iterate through each element
      for(int i = 0; i < num_elements; i++) {
         //go to i'th element
         moveFront();
         while(pos_cursor != i) {
            moveNext();
         }
         moveNext();
         //std::cout <<pos_cursor<<std::endl;
         int k = peekPrev();
         while(findNext(k) != -1) {
            if(pos_cursor < original_pos) {
               original_pos--;
            }
            eraseBefore();
            //std::cout<<*this<<std::endl;
         }
      }
      //std::cout<<original_pos<<std::endl;
      //move to original cursor
      moveFront();
      for(int i = 0; i < original_pos-1; i++) {
         moveNext();
      }
   }
 
   // concat()
   // Returns a new List consisting of the elements of this List, followed by
   // the elements of L. The cursor in the returned List will be at postion 0.
   List List::concat(const List& L) const {
      //X is the object we return (calls empty constructor)
      List X;
      // if S is non-empty, load its elements into this new List
      if(this->frontDummy->next != this->backDummy) {
         Node* K = this->frontDummy->next;
         Node* J = new Node(K->data);
         X.frontDummy->next = J;
         J->next = X.backDummy;
         J->prev = X.frontDummy;
         X.backDummy->prev = J;
         while(K->next != this->backDummy) {
            K = K->next;
            J->next = new Node(K->data);
            J->next->prev = J;
            J = J->next;
            X.backDummy->prev = J;
            J->next = X.backDummy;
         }
      }
      // after copying this to list, copy L
      if(L.frontDummy->next != L.backDummy) {
         Node* N = L.frontDummy->next;
         Node* M = new Node(N->data);
         X.backDummy->prev->next = M;
         M->prev = X.backDummy->prev;
         M->next = X.backDummy;
         X.backDummy->prev = M;
         while(N->next != L.backDummy) {
            N = N->next;
            M->next = new Node(N->data);
         // std::cout <<"Adding(B);" <<M->next->data<<std::endl;
            M->next->prev = M;
            M = M->next;
            X.backDummy->prev = M;
            M->next = X.backDummy;
         }
      }
      X.num_elements = this->num_elements+L.num_elements;
      //set cursor to 0
      X.afterCursor = X.frontDummy->next;
      //std::cout<<"afterCursor" <<std::endl;
      X.beforeCursor = X.frontDummy;
      //std::cout<<"beforeCursor" <<std::endl;
      X.pos_cursor = 0;
      //std::cout<<"pos" <<std::endl;
      return X;
   }

   // to_string()
   // Returns a string representation of this List consisting of a comma 
   // separated sequence of elements, surrounded by parentheses.
   std::string List::to_string() const {
      std::string S = "(";
      //iterate through list, add stuff to S
      if(num_elements != 0) {
         Node* N =  nullptr;
         for(N = frontDummy->next; N->next != backDummy; N = N->next){
            S = S + std::to_string(N->data) + ", ";
         }
            S = S+ std::to_string(N->data) + ")";
         return S;
      }
      else {
         S = S+")";
         return S;
      }
   }

   // equals()
   // Returns true if and only if this List is the same integer sequence as R.
   // The cursors in this List and in R are unchanged.
   bool List::equals(const List& R) const {
      //check to see if data in each list is the same
      Node* N = this->frontDummy;
      Node* M = R.frontDummy;
      if(this->num_elements == R.num_elements) {
         for(int i = 0; i < num_elements; i++) {
            if(N->next != backDummy && M->next != backDummy) {
               M = M->next;
               N = N->next;
               if(M->data != N->data) {
                  return false;
               } 
            }
         }
         return true;
      }
      else {
         return false;
      }
   }


   // Overriden Operators -----------------------------------------------------
   
   // operator<<()
   // Inserts string representation of L into stream.
   std::ostream& operator<<( std::ostream& stream, const List& L ) {
      return stream << L.List::to_string();
   }

   // operator==()
   // Returns true if and only if A is the same integer sequence as B. The 
   // cursors in both Lists are unchanged.
   bool operator==( const List& A, const List& B ) {
      return A.List::equals(B);
   }

   // operator=()
   // Overwrites the state of this List with state of L.
   List& List::operator=( const List& L ) {
      if(this != &L) {
         List temp = L;
         //swap all fields
         std::swap(frontDummy, temp.frontDummy);
         std::swap(backDummy,temp.backDummy);
         std::swap(pos_cursor,temp.pos_cursor);
         std::swap(num_elements,temp.num_elements);
         std::swap(afterCursor,temp.afterCursor);
         std::swap(beforeCursor,temp.beforeCursor);
      }
      return *this;
   }
