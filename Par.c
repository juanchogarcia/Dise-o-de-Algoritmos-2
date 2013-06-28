
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

Taboo* InsertarTaboo(Taboo **p,int i1,int j1, int i2,int j2, int numiter){
	Taboo *Temporal;
	Temporal = (Taboo*)malloc(sizeof(Taboo));
	if (Temporal==NULL){
		exit(-1);
	}
	Temporal->next = *p;
	*p = Temporal;
	Temporal->i1 = i1;
	Temporal->j1 = j1;
	Temporal->i2 = i2;
	Temporal->j2 =j2;
	Temporal->numiter = numiter;
	return Temporal;
}

void Imprimir_Pares(Pares *p){
	while(p!=NULL){
		printf("%d %d %d %d %d %d %d\n",p->id,p->x,p->y,p->dem,p->vi,p->vf,p->ts);
		p = p->sig;
	}
}

void Imprimir_Taboo(Taboo *aux){
    Taboo *p = aux;
    while(p!=NULL){
		printf("%d %d %d %d %d\n",p->i1,p->j1,p->i2,p->j2,p->numiter);
		p = p->next;
	}
}

int Buscar_Taboo(Taboo *aux, int i1, int j1, int i2, int j2){
    Taboo *p = aux;
    while(p!=NULL){
        if((i1==p->i1 && i2 == p->i2 && j1==p->j1 && j2==p->j2) ||
           (i2==p->i1 && i1 == p->i2 && j2==p->j1 && j1==p->j2))
            return 1;
        p = p->next;
    }
    return 0;
}


int Longitud(Pares *p){
	int tam = 0;
	while(p!=NULL){
		tam++;
		p=p->sig;
	}
	return tam;
}


Taboo* EliminarTaboo(Taboo **p,int i1,int j1,int i2,int j2){
    Taboo *Temporal;
    return Temporal;

}
