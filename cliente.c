// Global variables
int Cap;
double CostoRutaAct = 0;

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Lectura.h"
#include "Metaheuristicas.h"
#include <string.h>

#define True 1
#define False 0

int **taboo;
int tabooTam = 15; //Gendreau usa 4 y 5
int posTaboo = 0;

//Programa Principal.

int main(int argc, char **argv) {
       
    srand(time(NULL));
    int tab; 
    int number;
    int capacity;
    int n;
    int i,j,id;
    int **Costos;
    int **Datos;
    int **Rutas;
    int **RutasP;
    int **RutasMejor;
    int h;

    Pares *par = NULL;
    
    par = Leer_Archivo(argv[1],&number,&capacity);
    Cap = capacity;
    
    int RutasCambio[number];
    int CostoRutas[number];
    int LRec[number];

    for (h = 0; h < number; ++h) {
        LRec[h] = 0;
        CostoRutas[h] = 0;
        RutasCambio[h] = 0;
    }

    taboo = Crear_Matriz(4, tabooTam);

    for (tab = 0; tab < tabooTam; ++tab) {
        taboo[0][tab]=0;
        taboo[1][tab]=0;
        taboo[2][tab]=0;
        taboo[3][tab]=0;
    }

    int **Cargas = Crear_Matriz(2, number);
    int ii;
    int jj;
    for (ii = 0; ii < 2; ++ii) {
        for (jj = 0; jj < number; ++jj) {
            Cargas[ii][jj] = 0;
        }
    }


    n = Longitud(par);
    n = n - 1; //Por leer el ultimo 2 veces
    
    Rutas = Crear_Matriz(number, n);
    RutasP = Crear_Matriz(number, n);
    RutasMejor = Crear_Matriz(number, n);
    int mi, mj;

    for (mi = 0; mi < number; ++mi) {
        for (mj = 0; mj < n; ++mj) {
            Rutas[mi][mj] = -1;
            RutasP[mi][mj] = -1;
            RutasMejor[mi][mj] = -1;
        }
    }

    Costos = Crear_Matriz(n, n);
    Leer_Costos(par,Costos);
    
    Datos = Crear_Matriz(4, n);
    Leer_Datos(par,Datos);

    int Carga[number];
    int k;
    for (k = 0; k < number; ++k) {
        Carga[k] = 0;
    }
    
    //Generando la solución aleatoria.
    Sol_Aleatoria(Carga, Costos, Datos, Rutas, n, number, LRec);
    //Copiando la matriz de rutas en otra auxiliar.	
    matrixcopy(RutasMejor, Rutas, number, n);
    //Flag de reduccion de rutas.
    int boolredRootext = False;
    //Reduccion de rutas.
    ReduccionRutas(number,RutasMejor,Datos,Carga,LRec,boolredRootext);
    //Realización de la busqueda Tabu-Local
    Busq_Tabu_Local(RutasMejor,Costos,Datos,LRec,number,n, CostoRutas,RutasCambio,Carga);
    exit(0);
}
