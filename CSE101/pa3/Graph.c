//-----------------------------------------------------------------------------
// pa3
// Tarun Sohal, cruzID: tsohal
// Graph.c
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "Graph.h"

// structs --------------------------------------------------------------------
//typedef struct ListObj* List;
// private GraphObj type
typedef struct GraphObj{
    //stores adjacency matrix(points to first list)
    List *listArray;
    //stores color of vertex i
    int* colorArray;
    //stores parents of vertex i
    int* parentArray;
    //stores discover time of vertex i
    int* discoverArray;
    //stores finish time of vertex i
    int* finishArray;
    //stores # of vertices
    int order;
    //stores # of edges
    int size;
} GraphObj;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object.
Graph newGraph(int n){
    Graph G;
    G = malloc(sizeof(GraphObj));
    //allocate memory for each array in list
    G->discoverArray = (int*)calloc(n+1, sizeof(int));
    G->finishArray = (int*)calloc(n+1, sizeof(int));
    G->parentArray = (int*)calloc(n+1,sizeof(int));
    G->colorArray = (int*)calloc(n+1, sizeof(int));
    //allocate memory for each list pointer in array
    G->listArray = calloc(n+1,sizeof(List));
    //create lists at each pointer
    for(int i = 1; i < n+1; i++) {
        G->listArray[i] = newList();
    }
    //set default values for graph
    G->order = n;
    G->size = 0;
    //set default values for arrays
    for(int i = 1; i < G->order+1; i++) {
        G->colorArray[i] = WHITE;
        G->discoverArray[i] = UNDEF;
        G->finishArray[i] = UNDEF;
        G->parentArray[i] = NIL;
    }
    return G;
}

// freeList()
// Frees all heap memory associated with Graph *pG, and sets *pG to NULL.
void freeGraph(Graph* pG){
   //go through and delete every single piece of memory allocated
   //goes through and frees all memory associated with lists (including pointers in listArray)
   for(int i = 1; i < (*pG)->order+1; i++) {
       freeList(&((*pG)->listArray[i]));
   }
   //free the memory with integer arrays
       free((*pG)->listArray);
       free((*pG)->discoverArray);
       free((*pG)->finishArray);
       free((*pG)->colorArray);
       free((*pG)->parentArray);
       free((*pG));
   //at this point, everything related to G should have been freed, so set G to NULL
   (*pG) = NULL;
}


// Access functions -----------------------------------------------------------

// int getOrder()
// Gets the order (# of vertices) in the graph
int getOrder(Graph G) {
    if(G==NULL ){
      printf("Graph Error: Calling getOrder on NULL graph reference\n");
      exit(EXIT_FAILURE);
   }
    return G->order;
}

// int getSize()
// returns # of edges in Graph
int getSize(Graph G) {
    if(G==NULL ){
      printf("Graph Error: Calling getSize on NULL graph reference\n");
      exit(EXIT_FAILURE);
   }
    return G->size;
}

