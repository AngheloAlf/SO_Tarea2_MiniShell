//
// Created by AngheloAlf10 on 16-07-2017.
//

#include "strParse.h"

char *raw_input(char *outMessage){
    printf("%s", outMessage);

    int inSize = 32;
    char *inData = malloc(sizeof(char)*inSize);
    if(!fgets(inData, inSize, stdin)){ // No se pudo leer
        free(inData);
        return NULL;
    }

    size_t len = strlen(inData);
    if(inData[len-1] == '\n'){ // String completo
        inData[len-1] = '\0'; // Eliminando el salto de linea
        return inData;
    }
    else{ // No se encontro el salto de linea. A seguir leyendo!
        char *auxData = malloc(sizeof(char)*inSize*2); // String mas grande
        strcpy(auxData, inData); // Copiando datos al string final
        while(fgets(inData, inSize, stdin)){ // En caso de error// Lee datos de stdin
            strcat(auxData, inData); // Se concatena al string grande
            len = strlen(auxData);
            if(auxData[len-1] == '\n'){ // Revisando si tenemos toodo el string
                auxData[len-1] = '\0'; // Elimina salto de linea
                free(inData);
                return auxData; // Yay!
            }
            auxData = realloc(auxData, sizeof(char)*(len + inSize)); //String mas grande!
        }
        free(inData);
        free(auxData);
        return NULL;
    }
}

char **split(char *string, char *delimiters){
    char **splitted = malloc(sizeof(char *));
    char *token = strtok(string, delimiters);
    int i = 0;
    splitted[i++] = token;
    while(token != NULL){
        splitted = realloc(splitted, sizeof(char *) * (i + 1));
        token = strtok(NULL, delimiters);
        splitted[i++] = token;
    }
    return splitted;
}
