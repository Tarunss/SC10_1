//-----------------------------------------------------------------------------
// pa4
// Tarun Sohal, CruzID: tsohal
// Test client program for pa4
//-----------------------------------------------------------------------------
// #include<stdio.h>
// #include<stdlib.h>
// #include<stdbool.h>
// #include"Matrix.h"
// #include"List.h"
// int main(int argc, char* argv[]){
//     Matrix M = newMatrix(5);
//     //Matrix H = newMatrix(5);
//     //testing equals()
//     //printf("%d\n",equals(M,H));

//     //testing changeEntry
//     //printMatrix(stdout,M);
//     for(int i = size(M); i > 0; i--) {
//         for(int j = size(M); j > 0; j--) {
//             changeEntry(M,i, j, 8);
//             //printf("changing row %d, column %d, to 8\n", i,j);
//         }
//     }
//         //printMatrix(stdout,M);
//         printf("\n");
//     //testing changeEntry changing functionality
//     Matrix F = copy(M);
//     changeEntry(M,1,2,3.5);
//     changeEntry(M,2,4,4.5);
//     changeEntry(M,3,3,5.5);
//     changeEntry(M,1,5,6.5);
//     changeEntry(M,4,3,7.5);
//     changeEntry(M,3,2,8.5);
//     //printMatrix(stdout, M);
//     printf("\n");
//     //testing copy functionality
//     Matrix B = copy(M);
//     Matrix C = copy(B);
//     printMatrix(stdout,B);
//     printf("\n");
//     printMatrix(stdout,F);
//     printf("\n");
//     //sum test 1
//     Matrix D = sum(B,C);
//     Matrix E = diff(B,F);
//     //printMatrix(stdout,D);
//     //printf("\n");
//     printMatrix(stdout,E);
//     printf("\n");

//     //testing changeEntry clear functionality
//     for(int i = 1; i < size(M)+1; i++) {
//         for(int j = 1; j < size(M)+1; j++) {
//             changeEntry(M,i, j, 0.0);
//             //printf("changing row %d, column %d, to 8\n", i,j);
//         }
//     }
//     //need to print the lists
//     printf("\n Done with changeEntry test1 \n");
//     printMatrix(stdout,M);
//     freeMatrix(&M);
//     freeMatrix(&B);
//     freeMatrix(&C);
//     freeMatrix(&D);
//     freeMatrix(&F);
//     //freeMatrix(&H);
// }
//-----------------------------------------------------------------------------
//  MatrixClient.c 
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;
    
   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   printf("past changeEntry\n");
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   printf("past changeEntry\n");
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   printf("past changeEntry\n");
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   printf("past changeEntry\n");
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   printf("past changeEntry\n");
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   printf("past changeEntry\n");
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   printf("past changeEntry\n");
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);
    printf("past changeEntry\n");
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, H)?"true":"false" );
   printf("%s\n", equals(A, B)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}

/*
Output of this program:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/