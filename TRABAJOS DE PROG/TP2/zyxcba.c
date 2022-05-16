#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "strutil.h"
#include "mensajes.h"
#include "especialidad.h"
#include "hash.h"
#include "abb.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"
#define URGENTE "URGENTE"
#define REGULAR "REGULAR"

void eliminar_fin_linea(char* linea) {
	size_t len = strlen(linea);
  if (len == 0) return;
	if (linea[len - 1] == '\n') {
		linea[len - 1] = '\0';
	}
}

bool crear_directorio_doctores(char* nombre_archivo, hash_t* especialidades, abb_t* doctores) {

  FILE* archivo = fopen(nombre_archivo, "r");
  if (!archivo) return false;

  char* linea = NULL;
  size_t tam = 0;

  especialidad_t* especialidad;
  doctor_t* doctor;

  while (getline(&linea, &tam, archivo) != EOF) {
    eliminar_fin_linea(linea);

    char** campos = split(linea, ',');
    if (campos[1] == NULL){
      free_strv(campos); 
      continue;
    }
    if (hash_pertenece(especialidades, campos[1])) {
      especialidad = (especialidad_t*)hash_obtener(especialidades, campos[1]);
    }
    else {
      especialidad = especialidad_crear(campos[1]);
      hash_guardar(especialidades, campos[1], especialidad);
    }
    doctor = doctor_crear(campos[0], especialidad);
    abb_guardar(doctores, campos[0], doctor);

    free_strv(campos);
  }
  
  free(linea);
  fclose(archivo);
  return true;
}

bool crear_directorio_pacientes(char* nombre_archivo, hash_t* pacientes) {

  FILE* archivo = fopen(nombre_archivo, "r");
  if (!archivo) return false;

  char* linea = NULL;
  size_t tam = 0;
  size_t anio;

  while (getline(&linea, &tam, archivo) != EOF) {
    eliminar_fin_linea(linea);
    
    char** campos = split(linea, ',');
    if (campos[1] == NULL) continue;

    anio = atoi(campos[1]);
    hash_guardar(pacientes, campos[0], paciente_crear(campos[0], anio));
    free_strv(campos);
  }
  
  free(linea);
  fclose(archivo);
  return true;
}

void comando_pedir_turno(const char* comando, char** parametros, hash_t* especialidades, abb_t* doctores,
                         hash_t* pacientes, size_t cantidad_parametros){

  if (cantidad_parametros != 3) {
    printf(ENOENT_PARAMS, comando);
    return;
  }
  // Parametros: nombre_paciente, especialidad, urgencia
  bool error1 = !hash_pertenece(pacientes, parametros[0]);
  bool error2 = !hash_pertenece(especialidades, parametros[1]);
  bool error3 = strcmp(parametros[2], URGENTE) != 0 && strcmp(parametros[2], REGULAR)!= 0;

  if (error1 || error2 || error3) {
    if (error1) printf(ENOENT_PACIENTE, parametros[0]);
    if (error2) printf(ENOENT_ESPECIALIDAD, parametros[1]);
    if (error3) printf(ENOENT_URGENCIA, parametros[2]);
    return;
  }

  bool es_urgente;
  if (strcmp(URGENTE, parametros[2]) == 0) es_urgente = true;
  else es_urgente = false;

  especialidad_t* especialidad = hash_obtener(especialidades, parametros[1]);
  paciente_t* paciente = hash_obtener(pacientes, parametros[0]);
  especialidad_pedir_turno(especialidad, paciente, es_urgente); 

  printf(PACIENTE_ENCOLADO, parametros[0]);
  printf(CANTIDAD_PACIENTES_ENCOLADOS, especialidad_cantidad_pacientes(especialidad), parametros[1]);
 
  return;                   
}

void comando_atender_pacientes(const char* comando, char** parametros, hash_t* especialidades, abb_t* doctores,
                         hash_t* pacientes, size_t cantidad_parametros){

  // Parametros: Doctor
  if (!abb_pertenece(doctores, parametros[0])) {
    printf(ENOENT_DOCTOR, parametros[0]);
    return;
  }
  doctor_t* doctor = abb_obtener(doctores, parametros[0]);

  especialidad_t* especialidad = doctor_especialidad(doctor);

  if (!especialidad_tiene_turnos(especialidad)) {
    printf(SIN_PACIENTES);
    return;
  }

  paciente_t* paciente = doctor_atender_paciente(doctor);

  printf(PACIENTE_ATENDIDO, paciente_obtener_nombre(paciente));
  printf(CANTIDAD_PACIENTES_ENCOLADOS, especialidad_cantidad_pacientes(especialidad), especialidad_obtener_nombre(especialidad));


  return;
}

bool contar_en_rango(const char* nombre, void* doctor, void* extra) {
  *(size_t*)extra += 1;
  return true;
}

