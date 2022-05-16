#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


static void prueba_lista_vacia(void) {
    printf("INICIO DE PRUEBAS CON LISTA VACIA\n");

    lista_t* lista = lista_crear();

    print_test("Se creo la lista vacia", lista != NULL);

    /*Pruebo operaciones con una lista vacia*/
    print_test("Ver primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("Esta vacia", lista_esta_vacia(lista));
    print_test("Ver el ultimo es NULL", lista_ver_ultimo(lista) == NULL);
    print_test("El largo es cero", lista_largo(lista) == 0);
    print_test("Borrar primero es NULL", lista_borrar_primero(lista) == NULL);

    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true); 

}

static void pruebas_con_algunos_elementos(void){
    printf("\nINICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");

    lista_t *lista = lista_crear();
    void* valor = (void*) 53;
    void* cadena = "hola";

    /* Pruebas con insertar primero */
    lista_insertar_primero(lista, valor);
    print_test("El primero es 53", lista_ver_primero(lista) == valor);
    print_test("El ultimo es 53", lista_ver_ultimo(lista) == valor);

    lista_insertar_primero(lista, cadena);
    print_test("El primero es hola", lista_ver_primero(lista) == cadena);
    print_test("El ultimo es 53", lista_ver_ultimo(lista) == valor);

    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("El largo es dos", lista_largo(lista) == 2);

    print_test("Ver primero es hola", lista_ver_primero(lista) == cadena);
    print_test("Ver ultimo es 53", lista_ver_ultimo(lista) == valor);

    lista_destruir(lista, NULL);
    print_test("La lista con elementos fue destruida", true);

    /* Pruebas con insertar ultimo */
    lista_t* lista2 = lista_crear();
    
    print_test("Se creo la lista vacia", lista2 != NULL);

    lista_insertar_ultimo(lista2, cadena);
    print_test("Ver primero es cadena", lista_ver_primero(lista2) == cadena);
    print_test("Ver ultimo es cadena", lista_ver_ultimo(lista2) == cadena);

    lista_insertar_ultimo(lista2, valor);
    print_test("Ver primero es cadena", lista_ver_primero(lista2) == cadena);
    print_test("Ver ultimo es valor", lista_ver_ultimo(lista2) == valor);
    print_test("El largo es dos", lista_largo(lista2) == 2);
    print_test("No esta vacia", !lista_esta_vacia(lista2));

    print_test("Borrar primero devuelve cadena", lista_borrar_primero(lista2) == cadena);
    print_test("El largo es 1", lista_largo(lista2) == 1);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista2));

    lista_destruir(lista2, NULL);
    print_test("La lista fue destruida", true);


    /* Pruebas con NULL*/
    lista_t* lista3 = lista_crear();
    print_test("Se creo la lista vacia", lista3 != NULL);

    lista_insertar_primero(lista3, NULL);

    print_test("La lista3 no esta vacia", !lista_esta_vacia(lista3));
    print_test("El primero es NULL", lista_ver_primero(lista3) == NULL);
    print_test("Borrar primero devuelve NULL", lista_borrar_primero(lista3) == NULL);
    print_test("La lista3 esta vacia", lista_esta_vacia(lista3));

    lista_destruir(lista3, NULL);
    print_test("La lista fue destruida", true); 
}

static void pruebas_volumen(int volumen){
    printf("\nINICIO PRUEBAS DE VOLUMEN\n");

    lista_t* lista = lista_crear();
    print_test("Se creo la lista vacia", lista != NULL);

    /*Creo arreglo de 10000 elementos*/
    int arreglo[volumen];

    /* Encolo 10000 elementos, estado sera false si fallo algo */

    bool estado = true;

    for (int i = 0; i < volumen; i++){
        arreglo[i] = i;
        estado = lista_insertar_ultimo(lista, &arreglo[i]);
        if (!estado){
            break;
        }
    }
    print_test("Se insertaron 10000 elementos", estado);

    /*Verifico que al borrar primero se haga correctamente correctamente*/
    for (int j = 0; j < volumen; j++){
        void *aux = lista_borrar_primero(lista);
        if(aux != &arreglo[j]){
            estado = false;
            break;
        }
    }
    print_test("Elementos borrados correctamente", estado);
    print_test("La lista esta vacia", lista_esta_vacia(lista));

    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);
}

void destruir_lista_en_lista(void* dato){
    /* Destruye una cola dentro de una cola, usando sus primitiva */
       lista_destruir(dato, NULL);
    }

static void pruebas_destruir(void){ /* Ya fue probado pasandole NULL */

    printf("\nINICIO DE PRUEBAS DESTRUIR\n");

    /* Destruir pasandole free() */

    lista_t* lista = lista_crear();
    print_test("Se creo la lista vacia", lista != NULL);

    for (int j = 0; j < 3; j++){
        int* aux = malloc(sizeof(int));
        lista_insertar_ultimo(lista, aux);
    }

    lista_destruir(lista, free);
    print_test("La lista fue destruida con free", true);

    /* Pruebas con una funcion que destruye listas enlistadas */

    lista_t* lista2 = lista_crear();

    for (int j = 0; j < 3; j++){
        lista_t* aux = lista_crear();
        lista_insertar_ultimo(lista2, aux);
    }

    lista_destruir(lista2, destruir_lista_en_lista);
    print_test("La lista con listas fue destruida", true);

}

