//Tipo de paralelismo: Dados

#include <stdio.h>
#include <stdlib.h>
#define TAM 1024 // tamanho da matriz
#define A_VALUE 3.0 // valor de A
#define B_VALUE 5.0 // valor de B 
 
int main(int argc, char **argv)
{
    int l, m, n;   // A[l][m], B[m][n], C[l][n] 
    double *A, *B, *C, t; // matrizes e acumulador do produto
    int i, j, k; // contadores
 
    l = m = n = TAM; // tamanho da matriz
 
 // alocação de memória para as matrizes
    A = (double *) malloc(l * m * sizeof(double));
    B = (double *) malloc(m * n * sizeof(double));
    C = (double *) malloc(l * n * sizeof(double));
 
    // inicialização da matriz A
    for (i = 0; i < l; i++)
        for (j = 0; j < m; j++)
            *(A+(i*l+j)) = A_VALUE;
 
    // inicialização da matriz B
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            *(B+(i*m+j)) = B_VALUE;
 
   // inicialização da matriz C
    for (i = 0; i < l; i++)
        for (j = 0; j < n; j++)
            *(C+(i*l+j)) = 0.0;
 
    // multiplicação das matrizes A e B
    #pragma omp parallel for private(t, i, j, k) shared(l, n, m) // paralelização
    for (i = 0; i < l; i++){
        for (j = 0; j < n; j++){
            t = 0.0; 
            for(k = 0;k < m; k++){
                // t = t + A[i][k] * B[k][j];
                t += (*(A+(i*l+k))) * (*(B+(k*m+j)));
            }
            *(C+(i*l+j)) = t; // C[i][j] = t;
        }
    }
 /*imprimir matriz C
    for (i = 0; i < l; i++){
        for (j = 0; j < n; j++){
            printf("%f ", *(C+(i*l+j)));
        }
        printf("\n");
 }*/
    printf("Done!\n");
    return 0;
}