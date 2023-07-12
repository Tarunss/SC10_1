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
            addEdge(G,vert1,vert2);
            // printf("%d ", vert1);
            // printf("%d \n", vert2);
            counter++;
        }
   }
   //print out the adjacencyLists of each element in Graph
   printGraph(out,G);
   //Read in the rest of fgets until null, do BFS, and print out
   List L = newList();
   while (fgets(line, MAX_LEN, in) != NULL)
   {
        //check to see if the line is a \n
        if(strcmp(line,"\n") == 0) {
            //go to next line
        }
        else {
            //read in pairs, prepare for BFS
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
            //at this point, both vertices are read
            //BFS call
            BFS(G,vert1);
            //print distance to file2 (IF PATH EXISTS)
            if(getDist(G,vert2)!= INF){
                //printf("do I even get this far\n");
                clear(L);
                fprintf(out,"\n");
                fprintf(out,"The distance from ");
                fprintf(out,"%d ", vert1);
                fprintf(out,"to %d ", vert2);
                fprintf(out,"is %d\n", getDist(G,vert2));
                fprintf(out,"A shortest %d",vert1);
                fprintf(out,"-%d ",vert2);
                fprintf(out,"path is: ");
                getPath(L,G,vert2);
                printList(out,L);
                fprintf(out,"\n");
            }
            else {
                fprintf(out,"\n");
                fprintf(out,"The distance from ");
                fprintf(out,"%d ", vert1);
                fprintf(out,"to %d ", vert2);
                fprintf(out,"is infinity\n");
                fprintf(out,"No %d",vert1);
                fprintf(out,"-%d ",vert2);
                fprintf(out,"path exists");
                fprintf(out,"\n");
                //printf("do I even get this far\n");
            }
        }
   }
   // close files
   fclose(in);
   fclose(out);
   //free the array made
   free(line);
   //free graph and List
   freeList(&L);
   freeGraph(&G);
   return (0);
}