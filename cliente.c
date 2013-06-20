// Global variables
int Cap;
double CostoRutaAct = 0;

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Par.h"
#include "Vector.h"
#include <string.h>


#define N 100
#define True 1
#define False 0

/* Procedimiento que copia una matriz en otra. */

void matrixcopy(int **destmat, int **srcmat, int n, int m) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            //if(srcmat[i][j]==-1)
            //break;
            destmat[i][j] = srcmat[i][j];
        }
    }
}

/* Funcion que obtiene el costo total de una solucion al VRP con ventanas deslizantes. */

double Costo(int **Costos, int **Rutas, int **Datos, int veh, int cli, int *CostoRutas, int *RutasCambio) {
    double cost = 0.0;
    int i, j;
    int Cargas[2][veh];

    for (i = 0; i < 2; ++i) {
        for (j = 0; j < veh; ++j) {
            Cargas[i][j] = 0;
        }
    }

    for (i = 0; i < veh; ++i) {
        if (Rutas[i][0] != -1) {
            Cargas[0][i] = Cargas[0][i] + Costos[0][Rutas[i][0]];
            if ((Cargas[1][i] + Costos[0][Rutas[i][0]]) < Datos[1][Rutas[i][0]]) {
                Cargas[1][i] = Datos[1][Rutas[i][0]] + Datos[3][Rutas[i][0]];
            } else {
                Cargas[1][i] = Cargas[1][i] + Costos[0][Rutas[i][0]] + Datos[3][Rutas[i][0]];
            }

            if (Cargas[1][i] > Datos[2][Rutas[i][0]]) {
                Cargas[0][i] = Cargas[0][i] + (Cargas[1][i] - Datos[2][Rutas[i][0]]);
            }
            for (j = 1; (j < cli) && (Rutas[i][j] != -1); ++j) {
                Cargas[0][i] = Cargas[0][i] + Costos[Rutas[i][j - 1]][Rutas[i][j]];
                //Cargas[2][i] = Cargas[2][i]  + Costos[Rutas[i][j-1]][Rutas[i][j]] + Datos[3][Rutas[i][j]];
                if ((Cargas[1][i] + Costos[Rutas[i][j - 1]][Rutas[i][j]]) < Datos[1][Rutas[i][j]]) {
                    Cargas[1][i] = Costos[Rutas[i][j - 1]][Rutas[i][j]] + Datos[3][Rutas[i][j]];
                } else {
                    Cargas[1][i] = Cargas[1][i] + Costos[Rutas[i][j - 1]][Rutas[i][j]] + Datos[3][Rutas[i][j]];
                }

                if (Cargas[1][i] > Datos[2][Rutas[i][j]]) {
                    Cargas[0][i] = Cargas[0][i] + (Cargas[1][i] - Datos[2][Rutas[i][j]]);
                }
            }
            Cargas[0][i] = Cargas[0][i] + Costos[Rutas[i][j - 1]][0];
            Cargas[1][i] = Cargas[1][i] + Costos[0][Rutas[i][0]];
        }
    }

    for (j = 0; j < veh; ++j) {
        cost = cost + Cargas[0][j];
    }
    //liberar memoria. Casilla por casilla???
    //free(Cargas);
    return cost;
}

/* Funcion que reinicializa la matriz de las rutas. */

void reinicializarRutas(int **Rutas, int number, int n) {
    int mi, mj;

    for (mi = 0; mi < number; ++mi) {
        for (mj = 0; mj < n; ++mj) {
            Rutas[mi][mj] = -1;
        }
    }
}

/* Funcion que reinicializa la matriz de las cargas. */

void reinicializarCargas(int **Cargas, int number, int n) {
    int h;
    for (h = 0; h < number; ++h) {
        Cargas[0][h] = 0;
        Cargas[1][h] = 0;
        Cargas[2][h] = 0;
    }
}

/* Funcion que genera una solucion aleatoria al VRP con ventanas deslizantes. */

void Sol_Aleatoria(int *Carga, int **Costos, int **Datos, int** Rutas, int cli, int veh, int *LRec) {

    int i, rnd, j;

    /* Arreglo que contiene las cargas de los vehiculos. */

    for (i = 1; i < cli; ++i) {
        rnd = rand() % (veh);
        while (!((Carga[rnd] + Datos[0][i]) <= Cap)) {
            rnd = rand() % (veh);
        }
        Carga[rnd] += Datos[0][i];
        //Arreglado y Verificado
        /*int R;
        for(R=0;R<cli;++R){
          if(Rutas[rnd][R]==-1){
            Rutas[rnd][R]=i;
            LRec[rnd]++;
            //Con el arreglo LRec no es necesario este bucle que usa R
            break;
          }
        }*/
        Rutas[rnd][LRec[rnd]] = i;
        LRec[rnd]++;
    }
}

//Vecindad que permuta dos ciudades de una misma ruta.