// int getParent
// returns parent vertex of u in BFS tree, or NIL if BFS hasn't been called
// PRE: 1 <= u <= getOrder(G)
int getParent(Graph G, int u) {
    if(G==NULL ){
        printf("Graph Error: Calling getSource on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    
   // PRE: 1 <= u <= getOrder(G)
    if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDist() on out of bounds index\n");
		exit(EXIT_FAILURE);
	}

    //return parent
    return G->parentArray[u];
}

// int getDiscover()
// returns the discover time of vertex u in the DFS search
// Pre: 1<=u<=n=getOrder(G) 
int getDiscover(Graph G, int u) {
    if(G==NULL ){
        printf("Graph Error: Calling getSource on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    
   // PRE: 1 <= u <= getOrder(G)
    if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDist() on out of bounds index\n");
		exit(EXIT_FAILURE);
	}
    //return discover time of G
    return G->discoverArray[u];
}

// int getFinish()
// returns the finish time of a vertex once DFS has been run
// Pre: 1<=u<=n=getOrder(G)
int getFinish(Graph G, int u) {
    if(G==NULL ){
        printf("Graph Error: Calling getSource on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    
   // PRE: 1 <= u <= getOrder(G)
    if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDist() on out of bounds index\n");
		exit(EXIT_FAILURE);
	}
    return G->finishArray[u];
}


// Manipulation Functions ------------------------------------------------------

// makeNull()
// deletes all edges in a graph, restoring it to its original no edge state
void makeNull(Graph G) {
    if(G==NULL ){
        printf("Graph Error: Calling makeNull on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    //go through and clear all adjacency lists
    for(int i = 1; i < getOrder(G)+1; i++) {
        clear(G->listArray[i]);
    }
    //set all other variables to default
    G->order = 0;
    G->size = 0;
}

// addEdge()
// inserts a new edge joining u to v, and v to u (u is added to adjacency list of v,
// and v is added to the adjacency list of u)
//PRE: u and v must be between 0 and n-1
void addEdge(Graph G, int u, int v) {
    if(G==NULL ){
        printf("Graph Error: Calling getSource on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    //check to see if vertices exist
    if(!(1 <= v && v <=G->order)) {
        printf("Graph Error: v is not an existing vertex\n");
        exit(EXIT_FAILURE);
    }
    if(!(1 <= u && u<=G->order)) {
        printf("Graph Error: u is not an existing vertex\n");
        exit(EXIT_FAILURE);
    }
    //just call addarc twice
    addArc(G,u,v);
    addArc(G,v,u);
    G->size--;
}

// addArc()
// inserts a new directed edge from u to v (u is added to adjacecny list of v)
void addArc(Graph G, int u, int v) {
    if(G==NULL ){
        printf("Graph Error: Calling getSource on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    //check to see if vertices exist
    if(!(1 <= v && v <=G->order)) {
        printf("Graph Error: v is not an existing vertex\n");
        exit(EXIT_FAILURE);
    }
    if(!(1 <= u && u<=G->order)) {
        printf("Graph Error: u is not an existing vertex\n");
        exit(EXIT_FAILURE);
    }
    //go to v's adjacency list and append u
    //if v's adjacency list is empty, append
     if(isEmpty(G->listArray[u])) {
        append(G->listArray[u],v);
        //printf("List is empty, appending...\n");
    }
     //insertion sort for list of vertices
     else {
         moveFront(G->listArray[u]);
         while(index(G->listArray[u]) != -1 && v > get(G->listArray[u])) {
             //moves cursor to correct area for insert
             moveNext(G->listArray[u]);
         }
         //if index is -1, append (back of list)
         if(index(G->listArray[u]) == -1) {
             append(G->listArray[u], v);
         }
         //else, cursor is at element greater than before
         else {
             insertBefore(G->listArray[u],v);
         }
    }
    G->size++;
}
// DFS()
// Performs a depth first search on graph passed, setting discover times, finish
// times, color, parents, and etc. takes in a stack containing # of vertices,
// and returns it with the vertices ordered in decreasing finish times.
void DFS(Graph G, List S) {
    //initialization first (we are iterating through stack S)
    //A will be the stack we append all of our elements to
    for(moveFront(S); index(S) != -1; moveNext(S)) {
        int y = get(S);
        G->colorArray[y] = WHITE;
        G->parentArray[y] = NIL;
        G->finishArray[y] = UNDEF;
        G->discoverArray[y] = UNDEF;
    }
    int time = 0; //set time
    //main loop of DFS()
    for(moveFront(S); index(S) != -1; moveNext(S)) {
        int y = get(S);
        if(G->colorArray[y] ==WHITE) {
            //need to pass time by reference
            visit(G,S,y,&time);
        }
    }
    //now we need to trim S to be correct
    for(int i = 0; i < length(S)+1/2; i++) {
        deleteBack(S);
    }
    //printList(stdout,S);
}
// visit()
// Helper function to DFS. recursive function that "does" the search in each
// vertex in G. alters the local time variable passed by DFS as well
void visit(Graph G,List S, int u, int* time) {
    //discover u
    G->discoverArray[u] = ++(*time);
    // printf("%d ", u);
    // printf("Discover time: %d \n", G->discoverArray[u]);
    G->colorArray[u] = GRAY;
    //placer for adj[x]
    List x = G->listArray[u];
    //iterate through adj[x]
    if(length(x) >0) {
        for(moveFront(x); index(x) != -1; moveNext(x)) {
            int y = get(x);
            if(G->colorArray[y] == WHITE) { //if undiscovered
                G->parentArray[y] = u;  //discover it
                visit(G,S,y,time);    //go in deeper
            }
        }
    }
    G->colorArray[u] = BLACK;
    G->finishArray[u] = ++(*time); //put finish time in appropriate pos
    //since we have finished a vertex, prepend to list S
    //deleteFront(S);
    prepend(S,u);
}


//Other Operations --------------------------------------------------------------

// printGraph()
// prints the adjacency list representation of G to a file pointed to by out
// format of this should match examples in pa2 PDF
void printGraph(FILE* out, Graph G) {
    //go through list array 1-n, printList
    for(int i = 1; i < getOrder(G)+1; i++) {
        fprintf(out,"%d: ", i);
        printList(out,G->listArray[i]);
        fprintf(out,"\n");
    }
}

// transpose()
// returns a reference to a new graph object representing the transpose of G
// we transpose G by 
Graph transpose(Graph G) {
    Graph Z = newGraph(getOrder(G));
    for(int i = 1; i < getOrder(Z)+1; i++) {
        //iterate through adjacency list of each vertex
        List adj = G->listArray[i];
        if(length(adj) != 0) {
            for(moveFront(adj);index(adj) != -1; moveNext(adj)) {
                int y = get(adj);
                //add the vert to adj of vertex
                addArc(Z,y,i);
            }
        }
    }
    return Z;
}

// copyGraph()
// returns a new copy of G 
Graph copyGraph(Graph G) {
    Graph Z = newGraph(getOrder(G));
    Z->size = G->size;
    //copy the arrays over
    for(int i = 1; i < getOrder(G)+1; i++) {
        Z->colorArray[i] = G->colorArray[i];
        Z->discoverArray[i] = G->discoverArray[i];
        Z->finishArray[i] = G->finishArray[i];
        Z->parentArray[i] = G->parentArray[i];
    }
    //copy the adjacency list
    for(int i = 1; i < getOrder(Z)+1; i++) {
        //MIGHT BE A MEMORY LEAK, PAY ATTENTION WHEN TESTING
        //first we free the empty list
        freeList(&(Z->listArray[i]));
        //then we allocate the  new copied list
        Z->listArray[i] = copyList(G->listArray[i]);
    }
    return Z;
}