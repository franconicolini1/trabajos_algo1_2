# Aclaracion : v -> cantidad de vertices, e -> cantidad de aristas.
# EJERCICIO 1:

typedef int (*cmp_func_t)(const char*, const char*);
typedef struct heap {
    char** datos;
    size_t cantidad;
    size_t tam;
    cmp_func_t cmp;
} heap_t;

heap_t* heap_union(const heap_t* h1, const heap_t* h2, cmp_funct_t nueva_cmp){ # n = cantidad de h1, m = cantidad de h2.
    heap_t* heap = heap_crear(nueva_cmp);
    if (!heap) return NULL;

    char** arreglo = malloc(sizeof(char*) * (h1->cantidad + h2->cantidad))
    if (!arreglo){
        free(heap);
        return NULL;
    }
    hash_t* hash = hash_crear(NULL);
    if (!hash){
        free(heap);
        free(arreglo);
        return NULL;
    }

    for (size_t i = 0; i < h1->cantidad; i++){ # O(n)
        arreglo[i] = h1->datos[i];
        hash_guardar(hash, *(h1->datos[i]), h1->datos[i]); # Supongo que se puede guardar la cadena y no su puntero.
    }
    for (size_t j = 0; j < h2->cantidad; j++){ # O(m)
        if (hash_pertenece(hash, *(h2->datos[j]))) continue;
        arreglo[j + h1->cantidad] = h2->datos[j];
    }

    heap->cmp = nueva_cmp;
    heapify(arreglo, nueva_cmp); # O(n + m)
    heap->datos = arreglo;
    heap->tam = h1->cantidad + h2->cantidad;
    heap->cantidad= h1->cantidad + h2->cantidad - hash_cantidad(hash);
    hash_destruir(hash);

    return heap;
}
# Todo lo no aclarado es O(1)
# Complejidad = O(n) + O(m) + O(n + m) = O(2(n+m)) = O(n+m)

# EJERCICIO 6:

def calcular_sumatoria_grados(grafo):
    dic = {}
    
    for vertice in grafo.obtener_vertices(): # inicializo los vertices. O(v)
        dic[vertice] = 0

    for vertice in grafo.obtener_vertices(): # calculo su grado. O(v*e)
        for ady in grafo.adyacentes(vertice):
            dic[vertice] += 1

    resultado = 0

    for vertice in dic: # O(v)
        resultado += dic[vertice]

    return resultado

# Complejidad = O(v) + O(v*e) + O(v) = O(2v + v*e) = O(v(2+e)) = O(v*e)
    

# EJERCICIO 9:
#
# Primero hay que resaltar que sera un grafo dirigido. Lo primero que haria seria armar una set con
# todos los grupos debilmente conexos(que estarian en una lista). Luego me armo otro set que tenga los diferentes ciclos
# (sin repetir).
# Luego digo que cada ciclo va a ser un grupo que nunca se denunciaria entre si y ademas tampoco lo va a denunciar (Porque nunca
# se pasaron informacion) alguien que no este en su grupo debilmente conexo. Entonces cada grupo quedaria formado por
# el ciclo + las personas que no esten en su grupo debilmente conexo. Luego hay que chequear si hay elementos en el grupo
# debilmente conexo que no esten en algun ciclo y formaran otro grupo con los de los demas grupos debilmente conexos.
# El ejemplo esta en la foto :)
# El vertice c cumple que esta en un grupo debilmente conexo pero no esta en ningun ciclo, por eso conforma un grupo con e.
# 
# Complejidad:

# debilmente conexos -> O(v*(v+e)) Recorre todos los vertices aplicando un recorrido en cada uno.  
# ciclos -> O(v*(v+e)) Porque seria aplicar algun recorrido a cada vertice para ver si forma algun ciclo.
# chequeo -> O(v**2) Revisa todos los vertices del debilmente conexo y para cada uno si pertenece a un ciclo.
# total -> 2 O(v*(v+e)) + O(v**2) = O(v**2 + ve + v**2) = O(v**2 + ve)