int EntreCiudad(int *ruta1, int *ruta2, int *ciudad1, int *ciudad2, int **RutasMejor, int CostoMejor, int **Costos, int **Datos, int *LRec, int number, int n, int *CostoRutas, int *RutasCambio) {
    //Obteniendo una ruta aleatoria.
    int rnd, rndC1, rndC2, auxiliar;
    int CostoInt;
    int CostoR = CostoMejor;
    rnd = rand() % (number);
    while (LRec[rnd] < 2) {
        rnd = rand() % (number);
    }
    //Obteniendo dos ciudades aleatorias de esa ruta.
    rndC1 = rand() % (LRec[rnd]);
    rndC2 = rand() % (LRec[rnd]);
    while (rndC1 == rndC2) {
        rndC2 = rand() % (LRec[rnd]);
    }

    //Swap entre ciudades de la misma ruta.
    auxiliar = RutasMejor[rnd][rndC1];
    RutasMejor[rnd][rndC1] = RutasMejor[rnd][rndC2];
    RutasMejor[rnd][rndC2] = auxiliar;

    CostoInt = Costo(Costos, RutasMejor, Datos, number, n, CostoRutas, RutasCambio);
    if (CostoInt < CostoMejor) {
        CostoR = CostoInt;
        *ruta1 = rnd;
        *ruta2 = rnd;
        *ciudad1 = rndC1;
        *ciudad2 = rndC2;
    }

    //Deshaciendo el cambio.
    auxiliar = RutasMejor[rnd][rndC1];
    RutasMejor[rnd][rndC1] = RutasMejor[rnd][rndC2];
    RutasMejor[rnd][rndC2] = auxiliar;
    return CostoR;
}

//Vecindad que permuta dos ciudades de distintas rutas.

int EntreRutas(int *ruta1, int *ruta2, int *ciudad1, int *ciudad2, int **RutasMejor, int CostoMejor, int **Costos, int **Datos, int *LRec, int *Carga, int number, int n, int *CostoRutas, int *RutasCambio) {
    int rnd, rnd2, rndC1, rndC2, auxiliar;
    int CostoInt;
    int CostoR = CostoMejor;
    //Obteniendo una ruta aleatoria.
    rnd = rand() % (number);
    while (LRec[rnd] < 1) {
        rnd = rand() % (number);
    }

    //Obteniendo otra ruta aleatoria.
    rnd2 = rand() % (number);
    while (LRec[rnd2] < 1) {
        rnd2 = rand() % (number);
    }

    while (rnd == rnd2) {
        rnd2 = rand() % (number);
        while (LRec[rnd2] < 1) {
            rnd2 = rand() % (number);
        }
    }

    //Obteniendo dos ciudades aleatorias.
    rndC1 = rand() % (LRec[rnd]);
    rndC2 = rand() % (LRec[rnd2]);

    if ((Carga[rnd] - Datos[0][RutasMejor[rnd][rndC1]] + Datos[0][RutasMejor[rnd2][rndC2]]) <= Cap && (Carga[rnd2] - Datos[0][RutasMejor[rnd2][rndC2]] + Datos[0][RutasMejor[rnd][rndC1]]) <= Cap) {
        Carga[rnd] = Carga[rnd] - Datos[0][RutasMejor[rnd][rndC1]] + Datos[0][RutasMejor[rnd2][rndC2]];
        Carga[rnd2] = Carga[rnd2] - Datos[0][RutasMejor[rnd2][rndC2]] + Datos[0][RutasMejor[rnd][rndC1]];

        //Swap entre ambas ciudades.
        auxiliar = RutasMejor[rnd][rndC1];
        RutasMejor[rnd][rndC1] = RutasMejor[rnd2][rndC2];
        RutasMejor[rnd2][rndC2] = auxiliar;

        CostoInt = Costo(Costos, RutasMejor, Datos, number, n, CostoRutas, RutasCambio);
        if (CostoInt < CostoMejor) {
            CostoR = CostoInt;
            *ruta1 = rnd;
            *ruta2 = rnd2;
            *ciudad1 = rndC1;
            *ciudad2 = rndC2;
        }

        //Deshaciendo el cambio.
        auxiliar = RutasMejor[rnd][rndC1];
        RutasMejor[rnd][rndC1] = RutasMejor[rnd2][rndC2];
        RutasMejor[rnd2][rndC2] = auxiliar;

    }
    return CostoR;

}

//Programa Principal.

