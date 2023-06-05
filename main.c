
#include <stdio.h>
#include <string.h>
#define MAX 100

// The estalactite function sets the value of Matr[X][Y] to 1 and returns 0
int estalactite(int Matr[][MAX],int X,int Y){
  Matr[X][Y]= 1 ;
  return 0;
}

// The destroi function sets the value of Matr[X][Y] to 0 and returns 0
int destroi(int Matr[][MAX], int X, int Y){
  Matr[X][Y]= 0;
  return 0;
}

// The imprime function prints the contents of the Matr array in a grid format
int imprime(int Matr[][MAX], int linhas, int colunas){
   for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
          if(Matr[i][j] == 0)
            printf(".");
          if(Matr[i][j] == 1)
            printf("X");
        }
        printf("\n");
    }
  printf("\n");
  return 0;//put on commit 
}

int main(void) {
    int N, x, y;
    int M;
    char entrada[10];
    int Matr[MAX][MAX] = {0}; // Initialize Matr array with all values set to 0

    scanf("%d", &N);
    scanf("%d", &M);
    imprime(Matr, N, M);

    while (1) {
        scanf("%s", entrada);

        // If entrada is "F" or "f", break out of the loop
        if (strcmp(entrada, "F") == 0 || strcmp(entrada, "f") == 0) {
            break;
        } else if (strcmp(entrada, "x") == 0) { // If entrada is "x"
            scanf("%d %d", &x, &y);
            estalactite(Matr, x , y ); // Call estalactite function
            imprime(Matr, N, M); // Call imprime function
        } else if (strcmp(entrada, ".") == 0) { // If entrada is "."
            scanf("%d %d", &x, &y);
            destroi(Matr, x , y); // Call destroi function
            imprime(Matr, N, M); // Call imprime function
        } 
    }
}