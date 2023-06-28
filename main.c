#include <stdio.h>
#include <stdlib.h>
#include "funcionesCesar.h"
#include <string.h>

int main()
{
    //Bloque declaraciones
    int opcion,
        cantElemt,
        cantClave;

    char nombreArchivo[MAX_LONGITUD];
    char nombreArchClave[MAX_LONGITUD];

    char* aux,
        * vecDatos,
        * vecClave;

    //Asigno memoria
    vecDatos = (char*)calloc(1, sizeof(char));
    if (vecDatos == NULL) {
        printf("\nError al asignar memoria.");
        return(1);
    }

    vecClave = (char*)calloc(1, sizeof(char));
    if (vecClave == NULL){
        printf("\nError al asignar memoria");
    }

    //DETERMINAR SI SE VA A DESENCRIPTAR O ENCRIPTAR
    //Pido la operacion que se va a hacer
    printf("\nIngrese 1 para encriptar, 2 para decodificar: ");
    scanf("%d", &opcion);
    while (opcion != 1 && opcion != 2) {
        printf("\nIngrese una opcion valida: ");
        scanf("%d", &opcion);
    }
    fflush(stdin);

    // CARGAR LOS DATOS A MEMORIA
    // Pido el archivo que se va a trabajar
    printf("\nIngrese el nombre del archivo a aplicar la operacion: ");
    if (fgets(nombreArchivo, MAX_LONGITUD, stdin) == NULL) {
        printf("\nError al leer el nombre del archivo.");
        return(1);
    }
    aux = strchr(nombreArchivo, '\n');
    if (aux != NULL) {
        *aux = '\0';
    }
    else {
        printf("\nNombre de archivo invalido o demasiado largo.");
        return(1);
    }

    // Abro el archivo
    FILE* archivo = fopen(nombreArchivo, "rt");
    if (archivo == NULL) {
        printf("\nError al abrir el archivo.");
        return(1);
    }


    //Leo el archivo y lo cargo a un vector
    vecDatos = cargarDatos(nombreArchivo, &cantElemt, vecDatos);


    //CARGAR LA CLAVE A MEMORIA
    // Pido el archivo done esta la clave
    printf("\nIngrese el nombre del archivo donde esta la clave: ");
    if (fgets(nombreArchClave, MAX_LONGITUD, stdin) == NULL) {
        printf("\nError al leer el nombre del archivo.");
        return(1);
    }
    aux = strchr(nombreArchClave, '\n');
    if (aux != NULL) {
        *aux = '\0';
    }
    else {
        printf("\nNombre de archivo invalido o demasiado largo.");
        return(1);
    }

    // Abro el archivo
    FILE* clave = fopen(nombreArchClave, "rt");
    if (clave == NULL) {
        printf("\nError al abrir el archivo.");
        return(1);
    }

    //Leo el archivo y lo cargo a un vector
    vecClave = cargarDatos(nombreArchClave, &cantClave, vecClave);


    //printf("\nLa cantidad de caracteres leido datos es cant: %d", cantElemt);
    printf("\nCadena que se va a operar: ");
    for(int x = 0; x < cantElemt ; x++){
        printf("%c", vecDatos[x]);
    }

    //printf("\nLa cantidad de caracteres leido datos es cant: %d", cantClave);
    printf("\nLa clave de encriptacion es: ");
    for(int x = 0; x < cantClave ; x++){
        printf("%c", vecClave[x]);
    }

    //La misma funcion hace ambas cosas
    operar(vecDatos,cantElemt,vecClave,cantClave);

    if(opcion == 1){
        printf("\nEl texto encriptado es: ");
    } else {
        printf("\nEl texto desencriptado es: ");
    }
    for(int x = 0; x < cantElemt ; x++){
            printf("%c", vecDatos[x]);
    }


    //Libero lo que use
    fclose(archivo);
    free(vecDatos);
    free(vecClave);

    return 0;
}
