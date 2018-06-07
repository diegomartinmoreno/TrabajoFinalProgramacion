#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char nombre[30];
int dni;
int edad;
}PERSONA;

void openDb();
void cargaDb ();
void cargaDbPacientes();
void mostrarDb();


int main()
{
    openDb();
    cargaDbPacientes();
    mostrarDb();

}
void openDb (){
    FILE *db;
        puts("BIENVENIDO.\n");
        if ((db=fopen("D:\\pp\\dbprueba.dat","wb"))==NULL){
            puts("PROBLEMAS AL ABRIR ARCHIVO");
        }
        system("pause");
        system("cls");
        fclose(db);
}
void cargaDb (){
    FILE *db;
    PERSONA p1;
    if ((db=fopen("D:\\pp\\dbprueba.dat","ab+"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO.");
    }
        printf("INGRESE NOMBRE Y APELLIDO\n");
        fflush(stdin);
        gets(p1.nombre);
        fwrite(p1.nombre,sizeof(char),30,db);
        printf("INGRESE DNI\n");
        fflush(stdin);
        scanf("%i",&p1.dni);
        fwrite(&p1.dni,sizeof(int),1,db);
        printf("INGRESE EDAD\n");
        fflush(stdin);
        scanf("%i",&p1.edad);
        fwrite(&p1.edad,sizeof(int),1,db);
        fclose(db);
}
void cargaDbPacientes(){
    char control=26;
    puts("Comienza la carga de pacientes.");
    while((control!='n'&&control!='N')){
        cargaDb();
        fflush(stdin);
        puts("Desea continuar S/N\n");
        control=getchar();
    }
}

void mostrarDb(){
    FILE *db;
    PERSONA p1;
    if ((db=fopen("D:\\pp\\dbprueba.dat","rb"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO.");
    }
    system("cls");
    printf("\t\t\t.:BASE DE DATOS:.");
    printf("\n");
    printf("NOMBRE Y APELLIDO\t\tDNI\t\t\t EDAD\n");
    fread(p1.nombre,sizeof(char),30,db);
    printf("%s",p1.nombre);
    fread(&p1.dni,sizeof(int),1,db);
    printf("\t\t%i  ",p1.dni);
    fread(&p1.edad,sizeof(int),1,db);
    printf("\t\t%i  \n",p1.edad);
    fclose(db);
}
