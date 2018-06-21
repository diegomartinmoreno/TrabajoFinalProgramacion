#include "headers.h"


PACIENTE leerPaciente (){
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

void sumarAtencion(int dni){
    PACIENTE aux;
    int hit=0, i=0, cantPac;
    aux=buscarXDNI(dni);
    FILE *db;
    db=fopen(pathPac,"r+b");
    if (db==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO PACIENTES.");
    }else {
        cantPac=contarPacientes(db);
        while(i<cantPac&&hit==0){
            fread(&aux, sizeof(PACIENTE), 1, db);
            i++;
            if(aux.dni==dni)
                hit=1;
        }
        if (hit){
            aux.cantAtendido++;
            fseek(db, -sizeof(PACIENTE), SEEK_CUR);
            fwrite(&aux, sizeof(PACIENTE), 1, db);
        }else{puts("DNI no coincide con ningun paciente, error en atencion++.");}
    }
    fclose(db);
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
                aux=leerPaciente();
                fwrite(&aux, sizeof(PACIENTE), 1, db);
                puts("Paciente modificado exitosamente.");
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
    eliminarPaciente(aux.dni);
}

void eliminarPaciente(int dni){
    int cantPac, encontrado=0, i=0;
    FILE *db;
    PACIENTE aux;
    db=fopen(pathPac, "r+b");
    if(db==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO PACIENTES.");
    }else{
        cantPac=contarPacientes(db);
        while (encontrado==0&&i<cantPac){
            i++;
            fread(&aux, sizeof(PACIENTE), 1, db);
            if (dni==aux.dni){
                encontrado=1;
            }
        }
        if (dni==aux.dni){
            fseek(db, -sizeof(PACIENTE), SEEK_CUR);
            aux.eliminado=1;
            fwrite(&aux, sizeof(PACIENTE), 1, db);
        } else {
            puts("El paciente que desea modificar no se encuentra en la base de datos.");
        }
    }
    fclose(db);
}

void loopEliminarPacientes(){
    char control='s';
    PACIENTE pac;
    while(control=='s'||control=='S'){
        puts("Ingrese el nombre completo o documento del paciente que desea eliminar:");
        pac=buscarPaciente();
        eliminarPaciente(pac.dni);
        puts("Desea eliminar otro paciente? S/N");
        fflush(stdin);
        control=getchar();
    }
}

PACIENTE guardarPaciente(){
    PACIENTE pac, aux;
    pac=leerPaciente();
    aux=buscarXDNI(pac.dni);
    FILE *db;
    db=fopen(pathPac,"ab");
    if (db==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO PACIENTES.");
    }else {
        if(aux.eliminado==1)
            fwrite(&pac, sizeof(PACIENTE), 1, db);
        else
            puts("La persona que intenta cargar ya se encuentra en la base de datos.");
    }
    fclose(db);
    return pac;
}

int cargaPacientes (){
    char opc;
    int i=0;
    do{
        guardarPaciente();
        i++;
        printf("Desea continuar? S/N \n");
        fflush(stdin);
        opc=getchar();
    }while (opc=='s'||opc=='S');
    return i;
}
