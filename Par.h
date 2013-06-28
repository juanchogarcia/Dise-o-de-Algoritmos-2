#ifndef Par
#define Par

#include <stdio.h>
#include <stdlib.h>

typedef struct pr {
	int id;
	int x;
	int y;
	int dem;
	int vi;
	int vf;
	int ts;
	struct pr *sig;
} Pares;

typedef struct taboo {
	int i1;
        int j1;
        int i2;
        int j2;
        int numiter;
	struct taboo *next;
} Taboo;

Taboo* InsertarTaboo(Taboo **p,int i1,int j1, int i2,int j2, int numiter);
Pares* Insertar(Pares **p,int i,int c1, int c2,int d,int a,int b,int ser);
void Imprimir_Pares(Pares *p);
void Imprimir_Taboo(Taboo *p);
int Buscar_Taboo(Taboo *p, int i1, int j1, int i2, int j2);
int Longitud(Pares *p);

#endif /* Par*/
