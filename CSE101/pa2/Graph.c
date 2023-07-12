//-----------------------------------------------------------------------------
// pa2
// Tarun Sohal, Student ID: 1898930
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
    //stores distance from source to i
    int* distanceArray;
    //stores # of vertices
    int order;
    //stores # of edges
    int size;
    //stores most recent src vertex
    int src;
} GraphObj;


// Constructors-Destructors ---------------------------------------------------

// newGraph()
// Returns reference to new empty Graph object.
Graph newGraph(int n){
    Graph G;
    G = malloc(sizeof(GraphObj));
    //allocate memory for each array in list
    G->distanceArray = (int*)calloc(n+1, sizeof(int));
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
    G->src = NIL;
    //set default values for arrays
    for(int i = 1; i < G->order+1; i++) {
        G->colorArray[i] = WHITE;
        G->distanceArray[i] = INF;
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
       free((*pG)->distanceArray);
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

// int getSource()
// returns last source vertex used in BFS(),or NIL if func hasn't been called
int getSource(Graph G) {
    if(G==NULL ){
      printf("Graph Error: Calling getSource on NULL graph reference\n");
      exit(EXIT_FAILURE);
   }
       return G->src;
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


// int getDist
// returns distance from most recent BFS source to vertex u, or INF
// if BFS hasn't been called
// PRE: 1 <= u <= getOrder(G)
int getDist(Graph G, int u) {
    if(G==NULL ){
        printf("Graph Error: Calling getSource on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    
   // PRE: 1 <= u <= getOrder(G)
    // PRE: 1 <= u <= getOrder(G)
    if(u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDist() on out of bounds index\n");
		exit(EXIT_FAILURE);
	}
    if(getSource(G) == NIL) {
        return INF;
    }
    //return distance
    return G->distanceArray[u];
}

// void getPath()
// appends to the list L the vertices of a shortest path G from source to u, or 
// appends to L the value NIL if no such path exists.
// PRE: getSource(G) != NIL
void getPath(List L, Graph G, int u) {
    if(G==NULL ){
        printf("Graph Error: Calling getPath on NULL graph reference\n");
        exit(EXIT_FAILURE);
    }
    if(G->src == NIL) {
        printf("Graph Error: getPath() called on Graph with src == NIL\n");
        exit(EXIT_FAILURE);
    }
    //if src == u
    if(u == getSource(G)) {
        append(L,u);
    }
    else if(getParent(G,u) == NIL) {
        append(L,NIL);
    }
    else { //recursive function
        getPath( L ,G, getParent(G,u));
        append(L,u);
    }

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
    G->src = NIL;
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

// BFS()
// runs the BFS algorithm on graph G with source s, setting color, distance, parents,
// and source fields of G accordingly
void BFS(Graph G, int s) {
    //initialize everything we might need first
    G->src = s;
    for(int i = 1; i < G->order+1; i++) {
        G->colorArray[i] = WHITE;
        G->distanceArray[i] = INF;
        G->parentArray[i] = NIL;
    }
    //need to check if source has any adjacent nodes
    if(length(G->listArray[s]) == 0) {
        G->colorArray[s] = BLACK;
        G->distanceArray[s] = 0;
        G->parentArray[s] = NIL;
    }
    else {
        //initialize source first
        G->colorArray[s] = GRAY;
        G->distanceArray[s] = 0;
        G->parentArray[s] = NIL;
        //create list for all gray vertices
        List L = newList();
        //put in source vertex
        append(L,s);
        //while list is not empty
        while(!isEmpty(L)) {
            //put last gray vertex as x, delete from list (we are discovering neigbors now)
            int x = front(L);
            deleteFront(L); 
            //for all elements in the adjacency list of x
            //check to see if G->listArray[x] is empty
            if(!(length(G->listArray[x]) == 0)) {   
                //iterate through all y in adj[x]
                moveFront(G->listArray[x]);
                //printf("past movefront \n");
                while(index(G->listArray[x]) != -1) {
                    int y = get(G->listArray[x]);
                    if(G->colorArray[y] == WHITE) { //if not discovered
                        G->colorArray[y] = GRAY; //discover all d = 1 vertices
                        G->distanceArray[y] = G->distanceArray[x]+1;
                        G->parentArray[y] = x;
                        append(L,y); // append next gray vertex to list
                    }
                    moveNext(G->listArray[x]);
                }
            }
            G->colorArray[x] = BLACK; // all neighbors for x are discovered
        }
        freeList(&L); //free memory associated with List
    }
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
