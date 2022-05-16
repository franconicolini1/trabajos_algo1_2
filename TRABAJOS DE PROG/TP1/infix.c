#define _POSIX_C_SOURCE 200809L
#include "pila.h"
#include "cola.h"
#include "calc_helper.h"
#include "strutil.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool conversor(char** arreglo){
    cola_t *cola = cola_crear();
    if(!cola) return false;

    pila_t *pila = pila_crear();
    if(!pila) return false;

    bool flag = true; // Si algo falla, indica que se destruyan los TDA auxiliares.

    for(size_t i = 0; arreglo[i] != NULL; i++){
        
        struct calc_token token;
        struct calc_token token2;
        
        bool estado1 = calc_parse(arreglo[i], &token);
        if(!estado1){
            flag = false;
            break;
        }
        
        if(token.type == TOK_NUM){
            cola_encolar(cola, arreglo[i]);
        }
        if(token.type == TOK_OPER && !pila_esta_vacia(pila)){
            bool estado2 = calc_parse(pila_ver_tope(pila), &token2);    
            if(!estado2){
                flag = false;
                break;
            }         

            while((token2.type != TOK_LPAREN) && 
                ((token.oper.aso_izq && token.oper.precedencia <= token2.oper.precedencia) || 
                (!token.oper.aso_izq && token.oper.precedencia < token2.oper.precedencia))){

                cola_encolar(cola, pila_desapilar(pila));

                if(pila_esta_vacia(pila)) break;
                
                bool estado3 = calc_parse(pila_ver_tope(pila), &token2);    
                if(!estado3){
                    flag = false;
                    break;
                }         
            }
            pila_apilar(pila, arreglo[i]);
        }
        else if((token.type == TOK_OPER && pila_esta_vacia(pila))){
            pila_apilar(pila, arreglo[i]);
        }

        else if(token.type == TOK_LPAREN){
            pila_apilar(pila, arreglo[i]);
        }
        
        else if(token.type == TOK_RPAREN){

            bool estado5 = calc_parse(pila_ver_tope(pila), &token2);    
            if(!estado5){
                flag = false;
                break;
            }

            while(token2.type != TOK_LPAREN && !pila_esta_vacia(pila)){
                cola_encolar(cola, pila_desapilar(pila));

                if(pila_esta_vacia(pila)) break;

                bool estado_aux2 = calc_parse(pila_ver_tope(pila), &token2);    
                if(!estado_aux2){
                    flag = false;
                    break;
                }         
            }
            pila_desapilar(pila);
        }
    }
    if(!flag){
        pila_destruir(pila);
        cola_destruir(cola, NULL);
        return false;
    }

    struct calc_token token_aux;

    while(!pila_esta_vacia(pila)){

        bool estado_aux = calc_parse(pila_ver_tope(pila), &token_aux);    
        
        if(!estado_aux || token_aux.type == TOK_LPAREN || token_aux.type == TOK_RPAREN){

            pila_destruir(pila);
            cola_destruir(cola, NULL);

            return false;
        }

        cola_encolar(cola, pila_desapilar(pila));
    }

    while(!cola_esta_vacia(cola)){
        fprintf(stdout, "%s ",(char*)cola_desencolar(cola));
    }
    fprintf(stdout, "\n");

    pila_destruir(pila);
    cola_destruir(cola, NULL);

    return true;
}

bool programa(){
    size_t tam = 0;
    char *linea = NULL;
    char *aux;
    
    while(getline(&linea, &tam, stdin) != EOF){
        aux = linea;
        char **arreglo = infix_split(aux);
        conversor(arreglo);
        
        free_strv(arreglo);
    }
    
    free(linea);
    return true;
}


int main(void){
    programa();
    return 0;
}