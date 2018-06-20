#include "headers.h"


PACIENTE cargaPaciente (){
    PACIENTE pac;
    pac.eliminado=0;
    pac.cantAtendido=0;
    printf("INGRESE NOMBRE Y APELLIDO\n");
    fflush(stdin);
    gets(pac.nombreApellido);
    printf("INGRESE DNI\n");
    fflush(stdin);
    scanf("%i",&pac.dni);
    printf("INGRESE EDAD\n");
    fflush(stdin);
    scanf("%i",&pac.edad);
    return pac;
}

void modificarPacientes (){
    char control='s';
    PACIENTE pac, aux;
    FILE *db;
    int encontrado=0, i=0, cantPac;
    db=fopen(pathPac, "r+b");
    if (db!=NULL)
    {
        puts("Ingrese el nombre completo o documento del paciente que desea modificar:");
        while(control=='s'||control=='S'){
            pac=buscarPaciente();
            cantPac=contarPacientes(db);
            while (encontrado==0&&i<cantPac){
                i++;
                fread(&aux, sizeof(PACIENTE), 1, db);
                if (pac.dni==aux.dni){
                    encontrado=1;
                }
            }
            if (pac.dni==aux.dni){
                fseek(db, -sizeof(PACIENTE), SEEK_CUR);
                aux=cargaPaciente();
                fwrite(&aux, sizeof(PACIENTE), 1, db);
            } else {
                puts("El paciente que desea modificar no se encuentra en la base de datos.");
            }
            puts("Desea modificar otro paciente? S/N");
            fflush(stdin);
            control=getchar();
        }
    }else {
        puts("ERROR EN APERTURA DE ARCHIVO PACIENTES.");
    }
    fclose(db);
}

void eliminarPacientes(){
    char control='s';
    PACIENTE pac, aux;
    FILE *db;
    int encontrado=0, i=0, cantPac;
    db=fopen(pathPac, "r+b");
    if (db!=NULL){
        while(control=='s'||control=='S'){
            puts("Ingrese el nombre completo o documento del paciente que desea eliminar:");
            pac=buscarPaciente();
            cantPac=contarPacientes(db);
            while (encontrado==0&&i<cantPac){
                i++;
                fread(&aux, sizeof(PACIENTE), 1, db);
                if (pac.dni==aux.dni){
                    encontrado=1;
                }
            }
            if (pac.dni==aux.dni){
                fseek(db, -sizeof(PACIENTE), SEEK_CUR);
                aux.eliminado=1;
                fwrite(&aux, sizeof(PACIENTE), 1, db);
                puts("Eliminado exitosamente.");
            } else {
                puts("El paciente que desea modificar no se encuentra en la base de datos.");
            }
            puts("Desea eliminar otro paciente? S/N");
            fflush(stdin);
            control=getchar();
        }
    }else {
        puts("ERROR EN APERTURA DE ARCHIVO PACIENTES.");
    }
    fclose(db);
}

int cargaPacientes (){
    FILE *db;
    char opc;
    PACIENTE pac;
    int i=0;
    db=fopen(pathPac,"ab");
    if (db==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO PACIENTES.");
    }else {
        do{
            pac=cargaPaciente();
            fwrite(&pac, sizeof(PACIENTE), 1, db);
            i++;
            printf("Desea continuar? S/N \n");
            fflush(stdin);
            opc=getchar();
        }while (opc=='s'||opc=='S');
    }
    fclose(db);
    return i;
}
