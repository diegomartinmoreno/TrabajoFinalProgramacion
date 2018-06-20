#include "headers.h"

int contarMedicos(FILE *fichero){
    int resultado;
    fseek(fichero, 0, SEEK_END);
    resultado=ftell(fichero)/sizeof(MEDICO);
    fseek(fichero, 0, SEEK_SET);
    return resultado;
}

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
}

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
}

void cargaMedicos(){
    char control='s';
    while (control=='s'||control=='S'){
        cargaMedico();
        fflush(stdin);
        printf("Desea Continuar? S/N\n");
        control=getchar();
    }
}

void cargaMedico(){
    FILE *db;
    MEDICO m;
    if ((db=fopen(pathMed,"a+b"))==NULL){
        puts("ERROR EN APERTURA DE ARCHIVO\n");
    }
    else{
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
        fwrite(&m,sizeof(MEDICO),1,db);
    }
    fclose(db);
}

void eliminarMedico(){
    char control='s';
    MEDICO med, aux;
    med=buscarMed();
    int cantMed, i=0, encontrado=0;
    FILE *fichero;
    fichero=fopen(pathMed, "r+b");
    cantMed=contarMedicos(fichero);
    if(fichero==NULL){
        perror("Error al acceder a la base de datos de Medicos.");
    }else{
        while (control=='s'||control=='S'){
            while (i<cantMed&&encontrado==0){
                i++;
                fread(&aux, sizeof(MEDICO), 1, fichero);
                if (med.matricula==aux.matricula)
                    encontrado=1;
            }
            if (med.matricula==aux.matricula) {
                fseek(fichero, -sizeof(MEDICO), SEEK_CUR);
                strcpy(med.nombreApellido, "ELIMINADO");
                med.eliminado=1;
                fwrite(&med, sizeof(MEDICO), 1, fichero);
            }
            else{
                puts("No se pudo eliminar medico ya que no se encontro en base de datos.");
            }
            puts("Desea eliminar otro medico de la nomina? S/N");
            fflush(stdin);
            scanf("%c", &control);
        }
    }
    fclose(fichero);
}