bool sumar(void* dato, void* extra){
    if(*(int*)dato > 8) return false;
    
    *(int*)extra += *(int*)dato;
    return true;
}

static void pruebas_iter_interno(void){
    printf("\nINICIO DE PRUEBAS ITER INTERNO\n");

    lista_t* lista = lista_crear();
    print_test("Se creo la lista vacia", lista != NULL);

    int suma_total = 0;
    int resultado = 10;
    int arreglo[5];

    for (int i = 0; i < 5; i++){
        arreglo[i] = i;
        lista_insertar_ultimo(lista, &arreglo[i]);
    }

    lista_iterar(lista, sumar, (void*)&suma_total);

    print_test("Suma es 10", resultado == suma_total);

    lista_destruir(lista, NULL);
    print_test("La lista fue destruida", true);

    /* Caso en que sumar devuelve false */
    lista_t* lista2 = lista_crear();
    print_test("Se creo la lista vacia", lista2 != NULL);

    suma_total = 0;
    resultado = 36;
    int arreglo2[10];

    for(int j = 0; j < 10; j++){
        arreglo2[j] = j;
        lista_insertar_ultimo(lista2, &arreglo2[j]);
    }

    lista_iterar(lista2, sumar, (void*)&suma_total);

    print_test("Suma es 36", resultado == suma_total);

    lista_destruir(lista2, NULL);
    print_test("La lista fue destruida", true);

}

static void pruebas_basicas_iter_externo(void){
    printf("\nINICIO DE PRUEBAS ITER EXTERNO\n");

    /* Con lista vacia */
    lista_t* lista = lista_crear();
    print_test("Se creo la lista vacia", lista != NULL);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("Se creo el iter", iter != NULL);

    print_test("Actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Estamos al final", lista_iter_al_final(iter));
    print_test("Avanzar es false", !lista_iter_avanzar(iter));

    /* Con algunos elementos */
    void* valor = (void*)53;
    lista_insertar_primero(lista, valor);
    print_test("Actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("Avanzar es true", lista_iter_avanzar(iter));
    print_test("No estamos al final", !lista_iter_al_final(iter));
    print_test("Actual es valor", lista_iter_ver_actual(iter) == valor);
    print_test("Avanzar da true", lista_iter_avanzar(iter));
    print_test("Estamos al final", lista_iter_al_final(iter));
    print_test("Actual es NULL", lista_iter_ver_actual(iter) == NULL);  
    print_test("Avanzar es false", !lista_iter_avanzar(iter));

    lista_destruir(lista, NULL);
    print_test("La lista se destruyo", true);

    lista_iter_destruir(iter);
    print_test("El iter se destruyo", true);

}

static void pruebas_insertar_iter_externo(void){
    printf("\nINICIO DE PRUEBAS INSERTAR\n");

    lista_t* lista = lista_crear();
    print_test("Se creo una lista vacia", lista != NULL);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("Se creo el iter", iter != NULL);

    void* valor = (void*)1;
    void* valor2 = (void*)2;
    void* valor3 = (void*)3;

    print_test("Se inserto un valor al inicio", lista_iter_insertar(iter, valor));
    print_test("El primero es valor", lista_ver_primero(lista) == valor);
    print_test("El ultimo es valor", lista_ver_ultimo(lista) == valor);
    print_test("El actual es valor", lista_iter_ver_actual(iter) == valor);
    print_test("El largo es uno", lista_largo(lista) == 1);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));

    print_test("Se inserta al inicio", lista_iter_insertar(iter, valor2));
    print_test("El primero es valor2", lista_ver_primero(lista) == valor2);
    print_test("Avanzar da true", lista_iter_avanzar(iter));
    print_test("El actual es valor", lista_iter_ver_actual(iter) == valor);
    print_test("El ultimo es valor", lista_ver_ultimo(lista) == valor);
    print_test("El largo es dos", lista_largo(lista) == 2);
    print_test("La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("El primero es valor2", lista_ver_primero(lista) == valor2);

    lista_destruir(lista, NULL);
    print_test("La lista se destruyo", true);

    lista_iter_destruir(iter);
    print_test("El iter se destruyo", true);

    /* Insertar en el medio */
    lista_t* lista2 = lista_crear();
    print_test("Se creo una lista vacia", lista2 != NULL);

    lista_iter_t* iter2 = lista_iter_crear(lista2);
    print_test("Se creo el iter", iter2 != NULL);

    print_test("Se inserto al inicio", lista_insertar_primero(lista2, valor3));
    print_test("Se inserto al inicio", lista_insertar_primero(lista2, valor));

    print_test("Se avanzo correctamente", lista_iter_avanzar(iter2));
    print_test("Se avanzo correctamente", lista_iter_avanzar(iter2));
    print_test("Se inserta en el medio", lista_iter_insertar(iter2, valor2));
    print_test("El largo es tres", lista_largo(lista2) == 3);
    print_test("El primero es valor", lista_ver_primero(lista2) == valor);
    print_test("El ultimo es valor3", lista_ver_ultimo(lista2) == valor3);
    print_test("La lista2 no esta vacia", !lista_esta_vacia(lista2));
    print_test("El actual es valor2", lista_iter_ver_actual(iter2) == valor2);

    lista_destruir(lista2, NULL);
    print_test("La lista se destruyo", true);

    lista_iter_destruir(iter2);
    print_test("El iter se destruyo", true);

    /* Insertar al final */
    lista_t* lista3 = lista_crear();
    print_test("Se creo una lista vacia", lista3 != NULL);

    lista_iter_t* iter3 = lista_iter_crear(lista3);
    print_test("Se creo el iter", iter3 != NULL);

    print_test("Se inserto al inicio", lista_insertar_primero(lista3, valor));
    print_test("Se avanzo correctamente", lista_iter_avanzar(iter3));
    print_test("Se avanzo correctamente", lista_iter_avanzar(iter3));
    print_test("Se inserta en el final", lista_iter_insertar(iter3, valor2));
    print_test("El ultimo es valor2", lista_ver_ultimo(lista3) == valor2);
    print_test("El primero es valor", lista_ver_primero(lista3) == valor);
    print_test("El actual es valor2", lista_iter_ver_actual(iter3) == valor2);

    lista_destruir(lista3, NULL);
    print_test("La lista se destruyo", true);

    lista_iter_destruir(iter3);
    print_test("El iter se destruyo", true);

}

