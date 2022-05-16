#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include <stdio.h>

#define UPSIZE 71
#define DOWNSIZE 20
#define FACTOR_REDIMENSION 2
#define CAP_MIN 10
#define OCUPADO 1
#define VACIO 2
#define BORRADO 3

                                    /* HASH CERRADO */

// Funcion de hashing a usar
unsigned long djb2(char *str) {

        unsigned long hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; 
        return hash;

}

typedef struct hash{
    unsigned long cap;
    unsigned long cant_total; // Ocupados + Borrados
    unsigned long cant_ocupados;

    char** claves;
    void** datos;
    int* estados;

    hash_destruir_dato_t destruir_dato;

} hash_t;

hash_t *hash_crear_ajustable(hash_destruir_dato_t destruir_dato, unsigned long size_inicial){
  
    hash_t* hash = malloc(sizeof(hash_t));
    if (!hash) return NULL;

    hash->claves = malloc(sizeof(char*) * size_inicial);
    if (!hash->claves) {
        free(hash);
        return NULL;
    }

    hash->datos = malloc(sizeof(void*) * size_inicial);
    if(!hash->datos) {
        free(hash->claves);
        free(hash);
        return NULL;
    }
    
    hash->estados = calloc(size_inicial, sizeof(int));
    if (!hash->estados) {
        free(hash->datos);
        free(hash->claves);
        free(hash);
        return NULL;
    }
    
    hash->cap = size_inicial;
    hash->cant_total = 0;
    hash->cant_ocupados = 0;

    hash->destruir_dato = destruir_dato;

    // Inicializo el todos los espacios como vacio
    for (unsigned long i = 0; i < size_inicial; i++) {
      (hash->estados)[i] = VACIO;
    }

    return hash;
}

hash_t *hash_crear(hash_destruir_dato_t destruir_dato){
    return hash_crear_ajustable(destruir_dato, CAP_MIN);
}

bool redimensionar_hash(hash_t* hash, char modo) {

  unsigned long valor = 0;

  if (modo != 'u' && modo != 'd') return false;
  
  if (modo == 'u') {
    valor = hash->cap * FACTOR_REDIMENSION;
  }
  if (modo == 'd') {
    valor = hash->cap / FACTOR_REDIMENSION;
  }
  hash_t* hash_remplazo = hash_crear_ajustable(hash->destruir_dato, valor);
  if (!hash_remplazo) return false;

  for (unsigned long i = 0; i < hash->cap; i++) {
    if ((hash->estados)[i] == OCUPADO) {
      hash_guardar(hash_remplazo, (hash->claves)[i], (hash->datos)[i]);
      free(hash->claves[i]);
    }
  }
  hash->cap = hash_remplazo->cap;
  hash->cant_total = hash_remplazo->cant_total;
  hash->cant_ocupados = hash_remplazo->cant_ocupados;

  void* aux;
  aux = hash->datos;
  hash->datos = hash_remplazo->datos;
  free(aux);

  aux = hash->claves;
  hash->claves = hash_remplazo->claves;
  free(aux);

  aux = hash->estados;
  hash->estados = hash_remplazo->estados;
  free(aux);

  free(hash_remplazo);

  return true;

}

bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
  if (((hash->cant_total * 100) / hash->cap) >= UPSIZE) {
		if (!redimensionar_hash(hash, 'u')) return false;
	}
	unsigned long pos = djb2((char*) clave) % hash->cap;
	unsigned long pos_check = pos; 

  
	while ((hash->estados)[pos] != VACIO && ((hash->estados)[pos] == BORRADO || strcmp(clave, (hash->claves)[pos]) != 0)) {
		pos++;

		if (pos >= hash->cap) {
			pos = 0;
		}
		if (pos == pos_check) {
			return false;
		}
	}
  if ((hash->estados)[pos] == VACIO) {
    (hash->claves)[pos] = strdup((char*)clave);
    hash->cant_ocupados++;
    hash->cant_total++;

  } else{
      if (hash->destruir_dato) {
        hash->destruir_dato(hash->datos[pos]);
      }
  }

  (hash->datos)[pos] = dato;
	(hash->estados)[pos] = OCUPADO;
	
	return true;
}

