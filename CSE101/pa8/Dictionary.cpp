//-----------------------------------------------------------------------------
// Dictionary.cpp
// Implementation file for Dictionary.cpp
// cruzID: tsohal
//-----------------------------------------------------------------------------
#include "Dictionary.h"
#include<string>
#define red 1
#define black 0
//Private Node Constructor
Dictionary::Node::Node(keyType k, valType v) {
    //set key and value
    key = k;
    val = v;
    //don't know parent, left, or right
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}
// Class Constructors & Destructors ----------------------------------------
   
//Dictionary Constructor 
Dictionary::Dictionary() {
    //set dictionary values
    //create a NIL node to help with functions 
    nil = new Node("NIL",-1);
    //set nil's left, right, and parent
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = black;
    //since dictionary is empty, set everything to nil
    root = nil;
    current = nil;
    num_pairs = 0;
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D) {
    //create an empty dictionary
    nil = new Node("NIL", -1);
    //set nil's left, right, and parent
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    nil->color = black;
    //set empty parameters
    root = nil;
    current = nil;
    num_pairs = 0;
    //do pre order copy of BST
    this->preOrderCopy(D.root, D.nil);
}

// Destructor
Dictionary::~Dictionary() {
    //go through and delete all nodes in the dictionary
    postOrderDelete(root);
    //now delete nil
    delete nil;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Dictionary::Node* R) const {
    //taken from pseudocode
    if(R != nil) {
        //std::cout<<"within inOrderString\n";
        inOrderString(s,R->left);
        s+=R->key;
        s+=" : ";
        s+= std::to_string(R->val);
        s+='\n';
        inOrderString(s,R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Dictionary::Node* R) const {
    //taken from pseudocode
    if(R!=nil) {
        s+=R->key;
        s+='\n';
        preOrderString(s,R->left);
        preOrderString(s,R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Dictionary::Node* R, Dictionary::Node* N) {
    //this is a helper function to help make the copy constructor
    //do a preOrderWalk, and add nodes to dictionary as given
    if(R != N) {
        //copy the node to Dictionary N
        //Node* T = new Node(R->key,R->val);
        //add the node at R into this dictionary
        setValue(R->key,R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right,N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Dictionary::Node* R) {
    //just use a post order walk and delete each node
    if(R != nil) {
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        remove(R->key);
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Dictionary::Node* R, keyType k) const {
    //from psuedocode
    if(R == nil || k == R->key) {
        return R;
    }
    else if(k < R->key) {
        return search(R->left,k);
    }
    else {
        return search(R->right,k);
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Dictionary::Node* R) {
    //make a temp node, loop to get to most leftest node
    while(R->left != nil) {
        R = R->left;
    }
    return R;
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Dictionary::Node* R) {
   while(R->right != nil) {
        R = R->right;
    }
    return R;
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Dictionary::Node* N) {
    //use pseudocode for tree successor
    if(N->right != nil) {
        return findMin(N->right);
    }
    Node* y = N->parent;
    while(y != nil && N == y->right) {
        N = y;
        y = y->parent;
    }
    return y;
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Dictionary::Node* N) {
    //code out tree predecessor
    //use pseudocode for tree successor
    if(N->left != nil) {
        return findMax(N->left);
    }
    Node* y = N->parent;
    while(y != nil && N == y->left) {
        N = y;
        y = y->parent;
    }
    return y;
}
// RBT Helper Functions -----------------------------------------------------------------------------------------------
// LeftRotate()
void Dictionary::LeftRotate(Dictionary::Node* N) {
    //set y and x
    Node* y = N->right;
    //turn x's right into y's left
    N->right = y->left;
    if(y->left != nil) {
        y->left->parent = N;
    }
    y->parent = N->parent;
    if(N->parent == nil) {
        root = y;
    }
    else if(N == N->parent->left) {
        N->parent->left = y;
    }
    else {
        N->parent->right = y;
    }
    y->left = N;
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Dictionary::Node* N) {
//set y and x
    Node* y = N->left;
    //turn x's right into y's left
    N->left = y->right;
    if(y->right != nil) {
        y->right->parent = N;
    }
    y->parent = N->parent;
    if(N->parent == nil) {
        root = y;
    }
    else if(N == N->parent->right) {
        N->parent->right = y;
    }
    else {
        N->parent->left = y;
    }
    y->right = N;
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Dictionary::Node* N) {
    //copied from psuedocode from class website
    Node* y;
    while(N->parent->color == red) {
        if(N->parent == N->parent->parent->left) {
            y = N->parent->parent->right;
            if(y->color == red) {
                N->parent->color = black;
                y->color = black;
                N->parent->parent->color = red;
                N = N->parent->parent;
            }
            else {
                if(N == N->parent->right) {
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = black;
                N->parent->parent->color = red;
                RightRotate(N->parent->parent);
            }
        } 
        else {
            y = N->parent->parent->left;
            if(y->color == red) {
                N->parent->color = black;
                y->color = black;
                N->parent->parent->color = red;
                N = N->parent->parent;
            }
            else {
                if(N == N->parent->left) {
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = black;
                N->parent->parent->color = red;
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = black;
}

// RB_Transplant()
void Dictionary::RB_Transplant(Dictionary::Node* u, Dictionary::Node* v) {
    if(u->parent == nil) {
        root = v;
    }
    //if u is the left node
    else if(u == u->parent->left) {
        u->parent->left = v;
    } 
    //its on the right side
    else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Dictionary::Node* N) {
    Node* w;
    while(N != root && N->color == black) {
        if(N == N->parent->left) {
            w = N->parent->right;
            if(w->color == red) {
                w->color = black;
                N->parent->color = red;
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if(w->left->color == black && w->right->color == black) {
                w->color = red;
                N = N->parent;
            }
            else {
                if(w->right->color == black) {
                    w->left->color = black;
                    w->color = red;
                    RightRotate(w);
                    w = N->parent->right;
                }
                w->color = N->parent->color;
                N->parent->color = black;
                w->right->color = black;
                LeftRotate(N->parent);
                N = root;
            }
        }
        else {
            w = N->parent->left;
            if(w->color == red) {
                w->color = black;
                N->parent->color = red;
                RightRotate(N->parent);
                w = N->parent->left;
            }
            if(w->right->color == black && w->left->color == black) {
                w->color = red;
                N = N->parent;
            }
            else {
                if(w->left->color == black) {
                    w->right->color = black;
                    w->color = red;
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = black;
                w->left->color = black;
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = black;
}

// RB_Delete()
void Dictionary::RB_Delete(Dictionary::Node* N) {
    Node* y = N;
    Node* x;
    int y_original_color = y->color;
    if(N->left == nil) {
        x = N->right;
        RB_Transplant(N,N->right);
    }
    else if(N->right == nil) {
        x = N->left;
        RB_Transplant(N,N->left);
    }
    else {
        y = findMin(N->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == N) {
            x->parent = y;
        }
        else {
            RB_Transplant(y,y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N,y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if(y_original_color == black) {
        RB_DeleteFixUp(x);
    }
    delete N;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const {
    return num_pairs;
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const {
    //use search function with dictionary's root
    if(search(root,k) != nil) {
        return true;
    }
    return false;
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const {
    Node* v = search(root,k);
    if(v == nil) {
        throw std::logic_error("getValue(): error: key given does not exist in current tree\n");
    }
    return v->val;
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const {
    if(current == nil) {
        return false;
    }
    return true;
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const {
    if(hasCurrent()) {
        return current->key;
    }
    throw std::logic_error("currentKey(): error: current is not defined\n");
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const {
    if(hasCurrent()) {
        return current->val;
    }
    throw std::logic_error("currentVal(): error: current is not defined\n");
}


// Manipulation procedures -------------------------------------------------

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear() {
    //just call postorderdelete on root
    postOrderDelete(root);
    //now that all nodes are deleted, set num_elements to 0
    current = nil;
    num_pairs = 0;
}

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v) {
    //create a new node
    Node* z = new Node(k,v);
    //need to set left and right to nil
    z->left = nil;
    z->right = nil;
    Node* y = nil;
    Node* x = root;
    //travel down the tree
    while(x != nil) {
        y = x;
        if(z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == nil) {
        root = z; //tree was empty;
        num_pairs++;
        z->left = nil;
        z->right = nil;
        z->color = red;
        RB_InsertFixUp(z);
    }
    //if z's key is less than y's key
    else if(z->key < y->key) {
        y->left = z;
        num_pairs++;
        z->left = nil;
        z->right = nil;
        z->color = red;
        RB_InsertFixUp(z);
    }
    //if we passed a node with the same key, we just change y
    else if(z->key == y->key) {
        delete z;
        y->val = v;
        //we can delete z since we aren't using it
        //since we didn't insert anything, no need to modify tree
    }
    //if z's key is greater than y's key
    else {
        y->right = z;
        num_pairs++;
        z->left = nil;
        z->right = nil;
        z->color = red;
        RB_InsertFixUp(z);
    }
    //std::cout<<z->val<<std::endl;
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k) {
    //go to node with keyType k
    Node* z = search(root,k);
    if(current == z) {
        current = nil;
    }
    //std::cout<<"z is found"<<std::endl;
    //if key doesnt exist
    if(z == nil) {
        throw std::logic_error("remove(): error: key given does not exist within dictionary\n");
    }
    RB_Delete(z);
    //delete z;
    num_pairs--;

}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin() {
    if(root == nil) {
        throw std::length_error("error: begin(): tree is empty\n"); 
    }
    current = findMin(root);
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end() {
    if(root == nil) {
        throw std::length_error("error: end(): tree is empty\n"); 
    }
    current = findMax(root);
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next() {
    if(current == nil) {
        throw std::logic_error("next(): error: current is nil\n");
    }
    current = findNext(current);

}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev() {
    if(current == nil) {
        throw std::logic_error("prev(): error: current is nil\n");
    }
    current =  findPrev(current);
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const {
    std::string s = "";
    inOrderString(s,root);
    return s;
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const { 
    std::string s = "";
    preOrderString(s,root);
    return s;

}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const {
    //if they have the same elements, order of the tree doesn't matter. compare strings instead
    //std::cout<<"beginning comparison\n";
    std::string A = D.Dictionary::to_string();
    //std::cout<<A<<std::endl;
    std::string B = this->Dictionary::to_string();
   //std::cout<<B<<std::endl;

    if(A != B) {
        return false;
    }
    //now test internal stucture
    // A = D.Dictionary::pre_string();
    // B = this->Dictionary::pre_string();
    // if(A != B) {
    //     return false;
    // }
    //both vals and internal structure are equal, so they are the same
    return true;
    
}


// Overloaded Operators ----------------------------------------------------

// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) {
    return stream << D.Dictionary::to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ) {
    return A.Dictionary::equals(B);
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ) {
    //swap each of the fields within themsleves
    if(this != &D) {
        Dictionary temp = D;
        //swap all fields
        std::swap(nil, temp.nil);
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(num_pairs, temp.num_pairs);
    }
    return *this;
}