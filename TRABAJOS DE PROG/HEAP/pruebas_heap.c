#include "heap.h"
#include "testing.h"
#include "pruebas_heap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcmp_wrapper(const void* a, const void* b) {
  return strcmp((char*) a, (char*) b);
}

static void pruebas_heap_vacio(void){
  printf("\n\nINICIO DE PRUEBAS HEAP VACIO\n");

  heap_t* heap = heap_crear(strcmp_wrapper);

  print_test("Se creo el heap", heap);
  print_test("La cantidad es cero", heap_cantidad(heap) == 0);
  print_test("Obtener algo que no esta devuelve NULL", !heap_desencolar(heap));
  print_test("Esta vacio", heap_esta_vacio(heap));
  print_test("Pertenece es false", !heap_ver_max(heap));

  heap_destruir(heap, NULL);
  print_test("Se destruyo el heap", true);

}

static void pruebas_heap_crear_arr(void) {
  printf("\n\nINICIO DE PRUEBAS DE HEAP CREAR ARR\n");

  void *valor1 = "guau";
  void *valor2 = "miau";
  void *valor3 = "mu";

  void* arreglo[] = {valor1, valor2, valor3};

  heap_t* heap = heap_crear_arr(arreglo, 3, strcmp_wrapper);

  print_test("El arreglo original no fue modificado", arreglo[0] == valor1 && arreglo[1] == valor2 && arreglo[2] == valor3);

  print_test("El maximo del heap es el correcto", heap_ver_max(heap) == valor3);
  print_test("Se desencola el elemento correcto", heap_desencolar(heap) == valor3);

  // Agregar pruebas

  void* valor4 = "a";
  void* valor5 = "b";
  void* valor6 = "c";
  void* valor7 = "d";
  void* valor8 = "e";
  void* valor9 = "f";
  void* valor10 = "g";

  void* arreglo2[] = {valor4, valor5, valor6, valor7, valor8, valor9, valor10};  

  heap_t* heap2 = heap_crear_arr(arreglo2, 7, strcmp_wrapper);

  print_test("El maximo es el correcto", heap_ver_max(heap2) == valor10);
  print_test("La cantidad es la correcta", heap_cantidad(heap2) == 7);
  print_test("Se desencola el maximo", heap_desencolar(heap2) == valor10);
  print_test("El nuevo maximo es el correcto", heap_ver_max(heap2) == valor9);
  print_test("Se desencola correctamente", heap_desencolar(heap2) == valor9);
  print_test("El siguiente que se desencola es el correcto", heap_desencolar(heap2) == valor8);
  
  bool ok = heap_desencolar(heap2) == valor7 && heap_desencolar(heap2) == valor6;

  print_test("Los proximos 2 son los correctos", ok);

  ok = heap_desencolar(heap2) == valor5 && heap_desencolar(heap2) == valor4;

  print_test("Los proximos 2 son los correctos", ok);
  print_test("El heap esta vacio", heap_esta_vacio(heap2));

  heap_destruir(heap2, NULL);
  heap_destruir(heap, NULL);
}

static void pruebas_heap_encolar_desencolar(void){
  printf("\n\nINICIO DE PRUEBAS HEAP ENCOLAR Y DESENCOLAR\n");

    heap_t* heap = heap_crear(strcmp_wrapper);

    void *valor1 = "guau";
    void *valor2 = "miau";
    void *valor3 = "mu"; 

    print_test("Encolar NULL devuelve false", !heap_encolar(heap, NULL));

    /* Pruebo upheap */
    print_test("Encolar valor3", heap_encolar(heap, valor3));
    print_test("Encolar valor2", heap_encolar(heap, valor2));
    print_test("Encolar valor1", heap_encolar(heap, valor1));
    print_test("Desencolar es valor3", heap_desencolar(heap) == valor3);
    print_test("Desencolar es valor2", heap_desencolar(heap) == valor2);
    print_test("Desencolar es valor1", heap_desencolar(heap) == valor1);

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba heap insertar valor1", heap_encolar(heap, valor1));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver max es valor1", heap_ver_max(heap) == valor1);
    print_test("Prueba heap no esta vacio", !heap_esta_vacio(heap));
    print_test("Prueba heap desencolar valor1, es valor1", heap_desencolar(heap) == valor1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);

    /* Inserta otros 2 valores y no los borra (se destruyen con el heap) */
    heap_t* heap2 = heap_crear(strcmp_wrapper);

    print_test("Prueba heap encolar valor2", heap_encolar(heap2, valor2));
    print_test("Prueba heap2 la cantidad de elementos es 1", heap_cantidad(heap2) == 1);
    print_test("Prueba heap2 encolar valor3", heap_encolar(heap2, valor3));
    print_test("Prueba heap2 la cantidad de elementos es 2", heap_cantidad(heap2) == 2);
    print_test("Prueba heap2 ver max es valor3", heap_ver_max(heap2) == valor3);
    print_test("Prueba heap2 desencolar es valor3", heap_desencolar(heap2) == valor3);
    print_test("Prueba heap2 ver max valor2, es true", heap_ver_max(heap2) == valor2);
    print_test("La cantidad es 1", heap_cantidad(heap2) == 1);
    print_test("El heap2 no esta vacio", !heap_esta_vacio(heap2));
    print_test("Desencolar devuelve valor2", heap_desencolar(heap2) == valor2);
    print_test("Desencolar devuelve NULL", heap_desencolar(heap2) == NULL);

    heap_destruir(heap2, NULL);
  
}

