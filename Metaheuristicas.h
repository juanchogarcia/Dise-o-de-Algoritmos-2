#ifndef Metaheuristicas
#define Metaheuristicas

#include "Vector.h"
#include <time.h>

extern int Cap;
extern int tabooTam;
extern int **taboo;
extern int posTaboo;

void Sol_Aleatoria(int *Carga, int **Costos, int **Datos, int** Rutas, int cli, int veh, int *LRec);
double Costo(int **Costos, int **Rutas, int **Datos, int veh, int cli, int *CostoRutas, int *RutasCambio);
int EntreRutas(int *ruta1, int *ruta2, int *ciudad1, int *ciudad2, int **RutasMejor, int CostoMejor, int **Costos, int **Datos, int *LRec, int *Carga, int number, int n, int *CostoRutas, int *RutasCambio);
void ReduccionRutas(int number,int **RutasMejor,int **Datos,int *Carga,int *LRec,int flag);
void Busq_Tabu_Local(int **RutasMejor,int **Costos,int **Datos,int *LRec,int number, int n, int *CostoRutas,int *RutasCambio,int *Carga);

#endif /* Metaheuristicas */
