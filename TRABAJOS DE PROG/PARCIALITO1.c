#include <stdbool.h>
#include <stddef.h>

bool lista_any(const lista_t* lista, bool (*f)(void*)){  
    nodo_lista_t* actual = lista->prim; // O(1)

    while (actual){  // O(n) con n la cantidad de elementos de la lista (eso en el peor caso que es el que importa)

        if (f(actual->dato)) return true; // Depende de f, suponiendo que f es O(1) => todo es O(1)
        
        actual = actual->prox; // O(1)
    }
    return false; // O(1)
}                                   // Por lo tanto la funcion es O(1) + O(n) + ...(todo O(1)) = O(n)

bool ingresados_mismo_orden(cola_t* cola, pila_t* pila){
    pila_t* pila_aux = pila_crear();
    if (!pila_aux) return NULL;

    cola_t* cola_aux = cola_crear();
    if(!cola_aux) return NULL; // Hasta aca todo es O(1)

    while (!pila_esta_vacia(pila)){ // La doy vuelta para comparar en el orden correcto // O(n) con n cantidad de elementos de la pila
        pila_apilar(pila_aux, pila_desapilar(pila));  // O(1)
    }
    bool estado = true; // O(1)

    while (!pila_esta_vacia(pila_aux) || !cola_esta_vacia(cola)){ // O(n) o O(k) con k la cantidad de elementos de la cola
                                                                  // Depende cual sea el mayor
        if (pila_esta_vacia(pila) || cola_esta_vacia(cola)){
            estado = false;
        }

        if (!pila_esta_vacia(pila_aux)){

            void* dato_pila = pila_desapilar(pila_aux);
            pila_apilar(pila, dato_pila);  // Dejo la pila tal como llego
        }
        else{
            void* dato_cola = cola_desencolar(cola);
            cola_encolar(cola_aux, dato_cola);
        }

        if (estado && (dato_pila != dato_cola)){ 
            estado = false;                                                            
        }                                                                              
    }                                                   // Hasta aca es todo O(1)

    while(!cola_esta_vacia(cola_aux)){ // Dejo la cola como ingreso a la funcion  // O(k)
        cola_encolar(cola, cola_desencolar(cola_aux));
    }

    return estado; // En el codigo no considero si falla el apilar o el encolar porque complicaria demasiado el ejercicio
}                  // y no me da el tiempo. Ademas no creo que el ejercicio apunte a eso :)

// Complejidad = O(n) + O(n / k) + O(k) = O(n + k) lineal.
//                    (Puede ser n o k) 

bool _arreglo_es_magico(int arr[], size_t izq, size_t der){
    size_t medio = (der + izq) / 2;

    while (izq < der){ 
        if (arr[medio] == medio){
            return true;
        }
        return _arreglo_es_magico(arr, medio + 1, der);
        return _arreglo_es_magico(arr, izq, medio - 1);
    }
    return false;
}

bool arreglo_es_magico(int arr[], size_t n) {
    return _arreglo_es_magico(arr, 0, n - 1);
}

/* Calculo de complejidad con teorema maestro */

// T(n) = 2 T(n / 2) + O(n ^ 0)  
// Con:
// A = 2
// B = 2
// C = 0

// Como logB (A) > C => T(n) = O(n ^ logB(A))