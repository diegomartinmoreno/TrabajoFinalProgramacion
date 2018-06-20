#include "headers.h"

int contarMedicos(FILE *fichero){
    int resultado;
    fseek(fichero, 0, SEEK_END);
    resultado=ftell(fichero)/sizeof(MEDICO);
    fseek(fichero, 0, SEEK_SET);
    return resultado;
};

void listarMedicos(){
    int i, cantMed;
    FILE *fichero;
    MEDICO med;
    system("cls");
    fichero=fopen(pathMed, "rb");
    if (fichero==0){
        perror("No pudo acceder a base de datos de Medicos.");
    }else{
        cantMed=contarMedicos(fichero);
        for (i=0; i<cantMed; i++){
            fread(&med, sizeof(MEDICO), 1, fichero);
            imprimirMedicos(&med, 1);
        }
    }
    fclose(fichero);
};

void inicializarTurno(MEDICO *med){
    int i, d;
    for (d=0;d<7;d++){
        float inihorario=10;
        for (i=0;i<10;i++){
            med->listaTurnos[d*i].dia=d+1;
            med->listaTurnos[d*i].hora=inihorario;
            med->listaTurnos[d*i].dniPaciente=0;
            med->listaTurnos[d*i].ocupado=0;
            med->listaTurnos[d*i].matMedico=med->matricula;
            inihorario+=0.3;
            float result=inihorario-(int)inihorario;
            if (result>=0.59){
                inihorario=(int)inihorario+1;
            }
        }
    }
};

MEDICO leerMedico(){
    MEDICO m;
    printf("INGRESE NOMBRE Y APELLIDO\n");
    fflush(stdin);
    gets(m.nombreApellido);
    printf("INGRESE MATRICULA\n");
    fflush(stdin);
    scanf("%i",&m.matricula);
    printf("INGRESE ESPECIALIDAD\n");
    fflush(stdin);
    gets(m.especialidad);
    inicializarTurno(&m);
    m.eliminado=0;
    return m;
};

void cargaMedicos(){
    char control='s';
    FILE *db;
    MEDICO m;
    if ((db=fopen(pathMed,"a+b"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    }
    else{
        while (control=='s'||control=='S'){
            m=leerMedico();
            fwrite(&m,sizeof(MEDICO),1,db);
            fflush(stdin);
            printf("Desea Continuar? S/N\n");
            control=getchar();
        }
    }
    fclose(db);
};

void eliminarMedico(){
    char control='s';
    MEDICO med, aux;
    int cantMed, i=0, encontrado=0;
    FILE *fichero;
    fichero=fopen(pathMed, "r+b");
    if(fichero==NULL){
        perror("Error al acceder a la base de datos de Medicos.");
    }else{
        cantMed=contarMedicos(fichero);
        while (control=='s'||control=='S'){
            fclose(fichero);
            med=buscarMed();
            fichero=fopen(pathMed, "r+b");
            fseek(fichero,0,SEEK_SET);
            if (med.eliminado!=1){
                while (i<cantMed&&encontrado==0){
                    i++;
                    fread(&aux, sizeof(MEDICO), 1, fichero);
                    if (med.matricula==aux.matricula)
                        encontrado=1;
                }
                fseek(fichero, -sizeof(MEDICO), SEEK_CUR);
                strcpy(med.nombreApellido, "ELIMINADO");
                med.eliminado=1;
                fwrite(&med, sizeof(MEDICO), 1, fichero);
                puts("Su seleccion se ha eliminado con exito.");
            } else{
                puts("No se pudo eliminar medico ya que no se encontro en base de datos.");
            }
            puts("Desea eliminar otro medico de la nomina? S/N");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    fclose(fichero);
};

void modificarMedicos(){
    char control='s';
    while (control=='s'||control=='S'){
            modificarMedico();
            puts("Desea modificar otro medico? S/N");
            fflush(stdin);
            scanf("%c", &control);
    }
};

void modificarMedico(){
    MEDICO med, aux;
    med=buscarMed();
    int cantMed, i=0, encontrado=0;
    FILE *fichero;
    fichero=fopen(pathMed, "r+b");
    if(fichero==NULL){
        perror("Error al acceder a la base de datos de Medicos.");
    }else{
        if (med.eliminado==0){
            cantMed=contarMedicos(fichero);
            while (i<cantMed&&encontrado==0){
                fread(&aux, sizeof(MEDICO), 1, fichero);
                i++;
                if(aux.matricula==med.matricula){
                    encontrado=1;}
            }
            fseek(fichero, -sizeof(MEDICO), SEEK_CUR);
            puts("Ingrese modificaciones:");
            aux=leerMedico();
            fwrite(&aux, sizeof(MEDICO), 1, fichero);
        } else{
            puts("El medico que desea modificar no se encuentra en la base de datos.");
        }
    }
    fclose(fichero);
};