bool imprimir_formateado_para_informe(const char* nombre, void* doctor, void* extra) {
  //1: NOMBRE, especialidad ESPECIALIDAD, X paciente(s) atendido(s)
  especialidad_t* especialidad = doctor_especialidad(doctor);
  printf(INFORME_DOCTOR, *((size_t*) extra) + 1, nombre, especialidad_obtener_nombre(especialidad), doctor_pacientes_atendidos(doctor));
  *((size_t*) extra) += 1;

  return true;
}

void comando_informe(const char* comando, char** parametros, hash_t* especialidades, abb_t* doctores, hash_t* pacientes){

  if (!parametros[0] || !parametros[1] || parametros[2]) {
    printf(ENOENT_PARAMS, comando);
    return;
  }

  char* cota_inf = parametros[0];
  char* cota_sup = parametros[1];

  if (strcmp(cota_inf, "") == 0) *cota_inf = '\0';
  if (strcmp(cota_sup, "") == 0) cota_sup = "zzzzz";
  
  size_t cant_doctores = 0;
  abb_in_order_acotado(doctores, contar_en_rango, &cant_doctores, cota_inf, cota_sup);
  printf(DOCTORES_SISTEMA, (size_t)cant_doctores);

  if (cant_doctores != 0) {
    size_t num = 0;
    abb_in_order_acotado(doctores, imprimir_formateado_para_informe , &num, cota_inf, cota_sup);
  }
}


void procesar_comando(const char* comando, char** parametros, hash_t* especialidades, abb_t* doctores, hash_t* pacientes) {
  size_t cantidad_parametros = 0;
  for (size_t i = 0; parametros[i] != NULL; i++){
      cantidad_parametros++;
  }

	if (strcmp(comando, COMANDO_PEDIR_TURNO) == 0) {
    comando_pedir_turno(comando, parametros, especialidades, doctores, pacientes, cantidad_parametros);

	} else if (strcmp(comando, COMANDO_ATENDER) == 0) {
      comando_atender_pacientes(comando, parametros, especialidades, doctores, pacientes, cantidad_parametros);

	} else if (strcmp(comando, COMANDO_INFORME) == 0) {
      comando_informe(comando, parametros, especialidades, doctores, pacientes);
	} else {
    printf(ENOENT_CMD, comando);
	}
}

bool inicializacion(hash_t** especialidades, abb_t** doctores, hash_t** pacientes, char* doct_file, char* paci_file) {
  
  // Se crean los directorios de pacientes, doctores y especialidades
  *especialidades = hash_crear((hash_destruir_dato_t)especialidad_destruir);
  if (!especialidades) return false;

  *doctores = abb_crear(strcmp ,(abb_destruir_dato_t)doctor_destruir);
  if (!doctores) {
    hash_destruir(*especialidades);
    return false;
  }

  *pacientes = hash_crear((hash_destruir_dato_t)paciente_destruir);
  if (!pacientes) {
    hash_destruir(*especialidades);
    abb_destruir(*doctores);
    return false;
  }
  
  bool ok = true;  

  ok = crear_directorio_doctores(doct_file, *especialidades, *doctores);
  if (!ok) {
    printf(ENOENT_ARCHIVO, doct_file);
    hash_destruir(*especialidades);
    abb_destruir(*doctores);
    hash_destruir(*pacientes);
    return false;
  }

  ok = crear_directorio_pacientes(paci_file, *pacientes) && ok;
  if (!ok) {
    printf(ENOENT_ARCHIVO, paci_file);
    hash_destruir(*especialidades);
    abb_destruir(*doctores);
    hash_destruir(*pacientes);
    return false;
  }

  return true;
}

void procesar_entrada(hash_t* especialidades, abb_t* doctores, hash_t* pacientes) {
	char* linea = NULL;
	size_t tam = 0;
	while (getline(&linea, &tam, stdin) != EOF) {
		eliminar_fin_linea(linea);
		char** campos = split(linea, ':');
		if (campos[1] == NULL) {
			printf(ENOENT_FORMATO, linea);
			free_strv(campos);
			continue;	
		}
		char** parametros = split(campos[1], ',');
		procesar_comando(campos[0], parametros, especialidades, doctores, pacientes);
		free_strv(parametros);
		free_strv(campos);
	}
	free(linea);
}


int main(int argc, char** argv) {
  if (argc != 3) {
    printf(ENOENT_CANT_PARAMS);
    return 1;
  }
  // Se crean los directorios de pacientes, doctores y especialidades
  hash_t* especialidades, *pacientes;
  abb_t* doctores;
  if (!inicializacion(&especialidades, &doctores, &pacientes, argv[1], argv[2])) return 1; // Falla fopen o hash_crear.

  procesar_entrada(especialidades, doctores, pacientes);

  hash_destruir(especialidades);
  hash_destruir(pacientes);
  abb_destruir(doctores);

	return 0;
}
