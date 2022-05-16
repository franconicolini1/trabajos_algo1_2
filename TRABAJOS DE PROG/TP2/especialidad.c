#define _POSIX_C_SOURCE 200809L
#include "especialidad.h"
#include "cola.h"
#include "heap.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*************************************************************************************
*                                   TDA DOCTOR                                       *
*************************************************************************************/

struct doctor {

  char* nombre;
  especialidad_t* especialidad;
  size_t pacientes_atendidos;

};

doctor_t* doctor_crear(char* nombre, especialidad_t* especialidad){
  doctor_t* doctor = malloc(sizeof(doctor_t));
  if (!doctor) return NULL;

  doctor->nombre = strdup(nombre);
  doctor->especialidad = especialidad;
  doctor->pacientes_atendidos = 0;

  return doctor;
}

especialidad_t* doctor_especialidad(doctor_t* doctor){
  if (!doctor) return NULL;
  return doctor->especialidad;
}

void doctor_destruir(doctor_t* doctor){
  if (!doctor) return;
  free(doctor->nombre);
  free(doctor);
}

size_t doctor_pacientes_atendidos(doctor_t* doctor){
  return doctor->pacientes_atendidos;
}

paciente_t* doctor_atender_paciente(doctor_t* doctor) {
  if (!doctor) return NULL;
  paciente_t* paciente = especialidad_atender(doctor->especialidad);

  if (!paciente) return NULL;
  doctor->pacientes_atendidos++;

  return paciente;
}



/*************************************************************************************
*                                   TDA PACIENTE                                     *
*************************************************************************************/ 

struct paciente {
  char* nombre;
  size_t anio;
};

paciente_t* paciente_crear(char* nombre, size_t anio) {
  paciente_t* paciente = malloc(sizeof(paciente_t));
  if (!paciente) return NULL;

  paciente->nombre = strdup(nombre);
  paciente->anio = anio;

  return paciente;
}

char* paciente_obtener_nombre(paciente_t* paciente) {
  return paciente->nombre;
}

void paciente_destruir(paciente_t* paciente) {
  free(paciente->nombre);
  free(paciente);
}
 
/*************************************************************************************
*                                 TDA ESPECIALIDAD                                   *
*************************************************************************************/ 

struct especialidad{
  char* nombre;

  cola_t* urgencia;
  heap_t* regular;

  size_t cant_urgencia;

};

// Para el heap de especialidad
// Hace que el menor año sea el mayor (ya que usamos un heap de mayores)
int anio_cmp(const void* a,const void* b) {
  size_t aux_1 = ((paciente_t*)a)->anio;
  size_t aux_2 = ((paciente_t*)b)->anio;

  int resultado = 0;

  if (aux_1 > aux_2) resultado = -1;
  if (aux_1 == aux_2) resultado = 0;
  if (aux_1 < aux_2) resultado = 1;
  
  return resultado;
}

especialidad_t *especialidad_crear(char* nombre) {
  especialidad_t* especialidad = malloc(sizeof(especialidad_t));
  if(!especialidad) return NULL;

  especialidad->urgencia = cola_crear();
  if(!especialidad->urgencia){
    free(especialidad);
    return NULL;
  }

  especialidad->regular = heap_crear(anio_cmp);
  if(!especialidad->regular){
    cola_destruir(especialidad->urgencia, NULL);
    free(especialidad);
    return NULL;
  }
  especialidad->nombre = strdup(nombre);
  especialidad->cant_urgencia = 0;
  
  return especialidad;
}

void especialidad_destruir(especialidad_t *especialidad) {
  cola_destruir(especialidad->urgencia, NULL);
  heap_destruir(especialidad->regular, NULL);
  free(especialidad->nombre);
  free(especialidad);
}

size_t especialidad_cantidad_pacientes(const especialidad_t* especialidad) {
  return (especialidad->cant_urgencia + heap_cantidad(especialidad->regular));
}

bool especialidad_tiene_turnos(const especialidad_t *especialidad) {
  return especialidad_cantidad_pacientes(especialidad) != 0;
}

char* especialidad_obtener_nombre(especialidad_t* especialidad) {
  return especialidad->nombre;
}

bool especialidad_pedir_turno(especialidad_t *especialidad, paciente_t* paciente, bool es_urgente) {
  bool ok = true;

  if (es_urgente) {
     ok = cola_encolar(especialidad->urgencia, paciente);
     especialidad->cant_urgencia++;
  }
  else ok = heap_encolar(especialidad->regular, paciente);
  
  return ok;
}

paciente_t *especialidad_atender(especialidad_t *especialidad) {

  if (!cola_esta_vacia(especialidad->urgencia)) {
    especialidad->cant_urgencia--;
    return cola_desencolar(especialidad->urgencia);
  }
  return heap_desencolar(especialidad->regular);

}