#include "headers.h"

void generarEspecialidad(char resultado[]){
    int i;
    char especs[4][sizeNom] = {{"Cardiologo"},{"Urologo"},{"Obstetra"},{"Clinico"}};
    i=rand() % 4;
    strcpy(resultado, especs[i]);
}

void generarNombre(char resultado[]){
    char nombres[8][sizeNom] = {{"Jose"},{"Pedro"},{"Luis"},{"Omar"},{"Laura"},{"Belen"},{"Estefania"},{"Daiana"}};
    char apellidos[8][sizeNom] = {{"Torres"},{"Gomez"},{"Moreno"},{"Toledo"},{"Perez"},{"Rodriguez"},{"Sanchez"},{"Gutierrez"}};
    int i, j;
    i=rand() % 8;
    j=rand() % 8;
    strcpy(resultado, "\0");
    strcat(resultado, nombres[i]);
    strcat(resultado, " ");
    strcat(resultado, apellidos[j]);
};

void cargarMedsRandom (int cant){
    FILE *db;
    MEDICO m;
    int i;
    if ((db=fopen(pathMed,"ab"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    }
    else{
        for (i=0; i<cant; i++){
            m.matricula=(rand () % 20000000) + 15000000;
            generarNombre(m.nombreApellido);
            generarEspecialidad(m.especialidad);
            m.eliminado=0;
            inicializarTurno(&m);
            fwrite(&m,sizeof(MEDICO),1,db);
        }
    }
    fclose(db);
};

void cargarPacsRandom(int cant){
    FILE *db;
    PACIENTE pac;
    int i;
    if ((db=fopen(pathPac,"ab"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    }
    else{
        for (i=0; i<cant; i++){
            pac.dni=(rand () % 20000000) + 15000000;
            generarNombre(pac.nombreApellido);
            pac.edad=rand() % 91;
            pac.cantAtendido=rand() %5;
            pac.eliminado=0;
            fwrite(&pac,sizeof(PACIENTE),1,db);
        }
    }
    fclose(db);
};
