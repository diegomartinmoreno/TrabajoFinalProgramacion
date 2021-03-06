#ifndef H_H_INCLUDED
#define H_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

#define sizeNom 50 // Tama�o maximo permitido para los nombres.
#define pisosHab 5 // Cantidad de pisos que tiene la clinica.
#define habXPiso 10 // Cantidad de habitaciones por piso.

//Rutas a bases de datos.
#define pathPac ".\\dataPac"
#define pathMed ".\\dataMed"
#define pathHab ".\\dataHab"
#define pathTurn ".\\dataTurn"

typedef struct{
    int ano;
    int mes;
    int dia;
}FECHA; // Agregado para manejo automatico de alta de internos.

typedef struct{
    char nombreApellido[sizeNom];
    int dni;
    int edad;
    int cantAtendido;
    int cantInternado;
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
    int dniPac;
    FECHA ingreso; // Agregado para manejo automatico de desocupacion.
    FECHA alta; // Agregado para manejo automatico de desocupacion.
}HABITACION;

// procesamientoMenu.c
int inicializarBasesDatos(char path[]);
void iniciarSistema();
void menuOpPacientes();
void menuOpTurnos();
void menuOpInternaciones();
void menuOpMedicos();
void SwitchMenuPrincipal();

////impresiones.c
void listarTurnos(TURNO turno[], int op);
void imprimirTurno(TURNO turno, int op);
void indiceADia(char guardar[], int num);
void imprimirMedicos(MEDICO meds[], int dimL);
void imprimirPacientes(PACIENTE pacs[], int dimL);
void imprimirHabitacion(HABITACION hab);
void imprimirMenuOpPacientes ();
void imprimirMenuOpTurnos ();
void imprimirMenuOpInternaciones ();
void imprimirMenuOpMedicos ();
void imprimirMenuPrincipal ();
void imprimirHeader(char titulo[]);

//buscarPacientes.c
int contarPacientes (FILE *fichero);
PACIENTE buscarXDNI (int buscado);
PACIENTE buscarXNombreApellido (char nomApe[]);
PACIENTE buscarPaciente();

//basePacientes.c
PACIENTE leerPaciente (PACIENTE pac, int nuevo);
void sumarAtencion(int dni);
void sumarInternacion(int dni);
PACIENTE guardarPaciente();
int cargaPacientes ();
void modificarPacientes ();
void eliminarPaciente();
void loopEliminarPacientes();
void listarPacientes();

// baseMedicos.c
int contarMedicos(FILE *fichero);
void eliminarMedico();
void listarMedicos();
void inicializarTurno(MEDICO *med);
void modificarMedico();
void modificarMedicos();
MEDICO leerMedico();
void cargaMedicos();

// buscarMedico.c
int Encontrado(char mat[][sizeNom], char buscado[]);
int determinarEspecialidades (char especialidades[][sizeNom]);
MEDICO imprimirXESPEC(char busqueda[]);
MEDICO imprimirXNOM(char busqueda[]);
MEDICO buscarMed();

//baseHabitaciones.c
void guardarHabitacion(HABITACION guardar, FILE *db);
void inicializadorHabitaciones();
void listarHabitaciones(int ocupado); // Ocupado -> 0 para listar OCUPADAS, 1 para listar LIBRES, 2 para listar TODAS.
void cargarHab();

//buscarHabitaciones.c
void actualizarBase();
int obtenerNumHab();
int obtenerEspecialidades(char especs[pisosHab][sizeNom]);
PACIENTE obtenerInternado();
int comprobarYaInternado(int dni, FILE *db);
HABITACION buscarHabXPac(PACIENTE buscado, FILE *db);
HABITACION buscarHabXNum(int buscado, FILE *db);
HABITACION buscarInterno(int *hit);
void darAlta(HABITACION aux, FILE *db);
void modificarAltaPrevista(HABITACION hab, FILE *db);
void reemplazarPaciente(HABITACION hab, FILE *db);
void opModificacion(HABITACION hab, FILE *db);
void modificarInterno();

//baseTurnos.c
void actualizarTurnos();
void listarTurnosTodos(int op);
void cargarTurno ();
void cancelarTurno();
void guardarTurno (TURNO tur, int matMed);
void atenderPaciente();

//buscarTurnos.c
void imprimirTurnosXMedico ();
TURNO leerTurno(int matMed, int d, float h);
TURNO buscarTur(TURNO tur[], int dia, float hora);


//RANDOM solo a fines de ejemplo
void generarEspecialidad(char resultado[]);
void generarNombre(char resultado[]);
void cargarMedsRandom (int cant);
void cargarPacsRandom(int cant);


#endif // H_H_INCLUDED
