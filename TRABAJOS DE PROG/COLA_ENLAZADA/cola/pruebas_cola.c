#include "cola.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>


static void prueba_cola_vacia(void) {
    printf("INICIO DE PRUEBAS CON COLA VACIA\n");

    cola_t* cola = cola_crear();

    print_test("Se creo la cola vacia", cola != NULL);

    /*Pruebo operaciones con una cola vacia*/
    print_test("Desencolar vacia", cola_desencolar(cola) == NULL);
    print_test("Esta vacia", cola_esta_vacia(cola));
    print_test("Ver el primero es NULL", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
    print_test("La cola fue destruida", true); 

}

static void pruebas_con_algunos_elementos(void){
    printf("INICIO DE PRUEBAS CON ALGUNOS ELEMENTOS\n");

    cola_t *cola = cola_crear();
    void *valor = (void*) 53;
    void *cadena = "hola";

    cola_encolar(cola, valor);
    cola_encolar(cola, cadena);

    print_test("El tope es hola", cola_ver_primero(cola) == valor);
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));

    /*Pruebas con desencolar*/
    print_test("Desencolar devuelve 53", cola_desencolar(cola) == valor);
    print_test("La cola no esta vacia", !cola_esta_vacia(cola));
    print_test("El tope es hola", cola_ver_primero(cola) == cadena);

    print_test("Desencolar devuelve hola", cola_desencolar(cola) == cadena);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("Desencolar devuelve NULL", cola_desencolar(cola) == NULL);
    print_test("Ver el primero es NULL", cola_ver_primero(cola) == NULL);

    cola_destruir(cola, NULL);
    print_test("La cola fue destruida", true);


    /* Pruebas con NULL*/
    cola_t* cola2 = cola_crear();
    cola_encolar(cola2, NULL);

    print_test("La cola no esta vacia", !cola_esta_vacia(cola2));
    print_test("El primero es NULL", cola_ver_primero(cola2) == NULL);
    print_test("Desencolar devuelve NULL", cola_desencolar(cola2) == NULL);
    print_test("La cola esta vacia", cola_esta_vacia(cola2));

    cola_destruir(cola2, NULL);
    print_test("La cola fue destruida", true); 
}

static void pruebas_volumen(int volumen){
    printf("INICIO PRUEBAS DE VOLUMEN\n");

    cola_t* cola = cola_crear();

    /*Creo arreglo de 10000 elementos*/
    int arreglo[volumen];

    /*Encolo 10000 elementos, estado sera false si fallo algo*/

    bool estado = true;

    for (int i = 0; i < volumen; i++){
        arreglo[i] = i;
        estado = cola_encolar(cola, &arreglo[i]);
        if (!estado){
            break;
        }
    }
    print_test("Se encolaron 10000 elementos", estado);

    /*Verifico que al desencolar desencole correctamente*/
    for (int j = 0; j < volumen; j++){
        void *aux = cola_desencolar(cola);
        if(aux != &arreglo[j]){
            estado = false;
            break;
        }
    }
    print_test("Elementos desencolados correctamente", estado);
    print_test("La cola esta vacia", cola_esta_vacia(cola));

    cola_destruir(cola, NULL);
    print_test("La cola fue destruida", true);
}

void destruir_cola_en_cola(void* dato){
    /* Destruye una cola dentro de una cola, usando sus primitiva */
       cola_destruir(dato, NULL);
    }

static void pruebas_destruir(void){ /* Ya fue probado pasandole NULL */

    printf("INICIO DE PRUEBAS DESTRUIR\n");

    /* Destruir pasandole free() */

    cola_t* cola = cola_crear();
    for (int j = 0; j < 3; j++){
        int* aux = malloc(sizeof(int));
        cola_encolar(cola, aux);
    }

    cola_destruir(cola, free);
    print_test("La cola fue destruida con free", true);

    /* Pruebas con una funcion que destruye colas encoladas */

    cola_t* cola2 = cola_crear();

    for (int j = 0; j < 3; j++){
        cola_t* aux = cola_crear();
        cola_encolar(cola2, aux);
    }

    cola_destruir(cola2, destruir_cola_en_cola);
    print_test("La cola con colas fue destruida", true);

}

void pruebas_cola_estudiante() {
    prueba_cola_vacia();
    pruebas_con_algunos_elementos();
    int volumen = 10000;
    pruebas_volumen(volumen);
    pruebas_destruir();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