void *hash_borrar(hash_t *hash, const char *clave) {
  if (hash->cant_ocupados * 100 / hash->cap <= DOWNSIZE && hash->cap / FACTOR_REDIMENSION > CAP_MIN) {
    if (!redimensionar_hash(hash, 'd')) return false;
    
  }

  unsigned long pos = djb2((char*) clave) % hash->cap;
  unsigned long pos_check = pos; 

  while ((hash->estados)[pos] != VACIO && ((hash->estados)[pos] == BORRADO || strcmp(clave, (hash->claves)[pos]) != 0)) {
		pos++;

		if (pos >= hash->cap) {
			pos = 0;
		}
    if (pos == pos_check) {
			return false;
		}
	}
  if ((hash->estados)[pos] == VACIO) {
    return NULL;
  }
  
  if (strcmp(clave, (hash->claves)[pos]) == 0) {
    hash->cant_ocupados--;
    free((hash->claves)[pos]);
    (hash->estados)[pos] = BORRADO;
    return (hash->datos)[pos];
    
  } 
  
  else {
    return NULL;
  }


}

void hash_destruir(hash_t *hash){
    for (unsigned long i = 0; i < hash->cap; i++){
    
        if ((hash->estados)[i] == OCUPADO) {
          free((hash->claves)[i]);
          if (hash->destruir_dato) {
            hash->destruir_dato((hash->datos)[i]);
          }
        }
    }
    free(hash->datos);
    free(hash->claves);
    free(hash->estados);
    free(hash);
}

bool hash_pertenece(const hash_t *hash, const char *clave){
    unsigned long pos = djb2((char*)clave) % hash->cap; 
    unsigned long aux = pos;

    while((hash->estados)[pos] != VACIO){
        
        if((hash->estados)[pos] == OCUPADO && strcmp((hash->claves)[pos], clave) == 0){
            return true;
        }
        pos++;
        if (pos >= hash->cap) {
            pos = 0;
        }
        if (pos == aux) {
            return false;
        }
    }

    return false;
  
}

unsigned long hash_cantidad(const hash_t *hash){
    return hash->cant_ocupados;
}

void *hash_obtener(const hash_t *hash, const char *clave){
    unsigned long pos = djb2((char*)clave) % hash->cap;
    unsigned long aux = pos;

    while((hash->estados)[pos] != VACIO){
        
        if ((hash->estados)[pos] == OCUPADO && strcmp((hash->claves)[pos], clave) == 0){
            return (void*)((hash->datos)[pos]);
        }
        pos++;
        
        if (pos >= hash->cap) {
            pos = 0;
        }
        if (pos == aux) {
            return NULL;
        }
    }

    return NULL;

}

/* FUNCIONES DEL ITERADOR */

typedef struct hash_iter{
    const hash_t* hash;
    unsigned long pos_act;

} hash_iter_t;

hash_iter_t *hash_iter_crear(const hash_t *hash){
    hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    if(!iter) return NULL;

    iter->hash = hash;
    iter->pos_act = 0;
    while (iter->hash->estados[iter->pos_act] != OCUPADO && iter->pos_act < iter->hash->cap -1) {
      iter->pos_act++;
    }

    return iter;
}

const char *hash_iter_ver_actual(const hash_iter_t *iter){
  if (iter->hash->estados[iter->pos_act] != OCUPADO) {
    return NULL;
  }
  return iter->hash->claves[iter->pos_act];
}

bool hash_iter_al_final(const hash_iter_t *iter){
    if(iter->hash->cant_ocupados == 0) return true;

    unsigned long aux = iter->pos_act;

    while(aux < (iter->hash->cap) && (iter->hash->estados)[aux] != OCUPADO){
        aux++;
    }
    if(aux >= (iter->hash->cap)) return true;    
    return false;
}

void hash_iter_destruir(hash_iter_t *iter){
    free(iter);
}

bool hash_iter_avanzar(hash_iter_t *iter){
    while(!hash_iter_al_final(iter)){
        iter->pos_act++;
        if(hash_iter_al_final(iter)) break;
        if((iter->hash->estados)[iter->pos_act] == OCUPADO){
            return true;
        }
    }

    return false;
}

