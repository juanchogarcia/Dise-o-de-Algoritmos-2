
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

void Destruir_Matriz(int **matriz,int n){
    int i;
    for (i=0;i<n;++i){
        free(matriz[i]);
    }
    free(matriz);
}

void ImprimirMatriz(int **matriz,int n,int m){
	int i,j;
        int verif=0;
	for (i=0;i<n;i++){
		for (j=0;j<m;j++){
                    printf("%d ",matriz[i][j]);
                    if(matriz[i][j]==-1)
                        break;
                    verif++;
			
		}
		printf("\n");
	}
        printf("\n");
        printf("%d\n",verif);
        printf("\n");
}

int buscarTaboo(int i1, int i2, int j1, int j2,int **taboo,int tabooTam){
    int i;
    int ret=1;
    for(i=0;i<tabooTam;++i){
        if((taboo[0][i]==i1 && taboo[1][i]==j1 && taboo[2][i]==i2 && taboo[3][i]==j2)||
           (taboo[0][i]==i2 && taboo[1][i]==j2 && taboo[2][i]==i1 && taboo[3][i]==j1)){
            ret=0;
            //printf("Entre Taboo \n");
            break;
        }
    }
    return ret;
}

/* Procedimiento que copia una matriz en otra. */

void matrixcopy(int **destmat, int **srcmat, int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            destmat[i][j] = srcmat[i][j];
        }
    }
}
