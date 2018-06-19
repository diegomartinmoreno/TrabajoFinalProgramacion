#ifndef H_H_INCLUDED
#define H_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

#define sizeNom 50

const char pathPac[]=".\\dataPac";
const char pathMed[]=".\\dataMed";
const char pathHab[]=".\\dataHab";

typedef struct{
    char nombreApellido[sizeNom];
    int dni;
    int edad;
    int cantAtendido;
    int eliminado;
}PACIENTE;

typedef struct{
    int dniPaciente;
    int dia;
    float hora;
    int ocupado;
    int matMedico;
}TURNO;

typedef struct{
    char nombreApellido[sizeNom];
    int matricula;
    char especialidad[sizeNom];
    int eliminado;
    TURNO listaTurnos[100];
}MEDICO;

typedef struct{
    int nroHabitacion;
    int ocupado;
    PACIENTE paciente;
}HABITACION;


void iniciarSistema();

////impresiones.c
void imprimirMenuPrincipal ();
void imprimirHeader(char titulo[]);


////buscar pacientes.c
int contarPacientes (FILE *fichero);
PACIENTE buscarXDNI (int buscado);
PACIENTE buscarXNombreApellido (char nomApe[]);
PACIENTE buscarPaciente();

// banco de prueba.c
void subMenuOpc3(int opc); //REGISTRO DE INTERNACIONES
void menuOp1swt(int op); // REGISTRO DE PACIENTES

// buscar Medico.c
int Encontrado(char mat[][sizeNom], char buscado[], int dimL);
int determinarEspecialidades (char especialidades[][sizeNom]);
void imprimirMedicos(MEDICO meds[], int dimL);
void ordenarMedicos(MEDICO meds[], int dimL);
void imprimirXESPEC(char busqueda[]);
void imprimirXNOM(char busqueda[]);
void buscarMed(char busqueda[]);

// base Medicos
/*Al inicio de la base de datos de Medicos hay un dato entero (4bytes), cuyo valor indica 1=los turnos han sido inicializados, 0= los turnos guardan basura.
*/
void inicializadorTurnos ();


#endif // H_H_INCLUDED