static void pruebas_borrar_iter_externo(void){
    printf("\nINICIO DE PRUEBAS BORRAR\n");

    lista_t* lista = lista_crear();
    print_test("Se creo una lista vacia", lista != NULL);

    lista_iter_t* iter = lista_iter_crear(lista);
    print_test("Se creo el iter", iter != NULL);

    void* valor = (void*)1;
    void* valor2 = (void*)2;
    void* valor3 = (void*)3;

    lista_insertar_primero(lista, valor);

    /* Un elemento */
    print_test("Avanzar es true", lista_iter_avanzar(iter));
    print_test("Borrar devuelve valor", lista_iter_borrar(iter) == valor);
    print_test("El largo es cero", lista_largo(lista) == 0);
    print_test("El primero es NULL", lista_ver_primero(lista) == NULL);
    print_test("El ultimo es NULL", lista_ver_ultimo(lista) == NULL);

    lista_destruir(lista, NULL);
    print_test("La lista se destruyo", true);

    lista_iter_destruir(iter);
    print_test("El iter se destruyo", true);


    /* Dos elementos */
    lista_t* lista2 = lista_crear();
    print_test("Se creo una lista2 vacia", lista2 != NULL);

    lista_iter_t* iter2 = lista_iter_crear(lista2);
    print_test("Se creo el iter2", iter2 != NULL);

    lista_insertar_primero(lista2, valor2);
    lista_insertar_primero(lista2, valor);
    lista_iter_avanzar(iter2);

    print_test("Borrar devuelve valor", lista_iter_borrar(iter2) == valor);
    print_test("El primero y el ultimo es valor2", lista_ver_primero(lista2) == valor2 && lista_ver_ultimo(lista2) == valor2);
    print_test("El actual es valor2", lista_iter_ver_actual(iter2) == valor2);

    lista_destruir(lista2, NULL);
    print_test("La lista se destruyo", true);

    lista_iter_destruir(iter2);
    print_test("El iter se destruyo", true);

    /* Borrar el del medio */
    lista_t* lista3 = lista_crear();
    print_test("Se creo una lista vacia", lista3 != NULL);

    lista_iter_t* iter3 = lista_iter_crear(lista3);
    print_test("Se creo el iter", iter3 != NULL);

    lista_insertar_primero(lista3, valor3);
    lista_insertar_primero(lista3, valor2);
    lista_insertar_primero(lista3, valor);
    lista_iter_avanzar(iter3);
    lista_iter_avanzar(iter3);

    print_test("Borrar devuelve valor2", lista_iter_borrar(iter3) == valor2);
    print_test("El largo es dos", lista_largo(lista3) == 2);
    print_test("El ultimo es valor3", lista_ver_ultimo(lista3) == valor3);
    print_test("El primero es valor", lista_ver_primero(lista3) == valor);


    lista_destruir(lista3, NULL);
    print_test("La lista3 se destruyo", true);

    lista_iter_destruir(iter3);
    print_test("El iter3 se destruyo", true);
}


void pruebas_lista_estudiante() {
    prueba_lista_vacia();
    pruebas_con_algunos_elementos();
    int volumen = 10000;
    pruebas_volumen(volumen);
    pruebas_destruir();
    pruebas_iter_interno();
    pruebas_basicas_iter_externo();
    pruebas_insertar_iter_externo();
    pruebas_borrar_iter_externo();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_lista_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
