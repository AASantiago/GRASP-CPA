/*
 *  eft.c
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
#include <time.h>

int **EFT(int *order)
{
	int i,j,pos;
	int **regresa;
	double menor,temp;
	int iteracion;
	iteracion=0;
	regresa=reserva_matriz_int(2,T);
	for(i=0;i<T;i++)
		regresa[1][i]=0;
	
	for(i=0;i<T;i++)
	{
		menor=9999;
		for(j=0;j<M;j++)
		{
			regresa[0][order[i]]=j;
			temp=makespan_parcial(regresa, order, i);
			if(temp<menor) //< o <= cambia mucho los empates 
			{
				menor=temp;
				pos=j;
			}
		}
		regresa[0][order[i]]=pos;
	}
	return regresa;
}

double EFTPartial(int *order, int upTo, int **matrizTrabajo, double TAEM[], struct tarea tareas[])
{
    int i,j,pos;
    double menor,temp;
    
    if ((i = upTo - 1) < 0)
    {
        i = 0;
    }
    
    for( ;i <= upTo; i++)
    {
        menor=9999;
        for(j=0;j<M;j++)
        {
            matrizTrabajo[0][order[i]]=j;
            temp=makespan_parcialDavid(matrizTrabajo, order, i, TAEM, tareas);
            if(temp<menor) //< o <= cambia mucho los empates
            {
                menor=temp;
                pos=j;
            }
        }
        matrizTrabajo[0][order[i]]=pos;
    }
    return menor;
}
