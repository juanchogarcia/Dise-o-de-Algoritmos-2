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

Pares* Insertar(Pares **p,int i,int c1, int c2,int d,int a,int b,int ser);
void Imprimir_Pares(Pares *p);
int Longitud(Pares *p);

#endif /* Par*/
