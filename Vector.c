
#include "Vector.h"

int** Crear_Matriz(int n,int m){
	int i;
	int **matriz = (int **)malloc(n*sizeof(int *));
	if (matriz==NULL){
		exit(-1);
	}
	for (i=0;i<m;i++){
		matriz[i]=(int *)malloc(m*sizeof(int));
		if (matriz[i]==NULL){
			exit(-1);
		}
	}
	return matriz;
}

void Destruir_Matriz(int *matriz){

}

void ImprimirMatriz(int **matriz,int n,int m){
	int i,j;
	for (i=0;i<n;i++){
		for (j=0;j<m;j++){
			printf("%d ",matriz[i][j]);
		}
		printf("\n");
	}
}
