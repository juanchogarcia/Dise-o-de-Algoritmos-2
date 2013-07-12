#ifndef Vector
#define Vector

#include <stdio.h>
#include <stdlib.h>

int** Crear_Matriz(int n,int m);
void Destruir_Matriz(int **matriz,int n);
void ImprimirMatriz(int **matriz,int n,int m);
int buscarTaboo(int i1, int i2, int j1, int j2,int **taboo,int tabooTam);
void matrixcopy(int **destmat, int **srcmat, int n, int m);

#endif /* Vector */
