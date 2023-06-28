#include <stdio.h>
#include <stdlib.h>
#include "funcionesCesar.h"

char* cargarDatos(char* nombreFL, int* elem, char* vector)
{
    int cant = 0;
    char* aux = vector;
    FILE* archivo = fopen(nombreFL, "rt");
    if (archivo == NULL)
    {
        printf("\nError al abrir el archivo.\n");
        return NULL;
    }

    char buffer;
    while((buffer = fgetc(archivo))!= EOF)
    {
        *aux = buffer;
        cant++;
        vector = realloc(vector, sizeof(char) * (cant + 1));
        if (vector == NULL)
        {
            printf("\nError al asignar memoria.\n");
            fclose(archivo);
            return NULL;
        }
        aux = vector + cant;
    }
    fclose(archivo);
    *elem = cant;

    return vector;
}

//Determina si un elemento existe o no dentro de la clave
char* existe (char* laClave,int cantE, char elemento)
{
    char* inicio = laClave;
    for(char* fin = laClave + cantE; inicio != fin; inicio++)
    {
        if(*inicio == elemento)
        {
            return(inicio);
        }
    }
    return(NULL);
}

//Codifica y decodifica
char* operar(char* vectorDatos,int cantDatos,char* vectorClave,int cantClave)
{
    char* auxD = vectorDatos,
        * finD = vectorDatos + cantDatos,
        * auxC;

    for(; auxD != finD; auxD++)
    {
        auxC = vectorClave;

        //Busco si existe el elemento en la clave. Si existe, lo cambio por el que corresponda. Sino, no hago nada.
        char* pos = existe(vectorClave,cantClave,*auxD);
        if(pos != NULL)
        {
            /*Calculo el desplazamiento. Tomo la posicion donde esta el elemento
            Luego le resto la posicion base del vector y la divido por el tam del tipo de dato
            Eso me da cuanto se desplazo respecto al inicio
            Luego a eso le sumo el desplazamiento
            y divido por la cantidad de elementos para corregir el exceso
            El resultado es un numero que representa cuanto me tengo que desplazar respecto al inicio de la clave
            */
            auxC += ((pos - vectorClave)/sizeof(char) + DESPLAZAMIENTO) % cantClave;
            *auxD = *auxC;
        }
    }

    return(vectorDatos);
}
