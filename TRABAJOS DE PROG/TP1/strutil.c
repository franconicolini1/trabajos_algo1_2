#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <string.h>
#include "strutil.h"
#include <stdio.h>

char *substr(const char *str, size_t n){

    char* slice = strndup(str, n);

    return slice; // Si slice es null es porque fallo la funcion (su malloc).
}

size_t contar_separadores(const char *str, char sep, size_t largo){
    size_t contador = 0;
    
    for(size_t i = 0; i < largo; i++){
        if (str[i] == sep) contador++;
    }
    return contador;
}

char **split(const char *str, char sep){
    size_t largo = strlen(str);
    size_t tam_arr = 2 + contar_separadores(str, sep, largo);

    char** arreglo = malloc(sizeof(char*) * tam_arr);
    if(!arreglo) return NULL;

    size_t pos_ant = 0; // De la cadena
    size_t pos_arr = 0;


    for(size_t j = 0; j <= largo; j++){
        
        if(str[j] == '\0' || str[j] == sep){
            arreglo[pos_arr] = substr(&str[pos_ant], j - pos_ant);
            
            if(!arreglo[pos_arr]){
                for(size_t i = 0; i < pos_arr - 1; i++){
                    free(arreglo[i]);
                }
                free(arreglo);
                return NULL;
            }

            pos_arr++;
            pos_ant = j + 1;
        }
    }
    arreglo[tam_arr - 1] = NULL;
    return arreglo;
}

size_t calcular_largo_cadena(char **strv){
    size_t largo = 0;

    for(size_t i = 0; strv[i] != NULL; i++){
        largo += (strlen(strv[i]) + 1);
    }
    return largo;
}

char *join(char **strv, char sep){
    size_t largo = calcular_largo_cadena(strv);

    if(largo == 0) largo++;
    char* resultado = malloc(sizeof(char*) * largo);
    if(!resultado) return NULL;

    size_t pos_str_act = 0;

    for(size_t i = 0; strv[i] != NULL; i++){ // Seguira siendo O(n) ya que recorre cada caracter de una cadena de n caracteres.
        
        for(size_t j = 0; strv[i][j] != '\0'; j++){
            resultado[pos_str_act] = strv[i][j];
            pos_str_act++;
        }
        if(strv[i + 1] != NULL && sep != '\0'){
            resultado[pos_str_act] = sep;
            pos_str_act++;
        }
    }

    resultado[pos_str_act] = '\0';
    return resultado;
}

void free_strv(char *strv[]){
    size_t contador = 0;

    while (strv[contador]){
        free(strv[contador]);
        contador++;
    }
    free(strv);
}
