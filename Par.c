
#include "Par.h"

Pares* Insertar(Pares **p,int i,int c1, int c2,int d,int a,int b,int ser){
	Pares *Temporal;
	Temporal = (Pares*)malloc(sizeof(Pares));
	if (Temporal==NULL){
		exit(-1);
	}
	Temporal->sig = *p;
	*p = Temporal;
	Temporal->id = i;
	Temporal->x = c1;
	Temporal->y = c2;
	Temporal->dem =d;
	Temporal->vi =a;
	Temporal->vf =b;
	Temporal->ts =ser;
	return Temporal;
}

void Imprimir_Pares(Pares *p){
	while(p!=NULL){
		printf("%d %d %d %d %d %d %d\n",p->id,p->x,p->y,p->dem,p->vi,p->vf,p->ts);
		p = p->sig;
	}
}

int Buscar_Taboo(int **p,int m, int i1, int j1, int i2, int j2){
    int cierto = 0;
    int i;
    for (i=0;i<m;++i){
        if (p[0][i]==i1 && p[1][i]==j1 && p[2][i]==i2 && p[3][i]==j2){
            cierto = 1;
            break;
        }
    }
    return cierto;
}


int Longitud(Pares *p){
	int tam = 0;
	while(p!=NULL){
		tam++;
		p=p->sig;
	}
	return tam;
}
