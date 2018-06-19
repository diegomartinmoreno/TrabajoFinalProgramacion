#include "headers.h"

int cargaPacientes (PACIENTE pac,int dim){
    FILE *db;
    char opc;
    int i=0;
    if ((db=fopen(pathPac,"a+"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");}
    else{
        do{
            pac.eliminado=0;
            printf("INGRESE NOMBRE Y APELLIDO\n");
            fflush(stdin);
            gets(pac.nombreApellido);
            printf("INGRESE DNI\n");
            fflush(stdin);
            scanf("%i",&pac.dni);
            printf("INGRESE EDAD\n");
            fflush(stdin);
            scanf("%i",&pac.edad);
            fwrite(&pac,sizeof(PACIENTE),1,db);
            printf("Desea continuar? S/N \n");
            fflush(stdin);
            opc=getchar();
            i++;
        }while (i<100 && (opc=='s'||opc=='S'));
    }
    fclose(db);
    return i;
}
void mostrarPaciente(){
    FILE *db;
    PACIENTE p;
    if((db=fopen(pathPac,"rb"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    } else{
        fread(&p,sizeof(PACIENTE),1,db);
        printf("\nNOMBRE Y APELLIDO: %s",p.nombreApellido);
        printf("\t\tDNI: %i",p.dni);
        printf("\t\tEDAD: %i",p.edad);
        printf("\t\tCANTIDAD DE VECES ATENDIDO: %i",p.cantAtendido);
        printf("\t\tESTADO: %i 1.ACTIVO 2.ELIMINADO",p.eliminado);
    }
    fclose(db);
}