int main(int argc, char **argv) {

    srand(time(NULL));
    FILE *archivo;
    archivo = fopen(argv[1], "r");
    char *buffer = (char *) malloc(N * sizeof (char));
    int number;
    int capacity;
    int id, x, y, d, a, b, s;
    double distancia;
    int c_arco, n, e1, e2;
    int i, j;
    int **Costos;
    int **Datos;
    int **Rutas;
    int **RutasP;
    int **RutasMejor;

    //Eliminar Cargas y colocarlo dentro de la funcion costo.
    int h;

    Pares *par = NULL;
    if (archivo == NULL) {
        printf("\nError de apertura del archivo. \n\n");
    } else {
        fscanf(archivo, "%s", buffer);
        fscanf(archivo, "%s", buffer);
        fscanf(archivo, "%s", buffer);
        fscanf(archivo, "%s", buffer);
        fscanf(archivo, "%d %d", &number, &capacity);
        Cap = capacity;
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
            if (feof(archivo) == True) {
                break;
            }
            fscanf(archivo, "%d %d %d %d %d %d %d", &id, &x, &y, &d, &a, &b, &s);
            Insertar(&par, id, x, y, d, a, b, s);

        }

    }
    
    int RutasCambio[number];
    int CostoRutas[number];
    int LRec[number];

    for (h = 0; h < number; ++h) {
        LRec[h] = 0;
        CostoRutas[h] = 0;
        RutasCambio[h] = 0;
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
    Pares *aux = par;
    Costos = Crear_Matriz(n, n);
    Datos = Crear_Matriz(4, n);
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

    Pares *aux3 = par;
    while (aux3 != NULL) {
        id = aux3->id;
        Datos[0][id] = aux3->dem;
        Datos[1][id] = aux3->vi;
        Datos[2][id] = aux3->vf;
        Datos[3][id] = aux3->ts;
        aux3 = aux3->sig;
    }

    int Carga[number];
    int k;
    for (k = 0; k < number; ++k) {
        Carga[k] = 0;
    }
    Sol_Aleatoria(Carga, Costos, Datos, Rutas, n, number, LRec);

    int i1 = -1;
    int i2 = -1;
    int j1 = -1;
    int j2 = -1;

    int auxiliar;
    int cic;
    int rnd;
    int rnd2;
    int rndC1;
    int rndC2;
    int it = 0;
    int CostoActual;
    int CostoMejor;
    int CostoInt;
    CostoActual = Costo(Costos, Rutas, Datos, number, n, CostoRutas, RutasCambio);
    printf("%d\n", CostoActual);
    matrixcopy(RutasMejor, Rutas, number, n);
    int redRut = 0;
    int boolredRootext = True;

    if (boolredRootext) {
        while (redRut < 50000) {
            rnd = rand() % (number);
            while (LRec[rnd] < 1) {
                rnd = rand() % (number);
            }

            rnd2 = rand() % (number);
            while (LRec[rnd2] < 1) {
                rnd2 = rand() % (number);
            }

            while (rnd == rnd2) {
                rnd2 = rand() % (number);
                while (LRec[rnd2] < 1) {
                    rnd2 = rand() % (number);
                }
            }

            rndC1 = rand() % (LRec[rnd]);

            if ((Carga[rnd2] + Datos[0][RutasMejor[rnd][rndC1]]) <= Cap) {

                Carga[rnd2] = Carga[rnd2] + Datos[0][RutasMejor[rnd][rndC1]];

                Carga[rnd] = Carga[rnd] - Datos[0][RutasMejor[rnd][rndC1]];


                auxiliar = RutasMejor[rnd][LRec[rnd] - 1];
                RutasMejor[rnd][LRec[rnd] - 1] = RutasMejor[rnd][rndC1];
                RutasMejor[rnd][rndC1] = auxiliar;

                RutasMejor[rnd2][LRec[rnd2]] = RutasMejor[rnd][LRec[rnd] - 1];
                LRec[rnd2]++;

                RutasMejor[rnd][LRec[rnd] - 1] = -1;
                LRec[rnd]--;
            }

            printf("%d ", redRut);
            redRut++;
        }
    }
    ImprimirMatriz(RutasMejor, number, n);
    CostoActual = Costo(Costos, RutasMejor, Datos, number, n, CostoRutas, RutasCambio);
    printf("%d\n", CostoActual);
    int CostoR;
    while (1) {
        cic = 0;
        CostoMejor = CostoActual;
        clock_t start = clock();
        int bol = True;
        while (cic < 50) {
            if (bol){
                bol=False;
                CostoMejor = EntreCiudad(&i1, &i2, &j1, &j2, RutasMejor, CostoActual, Costos, Datos, LRec, number, n, CostoRutas, RutasCambio);
            }
            else{
                bol=True;                
                CostoMejor = EntreRutas(&i1, &i2, &j1, &j2, RutasMejor, CostoActual, Costos, Datos, LRec, Carga, number, n, CostoRutas, RutasCambio);
            }
            cic++;
        }
        if (i1 != -1) {
            auxiliar = RutasMejor[i1][j1];
            RutasMejor[i1][j1] = RutasMejor[i2][j2];
            RutasMejor[i2][j2] = auxiliar;
            i1 = -1;
        }

        clock_t end = clock();
        float seconds = (float) (end - start) / CLOCKS_PER_SEC;
        //printf("%f\n",seconds);
        if (CostoMejor < CostoActual) {
            printf("%d\n", CostoMejor);
            CostoActual = CostoMejor;
        }
        it++;
    }

    fclose(archivo);
    exit(0);
}
