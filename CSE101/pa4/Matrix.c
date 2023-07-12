//-----------------------------------------------------------------------------
// pa4
// Tarun Sohal, CruzID: tsohal
// Matrix.c
//-----------------------------------------------------------------------------
#include "Matrix.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{
   //int for column, double for data
    int column;
    double data;
} EntryObj;
//Private Entry structs

//newEntry()
Entry newEntry(int c, double d) {
    Entry E;
    E = malloc(sizeof(EntryObj));
    E->column = c;
    E->data = d;
    return E;
}
//freeEntry()
void freeEntry(Entry* pE) {
    if( pE!=NULL && *pE!=NULL ){
      free(*pE);
      *pE = NULL;
    }
}
//Matrix Object
typedef struct MatrixObj {
    //a matrix is an array of list of entries
    List *listArray;

    //need an int to calculate size
    int size;

    //need an int to calculate # of nonzero entries
    int nonzero;

    //since we don't store rows, heres a list with rows that have entries
    List entryRows;


} MatrixObj;

// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    //set size of matrix
    M->size = n;
    //create a zero entry matrix of n x n
    M->listArray = calloc(n+1, sizeof(List));
    // for(int i = 1; i < n+1; i++) {
    //     M->listArray[i] = newList();
    // }
    //create a new list for rows with entries
    M->entryRows = newList();
    
    return M;
}   

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) { 
        //iterate through each entry in entrylist, and free it
        List x = (*pM)->entryRows;
        //if there are entries, free them
        if(length(x) != 0) {
            for(moveFront(x); index(x) != -1; moveNext(x)) {
                int* z = (int*)get(x);
                //printf("freeing data at row: %d\n", (*z));
                List y = (*pM)->listArray[(*z)];
                //free all entries in this list
                for(moveFront(y); index(y)!=-1; moveNext(y)) {
                    Entry E = (Entry)get(y);
                    freeEntry(&E);
                }
                //free the integer associated with entryRows
                free(z);
                //free the list associated with that row
                freeList(&y);
            }
        }
    //now deallocate listArray
    free((*pM)->listArray);
    //deallocate entryRow array & its int pointers
    freeList(&(*pM)->entryRows);
    //finally, deallocate Matrix
    free(*pM);
    //set pointer to NULL
    (*pM) = NULL;
 }

// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling size() on a NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->size;
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
     if(M == NULL) {
        printf("Matrix Error: calling NNZ() on a NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    return M->nonzero;
}


// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if(A == NULL || B ==NULL) {
        printf("Matrix Error: calling equals() on a NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    //first check if size is same
    if(A->size != B->size) {
        return 0;
    }
    //iterate through, compare each matrix to see if column and data entries = each other
    for(int i = 1; i < A->size+1; i++) {
        List one = A->listArray[i];
        List two = B->listArray[i];
        if(length(one) != 0) {
            for(moveFront(one),moveFront(two); index(one) != 0; moveNext(one), moveNext(two)) {
                Entry entryA = (Entry)get(one);
                Entry entryB =(Entry)get(two);
                //settiing up for comparison (columns are maintained in sorted order)
                double dataA = entryA->data;
                int colA = entryA->column;
                double dataB = entryB->data;
                int colB = entryB->column;
                //compare each entry
                if(colB != colA || dataA != dataB) {
                    return 0;
                }
            }
        }
    }
    //else, they are equal
    return 1;
}

// Manipulation procedures

// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    if(M == NULL) {
        printf("Matrix Error: calling NNZ() on a NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    //iterate through each list, delete each entry

}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {

    if(1 > j || j >size(M)) {
        printf("Matrix Error: 1 <= j <= size(M)\n");
        exit(EXIT_FAILURE);
    }
     if(1 > i || i >size(M)) {
        printf("Matrix Error: 1 <= i <= size(M)\n");
        exit(EXIT_FAILURE);
    }
    //if column's data is changed to 0, delete entry 
    if(x == 0.0) {
        //iterate and delete ij'th entry
        //\List L = M->listArray[i];
        if(M->listArray[i] != NULL) {
        if(length(M->listArray[i]) != 0) {
            moveFront(M->listArray[i]);
            while(index(M->listArray[i]) != -1) {
                //check to see if entry is at j
                Entry E = (Entry)get(M->listArray[i]);
                if(E->column == j) {
                    //free entry
                    freeEntry(&E);
                    //delete element from list
                    //printf("LENGTH OF LIST: %d\n", length(M->listArray[i]));
                    delete(M->listArray[i]);
                    M->nonzero--;
                    //check to see if row has any entries
                    //printf("LENGTH OF LIST: %d\n", length(M->listArray[i]));
                    if(length(M->listArray[i]) == 0) {
                        //if length is now zero, deallocate list and delete from entryRow
                        List entries = M->entryRows;
                        //iterate through and delete correct row from entryList
                        moveFront(entries);
                        while(index(entries)!= -1) {
                            int* y = (int*)get(entries);
                            if((*y) == i) {
                                //deletes element from the list
                                delete(entries);
                                //delete the int allocated beforehand
                                free(y);
                                //printf("deleted and freed entries\n");
                            }
                            else {
                                //printf("moving next (ENTRIES)...\n");
                                moveNext(entries);
                            }
                         }
                    //free the list if its length is empty
                    //printf("FREEING LIST SINCE ITS EMPTY...\n");
                    freeList(&(M->listArray[i]));
                    break;
                    }
                } else {
                    //printf("moving next (LIST)...\n");
                    moveNext(M->listArray[i]);
                }
            }
        }
        } 
    }
    //else, traverse to entry point and insert new data
    else {
        //first need to know if data we replace exists
        //List L = M->listArray[i];
        //need to check if this is NULL
        if(M->listArray[i] != NULL) {
            moveFront(M->listArray[i]);
            while(index(M->listArray[i]) != -1) {
                //get the column so we can sort into list
                Entry E = (Entry)get(M->listArray[i]);
                int e = E->column;
                //first case: j > e
                if(j > e) {
                    moveNext(M->listArray[i]);
                }
                //second case: j == e
                else if(j == e) {
                    //no need to allocate an entry: just modify the one @ e
                    E->data = x;
                    break;
                }
                //last case: if j !>= e, insBefore
                else if(j < e) {
                    //allocate and ins non existing, but not greatest entry
                    Entry N = newEntry(j, x);
                    insertBefore(M->listArray[i],N);
                    M->nonzero++;
                    break;
                }
            }
            //reached back of list, append
            if(index(M->listArray[i]) == -1) {
                Entry N = newEntry(j,x);
                append(M->listArray[i],N);
                M->nonzero++;
            }
        } else if(M->listArray[i] == NULL){
            //L is NULL, so we allocate memory to M->listArray[i]
            //printf("L is null, creating new list at listArray[%d]\n", i);
            M->listArray[i] = newList();
            //same process of adding entry, but since L is empty, we can just append
            Entry N = newEntry(j,x);
            append(M->listArray[i],N);
            M->nonzero++;
            //since L now has entries, we insertion sort its index into entryRows
            //typecast so that we don't lose data
            //int z = i;
            int z = i;
            //NOTE: I HAVE TO FREE THE INTS IN ENTRYLIST WHENEVER I DELETE THEM
            int* pI = malloc(sizeof(int));
            (*pI) = z;
            if(isEmpty(M->entryRows)) {
                append(M->entryRows,pI);
                //printf("List is empty, appending...\n");
            }
            //insertion sort for list of vertices
            else {
                moveFront(M->entryRows);
                while(index(M->entryRows) != -1 && (*pI) > (*(int*)get(M->entryRows))) {
                    //moves cursor to correct area for insert
                    moveNext(M->entryRows);
                }
                //if index is -1, append (back of list)
                if(index(M->entryRows) == -1) {
                    append(M->entryRows, pI);
                }
                //else, cursor is at element greater than before
                else {
                    insertBefore(M->entryRows,pI);
                }
            }
        }
    }
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    if(A == NULL) {
        printf("Matrix Error: called copy on a null matrix reference\n");
        exit(EXIT_FAILURE);
    }
    //first, make a new Matrix
    Matrix B;
    B = newMatrix(A->size);
    //iterate through A's entryrows
    if(length(A->entryRows) != 0) {
        moveFront(A->entryRows);
        while(index(A->entryRows)!= -1) {
            //get index i
            int* i = (int*)get(A->entryRows);
            //go to index j at i
            List L = A->listArray[(*i)];
            //iterate through i's entrys
            moveFront(L);
            while(index(L) != -1) {
                Entry C = (Entry)get(L);     
                //add switched i and j entry to B 
                changeEntry(B,(*i),C->column,C->data);
                moveNext(L);
            }
            moveNext(A->entryRows);
        }
    }
    return B;
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    if(A == NULL) {
        printf("Matrix Error: called transpose on a null matrix reference\n");
        exit(EXIT_FAILURE);
    }
    //first, make a new Matrix
    Matrix B;
    B = newMatrix(A->size);
    //iterate through A's entryrows
    if(length(A->entryRows) != 0) {
        moveFront(A->entryRows);
        while(index(A->entryRows)!= -1) {
            //get index i
            int* i = (int*)get(A->entryRows);
            //go to index j at i
            List L = A->listArray[(*i)];
            //iterate through i's entrys
            moveFront(L);
            while(index(L) != -1) {
                Entry C = (Entry)get(L);     
                //add same entry to B 
                changeEntry(B,C->column,(*i),C->data);
                moveNext(L);
            }
            moveNext(A->entryRows);
        }
    }
    return B;
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    //same as copy, but just mult data with x
    if(A == NULL) {
        printf("Matrix Error: called scalarMult on a null matrix reference\n");
        exit(EXIT_FAILURE);
    }
    //first, make a new Matrix
    Matrix B;
    B = newMatrix(A->size);
    //iterate through A's entryrows
    if(length(A->entryRows) != 0) {
        moveFront(A->entryRows);
        while(index(A->entryRows)!= -1) {
            //get index i
            int* i = (int*)get(A->entryRows);
            //go to index j at i
            List L = A->listArray[(*i)];
            //iterate through i's entrys
            moveFront(L);
            while(index(L) != -1) {
                Entry C = (Entry)get(L);     
                //add switched i and j entry to B 
                changeEntry(B,(*i),C->column,C->data * x);
                moveNext(L);
            }
            moveNext(A->entryRows);
        }
    }
    return B;
}
// rowSum()
// helper function for sum()
// returns a list that sums the elements on entrylists given, + size of matrices
void rowSum(Matrix S, List rowA, List rowB, int row) {
    if(length(rowA)!= 0 && length(rowB) != 0) {
        //iterate through each element
        moveFront(rowA);
        moveFront(rowB);
        for(int j = 1; j < size(S)+1; j++) {
            Entry A = (Entry)get(rowA);
            Entry B = (Entry)get(rowB);
            //if both entries are the same
            if(A->column == j && B->column == j) {
                //edge case where A + B == 0 needs to be taken care of
                if(A->data + B->data != 0.0) {
                    changeEntry(S,row,j, A->data + B->data);
                }
                moveNext(rowA);
                moveNext(rowB);
            }
            //if A matches and B doesn't
            else if(A->column == j && B->column != j) {
                changeEntry(S,row,j,A->data);
            }
            //if B matches and A doesn't
            else if(B->column == j && A->column != j) {
                changeEntry(S,row,j,B->data);
            }
            //else if no columns match
            else if(A->column != j && B->column != j) {
                if(A->column < j) {
                    moveNext(rowA);
                }
                if(B->column < j) {
                    moveNext(rowB);
                }
            }
        }
    }
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if(size(A) != size(B)) {
        printf("Matrix Error: called sum on matrices with different sizes\n");
        exit(EXIT_FAILURE);
    }
    if(A == NULL || B == NULL) {
        printf("Matrix Error: called sum on a null matrix reference\n");
        exit(EXIT_FAILURE);
    }
    //first make a new matrix
    Matrix S = newMatrix(size(A));
    
    List rowA = A->entryRows;
    List rowB = B->entryRows;
    if(length(rowA) != 0 && length(rowB)!= 0) {
        moveFront(rowA);
        moveFront(rowB);
        //iterate through rows first
        for(int i = 1; i < size(S)+1; i++) {
            int* a = (int*)get(rowA);
            int* b = (int*)get(rowB);
            //case where both entries have matching columns == i
            if((*a) == i && (*b) == i) {
                //proceed to do a rowsum on these A->listArray[i]
                rowSum(S,A->listArray[i],B->listArray[i],i);
                moveNext(rowA);
                moveNext(rowB);
            }
            else if((*a) == i && (*b) != i) {
                //move B forward, repeat
                //since there are no entries in b but there are in a,
                //just add those entries into appropriate spot 
                moveFront(A->listArray[i]);
                for(int j = 1; j < size(S)+1; j++) {
                    Entry X = (Entry)get(A->listArray[i]);
                    changeEntry(S,i,j, X->data);
                    moveNext(A->listArray[i]);
                }
                moveNext(rowB);
            }
            else if((*b) == i && (*a) != i) {
                //move A forward, repeat
                //since there are no entries in a but there are in b,
                //just add those entries into appropriate spot
                moveFront(B->listArray[i]);
                for(int j = 1; j < size(S)+1; j++) {
                    Entry X = (Entry)get(B->listArray[i]);
                    changeEntry(S,i,j, X->data);
                    moveNext(B->listArray[i]);
                }
                moveNext(rowA);
            }
            else if((*b) != i && (*a) != i) {
                //step only when b < i
                if((*b) < i) {
                    moveNext(rowB);
                }
                if((*a) < i) {
                    moveNext(rowA);
                } 
            }
        }
    }
    return S;
}
// rowDiff()
// helper function for diff() that takes the difference of 2 rows in 
// matrix S
void rowDiff(Matrix S, List rowA, List rowB, int row) {
if(length(rowA)!= 0 && length(rowB) != 0) {
        //iterate through each element
        moveFront(rowA);
        moveFront(rowB);
        for(int j = 1; j < size(S)+1; j++) {
            Entry A = (Entry)get(rowA);
            Entry B = (Entry)get(rowB);
            //if both entries are the same
            if(A->column == j && B->column == j) {
                //edge case where A - B == 0 needs to be taken care of
                if(A->data - B->data != 0.0) {
                    changeEntry(S,row,j, A->data - B->data);
                }
                moveNext(rowA);
                moveNext(rowB);
            }
            //if A matches and B doesn't
            else if(A->column == j && B->column != j) {
                changeEntry(S,row,j,A->data);
            }
            //if B matches and A doesn't
            else if(B->column == j && A->column != j) {
                changeEntry(S,row,j,-(B->data));
            }
            //else if no columns match
            else if(A->column != j && B->column != j) {
                if(A->column < j) {
                    moveNext(rowA);
                }
                if(B->column < j) {
                    moveNext(rowB);
                }
            }
        }
    }
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if(size(A) != size(B)) {
        printf("Matrix Error: called sum on matrices with different sizes\n");
        exit(EXIT_FAILURE);
    }
    if(A == NULL || B == NULL) {
        printf("Matrix Error: called sum on a null matrix reference\n");
        exit(EXIT_FAILURE);
    }
    //first make a new matrix
    Matrix S = newMatrix(size(A));
    
    List rowA = A->entryRows;
    List rowB = B->entryRows;
    if(length(rowA) != 0 && length(rowB)!= 0) {
        moveFront(rowA);
        moveFront(rowB);
        //iterate through rows first
        for(int i = 1; i < size(S)+1; i++) {
            int* a = (int*)get(rowA);
            int* b = (int*)get(rowB);
            //case where both entryRows have matching columns == i
            if((*a) == i && (*b) == i) {
                //proceed to do a rowDiff on these M->listArray[i]
                rowDiff(S,A->listArray[i],B->listArray[i],i);
                moveNext(rowA);
                moveNext(rowB);
            }
            else if((*a) == i && (*b) != i) {
                //move B forward, repeat
                //just add whatever is in listArray[i], since we are subtracting
                //zero from it
                moveFront(A->listArray[i]);
                for(int j = 1; j < size(S)+1; j++) {
                    Entry X = (Entry)get(A->listArray[i]);
                    changeEntry(S,i,j, X->data);
                    moveNext(A->listArray[i]);
                }
                moveNext(rowB);
            }
            else if((*b) == i && (*a) != i) {
                //move A forward, repeat
                //just add -(whatever) is in listArray[i], since we are subtracting 
                //it from zero
                moveFront(B->listArray[i]);
                for(int j = 1; j < size(S)+1; j++) {
                    Entry X = (Entry)get(B->listArray[i]);
                    changeEntry(S,i,j, X->data);
                    moveNext(B->listArray[i]);
                }
                moveNext(rowA);
            }
            else if((*b) != i && (*a) != i) {
                //step only when b < i
                if((*b) < i) {
                    moveNext(rowB);
                }
                if((*a) < i) {
                    moveNext(rowA);
                } 
            }
        }
    }
    return S;
}
// vectorDot()
// gets the dot product of an element given two lists and returns it as a double
double vectorDot(List arrayListA, List arrayListB, int n) {
    //need to make sure that the columns that I am multiplying are lined up
    //iterate through from 1 to n
    moveFront(arrayListA);
    moveFront(arrayListB);
    double dot = 0;
    for(int i = 1; i < n+1; i++) {
        Entry entryA = (Entry)get(arrayListA);
        Entry entryB = (Entry)get(arrayListB);
        //need to compare the columns
        if(entryA->column == i && entryB->column == i) {
            //multiply each element and add to dot
            dot = dot + (entryA->data * entryB->data);
            moveNext(arrayListA);
            moveNext(arrayListB);
        }
        else if(entryA->column == i && entryB->column != i) {
            //do nothing, since adding zero. move arrayListyB up
            moveNext(arrayListB);
        }
        else if(entryB->column == i && entryA->column != i) {
            //do nothing, since adding zero. move arrayListyA up
            moveNext(arrayListA);
        }
        else if(entryB->column != i && entryA->column != i) {
            //step only when b < i
                if((entryB->column) < i) {
                    moveNext(arrayListB);
                }
                if((entryA->column) < i) {
                    moveNext(arrayListA);
                } 
        }
        //need to address case where reaches end of entry list before loop ends
        else if(index(arrayListA) == -1 || index(arrayListB) == -1) {
            //since this means that either entryList has ended, we
            //are multiplying the next rows by zero. Therefore, break
            break;
        }
    }
    return dot;
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if(size(A) != size(B)) {
        printf("Matrix Error: called sum on matrices with different sizes\n");
        exit(EXIT_FAILURE);
    }
    if(A == NULL || B == NULL) {
        printf("Matrix Error: called sum on a null matrix reference\n");
        exit(EXIT_FAILURE);
    }
    //first, transpose B so that we can do product
    Matrix T = transpose(B);
    //make a new matrix to represent product
    Matrix P = newMatrix(size(A));
    //iterate with i'th row of entrylist A , to ALL rows of entryList T
    moveFront(A->entryRows);
    while(index(A->entryRows) != -1) {
        moveFront(T->entryRows);
        int* a = (int*)get(A->entryRows);
        while(index(T->entryRows) != -1) {
            int* t = (int*)get(T->entryRows);
            //compute and add dot product to P
            vectorDot(A->listArray[(*a)], T->listArray[(*t)], size(P));
            moveNext(T->entryRows);
        }
        moveNext(A->entryRows);
    }
    freeMatrix(&T);
    return P;
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    //iterate through entryRows and print out each entry
    //of 

    if(length(M->entryRows) != 0) {
        //iterate through entryRows, print out entries at listArray[get(entryRows)]
        for(moveFront(M->entryRows); index(M->entryRows) != -1; moveNext(M->entryRows)) {
            int* i = (int*)get(M->entryRows);
            //print out row number
            fprintf(out,"%d: ", (*i)); 
            List printingList = M->listArray[(*i)];
            //iterate through this list, printing each nonzero entry
            for(moveFront(printingList); index(printingList) != -1; moveNext(printingList)) {
                Entry E = (Entry)get(printingList);
                int c = E->column;
                double d = E->data;
                fprintf(out, " (%d, %lf) ", c,d);
            }
            fprintf(out,"\n");
        }
    }
}
