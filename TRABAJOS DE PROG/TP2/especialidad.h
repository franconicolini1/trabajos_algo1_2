#ifndef ESPECIALIDAD_H
#define ESPECIALIDAD_H

#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La especialidad está planteado como un especialidad de punteros genéricos. */

struct especialidad;
typedef struct especialidad especialidad_t;
typedef struct doctor doctor_t;
typedef struct paciente paciente_t;
typedef int (*cmp_func_t)(const void *a, const void *b);

/* ******************************************************************
 *                    PRIMITIVAS DEL PACIENTE
 * *****************************************************************/
// Crea un struct paciente
// Pre: Se pasa un nombre y un anio mayor a 0
// Post: un paciente es creado
paciente_t* paciente_crear(char* nombre, size_t anio);

// Devuelve el nombre del paciente
// Devuelve una copia del nombre en memoria estatica
// Pre: el paciente fue creado
// Post: Devuelve una copia del nombre del paciente
char* paciente_obtener_nombre(paciente_t* paciente);

// Destruye el paciente y la memoria asociada a el
// Pre: El paciente fue creado
// Post: Se libera la memoria usada por el paciente
void paciente_destruir(paciente_t* paciente);

/* ******************************************************************
 *                    PRIMITIVAS DEL DOCTOR
 * *****************************************************************/
// Crea un struct doctor
// Pre: Se pasa un nombre y una especialdidad ya creada
// Post: Devuelve un doctor
doctor_t* doctor_crear(char* nombre, especialidad_t* especialidad);

// Destruye el struct doctor y libera la memoria asociada
// Pre: El doctor fue creado
// Post: La memoria es liberada
void doctor_destruir(doctor_t* doctor);

// Devuelve la cantidad de pacientes que fueron atendidos por el doctor
// Pre: El doctor fue creado
// Post: Devuelve la cantidad de pacientes atendidos
size_t doctor_pacientes_atendidos(doctor_t* doctor);

// Devuelve un puntero al tda especialidad al que pertenece el doctor
// Pre: El doctor fue creado
// Post: Devuelve un puntero a la especialidad pasada por parametro en el doctor crear
especialidad_t* doctor_especialidad(doctor_t* doctor);

// Atiende a un paciente de la especialidad del doctor 
// Pre: El doctor fue creado
// Post: Devuelve el struct paciente atendido o en caso de que no haya nadie
// para atender, devuelve NULL
paciente_t* doctor_atender_paciente(doctor_t* doctor);

/* ******************************************************************
 *                    PRIMITIVAS DE ESPECIALIDAD
 * *****************************************************************/

// Crea una especialidad.
// Post: devuelve una nueva especialidad vacío.
especialidad_t *especialidad_crear(char* nombre);

// Destruye la especialidad. 
// Pre: la especialidad fue creado.
// Post: se eliminaron todos los elementos de la especialidad.
void especialidad_destruir(especialidad_t *especialidad);

// Devuelve una copia en memoria estatica del nombre de la especialidad
// Pre: La especialidad fue creada
// Post: Devuelve el nombre de la especialidad
char* especialidad_obtener_nombre(especialidad_t* especialidad);

// Devuelve verdadero si la especialidad tiene elementos encolados, false en caso contrario.
// Pre: la especialidad fue creado.
bool especialidad_tiene_turnos(const especialidad_t *especialidad);

// Agrega un nuevo elemento a la especialidad. Devuelve falso en caso de error.
// Pre: la especialidad fue creado.
// Post: se agregó un nuevo elemento a la especialidad, valor se encuentra al final
// de la especialidad.
bool especialidad_pedir_turno(especialidad_t *especialidad, paciente_t* paciente, bool es_urgente);

// Saca el primer elemento de la especialidad. Si la especialidad tiene elementos, se quita el
// primero de la especialidad, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la especialidad fue creado.
// Post: se devolvió el valor del primer elemento anterior, la especialidad
// contiene un elemento menos, si la especialidad no estaba vacío.
// Devuelve NULL si no hay pacientes.
paciente_t *especialidad_atender(especialidad_t *especialidad);

// Pre: La especialidad fue creado.
// Post: Devuelve la cantidad de pacientes de la especialidad.
size_t especialidad_cantidad_pacientes(const especialidad_t* especialidad);


/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

void pruebas_especialidad_estudiante(void);

#endif  // especialidad_H
