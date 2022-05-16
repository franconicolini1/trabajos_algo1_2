#include "abb.h"
#include "cola.h"
#include <string.h>
#include <stdlib.h>

typedef struct ab ab_t;

typedef struct ab {
  ab_t* izq;
  ab_t* der;

  char* clave;
  void* dato;

} ab_t;

ab_t* ab_crear(const char* clave, void* dato) {
  
  ab_t* ab = malloc(sizeof(ab_t));
  if (!ab) return NULL;

  ab->izq = NULL;
  ab->der = NULL;

  ab->clave = strdup(clave);
  ab->dato = dato;

  return ab;
} 

void* ab_destuir(ab_t* ab) {

  void* valor = ab->dato;

  free(ab->clave);
  free(ab);

  return valor;
}

typedef struct abb {
  ab_t* raiz;
  size_t cantidad;

  abb_comparar_clave_t comp_func;
  abb_destruir_dato_t destruir_dato;

} abb_t;

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {

  abb_t* abb = malloc(sizeof(abb_t));
  if (!abb) return NULL;

  abb->raiz = NULL;
  abb->comp_func = cmp;
  abb->cantidad = 0;
  abb->destruir_dato = destruir_dato;

  return abb;
}

bool abb_obtener_abs(abb_t* arbol, const char* clave, ab_t** hijo, ab_t** padre) {

  ab_t* ab_anterior = NULL;
  ab_t* ab_actual = arbol->raiz;

  while (ab_actual) {
    if (arbol->comp_func(clave, ab_actual->clave) == 0) {
      *hijo = ab_actual;
      *padre = ab_anterior;
      return true;
    }
    if (arbol->comp_func(clave, ab_actual->clave) > 0) {
      ab_anterior = ab_actual;
      ab_actual = ab_actual->der;

    } else {
      ab_anterior = ab_actual;
      ab_actual = ab_actual->izq;
    }

  }
  *hijo = ab_actual;
  *padre = ab_anterior;
  return false;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {

  ab_t* ab_anterior,* ab_actual;

  // Si ya esta la clave
  if (abb_obtener_abs(arbol, clave, &ab_actual, &ab_anterior)) {
    if (arbol->destruir_dato) {
      arbol->destruir_dato(ab_actual->dato);
    } 
    ab_actual->dato = dato;
    return true;

  }
  // Casos que no esta la clave
  // Caso que esta vacio
  if (!ab_actual && !ab_anterior) {
    arbol->raiz = ab_crear(clave, dato);
    arbol->cantidad++;
    return arbol->raiz != NULL;
  // Caso que no esta vacio
  } else if (arbol->comp_func(clave, ab_anterior->clave) > 0) {
    ab_anterior->der = ab_crear(clave, dato);
    ab_actual = ab_anterior->der;

  } else {
    ab_anterior->izq = ab_crear(clave, dato);
    ab_actual = ab_anterior->izq;
  }
  arbol->cantidad++;
  return ab_actual != NULL;
  
}

/*
*
* Funcion auxiliar para el caso de borrar que el elemento tiene 2 hijos
* Pasas la raiz del arbol que queres encontrar el minimo y la funcion de comparacion
*
*/
ab_t* min_ab_superior(ab_t* raiz) {
  // Raiz esta garantizado no ser NULL
  ab_t* min = raiz;

  while (min->izq) {
    min = min->izq;
  }

  return min;
}

void *abb_borrar_un_hijo(abb_t* arbol ,ab_t* padre, ab_t* hijo, const char* clave) {
  if (!padre) {
    if (hijo->izq) arbol->raiz = hijo->izq;
    else arbol->raiz = hijo->der;

    arbol->cantidad--;
    return ab_destuir(hijo);
  }
  if (arbol->comp_func(clave, padre->clave) > 0) {
      // der der
      if (!hijo->izq) padre->der = hijo->der;
      // der izq
      else padre->der = hijo->izq;
  } else {
      // izq der
      if (!hijo->izq) padre->izq = hijo->der;
      // izq izq
      else padre->izq = hijo->izq;
    }
    arbol->cantidad--;
    return ab_destuir(hijo);

}

void *abb_borrar(abb_t *arbol, const char *clave) {

  ab_t* ab_anterior,* ab_actual;

  // NO esta la clave
  if (!abb_obtener_abs((abb_t*) arbol, clave, &ab_actual, &ab_anterior)) {
    return NULL;
  // Si esta la clave
  }
  // Caso que es una hoja
  if (!ab_actual->izq && !ab_actual->der) {
    if (!ab_anterior) {
      arbol->raiz = NULL;
    } else {
      if (arbol->comp_func(clave, ab_anterior->clave) > 0) ab_anterior->der = NULL;
      else ab_anterior->izq = NULL;
    }
    arbol->cantidad--;
    return ab_destuir(ab_actual);
  // Caso que tiene un solo hijo
  } else if ((!ab_actual->izq || !ab_actual->der)) {
    return abb_borrar_un_hijo(arbol, ab_anterior, ab_actual, clave);
  // Casos que tiene 2 hijos
  } else {
    ab_t* min =  min_ab_superior(ab_actual->der);

    void* valor = ab_actual->dato;
    char* nueva_clave = strdup(min->clave);

    ab_actual->dato = abb_borrar(arbol, nueva_clave);
    char* aux = ab_actual->clave;
    ab_actual->clave = nueva_clave;
    free(aux);

    return valor;
  }
}

void *abb_obtener(const abb_t *arbol, const char *clave) {

  ab_t* ab_anterior,* ab_actual;

  if (abb_obtener_abs((abb_t*) arbol, clave, &ab_actual, &ab_anterior)) {
    return ab_actual->dato;

  } else {
    return NULL;
  }
}

bool abb_pertenece(const abb_t *arbol, const char *clave) {

  ab_t* ab_anterior,* ab_actual;

  return abb_obtener_abs((abb_t*) arbol, clave, &ab_actual, &ab_anterior);
}

size_t abb_cantidad(abb_t *arbol) {
  return arbol->cantidad;
}

// Funcion recursiva que destruye 
void _abb_destruir(ab_t* raiz, abb_t* arbol) {
  if (raiz == NULL) {
    return;
  }
  // Uso postorder para que se borren corectamente
  _abb_destruir(raiz->izq, arbol);
  _abb_destruir(raiz->der, arbol);

  // Destuye el ab y destruye el dato que devuelve
  if (arbol->destruir_dato) {
    arbol->destruir_dato(ab_destuir(raiz));
  } else {
    ab_destuir(raiz);
  }
  
}

void abb_destruir(abb_t *arbol) {
  _abb_destruir(arbol->raiz, arbol);

  free(arbol);

}

bool _abb_in_order(ab_t *raiz, bool visitar(const char *, void *, void *), void *extra) {
  if (!raiz) return true;

  // Si un solo visitar devuelve false se corta todo
  if (!_abb_in_order(raiz->izq, visitar,  extra)) {
    return false;
  }
  if (!visitar(raiz->clave, raiz->dato, extra)) {
    return false;
  }
  if (!_abb_in_order(raiz->der, visitar,  extra)) {
    return false;
  }
  return true;
}

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
  _abb_in_order(arbol->raiz, visitar,  extra);
  
}

typedef struct abb_iter{
  // Implementacion con cola auxiliar
  const abb_t* abb;
  cola_t* cola;

} abb_iter_t;

void _cola_abb(const abb_t* abb, ab_t* raiz, cola_t* cola){
  // Uso in-order para encolar los datos.
  if (raiz == NULL) {
    return;
  }
  _cola_abb(abb, raiz->izq, cola);
  cola_encolar(cola, raiz->clave);
  _cola_abb(abb, raiz->der, cola);
  
}

cola_t* cola_abb(const abb_t* abb){
  cola_t* cola = cola_crear();
  if(!cola) return NULL;

  _cola_abb(abb, abb->raiz, cola);
  return cola;
}

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
  abb_iter_t* iter = malloc(sizeof(abb_iter_t));
  if(!iter) return NULL;

  iter->abb = arbol;
  iter->cola = cola_abb(arbol);

  return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter){
  if(!cola_desencolar(iter->cola)) return false;

  return true;
}

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
  return cola_ver_primero(iter->cola);
}

bool abb_iter_in_al_final(const abb_iter_t *iter){
  return cola_esta_vacia(iter->cola);
}

void abb_iter_in_destruir(abb_iter_t* iter){
  cola_destruir(iter->cola, NULL);
  free(iter);
}