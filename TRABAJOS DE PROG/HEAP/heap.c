#include "heap.h"
#include <stdlib.h>
#include <stdbool.h>

#include "stdio.h"

#define CAP_MIN 100

typedef struct heap {
  void** arreglo;
  cmp_func_t cmp;
  size_t cant;
  size_t cap;
  
} heap_t;
  

heap_t *heap_crear(cmp_func_t cmp){
  
  heap_t* heap = malloc(sizeof(heap_t));
  if(!heap) return NULL;

  heap->arreglo = calloc(CAP_MIN, sizeof(void*));
  if(!heap->arreglo) return NULL;

  heap->cant = 0;
  heap->cap = CAP_MIN;
  heap->cmp = cmp;

  return heap;
}

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
  if(destruir_elemento){
    for(size_t i = 0; i < heap->cap; i++){
      destruir_elemento((heap->arreglo)[i]);
    }
  }
  
  free(heap->arreglo);
  free(heap);
}

size_t heap_cantidad(const heap_t *heap){
  return heap->cant;
}

bool heap_esta_vacio(const heap_t *heap){
  return heap->cant == 0;
}

void swap(void **x, void **y) {
    void* aux = *x;
    *x = *y;
    *y = aux;
}

void upheap(heap_t* heap, size_t pos) {
  if (pos == 0) return;

  size_t pos_padre = (pos - 1) / 2;

  if (heap->cmp(heap->arreglo[pos], heap->arreglo[pos_padre]) > 0) {
    swap(&heap->arreglo[pos], &heap->arreglo[pos_padre]);

    upheap(heap, pos_padre);
  }
}

void downheap(heap_t* heap, size_t pos){
  if (!(heap->arreglo[pos])) return;
  // Si sus hijos no estaria en el arreglo
  if (2 * pos + 1 >= heap->cap) return;
  if (!heap->arreglo[2 * pos + 1]) return;
  // Busco el mayor de los hijos y me guardo su posicion
  size_t pos_mayor;
  // Si el hijo derecho no esta pero el izquierdo si
  if (2 * pos + 2 >= heap->cap) {
    pos_mayor = 2 * pos + 1;
    if (!heap->arreglo[pos_mayor]) return;
  }
  // Ambos hijos estan

  else {
    if (!heap->arreglo[2 *pos + 2]) pos_mayor = 2 * pos + 1;
    else if (heap->cmp(heap->arreglo[2 * pos + 1], heap->arreglo[2 * pos + 2]) >= 0) {
      pos_mayor = 2 * pos + 1; 
      
    } else {
      pos_mayor = 2* pos + 2;
    }
  }
  if (heap->cmp(heap->arreglo[pos_mayor], heap->arreglo[pos]) > 0){
    swap(&heap->arreglo[pos_mayor], &heap->arreglo[pos]);
    downheap(heap, pos_mayor);
  }
}

bool redimensionar_heap(heap_t* heap, size_t tam_nuevo){
  if(tam_nuevo < CAP_MIN){
    tam_nuevo = CAP_MIN;
  }

  void** arreglo = realloc(heap->arreglo, sizeof(void*) * tam_nuevo);
  if(!arreglo) return false;

  for (size_t i = heap->cap; i < tam_nuevo; i++) {
    arreglo[i] = NULL;
  }

  heap->arreglo = arreglo;
  heap->cap = tam_nuevo;

  return true;
}

bool heap_encolar(heap_t *heap, void *elem){
  if(!elem) return false;

  if ((2* heap->cant + 2) >= heap->cap) {
    if(!redimensionar_heap(heap, heap->cap * 2)) return false;
  }
  heap->arreglo[heap->cant] = elem;
  upheap(heap, heap->cant);
  heap->cant++;

  return true;
  
}

void *heap_ver_max(const heap_t *heap){
  return heap->arreglo[0];
}

void *heap_desencolar(heap_t *heap){
  if (heap_esta_vacio(heap)) return NULL;

  void* valor = (heap->arreglo)[0];
  (heap->arreglo)[0] = NULL;

  swap(&((heap->arreglo)[0]), &((heap->arreglo)[heap->cant - 1]));

  downheap(heap, 0);

  heap->cant--;

  if(heap->cant < (heap->cap) / 4 && heap->cap / 2 > CAP_MIN){
    redimensionar_heap(heap, heap->cap / 2);
  }

  return valor;
}


heap_t *heap_crear_arr(void *arreglo[], size_t tam, cmp_func_t cmp){

  heap_t* heap = malloc(sizeof(heap_t));
  if (!heap) return NULL;

  // n * 2 + 2 asi garantizo que todos los hijos entran en el arreglo 
  heap->arreglo = calloc(tam * 2, sizeof(void*));
  if(!heap->arreglo) {
    free(heap);
    return NULL;
  }

  heap->cant = 0;
  heap->cap = tam * 2;
  heap->cmp = cmp;

  // Copiar el arreglo al heap
  for (size_t i = 0; i < tam; i++) {
    // Caso en que el arreglo viene con NULL
    if (arreglo[i] == NULL){
      free(heap->arreglo);
      free(heap);
      return NULL;
    }
    heap->arreglo[i] = arreglo[i];
    heap->cant++;
  }
  for (size_t t = 0; t < tam; t++) {
    downheap(heap, tam - 1- t);
  }
  return heap;
}

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){

  heap_t* heap = malloc(sizeof(heap_t));
  if (!heap) return;

  heap->arreglo = elementos;
  heap->cant = cant;
  heap->cap = cant;
  heap->cmp = cmp;

  // Ordeno en manera de heap
  for (size_t t = 0; t < cant; t++) {
    downheap(heap, cant - 1- t);
  }
  
  for (size_t t = cant; t > 1; t--) {
    swap(&elementos[0], &elementos[heap->cant-1]);
    heap->cant--;
    heap->cap--;
    downheap(heap, 0);
  }
  
  free(heap);
}
