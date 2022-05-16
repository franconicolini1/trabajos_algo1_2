#include "cola.h"
#include <stdlib.h>
#include <stdbool.h>

/* Defino el struct Nodo */

typedef struct nodo{
    void* dato;
    struct nodo* prox;
} nodo_t;

/* Defino sus primitivas */

nodo_t* crear_nodo(void* valor){
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if (nodo == NULL){
        return NULL;
    }
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

/* Defino el struct cola y sus primitivas */

struct cola{
    nodo_t* prim;
    nodo_t* ult;
};

cola_t *cola_crear(void){
    cola_t *cola = malloc(sizeof(cola_t));

    if (cola == NULL){
        return NULL;
    }
    cola->prim = NULL;
    cola->ult = NULL;
    return cola;
}

bool cola_esta_vacia(const cola_t *cola){
    return cola->prim == NULL;
}

void *cola_ver_primero(const cola_t *cola){
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    return cola->prim->dato;
}

bool cola_encolar(cola_t *cola, void *valor){
    nodo_t* nodo = crear_nodo(valor);
    
    if (nodo == NULL){
        return false;
    }
    if (cola_esta_vacia(cola)){
        cola->prim = nodo;
    }
    else{
        cola->ult->prox = nodo;
    }
    cola->ult = nodo;
    
    return true;
}

void *cola_desencolar(cola_t *cola){
    if (cola_esta_vacia(cola)){
        return NULL;
    }
    void* aux = cola->prim->dato;
    void* puntero_aux = cola->prim;

    cola->prim = cola->prim->prox;
    free(puntero_aux);
    return aux;
}

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)){
    while (!cola_esta_vacia(cola)){
        void* dato = cola_desencolar(cola);

        if (destruir_dato != NULL){
            destruir_dato(dato);
        }
    }
    free(cola);
}



