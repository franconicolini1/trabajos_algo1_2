#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

/* Defino el struct nodos */

typedef struct nodos{
    void* dato;
    struct nodos* prox;
} nodos_t;

/* Defino sus primitivas */

nodos_t* crear_nodos(void* valor){
    nodos_t* nodos = malloc(sizeof(nodos_t));

    if (!nodos) return NULL;
    
    nodos->dato = valor;
    nodos->prox = NULL;
    return nodos;
}

/* Defino el struct lista y sus primitivas */

struct lista{
    nodos_t* prim;
    nodos_t* ult;
    size_t largo;
};

lista_t *lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if(!lista) return NULL;

    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = 0;

    return lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->prim == NULL;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodos_t* nodos = crear_nodos(dato);
    if (!nodos) return false;
    nodos->prox = lista->prim;

    lista->prim = nodos;
    if(!lista->prim->prox) lista->ult = nodos;
    lista->largo++;

    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodos_t* nodos = crear_nodos(dato);
    if (!nodos) return false;

    if(!lista->prim){
        lista->prim = nodos;
    }
    else{
        lista->ult->prox = nodos;
    }
    lista->ult = nodos;
    lista->largo++;

    return true;
}

void* lista_ver_primero(const lista_t *lista){
    return lista->prim ? lista->prim->dato : NULL;
}

void* lista_ver_ultimo(const lista_t* lista){
    return lista->ult ? lista->ult->dato : NULL;
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

void* lista_borrar_primero(lista_t* lista){
    if (lista_esta_vacia(lista)) return NULL;
    void* aux = lista->prim->dato;
    void* puntero_aux = lista->prim;
 
    lista->prim = lista->prim->prox;
    if(!lista->prim) lista->ult = NULL;

    free(puntero_aux);
    lista->largo--;
    return aux;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    while (!lista_esta_vacia(lista)){
        void* dato = lista_borrar_primero(lista);

        if (destruir_dato != NULL){
            destruir_dato(dato);
        }
    }
    free(lista);
}

/* Primitivas del iterador interno */

void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra){
    nodos_t* actual = lista->prim;
    
    while (actual && visitar){
        bool estado = visitar(actual->dato, extra);
        if (!estado) break;

        actual = actual->prox;
    }
}

/* Defino el struct del iterador externo  y sus primitivas */

struct lista_iter{
    nodos_t* anterior;
    nodos_t* actual;
    lista_t* lista;
};

lista_iter_t* lista_iter_crear(lista_t *lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if(!iter) return NULL;

    iter->actual = lista->prim;
    iter->anterior = NULL;
    iter->lista = lista;

    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if((!iter->actual && !iter->lista->prim) || (!iter->actual && iter->anterior)) return false;

    if(iter->lista->prim && !iter->actual && !iter->anterior){
        iter->actual = iter->lista->prim;
        return true;
    }
    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;
    return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter){
    return iter->actual ? iter->actual->dato : NULL;
}

bool lista_iter_al_final(const lista_iter_t* iter){
    return !iter->actual? true : false;
}

void lista_iter_destruir(lista_iter_t* iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t* iter, void* dato){
    nodos_t* nodos = crear_nodos(dato);
    if(!nodos) return false;

    iter->lista->largo++;
    
    if(!iter->actual && iter->anterior){
        if(!iter->lista->prim){
            iter->lista->prim = nodos;
        }
        else{
            iter->lista->ult->prox = nodos;
        }
        iter->lista->ult = nodos;
        iter->anterior = iter->anterior->prox;
        iter->actual = nodos;

        return true;
    }

    nodos->prox = iter->actual;
    if(!iter->anterior) iter->lista->prim = nodos;
    else iter->anterior->prox = nodos;
    iter->actual = nodos;

    if(!iter->lista->prim->prox) iter->lista->ult = nodos;

    return true;
}

void* lista_iter_borrar(lista_iter_t *iter){
    if((!iter->actual && !iter->anterior) || !iter->actual) return NULL;

    iter->lista->largo--;

    if(!iter->anterior){
        if(!iter->actual->prox){
            iter->lista->ult = NULL;
        }
        void* aux = iter->lista->prim->dato;
        void* puntero_aux = iter->lista->prim;

        iter->lista->prim = iter->lista->prim->prox;
        iter->actual = iter->lista->prim;
        free(puntero_aux);
        
        return aux;
    }

    if(iter->actual == iter->lista->ult) iter->lista->ult = iter->anterior;
    
    void* dato = iter->actual->dato;

    iter->actual = iter->actual->prox;

    free(iter->anterior->prox);
    iter->anterior->prox = iter->actual;

    return dato;
}