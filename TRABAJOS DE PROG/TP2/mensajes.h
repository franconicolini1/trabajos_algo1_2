#ifndef __MENSAJES__H_
#define __MENSAJES__H_

#define PACIENTE_ENCOLADO "Paciente %s encolado\n" // ya esta
#define CANTIDAD_PACIENTES_ENCOLADOS "%zu paciente(s) en espera para %s\n" // ya esta
#define ENOENT_PACIENTE "ERROR: no existe el paciente '%s'\n" // ya esta
#define ENOENT_ESPECIALIDAD "ERROR: no existe la especialidad '%s'\n" // ya esta
#define ENOENT_URGENCIA "Error: grado de urgencia no identificado ('%s')\n" // ya esta

#define PACIENTE_ATENDIDO "Se atiende a %s\n" // ya esta
#define SIN_PACIENTES "No hay pacientes en espera\n" // ya esta
#define ENOENT_DOCTOR "ERROR: no existe el doctor '%s'\n" // ya esta

#define DOCTORES_SISTEMA "%zu doctor(es) en el sistema\n" // ya esta
#define INFORME_DOCTOR "%zu: %s, especialidad %s, %zu paciente(s) atendido(s)\n" // ya esta

#define ENOENT_CANT_PARAMS "No se recibieron los 2 (dos) parametros: <archivo doctores> y <archivo pacientes>\n" // Ya lo puse
#define ENOENT_ARCHIVO "No se pudo leer archivo %s\n" // ya esta
#define ENOENT_ANIO "Valor no numerico en campo de anio: %s\n"
#define ENOENT_FORMATO "ERROR: formato de comando incorrecto ('%s')\n"
#define ENOENT_CMD "ERROR: no existe el comando '%s'\n"// ya esta

#define ENOENT_PARAMS "ERROR: cantidad de parametros invalidos para comando '%s'\n" // ya esta

#endif
