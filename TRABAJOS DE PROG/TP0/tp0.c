#include "tp0.h"
#include <stdio.h>

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
}


int maximo(int vector[], int n) {
    if (n == 0){
        return -1;
    }
    int posicion = 0;
    for (int i = 0; i < n; i++){

        if (vector[i] > vector[posicion]){
            posicion = i;
        }
    }
    return posicion;
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    for (int i = 0; i < n1 && i < n2; i++){
        if (vector1[i] != vector2[i]){
            if (vector1[i] < vector2[i]){
                return -1;
            }
            return 1;
        }
    }
    if (n1 == n2){ 
        return 0;
    }
    if (n1 < n2){
        return -1;
    }
    return 1; 
}


void seleccion(int vector[], int n) {
    int pos_max = 0;
    int contador = 0;
    for (int i = n - 1; i > -1; i--){
        pos_max = maximo(vector, n - contador);
        swap(&vector[i],&vector[pos_max]);
        contador ++;
    }
} 
