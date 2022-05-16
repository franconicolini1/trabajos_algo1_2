#include "pila.h"

#include <stdlib.h>
#include <stdbool.h>
#define CAPACIDAD_MINIMA 100
#define NUM_MODIFICA_CAP 2 
#define NUM_DISMINUYE_CAP 4 

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t *pila_crear(void){
    pila_t *pila = malloc(sizeof(pila_t));

    if (pila == NULL){
        return NULL;
    }
    pila->cantidad = 0;

    pila->datos = malloc(sizeof(void*) * CAPACIDAD_MINIMA);

    if (pila->datos == NULL){
        free(pila);
        return NULL;
    }

    pila->capacidad = CAPACIDAD_MINIMA;
    return pila;
}

void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return (pila->cantidad == 0);
}

bool pila_redimensionar(pila_t *pila, size_t nueva_cap){
    if (nueva_cap < CAPACIDAD_MINIMA){
        nueva_cap = CAPACIDAD_MINIMA;
    }
    void **nuevo = realloc(pila->datos, nueva_cap * sizeof(void*));

    if (nuevo == NULL){
        return false;
    }
    pila->capacidad = nueva_cap;
    pila->datos = nuevo;

    return true;
}

bool pila_apilar(pila_t *pila, void *valor){
    if (pila->cantidad == pila->capacidad){
        if(!pila_redimensionar(pila, NUM_MODIFICA_CAP * pila->capacidad)){
            return false;
        }
    }
    pila->datos[pila->cantidad] = valor;
    pila->cantidad++;

    return true;
}

void *pila_ver_tope(const pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    void *valor = pila->datos[pila->cantidad - 1];
    return valor;
}

void *pila_desapilar(pila_t *pila){
    if (pila_esta_vacia(pila)){
        return NULL;
    }
    pila->cantidad--;

    void *valor = pila->datos[pila->cantidad];

    if(pila->cantidad * NUM_DISMINUYE_CAP <= pila->capacidad && pila->capacidad > CAPACIDAD_MINIMA){
        pila_redimensionar(pila, pila->capacidad / NUM_MODIFICA_CAP);
    }

    return valor;

}