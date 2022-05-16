#include <stdbool.h>
#include <stdlib.h>

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

// Crea un arbol de busqueda binaria 
// Pre: cmp es una funcion que compara cadenas y con devuelve un entero <0, =0, 0<.
// tambien se debe pasar una funcion para destuir los datos pasados
// Post: se crea un abb en caso excitoso y NULL en caso fallido
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Dado un abb, una clave y un dato inserta el dato en el abb con la clave pasada
// Si se guarda con una clave ya existente se elimina el dato ya existente con la funcion destuir dato
// y es remplazada por el nuevo dato
// Pre: el abb existe 
// Post: se guarda el dato con la clave pasada y devuelve true o false en caso de error
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Elimina una clave del abb y devuelve su dato
// Devuelve NULL en caso de que la clave no pertenezca al abb
// Pre: el abb existe
// Post: Devuelve el dato asociado con la clave o NULL en caso contrario
void *abb_borrar(abb_t *arbol, const char *clave);

// Devuelve el dato asociado de la clave pasada
// En caso que no pertenezca devuelve NULL
// Pre: el abb existe
// Post: Devuelve el dato asociado con la clave o NULL en caso contrario
void *abb_obtener(const abb_t *arbol, const char *clave);

// Funcion boolena que indica si una clave pertenece al abb o no
// Pre el abb existe
// Post: Devuelve true en caso de que la clave pertenezca o false en caso contrario
bool abb_pertenece(const abb_t *arbol, const char *clave);

// Devuelve la cantidad de elementos existentes en el abb
// Pre: el abb existe
// Post: Devuelve la cantidad del elementos
size_t abb_cantidad(abb_t *arbol);

// Destruye el abb y libera toda la memoria dinamica asociada con existe
// Pre: el abb existe
// Post: Se destuye el abb y se libera la memoria
void abb_destruir(abb_t *arbol);

// Iterador interno que recore de manera inorden a el arbol
// Pre: el iterador fue creado
// Post: se le aplica la funcion visitar a todos los elementos hasta que devuelva false
// o los recorra todos.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

// Pre: El abb fue creado.
// Post: Visita las cadenas en el rango (cota_inf, cota_sup) 
// con la funcion recibida por parametro.
void abb_in_order_acotado(abb_t* arbol, bool visitar(const char *, void *, void *) , void* extra, char* cota_inf, char* cota_sup);

typedef struct abb_iter abb_iter_t;

// Crea un iterador del abb
// El iterador recorerra el arbol de forma Inorder
// Pre: El abb existe
// Post: Devuelve un iterador del abb
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

// Avanza una posicion el iterador en caso de ser posible
// Si el moviemiento es posible devuelve true o en caso contrario false
// Pre: el iterador existe
// Post: Avanza el iterador y devuelve true en caso de que sea posible o false en caso contrario
bool abb_iter_in_avanzar(abb_iter_t *iter);

// Devuelve la clave del elemento al que apunta el iterador
// Pre: el iterador existe
// Post: Devuelve una copia de la clave actual 
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

// Funcion booleana que indica si el iterador esta al final o no
// Pre: el iterador existe
// Post: Devuleve true en caso de que el iterador este al final o false en caso contrario
bool abb_iter_in_al_final(const abb_iter_t *iter);

// Destruye el iterador y libera la memoria asociada
// Pre: el iterador existe
// Post: el iterador se destruye y se libera la memoria asociada 
void abb_iter_in_destruir(abb_iter_t* iter);


