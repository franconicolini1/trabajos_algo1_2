#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista de punteros genéricos. */

typedef struct lista lista_t;


/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista.
// Post: Devuelve una lista vacia.
lista_t *lista_crear(void);

// Pre: La lista fue creada
// Post: Devuelve true si la lista esta vacia, false de lo contrario.
bool lista_esta_vacia(const lista_t *lista);

// Pre: La lista fue creada
// Post: Se inserta el dato al principio de la lista y devuelve true si se pudo insertar, false caso contrario.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Pre: La lista fue creada
// Post: Se inserta el dato al final de la lista, devuelve true si se inserto, false en caso contrario.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Pre: La lista fue creada
// Post: Se borra el primer elementos si la lista tiene elementos y lo devuelve como puntero, en caso de estar vacia devuelve NULL.
void* lista_borrar_primero(lista_t *lista);

// Pre: La lista fue creada
// Post: Devuelve un puntero a el primer elemento, en caso de estar vacia devuelve NULL.
void* lista_ver_primero(const lista_t *lista);

// Pre: La lista fue creada
// Post: Devuelve un puntero al ultimo elemento de la lista, si la lista esta vacia devuelve NULL.
void* lista_ver_ultimo(const lista_t* lista);

// Pre: La lista fue creada
// Post: Devuelve el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Pre: La lista fue creada
// Post: Destruye la lista, aplicando la funcion destruir_dato a cada dato de la lista (En caso de que destruir dato no sea NULL).
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

// Pre: La lista fue creada.
// Post: Recorre cada elemento de la lista aplicandole visitar a cada dato.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* DEFINICION TIPO DE DATO */

typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

// Post: Crea un iterador de lista y lo devuelve
lista_iter_t* lista_iter_crear(lista_t *lista);

// Pre: El iterador fue creado.
// Post: Avanza un eslabon de la lista. Devuelve true si se pudo avanzar,
// false de lo contrario (si el actual es el ultimo o actual es NULL).
bool lista_iter_avanzar(lista_iter_t *iter);

// Pre: El iterador fue creado.
// Post: Devuelve un puntero al dato actual.
void* lista_iter_ver_actual(const lista_iter_t *iter);

// Pre: El iterador fue creado.
// Post: Avanza hasta el final de la lista. Devuelve true si funciono, false de lo contrario.
bool lista_iter_al_final(const lista_iter_t *iter);

// Pre: El iterador fue creado.
// Post : Destruye el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Pre: El iterador fue creado.
// Post: Se inserto el dato en la posicion actual.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Pre: El iterador fue creado.
// Post: Se borro el dato en la posicion actual y se lo devuelve como puntero.
void* lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
//
// Las pruebas deben emplazarse en el archivo pruebas_lista.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
void pruebas_lista_estudiante(void);

#endif