int numcmp(const void* a,const void* b) {

  int num1 = *((int*)a);
  int num2 = *((int*)b);

  if (num1 > num2) return 1;
      
  else if (num1 == num2) return 0;
      
  else return -1;
      
} 

static void pruebas_heap_sort(void){
  printf("\n\nINICIO DE PRUEBAS HEAPSORT\n");

  int valor1 = 1;
  int valor2 = 2;
  int valor3 = 3;
  int valor4 = 4;


  void *arreglo[] = {&valor3, &valor2, &valor1, &valor4};

  heap_sort(arreglo, 4, numcmp);

  print_test("Esta ordenado", arreglo[0] == &valor1 && arreglo[1] == &valor2 && arreglo[2] == &valor3 && arreglo[3] == &valor4);
  print_test("No esta vacio", arreglo[0] != NULL);

  void* arreglo2[] = {NULL};

  heap_sort(arreglo2, 1, strcmp_wrapper);

  print_test("Esta vacio", arreglo2[0] == NULL);

}

static void pruebas_heap_destruir(void){
  printf("\n\nINICIO DE PRUEBAS HEAP DESTRUIR\n");

  heap_t* heap1 = heap_crear(strcmp_wrapper);
  heap_t* heap2 = heap_crear(strcmp_wrapper);

  void *valor1 = "guau"; 
  void *valor2 = "miau";  
  void *valor3 = "mu";

  /* Pruebo destruir con elementos adentro */ 
  heap_encolar(heap1, valor1);
  heap_encolar(heap1, valor2);
  heap_encolar(heap1, valor3);

  heap_destruir(heap1, NULL);
  print_test("Se destruyo con elementos", true);

  /* Pide memoria para 4 valores */
  char *valor1a = strdup("hola");
  char *valor1b = strdup("hoa");
  char *valor2a = strdup("como");
  char *valor2b = strdup("esta");

  heap_encolar(heap2, valor1a);
  heap_encolar(heap2, valor2a);
  heap_encolar(heap2, valor1b);
  heap_encolar(heap2, valor2b);

  heap_destruir(heap2, free);
  print_test("Se destruyo con free", true);
}

static void pruebas_heap_volumen(size_t volumen){

  printf("\n\nPRUEBAS DE HEAP VOLUMEN\n");

  int* arreglo = malloc(sizeof(int) * volumen);
  heap_t* heap = heap_crear(numcmp);

  bool ok = true;

  for (unsigned int i = 0; i < volumen; i++) {
    arreglo[i] = i;
    ok = heap_encolar(heap, &arreglo[i]);
    if (!ok) break;
    // Como siempre encolo numeros mas grandes deberia ser siempre el max
    ok = (heap_ver_max(heap) == &arreglo[i]);
    if (!ok) break;
  }
  print_test("Se encolaron todos los elementos correctamente", ok);
  print_test("El elemento maximo es el correcto", heap_ver_max(heap) == &arreglo[volumen - 1]);
  print_test("La cantidad es la correcta", heap_cantidad(heap) == volumen);

  for (unsigned int i = 0; i < volumen; i++) {
    ok = (heap_desencolar(heap) == &arreglo[volumen - i - 1]);
    if (!ok) break;
  }
  print_test("Se desencolaron todos los elementos en el orden correcto", ok);
  print_test("El heap esta vacio", heap_esta_vacio(heap));

  free(arreglo);
  heap_destruir(heap, NULL);
}


void pruebas_heap_estudiante(void) {

  pruebas_heap_vacio();
  pruebas_heap_crear_arr();
  pruebas_heap_encolar_desencolar();
  pruebas_heap_destruir();
  pruebas_heap_volumen(50000);
  pruebas_heap_sort();
  
}
