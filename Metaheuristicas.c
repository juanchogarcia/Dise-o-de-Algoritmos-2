
#include "Metaheuristicas.h"

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
        Rutas[rnd][LRec[rnd]] = i;
        LRec[rnd]++;
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
                //Penalizacion???
                if (Cargas[1][i] > Datos[2][Rutas[i][j]]) {
                    Cargas[0][i] = Cargas[0][i] + (Cargas[1][i] - Datos[2][Rutas[i][j]])*5;
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

    if (buscarTaboo(rnd, rndC1, rnd, rndC2,taboo,tabooTam)) {
        //printf("hola2\n");
        taboo[0][posTaboo]=rnd;
        taboo[1][posTaboo]=rndC1;
        taboo[2][posTaboo]=rnd;
        taboo[3][posTaboo]=rndC2;
                
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
    }
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

        if (buscarTaboo(rnd, rndC1, rnd2, rndC2,taboo,tabooTam)) {
        
        //printf("hola\n");
        taboo[0][posTaboo]=rnd;
        taboo[1][posTaboo]=rndC1;
        taboo[2][posTaboo]=rnd2;
        taboo[3][posTaboo]=rndC2;
                
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

    }
    return CostoR;

}

//Funcion de reduccion de rutas.

void ReduccionRutas(int number,int **RutasMejor,int **Datos,int *Carga,int *LRec,int flag){
    int rnd;
    int rnd2;
    int rndC1;
    int rndC2;
    int auxiliar;
    int redRut = 0;
    if (flag){
    	while (redRut < 50000) {
    		rnd = rand() % (number);
            	while (LRec[rnd] < 1) {
                	printf("%d ", redRut);
                	rnd = rand() % (number);
            	}

            	rnd2 = rand() % (number);
            	while (LRec[rnd2] < 1) {
                	rnd2 = rand() % (number);
            	}
            	
            	/*
            	while (rnd == rnd2) {
                	rnd2 = rand() % (number);
                	while (LRec[rnd2] < 1) {
                    		rnd2 = rand() % (number);
                	}
            	}
		*/
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
    		redRut++;
    	}
    }
}

//Metaheuristica hibrida que combina la busqueda local con la tabu.

void Busq_Tabu_Local(int **RutasMejor,int **Costos,int **Datos,int *LRec,int number, int n, int *CostoRutas,int *RutasCambio,int *Carga){

	int cic,it,auxiliar;
	int CostoMejor;
	int i1 = -1;
    	int i2 = -1;
    	int j1 = -1;
    	int j2 = -1;
    	//Imprime las rutas iniciales.
    	ImprimirMatriz(RutasMejor, number, n);
    	//Calcula el costo de las rutas iniciales.
    	int CostoActual = Costo(Costos, RutasMejor, Datos, number, n, CostoRutas, RutasCambio);
    	printf("%d\n", CostoActual);
    	clock_t start = clock();
	while (1) {
        	cic = 0;
        	CostoMejor = CostoActual;
        
        	int bol = 1;
        	while (cic < 50) {
        	    posTaboo++;
        	    if(posTaboo==tabooTam){
        	        posTaboo=0;
        	    }
        	    if (bol){
        	        bol=0;
        	        CostoMejor = EntreCiudad(&i1, &i2, &j1, &j2, RutasMejor, CostoActual, Costos, Datos, LRec, number, n, CostoRutas, RutasCambio);
                    }else{
                	bol=1;                
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


        	if (CostoMejor < CostoActual) {
            		printf("%d\n", CostoMejor);
            		CostoActual = CostoMejor;
            		if(CostoActual<4500){
                    		clock_t end = clock();
                    		float seconds = (float) (end - start) / CLOCKS_PER_SEC;
                    		printf("%f\n",seconds);
            		}
            		ImprimirMatriz(RutasMejor,number,n);
        	}
 	       it++;
 	   }
}
