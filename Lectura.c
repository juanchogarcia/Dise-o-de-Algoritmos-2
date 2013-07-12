
#include "Lectura.h"

Pares* Leer_Archivo(char *name,int *number,int *capacity){
	FILE *archivo;
	int numb;
    	int cap;
    	int id, x, y, d, a, b, s;
    	Pares *par = NULL;
	char *buffer = (char *) malloc(N * sizeof (char));
    	archivo = fopen(name, "r");
    	
    	if (archivo == NULL) {
        	printf("\nError de apertura del archivo. \n\n");
    	} else {
        
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%d %d", &numb, &cap);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	fscanf(archivo, "%s", buffer);
        	while (1) {
            	if (feof(archivo) == 1) {
                	break;
            	}
            		fscanf(archivo, "%d %d %d %d %d %d %d", &id, &x, &y, &d, &a, &b, &s);
            		Insertar(&par, id, x, y, d, a, b, s);
		}

		*number = numb;
		*capacity = cap;
    	}    	
	return par;
}

void Leer_Costos(Pares *par,int **Costos){

	Pares *aux = par;
	double distancia;
    	int c_arco, n, e1, e2;
	while (aux != NULL) {
      		int i, j;
        	Pares *aux2 = par;
        	i = aux->id;
       		while (aux2 != NULL) {
            		j = aux2->id;
            		if (j != i) {
                		e1 = pow(((aux2->x)-(aux->x)), 2);
                		e2 = pow(((aux2->y)-(aux->y)), 2);
                		distancia = sqrt((e1 + e2));
                		c_arco = (int) distancia;
                		Costos[i][j] = c_arco;
            		} else {
                		Costos[i][j] = 0;
            		}
            	aux2 = aux2->sig;
        	}
        	aux = aux->sig;
    	}
    
}

void Leer_Datos(Pares *par,int **Datos){
	Pares *aux3 = par;
	int id;
    	while (aux3 != NULL) {
        	id = aux3->id;
        	Datos[0][id] = aux3->dem;
        	Datos[1][id] = aux3->vi;
        	Datos[2][id] = aux3->vf;
        	Datos[3][id] = aux3->ts;
        	aux3 = aux3->sig;
    	}
}
