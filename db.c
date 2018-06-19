#include "headers.h"

void abrirArchivoPacientes(){
    FILE *db;
    //apertura del archivo base de datos para pacientes
    if ((db=fopen(pathPac,"wb"))==NULL){
        puts("Error en apertura de archivo");
    }
    fclose(db);
}
void cargaArchivoPacientes (){
    FILE *db;
    char control;
    PACIENTE pac[100];
    int cantRegistros;
    if ((db=fopen(pathPac,"a+"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO");
    }
    while (control=='s'&&control=='S'){
        cantRegistros=cargaPacientesPrueba(pac);
        fflush(stdin);
        printf("Desea Continuar? S/N\n");
        control=getchar();
    }
}
void cargaPacientes(){
    FILE *db;
    PACIENTE p;
    if ((db=fopen(pathPac,"a+"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO.\n");
    }
     printf("INGRESE NOMBRE Y APELLIDO\n");
     fflush(stdin);
     gets(p.nombreApellido);
     fwrite(&p.nombreApellido,sizeof(char),sizeNom,db);
     printf("INGRESE DNI\n");
     fflush(stdin);
     scanf("%i",&p.dni);
     fwrite(&p.dni,sizeof(int),1,db);
     printf("INGRESE EDAD\n");
     fflush(stdin);
     scanf("%i",&p.edad);
     fwrite(&p.edad,sizeof(int),1,db);
     fclose(db);
}
void generadorTurnos (TURNO a[],int mat){
    int i=0;
    for (int d=0;d<7;d++){
        float inihorario=10;
        for (i;i<10*(d+1);i++){
            a[i].dia=d+1;
            a[i].hora=inihorario;
            a[i].dniPaciente=0;
            a[i].ocupado=0;
            a[i].matMedico=mat;//opcional, en caso de no agregar, borrar parametro int mat.
            inihorario+=0.3;
            float result=inihorario-(int)inihorario;
            if (result>=0.59){
                inihorario=(int)inihorario+1;
            }
        }
    }
}

void generadorHabitaciones(HABITACION a[],PACIENTE b){
    int h=000;
    for (int p=0;p<5;p++){
        for (h=0;h<10*(p+10);h++){
            a[h].nroHabitacion=h+1;
            a[h].ocupado=0;
            if (a[h].ocupado==1){
                printf(".:DATOS DEL PACIENTE INTERNADO EN LA HABITACION %i:.",h);
                printf("%s",b.nombreApellido);
                printf("%i",b.dni);
            }
        }
    }
}
void abrirArchivoHabitaciones(){
    FILE *db;
    if ((db=fopen("D:\\tpFinal\\Habitaciones.dat","wb"))==NULL){
        puts("Error en apertura de archivo");
    }
}
void abrirArchivoMedicos(){
    FILE *db;
    if ((db=fopen(pathMed,"wb"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    }
    fclose(db);
}
void cargaArchivoMedicos(){
    FILE *db;
    char control;
    if ((db=fopen(pathMed,"a+"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO");
    }
    while (control!='n'&&control!='N'){
        cargaMedicos();
        fflush(stdin);
        printf("Desea Continuar? S/N\n");
        control=getchar();
    }
}
void cargaMedicos (){
    FILE *db;
    MEDICO m;
    if ((db=fopen(pathMed,"a+"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    }
    printf("INGRESE NOMBRE Y APELLIDO\n");
    fflush(stdin);
    gets(m.nombreApellido);
    fwrite(&m.nombreApellido,sizeof(char),sizeNom,db);
    printf("INGRESE MATRICULA\n");
    fflush(stdin);
    scanf("%i",&m.matricula);
    fwrite(&m.matricula,sizeof(int),1,db);
    printf("INGRESE ESPECIALIDAD\n");
    fflush(stdin);
    scanf("%i",&m.matricula);
    fwrite(&m.matricula,sizeof(int),1,db);
}

