/*
 *  localsearch.c
 *
 *  Created by Alejandro Santiago on 12/09/20.
 *  aurelio.santiago@upalt.edu.mx
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "types.h"

void aleatoria_construction(int **candidata,int *order, int limitetarea, double TAEM[],struct tarea taeas[])
{
    
	static int iteraciones;
	int **temp;
	static double valor_objetivo,mejor_local;
	mejor_local=makespan_parcialDavid(candidata,order,limitetarea,TAEM,tareas);
    //printf("Mejor local entrante %lf\n",mejor_local);
	//PARTE DE BUSQUEDA LOCAL
    iteraciones=0;
    do{
        iteraciones++;

			temp=vecina_maquina(candidata,order[rand()%(limitetarea+1)],rand()%M,0);
			valor_objetivo=makespan_parcialDavid(candidata,order,limitetarea,TAEM,tareas);
			if(valor_objetivo<mejor_local)
			{
                iteraciones=0;
				mejor_local=valor_objetivo;
				candidata=copia_solucion(temp);
			}
			libera_memoria_matriz(temp,2);
        
	}while(iteraciones<100);
    
    //printf("Mejor local saliente %lf\n",mejor_local);

    
}

int first_derecha(int **candidata,int *order)
{
    int evals=0;
	int i,j,**temp;
	static double valor_objetivo,mejor_local;
	mejor_local=makespan(candidata,order);
    //printf("Mejor local entrante %lf\n",mejor_local);
    for(i=0;i<T;i++){
        for(j=0;j<M;j++){
        temp=vecina_maquina(candidata,order[i],j,0);
        valor_objetivo=makespan(temp, order);
        evals ++;
        if(valor_objetivo<mejor_local)
        {
            mejor_local=valor_objetivo;
            //libera_memoria_matriz(candidata,2);
            candidata=copia_solucion(temp);
            i=0;
            j=0;
            
        }
        libera_memoria_matriz(temp,2);
        if((evals+evaluaciones+3)>=maxevals) //+3 para la comunicación de las PCELLS
        {
            return evals;
        }
        }
    }
    return evals;

    //printf("Mejor local saliente %lf\n",mejor_local);
    
    
}
