// EJERCICIO 7:
// a) Falso. Si bien para usar counting sort los datos deben ser discretos, el rango de estos debe estar acotado. En caso
// contrario probablemente tarde lo mismo que un sort comparativo.
//
// b) Falso. No es necesario. Lo que si se debe cumplir para que sea estable(Muy importante para el algoritmo) es que el
// algoritmo auxiliar sea estable(Y ademas O(n) ya que sino uso directamente otro algoritmo.). Otro factor importante 
// es que la cantidad de digitos(que es la cantidad de veces que se va a aplicar el ordenamiento auxiliar) no sea muy alta, 
// de lo contrario sera mejor usar otra algoritmo.

// c) Falso. Las busquedas siempre seran O(1) sin importar que funcion de hashing se use
// (Doy por sentado que la funcion de hashing es O(1) o no se considera). Se accede directamente a la posicion 
// devuelta por la funcion de hashing, si no esta ahi se avanza hasta una cantidad K que es el maximo de posiciones donde puede estar.

#include <stdbool.h>

// EJERCICIO 5:

bool suman_k(int arreglo[], int len, int k){ // n sera la cantidad de numeros en el arreglo.
    if(len == 0) return false;

    int max = arreglo[0];
    int min = arreglo[0];

    for(int i = 0; i < len; i++){ // Hallo max y min. O(n).
        if(arreglo[i] > max) max = arreglo[i];
        if(arreglo[i] < min) min = arreglo[i];
    }

    int rango = max - min;
    int aux[rango];

    for(int j = 0; j < rango; j++){ // Uso una especie de counting. O(n).
        aux[arreglo[j] % rango]++;
    }

    for(int l = 0; l < rango; l++){ // k - (min + l) es el numero que le falta para ser k. O(n);
        if((aux[l] > 0 && k - (min + l)) < max && (k - (min + l)) >= min && aux[(k - (min + l))] > 0){ 
            return true;
        }              
    }
    return false;
} 
// Todas las operaciones no expecificadas son O(1). 
// T(n) = O(n) + O(n) + O(n) + todos los O(1) = O(3n) = O(n);

// EJERCICIO 1:

typedef struct ab {
    struct ab* izq;
    struct ab* der;
    void* dato;
} ab_t;

void _ab_completo(const ab_t* ab, bool* estado, int* h){ 

    if((!ab->der && ab->izq) || (ab->der && !ab->izq)){
        *estado = false;
        return;
    }

    *h++;
    int h_der = 0;
    int h_izq = 0;

    if(ab->der) _ab_completo(ab->der, estado, &h_der); // Chequeo por si ambos son NULL.
    if(ab->izq) _ab_completo(ab->der, estado, &h_izq); // T(n) = 2 O(n/2), el resto es todo O(1).
                                                        // A = 2, B = 2, C = 0;  
    if(h_der != h_izq){
        *estado = false;
        return;
    }

} // Por teorema maestro: T(n) = O(n ^ logB(A)) = O(n ^ 1) = O(n).


bool ab_completo(const ab_t* ab){
    if(!ab) return true; // Caso particular.
    
    bool estado = true;
    int h = 0;
    
    _ab_completo(ab, estado, &h);
    return estado;
}