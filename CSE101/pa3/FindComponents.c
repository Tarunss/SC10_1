//-----------------------------------------------------------------------------
// pa3
// Tarun Sohal, cruzID: tsohal
// FindComponents.c
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include <string.h>
#define MAX_LEN 300

int main(int argc, char *argv[])
{
   FILE *in, *out;
   char *line = malloc((MAX_LEN) * sizeof(char));
   //first check to see if 2 args are given
   if (argc != 3)
   {
      fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
      exit(EXIT_FAILURE);
   }
   //open input file for reading, and output file for writing
   in = fopen(argv[1], "r");
   if (in == NULL)
   {
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   //open output file for writing into
   out = fopen(argv[2], "w");
   if (out == NULL)
   {
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
   }
   //program to obtain adjacency List data

   //first fgets to get # vertices
   fgets(line, MAX_LEN, in);
   char* token = line;
   //get first pair (# of vertices)
    token = strtok(line, " ");
    int vertices = atoi(token);
    //printf("%d\n", vertices);
    //create Graph G
    Graph G = newGraph(vertices);
    int counter = 1;
    //extract vertices from data set
   while (fgets(line, MAX_LEN, in) != NULL)
   {
       if(strcmp(line,"\n") == 0) {
            //go to next line
        }
        else {
            //read in pairs, make adj list
            //at this point, we strtok to get first int
            token = strtok(line," ");
            int vert1 = atoi(token);
            //get second int
            token = strtok(NULL," ");
            int vert2 = atoi(token);
            //check to see if vert1 and 2 are null terminator
            if(vert1 == 0 && vert2 == 0) {
                //break from loop
                break;
            }
            //add vertices as edges in graph
            addArc(G,vert1,vert2);
            // printf("%d ", vert1);
            // printf("%d \n", vert2);
            counter++;
        }
   }
   //print out the adjacencyLists of each element in Graph
   fprintf(out,"Adjacency list representation of G:\n");
   printGraph(out,G);
   fprintf(out,"\n");
   //create input list in numerical order
   List S = newList();
   for(int i = 1; i < getOrder(G)+1; i++) {
        append(S,i);
    }
   //do DFS on G, obtain transpose of G
   DFS(G,S);
   Graph Z = transpose(G);
   //run DFS on G^T using same stack
   DFS(Z,S);
   //algorithm to print strongly connected points
   List connected = newList();
    //iterate through bottom of list
    //get amount of strongly connected tings
    int amtconn = 0;
    for(moveBack(S); index(S) != -1; movePrev(S)) {
        if(getParent(Z,get(S)) == NIL) {
            amtconn++;
        }
    }
    
    int count = 0;
    fprintf(out,"G contains %d strongly connected components:\n", amtconn);
    for(moveBack(S); index(S) != -1; movePrev(S)) {
        int x = get(S); 
        if(getParent(Z,x)!= NIL) {
            prepend(connected,x);
        }
        else {
        //once a nil parent is reached, append and print
            prepend(connected,x);
            count++;
            fprintf(out,"Component %d: ", count);
            printList(out,connected);
            fprintf(out,"\n");
            //clear for next print
            clear(connected);
        }
    }


   
   // close files
   fclose(in);
   fclose(out);
   //free the array made
   free(line);
   //free graph and List
   freeGraph(&G);
   freeGraph(&Z);
   freeList(&connected);
   freeList(&S);
   return (0);
}