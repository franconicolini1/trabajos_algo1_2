#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "strutil.h"
#include "calc_helper.h"
#include "pila.h"


bool programa(char* arreglo[], calc_num* resultado){ 
    // Se que me quedo un poco largo, lo rehice varias veces porque tenia un error
    // que no sabia donde estaba y me quedo esto je. Si hace falta lo corrijo
    // en la reentrega.
	if (!arreglo[0]) return false; // archivo vacio.

	pilanum_t* pila_num = pilanum_crear();
	pila_t* pila_oper = pila_crear();

    calc_num valor1; // Valores que se inicializan cuando desapilo nums.
	calc_num valor2;
	calc_num valor3;

	struct calc_token token;
    bool estado = true;

	for (size_t i = 0; arreglo[i] != NULL; i++){

		if(!calc_parse(arreglo[i], &token)){
			estado = false;
            break;
		}
		if(token.type == TOK_LPAREN || token.type == TOK_RPAREN){
			estado = false;
			break;
		}
        if(token.type == TOK_NUM){
			apilar_num(pila_num, token.value);
		}
        if(token.type == TOK_OPER){
			
			if(!desapilar_num(pila_num, &valor1)){ 
                estado = false;
                break;
			}

			switch (token.oper.op){ // Creo que me empezo a gustar el switch :)

				case(OP_LOG):
					if(!desapilar_num(pila_num, &valor2)){ // Va a dar false si no hay mas numeros y si hay operadores.
						estado = false;
                        break;
					}
					if(valor2 <= 0 || valor1 < 2){
						estado = false;
                        break;
					}
					apilar_num(pila_num, log(valor2) / log(valor1));
					break;

				case(OP_RAIZ):
					if(valor1 < 0){
						estado = false;
                        break;
					}
					apilar_num(pila_num, sqrt(valor1));					
                    break;

				case(OP_TERN):
					if(!desapilar_num(pila_num, &valor2) || !desapilar_num(pila_num, &valor3)){
						estado = false;
                        break;
					}
					apilar_num(pila_num, valor3 ? valor2 : valor1);
					break;

				case(OP_ADD):
					if(!desapilar_num(pila_num, &valor2)){
						estado = false;
                        break;
					}
					apilar_num(pila_num, valor1 + valor2);
					break;

				case(OP_SUB):
					if(!desapilar_num(pila_num, &valor2)){
						estado = false;
                        break;
					}
					apilar_num(pila_num, valor2 - valor1);
					break;

				case(OP_MUL):
					if(!desapilar_num(pila_num, &valor2)){
						estado = false;
                        break;
					}
					apilar_num(pila_num, valor1 * valor2);
					break;

				case(OP_DIV):
					if(!desapilar_num(pila_num, &valor2) || valor1 == 0){
						estado = false;
                        break;
					}
					apilar_num(pila_num, floor(valor2 / valor1)); // Para que redondee para abajo.
					break;

				case(OP_POW):
					if(!desapilar_num(pila_num, &valor2) || valor1 < 0){
						estado = false;
                        break;
					}
					apilar_num(pila_num, pow(valor2, valor1));
					break;

				default:                  
                    estado = false;
                    break;
			}
	    }
    }
	desapilar_num(pila_num, (calc_num*)resultado);
	
	bool ok = desapilar_num(pila_num, &valor1); // Si quedaron numeros y no hay mas operadores dara true.
	void* ok2 = pila_desapilar(pila_oper);

	pila_destruir(pila_oper);
	pilanum_destruir(pila_num);
    
    if(ok || !estado || ok2) return false;

    return true;
}


int main(void){
	char *linea = NULL;
	size_t tam = 0;
	calc_num resultado;

	char *aux;  // Por alguna razon la funcion cambiaba la direccion de memoria de linea(O eso creo) a una que no tenia permiso 
                //de acceder lo cual generaba el problema por el que pedi ayuda. Por eso uso esta auxiliar.

	while (getline(&linea, &tam, stdin) != EOF) {
		
		aux = linea;
		char **arreglo = dc_split(aux);

		if(!programa(arreglo, &resultado)){
			fprintf(stdout,"ERROR\n");
		} 
        else fprintf(stdout,"%ld\n", resultado);
		
		free_strv(arreglo);
	}
	free(linea);
	return 0;
}