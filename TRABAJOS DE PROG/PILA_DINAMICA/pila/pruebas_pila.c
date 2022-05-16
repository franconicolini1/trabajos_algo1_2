#include "pila.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


static void prueba_pila_vacia(void) {
    printf("INICIO DE PRUEBAS CON PILA VACIA\n");

    pila_t *pila = pila_crear();

    print_test("Se creo la pila vacia", pila != NULL);

    /*Pruebo operaciones con una pila vacia*/
    print_test("Desapilar vacia", pila_desapilar(pila) == NULL);
    print_test("Esta vacia", pila_esta_vacia(pila));
    print_test("Ver el tope es NULL", pila_ver_tope(pila) == NULL);

    pila_destruir(pila);
    print_test("La pila fue destruida", true); 

}

static void pruebas_con_algunos_elementos(void){
    printf("INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");

    pila_t *pila = pila_crear();
    void *valor = (void*) 12555;
    void *cadena = "prueba";

    pila_apilar(pila, valor);
    pila_apilar(pila, cadena);

    print_test("El tope es prueba", pila_ver_tope(pila) == cadena);
    print_test("La pila no esta vacia", !pila_esta_vacia(pila));

    /*Pruebas con desapilar*/
    print_test("Desapilar devuelve prueba", pila_desapilar(pila) == cadena);
    print_test("La pila no esta vacia", !pila_esta_vacia(pila));
    print_test("El tope es 2", pila_ver_tope(pila) == valor);

    print_test("Desapilar devuelve 2", pila_desapilar(pila) == valor);
    print_test("La pila esta vacia", pila_esta_vacia(pila));
    print_test("Desapilar devuelve NULL", pila_desapilar(pila) == NULL);
    print_test("Ver el tope es NULL", pila_ver_tope(pila) == NULL);

    pila_destruir(pila);
    print_test("La pila fue destruida", true);


    /* Pruebas con NULL*/
    pila_t *pila2 = pila_crear();
    pila_apilar(pila2, NULL);

    print_test("La pila no esta vacia", !pila_esta_vacia(pila2));
    print_test("El tope es NULL", pila_ver_tope(pila2) == NULL);
    print_test("Desapilar devuelve NULL", pila_desapilar(pila2) == NULL);
    print_test("La pila esta vacia", pila_esta_vacia(pila2));

    pila_destruir(pila2);
    print_test("La pila fue destruida", true); 
}

static void pruebas_volumen(int volumen){
    printf("INICIO PRUEBAS DE VOLUMEN");

    pila_t *pila = pila_crear();

    /*Creo arreglo de 10000 elementos*/
    int *arreglo = malloc(sizeof(int) * volumen);
    int **arreglo_punteros = malloc(sizeof(int*) * volumen);

    /*Apilo 10000 elementos, estado sera false si fallo algo*/

    bool estado = true;

    for (int i = 0; i < volumen; i++){
        arreglo_punteros[i] = &i;
        arreglo[i] = i;
        estado = pila_apilar(pila, arreglo_punteros[i]);
        if (!estado){
            break;
        }
    }
    print_test("Se apilaron 10000 elementos", estado);

    /*Verifico que al desapilar desapile correctamente*/
    for (int j = volumen - 1; j > -1; j--){
        void *aux = pila_desapilar(pila);
        if(aux != arreglo_punteros[j]){
            estado = false;
            break;
        }
    }
    print_test("Elementos desapilados correctamente", estado);
    print_test("La pila esta vacia", pila_esta_vacia(pila));

    free(arreglo);
    free(arreglo_punteros);

    pila_destruir(pila);
    print_test("La pila fue destruida", true);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    pruebas_con_algunos_elementos();
    int volumen = 10000;
    pruebas_volumen(volumen);
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
