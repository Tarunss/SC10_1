//-----------------------------------------------------------------------------
// Tarun Sohal, student ID: 1898930, pa1
// Lex.c
// A client program for List ADT
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include <string.h>
#define MAX_LEN 300

int main(int argc, char *argv[])
{
   //printList test
   int line_count;
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
   //program to count how many lines there are in a file
   line_count = 0;
   while (fgets(line, MAX_LEN, in) != NULL)
   {
      line_count++;
   }
   //Close and open file to reset fgets()
   fclose(in);
   in = fopen(argv[1], "r");
   if (in == NULL)
   {
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
   }
   //create an array with size == # of lines in file
   char **stringArray;
   //allocating memory for array
   stringArray = (char **)malloc(line_count * sizeof(char *));
   //fgets to store strings in array
   int counter = 0;
   //char* lineDup = strdup(line);
   while (fgets(line, MAX_LEN, in) != NULL)
   {
      char *token;
      // check to see if line is only a \n
      if(strtok(line,"\n") == NULL)
      {
         token = line;
      }
      else 
      {
         token = strtok(line,"\n");
      }
      //allocate memory to each element in the array
      stringArray[counter] = (char *)malloc((strlen(token) + 1) * sizeof(char));
      //assign element to array
      strncpy(stringArray[counter], token, (strlen(token) + 1) * sizeof(char));
      counter++;
   }
   //now that my stringArray has been made, create a List with sorted indeces
   List sortedList = newList();
   //insert 0 as first index in array
   append(sortedList, 0);
   int i, j;
   for(i = 1; i<counter;i++) {
      j = i-1;
      moveFront(sortedList);
      //while 
      while(j >=0 && strcmp(stringArray[i],stringArray[get(sortedList)])>0) {
         moveNext(sortedList);
         j--;
      }
      //cursor is -1,insert at end
      if(j == -1) 
      {  
         append(sortedList,i);
      }
      //else, insert before cursor
      else 
      {
         insertBefore(sortedList,i);
      }
   }
   //print out the sorted list according to indeces
   moveFront(sortedList);
   for (int n = 0; n < counter; n++)
   {
      fprintf(out, "%s\n", stringArray[get(sortedList)]);
      moveNext(sortedList);
   }
   // close files
   fclose(in);
   fclose(out);
   //free the array made
   for (int k = 0; k < line_count; k++)
   {
      free(stringArray[k]);
   }
   free(stringArray);
   free(line);
   freeList(&sortedList);
   return (0);
}


